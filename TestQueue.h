#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "Test.h"

typedef struct _TestWrapper{
    Test* test; cycles:1 = true;
    struct _TestWrapper next;
    } TestWrapper;

public class TestQueue{
    public void TestQueue(Test t);
    public void addTest(Test t);
    public Test pop();
    public int size();
}



#endif
