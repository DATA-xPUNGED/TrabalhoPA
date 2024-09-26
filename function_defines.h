#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct_defines.h"

#ifndef FUNCTION_DEFINES_H
#define FUNCTION_DEFINES_H

int g_estudante();
int g_professor();
int g_disciplina();
int g_turma();

int menu_principal() {
    int input = 0;
    printf("//-Gerenciamento de Escola-//\n");
    printf("Pressione o numero correspondente a opcao desejada.\n");
    printf("[1] Gestao de Estudantes\n");
    printf("[2] Gestao de Professores\n");
    printf("[3] Gestao de Disciplinas\n");
    printf("[4] Gestao de Turmas\n");
    printf("[5] Sair do Sistema\n");
    scanf("%d", &input);
    return input;
}

void adicionar_estudante();
void consultar_estudante();
void atualizar_estudante();
void remover_estudante();

int g_estudante(){
    int input;
    printf("[1] Adicionar Estudante\n");
    printf("[2] Consultar Estudante\n");
    printf("[3] Atualizar Estudante\n");
    printf("[4] Remover Estudante\n");
    printf("[5] Voltar\n");
    scanf("%d", &input);    
    switch(input)
    {
        case 1:
            adicionar_estudante();
            return 1;
            break;
        case 2:
            consultar_estudante();
            return 1;
            break;
        case 3:
            atualizar_estudante();
            return 1;
            break;
        case 4:
            remover_estudante();
            return 1;
            break;
        case 5:
            return 6;
            break;
        default:
            return 6;
            break;
    }
}

int id_existe(int id_procurado) {
    estudante estudante;
    int id = id_procurado;
    int total_estudantes;
    FILE *arq = fopen("estudantes.bin", "rb");
    if (arq == NULL){
        perror("Falha ao abrir o arquivo");
        return 0;
    }
    while (fread(&estudante, sizeof(estudante), 1, arq) == 1) {
        if(id == estudante.id)
            return 1;
    }
    fclose(arq);
    
    return 0;  // O ID nao existe
}


void adicionar_estudante(){
    FILE *arq;
    estudante novato;
    int input;
    printf("Insira o nome do estudante\n");
    scanf("%s", &novato.nome);
    printf("Insira o ID do estudante (precisa ser unico).\n");  
    scanf("%d", &novato.id);
    int id_anterior;
    while (id_existe(novato.id) == 1) {
        id_anterior = novato.id;
        if(novato.id == id_anterior) {
            printf("Insira OUTRO ID");
        }
        printf("Esse ID ja foi usado, tente outro!\n");
        scanf("%d", &novato.id);
    }  

    printf("Insira a data de nascimento do estudante, no formato DD MM AAAA\n");
    scanf("%d %d %d", &novato.nasc_dia, &novato.nasc_mes, &novato.nasc_ano);
    printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
    printf("Professor %s - ID: %d\n", novato.nome, novato.id);
    printf("Nascimento: %d/%d/%d\n", novato.nasc_dia, novato.nasc_mes, novato.nasc_ano);
    scanf("%d", &input);
    if(input == 1){
        arq = fopen("estudantes.bin", "ab");
        fwrite(&novato, sizeof(estudante), 1, arq);
        printf("O Professor foi salvo!");
        
    }
    fclose(arq);
}

void consultar_estudante(){
    int id;
    int encontrado = 0;
    estudante estudante;
    FILE *arq = fopen("estudantes.bin", "rb");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
    }

    printf("Insira o ID do estudante a ser pesquisado:");
    scanf("%d", &id);
    while (fread(&estudante, sizeof(estudante), 1, arq) == 1) {
        if(id == estudante.id){
            encontrado = 1;
            printf("Aluno %s - ID: %d\n", estudante.nome, estudante.id);
            printf("Nascimento: %d/%d/%d\n", estudante.nasc_dia, estudante.nasc_mes, estudante.nasc_ano);
            break;
        }
    }
    if(encontrado = 1){
        printf("Aluno com esse ID nao encontrado, listando todos\n");
        fseek(arq, 0, SEEK_SET);
        while(fread(&estudante, sizeof(estudante), 1, arq) == 1) {
            printf("Aluno: %s - ID: %d\n", estudante.nome, estudante.id);
            printf("Nascimento: %d/%d/%d\n", estudante.nasc_dia, estudante.nasc_mes, estudante.nasc_ano);
        }
    }
    fclose(arq);
}

