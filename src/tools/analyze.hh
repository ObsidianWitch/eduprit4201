#ifndef ANALYZE_HH
#define ANALYZE_HH

#include "tools/Image2D.hh"
#include "tools/ImageIf.hh"
#include "tools/Helper.hh"
#include "tools/compute_dmap__v2.hh"

namespace my {

    Image2D<unsigned> analyze(Image2D<unsigned>& lab,
        const Image2D<bool_t>& msk)
    {
        Box2D b = lab.domain();

        // FIXME: cut

        Image2D<unsigned> path(b);
        data_fill(path, 0);

        // FIXME: cut

        return path;
    }

} // end of namepace my

#endif // ANALYZE_HH
