#pragma once

#include <string>
#include <memory>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace OSVR_IPC {

	template<typename T>
	class MemoryMappedValue
	{
	public:
		MemoryMappedValue(std::string path) {
			m_shared_memory(create_or_open, path, read_only);
			m_mapped_region(m_shared_memory, read_only, 0, sizeof(T));
			m_shared_object = (T*)m_mapped_region.get_address();
		}
		~MemoryMappedValue() {
		};
		operator T*() {
			return m_shared_object;
		}
		operator T() {
			return *m_shared_object;
		};
	protected:
		T* m_shared_object;
	private:
		boost::interprocess::shared_memory_object m_shared_memory;
		boost::interprocess::mapped_region m_mapped_region;
	};

}