#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment
{
public:
	// constructor
	Environment(int num_x_cells, int num_y_cells);

	// class functions
	void ApplyAction(int world_action);
	void ResetEnvironment();

	// get functions
	int GetStateIndex();
	int GetReward();
	int GetEpisodeEnd();

	// set functions
	void SetAgentGridPosition(int grid_x_position, int grid_y_position);
	void SetAgentStartGridPosition(int grid_x_position, int grid_y_position);
	void SetGoalGridPosition(int grid_x_position, int grid_y_position);

	// printing and plotting functions
	void PrintGrid();

	// deconstructor
	~Environment();

private:
	// class variables
	int grid_width_;
	int grid_height_;
	int agent_x_position_;
	int agent_y_position_;
	int agent_start_x_position_;
	int agent_start_y_position_;
	int goal_x_position_;
	int goal_y_position_;
	int state_index_;
	int reward_;
	int episode_end_;

	// private functions
	void CheckEpisodeEnd();
	void UpdateState();
	void CalculateReward();
	void UpdateAgentLocation(int world_action);
};

#endif