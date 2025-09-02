#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

vector_t* vec_init(int capacity) {
    vector_t *vec = malloc(sizeof(vector_t));
    vec->elements = malloc(capacity * sizeof(void*));
    vec->size = 0;
    vec->capacity = capacity;

    return vec;
}

void vec_increase_capacity(vector_t *vec) {
    int capacity = vec->capacity;
    int new_capacity = capacity * RESIZE_FACTOR;
    capacity = new_capacity;

    vec->elements = realloc(vec->elements, new_capacity * sizeof(void*));
}

int vec_empty(vector_t *vec) {
    return vec->size == 0;
}

void* vec_at(vector_t *vec, int index) {
    if (index < 0 || index > vec->size - 1) {
        return NULL;
    }

    return vec->elements[index];
}

void* vec_unsafe_at(vector_t *vec, int index) {
    return vec->elements[index];
}

void* vec_front(vector_t *vec) {
    return vec_at(vec, 0);
}

void* vec_back(vector_t *vec) {
    return vec_at(vec, vec->size - 1);
}

int vec_size(vector_t *vec) {
    return vec->size;
}

int vec_capacity(vector_t *vec) {
    return vec->capacity;
}

void vec_reserve(vector_t *vec, int capacity) {
    if (vec->capacity >= capacity) {
        return;
    }

    vec->capacity = capacity;
    vec->elements = realloc(vec->elements, vec->capacity * sizeof(void*));
}

void vec_shrink_to_fit(vector_t *vec) {
    vec->capacity = vec->size;
    vec->elements = realloc(vec->elements, vec->capacity * sizeof(void*));
}

void vec_clear(vector_t *vec, destructor_func_t destr_func) {
    for (int i = 0; i < vec->size; i++) {
        destr_func(vec->elements[i]);
    }

    vec->size = 0;
}

void vec_push(vector_t *vec, void *element) {
    int old_capacity = vec->capacity;
    int size = vec->size;

    if (size + 1 > old_capacity) {
        vec_increase_capacity(vec);
    }

    vec->elements[size] = element;
    vec->size++;
}

void* vec_pop(vector_t *vec) {
    if (vec_empty(vec)) {
        return NULL;
    }

    void *last_element = vec_back(vec);
    vec->size--;

    return last_element;
}

void vec_append(vector_t *vec1, vector_t *vec2) {
    vec_reserve(vec1, vec1->size + vec2->size);

    for (int i = 0; i < vec2->size; i++) {
        void *element = vec2->elements[i];
        vec_push(vec1, element);
    }

    vec2->size = 0;
}

void vec_insert(vector_t *vec, int index, void *element) {
    int size = vec->size;

    if (index >= size) {
        return;
    }

    if (vec_empty(vec)) {
        vec_push(vec, element);
        return;
    }

    if (size + 1 > vec->capacity) {
        vec_increase_capacity(vec);
    }

    for (int i = size - 1; i >= index; i--) {
        vec->elements[i + 1] = vec->elements[i];
    }

    vec->elements[index] = element;
    vec->size++;
}
