#include <cstdlib>
#include <ios>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cmath>
using namespace std;

void getToday(int &day, int &month, int &year);
void printMonth(int day, int month, int year);
void printYear(int day, int month, int year);
int gregorianDay(int day, int month, int year);
int julianDay(int day, int month, int year);
bool isLeapYear(int year);

const char days[7][3] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
const char months[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

/**
 * Entry point of program which handles the command line args
 */
int main(int argc, const char* argv[]){
  cout.setf(std::ios::unitbuf);
  int td, tm, ty, d, y, m, space;
  getToday(td, tm, ty);
  switch(argc){
  case 1: // today's date
    space = (21 - strlen(months[tm-1]) - 4) / 2;
    for (int i = 0; i < space; i++){
      cout << " ";
    }
    cout <<  months[tm-1] << " " << ty <<  endl;
    printMonth(td, tm, ty);
    break;
  case 2: // certain year
    y = atoi(argv[1]);
    if ((y < 1)||(y > 9999)){
      cout << "cal: illegal year value: use 1-9999" << endl;
      exit(EXIT_FAILURE);
    }
    printYear(td, tm, y);
    break;
  case 3: // certain month and year
    m = atoi(argv[1]);
    y = atoi(argv[2]);
    if ((m < 1)||(m > 12)){
      cout << "cal: illegal month value: use 1-12" << endl;
      exit(EXIT_FAILURE);
    }
    if ((m == tm)&&(y == ty)){
      d = td;
    }
    else {
      d = 0;
    }
    space = (21 - strlen(months[m-1]) - 4) / 2;
    for (int i = 0; i < space; i++){
      cout << " ";
    }
    cout <<  months[m-1] << " " << y <<  endl;
    printMonth(d, m, y);
    break;
  }
  return EXIT_SUCCESS;
} // main

/**
 * Gets today's day of month, month, and year
 */ 
void getToday(int &day, int &month, int &year){
  time_t today = time(0);
  tm *ltm = localtime(&today);
  day = ltm->tm_mday;
  month = 1 + ltm->tm_mon;
  year = 1900 + ltm->tm_year;
} // getToday

/**
 * Prints the calendar for specified month of year
 * If today's date is included, highlight it
 */
void printMonth(int day, int month, int year){
  for (int i = 0; i < 8; i++){
    cout << days[i] << " ";
  }
  cout << endl;

  int dayCount = 1;
  int monthLength = 0;
  switch (month){
  case 1: case 3: case 5: case 7: case 8: case 10: case 12:
    monthLength = 31;
    break;
  case 4: case 6: case 9: case 11:
    monthLength = 30;
    break;
  case 2: 
    if (isLeapYear(year)){
      monthLength = 29;
    }
    else{
      monthLength = 28;
    }
    break;
  }
  int td, tm, ty;
  getToday(td, tm, ty);

  if ((year < 1752)||((year==1752)&&(month < 9))){ // Julian
    for (int i = 0; i < 7; i++){
      for (int j = 0; j < 7; j++){
	if (j == julianDay(dayCount, month, year)){
	  if (dayCount < 10){
	    if ((dayCount == td)&&(month == tm)&&(year == ty)){
	      cout << "\033[30;47m " << dayCount << "\033[0m" << " ";
	    }
	    else{
	      cout << " " << dayCount << " ";
	    }
	  }
	  else{
	    if ((dayCount == td)&&(month == tm)&&(year == ty)){
	      cout << "\033[30;47m" << dayCount << "\033[0m" << " ";
	    }
	    else{
	      cout << dayCount << " ";
	    }
	  }
	  dayCount++;
	}
	else {
	  cout << "   ";
	}
	if (dayCount > monthLength) break;
      }
      if (dayCount > monthLength) break;
      cout << endl;
    }  
    cout << endl;
  }
  else if ((year > 1752)||((year == 1752)&&(month > 9))){ // Gregorian
    for (int i = 0; i < 7; i++){
      for (int j = 0; j < 7; j++){
	if (j == gregorianDay(dayCount, month, year)){
	  if (dayCount < 10){
	    if ((dayCount == td)&&(month == tm)&&(year == ty)){
	      cout << "\033[30;47m " << dayCount << "\033[0m" << " ";
	    }
	    else{
	      cout << " " << dayCount << " ";
	    }
	  }
	  else{
	    if ((dayCount == td)&&(month == tm)&&(year == ty)){
	      cout << "\033[30;47m" << dayCount << "\033[0m" << " ";
	    }
	    else{
	      cout << dayCount << " ";
	    }
	  }
	  dayCount++;
	}
	else {
	  cout << "   ";
	}
	if (dayCount > monthLength) break;
      }
      if (dayCount > monthLength) break;
      cout << endl;
    }
    cout << endl;
  }
  else if ((year == 1752)&&(month == 9)){ // September 1752
    cout << "       1  2 14 15 16" << endl;
    cout << "17 18 19 20 21 22 23" << endl;
    cout << "24 25 26 27 28 29 30" << endl;
  }
  cout << endl;
} // printMonth

/**
 * Print the calendar for the entire year
 */
void printYear(int day, int month, int year){
  int space = (21 - 4) / 2;
    for (int i = 0; i < space; i++){
      cout << " ";
    }
  cout << year << endl;
  cout << endl;
  for (int m = 1; m < 13; m++){
    int space = (21 - strlen(months[m-1])) / 2;
    for (int i = 0; i < space; i++){
      cout << " ";
    }
    cout <<  months[m-1] <<  endl;
    printMonth(day, m, year);
  }
} // printYear

/**
 * get number of days since sunday in the Julian calendar
 */
int julianDay(int day, int month, int year){
  int a = floor((14 - month) / 12);
  int y = year + 4800 - a;
  int m = month + 12 * a - 3;
  int j = day + floor((153 * m + 2) / 5) + (365 * y) + floor(y / 4) - 32083;
  return (j + 1) % 7;
} // julianDay

/**
 * get number of days sicne sunday in the Gregorian calendar
 */
int gregorianDay(int day, int month, int year){
  struct tm tm;
  char date [11];
  sprintf(date, "%d-%d-%d", year, month, day);  
  strptime(date, "%Y-%m-%d", &tm);
  return tm.tm_wday;    
} // gregorianDay

/**
 * return whether or not a year is a leap year
 */
bool isLeapYear(int year){
  return ((year % 4) == 0);
}
