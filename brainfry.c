#include "instr.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *file;

void error_callback(const char *msg) {
  fprintf(stderr, "%s: error: %s\n", file, msg);
  exit(1);
}

static void *append(void *arr, size_t type_size, size_t *len, void *data,
                    size_t data_size) {
  size_t new_len = *len + data_size / type_size;
  arr = realloc(arr, new_len * type_size);
  memcpy(arr + *len * type_size, data, data_size);
  *len = new_len;
  return arr;
}

// clang-format off
static void compile(instruction_t **instr, size_t *len, char ch) {
  #define DEF_INSTR(in)                                                          \
   append(*instr, sizeof(instruction_t), len, &in, sizeof(in))

  switch (ch) {
  case '>': *instr = DEF_INSTR(next); break;
  case '<': *instr = DEF_INSTR(back); break;
  case '+': *instr = DEF_INSTR(plus); break;
  case '-': *instr = DEF_INSTR(min); break;
  case '.': *instr = DEF_INSTR(print); break;
  case ',': *instr = DEF_INSTR(__in); break;

  default:
    break;
  }
}
#undef DEF_INSTR // Preventing clashes
// clang-format on

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

  size_t len = 0;
  instr = append(instr, sizeof(instruction_t), &len, start, sizeof(start));

  do {
    ch = fgetc(f);
    compile(&instr, &len, ch);
  } while (ch != EOF);
  fclose(f);

  instr = append(instr, sizeof(instruction_t), &len, __exit, sizeof(__exit));

  instruction_t **arr = malloc(sizeof(instruction_t *) * len);
  for (size_t k = 0; k < len; k++)
    arr[k] = &instr[k];

  buffer_t buf = codegen(MODE_LONG, arr, len, CODEGEN_ELF);
  free(instr);

  for (size_t i = sizeof(file); i > 0; i--) {
    if (file[i] == '.') {
      file[i] = '\0';
      break;
    }
  }
  strcat(file, ".o");

  FILE *file_out = fopen(file, "wb");
  size_t written = fwrite(buf.data, sizeof(uint8_t), buf.len, file_out);
  fclose(file_out);

  free(buf.data);

  return 0;
}
