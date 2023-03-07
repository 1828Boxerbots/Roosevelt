// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ForwardTimerCMD.h"

ForwardTimerCMD::ForwardTimerCMD(DriveSub* pDrive, double speed, double time)
{
  m_pDrive = pDrive;
  m_speed = speed;
  m_time = time;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void ForwardTimerCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void ForwardTimerCMD::Execute()
{
  m_pDrive->MoveTank(m_speed, m_speed);
  m_timer.Start();
}

// Called once the command ends or is interrupted.
void ForwardTimerCMD::End(bool interrupted)
{
  m_pDrive->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool ForwardTimerCMD::IsFinished()
{
  bool value = false;
  if((double)m_timer.Get() >= m_time)
  {
    value = true;
  }
  return value;
}
