#ifndef  XCL_COM_H
//@隐藏{
#define  XCL_COM_H
//@隐藏}

//@模块名称  COM操作
//@版本  1.0  
//@日期  2025-01-18
//@作者  XCGUI  
//@QQ    154460336
//@模块备注  COM操作
//VARIANT 变体型参见MSDN: https://docs.microsoft.com/zh-cn/previous-versions/windows/embedded/ee488339(v=winembedded.80)
//IDispatch::Invoke() 参见MSDN: https://docs.microsoft.com/zh-cn/previous-versions/windows/embedded/ee487850(v=winembedded.80)
//VARIANT 和 VARIANTARG 结构用于描述DISPARAMS结构中传递的参数
//C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include\OAIdl.h

//@依赖  module_base.h

#if XC_MODULE
#include "module_base.h"
#endif

//@src "module_com.cpp"

/*@声明

HRESULT CoInitialize(LPVOID pvReserved);  //@别名  COM初始化()
void CoUninitialize();  //@别名  COM清理()

@分组{  COM数据类型

#define  VT_BOOL      //@别名   COM数据类型_逻辑型C
#define  VT_I1        //@别名   COM数据类型_字符型
#define  VT_I2        //@别名   COM数据类型_短整型
#define  VT_I4        //@别名   COM数据类型_整型4
#define  VT_I8        //@别名   COM数据类型_长整型
#define  VT_INT       //@别名   COM数据类型_整型
#define  VT_UI1       //@别名   COM数据类型_字节型
#define  VT_UI2       //@别名   COM数据类型_正短整型
#define  VT_UI4       //@别名   COM数据类型_正整型4
#define  VT_UINT      //@别名   COM数据类型_正整型
#define  VT_UI8       //@别名   COM数据类型_正长整型
#define  VT_BSTR      //@别名   COM数据类型_OLE字符串
#define  VT_LPSTR     //@别名   COM数据类型_字符串A
#define  VT_LPWSTR    //@别名   COM数据类型_字符串
#define  VT_EMPTY     //@别名   COM数据类型_空
#define  VT_DATE      //@别名   COM数据类型_数据
#define  VT_DISPATCH  //@别名   COM数据类型_IDispatch
#define  VT_R4        //@别名   COM数据类型_浮点型
#define  VT_R8        //@别名   COM数据类型_双浮点型

@分组}
*/

//@分组{   COM操作

/*@声明

//@别名 COM智能指针
template<class T>
class CComPtr
{
public:
	T*  operator->();
};
*/


//@备注 封装COM VARIANT, 支持任意数据类型 不同数据类型可自动转换; 例如:
// COM变体型 变量整型 = 1
// COM变体型 变量字符串 = "123"
// COM变体型 变量2 = 变量字符串
// 整型  整型1 = 变量整型
//@别名 COM变体型
class CXComVariant : public _variant_t
{
public:
	//@隐藏{
	CXComVariant();
	CXComVariant(_variant_t&& variant);
	CXComVariant(const _variant_t& variant);
	CXComVariant(const CXComVariant& variant);
	CXComVariant(LONG* vale_);
	operator CXText() const;
	operator CXTextA() const;
	operator const wchar_t* () const;

	void operator=(const VARIANT& varSrc) { _variant_t::operator=(varSrc); }
	void operator=(const VARIANT* pSrc) { _variant_t::operator=(pSrc); }
	void operator=(const _variant_t& varSrc) { _variant_t::operator=(varSrc); }
	void operator=(const _bstr_t& bstrSrc) { _variant_t::operator=(bstrSrc); }
	void operator=(const wchar_t* pSrc) { _variant_t::operator=(pSrc); }
	void operator=(const char* pSrc) { _variant_t::operator=(pSrc); }
	void operator=(IDispatch* pSrc) { _variant_t::operator=(pSrc); }
	void operator=(IUnknown* pSrc) { _variant_t::operator=(pSrc); }
	void operator=(const DECIMAL& decSrc) { _variant_t::operator=(decSrc); }

	//修改地址(修改引用地址)
	void operator=(LONG* vale_); // VT_BYREF
	void operator=(int* vale_);  // VT_BYREF
	void operator=(BSTR* pSrc);  // VT_BYREF

