#include <iostream>
#include "Environment.h"
using namespace std;

// constructor fuction
Environment::Environment(int num_x_cells, int num_y_cells)
// member initializer list
:	grid_width_(num_x_cells),
	grid_height_(num_y_cells){
}

// ApplyAction function
void Environment::ApplyAction(int world_action){
	// update the agents location
	UpdateAgentLocation(world_action);

	// calcualte the reward_ for the transition
	CalculateReward();

	// check if the episode is ended
	CheckEpisodeEnd();
}

// CalculateReward function
void Environment::CalculateReward(){
	// define reward_ according to agents position
	if(agent_x_position_ == goal_x_position_ && agent_y_position_ == goal_y_position_){
		// goal reached
		this->reward_ = 0;
	}else{
		// not yet at goal
		this->reward_ = -1;
	}
}

// UpdateAgentLocation function
void Environment::UpdateAgentLocation(int world_action){
	// placeholder variable
	int new_position;

	switch(world_action){
		// move up
		case 0:
		new_position = agent_y_position_ + 1; 
		if(new_position < 0 || new_position > grid_height_-1){
			// do nothing
		}else{
			SetAgentGridPosition(agent_x_position_, new_position);
		}
		break;

		// move down
		case 1:
		new_position = agent_y_position_ - 1; 
		if(new_position < 0 || new_position > grid_height_-1){
			// do nothing
		}else{
			SetAgentGridPosition(agent_x_position_, new_position);
		}
		break;

		// move left
		case 2:
		new_position = agent_x_position_ - 1; 
		if(new_position < 0 || new_position > grid_width_-1){
			// do nothing
		}else{
			SetAgentGridPosition(new_position, agent_y_position_);
		}
		break;
		
		// move right
		case 3:
		new_position = agent_x_position_ + 1; 
		if(new_position < 0 || new_position > grid_width_-1){
			// do nothing
		}else{
			SetAgentGridPosition(new_position, agent_y_position_);
		}
	}
}

// ResetEnvironment function
void Environment::ResetEnvironment(){
	// set the agent grid position back to the start position
	SetAgentGridPosition(agent_start_x_position_, agent_start_y_position_);
}


// CheckEpisodeEnd function
void Environment::CheckEpisodeEnd(){
	// check if goal position is reached
	if(agent_x_position_ == goal_x_position_ && agent_y_position_ == goal_y_position_){
		this->episode_end_ = 1;
	} else{
		this->episode_end_ = 0;
	}
}

// UpdateState function
void Environment::UpdateState(){
	// placeholder for state
	int s;	

	// calculate the state index, starting at zero in the bottom left corner
	// and increasig row wise from bottom to top
	s = agent_x_position_ + (agent_y_position_)*grid_width_;
	
	// set the state
	this->state_index_ = s;
}

// SetAgentGridPosition function
void Environment::SetAgentGridPosition(int grid_x_position, int grid_y_position){
	// set the class variables
	this->agent_x_position_ = grid_x_position;
	this->agent_y_position_ = grid_y_position;

	// update the state
	UpdateState();
}

// SetAgentStartGridPosition function
void Environment::SetAgentStartGridPosition(int grid_x_position, int grid_y_position){
	// set the class variables
	this->agent_start_x_position_ = grid_x_position;
	this->agent_start_y_position_ = grid_y_position;
}

// SetGoalGridPosition function
void Environment::SetGoalGridPosition(int grid_x_position, int grid_y_position){
	// set the class variables
	this->goal_x_position_ = grid_x_position;
	this->goal_y_position_ = grid_y_position;
}

// GetStateIndex fuction
int Environment::GetStateIndex(){
	// get the state
	int s = this->state_index_;
	return s;	
}

// GetReward function
int Environment::GetReward(){
 	// get the reward
 	int r = this->reward_;
	return r;		
}

// ApplyAction function
int Environment::GetEpisodeEnd(){
	// get the episode_end_ booloean
	int episode_e = this->episode_end_;
	return episode_e;
}

// PrintGrid function
void Environment::PrintGrid(){
	// loop over the height of the grid, top down
	for(int i = (grid_height_-1); i >= 0; i--){
		// loop over the width of the grid, left to right
		for(int j = 0; j < grid_width_; j++){

			if(i == agent_y_position_ && j == agent_x_position_){
				cout << " A ";
			}else if(i == goal_y_position_ && j == goal_x_position_){
				cout << " G ";
			}else{
				cout << " 0 ";
			}
		}
		cout << endl;
	}
}

// deconstructer function
Environment::~Environment(){

}


