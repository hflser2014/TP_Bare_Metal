typedef unsigned int size_t;
void* memcpy(void* destination, void* source, size_t size){
	// GCC espère que memcpy() peut aussi gérer le cas oû dst et src se repile.
	// Donc les réalisation de memcpy et memmove sont identiques ici.
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

void* memset(void *pointer, int value, size_t n) {
    unsigned char *p = (unsigned char *)pointer;

    while (n--) {
        *p++ = (unsigned char)value;
    }

    return pointer;
}

int memcmp(const void *pointer1, const void *pointer2, size_t n) {
    const unsigned char *p1 = (const unsigned char *)pointer1;
    const unsigned char *p2 = (const unsigned char *)pointer2;

    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;  // Renvoyer la différence des premières bits qui sont différents. 
        }
        p1++;
        p2++;
    }

    return 0;
}
