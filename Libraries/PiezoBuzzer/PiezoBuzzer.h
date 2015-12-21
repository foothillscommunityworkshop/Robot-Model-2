#ifndef PiezoBuzzer_h
#define PiezoBuzzer_h


class PiezoBuzzer
{
  public:
    PiezoBuzzer(int pinId);
    void Beep(int amount);
    void SetBuzzerLength(int length);

  private:
   int _pinId;  
};



#endif


