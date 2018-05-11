#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
#include <iostream>

using namespace std;

bool makedirp(const char* path, mode_t mode = 0755) {
  char* p = const_cast<char*>(path);
  while (*p != '\0') {
    p++;
    while(*p != '\0' && *p != '/') {
      p++;
    }
    char cp2 = *p;
    *p = '\0';
    if(mkdir(path, mode) != 0 && errno != EEXIST) {
      *p = cp2;
      return false;
    }
    *p = cp2;
  }
  return true;
} //makedirp

int main(int argc, char *argv[]) {
  if (argc == 2) {
    if (mkdir(argv[1], 0755) == 0) {
      return 0;
    }
    else {
      printf("Error: Cannot create directory\n");
    } 
  } // ./mkdir dir
  else if ((argc == 3) && (strcmp(argv[1], "-p") == 0)) {
    makedirp(argv[2], 0755) == 0;
  } // ./mkdir -p dir
  else if ((argc == 4) && (strcmp(argv[1], "-m") == 0)) {
    char *p;
    long mode = strtol(argv[2], &p, 0);
    int modei = mode;
    if (mkdir(argv[3], modei) == 0) {
      return 0;
    }
    else {
      printf("Error: Cannot create directory\n");
    }
  } // ./mkdir -m mode dir
  else if ((argc == 5) && (strcmp(argv[1], "-p") == 0) && (strcmp(argv[2], "-m") == 0)) {
    char *p;
    long mode = strtol(argv[3], &p, 0);
    int modei = mode;
    makedirp(argv[4], modei);
  } // ./mkdir -p -m mode dir
  else {
    printf("Error: Cannot create directory\n"); 
  } // error

  return 0;

} // main
