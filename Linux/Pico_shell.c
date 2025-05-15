#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

#define ARG_SIZE 11000
#define CMD_SIZE 100
#define COUNT 11000


char * Femto_ptr;


int my_printer(char * printer_str)
{
	   int count, count2;
	   char space_flag=0;
		count2 = strlen(printer_str);
                while(  count< count2)
                {
                    if( space_flag == 1)
                    {
		       count++;
                       printer_str++;
		        if( (*(printer_str) ) == ' ')
                        {
                                space_flag = 1;
				continue;
                        }

                        else
                        {
                                space_flag = 0;
                        }
	             }

		     if( write(1, printer_str, 1 ) < 0)
                        {
                         printf("write failed\n");
                         exit(-3);
                        }

                     if( (*(printer_str) ) == ' ')
                        {
                                space_flag = 1;
                                continue;
			}

		       count++;
                       printer_str++;
                }

}

int pwd_task(void)
{
        char wd_arr[COUNT];
        char * wd_ptr;

        wd_ptr = getcwd(wd_arr,COUNT);
        if( wd_ptr == NULL)
        {
                printf("error occured\n");
        }

        else
        {
		my_printer(wd_arr);
		my_printer("\n");
        }

        return 0;
}


int echo_task(void)
{
		my_printer(Femto_ptr);
                my_printer("\n");
}

int main(int argc, char *argv[])
{
         char Femto_shell_arg[ARG_SIZE], Femto_shell_cmd[CMD_SIZE],i=0;

        while(1)
        {
                printf("Dahshan shell -> ");

                Femto_ptr = fgets(Femto_shell_arg,ARG_SIZE,stdin);

                if( !(feof(stdin)) )
                {
                }

                else
                {
                                printf("EOF\n");
                }

                i=0;
                while( (*Femto_ptr != '\n') && (*Femto_ptr !=' ') )
                {
                        Femto_shell_cmd[i] = *Femto_ptr;
                        Femto_ptr++;
                        i++;
                }

                Femto_shell_cmd[i]='\0';
                Femto_ptr++;

                if( !(strcmp(Femto_shell_cmd,"echo") ) )
                {
                        echo_task();
                }

                else if( !(strcmp(Femto_shell_cmd,"exit") ) )
                {
                write(1, "Good Bye\n", strlen("Good Bye\n") );
                return 0;
                }

                else if( !(strcmp(Femto_shell_cmd,"\0") ) )
                {}

        	else if( !(strcmp(Femto_shell_cmd,"pwd") ) )
                {
                    pwd_task();
                }

                else
                {
                            my_printer("command not found\n");
                            return -1;
                }
        }
    return -1;
}


