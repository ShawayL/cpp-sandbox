#include <catch2/catch_test_macros.hpp>
#include <cpp_sandbox/sample_library0.hpp>
#include <cpp_sandbox/sample_library1.hpp>
#include <cpp_sandbox/StringConverter.hpp>
#include <algorithm>
#include <vector>

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(sample_library0::factorial(0) == 1);
  REQUIRE(sample_library0::factorial(1) == 1);
  REQUIRE(sample_library0::factorial(2) == 2);
  REQUIRE(sample_library0::factorial(3) == 6);
  REQUIRE(sample_library0::factorial(10) == 3628800);

  REQUIRE(sample_library1::factorial(0) == 1);
  REQUIRE(sample_library1::factorial(1) == 1);
  REQUIRE(sample_library1::factorial(2) == 2);
  REQUIRE(sample_library1::factorial(3) == 6);
  REQUIRE(sample_library1::factorial(10) == 3628800);
}

TEST_CASE("StringConverter", "[StringConverter]") {
    SECTION("utf8_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::utf8_to_wstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::utf8_to_wstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::utf8_to_wstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::utf8_to_wstring(utf8_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        REQUIRE(StringConverter::utf8_to_wstring(utf8_chinese) == wide_chinese);
    }
    
    SECTION("wstring_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::wstring_to_utf8(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::wstring_to_utf8(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::wstring_to_utf8(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::wstring_to_utf8(wide_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
        
        // 测试中文字符串
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        REQUIRE(StringConverter::wstring_to_utf8(wide_chinese) == utf8_chinese);
    }
    
    SECTION("ansi_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::ansi_to_wstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::ansi_to_wstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::ansi_to_wstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::ansi_to_wstring(ansi_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::ansi_to_wstring("Hello World Test") == L"Hello World Test");
    }
    
    SECTION("wstring_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::wstring_to_ansi(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::wstring_to_ansi(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::wstring_to_ansi(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::wstring_to_ansi(wide_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::wstring_to_ansi(L"Programming Test") == "Programming Test");
    }
    
    SECTION("utf8_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::utf8_to_ansi("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::utf8_to_ansi("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::utf8_to_ansi("12345") == "12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::utf8_to_ansi(utf8_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::utf8_to_ansi("Test String Conversion") == "Test String Conversion");
    }
    
    SECTION("ansi_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::ansi_to_utf8("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::ansi_to_utf8("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::ansi_to_utf8("12345") == "12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::ansi_to_utf8(ansi_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
        
        // 测试英文字符串
        REQUIRE(StringConverter::ansi_to_utf8("Testing ANSI UTF8 Conversion") == "Testing ANSI UTF8 Conversion");
    }
    
    SECTION("gb2312_to_wstring") {
        // 测试空字符串
        REQUIRE(StringConverter::gb2312_to_wstring("") == L"");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::gb2312_to_wstring("Hello") == L"Hello");
        
        // 测试数字
        REQUIRE(StringConverter::gb2312_to_wstring("12345") == L"12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::wstring wide_special = StringConverter::gb2312_to_wstring(gb2312_special);
        REQUIRE(wide_special == L"Hello! @#$%^&*()");
    }
    
    SECTION("wstring_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::wstring_to_gb2312(L"") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::wstring_to_gb2312(L"Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::wstring_to_gb2312(L"12345") == "12345");
        
        // 测试特殊字符
        std::wstring wide_special = L"Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::wstring_to_gb2312(wide_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
    }
    
    SECTION("gb2312_to_utf8") {
        // 测试空字符串
        REQUIRE(StringConverter::gb2312_to_utf8("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::gb2312_to_utf8("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::gb2312_to_utf8("12345") == "12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::string utf8_special = StringConverter::gb2312_to_utf8(gb2312_special);
        REQUIRE(utf8_special == "Hello! @#$%^&*()");
    }
    
    SECTION("utf8_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::utf8_to_gb2312("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::utf8_to_gb2312("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::utf8_to_gb2312("12345") == "12345");
        
        // 测试特殊字符
        std::string utf8_special = "Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::utf8_to_gb2312(utf8_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
    }
    
    SECTION("gb2312_to_ansi") {
        // 测试空字符串
        REQUIRE(StringConverter::gb2312_to_ansi("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::gb2312_to_ansi("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::gb2312_to_ansi("12345") == "12345");
        
        // 测试特殊字符
        std::string gb2312_special = "Hello! @#$%^&*()";
        std::string ansi_special = StringConverter::gb2312_to_ansi(gb2312_special);
        REQUIRE(ansi_special == "Hello! @#$%^&*()");
    }
    
    SECTION("ansi_to_gb2312") {
        // 测试空字符串
        REQUIRE(StringConverter::ansi_to_gb2312("") == "");
        
        // 测试ASCII字符串
        REQUIRE(StringConverter::ansi_to_gb2312("Hello") == "Hello");
        
        // 测试数字
        REQUIRE(StringConverter::ansi_to_gb2312("12345") == "12345");
        
        // 测试特殊字符
        std::string ansi_special = "Hello! @#$%^&*()";
        std::string gb2312_special = StringConverter::ansi_to_gb2312(ansi_special);
        REQUIRE(gb2312_special == "Hello! @#$%^&*()");
    }
}
