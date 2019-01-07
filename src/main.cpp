#include "OutputBuffer.h"
#include "InputBuffer.h"
#include "main.h"
#include <thread>
#include <algorithm>

const unsigned int MAX_NUM_WORKER_THREADS=4;

enum SortAlgorithm { CountingSort, HeapSort, RadixSort };

static SortAlgorithm algorithm;
static OutputBuffer* outputBuf;
static InputBuffer inputBuf(MAX_NUM_WORKER_THREADS);

void readInput(string inputFileName)
{
	ifstream in;
	in.open(inputFileName);
	string str;

	//Populate input buffer
	while (std::getline(in, str)) 
	{
		inputBuf.storeInputString(str);
    	}
	in.close();

	/*Then, while it isn't empty, call the worker threads. 
	"Block" when maximum number of threads active (inputQueueBusy() is true). 
	Else, increase number of active threads, create new thread.*/
	while (!inputBuf.inputQueueEmpty())
	{
		if (!inputBuf.inputQueueBusy())
		{
			inputBuf.increaseCurrNumberOfConsumingThreads();
			std::thread consumerThread=std::thread(processInputLine);
			consumerThread.detach();
		}
	}

	//Then, wait until all threads have finished processing.
	while (!inputBuf.inputQueueFinished())
	{
		
	}	
}

void processInputLine()
{
	const unsigned int waitPeriod=1;
	if (!inputBuf.inputQueueEmpty())
	{
		vector<int>charsFromInput;

		string sortedOutput;

		string input=inputBuf.retrieveInputString();

		//Get rid of any newlines at the end of the string
		if (!input.empty() && input[input.length()-1] == '\n') {
		    input.erase(input.length()-1);
		}
		
		//Parse each digit in the line, store in a vector for sorting. If a space is encountered, pause for one second.
		for(char& c : input) 
		{
		    if (c!=' ')
		    {
			charsFromInput.push_back(c-'0');
		    }
		    else
		    {
			std::this_thread::sleep_for(std::chrono::seconds(waitPeriod));
		    }
		}

		//Sort vector according to algorithm chosen at runtime.
		switch(algorithm)
		{
			case CountingSort:
				countSort(charsFromInput);
			break;

			case HeapSort:
				heapSort(charsFromInput);
			break;

			default:
				radixSort(charsFromInput);
			break;
		}
		
		//Output results into a comma delimited string.
		for (int &i: charsFromInput)
		{
			sortedOutput+=std::to_string(i)+",";
		}

		//Remove last comma
		sortedOutput.erase(sortedOutput.length()-1);

		//Store result in output buffer
		outputBuf->storeSortedString(sortedOutput);
	}

	//Decrease number of active threads by one-finished.
	inputBuf.decreaseCurrNumberOfConsumingThreads();
}


void countSort(vector <int>& arr) 
{ 
    int max = *std::max_element(arr.begin(), arr.end()); 
    int min = *std::min_element(arr.begin(), arr.end()); 
    int range = max - min + 1; 
      
    vector<int> count(range), output(arr.size());
    int arraySize=(int)arr.size();
    int countSize=(int)count.size();
    for(int i = 0; i < arraySize; i++) 
        count[arr[i]-min]++; 
          
    for(int i = 1; i < countSize; i++) 
           count[i] += count[i-1]; 
    
    for(int i = arraySize-1; i >= 0; i--) 
    {  
         output[ count[arr[i]-min] -1 ] = arr[i];  
              count[arr[i]-min]--;  
    } 
      
    for(int i=0; i < arraySize; i++) 
            arr[i] = output[i]; 
}

void radixSort( vector<int> & arr)
{
    int radix = 1;
    // Largest element in unsorted array
    int max = *(std::max_element(arr.begin(), arr.end()));
    while(max / radix)
    {
        // Buckets used for sorting. Each bucket representing a digit.
        std::vector<std::vector<int>> buckets(10, std::vector<int>());
        for(const auto& num : arr)
        {
            int digit = num / radix % 10;
            buckets[digit].push_back(num);
        }
        std::size_t k = 0;
        // Take the elements out of buckets into the array
        for(std::size_t i = 0; i < 10; i++)
        {
            for(std::size_t j = 0; j < buckets[i].size(); j++)
            {
                arr[k] = buckets[i][j];
                k++;
            }
        }
        // Change the place of digit used for sorting
        radix *= 10;
    }
}

void heapSort(vector<int> & arr) 
{
	//Make a heap from the array.
	std::make_heap(arr.begin(), arr.end());

	//Sort the heap.
	std::sort_heap(arr.begin(), arr.end());
}

int main(int argc, char *argv[])
{
	string inputFileName;
	string outputFileName;
	string sortAlgorithm;
	if (argc!=4)
	{
		cout<<"Usage: ./ProducerConsumer  /path/to/InputFile /path/to/OutputFile algorithmToSort"<<endl;
		cout<<"Supported sorting algorithms: CountingSort, HeapSort, RadixSort"<<endl;
	}
	else
	{
		inputFileName = argv[1];
		outputFileName = argv[2];
		sortAlgorithm = argv[3];
		if (sortAlgorithm.compare("CountingSort")==0)
		{
			algorithm=CountingSort;
		}
		else if (sortAlgorithm.compare("HeapSort")==0)
		{
			algorithm=HeapSort;
		}
		else
		{
			algorithm=RadixSort;
		}
		outputBuf=new OutputBuffer(outputFileName);
		std::thread readThread=std::thread(readInput, inputFileName);
		readThread.join();
		
		//Once producer and all consumers are done, dump all contents to output file.
		outputBuf->writeBufferToFile();
		delete outputBuf;
	}
	return 0;
}
