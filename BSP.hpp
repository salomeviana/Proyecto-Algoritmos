#ifndef __BSP__
#define __BSP__

#include <iostream>
#include <vector>
#include <stdexcept>

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

	bool operator==(Point &other){
		if (this->x == other.x && this->y == other.y){
			return true;
		}
		else{
			return false;
		}
	}
	
};

ostream& operator<<(ostream& out, Point &p){
	out << "(" << p.x << " , " << p.y << ")";
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
	Interval(){min = 0; max = 1;}
	Interval(float mn, float mx){
		min = mn;
		max = mx;
	}

	//pair<Interval, Interval> split_interval(Interval i1, Interval i2);
};

ostream& operator<<(ostream& out, Interval &inter){
	out << "[" << inter.min << " , " << inter.max << "]";
	return out;
}

struct Rectangle{
	Interval x;
	Interval y;
	Rectangle(){x = Interval(0,1); y = Interval(0,1);}
	Rectangle(Interval x_int, Interval y_int){
		x = x_int;
		y = y_int;
	}
	void operator=(Rectangle &other){
		this->x = other.x;
		this->y = other.y;
	}
};

ostream& operator<<(ostream& out, Rectangle &rec){
	out << rec.x << " x " << rec.y;
	return out;
}

class BSP{
	private:
		
		float precision;

		void partition_x(BSPNode* &t); //checked
		void partition_y(BSPNode* &t); //checked
		void partition_helper(BSPNode* &t); //checked
		void partition_helper_left(BSPNode* &t); //checked
		void partition_helper_right(BSPNode* &t); //checked
		void partition(); //checked

		bool left_son(BSPNode* &t); //checked
		bool right_son(BSPNode* &t); //checked

		BSPNode* find_point(BSPNode* t, Point &p); //checked
		BSPNode* find_point_x(BSPNode* t, Point &p);//checked
		BSPNode* find_point_y(BSPNode* t, Point &p);//checked

		BSPNode* insert_node(BSPNode* &t, BSPNode* parent);
		BSPNode* remove_node(BSPNode* &t);
		int height(BSPNode* t) const; //checked
		int size(BSPNode* t) const; //checked
		void destroy_recursive(BSPNode* &t);
		pair<vector<Point>, vector<Point>> def_points_x(BSPNode* &t); //checked
		pair<vector<Point>, vector<Point>> def_points_y(BSPNode* &t); //checked
		void display_node(BSPNode *t, int count); //checked
		float covered_length_x(BSPNode* &t); //checked
		float covered_length_y(BSPNode* &t); //checked

		vector<Point> scan_region( Interval x_interval, Interval y_interval, BSPNode* &t);
		


	public:
		BSPNode* root;
		BSP(){root = nullptr; precision = 0.5;} //checked
		BSP(Region region, vector<Point> points, float prec); //checked
		~BSP(); 
		int height() const; //checked
		int size() const; //checked
		void remove_point(Point &p); //checked
		vector<Point> scan_region( Interval x_interval, Interval y_interval);
		Rectangle find_point_region(Point &p);//checked
		void display(); //checked



};


#include "BSP.cpp"

#endif