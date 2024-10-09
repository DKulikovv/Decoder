#include "compact_enc_det/compact_enc_det.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

class Decoder {
public:
    int decode(const std::string& filePath) {
        std::string text;
        Encoding encoding = UNKNOWN_ENCODING;
        if (LoadFile(filePath, text)) {
            encoding = getEncoding(text.c_str());
        }
        return covertToSpecifiedEncoding(encoding);
    }

private:
    bool LoadFile(const std::string& filePath, std::string& text) {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(filePath, std::ios_base::in | std::ios::ate);
            std::streamsize fileSize = file.tellg();
            text.reserve(fileSize);

            file.seekg(0, std::ios::beg);
            text.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
        }
        catch (const std::ifstream::failure& e) {
            std::cout << "Exception opening/reading file - " << e.what() <<
                "\nFile path: " << filePath << std::endl;
            return false;
        }
        return true;
    }

    Encoding getEncoding(const char* text) {
        bool is_reliable;
        int bytes_consumed;
        return DetectEncoding(text, strlen(text), nullptr, nullptr, nullptr, UNKNOWN_ENCODING,
            UNKNOWN_LANGUAGE, CompactEncDet::WEB_CORPUS, false, &bytes_consumed, &is_reliable);
    }

    int covertToSpecifiedEncoding(const Encoding& encoding) {
        int rc = -1;
        std::string strToFind = "";
        switch (encoding) {
        case UTF8:
            strToFind = "UTF-8";
            break;
        case UTF16BE:
        case UTF16LE:
            strToFind = "UTF-16";
            break;
        case UTF32BE:
        case UTF32LE:
            strToFind = "UTF-32";
            break;
        case CHINESE_BIG5:
        case CHINESE_BIG5_CP950:
        case BIG5_HKSCS:
            strToFind = "BIG5";
            break;
        case ISO_8859_1:
        case ASCII_7BIT:
        case MSFT_CP1252:
            strToFind = "ASCII";
            break;
        case RUSSIAN_CP1251:
            strToFind = "WINDOWS-1251";
            break;
        case RUSSIAN_KOI8_R:
            strToFind = "KOI8-R";
            break;
        case ISO_8859_5:
            strToFind = "ISO-8859-5";
            break;
        default:
            return -1;
        }
        auto it = std::find(specifiedEncodings.begin(), specifiedEncodings.end(), strToFind);
        if (it != specifiedEncodings.end()) {
            rc = it - specifiedEncodings.begin();
        }
        return rc;
    }

    static const std::vector<std::string> specifiedEncodings;
};
const std::vector<std::string> Decoder::specifiedEncodings = { "UTF-8", "UTF-16", "UTF-32", "BIG5", "ASCII", "WINDOWS-1251", "KOI8-R", "ISO-8859-5" };