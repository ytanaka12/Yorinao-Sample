#include <Encoder_Driver_Two_Phase.h>

Encoder_Driver_Two_Phase enc_1(2, 3);
Encoder_Driver_Two_Phase enc_2(4, 5);
Encoder_Driver_Two_Phase enc_3(6, 7);

void setup() {
  // put your setup code here, to run once:
  Serial.setTimeout(2);
  Serial.begin(115200);
  
  enc_1.Set_CountMode(4);
  enc_1.Set_EncoderPulse(50);
  enc_2.Set_CountMode(4);
  enc_2.Set_EncoderPulse(50);
  enc_3.Set_CountMode(4);
  enc_3.Set_EncoderPulse(50);
}

void loop() {
  // put your main code here, to run repeatedly:

  enc_1.Read_Pulses();
  enc_2.Read_Pulses();
  enc_3.Read_Pulses();
  double angle_1 = enc_1.Get_Angle();
  double angle_2 = enc_2.Get_Angle();
  double angle_3 = enc_3.Get_Angle();

  int msgSize = 100;
  char outputMsg[100];
  
  if(Serial.available()){
    String str = Serial.readString();
    if(str == "all"){
      Serial.print(angle_1);
      Serial.print(',');
      Serial.print(angle_2);
      Serial.print(',');
      Serial.print(angle_3);
      Serial.print(',');
      Serial.print('\n');
    }
  }
  delay(1);
}
