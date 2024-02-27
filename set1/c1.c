// Convert hex to base64
#include "encodeDecode.c"

int main(int argc, char* argv[]) {
  char* hex_str = argv[1];
  size_t hex_str_len = strlen(hex_str);
  printf("hex string: %s \n", hex_str);
  printf("b64 string: %s", convertHexToB64(hex_str, hex_str_len));
  return 0;
}
