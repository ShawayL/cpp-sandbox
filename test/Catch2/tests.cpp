#include <catch2/catch_test_macros.hpp>
#include <cpp_sandbox/sample_library0/sample_library0.hpp>
#include <cpp_sandbox/sample_library1/sample_library1.hpp>
#include <cpp_sandbox/string_converter/StringConverter.hpp>
#include <algorithm>
#include <vector>

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(sample_library0::Factorial(0) == 1);
  REQUIRE(sample_library0::Factorial(1) == 1);
  REQUIRE(sample_library0::Factorial(2) == 2);
  REQUIRE(sample_library0::Factorial(3) == 6);
  REQUIRE(sample_library0::Factorial(10) == 3628800);

  REQUIRE(sample_library1::Factorial(0) == 1);
  REQUIRE(sample_library1::Factorial(1) == 1);
  REQUIRE(sample_library1::Factorial(2) == 2);
  REQUIRE(sample_library1::Factorial(3) == 6);
  REQUIRE(sample_library1::Factorial(10) == 3628800);
}

TEST_CASE("StringConverter", "[StringConverter]") {
    SECTION("utf8_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::Utf8ToWstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Utf8ToWstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Utf8ToWstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::Utf8ToWstring(utf8_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        REQUIRE(StringConverter::Utf8ToWstring(utf8_chinese) == wide_chinese);
    }
    
    SECTION("wstring_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::WstringToUtf8(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::WstringToUtf8(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::WstringToUtf8(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::WstringToUtf8(wide_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        REQUIRE(StringConverter::WstringToUtf8(wide_chinese) == utf8_chinese);
    }
    
    SECTION("ansi_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::AnsiToWstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::AnsiToWstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::AnsiToWstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::AnsiToWstring(ansi_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::AnsiToWstring("Hello World Test") == L"Hello World Test");
    }
    
    SECTION("wstring_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::WstringToAnsi(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::WstringToAnsi(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::WstringToAnsi(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::WstringToAnsi(wide_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::WstringToAnsi(L"Programming Test") == "Programming Test");
    }
    
    SECTION("utf8_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::Utf8ToAnsi("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Utf8ToAnsi("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Utf8ToAnsi("12345") == "12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::Utf8ToAnsi(utf8_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::Utf8ToAnsi("Test String Conversion") == "Test String Conversion");
    }
    
    SECTION("ansi_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::AnsiToUtf8("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::AnsiToUtf8("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::AnsiToUtf8("12345") == "12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::AnsiToUtf8(ansi_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::AnsiToUtf8("Testing ANSI UTF8 Conversion") == "Testing ANSI UTF8 Conversion");
    }
    
    SECTION("gb2312_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::Gb2312ToWstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Gb2312ToWstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Gb2312ToWstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::Gb2312ToWstring(gb2312_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        REQUIRE(StringConverter::Gb2312ToWstring(gb2312_chinese) == wide_chinese);
    }
    
    SECTION("wstring_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::WstringToGb2312(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::WstringToGb2312(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::WstringToGb2312(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::WstringToGb2312(wide_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        REQUIRE(StringConverter::WstringToGb2312(wide_chinese) == gb2312_chinese);
    }
    
    SECTION("gb2312_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::Gb2312ToUtf8("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Gb2312ToUtf8("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Gb2312ToUtf8("12345") == "12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::Gb2312ToUtf8(gb2312_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        REQUIRE(StringConverter::Gb2312ToUtf8(gb2312_chinese) == utf8_chinese);
    }
    
    SECTION("utf8_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::Utf8ToGb2312("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Utf8ToGb2312("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Utf8ToGb2312("12345") == "12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::Utf8ToGb2312(utf8_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        REQUIRE(StringConverter::Utf8ToGb2312(utf8_chinese) == gb2312_chinese);
    }
    
    SECTION("gb2312_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::Gb2312ToAnsi("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::Gb2312ToAnsi("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::Gb2312ToAnsi("12345") == "12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::Gb2312ToAnsi(gb2312_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串 - 使用往返测试
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        
        // 在 Windows 1252 编码环境下跳过此测试，因为编码转换可能有问题
#ifdef _WIN32
        if (StringConverter::GetAnsiCodepage() == 1252) {
            // 跳过 Windows 1252 编码环境下的测试
            WARN("Skipping GB2312 to ANSI roundtrip test on Windows 1252 codepage");
        } else {
#endif
            std::string ansi_chinese = StringConverter::Gb2312ToAnsi(gb2312_chinese);
            std::string gb2312_roundtrip = StringConverter::AnsiToGb2312(ansi_chinese);
            REQUIRE(gb2312_roundtrip == gb2312_chinese);
#ifdef _WIN32
        }
#endif
    }
    
    SECTION("ansi_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::AnsiToGb2312("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::AnsiToGb2312("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::AnsiToGb2312("12345") == "12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::AnsiToGb2312(ansi_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串 - 使用往返测试
        // "你好世界" 的 GB2312 编码
        std::string gb2312_chinese = "\xC4\xE3\xBA\xC3\xCA\xC0\xBD\xE7";
        
        // 在 Windows 1252 编码环境下跳过此测试，因为编码转换可能有问题
#ifdef _WIN32
        if (StringConverter::GetAnsiCodepage() == 1252) {
            // 跳过 Windows 1252 编码环境下的测试
            WARN("Skipping ANSI to GB2312 roundtrip test on Windows 1252 codepage");
        } else {
#endif
            std::string ansi_chinese = StringConverter::Gb2312ToAnsi(gb2312_chinese);
            std::string gb2312_roundtrip = StringConverter::AnsiToGb2312(ansi_chinese);
            REQUIRE(gb2312_roundtrip == gb2312_chinese);
#ifdef _WIN32
        }
#endif
    }
}
