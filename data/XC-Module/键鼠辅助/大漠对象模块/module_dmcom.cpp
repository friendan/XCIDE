#include "module_dmcom.h"

class MyVariant {
public:
    MyVariant() { }
    ~MyVariant() { }

    operator int()
    {
        if (mVal.vt == VT_INT)
            return mVal.intVal;
        if (mVal.vt == VT_I4)
            return mVal.lVal;
        return 0;
    }
    operator long()
    {
        if (mVal.vt == VT_INT)
            return mVal.intVal;
        if (mVal.vt == VT_I4)
            return mVal.lVal;
        return 0;
    }
    operator float()
    {
        if (mVal.vt == VT_R4)
            return mVal.fltVal;
        if (mVal.vt == VT_DATE)
            return mVal.fltVal;
        return 0.0F;
    }
    operator double()
    {
        if (mVal.vt == VT_R8)
            return mVal.dblVal;
        if (mVal.vt == VT_DATE)
            return mVal.dblVal;
        return 0.0;
    }
    operator CXText()
    {
        return mVal.vt == VT_BSTR ? mVal.bstrVal : CXText(L"");
    }
    operator _variant_t*() { return &mVal; }

private:
    _variant_t mVal;
};

class MyVariants {
public:
    MyVariants() { mCount = 0; }

    template <typename... Args>
    MyVariants(const Args... args)
    {
        mCount = sizeof...(args);
        if (mCount > 0) {
            pVariant = new _variant_t[mCount];
            Init(args...);
        }
    };
    ~MyVariants()
    {
        if (mCount) {
            delete[] pVariant;
            mCount = 0;
        }
    };

public:
    UINT mCount;
    _variant_t* pVariant = NULL;

private:
    UINT p = 0;
    template <typename T>
    void Init(T Val)
    {
        p++;
        pVariant[mCount - p] = _variant_t(Val);
    }

    template <typename T, typename... Args>
    void Init(const T t, const Args... args)
    {
        Init(t);
        Init(args...);
    }
};

class MyDispatchDriver {
public:
    IDispatch* p;
    MyDispatchDriver()
    {
        p = NULL;
    }

    MyDispatchDriver(IDispatch* lp)
    {
        if ((p = lp) != NULL)
            p->AddRef();
    }

    ~MyDispatchDriver()
    {
        if (p)
            p->Release();
    }

    HRESULT GetIDOfName(LPCOLESTR lpsz, DISPID* pdispid)
    {
        HRESULT hr = E_FAIL;
        if (p == NULL)
            return hr;

        return p->GetIDsOfNames(IID_NULL, (LPOLESTR*)&lpsz, 1, LOCALE_USER_DEFAULT, pdispid);
    }

    HRESULT Invoke(DISPID dispid, const MyVariants& variant, VARIANT* pvarRet = NULL)
    {
        HRESULT hr = E_FAIL;
        DISPPARAMS dispparams = { variant.pVariant, NULL, variant.mCount, 0 };
        if (p == NULL)
            return hr;

        return p->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, pvarRet, NULL, NULL);
    }
};

DmSoft_Com::DmSoft_Com()
{
    mObj = NULL;
    mIsInit = FALSE;
    auto hResult = CoInitialize(NULL);
};

DmSoft_Com::~DmSoft_Com()
{
    if (mObj)
        mObj->Release();
    mIsInit = FALSE;
    CoUninitialize();
}

typedef int(_stdcall* Fun_SetDllPathW)(const wchar_t*);

BOOL DmSoft_Com::RegDll(const wchar_t* dmregdll, const wchar_t* dmdll)
{
    if (dmregdll && dmdll) {
        auto hModle = LoadLibraryW(dmregdll);
        if (hModle) {
            Fun_SetDllPathW SetDllPathW = (Fun_SetDllPathW)GetProcAddress(hModle, "SetDllPathW");
            if (SetDllPathW) {
                SetDllPathW(dmdll);
				return TRUE;
            }
        }
    }
	return FALSE;
}

BOOL DmSoft_Com::Init(){

    CLSID clsid;
    IUnknown* pUnknown = NULL;
    HRESULT hr;

    hr = ::CLSIDFromProgID(L"dm.dmsoft", &clsid);
    if (FAILED(hr))
        goto exit;

    hr = ::CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (LPVOID*)&pUnknown);
    if (FAILED(hr))
        goto exit;

    pUnknown->QueryInterface(IID_IDispatch, (void**)&mObj);
    if (pUnknown)
        mIsInit = TRUE;

exit:
    if (pUnknown)
        pUnknown->Release();
    return mIsInit;
}

