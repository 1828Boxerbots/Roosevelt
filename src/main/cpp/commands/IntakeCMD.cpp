// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeCMD.h"

IntakeCMD::IntakeCMD(IntakeSub* pIntake, bool useIsFinished, double holdtime)
{
  m_pIntake = pIntake;
  m_useIsFinished = useIsFinished;
  m_holdTime = holdtime;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pIntake);
}

// Called when the command is initially scheduled.
void IntakeCMD::Initialize() 
{
  m_timer.Reset();
  m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void IntakeCMD::Execute()
{
  m_pIntake->SetIntake(!m_pIntake->IsIntakeOpen());
}

// Called once the command ends or is interrupted.
void IntakeCMD::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeCMD::IsFinished()
{  
  bool value = false;
  if((double)m_timer.Get() >= m_holdTime and m_useIsFinished)
  {
    value = true;
  }
  return value;
}
