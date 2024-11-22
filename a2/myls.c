#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 100
#define MAX_BYTES 500

void ls_dir (char*);
void ls_long (char*);
void ls_file (char*);
void printFileProperties(struct stat);

int main (int argc, char* argv[]) {
	if (argc == 1) {
		ls_dir(".");
		exit(1);
		}
	
	int opCount = 0;
	if (strcmp(argv[1],"-l")==0) {
		opCount = 1;
		if (argc-opCount == 1) {
			ls_long(".");
			}
			
		else if (argc-opCount == 2) {
			ls_long(argv[1+opCount]);
			}
			
		else {
			for (int i=1+opCount; i<argc; i++) {
				if (i==1+opCount)
					printf("%s: \n",argv[i]);
				else
					printf("\n%s: \n",argv[i]);
				ls_long(argv[i]);
				}
			}
		}
	
	else {	
		if (argc-opCount == 1) {
			//call function to list contents of curr dir
			ls_dir(".");
			}
			
		else if (argc-opCount == 2) {
			ls_dir(argv[1]);
			}
			
		else {
			for (int i=1; i<argc; i++) {
				printf("%s: \n",argv[i]);
				ls_dir(argv[i]);
				}
			}
		}
	}

//function to list contents of a given dir
void ls_dir (char* dir) {
	DIR *folder;
	struct dirent *entry;
	
	//open given dir
	folder = opendir(dir);
	if (folder == NULL) { 
		perror("Could not open directory.");
		exit(1);
		}
	//read and print contents of dir
	while (entry = readdir(folder)) {
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0)
			printf(" %s\n", entry->d_name);
		}
	
	//close dir
	closedir(folder);
	//printf("\n");
	}
	
//function to list contents of a given dir in long format
void ls_long (char* dir) {
	DIR *folder;
	struct dirent *entry;
	struct stat fileStats;
	
	//open given dir
	folder = opendir(dir);
	if (folder == NULL) { 
		perror("Could not open directory");
		exit(1);
		}
	//read and print contents of dir
	while (entry = readdir(folder)) {
		if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0) {
			//ls_file(entry->d_name);
			stat(entry->d_name,&fileStats);
			printFileProperties(fileStats);
			printf("%s\n",entry->d_name);
			}
		}
	
	//close dir
	closedir(folder);
	}

//function to print the file properties
void printFileProperties(struct stat stats) {
	struct tm dt;
	
	//printf("%ld ", stats.st_ino);
	
	//printf("%o ", stats.st_mode);
	
	printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
	printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
	printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
	printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
	printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
	printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
	printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
	printf( (stats.st_mode & S_IROTH) ? "r" : "-");
	printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
	printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
	
	printf("%ld ", stats.st_nlink);
	
	printf("%ld ", stats.st_size);

	//get file creation time in seconds and convert seconds to date and time format
	dt = *(gmtime(&stats.st_ctime));
	printf("%d-%d-%d %d:%d:%d ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);

	// File modification time
	dt = *(gmtime(&stats.st_mtime));
	printf("%d-%d-%d %d:%d:%d ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, dt.tm_hour, dt.tm_min, dt.tm_sec);
	}
