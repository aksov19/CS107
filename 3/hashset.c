#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{
	assert( elemSize > 0 );
	assert( numBuckets > 0);
	assert( hashfn != NULL );
	assert( comparefn != NULL );

	h->elemSize 	= elemSize;
	h->numBuckets 	= numBuckets;
	h->numElems		= 0;
	h->compare 		= comparefn;
	h->free			= freefn;
	h->hash			= hashfn;

	h->buckets		= malloc( sizeof(vector) * numBuckets );
	// Creates buckets that are size of 4
	for(int i = 0; i < numBuckets; i++){
		vector tmp;
		VectorNew( &tmp, elemSize, freefn, 4 );
		h->buckets[i] = tmp;
	}
}

void HashSetDispose(hashset *h)
{
	for(int i = 0; i < h->numBuckets; i++)
		VectorDispose( &h->buckets[i] );
	free( h->buckets );
}

int HashSetCount(const hashset *h)
{
	return h->numElems;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{
	assert( mapfn != NULL );
	
	for(int i = 0; i < h->numBuckets; i++){
		VectorMap( &h->buckets[i], mapfn, auxData );
	}
}

void HashSetEnter(hashset *h, const void *elemAddr)
{
	assert( elemAddr != NULL );

	int bucketIndex = h->hash( elemAddr, h->numBuckets );
	assert( bucketIndex >= 0 && bucketIndex < h->numBuckets );

	vector* curBucket = &h->buckets[bucketIndex];
	// Looks for a similar element in the hashset
	void* equalTo = HashSetLookup( h, elemAddr );
	
	// Checks if the elemAddr is in the hashset, if not, just appends the elemAddr to the bucket
	if( equalTo == NULL ){
		VectorAppend( curBucket, elemAddr ); 
	}else{
		// Gets the index of the element to be replaced and replaces it
		int equalToIndex = VectorSearch( curBucket, elemAddr, h->compare, 0, false );
		VectorReplace( curBucket, elemAddr, equalToIndex );
	}
}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{
	assert( elemAddr != NULL );

	int bucketIndex = h->hash( elemAddr, h->numBuckets );
	assert( bucketIndex >= 0 && bucketIndex < h->numBuckets );

	vector* curBucket = &h->buckets[bucketIndex];
	// Returns NULL if the buckets length is 0 ( necessary to avoid VectorSearch's assert() stopping the program )
	if( curBucket->logLen == 0 ) return NULL;

	// Uses VectorSearch function to look for elemAddr in a proper bucket
	int found = VectorSearch( curBucket, elemAddr, h->compare, 0, false );
	if( found == -1 ) return NULL;
	return VectorNth( curBucket, found );
}
