#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <cpp_sandbox/string_converter/string_converter_export.hpp>
#include <string>

class STRING_CONVERTER_EXPORT StringConverter {
public:
    /**
     * 将 UTF-8 编码的 std::string 转换为 std::wstring
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring Utf8ToWstring(const std::string& utf8_str);

    /**
     * 将 std::wstring 转换为 UTF-8 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string WstringToUtf8(const std::wstring& wide_str);

    /**
     * 将本地 ANSI 编码的 std::string 转换为 std::wstring
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring AnsiToWstring(const std::string& ansi_str);

    /**
     * 将 std::wstring 转换为本地 ANSI 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string WstringToAnsi(const std::wstring& wide_str);

    /**
     * 将 UTF-8 编码的 std::string 直接转换为本地 ANSI 编码的 std::string
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string Utf8ToAnsi(const std::string& utf8_str);

    /**
     * 将本地 ANSI 编码的 std::string 直接转换为 UTF-8 编码的 std::string
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string AnsiToUtf8(const std::string& ansi_str);

    /**
     * 将 GB2312 编码的 std::string 转换为 std::wstring
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的宽字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::wstring Gb2312ToWstring(const std::string& gb2312_str);

    /**
     * 将 std::wstring 转换为 GB2312 编码的 std::string
     * @param wide_str 宽字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string WstringToGb2312(const std::wstring& wide_str);

    /**
     * 将 GB2312 编码的 std::string 转换为 UTF-8 编码的 std::string
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的 UTF-8 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string Gb2312ToUtf8(const std::string& gb2312_str);

    /**
     * 将 UTF-8 编码的 std::string 转换为 GB2312 编码的 std::string
     * @param utf8_str UTF-8 编码的字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string Utf8ToGb2312(const std::string& utf8_str);

    /**
     * 将 GB2312 编码的 std::string 转换为本地 ANSI 编码的 std::string
     * @param gb2312_str GB2312 编码的字符串
     * @return 转换后的本地 ANSI 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string Gb2312ToAnsi(const std::string& gb2312_str);

    /**
     * 将本地 ANSI 编码的 std::string 转换为 GB2312 编码的 std::string
     * @param ansi_str 本地 ANSI 编码的字符串
     * @return 转换后的 GB2312 编码字符串
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::string AnsiToGb2312(const std::string& ansi_str);

    /**
     * 获取当前系统的 ANSI 代码页
     * @return 当前 ANSI 代码页编号，在非 Windows 系统上返回 0
     */
    static unsigned int GetAnsiCodepage();
};

#endif // STRING_CONVERTER_H
