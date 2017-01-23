#include <stdio.h>
//int __attribute__((always_inline)) foo(){
int foo(){
	printf("this is foo!\n");
	return 0;
}
int main(){
	printf("this is main\n");
	foo();
	return 0;
}
