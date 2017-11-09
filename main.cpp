/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yasufumi
 *
 * Created on 2017/11/08, 23:54
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <vector>

#include <wiringPi.h>
#include "ServoBlaster.h"
#include "Serial_CSV_Format.h"
#include "LowLevelControl.h"

using namespace std;

const double DEG2RAD = 3.1415 / 180.0;
const double RAD2DEG = 180.0 / 3.1415;

const int BUTTON_INPUT_PORT = 21;

const int ENCORDER_A_PORT = 16;
const int ENCORDER_B_PORT = 20;

/*
 * 
 */
int main(int argc, char** argv) {
	
	cout << "hello world" << endl;
	
	if(wiringPiSetupGpio() == -1){
		return 1;
	}
	
	pinMode(BUTTON_INPUT_PORT, INPUT);

	//ServoBlaster
	nsServoBlaster::ServoBlaster sb;
	
	//Ecoder(serial connection)
	nsSerial_CSV_Format::Serial_CSV_Format serial;
	
	int tick = 0;

	//unlock
	sb.SendPulseWidth_us(0, 0);
	sb.SendPulseWidth_us(1, 0);
	sb.SendPulseWidth_us(2, 0);
	sb.SendPulseWidth_us(3, 0);
	usleep(10000);
	
	while(true){
		if(digitalRead(BUTTON_INPUT_PORT) == 1){
			break;
		}
		
		//Get Angles
		serial.Update();
		vector<double> bufs = serial.GetValues();
		static vector<double> angles{0.0 , 0.0, 0.0};
		if(bufs.size() == 0){
			//cout << "encoder signal is invalid" << endl;
			//break;
		}else{
			angles = bufs;
		}

		angles[0] *= - 1.0 / 2.0;	//ratio
		angles[1] *= - 2.0 / 9.0;	//ratio
		angles[2] *= - 50.0 / 55.0;	//ratio
		
//		int pwm = 500 * cos((double)tick / 1000.0) + 1500.0;
//		sb.SendPulseWidth_us(0, pwm);
//		sb.SendPulseWidth_us(1, 0);
		
		double Target_0 = 0.0 * DEG2RAD;
		double Target_1 = 0.0 * DEG2RAD;
		double Target_2 = 0.0 * DEG2RAD;
		
		LowLevelControl llc_0;
		llc_0.Set_pGain(2000.0);
		llc_0.Set_Desired_X(Target_0);
		llc_0.Set_Current_X(angles[0]);
		llc_0.Update();
		sb.SendPulseWidth_us(0, llc_0.Get_Output_A() );
		sb.SendPulseWidth_us(1, llc_0.Get_Output_B() );
		
		LowLevelControl llc_1;
		llc_1.Set_pGain(2000.0);
		llc_1.Set_Desired_X(Target_1);
		llc_1.Set_Current_X(angles[1]);
		llc_1.Update();
		sb.SendPulseWidth_us(2, llc_1.Get_Output_A() );
		sb.SendPulseWidth_us(3, llc_1.Get_Output_B() );

		LowLevelControl llc_2;
		llc_2.Set_pGain(2000.0);
		llc_2.Set_Desired_X(Target_2);
		llc_2.Set_Current_X(angles[2]);
		llc_2.Update();
		sb.SendPulseWidth_us(4, llc_2.Get_Output_A() );
		sb.SendPulseWidth_us(5, llc_2.Get_Output_B() );
		
//		double pGain = 2000.0;
//		double dGain = 1.0;
//		double target = 0.0 * DEG2RAD;
//		double output = pGain * (target - angles[0]);
//		
//		if(0.0 < output){
//			output += 1000.0;
//			if(3000.0 < output){
//				output = 3000.0;
//			}
//			sb.SendPulseWidth_us(0, 0);
//			sb.SendPulseWidth_us(1, (int)output);
//		}else{
//			output = - output;	
//			output += 1000.0;
//			if(3000.0 < output){
//				output = 3000.0;
//			}
//			sb.SendPulseWidth_us(0, (int)output);
//			sb.SendPulseWidth_us(1, 0);
//		}

		if(tick%50 == 0){
			cout << "tick = " << tick;
//			cout << " / pwm = " << output;
			cout << " angle: " << angles[0] * RAD2DEG;
			cout << " / " << angles[1] * RAD2DEG;
			cout << " / " << angles[2] * RAD2DEG;
			cout << endl;
		}

		tick++;

		usleep(1000);
	}

	return 0;
}
