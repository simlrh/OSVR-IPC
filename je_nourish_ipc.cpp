// Internal Includes
#include <osvr/PluginKit/PluginKit.h>
#include <osvr/PluginKit/AnalogInterfaceC.h>

// Library/third-party includes
#include <boost/asio.hpp>

// Standard includes
#include <iostream>
#include <map>
#include <memory>

#include "IPCTypes.h"

// Anonymous namespace to avoid symbol collision
namespace OSVR_IPC {


class IPCDevice {
  public:
    IPCDevice(OSVR_PluginRegContext ctx, std::string name, std::string descriptor) 
		: m_name(name), m_descriptor(descriptor) {
        /// Create the initialization options
        OSVR_DeviceInitOptions opts = osvrDeviceCreateInitOptions(ctx);

        /// Indicate that we'll want 1 analog channel.
        osvrDeviceAnalogConfigure(opts, &m_analog, 1);

        /// Create the device token with the options
        m_dev.initAsync(ctx, m_name, opts);

        /// Send JSON descriptor
        m_dev.sendJsonDescriptor(m_descriptor);

        /// Register update callback
        m_dev.registerUpdateCallback(this);
    }

    OSVR_ReturnCode update() {
        /// This dummy loop just wastes time, to pretend to be your plugin
        /// blocking to wait for the arrival of data. It should be completely
        /// removed from your plugin.
        volatile int j; // volatile to keep it from being optimized out.
        for (int i = 0; i < 10000; ++i) {
            j = i;
        }
        /// End time-waster loop.

        /// Report the value of channel 0
        osvrDeviceAnalogSetValue(m_dev, m_analog, 0, 0);
        return OSVR_RETURN_SUCCESS;
    }

	bool registered;

  private:
    osvr::pluginkit::DeviceToken m_dev;
    OSVR_AnalogDeviceInterface m_analog;
	std::string m_path;
	std::string m_name;
	std::string m_descriptor;

	std::vector<IPC_AnalogState> m_analogValues;
	std::vector<IPC_ButtonState> m_buttonValues;
	std::vector<IPC_DirectionState> m_directionValues;
	std::vector<IPC_EyeTrackerState> m_eyeTrackerValues;
	std::vector<IPC_Location2DState> m_location2DValues;
	std::vector<IPC_LocmotionState> m_locomotionValues;
	std::vector<IPC_PoseState> m_poseValues;
};


class HardwareDetection {
  public:
    HardwareDetection() : m_found(false) {}
    OSVR_ReturnCode operator()(OSVR_PluginRegContext ctx) {

		if (!m_found) {
			m_found = true;
			/// Create our device object
			osvr::pluginkit::registerObjectForDeletion(ctx, new IPCDevice(ctx, "TestDevice", "{}"));
		}
		
        return OSVR_RETURN_SUCCESS;
    }

  private:
	std::map<std::string, std::unique_ptr<IPCDevice>> m_deviceMap;
	bool m_found;
};
} // namespace

OSVR_PLUGIN(com_osvr_example_selfcontained) {
    osvr::pluginkit::PluginContext context(ctx);

    /// Register a detection callback function object.
    context.registerHardwareDetectCallback(new OSVR_IPC::HardwareDetection());

    return OSVR_RETURN_SUCCESS;
}
