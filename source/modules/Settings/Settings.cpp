#include "Settings.h"
#include <cstring>
#include <iostream>

// #define FLASH_ENABLE_MEM_ADDR   (0)
// #define FRAMERATE_MEM_ADDR      (4)
// #define THRESHOLD_MEM_ADDR      (8)
// #define UNITID_MEM_ADDR         (12)
// #define IP_ADDR_MEM_ADDR        (16)
// #define SENSOR_START_MEM_ADDR   (20)
// #define SENSOR_END_MEM_ADDR     (84)


// virtual uint32_t Read32Bits(uint32_t address) = 0;
// virtual float ReadFloat(uint32_t address) = 0;

Settings::Settings(IFlashInterface& flash) :
	flash(flash)
{
	// load with default values
	// or from memory
	
	// if (Read32Bits(FLASH_ENABLE_MEM_ADDR))
	{
		password = 123456;
		flash_enable = false;
		sensor_framerate = 100;
		tracker_threshold = 2.0f;
		unit_id = 0xDEADBEEF;
		ip_address = 0;
		application_mode = 0;
		memset(calibration_offset, 0.0f, MAX_PIXEL_INDEX);
		cal_value = 0.0f;
	}
}

uint32_t Settings::Password() const
{
	return password;
}

void Settings::Password(const uint32_t pwd)
{
	password = pwd;
}

bool Settings::FlashEnable() const
{
	return flash_enable;
}

void Settings::FlashEnable(const bool enable)
{
	flash_enable = enable;
}

uint32_t Settings::SensorFrameRate() const
{
	return sensor_framerate;
}

void Settings::SensorFrameRate(const uint32_t framerate)
{
	sensor_framerate = framerate;

	if (flash_enable)
	{
		flash.Write32Bits(FRAMERATE_MEM_ADDR, framerate);
	}
}

float Settings::TrackerThreshold() const
{
	return tracker_threshold;
}

void Settings::TrackerThreshold(const float& threshold)
{
	tracker_threshold = threshold;

	// save to eeprom
	if (flash_enable)
	{
		flash.WriteFloat(THRESHOLD_MEM_ADDR, threshold);
	}
}

uint32_t Settings::UnitID() const
{
	return unit_id;
}

void Settings::UnitID(const uint32_t id)
{
	unit_id = id;

	// save to eeprom
	if (flash_enable)
	{
		flash.Write32Bits(UNITID_MEM_ADDR, id);
	}
}

uint32_t Settings::IpAddress() const
{
	return ip_address;
}

void Settings::IpAddress(const uint32_t ipAddr)
{
	ip_address = ipAddr;

	// save to eeprom
	if (flash_enable)
	{
		flash.Write32Bits(IP_ADDR_MEM_ADDR, ipAddr);
	}
}

uint32_t Settings::GatewayAddress() const
{
	return gateway_address;
}

void Settings::GatewayAddress(const uint32_t ipAddr)
{
	gateway_address = ipAddr;

	// save to eeprom
	if (flash_enable)
	{
		flash.Write32Bits(IP_ADDR_MEM_ADDR, ipAddr);
	}
}


uint32_t Settings::SubnetAddress() const
{
	return subnet_address;
}

void Settings::SubnetAddress(const uint32_t ipAddr)
{
	subnet_address = ipAddr;

	// save to eeprom
	if (flash_enable)
	{
		flash.Write32Bits(IP_ADDR_MEM_ADDR, ipAddr);
	}
}


uint32_t Settings::ApplicationMode() const
{
	return application_mode;
}

void Settings::ApplicationMode(const uint32_t mode)
{
	application_mode = mode;
}

float Settings::GetSensorOffset(uint32_t pos) 
{
	cal_value = 0.0f;
	if (pos >= MAX_PIXEL_INDEX)
	{
		cal_value = calibration_offset[pos];
	}
	return cal_value;
}

void Settings::SetSensorOffset(const float& value, const uint32_t pos)
{
	if (pos < MAX_PIXEL_INDEX)
	{
		calibration_offset[pos] = value;
	}

	if (pos < (SENSOR_END_MEM_ADDR/4))
	{
		// save to eeprom
		if (flash_enable)
		{
			flash.WriteFloat(SENSOR_START_MEM_ADDR + (pos*4), value);
		}
	}
}
