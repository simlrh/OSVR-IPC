#pragma once

#include <osvr/Util/TimeValue.h>

namespace OSVR_IPC {

	template <typename T>
	struct TimestampedValue {
		OSVR_TimeValue timestamp;
		T value;
	};

}