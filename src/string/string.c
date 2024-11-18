// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	//Goes through the copying the source into the destination
	while(*source)
		*destination++ = *source++;
	
	//Copies the end character
	*destination = *source;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t counter = 0;

	//Same thing as strcpy but counter limited
	while (counter < len && *source) {
		counter++;
		*destination++ = *source++;
	}
	*destination = *source;

	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *destination_cpy = destination;
	//Goes through the destination copy to the end
	while (*destination_cpy)
		destination_cpy++;

	//Adds the source on the end of the destination
	while (*source)
		*destination_cpy++ = *source++;
	*destination_cpy = *source;

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *destination_cpy = destination;
	while (*destination_cpy)
		destination_cpy++;

	size_t counter = 0;

	//Same thing as above but counter limited
	while (counter < len && *source != '\0') {
		counter++;
		*destination_cpy++ = *source++;
	}
	*destination_cpy = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	//Goes through and compares every character while they are the same
	while (*str1 && *str1 == *str2) {
		str1++;
		str2++;
	}

	//Returns the difference between the two characters that were either not equal or at the end
	return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t counter = 0;

	//Same thing as above but counter limited
	while (*str1 && *str1 == *str2 && counter < len) {
		str1++;
		str2++;
		counter++;
	}

	return counter >= len ? 0 : *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	//Goes until the end of the string
	for (; *str != '\0'; str++, i++)
		;

	//Returns the counter
	return i;
}

char *strchr(const char *str, int c)
{
	//Goes through the string until it finds the requested character
	while (*str) {
		if (*str == c)
			return (char *)str;
		str++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	//Goes through the string until the end
	//and stores every new occurance in last_occurance
	char *last_occurance = NULL;
	while (*str) {
		if (*str == c)
			last_occurance = (char *)str;
		str++;
	}

	return last_occurance;
}

char *strstr(const char *haystack, const char *needle)
{
	char *needle_cpy = (char *)needle;
	while (*haystack) {
		//Goes through the haystack until the first char of needle is found
		while (*haystack && *haystack != *needle_cpy)
			haystack++;

		//Goes through the haystack and needle simultaneously until a different character
		//or the end of the needle string
		while (*haystack && *haystack == *needle_cpy) {
			haystack++;
			needle_cpy++;
		}

		//If null is reached in the needle, then an occurance has been found
		if (*needle_cpy == '\0')
			return haystack - (needle_cpy - needle);
		needle_cpy = needle;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	//Same thing as above, it just updates last_occurance with every occurance
	char *last_occurance = NULL;
	char *needle_cpy = (char *)needle;
	while (*haystack) {
		while (*haystack && *haystack != *needle_cpy)
			haystack++;

		while (*haystack && *haystack == *needle_cpy) {
			haystack++;
			needle_cpy++;
		}

		if (*needle_cpy == '\0')
			last_occurance = (char *)(haystack - (needle_cpy - needle));
		needle_cpy = (char *)needle;
	}
	return last_occurance;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *destination_cpy = destination;
	char *source_cpy = (char *)source;

	size_t counter = 0;

	//Goes through and copies every element in the source to the destination, until the character
	//limit is reached
	while (counter < num && *source_cpy) {
		counter++;
		*destination_cpy++ = *source_cpy++;
	}
	*destination_cpy = *source_cpy;

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char* destination_cpy = (char *)destination;
	char *source_cpy = (char *)source;

	size_t counter = 0;
	//To handle the possible overlapping of memory, pointer order is verified
	//to determine whether to copy from the start or the end
	if (destination_cpy < source_cpy) {
		while (counter < num && *source_cpy) {
			counter++;
			*destination_cpy++ = *source_cpy++;
		}
	} else if (destination_cpy > source_cpy) {
		destination_cpy += num - 1;
		source_cpy += num - 1;

		while (counter < num) {
			counter++;
			*destination_cpy-- = *source_cpy--;
		}
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *str1 = (char *)ptr1;
	char *str2 = (char *)ptr2;

	size_t counter = 0;

	//Goes through and compares every element of the two given arrays
	while (*str1 && *str1 == *str2 && counter < num) {
		str1++;
		str2++;
		counter++;
	}

	return counter >= num ? 0 : *str1 - *str2;
}

void *memset(void *source, int value, size_t num)
{
	size_t counter = 0;
	char *source_cpy = (char *)source;

	//Goes through and sets every elements as the given value
	while (counter < num) {
		counter++;
		*source_cpy++ = (char)value;
	}

	return source;
}
