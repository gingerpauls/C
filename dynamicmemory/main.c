#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define STRING_SIZE 100


typedef struct
{
    char *email;
    char *name;
} Account;

void PrintAccount ( Account *account_list, int num_accounts )
{
    printf ( "\nPrinting Accounts\n\n" );
    for ( size_t i = 0; i < num_accounts; i++ )
    {
        printf ( "account_list[%d]->email: %s\n", i, account_list[i].email );
        printf ( "account_list[%d]->name: %s\n", i, account_list[i].name );
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
        printf ( "Enter acct[%d] email: ", i );
        scanf ( "%s", input_buffer );
        account_list[i].email = malloc ( sizeof ( *account_list->email ) * ( strlen ( input_buffer ) + 1 ) );
        strcpy ( account_list[i].email, input_buffer );

        printf ( "Enter acct[%d] name: ", i );
        scanf ( "%s", input_buffer );
        account_list[i].name = malloc ( sizeof ( *account_list->name) * ( strlen ( input_buffer ) + 1 ) );
        strcpy ( account_list[i].name, input_buffer );
    }
    PrintAccount ( account_list, num_accounts );
    for ( size_t i = 0; i < num_accounts; i++ )
    {
        free ( account_list[i].email );
        free ( account_list[i].name );
    }
    free ( account_list );
    return 0;
}
