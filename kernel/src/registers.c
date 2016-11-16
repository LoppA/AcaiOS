#include "registers.h"

int getCS () {

	int value;

	__asm__ __volatile__("movl %%cs, %0" : "=r"(value) :);

	return value;

}

int getDS () () {

	int value;

	__asm__ __volatile__("movl %%ds, %0" : "=r"(value) :);

	return value;

} 

int getSS (){

	int value;

	__asm__ __volatile__("movl %%ss, %0" : "=r"(value) :);

	return value;

} 