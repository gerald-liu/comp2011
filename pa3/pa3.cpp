/*
 *       File: pa3.cpp
 * Created on: Nov 1, 2017
 *     Author: Weiyang Liu (wliuax@connect.ust.hk)
 *     		   Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Implement all functions without changing any function prototype.
 *             This is the only file you should modify and submit.
 */

#include <iostream>
#include "structure.h"
using namespace std;

/*
 * Description: get the pointer to the frame through frame index.
 *
 *       video: input video structure.
 * frame_index: the index of the frame to be extracted.
 *      return: the pointer to the frame or nullptr if the frame does not exsist.
 */
Frame* GetFrame(const Video& video, const int frame_index) {
	if (frame_index > video.num_frames - 1 || frame_index < 0) return nullptr;
	else {
		Frame* f = video.first_frame;
		if (f == nullptr) return nullptr;
		for (; f->index < frame_index && f->next_frame != nullptr; f = f->next_frame) ; // asked frame or last processed frame
		return f->index == frame_index ? f : nullptr;
	}
}

/*
 * Description: get the pointer to the vehicle through vehicle index.
 *
 *         video: input video structure.
 * vehicle_index: the index of the vehicle to be extracted.
 *        return: the pointer to the vehicle or nullptr if the vehicle does not exsist.
 */
Vehicle* GetVehicle(const Video& video, const int vehicle_index) {
	if (vehicle_index > video.num_vehicles - 1 || vehicle_index < 0) return nullptr;
	else return video.vehicles[vehicle_index];
}

/*
 * Description: get the pointer to vf_info of a vehicle in one frame.
 *
 *     vehicle: input vehicle structure.
 * frame_index: the frame index of the vf_info to be extracted from this vehicle.
 *      return: the pointer to the vf_info or nullptr if the vehicle is not visible in this frame.
 */
VehicleFrameInfo* GetVFInfo(const Vehicle* vehicle, const int frame_index) {
	if (frame_index < 0) return nullptr;
	else {
		VehicleFrameInfo* vfi = vehicle->first_frame_info;
		if (vfi == nullptr) return nullptr;
		for (; vfi->frame_index < frame_index && vfi->next_frame_info != nullptr; vfi = vfi->next_frame_info) ; // asked vfi or last processed vfi
		return vfi->frame_index == frame_index ? vfi : nullptr;
	}
}

/*
 * Description: initialize a new frame in the video during frame processing. You need to
 *              create a new frame, and initialize this new frame and add it to the link
 *              list. In this function, you don't need to use hard copy to initialize
 *              Frame.image. Also, you don't need to analyze the vehicles in this frame
 *              (set num_vehicles of this new frame as 0 and all pointers to vehicles as nullptr).
 *
 *  video: input video structure.
 * return: true if finish and false if all frames has been processed.
 */
bool InitializeNewFrame(Video& video) {
	if (video.num_processed_frames >= video.num_frames) return false;
	
	Frame* new_frame = new Frame;
	new_frame->index = video.num_processed_frames;
	new_frame->image = video.raw_data[new_frame->index];
	new_frame->num_vehicles = 0;
	for (int i = 0; i < MAX_VEHICLE_NUM; i++) new_frame->vehicles[i] = nullptr;
	new_frame->next_frame = nullptr;

	if (new_frame->index == 0) video.first_frame = new_frame;
	else GetFrame(video, new_frame->index - 1)->next_frame = new_frame;
	video.num_processed_frames++;

	return true;
}

/*
 * Description: add one vf_info to the video. You need to check if the
 *              corresponding frame and vehicle has been in the video, and
 *				the vf_info has been in the list of the vehicle before you add the VFInfo.
 *				
 *              video: input video structure.
 * vehicle_frame_info: pointer to the new info to be added. (vf_info)
 *             return: return true if finish and false if
 *                     1. the frame or the vehicle of this vf_info is not in this video or
 *                     2. vf_info has already been in the list of the vehicle.
 */
bool AddVFInfo(Video& video, VehicleFrameInfo* vehicle_frame_info) {
	if (vehicle_frame_info->frame_index > video.num_processed_frames - 1 || vehicle_frame_info->frame_index < 0
		|| vehicle_frame_info->vehicle_index > video.num_vehicles - 1 || vehicle_frame_info->vehicle_index < 0) return false;

	Vehicle* current_vehicle = video.vehicles[vehicle_frame_info->vehicle_index];
	if (current_vehicle == nullptr) return false;

	VehicleFrameInfo* vfi = current_vehicle->first_frame_info;
	if (vfi == nullptr) return false;
	for (; vfi != nullptr; vfi = vfi->next_frame_info)
		if (vfi->frame_index == vehicle_frame_info->frame_index && vfi->vehicle_index == vehicle_frame_info->vehicle_index) return false;

	GetVFInfo(current_vehicle, current_vehicle->first_frame_info->frame_index + current_vehicle->num_visible_frames - 1)->next_frame_info = vehicle_frame_info;
	current_vehicle->index = vehicle_frame_info->vehicle_index;
	current_vehicle->num_visible_frames++;

	Frame* current_frame = GetFrame(video, vehicle_frame_info->frame_index);
	if (current_frame ==  nullptr) return false;
	current_frame->vehicles[current_vehicle->index] = current_vehicle;
	current_frame->num_vehicles++;

	return true;
}

