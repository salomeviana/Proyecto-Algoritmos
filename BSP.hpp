#ifndef __BSP__
#define __BSP__

#include <iostream>
#include <vector>

using namespace std;

struct Point{
	float x;
	float y;
	Point(){
		x = 0;
		y = 0;
	}
	Point(float a, float b){
		x = a;
		y = b;
	}
	void operator=(Point &other){
		this->x = other.x;
		this->y = other.y;
	}
	
};

ostream& operator<<(ostream& out, Point &p){
	out << "(" << p.x << " , " << p.y << ")" << endl;
	return out;
}

struct Region{
	Point p_reference;
	float len_x;
	float len_y;
	Region(){ p_reference.x = 0; p_reference.y = 0; len_x = 1; len_y = 1;}
	Region(Point pr, float lx, float ly){
		p_reference = pr;
		len_x = lx;
		len_y = ly;
	}
};

struct BSPNode{
	Region reg;
	vector<Point> p_list = {};
	BSPNode* parent;
	BSPNode* left;
	BSPNode* right;
};

struct Interval{
	float min;
	float max;
};

class BSP{
	private:
		
		float precision;

		void partition_x(BSPNode* &t);
		void partition_y(BSPNode* &t);
		void partition_helper(BSPNode* &t);
		void partition();
		BSPNode* find_point(BSPNode* t, Point P);
		BSPNode* insert_node(BSPNode* &t, BSPNode* parent);
		BSPNode* remove_node(BSPNode* &t);
		int height(BSPNode* t) const;
		int size(BSPNode* t) const;
		void destroy_recursive();
		pair<vector<Point>, vector<Point>> def_points_x(BSPNode* &t);
		pair<vector<Point>, vector<Point>> def_points_y(BSPNode* &t);


	public:
		BSPNode* root;
		BSP(){root = nullptr; precision = 0.1;}
		BSP(Region region, vector<Point> points);
		~BSP(){};
		int height() const;
		int size() const;
		void remove_point(Point p);
		vector<Point> scan_region( Interval x_interval, Interval y_interval);
		Region find_point_region(Point P);
};


#include "BSP.cpp"

#endif