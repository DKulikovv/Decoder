#include "../CED_Decoder_App/DecoderApp.h"
#include "../Chardet_Library/src/chardet.h"
#include "../Uchardet_Library/src/uchardet.h"
#include "gtest/gtest.h"

#include <vector>
#include <algorithm>

namespace test {
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

    struct DecodeParam {
        std::string filename;
        Encodings expectedEncoding;

        DecodeParam(std::string file, const Encodings& expectedEncoding) : filename(file), expectedEncoding(expectedEncoding) {
            testname = filename;
            std::replace(testname.begin(), testname.end(), '.', '_');
            std::replace(testname.begin(), testname.end(), '-', '_');
        }

        std::string test_name() const {
            return "file_" + testname;
        }
    private:
        std::string testname;
    };

    class DecodeTestSuite : public ::testing::Test, public ::testing::WithParamInterface<DecodeParam> {
    public:
        std::string getCurrentDirectory() {
            const size_t size = 1024;
            char buffer[size];
            getcwd(buffer, size);
            return buffer;
        }
    };

    TEST_P(DecodeTestSuite, DecodeCompactEncDetTest) {
        const auto& param = GetParam();
        const auto& path = getCurrentDirectory() + "\\files\\" + param.filename;

        Decoder dec;
        auto result = dec.decode(path);
        ASSERT_EQ(result, param.expectedEncoding);
    }

    INSTANTIATE_TEST_CASE_P(DecodeCompactEncDetTest, DecodeTestSuite,
        ::testing::Values(
            DecodeParam{ "utf-8.txt" , Encodings::UTF_8 },
            DecodeParam{ "utf-16.txt" , Encodings::UTF_16 },
            DecodeParam{ "utf-32.txt" , Encodings::UTF_32 },
            DecodeParam{ "big-5.txt" , Encodings::BIG5 },
            DecodeParam{ "ascii.txt" , Encodings::ASCII },
            DecodeParam{ "windows-1251.txt" , Encodings::WINDOWS_1251 },
            DecodeParam{ "koi8-R.txt" , Encodings::KOI8_R },
            DecodeParam{ "iso-8859-5.txt" , Encodings::ISO_8859_5 }
        ),
        [](const ::testing::TestParamInfo<DecodeParam>& ti) {
            return ti.param.test_name();
    });
}