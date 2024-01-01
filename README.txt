NAME: SIMI BISHNU

STUDENT NUMBER: 101264827

PURPOSE: a program that contains a game set in the hollow, where two heroes, timmy and harold, try to escape from the attacks of the evil wizard's flying birds and monkeys. each instance of the program uses command line arguments to determine whether to behave as a server process which simulates the heroes' escape and displays its output, or a client process which connects to a running server in order to receive and display the identical escape output.

SOURCE: main.c, connect.c, hero.c, flyer.c, move.c, escape.c, view.c, spectator.c 

HEADER: defs.h

COMPILATION INSTRUCTIONS: make 

LAUNCHING INSTRUCTIONS: 
to run program as the server: ./a5
to run program as the client: ./a5 127.0.0.1

CHECKING MEMORY LEAKS WITH VALGRIND:  valgrind --leak-check=full ./a5