//@模块名称  大漠模块  
//@版本  大漠版本 7.2               
//@日期  2021-4-13
//@作者  情缘  
//@模块备注 封装大漠相应功能



//@隐藏{
typedef int(_stdcall* DM_CreateDM)(const wchar_t*);
typedef int(_stdcall* DM_FreeDM)();
typedef const wchar_t* (_stdcall* DM_Ver)(int);
typedef int(_stdcall* DM_SetPath)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_Ocr)(int, int, int, int, int, const wchar_t*, double);
typedef int(_stdcall* DM_FindStr)(int, int, int, int, int, const wchar_t*, double, int*, int*);
typedef int(_stdcall* DM_GetResultCount)(int, const wchar_t*);
typedef int(_stdcall* DM_GetResultPos)(int, const wchar_t*,int, int*, int*);
typedef int(_stdcall* DM_StrStr)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SendCommand)(int, const wchar_t*);
typedef int(_stdcall* DM_UseDict)(int, int);
typedef const wchar_t* (_stdcall* DM_GetBasePath)(int);
typedef int(_stdcall* DM_SetDictPwd)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_OcrInFile)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef int(_stdcall* DM_Capture)(int, int, int, int, int, const wchar_t*);
typedef int(_stdcall* DM_KeyPress)(int, int);
typedef int(_stdcall* DM_KeyDown)(int, int);
typedef int(_stdcall* DM_KeyUp)(int, int);
typedef int(_stdcall* DM_LeftClick)(int);
typedef int(_stdcall* DM_RightClick)(int);
typedef int(_stdcall* DM_MiddleClick)(int);
typedef int(_stdcall* DM_LeftDoubleClick)(int);
typedef int(_stdcall* DM_LeftDown)(int);
typedef int(_stdcall* DM_LeftUp)(int);
typedef int(_stdcall* DM_RightDown)(int);
typedef int(_stdcall* DM_RightUp)(int);
typedef int(_stdcall* DM_MoveTo)(int, int, int);
typedef int(_stdcall* DM_MoveR)(int, int, int);
typedef const wchar_t* (_stdcall* DM_GetColor)(int, int, int);
typedef const wchar_t* (_stdcall* DM_GetColorBGR)(int, int, int);
typedef const wchar_t* (_stdcall* DM_RGB2BGR)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_BGR2RGB)(int, const wchar_t*);
typedef int(_stdcall* DM_UnBindWindow)(int);
typedef int (_stdcall* DM_CmpColor)(int, int, int,  const wchar_t*, double);
typedef int(_stdcall* DM_ClientToScreen)(int,int, int*, int*);
typedef int(_stdcall* DM_ScreenToClient)(int, int, int*, int*);
typedef int(_stdcall* DM_ShowScrMsg)(int, int, int, int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SetMinRowGap)(int, int);
typedef int(_stdcall* DM_SetMinColGap)(int, int);
typedef int(_stdcall* DM_FindColor)(int, int, int, int, int, const wchar_t*, double,int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindColorEx)(int, int, int, int, int, const wchar_t*, double, int);
typedef int(_stdcall* DM_SetWordLineHeight)(int, int);
typedef int(_stdcall* DM_SetWordGap)(int, int);
typedef int(_stdcall* DM_SetRowGapNoDict)(int, int);
typedef int(_stdcall* DM_SetWordLineHeightNoDict)(int, int);
typedef int(_stdcall* DM_SetWordGapNoDict)(int, int);
typedef int(_stdcall* DM_GetWordResultCount)(int, const wchar_t*);
typedef int(_stdcall* DM_GetWordResultPos)(int, const wchar_t*,int,int*,int*);
typedef const wchar_t* (_stdcall* DM_GetWordResultStr)(int, const wchar_t*,int);
typedef const wchar_t* (_stdcall* DM_GetWords)(int, int, int, int, int, const wchar_t*, double);

typedef const wchar_t* (_stdcall* DM_GetWordsNoDict)(int, int, int, int, int, const wchar_t*);
typedef int(_stdcall* DM_SetShowErrorMsg)(int, int);
typedef int(_stdcall* DM_GetClientSize)(int, int, int*, int*);
typedef int(_stdcall* DM_MoveWindow)(int, int, int, int);
typedef const wchar_t* (_stdcall* DM_GetColorHSV)(int, int, int);
typedef const wchar_t* (_stdcall* DM_GetAveRGB)(int, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_GetAveHSV)(int, int, int, int, int);
typedef int(_stdcall* DM_GetForegroundWindow)(int);
typedef int(_stdcall* DM_GetForegroundFocus)(int);
typedef int(_stdcall* DM_GetMousePointWindow)(int);
typedef int(_stdcall* DM_GetPointWindow)(int, int, int);
typedef const wchar_t* (_stdcall* DM_EnumWindow)(int, int, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_GetWindowState)(int, int, int);
typedef int(_stdcall* DM_GetWindow)(int, int, int);
typedef int(_stdcall* DM_GetSpecialWindow)(int, int);
typedef int(_stdcall* DM_SetWindowText)(int, int, const wchar_t*);
typedef int(_stdcall* DM_SetWindowSize)(int, int, int, int);
typedef int(_stdcall* DM_GetWindowRect)(int, int, int*, int*, int*, int*);
typedef const wchar_t* (_stdcall* DM_GetWindowTitle)(int, int);
typedef const wchar_t* (_stdcall* DM_GetWindowClass)(int, int);
typedef int(_stdcall* DM_SetWindowState)(int, int, int);
typedef int(_stdcall* DM_CreateFoobarRect)(int, int, int, int, int, int);
typedef int(_stdcall* DM_CreateFoobarRoundRect)(int, int, int, int, int, int, int, int);
typedef int(_stdcall* DM_CreateFoobarEllipse)(int, int, int, int, int, int);
typedef int(_stdcall* DM_CreateFoobarCustom)(int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef int(_stdcall* DM_FoobarFillRect)(int, int, int, int, int, int, const wchar_t*);
typedef int(_stdcall* DM_FoobarDrawText)(int, int, int, int, int, int, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_FoobarDrawPic)(int, int, int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_FoobarUpdate)(int, int);
typedef int(_stdcall* DM_FoobarLock)(int, int);
typedef int(_stdcall* DM_FoobarUnlock)(int, int);
typedef int(_stdcall* DM_FoobarSetFont)(int, int, const wchar_t*, int, int);
typedef int(_stdcall* DM_FoobarTextRect)(int, int, int, int, int, int);
typedef int(_stdcall* DM_FoobarPrintText)(int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_FoobarClearText)(int, int);
typedef int(_stdcall* DM_FoobarTextLineGap)(int, int, int);
typedef int(_stdcall* DM_Play)(int, const wchar_t*);
typedef int(_stdcall* DM_FaqCapture)(int, int, int, int, int, int, int, int);
typedef int(_stdcall* DM_FaqRelease)(int, int);
typedef const wchar_t* (_stdcall* DM_FaqSend)(int, const wchar_t*, int, int, int);
typedef int(_stdcall* DM_Beep)(int, int, int);
typedef int(_stdcall* DM_FoobarClose)(int, int);
typedef int(_stdcall* DM_MoveDD)(int, int, int);
typedef int(_stdcall* DM_FaqGetSize)(int, int);
typedef int(_stdcall* DM_LoadPic)(int, const wchar_t*);
typedef int(_stdcall* DM_FreePic)(int, const wchar_t*);
typedef int(_stdcall* DM_GetScreenData)(int, int, int, int, int);
typedef int(_stdcall* DM_FreeScreenData)(int, int);
typedef int(_stdcall* DM_WheelUp)(int);
typedef int(_stdcall* DM_WheelDown)(int);
typedef int(_stdcall* DM_SetMouseDelay)(int, const wchar_t*, int);
typedef int(_stdcall* DM_SetKeypadDelay)(int, const wchar_t*, int);
typedef const wchar_t* (_stdcall* DM_GetEnv)(int, int, const wchar_t*);
typedef int(_stdcall* DM_SetEnv)(int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SendString)(int, int, const wchar_t*);
typedef int(_stdcall* DM_DelEnv)(int, int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetPath)(int);
typedef int(_stdcall* DM_SetDict)(int, int, const wchar_t*);
typedef int(_stdcall* DM_FindPic)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindPicEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef int(_stdcall* DM_SetClientSize)(int, int, int, int);
typedef int(_stdcall* DM_ReadInt)(int, int, const wchar_t*, int);
typedef int(_stdcall* DM_ReadFloat)(int, int, const wchar_t*);
typedef int(_stdcall* DM_ReadDouble)(int, int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_FindInt)(int, int, const wchar_t*, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindFloat)(int, int, const wchar_t*, int, int);
typedef const wchar_t* (_stdcall* DM_FindDouble)(int, int, const wchar_t*, double, double);
typedef const wchar_t* (_stdcall* DM_FindString)(int, int, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_GetModuleBaseAddr)(int, int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_MoveToEx)(int, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_MatchPicName)(int, const wchar_t*);
typedef int(_stdcall* DM_AddDict)(int, int, const wchar_t*);
typedef int(_stdcall* DM_EnterCri)(int);
typedef int(_stdcall* DM_LeaveCri)(int);
typedef int(_stdcall* DM_WriteInt)(int, int, const wchar_t*, int, int);
typedef int(_stdcall* DM_WriteFloat)(int, int, const wchar_t*, int);
typedef int(_stdcall* DM_WriteDouble)(int, int, const wchar_t*, double);
typedef int(_stdcall* DM_WriteString)(int, int, const wchar_t*, int, const wchar_t*);
typedef int(_stdcall* DM_AsmAdd)(int, const wchar_t*);
typedef int(_stdcall* DM_AsmClear)(int);
typedef int(_stdcall* DM_AsmCall)(int, int, int);
typedef int(_stdcall* DM_FindMultiColor)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindMultiColorEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_AsmCode)(int, int);
typedef const wchar_t* (_stdcall* DM_Assemble)(int, const wchar_t*, int, int);
typedef int(_stdcall* DM_SetWindowTransparent)(int, int, int);
typedef const wchar_t* (_stdcall* DM_ReadData)(int, int, const wchar_t*, int);
typedef int(_stdcall* DM_WriteData)(int, int, const wchar_t*, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_FindData)(int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SetPicPwd)(int, const wchar_t*);
typedef int(_stdcall* DM_Log)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_FindStrE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_FindColorE)(int, int, int, int, int, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_FindPicE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_FindMultiColorE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef int(_stdcall* DM_SetExactOcr)(int, int);
typedef const wchar_t* (_stdcall* DM_ReadString)(int, int, const wchar_t*, int, int);
typedef int(_stdcall* DM_FoobarTextPrintDir)(int, int, int);
typedef const wchar_t* (_stdcall* DM_OcrEx)(int, int, int, int, int, const wchar_t*, double);
typedef int(_stdcall* DM_SetDisplayInput)(int, const wchar_t*);
typedef int(_stdcall* DM_GetTime)(int);
typedef int(_stdcall* DM_GetScreenWidth)(int);
typedef int(_stdcall* DM_GetScreenHeight)(int);
typedef int(_stdcall* DM_BindWindowEx)(int, int, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, int);
typedef const wchar_t* (_stdcall* DM_GetDiskSerial)(int);
typedef const wchar_t* (_stdcall* DM_Md5)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetMac)(int);
typedef int(_stdcall* DM_ActiveInputMethod)(int, int, const wchar_t*);
typedef int(_stdcall* DM_CheckInputMethod)(int, int, const wchar_t*);
typedef int(_stdcall* DM_FindInputMethod)(int, const wchar_t*);
typedef int(_stdcall* DM_GetCursorPos)(int, int*, int*);
typedef int(_stdcall* DM_BindWindow)(int, int, const wchar_t*, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_FindWindow)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_GetScreenDepth)(int);
typedef int(_stdcall* DM_SetScreen)(int, int, int, int);
typedef int(_stdcall* DM_ExitOs)(int, int);
typedef const wchar_t* (_stdcall* DM_GetDir)(int, int);
typedef int(_stdcall* DM_GetOsType)(int);
typedef int(_stdcall* DM_FindWindowEx)(int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SetExportDict)(int, int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetCursorShape)(int);
typedef int(_stdcall* DM_DownCpu)(int, int);
typedef const wchar_t* (_stdcall* DM_GetCursorSpot)(int);
typedef int(_stdcall* DM_SendString2)(int, int, const wchar_t*);
typedef int(_stdcall* DM_FaqPost)(int, const wchar_t*, int, int, int);
typedef const wchar_t* (_stdcall* DM_FaqFetch)(int);
typedef const wchar_t* (_stdcall* DM_FetchWord)(int, int, int, int, int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_CaptureJpg)(int, int, int, int, int, const wchar_t*, int);
typedef int(_stdcall* DM_FindStrWithFont)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, const wchar_t*, int, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindStrWithFontE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, const wchar_t*, int, int);
typedef const wchar_t* (_stdcall* DM_FindStrWithFontEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, const wchar_t*, int, int);
typedef const wchar_t* (_stdcall* DM_GetDictInfo)(int, const wchar_t*, const wchar_t*, int, int);
typedef int(_stdcall* DM_SaveDict)(int, int, const wchar_t*);
typedef int(_stdcall* DM_GetWindowProcessId)(int, int);
typedef const wchar_t* (_stdcall* DM_GetWindowProcessPath)(int, int);
typedef int(_stdcall* DM_LockInput)(int, int);
typedef const wchar_t* (_stdcall* DM_GetPicSize)(int, const wchar_t*);
typedef int(_stdcall* DM_GetID)(int);
typedef int(_stdcall* DM_CapturePng)(int, int, int, int, int, const wchar_t*);
typedef int(_stdcall* DM_CaptureGif)(int, int, int, int, int, const wchar_t*, int, int);
typedef int(_stdcall* DM_ImageToBmp)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_FindStrFast)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindStrFastEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_FindStrFastE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef int(_stdcall* DM_EnableDisplayDebug)(int, int);
typedef int(_stdcall* DM_CapturePre)(int, const wchar_t*);
typedef int(_stdcall* DM_RegEx)(int, const wchar_t*, const wchar_t*, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetMachineCode)(int);
typedef int(_stdcall* DM_SetClipboard)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetClipboard)(int);
typedef int(_stdcall* DM_GetNowDict)(int);
typedef int(_stdcall* DM_Is64Bit)(int);
typedef int(_stdcall* DM_GetColorNum)(int, int, int, int, int, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_EnumWindowByProcess)(int, const wchar_t*, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_GetDictCount)(int, int);
typedef int(_stdcall* DM_GetLastError)(int);
typedef const wchar_t* (_stdcall* DM_GetNetTime)(int);
typedef int(_stdcall* DM_EnableGetColorByCapture)(int, int);
typedef int(_stdcall* DM_CheckUAC)(int);
typedef int(_stdcall* DM_SetUAC)(int, int);
typedef int(_stdcall* DM_DisableFontSmooth)(int);
typedef int(_stdcall* DM_CheckFontSmooth)(int);
typedef int(_stdcall* DM_SetDisplayAcceler)(int, int);
typedef int(_stdcall* DM_FindWindowByProcess)(int, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_FindWindowByProcessId)(int, int, const wchar_t*, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_ReadIni)(int, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_WriteIni)(int, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_RunApp)(int, const wchar_t*, int);
typedef int(_stdcall* DM_delay)(int, int);
typedef int(_stdcall* DM_FindWindowSuper)(int, const wchar_t*, int, int, const wchar_t*, int, int);
typedef const wchar_t* (_stdcall* DM_ExcludePos)(int, const wchar_t*, int, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindNearestPos)(int, const wchar_t*, int, int, int);
typedef const wchar_t* (_stdcall* DM_SortPosDistance)(int, const wchar_t*, int, int, int);
typedef int(_stdcall* DM_FindPicMem)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindPicMemEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_FindPicMemE)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_AppendPicAddr)(int, const wchar_t*, int, int);
typedef int(_stdcall* DM_WriteFile)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_Stop)(int, int);
typedef int(_stdcall* DM_SetDictMem)(int, int, int, int);
typedef const wchar_t* (_stdcall* DM_GetNetTimeSafe)(int);
typedef int(_stdcall* DM_ForceUnBindWindow)(int, int);
typedef const wchar_t* (_stdcall* DM_ReadIniPwd)(int, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_WriteIniPwd)(int, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_DecodeFile)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_KeyDownChar)(int, const wchar_t*);
typedef int(_stdcall* DM_KeyUpChar)(int, const wchar_t*);
typedef int(_stdcall* DM_KeyPressChar)(int, const wchar_t*);
typedef int(_stdcall* DM_KeyPressStr)(int, const wchar_t*, int);
typedef int(_stdcall* DM_EnableKeypadPatch)(int, int);
typedef int(_stdcall* DM_EnableKeypadSync)(int, int, int);
typedef int(_stdcall* DM_EnableMouseSync)(int, int, int);
typedef int(_stdcall* DM_DmGuard)(int, int, const wchar_t*);
typedef int(_stdcall* DM_FaqCaptureFromFile)(int, int, int, int, int, const wchar_t*, int);
typedef const wchar_t* (_stdcall* DM_FindIntEx)(int, int, const wchar_t*, int, int, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindFloatEx)(int, int, const wchar_t*, int, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindDoubleEx)(int, int, const wchar_t*, double, double, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindStringEx)(int, int, const wchar_t*, const wchar_t*, int, int, int, int);
typedef const wchar_t* (_stdcall* DM_FindDataEx)(int, int, const wchar_t*, const wchar_t*, int, int, int);
typedef int(_stdcall* DM_EnableRealMouse)(int, int, int, int);
typedef int(_stdcall* DM_EnableRealKeypad)(int, int);
typedef int(_stdcall* DM_SendStringIme)(int, const wchar_t*);
typedef int(_stdcall* DM_FoobarDrawLine)(int, int, int, int, int, int, const wchar_t*, int, int);
typedef const wchar_t* (_stdcall* DM_FindStrEx)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef int(_stdcall* DM_IsBind)(int, int);
typedef int(_stdcall* DM_SetDisplayDelay)(int, int);
typedef int(_stdcall* DM_GetDmCount)(int);
typedef int(_stdcall* DM_DisableScreenSave)(int);
typedef int(_stdcall* DM_DisablePowerSave)(int);
typedef int(_stdcall* DM_SetMemoryHwndAsProcessId)(int, int);
typedef int(_stdcall* DM_FindShape)(int, int, int, int, int, const wchar_t*, double, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindShapeE)(int, int, int, int, int, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_FindShapeEx)(int, int, int, int, int, const wchar_t*, double, int);
typedef const wchar_t* (_stdcall* DM_FindStrS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindStrExS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_FindStrFastS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindStrFastExS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_FindPicS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int, int*, int*);
typedef const wchar_t* (_stdcall* DM_FindPicExS)(int, int, int, int, int, const wchar_t*, const wchar_t*, double, int);
typedef int(_stdcall* DM_ClearDict)(int, int);
typedef const wchar_t* (_stdcall* DM_GetMachineCodeNoMac)(int);
typedef int(_stdcall* DM_GetClientRect)(int, int, int*, int*, int*, int*);
typedef int(_stdcall* DM_EnableFakeActive)(int, int);
typedef int(_stdcall* DM_GetScreenDataBmp)(int, int, int, int, int, int*, int*);
typedef int(_stdcall* DM_EncodeFile)(int, const wchar_t*, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_GetCursorShapeEx)(int, int);
typedef int(_stdcall* DM_FaqCancel)(int);
typedef const wchar_t* (_stdcall* DM_IntToData)(int, int, int);
typedef const wchar_t* (_stdcall* DM_FloatToData)(int, int);
typedef const wchar_t* (_stdcall* DM_DoubleToData)(int, double);
typedef const wchar_t* (_stdcall* DM_StringToData)(int, const wchar_t*, int);
typedef int(_stdcall* DM_SetMemoryFindResultToFile)(int, const wchar_t*);
typedef int(_stdcall* DM_EnableBind)(int, int);
typedef int(_stdcall* DM_SetSimMode)(int, int);
typedef int(_stdcall* DM_LockMouseRect)(int, int, int, int, int);
typedef int(_stdcall* DM_SendPaste)(int, int);
typedef int(_stdcall* DM_IsDisplayDead)(int, int, int, int, int, int);
typedef int(_stdcall* DM_GetKeyState)(int, int);
typedef int(_stdcall* DM_CopyFile)(int, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_IsFileExist)(int, const wchar_t*);
typedef int(_stdcall* DM_DeleteFile)(int, const wchar_t*);
typedef int(_stdcall* DM_MoveFile)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_CreateFolder)(int, const wchar_t*);
typedef int(_stdcall* DM_DeleteFolder)(int, const wchar_t*);
typedef int(_stdcall* DM_GetFileLength)(int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_ReadFile)(int, const wchar_t*);
typedef int(_stdcall* DM_WaitKey)(int, int, int);
typedef int(_stdcall* DM_DeleteIni)(int, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_DeleteIniPwd)(int, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_EnableSpeedDx)(int, int);
typedef int(_stdcall* DM_EnableIme)(int, int);
typedef int(_stdcall* DM_Reg)(int, const wchar_t*, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_SelectFile)(int);
typedef const wchar_t* (_stdcall* DM_SelectDirectory)(int);
typedef int(_stdcall* DM_LockDisplay)(int, int);
typedef int(_stdcall* DM_FoobarSetSave)(int, int, const wchar_t*, int, const wchar_t*);
typedef const wchar_t* (_stdcall* DM_EnumWindowSuper)(int, const wchar_t*, int, int, const wchar_t*, int, int, int);
typedef int(_stdcall* DM_DownloadFile)(int, const wchar_t*, const wchar_t*, int);
typedef int(_stdcall* DM_EnableKeypadMsg)(int, int);
typedef int(_stdcall* DM_EnableMouseMsg)(int, int);
typedef int(_stdcall* DM_RegNoMac)(int, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_RegExNoMac)(int, const wchar_t*, const wchar_t*, const wchar_t*);
typedef int(_stdcall* DM_SetEnumWindowDelay)(int, int);
typedef int(_stdcall* DM_FindMulColor)(int, int, int, int, int, const wchar_t*, double);
typedef const wchar_t* (_stdcall* DM_GetDict)(int, int, int);
//@隐藏}





