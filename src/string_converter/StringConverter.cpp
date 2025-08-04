#include <cpp_sandbox/StringConverter.hpp>
#include <stdexcept>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <locale>
    #include <codecvt>
    #include <iconv.h>
    #include <errno.h>
    #include <cstring>
#endif

// 通用模板函数用于检查空字符串
template<typename T, typename Func>
static auto safe_convert(const T& input, Func converter) -> decltype(converter(input)) {
    if (input.empty()) {
        return decltype(converter(input))();
    }
    return converter(input);
}

#ifdef _WIN32
    // Windows 平台统一转换函数
    static std::wstring windows_mb_to_wstring(const std::string& input, UINT codepage, const char* operation);
    static std::string windows_wstring_to_mb(const std::wstring& input, UINT codepage, const char* operation);
    
    // Windows 平台辅助函数
    static std::wstring windows_utf8_to_wstring(const std::string& utf8_str);
    static std::string windows_wstring_to_utf8(const std::wstring& wide_str);
    static std::wstring windows_ansi_to_wstring(const std::string& ansi_str);
    static std::string windows_wstring_to_ansi(const std::wstring& wide_str);
    static std::string windows_utf8_to_ansi(const std::string& utf8_str);
    static std::string windows_ansi_to_utf8(const std::string& ansi_str);
#else
    // 非 Windows 平台辅助函数
    static std::wstring posix_utf8_to_wstring(const std::string& utf8_str);
    static std::string posix_wstring_to_utf8(const std::wstring& wide_str);
    static std::wstring posix_ansi_to_wstring(const std::string& ansi_str);
    static std::string posix_wstring_to_ansi(const std::wstring& wide_str);
    static std::string posix_utf8_to_ansi(const std::string& utf8_str);
    static std::string posix_ansi_to_utf8(const std::string& ansi_str);

    // 通用的 iconv 转换函数
    template<typename InputType, typename OutputType>
    static OutputType posix_generic_convert(const InputType& input,
                                          const char* from_encoding,
                                          const char* to_encoding);

    static std::string get_system_encoding();
#endif

std::wstring StringConverter::utf8_to_wstring(const std::string& utf8_str) {
#ifdef _WIN32
    return safe_convert(utf8_str, windows_utf8_to_wstring);
#else
    return safe_convert(utf8_str, posix_utf8_to_wstring);
#endif
}

std::string StringConverter::wstring_to_utf8(const std::wstring& wide_str) {
#ifdef _WIN32
    return safe_convert(wide_str, windows_wstring_to_utf8);
#else
    return safe_convert(wide_str, posix_wstring_to_utf8);
#endif
}

std::wstring StringConverter::ansi_to_wstring(const std::string& ansi_str) {
#ifdef _WIN32
    return safe_convert(ansi_str, windows_ansi_to_wstring);
#else
    return safe_convert(ansi_str, posix_ansi_to_wstring);
#endif
}

std::string StringConverter::wstring_to_ansi(const std::wstring& wide_str) {
#ifdef _WIN32
    return safe_convert(wide_str, windows_wstring_to_ansi);
#else
    return safe_convert(wide_str, posix_wstring_to_ansi);
#endif
}

std::string StringConverter::utf8_to_ansi(const std::string& utf8_str) {
#ifdef _WIN32
    return safe_convert(utf8_str, windows_utf8_to_ansi);
#else
    return safe_convert(utf8_str, posix_utf8_to_ansi);
#endif
}

std::string StringConverter::ansi_to_utf8(const std::string& ansi_str) {
#ifdef _WIN32
    return safe_convert(ansi_str, windows_ansi_to_utf8);
#else
    return safe_convert(ansi_str, posix_ansi_to_utf8);
#endif
}

#ifdef _WIN32

