#pragma once
#include "event.h"
enum class ValidationError {
    None,
    EmptyDeviceId,
    EmptyEventId,
    EmptyMetric,
    EmptyTenant,
    SeqInvalid,
    FieldTooLong,
    IngestFromFuture,
    EventFromFuture,
    ClockSkewTooLarge
};

struct ValidationResult {
    bool ok;
    ValidationError error;
};

ValidationResult validate(const Event& data);