/*
 * Image.cpp
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

#include <OpGLLib/Image.h>
#include <bitset>

using namespace std;

namespace OpGLLib {

//Image<unsigned char> loadBMP(std::string filename) {
//
//}

Image<unsigned char> loadPNG(std::string filename) {
	//Decode png
	std::vector<unsigned char> data;
	unsigned int width, height;
	int errorCode = lodepng::decode(data, width, height, filename);
	if (errorCode) {
		cerr << "Loading " << filename << " failed with error: " << lodepng_error_text(errorCode) << "." << endl;
	}


	//Return Image
	return Image<unsigned char>({width, height}, std::move(data));
}

}
