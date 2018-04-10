#ifndef CONSTRAIN_HPP
#define CONSTARIN_HPP

class Constrain
{
  public:
    Constrain(){};
    Constrain(int _on, int _weight) : weight(_weight)
    {
      if (_on)
      {
        on = true;
      }
      else
      {
        on = false;
      }
    }
    Constrain(int _on, int _weight, int _value) : weight(_weight), value(_value)
    {
      if (_on)
      {
        on = true;
      }
      else
      {
        on = false;
      }
    }
    int on;
    int weight;
    int value;
    ~Constrain(){}
};

#endif
