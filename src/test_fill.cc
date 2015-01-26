#include "tools/Image2D.hh"
#include "tools/FunImage.hh"

int main() {
    using namespace my;

    Box2D b(4, 5);

    bool_t msk_dta[] = {
        0, 0, 0, 1, 1,
        1, 1, 1, 1, 0,
        0, 0, 0, 0, 0,
        1, 1, 1, 1, 1
    };

    unsigned lab_dta[] = {
        0, 0, 0, 0, 0,
    	1, 0, 0, 0, 0,
    	0, 0, 0, 0, 0,
    	2, 0, 0, 0, 0
    };

    Image2D<bool_t> msk(b);
    msk.fill(msk_dta);
    msk.debug_print();

    Image2D<unsigned> lab(b);
    lab.fill(lab_dta);
    lab.debug_print();

    unsigned out_dta[] = {
        0, 0, 0, 1, 1,
    	1, 1, 1, 1, 0,
    	0, 0, 0, 0, 0,
    	2, 2, 2, 2, 2
    };

    Image2D<unsigned> out(b);
    out.fill(out_dta);
    out.debug_print();

    std::cout << "out == 1" << std::endl;
    fancy_print(make_FunImage(out, equals(1)), b);

    std::cout << "out == 2" << std::endl;
    fancy_print(make_FunImage(out, equals(2)), b);
}
