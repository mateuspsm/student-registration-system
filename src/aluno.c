#include "../include/aluno.h"
#define TAM 100
#define EXPR_REG_NOME "[A-z]{3,20}\\s[A-z]{2,20}"
#define EXPR_REG_DISCIPLINA "[A-z]{5,20}\\s[A-z]{2,20}|[A-z]{2,20}"
#define EXPR_REG_CPF "[0-9]{11}|[0-9]{3}.[0-9]{3}.[0-9]{3}-[0-9]{2}"

struct _aluno
{
    int codigo;
    char nome[TAM], cpf[TAM], disciplina[TAM];
    float notas[3];
};

//Variable Global Struct.
struct _aluno aluno;

void validaNome(char nome[])
{
    regex_t reg;
    int result;

    if (regcomp(&reg, EXPR_REG_NOME, REG_EXTENDED | REG_NOSUB) != 0)
    {
        printf("\t\t\tExpressao regular invalida!\n");
        return 1;
    }
    else
    {
        do
        {
            printf("\n\t\t\tDigite o nome e sobrenome do aluno: ");
            __fpurge(stdin);
            gets(nome);

            if ((regexec(&reg, nome, 0, (regmatch_t *)NULL, 0)) == 0)
            {
                printf("\t\t\tNome valido\n");
                result = 0;
            }
            else
            {
                printf("\t\t\tNome invalido\n");
                result = 1;
                printf("\t\t\tValor: [%d]\n", result);
            }
        } while (result == 1);
    }
}

void validaCpf(char cpf[])
{
    regex_t reg;
    int result;

    if (regcomp(&reg, EXPR_REG_CPF, REG_EXTENDED | REG_NOSUB) != 0)
    {
        printf("\t\t\tExpressao regular invalida!\n");
        return 1;
    }
    else
    {
        do
        {
            printf("\n\t\t\tDigite o CPF do aluno: ");
            __fpurge(stdin);
            gets(cpf);

            if ((regexec(&reg, cpf, 0, (regmatch_t *)NULL, 0)) == 0)
            {
                printf("\t\t\tCPF válido.\n");
                result = 0;
            }
            else
            {
                printf("\t\t\tCPF inválido.\n");
                result = 1;
            }
        } while (result == 1);
    }
}

void validaDisciplina(char nome[])
{
    regex_t reg;
    int result;

    if (regcomp(&reg, EXPR_REG_DISCIPLINA, REG_EXTENDED | REG_NOSUB) != 0)
    {
        printf("\t\t\tExpressao regular invalida!\n");
        return 1;
    }
    else
    {
        do
        {
            printf("\n\t\t\tDigite o nome da disciplina do aluno: ");
            __fpurge(stdin);
            gets(nome);

            if ((regexec(&reg, nome, 0, (regmatch_t *)NULL, 0)) == 0)
            {
                printf("\t\t\tDisciplina válida.\n");
                result = 0;
            }
            else
            {
                printf("\t\t\tDisciplina invalido.\n");
                result = 1;
            }
        } while (result == 1);
    }
}

float validarNotas(int i)
{
    float nota = 0;
    do
    {
        printf("\t\t\tDigite a sua [%d]ª nota: ", i + 1);
        scanf("%f", &nota);
        if (nota < 0 || nota > 10)
            printf("\t\t\tNota inválida!\n");
        else
            return nota;
    } while (nota < 0 || nota > 10);
    return nota;
}

void acrescentarDados()
{
    FILE *arq = fopen("files/aluno.dat", "ab");
    FILE *cpy = fopen("files/aluno.txt", "a");
    char tecla;
    int i, cont;

    if (arq == NULL && cpy == NULL)
        printf("O arquivo não pode ser aberto.");
    else
    {
        cabecalho("CADASTRO DE ALUNOS");
        cont = countInd(aluno);
        printf("\n\t\t\tCódigo do cadastro - %d", cont);
        do
        {
            aluno.codigo = cont;
            validaNome(aluno.nome);
            validaCpf(aluno.cpf);
            validaDisciplina(aluno.disciplina);
            printf("\n\t\t\tCPF: %s\n", aluno.cpf);
            printf("\n\t\t\tDISCIPLINA: %s\n", aluno.disciplina);

            for (i = 0; i < 3; i++)
            {
                aluno.notas[i] = validarNotas(i);
            }

            if (fwrite(&aluno, sizeof(aluno), 1, arq))
            {
                fprintf(cpy, "%d %s %s %s %f %f %f\n", aluno.codigo, aluno.nome, aluno.cpf, aluno.disciplina, aluno.notas[0], aluno.notas[1], aluno.notas[2]);
                printf("\n\t\t\tDados cadastrados com sucesso.");
                cont++;
            }
            else
                printf("\t\t\tErro no cadastro.");

            printf("\n\t\t\tNovo aluno?[S/N]: ");
            __fpurge(stdin);
            tecla = toupper(getchar());
            system("clear");
        } while (tecla == 'S');
    }
    fclose(arq);
    fclose(cpy);
}

