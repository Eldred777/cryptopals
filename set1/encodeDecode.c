#ifndef ENCODE_DECODE
#define ENCODE_DECODE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------
// ----- DECODERS
// -------------------------

int decodeHexChar(char hex) {
  if ('0' <= hex && hex <= '9') {
    return hex - '0';
  } else if ('a' <= hex && hex <= 'f') {
    return hex - 'a' + 10;
  } else {
    return -1;
  }
}

int decodeHexStr(char* hex_str, size_t hex_str_len) {
  int acc = 0;
  int mantissa = 1;  // keep track of power of 16
  // to base 10
  for (size_t i = hex_str_len - 1; i < hex_str_len; i--) {
    // < because underflow
    acc += decodeHexChar(hex_str[i]) * mantissa;
    mantissa *= 16;
  }
  return acc;
}

// -------------------------
// ----- SINGLE CHARACTER ENCODERS
// -------------------------

char encodeSingleHex(int dec) {
  if (dec < 10) {
    return dec + '0';
  } else if (dec < 16) {
    return dec + 'a' - 10;
  } else {
    printf("error in `encodeSingleHex` %d", dec);
    exit(1);
  }
}

// Convert a decimal x satisfying 0<=x<=63 to a base 64 encoded character.
char encodeSingleB64(int dec) {
  const int NUM_DIGITS = 10;
  const int ALPHABET_LENGTH = 26;

  if (dec < ALPHABET_LENGTH) {
    return dec + 'A';
  } else if (dec < 2 * ALPHABET_LENGTH) {
    return dec + 'a' - ALPHABET_LENGTH;
  } else if (dec < 2 * ALPHABET_LENGTH + NUM_DIGITS) {
    return dec + '0' - 2 * ALPHABET_LENGTH;
  } else {
    printf("error in `encodeSingleB64` %d", dec);
    exit(1);
  }
  // TODO maybe need more characters?
}

// -------------------------
// ----- ENCODERS
// -------------------------

// TODO: test
char* encodeHex(int dec) {
  // Find the most significant bit `msb`
  int x = dec;
  int msb = 0;
  while (x >>= 1) {
    msb++;
  }
  int hex_str_len = msb / 4 + 1;
  char* hex_str = malloc(hex_str_len * sizeof(char) + 1);
  assert(hex_str);
  hex_str[hex_str_len] = '\0';

  size_t hex_idx = hex_str_len - 1;  // index the hex string
  while (hex_idx < hex_str_len) {
    // TODO: this is copy pasted, not working
    const int r = dec % 16;
    dec /= 16;
    hex_str[hex_idx + 1] = encodeSingleHex(r);
    hex_idx--;
  }
  return hex_str;
}

// -------------------------
// ----- TRANSCODERS
// -------------------------

// for set 1 challenge 1
char* convertHexToB64(char* hex_str, size_t hex_str_len) {
  assert(!(hex_str_len % 3));  // Precondition: `hex_str_len` divisible by 3.
  // 3 hex chars = 2 b64 chars
  int b64_str_len = hex_str_len * 2 / 3;
  char* b64_str = malloc(b64_str_len * sizeof(char) + 1);
  assert(b64_str);
  b64_str[b64_str_len] = '\0';

  int hex_idx = 0;  // index the hex string
  int b64_idx = 0;
  while (hex_idx < hex_str_len) {
    const int dec = decodeHexStr(hex_str + hex_idx, 3);
    const int q = dec / 64;  // quotient, 10's place of b64
    const int r = dec % 64;  // remainder
    b64_str[b64_idx] = encodeSingleB64(q);
    b64_str[b64_idx + 1] = encodeSingleB64(r);
    hex_idx += 3;
    b64_idx += 2;
  }
  return b64_str;
}

#endif