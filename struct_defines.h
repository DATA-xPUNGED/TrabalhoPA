#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCT_DEFINES_H
#define STRUCT_DEFINES_H

//instanciando as struct logo aqui pra eu não ter que mexer na ordem delas no código - Arthur
struct estudante;
struct professor;
struct disciplina;
struct turma;

struct estudante {
    int id;
    char nome[64];
    int nasc_ano;
    int nasc_mes;
    int nasc_dia;
};

struct professor {
    int id;
    char nome[64];
    int nasc_ano;
    int nasc_mes;
    int nasc_dia;
    disciplina disciplina;
};

struct disciplina {
    int codigo;
    char nome[64];
    int id_professor;
};

struct turma {
    int codigo;
    int codigo_disciplina;
    int id_professor;
    int id_alunos[64];
};

typedef struct estudante estudante;
typedef struct professor professor;
typedef struct disciplina disciplina;
typedef struct turma turma;

#endif