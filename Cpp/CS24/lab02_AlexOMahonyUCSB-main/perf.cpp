#include "perf.hpp"

//  Not required to understand. Used for Gradescope tests ONLY. 

bool PerformanceStats::operator==(PerformanceStats const& o) const{
    return this->horsepower == o.horsepower
        && this->zeroToSixtyNs == o.zeroToSixtyNs
        && this->headonDragCoeff == o.headonDragCoeff;
}

bool PerformanceStats::operator!=(PerformanceStats const& o) const{
    return !(*this==o);
}

bool PerformanceStats::operator<(PerformanceStats const& o) const{
    if(this->zeroToSixtyNs != o.zeroToSixtyNs){
        return this->zeroToSixtyNs > o.zeroToSixtyNs;
    }else if(this->horsepower != o.horsepower){
        return this->horsepower < o.horsepower;
    }else{
        return this->headonDragCoeff > o.headonDragCoeff;
    }
}

bool PerformanceStats::operator>(PerformanceStats const& o) const{
    return o<*this;
}

bool PerformanceStats::operator<=(PerformanceStats const& o) const{
    return !(*this>o);
}

bool PerformanceStats::operator>=(PerformanceStats const& o) const{
    return !(*this<o);
}

std::ostream& operator<<(std::ostream& o, PerformanceStats const& stats){
    return o<<"{ 0-60: "<<stats.zeroToSixtyNs<<", horsepower: "<<stats.horsepower<<", headonDragCoeff: "<<stats.headonDragCoeff<<" }";
}