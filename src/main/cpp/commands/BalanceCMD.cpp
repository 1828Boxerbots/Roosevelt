// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/BalanceCMD.h"

BalanceCMD::BalanceCMD(DriveSub* pDrive, bool onControl, double pidTolerance, double waitTime)
{
  m_pDrive = pDrive;
  m_pidTolerance = pidTolerance;
  m_waitTime = waitTime;
  m_onControl = onControl;

  m_pid.SetSetpoint(0.0);

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void BalanceCMD::Initialize()
{
  m_pid.Reset();
  m_pid.SetTolerance(m_pidTolerance);
  m_timer.Reset();
  m_timer.Stop();
}

// Called repeatedly when this Command is scheduled to run
void BalanceCMD::Execute()
{
  m_pDrive->MoveRC(0.0, m_pid.Calculate(m_pDrive->GetYAngle()));
  if(!m_onControl)
  {
    if(m_pid.AtSetpoint())
    {
      m_timer.Start();
    }
    else
    {
      m_timer.Reset();
      m_timer.Stop();
    }
  }
}

// Called once the command ends or is interrupted.
void BalanceCMD::End(bool interrupted)
{
  m_pDrive->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool BalanceCMD::IsFinished()
{
  if((double)m_timer.Get() > m_waitTime)
  {
    return true;
  }
  return false;
}