	//修改值(修改引用值)
	void operator=(bool boolSrc);    // VT_BYREF | VT_BOOL
	void operator=(short sSrc);      // VT_BYREF | VT_I2 
	void operator=(long lSrc);       // VT_BYREF | VT_I4 
	void operator=(float fltSrc);    // VT_BYREF | VT_R4 
	void operator=(double dblSrc);   // VT_BYREF | VT_R8 
	void operator=(const CY& cySrc); // VT_BYREF | VT_CY 
	void operator=(BYTE bSrc);       // VT_BYREF | VT_UI1
	void operator=(char cSrc);       // VT_BYREF | VT_I1 
	void operator=(unsigned short usSrc);    // VT_BYREF | VT_UI2
	void operator=(unsigned long ulSrc);     // VT_BYREF | VT_UI4
	void operator=(int iSrc);                // VT_BYREF | VT_INT
	void operator=(unsigned int uiSrc);      // VT_BYREF | VT_UINT
	void operator=(__int64 i8Src);           // VT_BYREF | VT_I8
	void operator=(unsigned __int64 ui8Src); // VT_BYREF | VT_UI8

	//@隐藏}


	//@别名 取逻辑型()
	inline BOOL   GetBOOL() { return operator bool(); }
	//@别名 取字节型()
	inline BYTE   GetBYTE() { return operator BYTE(); }
	//@别名 取字符型A()
	inline char   GetChar() { return operator char(); }
	//@别名 取短整型()
	inline short  GetShort() { return operator short(); }
	//@别名 取正短整型()
	inline USHORT GetUShort() { return operator unsigned short(); }
	//@别名 取整型()
	inline INT    GetInt() { return operator int(); }
	//@别名 取正整型()
	inline UINT   GetUINT() { return operator unsigned int(); }
	//@别名 取长整型()
	inline INT64  GetInt64() { return operator __int64(); }
	//@别名 取正长整型()
	inline UINT64 GetUInt64() { return operator unsigned __int64(); }
	//@别名 取浮点型()
	inline float  GetFloat() { return operator float(); }
	//@别名 取双浮点型()
	inline double GetDouble() { return operator double(); }
	//@别名 取CY()
	inline INT64  GetCY() { return operator CY().int64; }
	//@别名 取文本指针()
	inline const wchar_t* GetTextPtr() { return operator _bstr_t(); }
	//@别名 取IDispatch()
	inline IDispatch* GetIDispatch() { return operator IDispatch * (); }
	//@别名 取IUnknown()
	inline IUnknown*  GetIUnknown() { return operator IUnknown * (); }

	//@备注 判断是否为空数据, COM数据类型_空(VT_EMPTY)
	//@别名 是否为空()
	BOOL IsEmpty() const;

	//@备注 取数据类型, 返回COM数据类型, 通过判断数据类型, 明确当前存储的数据类型
	//@返回 COM数据类型_XXX
	//@别名 取类型()
	unsigned short GetType();

	//@备注 此函数将变体从一种类型转换为另一种类型
	// 基本类型之间的强制（包括数字到字符串和字符串到数字强制）
	// 使用此功能，一种类型的数组不能转换为另一种类型的数组。
	// VARIANTARG 的类型不应在 rgvarg 数组中就地更改
	//@参数  COM数据类型_XXX
	//@别名 置类型(COM类型)
	void ChangeType(unsigned short nVarType);
	/*@声明
	void Clear(); //@别名 清空()
	*/
	//@备注 返回本对象的值内容是否为数组数据
	//@别名 是否为数组()
	BOOL IsArray () const
    {
        return ((vt & VT_ARRAY) != 0);
    }
	//@备注 如果本对象中存放的是数组数据,执行本方法将返回其成员数目,否则将返回0
	//@别名 取数组成员数()
	long GetArrayLength() {
		if (GetType() == (VT_VARIANT | VT_ARRAY)) {
			SAFEARRAY* psa = this->parray;
			// 确保是一维数组  
			if (psa && psa->cDims == 1) {
				// 获取数组的长度（元素数量）  
				return psa->rgsabound[0].cElements;
			}
		}
		return 0;
	}
};


//@备注 COM对象操作封装类
//@别名 COM对象类
class CXComObject
{
	//@隐藏{
	struct  disp_param_retVal_{
		CXText* _text;
		BSTR    _bstr;
		int     index;
	};
	IUnknownPtr   m_pUnknown;
	IDispatchPtr  m_pDispatch;
	DISPPARAMS  m_dispParams;
	int         m_index;
	HRESULT     m_hResult;
	std::vector<disp_param_retVal_*>  m_list_out; //函数参数接收返回值
	//@隐藏}
public:
	CXComObject(){}

