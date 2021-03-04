#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define CAPACITYKEYS 10000000

typedef struct{
  int key;
  int value;
}arrayGeneric;

int* int_value(int n){
  int* num = (int*) malloc (sizeof(int));
  *num = n;
  return num;
}

int hash_map_int(void* key, int capacity){
  return *((int*)key) % capacity;
}

arrayGeneric* load_data_generic(char const* filename, unsigned long int capacity){
  FILE* file = fopen(filename, "r");

  int k;
  int v;
  int lineno = 0;

  arrayGeneric* rec = (arrayGeneric*) malloc(sizeof(arrayGeneric)*capacity);

  while(lineno<capacity) {
      assert(file!=NULL);
      int n = fscanf(file, "%d,%d", &k, &v);
      lineno++;

      if(n != 2) {
        if(feof(file)) {
            continue;
        }
      printf("Error while reading file at line: %d\n", lineno);
      exit(EXIT_FAILURE);
      }

      rec[lineno-1].key = k;
      rec[lineno-1].value = v;
  }
  return rec;
}

void quick_sort(arrayGeneric* arrayQuick, int p, int u){

   int i, j, piv;
   arrayGeneric temp = *((arrayGeneric*) malloc(sizeof(arrayGeneric)));

   if(p<u){
      piv=p;
      i=p;
      j=u-1;

      while(i<j){
         while(i<u && (arrayQuick[i].key <= arrayQuick[piv].key))
           i++;

         while(j>p && (arrayQuick[j].key > arrayQuick[piv].key))
           j--;

         if(i<j){
            temp = arrayQuick[i];
            arrayQuick[i] = arrayQuick[j];
            arrayQuick[j] = temp;
         }
      }

      temp = arrayQuick[piv];
      arrayQuick[piv] = arrayQuick[j];
      arrayQuick[j] = temp;
      quick_sort(arrayQuick, p, j);
      quick_sort(arrayQuick, j+1, u);
   }
}

// Binary search algoritm
boolean binary_search(arrayGeneric* arrayMerge, int x, int a, int z) {
    int m;
    m = (a+z)/2;   // middle element
    if (z-a<0)
      return FALSE;
    else if (x<arrayMerge[m].key)
      return binary_search(arrayMerge, x, a, m-1);
    else if (x>arrayMerge[m].key)
      return binary_search(arrayMerge, x, m+1, z);
    else
      return TRUE;
 }

// Generation of 10000000 values
int* array_keys(){
  int* keys = malloc(sizeof(int)*CAPACITYKEYS);
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i<CAPACITYKEYS; i++)
    keys[i] = rand()%(CAPACITYKEYS+1);
  return keys;
}

int main(int argc, char const *argv[])
{
    // ---- Start upload and sorted data ----
    printf("\n--- READING ---\n");

    unsigned long int capacity = atoi(argv[2]);
    arrayHashMap* arrayHash = create_HashMap(capacity);

    time_t start = clock();
    arrayGeneric* arrayTempHashMap = load_data_generic(argv[1], capacity);
    for(int i=0; i<capacity; i++)
      hashMapArray_insert(arrayHash, int_value(arrayTempHashMap[i].key), int_value(arrayTempHashMap[i].key), capacity, (Hash) hash_map_int);
    time_t end = clock();
    printf("Reading with Hash Map =  %f sec. \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    start = clock();
    arrayGeneric* arrayGeneric = load_data_generic(argv[1], capacity);
    quick_sort(arrayGeneric, 0, capacity);
    end = clock();
    printf("Reading with Quick Sort =  %f sec. \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    // ---- End upload and sorted data ----

    // ---- Start find keys ----
    int* keys = array_keys();
    int successesHM = 0, failuresHM = 0;
    int successesBS = 0, failuresBS = 0;

    printf("\n\n");
    printf("--- FINDING ---\n");

    // ---- Start find keys with hash map ----
    start = clock();
    for(int i=0; i<CAPACITYKEYS; i++){
      if(hashMapArray_exists_key(arrayHash, int_value(keys[i]), capacity, (Hash) hash_map_int))
        successesHM++;
      else
        failuresHM++;
    }
    end = clock();
    printf("Find with Hash Map =  %f sec.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Successes with Hash Map = %d\n", successesHM);
    printf("Failures with Hash Map = %d\n", failuresHM);
    // ---- End find keys with hash map ----

    printf("\n");

    // ---- Start find keys with binary search ----
    start = clock();
    for(int i=0; i<CAPACITYKEYS; i++){
      if(binary_search(arrayGeneric, keys[i], 0, capacity))
        successesBS++;
      else
        failuresBS++;
    }
    end = clock();
    printf("Find with Binary Search =  %f sec.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Successes with Binary Search = %d\n", successesBS);
    printf("Failures with Binary Search = %d\n\n", failuresBS);
    // ---- End find keys with binary search ----
    // ---- End find keys ----

    // ---- Deallocation ----
    hashMapArray_delete_all_association(arrayHash, capacity);
    destroy_HashMap(arrayHash);
    free(arrayTempHashMap);
    free(arrayGeneric);
    free(keys);

    return 0;
}
