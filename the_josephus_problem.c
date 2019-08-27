#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Setting and creating node
typedef struct soldierList{
    char name[15];
    struct soldierList *nextPtr;

} Circular;

Circular *createNode();

//Declaring insert and deletion node functions
void insertNode(Circular **node, char dado[15]);
void delNode(Circular *sPtr, int index, char soldierName[15]);

int main(){

    setlocale(LC_ALL, "");

    static Circular *startPtr = NULL;
    int n = 0, i = 0, nameCont = 0, chosen = 0;
    char name[15], nameVector[20][15];

    // Getting the step pattern
    printf("Insert the 'step' value: ");
    scanf("%d", &n);

    printf("Insert the soldiers names: \n");

    if (n == 1){
        n = 1;
    }
    else{
        n--;
    }

    strcpy(name, "");

    //Getting soldier names and creating nodes in a circular
    //linked list
    while(strcmp("STOP", name)){
        scanf("%s", name);

        strcpy(&nameVector[i][15], name);

        if(!strcmp("STOP", name)){
            break;
        }

        insertNode(&startPtr, name);
        strcpy(name, "");

        nameCont++;
        i++;
    }

    //Generating a random number in order choose a random soldier
    //to start counting
    srand(time(NULL));
    chosen = rand() % nameCont;

    printf("\nLucky soldier: %s\n", &nameVector[chosen][15]);

    //Removing soldiers in a circular linked list until there's
    //one left
    delNode(startPtr, n, &nameVector[chosen][15]);

    free(startPtr);

    return 0;
}

Circular *createNode(){
    Circular *newPtr =(Circular*) malloc(sizeof(Circular));

    if(!newPtr){
        printf("Pointer not allocated");
        exit(0);
    }
    return newPtr;
}

void insertNode(Circular **node, char dado[15]){

    Circular *newPtr, *auxPtr;

    newPtr = createNode();

    strcpy(newPtr->name, dado);

    if(*node == NULL){
        newPtr->nextPtr = newPtr;
        *node = newPtr;
     }
     else{
         auxPtr = *node;
         while(auxPtr->nextPtr != *node){
               auxPtr = auxPtr->nextPtr;
         }
         auxPtr->nextPtr = newPtr;
         newPtr->nextPtr = *node;
     }
}

void delNode(Circular *sPtr, int index, char soldierName[15]){

    int i = 0;

    Circular *auxPtr;

    if(sPtr == NULL){
        printf("Empty list!\n");
        system("pause");
    }

    //Comparing the random soldier name to star removing
    //soldiers from the circular list
    while ((strcmp(soldierName, sPtr->name))!= 0){
        sPtr = sPtr->nextPtr;
    }

    while(sPtr->nextPtr != sPtr){

        for(i = 1; i < index + 1; i++){
            if(i == index){
                auxPtr = sPtr;
            }
            sPtr = sPtr->nextPtr;
        }

        printf("\nRemoved soldier: %s", sPtr->name);
        auxPtr->nextPtr = sPtr->nextPtr;

        free(sPtr);

        sPtr = auxPtr->nextPtr;
    }
    printf("\n\nSoldier that escaped: %s\n", sPtr->name);

    exit(0);

    free(sPtr);
    free(auxPtr);
}
