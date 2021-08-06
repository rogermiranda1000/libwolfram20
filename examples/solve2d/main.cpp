#include <iostream>
#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID

int main(int argc, char const *argv[]) {
	WAEngine search(APP_ID);
	/*search.query.addFormat("html");
	search.query.addFormat("plaintext");*/

	search.query.setInput(std::string("x^3 - 6x^2 + 4x + 12 = 32y"));
	
	std::string contents;
	std::cout << "Searching '" << search.getURL() << "'..." << std::endl;
	if (!WAEngine::DownloadURL(search.getURL(), &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	search.Parse(contents);
	
	WAPod *response = search.getPod("Implicit plot");
	if (response != nullptr) {
		WASubpod *subpod = response->getSubpods()[0];
		if (subpod->hasImage()) std::cout << "Graph: " << subpod->getImage()->getSrc() << std::endl;
	}
	
	return 0;
}