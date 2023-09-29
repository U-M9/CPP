#include <iostream>
#include <windows.h>
#include <commdlg.h>

// Function to open a file dialog and return the selected file's path.
std::wstring getFileFromDialog() {
    // Initialize the OPENFILENAME structure.
    OPENFILENAME ofn;
    wchar_t szFile[260] = L""; // Buffer for the file name.

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL; // If you have a window handle, you can set it here.
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Open the file dialog.
    if (GetOpenFileName(&ofn) == TRUE) {
        return ofn.lpstrFile;
    }
    else {
        DWORD dwError = CommDlgExtendedError();
        if (dwError != 0) {
            std::cerr << "Error: " << dwError << std::endl;
        }
        else {
            std::cerr << "File dialog canceled by the user." << std::endl;
        }

        return L""; // Return an empty string on error or cancellation.
    }
}

int main() {
    // Call the function to open the file dialog and get the selected file's path.
    std::wstring filePath = getFileFromDialog();

    // Check if a file was selected.
    if (!filePath.empty()) {
        std::wcout << L"Selected File: " << filePath << std::endl;
    }

    return 0;
}
