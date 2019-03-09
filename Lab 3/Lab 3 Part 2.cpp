#include <stdio.h>

int main(void)
{
	char operation;
    double firstNumber, secondNumber, answer;
    
    printf("Enter first number: ");
    scanf("%lf", &firstNumber);
    printf("Enter second number: ");
    scanf("%lf", &secondNumber);
    printf("Enter calculation command (one of a, s, m, or d): ");
    scanf(" %c", &operation);

    if(operation=='a'){
        answer= firstNumber+secondNumber;
        printf("Sum of %2.2lf and %2.2lf is %2.2lf\n", firstNumber, secondNumber, answer);
    }else if(operation=='s'){
        answer= firstNumber-secondNumber;
        printf("Difference of %2.2lf from %2.2lf is %2.2lf\n", firstNumber, secondNumber, answer);
    }else if(operation=='m'){
        answer= firstNumber*secondNumber;
        printf("Product of %2.2lf and %2.2lf is %2.2lf\n", firstNumber, secondNumber, answer);
    }else if(operation=='d'){
        if(secondNumber!=0){
            answer= firstNumber/secondNumber;
            printf("Division of %2.2lf by %2.2lf is %2.2lf\n", firstNumber, secondNumber, answer);
        }
        else
            printf("Error, trying to divide by zero\n");
    }
    else
        printf("Error, unknown calculation command given\n");
	return 0;
}
