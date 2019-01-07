#include <iostream>

#include "InputBuffer.h"

InputBuffer::InputBuffer(int max)
{
	maxNumOfConsumerThreads=max;
	currNumOfConsumingThreads=0;
}

void InputBuffer::storeInputString(string sortedStr)
{
	mInputBufferAccessMutex.lock();
	mDataQueue.push(sortedStr+"\n");
	mInputBufferAccessMutex.unlock();
}
	
string InputBuffer::retrieveInputString()
{
	string data;
	mInputBufferAccessMutex.lock();
	data=mDataQueue.front();
	mDataQueue.pop();
	mInputBufferAccessMutex.unlock();
	return data;
}

bool InputBuffer::inputQueueBusy()
{
	bool activityState=false;
	mInputBufferAccessMutex.lock();
	if (currNumOfConsumingThreads==maxNumOfConsumerThreads-1)
	{
		activityState=true;
	}
	mInputBufferAccessMutex.unlock();
	return activityState;
}

bool InputBuffer::inputQueueEmpty()
{
	bool isEmpty=false;
	mInputBufferAccessMutex.lock();
	if (mDataQueue.empty())
	{
		isEmpty=true;
	}
	mInputBufferAccessMutex.unlock();
	return isEmpty;
}

bool InputBuffer::inputQueueFinished()
{
	bool isFinished=false;
	mInputBufferAccessMutex.lock();
	if  (currNumOfConsumingThreads==0) 
	{
		isFinished=true;
	}
	mInputBufferAccessMutex.unlock();
	return isFinished;
}

void InputBuffer::increaseCurrNumberOfConsumingThreads()
{
	mInputBufferAccessMutex.lock();
	currNumOfConsumingThreads++;
	mInputBufferAccessMutex.unlock();
}

void InputBuffer::decreaseCurrNumberOfConsumingThreads()
{
	mInputBufferAccessMutex.lock();
	currNumOfConsumingThreads--;
	mInputBufferAccessMutex.unlock();
}

InputBuffer::~InputBuffer() 
{ 
    //Perform any clean up here.
} 
