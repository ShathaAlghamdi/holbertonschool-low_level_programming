#include <stdio.h>
/**
main - using sizeof to determine the size of data types

return 0
 */

 int main(void){
    int n;
    printf("size of type 'char' on my computer: %lu bytes \n", sizeof(char));
    printf("size of type 'int' on my computer: %lu bytes \n", sizeof(int));
    printf("size of type 'float' on my computer: %lu bytes \n", sizeof(float));
    printf("size of type 'double' on my computer: %lu bytes \n", sizeof(double));
    printf("size of type 'long' on my computer: %lu bytes \n", sizeof(long));
    printf("size of type 'long long' on my computer: %lu bytes \n", sizeof(long long));
    printf("size of type 'short' on my computer: %lu bytes \n", sizeof(short));
    printf("size of type 'long double' on my computer: %lu bytes \n", sizeof(long double)); 

    char d; 
    int c; 
    printf("address of variable 'n' is : %p\n" , &n);
    printf("Adress of variable 'c ' is : %p\n" , &c);
    return 0; 

    /*Storing memory addresses*/
    int *p;
    printf("size of pointer: %lu\n ", sizeof(p));
    printf("Address of variable 'p': %p\n", &p);
  int n1;
  int *p;

  n1 = 98;
  p = &n1;
  printf("Address of 'n1': %p\n", &n1);
  printf("Value of 'p': %p\n", p);

 }