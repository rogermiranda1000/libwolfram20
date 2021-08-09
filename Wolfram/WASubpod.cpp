/*
 *      WASubpod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WASubpod.h"

/**
 * Copy constructor
 *
 * @param[in]	old		Object to copy
 */
WASubpod::WASubpod(const WASubpod &old) {
	this->_title = old._title;
	this->_plain = old._plain;
	this->_img = nullptr;
	if (old._img != nullptr) this->_img = new WAImage(*old._img);
}

/**
 * It generates the object with the \p subpod
 *
 * @param[in]	subpod		XML Node of subpod
 */
WASubpod::WASubpod(xml_node<>* subpod) {
	this->parse(subpod);
}

/**
 * Destructor. It frees the image.
 */
WASubpod::~WASubpod() {
    delete this->_img;
}

/**
 * Returns a 'title' attribute of subpod
 *
 * @return Title
 */
std::string WASubpod::getTitle() {
    return this->_title;
}

/**
 * Returns a plain-text data, included on subpod
 *
 * @return Plain-text
 */
std::string WASubpod::getPlainText() {
    return this->_plain;
}

/**
 * Returns the subpod's image
 *
 * @return					The subpod's image
 * @retval		nullptr		The subpod doesn't have any image
 */
WAImage* WASubpod::getImage() {
    return this->_img;
}

/**
 * Returns if the subpod contains an image
 *
 * @retval		true	The subpod have an image
 * @retval		false	The subpod doesn't have any image
 */
bool WASubpod::hasImage() {
    return (this->_img != nullptr);
}

/**
 * Parsing the input \p subpod
 *
 * @pre 				It must be called only once
 * @param[in]   subpod	XML Node of subpod
 */
void WASubpod::parse(xml_node<>* subpod) {
    // Get 'title' attribute
    this->_title = std::string( subpod->first_attribute("title")->value() );

    // Get included plaintext
    xml_node<>* plainNode = subpod->first_node("plaintext");
    this->_plain = std::string( plainNode->value() );

    // Reading 'img' block
    xml_node<>* imgNode = subpod->first_node("img");
	this->_img = nullptr;
    if (imgNode != nullptr) this->_img = new WAImage(imgNode);
}
