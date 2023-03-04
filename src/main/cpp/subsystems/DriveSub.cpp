// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSub.h"

DriveSub::DriveSub(double* pIMUAngle)
{
    m_pIMUAngle = pIMUAngle;
}

void DriveSub::Periodic()
{
    //*m_pIMUAngle = GetXAngle();

    // Util::Log("Left Get", m_leftEncoder.Get());
    // Util::Log("Right Get", m_rightEncoder.Get());
    // Util::Log("DriveLeft Dist", m_leftEncoder.GetDistance());
    // Util::Log("DriveRight Dist", m_rightEncoder.GetDistance());
    // Util::Log("DriveLeft GetRaw", m_leftEncoder.GetRaw());
}

void DriveSub::Init()
{
    m_rightOne.SetInverted(true);
    m_rightTwo.SetInverted(true);

    //ResetEncoders();

    // m_leftEncoder.SetDistancePerPulse(kDriveDistancePerPulse);
    // m_rightEncoder.SetDistancePerPulse(kDriveDistancePerPulse);
}

// MOTOR FUNCTIONS

void DriveSub::MoveTank(double left, double right)
{
    Util::Log("LeftPower", left);
    Util::Log("RightPower", right);
    Util::Log("Left-Right pwr", left-right);

    // Util::Log("Left Get", m_leftEncoder.Get());
    // Util::Log("Right Get", m_rightEncoder.Get());
    // Util::Log("DriveLeft Dist", m_leftEncoder.GetDistance());
    // Util::Log("DriveRight Dist", m_rightEncoder.GetDistance());

    m_leftOne.Set(left);
    m_leftTwo.Set(left);
    m_rightOne.Set(right);
    m_rightTwo.Set(right);
}

void DriveSub::MoveRC(double horizontal, double vertical)
{
    MoveTank(vertical+horizontal, vertical-horizontal);
}

// ENCODER FUNCTIONS

// double DriveSub::GetLeftDist()
// {
//     Util::Log("DriveLeft Dist", m_leftEncoder.GetDistance());
//     return m_leftEncoder.GetDistance();
// }

// double DriveSub::GetRightDist()
// {
//     Util::Log("DriveRight Dist", m_rightEncoder.GetDistance());
//     return m_rightEncoder.GetDistance();
// }

// double DriveSub::GetLeftVelocity()
// {
//     Util::Log("DriveLeft Rate", m_leftEncoder.GetRate());
//     return m_leftEncoder.GetRate();
// }

// double DriveSub::GetRightVelocity()
// {
//     Util::Log("DriveRight Rate", m_rightEncoder.GetRate());
//     return m_rightEncoder.GetRate();
// }

// void DriveSub::ResetEncoders()
// {
//     m_leftEncoder.Reset();
//     m_rightEncoder.Reset();
// }

// IMU FUNCTIONS

double DriveSub::GetXAngle()
{
    //Util::Log("IMU X Angle", (double)m_imu.GetGyroAngleX());
    return 0.0;//(double)m_imu.GetGyroAngleX();

    // Util::Log("IMU X Angle", (double)m_imu.GetAngle());
    // return (double)m_imu.GetAngle();
}

double DriveSub::GetYAngle()
{
    //Util::Log("IMU Y Angle", (double)m_imu.GetGyroAngleY());
    return 0.0;//(double)m_imu.GetGyroAngleY();

    //Util::Log("IMU Y Angle", (double)m_imu.GetYComplementaryAngle());
    //return (double)m_imu.GetYComplementaryAngle();
}

double DriveSub::GetZAngle()
{
    //Util::Log("IMU Z Angle", (double)m_imu.GetGyroAngleZ());
    return 0.0;//(double)m_imu.GetGyroAngleZ();

    //Util::Log("IMU Z Angle", (double)m_imu.GetXComplementaryAngle());
    //return (double)m_imu.GetXComplementaryAngle();
}

void DriveSub::ResetIMU()
{
    //m_imu.Reset();
}
