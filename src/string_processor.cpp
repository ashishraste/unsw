// #include <iostream>
#include "unsw/file_processor.h"

using namespace std;
using namespace boost::iostreams;

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
  static boost::shared_mutex mutex;
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


/**
 * @brief      Program to read strings from a file, sort them and write them to another file.
 *
 * @param[in]  argc  Number of arguments given as input to this program.
 * @param      argv  Input arguments, requires three of them.
 *
 * @return     Returns 0 (quits peacefully), on success.
 *             Writes the sorted strings to a file (with given name), created in the directory from where this program is run.
 */
int main(int argc, char** argv) 
{
  if (argc != 4) {
    std::cout << "Usage : From build/ directory \n ./string_generator processing-delay input-filename output-filename\n";
    return -1;
  }
  string inFile = string(argv[1]);
  string outFile = string(argv[2]);
  int delay = stoi(argv[3]);

  FileProcessor fp(inFile, outFile, delay); 
  fp.run();

  cout << "exiting.. \n";
  return 0;
}