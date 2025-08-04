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

// 私有辅助函数声明
#ifdef _WIN32
    // Windows 平台辅助函数
    static std::wstring windows_utf8_to_wstring(const std::string& utf8_str);
    static std::string windows_wstring_to_utf8(const std::wstring& wide_str);
    static std::wstring windows_ansi_to_wstring(const std::string& ansi_str);
    static std::string windows_wstring_to_ansi(const std::wstring& wide_str);
    static std::string windows_utf8_to_ansi_direct(const std::string& utf8_str);
    static std::string windows_ansi_to_utf8_direct(const std::string& ansi_str);
#else
    // 非 Windows 平台辅助函数
    static std::wstring posix_utf8_to_wstring(const std::string& utf8_str);
    static std::string posix_wstring_to_utf8(const std::wstring& wide_str);
    static std::wstring posix_ansi_to_wstring(const std::string& ansi_str);
    static std::string posix_wstring_to_ansi(const std::wstring& wide_str);
    static std::string posix_utf8_to_ansi_direct(const std::string& utf8_str);
    static std::string posix_ansi_to_utf8_direct(const std::string& ansi_str);
    static std::string posix_convert_encoding(const std::string& input, 
                                            const char* from_encoding, 
                                            const char* to_encoding);
    static std::string get_system_encoding();
#endif

std::wstring StringConverter::utf8_to_wstring(const std::string& utf8_str) {
    if (utf8_str.empty()) {
        return std::wstring();
    }
    
#ifdef _WIN32
    return ::windows_utf8_to_wstring(utf8_str);
#else
    return ::posix_utf8_to_wstring(utf8_str);
#endif
}

std::string StringConverter::wstring_to_utf8(const std::wstring& wide_str) {
    if (wide_str.empty()) {
        return std::string();
    }
    
#ifdef _WIN32
    return ::windows_wstring_to_utf8(wide_str);
#else
    return ::posix_wstring_to_utf8(wide_str);
#endif
}

std::wstring StringConverter::ansi_to_wstring(const std::string& ansi_str) {
    if (ansi_str.empty()) {
        return std::wstring();
    }
    
#ifdef _WIN32
    return ::windows_ansi_to_wstring(ansi_str);
#else
    return ::posix_ansi_to_wstring(ansi_str);
#endif
}

std::string StringConverter::wstring_to_ansi(const std::wstring& wide_str) {
    if (wide_str.empty()) {
        return std::string();
    }
    
#ifdef _WIN32
    return ::windows_wstring_to_ansi(wide_str);
#else
    return ::posix_wstring_to_ansi(wide_str);
#endif
}

std::string StringConverter::utf8_to_ansi(const std::string& utf8_str) {
    if (utf8_str.empty()) {
        return std::string();
    }
    
#ifdef _WIN32
    return ::windows_utf8_to_ansi_direct(utf8_str);
#else
    return ::posix_utf8_to_ansi_direct(utf8_str);
#endif
}

std::string StringConverter::ansi_to_utf8(const std::string& ansi_str) {
    if (ansi_str.empty()) {
        return std::string();
    }
    
#ifdef _WIN32
    return ::windows_ansi_to_utf8_direct(ansi_str);
#else
    return ::posix_ansi_to_utf8_direct(ansi_str);
#endif
}

#ifdef _WIN32

static std::wstring windows_utf8_to_wstring(const std::string& utf8_str) {
    int wide_length = MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), 
        static_cast<int>(utf8_str.length()), nullptr, 0
    );
    
    if (wide_length <= 0) {
        throw std::runtime_error("Failed to convert UTF-8 to wide string: MultiByteToWideChar failed");
    }
    
    std::wstring wide_str(wide_length, L'\0');
    int result = MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), 
        static_cast<int>(utf8_str.length()), &wide_str[0], wide_length
    );
    
    if (result <= 0) {
        throw std::runtime_error("Failed to convert UTF-8 to wide string: conversion failed");
    }
    
    return wide_str;
}

static std::string windows_wstring_to_utf8(const std::wstring& wide_str) {
    int utf8_length = WideCharToMultiByte(
        CP_UTF8, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), nullptr, 0, nullptr, nullptr
    );
    
    if (utf8_length <= 0) {
        throw std::runtime_error("Failed to convert wide string to UTF-8: WideCharToMultiByte failed");
    }
    
    std::string utf8_str(utf8_length, '\0');
    int result = WideCharToMultiByte(
        CP_UTF8, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), &utf8_str[0], utf8_length, nullptr, nullptr
    );
    
    if (result <= 0) {
        throw std::runtime_error("Failed to convert wide string to UTF-8: conversion failed");
    }
    
    return utf8_str;
}

static std::wstring windows_ansi_to_wstring(const std::string& ansi_str) {
    int wide_length = MultiByteToWideChar(
        CP_ACP, 0, ansi_str.c_str(), 
        static_cast<int>(ansi_str.length()), nullptr, 0
    );
    
    if (wide_length <= 0) {
        throw std::runtime_error("Failed to convert ANSI to wide string: MultiByteToWideChar failed");
    }
    
    std::wstring wide_str(wide_length, L'\0');
    int result = MultiByteToWideChar(
        CP_ACP, 0, ansi_str.c_str(), 
        static_cast<int>(ansi_str.length()), &wide_str[0], wide_length
    );
    
    if (result <= 0) {
        throw std::runtime_error("Failed to convert ANSI to wide string: conversion failed");
    }
    
    return wide_str;
}

