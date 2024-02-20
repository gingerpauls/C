#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define STRING_SIZE (254 + 1)
#define MAX_EMAIL_LENGTH (254 + 1)
#define MAX_NAME_LENGTH (254 + 1)
#define MAX_PW_LENGTH (254 + 1)
#define MAX_ISADMIN_LENGTH (1 + 1)

enum ACCOUNT_PROPERTY {
    ID, 
    email,
    name,
    pw,
    isAdmin,
};

typedef struct {
    char buffer[STRING_SIZE];
    unsigned int size;
} Input;

typedef struct
{
    char *email;
    char *name;
    char *pw;
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
void CopyString(AccountList account_list, Input *input, int i, int ACCOUNT_PROPERTY ) {
    switch(ACCOUNT_PROPERTY) {
        case email:
            if(strcpy_s(account_list.account[i].email, (strlen(input->buffer) + 1), input->buffer)) {
                printf("Error: Data too long.\n\n");
                exit(EXIT_FAILURE);
            }
            break;
        case name:
            if(strcpy_s(account_list.account[i].name, (strlen(input->buffer) + 1), input->buffer)) {
                printf("Error: Data too long.\n\n");
                exit(EXIT_FAILURE);
            }
            break;
        case pw:
            if(strcpy_s(account_list.account[i].pw, (strlen(input->buffer) + 1), input->buffer)) {
                printf("Error: Data too long.\n\n");
                exit(EXIT_FAILURE);
            }
            break;
        case isAdmin:
            if(strcpy_s(account_list.account[i].isAdmin, (strlen(input->buffer) + 1), input->buffer)) {
                printf("Error: Data too long.\n\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf_s("Could not copy account data.\n");
            break;
    }

}
int main(void) {
    FILE *account_stream = NULL;
    errno_t err;
    err = fopen_s(&account_stream, "accounts.txt", "r");
    if(err == 0) {
        printf("Database (accounts.txt) was opened.\n");
    }
    else {
        printf("Database (accounts.txt) was not opened.\n");
        return 1;
    }
    fseek(account_stream, 0, SEEK_END);
    if(ftell(account_stream) == 0) {
        printf("Database (accounts.txt) found, but no accounts created.\n");
        fclose(account_stream);
        return 1;
    }
    rewind(account_stream);
    AccountList account_list = {
        .account = NULL,
        .memory_size = 0,
        .num_accounts = 0,
        .num_admins = 0,
        .heap_ptr = NULL};
    Input input = {.buffer = NULL, .size = 255};
    while(!feof(account_stream)) {
        fscanf_s(account_stream, "%s", input.buffer, input.size);
        if(strcmp(input.buffer, "Email") == 0) {
            account_list.num_accounts++;
        }
    }
    rewind(account_stream);
    account_list.memory_size =
        (account_list.num_accounts * sizeof(Account)) +
        (account_list.num_accounts * (MAX_EMAIL_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_NAME_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_PW_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_ISADMIN_LENGTH) * sizeof(_Bool)); // sizeof (bool) ?
    account_list.account = malloc(account_list.memory_size);
    Input input = {.buffer = NULL, .size = STRING_SIZE};

    (char *) account_list.heap_ptr = (char *) account_list.account + (account_list.num_accounts * sizeof(Account));
    for(size_t i = 0; i < account_list.num_accounts; i++)
    {
        printf_s("email[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].email = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, email);

        printf_s("name[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].name = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, name);

        printf_s("pw[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].pw = account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, pw);

        printf_s("isAdmin[%d]: ", (int) i);
        GetInput(&input);
        account_list.account[i].isAdmin = (_Bool *) account_list.heap_ptr;
        (_Bool *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(_Bool);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, isAdmin);
    }

    for(size_t i = 0; i < account_list.num_accounts; i++) {
       printf_s("\nID \t\t%d\n", i);
       printf_s("Email \t\t%s\n", account_list.account[i].email);
       printf_s("Name \t\t%s\n", account_list.account[i].name);
       printf_s("Password \t%s\n", account_list.account[i].pw);
       printf_s("isAdmin \t%d\n", atoi(account_list.account[i].isAdmin));
    }

    free(account_list.account);
    fclose(account_stream);
    return 0;
}
