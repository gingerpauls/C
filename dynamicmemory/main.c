#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 100
#define MAX_EMAIL_LENGTH 254
#define MAX_NAME_LENGTH 254

typedef struct
{
    char *email;
    char *name;
} Account;

int main(void)
{
    char input_buffer[STRING_SIZE];
    unsigned int email_size, name_size, account_list_size = 0;
    unsigned int total_num_accounts = 10;
    void *memory_start;
    Account *account_list[] = {NULL, NULL};

    account_list_size = sizeof(Account) * total_num_accounts;
    email_size = (MAX_EMAIL_LENGTH + 1) * total_num_accounts;
    name_size = (MAX_NAME_LENGTH + 1) * total_num_accounts;

    memory_start = malloc(account_list_size + email_size + name_size);
    account_list[0] = (char *) memory_start;
    account_list[0]->email = (char *) (account_list + account_list_size);
    account_list[0]->name = (char *) (account_list[0]->email + email_size);

    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf("email: ");
        scanf("%s", input_buffer);
        strcpy(account_list[i]->email, input_buffer);

        printf("name: ");
        scanf("%s", input_buffer);
        strcpy(account_list[i]->name, input_buffer);
    }

    return 0;
}
