#include <stdio.h>
#include <stdbool.h>
#include <math.h>



void initializeBoard(int n, char board[][26]){ //Sets up board values array
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

void printBoard(char board[][26], int n){ //Spaces and Prints the specific values in specific places
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

char opponent(char color){
    if(color=='B') return 'W';
    if(color=='W') return 'B';
    else return '-';
}

bool positionInBounds(int n, char row, char col){
    if((row-'a'>=0)&&(row-'a'<n)&&
       (col-'a'>=0)&&(col-'a'<n))
           return true;
    return false;
}

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
void printLegalMoves(int n, char board[][26], char colour){
    for(int row=0; row<n; row++){
        for(int col=0; col<n; col++){
            if(board[row][col]=='U'){
                for(int deltaRow=-1; deltaRow<=1; deltaRow++){
                    bool broken=false;
                    for(int deltaCol=-1; deltaCol<=1; deltaCol++){
                        
                        if(deltaRow==0&&deltaCol==0) continue;
                        char rowLetter='a'+row;
                        char colLetter='a'+col;
                        if(checkLegalInDirection(board, n, rowLetter, colLetter, colour, deltaRow, deltaCol)){
                            printf("%c%c \n", rowLetter, colLetter);
                            broken=true;
                            break; 
                        }
                    }
                    if(broken) break;
                }
            }
        }
    }
}


void flipPieces(int n, char board[][26], char inputColour, char inputRowLetter, char inputColLetter){
    bool check= false;
    int count;
    for(int deltaRow=-1; deltaRow<=1; deltaRow++){
        for(int deltaCol=-1; deltaCol<=1; deltaCol++){
            if(deltaRow==0 && deltaCol==0) continue;
                
            int row=inputRowLetter-'a'+deltaRow;
            int col=inputColLetter-'a'+deltaCol;
            if(checkLegalInDirection(board, n, inputRowLetter, inputColLetter, inputColour, deltaRow, deltaCol)){
                check=true;
                for(count=0; board[row+deltaRow*count][col+deltaCol*count]==opponent(inputColour); count++)
                    board[row+deltaRow*count][col+deltaCol*count]=inputColour;
                board[inputRowLetter-'a'][inputColLetter-'a'+deltaCol]=inputColour;
            }
        }
    }
    if(check==true) printf("Valid move. \n");
    else if(check==false) printf("Invalid move. \n");
}    


int main(void){
    int n;
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    char board[26][26];
    
    initializeBoard(n, board);
    printBoard(board, n);
    
    //Change the configuration of the baord
    printf("Enter board configuration:\n");
    char playerConfigColour, colConfigLetter, rowConfigLetter;
    scanf(" %c%c%c",&playerConfigColour, &rowConfigLetter, &colConfigLetter);
    while(playerConfigColour!='!'){
        board[rowConfigLetter-'a'][colConfigLetter-'a']=playerConfigColour;
        scanf(" %c%c%c",&playerConfigColour, &rowConfigLetter, &colConfigLetter);
    }
    printBoard(board, n);
    
    //See Available moves
    printf("Available moves for W: \n");
    char colour;
    colour='W';
    printLegalMoves(n, board, colour);
    
    
    printf("Available moves for B: \n");
    colour='B';
    printLegalMoves(n, board, colour);
	
    //Ask user for move input
    printf("Enter a move: \n");
    char inputColour, inputRowLetter, inputColLetter;
    scanf(" %c%c%c", &inputColour, &inputRowLetter, &inputColLetter);
    
    //Making the move
    flipPieces(n, board, inputColour, inputRowLetter, inputColLetter);
    printBoard(board,n);
    
    return 0;
}