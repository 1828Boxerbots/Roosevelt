// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <photonlib/PhotonCamera.h>
#include <photonlib/PhotonUtils.h>
#include <photonlib/PhotonPipelineResult.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/motorcontrol/Victor.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include <units/angle.h>
#include <units/length.h>

class VisionSub : public frc2::SubsystemBase 
{
 public:
 //Constructor:
  VisionSub();

  //Periodic:
  void Periodic() override;

  //Initialize:
  void Init();

  //Pipeline:
  enum Pipelines
  {
    AprilTags, 
    ReflectiveTapeTop, 
    ReflectiveTapeBottom, 
    PseudoReflectiveTape, 
    Cone, 
    Cube
  };

  void SetPipeline(Pipelines pipeline);
  
  //Data:
  void ShowData();
  int GetPipelineIndex();
  bool HasTarget();
  double Yaw();
  double Pitch();

  private:
  //Camera Initialization:
  photonlib::PhotonCamera m_camera{"MicrosoftLifeCamHDTest1"};

  //Pipelines:
  const int kPipelineReflectiveTapeBottom = 0;
  const int kPipelineIndexCone = 1;
  const int kPipelineIndexCube = 2;
  const int kPipelineAprilTags = 3;
  const int kPipelineReflectiveTapeTop = 4;
  const int kPipelinePseudoRT = 5;
};