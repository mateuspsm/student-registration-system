# Sistema de Controle de Alunos - C Project CRUD

## Version

Version: 1.0

## Sobre o Mini-Projeto

Este mini-projeto feito em linguagem C, foi desenvolvido como trabalho final para a disciplina de programação estruturada da faculdade. A ideia era trabalhar todos os conhecimentos adiquiridos durante o semestre.
Dentre eles:
 - Variáveis e Constantes
 - Funções
 - Structs
 - Arrays
 - Arquivos binários e texto - CRUD
 - Validações
 - Cabeçalhos
 - Arquivo Makefile

## Caso de Uso do Mini-Projeto

![use case](https://github.com/mateuspsm/crud-c/blob/master/use%20case/use-case-v1.0.png)

## Pré-requisitos

Ter um compilador instalado.
Algumas opções são: GCC e MinGW

## Ferramentas utilizadas
 - Visual Studio Code
 - Git e Github

## Como rodar o Mini-Projeto

Tendo um compilador instalado, basta entrar na pasta raiz do projeto e abrir o teminal para rodar o seguinte código:

### Executar o Mini-Projeto
```
make run
```

Caso queira re-compilar o projeto. Use esses comando:

### Limpar arquivos
```
make clean
```

### Compilar os arquivos
```
make
```

### Observação

O projeto foi feito em linux, já deixei o projeto compilado aqui. Caso queira compila-lo novamente por questões de compilador, o comando de limpeza de buffer deve mudar se estiver no S.O Windows.

Mude isso:
```
 __fpurge(stdin)
```
Para isso:
```
 fflush(stdin)
```

## Autor

* **Mateus Perera** - *Student* - [Linkedin](https://www.linkedin.com/in/mateus-pereira-971946197/)

## Referencias

Na construção do projeto fiz algumas pesquisas que ajudaram muito as quais destaco:
 - Prof. Samuka [YouTube](https://www.youtube.com/watch?v=v3dSoFDSe-I&list=PL3ZslI15yo2qiGb4u7fLlbKGL2nTNV8F3)
 - Prof. Edwar Saliba [Apostila](https://www.youtube.com/watch?v=v3dSoFDSe-I&list=PL3ZslI15yo2qiGb4u7fLlbKGL2nTNV8F3)
 - André [Artigo - Viva O Linux](https://www.vivaolinux.com.br/artigo/Expressoes-Regulares-(POSIX)-em-C)
 - Apostila da UFMG de C [Apostila](http://paginapessoal.utfpr.edu.br/lalucas/disciplinas/el71e-s01-algoritmos/C_UFMG.pdf/view)
 - Além do material disponibilizado pelo professor da disciplina.

## Licença

[MIT](/LICENSE) &copy; Mateus Pereira - Brasil

## Obrigado!

