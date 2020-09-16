#include "asset/image.hh"

#include "stream/reader.hh"
#include "stream/writer.hh"

#include <iostream>
#include <sstream>


int main()
{
	std::stringstream l_I;



	shape::CoreImage l_OImage(16, 4, 8, 2, 2);
	shape::CoreImage l_IImage;


	l_OImage.save<shape::CoreStreamWriter>(l_I.seekp(0));
	l_IImage.load<shape::CoreStreamReader>(l_I.seekg(0));
	l_IImage.save<shape::CoreStreamWriter>(std::cout);

	return 0;
}