#include <stdio.h>

int main(void)
{
	char band1Input, band2Input, multiplierInput, toleranceInput;
    double band1, band2, multiplier, resistance, tolerance;
    char *colour1, *colour2, *colour3, *colour4, *unit;
    //asks the user for the character that matches the desired 1st band
    printf("Please enter the 1st band: \n"); 
    scanf(" %c", &band1Input);
    //asks the user for the character that matches the desired 2nd band
    printf("Please enter the 2nd band: \n");
    scanf(" %c", &band2Input);
    //asks the user for the character that matches the desired multiplier band
    printf("Please enter the multiplier band: \n");
    scanf(" %c", &multiplierInput);
    //asks the user for the character that matches the desired tolerance band
    printf("Please enter the tolerance band: \n");
    scanf(" %c", &toleranceInput);
    
    //depending on the 1st band input, a colour and 1st band value are assigned
    if (band1Input=='K'||band1Input=='k'){
        colour1="Black";
        band1=0;
    }else if(band1Input=='B'||band1Input=='b'){
        colour1="Brown";
        band1=10;
    }else if(band1Input=='R'||band1Input=='r'){
        colour1="Red";
        band1=20;
    }else if(band1Input=='O'||band1Input=='o'){
        colour1="Orange";
        band1=30;
    }else if(band1Input=='E'||band1Input=='e'){
        colour1="Yellow";
        band1=40;  
    }else if(band1Input=='G'||band1Input=='g'){
        colour1="Green";
        band1=50;
    }else if(band1Input=='U'||band1Input=='u'){
        colour1="Blue";
        band1=60; 
    }else if(band1Input=='V'||band1Input=='v'){
        colour1="Violet";
        band1=70;
    }else if(band1Input=='Y'||band1Input=='y'){
        colour1="Grey";
        band1=80;
    }else if(band1Input=='W'||band1Input=='w'){
        colour1="White";
        band1=90;
    }
    
    //depending on the 2nd band input, a colour and 2nd band value are assigned
    if (band2Input=='K'||band2Input=='k'){
        colour2="Black";
        band2=0;
    }else if(band2Input=='B'||band2Input=='b'){
        colour2="Brown";
        band2=1;
    }else if(band2Input=='R'||band2Input=='r'){
        colour2="Red";
        band2=2;
    }else if(band2Input=='O'||band2Input=='o'){
        colour2="Orange";
        band2=3;
    }else if(band2Input=='E'||band2Input=='e'){
        colour2="Yellow";
        band2=4;  
    }else if(band2Input=='G'||band2Input=='g'){
        colour2="Green";
        band2=5;
    }else if(band2Input=='U'||band2Input=='u'){
        colour2="Blue";
        band2=6; 
    }else if(band2Input=='V'||band2Input=='v'){
        colour2="Violet";
        band2=7;
    }else if(band2Input=='Y'||band2Input=='y'){
        colour2="Grey";
        band2=8;
    }else if(band2Input=='W'||band2Input=='w'){
        colour2="White";
        band2=9;
    }
    
    //depending on the multiplier band input, a colour and multiplier band value are assigned
    if (multiplierInput=='K'||multiplierInput=='k'){
        colour3="Black";
        multiplier=1;
    }else if(multiplierInput=='B'||multiplierInput=='b'){
        colour3="Brown";
        multiplier=10;
    }else if(multiplierInput=='R'||multiplierInput=='r'){
        colour3="Red";
        multiplier=100;
    }else if(multiplierInput=='O'||multiplierInput=='o'){
        colour3="Orange";
        multiplier=1000;
    }else if(multiplierInput=='E'||multiplierInput=='e'){
        colour3="Yellow";
        multiplier=10000;  
    }else if(multiplierInput=='G'||multiplierInput=='g'){
        colour3="Green";
        multiplier=100000;
    }else if(multiplierInput=='U'||multiplierInput=='u'){
        colour3="Blue";
        multiplier=1000000; 
    }else if(multiplierInput=='V'||multiplierInput=='v'){
        colour3="Violet";
        multiplier=10000000;
    }else if(multiplierInput=='L'||multiplierInput=='l'){
        colour3="Gold";
        multiplier=0.1;
    }else if(multiplierInput=='S'||multiplierInput=='s'){
        colour3="Silver";
        multiplier=0.01;
    }

    //depending on the tolerance band input, a colour and tolerance band value are assigned
    if(toleranceInput=='B'||toleranceInput=='b'){
        colour4="Brown";
        tolerance=1;
    }else if(toleranceInput=='R'||toleranceInput=='r'){
        colour4="Red";
        tolerance=2;
    }else if(toleranceInput=='G'||toleranceInput=='g'){
        colour4="Green";
        tolerance=0.5;
    }else if(toleranceInput=='U'||toleranceInput=='u'){
        colour4="Blue";
        tolerance=0.25; 
    }else if(toleranceInput=='V'||toleranceInput=='v'){
        colour4="Violet";
        tolerance=0.10;
    }else if(toleranceInput=='Y'||toleranceInput=='y'){
        colour4="Grey";
        tolerance=0.05;
    }else if(toleranceInput=='L'||toleranceInput=='l'){
        colour4="Gold";
        tolerance=5;
    }else if(toleranceInput=='S'||toleranceInput=='s'){
        colour4="Silver";
        tolerance=10;
    }
    
    //calculate the resistance value of the full resistor
    resistance=(band1+band2)*multiplier;
    
    //converts the Ohms units appropriately to be easily read
    if (resistance>=1000000){
        resistance=resistance/1000000;
        unit="MOhms";
    }else if(resistance>=1000){
        resistance=resistance/1000;
        unit="KOhms";
    }else{
        unit="Ohms";
    }
    //printing the resistor bands and the resistance calculated along with its tolerance
    printf("Resistor bands: %s %s %s %s \n", colour1, colour2, colour3, colour4);
    printf("Resistance: %6.2lf %s +/- %3.2lf %% \n",resistance,unit,tolerance);
	return 0;
}
