// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

// OPERATOR CONSTANTS
constexpr int kDriverControllerPort = 0;
constexpr int kOperatorControllerPort = 1;

constexpr double kDriveScale = .25;
constexpr double kSlowDriveScale = 0.10;

constexpr double kPivotScale = 0.25;
constexpr double kElevatorScale = 0.25;
constexpr double kTurretScale = 0.25;

constexpr int kTopDPDT = 10;
constexpr int kBottomDPDT = 11;

//------------Arm PID PivotAngle and ElevatorLength Values
constexpr double kPivotDegUp = 0.0;
constexpr double kElevatorInUp = 0.0;
constexpr double kPivotDegHigh = 55.1;
constexpr double kElevatorInHigh = 30.8;
constexpr double kPivotDegMid = 55.7;
constexpr double kElevatorInMid = 10.0;
constexpr double kPivotDegSubstation = 29.3;
constexpr double kElevatorInSubstation = 0.0; 
constexpr double kPivotDegGround = 90.0;

// AUTO CONSTANTS
constexpr double kForwardDistFt = 13.6;
constexpr double kBalanceDistFt = 6.6;
constexpr double kGridDistFt = 0.0;
constexpr double kForwardTolerance = 0.5;
constexpr double kTurretBack = 180.0;
constexpr double kTurretFront = 0.0;
constexpr double kTurretTowardsObj = 28.6; //arctan(24in (vertical dist from CONE) / 44in (horizontal dist from CONE))
constexpr double kArmHoldTime = 0.5;
constexpr double kArmTolerance = 1.0;
constexpr double kPivotHoldTime = 0.5;
constexpr double kPivotTolerance = 1.0;
constexpr double kElevatorHoldTime = 0.5;
constexpr double kElevatorTolerance = 1.0;
constexpr double kElevatorDistToConeInch = 5.0; // 44in (dist from CONE) - 43in (default elevator length) + 4in (half ot grabber length) = 5.0
constexpr double kElevatorLengthToMidObj = 7.1; // sqrt( pow2(24in (vertical dist from CONE)) + pow2(44in (horizontal dist from CONE)))


// DRIVE CONSTANTS
constexpr int kLeftDrive1 = 1;
constexpr int kLeftDrive2 = 3;
constexpr int kRightDrive1 = 0;
constexpr int kRightDrive2 = 2;

constexpr int kLeftEncoderA = 0;
constexpr int kLeftEncoderB = 1;
constexpr int kRightEncoderA = 2;
constexpr int kRightEncoderB = 3;

//------------ CPR (360.0 on E4T-360 Encoder) / Circumfrence (6.0 inches)
constexpr double kDriveDistancePerPulse = 360.0 / (6.0*M_PI);

// INTAKE CONSTANTS
constexpr int kForwardChannel = 4;
constexpr int kBackwardChannel = 5;

constexpr double kIntakeFinishedTime = 0.5;

// PIVOT CONSTANTS
constexpr int kPivotMotor = 14;

constexpr int kPivotEncoderA = 4;
constexpr int kPivotEncoderB = 5;

//------------Equation/Method to get number: CPR(2048.0 on REV Bore Encoder) / 360.0 Degrees (Encoder revolution is 1:1 with Pivot angle)
constexpr double kPivotDistancePerPulse = 530.0 / 90.0;

constexpr double kBatteryPivotAngleLimit = 60.0;

constexpr double kPivotP = 0.01;
constexpr double kPivotI = 0.0;
constexpr double kPivotD = 0.0;
    
// ELEVATOR CONSTANTS
constexpr int kElevatorMotor = 13;

constexpr int kElevatorEncoderA = 8;
constexpr int kElevatorEncoderB = 9;

//------------Equation/Method to get number: CPR (1024.0 on VersaPlanetary Integrated Encoder) / Circumfrence of shaft (0.5 inches)
constexpr double kElevatorDistancePerPulse = 1024.0/ (0.5*M_PI);

//------------Max height is 78 inches, robot base to turret is ~9in, 43 inch long arm by default (when GetLength = 0)
  // 78 - 9 - 43 = 26 - 5 (buffer) = 21.0
constexpr double kHeightLimit = 21.0; // Inches

//------------Max distance is 48 inches outside frame perminitar, frame to middle of robot is 14.125 inches, 43 inch long arm by default (when GetLength = 0)
    // (48+14.125)-43 = 19.125 - 5 (buffer) = 14.125
constexpr double kDistanceLimit = 14.125; // Inches

constexpr double kElevatorP = 0.01;
constexpr double kElevatorI = 0.0;
constexpr double kElevatorD = 0.0;

// TURRET CONSTANTS
constexpr int kTurretMotor = 12;

constexpr int kTurretEncoderA = 6;
constexpr int kTurretEncoderB = 7;

//------------Equation/Method to get number: CPR(2048.0 on REV Bore Encoder) / 360.0 Degrees (Encoder revolution is 1:1 with Turret angle)
constexpr double kTurretDistancePerPulse = 2048.0 / 360.0;

constexpr double kTurretAngleLimit = 225.0;
constexpr double kTurretRotateAround = 360.0;
constexpr double kLowerBackPositionAngle = 170.0;
constexpr double kHigherBackPositionAngle = 190.0;
constexpr double kBatteryTurretAngleLimit = 125.0;

constexpr double kTurretP = 0.1;
constexpr double kTurretI = 0.0;
constexpr double kTurretD = 0.0;

//VISION CONSTANTS:
constexpr double kVisionDeadzone = 3.0;
constexpr double kVisionP = 0.01;
constexpr double kVisionI = 0.0;
constexpr double kVisionD = 0.0;
constexpr double kVisionAlignSpeed = 1.0;