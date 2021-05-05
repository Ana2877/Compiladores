//
#include "asm.h"

void generate_ASM(TAC* first)
{
    TAC* tac;

    FILE *fout;
    fout = fopen("out.s", "w");

    // Init
    fprintf(fout, "# Data\n");
    fprintf(fout, ".section	.rodata\n");
    fprintf(fout, ".globl	main\n");
    fprintf(fout, ".print_int_string:\n");
    fprintf(fout, "\t.string	\"%%d\\n\"\n\n");
    fprintf(fout, ".print_char_string:\n");
    fprintf(fout, "\t.string	\"%%c\\n\"\n\n");
    fprintf(fout, ".print_float_string:\n");
    fprintf(fout, "\t.string	\"%%f\\n\"\n\n");
    fprintf(fout, ".print_string:\n");
    fprintf(fout, "\t.string	\"%%s\\n\"\n\n");

    // Each TAC
    for (tac = first; tac; tac = tac->next)
    {
        switch (tac->type)
        {
            case TAC_BEGINFUN:
                fprintf(fout, "%s:\n", tac->res->text);
                fprintf(fout, "\tpushq	%%rbp\n");
                fprintf(fout, "\tmovq	%%rsp, %%rbp\n\n");
                break;

            case TAC_ENDFUN:
                fprintf(fout, "\tpopq	%%rbp\n");
                fprintf(fout, "\tret\n");
                break;
        }
    }
}
