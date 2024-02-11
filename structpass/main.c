#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "assert.h"
//#include "malloc.h"
#include "stdlib.h"
#define STRING_SIZE 32
#define LIST_SIZE 4

typedef struct {
    char Email[STRING_SIZE];
    //char* Email;
} Account;

void GetAccount(Account* account);
void GetAccountList(Account* account_list);
void PrintAccount(Account* account);
//void PrintAccountList(Account* account_list, int size)

int main(int num_arguments, char* argument_value[]) {
    Account account1 = { 0 };
    //account1.Email = malloc(sizeof(char) * STRING_SIZE); // is this the same as char Email[STRING_SIZE] ?
    Account account_list[LIST_SIZE] = { 0 };

    GetAccount(&account1);
    GetAccountList(&account_list);

    PrintAccount(&account1);


    //free(account1.Email);
    return 0;
}

void GetAccount(Account* account) {
    FILE* accountfile;
    char header_string[STRING_SIZE];
    
    accountfile = fopen("accounts.txt", "r+");
    if (accountfile == NULL) {
        return 1;
    }
    fscanf(accountfile, "%s %s", header_string, account->Email);
    fclose(accountfile);
}

void GetAccountList(Account* account_list) {
    FILE* accountfile;
    char header_string[STRING_SIZE];
    char data_string[STRING_SIZE];

    accountfile = fopen("accounts.txt", "r+");
    if (accountfile == NULL) {
        return 1;
    }
    int i = 0;
    while (!(feof(accountfile))) {
        fscanf(accountfile, "%s %s", header_string, account_list[i].Email);
    }
    fscanf(accountfile, "%s %s", header_string, account_list[i].Email);
    fclose(accountfile);
}

void PrintAccount(Account* account) {
    printf("%s\n", account->Email);
}

//void PrintAccountList(Account* account_list, int size) {
//
//    printf("%s\n", account->Email);
//}