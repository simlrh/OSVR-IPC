#pragma once

#include "TimestampedValue.h"
#include "MemoryMappedValue.h"

#include <osvr/Util/ClientReportTypesC.h>

namespace OSVR_IPC {

	typedef struct {
		OSVR_TimeValue timestamp;
		OSVR_NaviPositionState position;
		OSVR_NaviVelocityState velocity;
	} IPC_LocomotionValue;

	typedef struct {
		OSVR_TimeValue timestamp;
		OSVR_EyeTracker2DState eyeTracker2D;
		OSVR_EyeTracker3DState eyeTracker3D;
		OSVR_EyeTrackerBlinkState eyeTrackerBlink;
	} IPC_EyeTrackerValue;

	typedef MemoryMappedValue<TimestampedValue<OSVR_AnalogState>>			IPC_AnalogState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_ButtonState>>			IPC_ButtonState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_DirectionState>>		IPC_DirectionState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_EyeTracker2DState>>		IPC_EyeTracker2DState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_EyeTracker3DState>>		IPC_EyeTracker3DState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_EyeTrackerBlinkState>>	IPC_EyeTrackerBlinkState;
	typedef MemoryMappedValue<IPC_EyeTrackerValue>							IPC_EyeTrackerState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_Location2DState>>		IPC_Location2DState;
	typedef MemoryMappedValue<IPC_LocomotionValue>							IPC_LocmotionState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_NaviPositionState>>		IPC_NaviPositionState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_NaviVelocityState>>		IPC_NaviVelocityState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_PoseState>>				IPC_PoseState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_PositionState>>			IPC_PositionState;
	typedef MemoryMappedValue<TimestampedValue<OSVR_OrientationState>>		IPC_OrientationState;

}