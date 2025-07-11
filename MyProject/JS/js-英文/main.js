import('XCGUI');
class main
{
	//{bindfile="main.xml"}
	constructor()
	{
		this.hWindow = XC_LoadLayout("main.xml", 0);
		//{EVENT_BEGIN}
		XEle_RegEventEx("button1", XE_BNCLICK, this.OnBtnClick_button1, this);
		//{EVENT_END}
		XWnd_AdjustLayout(this.hWindow);
		XWnd_ShowWindow(this.hWindow, SW_SHOW);
	}
	OnBtnClick_button1(pbHandled)
	{
		log("OnBtnClick_button1()");
		return 0;
	}
}
var my_main = new main
