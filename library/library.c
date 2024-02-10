/*
    admin
        add new books to library
        edit book
        delete book
        search book
        display list of books

        add members to to library
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


    1. I want to be able to create an account.
        If that account exists already, tell me and take me to create account or login.
        If account does not exist, create account.
    2. How do i not overwrite accounts.txt

*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "assert.h"

#define STRING_SIZE 30
#define DATABASE_SIZE 1000000
#define NUM_ACCOUNTS_MAX 200 // if larger, will cause stack overflow

typedef struct {
    bool IsAdmin;
    char Name[STRING_SIZE];
    char Password[STRING_SIZE];
    char Email[STRING_SIZE];
} Account;

int PopulateAccounts(FILE* accounts, Account* account_list[]);

int main(int num_arguments, char *argument_value[]) {
    FILE* accounts;
    char input_buffer[DATABASE_SIZE]; // change to sizeof(Account) * NUM_ACCOUNTS
    Account account_list[NUM_ACCOUNTS_MAX] = {0, 0, 0};
    //Account* account_ptr = &account_list;
    int num_matches;
    int num_accounts;
    //void *malloc(size_t size)

    accounts = fopen("accounts.txt", "r+");

    if(num_arguments < 2)
    {
        printf("Welcome to the library!\n");
        printf("use -c to create an account.\n");
        printf("use -l to login to an existing account.\n");
    }
    else if (strcmp(argument_value[1], "-c") == 0)
    {
        if (accounts == NULL) {
            fprintf(stderr, "accounts.txt does not exist.\n");
            return 1;
        }

        // populate data
        int i = 0;
        char header_string[16];
        rewind(accounts);
        while (!feof(accounts)) {
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Email);
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Name);
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Password);
            i++;
        }
        num_accounts = i - 1;

        printf("Create account\n");
        printf("Enter your email: \n");
        num_matches = scanf("%s", input_buffer);
        for (int i = 0; i < num_accounts; i++)
        {
            if (strcmp(input_buffer, account_list[i].Email) == 0) {
                printf("Email address already exists in database. Use -l for login.\n");
                return 1;
            }
        }
        fprintf(accounts, "Email \t\t%s\n", input_buffer);
        printf("Enter your name: \n");
        num_matches = scanf("%s", input_buffer);
        fprintf(accounts, "Name \t\t%s\n", input_buffer);
        printf("Enter your password: \n");
        num_matches = scanf("%s", input_buffer);
        fprintf(accounts, "Password \t%s\n", input_buffer);
        fprintf(accounts, "\n", input_buffer);

        // re-populate data
//        PopulateAccounts(accounts, &account_ptr);
        i = 0;
        rewind(accounts);
        while (!feof(accounts)) {
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Email);
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Name);
            num_matches = fscanf(accounts, "%s %s", header_string, account_list[i].Password);
            i++;
        }
        num_accounts = i - 1;

        // print accounts
        printf("Accounts:\n");
        for (int i = 0; i < num_accounts; i++)
        {
            if (account_list[i].Name == 0) {
                break;
            }
            printf("Account[%d].Email = %s\n", i, &account_list[i].Email);
            printf("Account[%d].Name = %s\n", i, &account_list[i].Name);
            printf("Account[%d].Password = %s\n\n", i, &account_list[i].Password);
        }
    }
    else if (strcmp(argument_value[1], "-l") == 0) 
    {
        accounts = fopen("accounts.txt", "a+");
        fseek(accounts, 0, SEEK_END);
        if (ftell(accounts) == 0) {
            printf("No accounts created. Please create an admin account using -c.\n");
            return 1;
        }
        printf("Login to your account\n");
        printf("Enter your name: \n");
    }
    else 
    {
        fprintf(stderr, "Unknown arguments.\n"
                        "Use -c to create an account or -l to login to an existing account.\n");
    }

    fclose(accounts);
    
    return 0;
}

//int PopulateAccounts(FILE *accounts, Account* account_list[]) {
//    int i = 0, num_matches, num_accounts;
//    char header_string[16];
//
//    rewind(accounts);
//    while (!feof(accounts)) {
//        num_matches = fscanf(accounts, "%s %s", header_string, &account_list[i]->Email);
//        num_matches = fscanf(accounts, "%s %s", header_string, &account_list[i]->Name);
//        num_matches = fscanf(accounts, "%s %s", header_string, &account_list[i]->Password);
//        i++;
//    }
//    return (num_accounts = i - 1);
//}