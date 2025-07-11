import("XCGUI"); //炫彩界面库API

function OnButtonCheck(hButton, bCheck, pbHandled)
{
	if(!bCheck) return 0;
	var name = XEle_GetName(hButton);
	log(name);
	return 0;
}

var ret=XC_LoadStyle("skin1\\style1.css"); //加载样式文件
log("ret: " + ret);

var hWindow=XC_LoadLayout("main.xml",0); //加载布局文件
log("hWindow: " + hWindow );

var hButton = XC_GetObjectByName("button");
XEle_RegEvent1(hButton, XE_BUTTON_CHECK, OnButtonCheck);

XWnd_AdjustLayout(hWindow);
XWnd_ShowWindow(hWindow, SW_SHOW);
