/********************************************************************
 *		@file WAQuery.cpp
 *		API query petition manager
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 *******************************************************************/

#include "WAQuery.h"

std::set<char> WAQuery::_special_char = {'!', '#', '$', '&', '\'', '(', ')', '*', '+', ',', '/', ':', ';', '=', '?', '@', '[', ']'};

/**
 * Default constructor. It sets the timeout on its default value.
 */
WAQuery::WAQuery() {
	this->_timeout = DEFAULT_TIMEOUT; // DEFAULT_TIMEOUT seconds timeout to get the data
}

/**
 * Returning a query param string
 *
 * @return Query
 */
std::string WAQuery::toString() {
    std::string q = std::string("&input=") + WAQuery::parseInput(this->_input);

    // Adding a vectors data to string
    q += VectorToStr("&format=",       false, this->_formats);
	if (this->_timeout != DEFAULT_TIMEOUT) q += std::string("&scantimeout=") + std::to_string(this->_timeout);
    q += VectorToStr("&includepodid=", true,  this->_includePodIDs);
    q += VectorToStr("&excludepodid=", true,  this->_excludePodIDs);
    q += VectorToStr("&podtitle=",     true,  this->_podTitle);
    q += VectorToStr("&scanner=",      true,  this->_podScanners);
    q += VectorToStr("&podindex=",     false, this->_podIndexes);

    return q;
}

/**
 * Given an string it creates a copy but with % code
 * More information [here](https://es.wikipedia.org/wiki/C%C3%B3digo_porciento)
 *
 * @param[in]	str		String to parse
 * @return				Parsed string
 */
std::string WAQuery::parseInput(std::string str) {
	std::stringstream result;
	
	std::string::iterator it;
	for (it = str.begin(); it < str.end(); it++) {
		if (WAQuery::_special_char.find(*it) != WAQuery::_special_char.end()) {
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
    return this->_input;
}

/**
 * Set text for search
 *
 * @param[in]	input	Text for search
 */
void WAQuery::setInput(std::string input) {
    this->_input = input;
}

/**
 * Adding a string format
 *
 * @param[in]	format		String of format
 */
void WAQuery::addFormat(std::string format) {
    this->_formats.push_back(format);
}

/**
 * Adding a string format
 *
 * @param[in]	format		String of format
 */
void WAQuery::addFormat(const char *format) {
	this->addFormat(std::string(format));
}

/**
 * Clear format config
 */
void WAQuery::clearFormats() {
    this->_formats.clear();
}

/**
 * Sets the timeout
 *
 * @param[in]	value		New timeout
 */
void WAQuery::setTimeout(unsigned int value) {
	this->_timeout = value;
}

/**
 * Adding a string title
 *
 * @param[in]	podtitle	String of title
 */
void WAQuery::addPodTitle(std::string podtitle) {
    this->_podTitle.push_back(podtitle);
}

/**
 * Clear title config
 */
void WAQuery::clearPodTitles() {
    this->_podTitle.clear();
}

/**
 * Adding a string index
 *
 * @param[in]	podindex	String of index
 */
void WAQuery::addPodIndex(int podindex) {
    this->_podIndexes.push_back(podindex);
}

/**
 * Clear index config
 */
void WAQuery::clearPodIndexes() {
    this->_podIndexes.clear();
}

/**
 * Adding a string scanner
 *
 * @param[in]	podscanner	String of scanner
 */
void WAQuery::addPodScanner(std::string podscanner) {
    this->_podScanners.push_back(podscanner);
}

/**
 * Clear scanner config
 */
void WAQuery::clearPodScanners() {
    this->_podScanners.clear();
}

/**
 * Adding a id config
 *
 * @param[in]	podid		String of id
 */
void WAQuery::addIncludePodID(std::string podid) {
    this->_includePodIDs.push_back(podid);
}

/**
 * Clear included id config
 */
void WAQuery::clearIncludePodIDs() {
    this->_includePodIDs.clear();
}

/**
 * Removing an id config
 *
 * @param[in]	podid		String of id
 */
void WAQuery::addExcludePodID(std::string podid) {
    this->_excludePodIDs.push_back(podid);
}

/**
 * Clear excluded id config
 */
void WAQuery::clearExcludePodIDs() {
    this->_excludePodIDs.clear();
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
