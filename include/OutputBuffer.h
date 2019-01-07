/*
Output buffer class. This is the shared object that the consumers will be writing the sorted data to.

A request for forgiveness: While the document specifies that a file should be shared, I am doing so indirectly through the sharing of the OutputBuffer for a specific reason: if I permit each thread to
write to the file (instead of storing the text in a buffer), I could have to open and close the file handle every time I write. While I could a file handle at some point in initialization, then close it
when I am all done, I would have to add extra code to ensure that handle is closed always at the end of the program. Instead, I am having the workers write to a buffer string, then when all the worker threads have finished and the input queue is empty, write everything out in one function call (writeBufferToFile).
*/


#ifndef __OUTPUTBUFFER_H__
#define __OUTPUTBUFFER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
using namespace std;
class OutputBuffer
{

private:
	string mOutputFileName;
	string mOutputBuf;
	ofstream mFileOutputHandle;
	std::mutex mOutputMutex;
public:
	OutputBuffer(string outputFile);
	void storeSortedString(string sortedStr);
	void writeBufferToFile();
	~OutputBuffer();
};

#endif
