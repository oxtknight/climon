program: source.code/main.c
	gcc source.code/main.c -lm -o climon
clean:
	rm -f source.code/climon
run: all
	./climon
