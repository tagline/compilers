etapa6: y.tab.o lex.yy.o main.o hash.o astree.o semantic.o tac.o code.o
	gcc -o etapa6 hash.o lex.yy.o y.tab.o main.o semantic.o tac.o code.o

main.o: main.c
	gcc -c main.c 

hash.o: hash.c
	gcc -c hash.c 

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 

y.tab.o: y.tab.c
	gcc -c y.tab.c 

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c 

y.tab.c: parser.y
	 yacc -d -v parser.y
	 
astree.o: astree.c
	gcc -c astree.c
	 
semantic.o: semantic.c
	gcc -c semantic.c

tac.o: tac.c
	gcc -c tac.c

code.o: code.c
	gcc -c code.c
	 
clean:
	rm *.o etapa6 lex.yy.c lex.yy.h y.tab.c y.tab.h
