#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>

using namespace std;
using namespace boost::iostreams;

/**
 * @brief      Class for processing a file having random strings.
 */
class FileProcessor
{
public:
  explicit FileProcessor(string infile="random.txt", string outfile="sorted.txt", int delay=1):
    delay(delay),outFile(outfile),inFile(infile)
  {}
  explicit FileProcessor():inFile("random.txt"),outFile("sorted.txt"),delay(1)
  {}

  // Perform an expensive routine, here it sorts strings read from a file.
  // Sorting solution given here has worst performance with O(n^2) runtime!
  virtual string expensiveFunc(string str)
  {
    int d=0, length;
    char *ptr, *result, ch;
    const char* s = str.c_str();
    length = strlen(s);
    result = (char*)malloc(length+1);
    ptr = const_cast<char *>(s);
    for (ch = 'A'; ch <= 'z'; ++ch) {     // iterate through all characters within the range [A - z]
      for (int i=0; i<length; ++i) {
         if (*ptr == ch) {
            *(result+d) = *ptr;           // store the matched characters in result
            d++;
         }
         ++ptr;
      }
      ptr = const_cast<char *>(s);
    }
    *(result+d) = '\0';
    // cout << result << "\n";
    string ret = string(result);
    free(result);
    return ret;
    // wait();                            // additional waiting time, not required I think, since the sorting itself has worse performance
  }

  void run() 
  {   
    stream_buffer<file_sink> buf(outFile);
    ostream out(&buf);
    ifstream file(inFile, std::ios_base::in | std::ios_base::binary);
    int numStr = 0;
    try {
      boost::iostreams::filtering_istream in;
      in.push(file);    // gets the whole file content into a buffer
      for(string inputStr; std::getline(in,inputStr);) {
        string sorted = expensiveFunc(inputStr);
        out << sorted << "\n";
        ++numStr;
        // cout << "Progress " << numStr << " sorted and written\n";      // uncomment to show the progress, in terms of number of strings sorted and written to a file
      }
    }
    catch(...) {
      std::cout << "exception occurred while reading file" << '\n';
    }
  }

private:
  int delay;        // in seconds
  string outFile;   // filename to which the sorted strings are written
  string inFile;    // input file name from where the strings are read
  void wait()
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{delay});
  }
};


#endif