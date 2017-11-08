/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Encoder_Driver_Two_Phase.h
 * Author: yasufumi
 *
 * Created on 2017/10/12, 19:07
 */

#ifndef ENCODER_DRIVER_TWO_PHASE_H
#define ENCODER_DRIVER_TWO_PHASE_H

#include "Arduino.h"

class Encoder_Driver_Two_Phase {
private:
  int DIN_Port_A;
  int DIN_Port_B;
  int ENC_PULSE;

  double PULSE2DEG_1, PULSE2DEG_2, PULSE2DEG_4;
  double PULSE2RAD_1, PULSE2RAD_2, PULSE2RAD_4;
  
  bool Pulse_A;
  bool Pulse_B;
  bool Bef_Pulse_A;
  bool Bef_Pulse_B;

  int CountMode;  //1 or 2 or 4
  int Counter;
  
  bool InitTrig;
  
  void Init();
  void PulseCounter_Multiplication_1();
  void PulseCounter_Multiplication_2();
  void PulseCounter_Multiplication_4();
  
public:
  Encoder_Driver_Two_Phase();
  Encoder_Driver_Two_Phase(int din_port_a, int din_port_b);
  Encoder_Driver_Two_Phase(const Encoder_Driver_Two_Phase& orig);
  virtual ~Encoder_Driver_Two_Phase();
  
  void Set_DIN_PORTS(int din_port_a, int din_port_b);
  void Set_EncoderPulse(int enc_pulse);
  void Set_CountMode(int c_mode);
  
  void Read_Pulses();
  
  double Get_Angle();
private:

};

#endif /* ENCODER_DRIVER_TWO_PHASE_H */


