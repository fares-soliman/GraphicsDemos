#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
    if (ray_intersect_box(ray, this->box, min_t, max_t)) {
        std::shared_ptr<Object> l_d = this->left;
        std::shared_ptr<Object> r_d = this->right;
        double l_t, r_t;

        bool l_hit = this->left ? this->left->ray_intersect(ray, min_t, max_t, l_t, l_d) : false;
        bool r_hit = this->right ? this->right->ray_intersect(ray, min_t, max_t, r_t, r_d) : false;

        if (l_hit && r_hit) {
            if (l_t < r_t) {
                t = l_t;
                descendant = l_d;
            }
            else {
                t = r_t;
                descendant = r_d;
            }
        }
        else if (l_hit || r_hit) {
            t = l_hit ? l_t : r_t;
            descendant = l_hit ? l_d : r_d;
            return true;
        }
        else {
            return false;
        }
        return true;
    }
    return false;
}

