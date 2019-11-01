build: telefon.c
	gcc -Wall telefon.c -o telefon

run: telefon
	./telefon

clean: telefon
	rm -f telefon

