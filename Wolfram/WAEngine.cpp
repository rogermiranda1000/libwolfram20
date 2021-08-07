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
 * Destructor; it frees the Pods
 */
WAEngine::~WAEngine() {
	for (auto it : this->Pods) delete it;
}

/**
 * Returns a setted AppID
 *
 * \return AppID
 */
std::string WAEngine::getAppID() {
    return this->appID;
}

/**
 * Set another AppID
 *
 * @param appID Another AppID
 */
void WAEngine::setAppID(std::string appID) {
    this->appID = appID;
}

/**
 * Returns a URL for HTTP request, using a internal WAQuery object
 *
 * @return URL to get the query, using the app ID
 */
std::string WAEngine::getURL() {
    return this->getURL(this->query);
}

/**
 * Returns a URL for HTTP request, using a external WAQuery object
 *
 * @param query Query to search
 * @return URL
 */
std::string WAEngine::getURL(WAQuery query) {
    return std::string("http://") + server + path + std::string("?appid=") + appID + query.toString();
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData	String containing the data
 * @retval	TRUE		All OK
 * @retval	FALSE		Parse failed
 */
bool WAEngine::Parse(std::string inputData) {
    xml_document<> root;
    root.parse<0>((char*)inputData.c_str());
    xml_node<>* query = root.first_node("queryresult");

    if (std::string(query->first_attribute("error")->value()) == "true") return false;

	//this->Pods.clear();
    xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < atoi(query->first_attribute("numpods")->value()); i++) {
		WAPod *tmp = new WAPod();
		if (tmp->Parse(node)) this->Pods.push_back(tmp);
        node = node->next_sibling("pod");
    }

    return true;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) { 
    size_t realsize = size * nmemb;
	((std::string*)userp)->append((char*)contents, realsize);
    return realsize;
}

bool WAEngine::DownloadURL(std::string url, std::string *readBuffer) {
	CURL *curl = nullptr;
	CURLcode res;

	readBuffer->clear();

	curl = curl_easy_init();
	if(curl == nullptr) {
		cerr << "CURL init error!" << endl;
		return false;
	}
	
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	
	if (res != CURLE_OK) {
		cerr << "Response code " << res << endl;
		return false;
	}
	
	return true;
}

/**
 * Returns the getted array of Pods
 *
 * @return array of Pods
 */
std::vector<WAPod*> WAEngine::getPods() {
    return this->Pods;
}

/**
 * Returns a Pod
 *
 * @param[in]	title	Title to search on the getted Pods
 * @return 				Pointer to the Pod with the specified title; nullptr if any
 */
WAPod *WAEngine::getPod(const char *title) {
	vector<WAPod*>::iterator it;
	for (it = begin(this->Pods); it != end(this->Pods); it++) {
		if (strcmp((*it)->getTitle(), title) == 0) return *it; // same title
	}
    return nullptr;
}
