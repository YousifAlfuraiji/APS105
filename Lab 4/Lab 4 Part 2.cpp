#include <stdio.h>
int convertDecimalToBinary(int n){
    int calc=0; int rem, i; 
    for(i=1; n>0; i=i*10){
        rem=n%2;
        n=n/2;
        calc=calc+rem*i;
        }
        return(calc);
}
int convertBinaryToDecimal(int n){
    int calc=0; int rem, i; 
    for(i=1; n>0; i=i*2){
        rem=n%10;
        n=n/10;
        calc=calc+rem*i;
    }
    return(calc);
}
int main(void)
{
    int input, answer;
    char choice;
    input=0;
    answer=0;
    printf("Enter B for conversion of Binary to Decimal, OR\n");
    printf("Enter D for conversion of Decimal to Binary: ");
    scanf(" %c", &choice);
    if(choice!='B'&&choice!='D'){
        printf("Invalid input; Goodbye\n");
		return 0;
    }
	
	printf("Enter your number: ");
    scanf("%d", &input);
    if(choice=='B'){
        answer=convertBinaryToDecimal(input);
        printf("%d in binary = %d in decimal\n", input, answer);
    }else if(choice=='D'){
        answer=convertDecimalToBinary(input);
        printf("%d in decimal = %d in binary\n", input, answer);
    }
    return 0;
}
