#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*  ADDED:
    Gets a vector element at a given position,
    used instead of VectorNth to avoid VectorNth's unnecessary assert check. */
#define elemAt(v, n) (char*)v->elems + n*v->elemSize;

// ADDED: Increases the size of the vector
void growVector(vector* v){
    if( v->allocLen == 0 ) v->allocLen = 1;
    else v->allocLen *= 2;

    v->elems = realloc(v->elems, v->allocLen*v->elemSize);
    assert(v->elems != NULL);
}

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
    assert( initialAllocation >= 0 );
    v->allocLen = initialAllocation;
    v->logLen   = 0;
    v->elemSize = elemSize;
    v->freeFn   = freeFn;
    v->elems    = malloc(elemSize * initialAllocation);
    assert( v->elems != NULL );
}

void VectorDispose(vector *v)
{
    if( v->freeFn != NULL ){
        for(int i = 0; i < v->logLen; i++){
            v->freeFn( (char*)v->elems + i*v->elemSize );
        }
    }
    free(v->elems);
}

int VectorLength(const vector *v)
{
    return v->logLen;
}

void *VectorNth(const vector *v, int position)
{ 
    assert( position >= 0 && position < v->logLen );
    return (char*)v->elems + v->elemSize * position;
}

void VectorReplace(vector *v, const void *elemAddr, int position)
{
    assert( position >= 0 && position < v->logLen );
    
    // Writes over the element at the given position
    void* nThElem = elemAt(v, position);
    if( v->freeFn != NULL ) v->freeFn( nThElem );
    memcpy( nThElem, elemAddr, v->elemSize );
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
    assert( position >= 0 && position <= v->logLen );

    // Checks if the size needs to be increased
    if( v->logLen == v->allocLen ){
        growVector(v);
    }

    void* elemAtPos = elemAt(v, position);
    // If position is not the end of the vector, moves every element after the given position to the right
    if( position != v->logLen ){
        memmove( (char*)elemAtPos + v->elemSize, elemAtPos, v->elemSize*(v->logLen - position) );
    }
    // Copies the elemAddr into the vector
    memcpy( elemAtPos, elemAddr, v->elemSize );
    v->logLen++;
}

void VectorAppend(vector *v, const void *elemAddr)
{
    // Checks if the size needs to be increased
    if( v->logLen == v->allocLen ){
        growVector(v);
    }

    // Copy the element to the end of the vector
    memcpy( (char*)v->elems + v->elemSize*v->logLen, elemAddr, v->elemSize );
    v->logLen++;
}

void VectorDelete(vector *v, int position)
{
    assert( position >= 0 && position < v->logLen );

    void* nThElem = elemAt(v, position);
    // Frees the element at the given position
    if( v->freeFn != NULL ) v->freeFn( nThElem );
    // If the element was not the last element of the vector, moves every value after the position to the left
    if( position != v->logLen - 1 ){
        memmove( nThElem, (char*)nThElem + v->elemSize, (v->logLen-position)*v->elemSize );
    }
    v->logLen--;
}

void VectorSort(vector *v, VectorCompareFunction compare)
{
    assert( compare != NULL );
    qsort( v->elems, v->logLen, v->elemSize, compare );
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{
    assert( mapFn != NULL );

    for(int i = 0; i < v->logLen; i++){
        mapFn( (char*)v->elems + i*v->elemSize, auxData );
    }
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
    assert( startIndex >= 0 && startIndex < v->logLen );
    assert( key != NULL && searchFn != NULL );

    // If the vector is sorted, uses bsearch and returns a value
    if( isSorted ){
        char* tmp = (char*)bsearch( key, v->elems, v->logLen, v->elemSize, searchFn );
        if( tmp == NULL ) return kNotFound;
        return ( tmp - (char*)v->elems ) / v->elemSize;
    }

    // If the vector is not sorted, searches manually
    for(int i = 0; i < v->logLen; i++ ){
        if( searchFn( (char*)v->elems + i*v->elemSize, key ) == 0 ) return i;
    }
    return kNotFound; 
}
