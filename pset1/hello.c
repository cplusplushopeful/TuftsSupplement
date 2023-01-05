#include <stdio.h>
#include <cs50.h>
int main(void)
{
    string username = get_string("What's your name?\n");
    printf("hello, world%s\n", username);
}