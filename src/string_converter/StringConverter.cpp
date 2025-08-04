#include <cpp_sandbox/StringConverter.hpp>
#include <stdexcept>

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
    static std::string posix_convert_encoding(const std::string& input, 
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

// 直接转换：UTF-8 -> ANSI (Windows)
static std::string windows_utf8_to_ansi(const std::string& utf8_str) {
    // UTF-8 -> Unicode -> ANSI
    std::wstring wide_str = windows_utf8_to_wstring(utf8_str);
    return windows_wstring_to_ansi(wide_str);
}

// 直接转换：ANSI -> UTF-8 (Windows)
static std::string windows_ansi_to_utf8(const std::string& ansi_str) {
    // ANSI -> Unicode -> UTF-8
    std::wstring wide_str = windows_ansi_to_wstring(ansi_str);
    return windows_wstring_to_utf8(wide_str);
}

#else // 非 Windows 平台

// POSIX 平台安全转换包装器
template<typename Converter>
static auto posix_safe_convert(Converter converter, const char* operation) {
    return [converter, operation](const auto& input) {
        try {
            return converter(input);
        } catch (const std::range_error& e) {
            throw std::runtime_error(std::string("Failed to ") + operation + ": " + e.what());
        }
    };
}

static std::wstring posix_utf8_to_wstring(const std::string& utf8_str) {
    auto converter = posix_safe_convert(
        [](const std::string& str) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            return conv.from_bytes(str);
        }, 
        "convert UTF-8 to wide string"
    );
    return converter(utf8_str);
}

static std::string posix_wstring_to_utf8(const std::wstring& wide_str) {
    auto converter = posix_safe_convert(
        [](const std::wstring& str) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            return conv.to_bytes(str);
        }, 
        "convert wide string to UTF-8"
    );
    return converter(wide_str);
}

static std::wstring posix_ansi_to_wstring(const std::string& ansi_str) {
    // ANSI -> UTF-8 -> wstring
    std::string utf8_str = posix_ansi_to_utf8(ansi_str);
    return posix_utf8_to_wstring(utf8_str);
}

static std::string posix_wstring_to_ansi(const std::wstring& wide_str) {
    // wstring -> UTF-8 -> ANSI
    std::string utf8_str = posix_wstring_to_utf8(wide_str);
    return posix_utf8_to_ansi(utf8_str);
}

// 直接转换：UTF-8 -> ANSI (Linux/Unix)
static std::string posix_utf8_to_ansi(const std::string& utf8_str) {
    std::string system_encoding = get_system_encoding();
    return posix_convert_encoding(utf8_str, "UTF-8", system_encoding.c_str());
}

// 直接转换：ANSI -> UTF-8 (Linux/Unix)
static std::string posix_ansi_to_utf8(const std::string& ansi_str) {
    std::string system_encoding = get_system_encoding();
    return posix_convert_encoding(ansi_str, system_encoding.c_str(), "UTF-8");
}

static std::string posix_convert_encoding(const std::string& input, 
                                         const char* from_encoding, 
                                         const char* to_encoding) {
    if (input.empty()) {
        return std::string();
    }
    
    // 如果源编码和目标编码相同，直接返回
    if (strcmp(from_encoding, to_encoding) == 0) {
        return input;
    }
    
    iconv_t cd = iconv_open(to_encoding, from_encoding);
    if (cd == (iconv_t)-1) {
        throw std::runtime_error("Failed to open iconv from " + std::string(from_encoding) + 
                                " to " + std::string(to_encoding) + ": " + std::string(strerror(errno)));
    }
    
    // 输入缓冲区
    size_t in_bytes_left = input.length();
    char* in_buf = const_cast<char*>(input.c_str());
    
    // 输出缓冲区（预分配足够的空间）
    size_t out_bytes_left = input.length() * 4; // 足够大的缓冲区
    size_t out_buf_size = out_bytes_left;
    std::string output(out_buf_size, '\0');
    char* out_buf = &output[0];
    
    // 执行转换
    size_t result = iconv(cd, &in_buf, &in_bytes_left, &out_buf, &out_bytes_left);
    
    if (result == (size_t)-1) {
        int error_code = errno;
        iconv_close(cd);
        throw std::runtime_error("Failed to convert from " + std::string(from_encoding) + 
                                " to " + std::string(to_encoding) + ": " + std::string(strerror(error_code)));
    }
    
    iconv_close(cd);
    
    // 调整输出字符串大小
    size_t converted_bytes = out_buf_size - out_bytes_left;
    output.resize(converted_bytes);
    
    return output;
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