#pragma once

#include <vector>
#include <string>


struct DataSample{
    using DataSamples = std::vector< DataSample >;
    
    unsigned int id;
    std::string name;
    std::string surname;
    std::string email;

    DataSamples createDataSamples();
};
