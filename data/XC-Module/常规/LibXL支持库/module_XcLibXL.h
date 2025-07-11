
#include "include\libxl.h"
using namespace libxl;

//@模块名称 LibXL支持库
//@版本  4.04
//@日期  2022-09-09
//@作者  炫彩
//@模块备注  炫彩有您更精彩
//@依赖  module_base.h


#ifdef  _WIN64
//@lib "x64\libxl.lib"
//@复制文件 @当前模块路径 "x64\libxl.dll"
#else
//@lib "win32\libxl.lib"
//@复制文件 @当前模块路径 "win32\libxl.dll"
#endif





//@启用枚举前缀 自动给枚举成员加上前缀
//@分组{  枚举类型

//@别名 XL文件类型
enum XLFileType { 
	//@别名 XLS
	XLFILETYPE_XLS,
	//@别名 XLSX
	XLFILETYPE_XLSX
};
//@别名 XL水平对齐
enum XLAlignH {
	//@别名 常规
	XLALIGNH_GENERAL,
	//@别名 左对齐
	XLALIGNH_LEFT,
	//@别名 居中对齐
	XLALIGNH_CENTER,
	//@别名 右对齐
	XLALIGNH_RIGHT,
	//@别名 填充
	XLALIGNH_FILL,
	//@别名 两端对齐
	XLALIGNH_JUSTIFY,
	//@别名 跨列居中
	XLALIGNH_MERGE,
	//@别名 分散对齐缩放
	XLALIGNH_DISTRIBUTED,
};
//@别名 XL垂直对齐
enum XLAlignV { 
	//@别名 靠上对齐
	XLALIGNV_TOP,
	//@别名 居中对齐
	XLALIGNV_CENTER,
	//@别名 靠下对齐
	XLALIGNV_BOTTOM,
	//@别名 两端对齐
	XXLALIGNV_JUSTIFY,
	//@别名 分散对齐
	XLALIGNV_DISTRIBUTED,
};
//@别名 XL上下标
enum XLScript {
	//@别名 正常
	XLScript_NORMAL,
	//@别名 上标
	XLScript_SUPER,
	//@别名 下标
	XLScript_SUB,
};
//@别名 XL边框样式
enum XLBorderStyle {
	//@别名 无
	XLBORDERSTYLE_NONE, 
	//@别名 细线
	XLBORDERSTYLE_THIN, 
	//@别名 中等线
	XLBORDERSTYLE_MEDIUM, 
	//@别名 虚线
	XLBORDERSTYLE_DASHED, 
	//@别名 带点
	XLBORDERSTYLE_DOTTED, 
	//@别名 粗线
	XLBORDERSTYLE_THICK,
	//@别名 双线
	XLBORDERSTYLE_DOUBLE,
	//@别名 毛发
	XLBORDERSTYLE_HAIR, 
	//@别名 中虚线
	XLBORDERSTYLE_MEDIUMDASHED, 
	//@别名 点画线
	XLBORDERSTYLE_DASHDOT, 
	//@别名 点画线粗
	XLBORDERSTYLE_MEDIUMDASHDOT,
	//@别名 虚线点
	XLBORDERSTYLE_DASHDOTDOT,
	//@别名 中等虚线点
	XLBORDERSTYLE_MEDIUMDASHDOTDOT, 
	//@别名 斜线点
	XLBORDERSTYLE_SLANTDASHDOT,
};
//@别名 XL纸张尺寸
enum XLPaper {
	//@别名 默认纸张尺寸
	XLPAPER_DEFAULT, 
	//@别名 信纸
	XLPAPER_LETTER, 
	//@隐藏{
	XLPAPER_LETTERSMALL, 
	XLPAPER_TABLOID, 
	XLPAPER_LEDGER, 
	XLPAPER_LEGAL, 
	XLPAPER_STATEMENT, 
	XLPAPER_EXECUTIVE, 
	//@隐藏}
	//@别名 A3
	XLPAPER_A3,
	//@别名 A4
	XLPAPER_A4, 
	//@别名 A4小
	XLPAPER_A4SMALL, 
	//@别名 A5
	XLPAPER_A5, 
	//@别名 B4
	XLPAPER_B4, 
	//@别名 B5
	XLPAPER_B5, 
	//@隐藏{
	XLPAPER_FOLIO, 
	XLPAPER_QUATRO, 
	XLPAPER_10x14, 
	XLPAPER_10x17, 
	XLPAPER_NOTE, 
	XLPAPER_ENVELOPE_9,
	XLPAPER_ENVELOPE_10, 
	XLPAPER_ENVELOPE_11, 
	XLPAPER_ENVELOPE_12, 
	XLPAPER_ENVELOPE_14, 
	//@隐藏}
	//@别名 C尺寸表
	XLPAPER_C_SIZE, 
	//@别名 D尺寸表
	XLPAPER_D_SIZE, 
	//@别名 E尺寸表
	XLPAPER_E_SIZE, 
	//@别名 信封DL
	XLPAPER_ENVELOPE_DL,
	//@别名 信封C5
	XLPAPER_ENVELOPE_C5, 
	//@别名 信封C3
	XLPAPER_ENVELOPE_C3, 
	//@别名 信封C4
	XLPAPER_ENVELOPE_C4, 
	//@别名 信封C6
	XLPAPER_ENVELOPE_C6,
	//@别名 信封C65
	XLPAPER_ENVELOPE_C65, 
	//@别名 信封B4
	XLPAPER_ENVELOPE_B4, 
	//@别名 信封B5
	XLPAPER_ENVELOPE_B5,
	//@别名 信封B6
	XLPAPER_ENVELOPE_B6, 
	//@隐藏{
	XLPAPER_ENVELOPE, 
	XLPAPER_ENVELOPE_MONARCH, 
	XLPAPER_US_ENVELOPE,
	XLPAPER_FANFOLD, 
	XLPAPER_GERMAN_STD_FANFOLD,
	XLPAPER_GERMAN_LEGAL_FANFOLD, 
	XLPAPER_B4_ISO, 
	XLPAPER_JAPANESE_POSTCARD, 
	XLPAPER_9x11, PAPER_10x11, 
	XLPAPER_15x11, 
	XLPAPER_ENVELOPE_INVITE,
	XLPAPER_US_LETTER_EXTRA = 50, 
	XLPAPER_US_LEGAL_EXTRA,
	XLPAPER_US_TABLOID_EXTRA, 
	XLPAPER_A4_EXTRA, 
	XLPAPER_LETTER_TRANSVERSE, 
	XLPAPER_A4_TRANSVERSE,
	XLPAPER_LETTER_EXTRA_TRANSVERSE, 
	XLPAPER_SUPERA, 
	XLPAPER_SUPERB, 
	XLPAPER_US_LETTER_PLUS,
	XLPAPER_A4_PLUS, 
	XLPAPER_A5_TRANSVERSE,
	XLPAPER_B5_TRANSVERSE,
	XLPAPER_A3_EXTRA, 
	XLPAPER_A5_EXTRA, 
	XLPAPER_B5_EXTRA, 
	XLPAPER_A2, 
	XLPAPER_A3_TRANSVERSE, 
	XLPAPER_A3_EXTRA_TRANSVERSE,
	XLPAPER_JAPANESE_DOUBLE_POSTCARD,
	XLPAPER_A6, 
	XLPAPER_JAPANESE_ENVELOPE_KAKU2, 
	XLPAPER_JAPANESE_ENVELOPE_KAKU3, 
	XLPAPER_JAPANESE_ENVELOPE_CHOU3, 
	XLPAPER_JAPANESE_ENVELOPE_CHOU4,
	XLPAPER_LETTER_ROTATED, 
	XLPAPER_A3_ROTATED, 
	XLPAPER_A4_ROTATED, 
	XLPAPER_A5_ROTATED, 
	XLPAPER_B4_ROTATED, 
	XLPAPER_B5_ROTATED,
	XLPAPER_JAPANESE_POSTCARD_ROTATED, 
	XLPAPER_DOUBLE_JAPANESE_POSTCARD_ROTATED, 
	XLPAPER_A6_ROTATED, 
	XLPAPER_JAPANESE_ENVELOPE_KAKU2_ROTATED,
	XLPAPER_JAPANESE_ENVELOPE_KAKU3_ROTATED, 
	XLPAPER_JAPANESE_ENVELOPE_CHOU3_ROTATED, 
	XLPAPER_JAPANESE_ENVELOPE_CHOU4_ROTATED, 
	XLPAPER_B6,
	XLPAPER_B6_ROTATED, 
	XLPAPER_12x11, 
	XLPAPER_JAPANESE_ENVELOPE_YOU4, 
	XLPAPER_JAPANESE_ENVELOPE_YOU4_ROTATED, 
	XLPAPER_PRC16K, PAPER_PRC32K,
	XLPAPER_PRC32K_BIG, 
	XLPAPER_PRC_ENVELOPE1, 
	XLPAPER_PRC_ENVELOPE2, 
	XLPAPER_PRC_ENVELOPE3, 
	XLPAPER_PRC_ENVELOPE4,
	XLPAPER_PRC_ENVELOPE5,
	PAPER_PRC_ENVELOPE6,
	XLPAPER_PRC_ENVELOPE7,
	XLPAPER_PRC_ENVELOPE8, 
	XLPAPER_PRC_ENVELOPE9, 
	XLPAPER_PRC_ENVELOPE10, 
	XLPAPER_PRC16K_ROTATED,
	XLPAPER_PRC32K_ROTATED, 
	XLPAPER_PRC32KBIG_ROTATED, 
	XLPAPER_PRC_ENVELOPE1_ROTATED,
	XLPAPER_PRC_ENVELOPE2_ROTATED, 
	XLPAPER_PRC_ENVELOPE3_ROTATED,
	XLPAPER_PRC_ENVELOPE4_ROTATED, 
	XLPAPER_PRC_ENVELOPE5_ROTATED, 
	XLPAPER_PRC_ENVELOPE6_ROTATED, 
	XLPAPER_PRC_ENVELOPE7_ROTATED,
	XLPAPER_PRC_ENVELOPE8_ROTATED, 
	XLPAPER_PRC_ENVELOPE9_ROTATED, 
	XLPAPER_PRC_ENVELOPE10_ROTATED
	//@隐藏}
};
//@别名 XL增强保护
enum XLEnhancedProtection {
	//@别名 默认保护
	XLPROT_DEFAULT = -1, 
	//@别名 保护所有
	XLPROT_ALL = 0, 
	//@别名 编辑对象
	XLPROT_OBJECTS = 1, 
	//@别名 编辑方案
	XLPROT_SCENARIOS = 2, 
	//@别名 设置单元格格式
	XLPROT_FORMAT_CELLS = 4, 
	//@别名 设置列格式
	XLPROT_FORMAT_COLUMNS = 8,
	//@别名 设置行格式
	XLPROT_FORMAT_ROWS = 16,
	//@别名 插入列
	XLPROT_INSERT_COLUMNS = 32,
	//@别名 插入行
	XLPROT_INSERT_ROWS = 64, 
	//@别名 插入超链接
	XLPROT_INSERT_HYPERLINKS = 128, 
	//@别名 删除列
	XLPROT_DELETE_COLUMNS = 256, 
	//@别名 删除行
	XLPROT_DELETE_ROWS = 512,
	//@别名 选择单元格
	XLPROT_SEL_LOCKED_CELLS = 1024, 
	//@别名 排序
	XLPROT_SORT = 2048, 
	//@别名 使用自动筛选
	XLPROT_AUTOFILTER = 4096,
	//@别名 使用数据透视表和数据透视图
	XLPROT_PIVOTTABLES = 8192, 
	//@别名 选定解除锁定的单元格
	XLPROT_SEL_UNLOCKED_CELLS = 16384
};
//@别名 XL下划线
enum XLUnderline { 
	//@别名 无
	XLUNDERLINE_NONE, 
	//@别名 单下划线
	XLUNDERLINE_SINGLE, 
	//@别名 双下划线
	XLUNDERLINE_DOUBLE, 
	//@别名 会计用单下划线
	XLUNDERLINE_SINGLEACC = 0x21, 
	//@别名 会计用双下划线
	XLUNDERLINE_DOUBLEACC = 0x22 
};
//@别名 XL筛选方式
enum XLOperator {
	//@别名 等于
	XLOPERATOR_EQUAL,
	//@别名 大于
	XLOPERATOR_GREATER_THAN,
	//@别名 大于等于
	XLOPERATOR_GREATER_THAN_OR_EQUAL,
	//@别名 小于
	XLOPERATOR_LESS_THAN,
	//@别名 小于等于
	XLOPERATOR_LESS_THAN_OR_EQUAL,
	//@别名 不等于
	XLOPERATOR_NOT_EQUAL
};
//@别名 XL对角线边框
enum XLBorderDiagonal { 
	//@别名 无
	XLBORDERDIAGONAL_NONE, 
	//@别名 右斜
	XLBORDERDIAGONAL_DOWN, 
	//@别名 左斜
	XLBORDERDIAGONAL_UP, 
	//@别名 交叉
	XLBORDERDIAGONAL_BOTH
};
//@别名 XL工作表类型
enum XLSheetType { 
	//@别名 标准
	XLSHEETTYPE_SHEET,
	//@别名 图表
	XLSHEETTYPE_CHART, 
	//@别名 未知
	XLSHEETTYPE_UNKNOWN 
};
//@别名 XL图片类型
enum XLPictureType {
	//@别名 PNG
	XLPICTURETYPE_PNG, 
	//@别名 JPEG
	XLPICTURETYPE_JPEG,
	//@别名 GIF
	XLPICTURETYPE_GIF, 
	//@别名 WMF
	XLPICTURETYPE_WMF, 
	//@别名 DIB
	XLPICTURETYPE_DIB,
	//@别名 EMF
	XLPICTURETYPE_EMF,
	//@别名 PICT
	XLPICTURETYPE_PICT,
	//@别名 TIFF
	XLPICTURETYPE_TIFF, 
	//@别名 错误
	XLPICTURETYPE_ERROR = 0xFF
};
//@别名 XL计算模式
enum XLCalcModeType { 
	//@别名 手动
	XLCALCMODE_MANUAL, 
	//@别名 自动
	XLCALCMODE_AUTO, 
	//@别名 除数据表外自动
	XLCALCMODE_AUTONOTABLE 
};
//@别名 XL单元格类型
enum XLCellType { 
	//@别名 空
	XLCELLTYPE_EMPTY, 
	//@别名 数值
	XLCELLTYPE_NUMBER, 
	//@别名 文本
	XLCELLTYPE_STRING, 
	//@别名 逻辑值
	XLCELLTYPE_boolEAN, 
	//@别名 空白
	XLCELLTYPE_BLANK, 
	//@别名 错误
	XLCELLTYPE_ERROR, 
	//@别名 日期
	XLCELLTYPE_STRICTDATE 
};
//@别名 XL单元格错误
enum XLErrorType {
	//@别名 NULL
	XLERRORTYPE_NULL = 0x00, 
	//@别名 DIV_0
	XLERRORTYPE_DIV_0 = 0x07, 
	//@别名 VALUE
	XLERRORTYPE_VALUE = 0x0F, 
	//@别名 REF
	XLERRORTYPE_REF = 0x17, 
	//@别名 NAME
	XLERRORTYPE_NAME = 0x1D,
	//@别名 NUM
	XLERRORTYPE_NUM = 0x24,
	//@别名 NA
	XLERRORTYPE_NA = 0x2A,
	//@别名 无
	XLERRORTYPE_NOERROR = 0xFF
};
//@别名 XL隐藏模式
enum XLSheetState { 
	//@别名 可见
	XLSHEETSTATE_VISIBLE,
	//@别名 可以显示
	XLSHEETSTATE_HIDDEN,
	//@别名 无法显示
	XLSHEETSTATE_VERYHIDDEN 
};
//@别名 XL忽略错误
enum XLIgnoredError {
	//@别名 无
	XLIERR_NO_ERROR = 0,
	//@备注 当单元格包含导致错误的公式时忽略错误。
	XLIERR_EVAL_ERROR = 1,
	//@备注 当公式引用空单元格时忽略错误。
	XLIERR_EMPTY_CELLREF = 2,
	//@备注 当数字格式化为文本或前面有撇号时忽略错误。
	XLIERR_NUMBER_STORED_AS_TEXT = 4,
	//@备注 当公式省略区域中的某些单元格时忽略错误。
	XLIERR_INCONSIST_RANGE = 8,
	//@备注 当工作表区域中的公式与同一区域中的其他公式不同时，忽略错误。
	XLIERR_INCONSIST_FMLA = 16,
	//@备注 当公式包含文本格式的单元格时忽略错误，年份表示为 2 位数字。
	XLIERR_TWODIG_TEXTYEAR = 32,
	//@备注 当未锁定的单元格包含公式时忽略错误。
	XLIERR_UNLOCK_FMLA = 64,
	//@备注 当表中单元格的值不符合指定的数据验证规则时忽略错误。
	XLIERR_DATA_VALIDATION = 128,
	//@别名 全部
	XLIERR_IGNORE_ALL = 255,
};
//@别名 XL数据验证类型
enum XLDataValidationType {
	//@别名 任何值
	XLVALIDATION_TYPE_NONE, 
	//@别名 整数值
	XLVALIDATION_TYPE_WHOLE, 
	//@别名 小数值
	XLVALIDATION_TYPE_DECIMAL, 
	//@别名 序列
	XLVALIDATION_TYPE_LIST,
	//@别名 日期
	XLVALIDATION_TYPE_DATE, 
	//@别名 时间
	XLVALIDATION_TYPE_TIME, 
	//@别名 文本长度
	XLVALIDATION_TYPE_TEXTLENGTH, 
	//@别名 自定义
	XLVALIDATION_TYPE_CUSTOM
};
//@别名 XL关系运算符
enum XLDataValidationOperator {
	//@别名 介于
	XLVALIDATION_OP_BETWEEN,
	//@别名 未介于
	XLVALIDATION_OP_NOTBETWEEN,
	//@别名 等于
	XLVALIDATION_OP_EQUAL,
	//@别名 不等于
	XLVALIDATION_OP_NOTEQUAL,
	//@别名 小于
	XLVALIDATION_OP_LESSTHAN,
	//@别名 小于等于
	XLVALIDATION_OP_LESSTHANOREQUAL,
	//@别名 大于
	XLVALIDATION_OP_GREATERTHAN,
	//@别名 大于等于
	XLVALIDATION_OP_GREATERTHANOREQUAL
};
//@别名 XL填充图案
enum XLFillPattern {
	//@别名 无
	XLFILLPATTERN_NONE,
	//@别名 实心
	XLFILLPATTERN_SOLID,
	//@别名 灰色50
	XLFILLPATTERN_GRAY50,
	//@别名 灰色75
	XLFILLPATTERN_GRAY75,
	//@别名 灰色25
	XLFILLPATTERN_GRAY25,
	//@别名 水平条纹
	XLFILLPATTERN_HORSTRIPE,
	//@别名 垂直条纹
	XLFILLPATTERN_VERSTRIPE,
	//@别名 反对角线条纹
	XLFILLPATTERN_REVDIAGSTRIPE,
	//@别名 对角线条纹
	XLFILLPATTERN_DIAGSTRIPE,
	//@别名 对角线剖面线
	XLFILLPATTERN_DIAGCROSSHATCH,
	//@别名 粗对角线剖面线
	XLFILLPATTERN_THICKDIAGCROSSHATCH,
	//@别名 水平条纹细
	XLFILLPATTERN_THINHORSTRIPE,
	//@别名 垂直条纹细
	XLFILLPATTERN_THINVERSTRIPE,
	//@别名 反对角线条纹细
	XLFILLPATTERN_THINREVDIAGSTRIPE,
	//@别名 对角线条纹细
	XLFILLPATTERN_THINDIAGSTRIPE,
	//@别名 水平剖面线细
	XLFILLPATTERN_THINHORCROSSHATCH,
	//@别名 对角线剖面线细
	XLFILLPATTERN_THINDIAGCROSSHATCH,
	//@别名 灰色12p5
	XLFILLPATTERN_GRAY12P5,
	//@别名 灰色6p25
	XLFILLPATTERN_GRAY6P25
};
//@别名 XL错误图标
enum XLDataValidationErrorStyle { 
	//@别名 停止图标
	XLVALIDATION_ERRSTYLE_STOP, 
	//@别名 警告图标
	XLVALIDATION_ERRSTYLE_WARNING, 
	//@别名 信息图标
	XLVALIDATION_ERRSTYLE_INFORMATION 
};
//@别名 XL图片属性
enum XLPosition { 
	//@别名 大小及位置随单元格而变
	XLPOSITION_MOVE_AND_SIZE, 
	//@别名 大小固定位置随单元格而变
	XLPOSITION_ONLY_MOVE, 
	//@别名 大小和位置均固定
	XLPOSITION_ABSOLUTE 
};
//@别名 XL表单控件类型
enum XLObjectType { 
	//@别名 未知
	XLOBJECT_UNKNOWN, 
	//@别名 按钮
	XLOBJECT_BUTTON, 
	//@别名 复选框
	XLOBJECT_CHECKBOX, 
	//@别名 组合框
	XLOBJECT_DROP, 
	//@别名 分组框
	XLOBJECT_GBOX, 
	//@别名 标签
	XLOBJECT_LABEL, 
	//@别名 列表框
	XLOBJECT_LIST, 
	//@别名 单选框
	XLOBJECT_RADIO, 
	//@别名 滚动条
	XLOBJECT_SCROLL, 