//@备注 大漠模块
//@别名 大漠
class DmSoft
{
public:
	DmSoft() {
		句柄 = LoadLibrary(L"dmreg.dll");
		是否成功 = FALSE;
		if (句柄 > 0)
		{
			是否成功 = TRUE;
			CreateDM = (DM_CreateDM)GetProcAddress(句柄, "CreateDM");
			FreeDM = (DM_FreeDM)GetProcAddress(句柄, "FreeDM");
			Ver = (DM_Ver)GetProcAddress(句柄, "Ver");
			SetPath = (DM_SetPath)GetProcAddress(句柄, "SetPath");
			Ocr = (DM_Ocr)GetProcAddress(句柄, "Ocr");
			FindStr = (DM_FindStr)GetProcAddress(句柄, "FindStr");
			GetResultCount = (DM_GetResultCount)GetProcAddress(句柄, "GetResultCount");
			GetResultPos = (DM_GetResultPos)GetProcAddress(句柄, "GetResultPos");
			StrStr = (DM_StrStr)GetProcAddress(句柄, "StrStr");
			SendCommand = (DM_SendCommand)GetProcAddress(句柄, "SendCommand");
			UseDict = (DM_UseDict)GetProcAddress(句柄, "UseDict");
			GetBasePath = (DM_GetBasePath)GetProcAddress(句柄, "GetBasePath");
			SetDictPwd = (DM_SetDictPwd)GetProcAddress(句柄, "SetDictPwd");
			OcrInFile = (DM_OcrInFile)GetProcAddress(句柄, "OcrInFile");
			Capture = (DM_Capture)GetProcAddress(句柄, "Capture");
			KeyPress = (DM_KeyPress)GetProcAddress(句柄, "KeyPress");
			KeyDown = (DM_KeyDown)GetProcAddress(句柄, "KeyDown");
			KeyUp = (DM_KeyUp)GetProcAddress(句柄, "KeyUp");
			LeftClick = (DM_LeftClick)GetProcAddress(句柄, "LeftClick");
			RightClick = (DM_RightClick)GetProcAddress(句柄, "RightClick");
			MiddleClick = (DM_MiddleClick)GetProcAddress(句柄, "MiddleClick");
			LeftDoubleClick = (DM_LeftDoubleClick)GetProcAddress(句柄, "LeftDoubleClick");
			LeftDown = (DM_LeftDown)GetProcAddress(句柄, "LeftDown");
			LeftUp = (DM_LeftUp)GetProcAddress(句柄, "LeftUp");
			RightDown = (DM_RightDown)GetProcAddress(句柄, "RightDown");
			RightUp = (DM_RightUp)GetProcAddress(句柄, "RightUp");
			MoveTo = (DM_MoveTo)GetProcAddress(句柄, "MoveTo");
			MoveR = (DM_MoveR)GetProcAddress(句柄, "MoveR");
			GetColor = (DM_GetColor)GetProcAddress(句柄, "GetColor");
			GetColorBGR = (DM_GetColorBGR)GetProcAddress(句柄, "GetColorBGR");
			RGB2BGR = (DM_RGB2BGR)GetProcAddress(句柄, "RGB2BGR");
			BGR2RGB = (DM_BGR2RGB)GetProcAddress(句柄, "BGR2RGB");
			UnBindWindow = (DM_UnBindWindow)GetProcAddress(句柄, "UnBindWindow");
			CmpColor = (DM_CmpColor)GetProcAddress(句柄, "CmpColor");
			ClientToScreen = (DM_ClientToScreen)GetProcAddress(句柄, "ClientToScreen");
			ScreenToClient = (DM_ScreenToClient)GetProcAddress(句柄, "ScreenToClient");
			ShowScrMsg = (DM_ShowScrMsg)GetProcAddress(句柄, "ShowScrMsg");
			SetMinRowGap = (DM_SetMinRowGap)GetProcAddress(句柄, "SetMinRowGap");
			SetMinColGap = (DM_SetMinColGap)GetProcAddress(句柄, "SetMinColGap");
			FindColor = (DM_FindColor)GetProcAddress(句柄, "FindColor");
			FindColorEx = (DM_FindColorEx)GetProcAddress(句柄, "FindColorEx");
			SetWordLineHeight = (DM_SetWordLineHeight)GetProcAddress(句柄, "SetWordLineHeight");
			SetWordGap = (DM_SetWordGap)GetProcAddress(句柄, "SetWordGap");
			SetRowGapNoDict = (DM_SetRowGapNoDict)GetProcAddress(句柄, "SetRowGapNoDict");
			SetWordLineHeightNoDict = (DM_SetWordLineHeightNoDict)GetProcAddress(句柄, "SetWordLineHeightNoDict");
			SetWordGapNoDict = (DM_SetWordGapNoDict)GetProcAddress(句柄, "SetWordGapNoDict");
			GetWordResultCount = (DM_GetWordResultCount)GetProcAddress(句柄, "GetWordResultCount");
			GetWordResultPos = (DM_GetWordResultPos)GetProcAddress(句柄, "GetWordResultPos");
			GetWordResultStr = (DM_GetWordResultStr)GetProcAddress(句柄, "GetWordResultStr");
			GetWords = (DM_GetWords)GetProcAddress(句柄, "GetWords");
			GetWordsNoDict = (DM_GetWordsNoDict)GetProcAddress(句柄, "GetWordsNoDict");
			SetShowErrorMsg = (DM_SetShowErrorMsg)GetProcAddress(句柄, "SetShowErrorMsg");
			GetClientSize = (DM_GetClientSize)GetProcAddress(句柄, "GetClientSize");
			MoveWindow = (DM_MoveWindow)GetProcAddress(句柄, "MoveWindow");
			GetColorHSV = (DM_GetColorHSV)GetProcAddress(句柄, "GetColorHSV");
			GetAveRGB = (DM_GetAveRGB)GetProcAddress(句柄, "GetAveRGB");
			GetAveHSV = (DM_GetAveHSV)GetProcAddress(句柄, "GetAveHSV");
			GetForegroundWindow = (DM_GetForegroundWindow)GetProcAddress(句柄, "GetForegroundWindow");
			GetForegroundFocus = (DM_GetForegroundFocus)GetProcAddress(句柄, "GetForegroundFocus");
			GetMousePointWindow = (DM_GetMousePointWindow)GetProcAddress(句柄, "GetMousePointWindow");
			GetPointWindow = (DM_GetPointWindow)GetProcAddress(句柄, "GetPointWindow");
			EnumWindow = (DM_EnumWindow)GetProcAddress(句柄, "EnumWindow");
			GetWindowState = (DM_GetWindowState)GetProcAddress(句柄, "GetWindowState");
			GetWindow = (DM_GetWindow)GetProcAddress(句柄, "GetWindow");
			GetSpecialWindow = (DM_GetSpecialWindow)GetProcAddress(句柄, "GetSpecialWindow");
			SetWindowText = (DM_SetWindowText)GetProcAddress(句柄, "SetWindowText");
			SetWindowSize = (DM_SetWindowSize)GetProcAddress(句柄, "SetWindowSize");
			GetWindowRect = (DM_GetWindowRect)GetProcAddress(句柄, "GetWindowRect");
			GetWindowTitle = (DM_GetWindowTitle)GetProcAddress(句柄, "GetWindowTitle");
			GetWindowClass = (DM_GetWindowClass)GetProcAddress(句柄, "GetWindowClass");
			SetWindowState = (DM_SetWindowState)GetProcAddress(句柄, "SetWindowState");
			CreateFoobarRect = (DM_CreateFoobarRect)GetProcAddress(句柄, "CreateFoobarRect");
			CreateFoobarRoundRect = (DM_CreateFoobarRoundRect)GetProcAddress(句柄, "CreateFoobarRoundRect");
			CreateFoobarEllipse = (DM_CreateFoobarEllipse)GetProcAddress(句柄, "CreateFoobarEllipse");
			CreateFoobarCustom = (DM_CreateFoobarCustom)GetProcAddress(句柄, "CreateFoobarCustom");
			FoobarFillRect = (DM_FoobarFillRect)GetProcAddress(句柄, "FoobarFillRect");
			FoobarDrawText = (DM_FoobarDrawText)GetProcAddress(句柄, "FoobarDrawText");
			FoobarDrawPic = (DM_FoobarDrawPic)GetProcAddress(句柄, "FoobarDrawPic");
			FoobarUpdate = (DM_FoobarUpdate)GetProcAddress(句柄, "FoobarUpdate");
			FoobarLock = (DM_FoobarLock)GetProcAddress(句柄, "FoobarLock");
			FoobarUnlock = (DM_FoobarUnlock)GetProcAddress(句柄, "FoobarUnlock");
			FoobarSetFont = (DM_FoobarSetFont)GetProcAddress(句柄, "FoobarSetFont");
			FoobarTextRect = (DM_FoobarTextRect)GetProcAddress(句柄, "FoobarTextRect");
			FoobarPrintText = (DM_FoobarPrintText)GetProcAddress(句柄, "FoobarPrintText");
			FoobarClearText = (DM_FoobarClearText)GetProcAddress(句柄, "FoobarClearText");
			FoobarTextLineGap = (DM_FoobarTextLineGap)GetProcAddress(句柄, "FoobarTextLineGap");
			Play = (DM_Play)GetProcAddress(句柄, "Play");
			FaqCapture = (DM_FaqCapture)GetProcAddress(句柄, "FaqCapture");
			FaqRelease = (DM_FaqRelease)GetProcAddress(句柄, "FaqRelease");
			FaqSend = (DM_FaqSend)GetProcAddress(句柄, "FaqSend");
			Beep = (DM_Beep)GetProcAddress(句柄, "Beep");
			FoobarClose = (DM_FoobarClose)GetProcAddress(句柄, "FoobarClose");
			MoveDD = (DM_MoveDD)GetProcAddress(句柄, "MoveDD");
			FaqGetSize = (DM_FaqGetSize)GetProcAddress(句柄, "FaqGetSize");
			LoadPic = (DM_LoadPic)GetProcAddress(句柄, "LoadPic");
			FreePic = (DM_FreePic)GetProcAddress(句柄, "FreePic");
			GetScreenData = (DM_GetScreenData)GetProcAddress(句柄, "GetScreenData");
			FreeScreenData = (DM_FreeScreenData)GetProcAddress(句柄, "FreeScreenData");
			WheelUp = (DM_WheelUp)GetProcAddress(句柄, "WheelUp");
			WheelDown = (DM_WheelDown)GetProcAddress(句柄, "WheelDown");
			SetMouseDelay = (DM_SetMouseDelay)GetProcAddress(句柄, "SetMouseDelay");
			SetKeypadDelay = (DM_SetKeypadDelay)GetProcAddress(句柄, "SetKeypadDelay");
			GetEnv = (DM_GetEnv)GetProcAddress(句柄, "GetEnv");
			SetEnv = (DM_SetEnv)GetProcAddress(句柄, "SetEnv");
			SendString = (DM_SendString)GetProcAddress(句柄, "SendString");
			DelEnv = (DM_DelEnv)GetProcAddress(句柄, "DelEnv");
			GetPath = (DM_GetPath)GetProcAddress(句柄, "GetPath");
			SetDict = (DM_SetDict)GetProcAddress(句柄, "SetDict");
			FindPic = (DM_FindPic)GetProcAddress(句柄, "FindPic");
			FindPicEx = (DM_FindPicEx)GetProcAddress(句柄, "FindPicEx");
			SetClientSize = (DM_SetClientSize)GetProcAddress(句柄, "SetClientSize");
			ReadInt = (DM_ReadInt)GetProcAddress(句柄, "ReadInt");
			ReadFloat = (DM_ReadFloat)GetProcAddress(句柄, "ReadFloat");
			ReadDouble = (DM_ReadDouble)GetProcAddress(句柄, "ReadDouble");
			FindInt = (DM_FindInt)GetProcAddress(句柄, "FindInt");
			FindFloat = (DM_FindFloat)GetProcAddress(句柄, "FindFloat");
			FindDouble = (DM_FindDouble)GetProcAddress(句柄, "FindDouble");
			FindString = (DM_FindString)GetProcAddress(句柄, "FindString");
			GetModuleBaseAddr = (DM_GetModuleBaseAddr)GetProcAddress(句柄, "GetModuleBaseAddr");
			MoveToEx = (DM_MoveToEx)GetProcAddress(句柄, "MoveToEx");
			MatchPicName = (DM_MatchPicName)GetProcAddress(句柄, "MatchPicName");
			AddDict = (DM_AddDict)GetProcAddress(句柄, "AddDict");
			EnterCri = (DM_EnterCri)GetProcAddress(句柄, "EnterCri");
			LeaveCri = (DM_LeaveCri)GetProcAddress(句柄, "LeaveCri");
			WriteInt = (DM_WriteInt)GetProcAddress(句柄, "WriteInt");
			WriteFloat = (DM_WriteFloat)GetProcAddress(句柄, "WriteFloat");
			WriteDouble = (DM_WriteDouble)GetProcAddress(句柄, "WriteDouble");
			WriteString = (DM_WriteString)GetProcAddress(句柄, "WriteString");
			AsmAdd = (DM_AsmAdd)GetProcAddress(句柄, "AsmAdd");
			AsmClear = (DM_AsmClear)GetProcAddress(句柄, "AsmClear");
			AsmCall = (DM_AsmCall)GetProcAddress(句柄, "AsmCall");
			FindMultiColor = (DM_FindMultiColor)GetProcAddress(句柄, "FindMultiColor");
			FindMultiColorEx = (DM_FindMultiColorEx)GetProcAddress(句柄, "FindMultiColorEx");
			AsmCode = (DM_AsmCode)GetProcAddress(句柄, "AsmCode");
			Assemble = (DM_Assemble)GetProcAddress(句柄, "Assemble");
			SetWindowTransparent = (DM_SetWindowTransparent)GetProcAddress(句柄, "SetWindowTransparent");
			ReadData = (DM_ReadData)GetProcAddress(句柄, "ReadData");
			WriteData = (DM_WriteData)GetProcAddress(句柄, "WriteData");
			FindData = (DM_FindData)GetProcAddress(句柄, "FindData");
			SetPicPwd = (DM_SetPicPwd)GetProcAddress(句柄, "SetPicPwd");
			Log = (DM_Log)GetProcAddress(句柄, "Log");
			FindStrE = (DM_FindStrE)GetProcAddress(句柄, "FindStrE");
			FindColorE = (DM_FindColorE)GetProcAddress(句柄, "FindColorE");
			FindPicE = (DM_FindPicE)GetProcAddress(句柄, "FindPicE");
			FindMultiColorE = (DM_FindMultiColorE)GetProcAddress(句柄, "FindMultiColorE");
			SetExactOcr = (DM_SetExactOcr)GetProcAddress(句柄, "SetExactOcr");
			ReadString = (DM_ReadString)GetProcAddress(句柄, "ReadString");
			FoobarTextPrintDir = (DM_FoobarTextPrintDir)GetProcAddress(句柄, "FoobarTextPrintDir");
			OcrEx = (DM_OcrEx)GetProcAddress(句柄, "OcrEx");
			SetDisplayInput = (DM_SetDisplayInput)GetProcAddress(句柄, "SetDisplayInput");
			GetTime = (DM_GetTime)GetProcAddress(句柄, "GetTime");
			GetScreenWidth = (DM_GetScreenWidth)GetProcAddress(句柄, "GetScreenWidth");
			GetScreenHeight = (DM_GetScreenHeight)GetProcAddress(句柄, "GetScreenHeight");
			BindWindowEx = (DM_BindWindowEx)GetProcAddress(句柄, "BindWindowEx");
			GetDiskSerial = (DM_GetDiskSerial)GetProcAddress(句柄, "GetDiskSerial");
			Md5 = (DM_Md5)GetProcAddress(句柄, "Md5");
			GetMac = (DM_GetMac)GetProcAddress(句柄, "GetMac");
			ActiveInputMethod = (DM_ActiveInputMethod)GetProcAddress(句柄, "ActiveInputMethod");
			CheckInputMethod = (DM_CheckInputMethod)GetProcAddress(句柄, "CheckInputMethod");
			FindInputMethod = (DM_FindInputMethod)GetProcAddress(句柄, "FindInputMethod");
			GetCursorPos = (DM_GetCursorPos)GetProcAddress(句柄, "GetCursorPos");
			BindWindow = (DM_BindWindow)GetProcAddress(句柄, "BindWindow");
			FindWindow = (DM_FindWindow)GetProcAddress(句柄, "FindWindow");
			GetScreenDepth = (DM_GetScreenDepth)GetProcAddress(句柄, "GetScreenDepth");
			SetScreen = (DM_SetScreen)GetProcAddress(句柄, "SetScreen");
			ExitOs = (DM_ExitOs)GetProcAddress(句柄, "ExitOs");
			GetDir = (DM_GetDir)GetProcAddress(句柄, "GetDir");
			GetOsType = (DM_GetOsType)GetProcAddress(句柄, "GetOsType");
			FindWindowEx = (DM_FindWindowEx)GetProcAddress(句柄, "FindWindowEx");
			SetExportDict = (DM_SetExportDict)GetProcAddress(句柄, "SetExportDict");
			GetCursorShape = (DM_GetCursorShape)GetProcAddress(句柄, "GetCursorShape");
			DownCpu = (DM_DownCpu)GetProcAddress(句柄, "DownCpu");
			GetCursorSpot = (DM_GetCursorSpot)GetProcAddress(句柄, "GetCursorSpot");
			SendString2 = (DM_SendString2)GetProcAddress(句柄, "SendString2");
			FaqPost = (DM_FaqPost)GetProcAddress(句柄, "FaqPost");
			FaqFetch = (DM_FaqFetch)GetProcAddress(句柄, "FaqFetch");
			FetchWord = (DM_FetchWord)GetProcAddress(句柄, "FetchWord");
			CaptureJpg = (DM_CaptureJpg)GetProcAddress(句柄, "CaptureJpg");
			FindStrWithFont = (DM_FindStrWithFont)GetProcAddress(句柄, "FindStrWithFont");
			FindStrWithFontE = (DM_FindStrWithFontE)GetProcAddress(句柄, "FindStrWithFontE");
			FindStrWithFontEx = (DM_FindStrWithFontEx)GetProcAddress(句柄, "FindStrWithFontEx");
			GetDictInfo = (DM_GetDictInfo)GetProcAddress(句柄, "GetDictInfo");
			SaveDict = (DM_SaveDict)GetProcAddress(句柄, "SaveDict");
			GetWindowProcessId = (DM_GetWindowProcessId)GetProcAddress(句柄, "GetWindowProcessId");
			GetWindowProcessPath = (DM_GetWindowProcessPath)GetProcAddress(句柄, "GetWindowProcessPath");
			LockInput = (DM_LockInput)GetProcAddress(句柄, "LockInput");
			GetPicSize = (DM_GetPicSize)GetProcAddress(句柄, "GetPicSize");
			GetID = (DM_GetID)GetProcAddress(句柄, "GetID");
			CapturePng = (DM_CapturePng)GetProcAddress(句柄, "CapturePng");
			CaptureGif = (DM_CaptureGif)GetProcAddress(句柄, "CaptureGif");
			ImageToBmp = (DM_ImageToBmp)GetProcAddress(句柄, "ImageToBmp");
			FindStrFast = (DM_FindStrFast)GetProcAddress(句柄, "FindStrFast");
			FindStrFastEx = (DM_FindStrFastEx)GetProcAddress(句柄, "FindStrFastEx");
			FindStrFastE = (DM_FindStrFastE)GetProcAddress(句柄, "FindStrFastE");
			EnableDisplayDebug = (DM_EnableDisplayDebug)GetProcAddress(句柄, "EnableDisplayDebug");
			CapturePre = (DM_CapturePre)GetProcAddress(句柄, "CapturePre");
			RegEx = (DM_RegEx)GetProcAddress(句柄, "RegEx");
			GetMachineCode = (DM_GetMachineCode)GetProcAddress(句柄, "GetMachineCode");
			SetClipboard = (DM_SetClipboard)GetProcAddress(句柄, "SetClipboard");
			GetClipboard = (DM_GetClipboard)GetProcAddress(句柄, "GetClipboard");
			GetNowDict = (DM_GetNowDict)GetProcAddress(句柄, "GetNowDict");
			Is64Bit = (DM_Is64Bit)GetProcAddress(句柄, "Is64Bit");
			GetColorNum = (DM_GetColorNum)GetProcAddress(句柄, "GetColorNum");
			EnumWindowByProcess = (DM_EnumWindowByProcess)GetProcAddress(句柄, "EnumWindowByProcess");
			GetDictCount = (DM_GetDictCount)GetProcAddress(句柄, "GetDictCount");
			GetLastError = (DM_GetLastError)GetProcAddress(句柄, "GetLastError");
			GetNetTime = (DM_GetNetTime)GetProcAddress(句柄, "GetNetTime");
			EnableGetColorByCapture = (DM_EnableGetColorByCapture)GetProcAddress(句柄, "EnableGetColorByCapture");
			CheckUAC = (DM_CheckUAC)GetProcAddress(句柄, "CheckUAC");
			SetUAC = (DM_SetUAC)GetProcAddress(句柄, "SetUAC");
			DisableFontSmooth = (DM_DisableFontSmooth)GetProcAddress(句柄, "DisableFontSmooth");
			CheckFontSmooth = (DM_CheckFontSmooth)GetProcAddress(句柄, "CheckFontSmooth");
			SetDisplayAcceler = (DM_SetDisplayAcceler)GetProcAddress(句柄, "SetDisplayAcceler");
			FindWindowByProcess = (DM_FindWindowByProcess)GetProcAddress(句柄, "FindWindowByProcess");
			FindWindowByProcessId = (DM_FindWindowByProcessId)GetProcAddress(句柄, "FindWindowByProcessId");
			ReadIni = (DM_ReadIni)GetProcAddress(句柄, "ReadIni");
			WriteIni = (DM_WriteIni)GetProcAddress(句柄, "WriteIni");
			RunApp = (DM_RunApp)GetProcAddress(句柄, "RunApp");
			delay = (DM_delay)GetProcAddress(句柄, "delay");
			FindWindowSuper = (DM_FindWindowSuper)GetProcAddress(句柄, "FindWindowSuper");
			ExcludePos = (DM_ExcludePos)GetProcAddress(句柄, "ExcludePos");
			FindNearestPos = (DM_FindNearestPos)GetProcAddress(句柄, "FindNearestPos");
			SortPosDistance = (DM_SortPosDistance)GetProcAddress(句柄, "SortPosDistance");
			FindPicMem = (DM_FindPicMem)GetProcAddress(句柄, "FindPicMem");
			FindPicMemEx = (DM_FindPicMemEx)GetProcAddress(句柄, "FindPicMemEx");
			FindPicMemE = (DM_FindPicMemE)GetProcAddress(句柄, "FindPicMemE");
			AppendPicAddr = (DM_AppendPicAddr)GetProcAddress(句柄, "AppendPicAddr");
			WriteFile = (DM_WriteFile)GetProcAddress(句柄, "WriteFile");
			Stop = (DM_Stop)GetProcAddress(句柄, "Stop");
			SetDictMem = (DM_SetDictMem)GetProcAddress(句柄, "SetDictMem");
			GetNetTimeSafe = (DM_GetNetTimeSafe)GetProcAddress(句柄, "GetNetTimeSafe");
			ForceUnBindWindow = (DM_ForceUnBindWindow)GetProcAddress(句柄, "ForceUnBindWindow");
			ReadIniPwd = (DM_ReadIniPwd)GetProcAddress(句柄, "ReadIniPwd");
			WriteIniPwd = (DM_WriteIniPwd)GetProcAddress(句柄, "WriteIniPwd");
			DecodeFile = (DM_DecodeFile)GetProcAddress(句柄, "DecodeFile");
			KeyDownChar = (DM_KeyDownChar)GetProcAddress(句柄, "KeyDownChar");
			KeyUpChar = (DM_KeyUpChar)GetProcAddress(句柄, "KeyUpChar");
			KeyPressChar = (DM_KeyPressChar)GetProcAddress(句柄, "KeyPressChar");
			KeyPressStr = (DM_KeyPressStr)GetProcAddress(句柄, "KeyPressStr");
			EnableKeypadPatch = (DM_EnableKeypadPatch)GetProcAddress(句柄, "EnableKeypadPatch");
			EnableKeypadSync = (DM_EnableKeypadSync)GetProcAddress(句柄, "EnableKeypadSync");
			EnableMouseSync = (DM_EnableMouseSync)GetProcAddress(句柄, "EnableMouseSync");
			DmGuard = (DM_DmGuard)GetProcAddress(句柄, "DmGuard");
			FaqCaptureFromFile = (DM_FaqCaptureFromFile)GetProcAddress(句柄, "FaqCaptureFromFile");
			FindIntEx = (DM_FindIntEx)GetProcAddress(句柄, "FindIntEx");
			FindFloatEx = (DM_FindFloatEx)GetProcAddress(句柄, "FindFloatEx");
			FindDoubleEx = (DM_FindDoubleEx)GetProcAddress(句柄, "FindDoubleEx");
			FindStringEx = (DM_FindStringEx)GetProcAddress(句柄, "FindStringEx");
			FindDataEx = (DM_FindDataEx)GetProcAddress(句柄, "FindDataEx");
			EnableRealMouse = (DM_EnableRealMouse)GetProcAddress(句柄, "EnableRealMouse");
			EnableRealKeypad = (DM_EnableRealKeypad)GetProcAddress(句柄, "EnableRealKeypad");
			SendStringIme = (DM_SendStringIme)GetProcAddress(句柄, "SendStringIme");
			FoobarDrawLine = (DM_FoobarDrawLine)GetProcAddress(句柄, "FoobarDrawLine");
			FindStrEx = (DM_FindStrEx)GetProcAddress(句柄, "FindStrEx");
			IsBind = (DM_IsBind)GetProcAddress(句柄, "IsBind");
			SetDisplayDelay = (DM_SetDisplayDelay)GetProcAddress(句柄, "SetDisplayDelay");
			GetDmCount = (DM_GetDmCount)GetProcAddress(句柄, "GetDmCount");
			DisableScreenSave = (DM_DisableScreenSave)GetProcAddress(句柄, "DisableScreenSave");
			DisablePowerSave = (DM_DisablePowerSave)GetProcAddress(句柄, "DisablePowerSave");
			SetMemoryHwndAsProcessId = (DM_SetMemoryHwndAsProcessId)GetProcAddress(句柄, "SetMemoryHwndAsProcessId");
			FindShape = (DM_FindShape)GetProcAddress(句柄, "FindShape");
			FindShapeE = (DM_FindShapeE)GetProcAddress(句柄, "FindShapeE");
			FindShapeEx = (DM_FindShapeEx)GetProcAddress(句柄, "FindShapeEx");
			FindStrS = (DM_FindStrS)GetProcAddress(句柄, "FindStrS");
			FindStrExS = (DM_FindStrExS)GetProcAddress(句柄, "FindStrExS");
			FindStrFastS = (DM_FindStrFastS)GetProcAddress(句柄, "FindStrFastS");
			FindStrFastExS = (DM_FindStrFastExS)GetProcAddress(句柄, "FindStrFastExS");
			FindPicS = (DM_FindPicS)GetProcAddress(句柄, "FindPicS");
			FindPicExS = (DM_FindPicExS)GetProcAddress(句柄, "FindPicExS");
			ClearDict = (DM_ClearDict)GetProcAddress(句柄, "ClearDict");
			GetMachineCodeNoMac = (DM_GetMachineCodeNoMac)GetProcAddress(句柄, "GetMachineCodeNoMac");
			GetClientRect = (DM_GetClientRect)GetProcAddress(句柄, "GetClientRect");
			EnableFakeActive = (DM_EnableFakeActive)GetProcAddress(句柄, "EnableFakeActive");
			GetScreenDataBmp = (DM_GetScreenDataBmp)GetProcAddress(句柄, "GetScreenDataBmp");
			EncodeFile = (DM_EncodeFile)GetProcAddress(句柄, "EncodeFile");
			GetCursorShapeEx = (DM_GetCursorShapeEx)GetProcAddress(句柄, "GetCursorShapeEx");
			FaqCancel = (DM_FaqCancel)GetProcAddress(句柄, "FaqCancel");
			IntToData = (DM_IntToData)GetProcAddress(句柄, "IntToData");
			FloatToData = (DM_FloatToData)GetProcAddress(句柄, "FloatToData");
			DoubleToData = (DM_DoubleToData)GetProcAddress(句柄, "DoubleToData");
			StringToData = (DM_StringToData)GetProcAddress(句柄, "StringToData");
			SetMemoryFindResultToFile = (DM_SetMemoryFindResultToFile)GetProcAddress(句柄, "SetMemoryFindResultToFile");
			EnableBind = (DM_EnableBind)GetProcAddress(句柄, "EnableBind");
			SetSimMode = (DM_SetSimMode)GetProcAddress(句柄, "SetSimMode");
			LockMouseRect = (DM_LockMouseRect)GetProcAddress(句柄, "LockMouseRect");
			SendPaste = (DM_SendPaste)GetProcAddress(句柄, "SendPaste");
			IsDisplayDead = (DM_IsDisplayDead)GetProcAddress(句柄, "IsDisplayDead");
			GetKeyState = (DM_GetKeyState)GetProcAddress(句柄, "GetKeyState");
			CopyFile = (DM_CopyFile)GetProcAddress(句柄, "CopyFile");
			IsFileExist = (DM_IsFileExist)GetProcAddress(句柄, "IsFileExist");
			DeleteFile = (DM_DeleteFile)GetProcAddress(句柄, "DeleteFile");
			MoveFile = (DM_MoveFile)GetProcAddress(句柄, "MoveFile");
			CreateFolder = (DM_CreateFolder)GetProcAddress(句柄, "CreateFolder");
			DeleteFolder = (DM_DeleteFolder)GetProcAddress(句柄, "DeleteFolder");
			GetFileLength = (DM_GetFileLength)GetProcAddress(句柄, "GetFileLength");
			ReadFile = (DM_ReadFile)GetProcAddress(句柄, "ReadFile");
			WaitKey = (DM_WaitKey)GetProcAddress(句柄, "WaitKey");
			DeleteIni = (DM_DeleteIni)GetProcAddress(句柄, "DeleteIni");
			DeleteIniPwd = (DM_DeleteIniPwd)GetProcAddress(句柄, "DeleteIniPwd");
			EnableSpeedDx = (DM_EnableSpeedDx)GetProcAddress(句柄, "EnableSpeedDx");
			EnableIme = (DM_EnableIme)GetProcAddress(句柄, "EnableIme");
			Reg = (DM_Reg)GetProcAddress(句柄, "Reg");
			SelectFile = (DM_SelectFile)GetProcAddress(句柄, "SelectFile");
			SelectDirectory = (DM_SelectDirectory)GetProcAddress(句柄, "SelectDirectory");
			LockDisplay = (DM_LockDisplay)GetProcAddress(句柄, "LockDisplay");
			FoobarSetSave = (DM_FoobarSetSave)GetProcAddress(句柄, "FoobarSetSave");
			EnumWindowSuper = (DM_EnumWindowSuper)GetProcAddress(句柄, "EnumWindowSuper");
			DownloadFile = (DM_DownloadFile)GetProcAddress(句柄, "DownloadFile");
			EnableKeypadMsg = (DM_EnableKeypadMsg)GetProcAddress(句柄, "EnableKeypadMsg");
			EnableMouseMsg = (DM_EnableMouseMsg)GetProcAddress(句柄, "EnableMouseMsg");
			RegNoMac = (DM_RegNoMac)GetProcAddress(句柄, "RegNoMac");
			RegExNoMac = (DM_RegExNoMac)GetProcAddress(句柄, "RegExNoMac");
			SetEnumWindowDelay = (DM_SetEnumWindowDelay)GetProcAddress(句柄, "SetEnumWindowDelay");
			FindMulColor = (DM_FindMulColor)GetProcAddress(句柄, "FindMulColor");
			GetDict = (DM_GetDict)GetProcAddress(句柄, "GetDict");

		}
	}
	DmSoft(const wchar_t* dll路径) {
		句柄 = LoadLibrary(dll路径);
		是否成功 = FALSE;
		if (句柄 > 0)
		{
			是否成功 = TRUE;
			CreateDM = (DM_CreateDM)GetProcAddress(句柄, "CreateDM");
			FreeDM = (DM_FreeDM)GetProcAddress(句柄, "FreeDM");
			Ver = (DM_Ver)GetProcAddress(句柄, "Ver");
			SetPath = (DM_SetPath)GetProcAddress(句柄, "SetPath");
			Ocr = (DM_Ocr)GetProcAddress(句柄, "Ocr");
			FindStr = (DM_FindStr)GetProcAddress(句柄, "FindStr");
			GetResultCount = (DM_GetResultCount)GetProcAddress(句柄, "GetResultCount");
			GetResultPos = (DM_GetResultPos)GetProcAddress(句柄, "GetResultPos");
			StrStr = (DM_StrStr)GetProcAddress(句柄, "StrStr");
			SendCommand = (DM_SendCommand)GetProcAddress(句柄, "SendCommand");
			UseDict = (DM_UseDict)GetProcAddress(句柄, "UseDict");
			GetBasePath = (DM_GetBasePath)GetProcAddress(句柄, "GetBasePath");
			SetDictPwd = (DM_SetDictPwd)GetProcAddress(句柄, "SetDictPwd");
			OcrInFile = (DM_OcrInFile)GetProcAddress(句柄, "OcrInFile");
			Capture = (DM_Capture)GetProcAddress(句柄, "Capture");
			KeyPress = (DM_KeyPress)GetProcAddress(句柄, "KeyPress");
			KeyDown = (DM_KeyDown)GetProcAddress(句柄, "KeyDown");
			KeyUp = (DM_KeyUp)GetProcAddress(句柄, "KeyUp");
			LeftClick = (DM_LeftClick)GetProcAddress(句柄, "LeftClick");
			RightClick = (DM_RightClick)GetProcAddress(句柄, "RightClick");
			MiddleClick = (DM_MiddleClick)GetProcAddress(句柄, "MiddleClick");
			LeftDoubleClick = (DM_LeftDoubleClick)GetProcAddress(句柄, "LeftDoubleClick");
			LeftDown = (DM_LeftDown)GetProcAddress(句柄, "LeftDown");
			LeftUp = (DM_LeftUp)GetProcAddress(句柄, "LeftUp");
			RightDown = (DM_RightDown)GetProcAddress(句柄, "RightDown");
			RightUp = (DM_RightUp)GetProcAddress(句柄, "RightUp");
			MoveTo = (DM_MoveTo)GetProcAddress(句柄, "MoveTo");
			MoveR = (DM_MoveR)GetProcAddress(句柄, "MoveR");
			GetColor = (DM_GetColor)GetProcAddress(句柄, "GetColor");
			GetColorBGR = (DM_GetColorBGR)GetProcAddress(句柄, "GetColorBGR");
			RGB2BGR = (DM_RGB2BGR)GetProcAddress(句柄, "RGB2BGR");
			BGR2RGB = (DM_BGR2RGB)GetProcAddress(句柄, "BGR2RGB");
			UnBindWindow = (DM_UnBindWindow)GetProcAddress(句柄, "UnBindWindow");
			CmpColor = (DM_CmpColor)GetProcAddress(句柄, "CmpColor");
			ClientToScreen = (DM_ClientToScreen)GetProcAddress(句柄, "ClientToScreen");
			ScreenToClient = (DM_ScreenToClient)GetProcAddress(句柄, "ScreenToClient");
			ShowScrMsg = (DM_ShowScrMsg)GetProcAddress(句柄, "ShowScrMsg");
			SetMinRowGap = (DM_SetMinRowGap)GetProcAddress(句柄, "SetMinRowGap");
			SetMinColGap = (DM_SetMinColGap)GetProcAddress(句柄, "SetMinColGap");
			FindColor = (DM_FindColor)GetProcAddress(句柄, "FindColor");
			FindColorEx = (DM_FindColorEx)GetProcAddress(句柄, "FindColorEx");
			SetWordLineHeight = (DM_SetWordLineHeight)GetProcAddress(句柄, "SetWordLineHeight");
			SetWordGap = (DM_SetWordGap)GetProcAddress(句柄, "SetWordGap");
			SetRowGapNoDict = (DM_SetRowGapNoDict)GetProcAddress(句柄, "SetRowGapNoDict");
			SetWordLineHeightNoDict = (DM_SetWordLineHeightNoDict)GetProcAddress(句柄, "SetWordLineHeightNoDict");
			SetWordGapNoDict = (DM_SetWordGapNoDict)GetProcAddress(句柄, "SetWordGapNoDict");
			GetWordResultCount = (DM_GetWordResultCount)GetProcAddress(句柄, "GetWordResultCount");
			GetWordResultPos = (DM_GetWordResultPos)GetProcAddress(句柄, "GetWordResultPos");
			GetWordResultStr = (DM_GetWordResultStr)GetProcAddress(句柄, "GetWordResultStr");
			GetWords = (DM_GetWords)GetProcAddress(句柄, "GetWords");
			GetWordsNoDict = (DM_GetWordsNoDict)GetProcAddress(句柄, "GetWordsNoDict");
			SetShowErrorMsg = (DM_SetShowErrorMsg)GetProcAddress(句柄, "SetShowErrorMsg");
			GetClientSize = (DM_GetClientSize)GetProcAddress(句柄, "GetClientSize");
			MoveWindow = (DM_MoveWindow)GetProcAddress(句柄, "MoveWindow");
			GetColorHSV = (DM_GetColorHSV)GetProcAddress(句柄, "GetColorHSV");
			GetAveRGB = (DM_GetAveRGB)GetProcAddress(句柄, "GetAveRGB");
			GetAveHSV = (DM_GetAveHSV)GetProcAddress(句柄, "GetAveHSV");
			GetForegroundWindow = (DM_GetForegroundWindow)GetProcAddress(句柄, "GetForegroundWindow");
			GetForegroundFocus = (DM_GetForegroundFocus)GetProcAddress(句柄, "GetForegroundFocus");
			GetMousePointWindow = (DM_GetMousePointWindow)GetProcAddress(句柄, "GetMousePointWindow");
			GetPointWindow = (DM_GetPointWindow)GetProcAddress(句柄, "GetPointWindow");
			EnumWindow = (DM_EnumWindow)GetProcAddress(句柄, "EnumWindow");
			GetWindowState = (DM_GetWindowState)GetProcAddress(句柄, "GetWindowState");
			GetWindow = (DM_GetWindow)GetProcAddress(句柄, "GetWindow");
			GetSpecialWindow = (DM_GetSpecialWindow)GetProcAddress(句柄, "GetSpecialWindow");
			SetWindowText = (DM_SetWindowText)GetProcAddress(句柄, "SetWindowText");
			SetWindowSize = (DM_SetWindowSize)GetProcAddress(句柄, "SetWindowSize");
			GetWindowRect = (DM_GetWindowRect)GetProcAddress(句柄, "GetWindowRect");
			GetWindowTitle = (DM_GetWindowTitle)GetProcAddress(句柄, "GetWindowTitle");
			GetWindowClass = (DM_GetWindowClass)GetProcAddress(句柄, "GetWindowClass");
			SetWindowState = (DM_SetWindowState)GetProcAddress(句柄, "SetWindowState");
			CreateFoobarRect = (DM_CreateFoobarRect)GetProcAddress(句柄, "CreateFoobarRect");
			CreateFoobarRoundRect = (DM_CreateFoobarRoundRect)GetProcAddress(句柄, "CreateFoobarRoundRect");
			CreateFoobarEllipse = (DM_CreateFoobarEllipse)GetProcAddress(句柄, "CreateFoobarEllipse");
			CreateFoobarCustom = (DM_CreateFoobarCustom)GetProcAddress(句柄, "CreateFoobarCustom");
			FoobarFillRect = (DM_FoobarFillRect)GetProcAddress(句柄, "FoobarFillRect");
			FoobarDrawText = (DM_FoobarDrawText)GetProcAddress(句柄, "FoobarDrawText");
			FoobarDrawPic = (DM_FoobarDrawPic)GetProcAddress(句柄, "FoobarDrawPic");
			FoobarUpdate = (DM_FoobarUpdate)GetProcAddress(句柄, "FoobarUpdate");
			FoobarLock = (DM_FoobarLock)GetProcAddress(句柄, "FoobarLock");
			FoobarUnlock = (DM_FoobarUnlock)GetProcAddress(句柄, "FoobarUnlock");
			FoobarSetFont = (DM_FoobarSetFont)GetProcAddress(句柄, "FoobarSetFont");
			FoobarTextRect = (DM_FoobarTextRect)GetProcAddress(句柄, "FoobarTextRect");
			FoobarPrintText = (DM_FoobarPrintText)GetProcAddress(句柄, "FoobarPrintText");
			FoobarClearText = (DM_FoobarClearText)GetProcAddress(句柄, "FoobarClearText");
			FoobarTextLineGap = (DM_FoobarTextLineGap)GetProcAddress(句柄, "FoobarTextLineGap");
			Play = (DM_Play)GetProcAddress(句柄, "Play");
			FaqCapture = (DM_FaqCapture)GetProcAddress(句柄, "FaqCapture");
			FaqRelease = (DM_FaqRelease)GetProcAddress(句柄, "FaqRelease");
			FaqSend = (DM_FaqSend)GetProcAddress(句柄, "FaqSend");
			Beep = (DM_Beep)GetProcAddress(句柄, "Beep");
			FoobarClose = (DM_FoobarClose)GetProcAddress(句柄, "FoobarClose");
			MoveDD = (DM_MoveDD)GetProcAddress(句柄, "MoveDD");
			FaqGetSize = (DM_FaqGetSize)GetProcAddress(句柄, "FaqGetSize");
			LoadPic = (DM_LoadPic)GetProcAddress(句柄, "LoadPic");
			FreePic = (DM_FreePic)GetProcAddress(句柄, "FreePic");
			GetScreenData = (DM_GetScreenData)GetProcAddress(句柄, "GetScreenData");
			FreeScreenData = (DM_FreeScreenData)GetProcAddress(句柄, "FreeScreenData");
			WheelUp = (DM_WheelUp)GetProcAddress(句柄, "WheelUp");
			WheelDown = (DM_WheelDown)GetProcAddress(句柄, "WheelDown");
			SetMouseDelay = (DM_SetMouseDelay)GetProcAddress(句柄, "SetMouseDelay");
			SetKeypadDelay = (DM_SetKeypadDelay)GetProcAddress(句柄, "SetKeypadDelay");
			GetEnv = (DM_GetEnv)GetProcAddress(句柄, "GetEnv");
			SetEnv = (DM_SetEnv)GetProcAddress(句柄, "SetEnv");
			SendString = (DM_SendString)GetProcAddress(句柄, "SendString");
			DelEnv = (DM_DelEnv)GetProcAddress(句柄, "DelEnv");
			GetPath = (DM_GetPath)GetProcAddress(句柄, "GetPath");
			SetDict = (DM_SetDict)GetProcAddress(句柄, "SetDict");
			FindPic = (DM_FindPic)GetProcAddress(句柄, "FindPic");
			FindPicEx = (DM_FindPicEx)GetProcAddress(句柄, "FindPicEx");
			SetClientSize = (DM_SetClientSize)GetProcAddress(句柄, "SetClientSize");
			ReadInt = (DM_ReadInt)GetProcAddress(句柄, "ReadInt");
			ReadFloat = (DM_ReadFloat)GetProcAddress(句柄, "ReadFloat");
			ReadDouble = (DM_ReadDouble)GetProcAddress(句柄, "ReadDouble");
			FindInt = (DM_FindInt)GetProcAddress(句柄, "FindInt");
			FindFloat = (DM_FindFloat)GetProcAddress(句柄, "FindFloat");
			FindDouble = (DM_FindDouble)GetProcAddress(句柄, "FindDouble");
			FindString = (DM_FindString)GetProcAddress(句柄, "FindString");
			GetModuleBaseAddr = (DM_GetModuleBaseAddr)GetProcAddress(句柄, "GetModuleBaseAddr");
			MoveToEx = (DM_MoveToEx)GetProcAddress(句柄, "MoveToEx");
			MatchPicName = (DM_MatchPicName)GetProcAddress(句柄, "MatchPicName");
			AddDict = (DM_AddDict)GetProcAddress(句柄, "AddDict");
			EnterCri = (DM_EnterCri)GetProcAddress(句柄, "EnterCri");
			LeaveCri = (DM_LeaveCri)GetProcAddress(句柄, "LeaveCri");
			WriteInt = (DM_WriteInt)GetProcAddress(句柄, "WriteInt");
			WriteFloat = (DM_WriteFloat)GetProcAddress(句柄, "WriteFloat");
			WriteDouble = (DM_WriteDouble)GetProcAddress(句柄, "WriteDouble");
			WriteString = (DM_WriteString)GetProcAddress(句柄, "WriteString");
			AsmAdd = (DM_AsmAdd)GetProcAddress(句柄, "AsmAdd");
			AsmClear = (DM_AsmClear)GetProcAddress(句柄, "AsmClear");
			AsmCall = (DM_AsmCall)GetProcAddress(句柄, "AsmCall");
			FindMultiColor = (DM_FindMultiColor)GetProcAddress(句柄, "FindMultiColor");
			FindMultiColorEx = (DM_FindMultiColorEx)GetProcAddress(句柄, "FindMultiColorEx");
			AsmCode = (DM_AsmCode)GetProcAddress(句柄, "AsmCode");
			Assemble = (DM_Assemble)GetProcAddress(句柄, "Assemble");
			SetWindowTransparent = (DM_SetWindowTransparent)GetProcAddress(句柄, "SetWindowTransparent");
			ReadData = (DM_ReadData)GetProcAddress(句柄, "ReadData");
			WriteData = (DM_WriteData)GetProcAddress(句柄, "WriteData");
			FindData = (DM_FindData)GetProcAddress(句柄, "FindData");
			SetPicPwd = (DM_SetPicPwd)GetProcAddress(句柄, "SetPicPwd");
			Log = (DM_Log)GetProcAddress(句柄, "Log");
			FindStrE = (DM_FindStrE)GetProcAddress(句柄, "FindStrE");
			FindColorE = (DM_FindColorE)GetProcAddress(句柄, "FindColorE");
			FindPicE = (DM_FindPicE)GetProcAddress(句柄, "FindPicE");
			FindMultiColorE = (DM_FindMultiColorE)GetProcAddress(句柄, "FindMultiColorE");
			SetExactOcr = (DM_SetExactOcr)GetProcAddress(句柄, "SetExactOcr");
			ReadString = (DM_ReadString)GetProcAddress(句柄, "ReadString");
			FoobarTextPrintDir = (DM_FoobarTextPrintDir)GetProcAddress(句柄, "FoobarTextPrintDir");
			OcrEx = (DM_OcrEx)GetProcAddress(句柄, "OcrEx");
			SetDisplayInput = (DM_SetDisplayInput)GetProcAddress(句柄, "SetDisplayInput");
			GetTime = (DM_GetTime)GetProcAddress(句柄, "GetTime");
			GetScreenWidth = (DM_GetScreenWidth)GetProcAddress(句柄, "GetScreenWidth");
			GetScreenHeight = (DM_GetScreenHeight)GetProcAddress(句柄, "GetScreenHeight");
			BindWindowEx = (DM_BindWindowEx)GetProcAddress(句柄, "BindWindowEx");
			GetDiskSerial = (DM_GetDiskSerial)GetProcAddress(句柄, "GetDiskSerial");
			Md5 = (DM_Md5)GetProcAddress(句柄, "Md5");
			GetMac = (DM_GetMac)GetProcAddress(句柄, "GetMac");
			ActiveInputMethod = (DM_ActiveInputMethod)GetProcAddress(句柄, "ActiveInputMethod");
			CheckInputMethod = (DM_CheckInputMethod)GetProcAddress(句柄, "CheckInputMethod");
			FindInputMethod = (DM_FindInputMethod)GetProcAddress(句柄, "FindInputMethod");
			GetCursorPos = (DM_GetCursorPos)GetProcAddress(句柄, "GetCursorPos");
			BindWindow = (DM_BindWindow)GetProcAddress(句柄, "BindWindow");
			FindWindow = (DM_FindWindow)GetProcAddress(句柄, "FindWindow");
			GetScreenDepth = (DM_GetScreenDepth)GetProcAddress(句柄, "GetScreenDepth");
			SetScreen = (DM_SetScreen)GetProcAddress(句柄, "SetScreen");
			ExitOs = (DM_ExitOs)GetProcAddress(句柄, "ExitOs");
			GetDir = (DM_GetDir)GetProcAddress(句柄, "GetDir");
			GetOsType = (DM_GetOsType)GetProcAddress(句柄, "GetOsType");
			FindWindowEx = (DM_FindWindowEx)GetProcAddress(句柄, "FindWindowEx");
			SetExportDict = (DM_SetExportDict)GetProcAddress(句柄, "SetExportDict");
			GetCursorShape = (DM_GetCursorShape)GetProcAddress(句柄, "GetCursorShape");
			DownCpu = (DM_DownCpu)GetProcAddress(句柄, "DownCpu");
			GetCursorSpot = (DM_GetCursorSpot)GetProcAddress(句柄, "GetCursorSpot");
			SendString2 = (DM_SendString2)GetProcAddress(句柄, "SendString2");
			FaqPost = (DM_FaqPost)GetProcAddress(句柄, "FaqPost");
			FaqFetch = (DM_FaqFetch)GetProcAddress(句柄, "FaqFetch");
			FetchWord = (DM_FetchWord)GetProcAddress(句柄, "FetchWord");
			CaptureJpg = (DM_CaptureJpg)GetProcAddress(句柄, "CaptureJpg");
			FindStrWithFont = (DM_FindStrWithFont)GetProcAddress(句柄, "FindStrWithFont");
			FindStrWithFontE = (DM_FindStrWithFontE)GetProcAddress(句柄, "FindStrWithFontE");
			FindStrWithFontEx = (DM_FindStrWithFontEx)GetProcAddress(句柄, "FindStrWithFontEx");
			GetDictInfo = (DM_GetDictInfo)GetProcAddress(句柄, "GetDictInfo");
			SaveDict = (DM_SaveDict)GetProcAddress(句柄, "SaveDict");
			GetWindowProcessId = (DM_GetWindowProcessId)GetProcAddress(句柄, "GetWindowProcessId");
			GetWindowProcessPath = (DM_GetWindowProcessPath)GetProcAddress(句柄, "GetWindowProcessPath");
			LockInput = (DM_LockInput)GetProcAddress(句柄, "LockInput");
			GetPicSize = (DM_GetPicSize)GetProcAddress(句柄, "GetPicSize");
			GetID = (DM_GetID)GetProcAddress(句柄, "GetID");
			CapturePng = (DM_CapturePng)GetProcAddress(句柄, "CapturePng");
			CaptureGif = (DM_CaptureGif)GetProcAddress(句柄, "CaptureGif");
			ImageToBmp = (DM_ImageToBmp)GetProcAddress(句柄, "ImageToBmp");
			FindStrFast = (DM_FindStrFast)GetProcAddress(句柄, "FindStrFast");
			FindStrFastEx = (DM_FindStrFastEx)GetProcAddress(句柄, "FindStrFastEx");
			FindStrFastE = (DM_FindStrFastE)GetProcAddress(句柄, "FindStrFastE");
			EnableDisplayDebug = (DM_EnableDisplayDebug)GetProcAddress(句柄, "EnableDisplayDebug");
			CapturePre = (DM_CapturePre)GetProcAddress(句柄, "CapturePre");
			RegEx = (DM_RegEx)GetProcAddress(句柄, "RegEx");
			GetMachineCode = (DM_GetMachineCode)GetProcAddress(句柄, "GetMachineCode");
			SetClipboard = (DM_SetClipboard)GetProcAddress(句柄, "SetClipboard");
			GetClipboard = (DM_GetClipboard)GetProcAddress(句柄, "GetClipboard");
			GetNowDict = (DM_GetNowDict)GetProcAddress(句柄, "GetNowDict");
			Is64Bit = (DM_Is64Bit)GetProcAddress(句柄, "Is64Bit");
			GetColorNum = (DM_GetColorNum)GetProcAddress(句柄, "GetColorNum");
			EnumWindowByProcess = (DM_EnumWindowByProcess)GetProcAddress(句柄, "EnumWindowByProcess");
			GetDictCount = (DM_GetDictCount)GetProcAddress(句柄, "GetDictCount");
			GetLastError = (DM_GetLastError)GetProcAddress(句柄, "GetLastError");
			GetNetTime = (DM_GetNetTime)GetProcAddress(句柄, "GetNetTime");
			EnableGetColorByCapture = (DM_EnableGetColorByCapture)GetProcAddress(句柄, "EnableGetColorByCapture");
			CheckUAC = (DM_CheckUAC)GetProcAddress(句柄, "CheckUAC");
			SetUAC = (DM_SetUAC)GetProcAddress(句柄, "SetUAC");
			DisableFontSmooth = (DM_DisableFontSmooth)GetProcAddress(句柄, "DisableFontSmooth");
			CheckFontSmooth = (DM_CheckFontSmooth)GetProcAddress(句柄, "CheckFontSmooth");
			SetDisplayAcceler = (DM_SetDisplayAcceler)GetProcAddress(句柄, "SetDisplayAcceler");
			FindWindowByProcess = (DM_FindWindowByProcess)GetProcAddress(句柄, "FindWindowByProcess");
			FindWindowByProcessId = (DM_FindWindowByProcessId)GetProcAddress(句柄, "FindWindowByProcessId");
			ReadIni = (DM_ReadIni)GetProcAddress(句柄, "ReadIni");
			WriteIni = (DM_WriteIni)GetProcAddress(句柄, "WriteIni");
			RunApp = (DM_RunApp)GetProcAddress(句柄, "RunApp");
			delay = (DM_delay)GetProcAddress(句柄, "delay");
			FindWindowSuper = (DM_FindWindowSuper)GetProcAddress(句柄, "FindWindowSuper");
			ExcludePos = (DM_ExcludePos)GetProcAddress(句柄, "ExcludePos");
			FindNearestPos = (DM_FindNearestPos)GetProcAddress(句柄, "FindNearestPos");
			SortPosDistance = (DM_SortPosDistance)GetProcAddress(句柄, "SortPosDistance");
			FindPicMem = (DM_FindPicMem)GetProcAddress(句柄, "FindPicMem");
			FindPicMemEx = (DM_FindPicMemEx)GetProcAddress(句柄, "FindPicMemEx");
			FindPicMemE = (DM_FindPicMemE)GetProcAddress(句柄, "FindPicMemE");
			AppendPicAddr = (DM_AppendPicAddr)GetProcAddress(句柄, "AppendPicAddr");
			WriteFile = (DM_WriteFile)GetProcAddress(句柄, "WriteFile");
			Stop = (DM_Stop)GetProcAddress(句柄, "Stop");
			SetDictMem = (DM_SetDictMem)GetProcAddress(句柄, "SetDictMem");
			GetNetTimeSafe = (DM_GetNetTimeSafe)GetProcAddress(句柄, "GetNetTimeSafe");
			ForceUnBindWindow = (DM_ForceUnBindWindow)GetProcAddress(句柄, "ForceUnBindWindow");
			ReadIniPwd = (DM_ReadIniPwd)GetProcAddress(句柄, "ReadIniPwd");
			WriteIniPwd = (DM_WriteIniPwd)GetProcAddress(句柄, "WriteIniPwd");
			DecodeFile = (DM_DecodeFile)GetProcAddress(句柄, "DecodeFile");
			KeyDownChar = (DM_KeyDownChar)GetProcAddress(句柄, "KeyDownChar");
			KeyUpChar = (DM_KeyUpChar)GetProcAddress(句柄, "KeyUpChar");
			KeyPressChar = (DM_KeyPressChar)GetProcAddress(句柄, "KeyPressChar");
			KeyPressStr = (DM_KeyPressStr)GetProcAddress(句柄, "KeyPressStr");
			EnableKeypadPatch = (DM_EnableKeypadPatch)GetProcAddress(句柄, "EnableKeypadPatch");
			EnableKeypadSync = (DM_EnableKeypadSync)GetProcAddress(句柄, "EnableKeypadSync");
			EnableMouseSync = (DM_EnableMouseSync)GetProcAddress(句柄, "EnableMouseSync");
			DmGuard = (DM_DmGuard)GetProcAddress(句柄, "DmGuard");
			FaqCaptureFromFile = (DM_FaqCaptureFromFile)GetProcAddress(句柄, "FaqCaptureFromFile");
			FindIntEx = (DM_FindIntEx)GetProcAddress(句柄, "FindIntEx");
			FindFloatEx = (DM_FindFloatEx)GetProcAddress(句柄, "FindFloatEx");
			FindDoubleEx = (DM_FindDoubleEx)GetProcAddress(句柄, "FindDoubleEx");
			FindStringEx = (DM_FindStringEx)GetProcAddress(句柄, "FindStringEx");
			FindDataEx = (DM_FindDataEx)GetProcAddress(句柄, "FindDataEx");
			EnableRealMouse = (DM_EnableRealMouse)GetProcAddress(句柄, "EnableRealMouse");
			EnableRealKeypad = (DM_EnableRealKeypad)GetProcAddress(句柄, "EnableRealKeypad");
			SendStringIme = (DM_SendStringIme)GetProcAddress(句柄, "SendStringIme");
			FoobarDrawLine = (DM_FoobarDrawLine)GetProcAddress(句柄, "FoobarDrawLine");
			FindStrEx = (DM_FindStrEx)GetProcAddress(句柄, "FindStrEx");
			IsBind = (DM_IsBind)GetProcAddress(句柄, "IsBind");
			SetDisplayDelay = (DM_SetDisplayDelay)GetProcAddress(句柄, "SetDisplayDelay");
			GetDmCount = (DM_GetDmCount)GetProcAddress(句柄, "GetDmCount");
			DisableScreenSave = (DM_DisableScreenSave)GetProcAddress(句柄, "DisableScreenSave");
			DisablePowerSave = (DM_DisablePowerSave)GetProcAddress(句柄, "DisablePowerSave");
			SetMemoryHwndAsProcessId = (DM_SetMemoryHwndAsProcessId)GetProcAddress(句柄, "SetMemoryHwndAsProcessId");
			FindShape = (DM_FindShape)GetProcAddress(句柄, "FindShape");
			FindShapeE = (DM_FindShapeE)GetProcAddress(句柄, "FindShapeE");
			FindShapeEx = (DM_FindShapeEx)GetProcAddress(句柄, "FindShapeEx");
			FindStrS = (DM_FindStrS)GetProcAddress(句柄, "FindStrS");
			FindStrExS = (DM_FindStrExS)GetProcAddress(句柄, "FindStrExS");
			FindStrFastS = (DM_FindStrFastS)GetProcAddress(句柄, "FindStrFastS");
			FindStrFastExS = (DM_FindStrFastExS)GetProcAddress(句柄, "FindStrFastExS");
			FindPicS = (DM_FindPicS)GetProcAddress(句柄, "FindPicS");
			FindPicExS = (DM_FindPicExS)GetProcAddress(句柄, "FindPicExS");
			ClearDict = (DM_ClearDict)GetProcAddress(句柄, "ClearDict");
			GetMachineCodeNoMac = (DM_GetMachineCodeNoMac)GetProcAddress(句柄, "GetMachineCodeNoMac");
			GetClientRect = (DM_GetClientRect)GetProcAddress(句柄, "GetClientRect");
			EnableFakeActive = (DM_EnableFakeActive)GetProcAddress(句柄, "EnableFakeActive");
			GetScreenDataBmp = (DM_GetScreenDataBmp)GetProcAddress(句柄, "GetScreenDataBmp");
			EncodeFile = (DM_EncodeFile)GetProcAddress(句柄, "EncodeFile");
			GetCursorShapeEx = (DM_GetCursorShapeEx)GetProcAddress(句柄, "GetCursorShapeEx");
			FaqCancel = (DM_FaqCancel)GetProcAddress(句柄, "FaqCancel");
			IntToData = (DM_IntToData)GetProcAddress(句柄, "IntToData");
			FloatToData = (DM_FloatToData)GetProcAddress(句柄, "FloatToData");
			DoubleToData = (DM_DoubleToData)GetProcAddress(句柄, "DoubleToData");
			StringToData = (DM_StringToData)GetProcAddress(句柄, "StringToData");
			SetMemoryFindResultToFile = (DM_SetMemoryFindResultToFile)GetProcAddress(句柄, "SetMemoryFindResultToFile");
			EnableBind = (DM_EnableBind)GetProcAddress(句柄, "EnableBind");
			SetSimMode = (DM_SetSimMode)GetProcAddress(句柄, "SetSimMode");
			LockMouseRect = (DM_LockMouseRect)GetProcAddress(句柄, "LockMouseRect");
			SendPaste = (DM_SendPaste)GetProcAddress(句柄, "SendPaste");
			IsDisplayDead = (DM_IsDisplayDead)GetProcAddress(句柄, "IsDisplayDead");
			GetKeyState = (DM_GetKeyState)GetProcAddress(句柄, "GetKeyState");
			CopyFile = (DM_CopyFile)GetProcAddress(句柄, "CopyFile");
			IsFileExist = (DM_IsFileExist)GetProcAddress(句柄, "IsFileExist");
			DeleteFile = (DM_DeleteFile)GetProcAddress(句柄, "DeleteFile");
			MoveFile = (DM_MoveFile)GetProcAddress(句柄, "MoveFile");
			CreateFolder = (DM_CreateFolder)GetProcAddress(句柄, "CreateFolder");
			DeleteFolder = (DM_DeleteFolder)GetProcAddress(句柄, "DeleteFolder");
			GetFileLength = (DM_GetFileLength)GetProcAddress(句柄, "GetFileLength");
			ReadFile = (DM_ReadFile)GetProcAddress(句柄, "ReadFile");
			WaitKey = (DM_WaitKey)GetProcAddress(句柄, "WaitKey");
			DeleteIni = (DM_DeleteIni)GetProcAddress(句柄, "DeleteIni");
			DeleteIniPwd = (DM_DeleteIniPwd)GetProcAddress(句柄, "DeleteIniPwd");
			EnableSpeedDx = (DM_EnableSpeedDx)GetProcAddress(句柄, "EnableSpeedDx");
			EnableIme = (DM_EnableIme)GetProcAddress(句柄, "EnableIme");
			Reg = (DM_Reg)GetProcAddress(句柄, "Reg");
			SelectFile = (DM_SelectFile)GetProcAddress(句柄, "SelectFile");
			SelectDirectory = (DM_SelectDirectory)GetProcAddress(句柄, "SelectDirectory");
			LockDisplay = (DM_LockDisplay)GetProcAddress(句柄, "LockDisplay");
			FoobarSetSave = (DM_FoobarSetSave)GetProcAddress(句柄, "FoobarSetSave");
			EnumWindowSuper = (DM_EnumWindowSuper)GetProcAddress(句柄, "EnumWindowSuper");
			DownloadFile = (DM_DownloadFile)GetProcAddress(句柄, "DownloadFile");
			EnableKeypadMsg = (DM_EnableKeypadMsg)GetProcAddress(句柄, "EnableKeypadMsg");
			EnableMouseMsg = (DM_EnableMouseMsg)GetProcAddress(句柄, "EnableMouseMsg");
			RegNoMac = (DM_RegNoMac)GetProcAddress(句柄, "RegNoMac");
			RegExNoMac = (DM_RegExNoMac)GetProcAddress(句柄, "RegExNoMac");
			SetEnumWindowDelay = (DM_SetEnumWindowDelay)GetProcAddress(句柄, "SetEnumWindowDelay");
			FindMulColor = (DM_FindMulColor)GetProcAddress(句柄, "FindMulColor");
			GetDict = (DM_GetDict)GetProcAddress(句柄, "GetDict");

		}
	}
	
