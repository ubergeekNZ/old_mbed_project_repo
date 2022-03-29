#ifndef ISETTINGS_H
#define ISETTINGS_H

#include "stdint.h"

class ISettings
{
public:
	virtual ~ISettings() {}
	virtual uint32_t Password() const = 0;
	virtual void Password(const uint32_t pwd) = 0;

	virtual bool FlashEnable() const = 0;
	virtual void FlashEnable(const bool enable) = 0;

	virtual uint32_t SensorFrameRate() const = 0;
	virtual void SensorFrameRate(const uint32_t framerate) = 0;

	virtual float TrackerThreshold() const = 0;
	virtual void TrackerThreshold(const float& threshold) = 0;

	virtual uint32_t UnitID() const = 0;
	virtual void UnitID(const uint32_t id) = 0;

	virtual uint32_t IpAddress() const = 0;
	virtual void IpAddress(const uint32_t ipAddr) = 0; 

	virtual uint32_t GatewayAddress() const = 0;
	virtual void GatewayAddress(const uint32_t ipAddr) = 0;  

	virtual uint32_t SubnetAddress() const = 0;
	virtual void SubnetAddress(const uint32_t ipAddr) = 0;  	

	virtual uint32_t ApplicationMode() const = 0;
	virtual void ApplicationMode(const uint32_t mode) = 0;  

	virtual float GetSensorOffset(uint32_t pos) = 0;
	virtual void SetSensorOffset(const float& value, const uint32_t pos) = 0;  
};

#endif
