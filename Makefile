all: main.c algo.c graph.c utils.c 
	gcc -g -I. main.c algo.c graph.c utils.c -o graph

clean:
	rm -f graph
