#include "span.hpp"

#include <armadillo>

#include <gtest/gtest.h>

TEST(test_span, init_from_arma_good_default) {
    const arma::span aspan_default;
    const Span span_default(aspan_default);
    EXPECT_EQ(span_default.start, 0);
    EXPECT_EQ(span_default.stop, 0);
}

TEST(test_span, init_from_arma_good_single) {
    const arma::span aspan_single(4);
    const Span span_single(aspan_single);
    EXPECT_EQ(span_single.start, 4);
    EXPECT_EQ(span_single.stop, 4);
}

TEST(test_span, init_from_arma_good_both) {
    const arma::span aspan_both(3, 8);
    const Span span_both(aspan_both);
    EXPECT_EQ(span_both.start, 3);
    EXPECT_EQ(span_both.stop, 8);
}

TEST(test_span, init_from_arma_bad) {
    const arma::span aspan_reversed(9, 2);
    // We don't allow reversed spans for now.
    EXPECT_THROW(Span span_reversed(aspan_reversed), std::runtime_error);
}
