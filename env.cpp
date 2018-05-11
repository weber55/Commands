#include <ios>
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * Entry point for the program which get the environmental variables
 * and prints them out
 */
int main(const int argc, const char * argv [], const char * envp []) {
  cout.setf(std::ios::unitbuf);
  for (int i = 0; envp[i] != nullptr; ++i) {
    cout << envp[i] << endl;
  } // for
  return EXIT_SUCCESS;
} // main
