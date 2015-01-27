#ifndef HELPER_HH
#define HELPER_HH

#include "tools/Image2D.hh"

namespace my {

    struct DoNothing {
        void init() {}
        void process(const Point2D&) {}
        void final() {}
    };

    struct Helper {
        // FIXME: cut
    };

} // end of namespace my

#endif // HELPER_HH
