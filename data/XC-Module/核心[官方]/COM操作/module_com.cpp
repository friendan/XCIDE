#include "module_com.h"

CXComVariant::CXComVariant()
{
	::VariantInit(this);
}
CXComVariant::CXComVariant(_variant_t&& variant) : _variant_t(variant)
{
}
CXComVariant::CXComVariant(const _variant_t& variant) : _variant_t(variant)
{
}
CXComVariant::CXComVariant(const CXComVariant& variant) : _variant_t(variant)
{
}
CXComVariant::CXComVariant(LONG* vale_) : _variant_t()
{
	this->plVal = vale_;
	this->vt = VT_I4;
}
CXComVariant::operator CXText() const {
	if (VT_BSTR == vt)
		return bstrVal;
	return L"";
}
CXComVariant::operator CXTextA() const {
	if (VT_BSTR == vt)
		return (wchar_t*)bstrVal;
	return "";
}
CXComVariant::operator const wchar_t* () const {
	if (VT_BSTR == vt)
		return (const wchar_t*)bstrVal;
	return L"";
}

//----------------------------------------
void CXComVariant::operator=(LONG* vale_) {
	if (this->vt != (VT_I4 | VT_BYREF))
		Clear();
	this->plVal = vale_;
	this->vt = VT_I4 | VT_BYREF;
}
void CXComVariant::operator=(int* vale_) {
	if (this->vt == (VT_I4 | VT_BYREF))
		Clear();
	this->pintVal = vale_;
	this->vt = VT_I4 | VT_BYREF;
}
void CXComVariant::operator=(BSTR* pSrc) {
	if (this->vt != (VT_BSTR | VT_BYREF))
		Clear();
	this->pbstrVal = pSrc;
	this->vt = VT_BSTR | VT_BYREF;
}

void CXComVariant::operator=(bool boolSrc)
{
	if (this->vt == VT_BOOL)
	{
		V_BOOL(this) = (boolSrc ? VARIANT_TRUE : VARIANT_FALSE);
	}else if (this->vt == (VT_BOOL | VT_BYREF))
	{
		*V_BOOLREF(this) = (boolSrc ? VARIANT_TRUE : VARIANT_FALSE);
	} else
	{
		Clear();
		V_VT(this) = VT_BOOL;
		V_BOOL(this) = (boolSrc ? VARIANT_TRUE : VARIANT_FALSE);
	}
}

void CXComVariant::operator=(short sSrc)
{
	if (this->vt == VT_I2)
	{
		V_I2(this) = sSrc;
	} if (this->vt == VT_BOOL)
	{
		V_BOOL(this) = (sSrc ? VARIANT_TRUE : VARIANT_FALSE);
	} else if (this->vt == (VT_I2 | VT_BYREF))
	{
		*V_I2REF(this) = sSrc;
	} else
	{
		Clear();
		V_VT(this) = VT_I2;
		V_BOOL(this) = sSrc;
	}
}

void CXComVariant::operator=(long lSrc)
{
	if (V_VT(this) == VT_I4)
	{
		V_I4(this) = lSrc;
	} else if (V_VT(this) == VT_ERROR)
	{
		V_ERROR(this) = lSrc;
	} else if (V_VT(this) == VT_BOOL)
	{
		V_BOOL(this) = (lSrc ? VARIANT_TRUE : VARIANT_FALSE);
	} else  if (V_VT(this) == (VT_I4 | VT_BYREF))
	{
		*V_I4REF(this) = lSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_I4;
		V_I4(this) = lSrc;
	}
}

void CXComVariant::operator=(float fltSrc)
{
	if (V_VT(this) == VT_R4)
	{
		V_R4(this) = fltSrc;
	} else if (V_VT(this) == (VT_R4 | VT_BYREF))
	{
		*V_R4REF(this) = fltSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_R4;
		V_R4(this) = fltSrc;
	}
}

