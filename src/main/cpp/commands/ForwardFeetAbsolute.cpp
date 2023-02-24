// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ForwardFeetAbsolute.h"

ForwardFeetAbsolute::ForwardFeetAbsolute(DriveSub *pDrive, double distance, double tolerance)
{
  m_pDrive = pDrive;
  m_distance = distance;

  m_forwardPID.SetSetpoint(distance);

  m_forwardPID.SetTolerance(tolerance);
  m_allignPID.SetTolerance(1);

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void ForwardFeetAbsolute::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();
  m_forwardPID.Reset();
  m_allignPID.Reset();
  m_isFinished = false;
  m_allignPID.SetSetpoint(m_pDrive->GetXAngle());
}

// Called repeatedly when this Command is scheduled to run
void ForwardFeetAbsolute::Execute()
{
  Util::Log("IN FORWARD", true);

  Util::Log("AtSetPoint FFA", m_forwardPID.AtSetpoint());

  //m_allignPID.SetSetpoint(m_pDrive->GetLeftDist());
  Util::Log("Difference between encoder", m_pDrive->GetLeftDist()-m_pDrive->GetRightDist());

  m_pDrive->MoveRC(m_allignPID.Calculate(m_pDrive->GetXAngle()), m_forwardPID.Calculate(m_pDrive->GetRightDist()));
  if(m_forwardPID.AtSetpoint() and m_allignPID.AtSetpoint())
  {
    m_timer.Start();
  }
  else
  {
    m_timer.Reset();
    m_timer.Stop();
  }

  Util::Log("FFA GetTimer", (double)m_timer.Get());
}

// Called once the command ends or is interrupted.
void ForwardFeetAbsolute::End(bool interrupted)
{
  m_pDrive->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool ForwardFeetAbsolute::IsFinished() 
{
  if((double)m_timer.Get() > 0.5)
  {
    return true;
  }
  return false;
}
