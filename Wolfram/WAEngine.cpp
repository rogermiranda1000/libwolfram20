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
	
    this->error = false;
	this->data = nullptr;
	this->Pods = nullptr;
}

WAEngine::~WAEngine()
{
    if (this->Pods != nullptr) delete this->Pods;
    if (this->data != nullptr) free(this->data);
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
 * Parsing a array of char 'data'
 *
 * @return false, if a error
 */
bool
WAEngine::Parse()
{
    if ((this->data == nullptr) || (this->length == 0)) return false;
    
    xml_document<> root;
    root.parse<0>(this->data);
    xml_node<>* query = root.first_node("queryresult");

    //Get attributes queryresult
    dataTypes = string(query->first_attribute("datatypes")->value());
    version   = string(query->first_attribute("version")->value());

    if (string(query->first_attribute("error")->value()) == "true")
    {
        this->error = true;
    }

    // Read Pods
    countPods = atoi(query->first_attribute("numpods")->value());
	if (this->Pods != nullptr) delete this->Pods;
    this->Pods = new WAPod[countPods];

    xml_node<>* node = query->first_node("pod");
    for(size_t i = 0; i < countPods; i++)
    {
        this->Pods[i].Parse(node);
        node = node->next_sibling("pod");
    }

    return true;
}

/**
 * Parsing data from a text-file
 *
 * @param filename  Name of file for parsing
 * @return false, if a error
 */
bool
WAEngine::Parse(string filename)
{
    ifstream file;
    file.open(filename.c_str(), ios::in);
    if (file.fail()) return false;
    // Get length of file
    file.seekg(0, ios_base::end);
    this->length = file.tellg();
    file.seekg(0, ios_base::beg);

    // Read file
	if (this->data != nullptr) free(this->data);
	this->data = nullptr;
    this->data = (char*)malloc(this->length);
	if (this->data == nullptr) return false; // no memory
    file.read(this->data, this->length);

    file.close();

    // Parse data from file
    Parse();

    return true;
}

/**
 * Parsing data from a external array of char
 *
 * @param   inputData  Pointer to array of data
 * @return  false, if a error
 */
bool
WAEngine::Parse(char *inputData)
{
    this->data = inputData;
	this->length = strlen(inputData);
    return Parse();
}

// TODO inside function?
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) { 
    size_t realsize = size * nmemb;
	((std::string*)userp)->append((char*)contents, realsize);
    return realsize;
}

bool WAEngine::DownloadURL(string url) {
	CURL *curl = nullptr;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if(curl == nullptr) {
		cerr << "CURL init error!" << endl;
		return false;
	}
	
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	
	if (res != CURLE_OK) {
		cerr << "Response code " << res << endl;
		return false;
	}

	cout << readBuffer << endl;
	
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
 * @return  pointer to array of Pod
 */
WAPod*
WAEngine::getPods()
{
    return this->Pods;
}
