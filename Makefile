cgl: main.c libs/strcap.c games/tictactoe.c libs/strcap.c libs/cs50.c
	cc -o games/tictactoe games/tictactoe.c libs/strcap.c libs/cs50.c
	cc -w -o cgl main.c libs/strcap.c