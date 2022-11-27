#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "..\tasks\Task.h"

#define MAX_TASKS 50

class Scheduler {
public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
  
private: 
  unsigned int basePeriod;
  unsigned int currentMillis;
  unsigned int previousMillis;
  int nTasks;
  Task* taskList[MAX_TASKS];  
};

#endif