#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_CHARS 100

void parse_and_print(const char *input, const char savedText[][MAX_CHARS], int totalLines);

int main(int argc, char *argv[]) {
	char savedText[MAX_LINES][MAX_CHARS];
	int totalLines = 0;
	char input[MAX_CHARS];

	if (argc != 2) {
		printf("Usage: %s\n", argv[0]);
		printf("Example: %s test.txt\n", argv[0]);
		return 1;
	}

	const char filename = argv[1];

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("File read failed.\n");
		return 1;
	}

	printf("File read success\n");
	while (fgets(savedText[totalLines], MAX_CHARS, fp) != NULL) {
		size_t len = strlen(savedText[totalLines]);
		if (len > 0 && savedText[totalLines][len - 1] == '\n') {
			savedText[totalLines][len - 1] = '\0';
		}
		totalLines++;
		if (totalLines >= MAX_LINES) break;
	}
	fclose(fp);

	printf("Total Line : %d\n", totalLines);
	printf("You can choose 1 ~ %d Line\n", totalLines);
	printf("Pls 'Enter' the LIne to select :");

	if (fgets(input,MAX_CHARS, stdin) == NULL) {
		printf("Input error.\n");
		return 1;
	}

	input[strcspn(input, "\n")] = '\0';

	parse_and_print(input, savedText, totalLines);
	return 0;
}

void parse_and_print(const char *input, const char savedText[][MAX_CHARS], int totalLines) {
	char temp[MAX_CHARS];
	strcpy(temp, input);
	char *token, *range_sep;

	if (strcmp(temp, "*") == 0) {
		for (int i = 1; i <= totalLines; i++) {
			printf("%d %s\n", i, savedText[i-1]);
		}
		return;
	}

	token = strtok(temp,",");
	while (token != NULL) {
		range_sep = strchr(token, '-');

		if (range_sep != NULL) {

		int start, end;
		if (sscanf(token, "%d-%d", &start, &end) == 2) {
			for (int i = start; i <= end; i++) {
				if (i >= 1 && i <= totalLines) {
					printf("%d %s \n", i, savedText[i-1]);
				}
			}
		}
	} else {
		int line_num = atoi(token);
		if (line_num >= 1 && line_num <= totalLines) {
			printf("%d %s\n", line_num, savedText[line_num-1]);
		}
	}
	token = strtok(NULL, ",");
	}
}

