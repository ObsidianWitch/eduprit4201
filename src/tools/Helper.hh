#ifndef HELPER_HH
#define HELPER_HH

#include "tools/Image2D.hh"

namespace my {

    struct DoNothing {
        void init() {}
        void process(const Point2D&, const Point2D&) {}
        void final() {}
    };

    class Helper {
    public:
        Helper(const Image2D<unsigned>& seeds) :
            seeds_(seeds),
            iz(seeds.domain()),
            prev(seeds.domain())
        {}

        void init() {
            initPrev();
            initIz();
        }

        void process(const Point2D& curPoint, const Point2D& prevPoint) {
            computePrev(curPoint, prevPoint);
            computeIz(curPoint);
        }

        const Image2D<unsigned>& seeds_;
        Image2D<unsigned> iz;
        Image2D<Point2D> prev;

    private:
        void initPrev() {
            auto p = prev.pIterator();
            for_all(p) {
                prev(p) = p;
            }
        }

        void computePrev(const Point2D& curPoint, const Point2D& prevPoint){
            prev(curPoint) = prevPoint;
        }

        void initIz() {
            auto p = iz.pIterator();
            for_all(p) {
                iz(p) = seeds_(p);
            }
        }

        void computeIz(const Point2D& curPoint) {
            if (curPoint != prev(curPoint)) {
                iz(curPoint) = iz(prev(curPoint));
            }
        }
    };

} // end of namespace my

#endif // HELPER_HH
