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
    Util::Log("Turret Speed", speed);
    Util::Log("Turret Get", m_encoder.Get());
    Util::Log("Turret Distance", m_encoder.GetDistance());

    m_turret.Set(speed);
}

double TurretSub::GetTurretAngle()
{
    Util::Log("Turret Get", m_encoder.Get());
    Util::Log("Turret Distance", m_encoder.GetDistance());
    return m_encoder.Get();
    return 0;
}

void TurretSub::ResetTurretEncoder()
{
    m_encoder.Reset();
}