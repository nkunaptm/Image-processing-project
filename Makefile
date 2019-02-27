imageops: interface.o Image.o
	g++ -std=c++11 interface.o Image.o -o imageops

interface.o: interface.cpp
	g++ -std=c++11 -c interface.cpp
	
Image.o: Image.cpp Image.h
	g++ -std=c++11 -c Image.cpp
 
clean:
	rm *.o imageops