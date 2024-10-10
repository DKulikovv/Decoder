// testapp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "src/chardet.h"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

std::vector<char> loadFile(const std::string& path)
{
    std::ifstream file;
    std::vector<char> buffer;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path, std::ios::in | std::ios::ate);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif
        buffer.resize(size);
#ifdef WIN32
#pragma warning( pop )
#endif

        file.read(buffer.data(), size);
    }
    catch (...)
    {
        //throw std::runtime_error("Unable to load file: " + path);
        std::cout << "Unable to load file: " << path << std::endl;
    }
    return buffer;
}

int main(int argc, char * argv[])
{
    std::string filename;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'f')
            {
                i++;
                filename = argv[i];
            }
        }
    }

    if (filename.empty())
    {
        std::cout << "File name is not specified\n";
        return CHARDET_NO_RESULT;
    }
    else
    {
        std::cout << "File name is " << filename << std::endl;

        DetectObj* obj;

        if ((obj = detect_obj_init()) == NULL) {
            fprintf(stderr, "Memory Allocation failed\n");
            return CHARDET_MEM_ALLOCATED_FAIL;
        }

        std::vector<char> buffer = loadFile(filename);
        if (buffer.empty())
        {
            return CHARDET_NULL_OBJECT;
        }
        char* str = buffer.data();

        switch (detect_r(str, strlen(str), &obj))
        {
        case CHARDET_OUT_OF_MEMORY:
            fprintf(stderr, "On handle processing, occured out of memory\n");
            detect_obj_free(&obj);
            return CHARDET_OUT_OF_MEMORY;
        case CHARDET_NULL_OBJECT:
            fprintf(stderr,
                "2st argument of chardet() is must memory allocation "
                "with detect_obj_init API\n");
            return CHARDET_NULL_OBJECT;
        }

#ifndef CHARDET_BOM_CHECK
        printf("encoding: %s, confidence: %f\n", obj->encoding, obj->confidence);
#else
        // from 1.0.6 support return whether exists BOM
        printf("encoding: %s, confidence: %f, exist BOM: %d\n", obj->encoding, obj->confidence, obj->bom);
#endif
        detect_obj_free(&obj);

        return 0;
    }
}
