#include "TestQueue.h"

public class TestQueue{
    //TestWrapper is a singly linked-list
    TestWrapper* begin;
    TestWrapper* end;
    int queueCounter = 0;
    public void TestQueue(Test t){
        this.addTest(t);
        /*TestWrapper tw = new TestWrapper(); 
        tw.test = &t;
        tw.next = 0;  
        begin = &tw;
        end = &tw;
        queueCounter++;*/
    }
    
    public void addTest(Test t){
        TestWrapper tw = new TestWrapper();
        tw.test = &t;
        if (queueCounter <= 0){
            begin = &tw
        }
        end.next = &tw;
        end = &tw;
        queueCounter++;
    }
    public Test pop(){
        Test* nextTest;
        if (queueCounter >= 1){
            //Return and remove from queue
            nextTest = begin.test;
            //Remove from queue
            TestWrapper* temp = begin.next;
            delete begin;
            begin = temp;
        }
        //Return       
        return nextTest;
    }
    public int size(){
        return queueCounter;
    }
}    