void atualizar_estudante() {
    int id;
    estudante estudante;
    FILE *arq = fopen("estudantes.bin", "r+b");  // Abre o arquivo em modo de leitura e escrita binária

    // Verificação de abertura do arquivo
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Solicita o ID do estudante que o usuário deseja editar
    printf("Insira o ID do estudante que queira editar: ");
    scanf("%d", &id);

    // Variável para verificar se o estudante foi encontrado
    int encontrado = 0;

    // Ler os estudantes até encontrar o ID desejado
    while (fread(&estudante, sizeof(estudante), 1, arq) == 1) {
        if (id == estudante.id) {
            encontrado = 1;

            printf("Estudante encontrado: \n");
            printf("Aluno %s - ID: %d\n", estudante.nome, estudante.id);
            printf("Nascimento: %d/%d/%d\n", estudante.nasc_dia, estudante.nasc_mes, estudante.nasc_ano);
            printf("Insira o novo nome do estudante: ");
            getchar();  // Consumir o '\n' deixado pelo scanf anterior
            scanf("%s", &estudante.nome);
            estudante.nome[strcspn(estudante.nome, "\n")] = 0;  // Remove o '\n' do final da string

            printf("Insira o novo ID do estudante (precisa ser unico): ");
            scanf("%d", &estudante.id);

            // Verificar se o novo ID já existe
            while (id_existe(estudante.id)) {
                printf("Esse ID ja foi usado, tente outro!\n");
                scanf("%d", &estudante.id);
            }

            printf("Insira a nova data de nascimento do estudante (formato DD MM AAAA): ");
            scanf("%d %d %d", &estudante.nasc_dia, &estudante.nasc_mes, &estudante.nasc_ano);
            printf("Aqui estão os novos dados inseridos. esta tudo certo? 1 para sim, 2 para nao.\n");
            printf("Aluno: %s - ID: %d\n", estudante.nome, estudante.id);
            printf("Nascimento: %d/%d/%d\n", estudante.nasc_dia, estudante.nasc_mes, estudante.nasc_ano);

            char input;
            scanf("%d", &input);

            if (input == 1) {
                fseek(arq, -sizeof(estudante), SEEK_CUR);
                fwrite(&estudante, sizeof(estudante), 1, arq);
                printf("Os dados do estudante foram atualizados com sucesso!\n");
            } else {
                printf("A operação de atualização foi cancelada.\n");
            }
        }
    }

    if (!encontrado) {
        printf("Estudante com ID %d nao encontrado.\n", id);
        }
    

    fclose(arq);
}

void remover_estudante() {
    int id_procurado;
    printf("Insira o ID do aluno que queira remover.");
    scanf("%d", &id_procurado);
    FILE *arq = fopen("estudantes.bin", "rb");  // Abre o arquivo original para leitura
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo original");
        return;
    }

    FILE *arq_temp = fopen("temp.bin", "wb");  // Abre um arquivo temporário para escrita
    if (arq_temp == NULL) {
        perror("Erro ao abrir o arquivo temporário");
        fclose(arq);
        return;
    }

    estudante estudante;
    int encontrado = 0;

    // Ler os estudantes do arquivo original
    while (fread(&estudante, sizeof(estudante), 1, arq) == 1) {
        if (estudante.id == id_procurado) {
            // Se o ID for o procurado, nao copia para o arquivo temporário (remoção)
            printf("Estudante com ID %d removido.\n", estudante.id);
            encontrado = 1;
        } else {
            // Escreve o estudante no arquivo temporário se nao for o removido
            fwrite(&estudante, sizeof(estudante), 1, arq_temp);
        }
    }

    if (!encontrado) {
        printf("Estudante com ID %d nao encontrado.\n", id_procurado);
    }

    fclose(arq);
    fclose(arq_temp);

    if (remove("estudantes.bin") != 0) {
        perror("Erro ao remover o arquivo original");
        return;
    }

    if (rename("temp.bin", "estudantes.bin") != 0) {
        perror("Erro ao renomear o arquivo temporário");
        return;
    }

}

//PROFESSORES
void adicionar_professor();
void consultar_professor();
void atualizar_professor();
void remover_professor();

