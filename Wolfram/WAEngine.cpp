/*********************************************************************
 *		@file WAEngine.cpp
 *      Wolfram API access point
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 ********************************************************************/

#include "WAEngine.h"

/**
 * Constructor with another config
 *
 * @param[in] 	appID 	AppID, for using WolframAlpha
 * @param[in] 	server 	Address of WolframAlpha server
 * @param[in] 	path 	Path to script on server
 */
WAEngine::WAEngine(std::string appID, std::string server, std::string path) {
    this->appID  = appID;
    this->server = server;
    this->path = path;
}

/**
 * Returns a URL for HTTP request, using the internal WAQuery object
 *
 * @param[in]	input	Text to search
 * @return 				URL to perform the query specified on \p input with the internal arguments of the internal variable \p _query
 */
std::string WAEngine::getURL(std::string input) {
	this->_query.setInput(input);
    return string("http://") + server + path + string("?appid=") + appID + this->_query.toString();
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData	String containing the data
 * @return				The parsed object indicated by \b inputData
 */
WAResult *WAEngine::getResult(std::string inputData) {
    rapidxml::xml_document<> root;
    root.parse<0>((char*)inputData.c_str());
    rapidxml::xml_node<>* query = root.first_node("queryresult");

    return new WAResult(query);
}

/**
 * It sets the max search time.
 * Wolfram API has a time limit on how much a request can last. Use \b timeout to modify it.
 * @param[in]	timeout		Max time that the request can last
 */
void WAEngine::setTimeout(unsigned int timeout) {
	this->_query.setTimeout(timeout);
}

/**
 * Function called by CUrl on \ref DownloadURL
 */
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) { 
    size_t realsize = size * nmemb;
	((std::string*)userp)->append((char*)contents, realsize);
    return realsize;
}

/**
 * Given an \p url it downloads its HTML contents
 *
 * @param[in]	url			URL to download
 * @param[out]	readBuffer	Downloaded website
 * @retval		TRUE		All OK
 * @retval		FALSE		Error while downloading
 */
bool WAEngine::DownloadURL(std::string url, std::string *readBuffer) {
	CURL *curl = nullptr;
	CURLcode res;

	readBuffer->clear();

	curl = curl_easy_init();
	if(curl == nullptr) {
		std::cerr << "CURL init error!" << std::endl;
		return false;
	}
	
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	
	if (res != CURLE_OK) {
		std::cerr << "Response code " << res << std::endl;
		return false;
	}
	
	return true;
}
