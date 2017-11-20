class SnakeDirection
{
	friend class SnakeGame;

public:

	SnakeDirection(int i, int j);

private:
	int x;
	int y;
	void set(int i, int j);
};

SnakeDirection::SnakeDirection(int i, int j)
{
	set(i, j);
}

void SnakeDirection::set(int i, int j)
{
	x = i;
	y = j;
}
