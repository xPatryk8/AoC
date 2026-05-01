#include <stdio.h>
#include <string.h>

int main() {
  FILE *file = fopen("in.txt", "r");
  char line[2048];

  int totalLen = 0;
  int totalStringLen = 0;
  int totalEncoded = 0;

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = 0;
    int len = strlen(line);
    if (len == 0)
      continue;
    totalLen += len;

    int stringLen = 0;
    int encoded = 4;
    for (int i = 1; i < len - 1; i++) {
      if (line[i] == '\\') {
        if (line[i + 1] == 'x') {
          stringLen++;
          encoded += 1;
          i += 3;
        } else if (line[i + 1] == '\\' || line[i + 1] == '\"') {
          encoded += 2;
          stringLen++;
          i++;
        }
      } else
        stringLen++;
    }
    encoded += len;
    totalEncoded += encoded;
    printf("%s, len: %i, string len: %i, encoded: %i\n", line, len, stringLen, encoded);
    totalStringLen += stringLen;
  }
  int result = totalLen - totalStringLen;
  int result2 = totalEncoded - totalLen;
  printf("total len: %i, total string len: %i, result: %i, result2: %i\n", totalLen, totalStringLen,
         result, result2);
}
