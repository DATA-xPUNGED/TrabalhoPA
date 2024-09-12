#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FUNCTION_DEFINES_H
#define FUNCTION_DEFINES_H

void g_estudante();
void g_professor();
void g_disciplina();
void g_turma();

void g_estudante(){
    printf("teste");
}
void g_professor(){
    printf("teste");
}
void g_disciplina(){
    printf("teste");
}
void g_turma(){
    printf("teste");
}

void menu_principal(FILE* arquivo) {
    int input;
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
        g_professor();
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
        menu_principal(arquivo);
        break;
    }
}

#endif