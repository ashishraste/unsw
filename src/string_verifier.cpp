#include <iostream>
#include <unsw/file_verifier.h>

using namespace std;

int main()
{
  FileVerifier fv;
  boost::thread rt(boost::bind(&FileVerifier::read, &fv));
  boost::thread pt1(boost::bind(&FileVerifier::process, &fv));
  rt.join();
  pt1.join();
  return 0;
}