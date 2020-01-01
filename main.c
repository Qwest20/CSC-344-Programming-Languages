#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//NOTE: This program was brought to you by Minecraft music. It's chill bruh.

//STRUCTS
//Cell Struct
typedef struct Cell{
    //reference to the left cell
    struct Cell *left;
    //reference to the right cell
    struct Cell *right;
    //the char label it contains
    char label;
}Cell;

//Instruction Struct
typedef struct Instruction{
    //newState int value
    int newState;
    //direction character value
    char dir;
    //newLabel value
    char newLabel;
}Instruction;

//GLOBAL WARIABLES
//file variable
FILE *inputFile;
//the fileName starts as this so the user can enter "test.txt"
char fileName[100]="C:\\Users\\ljmcm\\CLionProjects\\TuringMachineV2\\";
//what the user actually enters
char fileNameInput[20];

//CELLS
//Head of the doubly linked list
Cell *head;
//Last of the doubly linked list
Cell *last;
//The current cell being worked on
Cell *current;


//FUNCTIONS
//display the cells
void printCells() {
    //start from the beginning
    Cell *printCurrent = head;

    //navigate until the end of the list
    while(printCurrent != NULL) {
        printf("%c",printCurrent->label);
        //shift the pointer to the right
        printCurrent = printCurrent->right;
    }
}

//is the list empty?
//implemented in insertCell function below
int isEmpty() {
    if(head == NULL) {
        //no head
        return 0;
    }
    else{
        //head exists
        return 1;
    }
}

//insert a new cell on the end
void insertCell(char c) {
    //create a cell
    Cell *input = malloc(sizeof(Cell));
    //apply this character to the cell's label
    input->label=c;
    //decide what to do based on if we're empty or not
    if(isEmpty()==0) {
        //make it the last cell
        last = input;
        //set the head initially
        head = last;
    } else {
        //make input a new last cell
        last->right = input;
        //mark old last cell as prev of new cell
        input->left = last;
    }
    //point last to new last cell
    last = input;
}

//insert string
void insertStringOfCells(char *input) {
    //given a string, make cells for each of the characters within it
    for(int i=0;i<(int) strlen(input);i++){
        //create the cell
        insertCell(input[i]);
    }
}

//MAIN FUNCTION
int main(){

    //variables for lines 0 through 3
    int numStates;
    int firstState;
    int lastState;
    char firstLine[50];

    //Input file prompt
    printf("Hi! Let's get started with your file name!\n");
    printf("NOTE: 'test.txt' is recommended: ");
    //reads the user input
    gets(fileNameInput);
    //fileName now has the user added extension
    strcat(fileName,fileNameInput);

    //Open the file
    inputFile = fopen(fileName,"r");

    //Read the file
    //if else block to check the file's existence
    if(inputFile==NULL) {
        //the file doesn't exist bucko
        printf("InputFile=NULL");
    }
    else{
        printf("Writing tape...");
        //Read in the first 4 lines
        fscanf(inputFile, "%s", firstLine);
        fscanf(inputFile, "%d", &numStates);
        fscanf(inputFile, "%d", &firstState);
        fscanf(inputFile, "%d", &lastState);

        //create the first cell 'A'
        insertCell('A');
        //create the rest of the cells using the inputStringOfCells function
        insertStringOfCells(firstLine);
        //print the cells
        printf("\nInitial Tape Contents: ");
        printCells();

        //make the instruction table
        Instruction instructionTable[numStates][128];

        //Read in each of the transition lines with these variables
        int currentState, newState;
        char currentLabel,newLabel,dir;

        //transition line variable
        char transitionLine[50];

        //while loop to read each line until we hit the end of the file
        while(fgetc(inputFile) != EOF) {
            fscanf(inputFile, "%s", transitionLine);
            sscanf(transitionLine, "(%d,%c)->(%c,%c,%d)", &currentState, &currentLabel, &newLabel, &dir, &newState);
            instructionTable[currentState][currentLabel].newLabel = newLabel;
            instructionTable[currentState][currentLabel].dir = dir;
            instructionTable[currentState][currentLabel].newState = newState;
        }

        //Set the current cell to the head to help with the transitions
        current = head;

        //start counting with this variable at the beginning of the states
        int thisState=firstState;

        //while loop to apply the transitions
        while (thisState!=lastState) {

            //read new label
            Instruction currentOrder = instructionTable[thisState][current->label];
            current->label = currentOrder.newLabel;

            //move the head
            //move to the right
            if (currentOrder.dir == 'R') {
                //make a 'B' cell
                if (current->right==NULL) {
                    //make a blank cell
                    insertCell('B');
                }
                //bump current to the right
                current = current->right;
            } else {
                //bump current to the left
                current = current->left;
            }

            //update the state based on the instructions
            thisState=currentOrder.newState;
        }

        //Print the output
        printf("\nFinal Tape Contents: ");
        printCells();
        //close the file
        fclose(inputFile);
    }
    return 0;
}
