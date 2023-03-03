// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ElevatorSub.h"

ElevatorSub::ElevatorSub() = default;

void ElevatorSub::Init()
{
    ResetElevatorEncoder();
    m_elevator.SetInverted(false);

    m_encoder.SetDistancePerPulse(kElevatorDistancePerPulse);
}

void ElevatorSub::SetElevatorMotor(double speed)
{
    Util::Log("Extend Speed", speed);
    Util::Log("Extent Length", m_encoder.GetDistance());
    Util::Log("Extent Get", m_encoder.Get());
    m_elevator.Set(speed);
}

double ElevatorSub::GetElevatorLength()
{
    Util::Log("Extent Length", m_encoder.GetDistance());
    return m_encoder.GetDistance();
}

void ElevatorSub::ResetElevatorEncoder()
{
    m_encoder.Reset();
}
