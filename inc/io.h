#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include "common.h"
//#include <string.h>
//#include <stdio.h>

#ifdef _WIN32 /* implementation for Windows like POSIX */
#define POSIX_PORT
#include "getline.h"
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#define cout std::cout
#define endl std::endl

namespace IO
{
    namespace reserve_first
    {
        namespace ifstream_method
        {
            void pipe_newlines_read_line_by_line_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing pipe_newlines_read_line_by_line_and_reserve" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                std::string line_count;
                if (pipecall(count_new_lines(filename), line_count) == OK)
                {
                    line_count = line_count.substr(0, line_count.find(' '));

                    out.reserve(stoll(line_count));
                    out.emplace_back();
                    while (std::getline(file, out.back()))
                    {
                        out.emplace_back();
                    }
                }
                file.close();

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            void istreambuf_reserve_and_readfile_directly_line_by_line(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_reserve_and_readfile_directly_line_by_line" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );

                out.reserve(line_count);
                out.emplace_back();

                while (std::getline(file, out.back()))
                {
                    out.emplace_back();
                }
                file.close();

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            void istream_reserve_and_readfile_directly_line_by_line(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istream_reserve_and_readfile_directly_line_by_line" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);
                auto line_count = std::count(
                    std::istream_iterator<char>(file),
                    std::istream_iterator<char>(), '\n'
                );

                out.reserve(line_count);
                out.emplace_back();

                while (std::getline(file, out.back()))
                {
                    out.emplace_back();
                }
                file.close();

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            void istreambuf_read_into_reserved_ss_and_get_wholefile_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_read_into_reserved_ss_and_get_wholefile_and_reserve" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                std::string output;

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                output.reserve(charcount);
                file.seekg(0, std::ios::beg);

                std::copy((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>(), std::back_inserter(output));

                std::istringstream iss(output);

                /* reserve space for new lines in the vector */
                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );
                file.close();

                out.reserve(line_count);
                out.emplace_back();
                while (std::getline(iss, out.back()))
                {
                    out.emplace_back();
                }

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            void istreambuf_read_into_reserved_ss_and_get_wholefile(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_read_into_reserved_ss_and_get_wholefile" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                std::string output;

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                output.reserve(charcount);
                file.seekg(0, std::ios::beg);


                std::copy((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>(), std::back_inserter(output));

                std::istringstream iss(output);

                /* this is commented from above
                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );
                */
                file.close();

                /* this is commented from above
                out.reserve(line_count);
                */
                out.emplace_back();
                while (std::getline(iss, out.back()))
                {
                    out.emplace_back();
                }

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            void istreambuf_read_into_ss_and_get_wholefile_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_read_into_ss_and_get_wholefile_and_reserve" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                /* this is commented from above
                std::string output;

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                output.reserve(charcount);
                file.seekg(0, std::ios::beg);

                std::copy((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>(), std::back_inserter(output));
                */
                std::istringstream iss(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));

                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );
                file.close();

                out.reserve(line_count);
                out.emplace_back();
                while (std::getline(iss, out.back()))
                {
                    out.emplace_back();
                }
            }

            /* read a whole file into memory using ifstream, and then parse when the file is read */
            void ifstream_read_wholefile_into_charlist_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing ifstream_read_wholefile_into_charlist_and_reserve" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                file.seekg(0, std::ios::beg);

                std::vector<char> output(charcount);

                if (file.read(output.data(), charcount))
                {

                    auto line_count = std::count(
                        std::istreambuf_iterator<char>(file),
                        std::istreambuf_iterator<char>(), '\n'
                    );
                    out.reserve(line_count);
                    char* line = strtok(output.data(), "\n");
                    while (line != NULL)
                    {
                        out.emplace_back(line);
                        line = strtok(NULL, "\n");
                    }
                }
                file.close();

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            /* read a whole file into memory using ifstream, and then parse when the file is read */
            void ifstream_read_wholefile_into_charlist(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing ifstream_read_wholefile_into_charlist" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                file.seekg(0, std::ios::beg);

                std::vector<char> output(charcount);

                if (file.read(output.data(), charcount))
                {
                    /* this is commented from above
                    out.reserve(line_count);
                    */
                    char* line = strtok(output.data(), "\n");
                    while (line != NULL)
                    {
                        out.emplace_back(line);
                        line = strtok(NULL, "\n");
                    }
                }

                file.close();

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }
        }; // end of ifstream method

        namespace C_method
        {
            /* read a whole file into memory using FILE C function, and then parse when the file is read */
            void read_FILE_wholefile_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing read_FILE_wholefile_and_reserve" << endl;
                FILE* fp = fopen(filename.c_str(), "rb");

                if (fp == NULL)
                    throw std::runtime_error("File could not be opened. " + strerror());

                struct stat buffer;
                int         status;

                status = stat(filename.c_str(), &buffer);
                if (status != 0)
                    throw std::runtime_error("Could not determine file size . " + strerror());

                auto size = buffer.st_size; // number of chars
                char* data = (char*)malloc(size + 1);
                if (data == NULL)
                {
                    throw std::runtime_error("Could not allocate memory. " + strerror());
                }

                fread(data, size, 1, fp);

                data[size] = 0;

                size_t line_count = 0;
                int ch;
                while (!feof(fp))
                {
                    ch = fgetc(fp);
                    if (ch == '\n')
                    {
                        ++line_count;
                    }
                }
                fclose(fp);
                out.reserve(line_count);

                char* line = strtok(data, "\n");
                while (line != NULL)
                {
                    out.emplace_back(line);
                    line = strtok(NULL, "\n");
                }

                free(data);

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            /* read a whole file into memory using FILE C function, and then parse when the file is read */
            void read_FILE_wholefile(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing read_FILE_wholefile" << endl;
                FILE* fp = fopen(filename.c_str(), "rb");

                if (fp == NULL)
                    throw std::runtime_error("File could not be opened. " + strerror());

                struct stat buffer;
                int         status;

                status = stat(filename.c_str(), &buffer);
                if (status != 0)
                    throw std::runtime_error("Could not determine file size . " + strerror());

                auto size = buffer.st_size; // number of chars
                char* data = (char*)malloc(size + 1);
                if (data == NULL)
                {
                    throw std::runtime_error("Could not allocate memory. " + strerror());
                }

                fread(data, size, 1, fp);
                fclose(fp);

                data[size] = 0;

                char* line = strtok(data, "\n");
                while (line != NULL)
                {
                    out.emplace_back(line);
                    line = strtok(NULL, "\n");
                }

                free(data);

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }
        }; // end of C method
    }; // end of reserve first

