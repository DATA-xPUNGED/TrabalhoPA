#include <stdlib.h>
#include <stdio.h>
#include "struct_defines.h"
#include "function_defines.h"

int main(){
    int input = menu_principal();
    while(1 == 1){
        switch (input)
        {
        case 1:
            input = g_estudante();
            break;

        case 2:
            input = g_professor();
            break;

        case 3:
            input = g_disciplina();
            break;

        case 4:
            input = g_turma();
            break;

        case 5:
            exit(0);
            break;

        case 6:
            input = menu_principal();
            break;
        }
    }
    return 0;
}