#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define STRING_SIZE (30 + 1)
#define MAX_EMAIL_LENGTH (30 + 1)
#define MAX_NAME_LENGTH (30 + 1)
#define MAX_PW_LENGTH (30 + 1)
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


void BoundaryCheck(AccountList *account_list) {
    if((char *) account_list->heap_ptr > (char *) account_list->account + account_list->memory_size) {
        fprintf(stderr, "Error: Not enough heap memory.\n\n");
    }
}
void CopyString(AccountList account_list, Input *input, int i, int ACCOUNT_PROPERTY) {
    switch(ACCOUNT_PROPERTY) {
        case email:
            if(strcpy_s(account_list.account[i].email, (strlen(input->buffer) + 1), input->buffer)) {
                fprintf(stderr, "Error: Data too long.\n\n");
            }
            break;
        case name:
            if(strcpy_s(account_list.account[i].name, (strlen(input->buffer) + 1), input->buffer)) {
                fprintf(stderr, "Error: Data too long.\n\n");
            }
            break;
        case pw:
            if(strcpy_s(account_list.account[i].pw, (strlen(input->buffer) + 1), input->buffer)) {
                fprintf(stderr, "Error: Data too long.\n\n");
            }
            break;
        case isAdmin:
            if(strcpy_s(account_list.account[i].isAdmin, (strlen(input->buffer) + 1), input->buffer)) {
                fprintf(stderr, "Error: Data too long.\n\n");
            }
            break;
        default:
            fprintf(stderr, "Could not copy account data.\n");
            break;
    }
}
int GetInputFile(FILE *account_stream, Input *input) {
    char temp[STRING_SIZE];
    int err = 0;
    if(fgets(input->buffer, input->size, account_stream) == NULL) {
        fprintf(stderr, "fget error\n");
    }
    strcpy_s(temp, STRING_SIZE, input->buffer);
    if(strcmp(temp, "\n") == 0) {
        fgets(input->buffer, STRING_SIZE, account_stream);
        strcpy_s(temp, STRING_SIZE, input->buffer);
        while(strstr(temp, "\n") == NULL) {
            fgets(temp, STRING_SIZE, account_stream);
        }
    }
    while(strstr(temp, "\n") == NULL) {
        fgets(temp, STRING_SIZE, account_stream);
    }
    err = sscanf_s(input->buffer, "%*s %s", temp, STRING_SIZE);
    if(err == 0) {
        fprintf(stderr, "sscanf error: match failure before recieving first argument.\n");
    }
    else if(err == EOF) {
        fprintf(stderr, "sscanf error: input failure before first received argument was assigned.\n");
        strcpy_s(input->buffer, STRING_SIZE, "\0");
    }
    else if (err == 1){
        strcpy_s(input->buffer, STRING_SIZE, temp);
    }
    else {
        fprintf(stderr, "sscanf error: no matches found.\n");
    }
    return err;
}
int main(void) {
    FILE *account_stream = NULL;
    errno_t err;
    err = fopen_s(&account_stream, "accounts.txt", "r");
    if(err == 0) {
        fprintf(stderr, "Database (accounts.txt) was opened.\n");
    }
    else {
        fprintf(stderr, "Database (accounts.txt) was not opened.\n");
        return 1;
    }
    fseek(account_stream, 0, SEEK_END);
    if(ftell(account_stream) == 0) {
        fprintf(stderr, "Database (accounts.txt) found, but no accounts created.\n");
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
    Input input = {.buffer = NULL, .size = STRING_SIZE};
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
        (account_list.num_accounts * (MAX_ISADMIN_LENGTH) * sizeof(_Bool));
    account_list.account = malloc(account_list.memory_size);
    (char *) account_list.heap_ptr = (char *) account_list.account + (account_list.num_accounts * sizeof(Account));
    for(size_t i = 0; i < account_list.num_accounts; i++) {
        printf_s("\nID \t\t\t%d\n", i);
        // email
        GetInputFile(account_stream, &input);
        account_list.account[i].email = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, email);
        printf_s("Email \t\t%s\n", account_list.account[i].email);

        // name
        GetInputFile(account_stream, &input);
        account_list.account[i].name = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, name);
        printf_s("Name \t\t%s\n", account_list.account[i].name);

        // pw
        GetInputFile(account_stream, &input);
        account_list.account[i].pw = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, pw);
        printf_s("Password \t%s\n", account_list.account[i].pw);

        // isAdmin
        GetInputFile(account_stream, &input);
        account_list.account[i].isAdmin = (char *) account_list.heap_ptr;
        (char *) account_list.heap_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(&account_list);
        CopyString(account_list, &input, i, isAdmin);
        printf_s("isAdmin \t%d\n", atoi(account_list.account[i].isAdmin));
    }

    //for(size_t i = 0; i < account_list.num_accounts; i++) {
    //   printf_s("\nID \t\t\t%d\n", i);
    //   printf_s("Email \t\t%s\n", account_list.account[i].email);
    //   printf_s("Name \t\t%s\n", account_list.account[i].name);
    //   printf_s("Password \t%s\n", account_list.account[i].pw);
    //   printf_s("isAdmin \t%d\n", atoi(account_list.account[i].isAdmin));
    //}

    for(size_t i = 0; i < account_list.num_accounts; i++) {
        printf_s("\nID \t\t\t%d\n", i);
        printf_s("Email \t\t%p\n", &account_list.account[i].email);
        printf_s("Name \t\t%p\n", &account_list.account[i].name);
        printf_s("Password \t%p\n", &account_list.account[i].pw);
        printf_s("isAdmin \t%p", &account_list.account[i].isAdmin);
    }

    free(account_list.account);

    return 0;
}
