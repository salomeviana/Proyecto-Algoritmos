pair <Interval,Interval> split_interval(Interval i1, Interval i2){
	//TENER CUIDADO CON LOS PUNTOS QUE ESTAN EN LOS 2 INTERVALOS!!!
	if (i1.min < i2.min && i2.min < i1.max && i1.max < i2.max){
		Interval result1(i2.min, i1.max);
		Interval result2(i1.max, i2.max);
		return make_pair(result1, result2);
	}
	
	//if (i2.min < i1.min && i1.min < i2.max && i2.max < i1.max)
	else{
		Interval result1(i2.min, i1.min);
		Interval result2(i1.min, i2.max);
		return make_pair(result1, result2);
	}
}

Rectangle get_rectangle(BSPNode* t){
	Interval x(t->reg.p_reference.x, t->reg.p_reference.x + t->reg.len_x);
	Interval y(t->reg.p_reference.y, t->reg.p_reference.y + t->reg.len_y);
	return Rectangle(x,y);
}

BSP::BSP(Region region, vector<Point> points, float prec){
	BSPNode* tree = new BSPNode;
	tree->parent = nullptr;
	tree->left = nullptr;
	tree->right = nullptr;
	tree->reg = region;
	precision = prec;
	tree->p_list = points;
	root = tree;
	partition();
}

void BSP::destroy_recursive(BSPNode* &t){
	if (t != nullptr){
		destroy_recursive(t->left);
		destroy_recursive(t->right);
		delete t;
		cout << "holi" << endl;
	}
}

BSP::~BSP(){
	destroy_recursive(root);
}
// PARTITION X

void BSP::partition_x(BSPNode* &t){
	BSPNode* left = new BSPNode;
	BSPNode* right = new BSPNode;

	//Assigning Parent
	t->left = left;
	t->right = right;

	//Assigning left
	left->parent = t;
	left->left = nullptr;
	left->right = nullptr;

	//Assigning right
	right->parent= t;
	right->left = nullptr;
	right->right = nullptr;

	//Defining left region
	left->reg.p_reference = t->reg.p_reference;
	left->reg.len_x = t->reg.len_x/2;
	left->reg.len_y = t->reg.len_y;

	//Defining right region
	right->reg.p_reference.x = t->reg.p_reference.x + t->reg.len_x/2;
	right->reg.p_reference.y = t->reg.p_reference.y;
	right->reg.len_x = t->reg.len_x/2;
	right->reg.len_y = t->reg.len_y;

	pair< vector<Point>, vector<Point>> sons_points = def_points_x(t);

	vector<Point> left_points = get<0>(sons_points);
	vector<Point> right_points = get<1>(sons_points);

	for (unsigned i = 0; i<left_points.size(); i++){
		left->p_list.push_back(left_points[i]);
	}

	for (unsigned i = 0; i<right_points.size(); i++){
		right->p_list.push_back(right_points[i]);
	}

	if (left_points.empty() && right_points.empty()){
		t->left = nullptr;
		t->right = nullptr;
		delete left;
		delete right;
	}

	else if (left_points.empty() && 1 - right_points.empty() == 1){
		t->left = nullptr;
		t->right = right;
		delete left;
	}

	else if  (right_points.empty() && 1 - left_points.empty() == 1){
		t->right = nullptr;
		t->left = left;
		delete right;
	}

	else{
		t->right = right;
		t->left = left;
	}

	//t->right = right;
	//t->left = left;
}



pair <vector<Point>, vector<Point>> BSP::def_points_x(BSPNode* &t){
	vector<Point> parent_vec = t->p_list;
	vector<Point> left_vec;
	vector<Point> right_vec;

	for (unsigned i = 0; i<parent_vec.size(); i++){
		if (parent_vec[i].x <= t->reg.p_reference.x + t->reg.len_x/2){
			left_vec.push_back(parent_vec[i]);
		}
		else{ right_vec.push_back(parent_vec[i]);}
	}

	return make_pair(left_vec, right_vec);
}


//PARTITION Y

