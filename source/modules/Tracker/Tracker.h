#ifndef _TRACKER_H
#define _TRACKER_H

// Remove some unused headers from this file
#include "ITracker.h"
#include "ISystemTime.h"
#include "IThermopile.h"
#include "Types.h"
#include "List.h"
#include "Events.h"
#include "IQueue.h"

typedef struct 
{
	uint32_t pixel_x;
	uint32_t pixel_y;
  float temperature;
} FoundObjectStruct;

typedef struct 
{
  uint32_t start_x;
  uint32_t start_y;
	uint32_t tracker_id;
	uint32_t pixel_x;
	uint32_t pixel_y;
  float temperature;
  uint32_t timeout;
  bool counted;
} TrackerObjectStruct;

class Tracker : public ITracker {
 private:
  ImageStruct frame;
  ImageStruct average_frame;
  ISystemTime& m_timer;
  IThermopile& m_sensor;
  IQueue<sEvent>& m_event_queue;
  uint32_t current_ms;
  float average_pixel_value;
  uint32_t moving_average_counter;
  float max_value;
  sEvent event;
  uint32_t m_framerate;
  float m_threshold;
  void TrackerTimeout();
  void UpdateTrackerList();
  void FindObjects();
 public:
  Tracker(ISystemTime& timer, IThermopile& sensor, IQueue<sEvent>& event_queue);
  uint32_t read_up_counter();
  uint32_t read_down_counter();
  void SetThreshold(float level);
  float GetThreshold();
  void SetFrameRate(uint32_t rate);
  uint32_t GetFrameRate();
  void ProcessTracker();
  void Reset();
};

#endif  // _TRACKER_H
