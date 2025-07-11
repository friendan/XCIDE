
// 这是对 64 位的 winmm.dll 的劫持源码  南小鱼 QQ128492656
#嵌入代码

#include <windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:Noname2=AheadLib_Unnamed2,@2,NONAME")
#pragma comment(linker, "/EXPORT:mciExecute=AheadLib_mciExecute,@3")
#pragma comment(linker, "/EXPORT:CloseDriver=AheadLib_CloseDriver,@4")
#pragma comment(linker, "/EXPORT:DefDriverProc=AheadLib_DefDriverProc,@5")
#pragma comment(linker, "/EXPORT:DriverCallback=AheadLib_DriverCallback,@6")
#pragma comment(linker, "/EXPORT:DrvGetModuleHandle=AheadLib_DrvGetModuleHandle,@7")
#pragma comment(linker, "/EXPORT:GetDriverModuleHandle=AheadLib_GetDriverModuleHandle,@8")
#pragma comment(linker, "/EXPORT:OpenDriver=AheadLib_OpenDriver,@9")
#pragma comment(linker, "/EXPORT:PlaySound=AheadLib_PlaySound,@10")
#pragma comment(linker, "/EXPORT:PlaySoundA=AheadLib_PlaySoundA,@11")
#pragma comment(linker, "/EXPORT:PlaySoundW=AheadLib_PlaySoundW,@12")
#pragma comment(linker, "/EXPORT:SendDriverMessage=AheadLib_SendDriverMessage,@13")
#pragma comment(linker, "/EXPORT:WOWAppExit=AheadLib_WOWAppExit,@14")
#pragma comment(linker, "/EXPORT:auxGetDevCapsA=AheadLib_auxGetDevCapsA,@15")
#pragma comment(linker, "/EXPORT:auxGetDevCapsW=AheadLib_auxGetDevCapsW,@16")
#pragma comment(linker, "/EXPORT:auxGetNumDevs=AheadLib_auxGetNumDevs,@17")
#pragma comment(linker, "/EXPORT:auxGetVolume=AheadLib_auxGetVolume,@18")
#pragma comment(linker, "/EXPORT:auxOutMessage=AheadLib_auxOutMessage,@19")
#pragma comment(linker, "/EXPORT:auxSetVolume=AheadLib_auxSetVolume,@20")
#pragma comment(linker, "/EXPORT:joyConfigChanged=AheadLib_joyConfigChanged,@21")
#pragma comment(linker, "/EXPORT:joyGetDevCapsA=AheadLib_joyGetDevCapsA,@22")
#pragma comment(linker, "/EXPORT:joyGetDevCapsW=AheadLib_joyGetDevCapsW,@23")
#pragma comment(linker, "/EXPORT:joyGetNumDevs=AheadLib_joyGetNumDevs,@24")
#pragma comment(linker, "/EXPORT:joyGetPos=AheadLib_joyGetPos,@25")
#pragma comment(linker, "/EXPORT:joyGetPosEx=AheadLib_joyGetPosEx,@26")
#pragma comment(linker, "/EXPORT:joyGetThreshold=AheadLib_joyGetThreshold,@27")
#pragma comment(linker, "/EXPORT:joyReleaseCapture=AheadLib_joyReleaseCapture,@28")
#pragma comment(linker, "/EXPORT:joySetCapture=AheadLib_joySetCapture,@29")
#pragma comment(linker, "/EXPORT:joySetThreshold=AheadLib_joySetThreshold,@30")
#pragma comment(linker, "/EXPORT:mciDriverNotify=AheadLib_mciDriverNotify,@31")
#pragma comment(linker, "/EXPORT:mciDriverYield=AheadLib_mciDriverYield,@32")
#pragma comment(linker, "/EXPORT:mciFreeCommandResource=AheadLib_mciFreeCommandResource,@33")
#pragma comment(linker, "/EXPORT:mciGetCreatorTask=AheadLib_mciGetCreatorTask,@34")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDA=AheadLib_mciGetDeviceIDA,@35")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDA=AheadLib_mciGetDeviceIDFromElementIDA,@36")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDW=AheadLib_mciGetDeviceIDFromElementIDW,@37")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDW=AheadLib_mciGetDeviceIDW,@38")
#pragma comment(linker, "/EXPORT:mciGetDriverData=AheadLib_mciGetDriverData,@39")
#pragma comment(linker, "/EXPORT:mciGetErrorStringA=AheadLib_mciGetErrorStringA,@40")
#pragma comment(linker, "/EXPORT:mciGetErrorStringW=AheadLib_mciGetErrorStringW,@41")
#pragma comment(linker, "/EXPORT:mciGetYieldProc=AheadLib_mciGetYieldProc,@42")
#pragma comment(linker, "/EXPORT:mciLoadCommandResource=AheadLib_mciLoadCommandResource,@43")
#pragma comment(linker, "/EXPORT:mciSendCommandA=AheadLib_mciSendCommandA,@44")
#pragma comment(linker, "/EXPORT:mciSendCommandW=AheadLib_mciSendCommandW,@45")
#pragma comment(linker, "/EXPORT:mciSendStringA=AheadLib_mciSendStringA,@46")
#pragma comment(linker, "/EXPORT:mciSendStringW=AheadLib_mciSendStringW,@47")
#pragma comment(linker, "/EXPORT:mciSetDriverData=AheadLib_mciSetDriverData,@48")
#pragma comment(linker, "/EXPORT:mciSetYieldProc=AheadLib_mciSetYieldProc,@49")
#pragma comment(linker, "/EXPORT:midiConnect=AheadLib_midiConnect,@50")
#pragma comment(linker, "/EXPORT:midiDisconnect=AheadLib_midiDisconnect,@51")
#pragma comment(linker, "/EXPORT:midiInAddBuffer=AheadLib_midiInAddBuffer,@52")
#pragma comment(linker, "/EXPORT:midiInClose=AheadLib_midiInClose,@53")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsA=AheadLib_midiInGetDevCapsA,@54")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsW=AheadLib_midiInGetDevCapsW,@55")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextA=AheadLib_midiInGetErrorTextA,@56")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextW=AheadLib_midiInGetErrorTextW,@57")
#pragma comment(linker, "/EXPORT:midiInGetID=AheadLib_midiInGetID,@58")
#pragma comment(linker, "/EXPORT:midiInGetNumDevs=AheadLib_midiInGetNumDevs,@59")
#pragma comment(linker, "/EXPORT:midiInMessage=AheadLib_midiInMessage,@60")
#pragma comment(linker, "/EXPORT:midiInOpen=AheadLib_midiInOpen,@61")
#pragma comment(linker, "/EXPORT:midiInPrepareHeader=AheadLib_midiInPrepareHeader,@62")
#pragma comment(linker, "/EXPORT:midiInReset=AheadLib_midiInReset,@63")
#pragma comment(linker, "/EXPORT:midiInStart=AheadLib_midiInStart,@64")
#pragma comment(linker, "/EXPORT:midiInStop=AheadLib_midiInStop,@65")
#pragma comment(linker, "/EXPORT:midiInUnprepareHeader=AheadLib_midiInUnprepareHeader,@66")
#pragma comment(linker, "/EXPORT:midiOutCacheDrumPatches=AheadLib_midiOutCacheDrumPatches,@67")
#pragma comment(linker, "/EXPORT:midiOutCachePatches=AheadLib_midiOutCachePatches,@68")
#pragma comment(linker, "/EXPORT:midiOutClose=AheadLib_midiOutClose,@69")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsA=AheadLib_midiOutGetDevCapsA,@70")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsW=AheadLib_midiOutGetDevCapsW,@71")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextA=AheadLib_midiOutGetErrorTextA,@72")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextW=AheadLib_midiOutGetErrorTextW,@73")
#pragma comment(linker, "/EXPORT:midiOutGetID=AheadLib_midiOutGetID,@74")
#pragma comment(linker, "/EXPORT:midiOutGetNumDevs=AheadLib_midiOutGetNumDevs,@75")
#pragma comment(linker, "/EXPORT:midiOutGetVolume=AheadLib_midiOutGetVolume,@76")
#pragma comment(linker, "/EXPORT:midiOutLongMsg=AheadLib_midiOutLongMsg,@77")
#pragma comment(linker, "/EXPORT:midiOutMessage=AheadLib_midiOutMessage,@78")
#pragma comment(linker, "/EXPORT:midiOutOpen=AheadLib_midiOutOpen,@79")
#pragma comment(linker, "/EXPORT:midiOutPrepareHeader=AheadLib_midiOutPrepareHeader,@80")
#pragma comment(linker, "/EXPORT:midiOutReset=AheadLib_midiOutReset,@81")
#pragma comment(linker, "/EXPORT:midiOutSetVolume=AheadLib_midiOutSetVolume,@82")
#pragma comment(linker, "/EXPORT:midiOutShortMsg=AheadLib_midiOutShortMsg,@83")
#pragma comment(linker, "/EXPORT:midiOutUnprepareHeader=AheadLib_midiOutUnprepareHeader,@84")
#pragma comment(linker, "/EXPORT:midiStreamClose=AheadLib_midiStreamClose,@85")
#pragma comment(linker, "/EXPORT:midiStreamOpen=AheadLib_midiStreamOpen,@86")
#pragma comment(linker, "/EXPORT:midiStreamOut=AheadLib_midiStreamOut,@87")
#pragma comment(linker, "/EXPORT:midiStreamPause=AheadLib_midiStreamPause,@88")
#pragma comment(linker, "/EXPORT:midiStreamPosition=AheadLib_midiStreamPosition,@89")
#pragma comment(linker, "/EXPORT:midiStreamProperty=AheadLib_midiStreamProperty,@90")
#pragma comment(linker, "/EXPORT:midiStreamRestart=AheadLib_midiStreamRestart,@91")
#pragma comment(linker, "/EXPORT:midiStreamStop=AheadLib_midiStreamStop,@92")
#pragma comment(linker, "/EXPORT:mixerClose=AheadLib_mixerClose,@93")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsA=AheadLib_mixerGetControlDetailsA,@94")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsW=AheadLib_mixerGetControlDetailsW,@95")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsA=AheadLib_mixerGetDevCapsA,@96")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsW=AheadLib_mixerGetDevCapsW,@97")
#pragma comment(linker, "/EXPORT:mixerGetID=AheadLib_mixerGetID,@98")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsA=AheadLib_mixerGetLineControlsA,@99")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsW=AheadLib_mixerGetLineControlsW,@100")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoA=AheadLib_mixerGetLineInfoA,@101")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoW=AheadLib_mixerGetLineInfoW,@102")
#pragma comment(linker, "/EXPORT:mixerGetNumDevs=AheadLib_mixerGetNumDevs,@103")
#pragma comment(linker, "/EXPORT:mixerMessage=AheadLib_mixerMessage,@104")
#pragma comment(linker, "/EXPORT:mixerOpen=AheadLib_mixerOpen,@105")
#pragma comment(linker, "/EXPORT:mixerSetControlDetails=AheadLib_mixerSetControlDetails,@106")
#pragma comment(linker, "/EXPORT:mmDrvInstall=AheadLib_mmDrvInstall,@107")
#pragma comment(linker, "/EXPORT:mmGetCurrentTask=AheadLib_mmGetCurrentTask,@108")
#pragma comment(linker, "/EXPORT:mmTaskBlock=AheadLib_mmTaskBlock,@109")
#pragma comment(linker, "/EXPORT:mmTaskCreate=AheadLib_mmTaskCreate,@110")
#pragma comment(linker, "/EXPORT:mmTaskSignal=AheadLib_mmTaskSignal,@111")
#pragma comment(linker, "/EXPORT:mmTaskYield=AheadLib_mmTaskYield,@112")
#pragma comment(linker, "/EXPORT:mmioAdvance=AheadLib_mmioAdvance,@113")
#pragma comment(linker, "/EXPORT:mmioAscend=AheadLib_mmioAscend,@114")
#pragma comment(linker, "/EXPORT:mmioClose=AheadLib_mmioClose,@115")
#pragma comment(linker, "/EXPORT:mmioCreateChunk=AheadLib_mmioCreateChunk,@116")
#pragma comment(linker, "/EXPORT:mmioDescend=AheadLib_mmioDescend,@117")
#pragma comment(linker, "/EXPORT:mmioFlush=AheadLib_mmioFlush,@118")
#pragma comment(linker, "/EXPORT:mmioGetInfo=AheadLib_mmioGetInfo,@119")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcA=AheadLib_mmioInstallIOProcA,@120")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcW=AheadLib_mmioInstallIOProcW,@121")
#pragma comment(linker, "/EXPORT:mmioOpenA=AheadLib_mmioOpenA,@122")
#pragma comment(linker, "/EXPORT:mmioOpenW=AheadLib_mmioOpenW,@123")
#pragma comment(linker, "/EXPORT:mmioRead=AheadLib_mmioRead,@124")
#pragma comment(linker, "/EXPORT:mmioRenameA=AheadLib_mmioRenameA,@125")
#pragma comment(linker, "/EXPORT:mmioRenameW=AheadLib_mmioRenameW,@126")
#pragma comment(linker, "/EXPORT:mmioSeek=AheadLib_mmioSeek,@127")
#pragma comment(linker, "/EXPORT:mmioSendMessage=AheadLib_mmioSendMessage,@128")
#pragma comment(linker, "/EXPORT:mmioSetBuffer=AheadLib_mmioSetBuffer,@129")
#pragma comment(linker, "/EXPORT:mmioSetInfo=AheadLib_mmioSetInfo,@130")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCA=AheadLib_mmioStringToFOURCCA,@131")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCW=AheadLib_mmioStringToFOURCCW,@132")
#pragma comment(linker, "/EXPORT:mmioWrite=AheadLib_mmioWrite,@133")
#pragma comment(linker, "/EXPORT:mmsystemGetVersion=AheadLib_mmsystemGetVersion,@134")
#pragma comment(linker, "/EXPORT:sndPlaySoundA=AheadLib_sndPlaySoundA,@135")
#pragma comment(linker, "/EXPORT:sndPlaySoundW=AheadLib_sndPlaySoundW,@136")
#pragma comment(linker, "/EXPORT:timeBeginPeriod=AheadLib_timeBeginPeriod,@137")
#pragma comment(linker, "/EXPORT:timeEndPeriod=AheadLib_timeEndPeriod,@138")
#pragma comment(linker, "/EXPORT:timeGetDevCaps=AheadLib_timeGetDevCaps,@139")
#pragma comment(linker, "/EXPORT:timeGetSystemTime=AheadLib_timeGetSystemTime,@140")
#pragma comment(linker, "/EXPORT:timeGetTime=AheadLib_timeGetTime,@141")
#pragma comment(linker, "/EXPORT:timeKillEvent=AheadLib_timeKillEvent,@142")
#pragma comment(linker, "/EXPORT:timeSetEvent=AheadLib_timeSetEvent,@143")
#pragma comment(linker, "/EXPORT:waveInAddBuffer=AheadLib_waveInAddBuffer,@144")
#pragma comment(linker, "/EXPORT:waveInClose=AheadLib_waveInClose,@145")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsA=AheadLib_waveInGetDevCapsA,@146")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsW=AheadLib_waveInGetDevCapsW,@147")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextA=AheadLib_waveInGetErrorTextA,@148")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextW=AheadLib_waveInGetErrorTextW,@149")
#pragma comment(linker, "/EXPORT:waveInGetID=AheadLib_waveInGetID,@150")
#pragma comment(linker, "/EXPORT:waveInGetNumDevs=AheadLib_waveInGetNumDevs,@151")
#pragma comment(linker, "/EXPORT:waveInGetPosition=AheadLib_waveInGetPosition,@152")
#pragma comment(linker, "/EXPORT:waveInMessage=AheadLib_waveInMessage,@153")
#pragma comment(linker, "/EXPORT:waveInOpen=AheadLib_waveInOpen,@154")
#pragma comment(linker, "/EXPORT:waveInPrepareHeader=AheadLib_waveInPrepareHeader,@155")
#pragma comment(linker, "/EXPORT:waveInReset=AheadLib_waveInReset,@156")
#pragma comment(linker, "/EXPORT:waveInStart=AheadLib_waveInStart,@157")
#pragma comment(linker, "/EXPORT:waveInStop=AheadLib_waveInStop,@158")
#pragma comment(linker, "/EXPORT:waveInUnprepareHeader=AheadLib_waveInUnprepareHeader,@159")
#pragma comment(linker, "/EXPORT:waveOutBreakLoop=AheadLib_waveOutBreakLoop,@160")
#pragma comment(linker, "/EXPORT:waveOutClose=AheadLib_waveOutClose,@161")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsA=AheadLib_waveOutGetDevCapsA,@162")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsW=AheadLib_waveOutGetDevCapsW,@163")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextA=AheadLib_waveOutGetErrorTextA,@164")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextW=AheadLib_waveOutGetErrorTextW,@165")
#pragma comment(linker, "/EXPORT:waveOutGetID=AheadLib_waveOutGetID,@166")
#pragma comment(linker, "/EXPORT:waveOutGetNumDevs=AheadLib_waveOutGetNumDevs,@167")
#pragma comment(linker, "/EXPORT:waveOutGetPitch=AheadLib_waveOutGetPitch,@168")
#pragma comment(linker, "/EXPORT:waveOutGetPlaybackRate=AheadLib_waveOutGetPlaybackRate,@169")
#pragma comment(linker, "/EXPORT:waveOutGetPosition=AheadLib_waveOutGetPosition,@170")
#pragma comment(linker, "/EXPORT:waveOutGetVolume=AheadLib_waveOutGetVolume,@171")
#pragma comment(linker, "/EXPORT:waveOutMessage=AheadLib_waveOutMessage,@172")
#pragma comment(linker, "/EXPORT:waveOutOpen=AheadLib_waveOutOpen,@173")
#pragma comment(linker, "/EXPORT:waveOutPause=AheadLib_waveOutPause,@174")
#pragma comment(linker, "/EXPORT:waveOutPrepareHeader=AheadLib_waveOutPrepareHeader,@175")
#pragma comment(linker, "/EXPORT:waveOutReset=AheadLib_waveOutReset,@176")
#pragma comment(linker, "/EXPORT:waveOutRestart=AheadLib_waveOutRestart,@177")
#pragma comment(linker, "/EXPORT:waveOutSetPitch=AheadLib_waveOutSetPitch,@178")
#pragma comment(linker, "/EXPORT:waveOutSetPlaybackRate=AheadLib_waveOutSetPlaybackRate,@179")
#pragma comment(linker, "/EXPORT:waveOutSetVolume=AheadLib_waveOutSetVolume,@180")
#pragma comment(linker, "/EXPORT:waveOutUnprepareHeader=AheadLib_waveOutUnprepareHeader,@181")
#pragma comment(linker, "/EXPORT:waveOutWrite=AheadLib_waveOutWrite,@182")


