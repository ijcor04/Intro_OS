#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Page {
public:
    unsigned int pageNumber;
    bool referenced;
    
    Page(unsigned int num) : pageNumber(num), referenced(false) {}
};

class PageFaultAnalyzer {
private:
    vector<Page> frames;
    int maxFrames;
    int pageFaults;
    
    bool isPageInMemory(unsigned int pageNumber) {
        return find_if(frames.begin(), frames.end(),
            [pageNumber](const Page& p) { return p.pageNumber == pageNumber; }) != frames.end();
    }
    
    void addPage(unsigned int pageNumber) {
        // If there's still space in frames
        if (frames.size() < maxFrames) {
            frames.push_back(Page(pageNumber));
            pageFaults++;
            return;
        }
        
        // Use Second Chance algorithm
        while (true) {
            for (auto& page : frames) {
                if (!page.referenced) {
                    page.pageNumber = pageNumber;
                    page.referenced = false;
                    pageFaults++;
                    return;
                }
                page.referenced = false;
            }
        }
    }

public:
    PageFaultAnalyzer(int physicalMemorySize, int pageSize) {
        maxFrames = physicalMemorySize / pageSize;
        pageFaults = 0;
    }
    
    void processAddress(unsigned int address) {
        unsigned int pageNumber = address / 1024;  // 1024 is page size
        
        if (!isPageInMemory(pageNumber)) {
            addPage(pageNumber);
        } else {
            // Set referenced bit for Second Chance algorithm
            auto it = find_if(frames.begin(), frames.end(),
                [pageNumber](Page& p) { return p.pageNumber == pageNumber; });
            if (it != frames.end()) {
                it->referenced = true;
            }
        }
    }
    
    int getPageFaults() const {
        return pageFaults;
    }
};

int main() {
    ifstream inFile("input.txt");
    if (!inFile) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    
    // Initialize analyzer with 64KB physical memory and 1024B page size
    PageFaultAnalyzer analyzer(64 * 1024, 1024);
    
    int code;
    unsigned int address;
    
    // Read hexadecimal addresses
    while (inFile >> code >> hex >> address) {
        analyzer.processAddress(address);
    }
    
    cout << "Total page faults: " << analyzer.getPageFaults() << endl;
    
    inFile.close();
    return 0;
}
