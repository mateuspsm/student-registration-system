/* Arquivo de funções do cabeçalho Menu
** Aqui são implementadas as funções que controlam o menu do program */

//Inclusão do cabeçalho menu.h
#include "../include/menu.h"

/* Função que não retorna nenhum valor e recebe como parametro uma string contendo um texto,
** que dará o nome do titulo principal de cada uma das operações no programa principal.*/
void cabecalho(char *titulo)
{
    system("clear");
    printf("\n\n\t\t\t====[%s]====\n", titulo);
}

/* Função que retorna um número inteiro correspondente a uma das operações apresentadas no menu,
** e limpa a tela após receber o valor.*/
int menu()
{
    int op;
    
    cabecalho("MENU DE OPÇÕES");
    puts("\t\t\t-------------------------");
    puts("\t\t\t|| 1 |- Cadastrar Aluno |");
    puts("\t\t\t|| 2 |- Listar Alunos   |");
    puts("\t\t\t|| 3 |- Consultar Aluno |");
    puts("\t\t\t|| 4 |- Alterar Aluno   |");
    puts("\t\t\t|| 5 |- Deletar Aluno   |");
    puts("\t\t\t|| 6 |- Listar Inátivos |");
    puts("\t\t\t|| 7 |- Sair            |");
    puts("\t\t\t-------------------------");
    printf("\t\t\tDigite a opção: ");
    scanf("%d", &op);
    puts("\t\t\t-------------------------");
    system("clear");
    return op;
}