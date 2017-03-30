#include <iostream>
#include <vector>
#include <cstdlib>
#include "Environment.h"
using namespace std;

// constructor fuction
Environment::Environment():
// members initialization list
grid_dimensions_(2, 0),
agent_grid_position_(2, 0),
point_a_grid_position_(2, 0),
point_b_grid_position_(2, 0),
point_c_grid_position_(2, 0),
point_d_grid_position_(2, 0),
wall_grid_position_(6, std::vector<int>(2, 0))
{
	// Manually initialize the vector type variables
	grid_dimensions_[0] = 5;
	grid_dimensions_[1] = 5;

	// Positions of points a, b, c and d
	point_a_grid_position_[0] = 0;
	point_a_grid_position_[1] = 0;
	point_b_grid_position_[0] = 0;
	point_b_grid_position_[1] = 4;
	point_c_grid_position_[0] = 3;
	point_c_grid_position_[1] = 0;
	point_d_grid_position_[0] = 4;
	point_d_grid_position_[1] = 4;

	// Specify positions of walls, in this case 6, from left to right
	// and bottom to top
	wall_grid_position_[0][0] = 0;
	wall_grid_position_[0][1] = 0;
	wall_grid_position_[1][0] = 0;
	wall_grid_position_[1][1] = 1;
	wall_grid_position_[2][0] = 1;
	wall_grid_position_[2][1] = 3;
	wall_grid_position_[3][0] = 1;
	wall_grid_position_[3][1] = 4;
	wall_grid_position_[4][0] = 2;
	wall_grid_position_[4][1] = 0;
	wall_grid_position_[5][0] = 2;
	wall_grid_position_[5][1] = 1;

	// Reset the passenger location and goal
	ResetPassenger();
}

// Function to take the primitive action selected in the world
void Environment::TakeWorldAction(int primitive_action_index){
	// Placeholder variable to the new position and 
	// initialize as the current position
	std::vector<int> new_position = agent_grid_position_;

	switch(primitive_action_index){
		// Move up
		case 0:
		// Update the new position
		new_position[1] = agent_grid_position_[1] + 1;

		// Check if agent crashes
		CheckWallCrash(primitive_action_index, new_position);

		if(wall_crash_){
			// Do nothing
		}else{
			SetAgentGridPosition(new_position);
		}
		break;

		// Move down
		case 1:
		// Update the new position
		new_position[1] = agent_grid_position_[1] - 1;

		// Check if agent crashes
		CheckWallCrash(primitive_action_index, new_position);

		if(wall_crash_){
			// Do nothing
		}else{
			SetAgentGridPosition(new_position);
		}
		break;

		// Move left
		case 2:
		// Update the new position
		new_position[0] = agent_grid_position_[0] - 1;

		// Check if agent crashes
		CheckWallCrash(primitive_action_index, new_position);

		if(wall_crash_){
			// Do nothing
		}else{
			SetAgentGridPosition(new_position);
		}
		break;

		// Move right
		case 3:
		// Update the new position
		new_position[0] = agent_grid_position_[0] + 1;

		// Check if agent crashes
		CheckWallCrash(primitive_action_index, new_position);

		if(wall_crash_){
			// Do nothing
		}else{
			SetAgentGridPosition(new_position);
		}
		break;

		// Get the passenger
		case 4:
		AttemptGet();
		break;

		// Put the passenger
		case 5:
		AttemptPut();
		break;
	}

	// Calculate reward
}

// Checks if the current agent position coincides with the passenger location
void Environment::AttemptGet(){
	// Check if agent is at the goal position and passenger is in the taxi
	if(agent_grid_position_[0] == passenger_grid_position_[0] &&
	   agent_grid_position_[1] == passenger_grid_position_[1] &&
	   passenger_in_taxi_ == false){
		SetPassengerInTaxi(true);
	} else{
		SetPassengerInTaxi(false);
	}
}

// Checks if the current agent position coincides with the goal location and
// if the passenger is on board
void Environment::AttemptPut(){
	// Check if agent is at the goal position and passenger is in the taxi
	if(agent_grid_position_[0] == goal_grid_position_[0] &&
	   agent_grid_position_[1] == goal_grid_position_[1] &&
	   passenger_in_taxi_ == true){
		SetSuccesfullPut(true);
		ResetPassenger();
	} else{
		SetSuccesfullPut(false);
	}
}

