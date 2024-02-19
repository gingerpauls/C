#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE (254 + 1)
#define MAX_EMAIL_LENGTH (254 + 1)
#define MAX_NAME_LENGTH (254 + 1)

typedef struct
{
    char *email;
    char *name;
} Account;

typedef struct
{
    char buffer[STRING_SIZE];
    unsigned int size;
} Input;

void BoundaryCheck(char *current_ptr, Account *account_list, size_t account_list_size)
{
    if(current_ptr > (char *) account_list + account_list_size)
    {
        printf("Error: Not enough heap memory.\n\n");
        exit(EXIT_FAILURE);
    }
}
void GetInput(Input *input)
{
    if(scanf_s("%s", input->buffer, input->size) == 0)
    {
        printf("Error: Input too long.\n\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    Input input = { .buffer = NULL, .size = STRING_SIZE};
    unsigned int total_num_accounts = 3;
    size_t account_list_size =  (total_num_accounts * sizeof(Account)) +
                                (total_num_accounts * (MAX_EMAIL_LENGTH) * sizeof(char)) +
                                (total_num_accounts * (MAX_NAME_LENGTH) * sizeof(char));
    Account *account_list = malloc(account_list_size);
    char *current_ptr = (char *) account_list + (total_num_accounts * sizeof(Account));
    for(size_t i = 0; i < total_num_accounts; i++)
    {
        printf_s("email: ");
        GetInput(&input);
        account_list[i].email = current_ptr;
        current_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(current_ptr, account_list, account_list_size);
        if(strcpy_s(account_list[i].email, (strlen(input.buffer) + 1), input.buffer))
        {
            printf("Error: Data too long.\n\n");
            exit(EXIT_FAILURE);
        }
        printf_s("name: ");
        GetInput(&input);
        account_list[i].name = current_ptr;
        current_ptr += (strlen(input.buffer) + 1) * sizeof(char);
        BoundaryCheck(current_ptr, account_list, account_list_size);
        if(strcpy_s(account_list[i].name, (strlen(input.buffer) + 1), input.buffer))
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