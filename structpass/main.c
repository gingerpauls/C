#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h" // Include this header for malloc
#include "string.h" // Include this header for strcpy

#define LIST_SIZE 4

typedef struct {
    char* name;
} Account;

void printlist(Account* account_list);

int main(void) {
    char* string1;

    Account account1;

    Account account2 = { .name = 0 };
    Account* acc2ptr = &account2;

    Account* account3;
    account3 = malloc(sizeof(Account));

    Account account_list[LIST_SIZE] = { 0 }; // &account_list[0] ?

    Account* account_list_ptr[LIST_SIZE];
    //Account* account_list_ptr[LIST_SIZE] = malloc(sizeof(Account) * LIST_SIZE);
    //account_list_ptr[LIST_SIZE] = malloc(sizeof(Account) * LIST_SIZE);

    string1 = "Paul\n";
    account1.name = "Doug\n";
    account2.name = "Cheryl\n";
    account3->name = "Joanne\n";
    for (int i = 0; i < LIST_SIZE; i++)
    {
        account_list[i].name = "listname\n";
    }

    //for (int i = 0; i < LIST_SIZE; i++)
    //{
    //    account_list_ptr[i]->name = "listptrname\n";
    //}

    printf("%s", string1);
    printf("%s", account1.name);
    printf("%s", account2.name);
    printf("%s", acc2ptr->name);
    printf("%s", account3->name);

    //for (int i = 0; i < LIST_SIZE; i++)
    //{
    //    printf("%s", &account_list_ptr[i]->name);
    //}
    printlist(account_list);

    return 0;
}

void printlist(Account* account_list)
{    
    for (int i = 0; i < LIST_SIZE; i++)
    {
        printf("%s", account_list[i].name);
    }    
}