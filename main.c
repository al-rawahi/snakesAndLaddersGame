//Name: Al-Warith Al-Rawahi
//Student ID: R00196016

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//define struct square
typedef struct square {
    int value;
    struct square *next;
} square;

//define variables
int dice, numOfSnakes, numOfLadders, newPosition, aboveTheMax;

int main()
{
    //open a file to write in it
    FILE *fp;
    char str[128];
    int len;
    fp = fopen ("report.txt", "w");
    
    //create random number of squares between 32 and 64
    int min = 32;
    int max = 64;
    srand(time(0));
    int numOfSquares = (rand() % (max - min + 1)) + min;
    
    //create some squares
    struct square *firstSquare, *currentSquare, *temp;
    
    //print the number of squares
    printf("%d \n", numOfSquares);
    
    for (int i = 0; i < numOfSquares; i++) {
        //Allocate memory for each square
        currentSquare = (square *)malloc(sizeof(square));
        
        //set the values of squares
        currentSquare->value = i + 1;
        
        //All the squares are the same square in the begining -first square-
        if (i == 0) {
            firstSquare = temp = currentSquare;
        }
        
        else {
            temp->next = currentSquare;
            temp = currentSquare;
        }
    }
    
    //Set the next of the last square to NULL
    temp->next = NULL;
    
    //Go back to the first square
    temp = firstSquare;
    
    //Print squares values
    while (temp != NULL)
    {
        printf("%d \n", temp->value);
        temp = temp->next;
    }
    
    //Get number of snakes from user
    printf("How many snakes? \n");
    scanf("%d",&numOfSnakes);
    
    //Get number of ladders from user
    printf("How many ladders? \n");
    scanf("%d",&numOfLadders);

    //Print number of squares in the file
    len = sprintf(str, "number of squares is %d", numOfSquares);
    fwrite(str, len, 1, fp);

    
    //go back to first square
    currentSquare = firstSquare;
    
    while ((currentSquare->value) < numOfSquares) {
        //Get random number between 1 and 6
        dice = (rand() % 6) + 1;
        
        //Print dice value in the file
        len = sprintf(str, "\nYou get a %d \n", dice);
        fwrite(str, len, 1, fp);
        
        printf("\nYou get a %d \n", dice);
        
        //Add the dice value to the current square value
        currentSquare->value += dice;
      
        //If we reach the final square and go out of bounds
        if (currentSquare->value > numOfSquares) {
            //Calculate how much we are above the final square
            aboveTheMax = (currentSquare->value - numOfSquares);
            
            //Go back to the final square and end the game
            currentSquare->value = (numOfSquares - aboveTheMax);
        }  

        //Print current square value in the file
        len = sprintf(str, "\nYou are in square %d now.\n", currentSquare->value);
        fwrite(str, len, 1, fp);
        
        printf("\nYou are in square %d now.\n", currentSquare->value);
        
        //create snakes in random selected squares
        for (int i = 0; i < numOfSnakes; i++) {
            int snakeHead;
            do {
                snakeHead = (rand() % numOfSquares) + 1;
            }
            //Snake head cannot be in the last square in the board
            while(snakeHead == numOfSquares);
            
            //Set snake long to be a random number between 1 and 10
            int snakeLong = (rand() % 10) + 1;
            
            //If we are in a square that has a snake head, we go "snakeLong" squares back
            if ((currentSquare->value) == snakeHead) {
                newPosition = currentSquare->value - snakeLong;
            }
            else {
                newPosition = currentSquare->value;
            }
        }
        
        //create ladders in random selected squares
        for (int i = 0; i < numOfLadders; i++) {
            int ladderFoot;
            do {
                ladderFoot = (rand() % numOfSquares) + 1;
            }
            //Ladder foot cannot be in the first square in the board
            while(ladderFoot == 1);
            
            //Set ladder long to be a random number between 1 and 10
            int ladderLong = (rand() % 10) + 1;
            
            //If we are in a square that has a ladder foot, we go "ladderLong" squares forward
            if ((currentSquare->value) == ladderFoot) {
                newPosition = currentSquare->value + ladderLong;
            }
            else {
                newPosition = currentSquare->value;
            }
        }
      
        //Detecting ladders      
        if (currentSquare->value < newPosition) {
            //Print in the file that there is a ladder there
            len = sprintf(str, "\nThere is a ladder, now you are in square %d \n", newPosition);
            fwrite(str, len, 1, fp);
            
            printf("\nThere is a ladder, now you are in square %d \n", newPosition);
        }
        
        //Detecting snakes
        if (currentSquare->value > newPosition) {
            //Print in the file that there is a snake there
            len = sprintf(str, "\nThere is a snake, now you are in square %d \n", newPosition);
            fwrite(str, len, 1, fp);
            
            printf("\nThere is a snake, now you are in square %d \n", newPosition);
        }
      
        currentSquare->value = newPosition;
    }
    
    //Print in the file that the player has reached the final square
    len = sprintf(str, "Well done! you reached %d !!", numOfSquares);
    fwrite(str, len, 1, fp);
    
    printf("Well done! you reached %d !!", numOfSquares);
    
    //Close the file
    fclose(fp);

    getchar();
    return 0;
}