void CXComVariant::operator=(double dblSrc)
{
	if (V_VT(this) == VT_R8) 
	{
		V_R8(this) = dblSrc;
	} else if (V_VT(this) == VT_DATE)
	{
		V_DATE(this) = dblSrc;
	} else if (V_VT(this) == (VT_R8 | VT_BYREF))
	{
		*V_DATEREF(this) = dblSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_R8;
		V_R8(this) = dblSrc;
	}
}
void CXComVariant::operator=(const CY& cySrc)
{
	if (V_VT(this) == VT_CY)
	{
		V_CY(this) = cySrc;
	} else if (V_VT(this) == (VT_CY | VT_BYREF))
	{
		*V_CYREF(this) = cySrc;
	}else
	{
		Clear();
		V_VT(this) = VT_CY;
		V_CY(this) = cySrc;
	}
}

void CXComVariant::operator=(BYTE bSrc)
{
	if (V_VT(this) == VT_UI1)
	{
		V_UI1(this) = bSrc;
	} else if (V_VT(this) == (VT_UI1 | VT_BYREF))
	{
		*V_UI1REF(this) = bSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_UI1;
		V_UI1(this) = bSrc;
	}
}

void CXComVariant::operator=(char cSrc)
{
	if (V_VT(this) == VT_I1)
	{
		V_I1(this) = cSrc;
	} else if (V_VT(this) == (VT_I1 | VT_BYREF))
	{
		*V_I1REF(this) = cSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_I1;
		V_I1(this) = cSrc;
	}
}

void CXComVariant::operator=(unsigned short usSrc)
{
	if (V_VT(this) == VT_UI2)
	{
		V_UI2(this) = usSrc;
	} else if (V_VT(this) == (VT_UI2 | VT_BYREF))
	{
		*V_UI2REF(this) = usSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_UI2;
		V_UI2(this) = usSrc;
	}
}

void CXComVariant::operator=(unsigned long ulSrc)
{
	if (V_VT(this) == VT_UI4)
	{
		V_UI4(this) = ulSrc;
	} else if (V_VT(this) == (VT_UI4 | VT_BYREF))
	{
		*V_UI4REF(this) = ulSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_UI4;
		V_UI4(this) = ulSrc;
	}
}

void CXComVariant::operator=(int iSrc)
{
	if (V_VT(this) == VT_INT)
	{
		V_INT(this) = iSrc;
	} else if (V_VT(this) == (VT_INT | VT_BYREF))
	{
		*V_INTREF(this) = iSrc;
	}
#if 1
	else if (V_VT(this) == (VT_BOOL))
	{
		V_BOOL(this) = (iSrc ? VARIANT_TRUE : VARIANT_FALSE);
	}else if (V_VT(this) == (VT_BOOL | VT_BYREF))
	{
		*V_BOOLREF(this) = (iSrc ? VARIANT_TRUE : VARIANT_FALSE);
	}
#endif
	else
	{
		Clear();
		V_VT(this) = VT_INT;
		V_INT(this) = iSrc;
	}
}
void CXComVariant::operator=(unsigned int uiSrc)
{
	if (V_VT(this) == VT_UINT)
	{
		V_UINT(this) = uiSrc;
	} else if (V_VT(this) == (VT_UINT | VT_BYREF))
	{
		*V_UINTREF(this) = uiSrc;
	}else
	{
		Clear();
		V_VT(this) = VT_UINT;
		V_UINT(this) = uiSrc;
	}
}
void CXComVariant::operator=(__int64 i8Src)
{
	if (V_VT(this) == VT_I8)
	{
		V_I8(this) = i8Src;
	} else if (V_VT(this) == (VT_I8 | VT_BYREF))
	{
		*V_I8REF(this) = i8Src;
	}else
	{
		Clear();
		V_VT(this) = VT_I8;
		V_I8(this) = i8Src;
	}
}

void CXComVariant::operator=(unsigned __int64 ui8Src)
{
	if (V_VT(this) == VT_UI8)
	{
		V_UI8(this) = ui8Src;
	} else if (V_VT(this) == (VT_UI8 | VT_BYREF))
	{
		*V_UI8REF(this) = ui8Src;
	}else
	{
		Clear();
		V_VT(this) = VT_UI8;
		V_UI8(this) = ui8Src;
	}
}

BOOL CXComVariant::IsEmpty() const {
	return (VT_EMPTY == vt) ? TRUE : FALSE;
}

unsigned short CXComVariant::GetType() {
	return vt;
}

void CXComVariant::ChangeType(unsigned short nVarType) {
	_variant_t::ChangeType(nVarType, NULL);
}

