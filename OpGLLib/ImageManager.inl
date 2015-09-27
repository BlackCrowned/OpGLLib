/*
 * ImageManager.inl
 *
 *  Created on: 25.09.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<class T> Image<T> const& ImageManager::getCachedImage(std::string const& file) const {
	return std::experimental::any_cast<Image<T> const&>(_imageCache[file]);
}

}
