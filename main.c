#include <stdlib.h>
#include <stdio.h>
#include <struct_defines.c>
#include <function_define.c>

int main(){
    int input;
    FILE* arq;
    arq = fopen("..\\dados.bin", "w+");
    printf("-=Gerenciamento de Escola=-\n");
    printf("Pressione o número correspondente a opção desejada.\n");
    printf("[1] Gestão de Estudantes\n");
    printf("[2] Gestão de Professores\n");
    printf("[3] Gestão de Disciplinas\n");
    printf("[4] Gestão de Turmas\n");
    printf("[5] Sair do Sistema\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        g_estudante();
        break;
    
    case 2:
        g_professore();
        break;
    
    case 3:
        g_disciplina();
        break;
    
    case 4:
        g_turma();
        break;
    
    case 5:
        exit(0);
        break;
    
    default:
        menu_principal(arq);
        break;
    }
    fclose("..\\dados.bin");
    return 0;
}