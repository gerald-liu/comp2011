/*
 *       File: pa3.cpp
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Implementation of all functions by Yao Yao.
 */

#include <iostream>
#include "structure.h"
using namespace std;

/*
 * Description: get the pointer to the frame through frame index.
 *
 *       video: input video structure.
 * frame_index: the index of the frame to be extracted.
 *      return: the pointer to the frame or nullptr if the frame does not exist.
 */
Frame * GetFrame(const Video & video, const int frame_index)
{
	// your implementation
	if (frame_index >= video.num_processed_frames || frame_index < 0 || video.num_processed_frames <= 0)
		return (nullptr);

	Frame * frame = video.first_frame;
	for (int i = 0; i < frame_index; ++i)
	{
		frame = frame->next_frame;
	}
	return (frame);
}

/*
 * Description: get the pointer to the vehicle through vehicle index.
 *
 *         video: input video structure.
 * vehicle_index: the index of the vehicle to be extracted.
 *        return: the pointer to the vehicle or nullptr if the vehicle does not exist.
 */
Vehicle * GetVehicle(const Video & video, const int vehicle_index)
{
	// your implementation
	if (vehicle_index >= video.num_vehicles || vehicle_index < 0 || video.num_vehicles <= 0)
		return (nullptr);

	return (video.vehicles[vehicle_index]);
}

/*
 * Description: get the pointer to vf_info of a vehicle in one frame.
 *
 *     vehicle: input vehicle structure.
 * frame_index: the frame index of the vf_info to be extracted from this vehicle.
 *      return: the pointer to the vf_info or nullptr if the vehicle does not visible in
 *              this frame.
 */
VehicleFrameInfo * GetVFInfo(const Vehicle * vehicle, const int frame_index)
{
	// your implementation
	VehicleFrameInfo * vehicle_frame_info = vehicle->first_frame_info;
	for (int i = 0; i < vehicle->num_visible_frames; ++i)
	{
		if (vehicle_frame_info->frame_index == frame_index)
			return (vehicle_frame_info);
		vehicle_frame_info = vehicle_frame_info->next_frame_info;
	}
	return (nullptr);
}

/*
 * Description: initialize a new frame in the video during frame processing. You need to
 *              create a new frame, and initialize this new frame and add it to the link
 *              list. In this function, you don't need to use hard copy to initialize
 *              Frame.image. Also, you don't need to analyze the vehicles in this frame 
 *              (set num_vehicles of this new frame as 0 and all pointers to vehicles as 
 *              nullptr).
 *
 *  video: input video structure.
 * return: true if finish and false if all frames has been processed.
 */
bool InitializeNewFrame(Video & video)
{
	// your implementation
	if (video.num_processed_frames >= video.num_frames)
		return (false);

	// construct new frame
	Frame * new_frame = new Frame;
	new_frame->index = video.num_processed_frames;
	new_frame->image = video.raw_data[video.num_processed_frames];
	new_frame->num_vehicles = 0;
	new_frame->next_frame = nullptr;
	for (int i = 0; i < MAX_VEHICLE_NUM; ++i)
		new_frame->vehicles[i] = nullptr;

	// update video
	if (video.num_processed_frames == 0)
	{
		video.first_frame = new_frame;
	}
	else
	{
		Frame * last_frame = GetFrame(video, video.num_processed_frames - 1);
		last_frame->next_frame = new_frame;
	}
	video.num_processed_frames++;

	return (true);
}

/*
 * Description: add one vf_info to the video. You need to check if the vf_info, the
 *              corresponding frame and the corresponding the vehicle has been in the
 *              video before you add the VFInfo.
 *
 *              video: input video structure.
 * vehicle_frame_info: pointer to the new info to be added. (vf_info)
 *             return: return true if finish and false if
 *                     1. the frame or the vehicle of this vf_info is not in this video or
 *                     2. vf_info has already been in the list of the vehicle.
 */