//---------------基本设置-定义开始---------------
int DmSoft_Com::EnablePicCache(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnablePicCache", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetBasePath()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetBasePath", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetDmCount()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDmCount", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetID()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetID", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetLastError()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetLastError", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetPath()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetPath", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::Reg(const wchar_t* reg_code, const wchar_t* ver_info)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Reg", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(reg_code, ver_info);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RegEx(const wchar_t* reg_code, const wchar_t* ver_info, const wchar_t* ip)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RegEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(reg_code, ver_info, ip);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RegExNoMac(const wchar_t* reg_code, const wchar_t* ver_info, const wchar_t* ip)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RegExNoMac", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(reg_code, ver_info, ip);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RegNoMac(const wchar_t* reg_code, const wchar_t* ver_info)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RegNoMac", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(reg_code, ver_info);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetDisplayInput(const wchar_t* mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDisplayInput", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetEnumWindowDelay(int delay)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetEnumWindowDelay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(delay);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetPath(const wchar_t* path)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetPath", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(path);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetShowErrorMsg(int show)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetShowErrorMsg", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(show);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ver()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ver", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------基本设置-定义结束---------------

//---------------后台设置-定义开始---------------
int DmSoft_Com::BindWindow(int hwnd, const wchar_t* display, const wchar_t* mouse, const wchar_t* keypad, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"BindWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, display, mouse, keypad, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::BindWindowEx(int hwnd, const wchar_t* display, const wchar_t* mouse, const wchar_t* keypad, const wchar_t* publicinfo, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"BindWindowEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, display, mouse, keypad, publicinfo, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DownCpu(int rate)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DownCpu", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(rate);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableBind(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableBind", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableFakeActive(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableFakeActive", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableIme(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableIme", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableKeypadMsg(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableKeypadMsg", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableKeypadPatch(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableKeypadPatch", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableKeypadSync(int enable, int time_out)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableKeypadSync", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable, time_out);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableMouseMsg(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableMouseMsg", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableMouseSync(int enable, int time_out)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableMouseSync", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable, time_out);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableRealKeypad(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableRealKeypad", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableRealMouse(int enable, int mousedelay, int mousestep)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableRealMouse", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable, mousedelay, mousestep);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableSpeedDx(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableSpeedDx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::ForceUnBindWindow(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ForceUnBindWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetBindWindow()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetBindWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::IsBind(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"IsBind", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LockDisplay(int lock)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LockDisplay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(lock);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LockInput(int lock)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LockInput", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(lock);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LockMouseRect(int x1, int y1, int x2, int y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LockMouseRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetAero(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetAero", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetDisplayDelay(int time)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDisplayDelay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(time);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SwitchBindWindow(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SwitchBindWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::UnBindWindow()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"UnBindWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------后台设置-定义结束---------------

//---------------键鼠操作-定义开始---------------
int DmSoft_Com::GetCursorPos(int& x, int& y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetCursorPos", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    x = status ? pn.pVariant[1].lVal : 0;
    y = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::GetCursorShape()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetCursorShape", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetCursorShapeEx(int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetCursorShapeEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetCursorShapeEx()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetCursorShapeEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MoveTo(int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MoveTo", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MoveR(int rx, int ry)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MoveR", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(rx, ry);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::MoveToEx(int x, int y, int w, int h)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MoveToEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y, w, h);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetMouseDelay(const wchar_t* type, int delay)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetMouseDelay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(type, delay);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LeftDown()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LeftDown", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LeftUp()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LeftUp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LeftClick()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LeftClick", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LeftDoubleClick()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LeftDoubleClick", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MiddleDown()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MiddleDown", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MiddleUp()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MiddleUp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MiddleClick()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MiddleClick", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RightDown()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RightDown", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RightUp()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RightUp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::RightClick()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RightClick", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WheelDown()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WheelDown", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WheelUp()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WheelUp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetKeyState(int vk_code)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetKeyState", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(vk_code);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyDown(int vk_code)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyDown", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(vk_code);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyUp(int vk_code)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyUp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(vk_code);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyDownChar(const wchar_t* key_str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyDownChar", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(key_str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyUpChar(const wchar_t* key_str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyUpChar", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(key_str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyPress(int vk_code)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyPress", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(vk_code);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyPressChar(const wchar_t* key_str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyPressChar", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(key_str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::KeyPressStr(const wchar_t* key_str, int delay)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"KeyPressStr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(key_str, delay);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetKeypadDelay(const wchar_t* type, int delay)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetKeypadDelay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(type, delay);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetSimMode(int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetSimMode", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WaitKey(int vk_code, int time_out)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WaitKey", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(vk_code, time_out);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------键鼠操作-定义结束---------------

//---------------窗口操作-定义开始---------------
CXText DmSoft_Com::EnumProcess(const wchar_t* name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumProcess", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetProcessInfo(int pid)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetProcessInfo", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pid);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::ClientToScreen(int hwnd, int& x, int& y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ClientToScreen", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y);
    MyVariants pr(x, y);
    pr.pVariant[0].vt = VT_I4;
    pr.pVariant[1].vt = VT_I4;
    pn.pVariant[1].vt = VT_BYREF|VT_VARIANT;
    pn.pVariant[1].pvarVal = &pr.pVariant[1];
    pn.pVariant[0].vt = VT_BYREF|VT_VARIANT;
    pn.pVariant[0].pvarVal = &pr.pVariant[0];
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    x = status ? pr.pVariant[1].lVal : 0;
    y = status ? pr.pVariant[0].lVal : 0;
    return vResult;
}

int DmSoft_Com::ScreenToClient(int hwnd, int& x, int& y)
{
	static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ScreenToClient", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y);
    MyVariants pr(x, y);
    pr.pVariant[0].vt = VT_I4;
    pr.pVariant[1].vt = VT_I4;
    pn.pVariant[1].vt = VT_BYREF|VT_VARIANT;
    pn.pVariant[1].pvarVal = &pr.pVariant[1];
    pn.pVariant[0].vt = VT_BYREF|VT_VARIANT;
    pn.pVariant[0].pvarVal = &pr.pVariant[0];
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    x = status ? pr.pVariant[1].lVal : 0;
    y = status ? pr.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::EnumWindow(int parent, const wchar_t* title, const wchar_t* class_name, int filter)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(parent, title, class_name, filter);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumWindowByProcess(const wchar_t* process_name, const wchar_t* title, const wchar_t* class_name, int filter)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumWindowByProcess", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(process_name, title, class_name, filter);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumWindowByProcessId(int pid, const wchar_t* title, const wchar_t* class_name, int filter)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumWindowByProcessId", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pid, title, class_name, filter);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindWindowSuper(const wchar_t* spec1, int flag1, int type1, const wchar_t* spec2, int flag2, int type2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindWindowSuper", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(spec1, flag1, type1, spec2, flag2, type2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindWindowByProcess(const wchar_t* proc_name, const wchar_t* wnd_class, const wchar_t* title)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindWindowByProcess", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(proc_name, wnd_class, title);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindWindowByProcessId(int pid, const wchar_t* wnd_class, const wchar_t* title)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindWindowByProcessId", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pid, wnd_class, title);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetClientRect(int hwnd, int& x1, int& y1, int& x2, int& y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetClientRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x1, y1, x2, y2);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    pn.pVariant[2].vt |= VT_BYREF;
    pn.pVariant[3].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    x1 = status ? pn.pVariant[3].lVal : 0;
    y1 = status ? pn.pVariant[2].lVal : 0;
    x2 = status ? pn.pVariant[1].lVal : 0;
    y2 = status ? pn.pVariant[0].lVal : 0;
    return vResult;
    return vResult;
}

int DmSoft_Com::GetClientSize(int hwnd, int& width, int& height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetClientSize", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, width, height);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    width = status ? pn.pVariant[1].lVal : 0;
    height = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

int DmSoft_Com::SetClientSize(int hwnd, int width, int height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetClientSize", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, width, height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWindowRect(int hwnd, int& x1, int& y1, int& x2, int& y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x1, y1, x2, y2);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    pn.pVariant[2].vt |= VT_BYREF;
    pn.pVariant[3].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    x1 = status ? pn.pVariant[3].lVal : 0;
    y1 = status ? pn.pVariant[2].lVal : 0;
    x2 = status ? pn.pVariant[1].lVal : 0;
    y2 = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}
int DmSoft_Com::SetWindowSize(int hwnd, int width, int height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWindowSize", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, width, height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetForegroundFocus()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetForegroundFocus", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetForegroundWindow()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetForegroundWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetMousePointWindow()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetMousePointWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetPointWindow(int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetPointWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetSpecialWindow(int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetSpecialWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWindow(int hwnd, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetWindowClass(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowClass", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetWindowTitle(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowTitle", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWindowText_(int hwnd, const wchar_t* title)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWindowText", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, title);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWindowTransparent(int hwnd, int title)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWindowTransparent", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, title);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWindowState(int hwnd, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWindowState", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWindowState(int hwnd, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowState", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWindowProcessId(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowProcessId", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetWindowProcessPath(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWindowProcessPath", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MoveWindow(int hwnd, int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MoveWindow", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SendString(int hwnd, const wchar_t* str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SendString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SendString2(int hwnd, const wchar_t* str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SendString2", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SendStringIme(const wchar_t* str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SendStringIme", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SendStringIme2(int hwnd, const wchar_t* str, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SendStringIme2", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, str, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SendPaste(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SendPaste", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------窗口操作-定义结束---------------
//---------------图色操作-定义开始---------------
CXText DmSoft_Com::AppendPicAddr(const wchar_t* pic_info, int addr, int size)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AppendPicAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_info, addr, size);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::Capture(int x1, int y1, int x2, int y2, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Capture", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CaptureGif(int x1, int y1, int x2, int y2, const wchar_t* file, int delay, int time)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CaptureGif", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, file, delay, time);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CaptureJpg(int x1, int y1, int x2, int y2, const wchar_t* file, int quality)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CaptureJpg", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, file, quality);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CapturePng(int x1, int y1, int x2, int y2, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CapturePng", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CapturePre(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CapturePre", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CmpColor(int x, int y, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CmpColor", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableDisplayDebug(int enable_debug)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableDisplayDebug", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable_debug);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnableGetColorByCapture(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableGetColorByCapture", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindColor(int x1, int y1, int x2, int y2, const wchar_t* color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindColor", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

int DmSoft_Com::FindColorBlock(int x1, int y1, int x2, int y2, const wchar_t* color, double sim, int count, int width, int height, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindColorBlock", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim, count, width, height, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::FindColorBlockEx(int x1, int y1, int x2, int y2, const wchar_t* color, double sim, int count, int width, int height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindColorBlockEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim, count, width, height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindColorEx(int x1, int y1, int x2, int y2, const wchar_t* color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindColorEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindMulColor(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindMulColor", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindMultiColor(int x1, int y1, int x2, int y2, const wchar_t* first_color, const wchar_t* offset_color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindMultiColor", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, first_color, offset_color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::FindMultiColorEx(int x1, int y1, int x2, int y2, const wchar_t* first_color, const wchar_t* offset_color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindMultiColorEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, first_color, offset_color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindPic(int x1, int y1, int x2, int y2, const wchar_t* pic_name, const wchar_t* delta_color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPic", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_name, delta_color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::FindPicEx(int x1, int y1, int x2, int y2, const wchar_t* pic_name, const wchar_t* delta_color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPicEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_name, delta_color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindPicExS(int x1, int y1, int x2, int y2, const wchar_t* pic_name, const wchar_t* delta_color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPicExS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_name, delta_color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindPicMem(int x1, int y1, int x2, int y2, const wchar_t* pic_info, const wchar_t* delta_color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPicMem", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_info, delta_color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::FindPicMemEx(int x1, int y1, int x2, int y2, const wchar_t* pic_info, const wchar_t* delta_color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPicMemEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_info, delta_color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindPicS(int x1, int y1, int x2, int y2, const wchar_t* pic_name, const wchar_t* delta_color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindPicS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_name, delta_color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

int DmSoft_Com::FindShape(int x1, int y1, int x2, int y2, const wchar_t* offset_color, double sim, int dir, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindShape", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, offset_color, sim, dir, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : 0;
    intY = status ? pn.pVariant[0].lVal : 0;
    return vResult;
}

CXText DmSoft_Com::FindShapeEx(int x1, int y1, int x2, int y2, const wchar_t* offset_color, double sim, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindShapeEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, offset_color, sim, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FreePic(const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FreePic", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetAveHSV(int x1, int y1, int x2, int y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetAveHSV", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetAveRGB(int x1, int y1, int x2, int y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetAveRGB", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetColor(int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetColor", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetColorBGR(int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetColorBGR", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetColorHSV(int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetColorHSV", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetColorNum(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetColorNum", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetPicSize(const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetPicSize", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetScreenData(int x1, int y1, int x2, int y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetScreenData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetScreenDataBmp(int x1, int y1, int x2, int y2, int& data, int& size)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetScreenDataBmp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, data, size);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    data = status ? pn.pVariant[1].intVal : 0;
    size = status ? pn.pVariant[0].intVal : 0;
    return vResult;
}

int DmSoft_Com::ImageToBmp(const wchar_t* pic_name, const wchar_t* bmp_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ImageToBmp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_name, bmp_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::IsDisplayDead(int x1, int y1, int x2, int y2, int t)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"IsDisplayDead", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, t);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LoadPic(const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LoadPic", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LoadPicByte(int addr, int size, const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LoadPicByte", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(addr, size, pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::MatchPicName(const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MatchPicName", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::BGR2RGB(const wchar_t* bgr_color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"BGR2RGB", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(bgr_color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::RGB2BGR(const wchar_t* rgb_color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RGB2BGR", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(rgb_color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetPicPwd(const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetPicPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------图色操作-定义结束---------------

//---------------文字识别-定义开始---------------
int DmSoft_Com::AddDict(int index, const wchar_t* dict_info)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AddDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, dict_info);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::ClearDict(int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ClearDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FetchWord(int x1, int y1, int x2, int y2, const wchar_t* color, const wchar_t* word)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FetchWord", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, word);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindStr(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::FindStrEx(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindStrExS(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrExS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FindStrFast(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrFast", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::FindStrFastEx(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrFastEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindStrFastExS(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrFastExS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindStrFastS(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrFastS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::FindStrS(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrS", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

int DmSoft_Com::FindStrWithFont(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, const wchar_t* font_name, int font_size, int flag, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrWithFont", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, font_name, font_size, flag, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::FindStrWithFontEx(int x1, int y1, int x2, int y2, const wchar_t* string, const wchar_t* color_format, double sim, const wchar_t* font_name, int font_size, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStrWithFontEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, string, color_format, sim, font_name, font_size, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetDict(int index, int font_index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, font_index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetDictCount(int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDictCount", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetDictInfo(const wchar_t* str, const wchar_t* font_name, int font_size, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDictInfo", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str, font_name, font_size, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetNowDict()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetNowDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetResultCount(const wchar_t* ret)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetResultCount", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(ret);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetResultPos(const wchar_t* ret, int index, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetResultPos", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(ret, index, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::ExcludePos(const wchar_t* all_pos, int type, int x1, int y1, int x2, int y2)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ExcludePos", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(all_pos, type, x1, y1, x2, y2);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindNearestPos(const wchar_t* all_pos, int type, int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindNearestPos", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(all_pos, type, x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::SortPosDistance(const wchar_t* all_pos, int type, int x, int y)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SortPosDistance", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(all_pos, type, x, y);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWordResultCount(const wchar_t* str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWordResultCount", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetWordResultPos(const wchar_t* str, int index, int& intX, int& intY)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWordResultPos", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str, index, intX, intY);
    pn.pVariant[0].vt |= VT_BYREF;
    pn.pVariant[1].vt |= VT_BYREF;
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    intX = status ? pn.pVariant[1].lVal : -1;
    intY = status ? pn.pVariant[0].lVal : -1;
    return vResult;
}

CXText DmSoft_Com::GetWordResultStr(const wchar_t* str, int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWordResultStr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str, index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetWords(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWords", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetWordsNoDict(int x1, int y1, int x2, int y2, const wchar_t* color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetWordsNoDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::Ocr(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Ocr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::OcrEx(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"OcrEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::OcrExOne(int x1, int y1, int x2, int y2, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"OcrExOne", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::OcrInFile(int x1, int y1, int x2, int y2, const wchar_t* pic_name, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"OcrInFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, pic_name, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SaveDict(int index, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SaveDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetColGapNoDict(int col_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetColGapNoDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(col_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetDict(int index, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetDictMem(int index, int addr, int size)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDictMem", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, addr, size);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetDictPwd(const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDictPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetExactOcr(int exact_ocr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetExactOcr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(exact_ocr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetMinColGap(int min_col_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetMinColGap", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(min_col_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetMinRowGap(int min_row_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetMinRowGap", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(min_row_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetRowGapNoDict(int row_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetRowGapNoDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(row_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWordGap(int word_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWordGap", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(word_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWordGapNoDict(int word_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWordGapNoDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(word_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWordLineHeight(int line_height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWordLineHeight", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(line_height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetWordLineHeightNoDict(int line_height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetWordLineHeightNoDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(line_height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::UseDict(int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"UseDict", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------文字识别-定义结束---------------

//---------------杂项函数-定义开始---------------
int DmSoft_Com::ActiveInputMethod(int hwnd, const wchar_t* input_method)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ActiveInputMethod", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, input_method);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CheckInputMethod(int hwnd, const wchar_t* input_method)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CheckInputMethod", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, input_method);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::FindInputMethod(const wchar_t* input_method)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindInputMethod", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(input_method);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EnterCri()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnterCri", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::InitCri()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"InitCri", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LeaveCri()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LeaveCri", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------杂项函数-定义结束---------------

long DmSoft_Com::DmGuard(int enable, const wchar_t* type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DmGuard", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

//---------------文件操作-定义开始---------------
int DmSoft_Com::CopyFile(const wchar_t* src_file, const wchar_t* dst_file, int over)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CopyFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(src_file, dst_file, over);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CreateFolder(const wchar_t* folder)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CreateFolder", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(folder);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DecodeFile(const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DecodeFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DeleteFile(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DeleteFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DeleteFolder(const wchar_t* folder)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DeleteFolder", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(folder);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DeleteIni(const wchar_t* section, const wchar_t* key, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DeleteIni", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DeleteIniPwd(const wchar_t* section, const wchar_t* key, const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DeleteIniPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::DownloadFile(const wchar_t* url, const wchar_t* save_file, int timeout)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DownloadFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(url, save_file, timeout);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::EncodeFile(const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EncodeFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumIniKey(const wchar_t* section, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumIniKey", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumIniKeyPwd(const wchar_t* section, const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumIniKeyPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumIniSection(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumIniSection", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::EnumIniSectionPwd(const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnumIniSectionPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetFileLength_(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetFileLength", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::IsFileExist(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"IsFileExist", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::MoveFile(const wchar_t* src_file, const wchar_t* dst_file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"MoveFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(src_file, dst_file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadFile(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadIni(const wchar_t* section, const wchar_t* key, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadIni", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadIniPwd(const wchar_t* section, const wchar_t* key, const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadIniPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::SelectDirectory()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SelectDirectory", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::SelectFile()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SelectFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteFile(const wchar_t* file, const wchar_t* content)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file, content);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteIni(const wchar_t* section, const wchar_t* key, const wchar_t* value, const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteIni", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, value, file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteIniPwd(const wchar_t* section, const wchar_t* key, const wchar_t* value, const wchar_t* file, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteIniPwd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(section, key, value, file, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------文件操作-定义结束---------------

//---------------系统操作-定义开始---------------
int DmSoft_Com::Beep(int f, int duration)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Beep", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(f, duration);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::CheckFontSmooth()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CheckFontSmooth", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::EnableFontSmooth()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"EnableFontSmooth", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::DisableFontSmooth()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DisableFontSmooth", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::Delay(int mis)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Delay", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(mis);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::Delays(int mis_min, int mis_max)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Delays", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(mis_min, mis_max);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::DisablePowerSave()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DisablePowerSave", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::DisableScreenSave()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DisableScreenSave", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::ExitOs(int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ExitOs", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetDir(int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDir", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetDiskSerial()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDiskSerial", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetDisplayInfo()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetDisplayInfo", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetMachineCode()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetMachineCode", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetMachineCodeNoMac()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetMachineCodeNoMac", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetNetTime()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetNetTime", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetNetTimeByIp(const wchar_t* ip)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetNetTimeByIp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(ip);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::GetOsType()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetOsType", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::GetScreenDepth()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetScreenDepth", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::GetScreenHeight()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetScreenHeight", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::GetScreenWidth()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetScreenWidth", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::GetTime()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetTime", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::Is64Bit()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Is64Bit", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::RunApp(const wchar_t* app_path, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"RunApp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(app_path, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
CXText DmSoft_Com::GetClipboard()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetClipboard", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::SetClipboard(const wchar_t* value)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetClipboard", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(value);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::SetDisplayAcceler(int level)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetDisplayAcceler", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(level);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::SetScreen(int width, int height, int depth)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetScreen", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(width, height, depth);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::CheckUAC()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CheckUAC", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::SetUAC(int enable)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetUAC", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(enable);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::Play(const wchar_t* media_file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Play", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(media_file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
int DmSoft_Com::Stop(int id)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Stop", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(id);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------系统操作-定义结束---------------

//---------------内存操作-定义开始---------------
CXText DmSoft_Com::DoubleToData(double value)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"DoubleToData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(value);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FloatToData(float value)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FloatToData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(value);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::IntToData(int value, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"IntToData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(value, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::StringToData(const wchar_t* value, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"StringToData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(value, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindData(int hwnd, const wchar_t* addr_range, const wchar_t* data)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, data);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindDataEx(int hwnd, const wchar_t* addr_range, const wchar_t* data, int step, int multi_thread, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindDataEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, data, step, multi_thread, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindDouble(int hwnd, const wchar_t* addr_range, double double_value_min, double double_value_max)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindDouble", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, double_value_min, double_value_max);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindDoubleEx(int hwnd, const wchar_t* addr_range, double double_value_min, double double_value_max, int step, int multi_thread, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindDoubleEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, double_value_min, double_value_max, step, multi_thread, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindFloat(int hwnd, const wchar_t* addr_range, float float_value_min, float float_value_max)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindFloat", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, float_value_min, float_value_max);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindFloatEx(int hwnd, const wchar_t* addr_range, float float_value_min, float float_value_max, int step, int multi_thread, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindFloatEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, float_value_min, float_value_max, step, multi_thread, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindInt(int hwnd, const wchar_t* addr_range, int int_value_min, int int_value_max, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindInt", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, int_value_min, int_value_max, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindIntEx(int hwnd, const wchar_t* addr_range, int int_value_min, int int_value_max, int type, int step, int multi_thread, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindIntEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, int_value_min, int_value_max, type, step, multi_thread, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindString(int hwnd, const wchar_t* addr_range, const wchar_t* string_value, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, string_value, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FindStringEx(int hwnd, const wchar_t* addr_range, const wchar_t* string_value, int type, int step, int multi_thread, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FindStringEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr_range, string_value, type, step, multi_thread, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FreeProcessMemory(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FreeProcessMemory", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::GetCommandLine(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetCommandLine", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::GetModuleBaseAddr(int hwnd, int module)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"GetModuleBaseAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, module);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadData(int hwnd, const wchar_t* addr, int len)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, len);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadDataAddr(int hwnd, int addr, int len)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadDataAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, len);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

double DmSoft_Com::ReadDouble(int hwnd, const wchar_t* addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadDouble", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

double DmSoft_Com::ReadDoubleAddr(int hwnd, int addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadDoubleAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

float DmSoft_Com::ReadFloat(int hwnd, const wchar_t* addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadFloat", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

float DmSoft_Com::ReadFloatAddr(int hwnd, int addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadFloatAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::ReadInt(int hwnd, const wchar_t* addr, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadInt", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::ReadIntAddr(int hwnd, int addr, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadIntAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadString(int hwnd, const wchar_t* addr, int type, int len)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, len);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::ReadStringAddr(int hwnd, int addr, int type, int len)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"ReadStringAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, len);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetMemoryFindResultToFile(const wchar_t* file)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetMemoryFindResultToFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::SetMemoryHwndAsProcessId(int en)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"SetMemoryHwndAsProcessId", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(en);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::TerminateProcess(int pid)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"TerminateProcess", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(pid);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::VirtualAllocEx(int hwnd, int addr, int size, int type)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"VirtualAllocEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, size, type);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::VirtualFreeEx(int hwnd, int addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"VirtualFreeEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::VirtualProtectEx(int hwnd, int addr, int size, int type, int old_protect)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"VirtualProtectEx", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, size, type, old_protect);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteData(int hwnd, const wchar_t* addr, const wchar_t* data)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteData", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, data);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteDataAddr(int hwnd, int addr, const wchar_t* data)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteDataAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, data);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteDouble(int hwnd, const wchar_t* addr, double v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteDouble", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteDoubleAddr(int hwnd, int addr, double v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteDoubleAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteFloat(int hwnd, const wchar_t* addr, float v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteFloat", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteFloatAddr(int hwnd, int addr, float v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteFloatAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteInt(int hwnd, const wchar_t* addr, int type, int v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteInt", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteIntAddr(int hwnd, int addr, int type, int v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteIntAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteString(int hwnd, const wchar_t* addr, int type, const wchar_t* v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::WriteStringAddr(int hwnd, int addr, int type, const wchar_t* v)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"WriteStringAddr", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, addr, type, v);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------内存操作-定义结束---------------

//---------------汇编函数-定义开始---------------
int DmSoft_Com::AsmAdd(const wchar_t* asm_ins)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AsmAdd", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(asm_ins);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AsmCall(int hwnd, int mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AsmCall", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AsmClear()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AsmClear", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::AsmCode(int base_addr)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AsmCode", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(base_addr);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::Assemble(const wchar_t* asm_code, int base_addr, int is_upper)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"Assemble", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(asm_code, base_addr, is_upper);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

//---------------汇编函数-定义结束---------------

//---------------自绘函数-定义开始---------------
int DmSoft_Com::CreateFoobarCustom(int hwnd, int x, int y, const wchar_t* pic_name, const wchar_t* trans_color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CreateFoobarCustom", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, pic_name, trans_color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CreateFoobarEllipse(int hwnd, int x, int y, int w, int h)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CreateFoobarEllipse", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, w, h);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CreateFoobarRect(int hwnd, int x, int y, int w, int h)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CreateFoobarRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, w, h);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::CreateFoobarRoundRect(int hwnd, int x, int y, int w, int h, int rw, int rh)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"CreateFoobarRoundRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, w, h, rw, rh);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarClearText(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarClearText", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarClose(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarClose", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarDrawLine(int hwnd, int x1, int y1, int x2, int y2, const wchar_t* color, int style, int width)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarDrawLine", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x1, y1, x2, y2, color, style, width);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarDrawPic(int hwnd, int x, int y, const wchar_t* pic_name, const wchar_t* trans_color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarDrawPic", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, pic_name, trans_color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarDrawText(int hwnd, int x, int y, int w, int h, const wchar_t* text, const wchar_t* color, int align)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarDrawText", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, w, h, text, color, align);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarFillRect(int hwnd, int x1, int y1, int x2, int y2, const wchar_t* color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarFillRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x1, y1, x2, y2, color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarLock(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarLock", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarPrintText(int hwnd, const wchar_t* text, const wchar_t* color)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarPrintText", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, text, color);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarSetFont(int hwnd, const wchar_t* font_name, int size, int flag)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarSetFont", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, font_name, size, flag);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarSetSave(int hwnd, const wchar_t* file, int enable, const wchar_t* header)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarSetSave", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, file, enable, header);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarSetTrans(int hwnd, int is_trans, const wchar_t* color, double sim)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarSetTrans", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, is_trans, color, sim);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarStartGif(int hwnd, int x, int y, const wchar_t* pic_name, int repeat_limit, int delay)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarStartGif", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, pic_name, repeat_limit, delay);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarStopGif(int hwnd, int x, int y, const wchar_t* pic_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarStopGif", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, pic_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarTextLineGap(int hwnd, int line_gap)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarTextLineGap", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, line_gap);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarTextPrintDir(int hwnd, int dir)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarTextPrintDir", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, dir);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarTextRect(int hwnd, int x, int y, int w, int h)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarTextRect", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd, x, y, w, h);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarUnlock(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarUnlock", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FoobarUpdate(int hwnd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FoobarUpdate", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(hwnd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------汇编函数-定义开始---------------

//---------------答题函数-定义开始---------------
int DmSoft_Com::FaqCancel()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqCancel", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqCapture(int x1, int y1, int x2, int y2, int quality, int delay, int time)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqCapture", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, quality, delay, time);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqCaptureFromFile(int x1, int y1, int x2, int y2, const wchar_t* file, int quality)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqCaptureFromFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, file, quality);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqCaptureString(const wchar_t* str)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqCaptureString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(str);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FaqFetch()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqFetch", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqGetSize(int handle)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqGetSize", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(handle);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqIsPosted()
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqIsPosted", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn;
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::FaqPost(const wchar_t* server, int handle, int request_type, int time_out)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqPost", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(server, handle, request_type, time_out);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::FaqSend(const wchar_t* server, int handle, int request_type, int time_out)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"FaqSend", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(server, handle, request_type, time_out);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}
//---------------答题函数-定义结束---------------

//---------------AIYOLO-定义开始---------------
CXText DmSoft_Com::AiYoloDetectObjects(int x1, int y1, int x2, int y2, float prob, float iou)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloDetectObjects", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, prob, iou);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloDetectObjectsToDataBmp(int x1, int y1, int x2, int y2, float prob, float iou, int& data, int& size, long mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloDetectObjectsToDataBmp", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, prob, iou, data, size, mode);
    pn.pVariant[1].vt |= VT_BYREF;
    pn.pVariant[2].vt |= VT_BYREF;
    spDisp.Invoke(dispatch_id, pn, vResult);
    auto status = SUCCEEDED(spDisp.Invoke(dispatch_id, pn, vResult));
    data = status ? pn.pVariant[2].lVal : 0;
    size = status ? pn.pVariant[1].lVal : 0;
    return vResult;
}

int DmSoft_Com::AiYoloDetectObjectsToFile(long x1, long y1, long x2, long y2, float prob, float iou, const wchar_t* file_name, long mode)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloDetectObjectsToFile", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(x1, y1, x2, y2, prob, iou, file_name, mode);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloFreeModel(int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloFreeModel", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::AiYoloObjectsToString(const wchar_t* objects)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloObjectsToString", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(objects);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloSetModel(int index, const wchar_t* file_name, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloSetModel", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, file_name, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloSetModelMemory(int index, int addr, int size, const wchar_t* pwd)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloSetModelMemory", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index, addr, size, pwd);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloSetVersion(const wchar_t* Ver)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloSetVersion", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(Ver);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

CXText DmSoft_Com::AiYoloSortsObjects(const wchar_t* objects, long height)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloSortsObjects", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(objects, height);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::AiYoloUseModel(int index)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"AiYoloUseModel", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(index);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LoadAi(const wchar_t* file_name)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LoadAi", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(file_name);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

int DmSoft_Com::LoadAiMemory(int addr, int size)
{
    static DISPID dispatch_id = -1;
    MyDispatchDriver spDisp(mObj);
    if (dispatch_id == -1) {
        spDisp.GetIDOfName(L"LoadAiMemory", &dispatch_id);
        if (dispatch_id == -1)
            return NULL;
    }
    MyVariant vResult;
    MyVariants pn(addr, size);
    spDisp.Invoke(dispatch_id, pn, vResult);
    return vResult;
}

//---------------AIYOLO-定义结束---------------