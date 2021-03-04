// Test with int type

#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "hash.h"

#define CAPACITY 100

static int* int_value(int n){
  int* num = (int*) malloc (sizeof(int));
  *num = n;
  return num;
}

static int hash_map_int(void* key, int capacity){
      return *((int*)key) % capacity;
}

// ---- Create Hash Map with 5 association ----
static arrayHashMap* create_HashMap_KV() {
    arrayHashMap* array = create_HashMap(CAPACITY);
    hashMapArray_insert(array, int_value(25), int_value(340), CAPACITY, (Hash)hash_map_int);
    hashMapArray_insert(array, int_value(20), int_value(10), CAPACITY, (Hash)hash_map_int);
    hashMapArray_insert(array, int_value(72), int_value(34), CAPACITY, (Hash)hash_map_int);
    hashMapArray_insert(array, int_value(125), int_value(3), CAPACITY, (Hash)hash_map_int);
    hashMapArray_insert(array, int_value(40), int_value(40), CAPACITY, (Hash)hash_map_int);

    return array;
}

// ---- Start test empty Hash Map  ----
static void hashMapArray_is_empty() {
    arrayHashMap* array = create_HashMap(CAPACITY);
    TEST_ASSERT_EQUAL(TRUE, hashMapArray_empty(array, CAPACITY));

    destroy_HashMap(array);
}
// ---- End test empty Hash Map ----

// ---- Start count association ----
static void hashMapArray_association() {
  arrayHashMap* array = create_HashMap_KV();
  TEST_ASSERT_EQUAL(5, hashMapArray_num_association(array, CAPACITY));

  hashMapArray_delete_all_association(array, CAPACITY);
  destroy_HashMap(array);
}
// ---- End count association ----

// ---- Start delete all association ----
static void hashMapArray_delete_assoc() {
  arrayHashMap* array = create_HashMap_KV();
  hashMapArray_delete_all_association(array, CAPACITY);
  TEST_ASSERT_EQUAL(TRUE, hashMapArray_empty(array, CAPACITY));

  destroy_HashMap(array);
}
// ---- End delete all association ----

// ---- Start delete one association ----
static void hashMapArray_delete_one_assoc(){
  arrayHashMap* array = create_HashMap_KV();
  hashMapArray_delete_association(array, int_value(25), CAPACITY, (Hash)hash_map_int);
  TEST_ASSERT_EQUAL(NULL, hashMapArray_search_key(array, int_value(25), CAPACITY, (Hash)hash_map_int));

  hashMapArray_delete_all_association(array, CAPACITY);
  destroy_HashMap(array);
}
// ---- End delete one association ----

// ---- Start check if exist a key ----
static void hashMapArray_exist(){
  arrayHashMap* array = create_HashMap_KV();
  TEST_ASSERT_EQUAL(TRUE, hashMapArray_exists_key(array, int_value(25), CAPACITY, (Hash)hash_map_int));
  TEST_ASSERT_EQUAL(FALSE, hashMapArray_exists_key(array, int_value(0), CAPACITY, (Hash)hash_map_int));

  hashMapArray_delete_all_association(array, CAPACITY);
  destroy_HashMap(array);
}
// ---- End check if exist a key ----

// ---- Start find a key ----
static void hashMapArray_key(){
  arrayHashMap* array = create_HashMap_KV();
  TEST_ASSERT_EQUAL(340, *((int*)hashMapArray_search_key(array, int_value(25), CAPACITY, (Hash)hash_map_int)));
  TEST_ASSERT_EQUAL(NULL, hashMapArray_search_key(array, int_value(30), CAPACITY, (Hash)hash_map_int));

  hashMapArray_delete_all_association(array, CAPACITY);
  destroy_HashMap(array);
}
// ---- End find a key ----


int main() {
    UNITY_BEGIN();

    RUN_TEST(hashMapArray_is_empty);
    RUN_TEST(hashMapArray_association);
    RUN_TEST(hashMapArray_delete_assoc);
    RUN_TEST(hashMapArray_delete_one_assoc);
    RUN_TEST(hashMapArray_exist);
    RUN_TEST(hashMapArray_key);

    UNITY_END();
}
