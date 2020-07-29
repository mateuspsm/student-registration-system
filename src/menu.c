#include "../include/menu.h"

//Functions 
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