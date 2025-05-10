#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100

int main(int argc, char ** argv)
{
        char buff[COUNT];
        int num_read;
        int fd, fd2;

        if(argc > 3)
        {
                printf("too many arguments\n");
        }

        fd = open(*(argv+1), O_RDONLY);
        if (fd < 0)
        {
                printf("couldn't open a file\n");
                exit(-2);
        }
	
	fd2 = open(*(argv+2), O_CREAT|O_WRONLY|O_TRUNC,0644);
        if (fd2 < 0)
        {
                printf("couldn't open a file\n");
                exit(-3);
        }


        while( (num_read = read(fd,buff, COUNT) ) > 0)
        {

                if(write(fd2,buff,num_read) < 0)
                {
                        printf("write failed\n");
                        exit(-4);
                }


        }
}
