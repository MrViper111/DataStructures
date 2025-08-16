#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"

bucket_t* get_bucket(hash_table_t *hash_table, void *key) {
    int index = hash_table->hash_func(key);
    assert(index >= 0 && index < HT_CAPACITY);

    return &hash_table->buckets[index];
}

hash_table_t* ht_init(hash_func_t hash, equal_func_t equal) {
    hash_table_t *hash_table = malloc(sizeof(hash_table_t));
    hash_table->hash_func = hash;
    hash_table->equal_func = equal;

    for (int i = 0; i < HT_CAPACITY; i++) {
        bucket_t *bucket = &hash_table->buckets[i];
        bucket->head = NULL;
    }

    return hash_table;
}

void ht_insert(hash_table_t *hash_table, void *key, void *value) {
    bucket_t *bucket = get_bucket(hash_table, key);

    node_t *node = malloc(sizeof(node_t));
    assert(node != NULL);
    node->key=key;
    node->value=value;
    node->next = bucket->head;

    bucket->head = node;
}

void* ht_get(hash_table_t *hash_table, void *key) {
    bucket_t *bucket = get_bucket(hash_table, key);

    for (node_t *node = bucket->head; node != NULL; node=node->next) {
        if (hash_table->equal_func(key, node->key)) {
            return node->value;
        }
    }

    return NULL;
}
