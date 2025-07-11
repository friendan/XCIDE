#include "module_GridppReport.h"
#include "event.h"

BOOL CIGridppReport::Create()
{
	//启动时增加程序对 COM 的支持
	HRESULT hr = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hr));

	IGridppReportPtr   m_pGridppReport;
	//创建报表主对象
	hr = m_pGridppReport.CreateInstance(__uuidof(GridppReport));
	ATLASSERT(m_pGridppReport != NULL);
	m_ptr = m_pGridppReport;
	return TRUE;
}

BOOL CIGridppReport::BindEvent(CIGridppReportEvents* pEvent)
{
	//https://www.cnblogs.com/ybqjymy/p/15137761.html
	CComPtr<IConnectionPointContainer> pCPC;
	CComPtr<IConnectionPoint> pCP;
	HRESULT hr = m_ptr->QueryInterface(__uuidof(IConnectionPointContainer), (void**)&pCPC);
	ATLASSERT(SUCCEEDED(hr));

	CGridppReportEventImpl* event_ = new CGridppReportEventImpl;
	event_->m_event = pEvent;
	hr = pCPC->FindConnectionPoint(__uuidof(_IGridppReportEvents), &pCP);
	ATLASSERT(SUCCEEDED(hr));

	DWORD  conn = 0;
	hr = pCP->Advise(event_, &conn);
	ATLASSERT(SUCCEEDED(hr));

	//return _com_dispatch_method(this, 0x5, DISPATCH_METHOD, VT_EMPTY, NULL, 
	//L"\x0003\x0008", ErrorID, (BSTR)ErrorMsg);
	//event_->RuntimeError(1, L"123");
	return TRUE;
}

BOOL CIGRDisplayViewer::BindEvent(CIGRDisplayViewerEvents* pEvent)
{
	CComPtr<IConnectionPointContainer> pCPC;
	CComPtr<IConnectionPoint> pCP;
	HRESULT hr = m_ptr->QueryInterface(__uuidof(IConnectionPointContainer), (void**)&pCPC);
	ATLASSERT(SUCCEEDED(hr));

	CGRDisplayViewerEventImpl* event_ = new CGRDisplayViewerEventImpl;
	event_->m_event = pEvent;
	hr = pCPC->FindConnectionPoint(__uuidof(_IGridppReportEvents), &pCP);
	ATLASSERT(SUCCEEDED(hr));

	DWORD  conn = 0;
	hr = pCP->Advise(event_, &conn);
	ATLASSERT(SUCCEEDED(hr));

	return TRUE;
}

BOOL CIGRPrintViewer::BindEvent(CIGRPrintViewerEvents* pEvent)
{
	CComPtr<IConnectionPointContainer> pCPC;
	CComPtr<IConnectionPoint> pCP;
	HRESULT hr = m_ptr->QueryInterface(__uuidof(IConnectionPointContainer), (void**)&pCPC);
	ATLASSERT(SUCCEEDED(hr));

	CGRPrintViewerEventImpl* event_ = new CGRPrintViewerEventImpl;
	event_->m_event = pEvent;
	hr = pCPC->FindConnectionPoint(__uuidof(_IGridppReportEvents), &pCP);
	ATLASSERT(SUCCEEDED(hr));

	DWORD  conn = 0;
	hr = pCP->Advise(event_, &conn);
	ATLASSERT(SUCCEEDED(hr));
	return TRUE;
}

BOOL CIGRDisplayViewer::Create(int x, int y, int cx, int cy, HWINDOW hWindow)
{
	HRESULT hr = S_OK;
	IClassFactory* pClassFactory = NULL;
	hr = CoGetClassObject(CLSID_GRDisplayViewer, 3, NULL, IID_IClassFactory, (void**)&pClassFactory);
	if (SUCCEEDED(hr))
	{
		IOleObject* pUnkControl = NULL;
		hr = pClassFactory->CreateInstance(NULL, __uuidof(IOleObject), (void**)&pUnkControl);
		if (SUCCEEDED(hr))
		{
			COleClientSiteMy* OleClientSite = new COleClientSiteMy(hWindow);
			hr = pUnkControl->SetClientSite(OleClientSite);
			if (SUCCEEDED(hr))
			{
				// 				LPPROVIDECLASSINFO2 pPCI2 = NULL;
				// 				IID piid;
				// 				if (SUCCEEDED(pUnkControl->QueryInterface(IID_IProvideClassInfo2, (LPVOID*)&pPCI2)))
				// 				{
				// 					hr = pPCI2->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID, &piid);
				// 					pPCI2->Release();
				// 				}
								//OleCreate()

				OleClientSite->SetRect(x, y, cx, cy);
				hr = pUnkControl->DoVerb(OLEIVERB_INPLACEACTIVATE, NULL, OleClientSite, 0, NULL, NULL);
				if (SUCCEEDED(hr))
				{
					hr = pUnkControl->QueryInterface(__uuidof(IGRDisplayViewer), (void**)&m_ptr);
					if (SUCCEEDED(hr))
					{
						//m_pDisplayViewer->Report = pGridppReport.m_ptr;// .m_pGridppReport;
					}
				}
				OleClientSite->Release();
			}
			pUnkControl->Release();
		}
		pClassFactory->Release();
	}
	if (SUCCEEDED(hr))
		return TRUE;
	return FALSE;
}

