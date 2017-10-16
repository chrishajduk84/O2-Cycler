#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "Test.h"

typedef struct _TestWrapper{
    Test* test;
    struct _TestWrapper* next;
    } TestWrapper;

class TestQueue{
    public:
    TestQueue();
    TestQueue(Test* t);
    void addTest(Test* t);
    Test* pop();
    int size();
};



#endif
