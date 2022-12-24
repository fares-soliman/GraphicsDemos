#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
    leaf_pairs.clear(); 
    if (!box_box_intersect(rootA->box, rootB->box))
        return; 

    std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> intersect_queue; 
    intersect_queue.push_back(std::make_pair(rootA, rootB));

    while (!intersect_queue.empty()) {
        auto nodes = intersect_queue.front();
        std::shared_ptr<AABBTree> element1 = std::dynamic_pointer_cast<AABBTree>(nodes.first);
        std::shared_ptr<AABBTree> element2 = std::dynamic_pointer_cast<AABBTree>(nodes.second);
        intersect_queue.pop_front();

        if (!element1 && !element2) {
            leaf_pairs.push_back(std::make_pair(nodes.first, nodes.second));
        }
        else if (!element1) {
            if (element2->left && box_box_intersect(nodes.first->box, element2->left->box))
                intersect_queue.push_back(std::make_pair(nodes.first, element2->left));
            if (element2->right && box_box_intersect(nodes.first->box, element2->right->box))
                intersect_queue.push_back(std::make_pair(nodes.first, element2->right));
        }
        else if (!element2) {
            if (element1->left && box_box_intersect(nodes.second->box, element1->left->box))
                intersect_queue.push_back(std::make_pair(element1->left, nodes.second));
            if (element1->right && box_box_intersect(nodes.second->box, element1->right->box))
                intersect_queue.push_back(std::make_pair(element1->right, nodes.second));
        }
        else {
            if (element1->left && element2->left && box_box_intersect(element1->left->box, element2->left->box))
                intersect_queue.push_back(std::make_pair(element1->left, element2->left));
            if (element1->left && element2->right && box_box_intersect(element1->left->box, element2->right->box))
                intersect_queue.push_back(std::make_pair(element1->left, element2->right));
            if (element1->right && element2->left && box_box_intersect(element1->right->box, element2->left->box))
                intersect_queue.push_back(std::make_pair(element1->right, element2->left));
            if (element1->right && element2->right && box_box_intersect(element1->right->box, element2->right->box))
                intersect_queue.push_back(std::make_pair(element1->right, element2->right));
        }
    }
}
