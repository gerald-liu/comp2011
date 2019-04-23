/*
 *       File: main.cpp
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Do NOT modify this file
 */

#include "structure.h"

bool ProcessNextFrame_(Video & video)
{
	// 1. initialize a new frame.
	/**************** test start *****************/
	PrintFrameInfo_(video, video.num_processed_frames);
	if (!InitializeNewFrame(video))
	{
		cout << "Error while initializing new frame.\n";
		return (false);
	}
	int new_frame_index = video.num_processed_frames - 1;
	PrintFrameInfo_(video, new_frame_index);
	/**************** test end *****************/
	Frame * new_frame = GetFrame_(video, video.num_processed_frames - 1);
	
	// 2. if not the first frame, track all vehicles between previous frame and new frame
	// 3. update new infos in the vehicle and new frame
	if (new_frame_index != 0)
	{
		Frame * prev_frame = GetFrame_(video, video.num_processed_frames - 2);
		for (int v_idx = 0; v_idx < MAX_VEHICLE_NUM; ++v_idx)
		{
			// skip invisible vehicle
			if (prev_frame->vehicles[v_idx] == nullptr)
				continue;

			// track the vehicle
			Vehicle * vehicle = GetVehicle_(video, v_idx);
			VehicleFrameInfo * new_vf_info = TrackVehicle_(vehicle, new_frame, prev_frame);

			// if track success then add new info to the vehicle and new frame
			if (new_vf_info != nullptr)
			{
				// add new info to the the video, update both vehicle and frame
				if (!AddVFInfo_(video, new_vf_info))
				{
					cout << "Error while adding new vf_info.\n";
					return (false);
				}
			}
		}
	}

	// 4. detect new vehicles in all lanes, and add new vehicles and their infos to video
	if (!FindAndAddNewVehicles_(video))
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
    InitVideo_(video);
    
	// read the input video
	const string video_file("video.txt");
	if (!ReadVideoRawData_(video, video_file))
	{
		return (-1);
		cout << "Error while reading. Please check 'video.txt' file\n";
	}

	// analyze the video and print the information frame by frame
	for (int frame_index = 0; frame_index < video.num_frames; ++frame_index)
	{
		if (!ProcessNextFrame_(video))
		{
			cout << "Error while processing frame: " << frame_index
                 << ". Please check 'ProcessFrame' function\n";
			return (-1);
		}
		PrintFrameInfo_(video, frame_index);
	}
	cout << endl;
    

	// print vehicle information
	for (int vehicle_index = 0; vehicle_index < video.num_vehicles; ++vehicle_index)
		PrintVehicleInfo_(video, vehicle_index);
	cout << endl;

	// calculate the average speed in this video
	cout << "The average speed of this road: " << AverageRoadSpeed_(video) << "\n";

	// clean video with all the memory allocated
	CleanVideo_(video);
	return (0);
}
