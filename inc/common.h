#pragma once
#include <string>
#include <array>
#include <algorithm>
#include <memory>
#include <stdexcept>

#ifdef _WIN32 /* implementation for Windows like POSIX */
#define popen  _popen
#define pclose _pclose
#define stat   _stat64
#else
#include <cstring>
#endif
#define OK 0

extern std::string error;

/* find the number of lines in a file */
inline std::string count_new_lines(std::string filename)
{
#ifdef _WIN32
    return "type " + filename + " | find \/c \/v \"\"";
#else
    return "wc -l " + filename;
#endif
}

/* display the coresponding output from errno */
inline std::string strerror()
{
    return std::strerror(errno);
}

/* make a system pipe call, return 0 if success, or -1 */
inline int pipecall(std::string input_command, std::string& out)
{
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(input_command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        out += buffer.data();
    }

    if (out.empty())
    {
        error = "Pipe call did not succeed with input " + input_command + "\n";
        return -1;
    }

    return 0;

}

/* takes a system pipe command and returns the output */
inline std::string pipecall(std::string input_command)
{
    std::string output;
    if (pipecall(input_command, output) == OK)
    {
        return output;
    }

    return "";

}