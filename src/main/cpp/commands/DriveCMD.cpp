// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveCMD.h"

DriveCMD::DriveCMD(DriveSub* pDrive, frc::XboxController *pXbox, double scale)
{
  m_pDrive = pDrive;
  m_pXbox = pXbox;
  m_scale = scale;

  m_style = m_pDrive->kDriveStyle;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void DriveCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveCMD::Execute()
{

  m_LeftX = m_pXbox->GetLeftX() * m_scale;
  m_LeftY = -m_pXbox->GetLeftY() * m_scale;
  m_RightX = m_pXbox->GetRightX() * m_scale;
  m_RightY = -m_pXbox->GetRightY() * m_scale;

  switch(m_style)
  {
    case DriveSub::RC_STYLE:
      m_pDrive->MoveRC(m_RightX, m_LeftY);
      break;
    case DriveSub::TANK_STYLE:
      m_pDrive->MoveTank(m_LeftY, m_RightY);
      break;
    case DriveSub::ARCADE_STYLE:
      m_pDrive->MoveRC(m_LeftX, m_LeftY);
      break;
    default:
      // Forgot to set kDriveStyle LOG IT
      m_pDrive->MoveTank(0.0, 0.0);
      break;
  }
}

// Called once the command ends or is interrupted.
void DriveCMD::End(bool interrupted)
{
  m_pDrive->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool DriveCMD::IsFinished() {
  return false;
}