int g_professor(){
    int input;
    printf("[1] Adicionar professor\n");
    printf("[2] Consultar professor\n");
    printf("[3] Atualizar professor\n");
    printf("[4] Remover professor\n");
    printf("[5] Voltar\n");
    scanf("%d", &input);    
    switch(input)
    {
        case 1:
            adicionar_professor();
            return 2;
            break;
        case 2:
            consultar_professor();
            return 2;
            break;
        case 3:
            atualizar_professor();
            return 2;
            break;
        case 4:
            remover_professor();
            return 2;
            break;
        case 5:
            return 6;
            break;
        default:
            return 6;
            break;
    }
}

void adicionar_professor(){
    FILE *arq;
    FILE *arq_disc;
    professor novato;
    disciplina disciplina;
    int input;
    printf("Insira o nome do professor\n");
    scanf("%s", &novato.nome);
    printf("Insira o ID do professor (precisa ser unico).\n");  
    scanf("%d", &novato.id);
    int id_anterior;
    while (id_existe(novato.id) == 1) {
        id_anterior = novato.id;
        if(novato.id == id_anterior) {
            printf("Insira OUTRO ID");
        }
        printf("Esse ID ja foi usado, tente outro!\n");
        scanf("%d", &novato.id);
    }  
    char disc[64];

    
    printf("Insira a data de nascimento do professor, no formato DD MM AAAA\n");
    scanf("%d %d %d", &novato.nasc_dia, &novato.nasc_mes, &novato.nasc_ano);
    printf("Insira a disciplina que o professor trabalha\n");
    scanf("%s", &disc);
    arq_disc = fopen("disciplinas.bin", "rb");
    while(fread(&disciplina, sizeof(disciplina), 1, arq_disc)){
        if(novato.disciplina.nome == disc){
            novato.disciplina = disciplina;
        }else{
            printf("Disciplina invalida! Tente novamente.");
            return;
        }
    }
    printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
    printf("Professor %s - ID: %d\n", novato.nome, novato.id);
    printf("Nascimento: %d/%d/%d\n", novato.nasc_dia, novato.nasc_mes, novato.nasc_ano);
    scanf("%d", &input);
    if(input == 1){
        arq = fopen("professores.bin", "ab");
        fwrite(&novato, sizeof(professor), 1, arq);
        printf("O professor foi salvo!");
        
    }
    fclose(arq);
}

void consultar_professor(){
    int id;
    int encontrado = 0;
    professor professor;
    FILE *arq = fopen("professores.bin", "rb");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
    }

    printf("Insira o ID do professor a ser pesquisado:");
    scanf("%d", &id);
    while (fread(&professor, sizeof(professor), 1, arq) == 1) {
        if(id == professor.id){
            encontrado = 1;
            printf("Professor %s - ID: %d\n", professor.nome, professor.id);
            printf("Nascimento: %d/%d/%d\n", professor.nasc_dia, professor.nasc_mes, professor.nasc_ano);
            printf("Disciplina: %s", professor.disciplina.nome);
            break;
        }
    }
    if(encontrado = 0){
        printf("Professor com esse ID nao encontrado, listando todos\n");
        fseek(arq, 0, SEEK_SET);
        while(fread(&professor, sizeof(professor), 1, arq) == 1) {
            printf("Professor: %s - ID: %d\n", professor.nome, professor.id);
            printf("Nascimento: %d/%d/%d\n", professor.nasc_dia, professor.nasc_mes, professor.nasc_ano);
            printf("Disciplina: %s", professor.disciplina.nome);
        }
    }
    fclose(arq);
}