void _xcl_comVarToText(CXText* text_, const class CXComVariant* pComVar)
{
	*text_ = (const wchar_t*)(*pComVar);
}

////////////////////////////////////////////////////////
CXComObject::CXComObject(IUnknown* pUnknown)
{
	SetObject(pUnknown);
}

CXComObject::CXComObject(const CXComVariant& variant)
{
	if (VT_UNKNOWN == variant.vt || VT_DISPATCH== variant.vt)
	{
		IUnknown* pUnknown = variant.punkVal;
		SetObject(pUnknown);
	}
}

void CXComObject::Clear()
{
	if(m_pUnknown) m_pUnknown.Release();
	if (m_pDispatch) m_pDispatch.Release();
}
BOOL CXComObject::Create(const wchar_t* pName)
{
	CLSID clsid;
	if (FALSE == GetCLSID(pName, clsid))
		return FALSE;

	IUnknownPtr pUnknown;
	m_hResult = CoCreateInstance(clsid, NULL, (CLSCTX_ALL | CLSCTX_REMOTE_SERVER), IID_IUnknown, (void**)&pUnknown);
	if (m_hResult == E_INVALIDARG)
		m_hResult = CoCreateInstance(clsid, NULL, (CLSCTX_ALL & ~CLSCTX_REMOTE_SERVER), IID_IUnknown, (void**)&pUnknown);
	if (FAILED(m_hResult))
		return FALSE;

	if (FAILED(OleRun(pUnknown)))
		return FALSE;
	
	Clear();
	m_pUnknown = pUnknown;
	m_hResult = m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	return TRUE;
}

BOOL CXComObject::QueryInterface(const wchar_t* pName)
{
	if (NULL == m_pUnknown)
		return FALSE;

	CLSID clsid;
	if (FALSE == GetCLSID(pName, clsid))
		return FALSE;

	IUnknownPtr pUnknown;
	m_hResult = m_pUnknown->QueryInterface(clsid, (void**)&pUnknown);
	if (FAILED(m_hResult))
		return FALSE;

	Clear();
	m_pUnknown = pUnknown;
	m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	return TRUE;
}

IUnknown* CXComObject::QueryInterfaceObject(const wchar_t* pName)
{
	if (NULL == m_pUnknown)
		return FALSE;

	CLSID clsid;
	if (FALSE == GetCLSID(pName, clsid))
		return FALSE;

	IUnknownPtr pUnknown;
	m_hResult = m_pUnknown->QueryInterface(clsid, (void**)&pUnknown);
	if (FAILED(m_hResult))
		return FALSE;
	return pUnknown;
}

BOOL CXComObject::GetActiveObject(const wchar_t* pName)
{
	CLSID clsid;
	if (FALSE == GetCLSID(pName, clsid))
		return FALSE;

	IUnknownPtr pUnknown;
	m_hResult = ::GetActiveObject(clsid, NULL, &pUnknown);
	if (FAILED(m_hResult))
		return FALSE;

	Clear();
	m_pUnknown = pUnknown;
	m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	return TRUE;
}

void CXComObject::SetObject(IUnknown* pUnknown)
{
	Clear();
	if (pUnknown)
	{
		m_pUnknown = pUnknown;
		m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	}
}

IUnknown* CXComObject::GetObject() const
{
	return m_pUnknown;
}

BOOL CXComObject::CreatePicDispObject(const HBITMAP hBitmap)
{
	if (hBitmap == NULL)
		return FALSE;

	const HBITMAP hCloneBitmap = (HBITMAP)::CopyImage(hBitmap, IMAGE_BITMAP, 0, 0, 0);
	if (hCloneBitmap == NULL)
		return FALSE;

	PICTDESC desc = {0};
	desc.cbSizeofstruct = sizeof(desc);
	desc.picType = PICTYPE_BITMAP;
	desc.bmp.hbitmap = hCloneBitmap;

	IPictureDispPtr pPictureDisp;
	if (FAILED(OleCreatePictureIndirect(&desc, IID_IPictureDisp, TRUE, (void**)&pPictureDisp)))
	{
		::DeleteObject(hCloneBitmap);
		return FALSE;
	}

	Clear();
	m_pUnknown = pPictureDisp;
	m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	return TRUE;
}

