#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "Test.h"

typedef struct _TestWrapper{
    Test* test;
    struct _TestWrapper* next;
    } TestWrapper;

class TestQueue{
    //TestWrapper is a singly linked-list
    TestWrapper* begin;
    TestWrapper* end;
    unsigned int queueCounter = 0;
  
    public:
    TestQueue();
    TestQueue(Test* t);
    void addTest(Test* t);
    Test* pop();
    int size();
    Test* getCurrentTest();
};



#endif
