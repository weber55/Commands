#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <pwd.h>
#include <grp.h>
#include <ios>

using namespace std;

void showList(char *filename, bool isAll, bool isLong);
void longFormat(char *filename);

/**
 * For sorting the vectors alphabetically and ignoring case
 */
bool compareNoCase (string first, string second){
  return (strcasecmp(first.c_str(), second.c_str()) <= 0);
}

/**
 * Entry point for the program
 */
int main(int argc, char *argv[]){
  cout.setf(std::ios::unitbuf);
  if (argc == 1){
    char filename[] = "./";
    showList(filename, false, false);
    exit(EXIT_SUCCESS);
  } // if

  bool isAll = false;
  bool isLong = false;
  int c;
  int min = 1;
  opterr = 0;
  while ((c = getopt (argc, argv, "al")) != -1){
    switch(c){
    case 'a':
      isAll = true;
      min = 2;
      break;
    case 'l':
      isLong = true;
      min = 2;
      break;
    case '?':
      cout << "ls: invalid option" << endl;
      exit(EXIT_FAILURE);
      break;
    } // switch
  }
  
  if ((isAll || isLong)&&(argc < 3)){
    char filename[] = "./";
    showList(filename, isAll, isLong);
    exit(EXIT_SUCCESS);
  }
  if ((isAll || isLong)&&(argc < 4)){
    showList(argv[2], isAll, isLong);
    cout << "\n";
    exit(EXIT_SUCCESS);
  }
  if ((!isAll&&!isLong)&&(argc < 3)){
    showList(argv[1], isAll, isLong);
    exit(EXIT_SUCCESS);
  }

  vector<string> dirs;
  vector<string> other;
  for (int i = min; i < argc; i++){
    struct stat sb;
    lstat(argv[i], &sb);
    if (S_ISDIR(sb.st_mode)){
      dirs.push_back(argv[i]);
    }
    else {
      other.push_back(argv[i]);
    }
  } // for
  sort(dirs.begin(), dirs.end(), compareNoCase);
  sort(other.begin(), other.end(), compareNoCase);
  for(string n : other){
    char *f = &n[0u];
    showList(f, isAll, isLong);
  }
  for(string m : dirs){
    cout << "\n" << m << ":" << endl;
    char *f = &m[0u];
    showList(f, isAll, isLong);
  }
  return EXIT_SUCCESS;
} // main


/**
 * If the given file is a directory, lists all of the files
 * contained in the appropriate format. Otherwise, displays
 * the name of the file.
 */
void showList(char *filename, bool isAll, bool isLong){
  struct stat sb;
  if (lstat(filename, &sb) < 0){
    string nm = filename;
    string err = "ls: cannot access " + nm;
    perror(err.c_str());
  }
  else {
    if (S_ISDIR(sb.st_mode)){
      vector<string> files;
      DIR *dirp;
      struct dirent *entp;
      int total = 0;
      if ((dirp = opendir (filename)) != NULL) {
	while ((entp = readdir (dirp)) != NULL) {
	  string fn;
	  string fa = filename;
	  if (!isAll){
	    char *name = entp->d_name;
	    if (name[0] != '.'){
	      string name = entp->d_name;
	      files.push_back(name);
	      if (filename[strlen(filename)-1] != '/'){
		fn = fa + "/" + name;
	      }
	      else{
		fn = filename + name;
	      }
	      char *f = &fn[0u];
	      struct stat sb1;
	      if (lstat(f, &sb1) == 0){
		total += sb1.st_blocks;
	      }
	    }
	  }
	  else if (isAll){
	    string name = entp->d_name;
	    files.push_back(name);
	    if (filename[strlen(filename)-1] != '/'){
	      fn = fa + "/" + name;
	    }
	    else{
	      fn = filename + name;
	    }
	    char *f = &fn[0u];
	    struct stat sb1;
	    if (lstat(f, &sb1) == 0){
	      total += sb1.st_blocks;
	    }
	  }
	}
	closedir (dirp);
      }
      sort(files.begin(), files.end(), compareNoCase);
      if (isLong){
	total /= 2;
	cout << "total " << total << endl;
      }
      for(string n : files){
	if (isLong){
	  string fn;
	  string fa = filename;
	  if (filename[strlen(filename)-1] != '/'){
	    fn = fa + "/" + n;
	  }
	  else{
	    fn = filename + n;
	  }
	  char *f = &fn[0u];
	  longFormat(f);
	  cout << n << endl;
	}
	else{
	  cout << n << endl;
	}
      }
    } // ISDIR
    else {
      if (isLong){
	longFormat(filename);
	cout << filename << endl;
      }
      else{
	cout << filename << endl;
      }
    }
  }
} // showList

/**
 * Shows the additional info for the long format
 */
void longFormat(char *filename){
  struct stat sb;
  stat(filename, &sb);
  const char *specPerm;
  switch (sb.st_mode & S_IFMT) {
  case S_IFBLK:
    specPerm = "b";
    break;
  case S_IFCHR:
    specPerm  = "c";
    break;
  case S_IFDIR:
    specPerm = "d";
    break;
  case S_IFIFO:
    specPerm = "p";
    break;
  case S_IFLNK:
    specPerm = "l";
    break;
  case S_IFREG:
    specPerm = "-";
    break;
  case S_IFSOCK:
    specPerm = "s";
    break;
  }
  mode_t perms = sb.st_mode & 07777;
  printf(specPerm);
  printf((perms & S_IRUSR) ? "r": "-");
  printf((perms & S_IWUSR) ? "w": "-");
  printf((perms & S_IXUSR) ? "x": "-");
  printf((perms & S_IRGRP) ? "r": "-");
  printf((perms & S_IWGRP) ? "w": "-");
  printf((perms & S_IXGRP) ? "x": "-");
  printf((perms & S_IROTH) ? "r": "-");
  printf((perms & S_IWOTH) ? "w": "-");
  printf((perms & S_IXOTH) ? "x": "-");
  printf(". ");
  cout << sb.st_nlink << " ";
  struct passwd *pw;
  pw = getpwuid(sb.st_uid);
  cout << pw->pw_name << " "; 
  struct group *gr;
  gr = getgrgid(sb.st_gid);
  cout << gr->gr_name << " ";
  cout << sb.st_size << " ";
  struct tm *lt;
  lt = localtime(&sb.st_mtime);
  char tbuf[80];
  strftime(tbuf, 80, "%b %d %R", lt);
  cout << tbuf << " ";
} //longFormat

