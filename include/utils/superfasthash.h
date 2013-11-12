#ifndef SUPERFASTHASH_H
#define SUPERFASTHASH_H

#include <stdint.h>
#include <stddef.h> 

/* original version */
uint32_t SuperFastHash (const char * data, int len);

/* version for use with hashtab */
int ht_fast_hash (void * key, size_t keylen, size_t hashtab_size);

#endif