extern "C" {
 PVOID pfnAheadLib_Unnamed2;
 PVOID pfnAheadLib_mciExecute;
 PVOID pfnAheadLib_CloseDriver;
 PVOID pfnAheadLib_DefDriverProc;
 PVOID pfnAheadLib_DriverCallback;
 PVOID pfnAheadLib_DrvGetModuleHandle;
 PVOID pfnAheadLib_GetDriverModuleHandle;
 PVOID pfnAheadLib_OpenDriver;
 PVOID pfnAheadLib_PlaySound;
 PVOID pfnAheadLib_PlaySoundA;
 PVOID pfnAheadLib_PlaySoundW;
 PVOID pfnAheadLib_SendDriverMessage;
 PVOID pfnAheadLib_WOWAppExit;
 PVOID pfnAheadLib_auxGetDevCapsA;
 PVOID pfnAheadLib_auxGetDevCapsW;
 PVOID pfnAheadLib_auxGetNumDevs;
 PVOID pfnAheadLib_auxGetVolume;
 PVOID pfnAheadLib_auxOutMessage;
 PVOID pfnAheadLib_auxSetVolume;
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
 PVOID pfnAheadLib_sndPlaySoundA;
 PVOID pfnAheadLib_sndPlaySoundW;
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
 void AheadLib_Unnamed2(void);
 void AheadLib_mciExecute(void);
 void AheadLib_CloseDriver(void);
 void AheadLib_DefDriverProc(void);
 void AheadLib_DriverCallback(void);
 void AheadLib_DrvGetModuleHandle(void);
 void AheadLib_GetDriverModuleHandle(void);
 void AheadLib_OpenDriver(void);
 void AheadLib_PlaySound(void);
 void AheadLib_PlaySoundA(void);
 void AheadLib_PlaySoundW(void);
 void AheadLib_SendDriverMessage(void);
 void AheadLib_WOWAppExit(void);
 void AheadLib_auxGetDevCapsA(void);
 void AheadLib_auxGetDevCapsW(void);
 void AheadLib_auxGetNumDevs(void);
 void AheadLib_auxGetVolume(void);
 void AheadLib_auxOutMessage(void);
 void AheadLib_auxSetVolume(void);
 void AheadLib_joyConfigChanged(void);
 void AheadLib_joyGetDevCapsA(void);
 void AheadLib_joyGetDevCapsW(void);
 void AheadLib_joyGetNumDevs(void);
 void AheadLib_joyGetPos(void);
 void AheadLib_joyGetPosEx(void);
 void AheadLib_joyGetThreshold(void);
 void AheadLib_joyReleaseCapture(void);
 void AheadLib_joySetCapture(void);
 void AheadLib_joySetThreshold(void);
 void AheadLib_mciDriverNotify(void);
 void AheadLib_mciDriverYield(void);
 void AheadLib_mciFreeCommandResource(void);
 void AheadLib_mciGetCreatorTask(void);
 void AheadLib_mciGetDeviceIDA(void);
 void AheadLib_mciGetDeviceIDFromElementIDA(void);
 void AheadLib_mciGetDeviceIDFromElementIDW(void);
 void AheadLib_mciGetDeviceIDW(void);
 void AheadLib_mciGetDriverData(void);
 void AheadLib_mciGetErrorStringA(void);
 void AheadLib_mciGetErrorStringW(void);
 void AheadLib_mciGetYieldProc(void);
 void AheadLib_mciLoadCommandResource(void);
 void AheadLib_mciSendCommandA(void);
 void AheadLib_mciSendCommandW(void);
 void AheadLib_mciSendStringA(void);
 void AheadLib_mciSendStringW(void);
 void AheadLib_mciSetDriverData(void);
 void AheadLib_mciSetYieldProc(void);
 void AheadLib_midiConnect(void);
 void AheadLib_midiDisconnect(void);
 void AheadLib_midiInAddBuffer(void);
 void AheadLib_midiInClose(void);
 void AheadLib_midiInGetDevCapsA(void);
 void AheadLib_midiInGetDevCapsW(void);
 void AheadLib_midiInGetErrorTextA(void);
 void AheadLib_midiInGetErrorTextW(void);
 void AheadLib_midiInGetID(void);
 void AheadLib_midiInGetNumDevs(void);
 void AheadLib_midiInMessage(void);
 void AheadLib_midiInOpen(void);
 void AheadLib_midiInPrepareHeader(void);
 void AheadLib_midiInReset(void);
 void AheadLib_midiInStart(void);
 void AheadLib_midiInStop(void);
 void AheadLib_midiInUnprepareHeader(void);
 void AheadLib_midiOutCacheDrumPatches(void);
 void AheadLib_midiOutCachePatches(void);
 void AheadLib_midiOutClose(void);
 void AheadLib_midiOutGetDevCapsA(void);
 void AheadLib_midiOutGetDevCapsW(void);
 void AheadLib_midiOutGetErrorTextA(void);
 void AheadLib_midiOutGetErrorTextW(void);
 void AheadLib_midiOutGetID(void);
 void AheadLib_midiOutGetNumDevs(void);
 void AheadLib_midiOutGetVolume(void);
 void AheadLib_midiOutLongMsg(void);
 void AheadLib_midiOutMessage(void);
 void AheadLib_midiOutOpen(void);
 void AheadLib_midiOutPrepareHeader(void);
 void AheadLib_midiOutReset(void);
 void AheadLib_midiOutSetVolume(void);
 void AheadLib_midiOutShortMsg(void);
 void AheadLib_midiOutUnprepareHeader(void);
 void AheadLib_midiStreamClose(void);
 void AheadLib_midiStreamOpen(void);
 void AheadLib_midiStreamOut(void);
 void AheadLib_midiStreamPause(void);
 void AheadLib_midiStreamPosition(void);
 void AheadLib_midiStreamProperty(void);
 void AheadLib_midiStreamRestart(void);
 void AheadLib_midiStreamStop(void);
 void AheadLib_mixerClose(void);
 void AheadLib_mixerGetControlDetailsA(void);
 void AheadLib_mixerGetControlDetailsW(void);
 void AheadLib_mixerGetDevCapsA(void);
 void AheadLib_mixerGetDevCapsW(void);
 void AheadLib_mixerGetID(void);
 void AheadLib_mixerGetLineControlsA(void);
 void AheadLib_mixerGetLineControlsW(void);
 void AheadLib_mixerGetLineInfoA(void);
 void AheadLib_mixerGetLineInfoW(void);
 void AheadLib_mixerGetNumDevs(void);
 void AheadLib_mixerMessage(void);
 void AheadLib_mixerOpen(void);
 void AheadLib_mixerSetControlDetails(void);
 void AheadLib_mmDrvInstall(void);
 void AheadLib_mmGetCurrentTask(void);
 void AheadLib_mmTaskBlock(void);
 void AheadLib_mmTaskCreate(void);
 void AheadLib_mmTaskSignal(void);
 void AheadLib_mmTaskYield(void);
 void AheadLib_mmioAdvance(void);
 void AheadLib_mmioAscend(void);
 void AheadLib_mmioClose(void);
 void AheadLib_mmioCreateChunk(void);
 void AheadLib_mmioDescend(void);
 void AheadLib_mmioFlush(void);
 void AheadLib_mmioGetInfo(void);
 void AheadLib_mmioInstallIOProcA(void);
 void AheadLib_mmioInstallIOProcW(void);
 void AheadLib_mmioOpenA(void);
 void AheadLib_mmioOpenW(void);
 void AheadLib_mmioRead(void);
 void AheadLib_mmioRenameA(void);
 void AheadLib_mmioRenameW(void);
 void AheadLib_mmioSeek(void);
 void AheadLib_mmioSendMessage(void);
 void AheadLib_mmioSetBuffer(void);
 void AheadLib_mmioSetInfo(void);
 void AheadLib_mmioStringToFOURCCA(void);
 void AheadLib_mmioStringToFOURCCW(void);
 void AheadLib_mmioWrite(void);
 void AheadLib_mmsystemGetVersion(void);
 void AheadLib_sndPlaySoundA(void);
 void AheadLib_sndPlaySoundW(void);
 void AheadLib_timeBeginPeriod(void);
 void AheadLib_timeEndPeriod(void);
 void AheadLib_timeGetDevCaps(void);
 void AheadLib_timeGetSystemTime(void);
 void AheadLib_timeGetTime(void);
 void AheadLib_timeKillEvent(void);
 void AheadLib_timeSetEvent(void);
 void AheadLib_waveInAddBuffer(void);
 void AheadLib_waveInClose(void);
 void AheadLib_waveInGetDevCapsA(void);
 void AheadLib_waveInGetDevCapsW(void);
 void AheadLib_waveInGetErrorTextA(void);
 void AheadLib_waveInGetErrorTextW(void);
 void AheadLib_waveInGetID(void);
 void AheadLib_waveInGetNumDevs(void);
 void AheadLib_waveInGetPosition(void);
 void AheadLib_waveInMessage(void);
 void AheadLib_waveInOpen(void);
 void AheadLib_waveInPrepareHeader(void);
 void AheadLib_waveInReset(void);
 void AheadLib_waveInStart(void);
 void AheadLib_waveInStop(void);
 void AheadLib_waveInUnprepareHeader(void);
 void AheadLib_waveOutBreakLoop(void);
 void AheadLib_waveOutClose(void);
 void AheadLib_waveOutGetDevCapsA(void);
 void AheadLib_waveOutGetDevCapsW(void);
 void AheadLib_waveOutGetErrorTextA(void);
 void AheadLib_waveOutGetErrorTextW(void);
 void AheadLib_waveOutGetID(void);
 void AheadLib_waveOutGetNumDevs(void);
 void AheadLib_waveOutGetPitch(void);
 void AheadLib_waveOutGetPlaybackRate(void);
 void AheadLib_waveOutGetPosition(void);
 void AheadLib_waveOutGetVolume(void);
 void AheadLib_waveOutMessage(void);
 void AheadLib_waveOutOpen(void);
 void AheadLib_waveOutPause(void);
 void AheadLib_waveOutPrepareHeader(void);
 void AheadLib_waveOutReset(void);
 void AheadLib_waveOutRestart(void);
 void AheadLib_waveOutSetPitch(void);
 void AheadLib_waveOutSetPlaybackRate(void);
 void AheadLib_waveOutSetVolume(void);
 void AheadLib_waveOutUnprepareHeader(void);
 void AheadLib_waveOutWrite(void);
};

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
	if(NULL == (pfnAheadLib_WOWAppExit = GetAddress("WOWAppExit")))
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
	if(NULL == (pfnAheadLib_sndPlaySoundA = GetAddress("sndPlaySoundA")))
		return FALSE;
	if(NULL == (pfnAheadLib_sndPlaySoundW = GetAddress("sndPlaySoundW")))
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
	return TRUE;
}




#嵌入代码_结束


函数 整型 入口函数_动态库()

	如果 DLL_进程附加 == 被调用原因
		#嵌入代码
		// 这是对 64 位的 winmm.dll 的劫持源码  南小鱼 QQ128492656
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
		// 这是对 64 位的 winmm.dll 的劫持源码  南小鱼 QQ128492656
		Free();
		#嵌入代码_结束

	返回 真 //成功返回真




