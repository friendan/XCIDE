#include "module_GridppReport.h"
#include "event.h"

/* [local] */ HRESULT STDMETHODCALLTYPE CGridppReportEventImpl::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS* pDispParams,
	/* [out] */ VARIANT* pVarResult,
	/* [out] */ EXCEPINFO* pExcepInfo,
	/* [out] */ UINT* puArgErr)
{
#ifdef  XC_MODULE
	XTRACE(L"Invoke: %d \n", dispIdMember);
#endif
	if (NULL == m_event) {
		return E_NOTIMPL;
	}
	//CComPtr::_PtrClass
	switch (dispIdMember)
	{
	case DISPID_INITIALIZE: 
		if (m_event) m_event->OnInitialize(); 
		break;
	case DISPID_FETCHRECORD:if (m_event) m_event->OnFetchRecord(); break;
	case DISPID_BEFOREPOSTRECORD:if (m_event) m_event->OnBeforePostRecord(); break;
	case DISPID_BEFORESORT:
		if (1 == pDispParams->cArgs && VT_BSTR == pDispParams->rgvarg[0].vt)
			m_event->OnBeforeSort(pDispParams->rgvarg[0].bstrVal);
		break;
	case 5: 
		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_BSTR == pDispParams->rgvarg[0].vt)
		{
			m_event->OnRuntimeError(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].bstrVal);
		}break;
	case DISPID_FIELDGETDIAPLYTEXT:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			if (DISPATCH_METHOD == wFlags)
			{
				CIGRField  filed = (IGRField*)pDispParams->rgvarg[0].pdispVal;
				m_event->OnFieldGetDisplayText(&filed);
			}
		}break;
	case DISPID_TEXTBOXGETDIAPLYTEXT:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{ 
			CIGRTextBox arg_ = (IGRTextBox*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnTextBoxGetDisplayText(&arg_);
		}break;
	case DISPID_SECTIONFORMAT:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRSection arg_ = (IGRSection*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnSectionFormat(&arg_);
		}break;
	case DISPID_CONTROLCUSTOMDRAW:
		if (2 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[1].vt && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRControl arg1_ = (IGRControl*)pDispParams->rgvarg[1].pdispVal;
			CIGRGraphics arg2_ = (IGRGraphics*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnControlCustomDraw(&arg1_, &arg2_);
		}break;
	case DISPID_CHARTREQUESTDATA:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRChart arg_ = (IGRChart*)pDispParams->rgvarg[1].pdispVal;
			m_event->OnChartRequestData(&arg_);
		}break;
	case DISPID_PROCESSBEGIN:
		m_event->OnProcessBegin();
		break;
	case DISPID_PROCESSEND:
		m_event->OnProcessEnd();
		break;
	case DISPID_GROUPBEGIN:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRGroup arg_ = (IGRGroup*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnGroupBegin(&arg_);
		}break;
	case DISPID_GROUPEND:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRGroup arg_ = (IGRGroup*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnGroupEnd(&arg_);
		}break;
	case DISPID_PROCESSRECORD:
		m_event->OnProcessRecord();
		break;
	case DISPID_PAGEPROCESSRECORD:
		m_event->OnPageProcessRecord();
		break;
	case DISPID_PAGESTART:
		m_event->OnPageStart();
		break;
	case DISPID_PAGEEND:
		m_event->OnPageEnd();
		break;
	case DISPID_GENERATEPAGESBEGIN:
		m_event->OnGeneratePagesBegin();
		break;
	case DISPID_GENERATEPAGESEND:
		m_event->OnGeneratePagesEnd();
		break;
	case DISPID_PRINTBEGIN:
		m_event->OnPrintBegin();
		break;
	case DISPID_PRINTEND:
		m_event->OnPrintEnd();
		break;
	case DISPID_PRINTPAGE:
		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->OnPrintPage(pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_PRINTABORTED:
		m_event->OnPrintAborted();
		break;
	case DISPID_EXPORTBEGIN:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRExportOption  arg1_ = (IGRExportOption*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnExportBegin(&arg1_);
		}break;
	case DISPID_EXPORTEND:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRExportOption  arg1_ = (IGRExportOption*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnExportEnd(&arg1_);
		}break;
	case DISPID_SHOWPREVIEWWND:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRPrintViewer  arg1_ = (IGRPrintViewer*)pDispParams->rgvarg[0].pdispVal;
			m_event->OnShowPreviewWnd(&arg1_);
		}break;
	case 61:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			m_event->OnShowDesignerWnd(pDispParams->rgvarg[0].pdispVal);
		}break;
	case DISPID_HYPERLINKCLICK:
		if (3 == pDispParams->cArgs && VT_BOOL == pDispParams->rgvarg[2].vt && VT_BSTR == pDispParams->rgvarg[1].vt && 
			VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRControl    arg1_ = (IGRControl*)pDispParams->rgvarg[2].pdispVal;
			const wchar_t* arg2_ =pDispParams->rgvarg[1].bstrVal;
			VARIANT_BOOL   arg3_ = pDispParams->rgvarg[0].boolVal;
			m_event->OnHyperlinkClick(&arg1_, arg2_, -1==arg3_? TRUE : FALSE);
		}break;
	}
	return S_OK;
}