// Windows 平台统一多字节转宽字符函数
static std::wstring windows_mb_to_wstring(const std::string& input, UINT codepage, const char* operation) {
    int wide_length = MultiByteToWideChar(
        codepage, 0, input.c_str(), 
        static_cast<int>(input.length()), nullptr, 0
    );
    
    if (wide_length <= 0) {
        throw std::runtime_error(std::string("Failed to convert to wide string (") + operation + "): MultiByteToWideChar failed");
    }
    
    std::wstring wide_str(wide_length, L'\0');
    int result = MultiByteToWideChar(
        codepage, 0, input.c_str(), 
        static_cast<int>(input.length()), &wide_str[0], wide_length
    );
    
    if (result <= 0) {
        throw std::runtime_error(std::string("Failed to convert to wide string (") + operation + "): conversion failed");
    }
    
    return wide_str;
}

// Windows 平台统一宽字符转多字节函数
static std::string windows_wstring_to_mb(const std::wstring& input, UINT codepage, const char* operation) {
    int mb_length = WideCharToMultiByte(
        codepage, 0, input.c_str(), 
        static_cast<int>(input.length()), nullptr, 0, nullptr, nullptr
    );
    
    if (mb_length <= 0) {
        throw std::runtime_error(std::string("Failed to convert from wide string (") + operation + "): WideCharToMultiByte failed");
    }
    
    std::string mb_str(mb_length, '\0');
    int result = WideCharToMultiByte(
        codepage, 0, input.c_str(), 
        static_cast<int>(input.length()), &mb_str[0], mb_length, nullptr, nullptr
    );
    
    if (result <= 0) {
        throw std::runtime_error(std::string("Failed to convert from wide string (") + operation + "): conversion failed");
    }
    
    return mb_str;
}

static std::wstring windows_utf8_to_wstring(const std::string& utf8_str) {
    return windows_mb_to_wstring(utf8_str, CP_UTF8, "UTF-8 to Unicode");
}

static std::string windows_wstring_to_utf8(const std::wstring& wide_str) {
    return windows_wstring_to_mb(wide_str, CP_UTF8, "Unicode to UTF-8");
}

static std::wstring windows_ansi_to_wstring(const std::string& ansi_str) {
    return windows_mb_to_wstring(ansi_str, CP_ACP, "ANSI to Unicode");
}

static std::string windows_wstring_to_ansi(const std::wstring& wide_str) {
    return windows_wstring_to_mb(wide_str, CP_ACP, "Unicode to ANSI");
}

static std::string windows_utf8_to_ansi(const std::string& utf8_str) {
    // UTF-8 -> Unicode -> ANSI
    std::wstring wide_str = windows_utf8_to_wstring(utf8_str);
    return windows_wstring_to_ansi(wide_str);
}

static std::string windows_ansi_to_utf8(const std::string& ansi_str) {
    // ANSI -> Unicode -> UTF-8
    std::wstring wide_str = windows_ansi_to_wstring(ansi_str);
    return windows_wstring_to_utf8(wide_str);
}

#else // 非 Windows 平台

static std::wstring posix_utf8_to_wstring(const std::string& utf8_str) {
    return posix_generic_convert<std::string, std::wstring>(utf8_str, "UTF-8", "WCHAR_T");
}

static std::string posix_wstring_to_utf8(const std::wstring& wide_str) {
    return posix_generic_convert<std::wstring, std::string>(wide_str, "WCHAR_T", "UTF-8");
}

static std::wstring posix_ansi_to_wstring(const std::string& ansi_str) {
    std::string system_encoding = get_system_encoding();
    return posix_generic_convert<std::string, std::wstring>(ansi_str, system_encoding.c_str(), "WCHAR_T");
}

static std::string posix_wstring_to_ansi(const std::wstring& wide_str) {
    std::string system_encoding = get_system_encoding();
    return posix_generic_convert<std::wstring, std::string>(wide_str, "WCHAR_T", system_encoding.c_str());
}

static std::string posix_utf8_to_ansi(const std::string& utf8_str) {
    std::string system_encoding = get_system_encoding();
    return posix_generic_convert<std::string, std::string>(utf8_str, "UTF-8", system_encoding.c_str());
}

