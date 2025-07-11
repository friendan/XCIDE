#pragma once

class COleClientSiteMy : public  IOleClientSite, IOleInPlaceSite, IOleInPlaceFrame, IDispatch
{
public:
	COleClientSiteMy(HWINDOW hWindow)
	{
		m_nRefCount = 0;
		m_hWndParent = XWnd_GetHWND(hWindow);
		m_rect = { 100,100,400,400 };
		AddRef();
	}
	~COleClientSiteMy()
	{

	}
	int   m_nRefCount;
	HWND  m_hWndParent;
	RECT  m_rect;
	void SetRect(int x, int y, int cx, int cy)
	{
		m_rect = { x, y, x+ cx, y+cy };
	}
	//---------IOleClientSite
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR* __RPC_FAR* ppvObject)
	{
		*ppvObject = nullptr;
		if (riid == IID_IUnknown)
			*ppvObject = (IOleClientSite*)this;
		else if (riid == IID_IOleInPlaceSite)
			*ppvObject = (IOleInPlaceSite*)this;
		else if (riid == IID_IOleInPlaceUIWindow)
			*ppvObject = (IOleInPlaceUIWindow*)this;
		else if (riid == IID_IOleInPlaceFrame)
			*ppvObject = (IOleInPlaceFrame*)this;
		else if(riid == IID_IDispatch)
			*ppvObject = (IDispatch*)this;

		if (*ppvObject == nullptr)
			return E_NOINTERFACE;
		AddRef();
		return S_OK;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef(void){
		m_nRefCount++;
		return m_nRefCount;
	}
	virtual ULONG STDMETHODCALLTYPE Release(void){
		m_nRefCount--;
		if (m_nRefCount<=0)
		{
			delete this;
			return 0;
		}
		return m_nRefCount;
	}
	virtual HRESULT STDMETHODCALLTYPE SaveObject(void){
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetMoniker(
		/* [in] */ DWORD dwAssign,
		/* [in] */ DWORD dwWhichMoniker,
		/* [out] */ __RPC__deref_out_opt IMoniker** ppmk) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetContainer(/* [out] */ __RPC__deref_out_opt IOleContainer** ppContainer){
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE ShowObject(void){
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE OnShowWindow(	/* [in] */ BOOL fShow){
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout(void){
		return E_NOTIMPL;
	}
	//-----------IOleInPlaceSite
	virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void){
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void){
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE OnUIActivate(void){
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE GetWindowContext(
		/* [out] */ __RPC__deref_out_opt IOleInPlaceFrame** ppFrame,
		/* [out] */ __RPC__deref_out_opt IOleInPlaceUIWindow** ppDoc,
		/* [out] */ __RPC__out LPRECT lprcPosRect,
		/* [out] */ __RPC__out LPRECT lprcClipRect,
		/* [out][in] */ __RPC__inout LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		if (m_hWndParent == nullptr)
			return E_NOTIMPL;

		*ppFrame = (IOleInPlaceFrame*)this;
		*ppDoc = NULL;
		AddRef();
		//GetClientRect(m_hWndParent, lprcPosRect);
		//GetClientRect(m_hWndParent, lprcClipRect);
		*lprcPosRect = m_rect;   //相对于父坐标
		*lprcClipRect = m_rect; //客户区剪切坐标

		lpFrameInfo->cb = sizeof(OLEINPLACEFRAMEINFO);
		lpFrameInfo->fMDIApp = false;
		lpFrameInfo->hwndFrame = m_hWndParent;
		lpFrameInfo->haccel = nullptr;
		lpFrameInfo->cAccelEntries = 0;
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE Scroll(/* [in] */ SIZE scrollExtant){
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(/* [in] */ BOOL fUndoable) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE DiscardUndoState(void){
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(/* [in] */ __RPC__in LPCRECT lprcPosRect) {
		return E_NOTIMPL;
	}
	//---------IOleWindow
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(	/* [out] */ __RPC__deref_out_opt HWND* phwnd) {
		*phwnd = m_hWndParent;
		return S_OK;
	}
	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(	/* [in] */ BOOL fEnterMode) {
		return E_NOTIMPL;
	}

	//--------------------IOleInPlaceFrame
	virtual HRESULT STDMETHODCALLTYPE InsertMenus(
		/* [in] */ __RPC__in HMENU hmenuShared,
		/* [out][in] */ __RPC__inout LPOLEMENUGROUPWIDTHS lpMenuWidths) {
		return E_NOTIMPL;
	}
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetMenu(
		/* [in] */ __RPC__in HMENU hmenuShared,
		/* [in] */ __RPC__in HOLEMENU holemenu,
		/* [in] */ __RPC__in HWND hwndActiveObject) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE RemoveMenus(/* [in] */ __RPC__in HMENU hmenuShared) {
		return E_NOTIMPL;
	}
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetStatusText(	/* [unique][in] */ __RPC__in_opt LPCOLESTR pszStatusText) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE EnableModeless(/* [in] */ BOOL fEnable) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(	/* [in] */ __RPC__in LPMSG lpmsg,
		/* [in] */ WORD wID) {
		return E_NOTIMPL;
	}
	//-------------------IOleInPlaceUIWindow
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetBorder(/* [out] */ __RPC__out LPRECT lprectBorder) {
		return E_NOTIMPL;
	}
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE RequestBorderSpace(/* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths) {
		return E_NOTIMPL;
	}
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetBorderSpace(/* [unique][in] */ __RPC__in_opt LPCBORDERWIDTHS pborderwidths) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE SetActiveObject(
		/* [unique][in] */ __RPC__in_opt IOleInPlaceActiveObject* pActiveObject,
		/* [unique][string][in] */ __RPC__in_opt_string LPCOLESTR pszObjName) {
		return E_NOTIMPL;
	}
	//---------------IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(/* [out] */ __RPC__out UINT* pctinfo) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(/* [in] */ UINT iTInfo,/* [in] */ LCID lcid,/* [out] */ __RPC__deref_out_opt ITypeInfo** ppTInfo) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR* rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID* rgDispId) {
		return E_NOTIMPL;
	}

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr) {
		return E_NOTIMPL;
	}

};

class CGridppReportEventImpl : public _IGridppReportEvents
{
public:
	CGridppReportEventImpl() {
		m_event = NULL; m_nRefCount = 0;
	}
	~CGridppReportEventImpl() {
	}
	int   m_nRefCount;
	CIGridppReportEvents*   m_event;
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(/* [in] */ REFIID riid,/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
	{
		*ppvObject = NULL;
		if(riid == IID_IUnknown)
			*ppvObject = this;
		else if (riid == IID_IDispatch)
			*ppvObject = this;
		else if (riid == DIID__IGridppReportEvents)
			*ppvObject = this;
// 		else if (riid == DIID__IGRDisplayViewerEvents)
// 			*ppvObject = this;
// 		else if (riid == DIID__IGRPrintViewerEvents)
// 			*ppvObject = this;

		if (*ppvObject)
		{
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef(void) {
		m_nRefCount++;
		return m_nRefCount;
	}
	virtual ULONG STDMETHODCALLTYPE Release(void) {
		m_nRefCount--;
		if (m_nRefCount <= 0)
		{
			delete this;
			return 0;
		}
		return m_nRefCount;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT* pctinfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo** ppTInfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR* rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID* rgDispId) {
		return E_NOTIMPL;
	}
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
};


////////////////////////////////////////////////////////////
class CGRDisplayViewerEventImpl : public  _IGRDisplayViewerEvents
{
public:
	CGRDisplayViewerEventImpl() {
		m_event = NULL; m_nRefCount = 0;
	}
	~CGRDisplayViewerEventImpl() {
	}
	int   m_nRefCount;
	CIGRDisplayViewerEvents* m_event;
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(/* [in] */ REFIID riid,/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
	{
		*ppvObject = NULL;
		if (riid == IID_IUnknown)
			*ppvObject = this;
		else if (riid == IID_IDispatch)
			*ppvObject = this;
 		else if (riid == DIID__IGRDisplayViewerEvents)
 			*ppvObject = this;
		if (*ppvObject)
		{
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef(void) {
		m_nRefCount++;
		return m_nRefCount;
	}
	virtual ULONG STDMETHODCALLTYPE Release(void) {
		m_nRefCount--;
		if (m_nRefCount <= 0)
		{
			delete this;
			return 0;
		}
		return m_nRefCount;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT* pctinfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo** ppTInfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR* rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID* rgDispId) {
		return E_NOTIMPL;
	}
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
};


////////////////////////////////////////////////////////////
class CGRPrintViewerEventImpl : public  _IGRPrintViewerEvents
{
public:
	CGRPrintViewerEventImpl() {
		m_event = NULL; m_nRefCount = 0;
	}
	~CGRPrintViewerEventImpl() {
	}
	int   m_nRefCount;
	CIGRPrintViewerEvents* m_event;
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(/* [in] */ REFIID riid,/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject)
	{
		*ppvObject = NULL;
		if (riid == IID_IUnknown)
			*ppvObject = this;
		else if (riid == IID_IDispatch)
			*ppvObject = this;
		else if (riid == DIID__IGRDisplayViewerEvents)
			*ppvObject = this;

		if (*ppvObject)
		{
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	virtual ULONG STDMETHODCALLTYPE AddRef(void) {
		m_nRefCount++;
		return m_nRefCount;
	}
	virtual ULONG STDMETHODCALLTYPE Release(void) {
		m_nRefCount--;
		if (m_nRefCount <= 0)
		{
			delete this;
			return 0;
		}
		return m_nRefCount;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT* pctinfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo** ppTInfo) {
		return E_NOTIMPL;
	}
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR* rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID* rgDispId) {
		return E_NOTIMPL;
	}
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
};

