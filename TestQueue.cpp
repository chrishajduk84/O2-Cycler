#include "TestQueue.h"

//TestWrapper is a singly linked-list
TestWrapper* begin;
TestWrapper* end;
int queueCounter = 0;

TestQueue::TestQueue(){}

TestQueue::TestQueue(Test* t){
    this->addTest(t);
    /*TestWrapper tw = new TestWrapper(); 
    tw.test = &t;
    tw.next = 0;  
    begin = &tw;
    end = &tw;
    queueCounter++;*/
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
int TestQueue::size(){
    return queueCounter;
}
