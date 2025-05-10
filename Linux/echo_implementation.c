#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100

/*int main(int argc, char ** argv)
{
       int arg_num = 1;


        while( arg_num < argc-1)
        {


		if(write(1, *(argv + arg_num), strlen(*(argv + arg_num) ) ) < 0)
                {
                        printf("write failed\n");
                        exit(-3);
                }
		
               if(write(1," ", strlen(" ") )  < 0)
               {
                        printf("write failed\n");
                        exit(-3);
                }
    
	        	arg_num++;
            	}

		        if(write(1, *(argv + arg_num), strlen(*(argv + arg_num) ) ) < 0)
                {
                        printf("write failed\n");
                        exit(-3);
                }
                if(write(1,"\n", strlen("\n") )  < 0)
                {
                        printf("write failed\n");
                        exit(-3);
                }
	
	return 0;
}


