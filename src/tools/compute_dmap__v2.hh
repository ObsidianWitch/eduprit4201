#ifndef COMPUTE_DMAP__V2_HH
#define COMPUTE_DMAP__V2_HH

#include <queue>
#include <limits>
#include "tools/Image.hh"
#include "tools/Helper.hh"

namespace my {

    template <typename I, typename F>
    typename I::template with_value_type<unsigned>::ret
    compute_dmap__v2(const Image<I>& input_, F& f) {
        typedef typename I::point_type point_type;
        typedef typename I::template with_value_type<unsigned>::ret dmap_type;

        const I& input = input_.exact();
        auto D = input.domain();

        const unsigned max = std::numeric_limits<unsigned>::max();
        dmap_type dmap(D);

        auto p = input.pIterator();
        for_all(p) {
            dmap(p) = max;
        }

        std::queue<point_type> q;
        auto n = input.nIterator();

        for_all(p){
            if (input(p) != 0) {
                dmap(p) = 0;
                n.center_at(p);
                for_all(n) {
                    if (D.has(n) && input(n) == false) {
                        q.push(p);
                        break;
                    }
                }

                // FIXME: cut
            }
        }

        while (!q.empty()) {
            point_type p = q.front();
            q.pop();
            n.center_at(p);
            for_all(n) {
                if (D.has(n) && dmap(n) == max) {
                    dmap(n) = dmap(p) + 1;
                    q.push(n);
                    // FIXME: cut
                }
            }
        }

        return dmap;
    }

    template <typename I>
    typename I::template with_value_type<unsigned>::ret
    compute_dmap__v2(const Image<I>& input_) {
        DoNothing f;
        return compute_dmap__v2(input_, f);
    }

    // FIXME: cut

} // end of namespace my

#endif // COMPUTE_DMAP__V2_HH
