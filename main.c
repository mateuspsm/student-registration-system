//Import Libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "Headers/menu.h"
#include "Headers/aluno.h"

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