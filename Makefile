etapa3: y.tab.o lex.yy.o main.o hash.o astree.o
	gcc -o etapa3 hash.o lex.yy.o y.tab.o main.o 

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
	
clean:
	rm *.o etapa3 lex.yy.c lex.yy.h y.tab.c y.tab.h
