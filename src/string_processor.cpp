#include <iostream>
#include "unsw/file_processor.h"

using namespace std;

/**
 * @brief      Program to read strings from a file, sort them and write them to another file.
 *
 * @param[in]  argc  Number of arguments given as input to this program.
 * @param      argv  Input arguments, requires three of them.
 *
* @return     Returns 0 (quits peacefully), on success.
 *            Writes the sorted strings to a file (with given name), created in the directory from where this program is run.
 */
int main(int argc, char** argv) 
{
  if (argc != 4) {
    cout << "Usage : From build/ directory \n ./string_generator processing-delay input-filename output-filename\n";
    return -1;
  }
  string inFile = string(argv[1]);
  string outFile = string(argv[2]);
  int delay = stoi(argv[3]);

  FileProcessor fp(inFile, outFile, delay); 
  fp.run();
  return 0;
}