// Checks if the agent crashes into a wall
void Environment::CheckWallCrash(int primitive_action_index, std::vector<int> new_position){
	// Switch over the primitve action indexes
	switch(primitive_action_index){
		// Move up
		case 0:
		if(new_position[1] >= grid_dimensions_[1]){
			// Crashed in top wall
			SetWallCrash(true);
		} else {
			SetWallCrash(false);
		}
		break;

		// Move down
		case 1:
		if(new_position[1] < 0){
			// Crashed in bottom wall
			SetWallCrash(true);
		}else{
			SetWallCrash(false);
		}
		break;

		// Move left
		case 2:
		if(new_position[0] < 0){
			// Crashed in left wall
			SetWallCrash(true);
		} else{
			// Loop over all free standing walls
			for(int k = 0; k < wall_grid_position_.size(); k++){
				// Check if current position of agent was to the right of a wall
				if(agent_grid_position_[0] == wall_grid_position_[k][0]+1 &&
				   agent_grid_position_[1] == wall_grid_position_[k][1]){
					SetWallCrash(true);
					break;
				} else{
					SetWallCrash(false);
				}
			}
		}
		break;

		// Move right
		case 3:
		if(new_position[0] >= grid_dimensions_[0]){
			// Crashed in right wall
			SetWallCrash(true);
		} else{
			// Loop over all free standing walls
			for(int k = 0; k < wall_grid_position_.size(); k++){
				// Check if current position of agent was to the left of a wall
				if(agent_grid_position_[0] == wall_grid_position_[k][0] &&
				   agent_grid_position_[1] == wall_grid_position_[k][1]){
					SetWallCrash(true);
					break;
				} else{
					SetWallCrash(false);
				}
			}
		}
		// Get passenger
		case 4:
		// Do nothing
		break;

		// Put passenger
		case 5:
		break;
		// Do nothing
	}
}

// Resets the pasenger location and goal to a random position
void Environment::ResetPassenger(){
	// Select a random passenger- and goal location
	do{
		passenger_location_index_ = rand()%3;
		passenger_goal_location_index_ = rand()%3;
	} while(passenger_location_index_ == passenger_goal_location_index_);

	SetPassengerGridPosition();
	SetGoalGridPosition();
	SetPassengerInTaxi(false);
}

// Sets the passenger location
void Environment::SetPassengerGridPosition(){
	switch (passenger_location_index_){
		case 0:
		// Set passenger position to point a
		this->passenger_grid_position_ = point_a_grid_position_;
		break;
		
		case 1:
		// Set passenger position to point b
		this->passenger_grid_position_ = point_b_grid_position_;
		break;
		
		case 2:
		// Set passenger position to point c
		this->passenger_grid_position_ = point_c_grid_position_;
		break;

		case 3:
		// Set passenger position to point d
		this->passenger_grid_position_ = point_d_grid_position_;
	}
}

// Sets the goal location
void Environment::SetGoalGridPosition(){
	switch (passenger_goal_location_index_){
		case 0:
		// Set passenger position to point a
		this->goal_grid_position_ = point_a_grid_position_;
		break;
		
		case 1:
		// Set passenger position to point b
		this->goal_grid_position_ = point_b_grid_position_;
		break;
		
		case 2:
		// Set passenger position to point c
		this->goal_grid_position_ = point_c_grid_position_;
		break;

		case 3:
		// Set passenger position to point d
		this->goal_grid_position_ = point_d_grid_position_;
	}
}

// set the agent grid position and updates the state
void Environment::SetAgentGridPosition(std::vector <int> new_agent_grid_position){
	// set the class variables
	this->agent_grid_position_ = new_agent_grid_position;

	// update the state
	// UpdateState();
}

void Environment::SetWallCrash(bool wall_crash){
	this->wall_crash_ = wall_crash;
}

void Environment::SetSuccesfullPut(bool succesfull_put){
	this->succesfull_put_ = succesfull_put;
}

void Environment::SetPassengerInTaxi(bool passenger_in_taxi){
	this->passenger_in_taxi_= passenger_in_taxi;
}


// prints out the grid in the terminal
void Environment::PrintGrid(){
	// initialise print_wall boolean
	int print_wall;

	// loop over the height of the grid, top down
	for(int i = (grid_dimensions_[1]-1); i >= 0; i--){
		// loop over the width of the grid, left to right
		for(int j = 0; j < grid_dimensions_[0]; j++){
			// print grid cell contents
			if(i == agent_grid_position_[1] && j == agent_grid_position_[0]){
				// print agent
				cout << " A ";
			} else if(i == passenger_grid_position_[1] && j == passenger_grid_position_[0] &&
				      passenger_in_taxi_ == 0){
				// print passenger
				cout << " P ";
			} else if(i == goal_grid_position_[1] && j == goal_grid_position_[0]){
				// print goal
				cout << " G ";
			} else if(i == point_a_grid_position_[1] && j == point_a_grid_position_[0]){
				// print a
				cout << " a ";
			} else if(i == point_b_grid_position_[1] && j == point_b_grid_position_[0]){
				// print b
				cout << " b ";
			} else if(i == point_c_grid_position_[1] && j == point_c_grid_position_[0]){
				// print c
				cout << " c ";
			} else if(i == point_d_grid_position_[1] && j == point_d_grid_position_[0]){
				// print d
				cout << " d ";
			} else {
				// print 0
				cout << " 0 ";
			}

			// check if current cell has wall to the right
			print_wall = 0;
			for(int k = 0; k < wall_grid_position_.size(); k++){
				if(i == wall_grid_position_[k][1] && j == wall_grid_position_[k][0]){
					print_wall = 1;
					break;
				} 
			}

			// print walls
			if(print_wall == 1){
				cout << "|";
			} else{
				cout << " ";
			}
		}
		cout << endl;
	}
}

// deconstructer function
Environment::~Environment(){
}


