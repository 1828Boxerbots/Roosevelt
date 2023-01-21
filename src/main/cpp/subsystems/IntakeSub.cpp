// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IntakeSub.h"

IntakeSub::IntakeSub() = default;

// This method will be called once per scheduler run
void IntakeSub::Periodic() {}

void IntakeSub::Init()
{
    m_shoot.SetInverted(true);
}

void IntakeSub::SetIntake(bool setOpen)
{
    Util::Log("SetIntake", setOpen);
    if(setOpen == true)
    {
        //m_intake.Set(frc::DoubleSolenoid::kForward);
        m_load.Set(1.0);
    }
    else if(setOpen == false)
    {
        //m_intake.Set(frc::DoubleSolenoid::kReverse);
        m_load.Set(0.0);
    }
    //m_intake.Set(frc::DoubleSolenoid::kOff);
}

frc2::CommandPtr IntakeSub::IntakeOpen()
{
    return RunOnce([this]
    {
        SetIntake(true);
    });
}

frc2::CommandPtr IntakeSub::IntakeClose()
{
    return RunOnce([this]
    {
        SetIntake(false);
    });
}

// ROCKY TEST
void IntakeSub::SetShoot(double speed)
{
    m_shoot.Set(speed);
}