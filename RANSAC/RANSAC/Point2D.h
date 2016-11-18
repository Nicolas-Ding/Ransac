#pragma once
class Point2D
{
private : 
	int x;
	int y;

public:
	Point2D(int x0 = 0, int y0 = 0)
	{
		x = x0;  
		y = y0;
	};

	int getX() { return x; }
	int getY() { return y; }
	int setX(int x0) { x = x0; }
	int setY(int y0) { y = y0; }
	~Point2D();
};

