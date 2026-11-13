#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>


const double tolerance = 1e-6;
const double PI = 3.141592653589793;




struct Point {
	double x;
	double y;
	Point(double x, double y);

};


struct Object {

	std::vector<Point> points;
	std::vector<Point> convex;
	Point center_position;
	Point velocity;

	Object();

	void update_position();

	void load_position(std::string path);
	void load_points(std::string path);
	void jarvis_convex();
	void quickhull_convex();
	void quickhull_recur(Point A, Point B, std::vector <Point> points);
	void convex_fix();
	
	

};




struct Missile {

	double time;
	Point base_position;
	Point velocity;
	bool draw = false;
	void update_position(double t);
	Missile(double t, Point pos, Point vel);

};



struct Collision {

	double time;
	Point position;
	bool draw = false;
	Collision(double t, Point pos);
};

struct Mesh {

	std::vector<Object*> objects;
	std::vector<Missile> missiles;
	std::vector<Collision> collisions;
	
	void create_object(std::string path, std::string path2);
	void load_missiles(std::string path);
	void update_collision(Collision& col, Point vector, double time);
	void check_collision();

};






int side_check(Point p1, Point p2, Point p3);
double distance(Point p1, Point p2, Point p3);
double length(Point a, Point b);
void vector_change(Point& p, Point vector);
Point crossing(Point A, Point B, Point C, Point D);
