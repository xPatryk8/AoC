#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void increment(char password[], int len) {
  for (int i = len - 1; i >= 0; i--) {
    char nextChar = (password[i] - 'a' + 1) % 26 + 'a';
    password[i] = nextChar;
    if (nextChar != 'a')
      break;
  }
}

bool hasIncreasingStraight(char password[], int len) {
  for (int i = 0; i < len - 2; i++) {
    if (password[i + 2] - password[i + 1] == 1 && password[i + 1] - password[i] == 1)
      return true;
  }
  return false;
}

bool hasNoBannedLetters(char password[], int len) {
  for (int i = 0; i < len; i++) {
    if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l')
      return false;
  }
  return true;
}

bool hasTwoPairs(char password[], int len) {
  int pairs = 0;
  for (int i = 0; i < len - 1; i++) {
    if (password[i] == password[i + 1]) {
      pairs++;
      i++;
    }
    if (pairs == 2)
      return true;
  }
  return false;
}

bool checkIfCorrect(char password[], int len) {
  if (hasIncreasingStraight(password, len) && hasNoBannedLetters(password, len) &&
      hasTwoPairs(password, len))
    return true;
  else
    return false;
}

int main(int argc, char *argv[]) {
  char *password;
  if (argc == 2)
    password = argv[1];
  else
    password = "abcdffaa";

  int passLen = strlen(password);
  printf("pass len: %i\n", passLen);

  bool isCorrect = false;
  while (!isCorrect) {
    increment(password, passLen);
    isCorrect = checkIfCorrect(password, passLen);
    printf("%d\n", isCorrect);
  }
  printf("%s\n", password);
}
