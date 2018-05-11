#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
  if ((argc == 4) && (strcmp(argv[1], "-s") == 0)) {
    const char *targetfile = argv[2];
    const char *linkfile = argv[3];
    int hlink = symlink(targetfile, linkfile);
    return hlink;
  } // hard link
  else if (argc == 3) {
    const char *targetfile = argv[1];
    const char *linkfile = argv[2];
    int slink = link(targetfile, linkfile);
    return slink;
  } // symbolic link
  else {
    cout << "file could not be found\n";
  }
  return 0;
} // main
