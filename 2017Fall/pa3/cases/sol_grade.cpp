/*
 *       File: pa3.cpp
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Implementation of all functions by Yao Yao.
 */

#include "structure.h"

Frame * GetFrame_(const Video & video, const int frame_index)
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

Vehicle * GetVehicle_(const Video & video, const int vehicle_index)
{
	// your implementation
	if (vehicle_index >= video.num_vehicles || vehicle_index < 0 || video.num_vehicles <= 0)
		return (nullptr);

	return (video.vehicles[vehicle_index]);
}

VehicleFrameInfo * GetVFInfo_(const Vehicle * vehicle, const int frame_index)
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

bool InitializeNewFrame_(Video & video)
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
		Frame * last_frame = GetFrame_(video, video.num_processed_frames - 1);
		last_frame->next_frame = new_frame;
	}
	video.num_processed_frames++;

	return (true);
}

bool AddVFInfo_(Video & video, VehicleFrameInfo * vehicle_frame_info)
{
	// your implementation
	// check if the vehicle and vehicle are both in the video
	if (vehicle_frame_info->frame_index >= video.num_processed_frames
		|| vehicle_frame_info->frame_index < 0
		|| vehicle_frame_info->vehicle_index >= video.num_vehicles
		|| vehicle_frame_info->vehicle_index < 0)
		return (false);

	Frame * frame = GetFrame_(video, vehicle_frame_info->frame_index);
	Vehicle * vehicle = GetVehicle_(video, vehicle_frame_info->vehicle_index);

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

VehicleFrameInfo * TrackVehicle_(const Vehicle * vehicle, const Frame * current_frame, const Frame * prev_frame)
{
	// your implementation
	// find vehicle in previous frame
	VehicleFrameInfo * prev_info = GetVFInfo_(vehicle, prev_frame->index);
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

bool FindAndAddNewVehicles_(Video & video)
{
	// your implementation
	int new_frame_index = video.num_processed_frames - 1;
	Frame * new_frame = GetFrame_(video, new_frame_index);
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
			AddVFInfo_(video, new_vehicle_info);
		}
	}
	return (true);
}

double AverageRoadSpeed_(Video & video)
{
	// your implementation
	// go through all vehicle
	double speed_num = 0;
	double speed_count = 0;
	for (int vehicle_index = 0; vehicle_index < video.num_vehicles; ++vehicle_index)
	{
		Vehicle * vehicle = GetVehicle_(video, vehicle_index);
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

void CleanVideo_(Video & video)
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

void InitVideo_(Video& video)
{
	video.raw_data = nullptr;
	video.first_frame = nullptr;
	video.num_frames = 0;
	video.num_processed_frames = 0;
	video.num_vehicles = 0;
	for (int i = 0; i < MAX_VEHICLE_NUM; ++i)
		video.vehicles[i] = nullptr;
}

void PrintFrameInfo_(const Video & video, const int frame_index)
{
	Frame * frame = GetFrame_(video, frame_index);
	if (frame == nullptr)
	{
		cout << "Frame " << frame_index << " info: invalid!\n";
	}
	else
	{
		PrintFrameInfo1_(video, frame);
	}
}

void PrintFrameInfo1_(const Video & video, const Frame * frame)
{
	if (frame != nullptr)
	{
		int frame_index = frame->index;
		cout << "Frame " << frame_index << " full info: \n";
		cout << "    image: \n";
		// print some part of the image
		for (int i = 1; i < ROWS; i+=2)
		{
			cout << "        ";
			for (int j = 0; j < COLS / 2; ++j)
			{
				cout << frame->image[i][j] << " ";
			}
			cout << "\n";
		} 
		cout << "    " << frame->num_vehicles << " vehicles in this frame.\n";
		for (int vehicle_index = 0; vehicle_index < MAX_VEHICLE_NUM; ++vehicle_index)
		{
			// print vehicle index if the vehicle is visible to the frame
			if (frame->vehicles[vehicle_index] != nullptr)
			{
				Vehicle * vehicle = GetVehicle_(video, vehicle_index);
				VehicleFrameInfo * vf_info = GetVFInfo_(vehicle, frame_index);
				cout << "    vehicle " << vf_info->vehicle_index
					<< " in coordinate (" << vf_info->position[0] << ", " << vf_info->position[1] << ")"
					<< " with speed of " << vf_info->speed << "\n";
			}
		}
	}
}

void PrintVehicleInfo_(Video & video, const int vehicle_idx)
{
	Vehicle * vehicle = GetVehicle_(video, vehicle_idx);
	if (vehicle == nullptr)
	{
		cout << "Vehicle " << vehicle_idx << " full info: invalid!\n";
	}
	else
	{
		PrintVehicleInfo1_(video, vehicle);
	}
	return;
}

void PrintVehicleInfo1_(Video & video, const Vehicle * vehicle)
{
	if (vehicle != nullptr)
	{
		int vehicle_idx = vehicle->index;
		cout << "Vehicle " << vehicle_idx << " info:\n";
		VehicleFrameInfo * vf_info = vehicle->first_frame_info;
		for (int i = 0; i < vehicle->num_visible_frames; ++i)
		{
			cout << "    in frame " << vf_info->frame_index
				<< " in (" << vf_info->position[0] << ", " << vf_info->position[1] << ")"
				<< " with speed of " << vf_info->speed << "\n";
			vf_info = vf_info->next_frame_info;
		}
	}
	return;
}

bool ReadVideoRawData_(Video & video, const string & video_file)
{
	ifstream video_stream;
	video_stream.open(video_file);
	if (!video_stream.is_open())
		return (false);
	cout << "Reading video file. ";

	// read first line
	string word;
	video_stream >> word >> video.num_frames;
	cout << "Totally " << video.num_frames << " frames. ";

	// allocate memory for data
	//video.raw_data = new char[video.num_frames][ROWS][COLS];
	video.raw_data = new char** [video.num_frames];
	for (int f = 0; f < video.num_frames; ++f)
    {
        video.raw_data[f] = new char* [ROWS];
        for (int r = 0; r < ROWS; ++r)
            video.raw_data[f][r] = new char [COLS];
    }

	// read all frame
	for (int f = 0; f < video.num_frames; ++f)
	{
		int frame_id;
		video_stream >> word >> frame_id;
		for (int i = 0; i < ROWS; ++i)
		{
			for (int j = 0; j < COLS; ++j)
			{
				video_stream >> video.raw_data[f][i][j];
			}
		}
	}
	cout << "Finished.\n\n";

	return (true);
}
