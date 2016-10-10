cmake_minimum_required(VERSION 2.8.12)
project(IPCPlugin)

find_package(osvr REQUIRED)

link_directories(${BOOST_ROOT}/lib32-msvc-12.0)

osvr_add_plugin(NAME je_nourish_ipc
    CPP
    SOURCES
	TimestampedValue.h
	MemoryMappedValue.h
	IPCTypes.h
    je_nourish_ipc.cpp)