static std::string windows_wstring_to_ansi(const std::wstring& wide_str) {
    int ansi_length = WideCharToMultiByte(
        CP_ACP, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), nullptr, 0, nullptr, nullptr
    );
    
    if (ansi_length <= 0) {
        throw std::runtime_error("Failed to convert wide string to ANSI: WideCharToMultiByte failed");
    }
    
    std::string ansi_str(ansi_length, '\0');
    int result = WideCharToMultiByte(
        CP_ACP, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), &ansi_str[0], ansi_length, nullptr, nullptr
    );
    
    if (result <= 0) {
        throw std::runtime_error("Failed to convert wide string to ANSI: conversion failed");
    }
    
    return ansi_str;
}

// 直接转换：UTF-8 -> ANSI (Windows)
static std::string windows_utf8_to_ansi_direct(const std::string& utf8_str) {
    // 方法1：使用双重转换（更可靠）
    // UTF-8 -> Unicode -> ANSI
    
    // 步骤1：UTF-8 -> Unicode
    int wide_length = MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), 
        static_cast<int>(utf8_str.length()), nullptr, 0
    );
    
    if (wide_length <= 0) {
        throw std::runtime_error("Failed UTF-8 to ANSI: UTF-8 to Unicode conversion failed");
    }
    
    std::wstring wide_str(wide_length, L'\0');
    int result1 = MultiByteToWideChar(
        CP_UTF8, 0, utf8_str.c_str(), 
        static_cast<int>(utf8_str.length()), &wide_str[0], wide_length
    );
    
    if (result1 <= 0) {
        throw std::runtime_error("Failed UTF-8 to ANSI: UTF-8 to Unicode conversion failed");
    }
    
    // 步骤2：Unicode -> ANSI
    int ansi_length = WideCharToMultiByte(
        CP_ACP, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), nullptr, 0, nullptr, nullptr
    );
    
    if (ansi_length <= 0) {
        throw std::runtime_error("Failed UTF-8 to ANSI: Unicode to ANSI conversion failed");
    }
    
    std::string ansi_str(ansi_length, '\0');
    int result2 = WideCharToMultiByte(
        CP_ACP, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), &ansi_str[0], ansi_length, nullptr, nullptr
    );
    
    if (result2 <= 0) {
        throw std::runtime_error("Failed UTF-8 to ANSI: Unicode to ANSI conversion failed");
    }
    
    return ansi_str;
}

// 直接转换：ANSI -> UTF-8 (Windows)
static std::string windows_ansi_to_utf8_direct(const std::string& ansi_str) {
    // ANSI -> Unicode -> UTF-8
    
    // 步骤1：ANSI -> Unicode
    int wide_length = MultiByteToWideChar(
        CP_ACP, 0, ansi_str.c_str(), 
        static_cast<int>(ansi_str.length()), nullptr, 0
    );
    
    if (wide_length <= 0) {
        throw std::runtime_error("Failed ANSI to UTF-8: ANSI to Unicode conversion failed");
    }
    
    std::wstring wide_str(wide_length, L'\0');
    int result1 = MultiByteToWideChar(
        CP_ACP, 0, ansi_str.c_str(), 
        static_cast<int>(ansi_str.length()), &wide_str[0], wide_length
    );
    
    if (result1 <= 0) {
        throw std::runtime_error("Failed ANSI to UTF-8: ANSI to Unicode conversion failed");
    }
    
    // 步骤2：Unicode -> UTF-8
    int utf8_length = WideCharToMultiByte(
        CP_UTF8, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), nullptr, 0, nullptr, nullptr
    );
    
    if (utf8_length <= 0) {
        throw std::runtime_error("Failed ANSI to UTF-8: Unicode to UTF-8 conversion failed");
    }
    
    std::string utf8_str(utf8_length, '\0');
    int result2 = WideCharToMultiByte(
        CP_UTF8, 0, wide_str.c_str(), 
        static_cast<int>(wide_str.length()), &utf8_str[0], utf8_length, nullptr, nullptr
    );
    
    if (result2 <= 0) {
        throw std::runtime_error("Failed ANSI to UTF-8: Unicode to UTF-8 conversion failed");
    }
    
    return utf8_str;
}

#else // 非 Windows 平台

static std::wstring posix_utf8_to_wstring(const std::string& utf8_str) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(utf8_str);
    } catch (const std::range_error& e) {
        throw std::runtime_error("Failed to convert UTF-8 to wide string: " + std::string(e.what()));
    }
}

static std::string posix_wstring_to_utf8(const std::wstring& wide_str) {
    try {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wide_str);
    } catch (const std::range_error& e) {
        throw std::runtime_error("Failed to convert wide string to UTF-8: " + std::string(e.what()));
    }
}

static std::wstring posix_ansi_to_wstring(const std::string& ansi_str) {
    // ANSI -> UTF-8 -> wstring
    std::string utf8_str = posix_ansi_to_utf8_direct(ansi_str);
    return posix_utf8_to_wstring(utf8_str);
}

static std::string posix_wstring_to_ansi(const std::wstring& wide_str) {
    // wstring -> UTF-8 -> ANSI
    std::string utf8_str = posix_wstring_to_utf8(wide_str);
    return posix_utf8_to_ansi_direct(utf8_str);
}

// 直接转换：UTF-8 -> ANSI (Linux/Unix)
static std::string posix_utf8_to_ansi_direct(const std::string& utf8_str) {
    std::string system_encoding = get_system_encoding();
    return posix_convert_encoding(utf8_str, "UTF-8", system_encoding.c_str());
}

// 直接转换：ANSI -> UTF-8 (Linux/Unix)
static std::string posix_ansi_to_utf8_direct(const std::string& ansi_str) {
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