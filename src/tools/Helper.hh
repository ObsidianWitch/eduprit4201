#ifndef HELPER_HH
#define HELPER_HH

#include "tools/Image2D.hh"

namespace my {

    struct DoNothing {
        void init() {}
        void process(const Point2D&, const Point2D&) {}
        void final() {}
    };

    struct Helper {
        Helper(const Image2D<unsigned>& seeds) :
            seeds_(seeds),
            iz(seeds.domain()),
            prev(seeds.domain())
        {}

        void init() {
            auto p = prev.pIterator();
            for_all(p) {
                prev(p) = p;
            }
        }

        void process(const Point2D& curPoint, const Point2D& prevPoint) {
            // TODO compute iz
            prev(curPoint) = prevPoint;
        }

        const Image2D<unsigned>& seeds_;
        Image2D<unsigned> iz;
        Image2D<Point2D> prev;
    };

} // end of namespace my

#endif // HELPER_HH
