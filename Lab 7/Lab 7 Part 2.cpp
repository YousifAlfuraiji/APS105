#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//Sets up board values array
void initializeBoard(int n, char board[][26]){ 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            board[i][j]='U';
        }
    }
    board[(n-1)/2][(n-1)/2]='W';
    board[(n-1)/2+1][(n-1)/2]='B';
    board[(n-1)/2][(n-1)/2+1]='B';
    board[(n-1)/2+1][(n-1)/2+1]='W';
}

//Spaces and Prints the specific values in specific places
void printBoard(char board[][26], int n){ 
    printf("  ");
    for(int col=0; col<n; col++){
        printf("%c", 'a'+col);
    }
    printf("\n");
    for(int row=0; row<n; row++){
        printf("%c ", 'a'+row);
        for(int col=0; col<n; col++){
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

//Chooses the colour of the opponent
char opponent(char colour){
    if(colour=='B') return 'W';
    if(colour=='W') return 'B';
    else return '-';
}

//Checks if the position is in bounds
bool positionInBounds(int n, char row, char col){
    if((row-'a'>=0)&&(row-'a'<n)&&
       (col-'a'>=0)&&(col-'a'<n))
           return true;
    return false;
}

//Checks if one of the possible 8 directions is legal
bool checkLegalInDirection(char board[][26], int n, char row, char col,
                            char colour, int deltaRow, int deltaCol){
                                int r=(row-'a')+deltaRow;
                                int c=(col-'a')+deltaCol;
                                int count=0; //count #opponent colour appears in adj spots along direction
                                while(positionInBounds(n, r+'a', c+'a')&&board[r][c]==opponent(colour)){
                                    count++;
                                    r=r+deltaRow;
                                    c=c+deltaCol;
                                }
                                if(board[r][c]==colour && count!=0 && positionInBounds(n, r+'a', c+'a')) return true;
                                return false;
}

//Counts the score along one of the possible 8 directions
int countScoreInDirection(char board[][26], int n, char row, char col,
                            char colour, int deltaRow, int deltaCol){
                                int r=(row-'a')+deltaRow;
                                int c=(col-'a')+deltaCol;
                                int count=0; //count #opponent colour appears in adj spots along direction
                                while(positionInBounds(n, r+'a', c+'a')&&board[r][c]==opponent(colour)){
                                    count++;
                                    r=r+deltaRow;
                                    c=c+deltaCol;
                                }
                                return count;
}

//Check if move is legal in one of the 8 directions
bool checkIfMoveLegal(int n, char board[][26], char colour, int row, int col){
    if(board[row][col]=='U'){
        for(int deltaRow=-1; deltaRow<=1; deltaRow++){
            for(int deltaCol=-1; deltaCol<=1; deltaCol++){
                        
                if(deltaRow==0&&deltaCol==0) continue;
                char rowLetter='a'+row;
                char colLetter='a'+col;
                if(checkLegalInDirection(board, n, rowLetter, colLetter, colour, deltaRow, deltaCol)){
                    return true;
                        }
            }
        }
    }
    return false;
}

//Counts score for a single index in array
int countScore(int n, char board[][26], char colour, char rowLetter, char colLetter){ //check score
    int count=0;
    for(int deltaRow=-1; deltaRow<=1; deltaRow++){
        
        for(int deltaCol=-1; deltaCol<=1; deltaCol++){
            if(deltaRow==0 && deltaCol==0) continue;

            if(checkLegalInDirection(board, n, rowLetter, colLetter, colour, deltaRow, deltaCol)){
                
            count+=countScoreInDirection(board, n, rowLetter, colLetter, colour, deltaRow, deltaCol);
            }
        }
    }
    return count;
}

//Outputs the maxmimum value in the an array
int maxValInArray(int score[][26], int n, int *scoreRow, int *scoreCol){
    int max=0;
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            if(score[row][col]>max){
                max=score[row][col];
                *scoreRow=row;      //returns as a pointer the row of the max val in the array
                *scoreCol=col;      //returns as a pointer the col of the max val in the array
            }
        }
    }
    return max;
    
}

//Executes the move decided and flips pieces accordingly 
void applyMove(int n, char board[][26], char colour, char rowLetter, char colLetter){
    int count;
    for(int deltaRow=-1; deltaRow<=1; deltaRow++){
        for(int deltaCol=-1; deltaCol<=1; deltaCol++){
            if(deltaRow==0 && deltaCol==0) continue;
                
            int row=rowLetter-'a'+deltaRow;
            int col=colLetter-'a'+deltaCol;
            if(checkLegalInDirection(board, n, rowLetter, colLetter, colour, deltaRow, deltaCol)){
                for(count=0; board[row+deltaRow*count][col+deltaCol*count]==opponent(colour); count++)
                    board[row+deltaRow*count][col+deltaCol*count]=colour;
                board[rowLetter-'a'][colLetter-'a']=colour;
            }
        }
    }
}

//Computer decides what move to play
void compMove(int n, char board[][26], char colour){
    int score[26][26];
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            if(checkIfMoveLegal(n, board, colour, row, col)){
                score[row][col]=countScore(n, board, colour, row+'a', col+'a');
                if ((row == 0 && col == 0) ||
                    (row == 0 && col == n-1) ||
                    (row == n-1 && col == 0) ||
                    (row == n-1 && col == n-1)) score[row][col] += 20;
                /*if ((row == 1 && col == 0) ||
                    (row == 0 && col == 1) ||
                    (row == 1 && col == 1) ||
                    (row == n-2 && col == 0) ||
                    (row == n-2 && col == 1) ||
                    (row == n-1 && col == 1) ||
                    (row == 0 && col == n-2) ||
                    (row == 1 && col == n-2) ||
                    (row == 1 && col == n-1) ||
                    (row == n-2 && col == n-2) ||
                    (row == n-2 && col == n-1) ||
                    (row == n-1 && col == n-2)) score[row][col]=0;*/
                for(int i=2; i<=n-3; i++){
                    if((row == 0 && col == i) ||
                       (row == i && col == 0) ||
                       (row == n-1 && col == i) ||
                       (row == i && col == n-1)){
                           score[row][col]+=3;
                           break;
                    }
                }
            }
            
            else score[row][col]=0;
        }
    }
    
    
    int scoreRow=0;
    int scoreCol=0;
    int maxScore;
    //check which score is the highest
    maxScore=maxValInArray(score, n, &scoreRow, &scoreCol);
    //printf("row: %c, col: %c\n", scoreRow+'a', scoreCol+'a');
    //Play the best move
    applyMove(n, board, colour, scoreRow+'a', scoreCol+'a');
    printf("Computer places %c at %c%c.\n", colour, scoreRow+'a', scoreCol+'a');
}