    namespace reserve_not
    {
        namespace ifstream_method
        {
            void istreambuf_read_into_ss_and_get_wholefile(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_read_into_ss_and_get_wholefile" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                /* this is commented from above
                std::string output;

                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                output.reserve(charcount);
                file.seekg(0, std::ios::beg);
                */
                std::istringstream iss(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));

                /* this is commented from above
                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );
                */
                file.close();

                /* this is commented from above
                out.reserve(line_count);
                */
                out.emplace_back();
                while (std::getline(iss, out.back()))
                {
                    out.emplace_back();
                }
            }

            void istreambuf_copy_to_string_then_read_into_ss_and_get_wholefile(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing istreambuf_copy_to_string_then_read_into_ss_and_get_wholefile" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                std::string output(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));

                /* this is commented from above
                file.seekg(0, std::ios::end);
                size_t charcount = file.tellg();
                output.reserve(charcount);
                file.seekg(0, std::ios::beg);
                */
                std::istringstream iss(output);

                /* this is commented from above
                auto line_count = std::count(
                    std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>(), '\n'
                );
                */
                file.close();

                /* this is commented from above
                out.reserve(line_count);
                */
                out.emplace_back();
                while (std::getline(iss, out.back()))
                {
                    out.emplace_back();
                }

                file.close();
            }

            /* read line by line using ifstream, and then parse when the file is read */
            void ifstream_and_read_line_by_line(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing ifstream_and_read_line_by_line" << endl;
                std::ifstream file(filename, std::ios::in | std::ios::binary);

                if (!file.good())
                    throw std::runtime_error("File could not be opened. " + strerror());

                std::string line;
                while (std::getline(file, line))
                {
                    out.emplace_back(line);
                }

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }
        };

        namespace C_method
        {
            /* read line by line using FILE C function, and then parse when the file is read */
            void read_FILE_line_by_line_and_reserve(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing read_FILE_line_by_line_and_reserve" << endl;
                FILE* fp = fopen(filename.c_str(), "rb");

                if (fp == NULL)
                    throw std::runtime_error("File could not be opened. " + strerror());

                char* data = NULL;
                size_t size = 0;

                size_t line_count = 0;
                int ch;
                while (!feof(fp))
                {
                    ch = fgetc(fp);
                    if (ch == '\n')
                    {
                        ++line_count;
                    }
                }
                out.reserve(line_count);
                fseek(fp, 0, SEEK_SET);

                while (getline(&data, &size, fp) != -1)
                {
                    out.emplace_back(data);
                }

                free(data);
                fclose(fp);

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }

            /* read line by line using FILE C function, and then parse when the file is read */
            void read_FILE_line_by_line(std::string filename, std::vector<std::string>& out)
            {
                cout << "Executing read_FILE_line_by_line" << endl;
                FILE* fp = fopen(filename.c_str(), "rb");

                if (fp == NULL)
                    throw std::runtime_error("File could not be opened. " + strerror());

                char* data = NULL;
                size_t size = 0;

                /* this is commented from above
                size_t line_count = 0;
                int ch;
                while (!feof(fp))
                {
                    ch = fgetc(fp);
                    if (ch == '\n')
                    {
                        ++line_count;
                    }
                }
                out.reserve(line_count);
                fseek(fp, 0, SEEK_SET);
                */

                while (getline(&data, &size, fp) != -1)
                {
                    out.emplace_back(data);
                }

                free(data);
                fclose(fp);

                if (out.empty())
                    throw std::runtime_error("Error: File is empty or not accessible. " + strerror());
            }
        }; // end of C method
    }; // end of reserve not
}; // end of io
