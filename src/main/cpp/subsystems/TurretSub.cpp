// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/TurretSub.h"

TurretSub::TurretSub(double* pTurretAngle)
{
    m_pTurretAngle = pTurretAngle;
}

void TurretSub::Periodic()
{
    if(m_pTurretAngle != nullptr)
    {
        *m_pTurretAngle = GetTurretAngle();
    }
}

void TurretSub::Init()
{
    m_turret.SetInverted(false);
    ResetTurretEncoder();

    m_encoder.SetDistancePerPulse(kTurretDistancePerPulse);
}

void TurretSub::SetTurretMotor(double speed)
{
    m_turret.Set(speed);
}

double TurretSub::GetTurretAngle()
{
    return m_encoder.Get();
}

void TurretSub::ResetTurretEncoder()
{
    m_encoder.Reset();
}

// IMU FUNCTIONS

double TurretSub::GetXAngle()
{
    //Util::Log("IMU X Angle", (double)m_imu.GetGyroAngleX());
    //return (double)m_imu.GetGyroAngleX();

    Util::Log("IMU X Angle", (double)m_imu.GetAngle());
    return (double)m_imu.GetAngle();
}

double TurretSub::GetYAngle()
{
    //Util::Log("IMU Y Angle", (double)m_imu.GetGyroAngleY());
    //return (double)m_imu.GetGyroAngleY();

    Util::Log("IMU Y Angle", (double)m_imu.GetYComplementaryAngle());
    return (double)m_imu.GetYComplementaryAngle();
}

double TurretSub::GetZAngle()
{
    //Util::Log("IMU Z Angle", (double)m_imu.GetGyroAngleZ());
    //return (double)m_imu.GetGyroAngleZ();

    Util::Log("IMU Z Angle", (double)m_imu.GetXComplementaryAngle());
    return (double)m_imu.GetXComplementaryAngle();
}

void TurretSub::ResetIMU()
{
    m_imu.Reset();
}