// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionPipelineCMD.h"

VisionPipelineCMD::VisionPipelineCMD(VisionSub::Pipelines* pPipeline, bool setPipeline, VisionSub::Pipelines pipeline)
{
  m_pPipeline = pPipeline;
  m_setPipeline = setPipeline;
  m_pipeline = pipeline;
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void VisionPipelineCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void VisionPipelineCMD::Execute()
{
  if(m_setPipeline)
  {
    *m_pPipeline = m_pipeline;
  }
  else
  {
    if(*m_pPipeline == VisionSub::Pipelines::Cone)
    {
      *m_pPipeline = VisionSub::Pipelines::Cube;
    }
    else if(*m_pPipeline == VisionSub::Pipelines::Cube)
    {
      *m_pPipeline = VisionSub::Pipelines::Cone;
    }
    else if(*m_pPipeline == VisionSub::Pipelines::PseudoReflectiveTape)
    {
      *m_pPipeline = VisionSub::Pipelines::AprilTags;
    }
    else if(*m_pPipeline == VisionSub::Pipelines::AprilTags)
    {
      *m_pPipeline = VisionSub::Pipelines::PseudoReflectiveTape;
    }
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void VisionPipelineCMD::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionPipelineCMD::IsFinished() {
  return m_isFinished;
}
