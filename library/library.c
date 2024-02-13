/*
    admin
        add new books to library
        edit book
        delete book
        search book
        display list of books

        delete members

        issue books to library members
        view due date
            late ? penalty : no penalty

    user
        search book
        display list of books
        edit self member information

        return book to library
        view due date
            late ? penalty : no penalty

    system
        save books
        load books
        ensure data persistence

    save database as binary file instead of text

    reports
        list of issued books, overdue books

    secure login?

*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "string.h"
#include "assert.h"
#include "stdbool.h"
#include "malloc.h"

#define STRING_SIZE 30
#define NUM_ACCOUNTS_MAX 100
#define MAX_ATTEMPTS 5

typedef struct
{
    char Name[STRING_SIZE];
    char Password[STRING_SIZE];
    char Email[STRING_SIZE];
    bool isAdmin;
} Account;

typedef struct
{
    Account *account_list;
    int num_accounts;
    int num_admins;
}AccountList;

void PrintAccountList ( AccountList *account_list );
int  LoginAccount ( AccountList *account_list );
int  SearchAccount ( AccountList *account_list );
void UpdateDatabase ( FILE *account_stream, AccountList *account_list );
int  CheckForEmptyDatabase ( FILE *account_stream, AccountList *account_list );
void PopulateAccounts ( FILE *account_stream, AccountList *account_list );
int  CreateAccount ( FILE *account_stream, AccountList *account_list, bool isAdmin );
void PrintAccount ( AccountList *account_list, int account_id );

int main ( int num_arguments, char *argument_value[] )
{
    FILE *account_stream;
    Account accounts[NUM_ACCOUNTS_MAX] = { 0, 0, 0, 0 };
    AccountList *account_list = (AccountList *) malloc ( sizeof ( Account ) * NUM_ACCOUNTS_MAX );
    account_list->account_list = accounts;
    account_list->num_accounts = 0;
    account_list->num_admins = 0;
    char input_buffer[STRING_SIZE];

    printf ( "Welcome to the library!\n\n" );

    account_stream = fopen ( "accounts.txt", "r" );
    if ( CheckForEmptyDatabase ( account_stream, account_list ) < 0 )
    {
        return -1;
    };

    while ( 1 )
    {
        PopulateAccounts ( account_stream, account_list );
        printf ( "Would you like to login (l) or create a user account (c)?\n" );
        printf ( "Enter any other key to quit the library program.\n" );
        scanf ( "%s", input_buffer );
        if ( strcmp ( input_buffer, "c" ) == 0 )
        {
            CreateAccount ( account_stream, account_list, false );
        }
        else if ( strcmp ( input_buffer, "l" ) == 0 )
        {
            int logged_in_id, num_attempts = 0;

            do
            {
                logged_in_id = LoginAccount ( account_list );
                num_attempts++;
            }
            while ( logged_in_id < 0 && num_attempts < MAX_ATTEMPTS );
            if ( num_attempts == MAX_ATTEMPTS )
            {
                printf ( "Too many attempts. Returning to main menu.\n\n" );
            }
            if ( ( account_list->account_list[logged_in_id].isAdmin ) == true )
            {
                char input_buffer[STRING_SIZE];

                printf ( "Welcome %s!\n", account_list->account_list[logged_in_id].Name );
                while ( 1 )
                {
                    printf ( "\n" );
                    printf ( "v     \t view your account information.\n" );
                    printf ( "a     \t view all account information.\n" );
                    printf ( "ca    \t create an admin account.\n" );
                    printf ( "cu    \t create a user account (no admin privileges).\n" );
                    printf ( "s     \t search for an account. \n" );
                    printf ( "e     \t edit an account. \n" );
                    printf ( "d     \t delete an account. \n" );
                    printf ( "      \t anything else to logout.\n\n" );
                    printf ( "\n" );
                    printf ( "Enter option: " );
                    scanf ( "%s", input_buffer );
                    if ( strcmp ( input_buffer, "v" ) == 0 )
                    {
                        PrintAccount ( account_list, logged_in_id );
                    }
                    else if ( strcmp ( input_buffer, "a" ) == 0 )
                    {
                        PrintAccountList ( account_list );
                    }
                    else if ( strcmp ( input_buffer, "ca" ) == 0 )
                    {
                        CreateAccount ( account_stream, account_list, 1 );
                    }
                    else if ( strcmp ( input_buffer, "cu" ) == 0 )
                    {
                        CreateAccount ( account_stream, account_list, 0 );
                    }
                    else if ( strcmp ( input_buffer, "s" ) == 0 )
                    {
                        SearchAccount ( account_list );
                    }
                    else if ( strcmp ( input_buffer, "e" ) == 0 )
                    {
                        int searched_account_id = 0;
                        searched_account_id = SearchAccount ( account_list );
                        if ( searched_account_id >= 0 )
                        {
                            {
                                printf ( "New name: " );
                                scanf ( "%s", input_buffer );
                                strcpy ( account_list->account_list[searched_account_id].Name, input_buffer );
                                printf ( "New password: " );
                                scanf ( "%s", input_buffer );
                                strcpy ( account_list->account_list[searched_account_id].Password, input_buffer );
                            }
                            if ( ( account_list->num_admins == 1 ) && ( logged_in_id == searched_account_id ) )
                            {
                                printf (    "\nCannot edit admin privileges.\n"
                                            "You are the only admin. Cannot have less than 1 admin account.\n"
                                            "If you want to remove your admin status, elevate privileges for\n"
                                            "another account, then edit your admin status.                  \n\n" );
                            }
                            else
                            {
                                printf ( "isAdmin? (0 or 1): " );
                                scanf ( "%s", input_buffer );
                                account_list->account_list[searched_account_id].isAdmin = atoi ( input_buffer );
                            }
                            UpdateDatabase ( account_stream, account_list );
                            PopulateAccounts ( account_stream, account_list );
                            if ( account_list->account_list[logged_in_id].isAdmin == 0 )
                            {
                                printf ( "No longer admin. Logging out... \n\n" );
                                break;
                            }
                        }
                    }
                    else if ( strcmp ( input_buffer, "d" ) == 0 )
                    {
                        int searched_account_id = 0;
                        searched_account_id = SearchAccount ( account_list );
                        if ( searched_account_id >= 0 )
                        {
                            if ( ( account_list->num_admins == 1 ) && ( logged_in_id == searched_account_id ) )
                            {
                                printf (    "\nCannot delete account.\n" 
                                            "You are the only admin. Cannot have less than 1 admin account.\n"
                                            "If you want to delete your admin account, elevate privileges for\n"
                                            "another account, then delete your account.                      \n\n" );
                            }
                            else 
                            {
                                printf ( "This will delete account %s. Are you sure? (y/n)\n", account_list->account_list[searched_account_id].Email );
                                scanf ( "%s", input_buffer );
                                if ( strcmp ( input_buffer, "y" ) == 0 )
                                {
                                    printf ( "Deleting account %s\n\n", account_list->account_list[searched_account_id].Email );
                                    strcpy ( account_list->account_list[searched_account_id].Email, "0" );
                                    strcpy ( account_list->account_list[searched_account_id].Name, "0" );
                                    strcpy ( account_list->account_list[searched_account_id].Password, "0" );
                                    account_list->account_list[searched_account_id].isAdmin = false;
                                    UpdateDatabase ( account_stream, account_list );
                                    PopulateAccounts ( account_stream, account_list );
                                    //break;
                                }
                                else
                                {
                                    printf ( "Account not deleted.\n\n" );
                                }
                            }
                        }
                    }
                    else
                    {
                        printf ( "Logging out...\n\n" );
                        break;
                    }
                }
            }
            else if ( account_list->account_list[logged_in_id].isAdmin == false )
            {
                char input_buffer[STRING_SIZE];
                printf ( "Welcome %s!\n", account_list->account_list[logged_in_id].Name );
                while ( 1 )
                {
                    printf ( "v     \t view your account information.\n" );
                    printf ( "e     \t edit your account information. \n" );
                    printf ( "      \t anything else to logout.\n\n" );
                    printf ( "Enter option: " );
                    scanf ( "%s", input_buffer );
                    if ( strcmp ( input_buffer, "v" ) == 0 )
                    {
                        PrintAccount ( account_list, logged_in_id );
                    }
                    else if ( strcmp ( input_buffer, "e" ) == 0 )
                    {
                        if ( logged_in_id >= 0 )
                        {
                            printf ( "New name: " );
                            scanf ( "%s", input_buffer );
                            strcpy ( account_list->account_list[logged_in_id].Name, input_buffer );
                            printf ( "New password: " );
                            scanf ( "%s", input_buffer );
                            strcpy ( account_list->account_list[logged_in_id].Password, input_buffer );
                            UpdateDatabase ( account_stream, account_list );
                        }
                    }
                    else
                    {
                        printf ( "Logging out...\n\n" );
                        //return 0;
                        break;
                    }
                }
            }
        }
        else
        {
            printf ( "\nQuitting library.\n" );
            return 0;
        }
    }
    free ( account_list );
    return 0;
}

void PrintAccountList ( AccountList *account_list )
{
    for ( int i = 0; i < account_list->num_accounts; i++ )
    {
        printf ( "\nID \t\t%d\n", i );
        printf ( "Email \t\t%s\n", account_list->account_list[i].Email );
        printf ( "Name \t\t%s\n", account_list->account_list[i].Name );
        printf ( "Password \t%s\n", account_list->account_list[i].Password );
        printf ( "isAdmin \t%d\n", account_list->account_list[i].isAdmin );
    }
}
int  LoginAccount ( AccountList *account_list )
{
    char input_buffer[STRING_SIZE];

    printf ( "Login to your account\n" );
    printf ( "Enter your email address: " );
    scanf ( "%s", input_buffer );
    for ( int i = 0; i < account_list->num_accounts; i++ )
    {
        if ( strcmp ( input_buffer, account_list->account_list[i].Email ) == 0 )
        {
            printf ( "Email address found.\n" );
            for ( int j = 0; j < MAX_ATTEMPTS; j++ )
            {
                printf ( "Enter your password: " );
                scanf ( "%s", input_buffer );
                if ( strcmp ( input_buffer, account_list->account_list[i].Password ) == 0 )
                {
                    printf ( "Logging in...\n\n" );
                    return i;
                }
                else
                {
                    printf ( "Incorrect password.\n\n" );
                }
                if ( j == MAX_ATTEMPTS - 1 )
                {
                    fprintf ( stderr, "Too many attempts. Returning to main menu.\n\n" );
                    return -1;
                }
            }
        }
    }
    fprintf ( stderr, "Email not found.\n\n" );
    return -1;
}
int  SearchAccount ( AccountList *account_list )
{
    char input_buffer[STRING_SIZE];
    printf ( "Enter the email of the account you're looking for: " );
    scanf ( "%s", input_buffer );
    for ( int i = 0; i < account_list->num_accounts; i++ )
    {
        if ( strcmp ( input_buffer, account_list->account_list[i].Email ) == 0 )
        {
            printf ( "Account found.\n" );
            PrintAccount ( account_list, i );
            return i;
        }
    }
    printf ( "Account not found.\n\n" );
    return -1;
}
void UpdateDatabase ( FILE *account_stream, AccountList *account_list )
{
    account_stream = fopen ( "accounts.txt", "w" );
    for ( int i = 0; i < account_list->num_accounts; i++ )
    {
        if ( strcmp ( account_list->account_list[i].Email, "0" ) )
        {
            fprintf ( account_stream, "Email \t\t%s\n", account_list->account_list[i].Email );
            fprintf ( account_stream, "Name \t\t%s\n", account_list->account_list[i].Name );
            fprintf ( account_stream, "Password \t%s\n", account_list->account_list[i].Password );
            fprintf ( account_stream, "isAdmin \t%u\n", account_list->account_list[i].isAdmin );
            fprintf ( account_stream, "\n" );
        }
    }
    fclose ( account_stream );
}
int  CheckForEmptyDatabase ( FILE *account_stream, AccountList *account_list )
{
    char input_buffer[STRING_SIZE];

    if ( account_stream == NULL )
    {
        printf ( "The database (accounts.txt) does not exist.\n"
                 "Would you like to create a new database?\n"
                 "Enter Y or y: " );
        scanf ( "%s", input_buffer );
        if ( strcmp ( input_buffer, "y" ) == 0 || strcmp ( input_buffer, "Y" ) == 0 )
        {
            account_stream = fopen ( "accounts.txt", "w" );
            fclose ( account_stream );
            CreateAccount ( account_stream, account_list, 1 );
            return 0;
        }
        else
        {
            printf ( "No database created. Exiting.\n" );
            return -1;
        }
    }
    else
    {
        fseek ( account_stream, 0, SEEK_END );
        if ( ftell ( account_stream ) == 0 )
        {
            printf ( "Database (accounts.txt) found, but no accounts created.\n" );
            CreateAccount ( account_stream, account_list, 1 );
            return 0;
        }
        else
        {
            //LoginAccount(account_list);
        }
    }
}
void PopulateAccounts ( FILE *account_stream, AccountList *account_list )
{
    int i = 0, num_admins;
    char header_string[STRING_SIZE];

    account_stream = fopen ( "accounts.txt", "r" );
    rewind ( account_stream );
    account_list->num_admins = 0;
    account_list->num_accounts = 0;
    while ( !feof ( account_stream ) )
    {
        fscanf ( account_stream, "%s %s", header_string, account_list->account_list[i].Email );
        fscanf ( account_stream, "%s %s", header_string, account_list->account_list[i].Name );
        fscanf ( account_stream, "%s %s", header_string, account_list->account_list[i].Password );
        fscanf ( account_stream, "%s %d", header_string, &account_list->account_list[i].isAdmin );
        if ( account_list->account_list[i].isAdmin == true )
        {
            account_list->num_admins++;
        }
        i++;
    }
    fclose ( account_stream );
    account_list->num_accounts = i - 1;
}
int  CreateAccount ( FILE *account_stream, AccountList *account_list, bool isAdmin )
{
    char input_buffer[STRING_SIZE];

    ( isAdmin == 1 ) ? printf ( "\nCreate admin account:\n" ) : printf ( "\nCreate user account:\n" );
    printf ( "Enter your email: " );
    scanf ( "%s", input_buffer );
    for ( int i = 0; i < account_list->num_accounts; i++ )
    {
        if ( strcmp ( input_buffer, account_list->account_list[i].Email ) == 0 )
        {
            printf (    "That email address already exists in database.\n"
                        "Try logging in to your account.\n\n" );
            return -1;
        }
    }
    account_stream = fopen ( "accounts.txt", "a" );
    fprintf ( account_stream, "Email \t\t%s\n", input_buffer );
    printf ( "Enter your name: " );
    scanf ( "%s", input_buffer );
    fprintf ( account_stream, "Name \t\t%s\n", input_buffer );
    printf ( "Enter your password: " );
    scanf ( "%s", input_buffer );
    fprintf ( account_stream, "Password \t%s\n", input_buffer );
    fprintf ( account_stream, "isAdmin \t%u\n", isAdmin );
    fprintf ( account_stream, "\n", input_buffer );
    fclose ( account_stream );
    PopulateAccounts ( account_stream, account_list );
    printf ( "Account creation successful.\n\n" );
    return 0;
}
void PrintAccount ( AccountList *account_list, int account_id )
{
    printf ( "\nID \t\t%d\n", account_id );
    printf ( "Email \t\t%s\n", account_list->account_list[account_id].Email );
    printf ( "Name \t\t%s\n", account_list->account_list[account_id].Name );
    printf ( "Password \t%s\n", account_list->account_list[account_id].Password );
    printf ( "isAdmin \t%d\n\n", account_list->account_list[account_id].isAdmin );
}