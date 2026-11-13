// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 2.1 -- 07/2026

// Este arquivo PODE/DEVE ser alterado.

// Implementação do TAD Mapa de objetos

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

struct map_t {
    int size;           
    int last_allocated;
    void** items;
};

struct map_t *map_create(int size) {
    if (size < 0)
        return NULL;

    struct map_t* map = (struct map_t*) malloc (sizeof(struct map_t));
    if(!map) return NULL;

    map->size = size;
    map->last_allocated = -1;
    map->items = (void**) malloc(sizeof(void*) * size);
    if (!map->items){
        free(map);
        return NULL;
    } 

    for (int i = 0; i < map->size; i++)
        map->items[i] = NULL;

    return map;
}

int map_destroy(struct map_t *map){
    if (!map) return ERROR;

    free(map->items);
    free(map);

    return NOERROR;
}

int map_put(struct map_t *map, void *object) {

    if(!map || !object) return ERROR;
        
    for(int i = 1; i <= map->size; i++){
        int cont = (map->last_allocated + i) % map->size;
        if (map->items[cont] == NULL){
            map->items[cont] = object;
            map->last_allocated = cont;
            return map->last_allocated;
        }

    }
    
    return ERROR;
}

void *map_get(struct map_t *map, int id) {
    if (!map) return NULL;
    if (id < 0 || id >= map->size) return NULL;

    return map->items[id];
}

void *map_del(struct map_t *map, int id) {
    if (!map) return NULL;
    if (id < 0 || id >= map->size) return NULL;

    void* aux;
    aux = map->items[id];
    map->items[id] = NULL;

    return aux;
}

int map_items(struct map_t *map) {
    if (!map) return ERROR;

    int cont = 0;
    for (int i = 0; i < map->size; i++)
        if (map->items[i] != NULL)
            cont++;

    return cont;
}

// Informa o número de objetos que o mapa pode registrar.
// Retorno: número de objetos ou -1 (erro)
int map_size(struct map_t *map) {
    if (!map) return ERROR;

    return map->size;
}

// Imprime o conteúdo do mapa, no seguinte formato:
// Mapa nulo:     nome: undef
// Mapa vazio:    nome: [ - - - - - ] (0/5)
// Mapa qualquer: nome: [ - * - * * ] (3/5)
// As posições "*" no vetor impresso correspondem aos IDs em uso no mapa;
// (3/5) indica que o mapa tem 3 objetos e pode registrar até 5 objetos.
void map_print(char *name, struct map_t *map) {
    
    printf("%s: ", name);

    if(!map){
        printf("undef\n");
        return;
    }

    printf("[");
    
    int c = 0;
    for (int i = 0; i < map->size; i++) {
        if (map->items[i] == NULL) {
            printf("- ");
        } else {
            printf("* ");
            c++;
        }
    }
    printf("] (%d/%d)\n", c, map->size);
}