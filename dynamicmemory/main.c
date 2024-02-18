#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 255
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
    unsigned int total_num_accounts = 3;
    size_t account_list_size =
        (total_num_accounts * sizeof(Account)) +
        (total_num_accounts * (MAX_EMAIL_LENGTH + 1) * sizeof(char)) +
        (total_num_accounts * (MAX_NAME_LENGTH + 1) * sizeof(char));
    Account *account_list = malloc(account_list_size);
    account_list_size = _msize(account_list);
    char *current_ptr = (char *) account_list + (total_num_accounts * sizeof(Account));
    char *mem_block_end = (char *) (account_list + (account_list_size>>4)); // this >> 4 is weird.. 
    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf_s("email: ");
        if(scanf_s("%s", input_buffer, sizeof(input_buffer)) == 0)
        {
            printf("Error reading input. Input possibly too long.\n\n");
            exit(EXIT_FAILURE);
        }
        account_list[i].email = current_ptr;
        current_ptr += (strlen(input_buffer) + 1) * sizeof(char);
        if(current_ptr > (char *) account_list + account_list_size)
        {
            printf("you are out of your memory boundary.\n\n");
            exit(EXIT_FAILURE);
        }
        if(strcpy_s(account_list[i].email, sizeof(input_buffer), input_buffer))
        {
            printf("Error copying data. Data possibly too long.\n\n");
        }
        printf_s("name: ");
        if(scanf_s("%s", input_buffer, sizeof(input_buffer)) == 0)
        {
            printf("Error reading input. Input possibly too long.\n\n");
            exit(EXIT_FAILURE);
        }
        account_list[i].name = current_ptr;
        current_ptr += (strlen(input_buffer) + 1) * sizeof(char);
        strcpy_s(account_list[i].name, sizeof(input_buffer), input_buffer);
    }
    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf("email[%d]: %s\n", i, account_list[i].email);
        printf("name[%d]: %s\n", i, account_list[i].name);
    }

    free(account_list);
    return 0;
}