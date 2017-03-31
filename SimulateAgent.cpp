#include <iostream>
#include <fstream>
#include <vector>
#include "Environment.h"
#include "Agent.h"
#include <unistd.h>
using namespace std;


int main(){
	int number_of_states = 500;
	int number_of_actions = 6;

	Agent agent_object(number_of_states, number_of_actions);
	Environment environment_object;

	// declare other variables
	double alpha = 0.25	, gamma = 0.8, epsilon = 0.0;

	// set other variables; 
	agent_object.SetAlpha(alpha);
	agent_object.SetGamma(gamma);
	agent_object.SetEpsilonZero(epsilon);


	agent_object.LoadPolicyFromFile();

	int current_state, new_state, action, reward, episode_end;

	int j = 0;

	// while the episode is not finished/agent is not at the goal state
	j = 0;
	environment_object.ResetEnvironment();
	
	do{
		// get the current state, which is equal agents initialization location
		current_state = environment_object.GetStateIndex();

		// pass the state to the agent
		agent_object.SetStateIndex(current_state);

		// select and retrieve the agents action for the current state
		agent_object.SelectPolicyAction();
		action = agent_object.GetActionIndex();

		// apply the action to the environment, observe new state and reward
		environment_object.ApplyAction(action);
		reward = environment_object.GetReward();
		new_state = environment_object.GetStateIndex();
				
		// set the new state as the current state
		agent_object.SetStateIndex(new_state);

		j++;

		cout << reward << endl;

		environment_object.PrintGrid();
		usleep(500000);

	}while(j < 150);



}