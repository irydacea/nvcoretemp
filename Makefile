nvcoretemp:
	$(CC) nvcoretemp.c -o nvcoretemp -lXNVCtrl

clean:
	rm nvcoretemp