	//@备注  指定COM接口, 并填入本对象中
	CXComObject(IUnknown* pUnknown);

	CXComObject(const CXComVariant& variant);

	//备注  释放引用的COM组件
	//@别名 清理()
	void Clear();

	//@备注 创建COM组件, 并填入本对象中, 本对象中的原有内容将被覆盖;
	//@参数 组件名称或GUID字符串, 例如: "Excel.Application" 或 "{00020400-0000-0000-C000-000000000046}"
	//@别名 创建(名称)
	BOOL Create(const wchar_t* pName);

	//@备注 获取本对象中的指定接口, 并填入本对象中, 本对象中的原有内容将被覆盖
	//@参数 组件名称或GUID字符串, 例如: "Excel.Application" 或 "{00020400-0000-0000-C000-000000000046}"
	//@别名 取接口(名称)
	BOOL QueryInterface(const wchar_t* pName);

	//@备注 获取本对象中的指定接口并返回, 本对象内容不改变; 直接返回IUnknown*, 不自动增加引用计数
	//@参数 组件名称或GUID字符串, 例如: "Excel.Application" 或 "{00020400-0000-0000-C000-000000000046}"
	//@别名 取接口对象(名称)
	IUnknown* QueryInterfaceObject(const wchar_t* pName);

	//@备注 检索指向已向 OLE 注册的正在运行的对象, 并填入本对象中, 本对象中的原有内容将被覆盖
	//@参数 组件名称或GUID字符串, 例如: "Excel.Application" 或 "{00020400-0000-0000-C000-000000000046}"
	//@别名 取活动对象(名称)
	BOOL GetActiveObject(const wchar_t* pName);

	//@备注 将指定COM接口填入本对象中, 本对象中的原有内容将被覆盖
	//@别名 置COM对象()
	void SetObject(IUnknown* pDispatch);
	
	//@备注 获取当前对象中的COM接口; 直接返回IUnknown*, 不自动增加引用计数
	//@别名 取COM对象()
	IUnknown* GetObject() const;

	//@备注 为指定图片创建对应的 COM 图片对象并填入本对象中, 本对象中的原有内容将被覆盖
	//@别名 创建图片对象()
	BOOL CreatePicDispObject(const HBITMAP hBitmap);
	
	//@备注 如果本对象为 COM 图片对象, 则取回其具体图片数据.
	//     成功返回真且将所获得的图片数据存放入"结果存储字节集"参数字节集中, 失败返回假
	//@别名 取回图片(结果存储字节集)
	BOOL GetPicDispData(CXBytes& memResult);

	//@备注 为指定字体数据创建对应的 COM 字体对象并填入本对象中,本对象中的原有内容将被覆盖
	//@别名 创建字体对象()
	BOOL CreateFontDispObject(const HFONT hFont);

	//@备注 如果本对象为 COM 字体对象, 创建HFONT返回
	//@别名 取回字体()
	HFONT CreateFontFromDispData();

	//@别名 取错误码()
	HRESULT GetErr(){return m_hResult;}
	//@备注 返回本对象的内容是否为空
	//@别名 是否为空()
	BOOL IsEmpty() const
	{
		return m_pUnknown == NULL;
	}
	//@备注 当读写属性/执行方法时,紧跟该语句后执行本方法可以检查其是否执行成功
	//@别名 是否成功()
	BOOL IsSuccess() const
	{
		return m_hResult == S_OK;
	}	
	/*@声明

	//@备注 调用COM接口的属性get, 例如:
	//     文本型  返回值 = 本对象.取属性("Name")
	//     COM变体型 返回值 = 本对象.取属性("Name")
	//@返回 返回结果存储在COM变体型中, 类型可自动转换
	//@别名 取属性(属性名, 参数列表)
	CXComVariant Get(const wchar_t* pName, ...);

	//@别名 取对象属性(属性名, 参数列表)
	CXComObject GetRetObject(const wchar_t* pName, ...);

	//@别名 取数值属性(属性名, 参数列表)
	vint GetMumber(const wchar_t* pName, ...);

	//@别名 取文本属性(属性名, 参数列表)
	vint GetText(const wchar_t* pName, ...);

	//@备注 调用COM接口的属性put, 例如:
	//     本对象.置属性("Name", "abc")
	//     本对象.置属性("Visible", (bool)真)
	//@返回 如果成功返回真,否则返回假
	//@别名  置属性(方法名, 参数列表)
	BOOL Set(const wchar_t* pName, ...);

	//@备注 调用COM接口的方法, 例如:
	//     整型  返回值 = 本对象.方法(L"Add", 1, 2)
	//     COM变体型  返回值 = 本对象.方法(L"Add", 1, 2)
	//@返回 返回结果存储在COM变体型中, 类型可自动转换
	//@别名 方法(方法名, 参数列表)
	CXComVariant Method(const wchar_t* pName, ...);

	*/

