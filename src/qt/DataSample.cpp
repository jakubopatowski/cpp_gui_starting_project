#include "DataSample.hpp"

constexpr const char* name1 = "Jakub";
constexpr const char* name2 = "Michał";
constexpr const char* name3 = "Bożydar";
constexpr const char* name4 = "Jacek";
constexpr const char* name5 = "Marek";
constexpr const char* name6 = "Anna";
constexpr const char* name7 = "Dorota";
constexpr const char* name8 = "Zofia";
constexpr const char* name9 = "Hanna";
constexpr const char* name10 = "Sylwia";

constexpr const char* surname1 = "Opatowski";
constexpr const char* surname2 = "Kowalski";
constexpr const char* surname3 = "Łuczak";
constexpr const char* surname4 = "Dębiński";
constexpr const char* surname5 = "Karwowski";
constexpr const char* surname6 = "Bukowska";
constexpr const char* surname7 = "Kowalczyk";
constexpr const char* surname8 = "Kotus";
constexpr const char* surname9 = "Bąkowska";
constexpr const char* surname10 = "Wieczorek";

DataSample::DataSamples DataSample::createDataSamples() {
    DataSamples result;

    DataSample item1{ 1, std::string( name1 ), std::string( surname1 ),
                      std::string( "1@gmail.com" ) };
    result.push_back( item1 );

    DataSample item2{ 2, std::string( name2 ), std::string( surname2 ),
                      std::string( "2@gmail.com" ) };
    result.push_back( item2 );

    DataSample item3{ 3, std::string( name3 ), std::string( surname3 ),
                      std::string( "3@gmail.com" ) };
    result.push_back( item3 );

    DataSample item4{ 4, std::string( name4 ), std::string( surname4 ),
                      std::string( "4@gmail.com" ) };
    result.push_back( item4 );

    DataSample item5{ 5, std::string( name5 ), std::string( surname5 ),
                      std::string( "5@gmail.com" ) };
    result.push_back( item5 );

    DataSample item6{ 6, std::string( name6 ), std::string( surname6 ),
                      std::string( "6@gmail.com" ) };
    result.push_back( item6 );

    DataSample item7{ 7, std::string( name7 ), std::string( surname7 ),
                      std::string( "7@gmail.com" ) };
    result.push_back( item7 );

    DataSample item8{ 8, std::string( name8 ), std::string( surname8 ),
                      std::string( "8@gmail.com" ) };
    result.push_back( item8 );

    DataSample item9{ 9, std::string( name9 ), std::string( surname9 ),
                      std::string( "9@gmail.com" ) };
    result.push_back( item9 );

    DataSample item10{ 10, std::string( name10 ), std::string( surname10 ),
                       std::string( "10@gmail.com" ) };
    result.push_back( item10 );

    return result;
}