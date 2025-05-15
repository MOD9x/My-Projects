#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_ARGS 64
#define MAX_CMD_LENGTH 1024
#define MAX_VARS 100

typedef struct {
    char *name;
    char *value;
    bool exported;
} ShellVar;

ShellVar variables[MAX_VARS];
int var_count = 0;

// Function prototypes
void my_printer(const char *str);
void pwd_task();
int cd_task(char *path);
void echo_task(char **args);
char **parse_command(char *cmd);
void free_args(char **args);
int execute_command(char **args);
int handle_assignment(char *cmd);
int handle_export(char **args);
//char *expand_variables(char *input);
//char **expand_args(char **args);
void add_variable(const char *name, const char *value, bool exported);
char *get_variable(const char *name);
bool is_valid_var_name(const char *name);
int setup_redirections(char **args, int *in_fd, int *out_fd, int *err_fd);

// Function to print string to stdout
void my_printer(const char *str) {
    if (write(STDOUT_FILENO, str, strlen(str)) < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

// Function to handle pwd command
void pwd_task() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        my_printer(cwd);
        my_printer("\n");
    } else {
        perror("getcwd");
    }
}

// Function to handle cd command
int cd_task(char *path) {
    if (path == NULL || strcmp(path, "") == 0) {
        path = getenv("HOME");
        if (path == NULL) {
            my_printer("cd: No home directory\n");
            return -1;
        }
    }
    
    if (chdir(path) == -1) {
        my_printer("cd: ");
        my_printer(path);
        my_printer(": ");
        my_printer(strerror(errno));
        my_printer("\n");
        return -1;
    }
    return 0;
}

// Function to handle echo command
void echo_task(char **args) {
    
    for (int i = 1; args[i] != NULL; i++) {
        my_printer(args[i]);
        if (args[i+1] != NULL) {
            my_printer(" ");
        }
    }
        my_printer("\n");
}

