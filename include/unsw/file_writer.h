#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <iostream>
#include <string>
#include <math.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

using namespace std;
using namespace boost::iostreams;

// boost::shared_mutex mutex;

/**
 * @brief      Class for writing random strings to a file.
 */
class FileWriter
{
public:
  explicit FileWriter(int r1=1, int r2=2, int size=4, const string& filename="random.txt"):
    min(r1),max(r2),fsize(size),fname(filename)
  {}
  explicit FileWriter():
    min(1),max(2),fsize(4),fname(string("random.txt"))
  {}
  ~FileWriter()
  {}

  virtual string generateRandomString()
  {
    static string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  // additional characters could be added, if required
    string rstring;
    int length = min + (rand() % (max-min));
    rstring.resize(length);
    for (int i=0; i<length; ++i) {
      rstring[i] = characters[rand() % characters.length()];
    }
    return rstring;
  }

  void run()
  {
    stream_buffer<file_sink> buf(fname);
    ostream out(&buf);
    static long int filesize = fsize * pow(10,9);  // file size in bytes
    static long int i;
    int numStrings = 0;
    for (i=0; i<filesize; ++i) {
      string input = generateRandomString();
      out << input << "\n";
      i += (input.length()); 
      ++numStrings;
      // cout << "Progress " << numStrings << " written " << "\n";  // uncomment for showing progress, in terms of nuumber of strings written
    }
  }

private:
  int min;        // minimum length of a random string
  int max;        // maximum length of a random string
  int fsize;      // file size, in GB
  string fname;   // file name
};


#endif