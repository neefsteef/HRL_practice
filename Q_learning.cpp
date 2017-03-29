#include <iostream>
#include <fstream>
#include "Environment.h"
#include "Agent.h"
#include "Q_learning.h"
#include <stdlib.h>
using namespace std;

// constructor function
Q_learning::Q_learning(Agent& ao, Environment& eo, int num_episodes)
// member initializer list
:	agent_object(ao),
	environment_object(eo),
	number_of_episodes_(num_episodes){

	// construct the reward per_episode
	reward_per_episode_ = new int [num_episodes];

	// pass the number of episodes to the agent object
	agent_object.SetNumberOfEpisodes(num_episodes);
}

// Learn function
void Q_learning::Learn(){
	// initialize states and actions
	int current_state, new_state, action, reward, episode_end;

	// loop over all episodes
	for (int i = 0; i < number_of_episodes_; i++){
		// reset the environment at the start of every episode
		environment_object.ResetEnvironment();
		agent_object.UpdateAgentParameters(i+1);
		SetTotalReward(0);

		// get the current state, which is equal agents initialization location
		current_state = environment_object.GetStateIndex();

		// pass the state to the agent
		agent_object.SetStateIndex(current_state);

		// while the episode is not finished/agent is not at the goal state
		do{
			// select and retrieve the agents action for the current state
			agent_object.SelectAction();
			action = agent_object.GetActionIndex();

			// apply the action to the environment, observe new state and reward
			environment_object.ApplyAction(action);
			reward = environment_object.GetReward();
			new_state = environment_object.GetStateIndex();
			
			// add reward to total reward
			AddReward(reward);

			// update the Q_table with the new state and the reward
			agent_object.UpdateQTable(new_state, reward);
			
			// set the new state as the current state
			agent_object.SetStateIndex(new_state);

			// check if the episode is complete
			episode_end = environment_object.GetEpisodeEnd();

		}while(episode_end != 1);

		// update the policy after every episode
		agent_object.UpdatePolicy();

		// save the reward per episode
		reward_per_episode_[i] = total_reward_;
	}

	// save the reward per episode
	SaveRewardPerEpisode();	
}

// SaveRewardPerEpisode function
void Q_learning::SaveRewardPerEpisode(){
	// open the file stream
	ofstream output_file("reward_per_episode.txt");

	// loop over all episodes
	for(int i = 0; i < number_of_episodes_; i++){
		// write the reward per episode
		output_file << i + 1 << " " << reward_per_episode_[i] << endl;
	}
}

// AddReward function
void Q_learning::AddReward(int reward){
	// add the reward
	int total_reward = total_reward_ + reward;

	// set the total reward
	SetTotalReward(total_reward);
}

// SetTotalReward function
void Q_learning::SetTotalReward(int total_reward){
	// add the reward
	this->total_reward_ = total_reward;
}

// PlotRewardPerEpisode function
void Q_learning::PlotRewardPerEpisode(){
	// open a pipe to gnuplot
    FILE *GNUPipe = popen("gnuplot -persist", "w");
	fprintf(GNUPipe, "reset\n");

	// set window number
	//fprintf(GNUPipe, "set term x11 1 \n");
	fprintf(GNUPipe, "set  terminal wxt enhanced font 'Helvetica,10' persist \n");

	// set title, labels, grid and legend/key
	fprintf(GNUPipe, "set title 'Cumulative reward per episode' \n");
	fprintf(GNUPipe, "set ylabel 'Cumulative reward' \n");
	fprintf(GNUPipe, "set xlabel 'Episode [-]' \n");
	fprintf(GNUPipe, "set grid \n");
	fprintf(GNUPipe, "set key inside r b reverse box Left\n");
	fprintf(GNUPipe, "set xrange[%d:%d] \n", 1, number_of_episodes_);

	// set line styles
	fprintf(GNUPipe, "set style line 1 lc rgb 'blue' \n");
	fprintf(GNUPipe, "set style line 2 lc rgb 'black' \n");

	// specify plot settings
	fprintf(GNUPipe, "plot 'reward_per_episode.txt' u 1:2 ls 1 title 'Data' ,\
	 					   'reward_per_episode.txt' u 1:2 ls 2 smooth bezier title 'Bezier interpolation'\n");

	// plot the results
	fflush(GNUPipe);
	
	// exit GNU interface
	fprintf(GNUPipe,"exit \n");

	// wait for character input to close the pipe, such that interaction with plot is possible
	//getchar();

	// close the pipe
	fclose(GNUPipe);
}


// deconstructor function
Q_learning::~Q_learning(){
}
