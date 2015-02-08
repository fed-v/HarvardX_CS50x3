#include <cs50.h>
#include <stdio.h>
#include <math.h>

float change;
int coins=0;

int main(void){
    
    //INITIALIZE FUNCTION & PROMPT CHANGE
    void countCoins(int cents);
    
    printf("How much is your change?\n ");
    change = GetFloat();
    
    
    //CONTROL CHANGE IS VALID
    do{

    if(change<=0)
    {
         printf("Retry:");
         change = GetFloat();
    }
    
    }while(change<=0);
    
    
    // CONVERT CHANGE TO CENTS
    change = change * 100;
    change = round(change);
    change = (int) change;
    
    
    //HOW MANY QUARTERS
    countCoins(25);
    
    //HOW MANY DIMES
    countCoins(10);
    
    //HOW MANY NICKELS
    countCoins(5);
    
    //HOW MANY PENNIES
    countCoins(1);
    
    //PRINT TOTAL COINS
    printf("%i\n", coins);
    
}

void countCoins(int cents)
{
    while(change>=cents)
    {
        change = change-cents;
        coins = coins + 1;   
    }
}
