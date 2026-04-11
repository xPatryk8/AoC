#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LINE = 0;

typedef struct {
  char *name;
  uint16_t value;
} var;

typedef struct {
  var *data;
  int count;
  int size;
} varMap;

varMap *MAP;

varMap *mapInit(void) {
  varMap *map = malloc(sizeof(varMap));
  map->count = 0;
  map->size = 4;
  map->data = malloc(map->size * sizeof(var));

  return map;
}

uint16_t mapFind(varMap *map, const char *name, uint16_t *result) {
  for (uint16_t i = 0; i < map->count; i++) {
    if (strcmp(map->data[i].name, name) == 0) {
      if (result != NULL)
        *result = map->data[i].value;
      return 1;
    }
  }

  return 0;
}

void mapAdd(varMap *map, const char *name, uint16_t value) {
  if (mapFind(map, name, NULL) == 0) {
    if (map->count >= map->size) {
      map->size *= 2;
      map->data = realloc(map->data, map->size * sizeof(var));
    }

    map->data[map->count].name = strdup(name);
    map->data[map->count].value = value;
    map->count++;
  }
}

int parseToArr(char line[128], const char *arr[5]) {
  line[strcspn(line, "\n")] = '\0';
  char *token = strtok(line, " ");

  int it = 0;
  while (token != NULL) {
    arr[it] = token;
    token = strtok(NULL, " ");
    it++;
  }
  return it;
}

void doInstructions(const char *elem[5], int len) {
  uint16_t num1 = 0, num2 = 0;
  switch (len) {
  case 3: // 123 -> x, y -> x
    if (isdigit(elem[0][0]))
      mapAdd(MAP, elem[2], atoi(elem[0]));
    else {
      if (mapFind(MAP, elem[0], &num1) == 1)
        mapAdd(MAP, elem[2], num1);
    }
    break;
  case 4: // NOT x -> y
    if (mapFind(MAP, elem[1], &num1) == 1) {
      mapAdd(MAP, elem[3], ~num1);
    }
    break;
  case 5: // x OP_Code y -> z
    int ok1 = mapFind(MAP, elem[0], &num1);
    if (!ok1 && isdigit(elem[0][0])) {
      num1 = atoi(elem[0]);
      ok1 = 1;
    }

    int ok2 = mapFind(MAP, elem[2], &num2);
    if (!ok2 && isdigit(elem[2][0])) {
      num2 = atoi(elem[2]);
      ok2 = 1;
    }

    if (ok1 && ok2) {
      if (strcmp(elem[1], "AND") == 0)
        mapAdd(MAP, elem[4], num1 & num2);
      else if (strcmp(elem[1], "OR") == 0)
        mapAdd(MAP, elem[4], num1 | num2);
      else if (strcmp(elem[1], "LSHIFT") == 0)
        mapAdd(MAP, elem[4], num1 << num2);
      else if (strcmp(elem[1], "RSHIFT") == 0)
        mapAdd(MAP, elem[4], num1 >> num2);
    }
    break;

    break;
  default:
    printf("Error in doInstruction\n at line: %d\n", LINE);
    break;
  }
}

void mapPrint(varMap *m, char *a) {
  if (a == NULL) {
    printf("%d wires:\n", m->count);
    printf("----------------------------\n");
    for (int i = 0; i < m->count; i++) {
      printf("%-20s = %d\n", m->data[i].name, m->data[i].value);
    }
  } else {
    for (int i = 0; i < m->count; i++) {
      if (strcmp(m->data[i].name, a) == 0)
        printf("%-20s = %d\n", m->data[i].name, m->data[i].value);
    }
  }
}

int main() {
  MAP = mapInit();
  FILE *file = fopen("in.txt", "r");

  char line[128];
  const char *elem[5];

  // Part 2
  mapAdd(MAP, "b", 956);

  while (mapFind(MAP, "a", NULL) != 1) {
    while (fgets(line, sizeof(line), file)) {
      LINE++;
      int len = parseToArr(line, elem);
      doInstructions(elem, len);
    }
    fseek(file, 0, SEEK_SET);
    LINE = 0;
  }

  mapPrint(MAP, "a");
}
