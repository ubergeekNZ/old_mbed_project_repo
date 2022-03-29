#include "Tracker.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static List<TrackerObjectStruct> *current_object_list;
static List<TrackerObjectStruct> *remove_tracker_object_list;
static List<FoundObjectStruct> *found_object_list;

// Tracker::Tracker(ISystemTime& timer) :
//     m_timer(timer)
// {
//     // create lists for tracking
//     current_object_list = new List<TrackerObjectStruct>(16);
//     tracker_object_list = new List<TrackerObjectStruct>(16);
//     found_object_list = new List<FoundObjectStruct>(16);
// }
// 
// 

static uint32_t up_counter = 0;
static uint32_t down_counter = 0;

Tracker::Tracker()
{
    // create lists for tracking
    current_object_list = new List<TrackerObjectStruct>(16);
    remove_tracker_object_list = new List<TrackerObjectStruct>(16);
    found_object_list = new List<FoundObjectStruct>(16);
}

void Tracker::ProcessFrame(ImageStruct& current_image)
{
    cout << "New frame" << endl;
    // reset object lists
    found_object_list->reset();

    // find objects
    FindObjects(current_image);

    // update tracker lists
    UpdateTrackerList(); 

    // cout << "<<<< (Current) up: " << up_counter << ", down: "<< down_counter << " >>>>" <<endl;
    
}

void Tracker::TrackerTimeout()
{
	uint32_t num_of_current_objects = current_object_list->sizeOfList();

	// cout << "Timeout - number of objects: " << num_of_current_objects << endl;

	for (uint32_t track_index = 0; track_index < num_of_current_objects; track_index++)
    {
    	TrackerObjectStruct current_object = current_object_list->peekElement(track_index);
    	current_object.timeout++;

    	// timeout check
        if (current_object.timeout > 2)
        {
        	cout << "Remove item from the list: " << current_object.tracker_id << endl;
            // remove the object
            current_object_list->removeFromList(track_index);
            num_of_current_objects--;
            track_index--;
        }
        else
        {
        	// cout << "Update track object time: " << current_object.tracker_id << endl;
        	// update the object
        	current_object_list->replaceElement(track_index, current_object);
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
    	uint32_t num_of_current_objects = current_object_list->sizeOfList();

        if (num_of_current_objects)
        {
            // browse through the found object list
            for (uint32_t find_index = 0; find_index < num_of_objects; find_index++)
            {
            	found_object = found_object_list->peekElement(find_index);
            	add_new_object = true;

                for (uint32_t track_index = 0; track_index < num_of_current_objects; track_index++)
                {
                	current_object = current_object_list->peekElement(track_index);
     		 
	                cout << "Found: " << found_object.pixel_x << "," << found_object.pixel_y << endl;
                    cout << "Track: " << current_object.pixel_x << "," << current_object.pixel_y << endl;

                	// check if it is one pixel difference
	                if (abs(int32_t(found_object.pixel_x) - int32_t(current_object.pixel_x)) <= 1 
	                    && abs(int32_t(found_object.pixel_y) - int32_t(current_object.pixel_y)) <= 2)
	                {
	                	cout << "Updating!!!!" << endl;
	                	// Check if the item has cross the center line
                        if ((current_object.pixel_y == 3 || current_object.pixel_y == 2) //
                        	&& (found_object.pixel_y == 4 || found_object.pixel_y == 5))
                        {
                            up_counter++;
                            cout << "<<<< up: " << up_counter << " >>>>" <<endl;
                        }

                        if ((current_object.pixel_y == 5 or current_object.pixel_y == 4) // 
                        	&& (found_object.pixel_y == 3 || found_object.pixel_y == 2))
                        {
                            down_counter++;
                            cout << "<<<< down: " << down_counter << " >>>>" << endl;
                        }

	                    // update current tracker list
	                    current_object.pixel_x = found_object.pixel_x;
		                current_object.pixel_y = found_object.pixel_y;
		                current_object.temperature = found_object.temperature;
		                current_object.timeout = 0;

	                    // update the object
        				current_object_list->replaceElement(track_index, current_object);
	                    add_new_object= false;
	                }
                }

                if (add_new_object)
                {	
	                current_object.tracker_id = rand() % 1000;
	                current_object.pixel_x = found_object.pixel_x;
	                current_object.pixel_y = found_object.pixel_y;
	                current_object.temperature = found_object.temperature;
	                current_object.timeout = 0;
	                current_object_list->push(current_object);

	                cout << "Add the new item to the tracker list: " << current_object.tracker_id //
	                	 << "(" << current_object.pixel_x << "," //
	                	 << current_object.pixel_y << ")" //
						 << endl;
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
                current_object.pixel_x = found_object.pixel_x;
                current_object.pixel_y = found_object.pixel_y;
                current_object.temperature = found_object.temperature;
                current_object.timeout = 0;
                current_object_list->push(current_object);

                cout << "Found first track object: " << current_object.tracker_id //
	                	 << "(" << current_object.pixel_x << "," //
	                	 << current_object.pixel_y << ")" //
						 << endl;
            }
        }
    }

    TrackerTimeout();
}

void Tracker::UpdateCount()
{

}

// TODO - calculate number of clock cycles
void Tracker::FindObjects(ImageStruct& current_image)
{
    // scroll through the columns and rows of the frame
    for (int32_t col = 0; col < 8; col++)
    {
        for (int32_t row = 0; row < 8; row++)
        {
            // check if pixel value is greater than 0 deg C
            if (current_image.pixel[(col*8) + row] > 0)
            {
                uint32_t num_of_objects = found_object_list->sizeOfList();
                if (num_of_objects)
                {
                    bool new_object_flag = true;
                    FoundObjectStruct found_object;

                    // scroll through the object list
                    for (uint32_t index = 0; index < num_of_objects; index++)
                    {
                    	// cout << "Number of found objects: " << num_of_objects << endl;

                        found_object = found_object_list->peekElement(index);

                        // check if it is one pixel difference
                        if (abs(int32_t(found_object.pixel_x) - col) <= 1 
                            && abs(int32_t(found_object.pixel_y) - row) <= 1)
                        {
                            if (current_image.pixel[(col*8) + row] > found_object.temperature)
                            {
                                cout << "Update object (" << col << "," << row << ")" <<endl;
                                // update the object in the list
                                found_object.pixel_x = col;
                                found_object.pixel_y = row;
                                found_object.temperature = current_image.pixel[(col*8) + row];
                                found_object_list->replaceElement(index, found_object);
                            }
                            new_object_flag= false;
                        }
                    }

                    if (new_object_flag)
                    {
                        cout << "Add new object (" << col << "," << row << ")" << endl;//
                         // << " temp:" << current_image.pixel[(col*8) + row] << endl;
                        // add a new object in the list
                        found_object.pixel_x = col;
                        found_object.pixel_y = row;
                        found_object.temperature = current_image.pixel[(col*8) + row];
                        found_object_list->push(found_object);
                    }
                }
                else
                {
                    cout << "Add first found object (" << col << "," << row << ")" << endl;//
                         // << " temp:" << current_image.pixel[(col*8) + row] << endl;
                    // first pixel > 0; add first found object
                    FoundObjectStruct current_object;
                    current_object.pixel_x = col;
                    current_object.pixel_y = row; 
                    current_object.temperature = current_image.pixel[(col*8) + row];
                    found_object_list->push(current_object);
                }
            }
        }
    }
}