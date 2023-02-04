// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ElevatorSub.h"

ElevatorSub::ElevatorSub() = default;

void ElevatorSub::Init()
{
    ResetElevatorEncoder();
}

void ElevatorSub::SetElevatorMotor(double speed)
{
    m_elevator.Set(speed);
}

double ElevatorSub::GetElevatorLength()
{
    return 0.0;
}

void ElevatorSub::ResetElevatorEncoder()
{
    m_encoder.Reset();
}
