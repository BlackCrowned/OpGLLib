/*
 * ImageLoader.cpp
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

#include <OpGLLib/ImageLoader.h>
#include <bitset>

using namespace std;

namespace OpGLLib {
namespace ImageLoader {
Bitmap::Bitmap() {

}

Bitmap::Bitmap(char* ptr) {
	loadBitmap(ptr);
}
Bitmap::Bitmap(std::string filename) {
	loadBitmap(filename);
}

Bitmap::~Bitmap() {

}

bool Bitmap::loadBitmap(char* ptr) {
	signature = ptr;
	if (signature.data != 19778) {
		std::cerr << "Wrong signature: Expected 19778 got " << signature.data << "!" << std::endl;
		return false;
	}
	fileSize = ptr + 0x2;
	offset = ptr + 0xA;
	headerSize = ptr + 0xE;
	width = ptr + 0x12;
	height = ptr + 0x16;
	planes = ptr + 0x1A;
	bitCount = ptr + 0x1C;
	compression = ptr + 0x1E;
	sizeImage = ptr + 0x22;
	clrUsed = ptr + 0x2E;
	clrImportant = ptr + 0x32;

	if (*compression == Compression::BI_BITFIELDS && (*bitCount == 16 || *bitCount == 32)) {
		bitmask = {
			OpGLLib::Types::DWORD<>(ptr + 0x36), OpGLLib::Types::DWORD<>(ptr + 0x3A), OpGLLib::Types::DWORD<>(ptr + 0x3E)
		};
	}
	else if (*bitCount == 16) {
		bitmask.red.data = 0x00007C00;
		bitmask.green.data = 0x000003E0;
		bitmask.blue.data = 0x0000001F;
	}
	else if (*bitCount == 32) {
		bitmask.red.data = 0x00FF0000;
		bitmask.green.data = 0x0000FF00;
		bitmask.blue.data = 0x000000FF;
	}

	if (*bitCount == 1 || *bitCount == 4 || *bitCount == 8) { //ColorTable
		colorTable(ptr + 0xE + *headerSize, *clrUsed == 0 ? std::pow(2, *bitCount) : *clrUsed);
	} else {
		colorTable(ptr + 0xE + *headerSize, 0);
	}

//	imageData = shared_ptr<tvec4<OpGLLib::Types::BYTE> >(new tvec4<OpGLLib::Types::BYTE> [*width * (*height > 0 ? *height : -*height)],
//			OpGLLib::default_delete<tvec4<OpGLLib::Types::BYTE> []>());

	imageData.reserve((*width * (*height > 0 ? *height : -*height)) * 4);
	imageData.resize((*width * (*height > 0 ? *height : -*height)) * 4);

	long int currentHeight = *height;
	long int maxWidth = *width;
	long int maxHeight = *height;
	OpGLLib::Types::DWORD<OpGLLib::Types::Endianness::BIG_ENDIAN> BMPImageData = ptr + *offset;
	int ImageDataOffset = 0;
	int ImageDataCount = 0;
	int ImageDataCountMultiplier = *bitCount == 24 ? 3 : 4;
	while (currentHeight != 0) {
		for (long int i = 0; i < maxWidth; i++) {
			if (ImageDataOffset >= 32) {
				BMPImageData = ptr + *offset + ++ImageDataCount * ImageDataCountMultiplier;
				ImageDataOffset = 0;
			}
			tvec4<dataType>* tmp = reinterpret_cast<tvec4<dataType>*>(imageData.data()) + (maxHeight - currentHeight) * maxWidth + i;
			switch (*bitCount) {
			case 1:
			case 4:
			case 8:
				*tmp = colorTable[OpGLLib::bitAccess<OpGLLib::Types::BYTE>(*bitCount, *BMPImageData, ImageDataOffset / *bitCount,
						OpGLLib::Types::Endianness::BIG_ENDIAN)].color;
				ImageDataOffset += *bitCount;
				break;
			case 16:
				*tmp = tvec4<OpGLLib::Types::BYTE>(((*BMPImageData >> (16 - ImageDataOffset)) & *bitmask.red) >> 10,
						((*BMPImageData >> (16 - ImageDataOffset)) & *bitmask.green) >> 5,
						(*BMPImageData >> (16 - ImageDataOffset) & *bitmask.blue), 0);
				ImageDataOffset += 16;
				break;
			case 24:
				*tmp = tvec4<OpGLLib::Types::BYTE>(BMPImageData[0], BMPImageData[1], BMPImageData[2], 0);
				ImageDataOffset = 32;
				break;
			case 32:
				*tmp = tvec4<OpGLLib::Types::BYTE>((*BMPImageData & *bitmask.red) >> 16, (*BMPImageData & *bitmask.green) >> 8,
						(*BMPImageData & *bitmask.blue), (*BMPImageData & *bitmask.red) >> 24);
				ImageDataOffset = 32;
				break;
			}

		}
		ImageDataOffset = 32;
		maxHeight > 0 ? currentHeight-- : currentHeight++;
	}
	return true;
}

bool Bitmap::loadBitmap(std::string filename) {
	fstream file(filename, std::ios::in);
	if (!file) {
		std::cerr << "Failed to open file: " << filename << "!" << std::endl;
		return false;
	}
	char *ptr = OpGLLib::files::dataPtr(file);
	return loadBitmap(ptr);
}

Image<Bitmap::dataType> Bitmap::getImage() {
//	return Image2D<OpGLLib::Types::BYTE>(static_cast<size_t>(*width),
//			*height > 0 ? static_cast<size_t>(*height) : static_cast<size_t>(-*height), imageData);
	return Image<dataType>( { static_cast<size_t>(*width), *height > 0 ? static_cast<size_t>(*height) : static_cast<size_t>(-*height) },
			imageData);
}

Dimensions Bitmap::getDimensions() {
	return {getWidth(), getHeight()};
}

size_t Bitmap::getWidth() {
	return width.data;
}

size_t Bitmap::getHeight() {
	return (height.data > 0 ? height.data : -height.data);
}

size_t Bitmap::getBitCount() {
	return bitCount.data;
}

Image<unsigned char> loadBMP(std::string filename) {
	Bitmap bitmap(filename);

	cout << "Loaded [" << bitmap.getWidth() << "|" << bitmap.getHeight() << "] " << bitmap.getBitCount() << "-Bit Bitmap" << endl;

	return bitmap.getImage();
}

Image<unsigned char> loadPNG(std::string filename) {
	//Decode png
	std::vector<unsigned char> data;
	unsigned int width, height;
	lodepng::decode(data, width, height, filename);

	//Return Image
	return Image<unsigned char>({width, height}, std::move(data));
}

}
}
