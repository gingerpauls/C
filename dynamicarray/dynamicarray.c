#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdlib.h"

int main ( void )
{
    char command[50];
    strcpy ( command, "dir" );
    
    srand ( time ( 0 ) );
    int num_array_elements = 0;
    printf ( "how many array elements do you want: " );
    scanf ("%d", &num_array_elements);
    system ( command );
    int *variable_array = calloc ( num_array_elements,  sizeof ( int ) * num_array_elements );
    for ( int i = 0; i < num_array_elements; i++ )
    {
        int user_input = 0;
        variable_array[i] = rand ( );
        printf ( "array[%d]: %d\n", i, variable_array[i] );
        size_t size;
        size = _msize ( variable_array );
        printf ( "_msize of variable_array: %d\n", size );

    }
    printf ( "how many array elements do you want: " );
    scanf ( "%d", &num_array_elements );
    int *new_variable_array = realloc (variable_array, sizeof ( int ) * num_array_elements );
    
    //free ( variable_array );
    for ( int i = 0; i < num_array_elements; i++ )
    {
        int user_input = 0;
        printf ( "array[%d]: %d\n", i, new_variable_array[i] );
        size_t size;
        size = _msize ( new_variable_array );
        printf ( "_msize of variable_array: %d\n", size );
    }
    free ( new_variable_array );
    return 0;
}