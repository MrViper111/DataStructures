#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main() {
    vector_t *vec = vec_init(INITIAL_CAPACITY);

    int is_empty = vec_empty(vec);
    printf(is_empty ? "CORRECT! empty\n" : "WRONG! not empty\n");

    printf("Adding elements...\n");
    for (int i = 0; i < 10; i++) {
        int *element = malloc(sizeof(int));
        *element = i;
        vec_push(vec, element);
    }

    printf("Last element: %d\n", *(int*)vec_back(vec));

    printf("Removing last element: %d\n", *(int*)vec_pop(vec));
    printf("Last element: %d\n", *(int*)vec_back(vec));

    vector_t *vec1 = vec_init(INITIAL_CAPACITY);
    for (int i = 0; i < 10; i++) {
        int *element = malloc(sizeof(int));
        *element = i + 10;
        vec_push(vec1, element);
    }

    printf("Appending elements of vec to vec1\n");
    vec_append(vec, vec1);
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", *(int*)vec_at(vec, i));
    }
    printf("\n");

    printf("im inserting\n");
    int index = 2;
    int *value = malloc(sizeof(int));
    *value = 0;
    printf("Inserting into index %i...", index);
    vec_insert(vec, index, value);
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", *(int*)vec_at(vec, i));
    }
    printf("\n");

    return 0;
}