void listarDados()
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int i, count = 0;
    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }
    else
    {
        cabecalho("LISTA DE ALUNOS");
        while (fread(&aluno, sizeof(aluno), 1, arq) != 0)
        {
            if (strcmp(aluno.nome, "\0") == 0)
            {
            }
            else
            {
                count++;
                printf("\n\t\t\tCódigo do aluno: %d | ", aluno.codigo);
                printf("Nome: %s", aluno.nome);
            }
        };
        if (count == 0)
            printf("\n\t\t\tNenhum registro foi encontrado.");
        fclose(arq);
        puts("\n\n\n\n\t\t\tTecle ENTER para continuar: ");
        __fpurge(stdin);
        getchar();
    }
}

void consultarAluno()
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int codigo, i;
    float media = 0;

    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }
    else
    {
        cabecalho("CONSULTA DE ALUNO");
        printf("\n\t\t\tDigite o código do aluno: ");
        scanf("%d", &codigo);

        fseek(arq, sizeof(aluno) * (codigo - 1), SEEK_SET);
        if (ferror(arq))
            printf("\n\t\t\tErro no posicionamento do cursor.");
        else
        {
            fread(&aluno, sizeof(aluno), 1, arq);
            if (ferror(arq))
                printf("\n\t\t\tErro na leitura do arquivo.");
            else
            {
                printf("\n\t\t\tCódigo do aluno: %d", aluno.codigo);
                printf("\n\t\t\tNome: %s", aluno.nome);
                printf("\n\t\t\tCPF: %s", aluno.cpf);
                printf(" - Disciplina: %s", aluno.disciplina);
                printf("\n\t\t\tNotas: ");
                for (i = 0; i < 3; i++)
                {
                    printf("%.2f | ", i + 1, aluno.notas[i]);
                    media += aluno.notas[i];
                }
                media = media / 3;
                printf("\n\t\t\tMédia: %.2f", media);
            }
            __fpurge(stdin);
            getchar();
        }
    }
}

void alterarNotaDoAluno()
{
    FILE *arq = fopen("files/aluno.dat", "r+b");
    int codigo, i;
    char nome[TAM], disc[TAM];

    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }
    else
    {
        cabecalho("ALTERAÇÃO DE NOTA DE ALUNO");
        printf("\n\t\t\tDigite o código do aluno: ");
        scanf("%d", &codigo);

        fseek(arq, sizeof(aluno) * (codigo - 1), SEEK_SET);
        if (ferror(arq))
            printf("\n\t\t\tErro no posicionamento do cursor.");
        else
        {
            fread(&aluno, sizeof(aluno), 1, arq);
            if (ferror(arq))
                printf("\n\t\t\tEr03 - Erro na leitura do arquivo.");
            else
            {
                printf("\n\t\t\tCódigo do aluno: %d | ", aluno.codigo);
                printf("Nome: %s\n", aluno.nome);
                for (i = 0; i < 3; i++)
                {
                    aluno.notas[i] = validarNotas(i);
                }
                fseek(arq, sizeof(aluno) * (codigo - 1), SEEK_SET);
                fwrite(&aluno, sizeof(aluno), 1, arq);
            }
        }
        fclose(arq);
    }
}

void deletarAluno()
{
    FILE *arq = fopen("files/aluno.dat", "r+b");
    int codigo, i;

    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }
    else
    {
        cabecalho("DELETAR ALUNO");
        printf("\n\t\t\tDigite o código do aluno: ");
        scanf("%d", &codigo);

        fseek(arq, sizeof(aluno) * (codigo - 1), SEEK_SET);
        if (ferror(arq))
            printf("\n\t\t\tErro no posicionamento do cursor.");
        else
        {
            fread(&aluno, sizeof(aluno), 1, arq);
            if (ferror(arq))
                printf("\n\t\t\tEr03 - Erro na leitura do arquivo.");
            else
            {
                strcpy(aluno.nome, "\0");
                strcpy(aluno.disciplina, "\0");
                for (i = 0; i < 3; i++)
                {
                    aluno.notas[i] = 0;
                }
                fseek(arq, sizeof(aluno) * (codigo - 1), SEEK_SET);
                fwrite(&aluno, sizeof(aluno), 1, arq);
            }
        }
        fclose(arq);
    }
}

int countInd()
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int i = 1;

    if (arq == NULL)
        return i = 1;
    else
    {
        rewind(arq);
        while (fread(&aluno, sizeof(aluno), 1, arq) != 0)
        {
            i++;
        };
        return i;
    }
    fclose(arq);
}