
// 这是对 32 位的 winmm.dll 的劫持源码  南小鱼 QQ128492656
#嵌入代码

#include <windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker,"/SUBSYSTEM:windows")
//#pragma comment(linker,"/Opt:nowin98")

#pragma comment(linker, "/EXPORT:Noname2=_AheadLib_Unnamed2,@2,NONAME")
#pragma comment(linker, "/EXPORT:mciExecute=_AheadLib_mciExecute,@3")
#pragma comment(linker, "/EXPORT:CloseDriver=_AheadLib_CloseDriver,@4")
#pragma comment(linker, "/EXPORT:DefDriverProc=_AheadLib_DefDriverProc,@5")
#pragma comment(linker, "/EXPORT:DriverCallback=_AheadLib_DriverCallback,@6")
#pragma comment(linker, "/EXPORT:DrvGetModuleHandle=_AheadLib_DrvGetModuleHandle,@7")
#pragma comment(linker, "/EXPORT:GetDriverModuleHandle=_AheadLib_GetDriverModuleHandle,@8")
#pragma comment(linker, "/EXPORT:NotifyCallbackData=_AheadLib_NotifyCallbackData,@9")
#pragma comment(linker, "/EXPORT:OpenDriver=_AheadLib_OpenDriver,@10")
#pragma comment(linker, "/EXPORT:PlaySound=_AheadLib_PlaySound,@11")
#pragma comment(linker, "/EXPORT:PlaySoundA=_AheadLib_PlaySoundA,@12")
#pragma comment(linker, "/EXPORT:PlaySoundW=_AheadLib_PlaySoundW,@13")
#pragma comment(linker, "/EXPORT:SendDriverMessage=_AheadLib_SendDriverMessage,@14")
#pragma comment(linker, "/EXPORT:WOW32DriverCallback=_AheadLib_WOW32DriverCallback,@15")
#pragma comment(linker, "/EXPORT:WOW32ResolveMultiMediaHandle=_AheadLib_WOW32ResolveMultiMediaHandle,@16")
#pragma comment(linker, "/EXPORT:WOWAppExit=_AheadLib_WOWAppExit,@17")
#pragma comment(linker, "/EXPORT:aux32Message=_AheadLib_aux32Message,@18")
#pragma comment(linker, "/EXPORT:auxGetDevCapsA=_AheadLib_auxGetDevCapsA,@19")
#pragma comment(linker, "/EXPORT:auxGetDevCapsW=_AheadLib_auxGetDevCapsW,@20")
#pragma comment(linker, "/EXPORT:auxGetNumDevs=_AheadLib_auxGetNumDevs,@21")
#pragma comment(linker, "/EXPORT:auxGetVolume=_AheadLib_auxGetVolume,@22")
#pragma comment(linker, "/EXPORT:auxOutMessage=_AheadLib_auxOutMessage,@23")
#pragma comment(linker, "/EXPORT:auxSetVolume=_AheadLib_auxSetVolume,@24")
#pragma comment(linker, "/EXPORT:joy32Message=_AheadLib_joy32Message,@25")
#pragma comment(linker, "/EXPORT:joyConfigChanged=_AheadLib_joyConfigChanged,@26")
#pragma comment(linker, "/EXPORT:joyGetDevCapsA=_AheadLib_joyGetDevCapsA,@27")
#pragma comment(linker, "/EXPORT:joyGetDevCapsW=_AheadLib_joyGetDevCapsW,@28")
#pragma comment(linker, "/EXPORT:joyGetNumDevs=_AheadLib_joyGetNumDevs,@29")
#pragma comment(linker, "/EXPORT:joyGetPos=_AheadLib_joyGetPos,@30")
#pragma comment(linker, "/EXPORT:joyGetPosEx=_AheadLib_joyGetPosEx,@31")
#pragma comment(linker, "/EXPORT:joyGetThreshold=_AheadLib_joyGetThreshold,@32")
#pragma comment(linker, "/EXPORT:joyReleaseCapture=_AheadLib_joyReleaseCapture,@33")
#pragma comment(linker, "/EXPORT:joySetCapture=_AheadLib_joySetCapture,@34")
#pragma comment(linker, "/EXPORT:joySetThreshold=_AheadLib_joySetThreshold,@35")
#pragma comment(linker, "/EXPORT:mci32Message=_AheadLib_mci32Message,@36")
#pragma comment(linker, "/EXPORT:mciDriverNotify=_AheadLib_mciDriverNotify,@37")
#pragma comment(linker, "/EXPORT:mciDriverYield=_AheadLib_mciDriverYield,@38")
#pragma comment(linker, "/EXPORT:mciFreeCommandResource=_AheadLib_mciFreeCommandResource,@39")
#pragma comment(linker, "/EXPORT:mciGetCreatorTask=_AheadLib_mciGetCreatorTask,@40")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDA=_AheadLib_mciGetDeviceIDA,@41")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDA=_AheadLib_mciGetDeviceIDFromElementIDA,@42")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDW=_AheadLib_mciGetDeviceIDFromElementIDW,@43")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDW=_AheadLib_mciGetDeviceIDW,@44")
#pragma comment(linker, "/EXPORT:mciGetDriverData=_AheadLib_mciGetDriverData,@45")
#pragma comment(linker, "/EXPORT:mciGetErrorStringA=_AheadLib_mciGetErrorStringA,@46")
#pragma comment(linker, "/EXPORT:mciGetErrorStringW=_AheadLib_mciGetErrorStringW,@47")
#pragma comment(linker, "/EXPORT:mciGetYieldProc=_AheadLib_mciGetYieldProc,@48")
#pragma comment(linker, "/EXPORT:mciLoadCommandResource=_AheadLib_mciLoadCommandResource,@49")
#pragma comment(linker, "/EXPORT:mciSendCommandA=_AheadLib_mciSendCommandA,@50")
#pragma comment(linker, "/EXPORT:mciSendCommandW=_AheadLib_mciSendCommandW,@51")
#pragma comment(linker, "/EXPORT:mciSendStringA=_AheadLib_mciSendStringA,@52")
#pragma comment(linker, "/EXPORT:mciSendStringW=_AheadLib_mciSendStringW,@53")
#pragma comment(linker, "/EXPORT:mciSetDriverData=_AheadLib_mciSetDriverData,@54")
#pragma comment(linker, "/EXPORT:mciSetYieldProc=_AheadLib_mciSetYieldProc,@55")
#pragma comment(linker, "/EXPORT:mid32Message=_AheadLib_mid32Message,@56")
#pragma comment(linker, "/EXPORT:midiConnect=_AheadLib_midiConnect,@57")
#pragma comment(linker, "/EXPORT:midiDisconnect=_AheadLib_midiDisconnect,@58")
#pragma comment(linker, "/EXPORT:midiInAddBuffer=_AheadLib_midiInAddBuffer,@59")
#pragma comment(linker, "/EXPORT:midiInClose=_AheadLib_midiInClose,@60")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsA=_AheadLib_midiInGetDevCapsA,@61")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsW=_AheadLib_midiInGetDevCapsW,@62")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextA=_AheadLib_midiInGetErrorTextA,@63")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextW=_AheadLib_midiInGetErrorTextW,@64")
#pragma comment(linker, "/EXPORT:midiInGetID=_AheadLib_midiInGetID,@65")
#pragma comment(linker, "/EXPORT:midiInGetNumDevs=_AheadLib_midiInGetNumDevs,@66")
#pragma comment(linker, "/EXPORT:midiInMessage=_AheadLib_midiInMessage,@67")
#pragma comment(linker, "/EXPORT:midiInOpen=_AheadLib_midiInOpen,@68")
#pragma comment(linker, "/EXPORT:midiInPrepareHeader=_AheadLib_midiInPrepareHeader,@69")
#pragma comment(linker, "/EXPORT:midiInReset=_AheadLib_midiInReset,@70")
#pragma comment(linker, "/EXPORT:midiInStart=_AheadLib_midiInStart,@71")
#pragma comment(linker, "/EXPORT:midiInStop=_AheadLib_midiInStop,@72")
#pragma comment(linker, "/EXPORT:midiInUnprepareHeader=_AheadLib_midiInUnprepareHeader,@73")
#pragma comment(linker, "/EXPORT:midiOutCacheDrumPatches=_AheadLib_midiOutCacheDrumPatches,@74")
#pragma comment(linker, "/EXPORT:midiOutCachePatches=_AheadLib_midiOutCachePatches,@75")
#pragma comment(linker, "/EXPORT:midiOutClose=_AheadLib_midiOutClose,@76")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsA=_AheadLib_midiOutGetDevCapsA,@77")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsW=_AheadLib_midiOutGetDevCapsW,@78")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextA=_AheadLib_midiOutGetErrorTextA,@79")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextW=_AheadLib_midiOutGetErrorTextW,@80")
#pragma comment(linker, "/EXPORT:midiOutGetID=_AheadLib_midiOutGetID,@81")
#pragma comment(linker, "/EXPORT:midiOutGetNumDevs=_AheadLib_midiOutGetNumDevs,@82")
#pragma comment(linker, "/EXPORT:midiOutGetVolume=_AheadLib_midiOutGetVolume,@83")
#pragma comment(linker, "/EXPORT:midiOutLongMsg=_AheadLib_midiOutLongMsg,@84")
#pragma comment(linker, "/EXPORT:midiOutMessage=_AheadLib_midiOutMessage,@85")
#pragma comment(linker, "/EXPORT:midiOutOpen=_AheadLib_midiOutOpen,@86")
#pragma comment(linker, "/EXPORT:midiOutPrepareHeader=_AheadLib_midiOutPrepareHeader,@87")
#pragma comment(linker, "/EXPORT:midiOutReset=_AheadLib_midiOutReset,@88")
#pragma comment(linker, "/EXPORT:midiOutSetVolume=_AheadLib_midiOutSetVolume,@89")
#pragma comment(linker, "/EXPORT:midiOutShortMsg=_AheadLib_midiOutShortMsg,@90")
#pragma comment(linker, "/EXPORT:midiOutUnprepareHeader=_AheadLib_midiOutUnprepareHeader,@91")
#pragma comment(linker, "/EXPORT:midiStreamClose=_AheadLib_midiStreamClose,@92")
#pragma comment(linker, "/EXPORT:midiStreamOpen=_AheadLib_midiStreamOpen,@93")
#pragma comment(linker, "/EXPORT:midiStreamOut=_AheadLib_midiStreamOut,@94")
#pragma comment(linker, "/EXPORT:midiStreamPause=_AheadLib_midiStreamPause,@95")
#pragma comment(linker, "/EXPORT:midiStreamPosition=_AheadLib_midiStreamPosition,@96")
#pragma comment(linker, "/EXPORT:midiStreamProperty=_AheadLib_midiStreamProperty,@97")
#pragma comment(linker, "/EXPORT:midiStreamRestart=_AheadLib_midiStreamRestart,@98")
#pragma comment(linker, "/EXPORT:midiStreamStop=_AheadLib_midiStreamStop,@99")
#pragma comment(linker, "/EXPORT:mixerClose=_AheadLib_mixerClose,@100")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsA=_AheadLib_mixerGetControlDetailsA,@101")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsW=_AheadLib_mixerGetControlDetailsW,@102")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsA=_AheadLib_mixerGetDevCapsA,@103")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsW=_AheadLib_mixerGetDevCapsW,@104")
#pragma comment(linker, "/EXPORT:mixerGetID=_AheadLib_mixerGetID,@105")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsA=_AheadLib_mixerGetLineControlsA,@106")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsW=_AheadLib_mixerGetLineControlsW,@107")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoA=_AheadLib_mixerGetLineInfoA,@108")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoW=_AheadLib_mixerGetLineInfoW,@109")
#pragma comment(linker, "/EXPORT:mixerGetNumDevs=_AheadLib_mixerGetNumDevs,@110")
#pragma comment(linker, "/EXPORT:mixerMessage=_AheadLib_mixerMessage,@111")
#pragma comment(linker, "/EXPORT:mixerOpen=_AheadLib_mixerOpen,@112")
#pragma comment(linker, "/EXPORT:mixerSetControlDetails=_AheadLib_mixerSetControlDetails,@113")
#pragma comment(linker, "/EXPORT:mmDrvInstall=_AheadLib_mmDrvInstall,@114")
#pragma comment(linker, "/EXPORT:mmGetCurrentTask=_AheadLib_mmGetCurrentTask,@115")
#pragma comment(linker, "/EXPORT:mmTaskBlock=_AheadLib_mmTaskBlock,@116")
#pragma comment(linker, "/EXPORT:mmTaskCreate=_AheadLib_mmTaskCreate,@117")
#pragma comment(linker, "/EXPORT:mmTaskSignal=_AheadLib_mmTaskSignal,@118")
#pragma comment(linker, "/EXPORT:mmTaskYield=_AheadLib_mmTaskYield,@119")
#pragma comment(linker, "/EXPORT:mmioAdvance=_AheadLib_mmioAdvance,@120")
#pragma comment(linker, "/EXPORT:mmioAscend=_AheadLib_mmioAscend,@121")
#pragma comment(linker, "/EXPORT:mmioClose=_AheadLib_mmioClose,@122")
#pragma comment(linker, "/EXPORT:mmioCreateChunk=_AheadLib_mmioCreateChunk,@123")
#pragma comment(linker, "/EXPORT:mmioDescend=_AheadLib_mmioDescend,@124")
#pragma comment(linker, "/EXPORT:mmioFlush=_AheadLib_mmioFlush,@125")
#pragma comment(linker, "/EXPORT:mmioGetInfo=_AheadLib_mmioGetInfo,@126")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcA=_AheadLib_mmioInstallIOProcA,@127")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcW=_AheadLib_mmioInstallIOProcW,@128")
#pragma comment(linker, "/EXPORT:mmioOpenA=_AheadLib_mmioOpenA,@129")
#pragma comment(linker, "/EXPORT:mmioOpenW=_AheadLib_mmioOpenW,@130")
#pragma comment(linker, "/EXPORT:mmioRead=_AheadLib_mmioRead,@131")
#pragma comment(linker, "/EXPORT:mmioRenameA=_AheadLib_mmioRenameA,@132")
#pragma comment(linker, "/EXPORT:mmioRenameW=_AheadLib_mmioRenameW,@133")
#pragma comment(linker, "/EXPORT:mmioSeek=_AheadLib_mmioSeek,@134")
#pragma comment(linker, "/EXPORT:mmioSendMessage=_AheadLib_mmioSendMessage,@135")
#pragma comment(linker, "/EXPORT:mmioSetBuffer=_AheadLib_mmioSetBuffer,@136")
#pragma comment(linker, "/EXPORT:mmioSetInfo=_AheadLib_mmioSetInfo,@137")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCA=_AheadLib_mmioStringToFOURCCA,@138")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCW=_AheadLib_mmioStringToFOURCCW,@139")
#pragma comment(linker, "/EXPORT:mmioWrite=_AheadLib_mmioWrite,@140")
#pragma comment(linker, "/EXPORT:mmsystemGetVersion=_AheadLib_mmsystemGetVersion,@141")
#pragma comment(linker, "/EXPORT:mod32Message=_AheadLib_mod32Message,@142")
#pragma comment(linker, "/EXPORT:mxd32Message=_AheadLib_mxd32Message,@143")
#pragma comment(linker, "/EXPORT:sndPlaySoundA=_AheadLib_sndPlaySoundA,@144")
#pragma comment(linker, "/EXPORT:sndPlaySoundW=_AheadLib_sndPlaySoundW,@145")
#pragma comment(linker, "/EXPORT:tid32Message=_AheadLib_tid32Message,@146")
#pragma comment(linker, "/EXPORT:timeBeginPeriod=_AheadLib_timeBeginPeriod,@147")
#pragma comment(linker, "/EXPORT:timeEndPeriod=_AheadLib_timeEndPeriod,@148")
#pragma comment(linker, "/EXPORT:timeGetDevCaps=_AheadLib_timeGetDevCaps,@149")
#pragma comment(linker, "/EXPORT:timeGetSystemTime=_AheadLib_timeGetSystemTime,@150")
#pragma comment(linker, "/EXPORT:timeGetTime=_AheadLib_timeGetTime,@151")
#pragma comment(linker, "/EXPORT:timeKillEvent=_AheadLib_timeKillEvent,@152")
#pragma comment(linker, "/EXPORT:timeSetEvent=_AheadLib_timeSetEvent,@153")
#pragma comment(linker, "/EXPORT:waveInAddBuffer=_AheadLib_waveInAddBuffer,@154")
#pragma comment(linker, "/EXPORT:waveInClose=_AheadLib_waveInClose,@155")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsA=_AheadLib_waveInGetDevCapsA,@156")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsW=_AheadLib_waveInGetDevCapsW,@157")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextA=_AheadLib_waveInGetErrorTextA,@158")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextW=_AheadLib_waveInGetErrorTextW,@159")
#pragma comment(linker, "/EXPORT:waveInGetID=_AheadLib_waveInGetID,@160")
#pragma comment(linker, "/EXPORT:waveInGetNumDevs=_AheadLib_waveInGetNumDevs,@161")
#pragma comment(linker, "/EXPORT:waveInGetPosition=_AheadLib_waveInGetPosition,@162")
#pragma comment(linker, "/EXPORT:waveInMessage=_AheadLib_waveInMessage,@163")
#pragma comment(linker, "/EXPORT:waveInOpen=_AheadLib_waveInOpen,@164")
#pragma comment(linker, "/EXPORT:waveInPrepareHeader=_AheadLib_waveInPrepareHeader,@165")
#pragma comment(linker, "/EXPORT:waveInReset=_AheadLib_waveInReset,@166")
#pragma comment(linker, "/EXPORT:waveInStart=_AheadLib_waveInStart,@167")
#pragma comment(linker, "/EXPORT:waveInStop=_AheadLib_waveInStop,@168")
#pragma comment(linker, "/EXPORT:waveInUnprepareHeader=_AheadLib_waveInUnprepareHeader,@169")
#pragma comment(linker, "/EXPORT:waveOutBreakLoop=_AheadLib_waveOutBreakLoop,@170")
#pragma comment(linker, "/EXPORT:waveOutClose=_AheadLib_waveOutClose,@171")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsA=_AheadLib_waveOutGetDevCapsA,@172")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsW=_AheadLib_waveOutGetDevCapsW,@173")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextA=_AheadLib_waveOutGetErrorTextA,@174")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextW=_AheadLib_waveOutGetErrorTextW,@175")
#pragma comment(linker, "/EXPORT:waveOutGetID=_AheadLib_waveOutGetID,@176")
#pragma comment(linker, "/EXPORT:waveOutGetNumDevs=_AheadLib_waveOutGetNumDevs,@177")
#pragma comment(linker, "/EXPORT:waveOutGetPitch=_AheadLib_waveOutGetPitch,@178")
#pragma comment(linker, "/EXPORT:waveOutGetPlaybackRate=_AheadLib_waveOutGetPlaybackRate,@179")
#pragma comment(linker, "/EXPORT:waveOutGetPosition=_AheadLib_waveOutGetPosition,@180")
#pragma comment(linker, "/EXPORT:waveOutGetVolume=_AheadLib_waveOutGetVolume,@181")
#pragma comment(linker, "/EXPORT:waveOutMessage=_AheadLib_waveOutMessage,@182")
#pragma comment(linker, "/EXPORT:waveOutOpen=_AheadLib_waveOutOpen,@183")
#pragma comment(linker, "/EXPORT:waveOutPause=_AheadLib_waveOutPause,@184")
#pragma comment(linker, "/EXPORT:waveOutPrepareHeader=_AheadLib_waveOutPrepareHeader,@185")
#pragma comment(linker, "/EXPORT:waveOutReset=_AheadLib_waveOutReset,@186")
#pragma comment(linker, "/EXPORT:waveOutRestart=_AheadLib_waveOutRestart,@187")
#pragma comment(linker, "/EXPORT:waveOutSetPitch=_AheadLib_waveOutSetPitch,@188")
#pragma comment(linker, "/EXPORT:waveOutSetPlaybackRate=_AheadLib_waveOutSetPlaybackRate,@189")
#pragma comment(linker, "/EXPORT:waveOutSetVolume=_AheadLib_waveOutSetVolume,@190")
#pragma comment(linker, "/EXPORT:waveOutUnprepareHeader=_AheadLib_waveOutUnprepareHeader,@191")
#pragma comment(linker, "/EXPORT:waveOutWrite=_AheadLib_waveOutWrite,@192")
#pragma comment(linker, "/EXPORT:wid32Message=_AheadLib_wid32Message,@193")
#pragma comment(linker, "/EXPORT:wod32Message=_AheadLib_wod32Message,@194")
PVOID pfnAheadLib_Unnamed2;
PVOID pfnAheadLib_mciExecute;
PVOID pfnAheadLib_CloseDriver;
PVOID pfnAheadLib_DefDriverProc;
PVOID pfnAheadLib_DriverCallback;
PVOID pfnAheadLib_DrvGetModuleHandle;
PVOID pfnAheadLib_GetDriverModuleHandle;
PVOID pfnAheadLib_NotifyCallbackData;
PVOID pfnAheadLib_OpenDriver;
PVOID pfnAheadLib_PlaySound;
PVOID pfnAheadLib_PlaySoundA;
PVOID pfnAheadLib_PlaySoundW;
PVOID pfnAheadLib_SendDriverMessage;
PVOID pfnAheadLib_WOW32DriverCallback;
PVOID pfnAheadLib_WOW32ResolveMultiMediaHandle;
PVOID pfnAheadLib_WOWAppExit;
PVOID pfnAheadLib_aux32Message;
PVOID pfnAheadLib_auxGetDevCapsA;
PVOID pfnAheadLib_auxGetDevCapsW;
PVOID pfnAheadLib_auxGetNumDevs;
PVOID pfnAheadLib_auxGetVolume;
PVOID pfnAheadLib_auxOutMessage;
PVOID pfnAheadLib_auxSetVolume;
PVOID pfnAheadLib_joy32Message;
PVOID pfnAheadLib_joyConfigChanged;
PVOID pfnAheadLib_joyGetDevCapsA;
PVOID pfnAheadLib_joyGetDevCapsW;
PVOID pfnAheadLib_joyGetNumDevs;
PVOID pfnAheadLib_joyGetPos;
PVOID pfnAheadLib_joyGetPosEx;
PVOID pfnAheadLib_joyGetThreshold;
PVOID pfnAheadLib_joyReleaseCapture;
PVOID pfnAheadLib_joySetCapture;
PVOID pfnAheadLib_joySetThreshold;
PVOID pfnAheadLib_mci32Message;
PVOID pfnAheadLib_mciDriverNotify;
PVOID pfnAheadLib_mciDriverYield;
PVOID pfnAheadLib_mciFreeCommandResource;
PVOID pfnAheadLib_mciGetCreatorTask;
PVOID pfnAheadLib_mciGetDeviceIDA;
PVOID pfnAheadLib_mciGetDeviceIDFromElementIDA;
PVOID pfnAheadLib_mciGetDeviceIDFromElementIDW;
PVOID pfnAheadLib_mciGetDeviceIDW;
PVOID pfnAheadLib_mciGetDriverData;
PVOID pfnAheadLib_mciGetErrorStringA;
PVOID pfnAheadLib_mciGetErrorStringW;
PVOID pfnAheadLib_mciGetYieldProc;
PVOID pfnAheadLib_mciLoadCommandResource;
PVOID pfnAheadLib_mciSendCommandA;
PVOID pfnAheadLib_mciSendCommandW;
PVOID pfnAheadLib_mciSendStringA;
PVOID pfnAheadLib_mciSendStringW;
PVOID pfnAheadLib_mciSetDriverData;
PVOID pfnAheadLib_mciSetYieldProc;
PVOID pfnAheadLib_mid32Message;
PVOID pfnAheadLib_midiConnect;
PVOID pfnAheadLib_midiDisconnect;
PVOID pfnAheadLib_midiInAddBuffer;
PVOID pfnAheadLib_midiInClose;
PVOID pfnAheadLib_midiInGetDevCapsA;
PVOID pfnAheadLib_midiInGetDevCapsW;
PVOID pfnAheadLib_midiInGetErrorTextA;
PVOID pfnAheadLib_midiInGetErrorTextW;
PVOID pfnAheadLib_midiInGetID;
PVOID pfnAheadLib_midiInGetNumDevs;
PVOID pfnAheadLib_midiInMessage;
PVOID pfnAheadLib_midiInOpen;
PVOID pfnAheadLib_midiInPrepareHeader;
PVOID pfnAheadLib_midiInReset;
PVOID pfnAheadLib_midiInStart;
PVOID pfnAheadLib_midiInStop;
PVOID pfnAheadLib_midiInUnprepareHeader;
PVOID pfnAheadLib_midiOutCacheDrumPatches;
PVOID pfnAheadLib_midiOutCachePatches;
PVOID pfnAheadLib_midiOutClose;
PVOID pfnAheadLib_midiOutGetDevCapsA;
PVOID pfnAheadLib_midiOutGetDevCapsW;
PVOID pfnAheadLib_midiOutGetErrorTextA;
PVOID pfnAheadLib_midiOutGetErrorTextW;
PVOID pfnAheadLib_midiOutGetID;
PVOID pfnAheadLib_midiOutGetNumDevs;
PVOID pfnAheadLib_midiOutGetVolume;
PVOID pfnAheadLib_midiOutLongMsg;
PVOID pfnAheadLib_midiOutMessage;
PVOID pfnAheadLib_midiOutOpen;
PVOID pfnAheadLib_midiOutPrepareHeader;
PVOID pfnAheadLib_midiOutReset;
PVOID pfnAheadLib_midiOutSetVolume;
PVOID pfnAheadLib_midiOutShortMsg;
PVOID pfnAheadLib_midiOutUnprepareHeader;
PVOID pfnAheadLib_midiStreamClose;
PVOID pfnAheadLib_midiStreamOpen;
PVOID pfnAheadLib_midiStreamOut;
PVOID pfnAheadLib_midiStreamPause;
PVOID pfnAheadLib_midiStreamPosition;
PVOID pfnAheadLib_midiStreamProperty;
PVOID pfnAheadLib_midiStreamRestart;
PVOID pfnAheadLib_midiStreamStop;
PVOID pfnAheadLib_mixerClose;
PVOID pfnAheadLib_mixerGetControlDetailsA;
PVOID pfnAheadLib_mixerGetControlDetailsW;
PVOID pfnAheadLib_mixerGetDevCapsA;
PVOID pfnAheadLib_mixerGetDevCapsW;
PVOID pfnAheadLib_mixerGetID;
PVOID pfnAheadLib_mixerGetLineControlsA;
PVOID pfnAheadLib_mixerGetLineControlsW;
PVOID pfnAheadLib_mixerGetLineInfoA;
PVOID pfnAheadLib_mixerGetLineInfoW;
PVOID pfnAheadLib_mixerGetNumDevs;
PVOID pfnAheadLib_mixerMessage;
PVOID pfnAheadLib_mixerOpen;
PVOID pfnAheadLib_mixerSetControlDetails;
PVOID pfnAheadLib_mmDrvInstall;
PVOID pfnAheadLib_mmGetCurrentTask;
PVOID pfnAheadLib_mmTaskBlock;
PVOID pfnAheadLib_mmTaskCreate;
PVOID pfnAheadLib_mmTaskSignal;
PVOID pfnAheadLib_mmTaskYield;
PVOID pfnAheadLib_mmioAdvance;
PVOID pfnAheadLib_mmioAscend;
PVOID pfnAheadLib_mmioClose;
PVOID pfnAheadLib_mmioCreateChunk;
PVOID pfnAheadLib_mmioDescend;
PVOID pfnAheadLib_mmioFlush;
PVOID pfnAheadLib_mmioGetInfo;
PVOID pfnAheadLib_mmioInstallIOProcA;
PVOID pfnAheadLib_mmioInstallIOProcW;
PVOID pfnAheadLib_mmioOpenA;
PVOID pfnAheadLib_mmioOpenW;
PVOID pfnAheadLib_mmioRead;
PVOID pfnAheadLib_mmioRenameA;
PVOID pfnAheadLib_mmioRenameW;
PVOID pfnAheadLib_mmioSeek;
PVOID pfnAheadLib_mmioSendMessage;
PVOID pfnAheadLib_mmioSetBuffer;
PVOID pfnAheadLib_mmioSetInfo;
PVOID pfnAheadLib_mmioStringToFOURCCA;
PVOID pfnAheadLib_mmioStringToFOURCCW;
PVOID pfnAheadLib_mmioWrite;
PVOID pfnAheadLib_mmsystemGetVersion;
PVOID pfnAheadLib_mod32Message;
PVOID pfnAheadLib_mxd32Message;
PVOID pfnAheadLib_sndPlaySoundA;
PVOID pfnAheadLib_sndPlaySoundW;
PVOID pfnAheadLib_tid32Message;
PVOID pfnAheadLib_timeBeginPeriod;
PVOID pfnAheadLib_timeEndPeriod;
PVOID pfnAheadLib_timeGetDevCaps;
PVOID pfnAheadLib_timeGetSystemTime;
PVOID pfnAheadLib_timeGetTime;
PVOID pfnAheadLib_timeKillEvent;
PVOID pfnAheadLib_timeSetEvent;
PVOID pfnAheadLib_waveInAddBuffer;
PVOID pfnAheadLib_waveInClose;
PVOID pfnAheadLib_waveInGetDevCapsA;
PVOID pfnAheadLib_waveInGetDevCapsW;
PVOID pfnAheadLib_waveInGetErrorTextA;
PVOID pfnAheadLib_waveInGetErrorTextW;
PVOID pfnAheadLib_waveInGetID;
PVOID pfnAheadLib_waveInGetNumDevs;
PVOID pfnAheadLib_waveInGetPosition;
PVOID pfnAheadLib_waveInMessage;
PVOID pfnAheadLib_waveInOpen;
PVOID pfnAheadLib_waveInPrepareHeader;
PVOID pfnAheadLib_waveInReset;
PVOID pfnAheadLib_waveInStart;
PVOID pfnAheadLib_waveInStop;
PVOID pfnAheadLib_waveInUnprepareHeader;
PVOID pfnAheadLib_waveOutBreakLoop;
PVOID pfnAheadLib_waveOutClose;
PVOID pfnAheadLib_waveOutGetDevCapsA;
PVOID pfnAheadLib_waveOutGetDevCapsW;
PVOID pfnAheadLib_waveOutGetErrorTextA;
PVOID pfnAheadLib_waveOutGetErrorTextW;
PVOID pfnAheadLib_waveOutGetID;
PVOID pfnAheadLib_waveOutGetNumDevs;
PVOID pfnAheadLib_waveOutGetPitch;
PVOID pfnAheadLib_waveOutGetPlaybackRate;
PVOID pfnAheadLib_waveOutGetPosition;
PVOID pfnAheadLib_waveOutGetVolume;
PVOID pfnAheadLib_waveOutMessage;
PVOID pfnAheadLib_waveOutOpen;
PVOID pfnAheadLib_waveOutPause;
PVOID pfnAheadLib_waveOutPrepareHeader;
PVOID pfnAheadLib_waveOutReset;
PVOID pfnAheadLib_waveOutRestart;
PVOID pfnAheadLib_waveOutSetPitch;
PVOID pfnAheadLib_waveOutSetPlaybackRate;
PVOID pfnAheadLib_waveOutSetVolume;
PVOID pfnAheadLib_waveOutUnprepareHeader;
PVOID pfnAheadLib_waveOutWrite;
PVOID pfnAheadLib_wid32Message;
PVOID pfnAheadLib_wod32Message;




