#include <iostream>
#include <Windows.h>
#include <wincred.h>
#include <tchar.h>

int main()
{
    CREDUI_INFO cui;
    TCHAR pszName[CREDUI_MAX_USERNAME_LENGTH + 1];
    TCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH + 1];
    BOOL fSave;
    DWORD dwErr;

    cui.cbSize = sizeof(CREDUI_INFO);
    cui.hwndParent = NULL;
    cui.pszMessageText = TEXT("Podaj dane logowania");
    cui.pszCaptionText = TEXT("Test CredUIPromptForCredentials");
    cui.hbmBanner = NULL;
    fSave = FALSE;
    SecureZeroMemory(pszName, sizeof(pszName));
    SecureZeroMemory(pszPwd, sizeof(pszPwd));

    dwErr = CredUIPromptForCredentials(
        &cui,                         // CREDUI_INFO structure
        TEXT("TheServer"),            // Target for credentials
        //   (usually a server)
        NULL,                         // Reserved
        0,                            // Reason
        pszName,                      // User name
        CREDUI_MAX_USERNAME_LENGTH + 1, // Max number of char for user name
        pszPwd,                       // Password
        CREDUI_MAX_PASSWORD_LENGTH + 1, // Max number of char for password
        &fSave,                       // State of save check box
        CREDUI_FLAGS_GENERIC_CREDENTIALS |  // flags
        CREDUI_FLAGS_ALWAYS_SHOW_UI |
        CREDUI_FLAGS_DO_NOT_PERSIST);

    if (!dwErr)
    {
        _tprintf(L"Nazwa uzytkownika: %s, haslo: %s", pszName, pszPwd);

        //  When you have finished using the credentials,
        //  erase them from memory.
        SecureZeroMemory(pszName, sizeof(pszName));
        SecureZeroMemory(pszPwd, sizeof(pszPwd));
    }
}
