#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool lights[1000][1000] = {false};
int result = 0;

void makeInstruction(char *instruction, int startX, int startY, int endX,
                     int endY) {
  if (strcmp(instruction, "on") == 0) {
    for (int x = startX; x <= endX; x++)
      for (int y = startY; y <= endY; y++) {
        lights[x][y] = true;
      }
  } else if (strcmp(instruction, "off") == 0) {
    for (int x = startX; x <= endX; x++)
      for (int y = startY; y <= endY; y++) {
        lights[x][y] = false;
      }
  } else if (strcmp(instruction, "toggle") == 0) {
    for (int x = startX; x <= endX; x++)
      for (int y = startY; y <= endY; y++) {
        lights[x][y] = !lights[x][y];
      }
  }
}

int countLightsOn() {
  int result = 0;

  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      if (lights[x][y] == true)
        result++;
    }
  }

  return result;
}

int main() {

  FILE *file = fopen("in.txt", "r");
  char line[128];

  char instruction[16];
  int startX, startY, endX, endY;
  while (fgets(line, sizeof(line), file)) {
    memset(instruction, 0, sizeof(instruction));
    if (strncmp(line, "toggle", 6) == 0) {
      sscanf(line, "%s %d,%d %*s %d,%d", instruction, &startX, &startY, &endX,
             &endY);
    } else {
      sscanf(line, "%*s %s %d,%d %*s %d,%d", instruction, &startX, &startY,
             &endX, &endY);
    }

    makeInstruction(instruction, startX, startY, endX, endY);
  }

  printf("Result: %d\n", countLightsOn());
  return 0;
}
