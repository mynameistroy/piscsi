//---------------------------------------------------------------------------
//
// SCSI Target Emulator PiSCSI
// for Raspberry Pi
//
// Copyright (C) 2022 Uwe Seimet
//
//---------------------------------------------------------------------------

#include "mocks.h"
#include "shared/scsi.h"
#include "shared/piscsi_exceptions.h"
#include "devices/primary_device.h"
#include "devices/device_factory.h"
#include "devices/scsi_command_util.h"

using namespace scsi_defs;
using namespace scsi_command_util;

TEST(PrimaryDeviceTest, GetId)
{
	const int ID = 5;

	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, ID);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	EXPECT_EQ(-1, device->GetId()) << "Device ID cannot be known without assignment to a controller";

	controller->AddDevice(device);
	EXPECT_EQ(ID, device->GetId());
}

TEST(PrimaryDeviceTest, PhaseChange)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<MockAbstractController>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	EXPECT_CALL(*controller, Status);
	device->EnterStatusPhase();

	EXPECT_CALL(*controller, DataIn);
	device->EnterDataInPhase();

	EXPECT_CALL(*controller, DataOut);
	device->EnterDataOutPhase();
}

TEST(PrimaryDeviceTest, Reset)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	device->Dispatch(scsi_command::eCmdReserve6);
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for initiator ID 1";
	device->Reset();
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved anymore for initiator ID 1";
}

TEST(PrimaryDeviceTest, CheckReservation)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	EXPECT_TRUE(device->CheckReservation(0, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved for initiator ID 0";

	device->Dispatch(scsi_command::eCmdReserve6);
	EXPECT_TRUE(device->CheckReservation(0, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved for initiator ID 0";
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for initiator ID 1";
	EXPECT_FALSE(device->CheckReservation(-1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for unknown initiator";
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdInquiry, false))
		<< "Device must not be reserved for INQUIRY";
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdRequestSense, false))
		<< "Device must not be reserved for REQUEST SENSE";
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdRelease6, false))
		<< "Device must not be reserved for RELEASE (6)";

	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdPreventAllowMediumRemoval, false))
		<< "Device must not be reserved for PREVENT ALLOW MEDIUM REMOVAL with prevent bit not set";
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdPreventAllowMediumRemoval, true))
		<< "Device must be reserved for PREVENT ALLOW MEDIUM REMOVAL with prevent bit set";
}

TEST(PrimaryDeviceTest, ReserveReleaseUnit)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	device->Dispatch(scsi_command::eCmdReserve6);
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for initiator ID 1";

	device->Dispatch(scsi_command::eCmdRelease6);
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved anymore for initiator ID 1";

	ON_CALL(*controller, GetInitiatorId).WillByDefault(Return(-1));
	device->Dispatch(scsi_command::eCmdReserve6);
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for unknown initiator";

	device->Dispatch(scsi_command::eCmdRelease6);
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved anymore for unknown initiator";
}

TEST(PrimaryDeviceTest, DiscardReservation)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	device->Dispatch(scsi_command::eCmdReserve6);
	EXPECT_FALSE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must be reserved for initiator ID 1";
	device->DiscardReservation();
	EXPECT_TRUE(device->CheckReservation(1, scsi_command::eCmdTestUnitReady, false))
		<< "Device must not be reserved anymore for initiator ID 1";
}

TEST(PrimaryDeviceTest, TestUnitReady)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<MockAbstractController>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	device->SetReset(true);
	device->SetAttn(true);
	device->SetReady(false);
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdTestUnitReady); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::UNIT_ATTENTION),
			Property(&scsi_exception::get_asc, asc::POWER_ON_OR_RESET))));

	device->SetReset(false);
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdTestUnitReady); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::UNIT_ATTENTION),
			Property(&scsi_exception::get_asc, asc::NOT_READY_TO_READY_CHANGE))));

	device->SetReset(true);
	device->SetAttn(false);
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdTestUnitReady); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::UNIT_ATTENTION),
			Property(&scsi_exception::get_asc, asc::POWER_ON_OR_RESET))));

	device->SetReset(false);
	device->SetAttn(true);
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdTestUnitReady); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::UNIT_ATTENTION),
			Property(&scsi_exception::get_asc, asc::NOT_READY_TO_READY_CHANGE))));

	device->SetAttn(false);
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdTestUnitReady); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::NOT_READY),
			Property(&scsi_exception::get_asc, asc::MEDIUM_NOT_PRESENT))));

	device->SetReady(true);
	EXPECT_CALL(*controller, Status);
	device->Dispatch(scsi_command::eCmdTestUnitReady);
	EXPECT_EQ(status::GOOD, controller->GetStatus());
}

