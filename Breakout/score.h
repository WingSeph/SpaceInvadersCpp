class Score
{
private:
	int i_Score;

public:
	Score()
	{
		i_Score = 0;
	}
	~Score() {}
	
	int GetScore() { return(i_Score); }
	void AddScore(int _Score) { i_Score += _Score; }
};