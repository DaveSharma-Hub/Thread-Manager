// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <thread>
// #include <function>

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
        ThreadManager(Input& threadManagerInput){
            this->config = threadManagerInput;
            this->threadConfig = {maxThreads:threadManagerInput.numberOfThreads};
        }
        
        void runFunction(uint64_t id){
            this->kernelFunction(id, this->threadConfig,this->inputData, this->outputData);
        }
        
        void setKernelFunction(void (*func)(uint64_t,ThreadIdx& ,void*, void*)){
            this->kernelFunction = func;
        }
        
        void setInputData(void* input){
            this->inputData = input;
        }
        
        void setOutputData(void* output){
            this->outputData = output;
        }
        
        std::thread atomicThreadCreation(uint64_t id) {
          return std::thread([=] { this->runFunction(id); });
        }
        
        void startExecution(){
            //check for input and output data being set
            for(uint64_t i=0;i<config.numberOfThreads;i++){
                uint64_t id = i;
                currentThreads.push_back(move(atomicThreadCreation(id)));
            }
            
            for(int i=0;i<this->currentThreads.size();i++){
                this->currentThreads[i].join();
            }
        }
};



void kernel(uint64_t id, ThreadIdx& threadIdx, void* in, void* out){
    // std::cout<<id;
    if(id < threadIdx.maxThreads){
        for(int i=id*10;i<(id+1)*10;i++){
            ((int*)out)[i] = ((int*)in)[i] * 5;
        }
    }
}

int main() {
    // Write C++ code here
    void* input = new int[100];
    void* output = new int[100];
    
    for(int i=0;i<100;i++){
        ((int*)input)[i] = 1;
    }
    
    Input config = {numberOfThreads:10};
    ThreadManager* manager = new ThreadManager(config);
    manager->setKernelFunction(&kernel);
    manager->setInputData(input);
    manager->setOutputData(output);
    manager->startExecution();
    
    for(int i=0;i<100;i++){
        printf("%d\n",((int*)output)[i]);
    }
    
    return 0;
}

/*

function kernelLevel(index, fn){
    // do whatever you want in fn
    fn(index);
}

function fn(index){
    
}

*/