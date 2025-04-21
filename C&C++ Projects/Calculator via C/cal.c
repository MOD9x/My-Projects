/*
 * cal.c
 *
 *  Created on: Sep 4, 2024
 *      Author: mod_n
 */

#include<stdio.h>

enum
{
	char_type,short_type,int_type,float_type
};

void *sum(void *a ,void *b ,int type)
{
	switch( type )
	{
		case char_type :
			*(char *)a = *(char *)a+ *(char *)b;
			return (char*)a;
		break;

		case short_type :
			*(short *)a = *(short *)a+ *(short *)b;
			return (short*)a;
		break;

		case int_type :
			*(int *)a = *(int *)a+ *(int *)b;
			return (int*)a;
		break;

		case float_type :
			*(float *)a = *(float *)a+ *(float *)b;
			return (float*)a;
		break;
	}

	return 0 ;
}

void *sub(void *a ,void *b ,int type)
{
	switch( type )
	{
		case char_type :
			*(char *)a = *(char *)a- *(char *)b;
			return (char*)a;
		break;

		case short_type :
			*(short *)a = *(short *)a- *(short *)b;
			return (short*)a;
		break;

		case int_type :
			*(int *)a = *(int *)a- *(int *)b;
			return (int*)a;
		break;

		case float_type :
			*(float *)a = *(float *)a- *(float *)b;
			return (float*)a;
		break;
	}

	return 0 ;
}

void *mul(void *a ,void *b ,int type)
{
	switch( type )
	{
		case char_type :
			*(char *)a = ( *(char *)a )* (*(char *)b);
			return (char*)a;
		break;

		case short_type :
			*(short *)a = ( *(short *)a )* (*(short *)b);
			return (short*)a;
		break;

		case int_type :
			*(int *)a = ( *(int *)a )* (*(int *)b);
			return (int*)a;
		break;

		case float_type :
			*(float *)a = ( *(float *)a )* (*(float *)b);
			return (float*)a;
		break;
	}

	return 0 ;
}

void *div(void *a ,void *b ,int type)
{
	switch( type )
	{
		case char_type :
			*(char *)a = ( *(char *)a )/ (*(char *)b);
			return (char*)a;
		break;

		case short_type :
			*(short *)a = ( *(short *)a )/ (*(short *)b);
			return (short*)a;
		break;

		case int_type :
			*(int *)a = ( *(int *)a )/ (*(int *)b);
			return (int*)a;
		break;

		case float_type :
			*(float *)a = ( *(float *)a )/ (*(float *)b);
			return (float*)a;
		break;
	}

	return 0 ;
}




int main()
{
	float a , b ;
	int type;

	void (*p1) (void *a ,void *b ,int type);


	a=10.3;
	b=23.6;
	type = float_type;

	p1 = sum(&a,&b,type);

	printf("%f",*(float*)p1 );


}
