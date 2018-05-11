#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <ios>
using namespace std;

/**
 * Get the current working directory and prints it out
 */
int main(){
  cout.setf(std::ios::unitbuf);
  char *cwd;
  char buffer[PATH_MAX + 1];
  cwd = getcwd(buffer, PATH_MAX+1);
  if (cwd != NULL){
    cout << cwd << endl;
  }
  return EXIT_SUCCESS;
} // main
