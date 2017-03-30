#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment
{
public:
	// Constructor
	Environment();

	// Class functions
	void TakeWorldAction(int primitive_action_index);
	void ResetEnvironment();
	void ResetPassenger();

	// get functions
	// int GetStateIndex();
	// int GetReward();
	// int GetEpisodeEnd();

	// Set functions
	void SetAgentGridPosition(std::vector <int> new_agent_grid_position);

	// Printing and plotting
	void PrintGrid();

	// Deconstructor
	~Environment();

private:
	// Cass variables
	// 
	int passenger_location_index_;
	int passenger_goal_location_index_;
	int reward_;

	// Booleans 
	bool wall_crash_;
	bool passenger_in_taxi_;
	bool succesfull_put_;

	// Vector
	std::vector <int> grid_dimensions_;
	std::vector <int> agent_grid_position_;
	std::vector <int> goal_grid_position_;
	std::vector <int> passenger_grid_position_;
	std::vector <int> point_a_grid_position_;
	std::vector <int> point_b_grid_position_;
	std::vector <int> point_c_grid_position_;
	std::vector <int> point_d_grid_position_;
	std::vector<std::vector<int> > wall_grid_position_;

	// Functions
	void CheckWallCrash(int primitive_action_index, std::vector<int> new_position);
	void AttemptGet();
	void AttemptPut();
	void SetPassengerLocation();
	void SetGoalGridPosition();
	void SetPassengerGridPosition();
	void SetPassengerInTaxi(bool);
	void SetWallCrash(bool);
	void SetSuccesfullPut(bool);
};

#endif