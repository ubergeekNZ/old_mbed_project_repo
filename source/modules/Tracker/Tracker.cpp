#include "Tracker.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

#define FRAME_PER_SECONDS           10
#define MOVING_AVERAGE_LENGTH       10
#define MS_IN_SECS                  1000
#define DEFAULT_FPS_IN_MS           (MS_IN_SECS/FRAME_PER_SECONDS)
#define DEFAULT_PEAK_THRESHOLD      1.8f
#define TRACKER_OBJECT_TIMEOUT      (2)

// #define DEBUG 1

using namespace std;

static uint32_t up_counter = 0;
static uint32_t down_counter = 0;
static List<TrackerObjectStruct> *tracker_list;
static List<FoundObjectStruct> *found_object_list;

Tracker::Tracker(ISystemTime& timer, IThermopile& sensor, IQueue<sEvent>& event_queue) : 
    m_timer(timer),
    m_sensor(sensor),
    m_event_queue(event_queue),
    average_pixel_value(0),
    max_value(0),
    moving_average_counter(1),
    m_framerate(DEFAULT_FPS_IN_MS),
    m_threshold(DEFAULT_PEAK_THRESHOLD)
    // tracker_list(16),
    // found_object_list(16)
{
    tracker_list = new List<TrackerObjectStruct>(16);
    found_object_list = new List<FoundObjectStruct>(16);
    m_timer.reset();
}

void Tracker::ProcessTracker()
{
    current_ms = m_timer.get_tick_ms();

    if (current_ms >= m_framerate)
    {

        average_pixel_value = 0.0f;
        max_value = 0.0f;

        // debug.printf("{");
        for(int pixel = 0; pixel < 64; pixel++)
        {
            frame.pixel[pixel] = m_sensor.ReadSinglePixel(pixel);

            if (frame.pixel[pixel] > max_value)
            {
                max_value = frame.pixel[pixel];
            }
            average_pixel_value += frame.pixel[pixel];

            // Perform a moving average
            if (moving_average_counter < MOVING_AVERAGE_LENGTH)
            {
                average_frame.pixel[pixel] += frame.pixel[pixel];
                average_frame.pixel[pixel] /= moving_average_counter;
            }
            else
            {
                average_frame.pixel[pixel] += frame.pixel[pixel];
                average_frame.pixel[pixel] /= 2;
            }
        }

        if (moving_average_counter < MOVING_AVERAGE_LENGTH)
        {
            moving_average_counter++;
        }

        average_pixel_value /= 64.0f;
#if DEBUG
        cout << "average: " << average_pixel_value << endl;
#endif
        FindObjects();

        UpdateTrackerList(); 

        m_timer.reset();
    }

    // cout << "fps: " << FPS_IN_MS << endl;
}

void Tracker::TrackerTimeout()
{
	uint32_t num_of_current_objects = tracker_list->sizeOfList();

	for (uint32_t track_index = 0; track_index < num_of_current_objects; track_index++)
    {
    	TrackerObjectStruct current_object = tracker_list->peekElement(track_index);
    	current_object.timeout++;

    	// timeout check
        if (current_object.timeout > TRACKER_OBJECT_TIMEOUT)
        {   	
#if DEBUG            
            cout << "Remove item from the list: " << current_object.tracker_id << endl;
#endif            
            // remove the object
            tracker_list->removeFromList(track_index);
            num_of_current_objects--;
            track_index--;
        }
        else
        {
        	// update the object
        	tracker_list->replaceElement(track_index, current_object);
        }
    }
}

