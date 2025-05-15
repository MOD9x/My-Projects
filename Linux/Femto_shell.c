#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

#define ARG_SIZE 1000
#define CMD_SIZE 100


char * Femto_ptr;

int echo_task(void)
{
                if(write(1, Femto_ptr, strlen(Femto_ptr) )  < 0)
                {
                        printf("write failed\n");
                        exit(-3);
                }

}

int main(int argc, char ** argv)
{
         char Femto_shell_arg[ARG_SIZE], Femto_shell_cmd[CMD_SIZE],i=0;
         
        while(1)
        {
		printf("Femto shell prompt >");
		while( (Femto_ptr = fgets(Femto_shell_arg,ARG_SIZE,stdin) ) != NULL);
		if( !(feof(stdin)) )
		{
			printf("EOF");
			continue;
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
				i= echo_task();
				if( (feof(stdin) ) )
					{return 0;}
		}

		else if( !(strcmp(Femto_shell_cmd,"exit") ) )
                {
                                printf("Good Bye :)\n");
				break;
                }

		else if( !(strcmp(Femto_shell_cmd,"\0") ) )
                {
                                //printf("\n");
                }


		else
		{
			printf("invalid command\n");
		}
	}

}



