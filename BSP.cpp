#include "main_functions.cpp"

BSP::BSP(){
	root = nullptr; precision = 0.5;
}

BSP::BSP(Region region, vector<Point> points, float prec){
	BSPNode* tree = new BSPNode;
	tree->type = 0;
	tree->parent = nullptr;
	tree->left = nullptr;
	tree->right = nullptr;
	tree->reg = region;
	precision = prec;
	tree->p_list = points;
	root = tree;
	if (prec < 1){ //does partition if precision is less than 1
		partition_4x(root);
	}
}

void BSP::destroy_recursive(BSPNode* &t){
	if (t != nullptr){ 
		destroy_recursive(t->left);
		destroy_recursive(t->right);
		delete t;
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
	left->type = 1;

	//Assigning right
	right->parent= t;
	right->left = nullptr;
	right->right = nullptr;
	right->type = 1;

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

	left->p_list = left_points;
	right->p_list = right_points;

	t->right = right;
	t->left = left;

	if (left_points.empty()){
		t->left = nullptr;
		delete left;
	}

	if (right_points.empty()){
		t->right = nullptr;
		delete right;
	}
}

pair <vector<Point>, vector<Point>> BSP::def_points_x(BSPNode* &t){
	//only for x partition / t->type = 1
	vector<Point> parent_vec = t->p_list; //parent's points
	vector<Point> left_vec; //left son's points
	vector<Point> right_vec; //right son's points

	for (unsigned i = 0; i<parent_vec.size(); i++){
		if (parent_vec[i].x <= t->reg.p_reference.x + t->reg.len_x/2){//checks if should go left
			left_vec.push_back(parent_vec[i]);
		}
		else{ right_vec.push_back(parent_vec[i]);}
	}

	return make_pair(left_vec, right_vec); //returns points of left and points of right
}


//PARTITION Y

void BSP::partition_y(BSPNode* &t){
	BSPNode* left = new BSPNode;
	BSPNode* right = new BSPNode;

	//Assigning left
	left->parent = t;
	left->left = nullptr;
	left->right = nullptr;
	left->type = 2;

	//Assigning right
	right->parent= t;
	right->left = nullptr;
	right->right = nullptr;
	right->type = 2;

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

	left->p_list = left_points;
	right->p_list = right_points;

	t->right = right;
	t->left = left;

	if (left_points.empty()){
		t->left = nullptr;
		delete left;
	}

	if (right_points.empty()){
		t->right = nullptr;
		delete right;
	}
}

pair <vector<Point>, vector<Point>> BSP::def_points_y(BSPNode* &t){
	//only for y partition / t->type = 2
	vector<Point> parent_vec = t->p_list; //parent's points
	vector<Point> left_vec; //left son's points
	vector<Point> right_vec; //right son's points

	for (unsigned i = 0; i<parent_vec.size(); i++){
		if (parent_vec[i].y <= t->reg.p_reference.y + t->reg.len_y/2){ //checks if should go left 
			left_vec.push_back(parent_vec[i]);
		}
		else{ right_vec.push_back(parent_vec[i]);}
	}

	return make_pair(left_vec, right_vec); //returns points of left and points of right
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

//PARTITIONING STARTING IN X

void BSP::partition_4x(BSPNode* &t){

	partition_x(t);
	partition_helper_4x(t);
}

void BSP::partition_helper_4x(BSPNode* &t){

	if (t->left != nullptr){ //checks left and does recursion
		partition_helper_left_4x(t);
		}

	if (t->right != nullptr){ //checks right and does recursion
		partition_helper_right_4x(t);
		}
}

void BSP::partition_helper_right_4x(BSPNode* &t){ //does recursion after spliting t->right
	partition_y(t->right);

	if (t->right->left != nullptr){ //recursion on the left
		if (covered_length_x(t->right->left) > precision && covered_length_y(t->right->left) > precision){
			partition_x(t->right->left);
			partition_helper_4x(t->right->left);
		}
	}
	
	if (t->right->right != nullptr){ //recursion on the right
		if (covered_length_x(t->right->right) > precision && covered_length_y(t->right->right) > precision){
			partition_x(t->right->right);
			partition_helper_4x(t->right->right);
		}
	}
}


void BSP::partition_helper_left_4x(BSPNode* &t){ //does recursion after spliting t->left
	partition_y(t->left);

	if (t->left->left != nullptr){ //recursion on the left
		if (covered_length_x(t->left->left) > precision && covered_length_y(t->left->left) > precision){
			partition_x(t->left->left);
			partition_helper_4x(t->left->left);
		}
	}
	
	if (t->left->right != nullptr){ //recursion on the right
		if (covered_length_x(t->left->right) > precision && covered_length_y(t->left->right) > precision){
			partition_x(t->left->right);
			partition_helper_4x(t->left->right);
		}
	}
}



//PARTITIONING STARTING IN Y

void BSP::partition_4y(BSPNode* &t){

	partition_y(t);
	partition_helper_4y(t);
}

void BSP::partition_helper_4y(BSPNode* &t){

	if (t->left != nullptr){ //checks left and does recursion
			partition_helper_left_4y(t);
		}

	if (t->right != nullptr){ //checks right and does recursion
			partition_helper_right_4y(t);
		}
}

void BSP::partition_helper_left_4y(BSPNode* &t){ //does recursion after spliting t->right
	partition_x(t->left);
	
	if (t->left->left != nullptr){ //recursion on the left
		if (covered_length_x(t->left->left) > precision && covered_length_y(t->left->left) > precision){
			partition_y(t->left->left);
			partition_helper_4y(t->left->left);
		}
	}
	
	if (t->left->right != nullptr){ //recursion on the right
		if (covered_length_x(t->left->right) > precision && covered_length_y(t->left->right) > precision){
			partition_y(t->left->right);
			partition_helper_4y(t->left->right);
		}
	}
}

void BSP::partition_helper_right_4y(BSPNode* &t){ //does recursion after spliting t->right
	partition_x(t->right);

	if (t->right->left != nullptr){ //recursion on the left
		if (covered_length_x(t->right->left) > precision && covered_length_y(t->right->left) > precision){
			partition_y(t->right->left);
			partition_helper_4y(t->right->left);
		}
	}
	
	if (t->right->right != nullptr){ //recursion on the right
		if (covered_length_x(t->right->right) > precision && covered_length_y(t->right->right) > precision){
			partition_y(t->right->right);
			partition_helper_4y(t->right->right);
		}
	}
} 


//INORDER TRAVERSAL DISPLAY
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

//determines in which node's son the point is if its a type 1 node
//does recursion with find_point_x
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
}

//determines in which node's son the point is if its a type 2 node
//does recursion with find_point_x
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

//finds point's node given a BSPNode 
BSPNode* BSP::find_point(BSPNode* t, Point &p){
	return find_point_x(t, p);
}


//finds point's region of the partition
Rectangle BSP::find_point_region(Point &p){
	BSPNode* result_node = find_point(root, p);

	if (result_node != nullptr){ //if point in the tree, creates a Rectangle/Region to return 
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
	return !left_son(t);
}


void BSP::remove_point(Point &p){
	cout << "Removing " << p << endl;

	BSPNode* p_node = find_point(root, p);
	if (p_node != nullptr){ //checks if the point is in the tree
		while (p_node != nullptr){ //removes point from every list in the tree
			int idx = -1;
			for (unsigned i = 0; i<p_node->p_list.size(); i++){
				if (p == p_node->p_list[i]){
					idx = i; //gets index of Point to erase
					break;
				}
			}

			if (idx != -1)
				p_node->p_list.erase(p_node->p_list.begin() + idx);	

			BSPNode* par = p_node->parent;

			if (p_node->p_list.empty()){
				if(left_son(p_node)){
					p_node->parent->left = nullptr;
					delete p_node;
				}
				else{
					p_node->parent->right = nullptr;
					delete p_node;
				}
			}

			p_node = par;
		}
	}
	else{
		throw runtime_error("Attempting to remove unexisting Point\n");
	}
//}
}

vector<Point> BSP::scan_region(Interval x, Interval y, BSPNode* &t){
	vector<Point> result;
	Rectangle rec(x,y);
	scan_region_helper(rec, t, result);
	return result;
}

vector<Point> BSP::scan_region(Interval x, Interval y){
	Rectangle rec(x,y);
	vector<Point> pre_result = scan_region(x, y, root);
	vector<Point> result;
	//checks which ones are inside the region 
	for (unsigned i = 0; i<pre_result.size(); i++){
		if (inside_rectangle(rec, pre_result[i])){
			result.push_back(pre_result[i]);
		}
	}
	return result;
}

void BSP::scan_region_helper(Rectangle rec_reference, BSPNode* &t, vector<Point> &result){
	Rectangle t_rec = get_rectangle(t);
	float error = 0.000001;
	rec_reference.x.min += error;
	rec_reference.x.max -= error;
	rec_reference.y.min += error;
	rec_reference.y.max += error;

	if (intersection(rec_reference, t_rec)){ //checks intersection between two Rectangles
		if (t->left != nullptr){ 
			Rectangle t_rec_left = get_rectangle(t->left);
			if(intersection(t_rec_left, rec_reference)){ //recursion with t->left and reference
				scan_region_helper(rec_reference, t->left, result);
			}
		}

		if (t->right != nullptr){
			Rectangle t_rec_right = get_rectangle(t->right);
			if(intersection(t_rec_right, rec_reference)){ //recursion with t->right and reference
				scan_region_helper(rec_reference, t->right, result);
			}
		}

		if (t->right == nullptr && t->left == nullptr){ //the region itself is either the node region or is less than the node region
			for (unsigned i = 0; i<t->p_list.size(); i++){ //pushes region points to result vector
				result.push_back(t->p_list[i]);
			}
		}
	}
}

void BSP::insert_point(Point &p){
	cout << "Inserting " << p << endl;
	if(root == nullptr){
		BSPNode* new_root = new BSPNode;

		new_root -> parent = nullptr;
		new_root -> left = nullptr;
		new_root -> right = nullptr;
		new_root -> type = 0;

		new_root->p_list = {p};

		root = new_root;
		partition_4x(root);
	}

	else{
		BSPNode* p_node = find_point(root, p);
		if (root->left == nullptr && root->right == nullptr){
			root->p_list.push_back(p);
			partition_4x(root);
		}

	
		else if (p_node == nullptr){ //if point is not in the tree
			root->p_list.push_back(p);
			BSPNode* node = find_node_2insert(root, p); // node where to insert the point
			if (node->left != nullptr && node->right == nullptr){ //creating node in the right to create partition for the point
				BSPNode* new_node = new BSPNode;

				new_node->reg.p_reference.x = node->reg.p_reference.x + node->reg.len_x/2;
				new_node->reg.p_reference.y = node->reg.p_reference.y;
				
				if (node->type == 1){
					new_node->reg.len_x = node->reg.len_x;
					new_node->reg.len_y = node->reg.len_y/2;
					new_node->type = 2;
				}
				else{
					new_node->reg.len_x = node->reg.len_x/2;
					new_node->reg.len_y = node->reg.len_y;
					new_node->type = 1;
				}
				
				node->right = new_node;
				new_node->parent = node;

				new_node->left = nullptr;
				new_node->left = nullptr;

				new_node->p_list.push_back(p);

				if (covered_length_y(new_node) > precision){
					partition_y(new_node);
					if (node->type == 1 || node->type == 0){
							
							//if (new_node->left != nullptr){
								if (covered_length_x(new_node->right) > precision && covered_length_y(new_node->right) > precision){
									partition_4x(new_node);
									partition_helper_4x(new_node);
								}
							//}

							/*if (new_node->right != nullptr){
								if (covered_length_x(new_node->right) > precision && covered_length_y(new_node->right) > precision){
									partition_x(new_node->right);
									partition_helper_4x(new_node->right);
								}
							}*/
					}
					else{
						if (new_node->left != nullptr){
							if (covered_length_x(new_node->left) > precision && covered_length_y(new_node->left) > precision){
								partition_x(new_node->left);
								partition_helper_4x(new_node->left);
								}
						}
						
						if (new_node->right != nullptr){
							if (covered_length_x(new_node->right) > precision && covered_length_y(new_node->right) > precision){
								partition_x(new_node->right);
								partition_helper_4x(new_node->right);
							}
						}
						
					}
				}
			}
			else if (node->left == nullptr && node->right != nullptr){ //creating node in the left to create partition for the point
				BSPNode* new_node = new BSPNode;
				new_node->reg.p_reference = node->reg.p_reference;
				
				if (node->type == 1){
					new_node->reg.len_x = node->reg.len_x;
					new_node->reg.len_y = node->reg.len_y/2;
					new_node->type = 2;
				}
				else{
					new_node->reg.len_x = node->reg.len_x/2;
					new_node->reg.len_y = node->reg.len_y;
					new_node->type = 1;
				}
				
				
				node->left = new_node;
				new_node->parent = node;

				new_node->left = nullptr;
				new_node->right =nullptr;


				new_node->p_list.push_back(p);


				if (covered_length_y(new_node) > precision){
						partition_y(new_node);
						if (node->type == 1 || node->type == 0){

							//if (new_node->left != nullptr){
								if (covered_length_x(new_node->left) > precision && covered_length_y(new_node->left) > precision){
									//checks if the precision has been achieved
									partition_4x(new_node);
									partition_helper_4x(new_node);
								}
							//}

							/*if (new_node->right != nullptr){
								if (covered_length_x(new_node->right) > precision && covered_length_y(new_node->right) > precision){
									//checks if the precision has been achieved
									partition_x(new_node->right);
									partition_helper_4x(new_node->right);
								}
							}*/
						}
						else{
							if (new_node->left != nullptr){
								if (covered_length_x(new_node->left) > precision && covered_length_y(new_node->left) > precision){
									//checks if the precision has been achieved
									partition_x(new_node->left);
									partition_helper_4x(new_node->left);
								}
							}

							if (new_node->right != nullptr){
								if (covered_length_x(new_node->right) > precision && covered_length_y(new_node->right) > precision){
									//checks if the precision has been achieved
									partition_x(new_node->right);
									partition_helper_4x(new_node->right);
								}
							}
					}
				}
			}
		}
		else{
			throw runtime_error("Attempting to insert an existing Point\n");
		}
	}

}


BSPNode* BSP::find_node_x_2insert(BSPNode* &t, Point &p){ //finds node in which to insert point if t is of type 1;
	if (t->left == nullptr && t->right == nullptr){
		return t;	
	}

	else if (p.x <= t->reg.p_reference.x + t->reg.len_x/2){
		if (t->left != nullptr){
			t->left->p_list.push_back(p);
			return find_node_y_2insert(t->left, p);
		}
		else{
			return t;
		}
	}

	else{
		if (t->right != nullptr){
			t->right->p_list.push_back(p);
			return find_node_y_2insert(t->right, p);
		}
		else{
			return t;
		}
	}
}

BSPNode* BSP::find_node_y_2insert(BSPNode* &t, Point &p){ //finds node in which to insert point if t is of type 1;
	if (t->left == nullptr && t->right == nullptr){
		return t;	
	}

	else if (p.y <= t->reg.p_reference.y + t->reg.len_y/2){
		if (t->left != nullptr){
			t->left->p_list.push_back(p);
			return find_node_x_2insert(t->left, p);
		}
		else{
			return t;
		}
	}

	else{
		if (t->right != nullptr){ 
			t->right->p_list.push_back(p);
			return find_node_x_2insert(t->right, p);
		}
		else{
			return t;
		}
	}
}

BSPNode* BSP::find_node_2insert(BSPNode* &t, Point &p){ //finds node in which to insert point
	return find_node_x_2insert(t,p);
}