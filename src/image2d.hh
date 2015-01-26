#ifndef IMAGE2D_HH
#define IMAGE2D_HH

#include <cstdlib>
#include <iostream>
#include <vector>

#define for_all(x) for (x.start(); x.is_valid(); x.next())

namespace my {

    struct point2d {
        point2d() {}

        point2d(int row, int col) {
            this->row = row;
            this->col = col;
        }

        bool operator!=(const point2d& p) const {
            return (row != p.row) || (col != p.col);
        }

        bool operator>= (const point2d &b) const {
            return (row >= b.row) && (col >= b.col);
        }

        bool operator<= (const point2d &b) const {
            return (row <= b.row) && (col <= b.col);
        }

        int row, col;
    };

    std::ostream& operator<<(std::ostream& ostr, const point2d& p) {
        return ostr << '(' << p.row << ',' << p.col << ')';
    }

    // Forward declarations
    class box2d_iterator;
    class neighb2d_iterator;

    class box2d {
    public:
        typedef point2d point_type;
        typedef box2d_iterator p_iterator_type;
        typedef neighb2d_iterator n_iterator_type;

        box2d(const point2d& pmin, const point2d& pmax) {
            pmin_ = pmin;
            pmax_ = pmax;
        }

        box2d(unsigned nrows, unsigned ncols)
            : pmin_(0,0), pmax_(nrows - 1, ncols - 1)
        {}

        const point2d& pmin() const {
            return pmin_;
        }

        const point2d& pmax() const {
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

        int index_of(const point2d& p) const {
            int i = (p.row - pmin_.row) * ncols() + (p.col - pmin_.col);
            return i;
        }

    private:
        point2d pmin_, pmax_;
    };


    /**
     * Iterator over the set of points contained in a 2D box.
     */
    class box2d_iterator {
    public:
        box2d_iterator(const box2d& b) : b_(b) {}

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

        operator point2d() const {
            return p_;
        }

    private:
        box2d b_;
        point2d p_;
    };


    /**
     * Iterator over the set of neighbors of a 2D point.
     */
    class neighb2d_iterator {
    public:
        neighb2d_iterator() {
            delta_.push_back(point2d(-1, 0));
            delta_.push_back(point2d(0, -1));
            delta_.push_back(point2d(0, 1));
            delta_.push_back(point2d(1, 0));
        }

        void center_at(const point2d& p) {
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

        operator point2d() const {
            point2d n;
            n.row = p_.row + delta_[i_].row;
            n.col = p_.col + delta_[i_].col;

            return n;
        }

    private:
        std::vector<point2d> delta_;
        unsigned i_; // current index in delta_
        point2d p_; // center is p_
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
    void fancy_print(const Image<I>& ima_, const box2d& b,
        std::ostream& ostr = std::cout)
    {
        const I& ima = ima_.exact();
        point2d p;
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
    class image2d : public Image< image2d<T> > {
    public:
        typedef T value_type;

        typedef box2d domain_type;
        typedef typename domain_type::point_type point_type;
        typedef typename domain_type::p_iterator_type p_iterator_type;
        typedef typename domain_type::n_iterator_type n_iterator_type;

        /**
         * TODO do it the C++ way :
         *   template <typename U>
         *   using with_value_type = image2d<U>;
         *
         * example :
         * with I being image2d<int>
         * ->  typename I::template with_value_type<float>::ret is image2d<float>
         */
        template <typename U>
        struct with_value_type {
            typedef image2d<U> ret;
        };

        image2d(const domain_type& d) :
            d_(d)
        {
            data_.resize(d_.npoints());
        }

        image2d(unsigned nrows, unsigned ncols) :
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

            box2d_iterator p(domain());
            unsigned i = 0;
            for_all(p) {
                (*this)(p) = data[i++];
            }
        }

        void debug_print(std::ostream& ostr = std::cout) const {
            for (int row = d_.pmin().row; row <= d_.pmax().row; row += 1) {
                for (int col = d_.pmin().col; col <= d_.pmax().col; col += 1) {
                    ostr << this->operator()(point2d(row, col)) << ' ';
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
