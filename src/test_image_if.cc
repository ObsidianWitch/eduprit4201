#include "image_if.hh"

int main() {
    using namespace my;

    Box2D b(2, 3);

    bool_t msk_dta[] = {
        0, 0, 1,
    	1, 0, 0
    };
    
    Image2D<bool_t> msk(b);
    msk.fill(msk_dta);
    fancy_print(msk, b);

    Image2D<int> ima(b);
    debug_iota(ima);
    fancy_print(ima, b);

    fancy_print(make_image_if(ima, msk), b);
}
