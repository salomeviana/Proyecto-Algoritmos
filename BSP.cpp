// holi loquix como estas?
// queria decirte que estas muy loquix de la tusta 
// y queeeee siii

BSP::BSP(Region region, vector<Point> points){
	BSPNode* tree = new BSPNode;
	tree->parent = nullptr;
	tree->left = nullptr;
	tree->right = nullptr;
	tree->reg = region;
	for (unsigned i = 0; i<points.size(); i++){
		tree->p_list.push_back(points[i]);
	}
	root = tree;
	partition();
	//cout << "puta madre" << endl;
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


void BSP::partition(){

	partition_x(root);
	partition_helper(root);
	//partition_helper(root->right);
}

void BSP::partition_helper(BSPNode* &t){
	
	if (t->p_list.size()==1){
		cout << "caso base" << endl;
	}

	else if (t->left == nullptr && t->right == nullptr){
		cout << "ni mierda pa el enemigo" << endl;
	}

	else if (t->left == nullptr && t->right != nullptr){
		partition_y(t);
		partition_x(t->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}

	else if (t->left != nullptr && t->right == nullptr){
		partition_y(t);
		partition_x(t->left);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
	}

	else{
		partition_y(t);
		partition_x(t->left);
		partition_x(t->right);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}
}

//AL REVES
/*void BSP::partition_helper(BSPNode* &t){
	
	if (t->p_list.size()==1){
		cout << "caso base" << endl;
	}

	else if (t->left == nullptr && t->right == nullptr){
		cout << "ni mierda pa el enemigo" << endl;
	}

	else if (t->left == nullptr && t->right != nullptr){
		partition_y(t);
		partition_x(t->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}

	else if (t->left != nullptr && t->right == nullptr){
		partition_y(t);
		partition_x(t->left);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
	}

	else{
		partition_y(t);
		partition_x(t->left);
		partition_x(t->right);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}
}*/

//FINAL AL REVES

/*void BSP::partition_helper(BSPNode* &t){
	
	if (t->p_list.size()==1){
		cout << "caso base" << endl;
	}

	else if (t->left == nullptr && t->right == nullptr){
		cout << "ni mierda pa el enemigo" << endl;
	}

	else if (t->left == nullptr && t->right != nullptr){
		partition_y(t);
		partition_x(t->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}

	else if (t->left != nullptr && t->right == nullptr){
		partition_y(t);
		partition_x(t->left);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
	}

	else{
		partition_y(t);
		partition_x(t->left);
		partition_x(t->right);
		partition_helper(t->left->left);
		partition_helper(t->left->right);
		partition_helper(t->right->left);
		partition_helper(t->right->right);
	}
}*/	