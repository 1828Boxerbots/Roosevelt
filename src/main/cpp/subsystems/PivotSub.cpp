// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/PivotSub.h"

PivotSub::PivotSub(double* pPivotAngle)
{
    m_pPivotAngle = pPivotAngle;
}

void PivotSub::Periodic()
{
    if(m_pPivotAngle != nullptr)
    {
        *m_pPivotAngle = GetPivotAngle();
    }
}

void PivotSub::Init()
{
    ResetPivotEncoder();
    m_pivot.SetInverted(true);

    m_encoder.SetDistancePerPulse(kPivotDistancePerPulse);
}

void PivotSub::SetPivotMotor(double speed)
{
    Util::Log("Pivot Speed", speed);
    Util::Log("Pivot Encoder", m_encoder.GetDistance());
    Util::Log("Pivot Get", m_encoder.Get());
    m_pivot.Set(speed);
}

double PivotSub::GetPivotAngle()
{
    Util::Log("Pivot Encoder", m_encoder.GetDistance());
    Util::Log("Pivot Get", m_encoder.Get());
    return m_encoder.GetDistance();
    //return 0;
}

void PivotSub::ResetPivotEncoder()
{
    m_encoder.Reset();
}