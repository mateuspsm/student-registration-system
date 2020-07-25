#ifndef ALUNO_H_
#define ALUNO_H_

    #define TAM 100 
    #define EXPR_REG "[A-z]{3,20}\\s[A-z]{2,20}"
    #define EXPR_REG2 "[A-z]{5,20}\\s[A-z]{2,20}|[A-z]{2,20}"

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

#endif