BOOL CXComObject::GetPicDispData(CXBytes& memResult)
{
	if (m_pUnknown == NULL)
		return FALSE;

	IPicturePtr pPicture;
	IStreamPtr  pStream;
	if (FAILED(m_pUnknown->QueryInterface(IID_IPicture, (void**)&pPicture)) ||
		FAILED(CreateStreamOnHGlobal(NULL, TRUE, &pStream)))
	{
		return FALSE;
	}

	LONG lSize = 0;
	if (FAILED(pPicture->SaveAsFile(pStream, TRUE, &lSize)) || lSize <= 0)
		return FALSE;

	LARGE_INTEGER nDisplacement;
	nDisplacement.QuadPart = 0;
	pStream->Seek(nDisplacement, STREAM_SEEK_SET, NULL);

	ULONG ulRead;
	if (SUCCEEDED(pStream->Read(memResult.resize((INT)lSize), (ULONG)lSize, &ulRead)) && ulRead == (ULONG)lSize)
		return TRUE;
	else
		memResult.clear();
	return FALSE;
}

BOOL CXComObject::CreateFontDispObject(const HFONT hFont)
{
	if (NULL == hFont) return FALSE;

	LOGFONT infFont;
	if (0 == ::GetObject(hFont, sizeof(LOGFONT), &infFont))
		return FALSE;

	FONTDESC desc = {0};
	desc.cbSizeofstruct = sizeof(desc);
	desc.lpstrName = (LPOLESTR)infFont.lfFaceName;
	desc.sWeight = (SHORT)infFont.lfWeight;
	desc.sCharset = (SHORT)infFont.lfCharSet;
	desc.fItalic = (BOOL)infFont.lfItalic;
	desc.fUnderline = (BOOL)infFont.lfUnderline;
	desc.fStrikethrough = (BOOL)infFont.lfStrikeOut;
	DoubleToCurrency(DoubleFontDpSize2Pt((double)infFont.lfHeight), &desc.cySize);

	IFontDispPtr pFontDisp;
	if (FAILED(OleCreateFontIndirect(&desc, IID_IFontDisp, (void**)&pFontDisp)))
		return FALSE;

	Clear();
	m_pUnknown = pFontDisp;
	m_pUnknown->QueryInterface(IID_IDispatch, (void**)&m_pDispatch);
	return TRUE;
}

HFONT CXComObject::CreateFontFromDispData()
{
	if (m_pUnknown == NULL) return NULL;

	IFontPtr pFont;
	HFONT hFont;
	CY size;
	if (FAILED(m_pUnknown->QueryInterface(IID_IFont, (void**)&pFont)) ||
		FAILED(pFont->get_hFont(&hFont)) || FAILED(pFont->get_Size(&size)))
	{
		return NULL;
	}

	LOGFONT infFont;
	if (::GetObject(hFont, sizeof(LOGFONT), &infFont) != 0)
	{
		infFont.lfHeight = -(INT)(fabs(DoubleFontPtSize2Dp(CurrencyToDouble(size))) + 0.5);
		return CreateFontIndirect(&infFont);
	}
	return NULL;
}

BOOL CXComObject::GetCLSID(const wchar_t* pName, CLSID &clsid)
{ 
	if ('{' == *pName)
		m_hResult = CLSIDFromString(pName, &clsid);
	else
		m_hResult = CLSIDFromProgID(pName, &clsid);
	if (SUCCEEDED(m_hResult))
		return TRUE;
	return FALSE;
}

void CXComObject::DoubleToCurrency(const double db, CY* pcy)
{
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_R8;
	var.dblVal = db;

	::VariantChangeType(&var, &var, 0, VT_CY);
	*pcy = var.cyVal;

	VariantClear(&var);
}

double CXComObject::CurrencyToDouble(const CY& cy)
{
	VARIANT var;
	VariantInit(&var);
	var.vt = VT_CY;
	var.cyVal = cy;

	VariantChangeType(&var, &var, 0, VT_R8);
	const double db = var.dblVal;

	VariantClear(&var);
	return db;
}

double CXComObject::DoubleFontPtSize2Dp(const double dFontPtSize)
{
	const HDC hDC = ::GetDC(NULL);
	const double dbDpSize = fabs(dFontPtSize) * (double)::GetDeviceCaps(hDC, LOGPIXELSY) / 72.0;
	::ReleaseDC(NULL, hDC);

	return dbDpSize;
}

