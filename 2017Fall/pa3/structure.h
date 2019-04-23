/*
 *		 File: structure.h
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Do NOT modify this file
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#define ROWS 9              // number of rows of each frame
#define COLS 30             // number of column of each frame
#define LANE_NUM 4          // number of lanes
#define MAX_SPEED 8         // the maximum speed of the vehicle
#define MAX_VEHICLE_NUM 50  // the maximum number of vehicles that will appear in one video

struct Video;
struct Vehicle;
struct Frame;
struct VehicleFrameInfo;

/*
 * Structure for the video
 *
 *           num_frames: the total number of frames of this video.
 *             raw_data: point to the 3 dimensional video data.
 *                       data of one frame.
 * num_processed_frames: the number of frames in the link list structure (processed number of frames).
 *          first_frame: the pointer to the first frame structure. All frames are chained by the link 
 *                       list structure.
 *         num_vehicles: the number of detected vehicles in the video.
 *             vehicles: the array of pointers to all vehicles in this frame. All pointers are 
 *                       initialized as nullptr.
 */
struct Video
{
    int num_frames;
    char*** raw_data;

    int num_processed_frames;
    Frame* first_frame;

    int num_vehicles;
    Vehicle* vehicles[MAX_VEHICLE_NUM];
};

/*
 * Structure for describing one frame
 *
 *        index: the index of this frame.
 *        image: point to the 2 dimensional image data.
 * num_vehicles: number of vehicles in this frame.
 *     vehicles: the array of pointers to all vehicles. If the i-th vehicle is not in this frame
 *               then set vehicles[i] to nullptr. All pointers are initialized as nullptr.
 *   next_frame: the pointer to the next frame. All frames are chained by the link list structure.
 *               If current frame is the end then set it to nullptr.
 */
struct Frame
{
	int index;
	char** image;

	int num_vehicles;
	Vehicle* vehicles[MAX_VEHICLE_NUM];

	Frame* next_frame;
};

/*
 * Structure for describing one vehicle
 *
 *             index: the index of the vehicle, and the vehicles are indexed by the occurrence 
 *                    order (starting from 0). If several vehicles first appear in the same frame,
 *                    index them by ascending order of their position from top rows to bottle rows.
 * num_visible_frames: the number of frames the vehicle is visible to.
 *  first_frame_info: pointer to the information of this vehicle in its first visible frame.
 *                    All infos (in this frame's all visible frames) are chained by the link list.
 */
struct Vehicle
{
    int index;
    int num_visible_frames;
    VehicleFrameInfo* first_frame_info;
};

/*
 * Structure for describing one vehicle in one frame
 *
 *   vehicle_index: the index of the vehicle.
 *     frame_index: the index of the frame.
 *     position[2]: the coordinate (row and column) of the vehicle in the frame;
 *           speed: the speed of the vehicle (distance between the coordinates in two frames).
 *                  For the new vehicles detected (in the first column), initialize the speed
 *                  as 1.
 * next_frame_info: pointer to the information of this vehicle in next visible frame. If the 
 *                  current info is of the last visible frame then set it to nullptr.
 */
struct VehicleFrameInfo
{
    int vehicle_index; 
    int frame_index;
    int position[2];
    double speed;

    VehicleFrameInfo* next_frame_info;
};

/******************** 9 functions to be implemented ********************/
Frame* GetFrame(const Video& video, const int frame_index);

Vehicle* GetVehicle(const Video& video, const int vehicle_index);

VehicleFrameInfo* GetVFInfo(const Vehicle* vehicle, const int frame_index);

bool InitializeNewFrame(Video& video);

VehicleFrameInfo* TrackVehicle(const Vehicle* vehicle, const Frame* current_frame, const Frame* prev_frame);

bool AddVFInfo(Video& video, VehicleFrameInfo* vehicle_frame_info);

bool FindAndAddNewVehicles(Video& video);

double AverageRoadSpeed(Video& video);

void CleanVideo(Video& video);

#endif	// STRUCTURE_H_
