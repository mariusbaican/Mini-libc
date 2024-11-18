// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	//First make a mmap call
	void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	//If it fails, exit
	if (addr == MAP_FAILED)
		return NULL;

	//Otherwise it adds an extra block to the memory list
	mem_list_add(addr, size);
	return addr;
}

void *calloc(size_t nmemb, size_t size)
{
	void *addr = mmap(NULL, nmemb * size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (addr == MAP_FAILED)
		return NULL;

	mem_list_add(addr, nmemb * size);

	//The only difference compared to malloc is that it sets every value to 0
	memset(addr, 0, nmemb * size);

	return addr;
}

void free(void *ptr)
{
	if (!ptr)
		return;

	//Firstly unmap the memory, then delete the block from the memory list
	munmap(ptr, mem_list_find(ptr)->len);
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	if(!ptr)
		return NULL;

	size_t old_size = mem_list_find(ptr)->len;

	//Allocate a new batch of memory
	void *addr = malloc(size);
	if (addr == NULL)
		return NULL;

	//Then copy the data to the new memory, choosing the minimum length between
	//the new and the old one
	memcpy(addr, ptr, MIN(old_size, size));
	free(ptr); //At the end, free the old memory

	return addr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return realloc(ptr, nmemb * size);
}