	//@隐藏{
	BOOL GetCLSID(const wchar_t* pName, CLSID& clsid);
	void DoubleToCurrency(const double db, CY* pcy);
	double CurrencyToDouble(const CY& cy);
	double DoubleFontPtSize2Dp(const double dFontPtSize);
	double DoubleFontDpSize2Pt(const double dFontDpSize);

	CXComVariant Get(const wchar_t* pName);
	template<typename T>
	void GetT(T value_){
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_;
		m_index++;
	}
	void GetT(const CXComObject& value_) {
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_.GetObject();
		m_index++;
	}
	template<typename T, typename... Args>
	void GetT(const T t, const Args ... args){
		GetT(t);
		GetT(args...);
	}
	template<typename ... Args>
	CXComObject GetRetObject(const wchar_t* pName, const Args ... args) //取对象属性
	{
		CXComObject comObj= Get(pName, args...);
		return comObj;
	}
	template<typename ... Args>
	vint GetMumber(const wchar_t* pName, const Args ... args) //取数值属性
	{
		vint ret = Get(pName, args...);
		return ret;
	}
	template<typename ... Args>
	CXText GetText(const wchar_t* pName, const Args ... args) //取文本属性
	{
		CXText ret = Get(pName, args...);
		return ret;
	}
	template<typename ... Args>
	CXComVariant Get(const wchar_t* pName, const Args ... args)
	{
		wprintf(L"get:%s\n", pName);
		if (NULL == m_pDispatch) return CXComVariant();

		int count = sizeof...(args);
		CXComVariant* pArray = new CXComVariant[count];
		m_dispParams.rgvarg = pArray;
		m_dispParams.cArgs = count;
		m_dispParams.rgdispidNamedArgs = NULL;
		m_dispParams.cNamedArgs = 0;
		m_index = 0;
		GetT(args...);

		DISPID   dispid;
		LPOLESTR szMember = (LPOLESTR)pName;
		m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (FAILED(m_hResult))
			return CXComVariant();
		
		EXCEPINFO excepInfo;
		VARIANT Result;
		::VariantInit(&Result);
		m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &m_dispParams, &Result, &excepInfo, NULL);

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

