#ifndef VECTOR_H
#define VECTOR_H

#define INITIAL_CAPACITY 10
#define RESIZE_FACTOR 2

typedef struct {
    void **elements;
    int size;
    int capacity;
} vector_t;

typedef void (*destructor_func_t)(void*);

vector_t* vec_init(int capacity);
int vec_empty(vector_t *vec);
void* vec_at(vector_t *vec, int index);
void* vec_front(vector_t *vec);
void* vec_back(vector_t *vec);
int vec_size(vector_t *vec);
int vec_capacity(vector_t *vec);
void vec_reserve(vector_t *vec, int capacity);
void vec_shrink_to_fit(vector_t *vec);
void vec_clear(vector_t *vec, destructor_func_t destr_func);
void vec_push(vector_t *vec, void *element);
void* vec_pop(vector_t *vec);
void vec_append(vector_t *vec1, vector_t *vec2);
void vec_insert(vector_t *vec, int index, void *element);

#endif // VECTOR_H
