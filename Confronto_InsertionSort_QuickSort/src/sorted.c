#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sorted.h"


#define INITIAL_CAPACITY 20000000

struct Array{
    void** element;
    int capacity;
    int size;
};

SortedArray* sortedArray_new() {
    SortedArray* result = (SortedArray*) malloc(sizeof(SortedArray));
    result->capacity = INITIAL_CAPACITY;
    result->element = (void**) malloc(sizeof(void*) * result->capacity);
    result->size = 0;

    return result;
}

void sortedArray_free(SortedArray* sa) {
    free(sa->element);
    free(sa);
}

void sortedArray_resize(SortedArray* sa, size_t memsize) {
    sa->capacity = memsize;
    sa->element = (void**) realloc(sa->element, sa->capacity*sizeof(void*));
}

void sortedArray_insert(SortedArray* sa, void* obj) {

    if(sa->capacity == sa->size) {
        sortedArray_resize(sa, sa->capacity * 2);
    }

    sa->element[sa->size] = obj;
    sa->size++;
}

void* sortedArray_get(SortedArray* sa, int i) {
    return sa->element[i];
}

int sortedArray_size(SortedArray* sa) {
    return sa->size;
}

void insertion_sort(SortedArray* sa, int n, Cmp compare){

      void* temp;
      int j;

       if(n>1){
          insertion_sort(sa, n-1, compare);
          temp = sa->element[n-1];
          j = n-2;
          while(j >= 0 && (compare(sa->element[j], temp)>0)){
            sa->element[j+1] = sa->element[j];
            j--;
          }
          sa->element[j+1] = temp;
        }
}

void quick_sort(SortedArray* sa, int p, int u, Cmp compare){

   int i, j, piv;
   void* temp;

   if(p<u){
      piv=p;
      i=p;
      j=u-1;

      while(i<j){
         while(i<u && (compare(sa->element[i], sa->element[piv]) <= 0))
           i++;

         while(j>p && (compare(sa->element[j], sa->element[piv])>0)){
           j--;
         }

         if(i<j){
            temp=sa->element[i];
            sa->element[i]=sa->element[j];
            sa->element[j]=temp;
         }
      }

      temp=sa->element[piv];
      sa->element[piv]=sa->element[j];
      sa->element[j]=temp;
      quick_sort(sa, p, j, compare);
      quick_sort(sa, j+1, u, compare);
   }
}