TEST(PrimaryDeviceTest, Inquiry)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	auto& cmd = controller->GetCmd();

	// ALLOCATION LENGTH
	cmd[4] = 255;

	ON_CALL(*device, InquiryInternal()).WillByDefault([&device]() {
		return device->HandleInquiry(device_type::PROCESSOR, scsi_level::SPC_3, false);
	});
	EXPECT_CALL(*device, InquiryInternal);
	EXPECT_CALL(*controller, DataIn);
	ON_CALL(*controller, GetEffectiveLun()).WillByDefault(Return(1));
	device->Dispatch(scsi_command::eCmdInquiry);
	EXPECT_EQ(0x7f, controller->GetBuffer()[0]) << "Invalid LUN was not reported";
	ON_CALL(*controller, GetEffectiveLun()).WillByDefault(Return(0));

	EXPECT_FALSE(controller->AddDevice(make_shared<MockPrimaryDevice>(0))) << "Duplicate LUN was not rejected";
	EXPECT_CALL(*device, InquiryInternal);
	EXPECT_CALL(*controller, DataIn);
	device->Dispatch(scsi_command::eCmdInquiry);
	EXPECT_EQ(device_type::PROCESSOR, (device_type)controller->GetBuffer()[0]);
	EXPECT_EQ(0x00, controller->GetBuffer()[1]) << "Device was not reported as non-removable";
	EXPECT_EQ(scsi_level::SPC_3, (scsi_level)controller->GetBuffer()[2]) << "Wrong SCSI level";
	EXPECT_EQ(scsi_level::SCSI_2, (scsi_level)controller->GetBuffer()[3]) << "Wrong response level";
	EXPECT_EQ(0x1f, controller->GetBuffer()[4]) << "Wrong additional data size";

	ON_CALL(*device, InquiryInternal()).WillByDefault([&device]() {
		return device->HandleInquiry(device_type::DIRECT_ACCESS, scsi_level::SCSI_1_CCS, true);
	});
	EXPECT_CALL(*device, InquiryInternal);
	EXPECT_CALL(*controller, DataIn);
	device->Dispatch(scsi_command::eCmdInquiry);
	EXPECT_EQ(device_type::DIRECT_ACCESS, (device_type)controller->GetBuffer()[0]);
	EXPECT_EQ(0x80, controller->GetBuffer()[1]) << "Device was not reported as removable";
	EXPECT_EQ(scsi_level::SCSI_1_CCS, (scsi_level)controller->GetBuffer()[2]) << "Wrong SCSI level";
	EXPECT_EQ(scsi_level::SCSI_1_CCS, (scsi_level)controller->GetBuffer()[3]) << "Wrong response level";
	EXPECT_EQ(0x1f, controller->GetBuffer()[4]) << "Wrong additional data size";

	cmd[1] = 0x01;
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdInquiry); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "EVPD bit is not supported";

	cmd[2] = 0x01;
	EXPECT_CALL(*controller, DataIn).Times(0);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdInquiry); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "PAGE CODE field is not supported";

	cmd[1] = 0x00;
	cmd[2] = 0x00;
	// ALLOCATION LENGTH
	cmd[4] = 1;
	EXPECT_CALL(*device, InquiryInternal);
	EXPECT_CALL(*controller, DataIn);
	device->Dispatch(scsi_command::eCmdInquiry);
	EXPECT_EQ(0x1f, controller->GetBuffer()[4]) << "Wrong additional data size";
	EXPECT_EQ(1, controller->GetLength()) << "Wrong ALLOCATION LENGTH handling";
}

TEST(PrimaryDeviceTest, RequestSense)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<NiceMock<MockAbstractController>>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	auto& cmd = controller->GetCmd();
	// ALLOCATION LENGTH
	cmd[4] = 255;

	device->SetReady(false);
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdRequestSense); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::NOT_READY),
			Property(&scsi_exception::get_asc, asc::MEDIUM_NOT_PRESENT))));

	device->SetReady(true);
	EXPECT_CALL(*controller, DataIn);
	device->Dispatch(scsi_command::eCmdRequestSense);
	EXPECT_EQ(status::GOOD, controller->GetStatus());
}

