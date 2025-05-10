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
	int fd ;

	if(argc > 2)
	{
		printf("too many arguments\n");
	}

	fd = open(*(argv+1), O_RDONLY);
	if (fd < 0)
	{
		printf("couldn't open a file\n");
		exit(-2);	
	}
	
	while( (num_read = read(fd,buff, COUNT) ) > 0)
	{
	
		if(write(1,buff,num_read) < 0)
		{
			printf("write failed\n");
			exit(-3);
		}


	}
	return 0;
	
	
}
