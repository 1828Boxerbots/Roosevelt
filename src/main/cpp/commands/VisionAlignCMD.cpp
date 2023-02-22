// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionAlignCMD.h"

VisionAlignCMD::VisionAlignCMD(VisionSub *pVisionSub, TurretSub *pTurretSub, VisionSub::Pipelines pipeline, double speed) 
{
  m_pVisionSub = pVisionSub;
  //m_pTurretSub = pTurretSub;
  m_pTurretSub = pTurretSub;
  m_pipeline = pipeline;
  m_speed = speed;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pTurretSub);
  //AddRequirements(m_pVisionSub);
}

// Called when the command is initially scheduled.
void VisionAlignCMD::Initialize() 
{
  //Set Pipeline:
  m_pVisionSub ->SetPipeline(m_pipeline);
  //Reset PIDs:
  m_pidController.Reset();
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignCMD::Execute() 
{
  //If Target is Spotted:
  if(m_pVisionSub->HasTarget() == true)
  {
    //If Camera Faces Center of Target:
    if(m_pVisionSub->Yaw() < kDeadzone and m_pVisionSub->Yaw() > -kDeadzone)
    {
      //End Execution:
      m_isFinished = true;
    }
    //If Camera Faces Right Side of Target:
    else if (m_pVisionSub->Yaw() < 0.0)
    {
      //Move Left:
      m_pTurretSub->SetTurretMotor(m_speed); //Needs Testing.
    }
    //If Camera Faces Left Side of Target:
    else if (m_pVisionSub->Yaw() > 0.0)
    {
      //Move Right:
      m_pTurretSub->SetTurretMotor(-m_speed); //Needs Testing.
    }
  }   
}

// Called once the command ends or is interrupted.
void VisionAlignCMD::End(bool interrupted) 
{
  //Stop Robot:
  m_pTurretSub->SetTurretMotor(m_stop);
}

// Returns true when the command should end.
bool VisionAlignCMD::IsFinished() {
  return m_isFinished;
}