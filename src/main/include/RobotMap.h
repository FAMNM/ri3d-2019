/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef RI3DROBOT_MAP_H__
#define RI3DROBOT_MAP_H__

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

namespace RobotMap {
    //GAMEPAD PORTS
    const constexpr int kDriver = 0;
    const constexpr int kOperator = 1;

    //PWM MAPPINGS
    const constexpr int kLeftDrive = 0;
    const constexpr int kRightDrive = 1;

    //SENSOR MAPPINGS
    
    //SUBSYSTEM IDS
    const constexpr int kDrivetrainId = 0;
}

#endif //RI3DROBOT_MAP_H__
