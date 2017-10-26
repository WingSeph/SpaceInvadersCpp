//player bullet fires upward
//enemy bullet fires downward

class Bullet
{
private:
	int BulletSpeed;
	bool DirectionUp;

public:
	Bullet()
	{
		BulletSpeed = 5;
		DirectionUp = true;
	}

	~Bullet(){}
	
	int GetBulletSpeed() { return(BulletSpeed); }
	void SetBulletSpeed(int _BulletSpeed) { DirectionUp = _BulletSpeed; }

	bool GetDirection() { return(DirectionUp); }
	void SetDirection(bool _Direction) { DirectionUp = _Direction; }

};