#ifndef SPAN_HPP_
#define SPAN_HPP_

#include <armadillo>

/**
 *
 */
class Span {
public:
    Span(size_t start_, size_t stop_) : start(start_), stop(stop_) {
        if (start > stop) {
            throw std::runtime_error("start must not be greater than stop");
        }
    }
    Span(size_t point) : Span(point, point) { }
    Span(const arma::span &aspan) : Span(aspan.a, aspan.b) { }

    const size_t start;
    const size_t stop;
};

#endif // SPAN_HPP_
