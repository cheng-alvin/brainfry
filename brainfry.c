#include "instr.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file;

void error_callback(const char *msg) {
  fprintf(stderr, "%s: error: %s\n", file, msg);
  exit(1);
}

void *append(void *arr, size_t type_size, size_t *len, void *data,
             size_t data_size) {
  size_t new_len = *len + data_size / type_size;
  arr = realloc(arr, new_len * type_size);
  memcpy(arr + *len * type_size, data, data_size);
  *len = new_len;
  return arr;
}
static void compile(instruction_t **instr, size_t *len, char ch) {
  switch (ch) {
  case '>':
    *instr = append(*instr, sizeof(instruction_t), len, &next, sizeof(next));
    break;

  case '<':
    *instr = append(*instr, sizeof(instruction_t), len, &back, sizeof(back));
    break;

  case '+':
    *instr = append(*instr, sizeof(instruction_t), len, &plus, sizeof(plus));
    break;

  case '-':
    *instr = append(*instr, sizeof(instruction_t), len, &min, sizeof(min));
    break;

  case '.':
    *instr = append(*instr, sizeof(instruction_t), len, print, sizeof(print));
    break;

  case ',':
    *instr = append(*instr, sizeof(instruction_t), len, __in, sizeof(__in));
    break;

  default:
    break;
  }
}

int main(int argc, char **argv) {
  err_add_callback(error_callback);

  if (argc != 2) {
    fprintf(stderr, "%s: usage: %s <file>\n", argv[0], argv[0]);
    return 1;
  }

  file = argv[1];

  FILE *f = fopen(file, "r");
  if (!f) {
    fprintf(stderr, "%s: error: could not open file %s\n", argv[0], file);
    return 1;
  }

  char ch;

  instruction_t *instr = malloc(sizeof(instruction_t));

  size_t len = 1;
  instr = append(instr, sizeof(instruction_t), &len, start, sizeof(start));

  do {
    ch = fgetc(f);
    compile(&instr, &len, ch);
  } while (ch != EOF);

  instr = append(instr, sizeof(instruction_t), &len, __exit, sizeof(__exit));
  buffer_t buf =
      codegen(MODE_LONG, instr, len * sizeof(instruction_t), CODEGEN_ELF);

  FILE *file_out = fopen("main.o", "wb");
  size_t written = fwrite(buf.data, sizeof(uint8_t), buf.len, file_out);

  fclose(file_out);
  fclose(f);

  free(buf.data);
  free(instr);

  return 0;
}
