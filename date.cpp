#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <locale>

using namespace std;

int main(int argc, char *argv[]) {  
  if (argc == 1) {
    time_t current_time;
    char *c_time;
    current_time = time(NULL);
    c_time = ctime(&current_time);
    cout << c_time;
  } // default
  else if (strncmp(argv[1], "+", 1) == 0) {
    argv[1]++;
    char buffer [80];
    time_t rawtime = time(NULL);
    strftime(buffer, 80, argv[1], localtime(&rawtime));
    cout << buffer << '\n';
  } // formatted
  else {
    cout << "Error: date could not be formatted.\n";
  } // error
  return EXIT_SUCCESS;

} // main
