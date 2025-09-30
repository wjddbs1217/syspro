#include <stdio.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

main(){
	int len;
	int max;
	max = 0;

	while(gets(line) != NULL) {
		len = strlen(line);

		if(max > 0) 
			printf("%s \n", longest);

		return 0;
	}

