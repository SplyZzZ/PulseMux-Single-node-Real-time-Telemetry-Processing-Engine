#include "pipeline/bootstrap.h"

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
        
        readFile(file.path().string(),[&](std::string_view line)
        {
            auto data = parseEvent(line);
            if(data)
            {
                auto convertData = typeConvertation(data.value());
                if(convertData)
                {
                    auto result = validate(convertData.value());
                    if(result.ok)
                    {
                        //TODO :: Normalizathion
                    }
                }
            }
                    
        }
                
            );
    }
}