#include "parse_validate/validateData.h"

ValidationResult validate(const Event& data)
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

    return {true, ValidationError::None};
}