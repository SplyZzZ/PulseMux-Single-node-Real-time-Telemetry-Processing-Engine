#include "windowAggregator.h"
#include <algorithm>
void update(windowsData&& data, double value)
{
 ++data.count;
 data.sum += value;
 data.min = std::min(data.min, value);
 data.max = std::max(data.max, value);
}