void CIGridppReportEvents::OnBeforeSort(/*[in]*/ const wchar_t* SortFields)
{
	//XTRACE(L"OnBeforeSort() %s\n", SortFields);
}

void CIGridppReportEvents::OnRuntimeError(/*[in]*/ long ErrorID, /*, [in]*/ const wchar_t* ErrorMsg)
{
	//XTRACE(L"OnRuntimeError() %d, %s\n", ErrorID, ErrorMsg);
}

void CIGridppReportEvents::OnFieldGetDisplayText(/*[in]*/ CIGRField* pSender)
{
	//XTRACE(L"OnFieldGetDisplayText() %s, %s\n", pSender->get_Name().get(),pSender->get_DisplayText().get());
}

void CIGridppReportEvents::OnTextBoxGetDisplayText(/*[in]*/ CIGRTextBox* pSender)
{
	//XTRACE(L"OnTextBoxGetDisplayText() %s, %s\n", pSender->get_Name().get(), pSender->get_DisplayText().get());
}

void CIGridppReportEvents::OnSectionFormat(/*[in]*/ CIGRSection* pSender)
{
	//XTRACE(L"OnSectionFormat() %s, %d\n", pSender->get_Name().get(), pSender->get_SectionType());
}

void CIGridppReportEvents::OnControlCustomDraw(/*[in]*/ CIGRControl* pSender, /*, [in]*/ CIGRGraphics* pGraphics)
{

} 

void CIGridppReportEvents::OnChartRequestData(/*[in]*/ CIGRChart* pSender)
{

}

