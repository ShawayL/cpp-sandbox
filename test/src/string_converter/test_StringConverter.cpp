#include <gtest/gtest.h>
#include <cpp_sandbox/string_converter/StringConverter.hpp>
#include <string>

// ============================================================================
// utf8_to_wstring
// ============================================================================

TEST(StringConverter, Utf8ToWstringEmpty) {
    EXPECT_EQ(StringConverter::Utf8ToWstring(""), L"");
}

TEST(StringConverter, Utf8ToWstringAscii) {
    EXPECT_EQ(StringConverter::Utf8ToWstring("Hello"), L"Hello");
}

TEST(StringConverter, Utf8ToWstringDigits) {
    EXPECT_EQ(StringConverter::Utf8ToWstring("12345"), L"12345");
}

TEST(StringConverter, Utf8ToWstringSpecialChars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::Utf8ToWstring(utf8_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverter, Utf8ToWstringChinese) {
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
    EXPECT_EQ(StringConverter::Utf8ToWstring(utf8_chinese), wide_chinese);
}

// ============================================================================
// wstring_to_utf8
// ============================================================================

TEST(StringConverter, WstringToUtf8Empty) {
    EXPECT_EQ(StringConverter::WstringToUtf8(L""), "");
}

TEST(StringConverter, WstringToUtf8Ascii) {
    EXPECT_EQ(StringConverter::WstringToUtf8(L"Hello"), "Hello");
}

TEST(StringConverter, WstringToUtf8Digits) {
    EXPECT_EQ(StringConverter::WstringToUtf8(L"12345"), "12345");
}

TEST(StringConverter, WstringToUtf8SpecialChars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::WstringToUtf8(wide_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, WstringToUtf8Chinese) {
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    EXPECT_EQ(StringConverter::WstringToUtf8(wide_chinese), utf8_chinese);
}

// ============================================================================
// ansi_to_wstring
// ============================================================================

TEST(StringConverter, AnsiToWstringEmpty) {
    EXPECT_EQ(StringConverter::AnsiToWstring(""), L"");
}

TEST(StringConverter, AnsiToWstringAscii) {
    EXPECT_EQ(StringConverter::AnsiToWstring("Hello"), L"Hello");
}

TEST(StringConverter, AnsiToWstringDigits) {
    EXPECT_EQ(StringConverter::AnsiToWstring("12345"), L"12345");
}

TEST(StringConverter, AnsiToWstringSpecialChars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::AnsiToWstring(ansi_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverter, AnsiToWstringEnglish) {
    EXPECT_EQ(StringConverter::AnsiToWstring("Hello World Test"), L"Hello World Test");
}

// ============================================================================
// wstring_to_ansi
// ============================================================================

TEST(StringConverter, WstringToAnsiEmpty) {
    EXPECT_EQ(StringConverter::WstringToAnsi(L""), "");
}

TEST(StringConverter, WstringToAnsiAscii) {
    EXPECT_EQ(StringConverter::WstringToAnsi(L"Hello"), "Hello");
}

TEST(StringConverter, WstringToAnsiDigits) {
    EXPECT_EQ(StringConverter::WstringToAnsi(L"12345"), "12345");
}

TEST(StringConverter, WstringToAnsiSpecialChars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::WstringToAnsi(wide_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, WstringToAnsiEnglish) {
    EXPECT_EQ(StringConverter::WstringToAnsi(L"Programming Test"), "Programming Test");
}

// ============================================================================
// utf8_to_ansi
// ============================================================================

TEST(StringConverter, Utf8ToAnsiEmpty) {
    EXPECT_EQ(StringConverter::Utf8ToAnsi(""), "");
}

TEST(StringConverter, Utf8ToAnsiAscii) {
    EXPECT_EQ(StringConverter::Utf8ToAnsi("Hello"), "Hello");
}

TEST(StringConverter, Utf8ToAnsiDigits) {
    EXPECT_EQ(StringConverter::Utf8ToAnsi("12345"), "12345");
}

TEST(StringConverter, Utf8ToAnsiSpecialChars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::Utf8ToAnsi(utf8_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, Utf8ToAnsiEnglish) {
    EXPECT_EQ(StringConverter::Utf8ToAnsi("Test String Conversion"), "Test String Conversion");
}

// ============================================================================
// ansi_to_utf8
// ============================================================================

TEST(StringConverter, AnsiToUtf8Empty) {
    EXPECT_EQ(StringConverter::AnsiToUtf8(""), "");
}

TEST(StringConverter, AnsiToUtf8Ascii) {
    EXPECT_EQ(StringConverter::AnsiToUtf8("Hello"), "Hello");
}

TEST(StringConverter, AnsiToUtf8Digits) {
    EXPECT_EQ(StringConverter::AnsiToUtf8("12345"), "12345");
}

TEST(StringConverter, AnsiToUtf8SpecialChars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::AnsiToUtf8(ansi_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, AnsiToUtf8English) {
    EXPECT_EQ(StringConverter::AnsiToUtf8("Testing ANSI UTF8 Conversion"), "Testing ANSI UTF8 Conversion");
}

// ============================================================================
// gb2312_to_wstring
// ============================================================================

TEST(StringConverter, Gb2312ToWstringEmpty) {
    EXPECT_EQ(StringConverter::Gb2312ToWstring(""), L"");
}

TEST(StringConverter, Gb2312ToWstringAscii) {
    EXPECT_EQ(StringConverter::Gb2312ToWstring("Hello"), L"Hello");
}

TEST(StringConverter, Gb2312ToWstringDigits) {
    EXPECT_EQ(StringConverter::Gb2312ToWstring("12345"), L"12345");
}

TEST(StringConverter, Gb2312ToWstringSpecialChars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::wstring wide_special = StringConverter::Gb2312ToWstring(gb2312_special);
    EXPECT_EQ(wide_special, L"Hello! @#$%^&*()");
}

TEST(StringConverter, Gb2312ToWstringChinese) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
    EXPECT_EQ(StringConverter::Gb2312ToWstring(gb2312_chinese), wide_chinese);
}

// ============================================================================
// wstring_to_gb2312
// ============================================================================

TEST(StringConverter, WstringToGb2312Empty) {
    EXPECT_EQ(StringConverter::WstringToGb2312(L""), "");
}

TEST(StringConverter, WstringToGb2312Ascii) {
    EXPECT_EQ(StringConverter::WstringToGb2312(L"Hello"), "Hello");
}

TEST(StringConverter, WstringToGb2312Digits) {
    EXPECT_EQ(StringConverter::WstringToGb2312(L"12345"), "12345");
}

TEST(StringConverter, WstringToGb2312SpecialChars) {
    std::wstring wide_special = L"Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::WstringToGb2312(wide_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, WstringToGb2312Chinese) {
    // "你好世界" Unicode codepoints
    std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    EXPECT_EQ(StringConverter::WstringToGb2312(wide_chinese), gb2312_chinese);
}

// ============================================================================
// gb2312_to_utf8
// ============================================================================

TEST(StringConverter, Gb2312ToUtf8Empty) {
    EXPECT_EQ(StringConverter::Gb2312ToUtf8(""), "");
}

TEST(StringConverter, Gb2312ToUtf8Ascii) {
    EXPECT_EQ(StringConverter::Gb2312ToUtf8("Hello"), "Hello");
}

TEST(StringConverter, Gb2312ToUtf8Digits) {
    EXPECT_EQ(StringConverter::Gb2312ToUtf8("12345"), "12345");
}

TEST(StringConverter, Gb2312ToUtf8SpecialChars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::string utf8_special = StringConverter::Gb2312ToUtf8(gb2312_special);
    EXPECT_EQ(utf8_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, Gb2312ToUtf8Chinese) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    EXPECT_EQ(StringConverter::Gb2312ToUtf8(gb2312_chinese), utf8_chinese);
}

// ============================================================================
// utf8_to_gb2312
// ============================================================================

TEST(StringConverter, Utf8ToGb2312Empty) {
    EXPECT_EQ(StringConverter::Utf8ToGb2312(""), "");
}

TEST(StringConverter, Utf8ToGb2312Ascii) {
    EXPECT_EQ(StringConverter::Utf8ToGb2312("Hello"), "Hello");
}

TEST(StringConverter, Utf8ToGb2312Digits) {
    EXPECT_EQ(StringConverter::Utf8ToGb2312("12345"), "12345");
}

TEST(StringConverter, Utf8ToGb2312SpecialChars) {
    std::string utf8_special = "Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::Utf8ToGb2312(utf8_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, Utf8ToGb2312Chinese) {
    // "你好世界" UTF-8 encoding
    std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
    EXPECT_EQ(StringConverter::Utf8ToGb2312(utf8_chinese), gb2312_chinese);
}

// ============================================================================
// gb2312_to_ansi
// ============================================================================

TEST(StringConverter, Gb2312ToAnsiEmpty) {
    EXPECT_EQ(StringConverter::Gb2312ToAnsi(""), "");
}

TEST(StringConverter, Gb2312ToAnsiAscii) {
    EXPECT_EQ(StringConverter::Gb2312ToAnsi("Hello"), "Hello");
}

TEST(StringConverter, Gb2312ToAnsiDigits) {
    EXPECT_EQ(StringConverter::Gb2312ToAnsi("12345"), "12345");
}

TEST(StringConverter, Gb2312ToAnsiSpecialChars) {
    std::string gb2312_special = "Hello! @#$%^&*()";
    std::string ansi_special = StringConverter::Gb2312ToAnsi(gb2312_special);
    EXPECT_EQ(ansi_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, Gb2312ToAnsiChineseRoundtrip) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";

#ifdef _WIN32
    if (StringConverter::GetAnsiCodepage() == 1252) {
        GTEST_SKIP() << "Skipping GB2312 to ANSI roundtrip test on Windows 1252 codepage";
    }
#endif

    std::string ansi_chinese = StringConverter::Gb2312ToAnsi(gb2312_chinese);
    std::string gb2312_roundtrip = StringConverter::AnsiToGb2312(ansi_chinese);
    EXPECT_EQ(gb2312_roundtrip, gb2312_chinese);
}

// ============================================================================
// ansi_to_gb2312
// ============================================================================

TEST(StringConverter, AnsiToGb2312Empty) {
    EXPECT_EQ(StringConverter::AnsiToGb2312(""), "");
}

TEST(StringConverter, AnsiToGb2312Ascii) {
    EXPECT_EQ(StringConverter::AnsiToGb2312("Hello"), "Hello");
}

TEST(StringConverter, AnsiToGb2312Digits) {
    EXPECT_EQ(StringConverter::AnsiToGb2312("12345"), "12345");
}

TEST(StringConverter, AnsiToGb2312SpecialChars) {
    std::string ansi_special = "Hello! @#$%^&*()";
    std::string gb2312_special = StringConverter::AnsiToGb2312(ansi_special);
    EXPECT_EQ(gb2312_special, "Hello! @#$%^&*()");
}

TEST(StringConverter, AnsiToGb2312ChineseRoundtrip) {
    // "你好世界" GB2312 encoding
    std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";

#ifdef _WIN32
    if (StringConverter::GetAnsiCodepage() == 1252) {
        GTEST_SKIP() << "Skipping ANSI to GB2312 roundtrip test on Windows 1252 codepage";
    }
#endif

    std::string ansi_chinese = StringConverter::Gb2312ToAnsi(gb2312_chinese);
    std::string gb2312_roundtrip = StringConverter::AnsiToGb2312(ansi_chinese);
    EXPECT_EQ(gb2312_roundtrip, gb2312_chinese);
}
