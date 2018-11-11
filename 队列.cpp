#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#define SIZE 20
typedef struct Queue {
    int first;
    int last;
    int* array;
    int size;
} Queue;

Queue* Init(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->first = queue->last = 0;
    queue->size = SIZE;
    queue->array = (int*)malloc(sizeof(int) * SIZE);
    return queue;
}

void Delete(Queue* queue) {
    free(queue->array);
    free(queue);
}

bool IsEmpty(Queue* queue) {
    return queue->first == queue->last;
}

int front(Queue* queue) {
    if (IsEmpty(queue)) {
        printf("None\n");
        exit(-1);
    }
    return queue->array[queue->first];
}

bool pop_front(Queue* queue) {
    if (IsEmpty(queue)) {
        return false;
    }
    queue->first++;
    return true;
}
#define SIZEUP 2
bool push_back(Queue* queue, int number) {
    if (IsEmpty(queue)) {
        queue->first = queue->last = 0;
    }

    if (queue->last == queue->size) {
        int* newArray = (int*)malloc(
            sizeof(int) * SIZEUP * queue->size);
        memcpy(newArray,
            queue->first + queue->array,
            sizeof(int) * (queue->last - queue->first));
        free(queue->array);
        queue->array = newArray;
        queue->size *= SIZEUP;
        queue->last -= queue->first;
        queue->first = 0;

    }

    queue->array[queue->last++] = number;
    return true;
}

int main(void) {
    Queue* queue = Init();

    int num = 2176213;
    int N = num;
    for (int i = 2; i <= N / 2; ++i) {
        while (num % i == 0) {
            push_back(queue, i);
            printf("i: %d\n", i);
            num /= i;
        }
        if (num == 1) {
            break;
        }
    }

    int num2 = 0;

    while(!IsEmpty(queue)) {
        if (num2 == front(queue)) {

        } else {
            printf("%d ", front(queue));
            num2 = front(queue);
        }
        pop_front(queue);
    }

    printf("\n done \n");


    free(queue);
}

