parser:
	flex scanner.l
	bison -d -v parser.y
	g++ -g -o parser AST.cpp lex.yy.c parser.tab.c -lfl

clean:
	rm lex.yy.c parser.tab.c parser.tab.h parser parser.output
