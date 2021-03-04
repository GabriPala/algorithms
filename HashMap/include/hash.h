#pragma once

typedef struct Array arrayHashMap;
typedef struct List arrayList;
typedef int (*Hash)(void*, int);
typedef enum {FALSE, TRUE} boolean;

arrayHashMap* create_HashMap(int capacity);
void destroy_HashMap(arrayHashMap* array);
boolean hashMapArray_empty(arrayHashMap* array, int capacity);
int hashMapArray_num_association(arrayHashMap* array, int capacity);
void hashMapArray_delete_all_association(arrayHashMap* array, int capacity);
boolean hashMapArray_exists_key(arrayHashMap* array, void* k, int capacity, Hash hash_map);
void hashMapArray_insert(arrayHashMap* array, void* k, void* v, int capacity, Hash hash_map);
void* hashMapArray_search_key(arrayHashMap* array, void* k, int capacity, Hash hash_map);
void hashMapArray_delete_association(arrayHashMap* array, void* k, int capacity, Hash hash_map);
void** hashMapArray_all_keys(arrayHashMap* array, int capacity);
void* hashMap_get(arrayHashMap* array, int i);
int hashMap_size(arrayHashMap* array, int i);
void keysArray_free(void** keys);
void* list_key(arrayList* list);
void* list_value(arrayList* list);
void* list_next(arrayList* list);
