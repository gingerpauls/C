/*
    admin
        add new books to library
        edit book
        delete book
        search book
        display list of books

        add members to library
        edit (any) member information
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
        save library data (books and members) to files
        load library data from files at startup
        ensure data persistence

    reports
        list of issued books, overdue books

    secure login?

*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "assert.h"

#define STRING_SIZE 30
#define NUM_ACCOUNTS_MAX 100

typedef struct {
    char Name[STRING_SIZE];
    char Password[STRING_SIZE];
    char Email[STRING_SIZE];    
    bool  isAdmin;
} Account;

int PopulateAccounts(FILE* accounts, Account* account_list);
void PrintAccount(Account* account_list, int account_id);
void PrintAccountList(Account* account_list, int num_accounts);
int CreateAccount(FILE* accounts, Account* account_list, int num_accounts, bool isAdmin);
int LoginAccount(Account* account_list, int num_accounts);

int main(int num_arguments, char *argument_value[]) {
    FILE* accounts;
    Account account_list[NUM_ACCOUNTS_MAX] = {0, 0, 0, 0};
    int num_accounts = 0;

    if(num_arguments < 2)
    {
        printf("Welcome to the library! \n");
        printf("Use:\t-i to create and initialize the database\n");
        printf("    \t-c to create an account\n");
        printf("    \t-l to login to an existing account\n");
    }
    else if (strcmp(argument_value[1], "-c") == 0)
    {
        accounts = fopen("accounts.txt", "r");
        if (accounts == NULL) {
            {
                printf("No database created. Create one using -i.\n");
                return -1;
            }
        }
        num_accounts = PopulateAccounts(accounts, &account_list);
        while (CreateAccount(accounts, account_list, num_accounts, 0));
        num_accounts = PopulateAccounts(accounts, &account_list);
    }
    else if (strcmp(argument_value[1], "-l") == 0) 
    {
        accounts = fopen("accounts.txt", "r");
        if (accounts == NULL) {
            printf("No database (accounts.txt) found. Create one using -i.");
            return -1;
        }
        fseek(accounts, 0, SEEK_END);
        if (ftell(accounts) == 0) {
            printf("No accounts created. Please create an admin account using -i.\n\n");
            return -1;
        }
        num_accounts = PopulateAccounts(accounts, &account_list);
        int account_id = LoginAccount(account_list, num_accounts);
        if (account_id < 0) {
            return -1;
        }
        else if (account_list[account_id].isAdmin == true)
        {
            PrintAccountList(account_list, num_accounts);
        }
        else
        {
            PrintAccount(account_list, account_id);
        }
    }
    else if (strcmp(argument_value[1], "-i") == 0) 
    {
        char input_buffer[STRING_SIZE];
        int num_matches;
        accounts = fopen("accounts.txt", "r");
        if (accounts == NULL) {
            printf("The database (accounts.txt) does not exist.\n");
            printf("Would you like to create a new database?\n");
            printf("Enter Y or y: ");
            num_matches = scanf("%s", input_buffer);
            if (strcmp(input_buffer, "y") == 0 || strcmp(input_buffer, "Y") == 0) {
                accounts = fopen("accounts.txt", "w");
                fclose(accounts);
                CreateAccount(accounts, account_list, num_accounts, true);
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
            if (ftell(accounts) == 0) {
                printf("No accounts created. Please create an admin account: \n");
                CreateAccount(accounts, account_list, num_accounts, true);
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

int PopulateAccounts(FILE *accounts, Account* account_list) {
    int i = 0, num_matches, num_accounts;
    char header_string[STRING_SIZE], data_string[STRING_SIZE];

    accounts = fopen("accounts.txt", "r");
    rewind(accounts);
    while (!feof(accounts)) {
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Email);
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Name);
        num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Password);
        num_matches = fscanf(accounts, "%s %d", header_string, &account_list[i].isAdmin);
        i++;
    }
    fclose(accounts);
    return (num_accounts = i - 1);
}

void PrintAccount(Account* account_list, int account_id) {
    printf("\nAccounts:\n\n");
    printf("Account[%d].Email = %s\n", account_id, account_list[account_id].Email);
    printf("Account[%d].Name = %s\n", account_id, account_list[account_id].Name);
    printf("Account[%d].Password = %s\n", account_id, account_list[account_id].Password);
    printf("Account[%d].isAdmin = %d\n\n", account_id, account_list[account_id].isAdmin);
}
void PrintAccountList(Account* account_list, int num_accounts) {
    printf("\nAccounts:\n\n");
    for (int i = 0; i < num_accounts; i++)
    {
        printf("Account[%d].Email = %s\n", i, account_list[i].Email);
        printf("Account[%d].Name = %s\n", i, account_list[i].Name);
        printf("Account[%d].Password = %s\n", i, account_list[i].Password);
        printf("Account[%d].isAdmin = %d\n\n", i, account_list[i].isAdmin);
    }
}

int CreateAccount(FILE* accounts, Account* account_list, int num_accounts, bool isAdmin) {
    char input_buffer[STRING_SIZE];
    int num_matches = 0;

    printf("Create account\n");
    printf("Enter your email: ");
    num_matches = scanf("%s", input_buffer);
    for (int i = 0; i < num_accounts; i++)
    {
        if (strcmp(input_buffer, account_list[i].Email) == 0) {
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
    //num_matches = scanf("%s", input_buffer);
    fprintf(accounts, "isAdmin \t%u\n", isAdmin);
    fprintf(accounts, "\n", input_buffer);
    printf("Account creation successful.\n");
    fclose(accounts);
    return 0;
}

int LoginAccount(Account* account_list, int num_accounts) {
    char input_buffer[STRING_SIZE];
    int num_matches;

    printf("Login to your account\n");
    printf("Enter your email address: ");
    num_matches = scanf("%s", input_buffer);
    for (int i = 0; i < num_accounts; i++)
    {
        if (strcmp(input_buffer, account_list[i].Email) == 0) {
            printf("Email address found.\n");
            for (int j = 0; j < 5; j++)
            {
                printf("Enter your password: ");
                num_matches = scanf("%s", input_buffer);
                if (strcmp(input_buffer, account_list[i].Password) == 0) {
                    printf("Logging in...\n");
                    return i;
                }
                else
                {
                    printf("Incorrect password.\n");
                }
                if (j == 4) {
                    fprintf(stderr, "Too many attempts. Exiting program.");
                    return -1;
                }
            }
        }
    }
    fprintf(stderr, "Email not found.\n");
    return -1;
}