double CXComObject::DoubleFontDpSize2Pt(const double dFontDpSize)
{
	const HDC hDC = ::GetDC(NULL);
	const int npLogY = ::GetDeviceCaps(hDC, LOGPIXELSY);
	::ReleaseDC(NULL, hDC);

	return (npLogY != 0 ? fabs(dFontDpSize) * 72.0 / (double)npLogY : 0);
}

CXComVariant CXComObject::Get(const wchar_t* pName)
{
	if (NULL == m_pDispatch) return CXComVariant();

	DISPID dispid;
	LPOLESTR szMember = (LPOLESTR)pName;
	m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(m_hResult))
		return CXComVariant();

	m_dispParams.rgvarg = NULL;
	m_dispParams.rgdispidNamedArgs = NULL;
	m_dispParams.cArgs = 0;
	m_dispParams.cNamedArgs = 0;

	VARIANT Result;
	::VariantInit(&Result);
	EXCEPINFO excepInfo;
	m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &m_dispParams, &Result, &excepInfo, NULL);
	if (SUCCEEDED(m_hResult))
	{
		CXComVariant ret(Result);
		VariantClear(&Result);
		return ret;
	}
	VariantClear(&Result);

	if (DISP_E_EXCEPTION == m_hResult)
		OutputDebugError(excepInfo);
	return CXComVariant();
}

BOOL CXComObject::Set(const wchar_t* pName)
{
	if (NULL == m_pDispatch) return FALSE;

	DISPID   dispid;
	LPOLESTR szMember = (LPOLESTR)pName;
	m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(m_hResult))
		return CXComVariant();

	m_dispParams.rgvarg = NULL;
	m_dispParams.rgdispidNamedArgs = NULL;
	m_dispParams.cArgs = 0;
	m_dispParams.cNamedArgs = 0;
	
	EXCEPINFO excepInfo;
	m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &m_dispParams, NULL, &excepInfo, NULL);
	if (SUCCEEDED(m_hResult))
		return TRUE;
	if (DISP_E_EXCEPTION == m_hResult)
		OutputDebugError(excepInfo);
	return FALSE;
}

CXComVariant CXComObject::Method(const wchar_t* pName)
{
	if (NULL == m_pDispatch) return CXComVariant();

	DISPID dispid;
	LPOLESTR szMember = (LPOLESTR)pName;
	m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(m_hResult))
		return CXComVariant();

	m_dispParams.rgvarg = NULL;
	m_dispParams.rgdispidNamedArgs = NULL;
	m_dispParams.cArgs = 0;
	m_dispParams.cNamedArgs = 0;

	VARIANT Result;
	::VariantInit(&Result);
	EXCEPINFO excepInfo;
	m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &m_dispParams, &Result, &excepInfo, NULL);
	if (SUCCEEDED(m_hResult))
	{
		CXComVariant ret(Result);
		::VariantClear(&Result);
		return ret;
	}
	::VariantClear(&Result);

	if (DISP_E_EXCEPTION == m_hResult)
		OutputDebugError(excepInfo);
	return CXComVariant();
}


///////////////////////////////////////////////////////////////////
CXComEventHandle::CXComEventHandle()
{
	m_nRefCount = 0;
	m_bAutoDestroy = TRUE;
}
CXComEventHandle::~CXComEventHandle()
{
// 	m_pUnknown->AddRef();
// 	int ref= m_pUnknown->Release();
// 
// 	wchar_t buf[1024] = {0};
// 	swprintf(buf, L"this=0x%08X, m_pUnknown=0x%08X, m_pIConnectionPoint=0x%08X, m_nRefCount=%d, ref=%d", 
// 		(int)this, (int)m_pUnknown.GetInterfacePtr(), (int)m_pIConnectionPoint.GetInterfacePtr(), m_nRefCount, ref);
// 	MessageBox(NULL, buf, L"DEBUG", 0);
	Clear();
}

HRESULT STDMETHODCALLTYPE CXComEventHandle::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == __uuidof(IUnknown))
	{
		*ppvObject =(IUnknown*)this;
	} else if (riid == __uuidof (IDispatch))
	{
		*ppvObject = (IDispatch*)this;
	} else if (m_IIDEventSource != IID_NULL && riid == m_IIDEventSource)
	{
		*ppvObject = (IDispatch*)this;
	}else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	this->AddRef();
	return S_OK;
}

