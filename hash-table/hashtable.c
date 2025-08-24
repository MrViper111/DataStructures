#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"

bucket_t* get_bucket(hash_table_t *hash_table, void *key) {
    int index = hash_table->hash_func(key, hash_table->capacity);
    assert(index >= 0 && index < hash_table->capacity);

    return &hash_table->buckets[index];
}

hash_table_t* ht_init(int capacity, hash_func_t hash, equal_func_t equal) {
    hash_table_t *hash_table = malloc(sizeof(hash_table_t));
    hash_table->hash_func = hash;
    hash_table->equal_func = equal;
    hash_table->capacity = capacity;
    hash_table->entries = 0;
    hash_table->buckets = malloc(capacity * sizeof(bucket_t));

    for (int i = 0; i < hash_table->capacity; i++) {
        bucket_t *bucket = &hash_table->buckets[i];
        bucket->head = NULL;
    }

    return hash_table;
}

void bucket_insert(bucket_t *bucket, void *key, void *value) {
    node_t *node = malloc(sizeof(node_t));
    assert(node != NULL);
    node->key=key;
    node->value=value;
    node->next = bucket->head;

    bucket->head = node;
}

void ht_insert(hash_table_t *hash_table, void *key, void *value) {
    bucket_t *bucket = get_bucket(hash_table, key);

    bucket_insert(bucket, key, value);
    hash_table->entries++;
    printf("New load factor: %f\n", ht_load_factor(hash_table));
    printf("Entries: %i, Capacity: %i\n", hash_table->entries, hash_table->capacity);

    if (ht_load_factor(hash_table) >= MAX_LOAD_FACTOR) {
        printf("RESIZING\n");
        int new_capacity = hash_table->capacity * RESIZE_FACTOR;
        int old_capacity = hash_table->capacity;
        bucket_t *new_buckets = malloc(new_capacity * sizeof(bucket_t));

        for (int i = 0; i < new_capacity; i++) {
            bucket_t *new_bucket = &new_buckets[i];
            new_bucket->head = NULL;
        }

        for (int i = 0; i < old_capacity; i++) {
            bucket_t *old_bucket = &hash_table->buckets[i];
            node_t *node = old_bucket->head;

            while (node != NULL) {
                int index = hash_table->hash_func(node->key, new_capacity);
                bucket_insert(&new_buckets[index], key, value);

                node_t *next = node->next;
                free(node);
                node=next;
            }
        }
        free(hash_table->buckets);

        hash_table->buckets = new_buckets;
        hash_table->capacity = new_capacity;
    }
}

void* ht_remove(hash_table_t *hash_table, void *key) {
    bucket_t *bucket = get_bucket(hash_table, key);

    node_t *node = bucket->head;
    node_t *previous_node = NULL;

    while (node != NULL) {
        if (hash_table->equal_func(key, node->key)) {
            if (previous_node == NULL) {
                bucket->head = node->next;
            } else {
                previous_node->next = node->next;
            }

            void *value = node->value;

            free(node);
            return value;
        }

        previous_node = node;
        node = node->next;
    }

    return NULL;
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

float ht_load_factor(hash_table_t *hash_table) {
    return (float) hash_table->entries / hash_table->capacity;
}
