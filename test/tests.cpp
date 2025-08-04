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
        
        // 测试中文字符串（注意：ANSI转换依赖于系统locale）
        // 使用已知的宽字符串，转换为ANSI再转回宽字符串进行往返测试
        std::wstring wide_original = L"\u4F60\u597D\u4E16\u754C"; // "你好世界"
        std::string ansi_converted = StringConverter::wstring_to_ansi(wide_original);
        REQUIRE(!ansi_converted.empty());
        // 测试往返转换的一致性
        std::wstring wide_roundtrip = StringConverter::ansi_to_wstring(ansi_converted);
        REQUIRE(wide_roundtrip == wide_original);
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
        
        // 测试中文字符串（注意：ANSI转换可能依赖于系统locale，这里测试基本转换功能）
        // "你好世界" 的 Unicode 码点
        std::wstring wide_chinese = L"\u4F60\u597D\u4E16\u754C";
        std::string ansi_chinese = StringConverter::wstring_to_ansi(wide_chinese);
        // 注意：ANSI编码结果取决于系统locale设置
        REQUIRE(!ansi_chinese.empty());
        // 测试往返转换的一致性
        std::wstring wide_roundtrip = StringConverter::ansi_to_wstring(ansi_chinese);
        REQUIRE(wide_roundtrip == wide_chinese);
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
        
        // 测试中文字符串
        // "你好世界" 的 UTF-8 编码
        std::string utf8_chinese = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c";
        std::string ansi_chinese = StringConverter::utf8_to_ansi(utf8_chinese);
        // 注意：ANSI编码结果取决于系统locale设置
        REQUIRE(!ansi_chinese.empty());
        // 测试往返转换的一致性
        std::string utf8_roundtrip = StringConverter::ansi_to_utf8(ansi_chinese);
        REQUIRE(utf8_roundtrip == utf8_chinese);
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
        
        // 测试中文字符串（注意：需要系统支持相应的ANSI编码）
        // 使用已知的UTF-8字符串，转换为ANSI再转回UTF-8进行往返测试
        std::string utf8_original = "\xe4\xbd\xa0\xe5\xa5\xbd\xe4\xb8\x96\xe7\x95\x8c"; // "你好世界"
        std::string ansi_converted = StringConverter::utf8_to_ansi(utf8_original);
        REQUIRE(!ansi_converted.empty());
        // 测试往返转换的一致性
        std::string utf8_roundtrip = StringConverter::ansi_to_utf8(ansi_converted);
        REQUIRE(utf8_roundtrip == utf8_original);
    }
}
