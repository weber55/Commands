#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#define BUFF_SIZE 4096

using namespace std;

FILE *openFile(const char *filePath) {
  FILE *file;
  file = fopen(filePath, "r");
  if(file == NULL) {
      fprintf(stderr, "Error opening file: %s\n", filePath);
      exit(errno);
  }
  return(file);
} // openFile

void printLine(FILE *file, off_t startline) {
  int fd;
  fd = fileno(file);
  int nread;
  char buffer[BUFF_SIZE];
  lseek(fd,(startline + 1), SEEK_SET);
  while((nread= read(fd, buffer, BUFF_SIZE)) > 0) {
      write(STDOUT_FILENO, buffer, nread);
  }
} // printLine

void printFile(FILE *file, long nlines) {
  off_t fposition;
  fseek(file, 0, SEEK_END);
  fposition= ftell(file);
  off_t index;
  off_t end = fposition;
  long countlines = 0;
  char cbyte;
  for(index = fposition; index >= 0; index --) {
      cbyte = fgetc(file);
      if ((cbyte == '\n') && ((end - index) > 1)) {
	  countlines ++;
	  if(countlines == nlines) {
	      break;
	  }
      }
      fposition--;
      fseek(file, fposition, SEEK_SET);
  }
  printLine(file, fposition);
  fclose(file);
} // printFile

int main(int argc, char *argv[]) {
  FILE *file;
  if ((argc == 1) || (strcmp(argv[1], "-") == 0)) {
    int x;
    while (1) {
      cin >> x;
    }
  } // standard input
  else if (argc == 2) {
    file = openFile(argv[1]);
    printFile(file, 10);
  } // tail file
  else if ((argc == 3) && (strcmp(argv[1], "-f") == 0)) {
    file = openFile(argv[2]);
    printFile(file, 10);
    int x;
    while (1) {
      cin >> x;
    }
  } // tail -f file
  else if ((argc == 4) && (strcmp(argv[1], "-c") == 0)) {
    char *p;
    long number = strtol(argv[2], &p, 10);
    int number2 = number / 8;
    file = openFile(argv[3]);
    printFile(file, number2);
  } // tail -c number file
  else if ((argc == 4) && (strcmp(argv[1], "-n") == 0)) {
    char *p;
    long number = strtol(argv[2], &p, 10);
    int number2 = number;
    file = openFile(argv[3]);
    printFile(file, number2);
  } // tao; -n number file
  else if ((argc == 5) && (strcmp(argv[1], "-f") == 0) && (strcmp(argv[2], "-c") == 0)) {
    int x;
    char *p;
    long number = strtol(argv[2], &p, 10);
    int number2 = number / 8;
    file = openFile(argv[4]);
    printFile(file, number2);
    while (1) {
      cin >> x;
    }
  } // tail -f -c number file
  else if ((argc == 5) && (strcmp(argv[1], "-f") == 0) && (strcmp(argv[2], "-n") == 0)) {
    int x;
    char *p;
    long number = strtol(argv[3], &p, 10);
    int number2 = number;
    file = openFile(argv[4]);
    printFile(file, number2);
    while (1) {
      cin >> x;
    } 
  } // tail -f -n number file 
  else {
    cout << "Error: Input invalid.\n";
  } // error
  return 0;

} // main
