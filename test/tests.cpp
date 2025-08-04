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
        std::string utf8_chinese = "你好世界";
        std::wstring wide_chinese = L"你好世界";
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
        std::wstring wide_chinese = L"你好世界";
        std::string utf8_chinese = "你好世界";
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
        
        // 测试简单英文句子
        std::string ansi_sentence = "Welcome to C++ world!";
        std::wstring wide_sentence = L"Welcome to C++ world!";
        REQUIRE(StringConverter::ansi_to_wstring(ansi_sentence) == wide_sentence);
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
        
        // 测试简单英文句子
        std::wstring wide_sentence = L"Welcome to C++ world!";
        std::string ansi_sentence = "Welcome to C++ world!";
        REQUIRE(StringConverter::wstring_to_ansi(wide_sentence) == ansi_sentence);
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
        
        // 测试简单英文句子
        std::string utf8_sentence = "Welcome to C++ world!";
        std::string ansi_sentence = "Welcome to C++ world!";
        REQUIRE(StringConverter::utf8_to_ansi(utf8_sentence) == ansi_sentence);
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
        
        // 测试简单英文句子
        std::string ansi_sentence = "Welcome to C++ world!";
        std::string utf8_sentence = "Welcome to C++ world!";
        REQUIRE(StringConverter::ansi_to_utf8(ansi_sentence) == utf8_sentence);
    }
}
