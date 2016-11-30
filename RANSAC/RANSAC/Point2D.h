#pragma once
class Point2D
{
private : 
	double x;
	double y;

public:
	Point2D(int x0 = 0, int y0 = 0)
	{
		x = x0;  
		y = y0;
	};

	double getX() { return x; }
	double getY() { return y; }
	void setX(double x0) { x = x0; }
	void setY(double y0) { y = y0; }

	friend ostream & operator<<(ostream & flux, const Point2D pt)
	{
		flux << "[" << pt.x << ";" << pt.y << "]";
		return flux;
	}
	~Point2D() {} ;
};

