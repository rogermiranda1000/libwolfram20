# libwolfram20
C++ library for using API Wolfram|Alpha v2.0.
Version 1.0

## Setup
- [RapidXML](https://techoverflow.net/2019/04/17/how-to-install-rapidxml-on-ubuntu/)
- Place the directory 'Wolfram' into 'deps' folder
- Add 'add_subdirectory(deps/Wolfram)' and 'target_link_libraries(<name> Wolfram)' to your CMakeLists.txt

## Example (using query)

```C++
#include "WAEngine.h"
...
WAEngine search;
search.query.setInput("text for search");
search.query.addFormat("html");
search.query.addFormat("plaintext");

string queryURL = search.getURL();
...
```


## Example (read parsed data)

```C++
WAEngine search;
...
// Data from Wolfram|Alpha in 'data'
...
search.Parse(data);
int numPod = search.getCountPods();
WAPod * pods = search.getPods();

for (int i = 0; i < numPod; i++)
{
    cout << "Pod "   << i << endl;
    cout << "Title:" << pods[i].getTitle() << endl;
    cout << "ID:"    << pods[i].getID()    << endl;

    // Get a count of sub-blocks
    int numSubPod = pods[i].getCountSubpods();
    int numStates = pods[i].getCountStates();
    
    WASubpod * subpods = pods[i].getSubpods();
    WAPodState * states = pods[i].getStates();
    
    // Enumerate a subpods
    for (int j = 0; j < numSubPod; j++)
    {
        cout << "\tSubPod "  << j << endl;
        // Get a subpod attributes
        cout << "\t\tTitle:"   << subpods[j].getTitle() << endl;
        // Get a built-in img attributes
        cout << "\tImg" << endl;
        cout << "\t\tTitle:" << subpods[j].getImage()->getTitle() << endl;
        cout << "\t\tSrc:"   << subpods[j].getImage()->getSrc() << endl;

    }
    
    // Enumerate a states
    for (int j = 0; j < numStates; j++)
    {
        cout << "\tStates " << j << endl;
        cout << "\t\tName:" << states[j].getName() << endl;
    }
}
```