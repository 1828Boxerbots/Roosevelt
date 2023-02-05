// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

// OPERATOR CONSTANTS
constexpr int kDriverControllerPort = 0;
constexpr int kOperatorControllerPort = 1;

constexpr int kDriveScale = 1.0;

constexpr int kTopDPDT = 9;
constexpr int kBottomDPDT = 10;

// DRIVE CONSTANTS
constexpr int kLeftDrive1 = 1;
constexpr int kLeftDrive2 = 3;
constexpr int kRightDrive1 = 2;
constexpr int kRightDrive2 = 4;

constexpr int kLeftEncoderA = 0;
constexpr int kLeftEncoderB = 1;
constexpr int kRightEncoderA = 2;
constexpr int kRightEncoderB = 3;

    // Equation/Method to get number:
constexpr double kDriveDistancePerPulse = 360;

// INTAKE CONSTANTS
constexpr int kForwardChannel = 0;
constexpr int kBackwardChannel = 1;

constexpr double kIntakeFinishedTime = 0.5;

// PIVOT CONSTANTS
constexpr int kPivotMotor = 13;

constexpr int kPivotEncoderA = 4;
constexpr int kPivotEncoderB = 5;

    // Equation/Method to get number:
constexpr double kPivotDistancePerPulse = 360;

constexpr double kPivotP = 0.01;
constexpr double kPivotI = 0.0;
constexpr double kPivotD = 0.0;

// ELEVATOR CONSTANTS
constexpr int kElevatorMotor = 12;

constexpr int kElevatorEncoderA = 6;
constexpr int kElevatorEncoderB = 7;

    // Equation/Method to get number:
constexpr double kElevatorDistancePerPulse = 360;

constexpr double kElevatorP = 0.01;
constexpr double kElevatorI = 0.0;
constexpr double kElevatorD = 0.0;

// TURRET CONSTANTS
constexpr int kTurretMotor = 14;

constexpr int kTurretEncoderA = 8;
constexpr int kTurretEncoderB = 9;

    // Equation/Method to get number:
constexpr double kTurretDistancePerPulse = 360;