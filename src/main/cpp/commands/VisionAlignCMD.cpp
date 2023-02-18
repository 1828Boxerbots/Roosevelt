// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionAlignCMD.h"

VisionAlignCMD::VisionAlignCMD(VisionSub *pVisionSub, DriveSub *pDriveSub, VisionSub::Pipelines pipeline, double speed) 
{
  m_pVisionSub = pVisionSub;
  m_pDriveSub = pDriveSub;
  m_pipeline = pipeline;
  m_speed = speed;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDriveSub);
  //AddRequirements(m_pVisionSub);
}

// Called when the command is initially scheduled.
void VisionAlignCMD::Initialize() 
{
  m_pVisionSub ->SetPipeline(m_pipeline);
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignCMD::Execute() 
{
  if(m_pVisionSub->GetHasTarget() == true)
  {
    //If Camera Faces Right Side of Target
    if(m_pVisionSub->GetYaw() < kDeadzone and m_pVisionSub->GetYaw() > -kDeadzone)
    {
      m_isFinished = true;
    }
    else if (m_pVisionSub->GetYaw() < 0.0)
    {
      m_pDriveSub->MoveTank(m_speed, -m_speed);
    }
    else if (m_pVisionSub->GetYaw() > 0.0)
    {
      m_pDriveSub->MoveTank(-m_speed, m_speed);
    }
  }   
}

// Called once the command ends or is interrupted.
void VisionAlignCMD::End(bool interrupted) 
{
  m_pDriveSub->MoveTank(0.0, 0.0);
}

// Returns true when the command should end.
bool VisionAlignCMD::IsFinished() {
  return m_isFinished;
}
