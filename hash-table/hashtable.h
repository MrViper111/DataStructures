#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MIN_LOAD_FACTOR 0.1
#define MAX_LOAD_FACTOR 0.75
#define RESIZE_FACTOR 2

typedef struct node {
    void *key;
    void *value;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
} bucket_t;

typedef int (*hash_func_t)(void*, int);
typedef int (*equal_func_t)(void*, void*);

typedef struct {
    bucket_t *buckets;
    hash_func_t hash_func;
    equal_func_t equal_func;
    int entries;
    int capacity;
} hash_table_t;

hash_table_t* ht_init(int capacity, hash_func_t hash, equal_func_t equal);
void ht_insert(hash_table_t *hash_table, void *key, void *value);
void* ht_remove(hash_table_t *hash_table, void *key);
void* ht_get(hash_table_t *hash_table, void *key);
float ht_load_factor(hash_table_t *hash_table);

#endif // HASHTABLE_H
