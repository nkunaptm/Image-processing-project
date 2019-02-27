#include "Image.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <tr1/unordered_map>

using namespace NKNPET001;
typedef unsigned char uchar_size;

int main(int argc, char *argv[]) {
  string check = argv[1];
  if (check == ("-a")){
    Image x;
    x.load(argv[2]);
    x.setimage_name(argv[4]);
    Image y;
    y.load(argv[3]);
    x+y;
    }
  else if (check==("-s")){
    Image x;
    x.load(argv[2]);
    x.setimage_name(argv[4]);
    Image y;
    y.load(argv[3]);
    x-y;
  }
  else if (check==("-i")){
    Image x;
    x.load(argv[2]);
    x.setimage_name(argv[3]);
    !x;
  }
  else if (check==("-l")){
    Image x;
    x.load(argv[2]);
    x.setimage_name(argv[4]);
    Image y;
    y.load(argv[3]);
    x/y;
  }
  else if (check==("-t")){
    Image x;
    x.load(argv[2]);
    x.setimage_name(argv[4]);
    int y = atoi(argv[3]);;
    x*y;
  }

  return 0;
}