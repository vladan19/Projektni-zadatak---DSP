#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>

int initBuffer(Buffer* buffer, int n){
  if(n>=1){
    buffer->buff=(float*)malloc(n*sizeof(float));
    buffer->front=-1;
    buffer->rear=-1;
    buffer->capacity=n;
    return 1;
  }
  return 0;
}
int insert(Buffer* buffer, float x){
  if(isEmpty(buffer)){
    buffer->front+=1;
    buffer->rear+=1;
  }
  else if(isFull(buffer)){
    buffer->front+=1;
    buffer->front%=buffer->capacity;
  }
  buffer->buff[buffer->rear]=x;
  buffer->rear+=1;
  buffer->rear%=buffer->capacity;
  return 1;
}
int isEmpty(Buffer* buffer){
  return (buffer->front==-1);
}
int isFull(Buffer* buffer){
  return (buffer->front!=-1) && (buffer->front==buffer->rear);
}
void deleteBuffer(Buffer* buffer){
  free(buffer->buff);
}