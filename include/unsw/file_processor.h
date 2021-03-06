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

using namespace boost::iostreams;
using namespace std; 

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


template<typename T> 
T FileProcessor::sortAndMerge(const T& left, const T& right)
{
  int l=0, r=0;
  T res;
  // iterate through the elements of left and right arrays, adding the sorted result in res
  while (l != left.size() && r != right.size()) {
    if (left[l] > right[r]) {
      res.push_back(right[r]);
      ++r;
    }
    else {
      res.push_back(left[l]);
      ++l;
    }
  }
  // for the elements which are left over in either of the two arrays, we append them directly to res
  while (l != left.size()) {
    res.push_back(left[l]);
    ++l;
  }
  while (r != right.size()) {
    res.push_back(right[r]);
    ++r;
  }
  return res;
}


// Merge sort with O(nlogn) runtime performance.
template<typename T> 
T FileProcessor::mergeSort(const string& input)
{
  if (input.size() <= 1) return input;
  T left, right, res;
  int mid = input.size() / 2;
  // divide the list of elements in two halves
  for (int i=0; i<mid; ++i) left.push_back(input[i]);
  for (int i=mid; i<input.size(); ++i) right.push_back(input[i]);
  // carry out divide and conquer, bottom-up approach
  left = mergeSort<T>(left);
  right = mergeSort<T>(right);
  // sort and merge the left and right arrays
  res = sortAndMerge<T>(left,right);
  return res;
}


void FileProcessor::run()
{   
  static stream_buffer<file_sink> buf(outFile);
  static ostream out(&buf);
  int numStr = 0;
  ifstream file(inFile, std::ios_base::in | std::ios_base::binary);
  boost::iostreams::filtering_istream in;
  if (file.fail()) {
    cout << "couldn't open the input file.. please check its name and read permissions\n";
    return;
  }
  try {
    in.push(file);                      // gets the whole file content into an input stream buffer
    for(string inputStr; std::getline(in,inputStr);) {
      string sorted = expensiveFunc(inputStr);
      out << sorted << "\n";
      ++numStr;
      // cout << "Progress " << numStr << " sorted and written\n";      // uncomment to show the progress, in terms of number of strings sorted and written to a file
    }
  }
  catch(std::exception& e) {
    cout << "exception occurred while reading file\n" << e.what() << "\n";
  }
}

#endif