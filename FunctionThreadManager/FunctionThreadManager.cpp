#include "FunctionThreadManager.hpp"

ThreadManager::ThreadManager(Input& threadManagerInput){
    this->config = threadManagerInput;
    this->threadConfig = {maxThreads:threadManagerInput.numberOfThreads};
}

void ThreadManager::runFunction(uint64_t id){
    this->kernelFunction(id, this->threadConfig,this->inputData, this->outputData);
}

void ThreadManager::setKernelFunction(void (*func)(uint64_t,ThreadIdx& ,void*, void*)){
    this->kernelFunction = func;
}

void ThreadManager::setInputData(void* input){
    this->inputData = input;
}

void ThreadManager::setOutputData(void* output){
    this->outputData = output;
}

std::thread ThreadManager::atomicThreadCreation(uint64_t id) {
    return std::thread([=] { this->runFunction(id); });
}

void ThreadManager::startExecution(){
    //check for input and output data being set
    for(uint64_t i=0;i<config.numberOfThreads;i++){
        uint64_t id = i;
        currentThreads.push_back(move(atomicThreadCreation(id)));
    }
    
    for(int i=0;i<this->currentThreads.size();i++){
        this->currentThreads[i].join();
    }
}