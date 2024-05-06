#include "AsyncThreadManager.hpp"

AsyncThreadManager::AsyncThreadManager(void (*func)(void)){
    this->asyncFunction = func;
}

AsyncThreadManager* AsyncThreadManager::runAsync(){
    std::thread tmp([=] { this->asyncFunction(); });
    this->th = move(tmp);
    return this;
}
void AsyncThreadManager::await(){
    if (this->th.joinable()){
        this->th.join();
    }
}