void BSP::partition_y(BSPNode* &t){
	BSPNode* left = new BSPNode;
	BSPNode* right = new BSPNode;

	//Assigning left
	left->parent = t;
	left->left = nullptr;
	left->right = nullptr;

	//Assigning right
	right->parent= t;
	right->left = nullptr;
	right->right = nullptr;

	//Defining left region
	left->reg.p_reference = t->reg.p_reference;
	left->reg.len_x = t->reg.len_x;
	left->reg.len_y = t->reg.len_y/2;

	//Defining right region
	right->reg.p_reference.x = t->reg.p_reference.x;
	right->reg.p_reference.y = t->reg.p_reference.y  + t->reg.len_y/2;;
	right->reg.len_x = t->reg.len_x;
	right->reg.len_y = t->reg.len_y/2;

	pair< vector<Point>, vector<Point>> sons_points = def_points_y(t);

	vector<Point> left_points = get<0>(sons_points);
	vector<Point> right_points = get<1>(sons_points);

	for (unsigned i = 0; i<left_points.size(); i++){
		left->p_list.push_back(left_points[i]);
	}

	for (unsigned i = 0; i<right_points.size(); i++){
		right->p_list.push_back(right_points[i]);
	}

	t->right = right;
	t->left = left;

	if (left_points.empty() && right_points.empty()){
		t->left = nullptr;
		t->right = nullptr;
		delete left;
		delete right;
	}

	else if (left_points.empty() && 1 - right_points.empty() == 1){
		t->left = nullptr;
		t->right = right;
		delete left;
	}

	else if  (right_points.empty() && 1 - left_points.empty() == 1){
		t->right = nullptr;
		t->left = left;
		delete right;
	}

	else{
		t->right = right;
		t->left = left;
	}
}

pair <vector<Point>, vector<Point>> BSP::def_points_y(BSPNode* &t){
	vector<Point> parent_vec = t->p_list;
	vector<Point> left_vec;
	vector<Point> right_vec;

	for (unsigned i = 0; i<parent_vec.size(); i++){
		if (parent_vec[i].y <= t->reg.p_reference.y + t->reg.len_y/2){
			left_vec.push_back(parent_vec[i]);
		}
		else{ right_vec.push_back(parent_vec[i]);}
	}

	return make_pair(left_vec, right_vec);
}

float BSP::covered_length_x(BSPNode* &t){
	float result;
	result = t->reg.len_x;
	return result;
}

float BSP::covered_length_y(BSPNode* &t){
	float result;
	result = t->reg.len_y;
	return result;
}

void BSP::partition(){

	partition_x(root);
	partition_helper(root);
}

void BSP::partition_helper(BSPNode* &t){

	if (t->left != nullptr){
			partition_helper_left(t);
		}

	if (t->right != nullptr){
			partition_helper_right(t);
		}
}


void BSP::partition_helper_left(BSPNode* &t){
	partition_y(t->left);
	//check if 
	if (t->left->left != nullptr){
		if (covered_length_x(t->left->left) > precision && covered_length_y(t->left->left) > precision){
			partition_x(t->left->left);
			partition_helper(t->left->left);
		}
		else{
			//cout << "not for t->left->left" << endl;
		}
	}
	
	if (t->left->right != nullptr){
		if (covered_length_x(t->left->right) > precision && covered_length_y(t->left->right) > precision){
			partition_x(t->left->right);
			partition_helper(t->left->right);
		}
		else{
			//cout << "not for t->left->right" << endl;
		}	
	}
}

void BSP::partition_helper_right(BSPNode* &t){
	partition_y(t->right);

	if (t->right->left != nullptr){
		if (covered_length_x(t->right->left) > precision && covered_length_y(t->right->left) > precision){
			partition_x(t->right->left);
			partition_helper(t->right->left);
		}
		else{
			//cout << "not for t->right->left" << endl;
		}
	}
	
	if (t->right->right != nullptr){
		if (covered_length_x(t->right->right) > precision && covered_length_y(t->right->right) > precision){
			partition_x(t->right->right);
			partition_helper(t->right->right);
		}
		else{
			//cout << "not for t->right->right" << endl;
		}
	}
}

void BSP::display_node(BSPNode *t, int count){
	if (t != nullptr){
		count ++;
		display_node(t->left, count);
		cout << endl <<  "(" << count -1 << ")" << "[";
		for (unsigned i = 0; i<t->p_list.size(); i++){
			cout << t->p_list[i] << ", ";
		}
		cout << "]" << endl;
		display_node(t->right, count);
	}
}