bool AddVFInfo(Video & video, VehicleFrameInfo * vehicle_frame_info)
{
	// your implementation
	// check if the vehicle and vehicle are both in the video
	if (vehicle_frame_info->frame_index >= video.num_processed_frames
		|| vehicle_frame_info->frame_index < 0
		|| vehicle_frame_info->vehicle_index >= video.num_vehicles
		|| vehicle_frame_info->vehicle_index < 0)
		return (false);

	Frame * frame = GetFrame(video, vehicle_frame_info->frame_index);
	Vehicle * vehicle = GetVehicle(video, vehicle_frame_info->vehicle_index);

	// check if the vf_info has been in the vehicle
	VehicleFrameInfo * existed_vf_info = vehicle->first_frame_info;
	for (int i = 0; i < vehicle->num_visible_frames; ++i)
	{
		if (existed_vf_info->frame_index == vehicle_frame_info->frame_index)
			return (false);
		existed_vf_info = existed_vf_info->next_frame_info;
	}

	// update vehicle
	if (vehicle->num_visible_frames == 0)	// first vf_info
	{
		vehicle->first_frame_info = vehicle_frame_info;
	}
	else
	{
		VehicleFrameInfo * last_vf_info = vehicle->first_frame_info;
		for (int i = 0; i < vehicle->num_visible_frames - 1; ++i)
			last_vf_info = last_vf_info->next_frame_info;
		last_vf_info->next_frame_info = vehicle_frame_info;
	}
	vehicle->num_visible_frames++;

	// update frame
	frame->vehicles[vehicle_frame_info->vehicle_index] = vehicle;
	frame->num_vehicles++;

	return (true);
}

/*
 * Description: track the vehicle in the new frame and return the new info. The speed
 *              is the distance between positions of the vehicle in two frames and note
 *              that 1. the maximum speed of one vehicle is MAX_SPEED and 2. the minimum
 *              distance between vehicles in the same lane is MAX_SPEED and 3. the vehicle
 *              is assumed always to stay in the same lane.
 *       vehicle: pointer to the vehicle to be tracked.
 * current_frame: pointer to the frame the vehicle to be tracked in.
 *    prev_frame: pointer to the previous frame the vehicle was in.
 *        return: the pointer to the new info or nullptr if 1. the vehicle is not in
 *                prev_frame or 2. the vehicle left scope of current frame.
 */
VehicleFrameInfo * TrackVehicle(const Vehicle * vehicle, const Frame * current_frame, const Frame * prev_frame)
{
	// your implementation
	// find vehicle in previous frame
	VehicleFrameInfo * prev_info = GetVFInfo(vehicle, prev_frame->index);
	if (prev_info == nullptr)
		return (nullptr);

	// define the range for detection
	int prev_pos_i = prev_info->position[0];
	int prev_pos_j = prev_info->position[1];
	int row = prev_pos_i;
	int col_start = prev_pos_j + 1;
	int col_end = (prev_pos_j + MAX_SPEED) <= (COLS - 1) ? (prev_pos_j + MAX_SPEED) : (COLS - 1);
	if (col_start >= col_end)
		return (nullptr);

	// search in the range
	for (int j = col_start; j <= col_end; ++j)
	{
		if (current_frame->image[row][j] == '*')
		{
			VehicleFrameInfo * new_info = new VehicleFrameInfo;
			new_info->vehicle_index = vehicle->index;
			new_info->frame_index = current_frame->index;
			new_info->position[0] = row;
			new_info->position[1] = j;
			new_info->speed = j - prev_pos_j;
			new_info->next_frame_info = nullptr;
			return (new_info);
		}
	}

	return (nullptr);
}

/*
 * Description: find and add new vehicles in the last frame of the frame list. You need to 1. find the
 *              new vehicles in the first column of each lane, and 2. create and initialize a new vehicle
 *              is a new vehicle is found and, 3. add the new vehicle to the video and, 4. create a
 *              vf_info for the new vehicle in this frame and, 5. add the vf_info to the video.
 *
 *  video: input video structure.
 * return: true is finish or false if the frame index is invalid.
 */
