#include <stdio.h>

int main(void)
{
    int cents, quarters, dimes, nickels, centSave;
    
    printf("Please give an amount in cents less than 100: ");
    scanf("%d", &cents);
    centSave=cents;
    if(cents>=25){
        quarters=cents/25;
        cents=cents-quarters*25;
    }else
        quarters=0;
    if(cents>=10){
        dimes=cents/10;
        cents=cents-dimes*10;
    }else
        dimes=0;
    if(cents>=5){
        nickels=cents/5;
        cents=cents-nickels*5;
    }else
        nickels=0;
        
    
    printf("%d cents: ", centSave);
    if(quarters==1)
        printf("%d quarter",quarters);
    else if(quarters>1)
        printf("%d quarters", quarters);
    if(dimes!=0||nickels!=0||cents!=0)
        printf(",");
    if(dimes==1)
        printf(" %d dime",dimes);
    else if(dimes>1)
        printf(" %d dimes", dimes);
    if(nickels!=0||cents!=0)
        printf(",");
    if(nickels==1)
        printf(" %d nickel", nickels);
    else if(nickels>1)
        printf(" %d nickels", nickels);
    if(cents!=0)
        printf(",");
    if(cents==1)
        printf(" %d cent", cents);
    else if(cents>1)
        printf(" %d cents", cents);
        printf(".");
    printf("\nGoodbye.\n");
	return 0;
}