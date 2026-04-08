#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define lineSize 17 // 16 chars + '\n'

bool checkVowels(char line[lineSize], int len) {
  char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
  int vowCount = 0;

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < 5; j++) {
      if (line[i] == vowels[j])
        vowCount++;
    }
  }

  if (vowCount >= 3)
    return true;
  else
    return false;
}

bool checkDouble(char line[lineSize], int len) {
  char curr = line[0];
  for (int i = 1; i < len; i++) {
    if (curr == line[i])
      return true;
    else
      curr = line[i];
  }
  return false;
}

bool checkStrings(char line[lineSize], int len) {
  char *strings[4] = {"ab", "cd", "pq", "xy"};

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < 4; j++) {
      if (line[i] == strings[j][0] && line[i + 1] == strings[j][1])
        return false;
    }
  }

  return true;
}

int main() {

  FILE *file = fopen("in.txt", "rb");

  char line[lineSize];
  int niceStrings = 0;

  while (fgets(line, sizeof(line), file)) {
    int len = strlen(line);
    if (checkDouble(line, len) && checkStrings(line, len) &&
        checkVowels(line, len)) {
      niceStrings++;
    }
  }

  printf("Nice: %d", niceStrings);
}
