#include "string.h"

int strlen(const char * palavra){
	int i;
	i=0;
	while(palavra[i]!='\0'){
		i++;
	}
	return i;
}

void *memcpy(void *mem1, const void *mem2, int tam){
	char *m1 = mem1;
	const char *m2 = mem2;
	int i = 0;

	for (i = 0; i < tam; i++)
		m1[i] = m2[i];

	return mem1;
}

char *strcpy(char *mem1, const char *mem2){
	int i=0;
	while(mem2[i]!='\0'){
		mem1[i] = mem2[i];
		i++;
	}
	return mem1;
}

int strcmp(const char *p1, const char *p2){
	int i=0;
	while(p1[i]==p2[i]){
		if(p1[i]=='\0' && p2[i]=='\0'){
			return 1;
		}
		i++;
	}
	return 0;
}
