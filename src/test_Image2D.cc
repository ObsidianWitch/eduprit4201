#include "tools/Image2D.hh"

int main() {
    using namespace my;

    Box2D b(Point2D(1,2), Point2D(2,4));

    Image2D<int> ima(b);
    debug_iota(ima);
    ima.debug_print();

    std::cout << "ima = " << ima << std::endl;
}
