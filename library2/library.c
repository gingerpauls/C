#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define STRING_SIZE (254 + 1)
#define MAX_EMAIL_LENGTH (254 + 1)
#define MAX_NAME_LENGTH (254 + 1)
#define MAX_PW_LENGTH (254 + 1)
#define MAX_ISADMIN_LENGTH (1 + 1)

typedef struct
{
    char buffer[STRING_SIZE];
    unsigned int size;
} Input;

typedef struct
{
    char *email;
    char *name;
    char *pw;
    //bool *isAdmin;
    _Bool *isAdmin;
} Account;

typedef struct
{
    Account *account;
    size_t memory_size;
    int num_accounts;
    int num_admins;
    void *heap_ptr;
} AccountList;

void GetInput(Input *input)
{
    if(scanf_s("%s", input->buffer, input->size) == 0)
    {
        printf("Error: Input too long.\n\n");
        exit(EXIT_FAILURE);
    }
}

void BoundaryCheck(AccountList *account_list)
{
    if((char *) account_list->heap_ptr > (char *) account_list->account + account_list->memory_size)
    {
        printf("Error: Not enough heap memory.\n\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    AccountList account_list = {.account = NULL, .memory_size = 0, .num_accounts = 2, .num_admins = 0, .heap_ptr = NULL};
    //account_list.account = {.email = NULL, .name = NULL, .pw = NULL, .isAdmin = NULL}
    account_list.memory_size =
        (account_list.num_accounts * sizeof(Account)) +
        (account_list.num_accounts * (MAX_EMAIL_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_NAME_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_PW_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_ISADMIN_LENGTH) * sizeof(char)); // sizeof (bool) ?
    account_list.account = malloc(account_list.memory_size);
    (char *) account_list.heap_ptr = (char *) account_list.account + sizeof(Account);
    Input input = {.buffer = NULL, .size = STRING_SIZE};

    for(size_t i = 0; i < account_list.num_accounts; i++)
    {
        (char *) account_list.heap_ptr = (char *) account_list.heap_ptr + sizeof(Account);
        printf_s("email[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].email = (char *) account_list.heap_ptr; // causes fuckyness
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].email, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }

        printf_s("name[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].name = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].name, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }

        printf_s("pw[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].pw = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].pw, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }

        printf_s("isAdmin[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].isAdmin = (_Bool *) account_list.heap_ptr;
        (_Bool *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(_Bool);
        BoundaryCheck(&account_list);
        if(strcpy_s(account_list.account[i].isAdmin, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < account_list.num_accounts; i++)
    {
        printf("email[%d]: %s\n", (int) i, account_list.account[i].email);
        printf("name[%d]: %s\n", (int) i, account_list.account[i].name);
        printf("name[%d]: %s\n", (int) i, account_list.account[i].pw);
        printf("name[%d]: %c\n", (int) i, *(account_list.account[i].isAdmin));
    }
    free(account_list.account);
    return 0;
}