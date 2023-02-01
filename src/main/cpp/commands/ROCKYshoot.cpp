// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ROCKYshoot.h"

ROCKYshoot::ROCKYshoot(IntakeSub *pIntake, double speed)
{
  m_pIntake = pIntake;
  m_speed = speed;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pIntake);
}

// Called when the command is initially scheduled.
void ROCKYshoot::Initialize() 
{
  m_time.Start();
  m_time.Reset();
}

// Called repeatedly when this Command is scheduled to run
void ROCKYshoot::Execute()
{
  //m_pIntake->SetShoot(m_speed);
}

// Called once the command ends or is interrupted.
void ROCKYshoot::End(bool interrupted)
{
  //m_pIntake->SetShoot(0.0);
}

// Returns true when the command should end.
bool ROCKYshoot::IsFinished() {
  if((double)m_time.Get() > 1)
  {
    return true;
  }
  return false;
}
