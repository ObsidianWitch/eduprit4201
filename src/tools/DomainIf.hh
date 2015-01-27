#ifndef DOMAIN_IF_HPP
#define DOMAIN_IF_HPP

namespace my {

    // Forward declarations
    class IteratorIf;

    class DomainIf {
    public:
        typedef Point2D point_type;
        typedef IteratorIf p_iterator_type;
        typedef Neighb2DIterator n_iterator_type;

        // FIXME generic image
        DomainIf(const Image2D<bool_t>& msk) :
            msk_(msk)
        {}

        const Point2D& pmin() const {
            return msk_.domain().pmin();
        }

        const Point2D& pmax() const {
            return msk_.domain().pmax();
        }

        unsigned nrows() const {
            return msk_.domain().nrows();
        }

        unsigned ncols() const {
            return msk_.domain().ncols();
        }

        unsigned npoints() const {
            return nrows() * ncols();
        }

        bool has(const point_type& p) const {
            bool containedInParentDomain = msk_.domain().has(p);
            if (!containedInParentDomain) { return false; }

            return (msk_(p) != false);
        }

        int index_of(const Point2D& p) const {
            return msk_.domain().index_of(p);
        }

        // TODO generic return type
        Box2DIterator parentIterator() const {
            return msk_.pIterator();
        }

    private:
        const Image2D<bool_t>& msk_;
    };

    class IteratorIf {
    public:
        IteratorIf(const DomainIf& domain) :
            domain_(domain)
        {}

        void start() {
            p_ = domain_.pmin();

            while(!domain_.has(p_) && is_valid()) {
                domain_.parentIterator().next();
            }
        }

        // TODO à modifier, va trop loin
        bool is_valid() const {
            return p_ <= domain_.pmax();
        }

        void next() {
            if (!is_valid()) {
                std::abort();
            }

            do {
                domain_.parentIterator().next();
            } while (!domain_.has(p_) && is_valid());
        }

        operator Point2D() const {
            return p_;
        }

    private:
        DomainIf domain_;
        Point2D p_;
    };

} // end of namespae my

#endif // DOMAIN_IF_HPP
