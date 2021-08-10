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

/**
 * Wolfram API's default timeout per query
 */
#define DEFAULT_TIMEOUT 5

/**
 * Latitude/longitude
 */
typedef struct {
	float latitude;			//!< Latitude
	float longitude;		//!< Longitude
} Location;

/**
 * API query petition manager.
 * More information on [Wolfram documentation](https://products.wolframalpha.com/api/documentation/#parameter-reference).
 */
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
    std::string _input;								//!< Text to search
	unsigned int _timeout;							//!< The number of seconds to allow Wolfram|Alpha to compute results in the "scan" stage of processing (in general, the most time-consuming stage)
	// TODO parsetimeout, formattimeout, podtimeout, totaltimeout

    /*
     * NOT REALESED
     *
    std::string ip;									//!< Specifies a custom query location based on an IP address
    std::string location;							//!< Specifies a custom query location based on a string
    // Objects, not double, so that they can have null == unassigned
    Location _lat_long;								//!< Specifies a custom query location based on a latitude/longitude pair

    bool metric;									//!< Lets you specify the preferred measurement system, either "metric" or "nonmetric" (US customary units)
	
	// TODO img size attributes
	*/

	/**
	 * The desired format for individual result pods
	 * It can be "image", "imagemap", "plaintext", "minput", "moutput", "cell", "mathml", "sound" and "wav"
	 */
    std::vector<std::string> _formats;
    std::vector<std::string> _podTitle;				//!< Specifies a pod title to include in the result
    std::vector<int> _podIndexes;					//!< Specifies the index(es) of the pod(s) to return
    std::vector<std::string> _podScanners;			//!< Specifies that only pods produced by the given scanner should be returned
    std::vector<std::string> _includePodIDs;		//!< Specifies a pod ID to include in the result
    std::vector<std::string> _excludePodIDs;		//!< Specifies a pod ID to exclude from the result
	
	static std::set<char> _special_char;			//!< Characters on https://es.wikipedia.org/wiki/C%C3%B3digo_porciento
	
    template <typename T> std::string VectorToStr(const char *prefix, bool individual, std::vector<T>& t);
    template <typename T> std::string VectorToStr(std::string prefix, bool individual, std::vector<T>& t);
	
	static std::string parseInput(std::string str);
};

/**
 * Template for converting any data to string
 *
 * @param[in]	t		Data to convert
 * @return  			Converted string
 */
template <class T>
inline std::string to_string (const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // WAQUERY_H
