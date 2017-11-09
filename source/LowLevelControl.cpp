/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LowLevelControl.cpp
 * Author: yasufumi
 * 
 * Created on 2017/11/09, 19:26
 */

#include "LowLevelControl.h"
#include <math.h>

const int MAX_CYCLING_TIME_OF_PWM_LOW_LEVEL_CONTROL = 3000;

/*-------------*/
/* Constructor */
/*-------------*/
LowLevelControl::LowLevelControl() {
	pGain = 1.0;
	dGain = 1.0;
	iGain = 1.0;
	
	DeadZonePW = 1000;
}

LowLevelControl::LowLevelControl(const LowLevelControl& orig) {
}

/*------------*/
/* Destructor */
/*------------*/
LowLevelControl::~LowLevelControl() {
}


/*-----------*/
/* Set pGain */
/*-----------*/
void LowLevelControl::Set_pGain(double p_gain){
	pGain = p_gain;
}

/*-----------*/
/* Set dGain */
/*-----------*/
void LowLevelControl::Set_dGain(double d_gain){
	dGain = d_gain;
}

/*-----------*/
/* Set iGain */
/*-----------*/
void LowLevelControl::Set_iGain(double i_gain){
	iGain = i_gain;
}

/*------------------------------------------*/
/* Dead Zone of Motor Driver in Pulse Width */
/*------------------------------------------*/
void LowLevelControl::Set_DeadZonePW(int dead_zone_pw){
	DeadZonePW = dead_zone_pw;
}

/*---------------*/
/* Set Desired X */
/*---------------*/
void LowLevelControl::Set_Desired_X(double desired_x){
	Desired_X = desired_x;
}

/*---------------*/
/* Set Current_X */
/*---------------*/
void LowLevelControl::Set_Current_X(double current_x){
	Current_X = current_x;
}


/*--------*/
/* Update */
/*--------*/
void LowLevelControl::Update(){
	double output = pGain * (Desired_X - Current_X);
	
	if(0.0 < output){
		output = fabs(output);
		output += (double)DeadZonePW;
		if((double)MAX_CYCLING_TIME_OF_PWM_LOW_LEVEL_CONTROL < output){
			output = (double)MAX_CYCLING_TIME_OF_PWM_LOW_LEVEL_CONTROL;
		}
		Output_A = 0;
		Output_B = (int)output;
	}else{
		output = fabs(output);
		output += (double)DeadZonePW;
		if((double)MAX_CYCLING_TIME_OF_PWM_LOW_LEVEL_CONTROL < output){
			output = (double)MAX_CYCLING_TIME_OF_PWM_LOW_LEVEL_CONTROL;
		}
		Output_A = (int)output;
		Output_B = 0;
	}
}


/*-------------------------*/
/* Get Output for 1st port */
/*-------------------------*/
int LowLevelControl::Get_Output_A(){
	return Output_A;
}

/*-------------------------*/
/* Get Output for 2nd port */
/*-------------------------*/
int LowLevelControl::Get_Output_B(){
	return Output_B;
}

