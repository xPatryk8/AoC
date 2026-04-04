#include <stdio.h>
#include <stdbool.h>

int main() {
  FILE* file = fopen("in.txt", "rb");

  char move;
  bool grid[2000][2000] = {false};
  grid[1000][1000] = true;
  int santaX = 1000, santaY = 1000;
  int roboX = 1000, roboY = 1000;
  int count = 1;
  int moveCount = 1;

  while((move = getc(file)) != EOF) {
    int x, y;
    if(moveCount % 2 == 1) {
      x = santaX;
      y = santaY;
    } else {
      x = roboX;
      y = roboY;
    }


    switch(move){
      case '^': y++; break;
      case '<': x--; break;
      case 'v': y--; break;
      case '>': x++; break;
    }

    if (grid[x][y] == false) {
      count++;
      grid[x][y] = true;
    }

    if(moveCount % 2 == 1) {
      santaX = x;
      santaY = y;
    } else {
      roboX = x;
      roboY = y;
    }

    moveCount++;
    printf("Move: %c\nCount: %d\nSanta: %d, %d\nRobo: %d, %d\n", move, count, santaX, santaY, roboX, roboY);
  }
  printf("------------------------------------\n");
  printf("Result: %d\nx: %d, y: %d\n", count, santaX, santaY);
}