ULONG STDMETHODCALLTYPE CXComEventHandle::AddRef(void)
{
	return InterlockedIncrement(&m_nRefCount);
}

ULONG STDMETHODCALLTYPE CXComEventHandle::Release(void)
{
	UINT  refCount = InterlockedDecrement(&m_nRefCount);
	if (m_bAutoDestroy)
	{
		if (refCount <= 0)
			delete this;
	}
	return refCount;
}

HRESULT STDMETHODCALLTYPE CXComEventHandle::GetTypeInfoCount(UINT* pctinfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CXComEventHandle::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CXComEventHandle::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CXComEventHandle::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	CXComVariant   retResult;
	if (pVarResult)
		retResult = pVarResult;
	if (pDispParams->cArgs > 0)
	{
		CXComVariant*  pArrayParams = new CXComVariant[pDispParams->cArgs];
		int index = 0;
		for (int i = pDispParams->cArgs - 1; i >= 0; i--)
		{
			pArrayParams[index] = pDispParams->rgvarg[i];
			index++;
		}
		OnEvent(dispIdMember, pArrayParams, pDispParams->cArgs, retResult);
		delete[] pArrayParams;
	} else
	{
		OnEvent(dispIdMember, NULL, 0, retResult);
	}
	if(pVarResult)
		::VariantCopy(pVarResult, &retResult);
	return S_OK;
}

void CXComEventHandle::OnEvent(int dispIdMember, CXComVariant* pArrayParams, int pArraycount,CXComVariant& retResult)
{
}

BOOL CXComEventHandle::BindEvent(CXComObject& comObj, const wchar_t* pEventIneterfaceName)
{
	IUnknownPtr pUnknow = comObj.GetObject();
	if (NULL == pUnknow) return FALSE;

	IID  iidEventSource;
	if (NULL == pEventIneterfaceName || 0 == *pEventIneterfaceName)
	{
		if (FindDefaultEventSource(pUnknow, &iidEventSource) == FALSE)
			return FALSE;
	} else
	{
		if (FALSE == GetCLSID(pEventIneterfaceName, iidEventSource))
			return FALSE;
	}
	return SetConnectionPoint(pUnknow, iidEventSource);
}

BOOL CXComEventHandle::SetConnectionPoint(IUnknown* pUnknown, const IID& riidEventSource)
{
	if (pUnknown == NULL || riidEventSource == IID_NULL)
		return FALSE;

	Clear();

	IConnectionPointContainerPtr pIConnectionPointContainer;
	if (SUCCEEDED(pUnknown->QueryInterface(IID_IConnectionPointContainer, (void**)&pIConnectionPointContainer)))
	{
		IConnectionPointPtr pIConnectionPoint;
		if (SUCCEEDED(pIConnectionPointContainer->FindConnectionPoint(riidEventSource, &pIConnectionPoint)))
		{
			m_IIDEventSource = riidEventSource;

			DWORD dwEventCookie;
			if (SUCCEEDED(pIConnectionPoint->Advise((IUnknown*)this, &dwEventCookie)))
			{
				m_pUnknown = pUnknown;
				m_pIConnectionPoint = pIConnectionPoint;
				m_dwEventCookie = dwEventCookie;
				return TRUE;
			}
			m_IIDEventSource = IID_NULL;
		}
	}
	return FALSE;
}

void CXComEventHandle::Clear()
{
	if (m_pIConnectionPoint)
	{
		m_pIConnectionPoint->Unadvise(m_dwEventCookie);
		m_pIConnectionPoint = NULL;
	}
	if (m_pUnknown)
	{
		m_pUnknown = NULL;
	}
	m_IIDEventSource = IID_NULL;
	m_dwEventCookie = 0;
}

