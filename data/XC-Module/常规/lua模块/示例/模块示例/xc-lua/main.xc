//Release模式编译, 请选择MD方式

函数 整型 luaF_add(lua_State* L) //自定义lua函数
	int n1 = luaL_checkinteger(L, 1)//取出第一个参数（第一个参数在栈底）
	int n2 = luaL_checkinteger(L, 2)//取出第二个参数
	int result = n1 + n2
	lua_pushinteger(L, result) //将返回值入栈
	返回 1  //返回值为返回的参数个数

函数 整型 入口函数()
	lua_State* L = luaL_newstate() //新建虚拟机环境
	luaL_openlibs(L) //在虚拟机中打开所有基础库
	luaL_dostring(L, A"print(123)") //运行字符串
	lua_pushcfunction(L, luaF_add) // 将自定义函数入栈
	lua_setglobal(L, A"add") //设置全局变量add为luaF_add函数
	bool result = luaL_dofile(L, A"main.lua") //运行文件
	if(result) // 如果运行产生错误
		控制台格式输出A(lua_tostring(L, -1)) //取出栈顶错误信息（此时错误信息在栈顶）

	控制台暂停()
	返回 0
