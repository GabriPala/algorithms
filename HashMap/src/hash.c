#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

struct List{
  void* key;
  void* value;
  arrayList* next;
};

struct Array{
  arrayList* list;
  int size;
};

arrayHashMap* create_HashMap(int capacity) {
  arrayHashMap* array = (arrayHashMap*) malloc(sizeof(arrayHashMap)*capacity);
  for(int i=0; i<capacity; i++)
    array[i].size = 0;
  return array;
}

void destroy_HashMap(arrayHashMap* array) {
  free(array);
}

boolean compareKey(void* listKey, void* key){
  int *key1 = (int*) (listKey);
  int *key2 = (int*) (key);
  return (*key1 == *key2);
}

void hashMapArray_insert(arrayHashMap* array, void* k, void* v, int capacity, Hash hash_map) {

	int hash = hash_map(k, capacity);

	if(array[hash].size == 0)
	{
		array[hash].list = (arrayList*) malloc(sizeof(arrayList));
    array[hash].size++;
    array[hash].list->key = k;
    array[hash].list->value = v;
	}
	else
	{
    /*  ALTERNATIVE SOLUTION WITHOUT compareKey() CONTROL --> COMPLEXITY = O(1)
    arrayList* temp = (arrayList*) malloc(sizeof(arrayList));
    temp->key = k;
    temp->value = v;
    temp->next = array[hash].list;
    array[hash].list = temp;
    array[hash].size++; */

    int cont=1;
    for(arrayList* temp = array[hash].list; cont<=array[hash].size; cont++){
      if(compareKey(temp->key, k)){
        temp->value = v;
        cont=array[hash].size;
      }
      else if(cont == array[hash].size){
        temp->next = (arrayList*) malloc(sizeof(arrayList));
        temp->next->key = k;
        temp->next->value = v;
        array[hash].size++;
        cont++;
      }
      if(cont<array[hash].size)
        temp = temp->next;
    }
	}
}

boolean hashMapArray_empty(arrayHashMap* array, int capacity) {

  for(int i=0; i<capacity; i++){
    if(array[i].size != 0)
      return FALSE;
  }
  return TRUE;
}

int hashMapArray_num_association(arrayHashMap* array, int capacity) {

  int num_association = 0;

  for(int i=0; i<capacity; i++)
    num_association += array[i].size;
  return num_association;
}

void delete_association_row(arrayList* list, int size){
  if(size==1)
    free(list);
  else {
    delete_association_row(list->next, size-1);
    free(list);
  }
}

void hashMapArray_delete_all_association(arrayHashMap* array, int capacity) {

  for(int i=0; i<capacity; i++){
    if(array[i].size!=0)
      delete_association_row(array[i].list, array[i].size);
    array[i].size = 0;
  }
}

boolean hashMapArray_exists_key(arrayHashMap* array, void* k, int capacity, Hash hash_map) {

  int hash = hash_map(k, capacity);
  int cont=1;
  for(arrayList* temp = array[hash].list; cont<=array[hash].size; cont++){
    if(compareKey(temp->key, k))
      return TRUE;

    if(cont<array[hash].size)
      temp = temp->next;
  }
  return FALSE;
}

void* hashMapArray_search_key(arrayHashMap* array, void* k, int capacity, Hash hash_map) {

  int hash = hash_map(k, capacity);
  int cont=1;
  for(arrayList* temp = array[hash].list; cont<=array[hash].size; cont++){
    if(compareKey(temp->key, k))
      return temp->value;

    if(cont<array[hash].size)
      temp = temp->next;
  }
  return NULL;
}

void hashMapArray_delete_association(arrayHashMap* array, void* k, int capacity, Hash hash_map) {

  int hash = hash_map(k, capacity);
  int cont = 1;
  arrayList* prec = array[hash].list;
  for(arrayList* temp = array[hash].list; cont<=array[hash].size; cont++){
    if(compareKey(temp->key, k)){
      if(cont<array[hash].size){
        if(cont == 1)
          array[hash].list = temp->next;
        else
          prec->next = temp->next;
      }
      else
        prec->next = NULL;

      free(temp);
      array[hash].size--;
    }
    if(cont<array[hash].size){
      prec = temp;
      temp = temp->next;
    }
  }
}

void** hashMapArray_all_keys(arrayHashMap* array, int capacity) {

  void** allKeys = (void**) malloc(sizeof(void*)*hashMapArray_num_association(array, capacity));

  int j=0;
  for(int i=0; i<capacity; i++){
    int cont = 1;
    for(arrayList* temp = array[i].list; cont<=array[i].size; cont++){
        allKeys[j] = temp->key;
        j++;
        if(cont<array[i].size)
          temp = temp->next;
    }
  }
  return allKeys;
}

void* hashMap_get(arrayHashMap* array, int i){
  return array[i].list;
}

int hashMap_size(arrayHashMap* array, int i){
  return array[i].size;
}

void* list_key(arrayList* list){
  return list->key;
}

void* list_value(arrayList* list){
  return list->value;
}

void* list_next(arrayList* list){
  return list->next;
}

void keysArray_free(void** keys) {
    free(keys);
}
