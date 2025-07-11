import('XCGUI');

class QQ
{
	constructor()
	{
	}
	Release()
	{
		log("Release()");
		
		if(this.pTemplate_group) XTemp_Destroy(this.pTemplate_group);
		if(this.hExpand) XImage_Destroy(this.hExpand);
		if(this.hExpandNo) XImage_Destroy(this.hExpandNo);
		if(this.hVip) XImage_Destroy(this.hVip);
		if(this.hQZone) XImage_Destroy(this.hQZone);
		if(this.hAvatar) XImage_Destroy(this.hAvatar);
		if(this.hAvatarLarge) XImage_Destroy(this.hAvatarLarge);		
	}
	Init()
	{
		var bRes=XC_LoadResource('resource.res');
		this.hWindow=XC_LoadLayout("main.xml",0);

		this.hTree=XC_GetObjectByName("tree");
		XTree_EnableConnectLine(this.hTree,FALSE,FALSE);
		XSView_ShowSBarH(this.hTree,FALSE);
		XTree_SetIndentation(this.hTree,0);
		XTree_SetItemHeightDefault(this.hTree,28,54);
		
		XTree_SetItemTemplateXML(this.hTree,"xml-template\\Tree_Item_friend.xml");
		XTree_SetItemTemplateXMLSel(this.hTree,"xml-template\\Tree_Item_friend_sel.xml");
		this.pTemplate_group=XTemp_Load(listItemTemp_type_tree,"xml-template\\Tree_Item_group.xml");
		
		this.hVip=XImage_LoadFile("image\\SuperVIP_LIGHT.png",FALSE);
		this.hQZone=XImage_LoadFile("image\\QQZone.png",FALSE);
		this.hAvatarSmall=XImage_LoadFile("image\\avatar_small.png",FALSE);
		this.hAvatarLarge=XImage_LoadFile("image\\avatar_large.png",FALSE);
		
		this.hExpand=XImage_LoadFile("image\\expand.png",FALSE);
		this.hExpandNo=XImage_LoadFile("image\\expandno.png",FALSE);
		XImage_EnableAutoDestroy(this.hExpandNo,FALSE);
		XImage_EnableAutoDestroy(this.hExpand,FALSE);
		
		var hAdapter=XAdTree_Create();
		XTree_BindAdapter(this.hTree, hAdapter);
		XAdTree_AddColumn(hAdapter,"name1"); 
		XAdTree_AddColumn(hAdapter,"name2");
		XAdTree_AddColumn(hAdapter,"name3");
		XAdTree_AddColumn(hAdapter,"name4");
		XAdTree_AddColumn(hAdapter,"name5");
		XAdTree_AddColumn(hAdapter,"name6");
		
		var nGroupID=0;
		var nItemID=0;
		for (var iGroup=0; iGroup<3; iGroup++)
		{
			var text = "好友分组-" + iGroup;
			nGroupID=XAdTree_InsertItemText(hAdapter,text,XC_ID_ROOT,XC_ID_LAST);
			XTree_SetItemHeight(this.hTree,nGroupID,26,26);
			for (var i=0; i<5; i++)
			{
				text = "我的好友-" + i
				nItemID=XAdTree_InsertItemText(hAdapter,text,nGroupID,XC_ID_LAST);
				XAdTree_SetItemTextEx(hAdapter,nItemID,"name2","我的个性签签名");
				XAdTree_SetItemImageEx(hAdapter,nItemID,"name5",this.hVip);
				XAdTree_SetItemImageEx(hAdapter,nItemID,"name6",this.hQZone);
				XAdTree_SetItemImageEx(hAdapter,nItemID,"name3",this.hAvatarSmall);
				XAdTree_SetItemImageEx(hAdapter,nItemID,"name4",this.hAvatarLarge);
			}
		}
		//log(this.OnTemplateCreate2);
		XEle_RegEvent(this.hTree, XE_TREE_TEMP_CREATE, this.OnTemplateCreate, this);
		XEle_RegEvent(this.hTree, XE_TREE_TEMP_CREATE_END, this.OnTreeTemplateCreateEnd, this);
		XEle_RegEvent(this.hTree, XE_DESTROY, this.OnDestroy, this);

		XWnd_AdjustLayout(this.hWindow);
		XWnd_ShowWindow(this.hWindow,SW_SHOW);
		return this.hWindow;
	}
	OnTemplateCreate(pItem, pbHandled)
	{
		log("OnTemplateCreate()");
//	log("OnTemplateCreate() nID:" + pItem.nID + ", hTemp:" + pItem.hTemp+
//	", nHeight:"+ pItem.nHeight);

//	log("rcItem > left:" + pItem.rcItem.left + ", top:" + pItem.rcItem.top );
	
		if(XC_ID_ERROR!=XTree_GetFirstChildItem(qq.hTree,pItem.nID))
		{
			if(qq.pTemplate_group)
			{
				log("===============>>:" + qq.pTemplate_group);
				pItem.hTemp= qq.pTemplate_group;
			}
		}
		log("=====测试修改值====pbHandled===>>100");
		pbHandled.value=100;
		return 0;
	}
	OnTreeTemplateCreateEnd(pItem, pbHandled)
	{
		log("OnTreeTemplateCreateEnd():" + pItem.nID);
		var hButtonExpand=XTree_GetTemplateObject(qq.hTree,pItem.nID,1);
		if(hButtonExpand && XC_IsHELE(hButtonExpand))
		{
			if(qq.hExpandNo)
			{
				XBtn_AddBkImage(hButtonExpand,button_state_leave,qq.hExpandNo);
				XBtn_AddBkImage(hButtonExpand,button_state_stay,qq.hExpandNo);
				XBtn_AddBkImage(hButtonExpand,button_state_down,qq.hExpandNo);
			}
			if(qq.hExpand)
				XBtn_AddBkImage(hButtonExpand,button_state_check,qq.hExpand);

			XEle_EnableBkTransparent(hButtonExpand, TRUE);
			XBtn_SetStyle(hButtonExpand, button_style_default);
			XEle_EnableFocus(hButtonExpand, FALSE);
		}
		return 0;
	}
	OnDestroy(pbHandled)
	{
		qq.Release();
		return 0;
	}
}
var qq = new QQ;
qq.Init();