// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSub.h"

DriveSub::DriveSub() = default;

// This method will be called once per scheduler run
void DriveSub::Periodic() {}

void DriveSub::Init()
{
    m_rightDrive.SetInverted(true);
    m_leftEncoder.SetDistancePerPulse((8.0*M_PI) / 7560.0);
    m_rightEncoder.SetDistancePerPulse((8.0*M_PI) / 7560.0);
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
}

// MOTOR FUNCTIONS

void DriveSub::MoveTank(double left, double right)
{
    Util::Log("LeftPower", left);
    Util::Log("RightPower", right);
    Util::Log("Left-Right pwr", left-right);
    m_leftDrive.Set(left);
    m_rightDrive.Set(right);
}

void DriveSub::MoveRC(double horizontal, double vertical)
{
    MoveTank(vertical+horizontal, vertical-horizontal);
}

// ENCODER FUNCTIONS

double DriveSub::GetLeftDist()
{
    Util::Log("DriveLeft Dist", m_leftEncoder.GetDistance());
    return m_leftEncoder.GetDistance();
}

double DriveSub::GetRightDist()
{
    Util::Log("DriveRight Dist", m_rightEncoder.GetDistance());
    return m_rightEncoder.GetDistance();
}

double DriveSub::GetLeftVelocity()
{
    Util::Log("DriveLeft Rate", m_leftEncoder.GetRate());
    return m_leftEncoder.GetRate();
}

double DriveSub::GetRightVelocity()
{
    Util::Log("DriveRight Rate", m_rightEncoder.GetRate());
    return m_rightEncoder.GetRate();
}

void DriveSub::ResetEncoders()
{
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
}

// IMU FUNCTIONS

double DriveSub::GetXAngle()
{
    Util::Log("IMU X Angle", (double)m_imu.GetGyroAngleX());
    Util::Log("new IMU GetAngle", (double)m_newIMU.GetAngle());
    return (double)m_imu.GetGyroAngleX();
}

double DriveSub::GetYAngle()
{
    Util::Log("IMU Y Angle", (double)m_imu.GetGyroAngleY());
    //return (double)m_imu.GetGyroAngleY();
    Util::Log("new IMU GetYComplementaryAngle", (double)m_newIMU.GetYComplementaryAngle());
    return (double)m_newIMU.GetYComplementaryAngle(); 
}

double DriveSub::GetZAngle()
{
    Util::Log("Gyro Z", (double)m_imu.GetGyroAngleZ());
    return (double)m_imu.GetGyroAngleZ();
}
