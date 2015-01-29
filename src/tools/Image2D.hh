#ifndef IMAGE2D_HH
#define IMAGE2D_HH

#include <cstdlib>
#include <iostream>
#include <vector>
#include "tools/Image.hh"
#include "tools/Point2D.hh"
#include "tools/Box2D.hh"

namespace my {

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

        p_iterator_type pIterator() const {
            return p_iterator_type(domain());
        }

        n_iterator_type nIterator() const {
            return n_iterator_type();
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
