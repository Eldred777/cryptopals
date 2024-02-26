//  Fixed XOR

#include <string.h>
#include "encodeDecode.c"

char* xorHexTogether(char* str1, char* str2, size_t len) {
  char* out = malloc(len + 1);
  assert(out);
  out[len] = '\0';

  for (size_t i = 0; i < len; i++) {
    out[i] = encodeSingleHex(decodeHexChar(str1[i]) ^ decodeHexChar(str2[i]));
  }
  return out;
}

int main(int argc, char const* argv[]) {
  char* hex_str = argv[1];
  size_t hex_str_len = strlen(hex_str);
  char* xor_str = argv[2];
  size_t xor_str_len = strlen(xor_str);
  assert(hex_str_len == xor_str_len);
  printf("XOR: %s", xorHexTogether(hex_str, xor_str, hex_str_len));
  return 0;
}
