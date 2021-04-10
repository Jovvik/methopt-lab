#include "lab/n_function.h"

using namespace lab;

std::size_t NFunction::get_call_count() const { return call_count; }
std::size_t NFunction::get_grad_count() const { return grad_count; }

void NFunction::inc_call_count() { call_count++; }
void NFunction::inc_grad_count() { grad_count++; }