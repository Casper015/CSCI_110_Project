#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Executable: " << argv[0] << endl;
    // Check for Microsoft Visual C++
#if defined(_MSC_VER)
    cout << "Microsoft Visual C++ (MSVC) version: " << _MSC_FULL_VER << endl;
    cout << "C++ Standard Version: " << _MSVC_LANG << endl;
#else
    // Check for Clang (must be before GCC check as Clang defines __GNUC__ too)
#if defined(__clang__)
    cout << "Clang version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << endl;
    // Check for GCC (GNU Compiler Collection)
#elif defined(__GNUC__)
    cout << "GCC version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << endl;
    // Check for Intel C++ Compiler
#elif defined(__INTEL_COMPILER)
    cout << "Intel C++ Compiler version: " << __INTEL_COMPILER << endl;
#else
    cout << "Unknown compiler or version information not available via macros.\n";
#endif
    cout << "C++ Standard Version: " << __cplusplus << endl;
#endif
}