void BSP::display(){
	display_node(root, 0);
}

int BSP::size(BSPNode * t) const{
	if (t == nullptr){
		return 0;
	}

	else if (t->left == nullptr && t->right == nullptr){
		return 1;
	}

	else{
		return 1 + size(t->left) + size(t->right);
	}
}

int BSP::size() const{
	return size(root);
}

int BSP::height(BSPNode *t) const{
	if (t == nullptr){
		return 0;
	}

	else if (t->left == nullptr && t->right == nullptr){
		return 0;
	}

	else{
		return 1 + max(height(t->left), height(t->right));
	}
}

int BSP::height() const{
	return height(root);
}

BSPNode* BSP::find_point_x(BSPNode* t, Point &p){
	if (t->left == nullptr && t->right == nullptr){
		for (unsigned i = 0; i<t->p_list.size(); i++){
			if (p == t->p_list[i]){
				return t;
			}
		}
		return nullptr;
	}

	else if (p.x <= t->reg.p_reference.x + t->reg.len_x/2){
		if (t->left != nullptr){
			return find_point_y(t->left, p);
		}
		else{
			return nullptr;
		}
	}

	else{
		if (t->right != nullptr){
			return find_point_y(t->right, p);
		}
		else{
			return nullptr;
		}
	}

	//return nullptr;
}

BSPNode* BSP::find_point_y(BSPNode* t, Point &p){
	if (t->left == nullptr && t->right == nullptr){
		for (unsigned i = 0; i<t->p_list.size(); i++){
			if (p == t->p_list[i]){
				return t;
			}
		}
		return nullptr;
	}

	else if (p.y <= t->reg.p_reference.y + t->reg.len_y/2){
		if (t->left != nullptr){
			return find_point_x(t->left, p);
		}
		else{
			return nullptr;
		}
	}

	else{
		if (t->right != nullptr){
			return find_point_x(t->right, p);
		}
		else{
			return nullptr;
		}
	}
}

BSPNode* BSP::find_point(BSPNode* t, Point &p){
	return find_point_x(t, p);
}

Rectangle BSP::find_point_region(Point &p){
	BSPNode* result_node = find_point(root, p);

	if (result_node != nullptr){
		Interval x(result_node->reg.p_reference.x, result_node->reg.p_reference.x + result_node->reg.len_x);
		Interval y(result_node->reg.p_reference.y, result_node->reg.p_reference.y + result_node->reg.len_y);
		Rectangle result(x,y);
		return result;
	}
	else{
		throw runtime_error("Attempting to find unexisting Point\n");
	}
}

bool BSP::left_son(BSPNode* &t){
	if (t->parent->left == t){
		return true;
	}
	else{
		return false;
	}
}

bool BSP::right_son(BSPNode* &t){
	return 1 - left_son(t);
}

void BSP::remove_point(Point &p){
	cout << "Removing " << p << endl;
	BSPNode* p_node = find_point(root, p);
	if (p_node != nullptr){
		while (p_node != nullptr){
			int idx;
			for (unsigned i = 0; i<p_node->p_list.size(); i++){
				if (p == p_node->p_list[i]){
					idx = i;
					break;
				}
			}


			p_node->p_list.erase(p_node->p_list.begin() + idx-1);

			if (p_node->p_list.empty()){
				if(left_son(p_node)){
					p_node->parent->left = nullptr;
					//delete p_node;
				}
				else{
					p_node->parent->right = nullptr;
					//delete p_node;
				}
			}

			p_node = p_node->parent;
		}
	}
	else{
		throw runtime_error("Attempting to remove unexisting Point\n");
	}
}



/*vector<Point> scan_region(Interval x, Interval y, BSPNode* &t){
	Rectangle t_rec = get_rectangle(t);
	if ( t_rec.x.min > x.min && t_rec.x.max < x.max){
		if (t_rec.y.min > y.min && t_rec.y.max < y.max){
			return t->parent->p_list;
		}
		else if( t_rec.y.min < y.min && y.min < t_rec.max && t_rec.y.max < y.max){
			pair <Interval, Interval> intervals = split_interval(Interval(t_rec.y.min, t_rec.y.max), y);
			scan_region(x, get<0>(intervals), t->left);
			scan_region(x, get<1>(intervals), t->right);
		}

		else 
	}
}*/