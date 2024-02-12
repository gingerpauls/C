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

#define STRING_SIZE 30
#define NUM_ACCOUNTS_MAX 100

typedef struct
{
    char Name[STRING_SIZE];
    char Password[STRING_SIZE];
    char Email[STRING_SIZE];
    _Bool isAdmin;
} Account;

typedef struct
{
    Account* account_list;
    int num_accounts;
}AccountList;

void PrintAccountList(Account *account_list, int num_accounts);
int  LoginAccount(Account *account_list, int num_accounts);
int  SearchAccount(Account *account_list, int num_accounts);
void PopulateAccounts(FILE *accounts, Account *account_list, int *num_accounts);
int  CreateAccount(FILE *accounts, Account *account_list, int *num_accounts, _Bool isAdmin);
void UpdateDatabase(FILE *accounts, Account *account_list, int num_accounts);
void PrintAccount(Account *account_list, int account_id);
int  CheckForEmptyDatabase(Account *account_list);

int main(int num_arguments, char *argument_value[])
{
    FILE *accounts;
    Account account_list[NUM_ACCOUNTS_MAX] = { 0, 0, 0, 0 };
    int num_accounts = 0;

    if ( num_arguments < 2 )
    {
        printf("Welcome to the library! \n");
        printf("Use:\t-i to create and initialize the database\n");
        printf("    \t-c to create an account\n");
        printf("    \t-l to login to an existing account\n");
    }
    else if ( strcmp(argument_value[1], "-c") == 0 )
    {
        accounts = fopen("accounts.txt", "r");
        if ( CheckForEmptyDatabase(accounts) )
        {
            return -1;
        }
        PopulateAccounts(accounts, &account_list, &num_accounts);
        CreateAccount(accounts, account_list, &num_accounts, 0);
    }
    else if ( strcmp(argument_value[1], "-l") == 0 )
    {
        accounts = fopen("accounts.txt", "r");
        if ( CheckForEmptyDatabase(accounts) != 0 )
        {
            return -1;
        }
        PopulateAccounts(accounts, &account_list, &num_accounts);
        int account_id = LoginAccount(account_list, num_accounts);
        if ( account_id < 0 )
        {
            return -1;
        }
        else if ( account_list[account_id].isAdmin == 1 )
        {
            char input_buffer[STRING_SIZE];

            printf("Welcome %s!\n", account_list[account_id].Name);
            while ( 1 )
            {
                printf("Press:  \tv     \t- view your account information.\n");
                printf("        \ta     \t- view all account information.\n");
                printf("        \tca    \t- create an admin account.\n");
                printf("        \tcu    \t- create a user account (no admin privileges).\n");
                printf("        \ts     \t- search for an account. \n");
                printf("        \te     \t- edit an account. \n");
                printf("        \td     \t- delete an account. \n");
                printf("        \t      \t- anything else to logout.\n");
                printf("\n");
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
                            printf("isAdmin?: ");
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
                            printf("You are the last admin. Cannot have less than 1 admin account.  \n"
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
                    printf("%s", input_buffer);
                    printf("Logging out...\n");
                    return 0;
                }
            }
        }
        else if ( account_list[account_id].isAdmin == 0 )
        {
            char input_buffer[STRING_SIZE];
            printf("Welcome %s!\n", account_list[account_id].Name);
            while ( 1 )
            {
                printf("Press:  \tv     \t- view your account information.\n");
                printf("        \te     \t- edit your account information. \n");
                printf("        \t      \t- anything else to logout.\n");
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
                        UpdateDatabase(accounts, account_list, num_accounts);
                    }
                }
                else
                {
                    printf("Logging out...\n");
                    return 0;
                }
            }
        }
    }
    else if ( strcmp(argument_value[1], "-i") == 0 )
    {
        char input_buffer[STRING_SIZE];
        int num_matches;
        accounts = fopen("accounts.txt", "r");
        if ( accounts == NULL )
        {
            printf("The database (accounts.txt) does not exist.\n");
            printf("Would you like to create a new database?\n");
            printf("Enter Y or y: ");
            num_matches = scanf("%s", input_buffer);
            if ( strcmp(input_buffer, "y") == 0 || strcmp(input_buffer, "Y") == 0 )
            {
                accounts = fopen("accounts.txt", "w");
                fclose(accounts);
                CreateAccount(accounts, account_list, &num_accounts, 1);
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
                printf("No accounts created. Please create an admin account: \n");
                CreateAccount(accounts, account_list, &num_accounts, 1);
                return -1;
            }
            printf("The database (accounts.txt) already exists. Login (-l) or create account (-c).\n");
        }
    }
    else
    {
        printf("Unknown arguments.\n"
               "Use -c to create an account or -l to login to an existing account.\n");
    }
    return 0;
}

void PopulateAccounts(FILE *accounts, Account *account_list, int *num_accounts)
{
    int i = 0, num_matches;
    char header_string[STRING_SIZE];

    accounts = fopen("accounts.txt", "r");
    rewind(accounts);
    while ( !feof(accounts) )
    {
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Email);
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Name);
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Password);
        num_matches = fscanf(accounts, "%s %c", header_string, &account_list[i].isAdmin);
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
int  CreateAccount(FILE *accounts, Account *account_list, int *num_accounts, _Bool isAdmin)
{
    char input_buffer[STRING_SIZE];
    int num_matches = 0;

    printf("Create account\n");
    printf("Enter your email: ");
    num_matches = scanf("%s", input_buffer);
    for ( int i = 0; i < *num_accounts; i++ )
    {
        if ( strcmp(input_buffer, account_list[i].Email) == 0 )
        {
            printf("Email address already exists in database. Use -l for login.\n");
            return -1;
        }
    }
    accounts = fopen("accounts.txt", "a");
    fprintf(accounts, "Email \t\t%s\n", input_buffer);
    printf("Enter your name: ");
    num_matches = scanf("%s", input_buffer);
    fprintf(accounts, "Name \t\t%s\n", input_buffer);
    printf("Enter your password: ");
    num_matches = scanf("%s", input_buffer);
    fprintf(accounts, "Password \t%s\n", input_buffer);
    fprintf(accounts, "isAdmin \t%u\n", isAdmin);
    fprintf(accounts, "\n", input_buffer);
    ( *num_accounts )++;
    fclose(accounts);
    printf("Account creation successful. Login with -l.\n");
    return 0;
}
int  LoginAccount(Account *account_list, int num_accounts)
{
    char input_buffer[STRING_SIZE];
    int num_matches;

    printf("Login to your account\n");
    printf("Enter your email address: ");
    num_matches = scanf("%s", input_buffer);
    for ( int i = 0; i < num_accounts; i++ )
    {
        if ( strcmp(input_buffer, account_list[i].Email) == 0 )
        {
            printf("Email address found.\n");
            for ( int j = 0; j < 5; j++ )
            {
                printf("Enter your password: ");
                num_matches = scanf("%s", input_buffer);
                if ( strcmp(input_buffer, account_list[i].Password) == 0 )
                {
                    printf("Logging in...\n");
                    return i;
                }
                else
                {
                    printf("Incorrect password.\n");
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
int  CheckForEmptyDatabase(Account *accounts)
{
    if ( accounts == NULL )
    {
        {
            printf("No database created. Create one using -i.\n");
            return -1;
        }
    }
    fseek(accounts, 0, SEEK_END);
    if ( ftell(accounts) == 0 )
    {
        printf("No accounts created. Please create an admin account using -i.\n\n");
        return -1;
    }
    return 0;
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