import("XCGUI");
log("start");
///////////////////////////////////////
function  Init_ListBox()
{
	var  hListBox=XC_GetObjectByName("listBox");
	XListBox_SetItemTemplateXML(hListBox,"template\\listBox_item.xml");
	var  hAdapter = XListBox_CreateAdapter(hListBox);
	
	for(var i =0; i<30; i++)
		 var index = XAdTable_AddItemText(hAdapter,"listBox-item-" + (i+1));
}

function  Init_List()
{
	var  hList=XC_GetObjectByName("list");
	XList_SetItemTemplateXML(hList,"template\\list_item.xml");
	var  hAdapterHead = XList_CreateAdapterHeader(hList);
	var  hAdapter = XList_CreateAdapter(hList);

	XList_AddColumn(hList,200);
	XList_AddColumn(hList,200);
	XList_AddColumn(hList,200);

	XAdMap_AddItemText(hAdapterHead, "name1", "aaa");
	XAdMap_AddItemText(hAdapterHead, "name2", "bbb");
	XAdMap_AddItemText(hAdapterHead, "name3", "ccc");

	for(var i =0; i<30; i++)
	{
		var index =XAdTable_AddItemText(hAdapter,"list-item-"+(i+1));
		XAdTable_SetItemText(hAdapter,index,1,"subitem-"+(i+1));
		XAdTable_SetItemText(hAdapter,index,2,"subitem-"+(i+1));
	}
}

function OnButtonCheck_tab(hButton, bCheck, pbHandled)
{
	if(!bCheck) return 0;
	var name = XEle_GetName(hButton);
	SetSelectTab(name);
	return 0;
}

function SetSelectTab(name)
{
	if(hCurPanel)
	{
		XEle_Destroy(hCurPanel);
		hCurPanel=null;
	}
	if(name=="tab1")
	{
		hCurPanel = XC_LoadLayout("template\\listBox_panel.xml",hLayout);
		Init_ListBox();
	}else if(name=="tab2")
	{
		hCurPanel = XC_LoadLayout("template\\list_panel.xml",hLayout);
		Init_List();
	}else if(name=="tab3")
	{

	}
	XWnd_AdjustLayout(hWindow);
	XWnd_RedrawWnd(hWindow, 0);
}
var bSuccess = XC_LoadStyle("skin1\\style1.css"); //加载样式文件
log("bSuccess: " + bSuccess);

var hWindow=XC_LoadLayout("main.xml",0); //加载布局文件
log("hWindow: " + hWindow );

var hWindow = XC_GetObjectByID(0,100);
var hLayout = XC_GetObjectByName("mainLayout");
var hRichEdit=XC_GetObjectByName("richEdit");
var hCurPanel;

var  hTab = XC_GetObjectByName("tab1");
XEle_RegEvent1(hTab, XE_BUTTON_CHECK, OnButtonCheck_tab);

hTab = XC_GetObjectByName("tab2");
XEle_RegEvent1(hTab, XE_BUTTON_CHECK, OnButtonCheck_tab);

hTab = XC_GetObjectByName("tab3");
XEle_RegEvent1(hTab, XE_BUTTON_CHECK, OnButtonCheck_tab);

SetSelectTab("tab1");

log("hRichEdit=" + hRichEdit);
XRichEdit_SetText(hRichEdit, "666");

XWnd_AdjustLayout(hWindow);
XWnd_ShowWindow(hWindow, SW_SHOW);
