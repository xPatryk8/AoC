#include <stdio.h>

int main() {
  FILE *file = fopen("in.txt", "rb");

  char ch;
  int floor = 0;
  int pos = 0;

  while((ch = fgetc(file)) != EOF) {
    if(ch == '(') floor++;
    else if (ch == ')') floor--;

    pos++;

    if (floor == -1) break;
  }

  printf("Floor: %i\nPosition: %i\n", floor, pos);

  fclose(file);

  return 0;
}
