#pragma once

void ChangeCaption(TCHAR* Path);
void ModifingCaption(TCHAR* Path);
int ConfirmSave();
BOOL Save();
BOOL SaveAs();
BOOL SaveToFile(TCHAR* Path);
void Load();