/*
 * Description: track the vehicle in the new frame and return the new info. 
 *				The speed is the distance between positions of the vehicle in two frames and note that
 *              1. the maximum speed of one vehicle is MAX_SPEED
 *				2. the minimum distance between vehicles in the same lane is MAX_SPEED
 *				3. the vehicle is assumed always to stay in the same lane.
 *
 *       vehicle: pointer to the vehicle to be tracked.
 * current_frame: pointer to the frame the vehicle to be tracked in.
 *    prev_frame: pointer to the previous frame the vehicle was in.
 *        return: the pointer to the new info or nullptr if the vehicle is not in prev_frame or has left the scope of current frame.
 */
VehicleFrameInfo* TrackVehicle(const Vehicle* vehicle, const Frame* current_frame, const Frame* prev_frame) {
	if (vehicle == nullptr || prev_frame == nullptr || current_frame == nullptr) return nullptr;
	if (prev_frame->vehicles[vehicle->index] == nullptr) return nullptr;

	VehicleFrameInfo* prev_vfi = GetVFInfo(vehicle, vehicle->first_frame_info->frame_index + vehicle->num_visible_frames - 1);
	if (prev_vfi == nullptr) return nullptr;
	int prev_row = prev_vfi->position[0];
	int prev_col = prev_vfi->position[1];
	
	for (int current_col = prev_col + 1; current_col <= prev_col + MAX_SPEED && current_col < COLS; current_col++) {
		if (current_frame->image[prev_row][current_col] == '*') {
			VehicleFrameInfo* new_frame_info = new VehicleFrameInfo;
			new_frame_info->frame_index = current_frame->index;
			new_frame_info->vehicle_index = vehicle->index;
			new_frame_info->position[0] = prev_row;
			new_frame_info->position[1] = current_col;
			new_frame_info->speed = current_col - prev_col;
			new_frame_info->next_frame_info = nullptr;
			
			return new_frame_info;
		}
	}
	return nullptr;
}

/*
 * Description: find and add new vehicles in the last frame of the frame list. You need to
 *				1. find the new vehicles in the first column of each lane
 *				2. create and initialize a new vehicle if a new vehicle is found
 *				3. add the new vehicle to the video
 *				4. create a vf_info for the new vehicle in this frame
 *				5. add the vf_info to the video.
 *
 *  video: input video structure.
 * return: true if finish or false if the frame index is invalid.
 */
bool FindAndAddNewVehicles(Video& video) {
	if (video.num_processed_frames > video.num_frames || video.num_processed_frames < 1) return false;
	Frame* current_frame = GetFrame(video, video.num_processed_frames - 1);
	if (current_frame == nullptr) return false;

	for (int lane = 0; lane < LANE_NUM; lane++) { 				// detect new vehicles lane by lane
		if (current_frame->image[2 * lane + 1][0] == '*') { 	// check if there is a new vehicle in the lane
			// construct and add a new vehicle
			Vehicle* new_vehicle = new Vehicle;
			new_vehicle->index = video.num_vehicles;
			new_vehicle->num_visible_frames = 1;
			new_vehicle->first_frame_info = nullptr;
			
			video.num_vehicles++;
			video.vehicles[new_vehicle->index] = new_vehicle;

			current_frame->num_vehicles++;
			current_frame->vehicles[new_vehicle->index] = new_vehicle;

			// construct and add a new vf_info
			VehicleFrameInfo* new_frame_info = new VehicleFrameInfo;
			new_frame_info->frame_index = current_frame->index;
			new_frame_info->vehicle_index = new_vehicle->index;
			new_frame_info->position[0] = 2 * lane + 1;
			new_frame_info->position[1] = 0;
			new_frame_info->speed = 1;
			new_frame_info->next_frame_info = nullptr;

			new_vehicle->first_frame_info = new_frame_info;
		}
	}
	return true;
}

/*
 * Description: calcute the average speed of all vehicles in all their visible frames (the average of all speeds).
 *
 *  video: input video structure.
 * return: the average speed or 0 if no vehicle is in the video.
 */
double AverageRoadSpeed(Video& video) {
	double sum = 0.0;
	int counter = 0;
	for (int i = 0; i < video.num_vehicles; i++) {
		for (VehicleFrameInfo* vfi = video.vehicles[i]->first_frame_info; vfi != nullptr; vfi = vfi->next_frame_info) sum += vfi->speed;
		counter += video.vehicles[i]->num_visible_frames;
	}
	return sum / counter;
}

/*
 * Description: clean all memories of the video, including raw_data, all frames, vehicles and vf_infos.
 *
 *  video: input video to be clean.
 * return: no return.
 */
void DeleteVFI(VehicleFrameInfo* head) {
	if (head == nullptr) return;

	DeleteVFI(head->next_frame_info);
	delete head;
	head = nullptr;
}

void DeleteFrame(Frame* head) {
	if (head == nullptr) return;

	DeleteFrame(head->next_frame);
	delete head;
	head = nullptr;
}

void CleanVideo(Video& video) {
	for (int f = 0; f < video.num_frames; f++) {
		for (int i = 0; i < ROWS; i++) delete[] video.raw_data[f][i];
		delete[] video.raw_data[f];
	}
	delete[] video.raw_data;
	video.raw_data = nullptr;
	
	for (int i = 0; i < video.num_vehicles; i++) {
		DeleteVFI(video.vehicles[i]->first_frame_info);
		delete video.vehicles[i];
		video.vehicles[i] = nullptr;
	}

	DeleteFrame(video.first_frame);
}
