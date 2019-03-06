#include <stdio.h>
#include <math.h>
int main(int argc, char **argv)
{
	double num1, num2, num3, mean, SD;
    printf("Enter three numbers: "); 
    scanf("%lf %lf %lf",&num1, &num2, &num3); //allows the user to input 3 numbers
    mean= (num1+num2+num3)/3; //calculates the mean of the numbers inputted
    SD=sqrt((pow((num1-mean),2)+pow((num2-mean),2)+pow((num3-mean),2))/2); //calculates the standard deviation of the numbers inputted
    printf("The mean is %5.2lf and the standard deviation is %5.2lf\n", mean, SD); //prints the final results
	return 0;
}