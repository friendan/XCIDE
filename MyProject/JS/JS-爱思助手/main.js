import('XCGUI');
class main
{
	//{bindfile="main.xml"}
	constructor()
	{
		this.hLayoutEle=0;
		XC_LoadResource("resource.res");
		this.hWindow = XC_LoadLayout("main.xml", 0);
		this.hLayoutBody= XC_GetObjectByName("body");
		//{EVENT_BEGIN}
		XEle_RegEventEx1("btn_tab1", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab2", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab3", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab4", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab5", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab6", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		XEle_RegEventEx1("btn_tab7", XE_BUTTON_CHECK, this.OnButtonCheck_Tab, this);
		//{EVENT_END}
		
		this.hLayoutEle=XC_LoadLayout("page-我的设备.xml",0);
		XEle_AddChild(this.hLayoutBody, this.hLayoutEle);	
		XWnd_AdjustLayout(this.hWindow);
		XWnd_ShowWindow(this.hWindow, SW_SHOW);
	}
	OnButtonCheck_Tab(hButton,bCheck, pbHandled)
	{
		if(!bCheck) return 0;
		if(this.hLayoutEle) XEle_Destroy(this.hLayoutEle);
		this.hLayoutEle=0;
		
		var name=XEle_GetName(hButton);
		if("btn_tab1"==name)
		{
			this.hLayoutEle=XC_LoadLayout("page-我的设备.xml",0);
			XEle_AddChild(this.hLayoutBody, this.hLayoutEle);
		}else if("btn_tab2"==name)
		{
			this.hLayoutEle=XC_LoadLayout("page-应用游戏.xml",0);
			XEle_AddChild(this.hLayoutBody, this.hLayoutEle);
		}
		XWnd_AdjustLayout(this.hWindow);
		XWnd_RedrawWnd(this.hWindow,0);
		return 0;
	}
}
var my_main = new main; 
