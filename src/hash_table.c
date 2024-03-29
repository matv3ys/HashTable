#include <stdlib.h>
#include <string.h>

#include "../Include/hash_table.h"

#define HT_PRIME_1 5381
#define HT_PRIME_2 13   /* should be smaller than table size */
#define HT_INIT_SIZE 19 /* table size (not only initial value)
                         * and HT_PRIME_2 should be coprime integers*/

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* item = (ht_item *) malloc(sizeof(ht_item));
    item->key = strdup(k);
    item->value = strdup(v);
    return item;
}

static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = (base_size % HT_PRIME_2 != 0) ? base_size : base_size + 1;

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

ht_hash_table* ht_new() {
    return ht_new_sized(HT_INIT_SIZE);
}

static void ht_del_item(ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM)
            ht_del_item(item);
    }
    free(ht->items);
    free(ht);
}

static void ht_resize(ht_hash_table* ht, const int size) {
    if (size < HT_INIT_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    new_ht->size = ht->size;
    ht->size = size;
    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->size / 2;
    ht_resize(ht, new_size);
}

size_t ht_hash(const char *str) {
    size_t key = HT_PRIME_1;
    char c;

    while ((c = *str++))
        key = ((key << 5) + key) + c; /* hash * 33 + c */

    return key;
}

static size_t ht_get_hash(const char* s, int num_buckets, int attempt) {
    size_t key = ht_hash(s);
    size_t hash_a = key % num_buckets;
    size_t hash_b = HT_PRIME_2 - (key % HT_PRIME_2);
    return (hash_a + attempt * hash_b) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }

    char* search_result = ht_search(ht, key);
    if (search_result != NULL) {
        ht_delete(ht, key);
        free(search_result);
    }

    ht_item* item = ht_new_item(key, value);
    size_t index = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int attempt = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        index = ht_get_hash(key, ht->size, attempt);
        cur_item = ht->items[index];
        ++attempt;
    }
    ht->items[index] = item;
    ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key) {
    size_t index = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int attempt = 1;
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(key, cur_item->key) == 0) {
                return strdup(cur_item->value);
            }
        }
        index = ht_get_hash(key, ht->size, attempt);
        cur_item = ht->items[index];
        ++attempt;
    }
    return NULL;
}

/* item we wish to delete may be part of collision chain, so we use HT_DELETED_ITEM */
void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }

    size_t index = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int attempt = 1;
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(key, cur_item->key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = &HT_DELETED_ITEM;
                ht->count--;
                break;
            }
        }
        index = ht_get_hash(key, ht->size, attempt);
        cur_item = ht->items[index];
        ++attempt;
    }
}

