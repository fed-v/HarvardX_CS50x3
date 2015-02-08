#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    
    //printf("What is you name?");
    string name = GetString();
    
    printf("%c", toupper(name[0]));
    
    for(int i=0; i<strlen(name); i++)
    {
       
        if(name[i] == ' ')
        {
            if(name[i+1] != ' ')
            {
                printf("%c", toupper(name[i+1]));
            }
        }
    
    }
    
    printf("\n");
   
    return 0;
}
