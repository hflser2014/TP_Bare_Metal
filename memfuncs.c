typedef unsigned int size_t;
// GCC expect that memcpy() can also deal with overlapping regions
// so the memcpy() and memmove() that we implemented are identical

/**
 * @brief Copies a block of memory from a source address to a destination address.
 *
 * This function copies `size` bytes from the memory area pointed to by `source`
 * to the memory area pointed to by `destination`. The memory areas should not overlap.
 *
 * @param destination Pointer to the destination memory area.
 * @param source Pointer to the source memory area.
 * @param size Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void* memcpy(void* destination, void* source, size_t size){
	unsigned char* dst = (unsigned char*) &destination;
	const unsigned char* src = (const unsigned char*) &source;

	// Depending on the relative position of src and dst,
	// as well as their overlapping situation,
	// we need to perform the copy process in different direction
	if (src < dst && src+size>dst ){
		src += size;
		dst += size;
		while (size--){
			*(--dst) = *(--src);
		}
	}else{
		while (size--){
			*(dst++) = *(src++);
		}
	}
	return destination;
};

/**
 * @brief Moves a block of memory from source to destination.
 *
 * This function copies `size` bytes from the memory area pointed to by `source`
 * to the memory area pointed to by `destination`. The memory areas may overlap.
 *
 * @param destination Pointer to the destination memory area.
 * @param source Pointer to the source memory area.
 * @param size Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void* memmove(void* destination, void* source, size_t size){
	unsigned char* dst = (unsigned char*) &destination;
	const unsigned char* src = (const unsigned char*) &source;
	if (src < dst && src+size>dst ){
		src += size;
		dst += size;
		while (size--){
			*(--dst) = *(--src);
		}
	}else{
		while (size--){
			*(dst++) = *(src++);
		}
	}
	return destination;
};

/**
 * @brief Sets the first `n` bytes of the block of memory pointed by `pointer` to the specified `value`.
 *
 * @param pointer Pointer to the block of memory to fill.
 * @param value Value to be set.
 * @param n Number of bytes to be set to the value.
 * @return Pointer to the block of memory.
 */
void* memset(void *pointer, int value, size_t n) {
    unsigned char *p = (unsigned char *)pointer;

    while (n--) {
        *p++ = (unsigned char)value;
    }

    return pointer;
}

/**
 * @brief Compares two blocks of memory.
 *
 * This function compares the first `n` bytes of the memory areas pointed to by `pointer1` and `pointer2`.
 * The comparison is done byte by byte (unsigned char), and stops as soon as a differing byte is found.
 *
 * @param pointer1 Pointer to the first block of memory.
 * @param pointer2 Pointer to the second block of memory.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first differing byte in `pointer1`
 * is found, respectively, to be less than, equal to, or greater than the corresponding byte in `pointer2`.
 * If the two memory blocks are identical for the first `n` bytes, the function returns 0.
 */
int memcmp(const void *pointer1, const void *pointer2, size_t n) {
	// Renvoyer la différence des premières bits qui sont différents. 
    const unsigned char *p1 = (const unsigned char *)pointer1;
    const unsigned char *p2 = (const unsigned char *)pointer2;

    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }

    return 0;
}
