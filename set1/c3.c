// Single-byte XOR cipher

#include <stdbool.h>
#include "encodeDecode.c"

typedef int heuristic_t;

void xorHexCipher(char key, char* hex_cipher, char* deciphered) {
  size_t dec_len = strlen(hex_cipher) / 2;
  for (int i = 0; i < dec_len; i += 1) {
    deciphered[i] = key ^ decodeHexByte(hex_cipher + 2 * i);
  }
}

bool isLetter(char c) {
  if ('a' <= c && c <= 'z') {
    return true;
  } else if ('A' <= c && c <= 'Z') {
    return true;
  } else {
    return false;
  }
}

bool isSpace(char c) {
  return c == ' ';
}

heuristic_t heuristic(char* string) {
  heuristic_t acc = 0.;
  // Count number of letters and spaces
  while (*string != '\0') {
    acc += isLetter(*string) || isSpace(*string);
    string++;
  }
  return acc;
}

int main(int argc, char* argv[]) {
  char* ciphered_str =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  // char* ciphered_str = argv[1];
  assert(!(strlen(ciphered_str) % 2));  // precondition: len divisible by 2
  size_t len = strlen(ciphered_str) / 2;
  char* deciphered_str = malloc(len * sizeof(char) + 1);
  deciphered_str[len] = '\0';
  // Exhaust key space
  char best_key = 0;
  heuristic_t best_heuristic = 0.;
  for (char key = CHAR_MIN; key <= CHAR_MAX; ++key) {
    xorHexCipher(key, ciphered_str, deciphered_str);
    heuristic_t current_heuristic = heuristic(deciphered_str);
    if (current_heuristic > best_heuristic) {
      best_key = key;
      best_heuristic = current_heuristic;
    }
    if (key == CHAR_MAX) {
      break;
    }
  }
  xorHexCipher(best_key, ciphered_str, deciphered_str);
  printf(
      "Final:\n  Key: %c = %d \n  Heuristic score: %d \n  Decoded string: "
      "\"%s\" \n",
      best_key, best_key, best_heuristic, deciphered_str);
  return 0;
}
