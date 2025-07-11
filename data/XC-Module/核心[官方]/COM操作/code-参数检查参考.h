	template<typename ... Args>
	CXComVariant Method(const wchar_t* pName, const Args& ... args)
	{
		wprintf(L"Method:%s\n", pName);
		//funcDescPrint.elemdescFunc.tdesc.vt = VT_HRESULT; // 返回值描述
		//funcDescPrint.lprgelemdescParam = &paramDesc; // 参数的描述

		DISPID   dispid;
		LPOLESTR szMember = (LPOLESTR)pName;
		m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (FAILED(m_hResult))
			return CXComVariant();

		ITypeInfo* typeinfo=NULL;
		ITypeComp* pTComp = NULL;
		m_hResult = m_pDispatch->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &typeinfo);
		if (SUCCEEDED(m_hResult))
			m_hResult = typeinfo->GetTypeComp(&pTComp);
		
		typeinfo->Release();
		typeinfo = NULL;
		BINDPTR  bindptr;
		DESCKIND kind;
		if (SUCCEEDED(m_hResult))
		{
			const ULONG lHash = LHashValOfNameSys(SYS_WIN32, LOCALE_SYSTEM_DEFAULT, pName);
			m_hResult = pTComp->Bind(szMember, lHash, DISPATCH_METHOD, &typeinfo, &kind, &bindptr);
		}
		if (pTComp)
		{
			pTComp->Release();
			pTComp = NULL;
		}
		if (typeinfo)
		{
			if (kind == DESCKIND_FUNCDESC)
				typeinfo->ReleaseFuncDesc(bindptr.lpfuncdesc);
			else if (kind == DESCKIND_VARDESC || kind == DESCKIND_IMPLICITAPPOBJ)
				typeinfo->ReleaseVarDesc(bindptr.lpvardesc);
			else if (kind == DESCKIND_TYPECOMP)
				bindptr.lptcomp->Release();

			typeinfo->Release();
			typeinfo = NULL;
		}

		if (FAILED(m_hResult))
			return CXComVariant();

		int count = sizeof...(args);
		CXComVariant* pArray = new CXComVariant[count];
		m_dispParams.rgvarg = pArray;
		m_dispParams.cArgs = count;
		m_dispParams.rgdispidNamedArgs = NULL;
		m_dispParams.cNamedArgs = 0;

//		bindptr.lpfuncdesc->elemdescFunc.tdesc.vt; //函数返回类型
//		int count_ = min(count, bindptr.lpfuncdesc->cParams);
//		for (int i = 0;  i < count_; i++) //参数数量
//		{
//			//bindptr.lpfuncdesc->lprgelemdescParam[i].tdesc.vt;  //参数类型
//			bindptr.lpfuncdesc->lprgelemdescParam[i].paramdesc.wParamFlags; //参数 输入输出 PARAMFLAG_FIN(输入), PARAMFLAG_FOUT(输出) , PARAMFLAG_FOPT(选项) PARAMFLAG_FRETVAL(返回值)
//			USHORT wParamFlags = bindptr.lpfuncdesc->lprgelemdescParam[i].paramdesc.wParamFlags;
//			if (!(wParamFlags & PARAMFLAG_FRETVAL))
//			{
//				if (wParamFlags & PARAMFLAG_FOUT) //出参
//				{
//					//标记出参, 赋值后移除标记
//					pArray[i].vt = bindptr.lpfuncdesc->lprgelemdescParam[i].tdesc.vt | VT_BYREF;
//				}
//			}
//		}

		m_index = 0;
		MethodT(args...);

		VARIANT Result;
		::VariantInit(&Result);
		EXCEPINFO excepInfo;
		m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &m_dispParams, &Result, &excepInfo, NULL);

		delete[]pArray;
		m_dispParams.rgvarg = NULL;

		if (SUCCEEDED(m_hResult))
		{
			CXComVariant ret(Result);
			::VariantClear(&Result);
			return ret;
		}
		if (DISP_E_EXCEPTION == m_hResult)
			OutputDebugError(excepInfo);

		::VariantClear(&Result);
		return CXComVariant();
	}