#include <iostream>
#include "unsw/file_writer.h"

using namespace std;

/**
 * @brief      Program to write randomly generated strings to a given file, uses single thread.
 *
 * @param[in]  argc  Number of arguments given as input to this program.
 * @param      argv  Input arguments, requires four of them.
 *
 * @return     Returns 0 (quits peacefully), on success.
 *             Writes into a file (with given name) created in the directory from where this program is run.
 */
int main(int argc, char** argv) 
{
  if (argc != 5) {
    cout << "Usage : From build/ directory do the following \n ./string_generator min-length max-length total-size-of-strings(GB) filename\n";
    return -1;
  }
  int min = stoi(string(argv[1]),nullptr,0);
  int max = stoi(string(argv[2]),nullptr,0);
  int totalSize = stoi(string(argv[3]),nullptr,0);
  string filename = string(argv[4]);

  srand(time(NULL));  // random seed for generating random strings

  FileWriter writer(min,max,totalSize,filename);
  writer.run();

  // Note : using multiple threads doesn't speed up the writing process.
  // Would only cause unnecessary switching between threads, which is not expensive though.
   
  // boost::thread writerOne(boost::bind(&FileWriter::run,&writer));
  // boost::thread writerTwo(boost::bind(&FileWriter::run,&writer));
  // writerOne.join();
  // writerTwo.join();

  cout << "finished generating a file with random strings.. exiting\n";
  return 0;  
}