// Function to parse command line into arguments
char **parse_command(char *cmd) {
    char temp;
    char *dollar_sign;
    char *token;
    char *cmd_copy;
    char *var_start;
    char *var_end;
    char *value;
    char **args = (char **)malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cmd_copy = strdup(cmd);  // Create a copy since strtok modifies its input
    if (!cmd_copy) {
        free(args);
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    token = strtok(cmd_copy, " ");
    int i = 0;
    
    while (token != NULL && i < MAX_ARGS - 1) {
        // Check if token contains a variable reference
        dollar_sign = strchr(token, '$');
        if (dollar_sign) {
            // Handle variable expansion
            var_start = dollar_sign + 1;
            var_end = var_start;
            
            // Extract variable name (alphanumeric + underscore)
            while (isalnum(*var_end) || *var_end == '_') {
                var_end++;
            }
            
            // Temporarily terminate the variable name
            temp = *var_end;
            *var_end = '\0';
            
            // Get variable value
            value = get_variable(var_start);
            
            // Restore original character
            *var_end = temp;
            
            // Calculate lengths for the new string
            size_t prefix_len = dollar_sign - token;
            size_t var_len = value ? strlen(value) : 0;
            size_t suffix_len = strlen(var_end);
            size_t total_len = prefix_len + var_len + suffix_len;
            
            // Allocate space for expanded string
            args[i] =(char*) malloc(total_len + 1);
            if (!args[i]) {
                // Cleanup on failure
                for (int j = 0; j < i; j++) free(args[j]);
                free(args);
                free(cmd_copy);
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            
            // Build the expanded string
            strncpy(args[i], token, prefix_len);
            if (value) {
                strcpy(args[i] + prefix_len, value);
            }
            strcpy(args[i] + prefix_len + var_len, var_end);
        } else {
            // Regular token
            args[i] = strdup(token);
        }

        if (!args[i]) {
            // Cleanup on failure
            for (int j = 0; j < i; j++) free(args[j]);
            free(args);
            free(cmd_copy);
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        
        i++;
        token = strtok(NULL, " ");
    }
    
    args[i] = NULL;  // NULL-terminate the array
    free(cmd_copy);   // Free our working copy
    return args;
}

// Function to free memory allocated for arguments
void free_args(char **args) {
    if (!args) return;
    
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

// Function to execute external commands
int execute_command(char **args) {
    int in_fd = -1, out_fd = -1, err_fd = -1;
    
    // Handle redirections first
    if (setup_redirections(args, &in_fd, &out_fd, &err_fd) < 0) {
        return -1;
    }
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        // Close any opened file descriptors before returning
        if (in_fd != -1) close(in_fd);
        if (out_fd != -1) close(out_fd);
        if (err_fd != -1) close(err_fd);
        return -1;
    } else if (pid == 0) {
        // Child process
        
        // Apply input redirection
        if (in_fd != -1) {
            if (dup2(in_fd, STDIN_FILENO) < 0) {
                perror("dup2 stdin");
                exit(EXIT_FAILURE);
            }
            close(in_fd);
        }
        
        // Apply output redirection
        if (out_fd != -1) {
            if (dup2(out_fd, STDOUT_FILENO) < 0) {
                perror("dup2 stdout");
                exit(EXIT_FAILURE);
            }
            close(out_fd);
        }
        
        // Apply error redirection
        if (err_fd != -1) {
            if (dup2(err_fd, STDERR_FILENO) < 0) {
                perror("dup2 stderr");
                exit(EXIT_FAILURE);
            }
            close(err_fd);
        }
        
        execvp(args[0], args);
        // If execvp returns, there was an error
        my_printer(args[0]);
        my_printer(": command not found\n");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        
        // Close file descriptors in parent
        if (in_fd != -1) close(in_fd);
        if (out_fd != -1) close(out_fd);
        if (err_fd != -1) close(err_fd);
        
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return 1;
    }
    return 0;
}

// Handle variable assignment
int handle_assignment(char *cmd) {
    //char *cmd_dup = strdup(cmd);
    char *equal_sign = strchr(cmd, '=');
    if (equal_sign == NULL) {
        return -1; // Not an assignment
    }
    
    // Check for spaces around equal sign
    if (equal_sign != cmd && *(equal_sign - 1) == ' ') {
        return -1;
    }
    if (*(equal_sign + 1) == ' ') {
        return -1;
    }
    
    // Split into name and value
    *equal_sign = '\0';
    char *var_name = cmd;
    char *var_value = equal_sign + 1;
    
    // Validate variable name
    if (!is_valid_var_name(var_name)) {
        my_printer("Invalid variable name\n");
        return -1;
    }
    
    add_variable(var_name, var_value, false);
        *equal_sign = '=';
    return 0;
}

// Handle export command
int export_task(const char *name){
    char *env_var;
    int i;
    for (i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].exported = true;
            env_var =(char *) malloc(strlen(variables[i].name) + strlen(variables[i].value) + 2);
            sprintf(env_var, "%s=%s", variables[i].name, variables[i].value);
            putenv(env_var);
        }
    }
    return 0;
}

int handle_export(char **args) {
    if (args[1] == NULL) {
        // Print all exported variables
        for (int i = 0; i < var_count; i++) {
            if (variables[i].exported) {
                my_printer(variables[i].name);
                my_printer("=");
                my_printer(variables[i].value);
                my_printer("\n");
            }
        }
        return 0;
    }
    
    // Mark variable as exported
    /*for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, args[1]) == 0) {
            variables[i].exported = true;
            
            // Also set in environment
            char *env_var =(char *) malloc(strlen(variables[i].name) + strlen(variables[i].value) + 2);
            sprintf(env_var, "%s=%s", variables[i].name, variables[i].value);
            putenv(env_var);
            
            return 0;
        }
    }
    */
    my_printer("export: ");
    my_printer(args[1]);
    my_printer(": no such variable\n");
    return -1;
}


// Add a variable to our storage
void add_variable(const char *name, const char *value, bool exported) {
    // Check if variable already exists
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            free(variables[i].value);
            variables[i].value = strdup(value);
            variables[i].exported = exported;
            return;
        }
    }
    
    // Add new variable
    if (var_count < MAX_VARS) {
        variables[var_count].name = strdup(name);
        variables[var_count].value = strdup(value);
        variables[var_count].exported = exported;
        var_count++;
    }
}

// Get a variable's value
char *get_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    return NULL;
}

