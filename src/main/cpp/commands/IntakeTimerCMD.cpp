// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeTimerCMD.h"

IntakeTimerCMD::IntakeTimerCMD(IntakeSub *pIntake, bool set, double waitTime)
{
  m_pIntake = pIntake;
  m_setOpen = set;
  m_waitTime = waitTime;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pIntake);
}

// Called when the command is initially scheduled.
void IntakeTimerCMD::Initialize()
{
  m_timer.Start();
  m_timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void IntakeTimerCMD::Execute()
{
  m_pIntake->SetIntake(m_setOpen);
}

// Called once the command ends or is interrupted.
void IntakeTimerCMD::End(bool interrupted) 
{
  m_pIntake->SetIntake(false);
}

// Returns true when the command should end.
bool IntakeTimerCMD::IsFinished() 
{
  if((double)m_timer.Get() > m_waitTime)
  {
    return true;
  }
  return false;
}
