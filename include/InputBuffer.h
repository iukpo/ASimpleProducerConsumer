/*
Input buffer class. This is the object that will be holding all the data for the workers (consumers) to be operating on.
Data will be stored using a queue to enforce FIFO.  
*/

#ifndef __INPUTBUFFER_H__
#define __INPUTBUFFER_H__

#include <string>
#include <queue>
#include <stack>
#include <mutex>
using namespace std;
class InputBuffer
{
	private:
		queue<string> mDataQueue;
		std::mutex mInputBufferAccessMutex;
		int maxNumOfConsumerThreads;
		int currNumOfConsumingThreads;
	public:
		InputBuffer(int maxNumConsumers);

		//Add data to be consumed
		void storeInputString(string sortedStr);

		//Pull data to be consumed from the front of the queue.
		string retrieveInputString();

		//Returns true if maximum number of worker threads active.
		bool inputQueueBusy();

		//Returns true if the queue is empty.
		bool inputQueueEmpty();

		//Returns true if the queue is finished (that is, currNumOfConsumingThreads is zero. Should only be called if there has ever been any work to be done).
		bool inputQueueFinished();

		//Increases the current count of consuming threads.
		void increaseCurrNumberOfConsumingThreads();

		//Decreases the current count of consuming threads.
		void decreaseCurrNumberOfConsumingThreads();

		~InputBuffer();
};

#endif