TEST(PrimaryDeviceTest, SendDiagnostic)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<MockAbstractController>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	auto& cmd = controller->GetCmd();

	EXPECT_CALL(*controller, Status);
	device->Dispatch(scsi_command::eCmdSendDiagnostic);
	EXPECT_EQ(status::GOOD, controller->GetStatus());

	cmd[1] = 0x10;
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdSendDiagnostic); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "SEND DIAGNOSTIC must fail because PF bit is not supported";
	cmd[1] = 0;

	cmd[3] = 1;
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdSendDiagnostic); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "SEND DIAGNOSTIC must fail because parameter list is not supported";
	cmd[3] = 0;
	cmd[4] = 1;
	EXPECT_THAT([&] { device->Dispatch(scsi_command::eCmdSendDiagnostic); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "SEND DIAGNOSTIC must fail because parameter list is not supported";
}

TEST(PrimaryDeviceTest, ReportLuns)
{
	const int LUN1 = 1;
	const int LUN2 = 4;

	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<MockAbstractController>(controller_manager, 0);
	auto device1 = make_shared<MockPrimaryDevice>(LUN1);
	auto device2 = make_shared<MockPrimaryDevice>(LUN2);
	const unordered_map<string, string> params;
	device1->Init(params);
	device2->Init(params);

	controller->AddDevice(device1);
	EXPECT_TRUE(controller->HasDeviceForLun(LUN1));
	controller->AddDevice(device2);
	EXPECT_TRUE(controller->HasDeviceForLun(LUN2));

	auto& cmd = controller->GetCmd();
	// ALLOCATION LENGTH
	cmd[9] = 255;

	EXPECT_CALL(*controller, DataIn);
	device1->Dispatch(scsi_command::eCmdReportLuns);
	const vector<uint8_t>& buffer = controller->GetBuffer();
	EXPECT_EQ(0, GetInt16(buffer, 0)) << "Wrong data length";
	EXPECT_EQ(16, GetInt16(buffer, 2)) << "Wrong data length";
	EXPECT_EQ(0, GetInt16(buffer, 8)) << "Wrong LUN1 number";
	EXPECT_EQ(0, GetInt16(buffer, 10)) << "Wrong LUN1 number";
	EXPECT_EQ(0, GetInt16(buffer, 12)) << "Wrong LUN1 number";
	EXPECT_EQ(LUN1, GetInt16(buffer, 14)) << "Wrong LUN1 number";
	EXPECT_EQ(0, GetInt16(buffer, 16)) << "Wrong LUN2 number";
	EXPECT_EQ(0, GetInt16(buffer, 18)) << "Wrong LUN2 number";
	EXPECT_EQ(0, GetInt16(buffer, 20)) << "Wrong LUN2 number";
	EXPECT_EQ(LUN2, GetInt16(buffer, 22)) << "Wrong LUN2 number";

	cmd[2] = 0x01;
	EXPECT_THAT([&] { device1->Dispatch(scsi_command::eCmdReportLuns); }, Throws<scsi_exception>(AllOf(
			Property(&scsi_exception::get_sense_key, sense_key::ILLEGAL_REQUEST),
			Property(&scsi_exception::get_asc, asc::INVALID_FIELD_IN_CDB))))
		<< "Only SELECT REPORT mode 0 is supported";
}

TEST(PrimaryDeviceTest, Dispatch)
{
	auto bus = make_shared<MockBus>();
	auto controller_manager = make_shared<ControllerManager>(*bus);
	auto controller = make_shared<MockAbstractController>(controller_manager, 0);
	auto device = make_shared<MockPrimaryDevice>(0);
	const unordered_map<string, string> params;
	device->Init(params);

	controller->AddDevice(device);

	EXPECT_THROW(device->Dispatch(static_cast<scsi_command>(0x1f)), scsi_exception) << "Unknown command";
}

TEST(PrimaryDeviceTest, WriteByteSequence)
{
	vector<uint8_t> data;
	MockPrimaryDevice device(0);

	EXPECT_FALSE(device.WriteByteSequence(data, 0)) << "Primary device does not support writing byte sequences";
}

TEST(PrimaryDeviceTest, GetSetSendDelay)
{
	MockPrimaryDevice device(0);

	EXPECT_EQ(-1, device.GetSendDelay()) << "Wrong delay default value";
	device.SetSendDelay(1234);
	EXPECT_EQ(1234, device.GetSendDelay());
}

TEST(PrimaryDeviceTest, Init)
{
	unordered_map<string, string> params;
	MockPrimaryDevice device(0);

	EXPECT_TRUE(device.Init(params)) << "Initialization of primary device must not fail";
}

TEST(PrimaryDeviceTest, FlushCache)
{
	MockPrimaryDevice device(0);

	// Method must be present
	device.FlushCache();
}