bool FindAndAddNewVehicles(Video & video)
{
	// your implementation
	int new_frame_index = video.num_processed_frames - 1;
	Frame * new_frame = GetFrame(video, new_frame_index);
	if (new_frame == nullptr)
		return (false);

	// detect new vehicles lane by lane
	for (int lane_index = 0; lane_index < LANE_NUM; ++lane_index)
	{
		int row = lane_index * 2 + 1;

		// check if there is a new vehicle in the lane
		if (new_frame->image[row][0] == '*')
		{
			// construct and add a new vehicle
			Vehicle * new_vehicle = new Vehicle;
			new_vehicle->index = video.num_vehicles;
			new_vehicle->num_visible_frames = 0;
			new_vehicle->first_frame_info = nullptr;
			video.vehicles[video.num_vehicles] = new_vehicle;
			video.num_vehicles++;

			// construct and add a new vf_info
			VehicleFrameInfo * new_vehicle_info = new VehicleFrameInfo;
			new_vehicle_info->frame_index = new_frame_index;
			new_vehicle_info->vehicle_index = new_vehicle->index;
			new_vehicle_info->position[0] = row;
			new_vehicle_info->position[1] = 0;
			new_vehicle_info->speed = 1;
			new_vehicle_info->next_frame_info = nullptr;
			AddVFInfo(video, new_vehicle_info);
		}
	}
	return (true);
}

/*
 * Description: calculate the average speed of all vehicles in all their visible frames.
 *
 *  video: input video structure.
 * return: the average speed or 0 if no vehicle is in the video.
 */
double AverageRoadSpeed(Video & video)
{
	// your implementation
	// go through all vehicle
	double speed_num = 0;
	double speed_count = 0;
	for (int vehicle_index = 0; vehicle_index < video.num_vehicles; ++vehicle_index)
	{
		Vehicle * vehicle = GetVehicle(video, vehicle_index);
		VehicleFrameInfo * vf_info = vehicle->first_frame_info;
		for (int i = 0; i < vehicle->num_visible_frames; ++i)
		{
			speed_num += vf_info->speed;
			speed_count++;
			vf_info = vf_info->next_frame_info;
		}
	}

	if (speed_count == 0)
		return (0);
	else
		return (speed_num / speed_count);
}

/*
 * Description: clean all memory of the video.
 *
 *  video: input video to be clean.
 * return: no return.
 */
void CleanVideo(Video & video)
{
	// your implementation
	// delete raw_data
	if (video.raw_data != nullptr)
	{
		for (int f = 0; f < video.num_frames; ++f)
		{
			for (int i = 0; i < ROWS; ++i)
			{
				delete[] (video.raw_data[f][i]);
				video.raw_data[f][i] = nullptr;
			}
			delete[] (video.raw_data[f]);
			video.raw_data[f] = nullptr;
		}
		delete[] video.raw_data;
		video.raw_data = nullptr;
	}

	// delete frames
	Frame * frame = video.first_frame;
	for (int i = 0; i < video.num_processed_frames; ++i)
	{
		// backup pointer to next frame
		Frame * next_frame = frame->next_frame;
		// delete frame
		delete frame;
		// to next frame
		frame = next_frame;
	}

	// delete vehicles and vf_infos
	for (int i = 0; i < video.num_vehicles; ++i)
	{
		Vehicle * vehicle = video.vehicles[i];
		//delete vf_infos
		VehicleFrameInfo * vf_info = vehicle->first_frame_info;
		for (int i = 0; i < vehicle->num_visible_frames; ++i)
		{
			// backup pointer to next vf_info
			VehicleFrameInfo * next_vf_info = vf_info->next_frame_info;
			//delete vf_info
			delete vf_info;
			// to next vf_info
			vf_info = next_vf_info;
		}
		// delete vehicle
		delete vehicle;
	}
}
