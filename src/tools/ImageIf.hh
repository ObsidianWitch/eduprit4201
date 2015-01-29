#ifndef IMAGE_IF_HH
#define IMAGE_IF_HH

#include "tools/Image2D.hh"
#include "tools/DomainIf.hh"

namespace my {

    template <typename I, typename M>
    class ImageIf : public Image< ImageIf<I,M> >{
    public:
        typedef typename I::value_type value_type;

        typedef DomainIf domain_type;
        typedef typename domain_type::point_type point_type;
        typedef typename domain_type::p_iterator_type p_iterator_type;
        typedef typename domain_type::n_iterator_type n_iterator_type;

        // TODO do it the C++ 11 way
        template <typename U>
        struct with_value_type {
            typedef typename I::template with_value_type<U, DomainIf>::ret ret;
        };

        ImageIf (Image<I>& ima, const Image<M>& msk) :
            domain_(msk.exact()),
            allocated(false)
        {
            ima_ = &ima.exact();
        }

        ImageIf(const domain_type& d) :
            domain_(d),
            allocated(true)
        {
            ima_ = new I(domain_.parentDomain());
        }

        ~ImageIf() {
            if (allocated) {
                delete ima_;
            }
        }

        value_type operator()(const point_type& p) const {
            if (!domain().has(p)) {
                std::abort();
            }

            return (*ima_)(p);
        }

        value_type& operator()(const point_type& p) {
            if (!domain().has(p)) {
                std::abort();
            }

            return (*ima_)(p);
        }

        const domain_type& domain() const {
            return domain_;
        }

        p_iterator_type pIterator() const {
            return p_iterator_type(domain());
        }

        n_iterator_type nIterator() const {
            return n_iterator_type();
        }

        I& removeIf() {
            return *ima_;
        }

    private:
        I* ima_;
        const domain_type domain_;
        bool allocated;
    };

    template <typename I, typename M>
    ImageIf<I,M> make_ImageIf(Image<I>& ima, const Image<M>& msk) {
        return ImageIf<I,M>(ima, msk);
    }

} // end of namespace my

#endif // IMAGE_IF_HH
