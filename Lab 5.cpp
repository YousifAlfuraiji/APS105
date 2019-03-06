#include <stdio.h>

//Determines the factorial of a given number
int factorial(int n){
    int product=1;
    for(int i=1; i<=n; i++){
        product=product*i;
    }
    return product;
}

//Calculates nCr 
int choose(int n, int r){
    int nCr=factorial(n)/(factorial(r)*factorial(n-r));
    return nCr;
}

// Main body of the function
int main(void){
    int answer, input, r;
    
    //Ask the user for desired row #s
    printf("Enter the number of rows: ");
    scanf("%d", &input);
    
    //Checks if input is not negative (won't terminate)
    while(input>=0){
        
        //Controls what's printed each row
        for(int row=0; row<=input-1; row++){
            r=row;
            
            //Controls what's printed each column
            for(int col=0; col<3*(input-row)-3; col++)   
                printf(" ");
            //Prints the nCr values of tha row
            for(int counter=0; counter<=row; counter++){
                answer=choose(row, r);
                r--;
                printf("%-6d", answer);
            }
            //Go to next line before restarting loop
            printf("\n");
        }
        //Request the input again
        printf("Enter the number of rows: ");
        scanf("%d", &input);
    }
    return 0;
}