	BOOL Set(const wchar_t* pName);
	template<typename T>
	void SetT(T value_)	{
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_;
		m_index++;
	}
	void SetT(const CXComObject& value_) {
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_.GetObject();
		m_index++;
	}
	template<typename T, typename... Args>
	void SetT(const T t, const Args ... args){
		SetT(t);
		SetT(args...);
	}
	template<typename ... Args>
	BOOL Set(const wchar_t* pName, const Args ... args)
	{
		if (NULL == m_pDispatch) return FALSE;

		DISPID   dispid;
		LPOLESTR szMember = (LPOLESTR)pName;
		m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (FAILED(m_hResult))
			return CXComVariant();

		wprintf(L"get:%s\n", pName);

		DISPID  disp = DISPID_PROPERTYPUT;
		int count = sizeof...(args);
		_variant_t* pArray = new CXComVariant[count];;
		m_dispParams.rgvarg = pArray;
		m_dispParams.cArgs = count;
		m_dispParams.rgdispidNamedArgs = &disp;
		m_dispParams.cNamedArgs = 1;

		m_index = 0;
		SetT(args...);
		EXCEPINFO excepInfo;
		m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &m_dispParams, NULL, &excepInfo, NULL);
		if(FAILED(m_hResult))
			m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUTREF, &m_dispParams, NULL, &excepInfo, NULL);
		
		delete[]pArray;
		m_dispParams.rgvarg = NULL;

		if (SUCCEEDED(m_hResult))
			return TRUE;

		if (DISP_E_EXCEPTION == m_hResult)
			OutputDebugError(excepInfo);
		return FALSE;
	}

	CXComVariant Method(const wchar_t* pName);
	template<typename T>
	void MethodT(T value_){
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_;
		m_index++;
	}
	void MethodT(const CXComObject& value_) {
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_.GetObject();
		m_index++;
	}
	void MethodT(BSTR* value_){
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		*var = value_;
		m_index++;
	}
	void MethodT(CXText* value_){
		CXComVariant* var = (CXComVariant*)&m_dispParams.rgvarg[m_index];
		disp_param_retVal_* pInfo = new disp_param_retVal_;
		pInfo->_text = value_;
		pInfo->_bstr = ::SysAllocString(value_->get());
		*var = &pInfo->_bstr;
		pInfo->index = m_index;
		m_list_out.push_back(pInfo);
		m_index++;
	}
	void MethodT(const CXComVariant& value_)
	{
		_variant_t* var = (_variant_t*)&m_dispParams.rgvarg[m_index];
		if (var->vt & VT_BYREF) //出参
		{
			var->pvarVal = (VARIANT*)&value_; //引用变量
			var->vt = VT_BYREF | VT_VARIANT;  //接收参数返回
		} else
		{
			var->vt = VT_EMPTY; //移除标记
			*var = value_;
		}
		m_index++;
	}
	template<typename T, typename... Args>
	void MethodT(T t, const Args& ... args){
		MethodT(args...);
		MethodT(t);
	}
	template<typename ... Args>
	CXComVariant Method(const wchar_t* pName, const Args& ... args)
	{
		wprintf(L"Method:%s\n", pName);
		//funcDescPrint.elemdescFunc.tdesc.vt = VT_HRESULT; // 返回值描述
		//funcDescPrint.lprgelemdescParam = &paramDesc; // 参数的描述
		if(NULL== m_pDispatch) return CXComVariant();

		//const LCID lcid = GetUserDefaultLCID(); //LOCALE_SYSTEM_DEFAULT
		DISPID   dispid;
		LPOLESTR szMember = (LPOLESTR)pName;
		m_hResult = m_pDispatch->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if (FAILED(m_hResult))
		{
			ITypeInfoPtr typeInfoPtr;
			ITypeCompPtr typeCompPtr;
			m_hResult = m_pDispatch->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &typeInfoPtr);
			if (SUCCEEDED(m_hResult))
				m_hResult = typeInfoPtr->GetTypeComp(&typeCompPtr);
			
			if (FAILED(m_hResult))
				return CXComVariant();

			DESCKIND kind;
			BINDPTR bindptr;
			ITypeInfoPtr typeInfoPtr2;
			ULONG lHash = LHashValOfNameSys(SYS_WIN32, LOCALE_SYSTEM_DEFAULT, szMember);
			m_hResult = typeCompPtr->Bind(szMember, lHash, DISPATCH_METHOD, &typeInfoPtr2, &kind, &bindptr);
			if (FAILED(m_hResult))
				return CXComVariant();
		
			if (kind == DESCKIND_FUNCDESC)
			{
				dispid = bindptr.lpfuncdesc->memid;
				typeInfoPtr2->ReleaseFuncDesc(bindptr.lpfuncdesc);
			} else if (kind == DESCKIND_VARDESC || kind == DESCKIND_IMPLICITAPPOBJ)
			{
				typeInfoPtr2->ReleaseVarDesc(bindptr.lpvardesc);
				return CXComVariant();
			} else if (kind == DESCKIND_TYPECOMP)
			{
				bindptr.lptcomp->Release();
				return CXComVariant();
			}
		}
		int count = sizeof...(args);
		CXComVariant* pArray = new CXComVariant[count];
		m_dispParams.rgvarg = pArray;
		m_dispParams.cArgs = count;
		m_dispParams.rgdispidNamedArgs = NULL;
		m_dispParams.cNamedArgs = 0;

		m_index = 0;
		MethodT(args...);

		VARIANT Result;
		::VariantInit(&Result);
		EXCEPINFO excepInfo;
		m_hResult = m_pDispatch->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &m_dispParams, 
			&Result, &excepInfo, NULL);

		delete[]pArray;
		m_dispParams.rgvarg = NULL;

		if (SUCCEEDED(m_hResult))
		{
			int count = (int)m_list_out.size();
			for (int i =0; i<count; i++)
			{
				disp_param_retVal_* pInfo = m_list_out[i];
				*(pInfo->_text) = (const wchar_t*)(pInfo->_bstr);
				::SysFreeString(pInfo->_bstr);
				delete pInfo;
			}
			m_list_out.clear();

			CXComVariant ret(Result);
			::VariantClear(&Result);
			return ret;
		}
		if (DISP_E_EXCEPTION == m_hResult)
			OutputDebugError(excepInfo);

		::VariantClear(&Result);
		return CXComVariant();
	}
	void OutputDebugError(EXCEPINFO &excepInfo){
		xcl_log(L"应用程序引发异常");
		xcl_log2(L"源: ", excepInfo.bstrSource);
		xcl_log2(L"描述: ", excepInfo.bstrDescription);
		xcl_log2(L"帮助文件: ", excepInfo.bstrHelpFile);
	}
	//@隐藏}
};

