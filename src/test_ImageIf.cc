#include "tools/ImageIf.hh"
#include "tools/Image2D.hh"

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

    auto imgIf1 = make_ImageIf(ima, msk);
    fancy_print(make_ImageIf(ima, msk), b);

    ImageIf<Image2D<unsigned>, Image2D<int>> imgIf2(imgIf1.domain());
    fancy_print(imgIf2, b);

    fancy_print(imgIf2.removeIf(), b);
}
