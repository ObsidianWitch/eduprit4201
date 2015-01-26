#ifndef NEIGHB2D_ITERATOR_HH
#define NEIGHB2D_ITERATOR_HH

#include <vector>
#include "Point2D.hh"

namespace my {

    /**
     * Iterator over the set of neighbors of a 2D point.
     */
    class Neighb2DIterator {
    public:
        Neighb2DIterator() {
            delta_.push_back(Point2D(-1, 0));
            delta_.push_back(Point2D(0, -1));
            delta_.push_back(Point2D(0, 1));
            delta_.push_back(Point2D(1, 0));
        }

        void center_at(const Point2D& p) {
            p_ = p;
        }

        void start() {
            i_ = 0;
        }

        bool is_valid() const {
            return i_ < 4;
        }

        void next() {
            i_ += 1;
        }

        operator Point2D() const {
            Point2D n;
            n.row = p_.row + delta_[i_].row;
            n.col = p_.col + delta_[i_].col;

            return n;
        }

    private:
        std::vector<Point2D> delta_;
        unsigned i_; // current index in delta_
        Point2D p_; // center is p_
    };

} // end of namespace my

#endif // NEIGHB2D_ITERATOR_HH
