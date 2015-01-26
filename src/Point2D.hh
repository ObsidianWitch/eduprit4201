#ifndef POINT2D_HH
#define POINT2D_HH

#include <iostream>

namespace my {

    struct Point2D {
        Point2D() {}

        Point2D(int row, int col) {
            this->row = row;
            this->col = col;
        }

        bool operator!=(const Point2D& p) const {
            return (row != p.row) || (col != p.col);
        }

        bool operator>= (const Point2D &b) const {
            return (row >= b.row) && (col >= b.col);
        }

        bool operator<= (const Point2D &b) const {
            return (row <= b.row) && (col <= b.col);
        }

        int row, col;
    };

    std::ostream& operator<<(std::ostream& ostr, const Point2D& p) {
        return ostr << '(' << p.row << ',' << p.col << ')';
    }

} // end of namespace my

#endif // POINT2D_HH
