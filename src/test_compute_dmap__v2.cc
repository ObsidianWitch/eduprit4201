#include <cstdlib>
#include "tools/Image2D.hh"
#include "tools/ImageIf.hh"
#include "tools/Helper.hh"
#include "tools/compute_dmap__v2.hh"

int main() {
    using namespace my;

    Box2D b(4, 5);

    bool_t msk_dta[] = {
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 0,
        0, 0, 0, 1, 1,
        1, 1, 1, 0, 1
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
    // gives:
    //
    // 0 0 0 0 1
    // 1 1 1 1 0
    // 0 0 0 1 1
    // 1 1 1 0 1

    Image2D<unsigned> lab(b); // this is the "seed" label image
    lab.fill(lab_dta);
    lab.debug_print();
    // gives:
    //
    // 0 0 0 0 0
    // 1 0 0 0 0
    // 0 0 0 0 0
    // 2 0 0 0 0

    fancy_print(make_ImageIf(lab, msk), b);
    // gives:
    //
    //         0
    // 1 0 0 0
    //       0 0
    // 2 0 0   0


    {
        Image2D<unsigned> dmap = compute_dmap__v2(lab);
        dmap.debug_print();
        // gives:
        //
        // 1 2 3 4 5
        // 0 1 2 3 4
        // 1 2 3 4 5
        // 0 1 2 3 4

        // THIS RESULT IS CORRECT BUT...  THIS IS *NOT* WHAT WE WANT!  :-(

        fancy_print( make_ImageIf(dmap, msk), b );
        // gives:
        //
        //         5
        // 0 1 2 3
        //       4 5
        // 0 1 2   4

        // WE WANT TO COMPUTE THE DISTANCE MAP *WITHIN* THE MASK:

        fancy_print(compute_dmap__v2(make_ImageIf(lab, msk)), b);

        // gives:
        //
        //         4294967295 <- this value is MAX, i.e., unsigned(-1)
        // 0 1 2 3
        //       4 5
        // 0 1 2   6

        // THAT IS THE *EXPECTED* RESULT  :-)
    }


    {
        Helper f(lab);
        Image2D<unsigned> dmap = compute_dmap__v2(
            make_ImageIf(lab, msk), f
        ).removeIf();

        dmap.debug_print();
        // gives:
        //
        // 0 0 0 0 4294967295
        // 0 1 2 3 0
        // 0 0 0 4 5
        // 0 1 2 0 6

        f.iz.debug_print(); // 'iz' means "influence zone" of a seed
        // gives:
        //
        // 0 0 0 0 0 <- this pixel cannot be reached from a seed
        // 1 1 1 1 0
        // 0 0 0 1 1
        // 2 2 2 0 1

        f.prev.debug_print();
        // gives:
        //
        // (0,0) (0,1) (0,2) (0,3) (0,4)
        // (1,0) (1,0) (1,1) (1,2) (1,4)
        // (2,0) (2,1) (2,2) (1,3) (2,3)
        // (3,0) (3,0) (3,1) (3,3) (2,4)
    }

    return EXIT_SUCCESS;
}
