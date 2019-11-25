#include <chrono>

vector<Point> generate_rand_points(int n){

	vector<Point> result;
	vector<float> v1;
	vector<float> v2;

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	
	default_random_engine generator(seed);
	for (int i = 0; i < n*2; i++){
		 // rd() provides a random seed
		uniform_real_distribution<float> distribution(0,1);

		double number = distribution(generator);

		double rounded = round(10. * number) / 10.;

		//cout << rounded << endl;
		if (i % 2 == 0) v1.push_back(rounded);
		else v2.push_back(rounded);

		distribution.reset();
	}

	
	for (unsigned i = 0; i < v1.size(); i ++){
		Point p(v1[i], v2[i]);
		result.push_back(p);
	}

	return result;
}

bool intersection_a(Interval a, Interval c){
	if (a.min < c.min && c.min < a.max && a.min < c.max && c.max < a.max){
		return true;
	}
	else if (a.min < c.min && c.min < a.max && a.max < c.max){
		return true;
	}

	else if (c.min < a.min && a.min < c.max && c.max < a.max){
		return true;
	}

	else{
		return false;
	}
}

bool intersection_c(Interval a, Interval c){
	if (c.min < a.min && a.min < c.max && c.min < a.max && a.max < c.max){
		return true;
	}
	else if (c.min < a.min && a.min < c.max && c.max < a.max){
		return true;
	}

	else if (a.min < c.min && c.min < a.max && a.max < c.max){
		return true;
	}

	else{
		return false;
	}
}

bool intersection(Interval a, Interval c){
	if (intersection_a(a,c) || intersection_c(a,c)){
		return true;
	}
	else{
		return false;
	}
}

Rectangle get_rectangle(BSPNode* t){
	Interval x(t->reg.p_reference.x, t->reg.p_reference.x + t->reg.len_x);
	Interval y(t->reg.p_reference.y, t->reg.p_reference.y + t->reg.len_y);
	return Rectangle(x,y);
}

//returns if an intersection occurs between two Rectangles
bool intersection(Rectangle rec1, Rectangle rec2){
	if (intersection(rec1.x,rec2.x) && intersection(rec1.y, rec2.y)){
		return true;
	}
	else{
		return false;
	}
}

bool inside_rectangle(Rectangle rec, Point &p){
	if (rec.x.min <= p.x && p.x <= rec.x.max){
		if (rec.y.min <= p.y && p.y <= rec.y.max){
			return true;
		}
		else{
			return false;
		}
	}
	else{ return false;}
}