void atualizar_professor() {
    int id;
    professor professor;
    FILE *arq = fopen("professores.bin", "r+b");  // Abre o arquivo em modo de leitura e escrita binária

    // Verificação de abertura do arquivo
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Solicita o ID do professor que o usuário deseja editar
    printf("Insira o ID do professor que queira editar: ");
    scanf("%d", &id);

    // Variável para verificar se o professor foi encontrado
    int encontrado = 0;

    // Ler os professores até encontrar o ID desejado
    while (fread(&professor, sizeof(professor), 1, arq) == 1) {
        if (id == professor.id) {
            encontrado = 1;
            FILE *arq_disc;
            char disc[64];
            disciplina disciplina;

            printf("professor encontrado: \n");
            printf("Professor %s - ID: %d\n", professor.nome, professor.id);
            printf("Nascimento: %d/%d/%d\n", professor.nasc_dia, professor.nasc_mes, professor.nasc_ano);
            printf("Insira o novo nome do professor: ");
            getchar();  // Consumir o '\n' deixado pelo scanf anterior
            scanf("%s", &professor.nome);
            professor.nome[strcspn(professor.nome, "\n")] = 0;  // Remove o '\n' do final da string

            printf("Insira o novo ID do professor (precisa ser unico): ");
            scanf("%d", &professor.id);

            while (id_existe(professor.id)) {
                printf("Esse ID ja foi usado, tente outro!\n");
                scanf("%d", &professor.id);
            }

            printf("Insira a nova data de nascimento do professor (formato DD MM AAAA): ");
            scanf("%d %d %d", &professor.nasc_dia, &professor.nasc_mes, &professor.nasc_ano);
                printf("Insira a disciplina que o professor trabalha\n");
            scanf("%s", &disc);
            arq_disc = fopen("disciplinas.bin", "rb");
            while(fread(&disciplina, sizeof(disciplina), 1, arq_disc)){
                if(professor.disciplina.nome == disc){
                    professor.disciplina = disciplina;
                }else{
                    printf("Disciplina invalida! Tente novamente.");
                    return;
                }
            }
            printf("Aqui estão os novos dados inseridos. esta tudo certo? 1 para sim, 2 para nao.\n");
            printf("Professor: %s - ID: %d\n", professor.nome, professor.id);
            printf("Nascimento: %d/%d/%d\n", professor.nasc_dia, professor.nasc_mes, professor.nasc_ano);

            char input;
            scanf("%d", &input);

            if (input == 1) {
                fseek(arq, -sizeof(professor), SEEK_CUR);
                fwrite(&professor, sizeof(professor), 1, arq);
                printf("Os dados do professor foram atualizados com sucesso!\n");
            } else {
                printf("A operação de atualização foi cancelada.\n");
            }
        }
    }

    if (!encontrado) {
        printf("professor com ID %d nao encontrado.\n", id);
        }
    

    fclose(arq);
}

void remover_professor() {
    int id_procurado;
    printf("Insira o ID do Professor que queira remover.");
    scanf("%d", &id_procurado);
    FILE *arq = fopen("professores.bin", "rb");  // Abre o arquivo original para leitura
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo original");
        return;
    }

    FILE *arq_temp = fopen("temp.bin", "wb");  // Abre um arquivo temporário para escrita
    if (arq_temp == NULL) {
        perror("Erro ao abrir o arquivo temporário");
        fclose(arq);
        return;
    }

    professor professor;
    int encontrado = 0;

    // Ler os professores do arquivo original
    while (fread(&professor, sizeof(professor), 1, arq) == 1) {
        if (professor.id == id_procurado) {
            // Se o ID for o procurado, nao copia para o arquivo temporário (remoção)
            printf("professor com ID %d removido.\n", professor.id);
            encontrado = 1;
        } else {
            // Escreve o professor no arquivo temporário se nao for o removido
            fwrite(&professor, sizeof(professor), 1, arq_temp);
        }
    }

    if (!encontrado) {
        printf("professor com ID %d nao encontrado.\n", id_procurado);
    }
    fclose(arq);
    fclose(arq_temp);
    if (remove("professores.bin") != 0) {
        perror("Erro ao remover o arquivo original");
        return;
    }

    if (rename("temp.bin", "professores.bin") != 0) {
        perror("Erro ao renomear o arquivo temporário");
        return;
    }

}

void adicionar_disciplina();
void consultar_disciplina();
void atualizar_disciplina();
void remover_disciplina(); 

int g_disciplina(){
    int input;
    printf("[1] Adicionar disciplina\n");
    printf("[2] Consultar disciplina\n");
    printf("[3] Atualizar disciplina\n");
    printf("[4] Remover disciplina\n");
    printf("[5] Voltar\n");
    scanf("%d", &input);    
    switch(input)
    {
        case 1:
            adicionar_disciplina();
            return 3;
            break;
        case 2:
            consultar_disciplina();
            return 3;
            break;
        case 3:
            atualizar_disciplina();
            return 3;
            break;
        case 4:
            remover_disciplina();
            return 3;
            break;
        case 5:
            return 6;
            break;
        default:
            return 6;
            break;
    }
}

