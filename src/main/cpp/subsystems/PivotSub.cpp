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
    m_pivot.SetInverted(false);

    m_encoder.SetDistancePerPulse(kPivotDistancePerPulse);
}

void PivotSub::SetPivotMotor(double speed)
{
    m_pivot.Set(speed);
}

double PivotSub::GetPivotAngle()
{
    return m_encoder.Get();
}

void PivotSub::ResetPivotEncoder()
{
    m_encoder.Reset();
}