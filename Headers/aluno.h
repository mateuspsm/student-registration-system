#ifndef ALUNO_H_
#define ALUNO_H_

    #define TAM 100 
    #define EXPR_REG "[A-z]{3,20}\\s[A-z]{2,20}"
    #define EXPR_REG2 "[A-z]{5,20}\\s[A-z]{2,20}|[A-z]{2,20}"
    #define Expr_REG_CPF "[0-9]{11}|[0-9]{3}.[0-9]{3}.[0-9]{3}-[0-9]{2}"

    typedef struct
    {
    int codigo;
    char nome[TAM],cpf[11], disciplina[TAM];
    float notas[3];
    } Aluno;

    void acrescentarDados(Aluno aluno);
    void listarDados(Aluno aluno);
    void consultarAluno(Aluno aluno);
    void alterarNotaDoAluno(Aluno aluno);
    void apagarArquivo();
    int countInd(Aluno aluno);
    void validaNome(char nome[]);
    void validaCpf(char cpf[]);
    float validarNotas(int i);
    void deletarAluno(Aluno aluno);

#endif