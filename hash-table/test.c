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

}
