#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define QUEUE_SIZE 5

typedef struct Queue {
    char results[QUEUE_SIZE][50];
    int front;
    int rear;
} Queue;

void initQueue(Queue* queue);
int isQueueFull(Queue* queue);
int isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, const char* result);
void displayResults(Queue* queue);
int getComputerChoice();
const char* getChoiceName(int choice);
const char* determineWinner(int player, int computer);

int main() {
    Queue results;
    initQueue(&results);
    char playerChoice[10];
    int computerChoice;

    srand(time(NULL)); 

    printf("Welcome to Rock, Paper, Scissors!\n");

    while (1) {
        printf("\nEnter rock, paper, or scissors (or type 'exit' to quit): ");
        scanf("%s", playerChoice);

        if (strcmp(playerChoice, "exit") == 0) {
            break; 
        }

        computerChoice = getComputerChoice();
        const char* winner = determineWinner(strcmp(playerChoice, "rock") == 0 ? 0 : strcmp(playerChoice, "paper") == 0 ? 1 : 2, computerChoice);

        char result[50];
        sprintf(result, "You chose %s, Computer chose %s. %s", playerChoice, getChoiceName(computerChoice), winner);
        enqueue(&results, result);
        printf("%s\n", result);
    }

    printf("\nGame Results:\n");
    displayResults(&results);
    
    return 0;
}


void initQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = 0;
}

int isQueueFull(Queue* queue) {
    return (queue->rear + 1) % QUEUE_SIZE == queue->front;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

void enqueue(Queue* queue, const char* result) {
    if (!isQueueFull(queue)) {
        strcpy(queue->results[queue->rear], result);
        queue->rear = (queue->rear + 1) % QUEUE_SIZE; 
    }
}

void displayResults(Queue* queue) {
    int i = queue->front;
    while (i != queue->rear) {
        printf("%s\n", queue->results[i]);
        i = (i + 1) % QUEUE_SIZE; 
    }
}

int getComputerChoice() {
    return rand() % 3; 
}

const char* getChoiceName(int choice) {
    if (choice == 0) return "rock";
    if (choice == 1) return "paper";
    return "scissors";
}

const char* determineWinner(int player, int computer) {
    if (player == computer) return "It's a draw!";
    if ((player == 0 && computer == 2) || (player == 1 && computer == 0) || (player == 2 && computer == 1)) {
        return "You win!";
    }
    return "Computer wins!";
}
