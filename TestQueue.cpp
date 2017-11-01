#include "TestQueue.h"

//TestWrapper is a singly linked-list
TestWrapper* begin;
TestWrapper* end;
int queueCounter = 0;

TestQueue::TestQueue(){}

TestQueue::TestQueue(Test* t){
    this->addTest(t);
}

void TestQueue::addTest(Test* t){
    TestWrapper* tw = new TestWrapper();
    tw->test = t;
    if (queueCounter <= 0){
        begin = tw;
    }
    end->next = tw;
    end = tw;
    queueCounter++;
}
Test* TestQueue::pop(){
    Test* nextTest;
    if (queueCounter >= 1){
        //Return and remove from queue
        nextTest = begin->test;
        //Remove from queue
        TestWrapper* temp = begin->next;
        delete begin;
        begin = temp;
    }
    //Return       
    return nextTest;
}

Test* TestQueue::getCurrentTest(){ //Does not pop from TestQueue
  return begin->test;
}

int TestQueue::size(){
    return queueCounter;
}
