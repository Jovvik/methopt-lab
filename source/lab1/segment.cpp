#include "lab1/segment.h"

using namespace lab1;

Segment::Segment(double start, double end) : start(start), end(end) {}

Segment::Segment(double start, double mid, double end)
    : start(start), mid(mid), end(end) {}

double Segment::get_start() { return start; }

double Segment::get_end() { return end; }

std::optional<double> Segment::get_ans() { return ans; }

std::optional<double> Segment::get_mid() { return mid; }

void Segment::set_ans(double ans) { this->ans = ans; }

void Segment::set_mid(double mid) { this->mid = mid; }
