#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>


/**
 * @brief      Class for processing a file having random strings.
 */
class FileProcessor
{
public:
  explicit FileProcessor(std::string infile="random.txt", std::string outfile="sorted.txt", int delay=1):
    delay(delay),outFile(outfile),inFile(infile)
  {}
  explicit FileProcessor():inFile("random.txt"),outFile("sorted.txt"),delay(1)
  {}

    // Sorting solution given here has worst runtime performance of O(n^2)!
  virtual std::string naiveSort(std::string str)
  {
    int d=0, length;
    char *ptr, *result, ch;
    const char* s = str.c_str();
    length = strlen(s);
    result = (char*)malloc(length+1);
    ptr = const_cast<char *>(s);          // removing const, ugly hack
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
    std::string ret = std::string(result);
    free(result);
    return ret;
  }
  
  template<typename T>
  T sortAndMerge(const T& left, const T& right);

  template<typename T>
  T mergeSort(const std::string& input);
  void run();

  // Perform an expensive routine, here it sorts strings read from a file.
  virtual std::string expensiveFunc(const std::string& str)
  {
    std::string sorted = mergeSort<std::string>(str);
    wait();                               // additional waiting time
    return sorted;
  }
  
  virtual void wait()
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{delay});
  }

private:
  int delay;              // in seconds
  std::string outFile;    // filename to which the sorted strings are written
  std::string inFile;     // input file name from where the strings are read
};


#endif