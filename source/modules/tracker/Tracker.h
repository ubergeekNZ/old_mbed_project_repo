#ifndef _TRACKER_H
#define _TRACKER_H

// Remove some unused headers from this file
#include "ITracker.h"
#include "ISystemTime.h"
#include "Types.h"
#include "List.h"

typedef struct 
{
	uint32_t pixel_x;
	uint32_t pixel_y;
  float temperature;
} FoundObjectStruct;

typedef struct 
{
	uint32_t tracker_id;
	uint32_t pixel_x;
	uint32_t pixel_y;
    float temperature;
    uint32_t timeout;
} TrackerObjectStruct;

class Tracker : public ITracker {
 private:
  // ISystemTime& m_timer;
  void TrackerTimeout();
  void UpdateTrackerList();
  void FindObjects(ImageStruct& current_image);
  void UpdateCount();
 public:
  // Tracker(ISystemTime& timer);
  explicit Tracker();
  void ProcessFrame(ImageStruct& current_image);
  // void register_listener(IListener *listener);
};

#endif  // _TRACKER_H
