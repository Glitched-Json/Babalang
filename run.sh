clear
flex babalang.l
bison babalang.y -Wcounterexamples
gcc lex.yy.c -lfl
./a.out
