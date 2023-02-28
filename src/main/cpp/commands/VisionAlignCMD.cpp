// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionAlignCMD.h"

VisionAlignCMD::VisionAlignCMD(VisionSub *pVisionSub, TurretSub *pTurretSub, double rotationSpeed) 
{
  m_pVisionSub = pVisionSub;
  m_pTurretSub = pTurretSub;
  m_rotationSpeed = rotationSpeed;

  // Use addRequirements() here to declare subsystem dependencies.
    //AddRequirements(m_pVisionSub);
  AddRequirements(m_pTurretSub);

}

// Called when the command is initially scheduled.
void VisionAlignCMD::Initialize() 
{
  //Reset PIDs:
  m_pidController.Reset();

  //Set Point:
  m_pidController.SetSetpoint(m_pVisionSub->Yaw());

  //Set Motor:
  m_pTurretSub->SetTurretMotor(0.0);
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignCMD::Execute() 
{
  //If Target is Spotted, Align to Target:
  if(m_pVisionSub->HasTarget() == true)
  {
    Align();
    //PIDAlign(); <-Keep Commented (Not operational).
  }   
}

// Called once the command ends or is interrupted.
void VisionAlignCMD::End(bool interrupted) 
{
  //Stop Robot:
  m_pTurretSub->SetTurretMotor(0.0);
}

// Returns true when the command should end.
bool VisionAlignCMD::IsFinished() 
{
  return false;
}


void VisionAlignCMD::PIDAlign()
{
  //Set Yaw:
  m_yaw = m_pVisionSub->Yaw();

  //Calculate Rotation Speed:
  m_rotationSpeed = -m_pidController.Calculate(m_yaw, 0.0);

  //Motors Set to Rotation Speed:
  m_pTurretSub->SetTurretMotor(m_rotationSpeed); //Needs Testing.
}

void VisionAlignCMD::Align()
{
  if(m_pVisionSub->Yaw() < kVisionDeadzone and m_pVisionSub->Yaw() > -kVisionDeadzone)
  {
  m_pTurretSub->SetTurretMotor(0.0);
  }
  else if (m_pVisionSub->Yaw() < 0)
  {
  m_pTurretSub->SetTurretMotor(m_rotationSpeed);
  }
  else if (m_pVisionSub->Yaw() > 0)
  {
  m_pTurretSub->SetTurretMotor(-m_rotationSpeed);  
  }
}