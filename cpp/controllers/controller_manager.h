//---------------------------------------------------------------------------
//
// SCSI Target Emulator PiSCSI
// for Raspberry Pi
//
// Copyright (C) 2022 Uwe Seimet
//
// Keeps track of and manages the controllers
//
//---------------------------------------------------------------------------

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "hal/bus.h"

using namespace std;

class AbstractController;
class PrimaryDevice;

class ControllerManager : public enable_shared_from_this<ControllerManager>
{
	BUS& bus;

	unordered_map<int, shared_ptr<AbstractController>> controllers;

public:

	explicit ControllerManager(BUS& bus) : bus(bus) {}
	~ControllerManager() = default;

	// Maximum number of controller devices
	static const int DEVICE_MAX = 8;

	inline BUS& GetBus() const { return bus; }
	bool AttachToScsiController(int, shared_ptr<PrimaryDevice>);
	bool DeleteController(shared_ptr<AbstractController>);
	shared_ptr<AbstractController> IdentifyController(int) const;
	shared_ptr<AbstractController> FindController(int) const;
	unordered_set<shared_ptr<PrimaryDevice>> GetAllDevices() const;
	void DeleteAllControllers();
	shared_ptr<PrimaryDevice> GetDeviceByIdAndLun(int, int) const;
};
