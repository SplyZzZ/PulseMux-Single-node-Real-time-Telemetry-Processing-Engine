#include "parse_validate/normalize.h"
#include "parse_validate/metricRegistry.h"
std::optional<double> normalizationValue(std::string_view metric)
{
   auto value =  lookupMetric(metric);
   if(value == nullptr) {return std::nullopt;}
   return value->scale;
}