// Convert hex to base64

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertHexToDec(char hex) {
  if ('0' <= hex && hex <= '9') {
    return hex - '0';
  } else if ('a' <= hex && hex <= 'f') {
    return hex - 'a' + 10;
  } else {
    return -1;
  }
}

int convertHexStringToDec(char* hex_str, size_t hex_str_len) {
  int acc = 0;
  int mantissa = 1;  // keep track of power of 16
  // to base 10
  for (size_t i = hex_str_len - 1; i < hex_str_len; i--) {
    // < because underflow
    acc += convertHexToDec(hex_str[i]) * mantissa;
    mantissa *= 16;
  }
  return acc;
}

// Convert a decimal x satisfying 0<=x<=63 to a base 64 encoded character.
char convertDecToB64(int dec) {
  const int NUM_DIGITS = 10;
  const int ALPHABET_LENGTH = 26;

  if (dec < ALPHABET_LENGTH) {
    return dec + 'A';
  } else if (dec < 2 * ALPHABET_LENGTH) {
    return dec + 'a' - ALPHABET_LENGTH;
  } else if (dec < 2 * ALPHABET_LENGTH + NUM_DIGITS) {
    return dec + '0' - 2 * ALPHABET_LENGTH;
  } else {
    printf("error in `convertDecToB64` %d", dec);
    exit(1);
  }
  // TODO maybe need more characters?
}

void convertHexGroupToB64(char* hex_str, size_t hex_str_len, char* b64_str) {
  // to base 10
  const int dec = convertHexStringToDec(hex_str, hex_str_len);

  // to base 64
  const int q = dec / 64;  // quotient, 10's place of b64
  const int r = dec % 64;  // remainder
  b64_str[0] = convertDecToB64(q);
  b64_str[1] = convertDecToB64(r);
}

char* convertHexToB64(char* hex_str, size_t hex_str_len) {
  int b64_str_len = hex_str_len * 2 / 3;
  char* b64_str = malloc(b64_str_len * sizeof(char) + 1);
  assert(b64_str);

  int hex_idx = 0;  // index the hex string
  int b64_idx = 0;
  while (hex_idx < hex_str_len) {
    convertHexGroupToB64(hex_str + hex_idx, 3, b64_str + b64_idx);
    // TODO: make this a bit more robust, namely the magic number 3 which is
    // manually verified; the original hex_str must have length divisible by 3
    hex_idx += 3;
    b64_idx += 2;
  }
  b64_str[b64_str_len] = '\0';
  return b64_str;
}

int main(int argc, char const* argv[]) {
  char* hex_str = argv[1];
  size_t hex_str_len = strlen(hex_str);
  printf("hex string: %s \n", hex_str);
  printf("b64 string: %s", convertHexToB64(hex_str, hex_str_len));
  return 0;
}
