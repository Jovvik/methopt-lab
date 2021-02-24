#include "lab/segment.h"

using namespace lab;

Segment::Segment(double start_, double end_, std::vector<std::pair<double, double>> points_)
    : start(start_), end(end_), points(points_) {}