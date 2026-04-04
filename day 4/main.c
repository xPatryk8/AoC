#include "md5-c/md5.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  char baseMsg[] = "yzbqklnj";
  int num = 0;

  while (true) {
    char msg[32];
    sprintf(msg, "%s%d", baseMsg, num);

    uint8_t result[16];
    md5String(msg, result);

    if (result[0] == 0x00 && result[1] == 0x00 && result[2] == 0x00) {

      printf("%d\n", num);
      break;
    }

    num++;
  }

  return 0;
}
