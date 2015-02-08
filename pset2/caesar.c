#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[]){
  
   
    //ERROR CONTROL
    if(argc != 2 )
    {
       
        printf("Please include one and only one positive int\nafter calling ceasar!\n");
        return 1;
    
    }
   
   
    //CONVERT STRING TO INT
    int key = atoi(argv[1]);
        
        
    //CONTROL VALID KEY
    if(isdigit(key) || key > 0)
    {
        
    }else{
        printf("Please provide a positive int\n");
        return 1;
    }
    
    
    //GET PHRASE TO CIPHER
    string plaintext= GetString();
    
    
    //ITERATE OVER PLAINTEXT
    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
    
        //CHECK IF ITS A LETTER
        if(isalpha(plaintext[i]))
        {
           
            //CHECK IF IT IS UPPER/LOWER CASE
            if(isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i]-'A'+key)%26+'A');
            }else{
                printf("%c", (plaintext[i]-'a'+key)%26+'a');
            }
       
        }else{
            printf("%c", plaintext[i]);
        }
    }
    
    printf("\n");
    
}

