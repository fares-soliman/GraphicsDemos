#include "AABBTree.h"
#include "insert_box_into_box.h"




AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
    int axis = 0;
    auto comparator = [&axis](const std::shared_ptr<Object>& elem1,
        const std::shared_ptr<Object>& elem2)
    {
        return(elem1->box.center()[axis] < elem2->box.center()[axis]);
    };
	
	if (num_leaves == 1) {
		left = objects[0];
		right = nullptr;
		insert_box_into_box(objects[0]->box, box);
	}
	else if (num_leaves == 2) {
		left = objects[0];
		right = objects[1];
		insert_box_into_box(objects[0]->box, box);
		insert_box_into_box(objects[1]->box, box);
	}
	else {
        auto x_max = std::max_element(objects.begin(), objects.end(), comparator);
        auto x_min = std::min_element(objects.begin(), objects.end(), comparator);
        double x_range = std::abs((*x_max)->box.center()[0] - (*x_min)->box.center()[0]);
        axis = axis + 1;

        auto y_max = std::max_element(objects.begin(), objects.end(), comparator);
        auto y_min = std::min_element(objects.begin(), objects.end(), comparator);
        double y_range = std::abs((*y_max)->box.center()[1] - (*y_min)->box.center()[1]);
        axis = axis + 1;

        auto z_max = std::max_element(objects.begin(), objects.end(), comparator);
        auto z_min = std::min_element(objects.begin(), objects.end(), comparator);
        double z_range = std::abs((*z_max)->box.center()[2] - (*z_min)->box.center()[2]);

        std::vector<double> ranges{ x_range, y_range, z_range };
        axis = std::max_element(ranges.begin(), ranges.end()) - ranges.begin();

        std::vector<std::shared_ptr<Object>> obj(objects);
        std::sort(obj.begin(), obj.end(), comparator);

      
        auto start = obj.begin();
        auto mid = obj.begin() + num_leaves / 2;
        auto end = obj.end();

        left = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(start, mid), this->depth + 1);
        right = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(mid, end), this->depth + 1);

        insert_box_into_box(this->left->box, this->box);
        insert_box_into_box(this->right->box, this->box);
	}
	


}