CXText CXComEventHandle::GetName(int dispIdMember)
{
	CXText retName;
	IDispatchPtr pDispatch;
	HRESULT hr = m_pUnknown->QueryInterface(IID_IDispatch, (void**)&pDispatch);
	if (SUCCEEDED(hr))
	{
		UINT count_ = 0;
		hr = pDispatch->GetTypeInfoCount(&count_);
		if (SUCCEEDED(hr))
		{
			ITypeInfoPtr  typeInfo;
			hr = pDispatch->GetTypeInfo(0, 0, &typeInfo);
			if (SUCCEEDED(hr))
			{
				ITypeLibPtr typelib;
				UINT index = 0;
				hr = typeInfo->GetContainingTypeLib(&typelib, &index);
				if (SUCCEEDED(hr))
				{
					ITypeInfoPtr typeInfoEvent;
					hr = typelib->GetTypeInfoOfGuid(m_IIDEventSource, &typeInfoEvent);
					if (SUCCEEDED(hr))
					{
						TYPEATTR* attr = NULL;
						hr = typeInfoEvent->GetTypeAttr(&attr);
						if (SUCCEEDED(hr))
						{
							BSTR   _bstrArgNames[1];
							UINT   _ArgNames = 0;
							hr = typeInfoEvent->GetNames(dispIdMember, _bstrArgNames, 1, &_ArgNames);
							if (SUCCEEDED(hr))
							{
								retName = _bstrArgNames[0];
								::SysFreeString(_bstrArgNames[0]);
							}
							typeInfoEvent->ReleaseTypeAttr(attr);
						}

					}
				}
			}
		}
	}
	return retName;
}

BOOL CXComEventHandle::GetCLSID(const wchar_t* pName, CLSID& clsid)
{
	HRESULT m_hResult;
	if ('{' == *pName)
		m_hResult = CLSIDFromString(pName, &clsid);
	else
		m_hResult = CLSIDFromProgID(pName, &clsid);
	if (SUCCEEDED(m_hResult))
		return TRUE;
	return FALSE;
}

