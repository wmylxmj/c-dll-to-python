// pydll1.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

#define exfun extern "C" __declspec(dllexport)

typedef struct
{
	double kp;//比例系数
	double ki;//积分系数
	double kd;//微分系数
	double set_point;//设定值
	double integration_sum;//误差积分项
	double p_term;//比例控制的返回值
	double i_term;//积分控制的返回值
	double d_term;//微分控制的返回值
	double now_error;//当前误差
	double last_error;//上一次误差
} SPID;

exfun void PIDInit(SPID *pid)
{
	pid->p_term = 0;
	pid->i_term = 0;
	pid->d_term = 0;
	pid->integration_sum = 0;
	pid->last_error = 0;
	pid->now_error = 0;
}

exfun void PIDConfigure(SPID *pid, double kp, double ki, double kd, double setpoint)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->set_point = setpoint;
	PIDInit(pid);
}

exfun double PIDControlPositionType(SPID *pid, double position)//位置试PID
{
	pid->now_error = pid->set_point - position;//求当前误差
	pid->integration_sum = pid->integration_sum + pid->now_error;//积分项累加
	pid->p_term = pid->kp * pid->now_error;
	pid->i_term = pid->ki * pid->integration_sum;
	pid->d_term = pid->kd * (pid->now_error - pid->last_error);
	pid->last_error = pid->now_error;
	return pid->p_term + pid->i_term + pid->d_term;
}

exfun char* PrintTime(void)
{
	time_t t;
	struct tm tm_time;
	char time_str[32];
	char return_info[40];
	time(&t);
	localtime_s(&tm_time, &t);
	asctime_s(time_str, &tm_time);
	sprintf_s(return_info, "Time: %s", time_str);
	return return_info;
}

