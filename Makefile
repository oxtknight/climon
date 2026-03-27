program: main.c
	gcc main.c -lm -o climon
clean:
	rm -f climon
run: all
	./climon
