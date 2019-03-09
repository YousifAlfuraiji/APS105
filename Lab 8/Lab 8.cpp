//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Yousif Al-Furaiji
// Student Number: 1004311899
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

Node *newNode(char *addArtist, char *addSongName, char *addGenre, Node *nextNode);

Node *InsertInOrder(Node *head, char *songName, char *artist, char *genre);

Node *deleteFirstNode(Node *head);

Node *deleteMiddleNode(Node *head, char *searchKey);

Node *deleteLastNode(Node *head);

Node *search(Node *head, char *searchKey);

void printNode(char *songName, char *artist, char *genre);

Node *deleteAllNodes(Node *head) ;

// Declarations of support functions
// See below the main function for descriptions of what these functions do



const int MAX_LENGTH = 1024;

int main( void ) {
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
	
	Node *head; //points to first node in list or is NULL if empty
	head=NULL; //all lists start empty
 
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE
			
            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            char *promptName = "Song name" ;
            char *promptArtist =  "Artist" ;
            char *promptGenre = "Genre" ;
			
			char name[MAX_LENGTH], artist[MAX_LENGTH], genre[MAX_LENGTH];
			
            //Taking the node parameters
			inputStringFromUser( promptName, name, MAX_LENGTH ) ;
			inputStringFromUser( promptArtist, artist, MAX_LENGTH ) ;
			inputStringFromUser( promptGenre, genre, MAX_LENGTH ) ;
			
			//Insert in right place or print duplicate then assign the new head
			head = InsertInOrder(head, name, artist, genre);
		
        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;

            //   ADD STATEMENT(S) HERE
			char searchKey[MAX_LENGTH];
			
            //prompt for the song to be deleted
            inputStringFromUser(prompt, searchKey, MAX_LENGTH);
			
			Node *nodeFound = search(head, searchKey);
			
            //If song was not found
            if(nodeFound == NULL) 
				songNameNotFound(searchKey);
			//Figure out where to delete
            else{ 
				if(nodeFound == head) deleteFirstNode(head);
				else if(nodeFound->nextNode == NULL) deleteLastNode(head);
				else deleteMiddleNode(head, searchKey);
                songNameDeleted(searchKey);
			}

        }
        else if( response == 'S' ) {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;

            //   ADD STATEMENT(S) HERE
			char searchKey[MAX_LENGTH];
            
            //prompt a searchKey and assign the found node
			inputStringFromUser(prompt, searchKey, MAX_LENGTH);
			Node *nodeFound = search(head, searchKey);
			
            //If no node was found
			if(nodeFound == NULL) 
				songNameNotFound(searchKey);
			//Print the found node
            else{ 
				songNameFound(searchKey);
				printNode(nodeFound->songName, nodeFound->artist, nodeFound->genre);
			}
        }
        else if( response == 'P' ) {
            // Print the music library.

            //   ADD STATEMENT(S) HERE
			
            //If the library is empty
            if(head==NULL) printMusicLibraryEmpty();
			
            //Print the full library
            else{
				printMusicLibraryTitle();
				for(Node *reference = head; reference != NULL; reference = reference->nextNode){
				printf("\n%s\n", reference->songName);
				printf("%s\n", reference->artist);
				printf("%s\n", reference->genre);
				}
			}
        }
        else if( response == 'Q' ) {
             // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE
	
	head = deleteAllNodes(head);

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
	printMusicLibraryEmpty();

    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE

//Inserts a new node into the library
Node *newNode(char *addArtist, char *addSongName, char *addGenre, Node *nextNode){

    //Allocate memory
	Node *np=(Node*)malloc(sizeof(Node));
	np->artist = (char*) malloc(sizeof(char) * strlen(addArtist));
	np->songName = (char*) malloc(sizeof(char) * strlen(addSongName));
	np->genre = (char*) malloc(sizeof(char) * strlen(addGenre));
	
	//Initialize the node structure
	strcpy(np->artist, addArtist);
	strcpy(np->songName, addSongName);
	strcpy(np->genre, addGenre);
	np->nextNode=nextNode;
	return np;
}

//Inserts in the right place 
Node *InsertInOrder(Node *head, char *songName, char *artist, char *genre){
	// If the list is empty, add to front
    if(head == NULL || strcmp(songName, head->songName) <0)
		return newNode(artist, songName, genre, head);
		
		
		Node *reference = head;
		while(reference->nextNode != NULL && strcmp(songName, reference->nextNode->songName) > 0)
			reference = reference->nextNode;

        //If at the tail of linked list or anywhere else in the right alphabetical location
		if(reference->nextNode == NULL||strcmp(songName, reference->nextNode->songName) < 0)
			reference->nextNode = newNode(artist, songName, genre, reference->nextNode);
		
        //Otherwise, it is a duplicate
        else songNameDuplicate(songName);
		
		return head;
}

//Deleting the first node of the list
Node *deleteFirstNode(Node *head) {
	if (head != NULL){
		Node *newHead = head -> nextNode;
		free(head->songName);
        free(head->artist);
        free(head->genre);
        free(head);
		return newHead;
	}
	return head;
}

//Deleting some node of the list that's not the first or last
Node *deleteMiddleNode(Node *head, char *searchKey){
	
	//List is empty
	if(head == NULL) return NULL;

	//Incase deleting 1st node
	if(head->songName == searchKey){
		Node *secondNode = head->nextNode;
		free(head->songName);
        free(head->artist);
        free(head->genre);
        free(head);
		return secondNode;
	}
	
	bool found = false;
	Node *reference = head;
	
    //Look for searchKey
	while(!found && reference->nextNode != NULL){
		if(reference->nextNode->songName == searchKey) found = true;
		else reference = reference->nextNode;
	}
	
	//If a node is found to delete
	if(reference->nextNode != NULL){
		Node *nodeToRemove = reference->nextNode;
		reference->nextNode = reference->nextNode->nextNode;
		free(nodeToRemove->songName);
        free(nodeToRemove->artist);
        free(nodeToRemove->genre);
        free(nodeToRemove);
	}
	return head;
}

//Delete last node of the list
Node *deleteLastNode(Node *head){
	if (head == NULL) //if empty list
		return NULL;
	else if (head->nextNode == NULL){ //if 1 node in list
		free(head);
		return NULL;
	}
	else{
		Node *reference = head;
		while(reference->nextNode->nextNode != NULL)
			reference = reference->nextNode;
		free(reference->nextNode);
		reference->nextNode = NULL;
		return head;
	}
}

Node *search(Node *head, char *searchKey){
	Node *reference = head;
	while(reference != NULL){
		if(strcmp(reference->songName, searchKey) == 0) return reference;
		reference = reference->nextNode;
	}
	return NULL;
}

void printNode(char *songName, char *artist, char *genre){
	printf("\n%s\n", songName);
	printf("%s\n", artist);
	printf("%s\n", genre);
}

Node *deleteAllNodes(Node *head){
	while(head != NULL){
		Node *firstNode = head;
		head = head->nextNode;
		songNameDeleted(firstNode->songName);
        free(firstNode->songName);
        free(firstNode->artist);
        free(firstNode->genre);
		free(firstNode);
	}
	return NULL;
}