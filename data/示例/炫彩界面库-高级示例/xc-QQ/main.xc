
类  CQQ : 继承 窗口类
	列表树类  m_列表树
	模板句柄  m_hTemplate_group
	模板句柄 m_hTemplate_item
	模板句柄 m_hTemplate_item_Sel
	图片句柄 m_hExpand
	图片句柄 m_hExpandNo
	图片句柄 m_hVip
	图片句柄 m_hQZone
	图片句柄 m_hAvatarLarge
	图片句柄 m_hAvatarSmall
	函数 窗口句柄 初始化()
		逻辑型 bRes = 炫彩_加载资源文件("resource.res")
		_句柄 = (窗口句柄)炫彩_加载布局文件("main.xml", 0)
		
		m_列表树._句柄 = (元素句柄)炫彩_取对象从名称("tree")
		调试输出(m_列表树._句柄)
		m_列表树.启用连接线(假, 假)
		m_列表树.显示水平滚动条(假)
		m_列表树.置缩进(0)
		m_列表树.置项默认高度(28, 54)
		m_列表树.启用模板复用(真)

		//m_列表树.置项模板文件("xml-template\\Tree_Item_friend.xml")
		m_hTemplate_item = 项模板_加载从文件(列表项模板类型_列表树, "xml-template\\Tree_Item_friend.xml")
		m_hTemplate_item_Sel = 项模板_加载从文件(列表项模板类型_列表树, "xml-template\\Tree_Item_friend_sel.xml")
		m_hTemplate_group = 项模板_加载从文件(列表项模板类型_列表树, "xml-template\\Tree_Item_group.xml")
		
		m_hVip = 图片_加载从文件("image\\SuperVIP_LIGHT.png")
		m_hQZone = 图片_加载从文件("image\\QQZone.png")
		m_hAvatarSmall = 图片_加载从文件("image\\avatar_small.png")
		m_hAvatarLarge = 图片_加载从文件("image\\avatar_large.png")
		
		m_hExpand = 图片_加载从文件("image\\expand.png")
		m_hExpandNo = 图片_加载从文件("image\\expandno.png")
		图片_启用自动销毁(m_hExpandNo, 假)
		图片_启用自动销毁(m_hExpand, 假)
		
		数据适配器树类  适配器
		适配器.创建()
		适配器.添加列("name1")
		适配器.添加列("name2")
		适配器.添加列("name3")
		适配器.添加列("name4")
		适配器.添加列("name5")
		适配器.添加列("name6")
		m_列表树.绑定数据适配器(适配器._句柄)
		
		整型 nGroupID = 0
		整型 nItemID = 0
		计次循环 整型 iGroup = 0 ; 3
			文本型 text = 文本组合("好友分组 - ", iGroup)
			nGroupID = m_列表树.插入项文本(text, XC_ID_ROOT, XC_ID_LAST)
			m_列表树.置项高度(nGroupID, 26, 26)
			计次循环  整型 i = 0; 5
				text = 文本组合("我的好友-", i)
				nItemID = m_列表树.插入项文本(text, nGroupID, XC_ID_LAST)
				m_列表树.置项文本扩展(nItemID, "name2", "我的个性签签名")
				m_列表树.置项图片扩展(nItemID, "name5", m_hVip)
				m_列表树.置项图片扩展(nItemID, "name6", m_hQZone)
				m_列表树.置项图片扩展(nItemID, "name3", m_hAvatarSmall)
				m_列表树.置项图片扩展(nItemID, "name4", m_hAvatarLarge)
		
		元素_注册事件CPP(m_列表树._句柄, 元素事件_列表树模板创建, &CQQ::OnTemplateCreate)
		元素_注册事件CPP(m_列表树._句柄, 元素事件_列表树模板创建完成, &CQQ::OnTreeTemplateCreateEnd)
		元素_注册事件CPP(m_列表树._句柄, 元素事件_即将销毁, &CQQ::OnDestroy)

		调整布局()
		显示(SW_SHOW)
		返回  _句柄
	//nFlag  0:状态改变; 1:新模板实例; 2:旧模板复用 
	函数 整型 OnTemplateCreate(列表树项结构 *pItem, 整型 nFlag, 逻辑型 *是否拦截)
		调试输出("OnTemplateCreate(): id:", pItem -> nID, ", nFlag:" , nFlag )
		如果 XC_ID_ERROR != m_列表树.取第一个子项(pItem->nID)
			pItem -> hTemp = m_hTemplate_group
		否则 如果 tree_item_state_select == pItem -> nState
			pItem -> hTemp = m_hTemplate_item_Sel
		否则
			pItem -> hTemp = m_hTemplate_item
		返回 0
	
	函数 整型 OnTreeTemplateCreateEnd(列表树项结构 *pItem, 整型 nFlag, 逻辑型 *是否拦截)
		调试输出("OnTreeTemplateCreateEnd(): id:", pItem -> nID, ", nFlag:" , nFlag )
		如果 1 == nFlag //新模板实例
			元素句柄 hButtonExpand = (元素句柄)m_列表树.取模板对象(pItem->nID, 1)
			如果 hButtonExpand && 炫彩_是否元素(hButtonExpand)
				如果 m_hExpandNo
					元素_添加背景图片(hButtonExpand, 按钮状态标识_鼠标离开 | 按钮状态标识_未选中, m_hExpandNo)
					元素_添加背景图片(hButtonExpand, 按钮状态标识_鼠标停留 | 按钮状态标识_未选中, m_hExpandNo)
					元素_添加背景图片(hButtonExpand, 按钮状态标识_鼠标按下 | 按钮状态标识_未选中, m_hExpandNo)
				
				如果 m_hExpand
					元素_添加背景图片(hButtonExpand, 按钮状态标识_选中, m_hExpand)
				
				元素_启用背景透明(hButtonExpand, 真)
				可视对象_置样式(hButtonExpand, 按钮样式_默认)
				元素_启用焦点(hButtonExpand, 假)
		返回 0

	函数 整型 OnDestroy(逻辑型 *是否拦截)
		调试输出("OnDestroy()")
		如果 m_hTemplate_group;  项模板_销毁(m_hTemplate_group)
		如果 m_hExpand; 图片_销毁(m_hExpand)
		如果 m_hExpandNo; 图片_销毁(m_hExpandNo)
		如果 m_hVip; 图片_销毁(m_hVip)
		如果 m_hQZone; 图片_销毁(m_hQZone)
		如果 m_hAvatarSmall; 图片_销毁(m_hAvatarSmall)
		如果 m_hAvatarLarge; 图片_销毁(m_hAvatarLarge)
		返回 0

函数 整型 入口函数_窗口()   //窗口程序入口
	炫彩_初始化(真)       //初始化界面库
	CQQ  qq
	qq.初始化()
	炫彩_运行()
	炫彩_退出()
	返回 0
