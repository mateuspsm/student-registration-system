//Arquivo de cabeçalho aluno

/* Aqui são definidos os prótotipos das funções do arquivo aluno.c, para que o mesmo não seja visivel
** para o arquivo main(principal) do projeto.*/
#ifndef ALUNO_H_
#define ALUNO_H_

    //Inclusão do arquivo aluno.c
    #include "menu.h"

    //Protótipo das funções.
    void acrescentarDados();
    void listarDados();
    void consultarAluno();
    void alterarNotaDoAluno();
    void apagarArquivo();
    int countInd();
    void deletarAluno();
    void alunosInativos();
    
#endif