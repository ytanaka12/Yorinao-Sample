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
#include "TimeKeeper.h"
#include "Interpolations.h"

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
	sb.SendPulseWidth_us(4, 0);
	sb.SendPulseWidth_us(5, 0);
	sb.SendPulseWidth_us(6, 0);
	sb.SendPulseWidth_us(7, 0);
	sb.SendPulseWidth_us(8, 0);
	sb.SendPulseWidth_us(9, 0);
	sb.SendPulseWidth_us(10, 0);
	sb.SendPulseWidth_us(11, 0);
	sb.SendPulseWidth_us(12, 0);
	sb.SendPulseWidth_us(13, 0);
	usleep(10000);

	/*----------------*/
	/* --- Idling --- */
	/*----------------*/
	cout << "Wait";
	for(int i = 0 ; i < 200 ; i++){
		serial.Update();
		cout << ".";
	}
	cout << endl;
	/*----------------*/
	/*----------------*/
	/*----------------*/

	const double ENC2ANGLE[7] = {- 1.0 / 2.0,
								- 10.0 / 49.0,
								- 25.0 / 27.0,
								  10.0 / 45.0,
								  18.0 / 27.0,
								  10.0 / 45.0,
								  10.0 / 30.0};
	
	double desAng[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	double curAng[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	
	double TargetAng[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	TargetAng[0] = 0.0 * DEG2RAD;
	TargetAng[1] = -45.0 * DEG2RAD;
	TargetAng[2] = 0.0 * DEG2RAD;
	TargetAng[3] = 90.0 * DEG2RAD;
	TargetAng[4] = 0.0 * DEG2RAD;
	TargetAng[5] = 0.0 * DEG2RAD;
	TargetAng[6] = 0.0 * DEG2RAD;

	vector<double>buf_enc = serial.GetValues();
	for(int i = 0 ; i < 7 ; i++){
		curAng[i] = buf_enc[i] * ENC2ANGLE[i];
	}
	
	Interpolations intplt[7];
	for(int i = 0 ; i < 7 ; i++){
		intplt[i].Set_Conditions(1.0, curAng[i], TargetAng[i]);
	}
	
	//Time Keeper
	nsTimeKeeper::TimeKeeper tk;
	
	while(true){
		if(digitalRead(BUTTON_INPUT_PORT) == 1){
			break;
		}
		
		//Get Angles
		serial.Update();
		vector<double> bufs = serial.GetValues();
		static vector<double> angles{0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		if(bufs.size() < 7){
			//cout << "encoder signal is invalid" << endl;
			//break;
		}else{
			angles = bufs;
		}

		for(int i = 0 ; i < 7 ; i++){
			curAng[i] = angles[i] * ENC2ANGLE[i];
		}
		
		desAng[1] = intplt[1].Get_Interpolated_X();
		desAng[3] = intplt[3].Get_Interpolated_X();
		
		for(int i = 0 ; i < 7 ; i++){
			intplt[i].Update();
			desAng[i] = intplt[i].Get_Interpolated_X();
		}
		
		//
		//
		//
		LowLevelControl llc_0;
		llc_0.Set_pGain(2000.0);
		llc_0.Set_Desired_X(desAng[0]);
		llc_0.Set_Current_X(curAng[0]);
		llc_0.Update();
		sb.SendPulseWidth_us(0, llc_0.Get_Output_A() );
		sb.SendPulseWidth_us(1, llc_0.Get_Output_B() );
		
		LowLevelControl llc_1;
		llc_1.Set_pGain(4000.0);
		llc_1.Set_Desired_X(desAng[1]);
		llc_1.Set_Current_X(curAng[1]);
		llc_1.Update();
		sb.SendPulseWidth_us(2, llc_1.Get_Output_A() );
		sb.SendPulseWidth_us(3, llc_1.Get_Output_B() );

		LowLevelControl llc_2;
		llc_2.Set_pGain(2000.0);
		llc_2.Set_Desired_X(desAng[2]);
		llc_2.Set_Current_X(curAng[2]);
		llc_2.Update();
		sb.SendPulseWidth_us(4, llc_2.Get_Output_A() );
		sb.SendPulseWidth_us(5, llc_2.Get_Output_B() );
		
		LowLevelControl llc_3;
		llc_3.Set_pGain(4000.0);
		llc_3.Set_Desired_X(desAng[3]);
		llc_3.Set_Current_X(curAng[3]);
		llc_3.Update();
		sb.SendPulseWidth_us(6, llc_3.Get_Output_A() );
		sb.SendPulseWidth_us(7, llc_3.Get_Output_B() );
		
		LowLevelControl llc_4;
		llc_4.Set_pGain(2000.0);
		llc_4.Set_Desired_X(desAng[4]);
		llc_4.Set_Current_X(curAng[4]);
		llc_4.Update();
		sb.SendPulseWidth_us(9, llc_4.Get_Output_A() );
		sb.SendPulseWidth_us(8, llc_4.Get_Output_B() );
		
		LowLevelControl llc_5;
		llc_5.Set_pGain(3000.0);
		llc_5.Set_Desired_X(desAng[5]);
		llc_5.Set_Current_X(curAng[5]);
		llc_5.Update();
		sb.SendPulseWidth_us(11, llc_5.Get_Output_A() );
		sb.SendPulseWidth_us(10, llc_5.Get_Output_B() );
		
		LowLevelControl llc_6;
		llc_6.Set_pGain(2000.0);
		llc_6.Set_Desired_X(desAng[6]);
		llc_6.Set_Current_X(curAng[6]);
		llc_6.Update();
		sb.SendPulseWidth_us(12, llc_6.Get_Output_A() );
		sb.SendPulseWidth_us(13, llc_6.Get_Output_B() );
		
		//
		//
		//
		tk.TimeKeep();

		if(tick%50 == 0){
			cout << "tick = " << tick;
			cout << endl;
			
			cout << "CurAng: ";
			for(int i = 0 ; i < 7 ; i++){
				cout << curAng[i] * RAD2DEG << " / ";
			}
			cout << endl;
			
			cout << "DesAng: ";
			for(int i = 0 ; i < 7 ; i++){
				cout << desAng[i] * RAD2DEG << " / ";
			}
			cout << endl;
		}

		tick++;

		//usleep(1000);
	}

	return 0;
}
