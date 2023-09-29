#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

DWORD returnProcessIdByName(const wchar_t* processName) {
    DWORD processId = 0; // Initialize the process ID to 0.

    // Determine if the current process is 32-bit or 64-bit.
    BOOL isWow64 = FALSE;
    IsWow64Process(GetCurrentProcess(), &isWow64);

    // Create a snapshot of the currently running processes based on the system architecture.
    DWORD snapshotFlags = isWow64 ? TH32CS_SNAPPROCESS : TH32CS_SNAPPROCESS | TH32CS_SNAPALL;
    HANDLE snapshot = CreateToolhelp32Snapshot(snapshotFlags, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32W);

        // Start iterating through the list of processes.
        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                // Compare the name of each process with the target process name.
                if (_wcsicmp(processEntry.szExeFile, processName) == 0) {
                    processId = processEntry.th32ProcessID; // Store the process ID when a match is found.
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry)); // Move to the next process in the list.
        }

        CloseHandle(snapshot); // Close the process snapshot.
    }
    else {
        std::cerr << "Error creating snapshot." << std::endl;
    }

    return processId;
}

int main() {
    DWORD processId = returnProcessIdByName(L"YourProcessName.exe"); // Change "YourProcessName" with the process name here

    if (processId != 0) {
        std::wcout << L"Found process ID: " << processId << std::endl;
    }
    else {
        std::wcout << L"Process not found." << std::endl;
    }

    return 0;
}
