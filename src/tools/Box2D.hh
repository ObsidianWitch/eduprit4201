#ifndef BOX2D_HH
#define BOX2D_HH

#include "tools/Point2D.hh"
#include "tools/Neighb2DIterator.hh"

namespace my {

    // Forward declarations
    class Box2DIterator;

    class Box2D {
    public:
        typedef Point2D point_type;
        typedef Box2DIterator p_iterator_type;
        typedef Neighb2DIterator n_iterator_type;

        Box2D(const Point2D& pmin, const Point2D& pmax) {
            pmin_ = pmin;
            pmax_ = pmax;
        }

        Box2D(unsigned nrows, unsigned ncols)
            : pmin_(0,0), pmax_(nrows - 1, ncols - 1)
        {}

        const Point2D& pmin() const {
            return pmin_;
        }

        const Point2D& pmax() const {
            return pmax_;
        }

        unsigned nrows() const {
            return pmax_.row - pmin_.row + 1;
        }

        unsigned ncols() const {
            return pmax_.col - pmin_.col + 1;
        }

        unsigned npoints() const {
            return nrows() * ncols();
        }

        bool has(const point_type& p) const {
            return (p >= pmin_) && (p <= pmax_);
        }

        int index_of(const Point2D& p) const {
            int i = (p.row - pmin_.row) * ncols() + (p.col - pmin_.col);
            return i;
        }

    private:
        Point2D pmin_, pmax_;
    };


    /**
     * Iterator over the set of points contained in a 2D box.
     */
    class Box2DIterator {
    public:
        Box2DIterator(const Box2D& b) : b_(b) {}

        void start() {
            p_ = b_.pmin();
        }

        bool is_valid() const {
            return p_.row <= b_.pmax().row;
        }

        void next() {
            if (not is_valid()){
                std::abort();
            }

            p_.col += 1;
            if (p_.col > b_.pmax().col) {
                p_.row += 1;
                p_.col = b_.pmin().col;
            }
        }

        operator Point2D() const {
            return p_;
        }

    private:
        Box2D b_;
        Point2D p_;
    };

} // end of namespace my

#endif // BOX2D_HH
