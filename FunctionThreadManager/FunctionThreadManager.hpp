#pragma once
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

struct Input{
    uint64_t numberOfThreads;
}typedef Input;

struct ThreadIdx{
    uint64_t maxThreads;
}typedef ThreadIdx;

class ThreadManager{
    private:
        Input config; 
        std::vector<thread> currentThreads;
        void (*kernelFunction)(uint64_t, ThreadIdx& ,void*, void*);
        void* inputData;
        void* outputData;
        ThreadIdx threadConfig;
    public:
        ThreadManager(Input& threadManagerInput);
        
        void runFunction(uint64_t id);
        
        void setKernelFunction(void (*func)(uint64_t,ThreadIdx& ,void*, void*));
        
        void setInputData(void* input);
        
        void setOutputData(void* output);
        
        std::thread atomicThreadCreation(uint64_t id);
        
        void startExecution();
};
