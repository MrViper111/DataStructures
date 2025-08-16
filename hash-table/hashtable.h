#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HT_CAPACITY 100

typedef struct node {
    void *key;
    void *value;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
} bucket_t;

typedef int (*hash_func_t)(void*);
typedef int (*equal_func_t)(void*, void*);

typedef struct {
    bucket_t buckets[HT_CAPACITY];
    hash_func_t hash_func;
    equal_func_t equal_func;
} hash_table_t;

hash_table_t* ht_init(hash_func_t hash, equal_func_t equal);
void ht_insert(hash_table_t *hash_table, void *key, void *value);
void* ht_get(hash_table_t *hash_table, void *key);

#endif // HASHTABLE_H
