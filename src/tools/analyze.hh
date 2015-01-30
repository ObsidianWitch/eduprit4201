#ifndef ANALYZE_HH
#define ANALYZE_HH

#include <map>
#include <iostream>

#include "tools/Image2D.hh"
#include "tools/ImageIf.hh"
#include "tools/Helper.hh"
#include "tools/compute_dmap__v2.hh"

namespace my {

    template<typename I>
    std::map<unsigned, Point2D> computeMaxPoints(const Image2D<unsigned>& iz,
        const Image<I>& dmap_)
    {
        const I& dmap = dmap_.exact();

        std::map<unsigned, Point2D> m;

        auto p = iz.pIterator();
        for_all(p) {
            unsigned label = iz(p);
            if (label != 0) {
                if (m.count(label) == 0) {
                    std::pair<unsigned, Point2D> pair(label, p);
                    m.insert(pair);
                }
                else if (dmap(m[label]) < dmap(p)) {
                    m[label] = p;
                }
            }
        }

        return m;
    }

    template<typename I>
    void computeShortestPath(Image2D<unsigned>& path, const Image2D<unsigned>& iz,
        const I& dmap_, Point2D endPoint, unsigned label)
    {
        const I& dmap = dmap_.exact();
        auto D = dmap.domain();

        Point2D p = endPoint;
        unsigned currentDistance = dmap(endPoint);
        path(p) = label;

        while(currentDistance > 0) {
            auto n = dmap.nIterator();
            n.center_at(p);

            for_all (n) {
                if (D.has(n) &&
                    iz(n) == label &&
                    dmap(n) == currentDistance - 1)
                {
                    path(n) = label;
                    p = n;
                    currentDistance--;
                    break;
                }
            }
        }
    }

    Image2D<unsigned> analyze(Image2D<unsigned>& lab,
        const Image2D<bool_t>& msk)
    {
        Box2D b = lab.domain();

        Helper f(lab);
        auto dmap = compute_dmap__v2(
            make_ImageIf(lab, msk), f
        );

        std::map<unsigned, Point2D> maxPoints = computeMaxPoints(f.iz, dmap);

        Image2D<unsigned> path(b);
        data_fill(path, 0);

        for (auto it = maxPoints.begin() ; it != maxPoints.end() ; it++) {
            std::cout << "label " << it->first
                << ":  max distance = " << dmap(it->second)
                << ",  max point = " << it->second << std::endl;

            computeShortestPath(path, f.iz, dmap, it->second, it->first);
        }

        std::cout << std::endl;

        return path;
    }

} // end of namepace my

#endif // ANALYZE_HH
