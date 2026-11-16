#include "lab.hpp"
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    std::wstring path = BesideExe(L"MathLib.dll");
    HMODULE dll = LoadLibraryExW(path.c_str(), nullptr,
        LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
    if (!dll) return Fail(L"LoadLibraryExW");
    using AddFunction = int (__cdecl*)(int, int);
    auto add = reinterpret_cast<AddFunction>(GetProcAddress(dll, "Add"));
    if (!add) { DWORD e = GetLastError(); FreeLibrary(dll); return Fail(L"GetProcAddress", e); }
    const int a = 20, b = 22;
    int result = add(a, b);
    FreeLibrary(dll);
    Show(L"DLL загружена, функция Add вызвана.\n\n" + std::to_wstring(a)
        + L" + " + std::to_wstring(b) + L" = " + std::to_wstring(result),
        L"Lab03 | Динамическая библиотека");
    return 0;
}
