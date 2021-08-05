/*
 *      WAEngine.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *		Copyright 2021 Roger Miranda <contacto@rogermiranda1000.com>
 *
 */

#include "WAEngine.h"

/**
 * Constructor with another config
 *
 * @param appid     AppID, for using WolframAlpha
 * @param server    Address of WolframAlpha server
 * @param path      Path to script on server
 */
WAEngine::WAEngine(string appid, string server, string path) {
    this->appID  = appid;
    this->server = server;
    this->path = path;
}

/**
 * Returns a setted AppID
 *
 * @return AppID
 */
string
WAEngine::getAppID()
{
    return this->appID;
}

/**
 * Set another AppID
 *
 * @param appid Another AppID
 */
void
WAEngine::setAppID(string appid)
{
    this->appID = appid;
}

/**
 * Returns a URL for HTTP request, using a internal WAQuery object
 *
 * @return URL
 */
string WAEngine::getURL() {
    return this->getURL(this->query);
}

/**
 * Returns a URL for HTTP request, using a external WAQuery object
 *
 * @param query Query to search
 * @return URL
 */
string WAEngine::getURL(WAQuery query) {
    return string("http://") + server + path + string("?appid=") + appID + query.toString();
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData  String containing the data
 * @return  false, if a error
 */
bool WAEngine::Parse(char *inputData) {
    xml_document<> root;
    root.parse<0>(inputData);
    xml_node<>* query = root.first_node("queryresult");

    if (string(query->first_attribute("error")->value()) == "true") return false;

	WAPod tmp;
	this->Pods.clear();
    xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < atoi(query->first_attribute("numpods")->value()); i++) {
		if (tmp.Parse(node)) this->Pods.push_back(tmp);
        node = node->next_sibling("pod");
    }

    return true;
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData  String containing the data
 * @return  false, if a error
 */
bool WAEngine::Parse(string inputData) {
	return this->Parse((char*)inputData.c_str());
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) { 
    size_t realsize = size * nmemb;
	((std::string*)userp)->append((char*)contents, realsize);
    return realsize;
}

bool WAEngine::DownloadURL(string url, string *readBuffer) {
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
 * Returns a count of blocks "pod"
 *
 * @return  count of block
 */
int
WAEngine::getCountPods()
{
    return countPods;
}

/**
 * Returns a array of Pod
 *
 * @return array of Pods
 */
vector<WAPod> WAEngine::getPods() {
    return this->Pods;
}

/**
 * Returns a Pod
 *
 * @return Pointer to the Pod with the specified title; nullptr if any
 */
WAPod *WAEngine::getPod(const char *title) {
	vector<WAPod>::iterator it;
	for (it = begin(this->Pods); it != end(this->Pods); it++) {
		if (strcmp(it->getTitle(), title) == 0) return &(*it); // same title
	}
    return nullptr;
}
