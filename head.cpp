#include <cerrno>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <ios>

using namespace std;

void printFile(const string &, int);
void readInput(int);

/**
 * Entry point for the program
 */
int main(int argc, char *argv[]){
  cout.setf(std::ios::unitbuf);
  int nLines = 10;
  if (argc < 2){
    readInput(10);
    exit(EXIT_SUCCESS);
  }
  
  int c;
  opterr = 0;
  while ((c = getopt(argc, argv, "n:")) != -1){
    switch(c){
    case 'n':
      nLines = atoi(optarg);
      break;
    case '?':
      if (optopt == 'n'){
	cout << "head: option requires an argument -- 'n'" << endl;
	exit(EXIT_FAILURE);
      }
    } // switch
  }

  if (optind == argc){
    readInput(nLines);
    exit(EXIT_SUCCESS);
  }

  for (int i = optind; i < argc; i++){
    if (argc > optind+1){
      if ((argv[i][0] == '-')&&(argv[i][1] == '\0')){
	cout << "==> standard input <==" << endl;
      }
      else {
	cout << "==> " << argv[i] << " <==" << endl;
      }
    }
    if ((argv[i][0] == '-')&&(argv[i][1] == '\0')){ 
      readInput(nLines);
    }
    else{	
      printFile(argv[i], nLines);
    }
    if (i < argc-1){
      cout << "\n";
    }
  }
  
  return EXIT_SUCCESS;
} // main

/**
 * Standard output of the contents of a file
 * given a file name and number of lines
 */
void printFile(const string &filename, int nLines){
  char buffer[1];
  int fd = -1;
  int numBytes = 0;
  if ((fd = open(filename.c_str(), O_RDONLY)) == -1){ 
    string str = "head: cannot open '" + filename + "' for reading";
    perror(str.c_str());
  }
  int nBreak = 0;
  while ((numBytes = read(fd, buffer, 1)) > 0) {
    if (buffer[0] == '\n'){
      nBreak++;
    }
    write(STDOUT_FILENO, buffer, numBytes);
    if (nBreak >= nLines){
      break;
    }
  } // while
} // printFile

/**
 * Reads from standard input
 */
void readInput(int nLines){
  char buffer[1];
  int numBytes = 0;
  int nBreak = 0;
  while ((numBytes = read(STDIN_FILENO, buffer, 1)) > 0){
    if (buffer[0] == '\n'){
      nBreak++;
    }
    write(STDOUT_FILENO, buffer, numBytes);
    if (nBreak >= nLines){
      break;
    }
  }
} // readInput
