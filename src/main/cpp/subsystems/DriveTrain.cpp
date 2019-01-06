/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"

#include "RobotMap.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
  speedController1.reset(new frc::Spark(0));
  speedController2.reset(new frc::Spark(1));
  robotDrive21.reset(new frc::RobotDrive(speedController1, speedController2));
}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new RobotDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::Periodic() {
  //Runs every loop
}