void adicionar_disciplina(){
    FILE *arq;
    disciplina disciplina;
    int input;
    printf("Insira o nome da disciplina\n");  
    scanf("%s", &disciplina.nome);

    printf("Insira o codigo da disciplina (precisa ser unico).\n");
    scanf("%s", &disciplina.codigo);
    int codigo_anterior;
    while (id_existe(disciplina.codigo) == 1) {
        codigo_anterior = disciplina.codigo;
        if(disciplina.codigo == codigo_anterior) {
            printf("Insira OUTRO codigo");
        }
        printf("Esse codigo ja foi usado, tente outro!\n");
        scanf("%d", &disciplina.codigo);
    }     
    printf("Insira o ID do professor que a ensina:\n");
    scanf("%d", &disciplina.id_professor);
    printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
    printf("Disciplina %s - codigo da disciplina: %d\n", disciplina.nome , disciplina.codigo);
    printf("ID do professor: %d\n", disciplina.id_professor);
    scanf("%d", &input);
    if(input == 1){
        arq = fopen("disciplinas.bin", "ab");
        fwrite(&disciplina, sizeof(disciplina), 1, arq);
        printf("A turma foi salva!");
        
    }
    fclose(arq);
}

void consultar_disciplina(){
    int codigo;
    int encontrado = 0;
    disciplina disciplina;
    FILE *arq = fopen("disciplinas.bin", "rb");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
    }

    printf("Insira o codigo da disciplina a ser pesquisada:\n");
    scanf("%d", &codigo);
    while (fread(&disciplina, sizeof(disciplina), 1, arq) == 1) {
        if(codigo == disciplina.codigo){
            encontrado = 1;
            printf("Disciplina %s - codigo da disciplina: %d\n", disciplina.nome , disciplina.codigo);
            printf("ID do professor: %d\n", disciplina.id_professor);
            break;
        }
    }
    if(encontrado = 1){
        printf("Disciplina com esse codigo nao encontrado, listando todas\n");
        fseek(arq, 0, SEEK_SET);
        while(fread(&disciplina, sizeof(disciplina), 1, arq) == 1) {
            printf("Disciplina %s - codigo da disciplina: %d\n", disciplina.nome , disciplina.codigo);
            printf("ID do professor: %d\n", disciplina.id_professor);
        }
    }
    fclose(arq);
}

void atualizar_disciplina() {
    int codigo;
    disciplina disciplina;
    FILE *arq = fopen("disciplinas.bin", "r+b");  // Abre o arquivo em modo de leitura e escrita binária

    // Verificação de abertura do arquivo
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Solicita o codigo do turma que o usuário deseja editar
    printf("Insira o codigo da disciplina que queira editar: ");
    scanf("%d", &codigo);

    // Variável para verificar se o disciplina foi encontrado
    int encontrado = 0;

    // Ler as disciplina até encontrar o codigo desejado
    while (fread(&disciplina, sizeof(disciplina), 1, arq) == 1) {
        if (codigo == disciplina.codigo) {
            encontrado = 1;

            printf("disciplina encontrada: \n");
            printf("disciplina %s - codigo: %d\n", disciplina.nome, disciplina.codigo);
            printf("ID do Professor: %d\n", disciplina.id_professor);
            printf("Insira o novo nome da disciplina\n");  
            scanf("%s", &disciplina.nome);
            printf("Insira o novo codigo da disciplina (precisa ser unico): \n");
            scanf("%d", &disciplina.codigo);

            // Verificar se o novo codigo já existe
            while (id_existe(disciplina.codigo)) {
                printf("Esse codigo ja foi usado, tente outro!\n");
                scanf("%d", &disciplina.codigo);
            }                   ;
            printf("Insira o novo ID do professor da disciplina");
            scanf("%d", &disciplina.id_professor);
            printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
            printf("Disciplina %s - codigo da disciplina: %d\n", disciplina.nome , disciplina.codigo);
            printf("ID do professor: %d\n", disciplina.id_professor);

            char input;
            scanf("%d", &input);

            if (input == 1) {
                fseek(arq, -sizeof(disciplina), SEEK_CUR);
                fwrite(&disciplina, sizeof(disciplina), 1, arq);
                printf("Os dados da disciplina foram atualizados com sucesso!\n");
            } else {
                printf("A operação de atualização foi cancelada.\n");
            }
        }
    }

    if (!encontrado) {
        printf("disciplina com codigo %d nao encontrado.\n", codigo);
        }
    

    fclose(arq);
}

