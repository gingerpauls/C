#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "stdlib.h"

#define STRING_SIZE 100
#define MAX_ACCOUNTS 5

typedef struct
{
    char *email;
} Account;

void PrintAccount ( Account *account );
void PrintAccountList ( Account *account_list );
void PopulateList ( Account *account_list );
void GetSizeOfEmail ( Account *account_list );
void FreeAccountList ( Account *account_list );
void PopulateListFromFile ( FILE *account_file, Account *account_list );

int main ( void )
{
    Account *account_list;
    account_list = malloc ( sizeof ( Account ) * MAX_ACCOUNTS );
    char input_buffer[STRING_SIZE];

    FILE *account_file = fopen ( "accounts.txt", "r" );
    if ( account_file == NULL )
        exit ( 1 );
    PopulateListFromFile ( account_file, account_list );
    PrintAccountList ( account_list );
    GetSizeOfEmail ( account_list );

    free ( account_list );
    return 0;
}

void PrintAccount ( Account *account )
{
    printf ( "account1.email: %s", account->email );
}
void PrintAccountList ( Account *account_list )
{
    for ( int i = 0; i < MAX_ACCOUNTS; i++ )
    {
        printf ( "account[%d].email: %s\n", i, account_list[i].email );
    }
}
void PopulateList ( Account *account_list )
{
    char input_buffer[STRING_SIZE];
    for ( int i = 0; i < MAX_ACCOUNTS; i++ )
    {
        printf ( "enter email: " );
        scanf ( "%s", input_buffer );
        account_list[i].email = malloc ( sizeof ( char ) * ( strlen ( input_buffer ) + 1 ) );
        strcpy ( account_list[i].email, input_buffer );
    }
}
void GetSizeOfEmail ( Account *account_list )
{
    size_t size;
    for ( int i = 0; i < MAX_ACCOUNTS; i++ )
    {
        size = _msize ( account_list[i].email );
        printf_s ( "Size of email: %u\n", size );
    }
    //size = _msize ( account_list );
    //printf_s ( "Size of account_list: %u\n", size );
}
void PopulateListFromFile ( FILE *account_file, Account *account_list )
{
    char input_buffer[STRING_SIZE];

    for ( int i = 0; i < MAX_ACCOUNTS; i++ )
    {
        fscanf (account_file, "%s", input_buffer );
        account_list[i].email = malloc ( sizeof ( char ) * ( strlen ( input_buffer ) + 1 ) );
        strcpy ( account_list[i].email, input_buffer );
    }
}