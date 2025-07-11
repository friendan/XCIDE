
//pdindex为填充方式
//数据填充_PKCS7_PADDING 1
//数据填充_ZERO_PADDING 2
//数据填充_X923_PADDING 3
//数据填充_ISO10126_PADDING 4
//数据填充_ISO78164_PADDING 5
函数 AES_CFB()
	动态数组 <文本型> 测试列表 = {"炫彩IDE-AES-CFB|", "炫彩IDE-AES-CFBa|", "炫彩IDE-AES-CFBad|", "炫彩IDE-AES-CFBaasssssssssssssa|", "炫彩IDE-AES-CFBaasssssssssssssad|", "炫彩IDE-AES-CFBaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' }
	BYTE iv[] = { '1', '2', '3' }
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_CFB_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小() * 2, key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(校验_Base64_编码_字节集(加密数据))
			字节集 解码明文 = 校验_AES解密_CFB_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(解码明文.取文本指针())
			调试输出("-----WW-----")
函数 AES_CFBA()
	动态数组<文本型A> 测试列表 = {A"炫彩IDE-AES-CFB|", A"炫彩IDE-AES-CFBa|", A"炫彩IDE-AES-CFBad|", A"炫彩IDE-AES-CFBaasssssssssssssa|", A"炫彩IDE-AES-CFBaasssssssssssssad|", A"炫彩IDE-AES-CFBaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' }
	BYTE iv[] = { '1', '2', '3' }
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_CFB_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(校验_Base64_编码_字节集A(加密数据))
			字节集 解码明文 = 校验_AES解密_CFB_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(解码明文.取文本指针A())
			调试输出(A"-----AA-----")


函数 AES_CBC()
	动态数组 <文本型> 测试列表 = {"炫彩IDE-AES-CBC|", "炫彩IDE-AES-CBCa|", "炫彩IDE-AES-CBCad|", "炫彩IDE-AES-CBCaasssssssssssssa|", "炫彩IDE-AES-CBCaasssssssssssssad|", "炫彩IDE-AES-CBCaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' }
	BYTE iv[] = { '1', '2', '3' }
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_CBC_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小() * 2, key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(校验_Base64_编码_字节集(加密数据))
			字节集 解码明文 = 校验_AES解密_CBC_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(解码明文.取文本指针())
			调试输出("-----WW-----")
函数 AES_CBCA()
	动态数组<文本型A> 测试列表 = {A"炫彩IDE-AES-CBC|", A"炫彩IDE-AES-CBCa|", A"炫彩IDE-AES-CBCad|", A"炫彩IDE-AES-CBCaasssssssssssssa|", A"炫彩IDE-AES-CBCaasssssssssssssad|", A"炫彩IDE-AES-CBCaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' }
	BYTE iv[] = { '1', '2', '3' }
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_CBC_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(校验_Base64_编码_字节集A(加密数据))
			字节集 解码明文 = 校验_AES解密_CBC_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), iv, 取类型大小(iv), pdindex)
			调试输出(解码明文.取文本指针A())
			调试输出(A"-----AA-----")

函数 AES_ECB()
	动态数组 <文本型> 测试列表 = {"炫彩IDE-AES-ECB|", "炫彩IDE-AES-ECBa|", "炫彩IDE-AES-ECBad|", "炫彩IDE-AES-ECBaasssssssssssssa|", "炫彩IDE-AES-ECBaasssssssssssssad|", "炫彩IDE-AES-ECBaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' };
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_ECB_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小() * 2, key, 取类型大小(key), pdindex)
			调试输出(校验_Base64_编码_字节集(加密数据))
			字节集 解码明文 = 校验_AES解密_ECB_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), pdindex)
			调试输出(解码明文.取文本指针())
			调试输出("-----WW-----")
函数 AES_ECBA()
	动态数组<文本型A> 测试列表 = {A"炫彩IDE-AES-ECB|", A"炫彩IDE-AES-ECBa|", A"炫彩IDE-AES-ECBad|", A"炫彩IDE-AES-ECBaasssssssssssssa|", A"炫彩IDE-AES-ECBaasssssssssssssad|", A"炫彩IDE-AES-ECBaasssssssssssssadb|"}
	BYTE key[] = { 'a', 'b', 'c' };
	变量循环 整型 pdindex=1; pdindex<6; pdindex++
		变量循环 整型 i = 0; i < 测试列表.取大小(); i++
			字节集 加密数据 = 校验_AES加密_ECB_Ex((BYTE*)测试列表[i].取地址(), 测试列表[i].取大小(), key, 取类型大小(key), pdindex)
			调试输出(校验_Base64_编码_字节集A(加密数据))
			字节集 解码明文 = 校验_AES解密_ECB_Ex(加密数据.取地址(), 加密数据.取大小(), key, 取类型大小(key), pdindex)
			调试输出(解码明文.取文本指针A())
			调试输出(A"-----AA-----")

函数 整型 入口函数_窗口()
	调试输出("-------AES_ECB--------")
	AES_ECB()
	AES_ECBA()
	调试输出("-------AES_CBC--------")
	AES_CBC()
	AES_CBCA()
	调试输出("-------AES_CFB--------")
	AES_CFB()
	AES_CFBA()
	返回 0

// [文档]<炫语言> 在线手册: http://www.xcgui.com/doc
// [视频]<炫语言> 入门教程: https://www.bilibili.com/video/BV1KM411h7KK
//
// [文档]<炫彩界面库> 最新在线文档: http://www.xcgui.com/doc-ui
// [视频]<炫彩界面库> 之火山PC: https://www.bilibili.com/video/BV15a411s7hK
// [视频]<炫彩界面库> 通用教程: https://www.bilibili.com/video/BV1kA411A71p/
//
// [商城]炫彩资源商城: http://mall.xcgui.com
//
// *新手尽量不要使用指针, 例如: 字符串使用"文本型", 函数参数若要返回值使用引用 "函数名(整型 &输入输出参数)",
//  内存使用"字节集"
//
//  文本型   双字节字符串  =  炫语言默认字符串类型  =  "字符串W"
//  文本型A  单字节字符串  =  易语言字符串类型     =  A"字符串A"
//  utf8字符串  = U"UTF8字符串"
//  A2W()   单字节字符串 转 双字节字符串
//  W2A()   双字节字符串 转 单字节字符串
//  A =  char    =  单字节
//  w =  wchar_t = 双字节 = UNICODE
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
