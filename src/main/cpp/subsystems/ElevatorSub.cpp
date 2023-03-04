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

void ElevatorSub::Periodic()
{
    Util::Log("Extent Length", m_encoder.GetDistance());
    Util::Log("Extent Get", m_encoder.Get());
    Util::Log("Extent GetRaw", m_encoder.GetRaw());

    double shaftDiamater = ((0.39/-49.0)*m_encoder.GetDistance()) + 1.15;
    m_encoder.SetDistancePerPulse(1.0/(1024.0/ (shaftDiamater*M_PI)));
    Util::Log("Shaft Diameter", shaftDiamater);
    Util::Log("Elevate DPP", 1.0/(1024.0/ (shaftDiamater*M_PI)));
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
    Util::Log("Extent Get", m_encoder.Get());
    return m_encoder.GetDistance();
    //return 0.0;
}

double ElevatorSub::GetElevatorEncoder()
{
    Util::Log("Extent Get", m_encoder.Get());
    return m_encoder.Get();
}

void ElevatorSub::ResetElevatorEncoder()
{
    m_encoder.Reset();
}