	const wchar_t* 屏幕找字(int x1, int y1, int x2, int y2, const wchar_t* str, double sim){
		const wchar_t* ss= Ocr(dm_, x1, y1, x2, y2, str, sim);
		return (ss);
	}
	
	int 查找(int x1, int y1, int x2, int y2, const wchar_t* str, double sim, int* x, int* y){
		int w= FindStr(dm_, x1, y1, x2, y2, str, sim, x, y);
		return (w);
	}

	int 获取结果计数(const wchar_t* str){
		int a= GetResultCount(dm_, str);
		return (a);
	}


	
	const wchar_t* 获取指定字库中指定条目的字库信息(int index, int font_index){
		return (GetDict(dm_, index, font_index));
	}

	
	int 注册大漠(const wchar_t* aaA){
		if (CreateDM== NULL )
		{
			return 0;
	}

		dm_= CreateDM(aaA);
		return dm_;
	}
	
	int 绑定窗口(int hwnd, const wchar_t* display, const wchar_t* mouse, const wchar_t* keypad, int mode){
				if (BindWindow== NULL )
		{
			return 0;
	}
		int aa;
		aa= BindWindow(dm_, hwnd, display, mouse, keypad, mode);
		return (aa);
	}
	
	int 设置路径(const wchar_t* 路径){
		return (SetPath(dm_, 路径));
	}
	
