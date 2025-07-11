
//在common.xh中声明 函数 add123 以便IDE识别
#嵌入代码
int  add123(int a, int b)
{
	return a + b;
}
#嵌入代码_结束

函数 整型 入口函数_窗口()

	整型 ret = add123(1, 2) //调用嵌入代码中的函数
	调试输出(ret)

	#嵌入代码
	ret = 20; //修改 ret 的值
	#嵌入代码_结束
	调试输出(ret)

	字符型  buf[256]={0}
	#嵌入代码
	//嵌入代码中调用系统API
	GetModuleFileName(模块句柄, buf, 256);
	#嵌入代码_结束
	调试输出(buf)
	返回 0
