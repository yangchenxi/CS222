#ifndef _pfm_h_
#define _pfm_h_

typedef unsigned PageNum;
typedef int RC;
typedef unsigned char byte;

#define PAGE_SIZE 4096
#define INFO_BLOCK_SIZE 2
//use 2 bytes to represent the index number info 这个是跟unsigned short搭配的，所以这里就不要动了

#include <string>
#include <climits>
#include <fstream>

class FileHandle;

class PagedFileManager {
public:
    static PagedFileManager &instance();                                // Access to the _pf_manager instance

    RC createFile(const std::string &fileName);                         // Create a new file
    RC destroyFile(const std::string &fileName);                        // Destroy a file
    RC openFile(const std::string &fileName, FileHandle &fileHandle);   // Open a file
    RC closeFile(FileHandle &fileHandle);                               // Close a file

protected:
    PagedFileManager();                                                 // Prevent construction
    ~PagedFileManager();                                                // Prevent unwanted destruction
    PagedFileManager(const PagedFileManager &);                         // Prevent construction by copying
    PagedFileManager &operator=(const PagedFileManager &);              // Prevent assignment

private:
    static PagedFileManager *_pf_manager;
};

class FileHandle {
public:
    std::fstream myFile;
    std::string filename;
    // variables to keep the counter for each operation
    unsigned readPageCounter;
    unsigned writePageCounter;
    unsigned appendPageCounter;
    unsigned RootPage;

    FileHandle();                                                       // Default constructor
    ~FileHandle();                                                      // Destructor

    RC readPage(PageNum pageNum, void *data);                           // Get a specific page
    RC writePage(PageNum pageNum, const void *data);                    // Write a specific page
    RC appendPage(const void *data);                                    // Append a specific page
    unsigned getNumberOfPages();                                        // Get the number of pages in the file
    RC collectCounterValues(unsigned &readPageCount, unsigned &writePageCount,
                            unsigned &appendPageCount);                 // Put current counter values into variables
};

#endif