# A Simple Producer/Consumer

This is a simple Producer/Consumer program written in C++ 11 for Linux that sorts input items in an input file and outputs them to an output file.

## How to build?

After pulling from GitHub, simply run **cmake .** to generate the Makefile. Then, run **make**.

## Choice of Sorting Algorithms

For this program, three sorting algorithms were chosen: CountingSort, RadixSort, and HeapSort.

CountingSort was chosen because we the range of inputs in the data is much smaller than the size of the data itself to be sorted (at least, generally-there are only ten possible values-the digits 0-9, which is smaller in size than any file containing more than ten digits). It also yields good time and space complexity with an average of O(n+k).

HeapSort was chosen as a sorting method because the underlying structure used, a heap, is sorted using a binary tree, which is a natural choice for sorting numbers. It is not as fast as CountingSort (O(N log N) vs O(N+K)), but it consumes less memory. It is also the only unstable sorting algorithm; Meaning, any information about the ordering of the items in the original sequence is lost during the process.

RadixSort was chosen because it sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value, so like HeapSort, it lends itself towards sorting numbers. However, this form of sorting is only competitive with the other two algorithms if the data to be sorted is numerical. Otherwise, there will be overhead in mapping data to something numerical for sorting. 

## How to use

**./ProducerConsumer  /path/to/InputFile /path/to/OutputFile algorithmToSort**


## License

None.
