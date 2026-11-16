#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <string>

inline void Show(const std::wstring& message,
                 const wchar_t* title = L"Lab03") {
    MessageBoxW(nullptr, message.c_str(), title, MB_OK | MB_ICONINFORMATION);
}

inline int Fail(const wchar_t* operation, DWORD error = GetLastError()) {
    wchar_t description[2048] = {};
    const DWORD length = FormatMessageW(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, error, 0, description,
        static_cast<DWORD>(sizeof(description) / sizeof(description[0])),
        nullptr);

    std::wstring message = std::wstring(operation)
        + L"\nКод ошибки: " + std::to_wstring(error);
    if (length != 0) {
        message += L"\n\n";
        message.append(description, length);
    }

    MessageBoxW(nullptr, message.c_str(), L"Lab03 | Ошибка",
                MB_OK | MB_ICONERROR);
    SetLastError(error);
    return 1;
}

// Путь к DLL строится от папки EXE, независимо от рабочей папки.
// При ошибке возвращается пустая строка; код доступен через GetLastError().
inline std::wstring BesideExe(const wchar_t* filename) {
    std::wstring path(32768, L'\0');
    const DWORD length = GetModuleFileNameW(
        nullptr, path.data(), static_cast<DWORD>(path.size()));
    if (length == 0) {
        return {};
    }
    if (length >= path.size()) {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return {};
    }

    path.resize(length);
    const std::wstring::size_type separator = path.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        SetLastError(ERROR_BAD_PATHNAME);
        return {};
    }

    path.resize(separator + 1);
    path += filename;
    return path;
}
