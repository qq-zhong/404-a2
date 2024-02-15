#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <ctime>
#include <cstring>

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

    int year = 2024;
    int month = 2;
    int day = 15;
    int hour = 0;
    int minute = 52;
    int second = 0;
    
    // Get Unix timestamp for specified date and time
    time_t unixTime = getUnixTime(year, month, day, hour, minute, second);
    
    // Print Unix timestamp
    std::cout << "Unix timestamp for specified date and time: " << unixTime << std::endl;

    
    // seed for PRG
    // equal to the current UNIX timestamp
    unsigned int seed = (unsigned int)time(NULL);

    std::cout << "seed = " << seed << "\n";
    
    /* initialize PRG with the given seed */
    srand (seed);
    
    char key[KEY_SIZE];
    
    for (unsigned int i = 0; i < KEY_SIZE; i++) {
        key[i] = rand() % BYTE_VALUE_OVERFILL;
    }
    
    std::string key_str = byteArray2hexString(key, KEY_SIZE);
    
    std::cout << "KEY: " << key_str << "\n";
    
    return 0;
}