void remover_disciplina() {
    int codigo_procurado;
    printf("Insira o codigo da disciplina que queira remover.");
    scanf("%d", &codigo_procurado);
    FILE *arq = fopen("disciplinas.bin", "rb");  // Abre o arquivo original para leitura
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo original");
        return;
    }

    FILE *arq_temp = fopen("temp.bin", "wb");  // Abre um arquivo temporário para escrita
    if (arq_temp == NULL) {
        perror("Erro ao abrir o arquivo temporário");
        fclose(arq);
        return;
    }

    disciplina disciplina;
    int encontrado = 0;

    // Ler as disciplinas do arquivo original
    while (fread(&disciplina, sizeof(disciplina), 1, arq) == 1) {
        if (disciplina.codigo == codigo_procurado) {
            // Se o codigo for o procurado, nao copia para o arquivo temporário (remoção)
            printf("disciplina %s com codigo %d removido.\n", disciplina.nome, disciplina.codigo);
            encontrado = 1;
        } else {
            // Escreve a disciplina no arquivo temporário se nao for o removcodigoo
            fwrite(&disciplina, sizeof(disciplina), 1, arq_temp);
        }
    }

    if (!encontrado) {
        printf("disciplina com codigo %d nao encontrado.\n", codigo_procurado);
    }
    fclose(arq);
    fclose(arq_temp);

if (remove("disciplinas.bin") != 0) {
    perror("Erro ao remover o arquivo original");
    return;
}

if (rename("temp.bin", "disciplinas.bin") != 0) {
    perror("Erro ao renomear o arquivo temporário");
    return;
}

}

void adicionar_turma();
void consultar_turma();
void atualizar_turma();
void remover_turma(); 

int g_turma(){
    int input;
    printf("[1] Adicionar turma\n");
    printf("[2] Consultar turma\n");
    printf("[3] Atualizar turma\n");
    printf("[4] Remover turma\n");
    printf("[5] Voltar\n");
    scanf("%d", &input);    
    switch(input)
    {
        case 1:
            adicionar_turma();
            return 4;
            break;
        case 2:
            consultar_turma();
            return 4;
            break;
        case 3:
            atualizar_turma();
            return 4;
            break;
        case 4:
            remover_turma();
            return 4;
            break;
        case 5:
            return 6;
            break;
        default:
            return 6;
            break;
    }
}

void adicionar_turma(){
    FILE *arq;
    turma turma;
    disciplina disciplina;
    int input;
    printf("Insira o codigo da turma (precisa ser unico).\n");
    scanf("%s", &turma.codigo);
    int codigo_anterior;
    while (id_existe(turma.codigo) == 1) {
        codigo_anterior = turma.codigo;
        if(turma.codigo == codigo_anterior) {
            printf("Insira OUTRO codigo");
        }
        printf("Esse codigo ja foi usado, tente outro!\n");
        scanf("%d", &turma.codigo);
    }     
    printf("Insira o codigo da disciplina\n");  
    scanf("%d", &turma.codigo_disciplina);

    int i= 0;
    int total;
    printf("Insira o ID do professor\n");
    scanf("%d", &turma.id_professor);
    printf("Insira quantos alunos a turma vai ter");
    scanf("%d", &total);
    for(i=0;i<total;i++)
    {
        printf("Insira o ID do aluno %d", i+1);
        scanf("%d", &turma.id_alunos[i]);
    }
    

    printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
    printf("Turma %s - codigo da disciplina: %d\n", turma.codigo , turma.codigo_disciplina);
    printf("ID do professor: %d ID dos Alunos: %d\n", turma.id_professor, turma.id_alunos);
    scanf("%d", &input);
    if(input == 1){
        arq = fopen("turmas.bin", "ab");
        fwrite(&turma, sizeof(disciplina), 1, arq);
        printf("A turma foi salva!");
        
    }
    fclose(arq);
}

void consultar_turma(){
    int codigo;
    int encontrado = 0;
    turma turma;
    FILE *arq = fopen("turmas.bin", "rb");
    if (arq == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
    }

    printf("Insira o codigo da turma a ser pesquisada:\n");
    scanf("%d", &codigo);
    while (fread(&turma, sizeof(turma), 1, arq) == 1) {
        if(codigo == turma.codigo){
            encontrado = 1;
            printf("Turma %s - codigo da disciplina: %d\n", turma.codigo , turma.codigo_disciplina);
            printf("ID do professor: %d ID dos Alunos: %d\n", turma.id_professor, turma.id_alunos);
            break;
        }
    }
    if(encontrado = 1){
        printf("Turma com esse codigo nao encontrado, listando todos\n");
        fseek(arq, 0, SEEK_SET);
        while(fread(&turma, sizeof(turma), 1, arq) == 1) {
            printf("Turma %s - codigo da disciplina: %d\n", turma.codigo , turma.codigo_disciplina);
            printf("ID do professor: %d ID dos Alunos: %d\n", turma.id_professor, turma.id_alunos);
        }
    }
    fclose(arq);
}

