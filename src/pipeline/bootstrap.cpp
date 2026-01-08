#include "pipeline/bootstrap.h"
#include "parse_validate/checkDuplicate.h"
#include "pipeline/router.h"
#include "parse_validate/normalize.h"
#include "pipeline/worker.h"
#include <thread>
#include <filesystem>
void runBootstrap()
{
    size_t workerCount = std::thread::hardware_concurrency()-1; 
    std::vector<Worker> workersList(workerCount);
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

        auto idx = router(converted->tenant, converted->deviceId, converted->metric, 10);
        workersList[idx].set(std::move(*converted));

       
    }
);
    }
}