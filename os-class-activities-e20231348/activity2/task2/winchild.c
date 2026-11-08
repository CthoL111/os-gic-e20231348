/* winchild.c — Process creation with Win32 CreateProcess() */
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu) — Launching mspaint.exe...\n", GetCurrentProcessId());

    if (!CreateProcess(
        _T("C:\\Windows\\System32\\mspaint.exe"), 
        NULL,                                    
        NULL,                                    
        NULL,                                    
        FALSE,                                   
        0,                                       
        NULL,                                    
        NULL,                                    
        &si,                                     
        &pi                                      
    )) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    printf("Child process launched successfully!\n");
    printf("Child PID: %lu\n", pi.dwProcessId);
    
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Child process has closed. Parent exiting.\n");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
