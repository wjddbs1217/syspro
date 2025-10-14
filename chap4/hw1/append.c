#include <stdio.h>
#include <stdlib.h>

void append_file(FILE *source, FILE *destination);

int main(int argc, char *argv[]) {
	FILE *source_file, *dest_file;

	if (argc != 3) {
		fprintf(stderr, "%s <file1.txt> <file2.txt>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((dest_file = fopen(argv[2], "a")) == NULL) {
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}

	if ((source_file = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		fclose(dest_file);
		exit(EXIT_FAILURE);
	}

	append_file(source_file, dest_file);

	fclose(source_file);
	fclose(dest_file);

	printf("test hi my name is jungyun go\n", argv[1], argv[2]);
	return 0;
}

void append_file(FILE *source, FILE *destination) {
	int ch;

	while ((ch = getc(source)) != EOF) {

		putc(ch, destination);
	}
}

