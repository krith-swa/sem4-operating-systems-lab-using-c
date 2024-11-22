#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_BYTES 500

int main (int argc, char* argv[]){   
	if (argc == 1) {
		perror("Two arguments expected"); exit(1);
		}
	
	int opCount = 0;
	if (strcmp(argv[1],"-i") == 0) {
			opCount++;
			}
	
	if (argc - opCount == 3){      
		char src[MAX_LENGTH], dest[MAX_LENGTH], option[2];
		int src_fd, src_sz, dest_fd, dest_sz; 
		char *c = (char *) calloc(100, sizeof(char));
		
		//check if command is to operating in interactive mode
		if (strcmp(argv[1],"-i") == 0) {
			strcpy(src,argv[2]);
			strcpy(dest,argv[3]);
			
			//check if dest file exists
			dest_fd = open(dest,O_RDONLY);
			//ask the user if dest file is to be overwritten or not
			if (dest_fd >= 0) {
				char ch;
				printf("cp: overwrite '%s'? ",dest);
				scanf("%c",&ch);
				if (ch != 'y' && ch != 'Y')
					exit(1);
				}
			}
		else {
			strcpy(src,argv[1]);
			strcpy(dest,argv[2]);
			}
		
		//find file desciptor for src file
		src_fd = open(src,O_RDONLY);
		//include error msg for case when src file not found
		if (src_fd < 0) { perror("Command unsuccessful. Source file not found."); exit(1); } 
		 
		//save the contents of src file in a string
		src_sz = read(src_fd,c,MAX_BYTES);  
		c[src_sz] = '\0'; 
		
		//close src file
		close(src_fd);
		
		//create dest file
		dest_fd = open(dest,O_WRONLY | O_CREAT | O_TRUNC,0754);
		//include error msg for case when dest file not created
		if (dest_fd < 0) { perror("Command unsuccessful. Destination file not created."); exit(1); }
		
		//write the saved contents of the src file from the string to the dest file
		dest_sz = write(dest_fd,c,strlen(c)); 
		 
		//close dest file
		close(dest_fd);
		}
		
	else if (argc - opCount > 3){      
		perror("Too many arguments supplied"); exit(1);
		}
		
	else { 
		perror("Two arguments expected"); exit(1);
		}
	}

