#ifndef posreg_h
#define posreg_h
/**
 * Absolute position header.
 *
 * This is a Work In Progress version, future API may change.
 */

/* If not using patched nbc. */
#ifndef OUT_REGMODE_POS
#define OUT_REGMODE_POS 4
#define MaxSpeed 16
#define MaxAcceleration 17
#endif

/**
 * Enable absolute position regulation with PID factors.
 * Enable absolute position regulation on the specified output.  Motor is kept
 * regulated as long as this is enabled.
 * Specify proportional, integral, and derivative factors.
 *
 * \param output Desired output port. Can be a constant or a variable, see
 * \ref OutputPortConstants.
 * \param p Proportional factor used by the firmware's PID motor control
 * algorithm. See \ref PIDConstants.
 * \param i Integral factor used by the firmware's PID motor control
 * algorithm. See \ref PIDConstants.
 * \param d Derivative factor used by the firmware's PID motor control
 * algorithm. See \ref PIDConstants.
 */
inline void
PosRegEnablePID (byte output, byte p, byte i, byte d)
{
    SetOutput (output,
	       OutputMode, OUT_MODE_MOTORON + OUT_MODE_BRAKE + OUT_MODE_REGULATED,
	       RegMode, OUT_REGMODE_POS,
	       RunState, OUT_RUNSTATE_RUNNING,
	       Power, 0,
	       TurnRatio, 0,
	       RegPValue, p, RegIValue, i, RegDValue, d,
	       UpdateFlags, UF_UPDATE_MODE + UF_UPDATE_SPEED + UF_UPDATE_PID_VALUES + UF_UPDATE_RESET_COUNT);
    Wait (2);
}

//#define PosRegEnable(output) PosRegEnablePID (output, PID_3, PID_1, PID_1)

/**
 * Change the current value for set angle.
 * Make the absolute position regulation going toward the new provided angle.
 * Returns immediately, but keep regulating.
 *
 * \param output Desired output port. Can be a constant or a variable, see
 * \ref OutputPortConstants.
 * \param angle New set position, in degree. The 0 angle corresponds to the
 * position of the motor when absolute position regulation was first enabled.
 * Can be negative. Can be greater than 360 degree to make several turns.
 */
inline void
PosRegSetAngle (byte output, long angle)
{
    SetOutput (output,
	       TachoLimit, angle,
	       UpdateFlags, UF_UPDATE_TACHO_LIMIT);
}

/**
 * Add to the current value for set angle.
 * Add an offset to the current set position. Returns immediately, but keep
 * regulating.
 *
 * \param output Desired output port. Can be a constant or a variable, see
 * \ref OutputPortConstants.
 * \param angle_add Value to add to the current set position, in degree. Can
 * be negative. Can be greater than 360 degree to make several turns.
 */
inline void
PosRegAddAngle (byte output, long angle_add)
{
    long current_angle = GetOutput (output, TachoLimit);
    SetOutput (output,
	       TachoLimit, current_angle + angle_add,
	       UpdateFlags, UF_UPDATE_TACHO_LIMIT);
}

/**
 * Set maximum limits.
 * Set maximum speed and acceleration.
 *
 * \param output Desired output port. Can be a constant or a variable, see
 * \ref OutputPortConstants.
 * \param max_speed Maximum speed, or 0 to disable speed limiting.
 * \param max_acceleration Maximum acceleration, or 0 to disable acceleration
 * limiting. The max_speed parameter should not be 0 if this is not 0.
 */
inline void
PosRegSetMax (byte output, byte max_speed, byte max_acceleration)
{
    SetOutput (output,
	       MaxSpeed, max_speed,
	       MaxAcceleration, max_acceleration,
	       UpdateFlags, UF_UPDATE_PID_VALUES);
    Wait (2);
}

#endif /* posreg_h */
