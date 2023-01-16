// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ForwardFeetAbsolute.h"

ForwardFeetAbsolute::ForwardFeetAbsolute(DriveSub *pDrive, double distance)
{
  m_pDrive = pDrive;
  m_distance = distance;

  m_forwardPID.SetSetpoint(distance);
  m_allignPID.SetSetpoint(m_pDrive->GetXAngle());

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void ForwardFeetAbsolute::Initialize()
{
  m_forwardPID.Reset();
  m_allignPID.Reset();
}

// Called repeatedly when this Command is scheduled to run
void ForwardFeetAbsolute::Execute()
{
  m_pDrive->MoveRC(m_allignPID.Calculate(m_pDrive->GetXAngle()), m_forwardPID.Calculate(m_pDrive->GetLeftDist()));
}

// Called once the command ends or is interrupted.
void ForwardFeetAbsolute::End(bool interrupted)
{
  m_pDrive->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool ForwardFeetAbsolute::IsFinished() {
  return false;
}