void Tracker::UpdateTrackerList()
{
    uint32_t num_of_objects = found_object_list->sizeOfList();
    bool add_new_object = true;
    FoundObjectStruct found_object;
    TrackerObjectStruct current_object;

    if (num_of_objects)
    {
    	uint32_t num_of_current_objects = tracker_list->sizeOfList();

        if (num_of_current_objects)
        {
            // browse through the found object list
            for (uint32_t find_index = 0; find_index < num_of_objects; find_index++)
            {
            	found_object = found_object_list->peekElement(find_index);
            	add_new_object = true;

                for (uint32_t track_index = 0; track_index < num_of_current_objects; track_index++)
                {
                	current_object = tracker_list->peekElement(track_index);
#if DEBUG
                    cout << "Found: " << found_object.pixel_y << "," << found_object.pixel_x << endl;
                    cout << "Track: " << current_object.pixel_y << "," << current_object.pixel_x << endl;
#endif
                	// check if it is one pixel difference
	                if (abs(int32_t(found_object.pixel_x) - int32_t(current_object.pixel_x)) <= 2 
	                    && abs(int32_t(found_object.pixel_y) - int32_t(current_object.pixel_y)) <= 1)
	                {	    
#if DEBUG
                        cout << "Pixel difference counted: " << current_object.counted << " Y: " << current_object.pixel_x << endl;
#endif
	                	// Check if the item has cross the center line
                        if ((current_object.start_x == 1 || current_object.start_x == 0) &&
                            !current_object.counted)
                        {
                            if ((current_object.pixel_x == 3 || current_object.pixel_x == 2) //
                            	&& (found_object.pixel_x == 4 || found_object.pixel_x == 5))
                            {
                                up_counter++;
                                event.id = EVT_SEND_COUNTER;
                                m_event_queue.enqueue(event);     
                                current_object.counted = true;
#if DEBUG                                
                                cout << "<<<< up ++ >>>>" << endl;
#endif                                
                            }
#if DEBUG
                            cout << "Update tracker list " << current_object.tracker_id << ": " <<                         
                            found_object.pixel_y << "," << found_object.pixel_x << endl;
#endif                        
                            // update current tracker list
                            current_object.pixel_x = found_object.pixel_x;
                            current_object.pixel_y = found_object.pixel_y;
                            current_object.temperature = found_object.temperature;
                        }

                        if ((current_object.start_x == 7 || current_object.start_x == 6) &&
                            !current_object.counted)
                        {
                            if ((current_object.pixel_x == 5 || current_object.pixel_x == 4) // 
                            	&& (found_object.pixel_x == 3 || found_object.pixel_x == 2))
                            {
                                down_counter++;
                                event.id = EVT_SEND_COUNTER;
                                m_event_queue.enqueue(event);  
                                current_object.counted = true;    
#if DEBUG                                
                                cout << "<<<< down ++ >>>>" << endl;           
#endif                                
                            }
#if DEBUG                            
                            cout << "Update tracker list " << current_object.tracker_id << ": " <<                            
                            found_object.pixel_y << "," << found_object.pixel_x << endl;
#endif                            
                            // update current tracker list
                            current_object.pixel_x = found_object.pixel_x;
                            current_object.pixel_y = found_object.pixel_y;
                            current_object.temperature = found_object.temperature;
                        }

	                    // update the object
                        current_object.timeout = 0;
        				tracker_list->replaceElement(track_index, current_object);
	                    add_new_object= false;

                        // exit the inner loop
                        break;
	                }
                }

                if (add_new_object)
                {	
	                current_object.tracker_id = rand() % 1000;
                    current_object.start_x = found_object.pixel_x;
                    current_object.start_y = found_object.pixel_y;
	                current_object.pixel_x = found_object.pixel_x;
	                current_object.pixel_y = found_object.pixel_y;
                    current_object.counted = false;
	                current_object.temperature = found_object.temperature;
	                current_object.timeout = 0;
#if DEBUG
                    cout << "Add the new item to the tracker list: " << current_object.tracker_id << ": " <<
                    found_object.pixel_y << "," << found_object.pixel_x << endl;
#endif                    
	                tracker_list->push(current_object);				 
                }
            }
        }
        else
        {
            // browse through the found object list
            for (uint32_t find_index = 0; find_index < num_of_objects; find_index++)
            {
                found_object = found_object_list->peekElement(find_index);

                current_object.tracker_id = rand() % 1000;
                current_object.start_x = found_object.pixel_x;
                current_object.start_y = found_object.pixel_y;
                current_object.pixel_x = found_object.pixel_x;
                current_object.pixel_y = found_object.pixel_y;
                current_object.counted = false;
                current_object.temperature = found_object.temperature;
                current_object.timeout = 0;
#if DEBUG
                cout << "copy to tracker list: " << current_object.tracker_id << ": " <<
                found_object.pixel_y << "," << found_object.pixel_x << endl;
#endif                

                tracker_list->push(current_object);		 
            }
        }
    }

    TrackerTimeout();
}

uint32_t Tracker::read_up_counter()
{
	return up_counter;
}

uint32_t Tracker::read_down_counter()
{
	return down_counter;
}

void Tracker::Reset()
{
    up_counter = 0;
    down_counter = 0;

    // reset the lists
    found_object_list->reset();
    tracker_list->reset();
}

void Tracker::SetFrameRate(uint32_t rate)
{
    m_framerate = MS_IN_SECS/rate;
}

uint32_t Tracker::GetFrameRate()
{
    return MS_IN_SECS/m_framerate;
}

void Tracker::SetThreshold(float level)
{
    m_threshold = level;
}

float Tracker::GetThreshold()
{
    return m_threshold;
}

// TODO - calculate number of clock cycles
void Tracker::FindObjects()
{
    found_object_list->reset();
#if DEBUG
    cout << "<<<<<<<<<<<<<<= Start =>>>>>>>>>>>>>>>>>" << endl;
#endif
    for (int32_t col = 0; col < 8; col++)
    {
        for (int32_t row = 0; row < 8; row++)
        {
            float diff = fabs(frame.pixel[(row*8) + col] - average_pixel_value);

            if (diff >= m_threshold)
            {
#if DEBUG                
                cout << "Found peak at: " << diff << "-" << row << "," << col << endl;
#endif         
                FoundObjectStruct found_object;
                found_object.pixel_x = col;
                found_object.pixel_y = row;
                found_object.temperature = frame.pixel[(col*8) + row];
                found_object_list->push(found_object);
            }
        }
    }
#if DEBUG
    cout << "<<<<<<<<<<<<<<= End =>>>>>>>>>>>>>>>>>" << endl;
#endif
}