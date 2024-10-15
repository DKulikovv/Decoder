#include "common_decoders.h"
#include "gtest/gtest.h"

using namespace test;

struct DecodeParam {
    Encodings expectedEncoding;
    std::string filePath;

    DecodeParam(std::string file, const Encodings& expectedEncoding) : filename(file), expectedEncoding(expectedEncoding) {
        testname = filename;
        std::replace(testname.begin(), testname.end(), '.', '_');
        std::replace(testname.begin(), testname.end(), '-', '_');
        filePath = getCurrentDirectory() + "\\files\\" + filename;
    }

    std::string test_name() const {
        return "file_" + testname;
    }
private:
    std::string getCurrentDirectory() {
        const size_t size = 1024;
        char buffer[size];
        getcwd(buffer, size);
        return buffer;
    }

    std::string testname;
    std::string filename;
};

class DecodeTestSuite : public ::testing::Test, public ::testing::WithParamInterface<DecodeParam> {
};

TEST_P(DecodeTestSuite, DecodeCompactEncDetTest) {
    const auto& param = GetParam();
    auto result = decode<TestCompactEncDet>(loadFile(param.filePath));
    ASSERT_EQ(result, param.expectedEncoding);
}

TEST_P(DecodeTestSuite, DecodeChardetTest) {
    const auto& param = GetParam();
    auto result = decode<TestChardet>(loadFile(param.filePath));
    ASSERT_EQ(result, param.expectedEncoding);
}

TEST_P(DecodeTestSuite, DecodeUchardetTest) {
    const auto& param = GetParam();
    auto result = decode<TestUChardet>(loadFile(param.filePath));
    ASSERT_EQ(result, param.expectedEncoding);
}

INSTANTIATE_TEST_CASE_P(DecodeCompactEncDetTest, DecodeTestSuite, ::testing::Values(
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