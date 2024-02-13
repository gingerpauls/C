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

#define STRING_SIZE 30
#define NUM_ACCOUNTS_MAX 100

typedef struct
{
    char Name[STRING_SIZE];
    char Password[STRING_SIZE];
    char Email[STRING_SIZE];
    bool isAdmin;
} Account;

//typedef struct
//{
//    Account *account_list;
//    int num_accounts;
//    int num_admins;
//}AccountList;

void PrintAccountList(Account *account_list, int num_accounts);
int  LoginAccount(Account *account_list, int num_accounts);
int  SearchAccount(Account *account_list, int num_accounts);
void PopulateAccounts(FILE *accounts, Account *account_list, int *num_accounts);
int  CreateAccount(FILE *accounts, Account *account_list, int *num_accounts, bool isAdmin);
void UpdateDatabase(FILE *accounts, Account *account_list, int num_accounts);
void PrintAccount(Account *account_list, int account_id);
int  CheckForEmptyDatabase(FILE *Accounts, Account *account_list, int num_accounts);

int main(int num_arguments, char *argument_value[])
{
    FILE *accounts;
    Account account_list[NUM_ACCOUNTS_MAX] = { 0, 0, 0, 0 };
    int num_accounts = 0;
    char input_buffer[STRING_SIZE];

    printf("Welcome to the library! \n");

    accounts = fopen("accounts.txt", "r");
    if ( CheckForEmptyDatabase(accounts, account_list, num_accounts) < 0 )
    {
        return -1;
    };

    printf("Would you like to login (l) or create a user account (c)?\n");
    scanf("%s", input_buffer);
    PopulateAccounts(accounts, &account_list, &num_accounts);
    while ( 1 )
    {
        if ( strcmp(input_buffer, "c") == 0 )
        {
            CreateAccount(accounts, account_list, &num_accounts, false);
        }
        else if ( strcmp(input_buffer, "l") == 0 )
        {
            int account_id = LoginAccount(account_list, num_accounts);
            if ( account_id < 0 )
            {
                return -1;
            }
            else if ( ( account_list[account_id].isAdmin ) == true )
            {
                char input_buffer[STRING_SIZE];

                printf("Welcome %s!\n", account_list[account_id].Name);
                while ( 1 )
                {
                    printf("v     \t view your account information.\n");
                    printf("a     \t view all account information.\n");
                    printf("ca    \t create an admin account.\n");
                    printf("cu    \t create a user account (no admin privileges).\n");
                    printf("s     \t search for an account. \n");
                    printf("e     \t edit an account. \n");
                    printf("d     \t delete an account. \n");
                    printf("      \t anything else to logout.\n\n");
                    printf("\n");
                    printf("Enter option: ");
                    scanf("%s", input_buffer);
                    if ( strcmp(input_buffer, "v") == 0 )
                    {
                        PrintAccount(account_list, account_id);
                    }
                    else if ( strcmp(input_buffer, "a") == 0 )
                    {
                        PrintAccountList(account_list, num_accounts);
                    }
                    else if ( strcmp(input_buffer, "ca") == 0 )
                    {
                        CreateAccount(accounts, account_list, &num_accounts, 1);
                        PopulateAccounts(accounts, &account_list, &num_accounts);
                    }
                    else if ( strcmp(input_buffer, "cu") == 0 )
                    {
                        CreateAccount(accounts, account_list, &num_accounts, 0);
                        PopulateAccounts(accounts, &account_list, &num_accounts);
                    }
                    else if ( strcmp(input_buffer, "s") == 0 )
                    {
                        SearchAccount(account_list, num_accounts);
                    }
                    else if ( strcmp(input_buffer, "e") == 0 )
                    {
                        int searched_account_id = 0;
                        searched_account_id = SearchAccount(account_list, num_accounts);
                        if ( searched_account_id >= 0 )
                        {
                            printf("New name: ");
                            scanf("%s", input_buffer);
                            strcpy(account_list[searched_account_id].Name, input_buffer);
                            printf("New password: ");
                            scanf("%s", input_buffer);
                            strcpy(account_list[searched_account_id].Password, input_buffer);
                            int num_admins = 0;
                            for ( int i = 0; i < num_accounts; i++ )
                            {
                                if ( account_list[i].isAdmin == 1 )
                                {
                                    num_admins++;
                                }
                            }
                            if ( ( num_admins == 1 ) && ( account_id == searched_account_id ) )
                            {
                                printf("You are the last admin. Cannot have less than 1 admin account. \n"
                                       "If you want to remove your admin status, elevate privileges for\n"
                                       "another account. Then edit your admin status.                \n\n");
                            }
                            else
                            {
                                printf("isAdmin? (0 or 1): ");
                                scanf("%s", input_buffer);
                                account_list[searched_account_id].isAdmin = atoi(input_buffer);
                            }
                            UpdateDatabase(accounts, account_list, num_accounts);
                            if ( account_list[account_id].isAdmin == 0 )
                            {
                                printf("No longer admin. Logging out... \n");
                                return 0;
                            }
                        }
                    }
                    else if ( strcmp(input_buffer, "d") == 0 )
                    {
                        int searched_account_id = 0;
                        searched_account_id = SearchAccount(account_list, num_accounts);
                        if ( searched_account_id >= 0 )
                        {
                            strcpy(account_list[searched_account_id].Email, "0");
                            strcpy(account_list[searched_account_id].Name, "0");
                            strcpy(account_list[searched_account_id].Password, "0");
                            int num_admins = 0;
                            for ( int i = 0; i < num_accounts; i++ )
                            {
                                if ( account_list[i].isAdmin == 1 )
                                {
                                    num_admins++;
                                }
                            }
                            if ( ( num_admins == 1 ) && ( account_id == searched_account_id ) )
                            {
                                printf("\nYou are the last admin. Cannot have less than 1 admin account.\n"
                                       "If you want to remove your admin account, elevate privileges for\n"
                                       "another account.                                              \n\n");
                            }
                            UpdateDatabase(accounts, account_list, num_accounts);
                            PopulateAccounts(accounts, account_list, &num_accounts);
                            if ( account_list[account_id].isAdmin == 0 )
                            {
                                printf("No longer admin. Logging out... \n");
                                return 0;
                            }
                        }
                    }
                    else
                    {
                        printf("Logging out...\n\n");
                        //return 0;
                        break;
                    }
                }
            }
            else if ( account_list[account_id].isAdmin == false )
            {
                char input_buffer[STRING_SIZE];
                printf("Welcome %s!\n", account_list[account_id].Name);
                while ( 1 )
                {
                    printf("v     \t view your account information.\n");
                    printf("e     \t edit your account information. \n");
                    printf("      \t anything else to logout.\n\n");
                    printf("Enter option: ");
                    scanf("%s", input_buffer);
                    if ( strcmp(input_buffer, "v") == 0 )
                    {
                        PrintAccount(account_list, account_id);
                    }
                    else if ( strcmp(input_buffer, "e") == 0 )
                    {
                        if ( account_id >= 0 )
                        {
                            printf("New name: ");
                            scanf("%s", input_buffer);
                            strcpy(account_list[account_id].Name, input_buffer);
                            printf("New password: ");
                            scanf("%s", input_buffer);
                            strcpy(account_list[account_id].Password, input_buffer);
                            UpdateDatabase(accounts, account_list, num_accounts);
                        }
                    }
                    else
                    {
                        printf("Logging out...\n\n");
                        //return 0;
                        break;
                    }
                }
            }
        }
        else
        {
            printf("Quitting library.\n");
            return 0;
        }
    }
    return 0;
}