	int 输入键代码(int 键代码){
		int aa;
		aa= KeyPress(dm_, 键代码);
		return (aa);
	}
	
	const wchar_t* 版本号(){
		return (Ver(dm_));
	}
	
	int 注册(const wchar_t* 注册码, const wchar_t* 附加码){
		int a= Reg(dm_, 注册码, 附加码);
		return (a);
	}
	
	//@别名  基本_取插件版本()
	const wchar_t* Ver_(){//Ver;ID:1
	
		return (Ver(dm_));
	}
	//@别名 基本_取插件注册路径()
	const wchar_t*  GetBasePath_()
		 {
			 return GetBasePath(dm_);
		}
		//@别名 基本_设置全局路径()
		 int  SetPath_(const wchar_t*  path)
		 {
			 return (SetPath(dm_, path));
		 }
		 //@别名 后台_解除绑定窗口()
		 int  UnBindWindow_()
		 {
		return (UnBindWindow(dm_));
		 }
		 //@别名 文字_设置字库密码()
		 int  SetDictPwd_(const wchar_t*  pwd)
		 {
		return (SetDictPwd(dm_, pwd));
		 }
		 //@别名 文字_设置当前库()
		 int  UseDict_(int  字库的序号)
		 {
		return (UseDict(dm_, 字库的序号));
		 }
		 //@别名 文字_识别字符串()
		 const wchar_t*  Ocr_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (Ocr(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度));
		 }
		 //@别名 文字_找字_小字库()
		 int  FindStr_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, double  相似度, int*  X坐标, int*  Y坐标)
		 {
		return (FindStr(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串,  相似度, X坐标, Y坐标));
		 }
		 //@别名 文字_找字_小字库_返回所有()
		 const wchar_t*  FindStrEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (FindStrEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度));
		 }
		 //@别名 文字_识别位图区域文字()
		 const wchar_t*  OcrInFile_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  图片名, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (OcrInFile(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 图片名, 颜色格式串, 相似度));
		 }
		 //@别名 文字_对返回值进行解析()
		 int  GetResultCount_(const wchar_t*  待查找的字符串)
		 {
		return (GetResultCount(dm_, 待查找的字符串));
		 }
		 //@别名 文字_对返回值进行解析2()
		 int  GetResultPos_(const wchar_t*  待查找的字符串, int  字库的序号, int*  X坐标, int*  Y坐标)
		 {
		return (GetResultPos(dm_, 待查找的字符串, 字库的序号, X坐标, Y坐标));
		 }
		 //@别名 文字_设定行间距()
		 int  SetMinRowGap_(int  row_gap)
		 {
		return (SetMinRowGap(dm_, row_gap));
		 }
		 //@别名 文字_设定行高()
		 int  SetWordLineHeight_(int  line_height)
		 {
		return (SetWordLineHeight(dm_, line_height));
		 }
		 //@别名 文字_设定间隔()
		 int  SetWordGap_(int  word_gap)
		 {
		return (SetWordGap(dm_, word_gap));
		 }
		 //@别名 文字_设定文字的行距()
		 int  SetRowGapNoDict_(int  row_gap)
		 {
		return (SetRowGapNoDict(dm_, row_gap));
		 }
		 //@别名 文字_设定文字列距()
		 int  文字_设定文字列距(int  col_gap)
		 {
			 return 0;
		//return (SetColGapNoDict(dm_, col_gap));
		 }
		 //@别名 文字_设定行高_无字库()
		 int  SetWordLineHeightNoDict_(int  line_height)
		 {
		return (SetWordLineHeightNoDict(dm_,line_height));
		 }
		 //@别名 文字_设定间隔_无字库()
		 int  SetWordGapNoDict_(int  word_gap)
		 {
		return (SetWordGapNoDict(dm_, word_gap));
		 }
		 //@别名 文字_识别词组数量()
		 int  GetWordResultCount_(const wchar_t*  待查找的字符串)
		 {
		return (GetWordResultCount(dm_, 待查找的字符串));
		 }
		 //@别名 文字_识别词组坐标()
		 int  GetWordResultPos_(const wchar_t*  待查找的字符串, int  字库的序号, int*  X坐标, int*  Y坐标)
		 {
		return (GetWordResultPos(dm_, 待查找的字符串, 字库的序号, X坐标, Y坐标));
		 }
		 //@别名 文字_识别词组内容()
		 const wchar_t*  GetWordResultStr_(const wchar_t*  待查找的字符串, int  字库的序号)
		 {
		return (GetWordResultStr(dm_, 待查找的字符串, 字库的序号));
		 }
		 //@别名 文字_识别满足条件的词组()
		 const wchar_t*  GetWords_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (GetWords(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度));
		 }
		 //@别名 文字_识别满足条件的词组2()
		 const wchar_t*  GetWordsNoDict_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串)
		 {
		return (GetWordsNoDict(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串));
		 }
		 //@别名 StrStr()
		 int  StrStr_(const wchar_t*  s, const wchar_t*  待查找的字符串)
		 {
		return (StrStr(dm_, s, 待查找的字符串));
		 }
		 //@别名 键盘_按下某键()
		 int  KeyPress_(int  vk)
		 {
		return (KeyPress(dm_, vk));
		 }
		 //@别名 键盘_按住某键()
		 int  KeyDown_(int  vk)
		 {
		return (KeyDown(dm_, vk));
		 }
		 //@别名 键盘_弹起某键()
		 int  KeyUp_(int  vk)
		 {
		return (KeyUp(dm_, vk));
		 }
		 //@别名 鼠标_按下鼠标左键()
		 int  LeftClick_()
		 {
		return (LeftClick(dm_));
		 }
		 //@别名 鼠标_按下鼠标右键()
		 int  RightClick_()
		 {
		return (RightClick(dm_));
		 }
		 //@别名 鼠标_按下鼠标中键()
		 int  MiddleClick_()
		 {
		return (MiddleClick(dm_));
		 }
		 //@别名 鼠标_双击鼠标左键()
		 int  LeftDoubleClick_()
		 {
		return (LeftDoubleClick(dm_));
		 }
		 //@别名 鼠标_按住鼠标左键()
		 int  LeftDown_()
		 {
		return (LeftDown(dm_));
		 }
		 //@别名 鼠标_弹起鼠标左键()
		 int  LeftUp_()
		 {
		return (LeftUp(dm_));
		 }
		 //@别名 鼠标_按住鼠标右键()
		 int  RightDown_()
		 {
		return (RightDown(dm_));
		 }
		 //@别名 鼠标_弹起鼠标右键()
		 int  RightUp_()
		 {
		return (RightUp(dm_));
		 }
		 //@别名 鼠标_鼠标移动()
		 int  MoveTo_(int  X坐标, int  Y坐标)
		 {
		return (MoveTo(dm_, X坐标, Y坐标));
		 }
		 //@别名 鼠标_鼠标相对位置移动()
		 int  MoveR_(int  rx, int  ry)
		 {
		return (MoveR(dm_, rx, ry));
		 }
		 //@别名 图色_截图存为BMP()
		 int  Capture_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  保存的文件名)
		 {
		return (Capture(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 保存的文件名));
		 }
		 //@别名 图色_取某点颜色RGB()
		 const wchar_t*  GetColor_(int  X坐标, int  Y坐标)
		 {
		return (GetColor(dm_, X坐标, Y坐标));
		 }
		 //@别名 图色_取某点颜色BGR()
		 const wchar_t*  GetColorBG_(int  X坐标, int  Y坐标)
		 {
		return (GetColorBGR(dm_, X坐标, Y坐标));
		 }
		 //@别名 图色_RGB转BGR()
		 const wchar_t*  RGB2BGR_(const wchar_t*  rgb_color)
		 {
		return (RGB2BGR(dm_, rgb_color));
		 }
		 //@别名 图色_BGR转RGB()
		 const wchar_t*  BGR2RGB_(const wchar_t*  bgr格式的颜色字符串)
		 {
		return (BGR2RGB(dm_, bgr格式的颜色字符串));
		 }
		 //@别名 图色_比较颜色()
		 int  CmpColor_(int  X坐标, int  Y坐标, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (CmpColor(dm_, X坐标, Y坐标, 颜色格式串, 相似度));
		 }
		 //@别名  图色_找色()
		 int  FindColor_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度, int  查找方向, int*  X坐标, int*  Y坐标)
		 {
		return (FindColor(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度, 查找方向, X坐标, Y坐标));
		 }
		 //@别名 图色_找所有色()
		 const wchar_t*  FindColorEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度, int  查找方向)
		 {
		return (FindColorEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度, 查找方向));
		 }
		 //@别名 图色_取颜色均值RGB()
		 const wchar_t*  GetAveRGB_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标)
		 {
		return (GetAveRGB(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标));
		 }
		 //@别名 图色_取颜色均值HSV()
		 const wchar_t*  GetAveHSV_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标)
		 {
		return (GetAveHSV(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标));
		 }
		 //@别名 图色_取某点颜色HSV()
		 const wchar_t*  GetColorHSV_(int  X坐标, int  Y坐标)
		 {
		return (GetColorHSV(dm_, X坐标, Y坐标));
		 }
		 //@别名 窗口_窗口转屏幕坐标()
		 int  ClientToScreen_(int  指定的窗口句柄, int*  X坐标, int*  Y坐标)
		 {
		return (ClientToScreen(dm_, 指定的窗口句柄, X坐标, Y坐标));
		 }
		 //@别名 窗口_屏幕转窗口坐标()
		 int  ScreenToClient_(int  指定的窗口句柄, int*  X坐标, int*  Y坐标)
		 {
		return (ScreenToClient(dm_, 指定的窗口句柄, X坐标, Y坐标));
		 }
		 //@别名 ShowScrMsg()
		 int  ShowScrMsg_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  msg, const wchar_t*  颜色格式串)
		 {
		return (ShowScrMsg(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, msg, 颜色格式串));
		 }
		 //@别名 窗口_取活动窗口()
		 int  GetForegroundWindow_()
		 {
		return (GetForegroundWindow(dm_));
		 }
		 //@别名 窗口_取有输入焦点的句柄()
		 int  GetForegroundFocus_()
		 {
		return (GetForegroundFocus(dm_));
		 }
		 //@别名 窗口_取鼠标指向窗口句柄()
		 int  GetMousePointWindow_()
		 {
		return (GetMousePointWindow(dm_));
		 }
		 //@别名 窗口_取坐标窗口句柄()
		 int  GetPointWindow_(int  X坐标, int  Y坐标)
		 {
		return (GetPointWindow(dm_, X坐标, Y坐标));
		 }
		 //@别名 窗口_枚举窗口()
		 const wchar_t*  EnumWindow_(int  parent, const wchar_t*  窗口标题, const wchar_t*  窗口类名, int  filter)
		 {
		return (EnumWindow(dm_, parent, 窗口标题, 窗口类名, filter));
		 }
		 //@别名 窗口_移动窗口()
		 int  MoveWindow_(int  指定的窗口句柄, int  X坐标, int  Y坐标)
		 {
		return (MoveWindow(dm_, 指定的窗口句柄, X坐标, Y坐标));
		 }
		 //@别名 窗口_取窗口属性()
		 int GetWindowState_(int  指定的窗口句柄, int  flag)
		 {
		return (GetWindowState(dm_, 指定的窗口句柄, flag));
		 }
		 //@别名 窗口_取相关句柄()
		 int  GetWindow_(int  指定的窗口句柄, int  flag)
		 {
		return (GetWindow(dm_, 指定的窗口句柄, flag));
		 }
		 //@别名 窗口_取特殊窗口()
		 int  GetSpecialWindow_(int  flag)
		 {
		return (GetSpecialWindow(dm_, flag));
		 }
		 //@别名 窗口_设置标题()
		 int  SetWindowText_(int  指定的窗口句柄, const wchar_t*  text)
		 {
		return (SetWindowText(dm_, 指定的窗口句柄, text));
		 }
		 //@别名 窗口_设置大小()
		 int  SetWindowSize_(int  指定的窗口句柄, int  width, int  height)
		 {
		return (SetWindowSize(dm_, 指定的窗口句柄, width, height));
		 }
		 //@别名 窗口_取窗口大小()
		 int  GetClientSize_(int  指定的窗口句柄, int* width, int* height)
		 {
		return (GetClientSize(dm_, 指定的窗口句柄, width, height));
		 }
		 //@别名 窗口_取窗口位置()
		 int  GetWindowRect_(int  指定的窗口句柄, int*  左上X坐标, int*  左上Y坐标, int*  右下X坐标, int*  右下Y坐标)
		 {
		return (GetWindowRect(dm_, 指定的窗口句柄, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标));
		 }
		 //@别名 窗口_取窗口标题()
		 const wchar_t*  GetWindowTitle_(int  指定的窗口句柄)
		 {
		return (GetWindowTitle(dm_, 指定的窗口句柄));
		 }
		 //@别名 窗口_取窗口类名()
		 const wchar_t*  GetWindowClass_(int  指定的窗口句柄)
		 {
		return (GetWindowClass(dm_, 指定的窗口句柄));
		 }
		 //@别名 窗口_设置状态()
		 int  SetWindowState_(int  指定的窗口句柄, int  flag)
		 {
		return (SetWindowState(dm_, 指定的窗口句柄, flag));
		 }
		 //@别名 CMD()
		 int  SendCommand_(const wchar_t*  cmd)
		 {
		return (SendCommand(dm_, cmd));
		 }
		 //@别名 基本_设置是否弹出错误信息()
		 int  SetShowErrorMsg_(int  show)
		 {
		return (SetShowErrorMsg(dm_, show));
		 }
		 //@别名 Foobar_创建矩形()
		 int  CreateFoobarRect_(int  指定的窗口句柄, int  X坐标, int  Y坐标, int  w, int  h)
		 {
		return (CreateFoobarRect(dm_, 指定的窗口句柄, X坐标, Y坐标, w, h));
		 }
		 //@别名 Foobar_创建圆角矩形()
		 int  CreateFoobarRoundRect_(int  指定的窗口句柄, int  X坐标, int  Y坐标, int  w, int  h, int  rw, int  rh)
		 {
		return (CreateFoobarRoundRect(dm_, 指定的窗口句柄, X坐标, Y坐标, w, h, rw, rh));
		 }
		 //@别名 Foobar_创建椭圆()
		 int  CreateFoobarEllipse_(int  指定的窗口句柄, int  X坐标, int  Y坐标, int  w, int  h)
		 {
		return (CreateFoobarEllipse(dm_, 指定的窗口句柄, X坐标, Y坐标, w, h));
		 }
		 //@别名 Foobar_从位图创建()
		 int  CreateFoobarCustom_(int  指定的窗口句柄, int  X坐标, int  Y坐标, const wchar_t*  pic, const wchar_t*  trans_color, double  相似度)
		 {
		return (CreateFoobarCustom(dm_, 指定的窗口句柄, X坐标, Y坐标, pic, trans_color, 相似度));
		 }
		 //@别名 Foobar_填充矩形()
		 int  FoobarFillRect_(int  指定的窗口句柄, int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串)
		 {
		return (FoobarFillRect(dm_, 指定的窗口句柄, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串));
		 }
		 //@别名 Foobar_绘制文字()
		 int  FoobarDrawText_(int  指定的窗口句柄, int  X坐标, int  Y坐标, int  w, int  h, const wchar_t*  text, const wchar_t*  颜色格式串, int  align)
		 {
		return (FoobarDrawText(dm_, 指定的窗口句柄, X坐标, Y坐标, w, h, text, 颜色格式串, align));
		 }
		 //@别名 Foobar_绘制图像()
		 int  FoobarDrawPic_(int  指定的窗口句柄, int  X坐标, int  Y坐标, const wchar_t*  pic, const wchar_t*  trans_color)
		 {
		return (FoobarDrawPic(dm_, 指定的窗口句柄, X坐标, Y坐标, pic, trans_color));
		 }
		 //@别名 Foobar_刷新()
		 int  FoobarUpdate_(int  指定的窗口句柄)
		 {
		return (FoobarUpdate(dm_, 指定的窗口句柄));
		 }
		 //@别名 Foobar_锁定()
		 int  FoobarLock_(int  指定的窗口句柄)
		 {
		return (FoobarLock(dm_, 指定的窗口句柄));
		 }
		 //@别名 Foobar_解锁()
		 int  FoobarUnlock_(int  指定的窗口句柄)
		 {
		return (FoobarUnlock(dm_, 指定的窗口句柄));
		 }
		 //@别名 Foobar_设置字体()
		 int  FoobarSetFont_(int  指定的窗口句柄, const wchar_t*  font_name, int  size, int  flag)
		 {
		return (FoobarSetFont(dm_, 指定的窗口句柄, font_name, size, flag));
		 }
		 //@别名 Foobar_设置滚动文本框()
		 int  FoobarTextRect_(int  指定的窗口句柄, int  X坐标, int  Y坐标, int  w, int  h)
		 {
		return (FoobarTextRect(dm_, 指定的窗口句柄, X坐标, Y坐标, w, h));
		 }
		 //@别名 Foobar_输出滚动文字()
		 int FoobarPrintText_(int  指定的窗口句柄, const wchar_t*  text, const wchar_t*  颜色格式串)
		 {
		return (FoobarPrintText(dm_, 指定的窗口句柄, text, 颜色格式串));
		 }
		 //@别名 Foobar_清除滚动文本区()
		 int  FoobarClearText_(int  指定的窗口句柄)
		 {
		return (FoobarClearText(dm_, 指定的窗口句柄));
		 }
		 //@别名 Foobar_设置行间距()
		 int  FoobarTextLineGap_(int  指定的窗口句柄, int  gap)
		 {
		return (FoobarTextLineGap(dm_, 指定的窗口句柄, gap));
		 }
		 //@别名 系統_播放MP3或wav文件()
		 int  Play_(const wchar_t*  保存的文件名)
		 {
		return (Play(dm_, 保存的文件名));
		 }
		 //@别名 答题_截取动画或图像()
		 int  FaqCapture_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, int  jpg压缩比率, int  时长, int  总共截取多久的动画)
		 {
		return (FaqCapture(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, jpg压缩比率, 时长, 总共截取多久的动画));
		 }
		 //@别名 答题_释放句柄()
		 int  FaqRelease_(int  handle)
		 {
		return (FaqRelease(dm_, handle));
		 }
		 //@别名 答题_同步发送()
		 const wchar_t*  FaqSend_(const wchar_t*  server, int  handle, int  request_type, int  time_out)
		 {
		return (FaqSend(dm_, server, handle, request_type, time_out));
		 }
		 //@别名 系统_蜂鸣器()
		 int  Beep_(int  频率, int  时长)
		 {
		return (Beep(dm_, 频率, 时长));
		 }
		 //@别名 Foobar_关闭Foobar()
		 int  FoobarClose_(int  指定的窗口句柄)
		 {
		return (FoobarClose(dm_, 指定的窗口句柄));
		 }
		 //@别名 MoveDD_()
		 int  MoveDD_(int  dx, int  dy)
		 {
		return (MoveDD(dm_,dx, dy));
		 }
		 //@别名 答题_取数据大小()
		 int  FaqGetSize_(int  handle)
		 {
		return (FaqGetSize(dm_, handle));
		 }
		 //@别名  图色_预先加载图片()
		 int  LoadPic_(const wchar_t*  图片名)
		 {
		return (LoadPic(dm_, 图片名));
		 }
		 //@别名 图色_释放图片()
		 int  FreePic_(const wchar_t*  图片名)
		 {
		return (FreePic(dm_, 图片名));
		 }
		 //@别名 图色_取图像二进制数()
		 int  GetScreenData_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标)
		 {
		return (GetScreenData(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标));
		 }
		 //@别名 图色_释放颜色数据()
		 int  FreeScreenData_(int  handle)
		 {
		return (FreeScreenData(dm_, handle));
		 }
		 //@别名 鼠标_滚轮向上滚()
		 int  WheelUp_()
		 {
		return (WheelUp(dm_));
		 }
		 //@别名 鼠标_滚轮向下滚()
		 int  WheelDown_()
		 {
		return (WheelDown(dm_));
		 }
		 //@别名 鼠标_设置鼠标延时()
		 int  SetMouseDelay_(const wchar_t*  type, int  时长)
		 {
		return (SetMouseDelay(dm_, type, 时长));
		 }
		 //@别名 键盘_设置按键延时()
		 int  SetKeypadDelay_(const wchar_t*  type, int  时长)
		 {
		return (SetKeypadDelay(dm_, type, 时长));
		 }
		 //@别名 GetEnv()
		 const wchar_t*  GetEnv_(int  字库的序号, const wchar_t*  name)
		 {
		return (GetEnv(dm_, 字库的序号, name));
		 }
		 //@别名 SetEnv()
		 int  SetEnv_(int  字库的序号, const wchar_t*  name, const wchar_t*  value)
		 {
		return (SetEnv(dm_, 字库的序号, name, value));
		 }
		 //@别名 窗口_发送文本新()
		 int  SendString_(int  指定的窗口句柄, const wchar_t*  待查找的字符串)
		 {
		return (SendString(dm_, 指定的窗口句柄, 待查找的字符串));
		 }
		 //@别名 DelEnv()
		 int  DelEnv_(int  字库的序号, const wchar_t*  name)
		 {
		return (DelEnv(dm_, 字库的序号, name));
		 }
		 //@别名 基本_取全局路径()
		 const wchar_t*  GetPath_()
		 {
		return (GetPath(dm_));
		 }
		 //@别名 文字_设置字库()
		 int  SetDict_(int  字库的序号, const wchar_t*  dict_name)
		 {
		return (SetDict(dm_, 字库的序号, dict_name));
		 }
		 //@别名 图色_找图()
		 int  FindPic_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  图片名, const wchar_t*  颜色色偏, double  相似度, int  查找方向, int*  X坐标, int*  Y坐标)
		 {
		return (FindPic(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 图片名, 颜色色偏, 相似度, 查找方向, X坐标, Y坐标));
		 }
		 //@别名 图色_找图_返回所有()
		 const wchar_t*  FindPicEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  图片名, const wchar_t*  颜色色偏, double  相似度, int  查找方向)
		 {
		return (FindPicEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 图片名, 颜色色偏, 相似度, 查找方向));
		 }
		 //@别名 窗口_设置尺寸()
		 int  SetClientSize_(int  指定的窗口句柄, int  width, int  height)
		 {
		return (SetClientSize(dm_, 指定的窗口句柄, width, height));
		 }
		 //@别名 内存_读整数数值()
		 int  ReadInt_(int  指定的窗口句柄, const wchar_t*  addr, int  type)
		 {
		return (ReadInt(dm_, 指定的窗口句柄, addr, type));
		 }
		 //@别名 内存_读单精度()
		 double  ReadFloat_(int  指定的窗口句柄, const wchar_t*  addr)
		 {
		return (ReadFloat(dm_, 指定的窗口句柄, addr));
		 }
		 //@别名 内存_读双精度()
		 double  ReadDouble_(int  指定的窗口句柄, const wchar_t*  addr)
		 {
		return (ReadDouble(dm_, 指定的窗口句柄, addr));
		 }
		 //@别名 内存_搜索整数()
		 const wchar_t*  FindInt_(int  指定的窗口句柄, const wchar_t*  addr_range, int  int_value_min, int  int_value_max, int  type)
		 {
		return (FindInt(dm_, 指定的窗口句柄, addr_range, int_value_min, int_value_max, type));
		 }
		 //@别名 内存_搜索单精度浮点数()
		 const wchar_t*  FindFloat_(int  指定的窗口句柄, const wchar_t*  addr_range, double  float_value_min, double  float_value_max)
		 {
		return (FindFloat(dm_, 指定的窗口句柄, addr_range, float_value_min, float_value_max));
		 }
		 //@别名 内存_搜索双精度浮点数()
		 const wchar_t*  FindDouble_(int  指定的窗口句柄, const wchar_t*  addr_range, double  double_value_min, double  double_value_max)
		 {
		return (FindDouble(dm_, 指定的窗口句柄, addr_range, double_value_min, double_value_max));
		 }
		 //@别名 内存_搜索字符串()
		 const wchar_t*  FindString_(int  指定的窗口句柄, const wchar_t*  addr_range, const wchar_t*  string_value, int  type)
		 {
		return (FindString(dm_, 指定的窗口句柄, addr_range, string_value, type));
		 }
		 //@别名 取进程下模块的基址()
		 int  GetModuleBaseAddr_(int  指定的窗口句柄, const wchar_t*  module_name)
		 {
		return (GetModuleBaseAddr(dm_, 指定的窗口句柄, module_name));
		 }
		 //@别名 MoveToEx_()
		 const wchar_t*  MoveToEx_(int  X坐标, int  Y坐标, int  w, int  h)
		 {
		return (MoveToEx(dm_, X坐标, Y坐标, w, h));
		 }
		 //@别名 图色_根据通配符获取文件()
		 const wchar_t*  MatchPicName_(const wchar_t*  图片名)
		 {
		return (MatchPicName(dm_, 图片名));
		 }
		 //@别名 文字_添加字库信息()
		 int  AddDict_(int  字库的序号, const wchar_t*  字库描述串)
		 {
		return (AddDict(dm_, 字库的序号, 字库描述串));
		 }
		 //@别名  EnterCri()
		 int  EnterCri_()
		 {
		return (EnterCri(dm_));
		 }
		 //@别名  LeaveCri()
		 int  LeaveCri_()
		 {
		return (LeaveCri(dm_));
		 }
		 //@别名 内存_写整数数值()
		 int  WriteInt_(int  指定的窗口句柄, const wchar_t*  addr, int  type, int  v)
		 {
		return (WriteInt(dm_, 指定的窗口句柄, addr, type, v));
		 }
		 //@别名 内存_写单精度()
		 int  WriteFloat_(int  指定的窗口句柄, const wchar_t*  addr, double  v)
		 {
		return (WriteFloat(dm_, 指定的窗口句柄, addr, v));
		 }
		 //@别名 内存_写双精度()
		 int  WriteDouble_(int  指定的窗口句柄, const wchar_t*  addr, double  v)
		 {
		return (WriteDouble(dm_, 指定的窗口句柄, addr, v));
		 }
		 //@别名 内存_写字符串()
		 int  WriteString_(int  指定的窗口句柄, const wchar_t*  addr, int  type, const wchar_t*  v)
		 {
		return (WriteString(dm_, 指定的窗口句柄, addr, type, v));
		 }
		 //@别名 汇编_添加MASM汇编指令()
		 int  AsmAdd_(const wchar_t*  MASM汇编指令)
		 {
		return (AsmAdd(dm_, MASM汇编指令));
		 }
		 //@别名 汇编_清除缓冲区()
		 int  AsmClear_()
		 {
		return (AsmClear(dm_));
		 }
		 //@别名 汇编_执行指令()
		 int  AsmCall_(int  指定的窗口句柄, int  模式)
		 {
		return (AsmCall(dm_, 指定的窗口句柄, 模式));
		 }
		 //@别名 图色_多点找色()
		 int  FindMultiColor_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  first_color, const wchar_t*  offset_color, double  相似度, int  查找方向, int*  X坐标, int*  Y坐标)
		 {
		return (FindMultiColor(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, first_color, offset_color, 相似度, 查找方向, X坐标, Y坐标));
		 }
		 //@别名 图色_多点找所有色()
		 const wchar_t*  FindMultiColorEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  first_color, const wchar_t*  offset_color, double  相似度, int  查找方向)
		 {
		return (FindMultiColorEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, first_color, offset_color, 相似度, 查找方向));
		 }
		 //@别名 汇编_汇编指令转机器码()
		 const wchar_t*  AsmCode_(int  用AsmAdd添加到缓冲区的第一条指令所在的地址)
		 {
		return (AsmCode(dm_, 用AsmAdd添加到缓冲区的第一条指令所在的地址));
		 }
		 //@别名 汇编_机器码转汇编语言()
		 const wchar_t*  Assemble_(const wchar_t*  MASM汇编指令, int  用AsmAdd添加到缓冲区的第一条指令所在的地址, int  表示转换的汇编语言是否以大写输出)
		 {
		return (Assemble(dm_, MASM汇编指令, 用AsmAdd添加到缓冲区的第一条指令所在的地址, 表示转换的汇编语言是否以大写输出));
		 }
		 //@别名 窗口_设置透明度()
		 int  SetWindowTransparent_(int  指定的窗口句柄, int  v)
		 {
		return (SetWindowTransparent(dm_, 指定的窗口句柄, v));
		 }
		 //@别名 内存_读二进制数据()
		 const wchar_t*  ReadData_(int  指定的窗口句柄, const wchar_t*  addr, int  len)
		 {
		return (ReadData(dm_, 指定的窗口句柄, addr, len));
		 }
		 //@别名 内存_写二进制数据()
		 int  WriteData_(int  指定的窗口句柄, const wchar_t*  addr, const wchar_t*  data)
		 {
		return (WriteData(dm_, 指定的窗口句柄, addr, data));
		 }
		 //@别名 内存_搜索二进制数据()
		 const wchar_t*  FindData_(int  指定的窗口句柄, const wchar_t*  addr_range, const wchar_t*  data)
		 {
		return (FindData(dm_, 指定的窗口句柄, addr_range, data));
		 }
		 //@别名 图色_设置图片密码()
		 int  SetPicPwd_(const wchar_t*  pwd)
		 {
		return (SetPicPwd(dm_, pwd));
		 }
		 //@别名 Log()
		 int  Log_(const wchar_t*  info)
		 {
		return (Log(dm_, info));
		 }
		 //@别名 文字_找字_小字库_易()
		 const wchar_t*  FindStrE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (FindStrE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度));
		 }
		 //@别名 图色_找色_易()
		 const wchar_t*  FindColorE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度, int  查找方向)
		 {
		return (FindColorE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度, 查找方向));
		 }
		 //@别名 图色_找图_易()
		 const wchar_t*  FindPicE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  图片名, const wchar_t*  颜色色偏, double  相似度, int  查找方向)
		 {
		return (FindPicE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 图片名, 颜色色偏, 相似度, 查找方向));
		 }
		 //@别名 图色_多点找色_易()
		 const wchar_t*  FindMultiColorE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  first_color, const wchar_t*  offset_color, double  相似度, int  查找方向)
		 {
		return (FindMultiColorE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, first_color, offset_color, 相似度, 查找方向));
		 }
		 //@别名 文字_设定精准识别()
		 int  SetExactOcr_(int  exact_ocr)
		 {
		return (SetExactOcr(dm_, exact_ocr));
		 }
		 //@别名 内存_读字符串()
		 const wchar_t*  ReadString_(int  指定的窗口句柄, const wchar_t*  addr, int  type, int  len)
		 {
		return (ReadString(dm_, 指定的窗口句柄, addr, type, len));
		 }
		 //@别名 Foobar_设置文字输出方向()
		 int FoobarTextPrintDir_(int  指定的窗口句柄, int  查找方向)
		 {
		return (FoobarTextPrintDir(dm_, 指定的窗口句柄, 查找方向));
		 }
		 //@别名 文字_识别字符串_返回所有()
		 const wchar_t*  OcrEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (OcrEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 相似度));
		 }
		 //@别名 基本_设定图色获取方式()
		 int  SetDisplayInput_(const wchar_t*  模式)
		 {
		return (SetDisplayInput(dm_, 模式));
		 }
		 //@别名 系統_取开机时间()
		 int  GetTime_()
		 {
		return (GetTime(dm_));
		 }
		 //@别名 系統_取屏幕的宽度()
		 int  GetScreenWidth_()
		 {
		return (GetScreenWidth(dm_));
		 }
		 //@别名 系統_取屏幕的高度()
		 int  GetScreenHeight_()
		 {
		return (GetScreenHeight(dm_));
		 }
		 //@别名 后台_绑定窗口高级()
		 int  BindWindowEx_(int  指定的窗口句柄, const wchar_t*  屏幕颜色获取方式, const wchar_t*  鼠标仿true模式, const wchar_t*  键盘仿true模式, const wchar_t*  公共属性, int  模式)
		 {
		return (BindWindowEx(dm_, 指定的窗口句柄, 屏幕颜色获取方式, 鼠标仿true模式, 键盘仿true模式, 公共属性, 模式));
		 }
		 //@别名 GetDiskSerial()
		 const wchar_t*  GetDiskSerial_()
		 {
		return (GetDiskSerial(dm_));
		 }
		 //@别名 Md5()
		 const wchar_t*  Md5_(const wchar_t*  待查找的字符串)
		 {
		return (Md5(dm_, 待查找的字符串));
		 }
		 //@别名 返回网卡的物理地址()
		 const wchar_t* GetMac_()
		 {
		return (GetMac(dm_));
		 }
		 //@别名 杂项_激活输入法()
		 int  ActiveInputMethod_(int  指定的窗口句柄, const wchar_t*  输入法名字)
		 {
		return (ActiveInputMethod(dm_, 指定的窗口句柄, 输入法名字));
		 }
		 //@别名 杂项_输入法是否开启()
		 int  CheckInputMethod_(int  指定的窗口句柄, const wchar_t*  输入法名字)
		 {
		return (CheckInputMethod(dm_, 指定的窗口句柄, 输入法名字));
		 }
		 //@别名 杂项_检测输入法()
		 int  FindInputMethod_(const wchar_t*  输入法名字)
		 {
		return (FindInputMethod(dm_, 输入法名字));
		}
		 //@别名 杂项_取系统位置()
		 int  GetCursorPos_(int*  X坐标, int*  Y坐标)
		 {
		return (GetCursorPos(dm_, X坐标, Y坐标));
		 }
		 //@别名 后台_绑定窗口()
		 int  BindWindow_(int  指定的窗口句柄, const wchar_t*  屏幕颜色获取方式, const wchar_t*  鼠标仿true模式, const wchar_t*  键盘仿true模式, int  模式)
		 {
		return (BindWindow(dm_, 指定的窗口句柄, 屏幕颜色获取方式, 鼠标仿true模式, 键盘仿true模式, 模式));
		 }
		 //@别名  窗口_取窗口句柄()
		 int  FindWindow_(const wchar_t*  窗口类名, const wchar_t*  title_name)
		 {
		return (FindWindow(dm_, 窗口类名, title_name));
		 }
		 //@别名 系统_取色深()
		 int  GetScreenDepth_()
		 {
		return (GetScreenDepth(dm_));
		 }
		 //@别名 系统_设置系统的分辨率()
		 int  SetScreen_(int  width, int  height, int  depth)
		 {
		return (SetScreen(dm_, width, height, depth));
		 }
		 //@别名 系统_退出系统()
		 int  ExitOs_(int  type)
		 {
		return (ExitOs(dm_, type));
		 }
		 //@别名 系统_取系统路径()
		 const wchar_t*  GetDir_(int  type)
		 {
		return (GetDir(dm_, type));
		 }
		 //@别名 系统_取系统类型()
		 int  GetOsType_()
		 {
		return (GetOsType(dm_));
		 }
		 //@别名 窗口_取子窗口句柄()
		 int  FindWindowEx_(int  parent, const wchar_t*  窗口类名, const wchar_t*  title_name)
		 {
		return (FindWindowEx(dm_, parent, 窗口类名, title_name));
		 }
		 //@别名 SetExportDict()
		 int  SetExportDict_(int  字库的序号, const wchar_t*  dict_name)
		 {
		return (SetExportDict(dm_, 字库的序号, dict_name));
		 }
		 //@别名 鼠标_取特征码()
		 const wchar_t*  GetCursorShape_()
		 {
		return (GetCursorShape(dm_));
		 }
		 //@别名 后台_降低CPU占用()
		 int  DownCpu_(int  rate)
		 {
		return (DownCpu(dm_ ,rate));
		 }
		 //@别名 鼠标_获取热点位置()
		 const wchar_t*  GetCursorSpot_()
		 {
		return (GetCursorSpot(dm_));
		 }
		 //@别名 窗口_发送文本旧()
		 int  SendString2_(int  指定的窗口句柄, const wchar_t*  待查找的字符串)
		 {
		return (SendString2(dm_, 指定的窗口句柄, 待查找的字符串));
		 }
		 //@别名 答题_异步发送()
		 int  FaqPost_(const wchar_t*  server, int  handle, int  request_type, int  time_out)
		 {
		return (FaqPost(dm_, server, handle, request_type, time_out));
		 }
		 //@别名 答题_取答案()
		 const wchar_t*  FaqFetch_()
		 {
		return (FaqFetch(dm_));
		 }
		 //@别名 文字_提取点阵信息()
		 const wchar_t*  FetchWord_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  颜色格式串, const wchar_t*  待定义的文字)
		 {
		return (FetchWord(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 颜色格式串, 待定义的文字));
		 }
		 //@别名 图色_截图存为JPG()
		 int  CaptureJpg_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  保存的文件名, int  jpg压缩比率)
		 {
		return (CaptureJpg(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 保存的文件名, jpg压缩比率));
		 }
		 //@别名 文字_找字_系统字库_返回索引()
		 int  FindStrWithFont_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度, const wchar_t*  font_name, int  font_size, int  flag, int*  X坐标, int*  Y坐标)
		 {
		return (FindStrWithFont(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度, font_name, font_size, flag, X坐标, Y坐标));
		 }
		 //@别名 文字_找字_系统字库_返回坐标及索引()
		 const wchar_t*  FindStrWithFontE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度, const wchar_t*  font_name, int  font_size, int  flag)
		 {
		return (FindStrWithFontE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度, font_name, font_size, flag));
		 }
		 //@别名 文字_找字_系统字库_返回所有()
		 const wchar_t*  FindStrWithFontEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度, const wchar_t*  font_name, int  font_size, int  flag)
		 {
		return (FindStrWithFontEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度, font_name, font_size, flag));
		 }
		 //@别名 文字_取字库描述信息()
		 const wchar_t*  GetDictInfo_(const wchar_t*  待查找的字符串, const wchar_t*  font_name, int  font_size, int  flag)
		 {
		return (GetDictInfo(dm_, 待查找的字符串, font_name, font_size, flag));
		 }
		 //@别名 文字_保存字库()
		 int  SaveDict_(int  字库的序号, const wchar_t*  保存的文件名)
		 { 
		return (SaveDict(dm_, 字库的序号, 保存的文件名));
		 }
		 //@别名 窗口_取窗口进程ID()
		 int  GetWindowProcessId_(int  指定的窗口句柄)
		 {
		return (GetWindowProcessId(dm_, 指定的窗口句柄));
		 }
		 //@别名 窗口_取进程exe文件路径()
		 const wchar_t*  GetWindowProcessPath_(int  指定的窗口句柄)
		 {
		return (GetWindowProcessPath(dm_, 指定的窗口句柄));
		 }
		 //@别名 后台_禁止外部输入()
		 int  LockInput_(int  lock)
		 {
		return (LockInput(dm_, lock));
		 }
		 //@别名 图色_取图片的尺寸()
		 const wchar_t*  GetPicSize_(const wchar_t*  图片名)
		 {
		return (GetPicSize(dm_, 图片名));
		 }
		 //@别名 基本_取大漠ID值()
		 int  GetID_()
		 {
		return (GetID(dm_));
		 }
		 //@别名 图色_截图存为PNG()
		 int  CapturePng_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  保存的文件名)
		 {
		return (CapturePng(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 保存的文件名));
		 }
		 //@别名 图色_截动画存为GIF()
		 int  CaptureGif_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  保存的文件名, int  时长, int  总共截取多久的动画)
		 {
		return (CaptureGif(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 保存的文件名, 时长, 总共截取多久的动画));
		 }
		 //@别名  图色_转为24位BMP()
		 int  ImageToBmp_(const wchar_t*  图片名, const wchar_t*  bmp_name)
		 {
		return (ImageToBmp(dm_, 图片名, bmp_name));
		 }
		 //@别名 文字_找字_大字库()
		 int  FindStrFast_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度, int*  X坐标, int*  Y坐标)
		 {
		return (FindStrFast(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度, X坐标, Y坐标));
		 }
		 //@别名 文字_找字_大字库_返回所有()
		 const wchar_t*  FindStrFastEx_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (FindStrFastEx(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度));
		 }
		 //@别名 文字_找字_大字库_易()
		 const wchar_t*  FindStrFastE_(int  左上X坐标, int  左上Y坐标, int  右下X坐标, int  右下Y坐标, const wchar_t*  待查找的字符串, const wchar_t*  颜色格式串, double  相似度)
		 {
		return (FindStrFastE(dm_, 左上X坐标, 左上Y坐标, 右下X坐标, 右下Y坐标, 待查找的字符串, 颜色格式串, 相似度));
		}
		 //@别名 图色_开启调试模式()
		 int  EnableDisplayDebug_(int  enable_debug)
		 {
		return (EnableDisplayDebug(dm_, enable_debug));
		}
		 //@别名 图色_抓取上次区域()
		 int  CapturePre_(const wchar_t*  保存的文件名)
		 {
		return (CapturePre(dm_, 保存的文件名));
		}


	//@隐藏{
	~DmSoft(){
		FreeDM();
		FreeLibrary(句柄);
	}
	//@隐藏}