	XLOBJECT_SPIN, 
	//@别名 编辑框
	XLOBJECT_EDITBOX, 
	//@别名 对话框
	XLOBJECT_DIALOG 
};
//@别名 XL筛选类型
enum XLFilter { 
	//@备注 按指定值筛选
	XLFILTER_VALUE, 
	//@备注 要筛选的前N个（项目的百分比或数量）
	XLFILTER_TOP10, 
	//@备注 具有指定条件的自定义筛选器。
	XLFILTER_CUSTOM, 
	//@备注 指定动态筛选条件。
	XLFILTER_DYNAMIC, 
	//@备注 指定筛选的颜色。
	XLFILTER_COLOR, 
	//@备注 指定作为排序依据的图标。
	XLFILTER_ICON, 
	//@备注 定义灵活的存储扩展。
	XLFILTER_EXT,
	//@备注 没有过筛选。
	XLFILTER_NOT_SET
};







//@分组}


//@分组{  操作类


//@别名 XL字体类
class XLFont
{
private:

public:
	//@隐藏{
	Book* book{NULL};
	libxl::Font* font{NULL};
	XLFont() {};
	//十进制颜色转换为Color
	Color IntToClr(int clr)
	{
		int r = (clr >> 16) & 0xff, g = (clr >> 8) & 0xff, b = (clr) & 0xff;
		return book->colorPack(b, g, r);
	}
	//Color颜色转换十进制
	int ClrToInt(Color clr)
	{
		if (clr < 0) { return -1; }
		int r{ 0 }, g{ 0 }, b{ 0 };
		book->colorUnpack(clr, &r, &g, &b);
		return r + g * 256 + b * 65536;
	}
	//@隐藏}

	//@别名 尺寸()
	int FontSize()
	{
		return font == NULL ? -1 : font->size();
	}
	//@别名 尺寸(尺寸)
	void FontSize(int size)
	{
		if (font != NULL) { font->setSize(size); }
	}
	//@别名 斜体()
	bool FontItalic()
	{
		return font == NULL ? false : font->italic();
	}
	//@别名 斜体(设置)
	void FontItalic(bool italic)
	{
		if (font != NULL) { font->setItalic(italic); }
	}
	//@别名 删除线()
	bool FontStrikeOut()
	{
		return font == NULL ? false : font->strikeOut();
	}
	//@别名 删除线(删除线)
	void FontStrikeOut(bool strikeOut)
	{
		if (font != NULL) { font->setStrikeOut(strikeOut); }
	}
	//@别名 颜色()
	int FontColor()
	{
		return font == NULL ? -1 : ClrToInt(font->color());
	}
	//@别名 颜色(颜色)
	void FontColor(int clr)
	{
		if (font != NULL) { font->setColor(IntToClr(clr)); }
	}
	//@别名 加粗()
	bool FontBold()
	{
		return font == NULL ? false : font->bold();
	}
	//@别名 加粗(加粗)
	void FontBold(bool bold)
	{
		if (font != NULL) { font->setBold(bold); }
	}

	//@别名 上下标()
	XLScript FontScript()
	{
		return font == NULL ? (XLScript) - 1 : (XLScript)font->script();
	}
	//@别名 上下标(上下标)
	void FontScript(XLScript script)
	{
		if (font != NULL) { font->setScript((Script)script); }
	}

	//@别名 下划线()
	XLUnderline FontUnderline()
	{
		return font == NULL ? (XLUnderline) - 1 : (XLUnderline)font->underline();
	}
	//@别名 下划线(下划线)
	void FontUnderline(XLUnderline underline)
	{
		if (font != NULL) { font->setUnderline((Underline)underline); }
	}
	//@别名 名称()
	CXText FontName()
	{
		return font == NULL ? NULL : (CXText)font->name();
	}
	//@别名 名称(名称)
	void FontName(CXText name)
	{
		if (font != NULL) { font->setName(name.get()); }
	}

};


