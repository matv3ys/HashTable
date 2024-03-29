#include <stdio.h>
#include "./src/hash_table.h"

int main(int argc, char *argv[]) {
    ht_hash_table* ht = ht_new();
    ht_insert(ht, "aa", "aaa");
    ht_insert(ht, "bb", "bbb");
    ht_insert(ht, "c", "abc");
    ht_insert(ht, "d", "abc");
    ht_insert(ht, "e", "abc");
    ht_insert(ht, "f", "abc");
    ht_insert(ht, "g", "abc");
    ht_insert(ht, "h", "abc");
    ht_insert(ht, "i", "abc");
    ht_insert(ht, "j", "abc");
    ht_insert(ht, "k", "abc");
    ht_insert(ht, "l", "abc");
    ht_insert(ht, "m", "abc");
    ht_insert(ht, "n", "abc");
    ht_insert(ht, "o", "abc");
    ht_insert(ht, "p", "abc");
    ht_insert(ht, "q", "abc");
    ht_insert(ht, "r", "abc");
    ht_insert(ht, "s", "abc");
    ht_insert(ht, "t", "abc");
    ht_insert(ht, "u", "abc");
    ht_insert(ht, "v", "abc");
    ht_delete(ht, "aa");
    ht_delete(ht, "bb");
    ht_delete(ht, "c");
    ht_delete(ht, "d");
    ht_delete(ht, "e");
    ht_delete(ht, "f");
    ht_delete(ht, "g");
    ht_delete(ht, "h");
    ht_delete(ht, "i");
    ht_delete(ht, "j");
    ht_delete(ht, "k");
    ht_delete(ht, "l");
    ht_delete(ht, "m");
    ht_delete(ht, "n");
    ht_delete(ht, "o");
    ht_delete(ht, "p");
    ht_delete(ht, "q");
    ht_delete(ht, "r");
    ht_delete(ht, "s");
    ht_delete(ht, "t");
    ht_delete(ht, "u");
    ht_delete(ht, "v");
    ht_del_hash_table(ht);
    printf("Hellozz\n");
    return 0;
}