// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/VisionSub.h"
#include "Constants.h"
#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionPipelineCMD
    : public frc2::CommandHelper<frc2::CommandBase, VisionPipelineCMD> {
 public:
  VisionPipelineCMD(VisionSub::Pipelines* pPipeline, bool setPipeline = false, VisionSub::Pipelines pipeline = VisionSub::Pipelines::Cube);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  VisionSub::Pipelines* m_pPipeline;
  bool m_setPipeline;
  VisionSub::Pipelines m_pipeline;

  bool m_isFinished = false;
};
