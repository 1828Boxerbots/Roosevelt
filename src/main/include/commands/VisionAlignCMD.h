// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include "subsystems/TurretSub.h"
#include "subsystems/VisionSub.h"
#include "Constants.h"


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
  VisionAlignCMD(VisionSub *pVisionSub, TurretSub *pTurretSub, double rotationSpeed = kVisionAlignSpeed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  void Align();  
  void PIDAlign(); //Note: Currently not operational.

  //Subsystems:
  VisionSub* m_pVisionSub = nullptr;
  TurretSub* m_pTurretSub = nullptr;

  //PIDs:
  frc::PIDController  m_pidController{kVisionP, kVisionI, kVisionD};

  //Command Variables:
  double m_speed = 0.2;
  double m_rotationSpeed = 0.0;
  double m_yaw = 0.0;
  int m_heartbeat = 0;
  };
