#include <cs50.h>
#include <stdio.h>

int main(void){
    
    // INIT VARIABLES
    
    int flag = 1;
    int height = 0;
 
    printf("Height: ");
    height = GetInt();
    
    //GET PYRAMID HEIGHT FROM USER
    do{
        
        // CONTROL EXIT CODE OF 0
        if(height==0){
           return 0;
        }
        
        // CONTROL VALUE AND SET FLAG
        if(height > 0 && height < 24){               
            flag = 0;
        }else{
             printf("Retry: ");
             height = GetInt();
        }
        
    } while(flag == 1);
    
    
    int spaces = height-1;
    
    //COLUMNS
    for(int i=1; i<=height; i++)
    {
        //EMPTY SPACES
        for(int n=0; n<spaces; n++)
        {
             printf(" ");    
        }
        
        //BRICKS
        for(int l=0; l<i+1; l++)
        {
             printf("#");    
        }
        
        printf("\n"); 
        spaces = spaces-1;
    }
}
