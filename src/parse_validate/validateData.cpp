
#include "parse_validate/TimeContext.h"
ValidationResult validate(const Event& data, const TimeContext& ctx)
{
    
    if (data.deviceId.empty()) { return {false, ValidationError::EmptyDeviceId};} 

    if (data.deviceId.size() >= 128) {return {false, ValidationError::FieldTooLong};}

    if (data.eventId.empty()) {return {false, ValidationError::EmptyEventId};}

    if (data.eventId.size() >= 128) {return {false, ValidationError::FieldTooLong};}

    if (data.metric.empty()) {return {false, ValidationError::EmptyMetric};}

    if (data.metric.size() >= 128) {return {false, ValidationError::FieldTooLong};}

    if (data.tenant.empty()) {return {false, ValidationError::EmptyTenant};}

    if (data.tenant.size() >= 128) {return {false, ValidationError::FieldTooLong};}

    if (data.seq == 0) {return {false, ValidationError::SeqInvalid};}

   auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());

    if (data.ingestTs > now + ctx.maxIngestFutureSkew){return{false, ValidationError::IngestFromFuture};}

    if (data.ts > now + ctx.maxEventFutureSkew) { return {false, ValidationError::EventFromFuture }; }

    if (std::chrono::abs(data.ingestTs - data.ts) > ctx.maxClockSkew) { return {false, ValidationError::ClockSkewTooLarge };}   

    return {true, ValidationError::None};
}