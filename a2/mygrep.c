#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_BYTES 10000
#define MAX_OPTIONS 3

int substring_count (char*, char*);

int main (int argc, char* argv[]){   
	if (argc == 1) {
		perror("Two arguments expected"); exit(1);
		}
	
	int opCount = 0;
	for (int i=1; i<argc && (argv[i][0]=='-' && argv[i][1]!='\0'); i++) {
		opCount++;
		}
	
	if (argc - opCount >= 3){      
		int src_fd, src_sz, num = MAX_OPTIONS;
		char src[MAX_LENGTH], pattern[MAX_LENGTH], options[num];
		char *content = (char *) calloc(MAX_BYTES, sizeof(char));
		memset(options,'-',num*sizeof(options[0]));
		
		//determine which options have been included
		int k=0;
		for (int i=1; i<argc && (argv[i][0]=='-' && argv[i][1]!='\0'); i++) {
			for (int j=1; argv[i][j]!='\0'; j++) {
				switch (argv[i][j]) {	
					case 'n': {
						options[0] = argv[i][j];
						k++; break;
						}
					case 'v': {
						options[1] = argv[i][j];
						k++; break;
						}
					case 'c': {
						options[2] = argv[i][j];
						k++; break;
						}
					default: {
						perror("Invalid option. Exiting..."); exit(1);
						break;
						}
					}
				}
			}
		
		//identify the pattern from CLA
		strcpy(pattern,argv[1+opCount]);
		
		for (int i = opCount+2; i<argc; i++) {
			//identify the filename from CLA
			strcpy(src,argv[i]);
			
			//find file desciptor for src file
			src_fd = open(src,O_RDONLY);
			//include error msg for case when src file not found
			if (src_fd < 0) { perror("Command unsuccessful"); exit(1); } 
			 
			//save the contents of src file in a string
			src_sz = read(src_fd,content,MAX_BYTES);  
			content[src_sz] = '\0'; 
			
			//close src file
			close(src_fd);
			
			//display required output
			if (k==0) {
				//split the content into lines
				char* line = strtok(content,"\n");
				while (line != NULL) {
					//check if pattern is a substring
						//note: match regex too
						//regcomp and regex functions
					
					if (strstr(line,pattern))
						printf("%s\n", line);
					//go to the next line
					line = strtok(NULL,"\n");
					}
				}
			
			else if (options[2] == 'c') {
				int count = 0;
				//split the content into lines
				char* line = strtok(content,"\n");
				while (line != NULL) {
					//check if pattern is a substring			
					if (strstr(line,pattern)) {
						count += substring_count(line,pattern);
						}
					//go to the next line
					line = strtok(NULL,"\n");
					}
				//print the number of occurrences
				printf("%d\n",count);
				}
			
			else if (options[0] == 'n' && options[1] == '-') {
				int n = 0;
				//split the content into tokens on newline
				char* line = strtok(content,"\n");
				while (line != NULL) {
					//count the line numbers
					n++;
					//check if pattern is a substring			
					if (strstr(line,pattern))
						printf("%d:%s\n", n,line);
					//go to the next line
					line = strtok(NULL,"\n");
					}
				}
				
			else if (options[0] == 'n' && options[1] == 'v') {
				int n = 0;
				//split the content into tokens on newline
				char* line = strtok(content,"\n");
				while (line != NULL) {
					//count the line numbers
					n++;
					//check if pattern is a substring			
					if (!strstr(line,pattern))
						printf("%d:%s\n", n,line);
					//go to the next line
					line = strtok(NULL,"\n");
					}
				}
				
			else if (options[0] == '-' && options[1] == 'v') {
				//split the content into tokens on newline
				char* line = strtok(content,"\n");
				while (line != NULL) {
					//check if pattern is a substring		
					if (!strstr(line,pattern))
						printf("%s\n",line);
					//go to the next line
					line = strtok(NULL,"\n");
					}
				}
				
			else { perror("Search unsuccesful"); exit(1); }
				
			}
		}
		
	else { 
		perror("At least two arguments expected"); exit(1);
		}
	}

//function to count the frequency of a given substring in a string
int substring_count(char* string, char* substring) {
	int i, j, l1, l2;
	int count = 0;
	int found = 0;

	l1 = strlen(string);
	l2 = strlen(substring);

	for(i = 0; i < l1-l2 + 1; i++) {
		found = 1;
		for(j = 0; j < l2; j++) {
			if(string[i+j] != substring[j]) {
				found = 0;
				break;
				}
			}
		if(found) {
			count++;
			i = i + l2 -1;
			}
		}
	return count;
	}
