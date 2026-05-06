#include <stdio.h>
#include <string.h>

char input[50000000] = "3113322113";
char output[50000000] = "";

int main() {
  for (int j = 0; j < 50; j++) {
    int outIndex = 0;
    int count = 0;
    char currChar = input[0];
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
      if (currChar == input[i]) {
        count++;
      } else {
        output[outIndex++] = count + '0';
        output[outIndex++] = currChar;

        currChar = input[i];
        count = 1;
      }
    }
    output[outIndex++] = count + '0';
    output[outIndex++] = currChar;

    output[outIndex] = '\0';

    strcpy(input, output);
  }

  int resLen = strlen(output);

  printf("Result: %i\n", resLen);
}
