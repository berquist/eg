#ifndef SPAN_HPP_
#define SPAN_HPP_

#include <armadillo>

/**
 *
 */
class Span {
    public:
    Span(size_t start, size_t stop) : m_start(start), m_stop(stop) { }
    Span(size_t point) : m_start(point), m_stop(point) { }
    Span(const arma::span &aspan) : m_start(aspan.a), m_stop(aspan.b) { }
    private:
    const size_t m_start;
    const size_t m_stop;
};

#endif // SPAN_HPP_
