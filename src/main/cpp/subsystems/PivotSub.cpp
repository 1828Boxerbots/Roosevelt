// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/PivotSub.h"

PivotSub::PivotSub() = default;

void PivotSub::Init()
{
    ResetPivotEncoder();
}

void PivotSub::SetPivotMotor(double speed)
{
    m_pivot.Set(speed);
}

double PivotSub::GetPivotMotor()
{
    return 0.0;
}

void PivotSub::ResetPivotEncoder()
{
    m_encoder.Reset();
}