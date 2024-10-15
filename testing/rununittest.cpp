#include "common_decoders.h"
#include "gtest/gtest.h"
#include "gtest_ext_combine.h"

using namespace test;

struct DecodeParam {
    std::string cfile;
    std::string source;
    std::string filePath;

    DecodeParam(std::string file, std::string source) : cfile(file), source(source) {
        filePath = getCurrentDirectory() + "\\files\\" + file;
    }

    std::string test_name() const {
        auto s = source;
        auto f = cfile;
        replace(s.begin(), s.end(), '-', '_');
        replace(f.begin(), f.end(), '.', '_');
        replace(f.begin(), f.end(), '-', '_');
        return "file_" + f + "_for_coding_" + s;
    }

    static DecodeParam fromTuple(const ::testing::tuple<std::string, std::string>& t) {
        return DecodeParam(std::get<0>(t), std::get<1>(t));
    }

    void checkResult(int& decoderResult) const {
        auto it = find(encodings.begin(), encodings.end(), source);
        int extected_result = it - encodings.begin();
        auto fupper = cfile;
        transform(fupper.begin(), fupper.end(), fupper.begin(), ::toupper);
        auto point = fupper.find(".");
        ASSERT_NE(point, std::string::npos);
        auto ss = (fupper.substr(0, point).compare(source)) == 0 ? true : false;
        if (ss) {
            ASSERT_EQ(extected_result, decoderResult) << "extected_result = " << extected_result << "(" << encodings.at(extected_result) << ") result = " << decoderResult << "(" << encodings.at(decoderResult) << ")" << '\n';
        }
        else {
            ASSERT_NE(extected_result, decoderResult) << "Encoding shouldn't be detected. Try to detect " << encodings.at(extected_result) << " in " << fupper.substr(0, point) << " file, but it detected as " << encodings.at(decoderResult) << '\n';
        }
    }

private:
    std::string getCurrentDirectory() {
        const size_t size = 1024;
        char buffer[size];
        getcwd(buffer, size);
        return buffer;
    }
};

class DecodeTestSuite : public ::testing::TestWithParam<DecodeParam> {
};

TEST_P(DecodeTestSuite, DecodeCompactEncDetTest) {
    const auto& param = GetParam();
    auto result = decode<TestCompactEncDet>(loadFile(param.filePath));
    ASSERT_NO_FATAL_FAILURE(param.checkResult(result));
}

TEST_P(DecodeTestSuite, DecodeChardetTest) {
    const auto& param = GetParam();
    auto result = decode<TestChardet>(loadFile(param.filePath));
    ASSERT_NO_FATAL_FAILURE(param.checkResult(result));
}

TEST_P(DecodeTestSuite, DecodeUchardetTest) {
    const auto& param = GetParam();
    auto result = decode<TestUChardet>(loadFile(param.filePath));
    ASSERT_NO_FATAL_FAILURE(param.checkResult(result));
}

//TEST_P(DecodeTestSuite, DecodeIcu4cTest) {
//    const auto& param = GetParam();
//    auto result = decode<TestIcu4c>(loadFile(param.filePath));
//    ASSERT_NO_FATAL_FAILURE(param.checkResult(result));
//}

INSTANTIATE_TEST_CASE_P(Decode, DecodeTestSuite, google_combine::fromTuple(::testing::Combine(
    ::testing::Values("utf-8.txt", "utf-16.txt", "utf-32.txt", "big5.txt", "ascii.txt", "windows-1251.txt", "koi8-R.txt", "iso-8859-5.txt"),
    ::testing::ValuesIn(encodings))),
    [](const ::testing::TestParamInfo<DecodeParam>& ti) {
        return ti.param.test_name();
    });