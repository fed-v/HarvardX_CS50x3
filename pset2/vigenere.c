#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[]){
  
   
    //ERROR CONTROL
    if(argc != 2 )
    {
       
        printf("Please include one and only one string key!\n");
        return 1;
    
    }
   
    //GET KEY 
    string key = argv[1];
    
    
    //ITERATE OVER PLAINTEXT
    for(int i = 0, n = strlen(key); i < n; i++)
    {
    
        //CHECK IF ITS A LETTER
        if(!isalpha(key[i]))
        {
           
            printf("Key must ONLY be alphabetical \n");
            return 1;
        }
    }
    
    
    //GET PHRASE TO CIPHER
    string plaintext= GetString();
    
    int shift = 0;
    char letter;
    
    
    //ITERATE OVER PLAINTEXT
    for(int i = 0, n = strlen(plaintext); i < n; i++)
    {
    
        //CHECK IF ITS A LETTER
        if(isalpha(plaintext[i]))
        {
           
           //CHECK IF KEY PHRASE IS UPPER/LOWER CASE TO CONVERT SALT LETTER
           if(isupper(key[shift]))
           {
                letter = (int)(key[shift])-(int)'A';
           }else{
                letter = (int)(key[shift])-(int)'a';
           }
           
           
            //CHECK IF PLAINTEXT IS UPPER/LOWER CASE TO CONVERT CIPHER LETTER
            if(isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i]-'A'+letter)%26+'A');
            }else{               
                printf("%c", (plaintext[i]-'a'+letter)%26+'a');
            }
            
            
            //CHANGE SHIFT NUMBER ACCORDING TO KEY LENGTH
            if(shift<(strlen(key)-1))
            {
                shift++;
            }else{
                shift = 0;
            }
       
        }else{
            printf("%c", plaintext[i]);
        }
    }
    
    printf("\n");
    
}
