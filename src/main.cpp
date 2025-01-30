#include "..\include\crumpir.hpp"

/*
Grayscale image generator example from CLI:
  crumpir.exe "input_file.pgm" // defaults to 64x64 format
  crumpir.exe "input_file.pgm" -w 32 -h 32 // generates only CLI ASCII grayscale art
  crumpir.exe "input_file.pgm" "output_file.txt" -width 32 -height 32
*/

int main(int argc, char** argv) {
  CrumpirGenerator(argc, argv);
  return 0;
}