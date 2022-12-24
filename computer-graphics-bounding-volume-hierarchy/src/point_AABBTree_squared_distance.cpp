#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <utility>


bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    struct comparator {
        bool operator() (const std::pair<std::shared_ptr<Object>, double>& a, const std::pair<std::shared_ptr<Object>, double>& b) const
        {
            return a.second > b.second;
        }
    };

    std::priority_queue<std::pair<std::shared_ptr<Object>, double >,
                        std::vector<std::pair<std::shared_ptr<Object>, double > >,
                        comparator >  pq;
    double distance = point_box_squared_distance(query, root->box);
    pq.push(std::pair<std::shared_ptr<Object>, double >(root, distance));
    sqrd = max_sqrd;

    while (!pq.empty()) {
        auto curr_node = pq.top();
        pq.pop();

        if (curr_node.second < sqrd && curr_node.second >= min_sqrd) {
            auto node = std::dynamic_pointer_cast<AABBTree>(curr_node.first);
            if (node == nullptr) {
                sqrd = std::min(sqrd, point_box_squared_distance(query, curr_node.first->box));
                descendant = curr_node.first;
            }
            else {
                if (node->left != nullptr) {
                    pq.push(std::pair<std::shared_ptr<Object>, double >(node->left, point_box_squared_distance(query, node->left->box)));
                }
                if (node->right != nullptr) {
                    pq.push(std::pair<std::shared_ptr<Object>, double >(node->right,point_box_squared_distance(query, node->right->box)));
                }
            }
        }
    }
    if (sqrd >= max_sqrd) {
        return false;
    }
    return true;
}

  ////////////////////////////////////////////////////////////////////////////

