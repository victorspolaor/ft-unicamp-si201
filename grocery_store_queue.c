#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define tempoSimulacao  100
#define probChegada     0.3
#define tempoAtendMin   5
#define tempoAtendMax   20

typedef struct Client{
   int clientNumber;
   int arrivalInstant;
   int attendanceTime;
} Client;

typedef struct Node{
   Client *data;
   struct Node *nextPtr;
} Node;

typedef struct Queue{
   Node *head;
   Node *tail;
} Queue;

typedef struct simulationData{
   Queue *queue;
   Client *activeClient;

   int time;
   int numberOfClients;
   int attendedNumber;
   int waitTimeSum;
   int sizeSum;

} simulationData;

void Enqueue(Queue *queue, Client *data);
void FreeQueue(Queue *queue);
int QueueIsEmpty(Queue *queue);
int QueueLength(Queue *queue);
Client *Dequeue(Queue *queue);
Queue *NewQueue();


void exeSimulation(simulationData *dataBase);
void processQueue(simulationData *dataBase);
bool RandomChance(double prob, int min, int max);

int main() {

    setlocale(LC_ALL, "Portuguese");

    simulationData data;

    srand((int)time(NULL));

    exeSimulation(&data);

    printf("\n");
    printf("Resultados da simulacao:\n\n");
    printf("    Numero de consumidores atendidos: %d\n", data.attendedNumber);
    printf("    Tempo medio de espera: %.2f\n", (double) data.waitTimeSum / data.attendedNumber);
    printf("    Tamanho medio da fila: %.2f\n", (double) data.sizeSum / tempoSimulacao);

    return 0;
}

//Queue functions
void Enqueue(Queue *queue, Client *data){
    Node *newPtr;
    newPtr = (Node*) malloc(sizeof(Node));

    if (newPtr == NULL){
        exit(EXIT_FAILURE);
    }

    newPtr->data = data;
    newPtr->nextPtr = NULL;

    if (queue->head == NULL){
        queue->head = newPtr;
    }
    else
        queue->tail->nextPtr= newPtr;
        queue->tail = newPtr;
}

void FreeQueue(Queue *queue) {
   Node *newPtr, *nextPtr;
   newPtr = queue->head;
   while (newPtr != NULL) {
      nextPtr = newPtr->nextPtr;

      free(newPtr->data);
      free(newPtr);

      newPtr = nextPtr;
   }
   free(queue);
}

int QueueIsEmpty(Queue *queue) {
   return queue->head == NULL;
}

int QueueLength(Queue *queue) {
    int sizeQueue = 0;
    Node *newPtr;

    for (newPtr = queue->head; newPtr != NULL; newPtr = newPtr->nextPtr){
        sizeQueue++;
    }
    return sizeQueue;
}

Client *Dequeue(Queue *queue){
   Client *result;
   Node *newPtr;
   newPtr = queue->head;
   if (newPtr == NULL) {
      printf( "Erro: a fila est� vazia");
      exit(1);
   }
   result = newPtr->data;
   queue->head = newPtr->nextPtr;

   free(newPtr);

   return result;
}

Queue *NewQueue() {
    Queue *queue;
    queue = malloc( sizeof (Queue));
    if (queue == NULL)
        exit(1);

    queue->head = NULL;

    return queue;
}

//Main functions
void exeSimulation(simulationData *dataBase){

    double probResult;

    dataBase->queue = NewQueue();
    dataBase->activeClient = NULL;
    dataBase->numberOfClients = 0; // Roberts esqueceu?
    dataBase->attendedNumber = 0;
    dataBase->waitTimeSum = 0;
    dataBase->sizeSum = 0;

    for (dataBase->time = 0; dataBase->time < tempoSimulacao; dataBase->time++) {
        if (RandomChance(probChegada, 0, 1)){
            Client *client;
            dataBase->numberOfClients++;

            client = (Client*) malloc(sizeof(Client));

            client->clientNumber = dataBase->numberOfClients;
            client->arrivalInstant = dataBase->time;

            probResult = (double) rand() / ((double) RAND_MAX + 1);

            client->attendanceTime = tempoAtendMin + (probResult * (tempoAtendMax - tempoAtendMin + 1));

            Enqueue(dataBase->queue, client);

            printf("%4d: Cliente %d entra na fila\n", dataBase->time, dataBase->numberOfClients);
        }

        processQueue(dataBase);
    }

    FreeQueue(dataBase->queue);
}


void processQueue(simulationData *dataBase){
    if (dataBase->activeClient == NULL) {
        if (!QueueIsEmpty( dataBase->queue)){
            Client *client;
            client = Dequeue(dataBase->queue);
            dataBase->activeClient = client;
            dataBase->attendedNumber++;
            dataBase->waitTimeSum += (dataBase->time - client->arrivalInstant);

            printf("%4d: Cliente %d chega ao caixa\n",

            dataBase->time, client->clientNumber);
        }
    }
    else{
        if (dataBase->activeClient->attendanceTime == 0){
            printf( "%4d: Cliente %d deixa o caixa\n", dataBase->time, dataBase->activeClient->clientNumber);

            free(dataBase->activeClient);

            dataBase->activeClient = NULL;
        }
        else{
            dataBase->activeClient->attendanceTime--;
        }
    }
   dataBase->sizeSum += QueueLength(dataBase->queue);
}

//Randomize arrive prob
bool RandomChance(double prob, int min, int max){
    double probResult;
    double randomReal;

    probResult = (double) rand() / ((double) RAND_MAX + 1);
    randomReal = min + probResult * (max - min);

    return randomReal < prob;
}