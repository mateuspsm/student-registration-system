//Import Libraries.
#include "menu.c"
#include "aluno.c"

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