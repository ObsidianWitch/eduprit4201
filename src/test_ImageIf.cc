#include "tools/ImageIf.hh"
#include "tools/Image2D.hh"

int main() {
    using namespace my;

    Box2D b(2, 3);

    bool_t msk_dta[] = {
        0, 0, 1,
    	1, 0, 0
    };

    std::cout << "msk" << std::endl;
    Image2D<bool_t> msk(b);
    msk.fill(msk_dta);
    fancy_print(msk, b);

    std::cout << "ima" << std::endl;
    Image2D<int> ima(b);
    debug_iota(ima);
    fancy_print(ima, b);

    std::cout << "imgIf1" << std::endl;
    auto imgIf1 = make_ImageIf(ima, msk);
    fancy_print(make_ImageIf(ima, msk), b);

    std::cout << "imgIf2" << std::endl;
    ImageIf<Image2D<unsigned>, Image2D<int>> imgIf2(imgIf1.domain());
    debug_iota(imgIf2);
    fancy_print(imgIf2, b);

    std::cout << "imgIf2_removedIf" << std::endl;
    auto imgIf2_removedIf = imgIf2.removeIf();
    fancy_print(imgIf2_removedIf, b);
}
