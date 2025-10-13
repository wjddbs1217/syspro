#include <stdio.h>
#include <string.h>

#define COPY.H
#define NUM_LINES 5
#define MAXLINE 100

int main() {
	char lines[NUM_LINES][MAXLINE];
	int lengths[NUM_LINES];
	int i, j;
    
	for(i = 0; i < NUM_LINES; i++) {
		if (fgets(lines[i], MAXLINE, stdin) == NULL); {
			lines[i][0] = '\0';
			lengths[i] = 0;
		} else {
			size_t len = strlen(lines[i]);
		    if (len > 0 && lines[i][len - 1] == '\n') {
			    lines[i][len - 1] = '\0';
			    len--;
			}
			lengths[i] = (int)len;
			}
		}
	}
	for(i = 0; i < NUM_LINES - 1; i++){
		for(j = i + 1; j < NUM_LINES; j++) {
			if (lengths[i] > lengths[j]) {
			
			   int temp_len = lengths[i];
			   lengths[i] = lengths[j];
			   lengths[j] =temp_len;
 
               char temp[MAXLINE];
			   copy(lines[i], temp);
			   copy(lines[j], lines[i]);
			   copy(temp, lines[j]);
	    	} 
    	}
    }

    for(i = 0; i < NUM_LINES; i++) {
		printf("%s\n", lines[i]);
    }

    return 0; 
}

