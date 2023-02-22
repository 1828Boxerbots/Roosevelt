// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>
#include "Constants.h"
#include "subsystems/TurretSub.h"
#include "subsystems/VisionSub.h"


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionAlignCMD : public frc2::CommandHelper<frc2::CommandBase, VisionAlignCMD> 
{
 public:
  VisionAlignCMD(VisionSub *pVisionSub, TurretSub *pTurretSub, VisionSub::Pipelines pipeline, double speed = 0.1);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  //Subsystems:
  VisionSub* m_pVisionSub = nullptr;
  TurretSub* m_pTurretSub = nullptr;

  //Pipeline:
  VisionSub::Pipelines m_pipeline;

  //PIDs:
  frc::PIDController  m_pidController{kVisionP, kVisionI, kVisionD};

  //Command Variables:
  double m_speed;
  double m_stop = 0.0;
  double kDeadzone = 5.0;
  bool m_isFinished = false;
};
