#ifndef FILE_VERIFIER_H
#define FILE_VERIFIER_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <unsw/blocking_queue.h>

using namespace boost::iostreams;

/**
 * @brief      Class for processing a file having random strings.
 */
class FileVerifier
{
public:
  explicit FileVerifier():bqueue(),inFile("random.txt")
  {}

  ~FileVerifier()
  {}
  
  void read()
  {
    std::ifstream file(inFile, std::ios_base::in | std::ios_base::binary);
    filtering_istream in;
    if (file.fail()) {
      std::cout << "couldn't open the input file.. please check its name and read permissions\n";
      return;
    }
    try {
      in.push(file);                      // gets the whole file content into an input stream buffer
      for(std::string inputStr; std::getline(in,inputStr);) 
      {
        bqueue.push(inputStr);
        std::cout << "inserted " << inputStr << "\n";
      }
    }
    catch(std::exception& e) {
      std::cout << "exception occurred while reading file\n" << e.what() << "\n";
    }
  }

  void process()
  {
    while (true)
    {
      std::string rstr = bqueue.pop();
      std::cout << "consumed " << rstr << "\n";
    }
  }

private:
  BlockingQueue<std::string> bqueue;
  std::string inFile;     // input file name from where the strings are read
};


#endif