#include <stdio.h>

int mini(int a, int b, int c) {
  int m = a;
  if (m > b) m = b;
  if (m > c) m = c;
  return m;
}

int mini2(int a, int b) {
  if (a < b) return a;
  else return b;
}

int main() {
  FILE *file = fopen("in.txt", "rb");

  char ch[128];

  int a, b, c;
  int result;
  int sum = 0;

  while (fgets(ch, sizeof(ch), file)) {
    sscanf(ch, "%dx%dx%d", &a, &b, &c);
    
    // PART 1
    // int A = a*b;
    // int B = a*c;
    // int C = b*c;
    // int min = mini(A, B, C);
    // if (min == -1) printf("Minus");
    // result = 2 * (A + B + C) + min;
    // sum += result;

    // PART 2
    int min1 = mini(a, b, c);
    int min2 = 0;
    if(min1 == a) min2 = mini2(b, c);
    else if(min1 == b) min2 = mini2(a, c);
    else min2 = mini2(a, b);

    int ribb = 2 * min1 + 2 * min2;
    int bow = a * b * c;

    result = ribb + bow;

    sum += result;

    printf("Result: %d\n", result);
  }

  printf("Sum: %d\n", sum);

  fclose(file);
}
