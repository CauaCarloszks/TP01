#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Alunos_Max 95
#define Nome_Max 50
#define Curso_Max 50

// informações do arquivo DadosEntrada em struct
typedef struct
{
    char nome[Nome_Max];
    char telefone[20];
    char curso[Curso_Max];
    float notas[2];
} Inscrito;

float calculaMedia(float notas[], float num_notas)
{
    float media = 0;
    for (int i = 0; i < num_notas; i++)
    {
        // Aqui o array vai se somando até prencher
        media += notas[i];
    }
    return media / num_notas;
}

// Utilizado essa função para retirar a necessidade de criar uma copia a cada loop
char *resultadoMedia(float media)
{
    return media >= 7.0 ? "APROVADO" : "REPROVADO";
}

int main()
{
    int alunos_qtd = 0;
    Inscrito inscritos[Alunos_Max];
    FILE *planilhaEntrada, *planilhaSaida;

    planilhaEntrada = fopen("DadosEntrada.csv", "r");
    planilhaSaida = fopen("SituacaoFinal.csv", "w");

    if (planilhaEntrada == NULL || planilhaSaida == NULL)
    {
        printf("Erro ao encontrar o arquivo! Codigo 13");
        return 13;
    }

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), planilhaEntrada);

    // While para o arquivo entrada ser lido e armazenado.
    while (alunos_qtd < Alunos_Max && fscanf(planilhaEntrada, "%49[^,],%19[^,],%49[^,],%f,%f\n", inscritos[alunos_qtd].nome, inscritos[alunos_qtd].telefone, inscritos[alunos_qtd].curso, &inscritos[alunos_qtd].notas[0], &inscritos[alunos_qtd].notas[1]) == 5)
    {
        alunos_qtd++;
    }

    fprintf(planilhaSaida, "Nome,Nota Media,Situação\n");
    
    // for para ir preenchendo a cada loop a situação do aluno
    for (int i = 0; i < alunos_qtd; i++)
    {
        float media = calculaMedia(inscritos[i].notas, 2);
        char *resultado = resultadoMedia(media);
        fprintf(planilhaSaida, "%s,%.2f,%s\n", inscritos[i].nome, media, resultado);
    }

    printf("Criado arquivo de saida chamado situacaoFinal.csv!");

    fclose(planilhaEntrada);
    fclose(planilhaSaida);

    return 0;
}