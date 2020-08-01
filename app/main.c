/* Project Name: CRUD - C
** Mini projeto, para cadastro de alunos e suas notas em arquivos. Trabalhando as operações de um CRUD.
** Author: Mateus Pereira
** Creation date: 10/06/2020 */

//Incluindo a biblioteca de função para manipulação de alunos.
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
            alunosInativos();
            break;
        case 7:
            puts("\t\t\tSaindo...");
            break;
        default:
            printf("\t\t\tOpção invalida.\n");
            break;
        }
    } while (op != 7);
    return (0);
}
