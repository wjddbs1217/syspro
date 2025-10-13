#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_file(const char *filename, int line_numbering) {
	FILE *fp;
	int ch;
	long line_count = 1;
	int at_line_start = 1;

	if ((fp = fopen(filename, "r")) == NULL) {
		perror(filename);
		return;
	}

	if (line_numbering && at_line_start) {
		printf("%6ld ", line_count);
		at_line_start = 0;
	}

	while ((ch = getc(fp)) != EOF) {
		putc(ch, stdout);

		if (ch == '\n') {
			at_line_start = 1;

			if (line_numbering) {
				line_count++;

				if (feof(fp) == 0) {
					printf("%6ld ", line_count);
				}
			}
		} else {
			at_line_start = 0;
		}
	}
	if (ch != '\n' && line_numbering && line_count > 1) {
		putc('\n', stdout);
	}
	 fclose(fp);
}

int main(int argc, char *argv[]) {
	int line_numbering = 0;
	int first_file_index = 1;

	if (argc < 2) {
		fprintf(stderr, "%s [-n] <file1.txt> [file2.txt file3.txt]\n",argv[0]);
		return 0;
	}

	if (strcmp(argv[1], "-n") == 0) {
		line_numbering = 1;
		first_file_index = 2;
	}

	if (argc <= first_file_index) {
		fprintf(stderr, "error.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = first_file_index; i < argc; i++) {
		display_file(argv[i], line_numbering);
	}

	return 0;
}

