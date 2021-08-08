#include <iostream>
#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID

int main(int argc, char const *argv[]) {
	WAEngine searcher(APP_ID);
	
	std::string contents;
	std::string url = searcher.getURL( std::string("16,000,000th Fibonacci number") );
	std::cout << "Searching '" << url << "'..." << std::endl;
	if (!WAEngine::DownloadURL(url, &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	WAResult *search = searcher.getResult(contents);
	WAPod *response = search->getPod("Decimal approximation");
	if (response != nullptr) {
		std::cout << "Solution: "   << response->getSubpods()[0]->getPlainText() << std::endl;
	}
	else std::cout << "Keep searching!" << std::endl;
	delete search;
	
	
	
	
	
	
	// now it will stop at 10s
	searcher.setTimeout(10);
	
	
	
	
	
	url = searcher.getURL( std::string("16,000,000th Fibonacci number") );
	std::cout << "Searching '" << url << "'..." << std::endl;
	if (!WAEngine::DownloadURL(url, &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	search = searcher.getResult(contents);
	response = search->getPod("Decimal approximation");
	if (response != nullptr) {
		std::cout << "Solution: "   << response->getSubpods()[0]->getPlainText() << std::endl;
	}
	delete search;
	
	return 0;
}