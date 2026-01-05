#include "pipeline/bootstrap.h"
#include "parse_validate/checkDuplicate.h"
#include <filesystem>
void runBootstrap()
{
    TimeContext timeContext;
    std::filesystem::path dir = "C:/PulseMux-Single-node-Real-time-Telemetry-Processing-Engine/data";
    if(!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir))
    {
        // TODO: обробити помилку зупиняюч потік
    }
    for(const auto& file : std::filesystem::directory_iterator(dir))
    { 
        if(!file.is_regular_file()) {continue;}
        if(file.path().extension() != ".ndjson") {continue;}
        
       readFile(
    file.path().string(),
    [&](std::string_view line)
    {
        auto data = parseEvent(line);
        if (!data) return;

        auto converted = typeConvertation(*data);
        if (!converted) return;

        auto validation = validate(*converted);
        if (!validation.ok) return;

        auto scale = normalizationValue(converted->metric);
        if (!scale) return;

        Event normalized = *converted;
        normalized.value *= *scale;

        if (checkDuplicate(normalized.eventId, normalized.ts)) return;
        
       
    }
);
    }
}