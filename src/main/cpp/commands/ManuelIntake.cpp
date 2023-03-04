// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ManuelIntake.h"

ManuelIntake::ManuelIntake(IntakeSub* pIntake, bool setOpen)
{
  m_pIntake = pIntake;
  m_setopen = setOpen;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pIntake);
}

// Called when the command is initially scheduled.
void ManuelIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManuelIntake::Execute()
{
  m_pIntake->SetIntake(m_setopen);
}

// Called once the command ends or is interrupted.
void ManuelIntake::End(bool interrupted) {}

// Returns true when the command should end.
bool ManuelIntake::IsFinished() {
  return false;
}
