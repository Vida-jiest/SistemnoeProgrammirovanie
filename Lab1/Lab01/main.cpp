#include "lab.hpp"
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    SYSTEM_INFO info{};
    GetSystemInfo(&info);
    const wchar_t* greeting = L"Лабораторная 1 выполнена.";
    std::wstring text = greeting;
    text += L"\n\nЛогических процессоров: ";
    text += std::to_wstring(info.dwNumberOfProcessors);
    text += L"\nРазмер страницы памяти: ";
    text += std::to_wstring(info.dwPageSize) + L" байт";
    Show(text, L"Lab01 | Первое приложение");
    return 0;
}