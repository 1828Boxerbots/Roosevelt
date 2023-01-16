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
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
}

// MOTOR FUNCTIONS

void DriveSub::MoveTank(double left, double right)
{
    m_leftDrive.Set(left);
    m_rightDrive.Set(right);
}

void DriveSub::MoveRC(double horizontal, double vertical)
{
    MoveTank(horizontal+vertical, horizontal-vertical);
}

// ENCODER FUNCTIONS

int DriveSub::GetLeftDist()
{
    return m_leftEncoder.GetDistance();
}

int DriveSub::GetRightDist()
{
    return m_rightEncoder.GetDistance();
}

void DriveSub::ResetEncoders()
{
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
}

// IMU FUNCTIONS

double DriveSub::GetXAngle()
{
    return (double)m_imu.GetGyroAngleX();
}

double DriveSub::GetYAngle()
{
    return (double)m_imu.GetGyroAngleY();
}

double DriveSub::GetZAngle()
{
    return (double)m_imu.GetGyroAngleZ();
}
