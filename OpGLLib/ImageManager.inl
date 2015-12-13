/*
 * ImageManager.inl
 *
 *  Created on: 25.09.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<> Image<unsigned char> const& ImageManager::getCachedImage(std::string const& file) const {
	return _imageCache[file];
}

}
