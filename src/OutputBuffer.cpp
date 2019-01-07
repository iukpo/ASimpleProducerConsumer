#include <iostream>

#include "OutputBuffer.h"

OutputBuffer::OutputBuffer(string outputFile)
{
	mOutputFileName=outputFile;
	mOutputBuf="";
}

void OutputBuffer::storeSortedString(string sortedStr)
{
	mOutputMutex.lock();
	mOutputBuf+=sortedStr;
	mOutputBuf+='\n';
	mOutputMutex.unlock();
}
	
void OutputBuffer::writeBufferToFile()
{
	mFileOutputHandle.open(mOutputFileName);
	mFileOutputHandle<<mOutputBuf;
	mFileOutputHandle.close();
}

OutputBuffer::~OutputBuffer() 
{ 
    
} 
