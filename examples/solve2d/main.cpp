#include "WAEngine.h"
#include "secrets.h" // place here #define APP_ID

int main(int argc, char const *argv[]) {
	WAEngine search(APP_ID);
	search.query.addFormat("html");
	search.query.addFormat("plaintext");

	search.query.setInput(std::string("3x^2+2y=7"));
	
	std::string contents;
	std::cout << "Searching '" << search.getURL() << "'..." << std::endl;
	if (!WAEngine::DownloadURL(search.getURL(), &contents)) {
		std::cerr << "Downloading error!" << std::endl;
		return EXIT_FAILURE;
	}
	
	search.Parse(contents);
	
	WAPod *response = search.getPod("Implicit plot");
	if (response != nullptr) {
		std::vector<WASubpod> subpods = response->getSubpods();
		
		// Enumerate a subpods
		for (int j = 0; j < subpods.size(); j++)
		{
			cout << "SubPod "  << j << endl;
			// Get a subpod attributes
			cout << "\tTitle:"   << subpods[j].getTitle() << endl;
			cout << "\tText:"   << subpods[j].getPlainText() << endl;
			
			if (subpods[j].hasImage()) {
				// Get a built-in img attributes
				cout << "Img" << endl;
				cout << "\tTitle:" << subpods[j].getImage()->getTitle() << endl;
				cout << "\tSrc:"   << subpods[j].getImage()->getSrc() << endl;
			}
		}
	}
	
	return 0;
}