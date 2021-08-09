/********************************************************************
 *		@file WAQuery.h
 *		API query petition manager
 *
 *      @author 	Nikolenko Konstantin <knikolenko@yandex.ru>
 *		@author 	Roger Miranda <contacto@rogermiranda1000.com>
 *		@date		2011-2021
 *******************************************************************/

#ifndef WAQUERY_H
#define WAQUERY_H

#include <string>
#include <set>
#include <sstream>
#include <vector>

class WAQuery
{
public:
    WAQuery();

    std::string toString();

    std::string getInput();
    void setInput(std::string input);

    void addFormat(std::string format);
	void addFormat(const char *format);
    void clearFormats();
	
	void setTimeout(unsigned int value);

    ////////////  Location-related properties  /////////////

    /*
     * NOT REALESED
     *
    string  getIP();
    void    setIP(string ip);

    double* getLatLong();
    void    setLatLong(string latlong);
    void    setLatitude(double latitude);
    void    setLongitude(double longitude);

    string  getLocation();
    void    setLocation(string loc);

    bool    isMetric();
    void    setMetric(bool metric);

    string  getCurrency();
    void    setCurrency(string currency);

    string  getCountryCode();
    void    setCountryCode(string code);

    bool    isAllowTranslation();
    void    setAllowTranslation(bool allow);
    */

    ////////////////  Pod selection  //////////////////

    void addPodTitle(std::string podtitle);
    void clearPodTitles();

    void addPodIndex(int podindex);
    void clearPodIndexes();

    void addPodScanner(std::string podscanner);
    void clearPodScanners();

    void addIncludePodID(std::string podid);
    void clearIncludePodIDs();

    void addExcludePodID(std::string podid);
    void clearExcludePodIDs();

    ///////////  Assumptions and podstates  ////////////

    /*
     * NOT REALESED
     *
    void    addAssumption(string assumption);
    void    clearAssumptions();

    //WAPodState[] getPodStates();
    // This doesn't really work for <statelist>-type states. The query will work, but if you modify an existing
    // query, you won't get the new state replacing the old state. Instead, you get chaining, so the old replacement happens
    // followed by the new replacement. Probably still works, but it's inefficient. (I'm not sure if the order is guaranteed,
    // so the old state might still be in effect.)
    void    addPodState(string podstate);
    // This one is for <statelist> types, but not intended to be called by users, since they don't know what the id is.
    void    addPodState(string podstate, long id);
    //void addPodState(WAPodState podstate);
    void    clearPodStates();

    //////////////////  From URL  ////////////////

    // Take values from an API-style URL.
    //void    fillFromURL(string url);
    */

private:
    std::string input;
	unsigned int timeout;

    std::string ip;
    std::string location;
    // Objects, not double, so that they can have null == unassigned
    double latitude;
    double longitude;

    bool metric;
    std::string currency;
    std::string countryCode;

    std::vector<std::string> formats;
    std::vector<std::string> PodTitle;
    std::vector<int> PodIndexes;
    std::vector<std::string> PodScanners;
    std::vector<std::string> IncludePodIDs;
    std::vector<std::string> ExcludePodIDs;
	
	static std::set<char> special_char;				//!< Characters on https://es.wikipedia.org/wiki/C%C3%B3digo_porciento
	
    // Template for concatenating item vector to string
    template <typename T> std::string VectorToStr(const char *prefix, bool individual, std::vector<T>& t);
    template <typename T> std::string VectorToStr(std::string prefix, bool individual, std::vector<T>& t);
	
	static std::string parseInput(std::string str);
};

/**
 * Template for converting any data to string
 *
 * @return  Converted string
 */
template <class T>
inline std::string to_string (const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // WAQUERY_H
