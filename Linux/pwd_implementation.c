#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 1000

int main(int argc, char ** argv)
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
		printf("%s\n", wd_arr ) ;
	}


	return 0;
	
	
}