//@别名 XL表单控件类
class XLFormControl
{
private:

public:
	//@隐藏{
	Book* book{ NULL };
	FormControl* formControl{ NULL };
	XLFormControl() {};
	//@隐藏}
	//@别名 取类型()
	XLObjectType GetobjectType()
	{
		return formControl == NULL ? (XLObjectType) - 1 : (XLObjectType)formControl->objectType();
	}
};


//@别名 XL富文本类
class XLRichstr
{
private:

public:
	//@隐藏{
	Book* book{NULL};
	RichString* richstr{NULL};
	XLRichstr() {};
	//@隐藏}
	//@别名 添加字体(初始字体)
	XLFont AddFont(XLFont initFont= XLFont())
	{
		XLFont font{};
		if (richstr == NULL) { return font; }
		font.font = richstr->addFont(initFont.font);
		font.book = book;
		return font;
	}
	//@别名 添加文本(文本,字体)
	void  AddText(CXText text, XLFont font = XLFont())
	{
		if (richstr != NULL) { richstr->addText(text.get(), font.font); }
	}
	//@别名 取文本(索引,字体)
	CXText GetText(int index, XLFont& font)
	{
		return richstr == NULL ? NULL : richstr->getText(index, &font.font);
	}
	//@别名 数量()
	int Count()
	{
		return richstr == NULL ? -1 : richstr->textSize();
	}


};

//@别名 XL筛选列类
class XLFilterCol
{
private:

public:
	//@隐藏{
	Book* book{ NULL };
	FilterColumn* filterCol{ NULL };
	XLFilterCol() {};
	//@隐藏}
	//@别名 索引()
	int GetIndex()
	{
		return filterCol == NULL ? -1 : filterCol->index();
	}
	//@别名 筛选类型()
	XLFilter GetFilterType()
	{
		return filterCol == NULL ? (XLFilter) - 1 : (XLFilter)filterCol->filterType();
	}
	//@别名 条件值数量()
	int GetFilterCount()
	{
		return filterCol == NULL ? -1 : filterCol->filterSize();
	}
	//@别名 取条件值(索引)
	CXText GetFilter(int index)
	{
		return filterCol == NULL ? NULL : filterCol->filter(index);
	}
	//@别名 添加条件值(条件值)
	void AddFilter(CXText value)
	{
		if (filterCol != NULL) { filterCol->addFilter(value.get()); }
	}

	//@别名 取顶部或底部项目数(值,顶部,百分比)
	bool GetTop10(double& value, bool& top, bool& percent)
	{
		return filterCol == NULL ? false : filterCol->getTop10(&value, &top, &percent);
	}

	//@别名 置顶部或底部项目数(值,顶部,百分比)
	void SetTop10(double value, bool top = true, bool percent = false)
	{
		if (filterCol != NULL) { filterCol->setTop10(value, top, percent); }
	}
	//@别名 取自定义条件(筛选方式1,条件值1,筛选方式2,条件值2,关系标志)
	bool GetCustomFilter(XLOperator & op1, CXText& vv1, XLOperator & op2, CXText& vv2, bool& andOp)
	{
		if (filterCol == NULL) { return false; }
		const wchar_t* v1;
		const wchar_t* v2;
		bool ret = filterCol->getCustomFilter((libxl::Operator*) & op1, &v1, (libxl::Operator*)&op2, &v2, &andOp);
		vv1.append( v1);
		vv2.append(v2);
		return ret;
	}
	//@别名 置自定义条件(筛选方式1,条件值1,筛选方式2,条件值2,关系标志)
	void  SetCustomFilter(XLOperator op1, CXText v1, XLOperator op2, CXText v2, bool andOp = false)
	{
		if (filterCol != NULL) { filterCol->setCustomFilter((Operator)op1, v1.get(), (Operator)op2, v2.get(), andOp); }
	}
	//@别名 清除条件()
	void  DelClear()
	{
		if (filterCol != NULL) { filterCol->clear(); }
	}



};

//@别名 XL自动筛选类
class XLAutoFilter
{
private:

public:
	//@隐藏{
	Book* book{ NULL };
	Sheet* sheet{ NULL };
	AutoFilter* autoFilter{ NULL };
	XLAutoFilter() {};
	struct CELL { int row{ 0 }; int col{ 0 }; };
	CELL RC(CXText cell)
	{
		CELL rc;
		if (sheet == NULL) { return rc; }
		wchar_t* str = (wchar_t*)cell.get();
		text_upper(str);
		sheet->addrToRowCol(str, &rc.row, &rc.col);
		return rc;
	}
	int L2N(CXText col)
	{
		if (sheet == NULL) { return 0; }
		wchar_t* str = (wchar_t*)col.get();
		text_upper(str);
		int c{ 0 };
		sheet->addrToRowCol(str, 0, &c);
		return c;
	}
	//@隐藏}
	//@别名 取筛选区域(起始行,终止行,起始列,终止列)
	CXText GetRef(int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (autoFilter == NULL) { return L""; }
		if (autoFilter->getRef(&rowFirst, &rowLast, &colFirst, &colLast) == false) { return L""; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 置筛选区域(起始行,终止行,起始列,终止列)
	void SetRef(int rowFirst, int rowLast, int colFirst, int colLast)
	{
		if (autoFilter == NULL) { return; }
		autoFilter->setRef(rowFirst, rowLast, colFirst, colLast);
	}
	//@别名 置筛选区域(起始单元格,终止单元格)
	void SetRef(CXText startCell, CXText endCell)
	{
		if (autoFilter == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		autoFilter->setRef(rc.row, rc1.row, rc.col, rc1.col);
	}
	//@别名 添加筛选列(列)
	XLFilterCol AddCol(int col)
	{
		XLFilterCol filterCol{};
		if (autoFilter == NULL) { return filterCol; }
		filterCol.filterCol = autoFilter->column(col);
		return filterCol;
	}
	//@别名 添加筛选列(列名)
	XLFilterCol AddCol(CXText col)
	{
		XLFilterCol filterCol{};
		if (autoFilter == NULL) { return filterCol; }
		filterCol.filterCol = autoFilter->column(L2N(col));
		return filterCol;
	}
	//@别名 筛选列数量()
	int GetColCount()
	{
		return autoFilter == NULL ? -1 : autoFilter->columnSize();
	}
	//@别名 取筛选列(索引)
	XLFilterCol GetCol(int index)
	{
		XLFilterCol filterCol{};
		if (autoFilter == NULL) { return filterCol; }
		filterCol.filterCol = autoFilter->columnByIndex(index);
		return filterCol;
	}
	//@别名 取排序区域(起始行,终止行,起始列,终止列)
	CXText GetSortRange(int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (autoFilter == NULL) { return L""; }
		if (autoFilter->getSortRange(&rowFirst, &rowLast, &colFirst, &colLast) == false) { return L""; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 取列排序(列,降序)
	bool GetSort(int& columnIndex, bool& descending)
	{
		return autoFilter == NULL ? false : autoFilter->getSort(&columnIndex, &descending);
	}
	//@别名 置列排序(列,降序)
	bool SetSort(int col, bool descending = false)
	{
		return autoFilter == NULL ? false : autoFilter->setSort(col, descending);
	}
	//@别名 置列排序(列名,降序)
	bool SetSort(CXText col, bool descending = false)
	{
		return autoFilter == NULL ? false : autoFilter->setSort(L2N(col), descending);
	}
	//@别名 添加列排序(列,降序)
	bool AddSort(int col, bool descending = false)
	{
		return autoFilter == NULL ? false : autoFilter->addSort(col, descending);
	}
	//@别名 添加列排序(列名,降序)
	bool AddSort(CXText col, bool descending = false)
	{
		return autoFilter == NULL ? false : autoFilter->addSort(L2N(col), descending);
	}



};

//@别名 XL格式类
class XLFormat
{
private:

public:
	//@隐藏{
	Book* book{NULL};
	Format* format{NULL};
	XLFormat(){};
	//十进制颜色转换为libxl格式
	Color IntToClr(int clr)
	{
		int r = (clr >> 16) & 0xff, g = (clr >> 8) & 0xff, b = (clr) & 0xff;
		return book->colorPack(b, g, r);
	}
	//libxl颜色转换十进制
	int ClrToInt(libxl::Color clr)
	{
		if (clr < 0) { return -1; }
		int r{ 0 }, g{ 0 }, b{ 0 };
		book->colorUnpack(clr, &r, &g, &b);
		return r + g * 256 + b * 65536;
	}
	//@隐藏}
	

	//@别名 字体()
	XLFont FormatFont()
	{
		XLFont font{};
		if (format != NULL)
		{
			font.font = format->font();
			font.book = book;
		}
		return font;
	}
	//@别名 字体(字体)
	void FormatFont(XLFont font)
	{
		if (format != NULL) { format->setFont(font.font); }
	}
	//@别名 自定义数字格式()
	int FormatNumFormat()
	{
		return format == NULL ? -1 : format->numFormat();
	}
	//@别名 自定义数字格式(标识符)
	void FormatNumFormat(int numFormat)
	{
		if (format != NULL) { format->setNumFormat(numFormat); }
	}
	//@别名 水平对齐()
	XLAlignH FormatAlignH()
	{
		return format == NULL ? (XLAlignH) - 1 : (XLAlignH)format->alignH();
	}
	//@别名 水平对齐(水平对齐)
	void FormatAlignH(XLAlignH align)
	{
		if (format != NULL) { format->setAlignH((AlignH)align); }
	}
	//@别名 垂直对齐()
	XLAlignV FormatAlignV()
	{
		return format == NULL ? (XLAlignV) - 1 : (XLAlignV)format->alignV();
	}
	//@别名 垂直对齐(垂直对齐)
	void FormatAlignV(XLAlignV align)
	{
		if (format != NULL) { format->setAlignV((AlignV)align); }
	}
	//@别名 自动换行()
	bool FormatWrap()
	{
		return format == NULL ? false : format->wrap();
	}
	//@别名 自动换行(自动换行)
	void FormatWrap(bool wrap)
	{
		if (format != NULL) { format->setWrap(wrap); }
	}
	//@别名 文本方向()
	int FormatRotation()
	{
		return format == NULL ? -1 : format->rotation();
	}
	//@别名 文本方向(方向)
	void FormatRotation(int rotation)
	{
		if (format != NULL) { format->setRotation(rotation); }
	}
	//@别名 缩进级别()
	int FormatIndent()
	{
		return format == NULL ? -1 : format->indent();
	}
	//@别名 缩进级别(级别)
	void FormatIndent(int indent)
	{
		if (format != NULL) { format->setIndent(indent); }
	}
	//@别名 自动缩小字体()
	bool FormatShrinkToFit()
	{
		return format == NULL ? false : format->shrinkToFit();
	}
	//@别名 自动缩小字体(设置)
	void FormatShrinkToFit(bool shrinkToFit)
	{
		if (format != NULL) { format->setShrinkToFit(shrinkToFit); }
	}
	//@别名 边框样式(边框样式)
	void FormatSetBorder(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorder((BorderStyle)style); }
	}
	//@别名 边框颜色(颜色)
	void FormatSetBorderColor(int clr)
	{
		if (format != NULL) { format->setBorderColor(IntToClr(clr)); }
	}
	//@别名 左边框样式()
	XLBorderStyle FormatBorderLeft()
	{
		return format == NULL ? (XLBorderStyle)-1 : (XLBorderStyle)format->borderLeft();
	}
	//@别名 左边框样式(边框样式)
	void FormatBorderLeft(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorderLeft((BorderStyle)style); }
	}
	//@别名 右边框样式()
	XLBorderStyle FormatBorderRight()
	{
		return format == NULL ? (XLBorderStyle) - 1 : (XLBorderStyle)format->borderRight();
	}
	//@别名 右边框样式(边框样式)
	void FormatBorderRight(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorderRight((BorderStyle)style); }
	}
	//@别名 上边框样式()
	XLBorderStyle FormatBorderTop()
	{
		return format == NULL ? (XLBorderStyle) - 1 : (XLBorderStyle)format->borderTop();
	}
	//@别名 上边框样式(边框样式)
	void FormatBorderTop(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorderTop((BorderStyle)style); }
	}
	//@别名 下边框样式()
	XLBorderStyle FormatBorderBottom()
	{
		return format == NULL ? (XLBorderStyle) - 1 : (XLBorderStyle)format->borderBottom();
	}
	//@别名 下边框样式(边框样式)
	void FormatBorderBottom(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorderBottom((BorderStyle)style); }
	}
	//@别名 左边框颜色()
	int FormatBorderLeftColor()
	{
		return format == NULL ? -1 : ClrToInt(format->borderLeftColor());
	}
	//@别名 左边框颜色(颜色)
	void FormatBorderLeftColor(int clr)
	{
		if (format != NULL) { format->setBorderLeftColor(IntToClr(clr)); }
	}
	//@别名 右边框颜色()
	int FormatBorderRightColor()
	{
		return format == NULL ? -1 : ClrToInt(format->borderRightColor());
	}
	//@别名 右边框颜色(颜色)
	void FormatBorderRightColor(int clr)
	{
		if (format != NULL) { format->setBorderRightColor(IntToClr(clr)); }
	}
	//@别名 上边框颜色()
	int FormatBorderTopColor()
	{
		return format == NULL ? -1 : ClrToInt(format->borderTopColor());
	}
	//@别名 上边框颜色(颜色)
	void FormatBorderTopColor(int clr)
	{
		if (format != NULL) { format->setBorderTopColor(IntToClr(clr)); }
	}
	//@别名 下边框颜色()
	int FormatBorderBottomColor()
	{
		return format == NULL ? -1 : ClrToInt(format->borderBottomColor());
	}
	//@别名 下边框颜色(颜色)
	void FormatBorderBottomColor(int clr)
	{
		if (format != NULL) { format->setBorderBottomColor(IntToClr(clr)); }
	}
	//@别名 对角线边框()
	XLBorderDiagonal FormatBorderDiagonal()
	{
		return format == NULL ? (XLBorderDiagonal) - 1 : (XLBorderDiagonal)format->borderDiagonal();
	}
	//@别名 对角线边框(对角线边框)
	void FormatBorderDiagonal(XLBorderDiagonal border)
	{
		if (format != NULL) { format->setBorderDiagonal((BorderDiagonal)border); }
	}
	//@别名 对角线边框样式()
	XLBorderStyle FormatBorderDiagonalStyle()
	{
		return format == NULL ? (XLBorderStyle) - 1 : (XLBorderStyle)format->borderDiagonalStyle();
	}
	//@别名 对角线边框样式(边框样式)
	void FormatBorderDiagonalStyle(XLBorderStyle style)
	{
		if (format != NULL) { format->setBorderDiagonalStyle((BorderStyle)style); }
	}
	//@别名 对角线边框颜色()
	int FormatBorderDiagonalColor()
	{
		return format == NULL ? -1 : ClrToInt(format->borderDiagonalColor());
	}
	//@别名 对角线边框颜色(颜色)
	void FormatBorderDiagonalColor(int clr)
	{
		if (format != NULL) { format->setBorderDiagonalColor(IntToClr(clr)); }
	}
	//@别名 填充图案()
	XLFillPattern FormatFillPattern()
	{
		return format == NULL ? (XLFillPattern) - 1 : (XLFillPattern)format->fillPattern();
	}
	//@别名 填充图案(填充图案)
	void FormatFillPattern(XLFillPattern pattern)
	{
		if (format != NULL) { format->setFillPattern((FillPattern)pattern); }
	}
	//@别名 填充图案前景色()
	int FormatPatternForegroundColor()
	{
		return format == NULL ? -1 : ClrToInt(format->patternForegroundColor());
	}
	//@别名 填充图案前景色(颜色)
	void FormatPatternForegroundColor(int clr)
	{
		if (format != NULL) { format->setPatternForegroundColor(IntToClr(clr)); }
	}
	//@别名 填充图案背景色()
	int FormatPatternBackgroundColor()
	{
		return format == NULL ? -1 : ClrToInt(format->patternBackgroundColor());
	}
	//@别名 填充图案背景色(颜色)
	void FormatPatternBackgroundColor(int clr)
	{
		if (format != NULL) { format->setPatternBackgroundColor(IntToClr(clr)); }
	}
	//@别名 保护锁定()
	bool FormatLocked()
	{
		return format == NULL ? false : format->locked();
	}
	//@别名 保护锁定(保护锁定)
	void FormatLocked(bool locked)
	{
		if (format != NULL) { format->setLocked(locked); }
	}
	//@别名 保护隐藏()
	bool FormatHidden()
	{
		return format == NULL ? false : format->hidden();
	}
	//@别名 保护隐藏(保护隐藏)
	void FormatHidden(bool hidden)
	{
		if (format != NULL) { format->setHidden(hidden); }
	}



};




