// Copyright Nicholas Bartow 2022

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/regex.hpp>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return 0;
    }

    std::string inputFile_name, outputFile_name, inLine;
    int lines = 1;

    inputFile_name = argv[1];

    std::ifstream inputFile(inputFile_name);
    outputFile_name = inputFile_name + ".rpt";
    std::ofstream outputFile;
    bool boot_status = false;

    if (!inputFile.is_open()) {
        std::cout << "Unable to open file \"" << argv[1] << "\"" << std::endl;
        return 0;
    }

    outputFile.open(outputFile_name);
    if (!outputFile.is_open()) {
        std::cout << "Unable to create file: " + outputFile_name << std::endl;
        return 0;
    }
    if (outputFile.is_open()) {
        outputFile << "Device Boot Report\n";
        outputFile << "InTouch log file: " << argv[1] << "\n\n";
    }

    boost::posix_time::time_duration timeDuration;
    boost::posix_time::ptime timeStart, timeEnd;
    boost::regex messageBegin("( \\(log.c.166\\) server started)");
    boost::regex messageEnd(
        "(oejs.AbstractConnector:Started SelectChannelConnector)");

    // Lambda to get message time in the line
    auto retrieveTime = [](std::string time) {
        return time.substr(0, 19);
    };

    while (getline(inputFile, inLine)) {
        if (regex_search(inLine, messageBegin)) {
            timeStart = boost::posix_time::
                        time_from_string(retrieveTime(inLine));
            if (boot_status) {
                outputFile << "***** Incomplete Booting ***** \n\n";
                boot_status = false;
            }
            boot_status = true;
            outputFile << "=== Device Boot ===\n";
            outputFile << lines << "(" << inputFile_name << "): " << timeStart
            << " Boot Start\n";
        } else if (regex_search(inLine, messageEnd)) {
            boot_status = false;
            timeEnd = boost::posix_time::time_from_string(retrieveTime(inLine));
            timeDuration = (timeEnd - timeStart);

            outputFile << "=== Device Boot ===\n";
            outputFile << lines << "(" << inputFile_name
            << "): " << timeEnd<< " Boot Completed\n\tBoot Time: "
            << timeDuration.total_milliseconds() << "ms\n\n";
        }
        lines++;
    }

    if (boot_status)
        outputFile << "***** Incomplete Booting ***** \n\n";

    return 0;
}
