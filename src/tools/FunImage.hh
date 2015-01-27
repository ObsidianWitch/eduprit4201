#ifndef FUN_IMAGE_HH
#define FUN_IMAGE_HH

#include "tools/Image.hh"

namespace my {

    struct equals {
        typedef bool result_type;
        int v_;

        equals(int v) : v_(v) {}

        bool operator()(int v) const {
            return v == v_;
        }
    };

    template <typename I, typename F>
    class FunImage : public Image< FunImage<I,F> > {
    public:
        typedef typename F::result_type value_type;

        typedef typename I::domain_type domain_type;
        typedef typename I::point_type point_type;
        typedef typename I::p_iterator_type p_iterator_type;
        typedef typename I::n_iterator_type n_iterator_type;

        // TODO do it the C++ 11 way
        template <typename U>
        struct with_value_type {
            typedef typename I::template with_value_type<U>::ret ret;
        };

        FunImage(const Image<I>& ima, F f) :
            ima_(ima.exact()),
            f_(f)
        {}

        value_type operator()(const point_type& p) const {
            if (!domain().has(p)) {
                std::abort();
            }

            return f_(ima_(p));
        }

        const domain_type& domain() const {
            return ima_.domain();
        }

        p_iterator_type pIterator() const {
            return p_iterator_type(domain());
        }

        n_iterator_type nIterator() const {
            return n_iterator_type(domain());
        }

    private:
        const I& ima_;
        F f_;
    };


    template <typename I, typename F>
    FunImage<I,F> make_FunImage(const Image<I>& ima, F f) {
        return FunImage<I,F>(ima, f);
    }

} // end of namespace my

#endif // FUN_IMAGE_HH