//@别名 XL工作表类
class XLSheet
{
private:

public:
	//@隐藏{
	Book* book{NULL};
	Sheet* sheet{NULL};
	XLSheet() {};
	struct CELL { int row{ 0 }; int col{ 0 }; };
	//十进制颜色转换为Color
	Color IntToClr(int clr)
	{
		int r = (clr >> 16) & 0xff, g = (clr >> 8) & 0xff, b = (clr) & 0xff;
		return book->colorPack(b, g, r);
	}
	//Color颜色转换十进制
	int ClrToInt(Color clr)
	{
		if (clr < 0) { return -1; }
		int r{ 0 }, g{ 0 }, b{ 0 };
		book->colorUnpack(clr, &r, &g, &b);
		return r + g * 256 + b * 65536;
	}
	CELL RC(CXText cell)
	{
		CELL rc;
		if (sheet == NULL) { return rc; }
		wchar_t* str = (wchar_t*)cell.get();
		text_upper(str);
		sheet->addrToRowCol(str, &rc.row, &rc.col);
		return rc;
	}
	int L2N(CXText col)
	{
		if (sheet == NULL) { return 0; }
		wchar_t* str = (wchar_t*)col.get();
		text_upper(str);
		int c{ 0 };
		sheet->addrToRowCol(str, 0, &c);
		return c;
	}
	//@隐藏}



	//@别名 取单元格类型(行,列)
	//@备注 行列索引从0开始
	XLCellType GetCellType(int row, int col)
	{
		if (sheet == NULL) { return (XLCellType) - 1; }
		return (XLCellType)sheet->cellType(row, col);
	}
	//@别名 取单元格类型(单元格)
	//@参数 单元格 如“A1”
	XLCellType GetCellType(CXText cell)
	{
		if (sheet == NULL) { return (XLCellType) - 1; }
		CELL rc = RC(cell);
		return (XLCellType)sheet->cellType(rc.row, rc.col);
	}
	//@别名 取单元格格式(行,列)
	//@备注 行列索引从0开始
	XLFormat GetCellFormat(int row, int col)
	{
		XLFormat ret{};
		if (sheet == NULL) { return ret; }
		ret.format = sheet->cellFormat(row, col);
		ret.book = book;
		return ret;
	}
	//@别名 取单元格格式(单元格)
	//@参数 单元格 如“A1”
	XLFormat GetCellFormat(CXText cell)
	{
		XLFormat ret{};
		if (sheet == NULL) { return ret; }
		CELL rc = RC(cell);
		ret.format = sheet->cellFormat(rc.row, rc.col);
		ret.book = book;
		return ret;
	}
	//@别名 置单元格格式(行,列,格式)
	//@备注 行列索引从0开始
	void SetCellFormat(int row, int col, XLFormat format)
	{
		if (sheet == NULL) { return; }
		sheet->setCellFormat(row, col, format.format);
	}
	//@别名 置单元格格式(起始行,终止行,起始列,终止列,格式)
	//@备注 行列索引从0开始
	void SetCellFormat(int rowFirst, int rowLast, int colFirst, int colLast, XLFormat format)
	{
		if (sheet == NULL) { return; }
		for (int r = 0; r <= rowLast - rowFirst; r++)
		{
			for (int c = 0; c <= colLast - colFirst; c++)
			{
				sheet->setCellFormat(rowFirst +r, colFirst+c, format.format);
			}
		}
		
	}