static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];
	lstrcat(tzPath,TEXT(".\\winmm_ORG.dll")); // 先判断是否存在"dll名称+_ORG.dll"
	if (-1 == GetFileAttributes(tzPath))
	{
	GetSystemDirectory(tzPath, MAX_PATH); // 这里是否从系统目录加载或者当前目录，自行修改
	lstrcat(tzPath, TEXT("\\winmm.dll"));
	}
	g_OldModule = LoadLibrary(tzPath);
	if (g_OldModule == NULL)
	{
		wsprintf(tzTemp, TEXT("无法找到模块 %s,程序无法正常运行"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
	}

	return (g_OldModule != NULL);	
}

// 释放原始模块
__inline VOID WINAPI Free()
{
	if (g_OldModule)
	{
		FreeLibrary(g_OldModule);
	}
}
// 获取原始函数地址
FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress;
	CHAR szProcName[128];
	TCHAR tzTemp[MAX_PATH];

	fpAddress = GetProcAddress(g_OldModule, pszProcName);
	if (fpAddress == NULL)
	{
		if (HIWORD(pszProcName) == 0)
		{
			wsprintfA(szProcName, "%d", pszProcName);
			pszProcName = szProcName;
		}

		wsprintf(tzTemp, TEXT("无法找到函数 %S,程序无法正常运行"), pszProcName);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		ExitProcess(-2);
	}
	return fpAddress;
}