// Check if a variable name is valid
bool is_valid_var_name(const char *name) {
    if (!name || !*name || isdigit(*name)) {
        return false;
    }
    
    for (const char *p = name; *p; p++) {
        if (!isalnum(*p) && *p != '_') {
            return false;
        }
    }
    return true;
}

// New function to handle redirections
int setup_redirections(char **args, int *in_fd, int *out_fd, int *err_fd) {
    *in_fd = -1;
    *out_fd = -1;
    *err_fd = -1;
    
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            // Input redirection
            if (args[i+1] == NULL) {
                my_printer("syntax error: no input file specified\n");
                return -1;
            }
            *in_fd = open(args[i+1], O_RDONLY);
            if (*in_fd < 0) {
                my_printer("cannot access ");
                perror(args[i+1]);
                return -1;
            }
            // Remove redirection tokens from args
            free(args[i]);
            free(args[i+1]);
            for (int j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i--; // Adjust index after removal
        }
        else if (strcmp(args[i], ">") == 0) {
            // Output redirection
            if (args[i+1] == NULL) {
                my_printer("syntax error: no output file specified\n");
                return -1;
            }
            *out_fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*out_fd < 0) {
                perror(args[i+1]);
                return -1;
            }
            free(args[i]);
            free(args[i+1]);
            for (int j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i--;
        }
        else if (strcmp(args[i], "2>") == 0) {
            // Error redirection
            if (args[i+1] == NULL) {
                my_printer("syntax error: no error file specified\n");
                return -1;
            }
            *err_fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*err_fd < 0) {
                perror(args[i+1]);
                return -1;
            }
            free(args[i]);
            free(args[i+1]);
            for (int j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i--;
        }
    }
    return 0;
}

// Main shell function
int microshell_main(int argc, char *argv[]) {
     int in_fd, out_fd, err_fd;
    char cmd[MAX_CMD_LENGTH];
    char **args;
    
    while (1) {
       // my_printer("Pico shell prompt > ");
        
        // Read command
        if (!fgets(cmd, sizeof(cmd), stdin)) {
            if (feof(stdin)) {
               // my_printer("\nGood Bye :)\n");
                break;
            } else {
                perror("fgets");
                continue;
            }
        }
        
        // Remove trailing newline
        cmd[strcspn(cmd, "\n")] = '\0';
        
        // Skip empty commands
        if (strcmp(cmd, "") == 0) {
            continue;
        }
        
        // Parse command into arguments
        args = parse_command(cmd);
     
          // Handle redirections first
        if (setup_redirections(args, &in_fd, &out_fd, &err_fd) < 0) {
          return -1;
         }
         
                 // Apply input redirection
        if (in_fd != -1) {
            if (dup2(in_fd, STDIN_FILENO) < 0) {
                perror("dup2 stdin");
                exit(EXIT_FAILURE);
            }
            close(in_fd);
        }
        
        // Apply output redirection
        if (out_fd != -1) {
            if (dup2(out_fd, STDOUT_FILENO) < 0) {
                perror("dup2 stdout");
                exit(EXIT_FAILURE);
            }
            close(out_fd);
        }
        
        // Apply error redirection
        if (err_fd != -1) {
            if (dup2(err_fd, STDERR_FILENO) < 0) {
                perror("dup2 stderr");
                exit(EXIT_FAILURE);
            }
            close(err_fd);
        }/**/
        
        // Handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            free_args(args);
            my_printer("Good Bye\n");
            return 0;
        } else if (strcmp(args[0], "pwd") == 0) {
            pwd_task();
        } else if (strcmp(args[0], "cd") == 0) {
            if(cd_task(args[1]) == (-1))
            {
                return -1;
            }
        } else if (strcmp(args[0], "echo") == 0) {
            echo_task(args);
        } else if (strcmp(args[0], "export") == 0) {
            export_task(args[1]);
                       my_printer(args[1]);
                       my_printer("=");
                       my_printer(get_variable(args[1]));
            return 0;
        }
         else {
             
           if(handle_assignment(args[0])== 0){
             continue;
           }
                    
            // Execute external command
            if(execute_command(args) == 1){
                free_args(args);
                return -1;
            }
        }
        
        free_args(args);
    }
    
    return 0;
}