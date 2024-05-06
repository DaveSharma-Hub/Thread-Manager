#include "FunctionThreadManager.cpp"

using namespace std;

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