private:
	HINSTANCE 句柄;
	int dm_;
	DM_GetResultPos GetResultPos;
	DM_StrStr StrStr;
	DM_SendCommand SendCommand;
	DM_UseDict UseDict;
	DM_GetBasePath GetBasePath;
	DM_SetDictPwd SetDictPwd;
	DM_OcrInFile OcrInFile;
	DM_Capture Capture;
	DM_KeyDown KeyDown;
	DM_KeyUp KeyUp;
	DM_LeftClick LeftClick;
	DM_RightClick RightClick;
	DM_MiddleClick MiddleClick;
	DM_LeftDoubleClick LeftDoubleClick;
	DM_LeftDown LeftDown;
	DM_LeftUp LeftUp;
	DM_RightDown RightDown;
	DM_RightUp RightUp;
	DM_MoveTo MoveTo;
	DM_MoveR MoveR;
	DM_GetColor GetColor;
	DM_GetColorBGR GetColorBGR;
	DM_RGB2BGR RGB2BGR;
	DM_BGR2RGB BGR2RGB;
	DM_UnBindWindow UnBindWindow;
	DM_CmpColor CmpColor;
	DM_ClientToScreen ClientToScreen;
	DM_ScreenToClient ScreenToClient;
	DM_ShowScrMsg ShowScrMsg;
	DM_SetMinRowGap SetMinRowGap;
	DM_SetMinColGap SetMinColGap;
	DM_FindColor FindColor;
	DM_FindColorEx FindColorEx;
	DM_SetWordLineHeight SetWordLineHeight;
	DM_SetWordGap SetWordGap;
	DM_SetRowGapNoDict SetRowGapNoDict;
	DM_SetWordLineHeightNoDict SetWordLineHeightNoDict;
	DM_SetWordGapNoDict SetWordGapNoDict;
	DM_GetWordResultCount GetWordResultCount;
	DM_GetWordResultPos GetWordResultPos;
	DM_GetWordResultStr GetWordResultStr;
	DM_GetWords GetWords;
	DM_GetWordsNoDict GetWordsNoDict;
	DM_SetShowErrorMsg SetShowErrorMsg;
	DM_GetClientSize GetClientSize;
	DM_MoveWindow MoveWindow;
	DM_GetColorHSV GetColorHSV;
	DM_GetAveRGB GetAveRGB;
	DM_GetAveHSV GetAveHSV;
	DM_GetForegroundWindow GetForegroundWindow;
	DM_GetForegroundFocus GetForegroundFocus;
	DM_GetMousePointWindow GetMousePointWindow;
	DM_GetPointWindow GetPointWindow;
	DM_EnumWindow EnumWindow;
	DM_GetWindowState GetWindowState;
	DM_GetWindow GetWindow;
	DM_GetSpecialWindow GetSpecialWindow;
	DM_SetWindowText SetWindowText;
	DM_SetWindowSize SetWindowSize;
	DM_GetWindowRect GetWindowRect;
	DM_GetWindowTitle GetWindowTitle;
	DM_GetWindowClass GetWindowClass;
	DM_SetWindowState SetWindowState;
	DM_CreateFoobarRect CreateFoobarRect;
	DM_CreateFoobarRoundRect CreateFoobarRoundRect;
	DM_CreateFoobarEllipse CreateFoobarEllipse;
	DM_CreateFoobarCustom CreateFoobarCustom;
	DM_FoobarFillRect FoobarFillRect;
	DM_FoobarDrawText FoobarDrawText;
	DM_FoobarDrawPic FoobarDrawPic;
	DM_FoobarUpdate FoobarUpdate;
	DM_FoobarLock FoobarLock;
	DM_FoobarUnlock FoobarUnlock;
	DM_FoobarSetFont FoobarSetFont;
	DM_FoobarTextRect FoobarTextRect;
	DM_FoobarPrintText FoobarPrintText;
	DM_FoobarClearText FoobarClearText;
	DM_FoobarTextLineGap FoobarTextLineGap;
	DM_Play Play;
	DM_FaqCapture FaqCapture;
	DM_FaqRelease FaqRelease;
	DM_FaqSend FaqSend;
	DM_Beep Beep;
	DM_FoobarClose FoobarClose;
	DM_MoveDD MoveDD;
	DM_FaqGetSize FaqGetSize;
	DM_LoadPic LoadPic;
	DM_FreePic FreePic;
	DM_GetScreenData GetScreenData;
	DM_FreeScreenData FreeScreenData;
	DM_WheelUp WheelUp;
	DM_WheelDown WheelDown;
	DM_SetMouseDelay SetMouseDelay;
	DM_SetKeypadDelay SetKeypadDelay;
	DM_GetEnv GetEnv;
	DM_SetEnv SetEnv;
	DM_SendString SendString;
	DM_DelEnv DelEnv;
	DM_GetPath GetPath;
	DM_SetDict SetDict;
	DM_FindPic FindPic;
	DM_FindPicEx FindPicEx;
	DM_SetClientSize SetClientSize;
	DM_ReadInt ReadInt;
	DM_ReadFloat ReadFloat;
	DM_ReadDouble ReadDouble;
	DM_FindInt FindInt;
	DM_FindFloat FindFloat;
	DM_FindDouble FindDouble;
	DM_FindString FindString;
	DM_GetModuleBaseAddr GetModuleBaseAddr;
	DM_MoveToEx MoveToEx;
	DM_MatchPicName MatchPicName;
	DM_AddDict AddDict;
	DM_EnterCri EnterCri;
	DM_LeaveCri LeaveCri;
	DM_WriteInt WriteInt;
	DM_WriteFloat WriteFloat;
	DM_WriteDouble WriteDouble;
	DM_WriteString WriteString;
	DM_AsmAdd AsmAdd;
	DM_AsmClear AsmClear;
	DM_AsmCall AsmCall;
	DM_FindMultiColor FindMultiColor;
	DM_FindMultiColorEx FindMultiColorEx;
	DM_AsmCode AsmCode;
	DM_Assemble Assemble;
	DM_SetWindowTransparent SetWindowTransparent;
	DM_ReadData ReadData;
	DM_WriteData WriteData;
	DM_FindData FindData;
	DM_SetPicPwd SetPicPwd;
	DM_Log Log;
	DM_FindStrE FindStrE;
	DM_FindColorE FindColorE;
	DM_FindPicE FindPicE;
	DM_FindMultiColorE FindMultiColorE;
	DM_SetExactOcr SetExactOcr;
	DM_ReadString ReadString;
	DM_FoobarTextPrintDir FoobarTextPrintDir;
	DM_OcrEx OcrEx;
	DM_SetDisplayInput SetDisplayInput;
	DM_GetTime GetTime;
	DM_GetScreenWidth GetScreenWidth;
	DM_GetScreenHeight GetScreenHeight;
	DM_BindWindowEx BindWindowEx;
	DM_GetDiskSerial GetDiskSerial;
	DM_Md5 Md5;
	DM_GetMac GetMac;
	DM_ActiveInputMethod ActiveInputMethod;
	DM_CheckInputMethod CheckInputMethod;
	DM_FindInputMethod FindInputMethod;
	DM_GetCursorPos GetCursorPos;
	DM_FindWindow FindWindow;
	DM_GetScreenDepth GetScreenDepth;
	DM_SetScreen SetScreen;
	DM_ExitOs ExitOs;
	DM_GetDir GetDir;
	DM_GetOsType GetOsType;
	DM_FindWindowEx FindWindowEx;
	DM_SetExportDict SetExportDict;
	DM_GetCursorShape GetCursorShape;
	DM_DownCpu DownCpu;
	DM_GetCursorSpot GetCursorSpot;
	DM_SendString2 SendString2;
	DM_FaqPost FaqPost;
	DM_FaqFetch FaqFetch;
	DM_FetchWord FetchWord;
	DM_CaptureJpg CaptureJpg;
	DM_FindStrWithFont FindStrWithFont;
	DM_FindStrWithFontE FindStrWithFontE;
	DM_FindStrWithFontEx FindStrWithFontEx;
	DM_GetDictInfo GetDictInfo;
	DM_SaveDict SaveDict;
	DM_GetWindowProcessId GetWindowProcessId;
	DM_GetWindowProcessPath GetWindowProcessPath;
	DM_LockInput LockInput;
	DM_GetPicSize GetPicSize;
	DM_GetID GetID;
	DM_CapturePng CapturePng;
	DM_CaptureGif CaptureGif;
	DM_ImageToBmp ImageToBmp;
	DM_FindStrFast FindStrFast;
	DM_FindStrFastEx FindStrFastEx;
	DM_FindStrFastE FindStrFastE;
	DM_EnableDisplayDebug EnableDisplayDebug;
	DM_CapturePre CapturePre;
	DM_RegEx RegEx;
	DM_GetMachineCode GetMachineCode;
	DM_SetClipboard SetClipboard;
	DM_GetClipboard GetClipboard;
	DM_GetNowDict GetNowDict;
	DM_Is64Bit Is64Bit;
	DM_GetColorNum GetColorNum;
	DM_EnumWindowByProcess EnumWindowByProcess;
	DM_GetDictCount GetDictCount;
	DM_GetLastError GetLastError;
	DM_GetNetTime GetNetTime;
	DM_EnableGetColorByCapture EnableGetColorByCapture;
	DM_CheckUAC CheckUAC;
	DM_SetUAC SetUAC;
	DM_DisableFontSmooth DisableFontSmooth;
	DM_CheckFontSmooth CheckFontSmooth;
	DM_SetDisplayAcceler SetDisplayAcceler;
	DM_FindWindowByProcess FindWindowByProcess;
	DM_FindWindowByProcessId FindWindowByProcessId;
	DM_ReadIni ReadIni;
	DM_WriteIni WriteIni;
	DM_RunApp RunApp;
	DM_delay delay;
	DM_FindWindowSuper FindWindowSuper;
	DM_ExcludePos ExcludePos;
	DM_FindNearestPos FindNearestPos;
	DM_SortPosDistance SortPosDistance;
	DM_FindPicMem FindPicMem;
	DM_FindPicMemEx FindPicMemEx;
	DM_FindPicMemE FindPicMemE;
	DM_AppendPicAddr AppendPicAddr;
	DM_WriteFile WriteFile;
	DM_Stop Stop;
	DM_SetDictMem SetDictMem;
	DM_GetNetTimeSafe GetNetTimeSafe;
	DM_ForceUnBindWindow ForceUnBindWindow;
	DM_ReadIniPwd ReadIniPwd;
	DM_WriteIniPwd WriteIniPwd;
	DM_DecodeFile DecodeFile;
	DM_KeyDownChar KeyDownChar;
	DM_KeyUpChar KeyUpChar;
	DM_KeyPressChar KeyPressChar;
	DM_KeyPressStr KeyPressStr;
	DM_EnableKeypadPatch EnableKeypadPatch;
	DM_EnableKeypadSync EnableKeypadSync;
	DM_EnableMouseSync EnableMouseSync;
	DM_DmGuard DmGuard;
	DM_FaqCaptureFromFile FaqCaptureFromFile;
	DM_FindIntEx FindIntEx;
	DM_FindFloatEx FindFloatEx;
	DM_FindDoubleEx FindDoubleEx;
	DM_FindStringEx FindStringEx;
	DM_FindDataEx FindDataEx;
	DM_EnableRealMouse EnableRealMouse;
	DM_EnableRealKeypad EnableRealKeypad;
	DM_SendStringIme SendStringIme;
	DM_FoobarDrawLine FoobarDrawLine;
	DM_FindStrEx FindStrEx;
	DM_IsBind IsBind;
	DM_SetDisplayDelay SetDisplayDelay;
	DM_GetDmCount GetDmCount;
	DM_DisableScreenSave DisableScreenSave;
	DM_DisablePowerSave DisablePowerSave;
	DM_SetMemoryHwndAsProcessId SetMemoryHwndAsProcessId;
	DM_FindShape FindShape;
	DM_FindShapeE FindShapeE;
	DM_FindShapeEx FindShapeEx;
	DM_FindStrS FindStrS;
	DM_FindStrExS FindStrExS;
	DM_FindStrFastS FindStrFastS;
	DM_FindStrFastExS FindStrFastExS;
	DM_FindPicS FindPicS;
	DM_FindPicExS FindPicExS;
	DM_ClearDict ClearDict;
	DM_GetMachineCodeNoMac GetMachineCodeNoMac;
	DM_GetClientRect GetClientRect;
	DM_EnableFakeActive EnableFakeActive;
	DM_GetScreenDataBmp GetScreenDataBmp;
	DM_EncodeFile EncodeFile;
	DM_GetCursorShapeEx GetCursorShapeEx;
	DM_FaqCancel FaqCancel;
	DM_IntToData IntToData;
	DM_FloatToData FloatToData;
	DM_DoubleToData DoubleToData;
	DM_StringToData StringToData;
	DM_SetMemoryFindResultToFile SetMemoryFindResultToFile;
	DM_EnableBind EnableBind;
	DM_SetSimMode SetSimMode;
	DM_LockMouseRect LockMouseRect;
	DM_SendPaste SendPaste;
	DM_IsDisplayDead IsDisplayDead;
	DM_GetKeyState GetKeyState;
	DM_CopyFile CopyFile;
	DM_IsFileExist IsFileExist;
	DM_DeleteFile DeleteFile;
	DM_MoveFile MoveFile;
	DM_CreateFolder CreateFolder;
	DM_DeleteFolder DeleteFolder;
	DM_GetFileLength GetFileLength;
	DM_ReadFile ReadFile;
	DM_WaitKey WaitKey;
	DM_DeleteIni DeleteIni;
	DM_DeleteIniPwd DeleteIniPwd;
	DM_EnableSpeedDx EnableSpeedDx;
	DM_EnableIme EnableIme;
	DM_SelectFile SelectFile;
	DM_SelectDirectory SelectDirectory;
	DM_LockDisplay LockDisplay;
	DM_FoobarSetSave FoobarSetSave;
	DM_EnumWindowSuper EnumWindowSuper;
	DM_DownloadFile DownloadFile;
	DM_EnableKeypadMsg EnableKeypadMsg;
	DM_EnableMouseMsg EnableMouseMsg;
	DM_RegNoMac RegNoMac;
	DM_RegExNoMac RegExNoMac;
	DM_SetEnumWindowDelay SetEnumWindowDelay;
	DM_FindMulColor FindMulColor;
	DM_FreeDM FreeDM;
	DM_Ocr Ocr;
	DM_GetDict GetDict;
	DM_GetResultCount GetResultCount;
	DM_FindStr FindStr;
	DM_CreateDM CreateDM;
	DM_SetPath SetPath;
	DM_BindWindow BindWindow;
	DM_KeyPress KeyPress;
	DM_Ver Ver;
	DM_Reg Reg;
	BOOL 是否成功;
};

