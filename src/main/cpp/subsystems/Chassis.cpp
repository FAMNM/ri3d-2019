/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Chassis.h"

#include "OI.h"
#include "Robot.h"
#include "commands/Drive.h"

Chassis::Chassis() : 
  frc::Subsystem("Chassis"),
  frontLeft{1},
  frontRight{2},
  backLeft{3},
  backRight{4},
  left{frontLeft, backLeft},
  right{frontRight, backRight},
  dDrive{left, right}
 {}

void Chassis::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new Drive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::move() {
  dDrive.TankDrive(-Robot::m_oi.gamepad1.GetRawAxis(1), -Robot::m_oi.gamepad1.GetRawAxis(5));
}

void Chassis::stop() {
  dDrive.TankDrive(0, 0);
}
