#include <_static_assert.h>
#include <stdio.h>
#include "hashtable.h"

int hash(void *key) {
    return *(int*)key % HT_CAPACITY;
}

int equals(void *key1, void *key2) {
    return *(int*)key1 == *(int*)key2;
}

int main() {
    hash_table_t *hash_table = ht_init(hash, equals);

    int key = 0;
    int value = 99;
    ht_insert(hash_table, &key, &value);

    void *result = ht_get(hash_table, &key);
    printf("Value of key: %i", *(int*)result);

    return 0;
}
