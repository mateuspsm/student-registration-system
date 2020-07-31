/* Arquivo de funções do cabeçalho Aluno
** Aqui são implementadas as funções que controlam as operações de registro do aluno */

//Inclusão do cabeçalho aluno.h
#include "../include/aluno.h"

/* Declaração de todas as constantes usadas para fazer validaçãoes:
** - Tamanho de variaveis
** - Expressões Regulares.*/
#define TAM 100
#define EXPR_REG_NOME "[A-z]{3,20}\\s[A-z]{2,20}"
#define EXPR_REG_DISCIPLINA "[A-z]{5,20}\\s[A-z]{2,20}|[A-z]{2,20}"
#define EXPR_REG_CPF "[0-9]{11}"

//Definição da estrutura que será manipulada pelas funções
struct _aluno
{
    int codigo;
    char nome[TAM], cpf[TAM], disciplina[TAM];
    float notas[3];
};


/* Função recebe uma string por referencia contendo um texto que será verificada se está vazia,
** ou se tem no minimo 2 letras + espaço + 2 letras para validação de um nome.
** Usando funções da biblioteca Regex.c.*/
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
            printf("\n\t\t\tAtenção somente número.");
            printf("\n\t\t\tDigite o CPF do aluno: ");
            __fpurge(stdin);
            gets(cpf);

            if ((regexec(&reg, cpf, 0, (regmatch_t *)NULL, 0)) == 0)
            {
                if (verificarCPF(cpf))
                {
                    result = 1;
                }
                else
                {
                    result = 0;
                }
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

int countInd()
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int i = 1;
    struct _aluno aluno;

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

int verificarCPF(char cpf[])
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int i, count = 0;
    struct _aluno aluno;

    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }

    else
    {
        while (fread(&aluno, sizeof(aluno), 1, arq) != 0)
        {
            if (strcmp(aluno.nome, "\0") == 0)
            {
            }
            else
            {
                count++;
                if (strcmp(aluno.cpf, cpf) == 0)
                {
                    printf("\n\t\t\tO CPF já se encontra cadastrado no sistema.");
                    printf("\n\t\t\tVariavel aluno.cpf [%s]", aluno.cpf);
                    printf("\n\t\t\tVariavel cpf [%s]", cpf);
                    return 1;
                }
            }
        };
        if (count == 0)
        {
            printf("\n\t\t\tNenhum registro foi encontrado.");
            return 0;
        }
        else
        {
            printf("\n\t\t\tO CPF não se encontra cadastrado no sistema.");
            return 0;
        }
        fclose(arq);
        puts("\n\n\n\n\t\t\tTecle ENTER para continuar: ");
        __fpurge(stdin);
        getchar();
    }
}

void acrescentarDados()
{
    FILE *arq = fopen("files/aluno.dat", "a+b");
    FILE *cpy = fopen("files/aluno.txt", "a");
    struct _aluno aluno;
    char tecla;
    int i, cont;

    if (arq == NULL && cpy == NULL)
        printf("O arquivo não pode ser aberto.");
    else
    {
        cabecalho("CADASTRAR DE ALUNOS");
        cont = countInd(aluno);
        printf("\n\t\t\tCODIGO DE CADASTRO DO ALUNO [STD%d]", cont);
        aluno.codigo = cont;
        validaCpf(aluno.cpf);
        if (restorarInativos(aluno.cpf))
        {
            printf("\n\t\t\tDados cadastrados com sucesso.");
        }
        else
        {
            validaNome(aluno.nome);
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
            }
            else
                printf("\t\t\tErro no cadastro.");
        }
    }
    fclose(arq);
    fclose(cpy);
}

void listarDados()
{
    FILE *arq = fopen("files/aluno.dat", "rb");
    int i, count = 0;
    struct _aluno aluno;
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
    struct _aluno aluno;

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
    struct _aluno aluno;
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
    FILE *alunoBackup = fopen("files/aluno_backup.dat", "ab");
    FILE *cpy = fopen("files/aluno_backup.txt", "a");
    struct _aluno aluno;
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
                fwrite(&aluno, sizeof(aluno), 1, alunoBackup);
                fprintf(cpy, "%d %s %s\n", aluno.codigo, aluno.nome, aluno.cpf);
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
        fclose(alunoBackup);
        fclose(cpy);
    }
}

void alunosInativos()
{
    FILE *arq = fopen("files/aluno_backup.dat", "r+b");
    struct _aluno aluno;
    int i, count = 0;
    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    }
    else
    {
        cabecalho("LISTA DE ALUNOS INÁTIVOS");
        while (fread(&aluno, sizeof(aluno), 1, arq) != 0)
        {
            if (strcmp(aluno.nome, "\0") == 0)
            {
            }
            else
            {
                count++;
                printf("\n\t\t\tCódigo do aluno: %d | ", aluno.codigo);
                printf("Nome: %s | CPF: %s", aluno.nome, aluno.cpf);
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

int restorarInativos(char cpf[])
{
    FILE *arq = fopen("files/aluno_backup.dat", "r+b");
    struct _aluno aluno;
    int i, count = 0;
    char restore;

    if (arq == NULL)
    {
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
        return 0;
    }

    else
    {
        while (fread(&aluno, sizeof(aluno), 1, arq) != 0)
        {
            if (strcmp(aluno.nome, "\0") == 0)
            {
            }
            else
            {
                count++;
                if (strcmp(aluno.cpf, cpf) == 0)
                {
                    printf("\n\t\t\tAluno inátivo.");
                    printf("\n\t\t\tDeseja restaura-lo [S/N]:");
                    __fpurge(stdin);
                    restore = toupper(restore = getchar());
                    if (restore == 'S')
                    {
                        FILE *arqAl = fopen("files/aluno.dat", "r+b");
                        fseek(arqAl, sizeof(aluno) * (aluno.codigo - 1), SEEK_SET);
                        if (fwrite(&aluno, sizeof(aluno), 1, arqAl))
                        {
                            fclose(arqAl);
                            return 1;
                        }
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        };
        if (count == 0)
        {
            printf("\n\t\t\tNenhum registro foi encontrado.");
            return 0;
        }
        else
        {
            return 0;
        }
        fclose(arq);
        puts("\n\n\n\n\t\t\tTecle ENTER para continuar: ");
        __fpurge(stdin);
        getchar();
    }
}