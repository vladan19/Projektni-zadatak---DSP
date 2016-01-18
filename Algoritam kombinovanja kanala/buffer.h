#ifndef BUFFER_H
#define BUFFER_H
typedef struct Buffer{
  float *buff;
  int front;
  int rear;
  int capacity;
}Buffer;

int initBuffer(Buffer* buffer, int n);
int insert(Buffer* buffer, float x);
int isEmpty(Buffer* buffer);
int isFull(Buffer* buffer);
void deleteBuffer(Buffer* buffer);
#endif