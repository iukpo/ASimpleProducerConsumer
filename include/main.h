/*
Header for functions defined in the main entry point (main.cpp). Provided to enforce separation of declaration and implementation.
*/

#ifndef __MAIN_H__
#define __MAIN_H__

#include <string>

//Producer thread. This thread reads each line of the input file and stores it in the InputBuffer. It waits until all consumer (worker) threads are done before exiting and bringing about program end.
void readInput(string inputFileName);

//Consumer thread. Obtains line of data from InputBuffer, sorts it, then saves the stored result in the OutputBuffer.
void processInputLine();

//Sorting functions. heapSort adapted from https://en.cppreference.com, rest adapted from Data Structures and Algorithm Analysis in C++ (Fourth Edition). 
void countSort(vector <int>& arr);

void radixSort( vector<int> & arr);

void heapSort(vector<int> & arr);

#endif
