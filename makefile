PARAMS = -Wall

main: main.c algorithm.o
	gcc $(PARAMS) main.c algorithm.o -o main

alorithm.o: algorithm.c algorithm.h
	gcc $(PARAMS) -c algorithm.c -o algorithm.o

run: main
	./main points.dat hull.dat

clean:
	rm -f *.o
	rm main

plot: main points.dat hull.dat
	./main points.dat hull.dat
	gnuplot plot.gp