///////////////////////////////////////////////////////
/* [local] */ HRESULT STDMETHODCALLTYPE CGRDisplayViewerEventImpl::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS* pDispParams,
	/* [out] */ VARIANT* pVarResult,
	/* [out] */ EXCEPINFO* pExcepInfo,
	/* [out] */ UINT* puArgErr)
{
#ifdef  XC_MODULE
	XTRACE(L"Invoke: %d \n", dispIdMember);
#endif
	if (NULL == m_event) {
		return E_NOTIMPL;
	}
	switch (dispIdMember)
	{
	case DISPID_CLICK:	m_event->Click(); break;
	case DISPID_DBLCLICK: m_event->DblClick(); break;
	case DISPID_KEYDOWN:
		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->KeyDown((GRShiftStates)pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_KEYPRESS:
		if (1 == pDispParams->cArgs && VT_UI1 == pDispParams->rgvarg[0].vt)
			m_event->KeyPress(pDispParams->rgvarg[0].cVal);
		break;
	case DISPID_KEYUP:
		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->KeyUp((GRShiftStates)pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		break;
	case DISPID_MOUSEDOWN:
		if (4 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[3].vt && VT_I4 == pDispParams->rgvarg[2].vt &&
			VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseDown((GRMouseButton)pDispParams->rgvarg[3].lVal, (GRShiftStates)pDispParams->rgvarg[2].lVal,
				pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_MOUSEUP:
		if (4 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[3].vt && VT_I4 == pDispParams->rgvarg[2].vt &&
			VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseUp((GRMouseButton)pDispParams->rgvarg[3].lVal, (GRShiftStates)pDispParams->rgvarg[2].lVal,
				pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_MOUSEMOVE:
		if (3 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt &&
			VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseMove((GRShiftStates)pDispParams->rgvarg[2].lVal, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_CONTROLCLICK:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRControl   arg1_ = (IGRControl*)pDispParams->rgvarg[0].pdispVal;
			m_event->ControlClick(&arg1_);
		}break;
	case DISPID_CONTROLDBLCLICK:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRControl   arg1_ = (IGRControl*)pDispParams->rgvarg[0].pdispVal;
			m_event->ControlDblClick(&arg1_);
		}break;
	case DISPID_SECTIONCLICK: 
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRSection   arg1_ = (IGRSection*)pDispParams->rgvarg[0].pdispVal;
			m_event->SectionClick(&arg1_);
		}break;
	case DISPID_SECTIONDBLCLICK: 
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRSection   arg1_ = (IGRSection*)pDispParams->rgvarg[0].pdispVal;
			m_event->SectionDblClick(&arg1_);
		}break;
	case DISPID_CONTENTCELLCLICK: 
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRColumnContentCell   arg1_ = (IGRColumnContentCell*)pDispParams->rgvarg[0].pdispVal;
			m_event->ContentCellClick(&arg1_);
		}break;
	case DISPID_CONTENTCELLDBLCLICK:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRColumnContentCell   arg1_ = (IGRColumnContentCell*)pDispParams->rgvarg[0].pdispVal;
			m_event->ContentCellDblClick(&arg1_);
		}break;
	case DISPID_TITLECELLCLICK:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRColumnTitleCell   arg1_ = (IGRColumnTitleCell*)pDispParams->rgvarg[0].pdispVal;
			m_event->TitleCellClick(&arg1_);
		}break;
	case DISPID_TITLECELLDBLCLICK:
		if (1 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[0].vt)
		{
			CIGRColumnTitleCell   arg1_ = (IGRColumnTitleCell*)pDispParams->rgvarg[0].pdispVal;
			m_event->TitleCellDblClick(&arg1_);
		}break;
	case DISPID_CHARTCLICKSERIES:
		if (3 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			CIGRChart arg_ = (IGRChart*)pDispParams->rgvarg[2].pdispVal;
			m_event->ChartClickSeries(&arg_, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_CHARTDBLCLICKSERIES:
		if (3 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			CIGRChart arg_ = (IGRChart*)pDispParams->rgvarg[2].pdispVal;
			m_event->ChartDblClickSeries(&arg_, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_CHARTCLICKLEGEND:
		if (3 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			CIGRChart arg_ = (IGRChart*)pDispParams->rgvarg[2].pdispVal;
			m_event->ChartClickLegend(&arg_, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_CHARTDBLCLICKLEGEND:
		if (3 == pDispParams->cArgs && VT_DISPATCH == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			CIGRChart arg_ = (IGRChart*)pDispParams->rgvarg[2].pdispVal;
			m_event->ChartDblClickLegend(&arg_, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
	case DISPID_COLUMNLAYOUTCHANGE:	m_event->ColumnLayoutChange(); break;
	case DISPID_SELECTIONCELLCHANGE:
		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->SelectionCellChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		break;
	case 22: m_event->StatusChange(); break;
	case 29: m_event->CloseButtonClick(); break;
	case 30:
		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->CustomButtonClick(pDispParams->rgvarg[0].lVal);
		break;
	case 31:
		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->ToolbarCommandClick((GRToolControlType2)pDispParams->rgvarg[0].lVal);
		break;
	case 15: m_event->BatchFetchRecord(); break;
	}
	return S_OK;
}

///////////////////////////////////////////////////////
/* [local] */ HRESULT STDMETHODCALLTYPE CGRPrintViewerEventImpl::Invoke(
	/* [in] */ DISPID dispIdMember,
	/* [in] */ REFIID riid,
	/* [in] */ LCID lcid,
	/* [in] */ WORD wFlags,
	/* [out][in] */ DISPPARAMS* pDispParams,
	/* [out] */ VARIANT* pVarResult,
	/* [out] */ EXCEPINFO* pExcepInfo,
	/* [out] */ UINT* puArgErr)
{
#ifdef  XC_MODULE
	XTRACE(L"Invoke: %d \n", dispIdMember);
#endif
	if (NULL == m_event) {
		return E_NOTIMPL;
	}
	switch (dispIdMember)
	{
	case DISPID_CLICK:	m_event->Click(); break;
	case DISPID_DBLCLICK: m_event->DblClick(); break;
 	case DISPID_KEYDOWN:
 		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
 		{
 			m_event->KeyDown((GRShiftStates)pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
 		}break;
 	case DISPID_KEYPRESS:
		if (1 == pDispParams->cArgs && VT_UI1 == pDispParams->rgvarg[0].vt)
 			m_event->KeyPress(pDispParams->rgvarg[0].cVal);
 		break;
	case DISPID_KEYUP:
		if (2 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
 			m_event->KeyUp((GRShiftStates)pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
 		break;
 	case DISPID_MOUSEDOWN:
		if (4 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[3].vt && VT_I4 == pDispParams->rgvarg[2].vt &&
			VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseDown((GRMouseButton)pDispParams->rgvarg[3].lVal, (GRShiftStates)pDispParams->rgvarg[2].lVal,
				pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
 	case DISPID_MOUSEUP:
		if (4 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[3].vt && VT_I4 == pDispParams->rgvarg[2].vt &&
			VT_I4 == pDispParams->rgvarg[1].vt && VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseUp((GRMouseButton)pDispParams->rgvarg[3].lVal, (GRShiftStates)pDispParams->rgvarg[2].lVal,
				pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
 	case DISPID_MOUSEMOVE:
		if (3 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[2].vt && VT_I4 == pDispParams->rgvarg[1].vt && 
			VT_I4 == pDispParams->rgvarg[0].vt)
		{
			m_event->MouseMove((GRShiftStates)pDispParams->rgvarg[2].lVal, pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}break;
 	case DISPID_CURPAGECHANGE:
 		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
 			m_event->CurPageChange(pDispParams->rgvarg[0].lVal);
 		break;
 	case DISPID_STATUSCHANGE: m_event->StatusChange(); break;
	case DISPID_RULERCLICK:
		if (1 == pDispParams->cArgs && VT_BOOL == pDispParams->rgvarg[0].vt)
			m_event->RulerClick( -1 == pDispParams->rgvarg[0].boolVal ? TRUE : FALSE);
 		break;
 	case DISPID_RULERDBLCLICK:
 		m_event->RulerDblClick(-1 == pDispParams->rgvarg[0].boolVal ? TRUE : FALSE);
 		break;
 	case DISPID_PAGECLICK: m_event->PageClick(); break;
 	case DISPID_PAGEDBLCLICK: m_event->PageDblClick(); break;
 	case DISPID_CLOSEBUTTONCLICK:  m_event->CloseButtonClick(); break;
 	case DISPID_CUSTOMBUTTONCLICK:
		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->CustomButtonClick(pDispParams->rgvarg[0].lVal);
		break;
 	case 31:
		if (1 == pDispParams->cArgs && VT_I4 == pDispParams->rgvarg[0].vt)
			m_event->ToolbarCommandClick((GRToolControlType)pDispParams->rgvarg[0].lVal);
		break;
	}
	return S_OK;
}