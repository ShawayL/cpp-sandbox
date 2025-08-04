#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <cpp_sandbox/string_converter_export.hpp>
#include <string>

class STRING_CONVERTER_EXPORT StringConverter {
public:
    /**
     * 将 UTF-8 编码的 std::string 转换为 std::wstring
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring utf8_to_wstring(const std::string& utf8_str);
    
    /**
     * 将 std::wstring 转换为 UTF-8 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string wstring_to_utf8(const std::wstring& wide_str);
    
    /**
     * 将本地 ANSI 编码的 std::string 转换为 std::wstring
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring ansi_to_wstring(const std::string& ansi_str);
    
    /**
     * 将 std::wstring 转换为本地 ANSI 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string wstring_to_ansi(const std::wstring& wide_str);
    
    /**
     * 将 UTF-8 编码的 std::string 直接转换为本地 ANSI 编码的 std::string
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string utf8_to_ansi(const std::string& utf8_str);
    
    /**
     * 将本地 ANSI 编码的 std::string 直接转换为 UTF-8 编码的 std::string
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string ansi_to_utf8(const std::string& ansi_str);
    
    /**
     * 将 GB2312 编码的 std::string 转换为 std::wstring
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring gb2312_to_wstring(const std::string& gb2312_str);
    
    /**
     * 将 std::wstring 转换为 GB2312 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string wstring_to_gb2312(const std::wstring& wide_str);
    
    /**
     * 将 GB2312 编码的 std::string 转换为 UTF-8 编码的 std::string
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string gb2312_to_utf8(const std::string& gb2312_str);
    
    /**
     * 将 UTF-8 编码的 std::string 转换为 GB2312 编码的 std::string
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string utf8_to_gb2312(const std::string& utf8_str);
    
    /**
     * 将 GB2312 编码的 std::string 转换为本地 ANSI 编码的 std::string
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string gb2312_to_ansi(const std::string& gb2312_str);
    
    /**
     * 将本地 ANSI 编码的 std::string 转换为 GB2312 编码的 std::string
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string ansi_to_gb2312(const std::string& ansi_str);
};

#endif // STRING_CONVERTER_H