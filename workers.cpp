#include <iostream>
#include "workers.h"
#include "constWorkers.cpp"
using namespace std;

void GoodWorker::info(){
    cout << GWorker << endl;
}

void BadWorker::info(){
    cout << BWorker << endl;
}

void ManagerWorker::info() {
    cout << MWorker << endl;
}