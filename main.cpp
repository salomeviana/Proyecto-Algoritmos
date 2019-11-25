//NOTA: COMPILAR CON C++17!

#include "BSP.hpp"

int main(){

	Point myp;
	Region myreg;


	Point p1(0.25,0.75);
	Point p2(0.25,0.25);
	Point p3(0.75,0.25);
	Point p4(0.75,0.75);

	Point p5(0.4,0.56);
	Point p6(0.6,0.6);
	Point p7(0.2,0.9);
	Point p8(0.9,0.9);
	Point p9(0.6,0.2);
	Point p10(0.2,0.56);

	
	//float precision;
	//cout << "Enter the precision you need " << endl;
	//cin >> precision;

	cout << "Using not randomized vector" << endl << endl;
	vector<Point> points = {p1,p2,p3};

	//cout << "Using randomized vector" << endl;
	//vector<Point> points = generate_rand_points(1000);
	

	cout << "Using Constructor with parameters" << endl;
	BSP mybsp(myreg, points, 0.25);

	//cout << "Using Defect Constructor" << endl;
	//BSP mybsp;

	
	//Inserting Points

	cout << "Tree size = " << mybsp.size() << endl;
	cout << "Tree height = " << mybsp.height() << endl << endl;

	mybsp.insert_point(p4);
	mybsp.insert_point(p5);
	mybsp.insert_point(p6);
	mybsp.insert_point(p7);
	mybsp.insert_point(p8);
	//mybsp.insert_point(p2);
	//mybsp.insert_point(p3);
	//mybsp.insert_point(p1);

	cout << endl << "Tree size = " << mybsp.size() << endl;
	cout << "Tree height = " << mybsp.height() << endl << endl;

	mybsp.display();

	cout << endl;


	Interval ix(0.2, 0.5);
	Interval iy(0.2, 0.75);

	cout << "Scanning region " << ix << " x " << iy << endl << endl; 

	vector<Point> scanned_points = mybsp.scan_region(ix, iy);

	for (unsigned i = 0; i<scanned_points.size(); i++){
		cout << scanned_points[i] << endl;
	}
	
	return 0;
}