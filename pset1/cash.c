#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void){
    int totalCoins = 0;
    bool moreToBeSubtracted = true;
    float changeOwed = 0;
    do{
        changeOwed = round((100 * get_float("How much change are you going to pay?")));        
    }
    while(changeOwed < 0);
    while(moreToBeSubtracted == true){
        if(changeOwed >= 25){
          changeOwed = round(changeOwed - 25);
          totalCoins += 1;
        }
        else{
            if(changeOwed >= 10){
                changeOwed = round(changeOwed - 10);
                totalCoins += 1;
            }
            else{
                if(changeOwed >= 5){
                    changeOwed = round(changeOwed - 5);
                    totalCoins += 1;
                }
                else{
                    if(changeOwed >= 1){
                        changeOwed = round(changeOwed - 1);
                        totalCoins += 1;
                    }
                    else{
                        moreToBeSubtracted = false;
                    }
                }
            }
        }
    }
    printf("%i\n", totalCoins);

}

 
