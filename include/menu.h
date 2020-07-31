//Arquivo de cabeçalho menu

/* Aqui são definidos os prótotipos das funções do arquivo menu.c, para que o mesmo não seja visivel
** para o arquivo main(principal) do projeto.*/
#ifndef __MENU_H__
#define __MENU_H__
    
    //Aqui dentro são declaradas todas as bibliotecas do sistemas que iremos utilizar.
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <regex.h>

    //Protótipo das funções.
    void cabecalho(char *titulo);
    int menu();
#endif