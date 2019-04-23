/*
 *       File: main.cpp
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Do NOT modify this file
 */

#include <iostream>
#include <fstream>
#include <string>
#include "structure.h"

using namespace std;


/*
 * Initialize the video structure from file
 */
void InitVideo(Video& video)
{
	video.raw_data = nullptr;
	video.first_frame = nullptr;
	video.num_frames = 0;
	video.num_processed_frames = 0;
	video.num_vehicles = 0;
	for (int i = 0; i < MAX_VEHICLE_NUM; ++i)
		video.vehicles[i] = nullptr;
}


/*
 * Print all vehicles in the frame
 */
void PrintFrameInfo(const Video & video, const int frame_index)
{
	Frame * frame = GetFrame(video, frame_index);
	if (frame == nullptr)
	{
		cout << "Frame " << frame_index << " info: invalid!";
	}
	else
	{
		cout << "Frame " << frame_index << " info:\n";
		for (int vehicle_index = 0; vehicle_index < MAX_VEHICLE_NUM; ++vehicle_index)
		{
			// print vehicle index if the vehicle is visible to the frame
			if (frame->vehicles[vehicle_index] != nullptr)
			{
				Vehicle * vehicle = GetVehicle(video, vehicle_index);
				VehicleFrameInfo * vf_info = GetVFInfo(vehicle, frame_index);
				cout << "    vehicle " << vf_info->vehicle_index
                     << " in coordinate (" << vf_info->position[0] << ", " << vf_info->position[1] << ")"
                     << " with speed of " << vf_info->speed << "\n";
			}
		}
	}
}

/*
 * Print all information of the vehicle
 */
void PrintVehicleInfo(Video & video, const int vehicle_idx)
{
	Vehicle * vehicle = GetVehicle(video, vehicle_idx);
	if (vehicle == nullptr)
	{
		cout << "Vehicle " << vehicle_idx << " full info: invalid!\n";
	}
	else
	{
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

/*
 * Note: only video.num_frames and video.raw_data will be initialized.
 *       All other variables in video should be filled in later processing
 */
bool ReadVideoRawData(Video & video, const string & video_file)
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

bool ProcessNextFrame(Video & video)
{
	// 1. initialize a new frame.
	if (!InitializeNewFrame(video))
	{
		cout << "Error while initializing new frame.\n";
		return (false);
	}
	int new_frame_index = video.num_processed_frames - 1;
	Frame * new_frame = GetFrame(video, video.num_processed_frames - 1);
	
	// 2. if not the first frame, track all vehicles between previous frame and new frame
	// 3. update new infos in the vehicle and new frame
	if (new_frame_index != 0)
	{
		Frame * prev_frame = GetFrame(video, video.num_processed_frames - 2);
		for (int v_idx = 0; v_idx < MAX_VEHICLE_NUM; ++v_idx)
		{
			// skip invisible vehicle
			if (prev_frame->vehicles[v_idx] == nullptr)
				continue;

			// track the vehicle
			Vehicle * vehicle = GetVehicle(video, v_idx);
			VehicleFrameInfo * new_vf_info = TrackVehicle(vehicle, new_frame, prev_frame);

			// if track success then add new info to the vehicle and new frame
			if (new_vf_info != nullptr)
			{
				// add new info to the the video, update both vehicle and frame
				if (!AddVFInfo(video, new_vf_info))
				{
					cout << "Error while adding new vf_info.\n";
					return (false);
				}
			}
		}
	}

	// 4. detect new vehicles in all lanes, and add new vehicles and their infos to video
	if (!FindAndAddNewVehicles(video))
	{
		cout << "Error while finding new vehicles.\n";
		return (false);
	}

	return (true);
}


int main()
{
	// initialize video
	Video video;
    InitVideo(video);
    
	// read the input video
	const string video_file("video.txt");
	if (!ReadVideoRawData(video, video_file))
	{
		return (-1);
		cout << "Error while reading. Please check 'video.txt' file\n";
	}


	// analyze the video and print the information frame by frame
	for (int frame_index = 0; frame_index < video.num_frames; ++frame_index)
	{
		if (!ProcessNextFrame(video))
		{
			cout << "Error while processing frame: " << frame_index
                 << ". Please check 'ProcessFrame' function\n";
			return (-1);
		}

		PrintFrameInfo(video, frame_index);
	}
	cout << endl;
    

	// print vehicle information
	for (int vehicle_index = 0; vehicle_index < video.num_vehicles; ++vehicle_index)
		PrintVehicleInfo(video, vehicle_index);
	cout << endl;

	// calculate the average speed in this video
	cout << "The average speed of this road: " << AverageRoadSpeed(video) << "\n";

	// clean video with all the memory allocated
	CleanVideo(video);
	return (0);
}
