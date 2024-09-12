#include <stdlib.h>
#include <stdio.h>
#include "struct_defines.h"
#include "function_defines.h"

int main(){

    FILE *arq;
    arq = fopen("dados.bin", "rb");
    if (arq == NULL) {
        printf("Erro ao ler o arquivo.");
        exit(1);
    }
    estudante l_estudante[20];
    professor l_professor[10];
    disciplina l_disciplina[10];
    turma l_turma[10];

    fread(l_estudante, sizeof(l_estudante), 1, arq);
    fread(l_professor, sizeof(l_professor), 1, arq);
    fread(l_disciplina, sizeof(l_disciplina), 1, arq);
    fread(l_turma, sizeof(l_turma), 1, arq);
    fclose(arq);
    
    arq = fopen("dados.bin", "wb");
    menu_principal(arq);


    fwrite(l_estudante, sizeof(l_estudante), 1, arq);
    fwrite(l_professor, sizeof(l_professor), 1, arq);
    fwrite(l_disciplina, sizeof(l_disciplina), 1, arq);
    fwrite(l_turma, sizeof(l_turma), 1, arq);

    fclose(arq);
    return 0;
}