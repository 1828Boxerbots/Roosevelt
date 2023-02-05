// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ElevatorPIDCMD.h"

ElevatorPIDCMD::ElevatorPIDCMD(ElevatorSub* pElevator, double setLength, bool useIsFinished, double holdtime, double threshold)
{
  m_pElevator = pElevator;
  m_setLength = setLength;
  m_holdTime = holdtime;
  m_threshold = threshold;

  m_pid.SetSetpoint(m_setLength);
  m_pid.SetTolerance(m_threshold);

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pElevator);
}

// Called when the command is initially scheduled.
void ElevatorPIDCMD::Initialize()
{
  m_timer.Stop();
  m_timer.Reset();
  m_pid.Reset();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorPIDCMD::Execute()
{
  m_pElevator->SetElevatorMotor(m_pid.Calculate(m_pElevator->GetElevatorLength()));

  if(m_pid.AtSetpoint())
  {
    m_timer.Start();
  }
  else
  {
    m_timer.Stop();
    m_timer.Reset();
  }
}

// Called once the command ends or is interrupted.
void ElevatorPIDCMD::End(bool interrupted)
{
  m_pElevator->SetElevatorMotor(0.0);
}

// Returns true when the command should end.
bool ElevatorPIDCMD::IsFinished() 
{
  bool value = false;
  if((double)m_timer.Get() >= m_holdTime and m_useIsFinished)
  {
    value = true;
  }

  return value;
}
