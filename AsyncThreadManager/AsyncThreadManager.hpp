#pragma once
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

class AsyncThreadManager{
    private:
        void (*asyncFunction)(void);
        std::thread th;
    public:
        AsyncThreadManager(void (*func)(void));
        AsyncThreadManager* runAsync();
        void await();
};



