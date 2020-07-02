/* Control Note - Version 1.0
**
** Student grade control software.
** Author: Mateus Pereira.
** Student of Systems Analysis and Development.
** Project: Structured Programming Project.
**
*/

//Built using the linux operating system in C language.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#define TAM 100
#define EXPR_REG "[A-z]{3,20}\\s[A-z]{2,20}"
#define EXPR_REG2 "[A-z]{5,20}\\s[A-z]{2,20}|[A-z]{2,20}"

//Struct Aluno
typedef struct
{
    int codigo;
    char nome[TAM], disciplina[TAM];
    float notas[3];
} Aluno;

void acrescentarDados(Aluno aluno);
void listarDados(Aluno aluno);
void consultarAluno(Aluno aluno);
void alterarNotaDoAluno(Aluno aluno);
void apagarArquivo();
int countInd(Aluno aluno);
void validaNome(char nome[]);
float validarNotas(int i);
void deletarAluno(Aluno aluno);

int main()
{
    Aluno aluno;
    int op;
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            acrescentarDados(aluno);
            break;
        case 2:
            listarDados(aluno);
            break;
        case 3:
            consultarAluno(aluno);
            break;
        case 4:
            alterarNotaDoAluno(aluno);
            break;
        case 5:
            deletarAluno(aluno);
            break;
        case 6:
            puts("\t\t\tSaindo...");
            break;
        default:
            printf("\t\t\tOpção invalida.\n");
            break;
        }
    } while (op != 6);
    return (0);
}

void cabecalho(char *titulo)
{
    system("clear");
    printf("\n\n\t\t\t====[%s]====\n", titulo);
}

int menu()
{
    int op;
    cabecalho("MENU DE OPÇÕES");
    puts("\t\t\t-------------------------");
    puts("\t\t\t|| 1 |- Cadastrar Aluno |");
    puts("\t\t\t|| 2 |- Listar Alunos   |");
    puts("\t\t\t|| 3 |- Consultar Aluno |");
    puts("\t\t\t|| 4 |- Alterar Nota    |");
    puts("\t\t\t|| 5 |- Deletar Aluno   |");
    puts("\t\t\t|| 6 |- Sair            |");
    puts("\t\t\t-------------------------");
    printf("\t\t\tDigite a opção: ");
    scanf("%d", &op);
    puts("\t\t\t-------------------------");
    system("clear");
    return op;
}

void acrescentarDados(Aluno aluno)
{
    FILE *arq = fopen("aluno.dat", "ab");
    FILE *cpy = fopen("aluno.txt", "a");
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
            validaDisciplina(aluno.disciplina);

            for (i = 0; i < 3; i++)
            {
                aluno.notas[i] = validarNotas(i);
            }

            if (fwrite(&aluno, sizeof(aluno), 1, arq))
            {
                fprintf(cpy, "%d %s %s %f %f %f\n", aluno.codigo, aluno.nome, aluno.disciplina, aluno.notas[0], aluno.notas[1], aluno.notas[2]);
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

void listarDados(Aluno aluno)
{
    FILE *arq = fopen("aluno.dat", "rb");
    int i, count=0;
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
            if(strcmp(aluno.nome,"\0")==0){
                
            }else
            {
                count++;
                printf("\n\t\t\tCódigo do aluno: %d | ", aluno.codigo);
                printf("Nome: %s", aluno.nome);
            }
        };
        if(count==0)
            printf("\n\t\t\tNenhum registro foi encontrado.");
        fclose(arq);
        puts("\n\n\n\n\t\t\tTecle ENTER para continuar: ");
        __fpurge(stdin);
        getchar();
    }
}

void consultarAluno(Aluno aluno)
{
    FILE *arq = fopen("aluno.dat", "rb");
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

        fseek(arq, sizeof(Aluno) * (codigo - 1), SEEK_SET);
        if (ferror(arq))
            printf("\n\t\t\tErro no posicionamento do cursor.");
        else
        {
            fread(&aluno, sizeof(Aluno), 1, arq);
            if (ferror(arq))
                printf("\n\t\t\tErro na leitura do arquivo.");
            else
            {
                printf("\n\t\t\tCódigo do aluno: %d", aluno.codigo);
                printf("\n\t\t\tNome: %s", aluno.nome);
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

void alterarNotaDoAluno(Aluno aluno)
{
    FILE *arq = fopen("aluno.dat", "r+b");
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

        fseek(arq, sizeof(Aluno) * (codigo - 1), SEEK_SET);
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
                fseek(arq, sizeof(Aluno) * (codigo - 1), SEEK_SET);
                fwrite(&aluno, sizeof(aluno), 1, arq);
            }
        }
        fclose(arq);
    }
}

void deletarAluno(Aluno aluno){
    FILE *arq = fopen("aluno.dat","r+b");
    int codigo,i;

    if(arq==NULL){
        puts("\t\t\tArquivo inexistente.");
        __fpurge(stdin);
        getchar();
    } 
    else{
        cabecalho("DELETAR ALUNO");
        printf("\n\t\t\tDigite o código do aluno: ");
        scanf("%d",&codigo);

        fseek(arq,sizeof(Aluno)*(codigo-1),SEEK_SET);
        if(ferror(arq))
            printf("\n\t\t\tErro no posicionamento do cursor.");
        else{
            fread(&aluno,sizeof(aluno),1,arq);
            if(ferror(arq))
                printf("\n\t\t\tEr03 - Erro na leitura do arquivo.");
            else{
                strcpy(aluno.nome,"\0");
                strcpy(aluno.disciplina,"\0");
                for (i = 0; i < 3; i++){
                    aluno.notas[i]=0;
                }
                fseek(arq,sizeof(Aluno)*(codigo-1),SEEK_SET);
                fwrite(&aluno,sizeof(aluno),1,arq);
            }
        }
        fclose(arq);
    }
}

int countInd(Aluno aluno)
{
    FILE *arq = fopen("aluno.dat", "rb");
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

void validaNome(char nome[])
{
    regex_t reg;
    int result;

    if (regcomp(&reg, EXPR_REG, REG_EXTENDED | REG_NOSUB) != 0)
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
            }
        } while (result == 1);
    }
}

void validaDisciplina(char nome[])
{
    regex_t reg;
    int result;

    if (regcomp(&reg, EXPR_REG2, REG_EXTENDED | REG_NOSUB) != 0)
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