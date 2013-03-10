#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "point.h"
#include "array.h"

	int
main ( int argn, char **args)
{
	printf("hello world\n");
	printf("test my CArray\n");
	Vector *test_array;
	test_array = createVector( 100 );
  //stack test
	for(int i = 0; i < 10 ; ++i)
	{
    Point * tmp_point = (Point *) malloc(sizeof(Point));
		push(test_array,(Object *)tmp_point);
	}
	printf("the size of test_array is : %d\n", size(test_array));
	printf("the capacity of test_array is : %d\n", capacity(test_array));
	for(int i = 0 ; i < size(test_array); ++i)
	{
	 //printf("%d ",index(test_array,i)); 
	}
	printf ("end world");
	return 0;
}
