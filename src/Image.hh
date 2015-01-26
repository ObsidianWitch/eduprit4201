#ifndef IMAGE_HH
#define IMAGE_HH

#include <iostream>
#include "Point2D.hh"
#include "Box2D.hh"

#define for_all(x) for (x.start(); x.is_valid(); x.next())

namespace my {

    template <typename I>
    struct Image {
        I& exact() {
            return *(I*)(void*)this;
        }

        const I& exact() const {
            return *(const I*)(const void*)this;
        }

        protected:
            Image() {}
    };

    template <typename I> void debug_iota(Image<I>& ima_) {
        I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        unsigned v = 0;
        for_all(p){
            ima(p) = v++;
        }
    }

    template <typename I>
    void data_fill(Image<I>& ima_, typename I::value_type v) {
        I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        for_all(p){
            ima(p) = v;
        }
    }


    template <typename I>
    std::ostream& operator<<(std::ostream& ostr, const Image<I>& ima_) {
        const I& ima = ima_.exact();
        typename I::p_iterator_type p(ima.domain());
        for_all(p) {
            ostr << p << ':' << ima(p) << ' ';
        }

        return ostr;
    }

    template <typename I>
    void fancy_print(const Image<I>& ima_, const Box2D& b,
        std::ostream& ostr = std::cout)
    {
        const I& ima = ima_.exact();
        Point2D p;
        int& row = p.row;
        int& col = p.col;

        for (row = b.pmin().row; row <= b.pmax().row; row += 1) {
            for (col = b.pmin().col; col <= b.pmax().col; col += 1){
                if (ima.domain().has(p)) {
                    ostr << ima(p) << ' ';
                }
                else {
                    ostr << "  ";
                }
            }

            ostr << std::endl;
        }

        ostr << std::endl;
    }

} // end of namespace my

#endif // IMAGE_HH
