/*
 *      WASubpod.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WASubpod.h"

WASubpod::WASubpod() {
    img = nullptr;
}

WASubpod::~WASubpod() {
    if (img != nullptr) delete img;
}

/**
 * Returns a 'title' attribute of subpod
 *
 * @return Title
 */
string
WASubpod::getTitle()
{
    return string(title);
}

/**
 * Returns a plain-text data, included on subpod
 *
 * @return Plain-text
 */
string
WASubpod::getPlainText()
{
    return string(plain);
}

WAImage* WASubpod::getImage() {
    return img;
}

bool WASubpod::hasImage() {
    return img != nullptr;
}

/**
 * Parsing a input 'subpod' xml node
 *
 * @param   subpod XML Node of subpod
 */
void WASubpod::Parse(xml_node<>* subpod) {
    xml_node<>* plainNode;
    xml_node<>* imgNode;

    // Get 'title' attribute
    title = subpod->first_attribute("title")->value();

    // Get included plaintext
    plainNode = subpod->first_node("plaintext");
    plain     = plainNode->value();

    // Reading 'img' block
    imgNode = subpod->first_node("img");
    if (imgNode != NULL)
    {
		if (img != nullptr) delete img;
        img = new WAImage();
        img->Parse(imgNode);
    }
}
