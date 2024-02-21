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

typedef struct {
    char *email;
    char *name;
    char *pw;
    _Bool *isAdmin;
} Account;

typedef struct {
    Account *account;
    size_t memory_size;
    int num_accounts;
    int num_admins;
    void *heap_ptr;
} AccountList;

void GetInputStdIn(Input *input) {
    scanf_s("%*s %s", input->buffer, input->size);
    //if(scanf_s("%*s %s", input->buffer, input->size) == 0) {
    //    printf("Error: Input too long.\n\n");
    //    exit(EXIT_FAILURE);
    //}
}
void GetInputFile(FILE* account_stream, Input *input) {
    if(fscanf_s(account_stream, "%*s %s", input->buffer, input->size) == 0) {
        printf("Error: Input too long.\n\n");
        exit(EXIT_FAILURE);
    }
}
void BoundaryCheck(AccountList *account_list) {
    if((char *) account_list->heap_ptr > (char *) account_list->account + account_list->memory_size) {
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
    AccountList account_list = {
        .account = NULL,
        .memory_size = 0,
        .num_accounts = 100,
        .num_admins = 0,
        .heap_ptr = NULL};
    Input input = {.buffer = NULL, .size = STRING_SIZE};
    //while(scanf_s("%s", input.buffer, input.size) == 1) {
    //    if(strcmp(input.buffer, "Email") == 0) {
    //        account_list.num_accounts++;
    //    }
    //}

    account_list.memory_size =
        (account_list.num_accounts * sizeof(Account)) +
        (account_list.num_accounts * (MAX_EMAIL_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_NAME_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_PW_LENGTH) * sizeof(char)) +
        (account_list.num_accounts * (MAX_ISADMIN_LENGTH) * sizeof(_Bool));
    account_list.account = malloc(account_list.memory_size);
    (char *) account_list.heap_ptr = (char *) account_list.account + (account_list.num_accounts * sizeof(Account));
    for(size_t i = 0; i < account_list.num_accounts; i++) {
        GetInputStdIn(&input);
        account_list.account[i].email = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, email);
        GetInputStdIn(&input);
        account_list.account[i].name = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, name);
        GetInputStdIn(&input);
        account_list.account[i].pw = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, pw);
        GetInputStdIn(&input);
        account_list.account[i].isAdmin = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
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
    //for(size_t i = 0; i < account_list.num_accounts; i++) {
    //    printf_s("\nID \t\t%d\n", i);
    //    printf_s("Email \t\t%p\n", &account_list.account[i].email);
    //    printf_s("Name \t\t%p\n", &account_list.account[i].name);
    //    printf_s("Password \t%p\n", &account_list.account[i].pw);
    //    printf_s("isAdmin \t%p", &account_list.account[i].isAdmin);
    //}
    //fclose(account_stream);
    free(account_list.account);

    return 0;
}
