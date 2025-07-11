import('XCGUI_CH');
class 主窗口
{
	//{bindfile="main.xml"}
	constructor()
	{
		this.hWindow = 炫彩_加载布局文件("main.xml", 0);
		//{EVENT_BEGIN}
		XEle_RegEventEx("按钮1", XE_BNCLICK, this.OnBtnClick_按钮1, this);
		//{EVENT_END}
		窗口_调整布局(this.hWindow);
		窗口_显示(this.hWindow, SW_SHOW);
	}
	OnBtnClick_按钮1(pbHandled)
	{
		return 0;
	}
}
var 我的_主窗口 = new 主窗口;
