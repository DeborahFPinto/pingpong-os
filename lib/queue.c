// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 2.1 -- 07/2026

// Este arquivo PODE/DEVE ser alterado.

// Implementação do TAD fila genérica
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

struct node_t;

struct node_t{
    struct node_t* next;
    void* item;
} node_t;

struct queue_t{
    struct node_t* head;
    struct node_t* tail;
    struct node_t* iterator;
};

struct queue_t* queue_create() {
    
    struct queue_t* queue = (struct queue_t*) malloc(sizeof(struct queue_t));

    if (queue != NULL) {    
        queue->head = NULL;
        queue->tail = NULL;
        queue->iterator = NULL;
    }

    return queue;
}

int queue_destroy(struct queue_t *queue) {
    
    if (!queue)
        return ERROR;
        
    if (queue->head != NULL) {    
            
        while (queue->head != queue->tail){
            struct node_t* temp;
            temp = queue->head;
            queue->head = queue->head->next;
            free(temp);
        }

        free(queue->head);
    }
    
    free(queue);
    return NOERROR;
}

int queue_add(struct queue_t *queue, void *item) {
    
    if (!queue || !item)
        return ERROR;
    
    struct node_t *node = (struct node_t*) malloc (sizeof(struct node_t));
    node->item = item;
    node->next = NULL;

    if (!queue->tail){
        queue->head = node;
        queue->iterator = node;
        queue->tail = node;
    }
    else {
        queue->tail->next = node;
        queue->tail = node;
    }

    return NOERROR;
}
int queue_del(struct queue_t *queue, void *item) {
    if (!queue || !item) return ERROR;
    if (!queue->head) return ERROR;
    
    struct node_t* temp = queue->head;

    if (temp->item == item) {
        queue->head = queue->head->next;
        if (queue->head == NULL) queue->tail = NULL;

        if (queue->iterator != NULL) {
            if (queue->iterator == temp) {
                queue->iterator = queue->iterator->next;
            }
        }
        free(temp);
        return NOERROR;
    }

    while (temp->next != NULL) {
        if (temp->next->item == item) {
            if (temp->next == queue->tail) {
                queue->tail = temp;
            }
            
            if (queue->iterator != NULL) {
                if (queue->iterator == temp->next)
                    queue->iterator = queue->iterator->next;
            }

            struct node_t* node_to_free = temp->next;
            temp->next = temp->next->next;
            free(node_to_free);
            return NOERROR;
        }

        temp = temp->next;
    }

    return ERROR;
}

bool queue_has(struct queue_t *queue, void *item) {
    
    if (!queue || !item) return false;
    struct node_t* aux = queue->head;

    while(aux != NULL){
        if (aux->item == item)
            return true;
        aux = aux->next;
    }

    return false;
}

int queue_size(struct queue_t *queue) {

    if (!queue) return ERROR;
    int size = 0;
    struct node_t* aux = queue->head;

    while (aux != NULL){
        aux = aux->next;
        size++;
    }

    return size;
}

void *queue_head(struct queue_t *queue) {
    if (!queue) return NULL;
    if (queue->head == NULL) return NULL;

    queue->iterator = queue->head;
    return queue->iterator->item;
}

void *queue_next(struct queue_t *queue) {
    if (!queue) return NULL;
    if (queue->head == NULL) return NULL;
    if(queue->iterator == queue->tail) {
        queue->iterator = NULL;
        return NULL;
    }

    queue->iterator = queue->iterator->next;
    return queue->iterator->item;
}

void *queue_item(struct queue_t *queue) {
    if (!queue) return NULL;
    if (queue->head == NULL) return NULL;
    if (queue->iterator == NULL) return NULL;
    
    return queue->iterator->item;
}

void queue_print(char *name, struct queue_t *queue, void (*func)(void *)) {
    if (!queue) {
        printf("%s: undef\n", name ? name : "");
        return;
    }

    printf("%s: [", name ? name : "");

    struct node_t* aux = queue->head;
    int count = 0;

    while (aux != NULL) {
        printf(" ");
        if (func != NULL && aux->item != NULL) {
            func(aux->item);
        } else {
            printf("undef");
        }
        aux = aux->next;
        count++;
    }

    if (count > 0) {
        printf(" ");
    }
    printf("] (%d items)\n", count);
}