static std::string posix_ansi_to_utf8(const std::string& ansi_str) {
    std::string system_encoding = get_system_encoding();
    return posix_generic_convert<std::string, std::string>(ansi_str, system_encoding.c_str(), "UTF-8");
}

template<typename InputType, typename OutputType>
static OutputType posix_generic_convert(const InputType& input,
                                       const char* from_encoding,
                                       const char* to_encoding) {
    if (input.empty()) {
        return OutputType();
    }
    
    // 如果源编码和目标编码相同，且类型相同，直接返回
    if (std::is_same_v<InputType, OutputType> && strcmp(from_encoding, to_encoding) == 0) {
        if constexpr (std::is_same_v<InputType, OutputType>) {
            return input;
        }
    }
    
    iconv_t cd = iconv_open(to_encoding, from_encoding);
    if (cd == (iconv_t)-1) {
        throw std::runtime_error("Failed to open iconv from " + std::string(from_encoding) + 
                                " to " + std::string(to_encoding) + ": " + std::string(strerror(errno)));
    }
    
    // 准备输入缓冲区
    size_t in_bytes_left;
    char* in_buf;
    
    if constexpr (std::is_same_v<InputType, std::string>) {
        in_bytes_left = input.length();
        in_buf = const_cast<char*>(input.c_str());
    } else { // std::wstring
        in_bytes_left = input.length() * sizeof(wchar_t);
        in_buf = reinterpret_cast<char*>(const_cast<wchar_t*>(input.c_str()));
    }
    
    // 准备输出缓冲区
    size_t out_buf_size;
    if constexpr (std::is_same_v<OutputType, std::string>) {
        out_buf_size = input.length() * 4; // 足够大的缓冲区
    } else { // std::wstring
        out_buf_size = input.length() * sizeof(wchar_t) * 2; // 足够大的缓冲区
    }
    
    size_t out_bytes_left = out_buf_size;
    std::vector<char> temp_output(out_buf_size);
    char* out_buf = temp_output.data();
    
    // 执行转换
    size_t result = iconv(cd, &in_buf, &in_bytes_left, &out_buf, &out_bytes_left);
    
    if (result == (size_t)-1) {
        int error_code = errno;
        iconv_close(cd);
        throw std::runtime_error("Failed to convert from " + std::string(from_encoding) + 
                                " to " + std::string(to_encoding) + ": " + std::string(strerror(error_code)));
    }
    
    iconv_close(cd);
    
    // 构造输出
    size_t converted_bytes = out_buf_size - out_bytes_left;
    
    if constexpr (std::is_same_v<OutputType, std::string>) {
        return std::string(temp_output.data(), converted_bytes);
    } else { // std::wstring
        size_t wchar_count = converted_bytes / sizeof(wchar_t);
        return std::wstring(reinterpret_cast<wchar_t*>(temp_output.data()), wchar_count);
    }
}

static std::string get_system_encoding() {
    // 获取系统默认编码
    const char* lang = std::getenv("LANG");
    if (lang) {
        std::string lang_str(lang);
        size_t dot_pos = lang_str.find('.');
        if (dot_pos != std::string::npos) {
            std::string encoding = lang_str.substr(dot_pos + 1);
            size_t at_pos = encoding.find('@');
            if (at_pos != std::string::npos) {
                encoding = encoding.substr(0, at_pos);
            }
            if (!encoding.empty()) {
                return encoding;
            }
        }
    }
    
    // 检查 LC_CTYPE
    const char* lc_ctype = std::getenv("LC_CTYPE");
    if (lc_ctype) {
        std::string lc_str(lc_ctype);
        size_t dot_pos = lc_str.find('.');
        if (dot_pos != std::string::npos) {
            std::string encoding = lc_str.substr(dot_pos + 1);
            size_t at_pos = encoding.find('@');
            if (at_pos != std::string::npos) {
                encoding = encoding.substr(0, at_pos);
            }
            if (!encoding.empty()) {
                return encoding;
            }
        }
    }
    
    // 默认编码
    return "UTF-8";
}

#endif