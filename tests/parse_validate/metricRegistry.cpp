#include <gtest/gtest.h>
#include "parse_validate/metricRegistry.h"
TEST(metricRegistry, TheMetricWasFoundInTheList) {
    EXPECT_NE(lookupMetric("latency"), nullptr);
}
TEST(metricRegistry, TheMetricNotWasFoundInTheList)  {
    EXPECT_EQ(lookupMetric("latency123"), nullptr);
}
TEST(MetricRegistry, LatencyHasCorrectScaleAndUnit)
{
    const auto* metric = lookupMetric("latency");
    ASSERT_NE(metric, nullptr);

    EXPECT_EQ(metric->unit, Unit::Milliseconds);
    EXPECT_EQ(metric->scale, 1.0);
}
// EXPECT_EQ(a, b);        // ==
// EXPECT_NE(a, b);        // !=
// EXPECT_LT(a, b);        // <
// EXPECT_GT(a, b);        // >
// EXPECT_TRUE(cond);
// EXPECT_FALSE(cond);
//
// EXPECT_THROW(func(), std::runtime_error);
// EXPECT_NO_THROW(func());