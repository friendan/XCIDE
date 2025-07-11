//interface IATLSimpleObject2 : IDispatch
//{
//	[id(1)] HRESULT Add([in] LONG a, [in] LONG b, [out, retval] LONG* ret);
//	[id(2)] HRESULT Add2([in] LONG a, [out] LONG* ret1, [out, retval] LONG* ret2);
//	[id(3)] HRESULT GetText([in] LONG a, [in, out] BSTR*  ret, [out, retval] BSTR* ret2);
//	[propget, id(4)] HRESULT Name([out, retval] BSTR* pVal);
//	[propput, id(4)] HRESULT Name([in] BSTR newVal);
//	[id(5)] HRESULT Method();
//};
//使用前先注册COM DLL "AmyCom1.dll", 使用系统 运行(WIN+R) 或者 命令行注册(CMD) 注册COM需要管理员权限
//注册: regsvr32 "路径\AmyCom1.dll"
//取消注册: regsvr32 -u "路径\AmyCom1.dll"
函数 整型 入口函数_窗口()
	COM初始化(NULL)
	COM对象类   COM对象
	如果 FALSE == COM对象.创建("AmyCom1.com2")
		返回 0
	如果 COM是否失败(COM对象.取错误码())
		返回 0

	整型 返回值 = COM对象.方法("Add", 1, 2)
	调试输出(返回值)

	整型 参数返回值 = 100 //out
	整型 返回值2 = COM对象.方法("Add2", 1, &参数返回值)
	调试输出(返回值2, 参数返回值)

	文本型 参数返回文本 = "123" //in,out
	文本型 返回值3 = COM对象.方法("GetText", 1, &参数返回文本)
	调试输出(返回值3, 参数返回文本)

	文本型 返回值4 = COM对象.方法("Method") //无参数

	COM对象.置属性("Name", "name1")

	文本型 返回值5 = COM对象.取属性("Name")
	调试输出(返回值5)

	COM清理()
	返回 0
