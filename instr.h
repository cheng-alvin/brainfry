#include "libs/libjas/include/jas.h"

instr_generic_t start[] = {(instr_generic_t){
    .type = DIRECTIVE,
    .dir =
        {
            .dir = DIR_DEFINE_LABEL,
            .label =
                (label_t){
                    .name = "start",
                    .exported = true,
                    .ext = false,
                    .address = 0,
                },
        },
}};

instr_generic_t __exit[] = {
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RAX}},
                        {.type = OP_IMM64, .data = &(uint64_t){60}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_XOR,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RDI}},
                        {.type = OP_R64, .data = &(enum registers){REG_RDI}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_SYSCALL,
                .operands = (operand_t[]){OP_NONE, OP_NONE, OP_NONE, OP_NONE},
            },
    },
};

instr_generic_t min[] = {{
    .type = INSTR,
    .instr =
        {
            .instr = INSTR_SUB,
            .operands =
                (operand_t[]){
                    {.type = OP_M64,
                     .data = &(enum registers){REG_RSP},
                     .offset = 0},
                    {.type = OP_IMM32, .data = &(uint32_t){1}},
                    OP_NONE,
                    OP_NONE,
                },
        },
}};

instr_generic_t next[] = {{
    .type = INSTR,
    .instr =
        {
            .instr = INSTR_SUB,
            .operands =
                (operand_t[]){
                    {.type = OP_R64, .data = &(enum registers){REG_RSP}},
                    {.type = OP_IMM32, .data = &(uint32_t){1}},
                    OP_NONE,
                    OP_NONE,
                },
        },
}};

instr_generic_t back[] = {{
    .type = INSTR,
    .instr =
        {
            .instr = INSTR_ADD,
            .operands =
                (operand_t[]){
                    {.type = OP_R64, .data = &(enum registers){REG_RSP}},
                    {.type = OP_IMM32, .data = &(uint32_t){1}},
                    OP_NONE,
                    OP_NONE,
                },
        },
}};

instr_generic_t plus[] = {{
    .type = INSTR,
    .instr =
        {
            .instr = INSTR_ADD,
            .operands =
                (operand_t[]){
                    {.type = OP_M64,
                     .data = &(enum registers){REG_RSP},
                     .offset = 0},
                    {.type = OP_IMM32, .data = &(uint32_t){1}},
                    OP_NONE,
                    OP_NONE,
                },
        },
}};

instr_generic_t print[] = {
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RDI}},
                        {.type = OP_IMM64, .data = &(uint64_t){1}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RSI}},
                        {.type = OP_R64, .data = &(enum registers){REG_RSP}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RAX}},
                        {.type = OP_IMM64, .data = &(uint64_t){1}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RDX}},
                        {.type = OP_IMM64, .data = &(uint64_t){1}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_SYSCALL,
                .operands = (operand_t[]){OP_NONE, OP_NONE, OP_NONE, OP_NONE},
            },
    },
};

instr_generic_t __in[] = {
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_XOR,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RAX}},
                        {.type = OP_R64, .data = &(enum registers){REG_RAX}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_XOR,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RDI}},
                        {.type = OP_R64, .data = &(enum registers){REG_RDI}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RSI}},
                        {.type = OP_R64, .data = &(enum registers){REG_RSP}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_MOV,
                .operands =
                    (operand_t[]){
                        {.type = OP_R64, .data = &(enum registers){REG_RDX}},
                        {.type = OP_IMM64, .data = &(uint64_t){1}},
                        OP_NONE,
                        OP_NONE,
                    },
            },
    },
    {
        .type = INSTR,
        .instr =
            {
                .instr = INSTR_SYSCALL,
                .operands = (operand_t[]){OP_NONE, OP_NONE, OP_NONE, OP_NONE},
            },
    },
};