	//@别名 置单元格格式(单元格,格式)
	//@参数 单元格 如“A1”
	void SetCellFormat(CXText cell, XLFormat format)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->setCellFormat(rc.row, rc.col, format.format);
	}
	//@别名 置单元格格式(起单元格,终止单元格,格式)
	//@参数 单元格 如“A1”
	void SetCellFormat(CXText startCell, CXText endCell, XLFormat format)
	{
		if (sheet == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		for (int r = 0; r <= rc1.row - rc.row; r++)
		{
			for (int c = 0; c <= rc1.col - rc.col; c++)
			{
				sheet->setCellFormat(rc.row + r, rc.col + c, format.format);
			}
		}

	}
	//@别名 取单元格文本(行,列,格式)
	//@备注 行列索引从0开始
	CXText GetStr(int row, int col, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return NULL; }
		format.book = book;
		return (CXText)sheet->readStr(row, col, &format.format);
	}
	//@别名 取单元格文本(单元格,格式)
	//@参数 单元格 如“A1”
	CXText GetStr(CXText cell, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return NULL; }
		CELL rc = RC(cell);
		format.book = book;
		return (CXText)sheet->readStr(rc.row, rc.col, &format.format);
	}

	//@别名 置单元格文本(行,列,文本,格式)
	//@备注 行列索引从0开始
	bool SetStr(int row, int col, CXText value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return  sheet->writeStr (row, col, value.get(), format.format);
	}
	//@参数 单元格 如“A1”
	//@别名 置单元格文本(单元格,文本,格式)
	bool SetStr(CXText cell, CXText value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return  sheet->writeStr(rc.row, rc.col, value.get(), format.format);
	}
	//@别名 取单元格富文本(行,列,格式)
	//@备注 行列索引从0开始
	XLRichstr GetRichStr(int row, int col, XLFormat& format = XLFormat())
	{
		XLRichstr ret{};
		if (sheet == NULL) { return ret; }
		format.book = book;
		ret.richstr = sheet->readRichStr(row, col, &format.format);
		ret.book = book;
		return ret;
	}
	//@别名 取单元格富文本(单元格,格式)
	//@参数 单元格 如“A1”
	XLRichstr GetRichStr(CXText cell, XLFormat& format = XLFormat())
	{
		XLRichstr ret{};
		if (sheet == NULL) { return ret; }
		CELL rc = RC(cell);
		format.book = book;
		ret.richstr = sheet->readRichStr(rc.row, rc.col, &format.format);
		ret.book = book;
		return ret;
	}
	//@别名 置单元格富文本(行,列,富文本,格式)
	//@备注 行列索引从0开始
	bool SetRichStr(int row, int col, XLRichstr richstr, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return sheet->writeRichStr(row, col, richstr.richstr, format.format);
	}
	//@别名 置单元格富文本(单元格,富文本,格式)
	//@参数 单元格 如“A1”
	bool SetRichStr(CXText cell, XLRichstr richstr, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->writeRichStr(rc.row, rc.col, richstr.richstr, format.format);
	}
	//@别名 取单元格数值(行,列,格式)
	//@备注 行列索引从0开始
	double GetNum(int row, int col, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return -1.0; }
		format.book = book;
		return sheet->readNum(row, col, &format.format);
	}
	//@别名 取单元格数值(单元格,格式)
	//@参数 单元格 如“A1”
	double GetNum(CXText cell, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return -1.0; }
		CELL rc = RC(cell);
		format.book = book;
		return sheet->readNum(rc.row, rc.col, &format.format);
	}
	//@别名 置单元格数值(行,列,数值,格式)
	//@备注 行列索引从0开始
	bool SetNum(int row, int col, double  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return sheet->writeNum(row, col, value, format.format);
	}
	//@别名 置单元格数值(单元格,数值,格式)
	//@参数 单元格 如“A1”
	bool SetNum(CXText cell, double  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->writeNum(rc.row, rc.col, value, format.format);
	}
	//@别名 置单元格日期(行,列,日期,格式)
	//@备注 行列索引从0开始
	bool SetDate(int row, int col, double  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		if (format.format == NULL)
		{
			format.format = book->addFormat();
		}
		if (format.format->numFormat() == NULL)
		{
			format.format->setNumFormat(NUMFORMAT_DATE);
		}
		return sheet->writeNum(row, col, value, format.format);
	}
	//@别名 置单元格日期(单元格,日期,格式)
	//@参数 单元格 如“A1”
	bool SetDate(CXText cell, double  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		if (format.format == NULL)
		{
			format.format = book->addFormat();
		}
		if (format.format->numFormat() == NULL)
		{
			format.format->setNumFormat(NUMFORMAT_DATE);
		}
		CELL rc = RC(cell);
		return sheet->writeNum(rc.row, rc.col, value, format.format);
	}
	//@别名 取单元格逻辑值(行,列,格式)
	//@备注 行列索引从0开始
	bool GetBool(int row, int col, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		format.book = book;
		return sheet->readBool(row, col, &format.format);
	}
	//@别名 取单元格逻辑值(单元格,格式)
	//@参数 单元格 如“A1”
	bool GetBool(CXText cell, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		format.book = book;
		return sheet->readBool(rc.row, rc.col, &format.format);
	}
	//@别名 置单元格逻辑值(行,列,逻辑值,格式)
	//@备注 行列索引从0开始
	bool SetBool(int row, int col, bool  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return sheet->writeBool(row, col, value, format.format);
	}
	//@别名 置单元格逻辑值(单元格,逻辑值,格式)
	//@参数 单元格 如“A1”
	bool SetBool(CXText cell, bool  value, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->writeBool(rc.row, rc.col, value, format.format);
	}
	//@别名 取单元格空白(行,列,格式)
	//@备注 行列索引从0开始
	bool GetBlank(int row, int col, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		format.book = book;
		return sheet->readBlank(row, col, &format.format);
	}
	//@别名 取单元格空白(单元格,格式)
	//@参数 单元格 如“A1”
	bool GetBlank(CXText cell, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		format.book = book;
		return sheet->readBlank(rc.row, rc.col, &format.format);
	}
	//@别名 置单元格空白(行,列,格式)
	//@备注 行列索引从0开始
	bool SetBlank(int row, int col, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return sheet->writeBlank(row, col, format.format);
	}
	//@别名 置单元格空白(单元格,格式)
	//@参数 单元格 如“A1”
	bool SetBlank(CXText cell, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->writeBlank(rc.row, rc.col, format.format);
	}
	//@别名 取单元格公式(行,列,格式)
	//@备注 行列索引从0开始
	CXText GetFormula(int row, int col, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return NULL; }
		format.book = book;
		return (CXText)sheet->readFormula(row, col, &format.format);
	}
	//@别名 取单元格公式(单元格,格式)
	//@参数 单元格 如“A1”
	CXText GetFormula(CXText cell, XLFormat& format = XLFormat())
	{
		if (sheet == NULL) { return NULL; }
		CELL rc = RC(cell);
		format.book = book;
		return (CXText)sheet->readFormula(rc.row, rc.col, &format.format);
	}
	//@别名 置单元格公式(行,列,公式,格式)
	//@备注 行列索引从0开始
	bool SetFormula(int row, int col, CXText  expr, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		return sheet->writeFormula(row, col, expr.get(), format.format);
	}
	//@别名 置单元格公式(单元格,公式,格式)
	//@参数 单元格 如“A1”
	bool SetFormula(CXText cell, CXText  expr, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->writeFormula(rc.row, rc.col, expr.get(), format.format);
	}
	//@别名 取单元格批注(行,列)
	//@备注 行列索引从0开始
	CXText GetComment(int row, int col)
	{
		if (sheet == NULL) { return NULL; }
		return (CXText)sheet->readComment(row,col);
	}
	//@别名 取单元格批注(单元格)
	//@参数 单元格 如“A1”
	CXText GetComment(CXText cell)
	{
		if (sheet == NULL) { return NULL; }
		CELL rc = RC(cell);
		return (CXText)sheet->readComment(rc.row, rc.col);
	}
	//@别名 置单元格批注(行,列,批注,作者,宽度,高度)
	//@备注 行列索引从0开始,仅支持XLS
	void SetComment(int row, int col, CXText value, CXText author = NULL, int width = 129, int height = 75)
	{
		if (sheet == NULL) { return; }
		sheet->writeComment(row, col, value, author, width, height);
	}
	//@别名 置单元格批注(单元格,批注,作者,宽度,高度)
	//@参数 单元格 如“A1”
	//@备注 仅支持XLS
	void SetComment(CXText cell, CXText value, CXText author = NULL, int width = 129, int height = 75)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->writeComment(rc.row, rc.col, value, author, width, height);
	}
	//@别名 删除单元格批注(行,列)
	//@备注 行列索引从0开始
	void DelComment(int row, int col)
	{
		if (sheet == NULL) { return; }
		sheet->removeComment(row, col);
	}
	//@别名 删除单元格批注(单元格)
	//@参数 单元格 如“A1”
	void DelComment(CXText cell)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->removeComment(rc.row, rc.col);
	}
	//@别名 取单元格错误(行,列)
	//@备注 行列索引从0开始
	XLErrorType GetError(int row, int col)
	{
		if (sheet == NULL) { return (XLErrorType) - 1; }
		return (XLErrorType)sheet->readError(row, col);
	}
	//@别名 取单元格错误(单元格)
	//@参数 单元格 如“A1”
	XLErrorType GetError(CXText cell)
	{
		if (sheet == NULL) { return (XLErrorType) - 1; }
		CELL rc = RC(cell);
		return (XLErrorType)sheet->readError(rc.row, rc.col);
	}
	//@别名 置单元格错误(行,列,错误,格式)
	//@备注 行列索引从0开始
	void SetError(int row, int col, XLErrorType error, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return; }
		sheet->writeError(row, col, (ErrorType)error, format.format);
	}
	//@别名 置单元格错误(单元格,错误,格式)
	//@参数 单元格 如“A1”
	void SetError(CXText cell, XLErrorType error, XLFormat format = XLFormat())
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->writeError(rc.row, rc.col, (ErrorType)error, format.format);
	}
	//@别名 取列宽(列)
	//@备注 列索引从0开始
	double GetColWidth(int col)
	{
		return sheet == NULL ? -1.0 : sheet->colWidth(col);
	}
	//@别名 取列宽(列名)
	//@参数 列名 如“A”
	double GetColWidth(CXText colname)
	{
		return sheet == NULL ? -1.0 : sheet->colWidth(L2N(colname));
	}
	//@别名 取行高(行)
	//@备注 行索引从0开始
	double GetRowHeight(int row)
	{
		return sheet == NULL ? -1.0 : sheet->rowHeight(row);
	}
	//@别名 取列宽像素(列)
	//@备注 列索引从0开始
	double GetColWidthPx(int col)
	{
		return sheet == NULL ? -1.0 : sheet->colWidthPx(col);
	}
	//@别名 取列宽像素(列名)
	//@参数 列名 如“A”
	double GetColWidthPx(CXText colname)
	{
		return sheet == NULL ? -1.0 : sheet->colWidthPx(L2N(colname));
	}
	//@别名 取行高像素(行)
	//@备注 行索引从0开始
	double GetRowHeightPx(int row)
	{
		return sheet == NULL ? -1.0 : sheet->rowHeightPx(row);
	}
	//@别名 置列宽(起始列,终止列,列宽,格式,隐藏)
	//@备注 列索引从0开始
	bool SetColWidth(int colFirst, int colLast, double width, XLFormat format = XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		if (colLast < colFirst) { colLast = colFirst; }
		return sheet->setCol(colFirst, colLast, width, format.format, hidden);
	}
	//@别名 置列宽(起始列名,终止列名,列宽,格式,隐藏)
	//@参数 列名 如“A”
	bool SetColWidth(CXText colFirst, CXText colLast, double width, XLFormat format = XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		int col1 = L2N(colFirst), col2 = L2N(colLast);
		if (col2 < col1) { col2 = col1; }
		return sheet->setCol(col1, col2, width, format.format, hidden);
	}
	//@别名 置列宽(列,列宽,格式,隐藏)
	//@备注 列索引从0开始
	bool SetColWidth(int col, double width, XLFormat format = XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		return sheet->setCol(col, col, width, format.format, hidden);
	}
	//@别名 置列宽(列名,列宽,格式,隐藏)
	//@参数 列名 如“A”
	bool SetColWidth(CXText col, double width, XLFormat format = XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		int c = L2N(col);
		return sheet->setCol(c, c, width, format.format, hidden);
	}
	//@别名 置行高(起始行,终止行,行高,格式,隐藏)
	//@备注 行索引从0开始
	bool SetRowHeight(int rowFirst, int rowLast, double height, XLFormat format =XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		if (rowLast < rowFirst) { return sheet->setRow(rowFirst, height, format.format, hidden); }
		for (int i = 0; i < rowLast; i++)
		{
			sheet->setRow(rowFirst + i, height, format.format, hidden);
		}
		return true;
	}
	//@别名 置行高(行,行高,格式,隐藏)
	//@备注 行索引从0开始
	bool SetRowHeight(int row, double height, XLFormat format = XLFormat(), bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		 return sheet->setRow(row, height, format.format, hidden);
	
	}
	//@别名 取行隐藏(行)
	//@备注 行索引从0开始
	bool  GetRowHidden(int row)
	{
		return sheet == NULL ? false : sheet->rowHidden(row);
	}
	//@别名 置行隐藏(行,隐藏)
	//@备注 行索引从0开始
	bool  SetRowHidden(int row, bool hidden = true)
	{
		return sheet == NULL ? false : sheet->setRowHidden(row, hidden);
	}
	//@别名 取列隐藏(列)
	//@备注 列索引从0开始
	bool GetColHidden(int col)
	{
		return sheet == NULL ? false : sheet->colHidden(col);
	}
	//@别名 取列隐藏(列)
	//@参数 列名 如“A”
	bool GetColHidden(CXText col)
	{
		return sheet == NULL ? false : sheet->colHidden(L2N(col));
	}
	//@别名 置列隐藏(列,隐藏)
	//@备注 列索引从0开始
	bool SetColHidden(int col, bool hidden = true)
	{
		return sheet == NULL ? false : sheet->setColHidden(col, hidden);
	}
	//@别名 置列隐藏(列,隐藏)
	//@参数 列名 如“A”
	bool SetColHidden(CXText col, bool hidden = true)
	{
		return sheet == NULL ? false : sheet->setColHidden(L2N(col), hidden);
	}
	//@别名 取单元格合并(行,列,起始行,终止行,起始列,终止列)
	//@备注 行列索引从0开始
	CXText GetMerge(int row, int col, int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (sheet == NULL) { return NULL; }
		if (sheet->getMerge(row, col, &rowFirst, &rowLast, &colFirst, &colLast) == false) { return NULL; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 取单元格合并(单元格,起始行,终止行,起始列,终止列)
	//@参数 单元格 如“A1”
	CXText GetMerge(CXText cell, int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (sheet == NULL) { return NULL; }
		CELL rc = RC(cell);
		if (sheet->getMerge(rc.row, rc.col, &rowFirst, &rowLast, &colFirst, &colLast) == false) { return NULL; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 置单元格合并(起始行,终止行,起始列,终止列)
	//@备注 索引从0开始
	bool SetMerge(int rowFirst, int rowLast, int colFirst, int colLast)
	{
		if (sheet == NULL) { return false; }
		return sheet->setMerge(rowFirst, rowLast, colFirst, colLast);
	}
	//@别名 置单元格合并(起始单元格,终止单元格)
	//@备注 起始、终止单元格 如“A1”
	bool SetMerge(CXText startCell, CXText endCell)
	{
		if (sheet == NULL) { return false; }
		CELL rc1 = RC(startCell), rc2 = RC(endCell);
		return sheet->setMerge(rc1.row, rc2.row, rc1.col, rc2.col);
	}
	//@别名 取消单元格合并(行,列)
	//@备注 索引从0开始
	bool DelMerge(int row, int col)
	{
		if (sheet == NULL) { return false; }
		return sheet->delMerge(row, col);
	}
	//@别名 取消单元格合并(单元格)
	//@参数 单元格 如“A1”
	bool DelMerge(CXText cell)
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->delMerge(rc.row, rc.col);
	}
	//@别名 取消单元格合并(索引)
	//@备注 索引从0开始
	bool DelMerge(int index)
	{
		return sheet == NULL ? false : sheet->delMergeByIndex(index);
	}
	//@别名 取单元格合并数量()
	int GetMergeCount()
	{
		return sheet == NULL ? -1 : sheet->mergeSize();
	}
	//@别名 取单元格合并(索引,起始行,终止行,起始列,终止列)
	//@备注 索引从0开始
	//@返回 返回单元格地址
	CXText GetMerge(int index, int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (sheet == NULL) { return L""; }
		if (sheet->merge(index, &rowFirst, &rowLast, &colFirst, &colLast) == false) { return L""; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 取图片数量()
	int GetpictureCount()
	{
		return sheet == NULL ? -1 : sheet->pictureSize();
	}
	//@别名 取图片信息(索引,顶行,左列,底行,右列,宽度,高度,水平偏移,垂直偏移)
	//@备注 索引从0开始
	int GetPicture(int index, int& rowTop, int& colLeft, int& rowBottom, int& colRight, int& width, int& height, int& offset_x, int& offset_y)
	{
		return sheet == NULL ? -1 : sheet->getPicture(index, &rowTop, &colLeft, &rowBottom, &colRight, &width, &height, &offset_x, &offset_y);
	}
	//@别名 删除图片(索引)
	//@备注 索引从0开始
	bool DelPicture(int index)
	{
		return sheet == NULL ? false : sheet->removePictureByIndex(index);
	}
	//@别名 置单元格图片(行,列,图片标识,缩放比例,水平偏移,垂直偏移,属性)
	//@备注 行列索引从0开始
	void SetPicture(int row, int col, int pictureId, double scale = 1.0, int offset_x = 0, int offset_y = 0, XLPosition pos = XLPOSITION_MOVE_AND_SIZE)
	{
		if (sheet == NULL) { return; }
		sheet->setPicture(row, col, pictureId, scale, offset_x, offset_y, (Position)pos);
	}
	//@别名 置单元格图片(单元格,图片标识,缩放比例,水平偏移,垂直偏移,属性)
	//@参数 单元格 如“A1”
	void SetPicture(CXText cell, int pictureId, double scale = 1.0, int offset_x = 0, int offset_y = 0, XLPosition pos = XLPOSITION_MOVE_AND_SIZE)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->setPicture(rc.row, rc.col, pictureId, scale, offset_x, offset_y, (Position)pos);
	}
	//@别名 置单元格图片(行,列,图片标识,宽度,高度,水平偏移,垂直偏移,属性)
	//@备注 行列索引从0开始
	void SetPicture(int row, int col, int pictureId, int width = -1, int height = -1, int offset_x = 0, int offset_y = 0, XLPosition pos = XLPOSITION_MOVE_AND_SIZE)
	{
		if (sheet == NULL) { return; }
		sheet->setPicture2(row, col, pictureId, width, height, offset_x, offset_y, (Position)pos);
	}
	//@别名 置单元格图片(单元格,图片标识,宽度,高度,水平偏移,垂直偏移,属性)
	//@参数 单元格 如“A1”
	void SetPicture(CXText cell, int pictureId, int width = -1, int height = -1, int offset_x = 0, int offset_y = 0, XLPosition pos = XLPOSITION_MOVE_AND_SIZE)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->setPicture2(rc.row, rc.col, pictureId, width, height, offset_x, offset_y, (Position)pos);
	}
	//@别名 删除图片(行,列)
	//@备注 行列索引从0开始
	bool DelPicture(int row, int col)
	{
		if (sheet == NULL) { return false; }
		return sheet->removePicture(row, col);
	}
	//@别名 删除图片(单元格)
	//@参数 单元格 如“A1”
	bool DelPicture(CXText cell)
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		return sheet->removePicture(rc.row, rc.col);
	}
	//@别名 取水平分页符数量()
	int GetHorPageBreakCount()
	{
		return sheet == NULL ? -1 : sheet->getHorPageBreakSize();
	}
	//@别名 取水平分页符(索引)
	//@备注 索引从0开始
	int GetHorPageBreak(int index)
	{
		return sheet == NULL ? -1 : sheet->getHorPageBreak(index);
	}
	//@别名 取垂直分页符数量()
	int GetVerPageBreakCount()
	{
		return sheet == NULL ? -1 : sheet->getVerPageBreakSize();
	}
	//@别名 取垂直分页符(索引)
	//@备注 索引从0开始
	int GetVerPageBreak(int index)
	{
		return sheet == NULL ? -1 : sheet->getVerPageBreak(index);
	}
	//@别名 置水平分页符(行,分页符)
	//@备注 行索引从0开始
	bool SetHorPageBreak(int row, bool pageBreak = true)
	{
		return sheet == NULL ? false : sheet->setHorPageBreak(row, pageBreak);
	}
	//@别名 置垂直分页符(列,分页符)
	//@备注 列索引从0开始
	bool SetVerPageBreak(int col, bool pageBreak = true)
	{
		return sheet == NULL ? false : sheet->setVerPageBreak(col, pageBreak);
	}
	//@别名 置垂直分页符(列名,分页符)
	//@参数 列名 如“A”
	bool SetVerPageBreak(CXText col, bool pageBreak = true)
	{
		return sheet == NULL ? false : sheet->setVerPageBreak(L2N(col), pageBreak);
	}
	//@别名 置单元格冻结(行,列)
	//@备注 列索引从0开始
	void SetSplit(int row, int col)
	{
		if (sheet == NULL) { return; }
		sheet->split(row, col);
	}
	//@别名 置单元格冻结(单元格)
	//@参数 单元格 如“A1”
	void SetSplit(CXText cell)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->split(rc.row, rc.col);
	}
	//@别名 取单元格冻结(行,列)
	//@返回 返回单元格地址
	CXText GetSplit(int& row, int& col)
	{
		if (sheet == NULL) { return NULL; }
		if (sheet->splitInfo(&row, &col) == false) { return NULL; }
		return (CXText)sheet->rowColToAddr(row, col);
	}
	//@别名 置行分组(起始行,终止行,折叠)
	//@备注 索引从0开始
	bool SetGroupRows(int row1, int row2, bool collapsed = false)
	{
		if (sheet == NULL) { return false; }
		if (row2 < row1) { row2 = row1; }
		return sheet->groupRows(row1, row2, collapsed);
	}
	//@别名 置列分组(起始列,终止列,折叠)
	//@备注 索引从0开始
	bool SetGroupCols(int col1, int col2, bool collapsed = false)
	{
		if (sheet == NULL) { return false; }
		if (col2 < col1) { col2 = col1; }
		return sheet->groupCols(col1, col2, collapsed);
	}
	//@别名 置列分组(起始列名,终止列名,折叠)
	//@备注 列名 如“A”
	bool SetGroupCols(CXText col1, CXText col2, bool collapsed = false)
	{
		if (sheet == NULL) { return false; }
		int r1 = L2N(col1), r2 = L2N(col2);
		if (r2 < r1) { r2 = r1; }
		return sheet->groupCols(r1, r2, collapsed);
	}
	//@别名 取行分组标志方向()
	//@备注 返回分组行标志要是否在下面
	bool GetGroupSummaryBelow()
	{
		return sheet == NULL ? false : sheet->groupSummaryBelow();
	}
	//@别名 置行分组标志方向(下方)
	void SetGroupSummaryBelow(bool below)
	{
		if (sheet != NULL) { sheet->setGroupSummaryBelow(below); }
	}
	//@别名 取列分组标志方向()
	//@备注 返回列分组标志是否在右侧
	bool GetGroupSummaryRight()
	{
		return sheet == NULL ? false : sheet->groupSummaryRight();
	}
	//@别名 置列分组标志方向(右侧)
	void SetGroupSummaryRight(bool below)
	{
		if (sheet != NULL) { sheet->setGroupSummaryRight(below); }
	}
	//@别名 清除单元格(起始行,终止行,起始列,终止列)
	//@备注 行列索引为0开始
	bool Clear(int row, int row1, int col, int col1)
	{
		if (sheet == NULL) { return false; }
		return sheet->clear(row, row1, col, col1);
	}
	//@别名 清除单元格(起始单元格,终止单元格)
	//@备注 单元格 如“A1”
	bool Clear(CXText cell, CXText cell1)
	{
		if (sheet == NULL) { return false; }
		CELL rc= RC(cell), rc1 = RC(cell1);
		return sheet->clear(rc.row, rc1.row, rc.col, rc1.col);
	}
	//@别名 插入行(起始插入行,插入行数,更新命名)
	//@备注 行索引为0开始
	bool InsertRow(int row, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		return sheet->insertRow(row, row + index - 1, updateNamedRanges);
	}
	//@别名 插入列(起始插入列,插入列数,更新命名)
	//@备注 列索引为0开始
	bool InsertCol(int col, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		return sheet->insertCol(col, col + index - 1, updateNamedRanges);
	}
	//@别名 插入列(起始插入列名,插入列数,更新命名)
	//@备注 列名 如“A”
	bool InsertCol(CXText col, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		int c = L2N(col);
		return sheet->insertCol(c, c + index - 1, updateNamedRanges);
	}
	//@别名 删除行(起始删除行,删除行数,更新命名)
	//@备注 行索引为0开始
	bool DelRow(int row, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		return sheet->removeRow(row, row + index - 1, updateNamedRanges);
	}
	//@别名 删除列(起始删除列,删除列数,更新命名)
	//@备注 列索引为0开始
	bool DelCol(int col, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		return sheet->removeCol(col, col + index - 1, updateNamedRanges);
	}
	//@别名 删除列(起始删除列名,删除列数,更新命名)
	//@备注 列名 如“A”
	bool DelCol(CXText col, int index = 1, bool updateNamedRanges = true)
	{
		if (sheet == NULL) { return false; }
		int c = L2N(col);
		return sheet->removeCol(c, c + index - 1, updateNamedRanges);
	}
	//@别名 复制粘贴(复制行,复制列,粘贴行,粘贴列)
	//@备注 行列索引为0开始
	bool CopyCell(int row, int col, int row1, int col1)
	{
		if (sheet == NULL) { return false; }
		return sheet->copyCell(row, col, row1, col1);
	}
	//@别名 复制粘贴(复制单元格,粘贴单元格)
	//@参数 单元格 如“A1”
	bool CopyCell(CXText cell, CXText cell1)
	{
		if (sheet == NULL) { return false; }
		CELL rc = RC(cell);
		CELL rc1 = RC(cell1);
		return sheet->copyCell(rc.row, rc.col, rc1.row, rc1.col);
	}
	//@别名 开始使用行(忽略空白单元格)
	int StartUsingRow(bool IgnoreWhitespace = true)
	{
		if (sheet == NULL) { return -1; }
		if (IgnoreWhitespace) { return sheet->firstFilledRow(); }
		else { return sheet->firstRow(); }
	}
	//@别名 开始使用列(忽略空白单元格)
	int StartUsingCol(bool IgnoreWhitespace = true)
	{
		if (sheet == NULL) { return -1; }
		if (IgnoreWhitespace) { return sheet->firstFilledCol(); }
		else { return sheet->firstCol(); }
	}
	//@别名 结束使用行(忽略空白单元格)
	int EndUseRow(bool IgnoreWhitespace = true)
	{
		if (sheet == NULL) { return -1; }
		if (IgnoreWhitespace) { return sheet->lastFilledRow(); }
		else { return sheet->lastRow(); }
	}
	//@别名 结束使用列(忽略空白单元格)
	int EndUseCol(bool IgnoreWhitespace = true)
	{
		if (sheet == NULL) { return -1; }
		if (IgnoreWhitespace) { return sheet->lastFilledCol(); }
		else { return sheet->lastCol(); }
	}
	//@别名 显示网格线()
	bool DisplayGridlines()
	{
		return sheet == NULL ? false : sheet->displayGridlines();
	}
	//@别名 显示网格线(显示网格线)
	void DisplayGridlines(bool show)
	{
		if (sheet != NULL) { sheet->setDisplayGridlines(show); }
	}
	//@别名 打印网格线()
	bool PrintGridlines()
	{
		return sheet == NULL ? false : sheet->printGridlines();
	}
	//@别名 打印网格线(打印网格线)
	void PrintGridlines(bool print)
	{
		if (sheet != NULL) { sheet->setPrintGridlines(print); }
	}
	//@别名 缩放比例()
	int Zoom()
	{
		return sheet == NULL ? -1 : sheet->zoom();
	}
	//@别名 缩放比例(缩放比例)
	void Zoom(int zoom)
	{
		if (sheet != NULL) { sheet->setZoom(zoom); }
	}
	//@别名 打印缩放比例()
	int PrintZoom()
	{
		return sheet == NULL ? -1 : sheet->printZoom();
	}
	//@别名 打印缩放比例(缩放比例)
	void PrintZoom(int zoom)
	{
		if (sheet != NULL) { sheet->setPrintZoom(zoom); }
	}
	//@别名 取打印适合页面(宽度适合页数,高度适合页数)
	bool PrintFit(int& wPages, int& hPages)
	{
		return sheet == NULL ? false : sheet->getPrintFit(&wPages, &hPages);
	}
	//@别名 置打印适合页面(宽度适合页数,高度适合页数)
	void PrintFit(int wPages = 1, int hPages = 1)
	{
		if (sheet != NULL) { sheet->setPrintFit(wPages, hPages); }
	}
	//@别名 横向模式()
	bool Landscape()
	{
		return sheet == NULL ? false : sheet->landscape();
	}
	//@别名 横向模式(横向)
	void Landscape(bool landscape)
	{
		if (sheet != NULL) { sheet->setLandscape(landscape); }
	}
	//@别名 纸张尺寸()
	XLPaper Paper()
	{
		return sheet == NULL ? (XLPaper)-1 : (XLPaper)sheet->paper();
	}
	//@别名 纸张尺寸(纸张尺寸)
	void Paper(XLPaper paper)
	{
		if (sheet != NULL) { sheet->setPaper((::Paper)paper); }
	}
	//@别名 取页眉()
	CXText GetHeader()
	{
		return sheet == NULL ? NULL : (CXText)sheet->header();
	}
	//@别名 置页眉(页眉,页眉边距)
	bool  SetHeader(CXText header, double margin = 0.5)
	{
		return sheet == NULL ? false : sheet->setHeader(header.get(), margin);
	}
	//@别名 取页眉边距()
	double GetHeaderMargin()
	{
		return sheet == NULL ? -1.0 : sheet->headerMargin();
	}
	//@别名 取页脚()
	CXText GetFooter()
	{
		return sheet == NULL ? NULL : (CXText)sheet->footer();
	}
	//@别名 置页脚(页脚,页脚边距)
	bool SetFooter(CXText footer, double margin = 0.5)
	{
		return sheet == NULL ? false : sheet->setFooter(footer.get(), margin);
	}
	//@别名 取页脚边距()
	double GetFooterMargin()
	{
		return sheet == NULL ? -1.0 : sheet->footerMargin();
	}
	//@别名 打印水平居中()
	bool HCenter()
	{
		return sheet == NULL ? false : sheet->hCenter();
	}
	//@别名 打印水平居中(水平居中)
	void HCenter(bool hCenter)
	{
		if (sheet != NULL) { sheet->setHCenter(hCenter); }
	}
	//@别名 打印垂直居中()
	bool VCenter()
	{
		return sheet == NULL ? false : sheet->vCenter();
	}
	//@别名 打印垂直居中(垂直居中)
	void VCenter(bool hCenter)
	{
		if (sheet != NULL) { sheet->setVCenter(hCenter); }
	}
	//@别名 左页边距()
	double MarginLeft()
	{
		return sheet == NULL ? -1.0 : sheet->marginLeft();
	}
	//@别名 左页边距(页边距)
	void MarginLeft(double margin)
	{
		if (sheet != NULL) { sheet->setMarginLeft(margin); }
	}
	//@别名 右页边距()
	double MarginRight()
	{
		return sheet == NULL ? -1.0 : sheet->marginRight();
	}
	//@别名 右页边距(页边距)
	void MarginRight(double margin)
	{
		if (sheet != NULL) { sheet->setMarginRight(margin); }
	}
	//@别名 上页边距()
	double MarginTop()
	{
		return sheet == NULL ? -1.0 : sheet->marginTop();
	}
	//@别名 上页边距(页边距)
	void MarginTop(double margin)
	{
		if (sheet != NULL) { sheet->setMarginTop(margin); }
	}
	//@别名 下页边距()
	double MarginBottom()
	{
		return sheet == NULL ? -1.0 : sheet->marginBottom();
	}
	//@别名 下页边距(页边距)
	void MarginBottom(double margin)
	{
		if (sheet != NULL) { sheet->setMarginBottom(margin); }
	}
	//@别名 打印行列标题()
	bool PrintRowCol()
	{
		return sheet == NULL ? false : sheet->printRowCol();
	}
	//@别名 打印行列标题(打印)
	void PrintRowCol(bool print)
	{
		if (sheet != NULL) { sheet->setPrintRowCol(print); }
	}
	//@别名 取打印行标题(起始行,终止行)
	bool GetPrintRepeatRows(int& rowFirst, int& rowLast)
	{
		return sheet == NULL ? false : sheet->printRepeatRows(&rowFirst, &rowLast);
	}
	//@别名 置打印行标题(起始行,终止行)
	void SetPrintRepeatRows(int rowFirst, int rowLast)
	{
		if (sheet == NULL) { return; }
		if (rowLast < rowFirst) { rowLast = rowFirst; }
		sheet->setPrintRepeatRows(rowFirst, rowLast);
	}
	//@别名 取打印列标题(起始列,终止列)
	bool GetPrintRepeatCols(int& rowFirst, int& rowLast)
	{
		return sheet == NULL ? false : sheet->printRepeatCols(&rowFirst, &rowLast);
	}
	//@别名 置打印列标题(起始列,终止列)
	void SetPrintRepeatCols(int colFirst, int colLast)
	{
		if (sheet == NULL) { return; }
		if (colLast < colFirst) { colLast = colFirst; }
		sheet->setPrintRepeatCols(colFirst, colLast);
	}
	//@别名 置打印列标题(起始列名,终止列名)
	void SetPrintRepeatCols(CXText colFirst, CXText colLast)
	{
		if (sheet == NULL) { return; }
		int c = L2N(colFirst), c1 = L2N(colLast);
		if (c1 < c) { c1 = c; }
		sheet->setPrintRepeatCols(c, c1);
	}
	//@别名 取打印区域(起始行,终止行,起始列,终止列)
	//@备注 返回单元格地址
	CXText GetPrintArea(int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		if (sheet == NULL) { return NULL; }
		if (sheet->printArea(&rowFirst, &rowLast, &colFirst, &colLast) == false) { return NULL; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 置打印区域(起始行,终止行,起始列,终止列)
	//@备注 行列索引为0开始
	void SetPrintArea(int row, int row1, int col, int col1)
	{
		if (sheet == NULL) { return; }
		sheet->setPrintArea(row, row1, col, col1);
	}
	//@别名 置打印区域(起始单元格,终止单元格)
	//@参数 单元格 如“A1”
	void SetPrintArea(CXText cell, CXText cell1)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell), rc1 = RC(cell1);
		sheet->setPrintArea(rc.row, rc1.row, rc.col, rc1.col);
	}
	//@别名 清除打印标题()
	void ClearPrintRepeats()
	{
		if (sheet != NULL) { sheet->clearPrintRepeats(); }
	}
	//@别名 清除打印区域()
	void ClearPrintArea()
	{
		if (sheet != NULL) { sheet->clearPrintArea(); }
	}
	//@别名 取定义名称(名称,范围,起始行,终止行,起始列,终止列,是否隐藏)
	//@备注 返回单元格地址
	CXText GetNamedRange(CXText name, int scopeId, int& rowFirst, int& rowLast, int& colFirst, int& colLast,  bool& hidden)
	{
		if (sheet == NULL) { return NULL; }
		if (sheet->getNamedRange(name.get(), &rowFirst, &rowLast, &colFirst, &colLast, scopeId, &hidden) == false) { return NULL; }
		CXText ret = sheet->rowColToAddr(rowFirst, colFirst);
		ret.append(L":");
		ret.append(sheet->rowColToAddr(rowLast, colLast));
		return ret;
	}
	//@别名 置定义名称(起始行,终止行,起始列,终止列,名称,范围,是否隐藏)
	//@备注 行列索引为0开始
	//@参数 范围 -1为全局  -2为局部
	bool SetNamedRange(int rowFirst, int rowLast, int colFirst, int colLast, CXText name, int scopeId = -1, bool hidden=false)
	{
		if (sheet == NULL) { return false; }
		return sheet->setNamedRange(name.get(), rowFirst, rowLast, colFirst, colLast, scopeId, hidden);
	}
	//@别名 置定义名称(起始单元格,终止单元格,名称,范围,是否隐藏)
	//@参数 单元格 如“A1”
	//@参数 范围 -1为全局  -2为局部
	bool SetNamedRange(CXText startCell, CXText endCell, CXText name, int scopeId = -1, bool hidden = false)
	{
		if (sheet == NULL) { return false; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		return sheet->setNamedRange(name.get(), rc.row, rc1.row, rc.col, rc1.col, scopeId, hidden);
	}
	//@别名 删除定义名称(名称,范围)
	//@参数 范围 -1为全局  -2为局部
	bool DelNamedRange(CXText name, int scopeId)
	{
		return sheet == NULL ? false : sheet->delNamedRange(name.get(), scopeId);
	}
	//@别名 取定义名称数量()
	int GetNamedRangeCount()
	{
		return sheet == NULL ? -1 : sheet->namedRangeSize();
	}
	//@别名 取定义名称(索引,范围,起始行,终止行,起始列,终止列,是否隐藏)
	CXText GetNamedRange(int index, int& rowFirst, int& rowLast, int& colFirst, int& colLast, int& scopeId, bool& hidden)
	{
		return sheet == NULL ? NULL : sheet->namedRange(index, &rowFirst, &rowLast, &colFirst, &colLast, &scopeId, &hidden);

	}
	//@别名 取表数量()
	int GetTableCount()
	{
		return sheet == NULL ? -1 : sheet->tableSize();
	}
	//@别名 取表参数(索引,起始行,终止行,起始列,终止列,标题行数,总计行数)
	CXText GetTable(int index, int& rowFirst, int& rowLast, int& colFirst, int& colLast, int& headerRowCount, int& totalsRowCount)
	{
		return sheet == NULL ? NULL : sheet->table(index, &rowFirst, &rowLast, &colFirst, &colLast, &headerRowCount, &totalsRowCount);
	}
	//@别名 取超链接数量()
	int GetHyperlinkCount()
	{
		return sheet == NULL ? -1 : sheet->hyperlinkSize();
	}
	//@别名 取超链接(索引,起始行,终止行,起始列,终止列)
	CXText GetHyperlink(int index, int& rowFirst, int& rowLast, int& colFirst, int& colLast)
	{
		return sheet == NULL ? NULL : sheet->hyperlink(index, &rowFirst, &rowLast, &colFirst, &colLast);
	}
	//@别名 删除超链接(索引)
	bool DelHyperlink(int index)
	{
		return sheet == NULL ? false : sheet->delHyperlink(index);
	}
	//@别名 添加超链接(起始行,终止行,起始列,终止列,超链接)
	//@备注 行列为0开始
	void AddHyperlink(int rowFirst, int rowLast, int colFirst, int colLast, CXText hyperlink)
	{
		if (sheet == NULL) { return; }
		sheet->addHyperlink(hyperlink.get(), rowFirst, rowLast, colFirst, colLast);
	}
	//@别名 添加超链接(起始单元格,终止单元格,超链接)
	//@备注 单元格 如“A1”
	void AddHyperlink(CXText startCell, CXText endCell, CXText hyperlink)
	{
		if (sheet == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		sheet->addHyperlink(hyperlink.get(), rc.row, rc1.row, rc.col, rc1.col);
	}
	//@别名 取自动筛选()
	XLAutoFilter GetAutoFilter()
	{
		XLAutoFilter ret{};
		if (sheet == NULL) { return ret; }
		ret.autoFilter = sheet->autoFilter();
		ret.sheet = sheet;
		return ret;
	}
	//@别名 置自动筛选()
	void SetAutoFilter()
	{
		if (sheet != NULL) { sheet->applyFilter(); }
	}
	//@别名 删除自动筛选()
	void DelAutoFilter()
	{
		if (sheet != NULL) { sheet->removeFilter(); }
	}
	//@别名 取名称()
	CXText GetName()
	{
		return sheet == NULL ? NULL : sheet->name();
	}
	//@别名 置名称(名称)
	void SetName(CXText name)
	{
		if (sheet != NULL) { sheet->setName(name.get()); }
	}
	//@别名 取保护()
	bool GetProtect()
	{
		return sheet == NULL ? false : sheet->protect();
	}

	//@别名 置保护(保护,密码,增强保护)
	void SetProtect(bool protect, CXText password, XLEnhancedProtection prot)
	{
		if (sheet != NULL) { sheet->setProtect(protect, password.get(), (EnhancedProtection)prot); }
	}
	//@别名 右到左显示模式()
	bool GetRightToLeft()
	{
		return sheet == NULL ? false : sheet->rightToLeft();
	}

	//@别名 右到左显示模式(设置)
	void SetRightToLeft(bool rightToLeft)
	{
		if (sheet != NULL) { sheet->setRightToLeft(rightToLeft); }
	}
	//@别名 隐藏模式()
	XLSheetState GetHidden()
	{
		return sheet == NULL ? (XLSheetState) - 1 : (XLSheetState)sheet->hidden();
	}

	//@别名 隐藏模式(隐藏模式)
	bool SetHidden(XLSheetState state)
	{
		return sheet == NULL ? false : sheet->setHidden((SheetState)state);
	}
	//@别名 取首见单元格(行,列)
	CXText GetTopLeftView(int& row, int& col)
	{
		if (sheet == NULL) { return NULL; }
		sheet->getTopLeftView(&row, &col);
		return sheet->rowColToAddr(row, col);
	}

	//@别名 置首见单元格(行,列)
	//@备注 行列索引为0开始
	void SetTopLeftView(int row, int col)
	{
		if (sheet == NULL) { return; }
		sheet->setTopLeftView(row, col);
	}
	//@别名 置首见单元格(单元格)
	//@参数 单元格 如“A1”
	void SetTopLeftView(CXText cell)
	{
		if (sheet == NULL) { return; }
		CELL rc = RC(cell);
		sheet->setTopLeftView(rc.row, rc.col);
	}
	//@别名 置自动调整列宽(起始行,终止行,起始列,终止列)
	//@备注 行列索引为0开始
	void SetAutoFitArea(int rowFirst, int rowLast, int colFirst, int colLast)
	{
		if (sheet == NULL) { return; }
		sheet->setAutoFitArea(rowFirst, colFirst, rowLast, colLast);
	}
	//@别名 置自动调整列宽(起始单元格,终止单元格)
	//@备注 单元格 如“A1”
	void SetAutoFitArea(CXText startCell, CXText endCell)
	{
		if (sheet == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		sheet->setAutoFitArea(rc.row, rc.col, rc1.row, rc1.col);
	}
	//@别名 置标签颜色(颜色)
	void  SetTabColor(int clr)
	{
		if (sheet != NULL) { sheet->setTabColor(IntToClr(clr)); }
	}
	//@别名 置标签RGB颜色(红色,绿色,蓝色)
	void  SetTabColor(int r, int g, int b)
	{
		if (sheet != NULL) { sheet->setTabColor(r, g, b); }
	}
	//@别名 忽略错误(起始行,终止行,起始列,终止列,错误值)
	//@备注 行列索引为0开始
	bool IgnoredError(int rowFirst, int rowLast, int colFirst, int colLast, XLIgnoredError iError = XLIERR_IGNORE_ALL)
	{
		if (sheet == NULL) { return false; }
		return sheet->addIgnoredError(rowFirst, colFirst, rowLast, colLast, (::IgnoredError)iError);
	}
	//@别名 忽略错误(起始单元格,终止单元格,错误值)
	//@备注 单元格 如“A1”
	bool IgnoredError(CXText startCell, CXText endCell, XLIgnoredError iError = XLIERR_IGNORE_ALL)
	{
		if (sheet == NULL) { return false; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		return sheet->addIgnoredError(rc.row, rc.col, rc1.row, rc1.col, (::IgnoredError)iError);
	}
	//@别名 添加数据验证(起始行,终止行,起始列,终止列,数据验证的类型,关系运算符,值1,值2,允许空白,下拉组合框,显示提示信息,显示错误消息,提示标题,提示文本,错误标题,错误文本,错误图标)
	//@备注 行列索引为0开始
	void AddDataValidation(int rowFirst, int rowLast, int colFirst, int colLast, XLDataValidationType type, XLDataValidationOperator op, CXText value1, CXText value2, bool allowBlank = true, bool hideDropDown=false, bool showInputMessage=true, bool showErrorMessage=true, CXText promptTitle = NULL, CXText prompt=NULL, CXText errorTitle=NULL, CXText error=NULL, XLDataValidationErrorStyle errorStyle= XLVALIDATION_ERRSTYLE_INFORMATION)
	{
		if (sheet == NULL) { return; }
		sheet->addDataValidation((DataValidationType)type, (DataValidationOperator)op, rowFirst, rowLast, colFirst, colLast, value1.get(), value2.get(), allowBlank, hideDropDown, showInputMessage, showErrorMessage, promptTitle.get(), prompt.get(), errorTitle.get(), error.get(), (DataValidationErrorStyle)errorStyle);
	}
	//@别名 添加数据验证(起始单元格,终止单元格,数据验证的类型,关系运算符,值1,值2,允许空白,下拉组合框,显示提示信息,显示错误消息,提示标题,提示文本,错误标题,错误文本,错误图标)
	//@备注 单元格 如“A1”
	void AddDataValidation(CXText startCell, CXText endCell, XLDataValidationType type, XLDataValidationOperator op, CXText value1, CXText value2, bool allowBlank = true, bool hideDropDown = false, bool showInputMessage = true, bool showErrorMessage = true, CXText promptTitle = NULL, CXText prompt = NULL, CXText errorTitle = NULL, CXText error = NULL, XLDataValidationErrorStyle errorStyle = XLVALIDATION_ERRSTYLE_INFORMATION)
	{
		if (sheet == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		sheet->addDataValidation((DataValidationType)type, (DataValidationOperator)op, rc.row, rc1.row, rc.col, rc1.col, value1.get(), value2.get(), allowBlank, hideDropDown, showInputMessage, showErrorMessage, promptTitle.get(), prompt.get(), errorTitle.get(), error.get(), (DataValidationErrorStyle)errorStyle);
	}
	//@别名 添加数据验证(起始行,终止行,起始列,终止列,数据验证的类型,关系运算符,值1,值2,允许空白,下拉组合框,显示提示信息,显示错误消息,提示标题,提示文本,错误标题,错误文本,错误图标)
//@备注 行列索引为0开始
	void AddDataValidation(int rowFirst, int rowLast, int colFirst, int colLast, XLDataValidationType type, XLDataValidationOperator op, double value1, double value2, bool allowBlank = true, bool hideDropDown = false, bool showInputMessage = true, bool showErrorMessage = true, CXText promptTitle = NULL, CXText prompt = NULL, CXText errorTitle = NULL, CXText error = NULL, XLDataValidationErrorStyle errorStyle = XLVALIDATION_ERRSTYLE_INFORMATION)
	{
		if (sheet == NULL) { return; }
		sheet->addDataValidationDouble((DataValidationType)type, (DataValidationOperator)op, rowFirst, rowLast, colFirst, colLast, value1, value2, allowBlank, hideDropDown, showInputMessage, showErrorMessage, promptTitle.get(), prompt.get(), errorTitle.get(), error.get(), (DataValidationErrorStyle)errorStyle);
	}
	//@别名 添加数据验证(起始单元格,终止单元格,数据验证的类型,关系运算符,值1,值2,允许空白,下拉组合框,显示提示信息,显示错误消息,提示标题,提示文本,错误标题,错误文本,错误图标)
	//@备注 单元格 如“A1”
	void AddDataValidation(CXText startCell, CXText endCell, XLDataValidationType type, XLDataValidationOperator op, double value1, double value2, bool allowBlank = true, bool hideDropDown = false, bool showInputMessage = true, bool showErrorMessage = true, CXText promptTitle = NULL, CXText prompt = NULL, CXText errorTitle = NULL, CXText error = NULL, XLDataValidationErrorStyle errorStyle = XLVALIDATION_ERRSTYLE_INFORMATION)
	{
		if (sheet == NULL) { return; }
		CELL  rc = RC(startCell), rc1 = RC(endCell);
		sheet->addDataValidationDouble((DataValidationType)type, (DataValidationOperator)op, rc.row, rc1.row, rc.col, rc1.col, value1, value2, allowBlank, hideDropDown, showInputMessage, showErrorMessage, promptTitle.get(), prompt.get(), errorTitle.get(), error.get(), (DataValidationErrorStyle)errorStyle);
	}
	//@别名 删除数据验证()
	void  DelDataValidation()
	{
		if (sheet != NULL) { sheet->removeDataValidations(); }
	}
	//@别名 取表单控件数量()
	int  GetFormControlCount()
	{
		return sheet == NULL ? -1 : sheet->formControlSize();
	}
	//@别名 取表单控件(索引)
	XLFormControl GetFormControl(int index)
	{
		XLFormControl formControl{};
		if (sheet == NULL) { return formControl; }
		formControl.formControl = sheet->formControl(index);
		return formControl;
	}



};
















//@别名 XL工作簿类
class XLBook
{
private:
	Book* book{NULL};
public:

	//@别名 新建文件(文件类型)
	bool NewFile(XLFileType Type)
	{
		if (XLFILETYPE_XLS == Type)
		{
			book = xlCreateBookW();
		}
		if (XLFILETYPE_XLSX == Type)
		{
			book = xlCreateXMLBookW();
		}
		if (book == NULL) { return false; }
		book->setKey(L"XcKey", L"windows-222224040aceee0360bc6b64a8mbr2df");
		book->setRgbMode(true);
		return true;
	};
	//@别名 打开文件(路径)
	bool OpenFile(CXText filename)
	{
		if (NewFile(XLFILETYPE_XLS))
		{
			if (book->load(filename.get()) != 0) { return true; }
			book->release();
		}
		if (NewFile(XLFILETYPE_XLSX))
		{
			if (book->load(filename.get()) != 0) { return true; }
			book->release();
		}
		return false;
	};
	//@别名 保存文件(路径)
	bool SaveFile(CXText filename)
	{
		if (book == NULL) { return false; }
		if (book->sheetCount() == 0) { book->addSheet(L"Sheet1"); }
		return book->save(filename.get());
	};

	//@别名 添加工作表(工作表名,初始工作表)
	XLSheet AddSheet(CXText name, XLSheet  initSheet = XLSheet())
	{
		XLSheet ret{};
		if (book == NULL) { return ret; }
		ret.book = book;
		ret.sheet = book->addSheet(name.get(), initSheet.sheet);
		return ret;
	};
	//@别名 插入工作表(工作表名,插入在此工作表前,初始工作表)
	XLSheet InsertSheet(CXText name, int index, XLSheet initSheet = XLSheet())
	{
		XLSheet ret{};
		if (book == NULL) { return ret; }
		ret.book = book;
		ret.sheet = book->insertSheet(index, name.get(), initSheet.sheet);
		return ret;
	};
	//@别名 选择工作表(工作表索引)
	XLSheet SelectSheet(int index)
	{
		XLSheet ret{};
		if (book == NULL) { return ret; }
		ret.book = book;
		ret.sheet = book->getSheet(index);
		return ret;
	};
	//@别名 取工作表名(工作表索引)
	CXText GetSheetName(int index)
	{
		return book == NULL ? NULL : (CXText)book->getSheetName(index);
	}
	//@别名 取活动工作表()
	XLSheet GetActiveSheet()
	{
		XLSheet ret{};
		if (book == NULL) { return ret; }
		ret.sheet = book->getSheet(book->activeSheet());
		ret.book = book;
		return ret;
	}
	//@别名 置活动工作表(工作表索引)
	void SetActiveSheet(int index)
	{
		if (book != NULL) { book->setActiveSheet(index); }
	}
	//@别名 取工作类型(工作表索引)
	int GetSheetType(int index)
	{
		return book == NULL ? -1 : book->sheetType(index);
	}
	//@别名 移动工作表(要移动的工作表索引,移动到此工作表前)
	bool MoveSheet(int srcIndex, int dstIndex)
	{
		return book == NULL ? false : book->moveSheet(srcIndex, dstIndex);
	}
	//@别名 删除工作表(工作表索引)
	bool DelSheet(int index)
	{
		return book == NULL ? false : book->delSheet(index);
	}
	//@别名 取工作表数()
	int GetSheetCount()
	{
		return book == NULL ? -1 : book->sheetCount();
	}
	//@别名 添加格式(初始格式)
	XLFormat AddFormat(XLFormat format = XLFormat())
	{
		XLFormat ret{};
		if (book == NULL) { return ret; }
		ret.format = book->addFormat(format.format);
		ret.book = book;
		return ret;
	}
	//@别名 添加字体(初始字体)
	XLFont AddFont(XLFont font = XLFont())
	{
		XLFont ret{};
		if (book == NULL) { return ret; }
		ret.font = book->addFont(font.font);
		ret.book = book;
		return ret;
	}

	//@别名 添加富文本()
	XLRichstr AddRichStr()
	{
		XLRichstr ret{};
		if (book == NULL) { return ret; }
		ret.richstr = book->addRichString();
		ret.book = book;
		return ret;
	}
	//@别名 添加自定义数字格式(自定义数字格式)
	int AddCustomNumFormat(CXText customNumFormat)
	{
		return book == NULL ? -1 : book->addCustomNumFormat(customNumFormat.get());
	}
	//@别名 取自定义数字格式(标识符)
	CXText GetCustomNumFormat(int fmt)
	{
		return book == NULL ? NULL : (CXText)book->customNumFormat(fmt);
	}
	//@别名 取格式数量()
	int GetFormatCount()
	{
		return book == NULL ? -1 : book->formatSize();
	}
	//@别名 取格式(格式索引)
	XLFormat GetFormat(int index)
	{
		XLFormat ret{};
		if (book == NULL) { return ret; }
		ret.format = book->format(index);
		ret.book = book;
		return ret;
	}
	//@别名 取字体数量()
	int GetFontCount()
	{
		return book == NULL ? -1 : book->fontSize();
	}
	//@别名 取字体(字体索引)
	XLFont GetFont(int index)
	{
		XLFont ret{};
		if (book == NULL) { return ret; }
		ret.font = book->font(index);
		ret.book = book;
		return ret;
	}
	//@别名 取图片数量()
	int GetPictureCount()
	{
		return book == NULL ? -1 : book->pictureSize();
	}
	//@别名 添加图片(图片路径)
	//@备注 返回图片标识符
	int AddPicture(CXText filename)
	{
		return book == NULL ? -1 : book->addPicture(filename.get());
	}
	//@别名 取默认字体(字体尺寸)
	CXText GetDefaultFont(int& fontSize)
	{
		return book == NULL ? NULL : (CXText)book->defaultFont(&fontSize);
	}
	//@别名 置默认字体(字体名称,字体尺寸)
	void SetDefaultFont(CXText fontName, int fontSize)
	{
		if (book != NULL) { book->setDefaultFont(fontName.get(), fontSize); }
	}
	//@别名 取R1C1模式()
	bool GetRefR1C1()
	{
		return book == NULL ? false : book->refR1C1();
	}
	//@别名 置R1C1模式(设置)
	void SetRefR1C1(bool refR1C1 = true)
	{
		if (book != NULL) { book->setRefR1C1(refR1C1); }
	}
	//@别名 取错误信息()
	CXText GetErrorMessage()
	{
		return book == NULL ? NULL : (CXText)book->errorMessage();
	}
	//@别名 释放()
	void Release()
	{
		if (book != NULL) { book->release(); }
	}




};

//@分组}