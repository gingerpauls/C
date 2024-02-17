#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 100

typedef struct
{
    char *email;
    char *name;
    int isAdmin;
} Account;

typedef struct
{
    int x;
    int y;
} Map;

void PrintAccount ( Account *account_list, int num_accounts )
{
    size_t memblocksize;
    printf ( "\nPrinting Accounts\n\n" );
    printf ( "account_list: %p \t&: %p\n", account_list, &account_list );
    printf ( "_msize %d\n", _msize ( account_list ) );
    for ( size_t i = 0; i < num_accounts; i++ )
    {
        printf ( "account_list[%d]->email: %s \t&: %p\n", i, account_list[i].email, &account_list[i].email );
        printf ( "account_list[%d]->name: %s \t&: %p\n", i, account_list[i].name, &account_list[i].name );
        printf ( "account_list[%d]->isAdmin: %d \t&: %p\n", i, account_list[i].isAdmin, &account_list[i].isAdmin );
    }
}

int main ( void )
{
    char input_buffer[STRING_SIZE];
    int num_accounts = 0;
    Account *account_list = NULL;

    printf ( "Enter number of accounts: " );
    scanf ( "%d", &num_accounts );
    account_list = malloc ( sizeof ( *account_list ) * num_accounts );

    for ( size_t i = 0; i < num_accounts; i++ )
    {
        {
            printf ( "Enter acct[%d].email: ", i );
            scanf ( "%s", input_buffer );
            account_list[i].email = malloc ( sizeof ( *account_list->email ) *
                                             ( strlen ( input_buffer ) + 1 ) );
            strcpy ( account_list[i].email, input_buffer );
        }

        {
            printf ( "Enter acct[%d].name: ", i );
            scanf ( "%s", input_buffer );
            account_list[i].name = malloc ( sizeof ( *account_list->name ) *
                                            ( strlen ( input_buffer ) + 1 ) );
            strcpy ( account_list[i].name, input_buffer );
        }

        {
            printf ( "Enter acct[%d].isAdmin: ", i );
            scanf ( "%s", input_buffer );
            account_list[i].isAdmin = malloc ( sizeof ( account_list->isAdmin ) );
            account_list[i].isAdmin = atoi ( input_buffer );
        }
    }
    PrintAccount ( account_list, num_accounts );
    for ( size_t i = 0; i < num_accounts; i++ )
    {
        free ( account_list[i].email );
        free ( account_list[i].name );
        //free ( account_list[i].isAdmin );
    }
    free ( account_list );

    Map map1;
    //map1.x = malloc ( sizeof ( map1.x ) );
    //map1.y = malloc ( sizeof ( map1.y ) );
    map1.x = 10;
    map1.y = 20;

    printf ( "x: %d, &x: %d\n", map1.x, &map1.x );
    printf ( "y: %d, &y: %d\n", map1.y, &map1.y );


    return 0;
}
