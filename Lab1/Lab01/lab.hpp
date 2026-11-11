#pragma once
#include <windows.h>
#include <string>

// Функция Show, которая вызывает стандартное окно сообщения Windows
inline void Show(const std::wstring& text, const wchar_t* title) {
    MessageBoxW(nullptr, text.c_str(), title, MB_OK | MB_ICONINFORMATION);
}