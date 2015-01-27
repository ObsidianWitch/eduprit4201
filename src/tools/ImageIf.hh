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
        typedef typename I::point_type point_type;
        typedef IteratorIf p_iterator_type;
        typedef typename I::n_iterator_type n_iterator_type;

        ImageIf (const Image<I>& ima, const Image<M>& msk) :
            ima_(ima.exact()),
            // TODO create domain from msk
            domain_(msk.exact()) // FIXME domain_(msk) ?
        {}

        value_type operator()(const point_type& p) const {
            if (!domain().has(p)) {
                std::abort();
            }

            return ima_(p);
        }

        const domain_type& domain() const {
            return domain_;
        }

    private:
        const I& ima_;
        const domain_type domain_;
    };

    template <typename I, typename M>
    ImageIf<I,M> make_ImageIf(const Image<I>& ima, const Image<M>& msk) {
        return ImageIf<I,M>(ima, msk);
    }

} // end of namespace my

#endif // IMAGE_IF_HH
