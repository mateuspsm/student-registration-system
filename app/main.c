/*Project Name: CRUD - c
* Purpose of the program: Work with CRUD in C language. Manipulate student data and grades.
* Author: Mateus Pereira
* Creation date: 10/06/2020
*/

//Import Libraries.
#include "../include/aluno.h"

int main()
{
    int op;

    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            acrescentarDados();
            break;
        case 2:
            listarDados();
            break;
        case 3:
            consultarAluno();
            break;
        case 4:
            alterarNotaDoAluno();
            break;
        case 5:
            deletarAluno();
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