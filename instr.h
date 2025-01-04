#include "libs/libjas/include/jas.h"

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

instruction_t __exit[] = (instruction_t[]){
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
                    .data = &(enum registers){REG_RDI},
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
                    .data = &(enum registers){REG_RSI},
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

instruction_t __in[] = (instruction_t[]){
    (instruction_t){
        .instr = INSTR_XOR,
        .operands =
            (operand_t[]){
                (operand_t){
                    .type = OP_R64,
                    .data = &(enum registers){REG_RAX},
                },
                (operand_t){
                    .type = OP_R64,
                    .data = &(enum registers){REG_RAX},
                },
                OP_NONE,
                OP_NONE,
            },
    },
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
    (instruction_t){
        .instr = INSTR_MOV,
        .operands =
            (operand_t[]){
                (operand_t){
                    .type = OP_R64,
                    .data = &(enum registers){REG_RSI},
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