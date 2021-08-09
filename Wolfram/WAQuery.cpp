/********************************************************************
 *		@file WAQuery.cpp
 *		API query petition manager
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 *******************************************************************/

#include "WAQuery.h"

std::set<char> WAQuery::special_char = {'!', '#', '$', '&', '\'', '(', ')', '*', '+', ',', '/', ':', ';', '=', '?', '@', '[', ']'};

WAQuery::WAQuery() {
	this->timeout = 5; // 5s timeout to get the data
}

/**
 * Returning a query param string
 *
 * @return Query
 */
std::string WAQuery::toString() {
    std::string q = std::string("&input=") + WAQuery::parseInput(this->input);

    // Adding a vectors data to string
    q += VectorToStr("&format=",       false, this->formats);
	q += std::string("&scantimeout=") + std::to_string(this->timeout);
    q += VectorToStr("&includepodid=", true,  this->IncludePodIDs);
    q += VectorToStr("&excludepodid=", true,  this->ExcludePodIDs);
    q += VectorToStr("&podtitle=",     true,  this->PodTitle);
    q += VectorToStr("&scanner=",      true,  this->PodScanners);
    q += VectorToStr("&podindex=",     false, this->PodIndexes);

    return q;
}

/**
 *	Given an string it creates a copy but with % code
 */
std::string WAQuery::parseInput(std::string str) {
	std::stringstream result;
	
	std::string::iterator it;
	for (it = str.begin(); it < str.end(); it++) {
		if (WAQuery::special_char.find(*it) != WAQuery::special_char.end()) {
			result << '%';
			result << std::hex << (int)(*it);
		}
		else if (*it == ' ') result << '+'; // space is special; it should be '+'
		else result << (*it);
	}
	
	return result.str();
}

/**
 * Returning a search query text
 *
 * @return Search query string
 */
std::string WAQuery::getInput() {
    return this->input;
}

/**
 * Set text for search
 *
 * @param[in]	input	Text for search
 */
void WAQuery::setInput(std::string input) {
    this->input = input;
}

/**
 * Adding a string format
 *
 * @param[in]	format		String of format
 */
void WAQuery::addFormat(std::string format) {
    this->formats.push_back(format);
}

/**
 * Adding a string format
 *
 * @param[in]	format		String of format
 */
void WAQuery::addFormat(const char *format) {
	this->addFormat(std::string(format));
}

void WAQuery::setTimeout(unsigned int value) {
	this->timeout = value;
	
}

/**
 * Clear format config
 */
void WAQuery::clearFormats() {
    this->formats.clear();
}

void WAQuery::addPodTitle(std::string podtitle) {
    this->PodTitle.push_back(podtitle);
}

void WAQuery::clearPodTitles() {
    this->PodTitle.clear();
}

void WAQuery::addPodIndex(int podindex) {
    this->PodIndexes.push_back(podindex);
}

void WAQuery::clearPodIndexes() {
    this->PodIndexes.clear();
}

void WAQuery::addPodScanner(std::string podscanner) {
    this->PodScanners.push_back(podscanner);
}

void WAQuery::clearPodScanners() {
    this->PodScanners.clear();
}

void WAQuery::addIncludePodID(std::string podid) {
    this->IncludePodIDs.push_back(podid);
}

void WAQuery::clearIncludePodIDs() {
    this->IncludePodIDs.clear();
}

void WAQuery::addExcludePodID(std::string podid) {
    this->ExcludePodIDs.push_back(podid);
}

void WAQuery::clearExcludePodIDs() {
    this->ExcludePodIDs.clear();
}
/**
 * Concatenating a vector data to string
 *
 * @param   prefix      String prefix for data; example '&name='
 * @param   individual  Type of concatenating string
 * @param   t           Vector of data
 * @return 	String with concatenated string
 */
template <typename T>
std::string WAQuery::VectorToStr(const char *prefix, bool individual, std::vector<T>& t) {
	return this->VectorToStr(std::string(prefix), individual, t);
}

/**
 * Concatenating a vector data to string
 *
 * @param   prefix      String prefix for data; example '&name='
 * @param   individual  Type of concatenating string
 * @param   t           Vector of data
 * @return 	String with concatenated string
 */
template <typename T>
std::string WAQuery::VectorToStr(std::string prefix, bool individual, std::vector<T>& t) {
    std::string q("");
    typename std::vector<T>::iterator tmpIter;

    if (t.size() == 0) return q;

    if (individual) {
        // [prefix][data][prefix][data]
        for (tmpIter = t.begin(); tmpIter < t.end(); tmpIter++) {
            q += prefix + to_string(*tmpIter);
        }
    }
    else {
        // [prefix][data,data,data,...]
        q += prefix;

        for (tmpIter = t.begin(); tmpIter < t.end(); tmpIter++) {
            q += to_string(*tmpIter);
            q += std::string(",");
        }
        q.pop_back(); // Erase last ','
    }
	
    return q;
}
