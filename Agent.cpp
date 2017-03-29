#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "Agent.h"
using namespace std;

// constructor function
Agent::Agent(int num_states, int num_actions)
// member initializer list
:	number_of_states_(num_states),
	number_of_actions_(num_actions){

		// construct the Q table
		Q_table_ = new double*[num_states];
		for(int i = 0; i < num_states; i++){
			Q_table_[i] = new double[num_actions];
		}

		// construct the policy_
		policy_ = new int [num_states];
}

// SelectAction function
void Agent::SelectAction(){
	// generate random number between 1 and 100
	int random_number = rand()%100;

	if(random_number < (100*epsilon_)){
		// select random action
		SelectRandomAction();
	} else{
		// select action according to policy_
		SelectPolicyAction();
	}
}

// SelectRandomAction function
void Agent::SelectRandomAction(){
	// initialize placeholder for the random action
	int random_action;
	
	// generate random number between 1 and the number of actions
	random_action = rand()%number_of_actions_;

	// set the random áction
	SetActionIndex(random_action);
}

// SelectPolicyAction function
void Agent::SelectPolicyAction(){
	// find the action index with the highest Q-value for the current state
	int max_Q_action_index = GetMaxQActionIndex(state_index_);

	// the policy_ action is equal to the index of the maximal Q_value of the current state
	int policy_action = max_Q_action_index;

	// set the policy_ aciont
	SetActionIndex(policy_action);
}

// CalculateTemporalDifference function
double Agent::CalculateTemporalDifference(int new_state_index, int reward){

	// initialize required variables
	int max_Q_action_index;	
	double temporal_difference, max_Q_value_new_state, Q_value_current_state;

	// max_a Q(s',a')
	max_Q_action_index = GetMaxQActionIndex(new_state_index);
	max_Q_value_new_state = Q_table_[new_state_index][max_Q_action_index];

	// Q(s,a)
	Q_value_current_state = Q_table_[state_index_][action_index_];
	
	// calculate temporal difference
	temporal_difference = reward + gamma_*max_Q_value_new_state - Q_value_current_state;

	return temporal_difference;
}

// GetMaxQActionIndex function
int Agent::GetMaxQActionIndex(int s_index){
	// initialise the max_Q_action index as the first element
	int max_Q_action_index = 0;

	// loop over all colums in the Q-table, starting at the second element
	for(int i = 1; i < number_of_actions_; i++){
		if(Q_table_[s_index][i] > Q_table_[s_index][max_Q_action_index]){
			max_Q_action_index = i;
		}
	}
	return max_Q_action_index;
}

// UpdateQTable_ function
void Agent::UpdateQTable(int new_state_index, int reward){
	// initialize variables
	double temporal_difference, Q_value_current_state, new_Q_value_current_state; 

	// calculate the temporal difference
	temporal_difference = CalculateTemporalDifference(new_state_index, reward);

	// Q(s,a)
	Q_value_current_state = Q_table_[state_index_][action_index_]; 

	// Q'(s,a) = Q(s,a) + alhpa*TD
	new_Q_value_current_state = Q_value_current_state + alpha_*temporal_difference;

	// store the new Q-value Q'(s,a)
	UpdateQValue(state_index_, action_index_, new_Q_value_current_state);
}

// UpdateQValue function
void Agent::UpdateQValue(int state, int action, double Q_value){
	// update the Q_table
	this->Q_table_[state][action] = Q_value;
}

// UpdatePolicy function
void Agent::UpdatePolicy(){
	// loop over all states in the Q_table_
	for(int i = 0; i < number_of_states_; i++){
		// save the index of the axtion with the highest Q-value per state as the policy_
		policy_[i] = GetMaxQActionIndex(i);
	}
}

// UpdateAgentParamters function
void Agent::UpdateAgentParameters(int current_episode){
	// placeholder variable
	double current_epsilon;

	// calculate the current epsilon
	current_epsilon = CalculateEpsilon(current_episode);

	// set the current epsilon
	SetEpsilon(current_epsilon);
}

// UpdateAgent function
double Agent::CalculateEpsilon(int current_episode){
	// placeholder variable
	double current_epsilon;
	double sigma = number_of_episodes_/8;
;
	// calculate the current epsilon
	current_epsilon = epsilon_zero_*exp(-current_episode/sigma);

	return current_epsilon;
}

// GetActionIndex function
int Agent::GetActionIndex(){
	int action;
	action = this->action_index_;
}

// SetAlpha function
void Agent::SetAlpha(double alpha){
	// set alpha
	this->alpha_ = alpha;
}

// SetGamma function
void Agent::SetGamma(double gamma){
	// set gamma
	this->gamma_ = gamma;
}

// SetEpsilon function
void Agent::SetEpsilon(double epsilon){
	// set epsilon
	this->epsilon_ = epsilon;
}

// SetEpsilonZero function
void Agent::SetEpsilonZero(double epsilon_zero){
	// set epsilon zero
	this->epsilon_zero_ = epsilon_zero;
}

// SetNumberOfEpisodes function
void Agent::SetNumberOfEpisodes(int number_of_episodes){
	// set new number of episodes
	this->number_of_episodes_ = number_of_episodes;
}

// SetActionIndex function
void Agent::SetActionIndex(int action_index){
	// set epsilon
	this->action_index_ = action_index;
}

// SetStateIndex function
void Agent::SetStateIndex(int state_index){
	// set the state index
	this->state_index_ = state_index;
}


// PrintQTable function
void Agent::PrintQTable(){
	// loop over all states
	for(int i = 0; i < number_of_states_; i++){
		// loop over all actions
		for(int j = 0; j < number_of_actions_; j++){

			cout << Q_table_[i][j] << "\t";
		}
		cout << endl;
	}
}

// PrintPolicy function
void Agent::PrintPolicy(){
	// print header
	cout << "state index:\t"  << "action index:" << endl;

	// loop over all state indexes
	for(int i = 0; i < number_of_states_; i++){
		cout << i << "\t" << policy_[i] << endl;
	}
}

// PrintMaxQValuePerState
void Agent::PrintMaxQValuePerState(int grid_width, int grid_height){
	// set the decimal precision
	std::cout << std::fixed;
    std::cout << std::setprecision(2);

    // initialise placeholder values
	int current_state_index, current_state_max_Q_index;

	// loop over the hight, from top to bottom
	for(int i = (grid_height-1); i >= 0; i--){

		// loop over the width, from left to right
		for(int j = 0; j < grid_width; j++){

			// find the state index of the current cell
			current_state_index = number_of_states_ - (grid_width*(grid_height - i))  + j;  

			// find and print the action index of the maximal Q-value of this state 
			current_state_max_Q_index = GetMaxQActionIndex(current_state_index);
			cout << Q_table_[current_state_index][current_state_max_Q_index] << "\t";
		}
		cout << endl;
	}
}


// deconstructor function
Agent::~Agent(){
}