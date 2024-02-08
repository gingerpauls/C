/*
    admin
        add new books to library
        edit book
        delete book
        search book
        display list of books

        add members to to library
        edit (any) member information
        delete members

        issue books to library members
        view due date 
            late ? penalty : no penalty



    user
        search book
        display list of books
        edit self member information
        
        return book to library
        view due date
            late ? penalty : no penalty

    create account



*/
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdbool.h"
#include "string.h"


#define STRINGSIZE 30

typedef struct {
    bool IsAdmin;
    char Name[STRINGSIZE];
    char Password[STRINGSIZE];
} Account;



int main(int args, char *argv[]) {
    if(args < 2)
    {
        printf("Welcome to the library!\n");
        printf("use -c to create an account.\n");
        printf("use -l to login to an existing account.\n");
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        printf("Create account\n");
        printf("Enter your name: \n");
    }
    else if (strcmp(argv[1], "-l") == 0) 
    {
        printf("Login to your account\n");
        printf("Enter your name: \n");
    }
    //else 
    //{
    //    printf("Welcome to the library!\n");
    //    printf("use -c to create an account.\n");
    //    printf("use -l to login to an existing account.\n");
    //}
    
    return 0;
}