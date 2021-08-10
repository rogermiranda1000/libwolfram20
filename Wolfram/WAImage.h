/********************************************************************
 *		@file WAImage.h
 *		Wolfram image
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 *******************************************************************/

#ifndef WAIMAGE_H
#define WAIMAGE_H

#include <cstring>

#include <rapidxml/rapidxml_utils.hpp>

using namespace rapidxml;

/**
 * Wolfram API image.
 * For more information see the [Wolfram documentation](https://products.wolframalpha.com/api/documentation/#result-img).
 */
class WAImage
{
public:
	/**
	 * Copy constructor
	 * @param[in]	old		Object to copy
	 */
	WAImage(const WAImage &old) = default;
    WAImage(xml_node<>* imgNode);

    std::string getSrc();
    std::string getAlt();
    std::string getTitle();
    size_t getWidth();
    size_t getHeight();

private:
    // Attributes of 'image' node
    std::string _src;						//!< The exact URL of the image being displayed
    std::string _alt;						//!< Alternate text to display in case the image does not render correctly
    std::string _title;						//!< Descriptive title for internal identification of an image
    size_t _width;							//!< The width of the image in pixels
    size_t _height;							//!< The height of the image in pixels. Scales depending on width setting.

    void parse(xml_node<>* imgNode);
};

#endif // WAIMAGE_H
