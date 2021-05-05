#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa6: lex.yy.c main.o hash.o y.tab.c ast.o decompiler.o semantic.o semanticUtils.o parameter_type_list.o tacs.o
	gcc -Wall -o etapa6 lex.yy.c main.o hash.o ast.c decompiler.c semantic.o semanticUtils.o parameter_type_list.o tacs.o

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

tacs.o: tacs.c
	gcc -c tacs.c

semanticUtils.o: semanticUtils.c
	gcc -c semanticUtils.c

parameter_type_list.o: parameter_type_list.c
	gcc -c parameter_type_list.c

decompiler.o: decompiler.c
	gcc -c decompiler.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

lex.yy.c: scanner.l y.tab.o
	flex --header-file=lex.yy.h scanner.l

y.tab.c: parser.y
	yacc -d parser.y

clean:
	rm *.o lex.yy.c y.tab.c y.tab.h etapa6
