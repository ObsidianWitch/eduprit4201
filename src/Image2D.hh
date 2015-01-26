#ifndef IMAGE2D_HH
#define IMAGE2D_HH

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Point2D.hh"
#include "Neighb2DIterator.hh"

#define for_all(x) for (x.start(); x.is_valid(); x.next())

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

    // ------------------------

    template <typename I>
    struct Image {
        I& exact() {
            return *(I*)(void*)this;
        }

        const I& exact() const {
            return *(const I*)(const void*)this;
        }

        protected:
            Image() {}
    };



    template <typename I> void debug_iota(Image<I>& ima_) {
        I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        unsigned v = 0;
        for_all(p){
            ima(p) = v++;
        }
    }

    template <typename I>
    void data_fill(Image<I>& ima_, typename I::value_type v) {
        I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        for_all(p){
            ima(p) = v;
        }
    }


    template <typename I>
    std::ostream& operator<<(std::ostream& ostr, const Image<I>& ima_) {
        const I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        for_all(p) {
            ostr << p << ':' << ima(p) << ' ';
        }

        return ostr;
    }


    template <typename I>
    void fancy_print(const Image<I>& ima_, const Box2D& b,
        std::ostream& ostr = std::cout)
    {
        const I& ima = ima_.exact();
        Point2D p;
        int& row = p.row;
        int& col = p.col;

        for (row = b.pmin().row; row <= b.pmax().row; row += 1) {
            for (col = b.pmin().col; col <= b.pmax().col; col += 1){
                if (ima.domain().has(p)) {
                    ostr << ima(p) << ' ';
                }
                else {
                    ostr << "  ";
                }
            }

            ostr << std::endl;
        }

        ostr << std::endl;
    }

    // ------------------------

    template <typename T>
    class Image2D : public Image< Image2D<T> > {
    public:
        typedef T value_type;

        typedef Box2D domain_type;
        typedef typename domain_type::point_type point_type;
        typedef typename domain_type::p_iterator_type p_iterator_type;
        typedef typename domain_type::n_iterator_type n_iterator_type;

        /**
         * TODO do it the C++ way :
         *   template <typename U>
         *   using with_value_type = Image2D<U>;
         *
         * example :
         * with I being Image2D<int>
         * ->  typename I::template with_value_type<float>::ret is Image2D<float>
         */
        template <typename U>
        struct with_value_type {
            typedef Image2D<U> ret;
        };

        Image2D(const domain_type& d) :
            d_(d)
        {
            data_.resize(d_.npoints());
        }

        Image2D(unsigned nrows, unsigned ncols) :
            d_(nrows, ncols)
        {
            data_.resize(d_.npoints());
        }

        T& operator()(const point_type& p) {
            if (!d_.has(p)) {
                std::abort();
            }

            int i = d_.index_of(p);
            if (i < 0 || i >= int(data_.size())) {
                std::abort();
            }

            return data_[i];
        }

        T operator()(const point_type& p) const {
            if (!d_.has(p)) {
                std::abort();
            }

            int i = d_.index_of(p);
            if (i < 0 || i >= int(data_.size())) {
                std::abort();
            }

            return data_[i];
        }

        const domain_type& domain() const {
            return d_;
        }

        template <typename U, unsigned n>
        void fill(U (&data)[n]) {
            if (n != domain().npoints()) {
                std::abort();
            }

            Box2DIterator p(domain());
            unsigned i = 0;
            for_all(p) {
                (*this)(p) = data[i++];
            }
        }

        void debug_print(std::ostream& ostr = std::cout) const {
            for (int row = d_.pmin().row; row <= d_.pmax().row; row += 1) {
                for (int col = d_.pmin().col; col <= d_.pmax().col; col += 1) {
                    ostr << this->operator()(Point2D(row, col)) << ' ';
                }

                ostr << std::endl;
            }

            ostr << std::endl;
        }

    private:
        domain_type d_;
        std::vector<T> data_;
    };

    typedef int bool_t;

} // end of namespace my

#endif // IMAGE2D_HH
