#include "../include/util/Utils.h"

void safe_free(void* ptr) {
	if (ptr) {
		free(ptr);
		ptr = NULL;
	}
}

void swap(void* ptr1, void* ptr2, int size)
{
    void* tmp = (void*)malloc(size);

    memcpy(tmp, ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, tmp, size);

    safe_free(tmp);
}