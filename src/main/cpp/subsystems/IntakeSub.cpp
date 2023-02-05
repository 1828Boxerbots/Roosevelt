// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IntakeSub.h"

IntakeSub::IntakeSub() = default;

void IntakeSub::Init()
{
    SetIntake(false);
}

void IntakeSub::SetIntake(bool setOpen)
{
    Util::Log("SetIntake", setOpen);
    if(setOpen == true)
    {
        m_intake.Set(frc::DoubleSolenoid::kForward);
    }
    else if(setOpen == false)
    {
        m_intake.Set(frc::DoubleSolenoid::kReverse);
    }
    m_intake.Set(frc::DoubleSolenoid::kOff);
    m_isIntakeOpen = setOpen;
}

bool IntakeSub::IsIntakeOpen()
{
    return m_isIntakeOpen;
}

IntakeSub::ColorTargets IntakeSub::GetHeldObject()
{
    return IntakeSub::CUBE;
}