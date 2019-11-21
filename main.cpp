#include "BSP.hpp"

int main(){

	Point myp;
	Region myreg;
	//Interval salosinter;
	Point p0(0.15,0.6);
	Point p1(0.26,0.75);
	Point p2(0.25,0.25);
	Point p3(0.75,0.25);
	Point p4(0.75,0.75);


	//cout << p1 << endl;

	vector<Point> points = {p0,p1,p2,p3,p4};
	
	BSP mybsp(myreg, points);

	cout << "left" << endl;
	for (unsigned i = 0; i<mybsp.root->left->p_list.size(); i++){
		cout << mybsp.root->left->p_list[i] << endl;
	}

	cout << endl << "right" << endl;
	for (unsigned i = 0; i<mybsp.root->right->p_list.size(); i++){
		cout << mybsp.root->right->p_list[i] << endl;
	}

	cout << endl << "el que yo uant" << endl;
	for (unsigned i = 0; i<mybsp.root-> right-> left-> right-> p_list.size(); i++){
		cout << mybsp.root-> right-> left-> right-> p_list[i] << endl;
	}

	return 0;
}