void atualizar_turma() {
    int codigo;
    turma turma;
    FILE *arq = fopen("turmas.bin", "r+b");  // Abre o arquivo em modo de leitura e escrita binária

    // Verificação de abertura do arquivo
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Solicita o codigo do turma que o usuário deseja editar
    printf("Insira o codigo do turma que queira editar: ");
    scanf("%d", &codigo);

    // Variável para verificar se o disciplina foi encontrado
    int encontrado = 0;

    // Ler os turmas até encontrar o codigo desejado
    while (fread(&turma, sizeof(turma), 1, arq) == 1) {
        if (codigo == turma.codigo) {
            encontrado = 1;

            printf("turma encontrado: \n");
            printf("turma %s - codigo: %d\n", turma.codigo, turma.codigo_disciplina);
            printf("ID do Professor: %d\n", turma.id_professor);
            printf("Insira o novo codigo da turma (precisa ser unico): ");
            scanf("%d", &turma.codigo);

            // Verificar se o novo codigo já existe
            while (id_existe(turma.codigo)) {
                printf("Esse codigo ja foi usado, tente outro!\n");
                scanf("%d", &turma.codigo);
            }            
            printf("Insira o novo codigo da disciplina da turma:");
            scanf("%d", &turma.codigo_disciplina)           ;
            printf("Insira o novo ID do professor da turma");
            scanf("%d", &turma.id_professor);
            int i;
            int total;
            printf("Insira quantos alunos a turma vai ter");
            scanf("%d", &total);
            for(i=0;i<total;i++)
            {
                printf("Insira o ID do aluno %d", i+1);
                scanf("%d", &turma.id_alunos[i]);
            }
            printf("Aqui estao os dados inseridos, esta tudo certo? 1 para sim, 2 para nao.\n");
            printf("Turma %s - codigo da disciplina: %d\n", turma.codigo , turma.codigo_disciplina);
            printf("ID do professor: %d ID dos Alunos: %d\n", turma.id_professor, turma.id_alunos);

            char input;
            scanf("%d", &input);

            if (input == 1) {
                fseek(arq, -sizeof(turma), SEEK_CUR);
                fwrite(&turma, sizeof(turma), 1, arq);
                printf("Os dados da turma foram atualizados com sucesso!\n");
            } else {
                printf("A operação de atualização foi cancelada.\n");
            }
        }
    }

    if (!encontrado) {
        printf("turma com codigo %d nao encontrado.\n", codigo);
        }
    

    fclose(arq);
}

void remover_turma() {
    int codigo_procurado;
    printf("Insira o codigo do aluno que queira remover.");
    scanf("%d", &codigo_procurado);
    FILE *arq = fopen("turmas.bin", "rb");  // Abre o arquivo original para leitura
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo original");
        return;
    }

    FILE *arq_temp = fopen("temp.bin", "wb");  // Abre um arquivo temporário para escrita
    if (arq_temp == NULL) {
        perror("Erro ao abrir o arquivo temporário");
        fclose(arq);
        return;
    }

    turma turma;
    int encontrado = 0;

    // Ler os turmas do arquivo original
    while (fread(&turma, sizeof(turma), 1, arq) == 1) {
        if (turma.codigo == codigo_procurado) {
            // Se o codigo for o procurado, nao copia para o arquivo temporário (remoção)
            printf("turma com codigo %d removido.\n", turma.codigo);
            encontrado = 1;
        } else {
            // Escreve o turma no arquivo temporário se nao for o removcodigoo
            fwrite(&turma, sizeof(turma), 1, arq_temp);
        }
    }

    if (!encontrado) {
        printf("turma com codigo %d nao encontrado.\n", codigo_procurado);
    }
    fclose(arq);
    fclose(arq_temp);

    if (remove("turmas.bin") != 0) {
        perror("Erro ao remover o arquivo original");
        return;
    }

    if (rename("temp.bin", "turmas.bin") != 0) {
        perror("Erro ao renomear o arquivo temporário");
        return;
    }

}

#endif