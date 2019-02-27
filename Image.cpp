#include "Image.h"
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <tr1/unordered_map>
#include <bits/stdc++.h>
using namespace NKNPET001;
typedef unsigned char uchar;
Image::Image(){}

Image::Image(const char* name){
  load(name);
}

Image::Image(const Image& rhs) {
  this->height = rhs.height;
  this->width = rhs.width;
  this->header = rhs.header;
    
  this->data = unique_ptr<unsigned char[]>(new unsigned char[height*width]);
  
  Image::iterator beg = begin(),endData = end(), rhdData(rhs.data.get());
  for(beg = begin(); beg != endData; beg++){
      *beg = *rhdData;
      rhdData++;
  }
}

Image::Image(Image&& rhs){
  this->width = rhs.width;
  this->height = rhs.height;
  this->header = rhs.header;
    
  this->data = std::move(rhs.data);
  
  rhs.data = nullptr;
}

Image::~Image() {}

 //reading a pmg image
void Image::load(string name){  
  ifstream infile(name.c_str(), ios::in | ios::binary);
  if(infile.is_open()){
    string holder;
    getline(infile, holder);
    infile >> ws;
    header += holder + "\n";
    getline(infile, holder);
    header += holder + "\n";
          //reading initail comments
    while(holder[0] == '#'){
      getline(infile, holder);
      infile >> ws;
      header += holder + "\n";
    }
            //finding the values for width and height
    string::size_type size_t;
    int finder = holder.find(" ");
    height = std::stoi(holder.substr(0, finder), &size_t);
    width = std::stoi(holder.substr(finder + 1), &size_t);
           //add holder with 255 to header
    std::getline(infile, holder);
    infile >> ws;
    header += holder + "\n";

            //Read the pgm unsigned char data
    unsigned char * memblock;
            
    memblock = new unsigned char [width*height];
    infile.read ((char*)memblock, width*height);
                
    data = unique_ptr<unsigned char[]>(memblock);       
  }else{
    cout << "Image could not be opened." << endl;
  }
  infile.close();
}

//setting the output name of the pgm file
void Image::setimage_name(string temp){
  image_name = temp.c_str();
}

//writing a pgm image
void Image::save(std::unique_ptr<unsigned char[]> &array, string name){
    unsigned char *temp= new unsigned char[width*height*sizeof(uchar)];
    //copy data into temporary array
    for(int i = 0; i<width*height;i++){
      temp[i] = array[i];
    }

    ofstream outfile (name.c_str());
    if (!outfile.is_open()){
       cout << "Can't open output file"  << "output.pgm" << endl;
       exit(1);
    }
    //add header of image
    outfile << header;
    //write image data
    outfile.write((char *)temp, width*height*sizeof(uchar));
    outfile.close();
    delete[] temp;

  }

std::unique_ptr<unsigned char[]> Image::operator+(Image& rhs){
      std::unique_ptr<unsigned char[]> Datavar(new unsigned char [width*height]);
      Image::iterator beg = this->begin(), end = this->end();
      Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
      int count = 0;

      while (beg!=end) {
        int sum = (int)(*(beg)) + (int)(*(inStart));
        if (sum>255){sum = 255;}
        char resChar = (char)(sum);
        Datavar[count] = resChar;
        beg++;
        inStart++;
        count++;
      }
      save(Datavar, image_name);
      return Datavar;
    }

std::unique_ptr<unsigned char[]> Image::operator-(Image& rhs){
      std::unique_ptr<unsigned char[]> Datavar(new unsigned char [width*height]);
      Image::iterator beg = this->begin(), end = this->end();
      Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
      int count = 0;

      while (beg!=end) {
        int sum = (int)(*(beg)) - (int)(*(inStart));
        if (sum<0){sum = 0;}
        char resChar = (char)(sum);
        Datavar[count] = resChar;
        beg++;
        inStart++;
        count++;
      }
      save(Datavar, image_name);
      return Datavar;
    }

std::unique_ptr<unsigned char[]> Image::operator!(){
      std::unique_ptr<unsigned char[]> Datavar(new unsigned char [width*height]);
      Image::iterator beg = this->begin(), end = this->end();
      int count = 0;
      while ( beg!=end) {
        int difference = 255 - (int)(*(beg));
        char resChar = (char)(difference);
        Datavar[count] = resChar;
        count++;
        beg++;
      }
    save(Datavar, image_name);
    return Datavar;

  }

std::unique_ptr<unsigned char[]> Image::operator/(Image& rhs){
      std::unique_ptr<unsigned char[]> Datavar(new unsigned char [width*height]);
      Image::iterator beg = this->begin(), end = this->end();
      Image::iterator inStart = rhs.begin(), inEnd = rhs.end();
      int count = 0;
      char resChar;
      while ( beg!=end) {
        if((int)(*(inStart)) == 0){
          resChar = (char)*inStart;
        }
        else{
          resChar = (char)*beg;
        }
        Datavar[count] = resChar;
        count++;
        beg++;
        inStart++;
      }
  save(Datavar, image_name);
  return Datavar;
  }

std::unique_ptr<unsigned char[]> Image::operator*(int rhs){
      std::unique_ptr<unsigned char[]> Datavar(new unsigned char [width*height]);
      Image::iterator beg = this->begin(), end = this->end();
      int count = 0;
      char resChar;
      while ( beg!=end) {
        if((int)(*(beg)) >rhs){
          resChar = (char)255;
        }
        else{
          resChar = (char)0;
        }
        Datavar[count] = resChar;
        count++;
        beg++;
      }
  save(Datavar, image_name);
  return Datavar;
  }

Image& Image::operator >>(const char* name){
    save(data, name);
    return *this;
}

Image& Image::operator <<(const char* name){
    load(name);
    return *this;
}

Image& Image::operator =(Image&& rhs){
  this->height = rhs.height;
  this->width = rhs.width;
  this->header = rhs.header;  
  this->data = move(rhs.data);
  rhs.data = nullptr;
  return *this;
}

Image& Image::operator =(const Image& rhs){
  this->width = rhs.width;
  this->height = rhs.height;
  this->header = rhs.header;
    
  unique_ptr<unsigned char[]> temp(new unsigned char[height*width]);
  this->data = std::move(temp);
    
  Image::iterator beg = begin(),endData = end(), rhsData(rhs.data.get());
  for(beg = begin(); beg != endData; beg++){
    *beg = *rhsData;
    rhsData++;
  }
  return *this;
}