int compMoveMaxScore(int n, char board[][26], char colour){
    int score[26][26];
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            if(checkIfMoveLegal(n, board, colour, row, col)){
                score[row][col]=countScore(n, board, colour, row+'a', col+'a');
            }
            else score[row][col]=0;
        }
    }
    
    
    int scoreRow=0;
    int scoreCol=0;
    //check which score is the highest
    int maxScore=maxValInArray(score, n, &scoreRow, &scoreCol);
    return maxScore;
}




void myMove(int n, char board[][26], char colour, char *rowLetter, char *colLetter){
    printf("Enter move for colour %c (RowCol): ", colour);
    scanf(" %c%c", rowLetter, colLetter);
    
    int score[26][26];
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            if(checkIfMoveLegal(n, board, colour, row, col)){
                score[row][col]=countScore(n, board, colour, row+'a', col+'a');
            }
            else score[row][col]=0;
        }
    }
    
    int scoreRow=0;
    int scoreCol=0;
    int maxScore;
    maxScore=maxValInArray(score, n, &scoreRow, &scoreCol);
}

int myMoveMaxScore(int n, char board[][26], char colour, char *rowLetter, char *colLetter){
    
    
    int score[26][26];
    int row, col;
    for(row=0; row<n; row++){
        for(col=0; col<n; col++){
            if(checkIfMoveLegal(n, board, colour, row, col)){
                score[row][col]=countScore(n, board, colour, row+'a', col+'a');
            }
            else score[row][col]=0;
        }
    }
    
    int scoreRow=0;
    int scoreCol=0;
    int maxScore;
    maxScore=maxValInArray(score, n, &scoreRow, &scoreCol);
    return maxScore;
}

int main(void){
    int n;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    char board[26][26];
    initializeBoard(n, board);
    
    //Request computer colour
    printf("Computer plays (B/W) : ");
    char compColour, myColour;
    scanf(" %c", &compColour);
    myColour=opponent(compColour);
    printBoard(board, n);
    
    int maxCompScore=1;
    int maxMyScore=1;
    bool myTurn;
    if(myColour=='B'){
        myTurn=true;
    }
    else{
        myTurn=false;
    }
    
    char rowLetter, colLetter;
    
    bool gameOver=false;
    while(!gameOver){
        if(maxCompScore<=0 && maxMyScore<=0){
            break;
        }
        
        if(myTurn){
            myTurn=false;
            maxMyScore=myMoveMaxScore(n, board, myColour, &rowLetter, &colLetter);
            if(maxMyScore>0){
                myMove(n, board, myColour, &rowLetter, &colLetter);
                
                //If my move is not legal then immediately lose
                if(!checkIfMoveLegal(n, board, myColour, rowLetter-'a', colLetter-'a')){
                    printf("Invalid move.\n%c player wins.", compColour);
                    return 0;
                }

                applyMove(n, board, myColour, rowLetter, colLetter);
                printBoard(board, n);
            }
            else printf("%c player has no valid move.\n", myColour);
        }
        else{
            myTurn=true;
            maxCompScore = compMoveMaxScore(n, board, compColour);
            if(maxCompScore>0){
            
                compMove(n, board, compColour);
                
                printBoard(board, n);
            }
            else printf("%c player has no valid move.\n", compColour);
            
            
        }
        gameOver = true;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (board[i][j] == 'U') {
                    gameOver = false;
                    break;
                }
            }
            if (!gameOver) break;
        }
    }
    int myTotalScore=0;
    int compTotalScore=0;
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            if(board[row][col]==myColour) 
                myTotalScore++;
            else if(board[row][col]==compColour)
                compTotalScore++;
        }
    }
    if(myTotalScore > compTotalScore)
        printf("%c player wins.", myColour);
    else if(myTotalScore < compTotalScore)
        printf("%c player wins.", compColour);
    else
        printf("Draw!");
    return 0;
}