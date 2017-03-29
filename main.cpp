#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Environment.h"
#include "Agent.h"
#include "Q_learning.h"
using namespace std;


int main(){
	// pick the seed location
	srand(time(0));

	// ------------------------------------------------------------------------------------
	// --------------------------------Environment settings-------------------------------- 
	// ------------------------------------------------------------------------------------
	// initialize and construct
	int grid_width = 10;
	int grid_height = 10;

	Environment environment_object(grid_width, grid_height);
	
	// agent start grid position
	int agent_start_x_grid_position = 0; 
	int agent_start_y_grid_position = 0;

	// goal grid position
	int goal_x_grid_position = 9;
	int goal_y_grid_position = 9;

	// set the positions
	environment_object.SetAgentStartGridPosition(agent_start_x_grid_position, agent_start_y_grid_position);
	environment_object.SetGoalGridPosition(goal_x_grid_position, goal_y_grid_position);

	// ------------------------------------------------------------------------------------
	// -----------------------------------Agent settings----------------------------------- 
	// ------------------------------------------------------------------------------------
	// initialize and construct
	int number_of_states = grid_width*grid_height;
	int number_of_actions = 4;

	Agent agent_object(number_of_states, number_of_actions);

	// declare other variables
	double alpha = 0.5, gamma = 1.0, epsilon = 1;

	// set other variables; 
	agent_object.SetAlpha(alpha);
	agent_object.SetGamma(gamma);
	agent_object.SetEpsilon(epsilon);

	// ------------------------------------------------------------------------------------
	// --------------------------------Q-Learning settings--------------------------------- 
	// ------------------------------------------------------------------------------------
	// specify number of episodes
	int number_of_episodes = 250;

	// initialize the Q_learing object
	Q_learning Q_object(agent_object, environment_object, number_of_episodes);
	
	// learn
	Q_object.Learn();

	// plot
	Q_object.PlotRewardPerEpisode();

	// print out results
    // agent_object.PrintQTable();
    // agent_object.PrintPolicy();
    agent_object.PrintMaxQValuePerState(grid_width, grid_height);
}