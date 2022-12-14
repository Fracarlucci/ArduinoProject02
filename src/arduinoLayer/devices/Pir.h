#ifndef __PIR__
#define __PIR__

class Pir {
public:
  Pir(int pin, int calibrating_time);
  void calibrating();
  bool isDetected();

private:
  int pin;  
  int calibrating_time;
  bool detected_status;
};

#endif