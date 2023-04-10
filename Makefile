tictactoe: games/tictactoe.c libs/strcap.c libs/cs50.c 
	cc -o tictactoe games/tictactoe.c libs/strcap.c libs/cs50.c

gamelib: main.c libs/strcap.c
	cc -o gamelib main.c libs/strcap.c