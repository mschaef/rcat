rcat: rcat.c
	gcc -o rcat rcat.c

.PHONY: clean
clean:
	rm rcat
