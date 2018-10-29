#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int getRand(){
  int file = open("/dev/random", O_RDONLY);
  if(file < 0) {
    printf("%s\n", strerror(errno));
  }
  int *ret = malloc(sizeof(int));
  int input = read(file, ret, sizeof(int));
  int c = close(file);
  return *ret;
}

int main(){

  int arr1[10];
  for (int i = 0; i < 10; i++){
    arr1[i] = getRand();
    printf("random %d: %d\n",i,arr1[i]);
  }
  printf("======================\n");

  int output = open("out.txt",O_CREAT|O_WRONLY, 777);
  if(output < 0) {
    printf("%s\n", strerror(errno));
  }
  int out = write(output, arr1, 10*sizeof(int));
  if(out < 0) {
    printf("%s\n", strerror(errno));
  }
  int input = open("out.txt",O_RDONLY);
  if(input < 0) {
    printf("%s\n", strerror(errno));
  }
  
  int arr2[10];
  int in = read(input, arr2, 10*sizeof(int));
  if(in < 0) {
    printf("%s\n", strerror(errno));
  }
  for (int k = 0; k < 10; k++){
    printf("random %d: %d\n",k,arr2[k]);
  }

  int close1 = close(output);
  if(close1 < 0) {
    printf("%s\n", strerror(errno));
  }
  int close2 = close(input);
  if(close2 < 0) {
    printf("%s\n", strerror(errno));
  }
  

}
