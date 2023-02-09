// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSub.h"

DriveSub::DriveSub() = default;


void DriveSub::Init()
{
    m_rightOne.SetInverted(true);
    m_rightTwo.SetInverted(true);

    ResetEncoders();

    m_leftEncoder.SetDistancePerPulse(kDriveDistancePerPulse);
    m_rightEncoder.SetDistancePerPulse(kDriveDistancePerPulse);
}

// MOTOR FUNCTIONS

void DriveSub::MoveTank(double left, double right)
{
    Util::Log("LeftPower", left);
    Util::Log("RightPower", right);
    Util::Log("Left-Right pwr", left-right);

    m_leftOne.Set(left);
    m_leftTwo.Set(left);
    m_rightOne.Set(right);
    m_rightTwo.Set(right);
}

void DriveSub::MoveRC(double horizontal, double vertical)
{
    MoveTank(vertical+horizontal, vertical-horizontal);
}

// ENCODER FUNCTIONS

double DriveSub::GetLeftDist()
{
    Util::Log("DriveLeft Dist", m_leftEncoder.GetDistance());
    return m_leftEncoder.GetDistance();
}

double DriveSub::GetRightDist()
{
    Util::Log("DriveRight Dist", m_rightEncoder.GetDistance());
    return m_rightEncoder.GetDistance();
}

double DriveSub::GetLeftVelocity()
{
    Util::Log("DriveLeft Rate", m_leftEncoder.GetRate());
    return m_leftEncoder.GetRate();
}

double DriveSub::GetRightVelocity()
{
    Util::Log("DriveRight Rate", m_rightEncoder.GetRate());
    return m_rightEncoder.GetRate();
}

void DriveSub::ResetEncoders()
{
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
}