//@备注 接收目标对象所发送的事件, 本对象使用了引用计数, 当计数为0时自动释放
//@别名 COM事件类
class CXComEventHandle : public IDispatch
{
public:
//@隐藏{
	CXComEventHandle();
	~CXComEventHandle();

	UINT m_nRefCount;
	IID  m_IIDEventSource;
	IUnknownPtr         m_pUnknown;
	IConnectionPointPtr m_pIConnectionPoint;
	DWORD               m_dwEventCookie;
	BOOL                m_bAutoDestroy;
//@隐藏}

	//@备注  如果启用, 当引用计数为0时, 自动销毁当前类, 否则由用户控制类的销毁
	//@别名  启用自动销毁(是否自动销毁)
	void EnableAutoDestroy(BOOL bAutoDestroy){
		m_bAutoDestroy = bAutoDestroy;
	}

	//@别名 引用计数递增()
	virtual ULONG __stdcall AddRef(void);
	//@别名 引用计数递减()
	virtual ULONG __stdcall Release(void);

//@隐藏{
	virtual HRESULT __stdcall QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void ** ppvObject)  override;

	virtual HRESULT __stdcall GetTypeInfoCount(
		/* [out] */ UINT* pctinfo);

	virtual HRESULT __stdcall GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ ITypeInfo** ppTInfo);

	virtual HRESULT __stdcall GetIDsOfNames(
		/* [in] */  REFIID riid,
		/* [size_is][in] */  LPOLESTR* rgszNames,
		/* [range][in] */ UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ DISPID* rgDispId);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [in] */ DISPID dispIdMember,
		/* [in] */ REFIID riid,
		/* [in] */ LCID lcid,
		/* [in] */ WORD wFlags,
		/* [out][in] */ DISPPARAMS* pDispParams,
		/* [out] */ VARIANT* pVarResult,
		/* [out] */ EXCEPINFO* pExcepInfo,
		/* [out] */ UINT* puArgErr);
//@隐藏}
	//@备注 可通过 取名称() 获取当前调度ID对应名称
	//@别名 事件响应(调度ID, 参数数组, 数组数量, 返回值)
	virtual void OnEvent(int dispIdMember, CXComVariant* pArrayParams, int pArraycount, CXComVariant& retResult);
	
	//@备注 将"目标对象"事件挂接到本事件类中
	//@参数 要挂接的COM对象, 挂接后该对象的事件将被本对象接收, 重载 "事件响应" 函数处理事件
	//@参数 要挂接的事件接口IID文本, 例如:"{bdfff072-497b-407b-a8f2-450d6e7b6827}",
	//     如果为空, 则自动去查找目标对象所实现的默认事件来源接口.
	//@别名 挂接(目标对象, 事件IID)
	BOOL BindEvent(CXComObject& comObj, const wchar_t* pEventIneterfaceName);
	
	//@备注 断开挂接事件,清理本对象内容
	//@别名 清理()
	void Clear();

	//@备注 通过调度ID获取成员名称
	//@别名 取名称(调度接口成员ID)
	CXText GetName(int dispIdMember);

//@隐藏{
	BOOL SetConnectionPoint(IUnknown* pUnknown, const IID& riidEventSource);
	BOOL GetCLSID(const wchar_t* pName, CLSID& clsid);
	BOOL FindDefaultEventSource(IUnknown* pUnknown, IID* pDefaultEventSource);
//@隐藏}
};

//@分组}


//@隐藏{
void mkValue(CXText& strText, const CXComVariant& value_);
void mkValue(CXTextA& strText, const CXComVariant& value_);
//@隐藏}


#endif //XCL_COM_H