// 初始化获取原函数地址
BOOL WINAPI Init()
{
	if(NULL == (pfnAheadLib_Unnamed2 = GetAddress(MAKEINTRESOURCEA(2))))
		return FALSE;
	if(NULL == (pfnAheadLib_mciExecute = GetAddress("mciExecute")))
		return FALSE;
	if(NULL == (pfnAheadLib_CloseDriver = GetAddress("CloseDriver")))
		return FALSE;
	if(NULL == (pfnAheadLib_DefDriverProc = GetAddress("DefDriverProc")))
		return FALSE;
	if(NULL == (pfnAheadLib_DriverCallback = GetAddress("DriverCallback")))
		return FALSE;
	if(NULL == (pfnAheadLib_DrvGetModuleHandle = GetAddress("DrvGetModuleHandle")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetDriverModuleHandle = GetAddress("GetDriverModuleHandle")))
		return FALSE;
	if(NULL == (pfnAheadLib_NotifyCallbackData = GetAddress("NotifyCallbackData")))
		return FALSE;
	if(NULL == (pfnAheadLib_OpenDriver = GetAddress("OpenDriver")))
		return FALSE;
	if(NULL == (pfnAheadLib_PlaySound = GetAddress("PlaySound")))
		return FALSE;
	if(NULL == (pfnAheadLib_PlaySoundA = GetAddress("PlaySoundA")))
		return FALSE;
	if(NULL == (pfnAheadLib_PlaySoundW = GetAddress("PlaySoundW")))
		return FALSE;
	if(NULL == (pfnAheadLib_SendDriverMessage = GetAddress("SendDriverMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_WOW32DriverCallback = GetAddress("WOW32DriverCallback")))
		return FALSE;
	if(NULL == (pfnAheadLib_WOW32ResolveMultiMediaHandle = GetAddress("WOW32ResolveMultiMediaHandle")))
		return FALSE;
	if(NULL == (pfnAheadLib_WOWAppExit = GetAddress("WOWAppExit")))
		return FALSE;
	if(NULL == (pfnAheadLib_aux32Message = GetAddress("aux32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxGetDevCapsA = GetAddress("auxGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxGetDevCapsW = GetAddress("auxGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxGetNumDevs = GetAddress("auxGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxGetVolume = GetAddress("auxGetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxOutMessage = GetAddress("auxOutMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_auxSetVolume = GetAddress("auxSetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_joy32Message = GetAddress("joy32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyConfigChanged = GetAddress("joyConfigChanged")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetDevCapsA = GetAddress("joyGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetDevCapsW = GetAddress("joyGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetNumDevs = GetAddress("joyGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetPos = GetAddress("joyGetPos")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetPosEx = GetAddress("joyGetPosEx")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyGetThreshold = GetAddress("joyGetThreshold")))
		return FALSE;
	if(NULL == (pfnAheadLib_joyReleaseCapture = GetAddress("joyReleaseCapture")))
		return FALSE;
	if(NULL == (pfnAheadLib_joySetCapture = GetAddress("joySetCapture")))
		return FALSE;
	if(NULL == (pfnAheadLib_joySetThreshold = GetAddress("joySetThreshold")))
		return FALSE;
	if(NULL == (pfnAheadLib_mci32Message = GetAddress("mci32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciDriverNotify = GetAddress("mciDriverNotify")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciDriverYield = GetAddress("mciDriverYield")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciFreeCommandResource = GetAddress("mciFreeCommandResource")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetCreatorTask = GetAddress("mciGetCreatorTask")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetDeviceIDA = GetAddress("mciGetDeviceIDA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetDeviceIDFromElementIDA = GetAddress("mciGetDeviceIDFromElementIDA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetDeviceIDFromElementIDW = GetAddress("mciGetDeviceIDFromElementIDW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetDeviceIDW = GetAddress("mciGetDeviceIDW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetDriverData = GetAddress("mciGetDriverData")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetErrorStringA = GetAddress("mciGetErrorStringA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetErrorStringW = GetAddress("mciGetErrorStringW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciGetYieldProc = GetAddress("mciGetYieldProc")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciLoadCommandResource = GetAddress("mciLoadCommandResource")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSendCommandA = GetAddress("mciSendCommandA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSendCommandW = GetAddress("mciSendCommandW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSendStringA = GetAddress("mciSendStringA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSendStringW = GetAddress("mciSendStringW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSetDriverData = GetAddress("mciSetDriverData")))
		return FALSE;
	if(NULL == (pfnAheadLib_mciSetYieldProc = GetAddress("mciSetYieldProc")))
		return FALSE;
	if(NULL == (pfnAheadLib_mid32Message = GetAddress("mid32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiConnect = GetAddress("midiConnect")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiDisconnect = GetAddress("midiDisconnect")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInAddBuffer = GetAddress("midiInAddBuffer")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInClose = GetAddress("midiInClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetDevCapsA = GetAddress("midiInGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetDevCapsW = GetAddress("midiInGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetErrorTextA = GetAddress("midiInGetErrorTextA")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetErrorTextW = GetAddress("midiInGetErrorTextW")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetID = GetAddress("midiInGetID")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInGetNumDevs = GetAddress("midiInGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInMessage = GetAddress("midiInMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInOpen = GetAddress("midiInOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInPrepareHeader = GetAddress("midiInPrepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInReset = GetAddress("midiInReset")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInStart = GetAddress("midiInStart")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInStop = GetAddress("midiInStop")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiInUnprepareHeader = GetAddress("midiInUnprepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutCacheDrumPatches = GetAddress("midiOutCacheDrumPatches")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutCachePatches = GetAddress("midiOutCachePatches")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutClose = GetAddress("midiOutClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetDevCapsA = GetAddress("midiOutGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetDevCapsW = GetAddress("midiOutGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetErrorTextA = GetAddress("midiOutGetErrorTextA")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetErrorTextW = GetAddress("midiOutGetErrorTextW")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetID = GetAddress("midiOutGetID")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetNumDevs = GetAddress("midiOutGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutGetVolume = GetAddress("midiOutGetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutLongMsg = GetAddress("midiOutLongMsg")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutMessage = GetAddress("midiOutMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutOpen = GetAddress("midiOutOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutPrepareHeader = GetAddress("midiOutPrepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutReset = GetAddress("midiOutReset")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutSetVolume = GetAddress("midiOutSetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutShortMsg = GetAddress("midiOutShortMsg")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiOutUnprepareHeader = GetAddress("midiOutUnprepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamClose = GetAddress("midiStreamClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamOpen = GetAddress("midiStreamOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamOut = GetAddress("midiStreamOut")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamPause = GetAddress("midiStreamPause")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamPosition = GetAddress("midiStreamPosition")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamProperty = GetAddress("midiStreamProperty")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamRestart = GetAddress("midiStreamRestart")))
		return FALSE;
	if(NULL == (pfnAheadLib_midiStreamStop = GetAddress("midiStreamStop")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerClose = GetAddress("mixerClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetControlDetailsA = GetAddress("mixerGetControlDetailsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetControlDetailsW = GetAddress("mixerGetControlDetailsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetDevCapsA = GetAddress("mixerGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetDevCapsW = GetAddress("mixerGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetID = GetAddress("mixerGetID")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetLineControlsA = GetAddress("mixerGetLineControlsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetLineControlsW = GetAddress("mixerGetLineControlsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetLineInfoA = GetAddress("mixerGetLineInfoA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetLineInfoW = GetAddress("mixerGetLineInfoW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerGetNumDevs = GetAddress("mixerGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerMessage = GetAddress("mixerMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerOpen = GetAddress("mixerOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_mixerSetControlDetails = GetAddress("mixerSetControlDetails")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmDrvInstall = GetAddress("mmDrvInstall")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmGetCurrentTask = GetAddress("mmGetCurrentTask")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmTaskBlock = GetAddress("mmTaskBlock")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmTaskCreate = GetAddress("mmTaskCreate")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmTaskSignal = GetAddress("mmTaskSignal")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmTaskYield = GetAddress("mmTaskYield")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioAdvance = GetAddress("mmioAdvance")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioAscend = GetAddress("mmioAscend")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioClose = GetAddress("mmioClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioCreateChunk = GetAddress("mmioCreateChunk")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioDescend = GetAddress("mmioDescend")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioFlush = GetAddress("mmioFlush")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioGetInfo = GetAddress("mmioGetInfo")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioInstallIOProcA = GetAddress("mmioInstallIOProcA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioInstallIOProcW = GetAddress("mmioInstallIOProcW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioOpenA = GetAddress("mmioOpenA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioOpenW = GetAddress("mmioOpenW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioRead = GetAddress("mmioRead")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioRenameA = GetAddress("mmioRenameA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioRenameW = GetAddress("mmioRenameW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioSeek = GetAddress("mmioSeek")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioSendMessage = GetAddress("mmioSendMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioSetBuffer = GetAddress("mmioSetBuffer")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioSetInfo = GetAddress("mmioSetInfo")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioStringToFOURCCA = GetAddress("mmioStringToFOURCCA")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioStringToFOURCCW = GetAddress("mmioStringToFOURCCW")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmioWrite = GetAddress("mmioWrite")))
		return FALSE;
	if(NULL == (pfnAheadLib_mmsystemGetVersion = GetAddress("mmsystemGetVersion")))
		return FALSE;
	if(NULL == (pfnAheadLib_mod32Message = GetAddress("mod32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_mxd32Message = GetAddress("mxd32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_sndPlaySoundA = GetAddress("sndPlaySoundA")))
		return FALSE;
	if(NULL == (pfnAheadLib_sndPlaySoundW = GetAddress("sndPlaySoundW")))
		return FALSE;
	if(NULL == (pfnAheadLib_tid32Message = GetAddress("tid32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeBeginPeriod = GetAddress("timeBeginPeriod")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeEndPeriod = GetAddress("timeEndPeriod")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeGetDevCaps = GetAddress("timeGetDevCaps")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeGetSystemTime = GetAddress("timeGetSystemTime")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeGetTime = GetAddress("timeGetTime")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeKillEvent = GetAddress("timeKillEvent")))
		return FALSE;
	if(NULL == (pfnAheadLib_timeSetEvent = GetAddress("timeSetEvent")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInAddBuffer = GetAddress("waveInAddBuffer")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInClose = GetAddress("waveInClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetDevCapsA = GetAddress("waveInGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetDevCapsW = GetAddress("waveInGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetErrorTextA = GetAddress("waveInGetErrorTextA")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetErrorTextW = GetAddress("waveInGetErrorTextW")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetID = GetAddress("waveInGetID")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetNumDevs = GetAddress("waveInGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInGetPosition = GetAddress("waveInGetPosition")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInMessage = GetAddress("waveInMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInOpen = GetAddress("waveInOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInPrepareHeader = GetAddress("waveInPrepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInReset = GetAddress("waveInReset")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInStart = GetAddress("waveInStart")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInStop = GetAddress("waveInStop")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveInUnprepareHeader = GetAddress("waveInUnprepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutBreakLoop = GetAddress("waveOutBreakLoop")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutClose = GetAddress("waveOutClose")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetDevCapsA = GetAddress("waveOutGetDevCapsA")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetDevCapsW = GetAddress("waveOutGetDevCapsW")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetErrorTextA = GetAddress("waveOutGetErrorTextA")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetErrorTextW = GetAddress("waveOutGetErrorTextW")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetID = GetAddress("waveOutGetID")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetNumDevs = GetAddress("waveOutGetNumDevs")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetPitch = GetAddress("waveOutGetPitch")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetPlaybackRate = GetAddress("waveOutGetPlaybackRate")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetPosition = GetAddress("waveOutGetPosition")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutGetVolume = GetAddress("waveOutGetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutMessage = GetAddress("waveOutMessage")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutOpen = GetAddress("waveOutOpen")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutPause = GetAddress("waveOutPause")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutPrepareHeader = GetAddress("waveOutPrepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutReset = GetAddress("waveOutReset")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutRestart = GetAddress("waveOutRestart")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutSetPitch = GetAddress("waveOutSetPitch")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutSetPlaybackRate = GetAddress("waveOutSetPlaybackRate")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutSetVolume = GetAddress("waveOutSetVolume")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutUnprepareHeader = GetAddress("waveOutUnprepareHeader")))
		return FALSE;
	if(NULL == (pfnAheadLib_waveOutWrite = GetAddress("waveOutWrite")))
		return FALSE;
	if(NULL == (pfnAheadLib_wid32Message = GetAddress("wid32Message")))
		return FALSE;
	if(NULL == (pfnAheadLib_wod32Message = GetAddress("wod32Message")))
		return FALSE;
	return TRUE;
}




 // 导出函数
EXTERN_C __declspec(naked) void __cdecl AheadLib_Unnamed2(void)
{
	__asm jmp pfnAheadLib_Unnamed2;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciExecute(void)
{
	__asm jmp pfnAheadLib_mciExecute;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_CloseDriver(void)
{
	__asm jmp pfnAheadLib_CloseDriver;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_DefDriverProc(void)
{
	__asm jmp pfnAheadLib_DefDriverProc;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_DriverCallback(void)
{
	__asm jmp pfnAheadLib_DriverCallback;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_DrvGetModuleHandle(void)
{
	__asm jmp pfnAheadLib_DrvGetModuleHandle;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetDriverModuleHandle(void)
{
	__asm jmp pfnAheadLib_GetDriverModuleHandle;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_NotifyCallbackData(void)
{
	__asm jmp pfnAheadLib_NotifyCallbackData;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_OpenDriver(void)
{
	__asm jmp pfnAheadLib_OpenDriver;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_PlaySound(void)
{
	__asm jmp pfnAheadLib_PlaySound;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_PlaySoundA(void)
{
	__asm jmp pfnAheadLib_PlaySoundA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_PlaySoundW(void)
{
	__asm jmp pfnAheadLib_PlaySoundW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_SendDriverMessage(void)
{
	__asm jmp pfnAheadLib_SendDriverMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_WOW32DriverCallback(void)
{
	__asm jmp pfnAheadLib_WOW32DriverCallback;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_WOW32ResolveMultiMediaHandle(void)
{
	__asm jmp pfnAheadLib_WOW32ResolveMultiMediaHandle;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_WOWAppExit(void)
{
	__asm jmp pfnAheadLib_WOWAppExit;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_aux32Message(void)
{
	__asm jmp pfnAheadLib_aux32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_auxGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_auxGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxGetNumDevs(void)
{
	__asm jmp pfnAheadLib_auxGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxGetVolume(void)
{
	__asm jmp pfnAheadLib_auxGetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxOutMessage(void)
{
	__asm jmp pfnAheadLib_auxOutMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_auxSetVolume(void)
{
	__asm jmp pfnAheadLib_auxSetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joy32Message(void)
{
	__asm jmp pfnAheadLib_joy32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyConfigChanged(void)
{
	__asm jmp pfnAheadLib_joyConfigChanged;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_joyGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_joyGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetNumDevs(void)
{
	__asm jmp pfnAheadLib_joyGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetPos(void)
{
	__asm jmp pfnAheadLib_joyGetPos;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetPosEx(void)
{
	__asm jmp pfnAheadLib_joyGetPosEx;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyGetThreshold(void)
{
	__asm jmp pfnAheadLib_joyGetThreshold;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joyReleaseCapture(void)
{
	__asm jmp pfnAheadLib_joyReleaseCapture;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joySetCapture(void)
{
	__asm jmp pfnAheadLib_joySetCapture;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_joySetThreshold(void)
{
	__asm jmp pfnAheadLib_joySetThreshold;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mci32Message(void)
{
	__asm jmp pfnAheadLib_mci32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciDriverNotify(void)
{
	__asm jmp pfnAheadLib_mciDriverNotify;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciDriverYield(void)
{
	__asm jmp pfnAheadLib_mciDriverYield;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciFreeCommandResource(void)
{
	__asm jmp pfnAheadLib_mciFreeCommandResource;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetCreatorTask(void)
{
	__asm jmp pfnAheadLib_mciGetCreatorTask;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetDeviceIDA(void)
{
	__asm jmp pfnAheadLib_mciGetDeviceIDA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetDeviceIDFromElementIDA(void)
{
	__asm jmp pfnAheadLib_mciGetDeviceIDFromElementIDA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetDeviceIDFromElementIDW(void)
{
	__asm jmp pfnAheadLib_mciGetDeviceIDFromElementIDW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetDeviceIDW(void)
{
	__asm jmp pfnAheadLib_mciGetDeviceIDW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetDriverData(void)
{
	__asm jmp pfnAheadLib_mciGetDriverData;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetErrorStringA(void)
{
	__asm jmp pfnAheadLib_mciGetErrorStringA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetErrorStringW(void)
{
	__asm jmp pfnAheadLib_mciGetErrorStringW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciGetYieldProc(void)
{
	__asm jmp pfnAheadLib_mciGetYieldProc;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciLoadCommandResource(void)
{
	__asm jmp pfnAheadLib_mciLoadCommandResource;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSendCommandA(void)
{
	__asm jmp pfnAheadLib_mciSendCommandA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSendCommandW(void)
{
	__asm jmp pfnAheadLib_mciSendCommandW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSendStringA(void)
{
	__asm jmp pfnAheadLib_mciSendStringA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSendStringW(void)
{
	__asm jmp pfnAheadLib_mciSendStringW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSetDriverData(void)
{
	__asm jmp pfnAheadLib_mciSetDriverData;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mciSetYieldProc(void)
{
	__asm jmp pfnAheadLib_mciSetYieldProc;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mid32Message(void)
{
	__asm jmp pfnAheadLib_mid32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiConnect(void)
{
	__asm jmp pfnAheadLib_midiConnect;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiDisconnect(void)
{
	__asm jmp pfnAheadLib_midiDisconnect;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInAddBuffer(void)
{
	__asm jmp pfnAheadLib_midiInAddBuffer;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInClose(void)
{
	__asm jmp pfnAheadLib_midiInClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_midiInGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_midiInGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetErrorTextA(void)
{
	__asm jmp pfnAheadLib_midiInGetErrorTextA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetErrorTextW(void)
{
	__asm jmp pfnAheadLib_midiInGetErrorTextW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetID(void)
{
	__asm jmp pfnAheadLib_midiInGetID;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInGetNumDevs(void)
{
	__asm jmp pfnAheadLib_midiInGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInMessage(void)
{
	__asm jmp pfnAheadLib_midiInMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInOpen(void)
{
	__asm jmp pfnAheadLib_midiInOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInPrepareHeader(void)
{
	__asm jmp pfnAheadLib_midiInPrepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInReset(void)
{
	__asm jmp pfnAheadLib_midiInReset;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInStart(void)
{
	__asm jmp pfnAheadLib_midiInStart;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInStop(void)
{
	__asm jmp pfnAheadLib_midiInStop;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiInUnprepareHeader(void)
{
	__asm jmp pfnAheadLib_midiInUnprepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutCacheDrumPatches(void)
{
	__asm jmp pfnAheadLib_midiOutCacheDrumPatches;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutCachePatches(void)
{
	__asm jmp pfnAheadLib_midiOutCachePatches;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutClose(void)
{
	__asm jmp pfnAheadLib_midiOutClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_midiOutGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_midiOutGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetErrorTextA(void)
{
	__asm jmp pfnAheadLib_midiOutGetErrorTextA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetErrorTextW(void)
{
	__asm jmp pfnAheadLib_midiOutGetErrorTextW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetID(void)
{
	__asm jmp pfnAheadLib_midiOutGetID;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetNumDevs(void)
{
	__asm jmp pfnAheadLib_midiOutGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutGetVolume(void)
{
	__asm jmp pfnAheadLib_midiOutGetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutLongMsg(void)
{
	__asm jmp pfnAheadLib_midiOutLongMsg;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutMessage(void)
{
	__asm jmp pfnAheadLib_midiOutMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutOpen(void)
{
	__asm jmp pfnAheadLib_midiOutOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutPrepareHeader(void)
{
	__asm jmp pfnAheadLib_midiOutPrepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutReset(void)
{
	__asm jmp pfnAheadLib_midiOutReset;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutSetVolume(void)
{
	__asm jmp pfnAheadLib_midiOutSetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutShortMsg(void)
{
	__asm jmp pfnAheadLib_midiOutShortMsg;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiOutUnprepareHeader(void)
{
	__asm jmp pfnAheadLib_midiOutUnprepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamClose(void)
{
	__asm jmp pfnAheadLib_midiStreamClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamOpen(void)
{
	__asm jmp pfnAheadLib_midiStreamOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamOut(void)
{
	__asm jmp pfnAheadLib_midiStreamOut;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamPause(void)
{
	__asm jmp pfnAheadLib_midiStreamPause;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamPosition(void)
{
	__asm jmp pfnAheadLib_midiStreamPosition;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamProperty(void)
{
	__asm jmp pfnAheadLib_midiStreamProperty;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamRestart(void)
{
	__asm jmp pfnAheadLib_midiStreamRestart;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_midiStreamStop(void)
{
	__asm jmp pfnAheadLib_midiStreamStop;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerClose(void)
{
	__asm jmp pfnAheadLib_mixerClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetControlDetailsA(void)
{
	__asm jmp pfnAheadLib_mixerGetControlDetailsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetControlDetailsW(void)
{
	__asm jmp pfnAheadLib_mixerGetControlDetailsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_mixerGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_mixerGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetID(void)
{
	__asm jmp pfnAheadLib_mixerGetID;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetLineControlsA(void)
{
	__asm jmp pfnAheadLib_mixerGetLineControlsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetLineControlsW(void)
{
	__asm jmp pfnAheadLib_mixerGetLineControlsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetLineInfoA(void)
{
	__asm jmp pfnAheadLib_mixerGetLineInfoA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetLineInfoW(void)
{
	__asm jmp pfnAheadLib_mixerGetLineInfoW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerGetNumDevs(void)
{
	__asm jmp pfnAheadLib_mixerGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerMessage(void)
{
	__asm jmp pfnAheadLib_mixerMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerOpen(void)
{
	__asm jmp pfnAheadLib_mixerOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mixerSetControlDetails(void)
{
	__asm jmp pfnAheadLib_mixerSetControlDetails;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmDrvInstall(void)
{
	__asm jmp pfnAheadLib_mmDrvInstall;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmGetCurrentTask(void)
{
	__asm jmp pfnAheadLib_mmGetCurrentTask;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmTaskBlock(void)
{
	__asm jmp pfnAheadLib_mmTaskBlock;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmTaskCreate(void)
{
	__asm jmp pfnAheadLib_mmTaskCreate;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmTaskSignal(void)
{
	__asm jmp pfnAheadLib_mmTaskSignal;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmTaskYield(void)
{
	__asm jmp pfnAheadLib_mmTaskYield;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioAdvance(void)
{
	__asm jmp pfnAheadLib_mmioAdvance;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioAscend(void)
{
	__asm jmp pfnAheadLib_mmioAscend;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioClose(void)
{
	__asm jmp pfnAheadLib_mmioClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioCreateChunk(void)
{
	__asm jmp pfnAheadLib_mmioCreateChunk;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioDescend(void)
{
	__asm jmp pfnAheadLib_mmioDescend;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioFlush(void)
{
	__asm jmp pfnAheadLib_mmioFlush;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioGetInfo(void)
{
	__asm jmp pfnAheadLib_mmioGetInfo;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioInstallIOProcA(void)
{
	__asm jmp pfnAheadLib_mmioInstallIOProcA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioInstallIOProcW(void)
{
	__asm jmp pfnAheadLib_mmioInstallIOProcW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioOpenA(void)
{
	__asm jmp pfnAheadLib_mmioOpenA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioOpenW(void)
{
	__asm jmp pfnAheadLib_mmioOpenW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioRead(void)
{
	__asm jmp pfnAheadLib_mmioRead;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioRenameA(void)
{
	__asm jmp pfnAheadLib_mmioRenameA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioRenameW(void)
{
	__asm jmp pfnAheadLib_mmioRenameW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioSeek(void)
{
	__asm jmp pfnAheadLib_mmioSeek;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioSendMessage(void)
{
	__asm jmp pfnAheadLib_mmioSendMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioSetBuffer(void)
{
	__asm jmp pfnAheadLib_mmioSetBuffer;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioSetInfo(void)
{
	__asm jmp pfnAheadLib_mmioSetInfo;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioStringToFOURCCA(void)
{
	__asm jmp pfnAheadLib_mmioStringToFOURCCA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioStringToFOURCCW(void)
{
	__asm jmp pfnAheadLib_mmioStringToFOURCCW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmioWrite(void)
{
	__asm jmp pfnAheadLib_mmioWrite;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mmsystemGetVersion(void)
{
	__asm jmp pfnAheadLib_mmsystemGetVersion;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mod32Message(void)
{
	__asm jmp pfnAheadLib_mod32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_mxd32Message(void)
{
	__asm jmp pfnAheadLib_mxd32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_sndPlaySoundA(void)
{
	__asm jmp pfnAheadLib_sndPlaySoundA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_sndPlaySoundW(void)
{
	__asm jmp pfnAheadLib_sndPlaySoundW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_tid32Message(void)
{
	__asm jmp pfnAheadLib_tid32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeBeginPeriod(void)
{
	__asm jmp pfnAheadLib_timeBeginPeriod;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeEndPeriod(void)
{
	__asm jmp pfnAheadLib_timeEndPeriod;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeGetDevCaps(void)
{
	__asm jmp pfnAheadLib_timeGetDevCaps;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeGetSystemTime(void)
{
	__asm jmp pfnAheadLib_timeGetSystemTime;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeGetTime(void)
{
	__asm jmp pfnAheadLib_timeGetTime;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeKillEvent(void)
{
	__asm jmp pfnAheadLib_timeKillEvent;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_timeSetEvent(void)
{
	__asm jmp pfnAheadLib_timeSetEvent;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInAddBuffer(void)
{
	__asm jmp pfnAheadLib_waveInAddBuffer;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInClose(void)
{
	__asm jmp pfnAheadLib_waveInClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_waveInGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_waveInGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetErrorTextA(void)
{
	__asm jmp pfnAheadLib_waveInGetErrorTextA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetErrorTextW(void)
{
	__asm jmp pfnAheadLib_waveInGetErrorTextW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetID(void)
{
	__asm jmp pfnAheadLib_waveInGetID;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetNumDevs(void)
{
	__asm jmp pfnAheadLib_waveInGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInGetPosition(void)
{
	__asm jmp pfnAheadLib_waveInGetPosition;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInMessage(void)
{
	__asm jmp pfnAheadLib_waveInMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInOpen(void)
{
	__asm jmp pfnAheadLib_waveInOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInPrepareHeader(void)
{
	__asm jmp pfnAheadLib_waveInPrepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInReset(void)
{
	__asm jmp pfnAheadLib_waveInReset;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInStart(void)
{
	__asm jmp pfnAheadLib_waveInStart;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInStop(void)
{
	__asm jmp pfnAheadLib_waveInStop;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveInUnprepareHeader(void)
{
	__asm jmp pfnAheadLib_waveInUnprepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutBreakLoop(void)
{
	__asm jmp pfnAheadLib_waveOutBreakLoop;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutClose(void)
{
	__asm jmp pfnAheadLib_waveOutClose;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetDevCapsA(void)
{
	__asm jmp pfnAheadLib_waveOutGetDevCapsA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetDevCapsW(void)
{
	__asm jmp pfnAheadLib_waveOutGetDevCapsW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetErrorTextA(void)
{
	__asm jmp pfnAheadLib_waveOutGetErrorTextA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetErrorTextW(void)
{
	__asm jmp pfnAheadLib_waveOutGetErrorTextW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetID(void)
{
	__asm jmp pfnAheadLib_waveOutGetID;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetNumDevs(void)
{
	__asm jmp pfnAheadLib_waveOutGetNumDevs;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetPitch(void)
{
	__asm jmp pfnAheadLib_waveOutGetPitch;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetPlaybackRate(void)
{
	__asm jmp pfnAheadLib_waveOutGetPlaybackRate;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetPosition(void)
{
	__asm jmp pfnAheadLib_waveOutGetPosition;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutGetVolume(void)
{
	__asm jmp pfnAheadLib_waveOutGetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutMessage(void)
{
	__asm jmp pfnAheadLib_waveOutMessage;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutOpen(void)
{
	__asm jmp pfnAheadLib_waveOutOpen;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutPause(void)
{
	__asm jmp pfnAheadLib_waveOutPause;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutPrepareHeader(void)
{
	__asm jmp pfnAheadLib_waveOutPrepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutReset(void)
{
	__asm jmp pfnAheadLib_waveOutReset;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutRestart(void)
{
	__asm jmp pfnAheadLib_waveOutRestart;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutSetPitch(void)
{
	__asm jmp pfnAheadLib_waveOutSetPitch;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutSetPlaybackRate(void)
{
	__asm jmp pfnAheadLib_waveOutSetPlaybackRate;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutSetVolume(void)
{
	__asm jmp pfnAheadLib_waveOutSetVolume;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutUnprepareHeader(void)
{
	__asm jmp pfnAheadLib_waveOutUnprepareHeader;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_waveOutWrite(void)
{
	__asm jmp pfnAheadLib_waveOutWrite;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_wid32Message(void)
{
	__asm jmp pfnAheadLib_wid32Message;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_wod32Message(void)
{
	__asm jmp pfnAheadLib_wod32Message;
}





#嵌入代码_结束


函数 整型 入口函数_动态库()

	如果 DLL_进程附加 == 被调用原因
		#嵌入代码
		// 这是对 32 位的 winmmm.dll 的劫持源码  南小鱼 QQ128492656
		DisableThreadLibraryCalls(模块句柄);
		Load() && Init();
		#嵌入代码_结束
		//这里就可以判断进程名,并启动线程处理自己的代码了

	否则 DLL_线程附加 == 被调用原因
		调试输出("DLL_线程附加")
	否则 DLL_线程分离 == 被调用原因
		调试输出("DLL_线程分离")
	否则 DLL_进程分离 == 被调用原因
		#嵌入代码
		// 这是对 32 位的 winmm.dll 的劫持源码  南小鱼 QQ128492656
		Free();
		#嵌入代码_结束

	返回 真 //成功返回真

