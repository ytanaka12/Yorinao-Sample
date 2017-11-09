/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LowLevelControl.h
 * Author: yasufumi
 *
 * Created on 2017/11/09, 19:26
 */

#ifndef LOWLEVELCONTROL_H
#define LOWLEVELCONTROL_H

class LowLevelControl {
private:
	double Desired_X;
	double Current_X;
	
	double pGain;
	double dGain;
	double iGain;
	
	int DeadZonePW;
	
	int Output_A;
	int Output_B;
	
public:
	LowLevelControl();
	LowLevelControl(const LowLevelControl& orig);
	virtual ~LowLevelControl();
	
	void Set_pGain(double p_gain);
	void Set_dGain(double d_gain);
	void Set_iGain(double i_gain);
	void Set_DeadZonePW(int dead_zone_pw);
	void Set_Desired_X(double desired_x);
	void Set_Current_X(double current_x);
	
	void Update();
	
	int Get_Output_A();
	int Get_Output_B();
};

#endif /* LOWLEVELCONTROL_H */