BOOL CXComEventHandle::FindDefaultEventSource(IUnknown* pUnknown, IID* pDefaultEventSource)
{
	if (NULL == pDefaultEventSource) return FALSE;
	*pDefaultEventSource = IID_NULL;
	if (pUnknown == NULL)	return FALSE;

	//从IProvideClassInfo2接口中查找
	IProvideClassInfo2Ptr pPCI2;
	if (SUCCEEDED(pUnknown->QueryInterface(IID_IProvideClassInfo2, (LPVOID*)&pPCI2)))
	{
		if (SUCCEEDED(pPCI2->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID, pDefaultEventSource)))
			return (IsEqualIID(*pDefaultEventSource, IID_NULL) == FALSE);
	}

	//从类信息中查找
	ITypeInfoPtr pClassInfo = NULL;
	HRESULT hrGetClassInfo = E_FAIL;

	IProvideClassInfoPtr pPCI;
	if (SUCCEEDED(pUnknown->QueryInterface(IID_IProvideClassInfo, (LPVOID*)&pPCI)))
	{
		hrGetClassInfo = pPCI->GetClassInfo(&pClassInfo);
	}
	if (FAILED(hrGetClassInfo) || pClassInfo == NULL)
	{
		IDispatchPtr pDispatch;
		if (SUCCEEDED(pUnknown->QueryInterface(IID_IDispatch, (LPVOID*)&pDispatch)))
		{
			hrGetClassInfo = pDispatch->GetTypeInfo(0, GetUserDefaultLCID(), &pClassInfo);
		}
	}
	if (SUCCEEDED(hrGetClassInfo) && pClassInfo != NULL)
	{
		LPTYPEATTR pClassAttr =NULL;
		if (SUCCEEDED(pClassInfo->GetTypeAttr(&pClassAttr)))
		{
			INT nFlags;
			HREFTYPE hRefType;
			for (UINT i = 0; i < pClassAttr->cImplTypes; i++)
			{
				if (SUCCEEDED(pClassInfo->GetImplTypeFlags(i, &nFlags)) &&
					((nFlags & (IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE | IMPLTYPEFLAG_FRESTRICTED)) == (IMPLTYPEFLAG_FDEFAULT | IMPLTYPEFLAG_FSOURCE)))
				{
					ITypeInfoPtr pEventInfo = NULL;
					if (SUCCEEDED(pClassInfo->GetRefTypeOfImplType(i, &hRefType)) &&
						SUCCEEDED(pClassInfo->GetRefTypeInfo(hRefType, &pEventInfo)))
					{
						LPTYPEATTR pEventAttr = NULL;
						if (SUCCEEDED(pEventInfo->GetTypeAttr(&pEventAttr)))
						{
							*pDefaultEventSource = pEventAttr->guid;
							pEventInfo->ReleaseTypeAttr(pEventAttr);
						}
					}
					break;
				}
			}
			pClassInfo->ReleaseTypeAttr(pClassAttr);
		}
	}

	//查找第一个事件接口
	if (IsEqualIID(*pDefaultEventSource, IID_NULL))
	{
		IConnectionPointContainerPtr pCPC;
		if (SUCCEEDED(pUnknown->QueryInterface(IID_IConnectionPointContainer, (LPVOID*)&pCPC)))
		{
			IEnumConnectionPointsPtr pECP;
			if (SUCCEEDED(pCPC->EnumConnectionPoints(&pECP)))
			{
				IConnectionPointPtr pCP;
				if (SUCCEEDED(pECP->Next(1, &pCP, NULL)))
				{
					if (FAILED(pCP->GetConnectionInterface(pDefaultEventSource)))
						*pDefaultEventSource = IID_NULL;
				}
			}
		}
	}
	return (IsEqualIID(*pDefaultEventSource, IID_NULL) == FALSE);
}
template<class T>
void mkValue_COM(T& strText, const CXComVariant& value_)
{
	switch (value_.vt)
	{
	case VT_BOOL: xcl_mkValue(strText, value_.boolVal); break;
	case VT_I1: xcl_mkValue(strText, value_.cVal); break;
	case VT_I2: xcl_mkValue(strText, value_.iVal); break;
	case VT_I4: xcl_mkValue(strText, value_.lVal); break;
	case VT_INT: xcl_mkValue(strText, value_.intVal); break;
	case VT_I8: xcl_mkValue(strText, value_.llVal);   break;
	case VT_UI1:  xcl_mkValue(strText, value_.bVal);	break;
	case VT_UI2: xcl_mkValue(strText, value_.uiVal);	break;
	case VT_UI4:  xcl_mkValue(strText, value_.ulVal);	break;
	case VT_UINT: xcl_mkValue(strText, value_.uintVal);	break;
	case VT_UI8: xcl_mkValue(strText, value_.ullVal);	break;
	case VT_BSTR:	xcl_mkValue(strText, (const wchar_t*)value_.bstrVal); break;
//	case VT_EMPTY: strText += (const wchar_t*)L"(空)";  break;
	case VT_DATE: xcl_mkValue(strText, value_.date); break;
//	case VT_DISPATCH: xcl_mkValue(strText, value_.pdispVal); break;
//	case VT_UNKNOWN:  xcl_mkValue(strText, value_.punkVal); break;
	case VT_CY: xcl_mkValue(strText, value_.cyVal.int64); break;
	case VT_ERROR:  xcl_mkValue(strText, value_.scode); break;
	case VT_R4: xcl_mkValue(strText, value_.fltVal); break;
	case VT_R8: xcl_mkValue(strText, value_.dblVal); break;
	}
}

void xcl_mkValue(CXText& strText, const CXComVariant& value_)
{
	if (VT_EMPTY == value_.vt)
	{
		strText += L"(空)";
	} else if (VT_DISPATCH == value_.vt)
	{
		strText += L"IDispatch(";
		xcl_mkValue(strText, value_.pdispVal);
		strText += L")";
	} else if (VT_UNKNOWN == value_.vt)
	{
		strText += L"IUnknown(";
		xcl_mkValue(strText, value_.pdispVal);
		strText += L")";
	} else
	{
		mkValue_COM(strText, value_);
	}
}

void xcl_mkValue(CXTextA& strText, const CXComVariant& value_)
{
	if (VT_EMPTY == value_.vt)
	{
		strText += "(空)";
	} else if (VT_DISPATCH == value_.vt)
	{
		strText += "IDispatch(";
		xcl_mkValue(strText, value_.pdispVal);
		strText += ")";
	} else if (VT_UNKNOWN == value_.vt)
	{
		strText += "IUnknown(";
		xcl_mkValue(strText, value_.pdispVal);
		strText += ")";
	} else
	{
		mkValue_COM(strText, value_);
	}
}

