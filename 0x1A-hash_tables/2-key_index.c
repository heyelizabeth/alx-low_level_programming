#include "hash_tables.h"

/**
 * key_index - Function that gives you the index of a key
 * @key: Key to be hashed
 * @size: Size of the array of the hash table
 * Return: Index at which the key/value pair should be stored in the array
 * of the hash table
 */

unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash_value = hash_djb2(key);
	unsigned long int index = hash_value % size;

	return (index);
}
