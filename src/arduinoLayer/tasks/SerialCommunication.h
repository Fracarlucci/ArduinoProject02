#ifndef __SERIALCOMM__
#define __SERIALCOMM__

#include "Task.h"

class SerialCommunication: public Task{
public:
  void init(int period);
  void tick();
};

#endif