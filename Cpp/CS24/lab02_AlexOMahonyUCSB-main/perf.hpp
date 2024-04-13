#ifndef PERF_HPP
#define PERF_HPP

#include <cstdint>
#include <ostream>

struct PerformanceStats{
    uint16_t horsepower; // Range: [0,65535]
    uint32_t zeroToSixtyNs; // Range: (0,4294967296]
    float headonDragCoeff; // Range: [0,1)

    constexpr PerformanceStats(uint16_t hp,
                               uint32_t zeroToSixtyNanoseconds,
                               float headOnDragCoefficient):
            horsepower(hp),
            zeroToSixtyNs(zeroToSixtyNanoseconds),
            headonDragCoeff(headOnDragCoefficient){}

    //  Not required to understand. Used for Gradescope tests ONLY. 
    bool operator==(PerformanceStats const& o) const;
    bool operator!=(PerformanceStats const& o) const;
    bool operator<(PerformanceStats const& o) const;
    bool operator>(PerformanceStats const& o) const;
    bool operator<=(PerformanceStats const& o) const;
    bool operator>=(PerformanceStats const& o) const;
};

//  Not required to understand. Used for Gradescope tests ONLY. 
std::ostream& operator<<(std::ostream& o, PerformanceStats const& stats);

#endif //PERF_HPP