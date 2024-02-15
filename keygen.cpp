#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>


const unsigned int KEY_SIZE = 16;
const unsigned int BYTE_VALUE_OVERFILL = 256;

// byte2str function converts a byte into
// its HEX representation, e.g.
// 179 => B3,
// 161 => A1,
// 56 => 38
// etc.
// Taken from https://stackoverflow.com/questions/10723403/char-array-to-hex-string-c
std::string byte2str(char byte) {
    const char hex_chars[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };
    std::string hex = "";
    hex += hex_chars[ ( byte & 0xF0 ) >> 4 ];
    hex += hex_chars[ ( byte & 0x0F ) >> 0 ];
    return hex;
}

void saveStringsToFile(const std::vector<std::string>& strings, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& str : strings) {
            file << str << std::endl; // Write each string to a new line
        }
        file.close();
        std::cout << "Strings saved to file successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}


//
std::string byteArray2hexString(char* bytes, unsigned int array_size) {
    std::string hexs = "";
    for (unsigned int i = 0; i < array_size; i++) {
        hexs += byte2str(bytes[i]);
    }
    return hexs;
}

time_t getUnixTime(int year, int month, int day, int hour, int minute, int second) {
    struct tm timeinfo = {0}; // Initialize struct tm
    
    // Set specified date and time components
    timeinfo.tm_year = year - 1900; // Years since 1900
    timeinfo.tm_mon = month - 1;    // Months since January [0,11]
    timeinfo.tm_mday = day;         // Day of the month [1,31]
    timeinfo.tm_hour = hour;        // Hours since midnight [0,23]
    timeinfo.tm_min = minute;        // Minutes after the hour [0,59]
    timeinfo.tm_sec = second;        // Seconds after the minute [0,59]
    
    // Convert struct tm to time_t
    return mktime(&timeinfo);
}


int main(int argc, const char * argv[]) {

    std::vector<std::string> strings; // Empty vector of strings

    int year = 2020;
    int month = 2;
    int day = 20;
    int hour = 11;
    int minute = 29;
    int second = 0;
    
    // Get Unix timestamp for specified date and time
    time_t unixTime = getUnixTime(year, month, day, hour, minute, second);
    unsigned int seed = (unsigned int)unixTime;

    
    // Print Unix timestamp
    std::cout << "Unix timestamp for specified date and time: " << unixTime << std::endl;

    
    // seed for PRG
    // equal to the current UNIX timestamp

    for (int i = 0; i <= 7300; ++i) {
        // std::cout << "Iteration " << i << std::endl;
        // unsigned int seed = (unsigned int)time(NULL);

        // std::cout << "seed = " << seed << "\n";
        
        /* initialize PRG with the given seed */
        srand (seed);
        
        char key[KEY_SIZE];
        
        for (unsigned int i = 0; i < KEY_SIZE; i++) {
            key[i] = rand() % BYTE_VALUE_OVERFILL;
        }
        
        std::string key_str = byteArray2hexString(key, KEY_SIZE);

        strings.push_back(key_str);
        seed++;
    }
    
    
    // std::cout << "KEY: " << key_str << "\n";

    // std::vector<std::string> strings = {"Hello", "World", "This", "is", "a", "test"};

    // File name to save the strings
    std::string filename = "strings.txt";

    // Save the strings to the file
    saveStringsToFile(strings, filename);

    

    // Add strings to the vector
    // strings.push_back("Hello");
    // strings.push_back("World");
    // strings.push_back("This");
    // strings.push_back("is");
    // strings.push_back("a");
    // strings.push_back("test");

    // Display the strings in the vector
    // for (const auto& str : strings) {
    //     std::cout << str << std::endl;
    // }
    
    return 0;
}
