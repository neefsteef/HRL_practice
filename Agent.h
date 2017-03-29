#ifndef AGENT_H
#define AGENT_H

class Agent
{
public:
	// constructor
	Agent(int number_of_states, int number_of_actions);

	// class functions
	void SelectAction();
	void UpdatePolicy();
	void UpdateQTable(int new_state_index, int reward);
	void UpdateAgentParameters(int current_episode);

	// get functions
	int GetActionIndex();

	// set functions
	void SetStateIndex(int tate_index);
	void SetActionIndex(int action_index);
	void SetNumberOfEpisodes(int number_of_episodes);
	void SetAlpha(double alpha);
	void SetGamma(double gamma);
	void SetEpsilon(double epsilon);
	void SetEpsilonZero(double epsilon_zero);

	// printing and plotting functions
	void PrintPolicy();
	void PrintQTable();
	void PrintMaxQValuePerState(int grid_width, int grid_height);

	// deconstructor
	~Agent();

private:
	// class variables
	int number_of_states_;
	int number_of_actions_;
	int action_index_;
	int state_index_;
	
	// learning hyper parameters
	int number_of_episodes_;
	double gamma_;
	double alpha_;
	double epsilon_zero_;
	double epsilon_;

	// arrays
	int* policy_;
	double** Q_table_;

	// class functions
	void SelectRandomAction();
	void SelectPolicyAction();
	void UpdateQValue(int state_index, int action_index, double new_Q_value);
	int GetMaxQActionIndex(int s_index);
	double CalculateTemporalDifference(int new_state_index, int reward);
	double CalculateEpsilon(int current_episode);
};


#endif