//炫彩JS基础示例
import('XCGUI');     //导入炫彩库文件
//var xc_js_ex = import('XCGUI_JS_EX.dll');  //导入JS扩展DLL,如果需要
//var xc_js = import('my.js');  //导入JS文件,如果需要
var hWindow=XC_LoadLayout("main.xml",0); //加载布局窗口文件
log("hWindow: " + hWindow);   //打印信息

var hButton = XC_GetObjectByName("button"); //获取按钮句柄

XEle_RegEvent(hButton, XE_BNCLICK, OnBtnClick); //注册按钮点击事件

XWnd_AdjustLayout(hWindow);   //调整布局
XWnd_ShowWindow(hWindow, SW_SHOW); //显示窗口

//按钮点击事件响应函数
function OnBtnClick(pbHandled)
{
	var rect={get:""};
	XEle_GetRect(hButton, rect);
	log("OnBtnClick()");
	alert("OnBtnClick()");
	return 0;
}