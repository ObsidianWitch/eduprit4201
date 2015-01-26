#include <cstdlib>
#include "compute_dmap.hh"

int main() {
    using namespace my;

    Image2D<bool_t> ima(4, 5);
    data_fill(ima, false);
    ima(Point2D(2, 3)) = true;
    ima.debug_print();

    {
        Image2D<unsigned> dmap = compute_dmap__SPECIFIC(ima);
        dmap.debug_print();
    }

    {
        Image2D<unsigned> dmap = compute_dmap__GENERIC(ima);
        dmap.debug_print();
    }

    return EXIT_SUCCESS;
}
