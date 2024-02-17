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
    char *email_next;
    char *name;
    char *name_next;
} Account;


int main(void)
{
    char input_buffer[STRING_SIZE];
    unsigned int email_size, name_size = 0;
    unsigned int total_num_accounts = 10;
    void *memory_start;
    Account account_list;

    email_size = (MAX_EMAIL_LENGTH + 1) * total_num_accounts;
    name_size = (MAX_NAME_LENGTH + 1) * total_num_accounts;

    memory_start = malloc(email_size + name_size);
    account_list.email = (char *) memory_start;
    account_list.email_next = account_list.email;
    account_list.name = (char*)(account_list.email + email_size);
    account_list.name_next = account_list.name;

    while(1)
    {
        printf("email: ");
        scanf("%s", input_buffer);
        strcpy(account_list.email_next, input_buffer);
        account_list.email_next = account_list.email_next + strlen(input_buffer);

        printf("name: ");
        scanf("%s", input_buffer);
        strcpy(account_list.name_next, input_buffer);
        account_list.name_next = account_list.name_next + strlen(input_buffer);
    }

    return 0;
}
