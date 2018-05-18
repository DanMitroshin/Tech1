#include <iostream>
#include "workers.h"
#include "constWorkers.cpp"
using namespace std;

void GoodWorker::info(){
    cout << GWorker;
}

void BadWorker::info(){
    cout << BWorker;
}

void ManagerWorker::info() {
    cout << MWorker;
}

void DecoratorW::info() {
    w->info();
}

void DecoratorHelp::info() {
    cout << helpAhead;
    DecoratorW::info();
}

void DecoratorInfo::info() {
    cout << helpAhead1;
    DecoratorW::info();
}
