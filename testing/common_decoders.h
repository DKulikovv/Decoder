#include "../CED_Library/compact_enc_det/compact_enc_det.h"
#include "../Chardet_Library/src/chardet.h"
#include "../Uchardet_Library/src/uchardet.h"
//#include "../Icu4c_Library/src/icu_decoder_impl.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace test {
    class TestChardet;
    class TestUChardet;;
    class TestCompactEncDet;
    class TestIcu4c;

    const std::vector<std::string> encodings = { "UTF-8", "UTF-16", "UTF-32", "BIG5", "ASCII", "WINDOWS-1251", "KOI8-R", "ISO-8859-5" };

    enum Encodings {
        UTF_8,
        UTF_16,
        UTF_32,
        BIG5,
        ASCII,
        WINDOWS_1251,
        KOI8_R,
        ISO_8859_5
    };

    class CompactEncDetDecoder {
    public:
        int decode(const std::string& filecontent) {
            Encoding encoding = getEncoding(filecontent.c_str());
            return covertToSpecifiedEncoding(encoding);
        }

    private:
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
            auto it = std::find(encodings.begin(), encodings.end(), strToFind);
            if (it != encodings.end()) {
                rc = it - encodings.begin();
            }
            return rc;
        }
    };

    std::string loadFile(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary);
        std::string filecontent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return filecontent;
    }

    template <class T>
    int decode(const std::string& filecontent);

    template<>
    int decode<TestChardet>(const std::string& filecontent) {
        int rc = -1;
        DetectObj* obj;

        if ((obj = detect_obj_init()) == nullptr) {
            std::cout << "Memory Allocation failed\n";
            return rc;
        }

        switch (detect_r(filecontent.c_str(), filecontent.length(), &obj)) {
        case CHARDET_OUT_OF_MEMORY:
            std::cout << "On handle processing, occured out of memory\n";
            detect_obj_free(&obj);
            return rc;
        case CHARDET_NULL_OBJECT:
            std::cout << "DetectObj argument of chardet() is must memory allocation with detect_obj_init API\n";
            return rc;
        }

        std::cout << "Encoding: " << obj->encoding << ", confidence: " << obj->confidence << ", exist BOM: " << obj->bom << "\n";

        std::string encoding(obj->encoding);
        for (auto& c : encoding) c = toupper(c);

        for (unsigned int idx = 0; idx < encodings.size(); idx++) {
            if (encoding.rfind(encodings[idx], 0) == 0) {
                rc = idx;
                std::cout << "Result: " << rc << "\n";
            }
        }

        if (rc < 0) {
            std::cout << "Unsupported encoding: " << encoding << "\n";
        }

        detect_obj_free(&obj);
        return rc;
    }

    template<>
    int decode<TestUChardet>(const std::string& filecontent) {
        int rc = -1;
        auto handle = uchardet_new();
        if (handle && !uchardet_handle_data(handle, filecontent.c_str(), filecontent.length())) {
            uchardet_data_end(handle);
            auto encoding0 = uchardet_get_charset(handle);
            auto it = find(encodings.begin(), encodings.end(), encoding0);
            uchardet_delete(handle);
            if (it != encodings.end()) {
                rc = it - encodings.begin();
            }
        }
        return rc;
    }

    template<>
    int decode<TestCompactEncDet>(const std::string& filecontent) {
        CompactEncDetDecoder decoder;
        return decoder.decode(filecontent);
    }

//    template<>
//    int decode<TestIcu4c>(const std::string& filecontent) {
//        int rc = -1;
//        UErrorCode u_glob_status = U_ZERO_ERROR;
//        UErrorCode uerr = U_ZERO_ERROR;
//        UCharsetDetector* ucd = ucsdet_open(&uerr);
//        ucsdet_setText(ucd, filecontent.c_str(), filecontent.size(), &uerr);
//        UCharsetMatch const* match = ucsdet_detect(ucd, &uerr);
//        std::string encoding(ucsdet_getName(match, &uerr));
//        std::cout << "Encoding: " << encoding << ", confidence: " << ucsdet_getConfidence(match, &uerr) << "\n";
//        ucsdet_close(ucd);
//        u_cleanup();
//        for (auto& c : encoding) c = toupper(c);
//
//        for (unsigned int idx = 0; idx < encodings.size(); idx++) {
//            if (encoding.rfind(encodings[idx], 0) == 0) {
//                rc = idx;
//            }
//        }
//        return rc;
//    }
}