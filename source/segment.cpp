#include "lab/segment.h"

using namespace lab;

Segment::Segment(double start_, double end_) : Segment(start_, end_, {}) {}

Segment::Segment(double start_, double end_,
                 std::vector<std::pair<double, double>> points_)
    : start(start_), end(end_), points(points_) {}

double Segment::get_start() { return start; }

double Segment::get_end() { return end; }

const std::vector<std::pair<double, double>>& Segment::get_points() {
    return points;
}

std::optional<double> Segment::get_ans() { return ans; }

void Segment::set_ans(double ans) { this->ans = ans; }