#ifndef _DATASTRUCT_STRING_STRSTR_H_ 
#define _DATASTRUCT_STRING_STRSTR_H_ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *naiveSearch(const char *str1, const char *str2);
char *kmpSearch(const char *str1, const char *str2);

int* computeOverlay( const char *ptn, int len);
#endif
