#ifndef Q_LEARNING_H
#define Q_LEARNING_H

class Q_learning
{
public:
	// constructor
	Q_learning(Agent& agent_object, Environment& environment_object, int number_of_episodes);

	// public function
	void Learn();
	void PlotRewardPerEpisode();

	// deconstructor
	~Q_learning();

private:
	// class variables
	int number_of_episodes_;
	int total_reward_;

	// arrays
	int* reward_per_episode_;

	// objects: agent and environment
	Agent& agent_object;
	Environment& environment_object;

	// private functions
	void SaveRewardPerEpisode();
	void AddReward(int reward);
	void SetTotalReward(int total_reward);
};

#endif