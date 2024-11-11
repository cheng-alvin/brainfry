#include <jas.h>
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
  size_t len = 1;

  instruction_t *instr = malloc(sizeof(instruction_t));
  instruction_t start[] = (instruction_t[]){
      // global _start:
      (instruction_t){
          .instr = INSTR_DIR_GLOBAL_LABEL,
          .operands =
              (operand_t[]){
                  (operand_t){.type = OP_MISC, .data = "_start"},
                  OP_NONE,
                  OP_NONE,
                  OP_NONE,
              },
      },
  };

  instruction_t exit[] = (instruction_t[]){
      // mov rax, 60
      (instruction_t){
          .instr = INSTR_MOV,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RAX},
                  },
                  (operand_t){
                      .type = OP_IMM64,
                      .data = &(uint64_t){60},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },
      // xor rdi, rdi
      (instruction_t){
          .instr = INSTR_XOR,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RDI},
                  },
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RDI},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },
      // syscall
      (instruction_t){
          .instr = INSTR_SYSCALL,
          .operands =
              (operand_t[]){
                  OP_NONE,
                  OP_NONE,
                  OP_NONE,
                  OP_NONE,
              },
      },
  };

  instruction_t min = (instruction_t){
      .instr = INSTR_SUB,
      .operands =
          (operand_t[]){
              (operand_t){
                  .type = OP_M64,
                  .data = &(enum registers){REG_RSP},
                  .offset = 0,
              },
              (operand_t){
                  .type = OP_IMM32,
                  .data = &(uint32_t){1},
              },
              OP_NONE,
              OP_NONE,
          },
  };
  instruction_t next = (instruction_t){
      .instr = INSTR_SUB,
      .operands =
          (operand_t[]){
              (operand_t){
                  .type = OP_R64,
                  .data = &(enum registers){REG_RSP},
              },
              (operand_t){
                  .type = OP_IMM32,
                  .data = &(uint32_t){1},
              },
              OP_NONE,
              OP_NONE,
          },
  };
  instruction_t back = (instruction_t){
      .instr = INSTR_ADD,
      .operands =
          (operand_t[]){
              (operand_t){
                  .type = OP_R64,
                  .data = &(enum registers){REG_RSP},
              },
              (operand_t){
                  .type = OP_IMM32,
                  .data = &(uint32_t){1},
              },
              OP_NONE,
              OP_NONE,
          },
  };
  instruction_t plus = (instruction_t){
      .instr = INSTR_ADD,
      .operands =
          (operand_t[]){
              (operand_t){
                  .type = OP_M64,
                  .data = &(enum registers){REG_RSP},
                  .offset = 0,
              },
              (operand_t){
                  .type = OP_IMM32,
                  .data = &(uint32_t){1},
              },
              OP_NONE,
              OP_NONE,
          },
  };

  instruction_t print[] = (instruction_t[]){
      (instruction_t){
          .instr = INSTR_MOV,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RDX},
                  },
                  (operand_t){
                      .type = OP_IMM64,
                      .data = &(uint64_t){1},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },

      (instruction_t){
          .instr = INSTR_MOV,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RCX},
                  },
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RSP},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },

      (instruction_t){
          .instr = INSTR_MOV,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RAX},
                  },
                  (operand_t){
                      .type = OP_IMM64,
                      .data = &(uint64_t){4},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },

      (instruction_t){
          .instr = INSTR_MOV,
          .operands =
              (operand_t[]){
                  (operand_t){
                      .type = OP_R64,
                      .data = &(enum registers){REG_RBX},
                  },
                  (operand_t){
                      .type = OP_IMM64,
                      .data = &(uint64_t){1},
                  },
                  OP_NONE,
                  OP_NONE,
              },
      },
      (instruction_t){
          .instr = INSTR_SYSCALL,
          .operands =
              (operand_t[]){
                  OP_NONE,
                  OP_NONE,
                  OP_NONE,
                  OP_NONE,
              },
      },
  };

  instr = append(instr, sizeof(instruction_t), &len, start, sizeof(start));

  do {
    ch = fgetc(f);
    switch (ch) {
    case '>':
      instr = append(instr, sizeof(instruction_t), &len, &next, sizeof(next));
      break;

    case '<':
      instr = append(instr, sizeof(instruction_t), &len, &back, sizeof(back));
      break;

    case '+':
      instr = append(instr, sizeof(instruction_t), &len, &plus, sizeof(plus));
      break;

    case '-':
      instr = append(instr, sizeof(instruction_t), &len, &min, sizeof(min));
      break;

    case '.':
      instr = append(instr, sizeof(instruction_t), &len, print, sizeof(print));
      break;

    case ',':
      break;

    default:
      break;
    }

  } while (ch != EOF);

  instr = append(instr, sizeof(instruction_t), &len, exit, sizeof(exit));
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
