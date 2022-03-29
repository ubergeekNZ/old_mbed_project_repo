#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdint.h"
#include "ProductConfig.h"
#include "IFlashInterface.h"
#include "ISettings.h"

#define FLASH_ENABLE_MEM_ADDR   (0)
#define FRAMERATE_MEM_ADDR      (4)
#define THRESHOLD_MEM_ADDR      (8)
#define UNITID_MEM_ADDR         (12)
#define IP_ADDR_MEM_ADDR        (16)
#define SENSOR_START_MEM_ADDR   (20)
#define SENSOR_END_MEM_ADDR     (84)

// need interface for testing
class Settings : public ISettings
{
private:
  uint32_t password;
  uint32_t sensor_framerate;
  float tracker_threshold;
  uint32_t unit_id;
  uint32_t ip_address;
  uint32_t gateway_address;
  uint32_t subnet_address;
  uint32_t application_mode;
  float calibration_offset[MAX_PIXEL_INDEX];
  float cal_value;
  bool flash_enable;
  IFlashInterface& flash;

  // set time and rtc

public:
	// load eeprom access class
  explicit Settings(IFlashInterface& flash);

  uint32_t Password() const;
  void Password(const uint32_t pwd);

  bool FlashEnable() const;
  void FlashEnable(const bool enable);

  uint32_t SensorFrameRate() const;
  void SensorFrameRate(const uint32_t framerate);

  float TrackerThreshold() const;
  void TrackerThreshold(const float& threshold);

  uint32_t UnitID() const;
  void UnitID(const uint32_t id);

  uint32_t IpAddress() const;
  void IpAddress(const uint32_t ipAddr);  

  uint32_t GatewayAddress() const;
  void GatewayAddress(const uint32_t ipAddr);  

  uint32_t SubnetAddress() const;
  void SubnetAddress(const uint32_t ipAddr);  

  uint32_t ApplicationMode() const;
  void ApplicationMode(const uint32_t mode);  

  float GetSensorOffset(uint32_t pos);
  void SetSensorOffset(const float& value, const uint32_t pos);  
};

#endif