#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <iostream>
#include <math.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>


/**
 * @brief      Class for writing random strings to a file.
 */
class FileWriter
{
public:
  explicit FileWriter(int r1=1, int r2=2, double size=4, const std::string& filename="random.txt"):
    min(r1),max(r2),fsize(size),fname(filename),bytesWritten(0)
  {}
  explicit FileWriter():
    min(1),max(2),fsize(4.0),fname(std::string("random.txt")),bytesWritten(0)
  {}
  ~FileWriter()
  {
    // No resource to release explicitly.
  }

  virtual std::string generateRandomString()
  {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  // additional characters could be added, if required
    std::string rstring;
    int length = min + (rand() % (max-min));
    rstring.resize(length);
    for (int i=0; i<length; ++i) {
      rstring[i] = characters[rand() % characters.length()];
    }
    return rstring;
  }

  void run()
  {
    static boost::shared_mutex mutex;
    static boost::iostreams::stream_buffer<boost::iostreams::file_sink> buf(fname);
    static std::ostream out(&buf);
    static const long int filesize = (long int)(fsize * pow(10,9));  // file size in bytes
    std::cout << "filesize " << filesize << "\n";
    int numStrings = 0;
    while (bytesWritten < filesize) {
      std::string input = generateRandomString();
      boost::unique_lock<boost::shared_mutex> lock{mutex};
      out << input << "\n";
      bytesWritten += (input.length()+1); 
      // std::cout << boost::this_thread::get_id() << " bytesWritten " << bytesWritten << "\n";
      ++numStrings;
      // std::cout << "Progress " << numStrings << " written " << "\n";  // uncomment for showing progress, in terms of nuumber of strings written
    }
    // lock.unlock();
    wait(1);
  }

  virtual void wait(int delay)
  {
    boost::this_thread::sleep_for(boost::chrono::seconds{delay});
  }

private:
  int min;            // minimum length of a random string
  int max;            // maximum length of a random string
  double fsize;       // file size, in GB
  std::string fname;  // file name
  long int bytesWritten;


};


#endif