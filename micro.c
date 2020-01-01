#include <stdio.h>
#include <malloc.h>

//item struct
typedef struct {
    double price;
    char *itemName;
} item;

int main() {

    //number of shelves and slots
    int shelves=0;
    int slots=0;

    //shelving unit dimensions input
    printf("Welcome to my shelving program!");
    printf("\n"); //jump to a new line
    printf("Please input the number of shelves you would like: ");
    scanf("%d", &shelves);
    printf("Please input the number of slots you would like on each shelf: ");
    scanf("%d", &slots);

    //shelving unit 2D array of items
    item shelvingUnit[shelves][slots];

    //item specs and location input
    int stop = 1;
    while (stop==1){

        //temp wariables (spelled this intentionally. An homage to my high school comp sci teacher)
        char iN[]="";
        double pr=0;
        int sh=0;
        int sl=0;

        //prompt
        printf("Let's enter your item! What is the item name? ");
        scanf("%s", iN);
        printf("What is the price? ");
        scanf("%lf", &pr);
        printf("Which shelf? Enter 0-%d",(shelves-1));
        printf(": ");
        scanf("%d", &sh);
        printf("Which slot? Enter 0-%d",(slots-1));
        printf(": ");
        scanf("%d", &sl);

        //insert item into the 2D array
        shelvingUnit[sh][sl].itemName=iN; //place the selected item in the right spot
        shelvingUnit[sh][sl].price=pr;

        //Enter another?
        printf("Your item has been inserted! Would you like to enter another item? Enter 1 for yes and 2 for no. ");
        scanf("%d", &stop);
    }

    //Pull up a specific item
    int end = 1;
    while (end==1) {

        //temp wariables
        int she=0;
        int slo=0;

        //prompt
        printf("\n");
        printf("Would you like to take a look at a specific location on the shelf? Enter 1 for yes and 2 for no. ");
        scanf("%d", &end);
        if(end != 1) {
            break;
        }
        printf("Which shelf? Enter 0-%d",(shelves-1));
        printf(": ");
        scanf("%d", &she);
        printf("Which slot? Enter 0-%d",(slots-1));
        printf(": ");
        scanf("%d", &slo);

        //display
        if(shelvingUnit[she][slo].price==0){ //not sure how to check for a null element of a struct matrix. I think this is hard coding...
            printf("Sorry, this slot is empty!\n");
        }
        else{
            printf("Here is your item:");
            printf("\n");
            printf("Item: %s",shelvingUnit[she][slo].itemName);
            printf("\n");
            printf("Price: $%d",&shelvingUnit[she][slo].price);
        }
    }
    printf("Thank you for testing my first C program! Have a good day!");
    return 0;
}