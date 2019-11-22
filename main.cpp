#include "BSP.hpp"

int main(){

	Point myp;
	Region myreg;
	//Interval salosinter;
	Point p0(0.15,0.6);

	Point p1(0.25,0.75);
	Point p2(0.25,0.25);
	Point p3(0.75,0.25);
	Point p4(0.75,0.75);

	Point p5(0.4,0.56);
	Point p6(0.6,0.6);
	Point p7(0.2,0.9);
	Point p8(0.9,0.9);
	Point p9(0.6,0.1);
	Point p10(0.2,0.56);

	vector<Point> points = {p1,p2,p3,p4};
	
	BSP mybsp(myreg, points, 0.5);


	/*Rectangle rec2 = mybsp.find_point_region(p0);
	cout << rec2 << endl;

	cout <<  "++++++++++++++++++++++++++++" << endl;*/
	//mybsp.display();

	Rectangle rec1 = mybsp.find_point_region(p2);
	cout << rec1 << endl;

	mybsp.remove_point(p2);

	cout << endl << "--------------------------" << endl << endl;
	//mybsp.display();


	//Rectangle rec = mybsp.find_point_region(p2);
	//cout << rec << endl;

	//Rectangle myrec = get_rectangle(mybsp.root->right->right);
	//cout << myrec << endl;

	/*Interval i1(1,5);
	Interval i2(3,7);
	pair<Interval, Interval> inters = split_interval(i1,i2);
	cout << get<0>(inters) << endl;
	cout << get<1>(inters) << endl;*/
	//mybsp.display();

	/*Rectangle root_rec = get_rectangle(mybsp.root->right);
	Rectangle root_l_p_rec = get_rectangle(mybsp.root->right->right->parent);
	cout << root_rec << endl;
	cout << root_l_p_rec << endl;
*/
	//cout << endl << "size = " << mybsp.size() << " and height = "<< mybsp.height() << endl;
	//cout << p1 << endl;
	//Rectangle rec_of_p1 = mybsp.find_point_region(p1);
	//cout << rec_of_p1 << endl;	

	return 0;
}
