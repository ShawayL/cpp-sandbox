#include <gtest/gtest.h>
#include <cpp_sandbox/string_converter/StringConverter.hpp>
#include <string>

// ============================================================================
// utf8_to_wstring
// ============================================================================

TEST(StringConverterTest, utf8_to_wstring_empty) {
    EXPECT_EQ(StringConverter::utf8_to_wstring(""), L"");
}

TEST(StringConverterTest, utf8_to_wstring_ascii) {
    EXPECT_EQ(StringConverter::utf8_to_wstring("Hello"), L"Hello");
}

TEST(StringConverterTest, utf8_to_wstring_digits) {
    EXPECT_EQ(StringConverter::utf8_to_wstring("12345"), L"12345");
}

TEST(StringConverterTest, utf8_to_wstring_special_chars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::utf8_to_wstring(utf8_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverterTest, utf8_to_wstring_chinese) {
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"你好世界";
    EXPECT_EQ(StringConverter::utf8_to_wstring(utf8_chinese), wide_chinese);
}

// ============================================================================
// wstring_to_utf8
// ============================================================================

TEST(StringConverterTest, wstring_to_utf8_empty) {
    EXPECT_EQ(StringConverter::wstring_to_utf8(L""), "");
}

TEST(StringConverterTest, wstring_to_utf8_ascii) {
    EXPECT_EQ(StringConverter::wstring_to_utf8(L"Hello"), "Hello");
}

TEST(StringConverterTest, wstring_to_utf8_digits) {
    EXPECT_EQ(StringConverter::wstring_to_utf8(L"12345"), "12345");
}

TEST(StringConverterTest, wstring_to_utf8_special_chars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::wstring_to_utf8(wide_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, wstring_to_utf8_chinese) {
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"你好世界";
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    EXPECT_EQ(StringConverter::wstring_to_utf8(wide_chinese), utf8_chinese);
}

// ============================================================================
// ansi_to_wstring
// ============================================================================

TEST(StringConverterTest, ansi_to_wstring_empty) {
    EXPECT_EQ(StringConverter::ansi_to_wstring(""), L"");
}

TEST(StringConverterTest, ansi_to_wstring_ascii) {
    EXPECT_EQ(StringConverter::ansi_to_wstring("Hello"), L"Hello");
}

TEST(StringConverterTest, ansi_to_wstring_digits) {
    EXPECT_EQ(StringConverter::ansi_to_wstring("12345"), L"12345");
}

TEST(StringConverterTest, ansi_to_wstring_special_chars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::ansi_to_wstring(ansi_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverterTest, ansi_to_wstring_english) {
    EXPECT_EQ(StringConverter::ansi_to_wstring("Hello World Test"), L"Hello World Test");
}

// ============================================================================
// wstring_to_ansi
// ============================================================================

TEST(StringConverterTest, wstring_to_ansi_empty) {
    EXPECT_EQ(StringConverter::wstring_to_ansi(L""), "");
}

TEST(StringConverterTest, wstring_to_ansi_ascii) {
    EXPECT_EQ(StringConverter::wstring_to_ansi(L"Hello"), "Hello");
}

TEST(StringConverterTest, wstring_to_ansi_digits) {
    EXPECT_EQ(StringConverter::wstring_to_ansi(L"12345"), "12345");
}

TEST(StringConverterTest, wstring_to_ansi_special_chars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::wstring_to_ansi(wide_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, wstring_to_ansi_english) {
    EXPECT_EQ(StringConverter::wstring_to_ansi(L"Programming Test"), "Programming Test");
}

// ============================================================================
// utf8_to_ansi
// ============================================================================

TEST(StringConverterTest, utf8_to_ansi_empty) {
    EXPECT_EQ(StringConverter::utf8_to_ansi(""), "");
}

TEST(StringConverterTest, utf8_to_ansi_ascii) {
    EXPECT_EQ(StringConverter::utf8_to_ansi("Hello"), "Hello");
}

TEST(StringConverterTest, utf8_to_ansi_digits) {
    EXPECT_EQ(StringConverter::utf8_to_ansi("12345"), "12345");
}

TEST(StringConverterTest, utf8_to_ansi_special_chars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::utf8_to_ansi(utf8_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, utf8_to_ansi_english) {
    EXPECT_EQ(StringConverter::utf8_to_ansi("Test String Conversion"), "Test String Conversion");
}

// ============================================================================
// ansi_to_utf8
// ============================================================================

TEST(StringConverterTest, ansi_to_utf8_empty) {
    EXPECT_EQ(StringConverter::ansi_to_utf8(""), "");
}

TEST(StringConverterTest, ansi_to_utf8_ascii) {
    EXPECT_EQ(StringConverter::ansi_to_utf8("Hello"), "Hello");
}

TEST(StringConverterTest, ansi_to_utf8_digits) {
    EXPECT_EQ(StringConverter::ansi_to_utf8("12345"), "12345");
}

TEST(StringConverterTest, ansi_to_utf8_special_chars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::ansi_to_utf8(ansi_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, ansi_to_utf8_english) {
    EXPECT_EQ(StringConverter::ansi_to_utf8("Testing ANSI UTF8 Conversion"), "Testing ANSI UTF8 Conversion");
}

// ============================================================================
// gb2312_to_wstring
// ============================================================================

TEST(StringConverterTest, gb2312_to_wstring_empty) {
    EXPECT_EQ(StringConverter::gb2312_to_wstring(""), L"");
}

TEST(StringConverterTest, gb2312_to_wstring_ascii) {
    EXPECT_EQ(StringConverter::gb2312_to_wstring("Hello"), L"Hello");
}

TEST(StringConverterTest, gb2312_to_wstring_digits) {
    EXPECT_EQ(StringConverter::gb2312_to_wstring("12345"), L"12345");
}

TEST(StringConverterTest, gb2312_to_wstring_special_chars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::gb2312_to_wstring(gb2312_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverterTest, gb2312_to_wstring_chinese) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"你好世界";
    EXPECT_EQ(StringConverter::gb2312_to_wstring(gb2312_chinese), wide_chinese);
}

// ============================================================================
// wstring_to_gb2312
// ============================================================================

TEST(StringConverterTest, wstring_to_gb2312_empty) {
    EXPECT_EQ(StringConverter::wstring_to_gb2312(L""), "");
}

TEST(StringConverterTest, wstring_to_gb2312_ascii) {
    EXPECT_EQ(StringConverter::wstring_to_gb2312(L"Hello"), "Hello");
}

TEST(StringConverterTest, wstring_to_gb2312_digits) {
    EXPECT_EQ(StringConverter::wstring_to_gb2312(L"12345"), "12345");
}

TEST(StringConverterTest, wstring_to_gb2312_special_chars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::wstring_to_gb2312(wide_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, wstring_to_gb2312_chinese) {
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"你好世界";
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    EXPECT_EQ(StringConverter::wstring_to_gb2312(wide_chinese), gb2312_chinese);
}

// ============================================================================
// gb2312_to_utf8
// ============================================================================

TEST(StringConverterTest, gb2312_to_utf8_empty) {
    EXPECT_EQ(StringConverter::gb2312_to_utf8(""), "");
}

TEST(StringConverterTest, gb2312_to_utf8_ascii) {
    EXPECT_EQ(StringConverter::gb2312_to_utf8("Hello"), "Hello");
}

TEST(StringConverterTest, gb2312_to_utf8_digits) {
    EXPECT_EQ(StringConverter::gb2312_to_utf8("12345"), "12345");
}

TEST(StringConverterTest, gb2312_to_utf8_special_chars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::gb2312_to_utf8(gb2312_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, gb2312_to_utf8_chinese) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    EXPECT_EQ(StringConverter::gb2312_to_utf8(gb2312_chinese), utf8_chinese);
}

// ============================================================================
// utf8_to_gb2312
// ============================================================================

TEST(StringConverterTest, utf8_to_gb2312_empty) {
    EXPECT_EQ(StringConverter::utf8_to_gb2312(""), "");
}

TEST(StringConverterTest, utf8_to_gb2312_ascii) {
    EXPECT_EQ(StringConverter::utf8_to_gb2312("Hello"), "Hello");
}

TEST(StringConverterTest, utf8_to_gb2312_digits) {
    EXPECT_EQ(StringConverter::utf8_to_gb2312("12345"), "12345");
}

TEST(StringConverterTest, utf8_to_gb2312_special_chars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::utf8_to_gb2312(utf8_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, utf8_to_gb2312_chinese) {
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    EXPECT_EQ(StringConverter::utf8_to_gb2312(utf8_chinese), gb2312_chinese);
}

// ============================================================================
// gb2312_to_ansi
// ============================================================================

TEST(StringConverterTest, gb2312_to_ansi_empty) {
    EXPECT_EQ(StringConverter::gb2312_to_ansi(""), "");
}

TEST(StringConverterTest, gb2312_to_ansi_ascii) {
    EXPECT_EQ(StringConverter::gb2312_to_ansi("Hello"), "Hello");
}

TEST(StringConverterTest, gb2312_to_ansi_digits) {
    EXPECT_EQ(StringConverter::gb2312_to_ansi("12345"), "12345");
}

TEST(StringConverterTest, gb2312_to_ansi_special_chars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::gb2312_to_ansi(gb2312_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, gb2312_to_ansi_chinese_roundtrip) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";

#ifdef _WIN32
    if (StringConverter::get_ansi_codepage() == 1252) {
        GTEST_SKIP() << "Skipping GB2312 to ANSI roundtrip test on Windows 1252 codepage";
    }
#endif

    std::string ansi_chinese = StringConverter::gb2312_to_ansi(gb2312_chinese);
    std::string gb2312_roundtrip = StringConverter::ansi_to_gb2312(ansi_chinese);
    EXPECT_EQ(gb2312_roundtrip, gb2312_chinese);
}

// ============================================================================
// ansi_to_gb2312
// ============================================================================

TEST(StringConverterTest, ansi_to_gb2312_empty) {
    EXPECT_EQ(StringConverter::ansi_to_gb2312(""), "");
}

TEST(StringConverterTest, ansi_to_gb2312_ascii) {
    EXPECT_EQ(StringConverter::ansi_to_gb2312("Hello"), "Hello");
}

TEST(StringConverterTest, ansi_to_gb2312_digits) {
    EXPECT_EQ(StringConverter::ansi_to_gb2312("12345"), "12345");
}

TEST(StringConverterTest, ansi_to_gb2312_special_chars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::ansi_to_gb2312(ansi_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverterTest, ansi_to_gb2312_chinese_roundtrip) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";

#ifdef _WIN32
    if (StringConverter::get_ansi_codepage() == 1252) {
        GTEST_SKIP() << "Skipping ANSI to GB2312 roundtrip test on Windows 1252 codepage";
    }
#endif

    std::string ansi_chinese = StringConverter::gb2312_to_ansi(gb2312_chinese);
    std::string gb2312_roundtrip = StringConverter::ansi_to_gb2312(ansi_chinese);
    EXPECT_EQ(gb2312_roundtrip, gb2312_chinese);
}
