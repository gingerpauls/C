#include "windows.h"
#include "stdio.h"

int WINAPI wWinMain(    HINSTANCE hInstance, 
                        HINSTANCE hPrevInstance, 
                        PWSTR pCmdLine, 
                        int nCmdShow)
{
    printf ( "Hello World!\n" );
    return (0);
}