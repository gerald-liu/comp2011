/*
 *		 File: structure.h
 * Created on: Nov 1, 2017
 *     Author: Yao Yao (yyaoag@cse.ust.hk)
 *       Note: Do NOT modify this file
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#define ROWS 9              // number of rows of each frame
#define COLS 30             // number of column of each frame
#define LANE_NUM 4          // number of lanes
#define MAX_SPEED 8         // the maximum speed of the vehicle
#define MAX_VEHICLE_NUM 50  // the maximum number of vehicles that will appear in one video



struct Video;
struct Frame;
struct Vehicle;
struct VehicleFrameInfo;

struct Video
{
    int num_frames;
    char*** raw_data;

    int num_processed_frames;
    Frame * first_frame;

    int num_vehicles;
    Vehicle * vehicles[MAX_VEHICLE_NUM];
};

struct Frame
{
	int index;
	char** image;

	int num_vehicles;
	Vehicle * vehicles[MAX_VEHICLE_NUM];

	Frame * next_frame;
};

struct Vehicle
{
    int index;
    int num_visible_frames;
    VehicleFrameInfo * first_frame_info;
};

struct VehicleFrameInfo
{
    int vehicle_index; 
    int frame_index;
    int position[2];
    double speed;

    VehicleFrameInfo * next_frame_info;
};

/******************** 9 functions to be implemented ********************/
Frame * GetFrame(const Video & video, const int frame_index);

Vehicle * GetVehicle(const Video & video, const int vehicle_index);

VehicleFrameInfo * GetVFInfo(const Vehicle * vehicle, const int frame_index);

bool InitializeNewFrame(Video & video);

VehicleFrameInfo * TrackVehicle(const Vehicle * vehicle, const Frame * current_frame, const Frame * prev_frame);

bool AddVFInfo(Video & video, VehicleFrameInfo * vehicle_frame_info);

bool FindAndAddNewVehicles(Video & video);

double AverageRoadSpeed(Video & video);

void CleanVideo(Video & video);

/******************** 9 correct implementations ********************/
Frame * GetFrame_(const Video & video, const int frame_index);

Vehicle * GetVehicle_(const Video & video, const int vehicle_index);

VehicleFrameInfo * GetVFInfo_(const Vehicle * vehicle, const int frame_index);

bool InitializeNewFrame_(Video & video);

VehicleFrameInfo * TrackVehicle_(const Vehicle * vehicle, const Frame * current_frame, const Frame * prev_frame);

bool AddVFInfo_(Video & video, VehicleFrameInfo * vehicle_frame_info);

bool FindAndAddNewVehicles_(Video & video);

double AverageRoadSpeed_(Video & video);

void CleanVideo_(Video & video);

/******************** 4 helper functions ********************/
void InitVideo_(Video& video);

void PrintFrameInfo_(const Video & video, const int frame_index);

void PrintFrameInfo1_(const Video & video, const Frame * frame);

void PrintVehicleInfo_(Video & video, const int vehicle_idx);

void PrintVehicleInfo1_(Video & video, const Vehicle * vehicle);

bool ReadVideoRawData_(Video & video, const string & video_file);

#endif	// STRUCTURE_H_
