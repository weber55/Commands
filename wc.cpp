#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[]) {
  int lines = 0; 
  int chars = 0; 
  int words = 0;
  int ch;
  FILE *file;
  if ((argc == 1) || (strcmp(argv[1], "-") == 0)) {
    int x;
    cin >> x;
  } // ./wc -
  if (argc == 2) {
    file = fopen(argv[1], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[1]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
	words++;
	lines++;
      }
      if (ch == '\t' || ch == ' ') {
	words++;
      }
      chars++;
    }
    printf(" %d %d %d %s\n", lines, words, chars, argv[1]);
  } // ./wc file
  else if ((argc == 3) && (strcmp(argv[1], "-c") == 0)) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[2]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
	words++;
	lines++;
      }
      if (ch == '\t' || ch == ' ') {
	words++;
      }
      chars++;
    }
    printf("%d %s\n", chars, argv[2]);
  } // ./wc -c file
  else if ((argc == 3) && (strcmp(argv[1], "-l") == 0)) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[2]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %s\n", lines, argv[2]); 
  } // ./wc -l file
  else if ((argc == 3) && (strcmp(argv[1], "-m") == 0)) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[2]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %s\n", chars, argv[2]);
  } // ./wc -m file
  else if ((argc == 3) && (strcmp(argv[1], "-w") == 0)) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[2]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %s\n", words, argv[2]);
  } // ./wc -w file
  else if ((argc == 3) && (strcmp(argv[1], "-lw") == 0)) {
    file = fopen(argv[2], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[2]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %s\n", lines, words, argv[2]);
  } // ./wc -lw file
  else if ((argc == 4) && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[2], "-l") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %s\n", chars, lines, argv[3]);
  } // ./wc -c -l file
  else if ((argc == 4) && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[2], "-w") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %s\n", chars, words, argv[3]);
  } // ./wc -c -w file
  else if ((argc == 4) && (strcmp(argv[1], "-c") == 0) && (strcmp(argv[2], "-lw") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %d %s\n", chars, lines, words, argv[3]);
  } // ./wc -c -lw file
  else if ((argc == 4) && (strcmp(argv[1], "-m") == 0) && (strcmp(argv[2], "-l") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %s\n", chars, lines, argv[3]);
  } // ./wc -m -l file
  else if ((argc == 4) && (strcmp(argv[1], "-m") == 0) && (strcmp(argv[2], "-w") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %s\n", chars, words, argv[3]);
  } // ./wc -m -w file
  else if ((argc == 4) && (strcmp(argv[1], "-m") == 0) && (strcmp(argv[2], "-lw") == 0)) {
    file = fopen(argv[3], "r");
    if (file == NULL) {
      fprintf(stderr, "Unable to open file %s. Exiting.\n", argv[3]);
      exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        words++;
        lines++;
      }
      if (ch == '\t' || ch == ' ') {
        words++;
      }
      chars++;
    }
    printf("%d %d %d %s\n", chars, lines, words, argv[3]);
  } // ./wc -m -lw file
  else {
    fprintf(stderr, "Unable to open file. Exiting.\n");
    exit(1);
  } // error
  fclose(file);
  return 0;

} // main
