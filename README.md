# Image-processing-project
for manipulating pmg images
files: - the Image.h file is the header for the image container - the Image.cpp file implements the methods for the image container - the interface takes in command line arguments and implements them using the image class - the makefile compiles the files  running the code: The commandline for runnning the sode is : imageops &lt;option> OutputImageName  where the &lt;option> represents one of the following options: 
-a I1 I2 (add I1 and I2) 
-s I1 I2 (subtract I2 from I1) 
-i I1 (invert I1) -l I1 I2 (mask I1 with I2) 
-t I1 f (threshold I1 with integer value f)
