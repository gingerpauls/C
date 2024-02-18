#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 254
#define MAX_EMAIL_LENGTH 254
#define MAX_NAME_LENGTH 254

typedef struct
{
    char *email;
    char *name;
} Account;

void BoundaryCheck(char *current_ptr, Account *account_list, size_t account_list_size)
{
    if(current_ptr > (char *) account_list + account_list_size)
    {
        printf("you are out of your memory boundary.\n\n");
        exit(EXIT_FAILURE);
    }
}
void GetInput(char *input_buffer, size_t size)
{
    sizeof(*input_buffer);
    if(scanf_s("%s", input_buffer, size) == 0)
    {
        printf("Error: Input too long.\n\n");
        exit(EXIT_FAILURE);
    }
}

void CopyData(Account *account_list, size_t size, char *input_buffer)
{
    if(strcpy_s(account_list[i].email, sizeof(input_buffer), input_buffer))
    {
        printf("Error: Data too long.\n\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    char input_buffer[STRING_SIZE + 1];
    unsigned int total_num_accounts = 2;
    size_t account_list_size =
        (total_num_accounts * sizeof(Account)) +
        (total_num_accounts * (MAX_EMAIL_LENGTH + 1) * sizeof(char)) +
        (total_num_accounts * (MAX_NAME_LENGTH + 1) * sizeof(char));
    Account *account_list = malloc(account_list_size);
    char *current_ptr = (char *) account_list + (total_num_accounts * sizeof(Account));
    char *mem_block_end = (char *) account_list + (account_list_size);
    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf_s("email: ");
        GetInput(input_buffer, sizeof(input_buffer));
        account_list[i].email = current_ptr;
        current_ptr += (strlen(input_buffer) + 1) * sizeof(char);
        BoundaryCheck(current_ptr, account_list, account_list_size);
        CopyData(account_list, sizeof(input_buffer), input_buffer);
        /*if(strcpy_s(account_list[i].email, sizeof(input_buffer), input_buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }*/
        printf_s("name: ");
        GetInput(input_buffer, sizeof(input_buffer));
        account_list[i].name = current_ptr;
        current_ptr += (strlen(input_buffer) + 1) * sizeof(char);
        BoundaryCheck(current_ptr, account_list, account_list_size);
        if(strcpy_s(account_list[i].name, sizeof(input_buffer), input_buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }
    }
    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf("email[%d]: %s\n", i, account_list[i].email);
        printf("name[%d]: %s\n", i, account_list[i].name);
    }

    free(account_list);
    return 0;
}