void PopulateAccounts(FILE *accounts, Account *account_list, int *num_accounts)
{
    int i = 0;
    char header_string[STRING_SIZE];

    accounts = fopen("accounts.txt", "r");
    rewind(accounts);
    while ( !feof(accounts) )
    {
        fscanf(accounts, "%s %s", header_string, account_list[i].Email);
        fscanf(accounts, "%s %s", header_string, account_list[i].Name);
        fscanf(accounts, "%s %s", header_string, account_list[i].Password);
        fscanf(accounts, "%s %d", header_string, &account_list[i].isAdmin);
        i++;
    }
    fclose(accounts);
    *num_accounts = i - 1;
}
void PrintAccount(Account *account_list, int account_id)
{
    printf("Account[%d].Email = %s\n", account_id, account_list[account_id].Email);
    printf("Account[%d].Name = %s\n", account_id, account_list[account_id].Name);
    printf("Account[%d].Password = %s\n", account_id, account_list[account_id].Password);
    printf("Account[%d].isAdmin = %d\n\n", account_id, account_list[account_id].isAdmin);
}
void PrintAccountList(Account *account_list, int num_accounts)
{
    for ( int i = 0; i < num_accounts; i++ )
    {
        printf("Account[%d].Email = %s\n", i, account_list[i].Email);
        printf("Account[%d].Name = %s\n", i, account_list[i].Name);
        printf("Account[%d].Password = %s\n", i, account_list[i].Password);
        printf("Account[%d].isAdmin = %d\n\n", i, account_list[i].isAdmin);
    }
}
int  CreateAccount(FILE *accounts, Account *account_list, int *num_accounts, bool isAdmin)
{
    char input_buffer[STRING_SIZE];

    ( isAdmin == 1 ) ? printf("Create admin account:\n") : printf("Create user account:\n");
    printf("Enter your email: ");
    scanf("%s", input_buffer);
    for ( int i = 0; i < *num_accounts; i++ )
    {
        if ( strcmp(input_buffer, account_list[i].Email) == 0 )
        {
            printf("Email address already exists in database.\n");
            return -1;
        }
    }
    accounts = fopen("accounts.txt", "a");
    fprintf(accounts, "Email \t\t%s\n", input_buffer);
    printf("Enter your name: ");
    scanf("%s", input_buffer);
    fprintf(accounts, "Name \t\t%s\n", input_buffer);
    printf("Enter your password: ");
    scanf("%s", input_buffer);
    fprintf(accounts, "Password \t%s\n", input_buffer);
    fprintf(accounts, "isAdmin \t%u\n", isAdmin);
    fprintf(accounts, "\n", input_buffer);
    ( *num_accounts )++;
    fclose(accounts);
    printf("Account creation successful.\n");
    return 0;
}
int  LoginAccount(Account *account_list, int num_accounts)
{
    char input_buffer[STRING_SIZE];

    printf("Login to your account\n");
    printf("Enter your email address: ");
    scanf("%s", input_buffer);
    for ( int i = 0; i < num_accounts; i++ )
    {
        if ( strcmp(input_buffer, account_list[i].Email) == 0 )
        {
            printf("Email address found.\n");
            for ( int j = 0; j < 5; j++ )
            {
                printf("Enter your password: ");
                scanf("%s", input_buffer);
                if ( strcmp(input_buffer, account_list[i].Password) == 0 )
                {
                    printf("Logging in...\n\n");
                    return i;
                }
                else
                {
                    printf("Incorrect password.\n\n");
                }
                if ( j == 4 )
                {
                    fprintf(stderr, "Too many attempts. Exiting program.");
                    return -1;
                }
            }
        }
    }
    fprintf(stderr, "Email not found.\n");
    return -1;
}
int  CheckForEmptyDatabase(FILE *accounts, Account *account_list, int num_accounts)
{
    char input_buffer[STRING_SIZE];

    if ( accounts == NULL )
    {
        printf("The database (accounts.txt) does not exist.\n"
               "Would you like to create a new database?\n"
               "Enter Y or y: ");
        scanf("%s", input_buffer);
        if ( strcmp(input_buffer, "y") == 0 || strcmp(input_buffer, "Y") == 0 )
        {
            accounts = fopen("accounts.txt", "w");
            fclose(accounts);
            CreateAccount(accounts, account_list, &num_accounts, 1);
            return 0;
        }
        else
        {
            printf("No database created. Exiting.\n");
            return -1;
        }
    }
    else
    {
        fseek(accounts, 0, SEEK_END);
        if ( ftell(accounts) == 0 )
        {
            printf("Database (accounts.txt) found, but no accounts created.\n");
            CreateAccount(accounts, account_list, &num_accounts, 1);
            return 0;
        }
    }
}
int  SearchAccount(Account *account_list, int num_accounts)
{
    char input_buffer[STRING_SIZE];
    printf("Enter the email of the account you're looking for: ");
    scanf("%s", input_buffer);
    for ( int i = 0; i < num_accounts; i++ )
    {
        if ( strcmp(input_buffer, account_list[i].Email) == 0 )
        {
            printf("Account found.\n");
            PrintAccount(account_list, i);
            return i;
        }
    }
    printf("Account not found.\n");
    return -1;
}
void UpdateDatabase(FILE *accounts, Account *account_list, int num_accounts)
{
    accounts = fopen("accounts.txt", "w");
    for ( int i = 0; i < num_accounts; i++ )
    {
        if ( strcmp(account_list[i].Email, "0") )
        {
            fprintf(accounts, "Email \t\t%s\n", account_list[i].Email);
            fprintf(accounts, "Name \t\t%s\n", account_list[i].Name);
            fprintf(accounts, "Password \t%s\n", account_list[i].Password);
            fprintf(accounts, "isAdmin \t%u\n", account_list[i].isAdmin);
            fprintf(accounts, "\n");
        }
    }
    fclose(accounts);
}