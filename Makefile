all:
	mkdir bin files obj
	gcc -c ./src/aluno.c -I ./include -o ./obj/aluno.o
	gcc -c ./src/menu.c -I ./include -o ./obj/menu.o
	gcc app/main.c obj/*.o -o bin/main
run:
	./bin/main
clean:
	rm -rf ./obj/ ./bin/ ./files/