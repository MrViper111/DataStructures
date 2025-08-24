#include <_static_assert.h>
#include <stdio.h>
#include "hashtable.h"

#define HT_CAPACITY 16

int hash(void *key, int capacity) {
    return *(int*)key % capacity;
}

int equals(void *key1, void *key2) {
    return *(int*)key1 == *(int*)key2;
}

int main() {
    hash_table_t *hash_table = ht_init(HT_CAPACITY, hash, equals);
    int keys[100];
    int values[100];

    for (int i = 0; i < 50; i++) {
        keys[i] = i;
        values[i] = i * 2;

        printf("INSERT %i, %i\n", keys[i], values[i]);
        ht_insert(hash_table, &keys[i], &values[i]);
    }

    return 0;
}
