#pragma once

//@模块名称 锐浪报表
//@版本 1.0
//@日期 2023-04-20
//@作者 XCGUI
//@依赖 module_base.h
//@QQ  154460336
//@模块备注 用法见模块自带示例, 模块目录中有锐浪官方chm文档

#ifdef XC_MODULE
#include "module_base.h"
#include "module_xcgui.h"
#endif

#include <comdef.h>
#include <atlbase.h>
#include "Utility\GRImport.h"

//@src "code.cpp"
//@src "event.cpp"
//@src "module_GridppReport.cpp"

//@启用枚举前缀

//struct GRPrintViewerProps; //coclass 
//struct GRPrintViewer; //coclass 
//struct GRDisplayViewerProps; //coclass 
//struct GRDisplayViewer; //coclass 
//struct GridppReport; //coclass 

//@分组{  事件

//@备注 报表的主对象事件类
//@别名 报表事件
class CIGridppReportEvents
{
public:
	//@备注 Initialize 编号：1
	// 在报表准备生成时触发，报表每生成一次触发一次本事件，此事件也是报表生成过程中最先触发的事件。在此事件中，报表开发者可以对报表模板定义进行修改调整。
	// 例如用户在报表生成之从所有可选的列中选择一部分列显示，就可以在此事件中以编程方式动态定义列。
	// 可以在此事件中对报表进行定义，即可以改变报表模板数据，如重新载入报表模板数据，以编程的方式定义报表。
	// 在此事件中，可以将在其它事件中使用的对象接口指针或对象属性等数据用变量缓存下来，以供后面直接使用，提高程序运行效率。
	// 在除此事件之外的其它事件中，除了 SectionFormat 事件可以对事件触发节对象及其拥有的子对象的显示外观属性进行修改外，禁止对报表进行重新定义，即不允许增减报表对象与改变报表对象的属性。
	//@别名 初始化事件()
	/*dispatch*/ virtual void OnInitialize(){  }
	//@备注 FetchRecord 编号：2
	// 采用推模式填充数据时，当报表的记录集上没有定义数据源连接串与查询SQL，或其“忽略数据查询”属性设为“是”，则在报表生成时，报表主对象请求数据时触发本事件。报表开发者必须在此事件中向记录集填入数据。
	// 如果没有定义数据库连接串与查询SQL，或指定在运行时不从数据库连接串与查询SQL设置中取得明细记录数据，则FetchRecord 事件在报表请求数据时触发，报表每生成一次触发一次本事件，只有具有明细网格的报表才会触发此事件。
	// 报表开发者必须响应此事件，且只能在此事件中向记录集填充记录。报表开发者使用记录集接口与字段接口的属性与方法向记录集填充记录。
	// 注意：Delphi 与 C++Builder 的包装类定义了一个 DataSet 属性，并对 FetchRecord 事件在包装类中进行了响应，如果设置了 DataSet 属性值，则会把 DataSet 属性关联记录集对象中的数据填入到 Grid++Report 中。
	// 因此在Delphi 与 C++Builder 中一般通过设置 DataSet 属性来提供明细记录数据。
	//@别名 请求记录数据()
	/*dispatch*/ virtual void OnFetchRecord(){  }
	//@备注 BeforePostRecord 编号：3
	// 在向报表中填入记录数据的过程中，每当提交一条记录时，触发一次本事件。在此事件中，我们可以对当前记录的各个字段值进行重新设置，记录提交之后就不能修改其字段值。
	// 譬如可以在此事件中设置需要由其它字段通过计算得来的字段值。
	// 报表开发者可以在此事件中设定各个字段的值，这样就可以对记录数据进行最后的调整。
	// 如某些字段的值不能直接从数据源中的得来，而是根据一定的运算求得，则可以在此事件中处理。
	// 不管是根据查询SQL取得的数据，还是通过 FetchRecord 事件提供的数据，在每提交一条记录之前都会触发本事件。
	//@别名 提交记录前()
	/*dispatch*/ virtual void OnBeforePostRecord(){  }
	//@备注 BeforeSort 编号：4
	// 当要对记录集中的记录进行重新排序之前触发本事件。在此事件中可以重新设置明细记录集的 SortFields 属性，随后排序将按新设定的字段进行。
	// 如果报表的记录集指定了排序字段，在 ProcessBegin 之前会触发 BeforeSort 事件。
	// 如果设置了记录集的排序字段(SortFields)属性，在每次生成报表时，在BeginPeocessRecord事件之前会触发BeforeSort事件。
	// 另当查询显示器设定为可排序时，点击明细网格的列标题会按点击的列对记录进行重新排序，此时也会触发BeforeSort事件。
	// 在此事件中可以重新设置明细记录集的 SortFields 属性，随后排序将按新设定的字段进行。如下代码：Report.DetailGrid.Recordset.SortFields = \"Field1 DESC;Field2\";
	//@参数 排序字段 事件参数 Name，字段名。
	//@别名 排序前(排序字段)
	/*dispatch*/ virtual void OnBeforeSort(/*[in]*/ const wchar_t* SortFields);
	//@备注 RuntimeError 编号：5
	//@参数 错误ID 
	//@参数 错误信息 
	//@别名 运行时错误(错误ID,错误信息)
	/*dispatch*/ virtual void OnRuntimeError(/*[in]*/ long ErrorID, /*, [in]*/ const wchar_t* ErrorMsg);
	//@备注 ProcessBegin 编号：30
	// 当报表准备对填入的数据进行分析处理之前触发本事件。
	// 报表在获得记录集的明细数据之后，会对明细数据进行运算处理。在开始处理之前触发 ProcessBegin 事件，在完成处理之时触发 ProcessEnd 事件。
	// 在 ProcessBegin 与 ProcessEnd 之间在处理每条明细数据时都会触发一次 ProcessRecord。
	//@别名 开始处理记录()
	/*dispatch*/ virtual void OnProcessBegin(){  }
	//@备注 ProcessEnd 编号：31
	// 当报表对填入的数据进行分析处理完成之后触发本事件。
	//@别名 结束处理记录()
	/*dispatch*/ virtual void OnProcessEnd(){  }
	//@备注 GroupBegin 编号：32
	// 在生成报表数据时，开始一个分组触发。当定义了页分组，在开始生成明细网格关联的每一页时，每个页分组将触发一次本事件。
	// 报表在生成的过程中，会按顺序逐条处理每个记录，如果报表定义有分组，每当一个分组项开始时，触发 GroupBegin 事件，每当一个分组项结束时，触发 GroupEnd 事件。
	// 如果要对分组进行自定义的复杂统计，可以在 GroupBegin 事件函数中设定运算的初值，在 ProcessRecord 事件中对每条记录进行累积运算，在 GroupEnd 事件中对运算的结果进行最后的运算。
	//@参数 分组对象 事件参数 pSender，分组。
	//@别名 分组开始(分组对象)
	/*dispatch*/ virtual void OnGroupBegin(/*[in]*/ class CIGRGroup* pSender) {}
	//@备注 GroupEnd 编号：33
	// 在生成报表数据时，结束一个分组触发。当定义了页分组，在结束生成明细网格关联的每一页时，每个页分组将触发一次本事件。
	//@参数 分组对象 事件参数 pSender，分组。
	//@别名 分组结束(分组对象)
	/*dispatch*/ virtual void OnGroupEnd(/*[in]*/ class CIGRGroup* pSender) {}
	//@备注 ProcessRecord 编号：34
	// 当报表生成时，会按顺序遍历每一条记录，每当遍历一条记录时触发本事件。在此事件中，可以取记录的各个字段的值。
	// 报表开发者可以在此事件中对数据进行一些自定义的分析统计。
	// 报表在生成的过程中，会按顺序逐条处理每个记录，在每处理一条记录之前，都会触发一次本事件，只有具有明细网格的报表才会触发此事件。
	// 如果要对报表数据进行自定义的统计运算，就应该在此事件中取记录数据进行运算，将计算结果保存到参数对象或程序中的变量中。
	// 在此事件中可以调用 IGRDetailGrid 接口的 StartNewGroup 方法指定前一个分组项的结束与后一个分组项的开始，从而实现自定义的分组。
	//@别名 处理记录()
	/*dispatch*/ virtual void OnProcessRecord(){  }
	//@备注 GeneratePagesBegin 编号：38
	// 在产生打印页面数据之前触发本事件。
	//@别名 页面生成前()
	/*dispatch*/ virtual void OnGeneratePagesBegin(){  }
	//@备注 GeneratePagesEnd 编号：39
	// 在产生打印页面数据完成后触发本事件。
	//@别名 页面生成后()
	/*dispatch*/ virtual void OnGeneratePagesEnd(){  }
	//@备注 PageProcessRecord 编号：35
	// 当报表在生成打印数据时，会再次按顺序遍历每一条记录，每当遍历一条记录时触发本事件，只有具有明细网格的报表才会触发此事件。
	// 此事件只有当报表将输出到打印机或打印预览时才会触发。
	// 在页分组中，如果要对报表数据进行自定义的统计运算，就应该在此事件中取记录数据进行运算，将计算结果保存到参数对象或程序中的变量中。
	//@别名 页处理记录()
	/*dispatch*/ virtual void OnPageProcessRecord(){  }
	//@备注 PageStart 编号：36
	// 此事件只有当报表将输出到打印机或打印预览时才会触发。在开始生成一个打印页面时触发本事件。在开始生成每一页时，将触发一次本事件。
	// 报表在生成打印页面的过程中，会再次按顺序逐条处理每个记录，在每处理一条记录之前，都会触发一次本事件，只有具有明细网格的报表才会触发此事件。
	// 在页分组中，如果要对报表数据进行自定义的统计运算，就应该在此事件中取记录数据进行运算，将计算结果保存到参数对象或程序中的变量中。
	//@别名 页开始()
	/*dispatch*/ virtual void OnPageStart(){  }
	//@备注 PageEnd 编号：37
	// 在完成一个打印页面生成时触发本事件。在结束生成每一页时，将触发一次本事件。
	//@别名 页结束()
	/*dispatch*/ virtual void OnPageEnd(){  }
	//@备注 SectionFormat 编号：23
	// 当报表节在输出之前触发。包括查询显示与打印生成显示。
	// 当报表节在输出显示之前触发。一般在 SectionFormat 事件中改变节及节中的部件框或单元格的显示外观属性，达到某些突出显示的效果。
	// 当报表输出在查询显示器中，当前可见的节在显示时会触发本事件，节如果是重复显示的，同一节还会多次触发。
	// 当节在查询显示器中显示时，每当查询显示器窗口需要刷新显示时（要进行自画时），都会触发节的 SectionFormat 事件，所以节的 SectionFormat 事件会频繁触发。
	// 当报表节打印生成时，当每个节在输出之前会触发 SectionFormat 事件。一个节每显示一次，就会触发一次 SectionFormat 事件，一个节如果多次显示，就会多次触发 SectionFormat 事件。
	// 当报表在打印或打印预览时，首先要生成打印页面数据，在页面中显示每个节之前触发本事件。可以通过取报表的当前显示状态（DispalyMode）属性确定事件是由查询显示器自画时触发，还是由生成打印页面时触发。
	// 注意：SectionForamt 事件会频繁触发，在此事件中不应该执行运行开销大的任务，在此事件响应函数中使用的对象接口指针最好在 Initialize 事件处理函数中缓存到变量中。
	//@参数 节对象 事件参数 pSender，节Section，包括：页眉、页脚、报表节ReportSection(报表头与报表尾)、列节ColumnSection(标题行与内容行)、分组节GroupSection(分组头与分组尾)。
	//@别名 格式化报表节(节对象)
	/*dispatch*/ virtual void OnSectionFormat(/*[in]*/ class CIGRSection* pSender);
	//@备注 FieldGetDisplayText 编号：20
	// 当字段对象准备生成其显示文本时触发。
	// 如果一个字段的显示文本不是字段对象内部生成的文本，就需要在此事件中为字段设定显示文本，通过给字段的 DisplayText 属性赋值改变字段的显示文本。
	// 报表在输出显示时，当部件框需要取关联字段的显示文本时触发本事件。在此事件中可以对触发事件的字段对象的显示文本(DisplayText)属性赋值，使字段的显示文本是报表开发者自定义的。
	// 例如在财务报表中，需要将负数用红字显示，就可以在此事件处理函数中将负号从显示文本中去掉，在 SectionFormat 事件处理函数中将对应显示部件框的前景色(ForeColor)设为红色。
	// 注意：FieldGetDisplayForamt 事件会频繁触发，在此事件中不应该执行运行开销大的任务，在此事件响应函数中使用的对象接口指针最好在 Initialize 事件处理函数中缓存到变量中。
	//@参数 字段对象 事件参数 pSender，字段。
	//@别名 请求字段显示文字(字段对象)
	/*dispatch*/ virtual void OnFieldGetDisplayText(/*[in]*/ class CIGRField* pSender);
	//@备注 TextBoxGetDisplayText 编号：22
	// 当文字类型的部件框准备生成其显示文本时触发。此事件类同 FieldGetDisplayText。
	// 如果其显示文本不是内部生成的文本，就需要在此事件中为其设定显示文本，通过给其 DisplayText 属性赋值改变字段的显示文本。
	// 报表在输出显示时，当文字部件输出文字时触发本事件。在此事件中可以对触发事件的文字部件框对象的显示文本(DisplayText)属性赋值，使显示文本是报表开发者自定义的。
	//@参数 文字框对象 事件参数 pSender，文字框， 各种显示文本的部件框的统称，包括：静态框、字段框、统计框、系统变量框、综合文字框。
	//@别名 请求文字框显示文字(文字框对象)
	/*dispatch*/ virtual void OnTextBoxGetDisplayText(/*[in]*/ class CIGRTextBox* pSender);
	//@备注 ControlCustomDraw 编号：24
	// 报表部件框自绘事件。
	// 当部件框为自绘部件框时(部件框的自绘属性设置为是)，部件框在输出显示时会触发本事件,报表开发者应该在本事件中实现部件框的显示输出。
	//@参数 部件框对象 事件参数 pSender，指定了触发本事件的部件框引用；
	//@参数 绘图接口对象 事件参数 Graphics， 提供了在部件框中实现显示输出功能的接口引用，调用其方法在部件框中实现输出；
	// 事件本参数可以继续获取 x, y, width, height 指定部件框的属性以得到输出区域。
	//@别名 部件框自定义绘制(部件框对象,绘图接口对象)
	/*dispatch*/ virtual void OnControlCustomDraw(/*[in]*/ class CIGRControl* pSender, /*, [in]*/ class CIGRGraphics* pGraphics);
	//@备注 ChartRequestData 编号：25
	// 当报表中的图表运行时，会触发本事件来请求加载图表数据。
	// 在此事件响应函数中，开发者可以将数据加载触发此事件的到图表中。如果此图表定义了数据记录集，则向其记录集中追加一条条记录数据。
	// 如果此图表没有定义数据记录集，则直接向图表载入数据，既可以载入XML形式的数据包，也可以通过调用图表接口的属性或方法写入一个个数据。
	//@参数 图表框对象 事件参数 pSender，图表框。
	//@别名 图表请求数据(图表框对象)
	/*dispatch*/ virtual void OnChartRequestData(/*[in]*/ class CIGRChart* pSender);
	//@备注 PrintBegin 编号：40
	// 在开始打印报表之前，触发本事件。另也可以在此事件中设置打印设置参数。
	// 在此事件中可以调用 AbortPrint 方法取消打印过程，这样就可以根据一定的条件控制是否可以打印输出。
	// 一次打印任务成功完成过程，开始时会触发 PrintBegin 事件，在打印数据全部传输给打印机之后触发 PrintEnd 事件；
	// 如果中途取消打印或发生了各种异常导致打印任务没有完成，PrintAborted 事件会触发，而PrintEnd 事件就不会执行到。
	//@别名 打印前()
	/*dispatch*/ virtual void OnPrintBegin(){  }
	//@备注 PrintEnd 编号：41
	// 在结束打印报表之后，触发本事件。
	// 一次打印任务成功完成过程，开始时会触发 PrintBegin 事件，在打印数据全部传输给打印机之后触发 PrintEnd 事件；
	// 如果中途取消打印或发生了各种异常导致打印任务没有完成，PrintAborted 事件会触发，而PrintEnd 事件就不会执行到。
	//@别名 打印后()
	/*dispatch*/ virtual void OnPrintEnd(){  }
	//@备注 PrintPage 编号：42
	// 在打印每一页报表页面时触发本事件。
	//@参数 页号 当前触发打印的页码。
	//@别名 打印页(页号)
	/*dispatch*/ virtual void OnPrintPage(/*[in]*/ long PageNo){  }
	//@备注 PrintAborted 编号：43
	// 当打印任务中途取消时触发本事件。
	// 一次打印任务成功完成过程，开始时会触发 PrintBegin 事件，在打印数据全部传输给打印机之后触发 PrintEnd 事件；
	// 如果中途取消打印或发生了各种异常导致打印任务没有完成，PrintAborted 事件会触发，而PrintEnd 事件就不会执行到。
	//@别名 打印中止()
	/*dispatch*/ virtual void OnPrintAborted(){  }
	//@备注 ExportBegin 编号：50
	// 在报表导出任务执行之前触发本事件。
	//@参数 导出选项对象 事件参数 pOptionObject，导出选项。
	//@别名 导出报表前(导出选项对象)
	/*dispatch*/ virtual void OnExportBegin(/*[in]*/ class CIGRExportOption* pOptionObject) {}
	//@备注 ExportEnd 编号：51
	// 在报表导出任务完成时触发本事件。
	//@参数 导出选项对象 事件参数 pOptionObject，导出选项。
	//@别名 导出报表后(导出选项对象)
	/*dispatch*/ virtual void OnExportEnd(/*[in]*/ class CIGRExportOption* pOptionObject) {}
	//@备注 ShowPreviewWnd 编号：60
	// 在显示默认打印预览窗口时触发本事件。可以在本事件响应中通过 IGRPrintViewer 控件接口对默认预览窗口进行自定义。
	//@参数 打印显示器对象 事件参数 pPrintViewer，打印显示器。
	//@别名 显示预览界面(打印显示器对象)
	/*dispatch*/ virtual void OnShowPreviewWnd(/*[in]*/ class CIGRPrintViewer* pPrintViewer) {}
	//@备注 ShowDesignerWnd 编号：61
	//@参数 报表设计器对象 事件参数 pDesigner，报表设计器。
	//@别名 显示设计界面(报表设计器对象)
	/*dispatch*/ virtual void OnShowDesignerWnd(/*[in]*/ IDispatch* pDesigner){  }
	//@备注 HyperlinkClick 编号：65
	//@参数 部件框对象 事件参数 pSender，部件框。
	//@参数 超链接文本 
	//@参数 从预览页面 
	//@别名 超链接文本被点击(部件框对象,超链接文本,从预览页面)
	/*dispatch*/ virtual void OnHyperlinkClick(/*[in]*/ class CIGRControl* pSender, /*, [in]*/ const wchar_t* HyperlinkText, /*, [in]*/ BOOL FromPreviewPage) {}

};

//@分组}


//@备注 Object，基类，基础对象，全部对象由此展开。
//@别名 IGR对象
class CIGRObject : public CXComObj /*IDispatch*/
{
public:
	CIGRObject(){};
	CIGRObject(IGRObject* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRObject* GetPtr(){ return ((IGRObject*)m_ptr.p); }
	/*virtual*/ CXText get_Tag(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRObject*)m_ptr.p)->get_Tag(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_Tag(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRObject*)m_ptr.p)->put_Tag((BSTR)pVal); return _result; }
	//@备注 Assign，将同类型的参数对象赋值到本对象。
	//@参数 对象类 
	//@别名 对象值复制(对象类)
	/*virtual*/ HRESULT Assign(/*[in]*/ IDispatch* Object){ HRESULT _result = ((IGRObject*)m_ptr.p)->raw_Assign(Object); return _result; }
	/*virtual*/ HRESULT _ObjSave(){ HRESULT _result = ((IGRObject*)m_ptr.p)->raw__ObjSave(); return _result; }
	/*virtual*/ HRESULT _ObjLoad(){ HRESULT _result = ((IGRObject*)m_ptr.p)->raw__ObjLoad(); return _result; }

};
//@备注 Group，表示记录的分组。可以定义不同的分组方式，分组对象拥有一个分组头与分组尾。
// 定义分组规则，对所有的记录数据进行归类，并将归类统计数据显示在分组头或分组尾。
// 当属性PageGroup为真，在打印生成页面时，每个页产生一个分组项；
// 当属性PageGroup为假，如果属性ByFields关联字段，将相同字段值的记录归类为一个分组项，通常记录的顺序应按分组字段进行排序，如果属性ByFields没有定义，表示全部记录形成一个分组项。
// 在报表主对象的ProcessRecord事件中每执行IGRDetailGrid接口的StartNewGroup方法，将生成指定分组的一个分组项。
//@别名 分组
class CIGRGroup : public CIGRObject
{
public:
	CIGRGroup(){};
	CIGRGroup(IGRGroup* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGroup* GetPtr(){ return ((IGRGroup*)m_ptr.p); }
	//@备注 Parent，获取父对象引用，亦即明细网格的接口引用。
	//@别名 取父对象()
	/*virtual*/ class CIGRDetailGrid get_Parent(/*[out][retVal] class CIGRDetailGrid** pVal*/);
	//@备注 Header，获取本分组拥有的分组头对象的接口引用。
	//@别名 取分组头()
	/*virtual*/ class CIGRGroupHeader get_Header(/*[out][retVal] class CIGRGroupHeader** pVal*/);
	//@备注 Footer，获取本分组拥有的分组尾对象的接口引用。
	//@别名 取分组尾()
	/*virtual*/ class CIGRGroupFooter get_Footer(/*[out][retVal] class CIGRGroupFooter** pVal*/);
	//@备注 Name，获取或设置分组的名称标识。
	// 分组的名称与其拥有的分组头与分组尾的名称保持相同。
	// 当改变三者中任何一个名称都会引起其它两个名称跟随改变。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroup*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，获取或设置分组的名称标识。
	// 分组的名称与其拥有的分组头与分组尾的名称保持相同。
	// 当改变三者中任何一个名称都会引起其它两个名称跟随改变。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 ByFields，获取或设置分组依据字段的名称。
	// 如果本属性值为空，则为全程分局，即全部明细记录只产生一个分组项。
	//@返回 如果要根据多个字段进行分组，字段名称之间用分号（;）隔开。
	//@别名 取依据字段()
	/*virtual*/ CXText get_ByFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroup*)m_ptr.p)->get_ByFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ByFields，获取或设置分组依据字段的名称。
	// 如果本属性值为空，则为全程分局，即全部明细记录只产生一个分组项。
	//@参数 字段名称 如果要根据多个字段进行分组，字段名称之间用分号（;）隔开。
	//@别名 置依据字段(字段名称)
	/*virtual*/ HRESULT set_ByFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_ByFields((BSTR)pVal); return _result; }
	//@备注 PageGroup，获取或设置本分组是否为页分组的标志。
	// 如果本属性为真，表示分组按打印页进行归类，即每个打印页生成一个分组项。按页分组在查询显示器中不应用。
	//@别名 取按页分组()
	/*virtual*/ BOOL get_PageGroup(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroup*)m_ptr.p)->get_PageGroup(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PageGroup，获取或设置本分组是否为页分组的标志。
	// 如果本属性为真，表示分组按打印页进行归类，即每个打印页生成一个分组项。按页分组在查询显示器中不应用。
	//@参数 逻辑值 
	//@别名 置按页分组(逻辑值)
	/*virtual*/ HRESULT set_PageGroup(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_PageGroup(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LimitsPerPage，指定在一页中最多显示的分组项数。
	// 本属性值为0时，在一页中产生的分组项数没有特定限制。
	//@返回 默认值0
	//@别名 取每页最多组数()
	/*virtual*/ long get_LimitsPerPage(/*[out][retVal] long* pVal*/){long _result=0; ((IGRGroup*)m_ptr.p)->get_LimitsPerPage(&_result); return _result; }
	//@备注 LimitsPerPage，指定在一页中最多显示的分组项数。
	// 本属性值为0时，在一页中产生的分组项数没有特定限制。
	//@参数 整数值 默认值0
	//@别名 置每页最多组数(整数值)
	/*virtual*/ HRESULT set_LimitsPerPage(/*[in]*/ long pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_LimitsPerPage(pVal); return _result; }
	//@备注 SortSummaryBox，根据指定统计框的值对分组项进行排序。
	// 如果指定了此属性，Grid++Report 将自动根据对应统计框的值对分组项进行排序，报表数据的显示顺序将与原始数据的顺序不一样。
	//@返回 返回统计框名称。
	//@别名 取排序统计框()
	/*virtual*/ CXText get_SortSummaryBox(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroup*)m_ptr.p)->get_SortSummaryBox(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SortSummaryBox，根据指定统计框的值对分组项进行排序。
	// 如果指定了此属性，Grid++Report 将自动根据对应统计框的值对分组项进行排序，报表数据的显示顺序将与原始数据的顺序不一样。
	//@参数 名称 统计框名称。
	//@别名 置排序统计框(名称)
	/*virtual*/ HRESULT set_SortSummaryBox(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_SortSummaryBox((BSTR)pVal); return _result; }
	//@备注 SortAsc，当按统计框的制对分组项进行排序时，是否按升序方式排序。
	//@别名 取排序按升序()
	/*virtual*/ BOOL get_SortAsc(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroup*)m_ptr.p)->get_SortAsc(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SortAsc，当按统计框的制对分组项进行排序时，是否按升序方式排序。
	//@参数 逻辑值 
	//@别名 置排序按升序(逻辑值)
	/*virtual*/ HRESULT set_SortAsc(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_SortAsc(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GroupBeginScript，表示报表 GroupBegin 事件对应的脚本语言代码。
	//@别名 取分组开始脚本()
	/*virtual*/ CXText get_GroupBeginScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroup*)m_ptr.p)->get_GroupBeginScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GroupBeginScript，表示报表 GroupBegin 事件对应的脚本语言代码。
	//@参数 文本 
	//@别名 置分组开始脚本(文本)
	/*virtual*/ HRESULT set_GroupBeginScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_GroupBeginScript((BSTR)pVal); return _result; }
	//@备注 GroupEndScript，表示报表 GroupEnd 事件对应的脚本语言代码。
	//@别名 取分组结束脚本()
	/*virtual*/ CXText get_GroupEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroup*)m_ptr.p)->get_GroupEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GroupEndScript，表示报表 GroupEnd 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置分组结束脚本(脚本文本)
	/*virtual*/ HRESULT set_GroupEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_GroupEndScript((BSTR)pVal); return _result; }
	/*virtual*/ class CIGRRecordset get__Dataset(/*[out][retVal] class CIGRRecordset** pVal*/);
	/*virtual*/ HRESULT _BeginOneGroup(){ HRESULT _result = ((IGRGroup*)m_ptr.p)->raw__BeginOneGroup(); return _result; }
	/*virtual*/ HRESULT _EndOneGroup(){ HRESULT _result = ((IGRGroup*)m_ptr.p)->raw__EndOneGroup(); return _result; }
	/*virtual*/ HRESULT _ProcessGroupRecord(){ HRESULT _result = ((IGRGroup*)m_ptr.p)->raw__ProcessGroupRecord(); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRGroup*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRGroup*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 DetailGrid，表示明细网格对象。绝大多数报表都拥有明细网格，并且明细网格是多数报表的主体。
// 明细网格就是处理报表明细数据生成的实现定义，一般的报表都需要一个明细网格，明细网格一般生成在报表头之后及报表尾之前。
// 一般明细网格构成了一个报表的主体，报表的主要信息输出在明细网格中，明细网格由实现明细数据生成需要的多种子对象组成。
//@别名 明细网格
class CIGRDetailGrid : public CIGRObject
{
public:
	CIGRDetailGrid(){};
	CIGRDetailGrid(IGRDetailGrid* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRDetailGrid* GetPtr(){ return ((IGRDetailGrid*)m_ptr.p); }
	//@备注 ColumnContent，获取明细网格拥有的内容行对象的接口引用。
	//@别名 取内容行()
	/*virtual*/ class CIGRColumnContent get_ColumnContent(/*[out][retVal] class CIGRColumnContent** pVal*/);
	//@备注 ColumnTitle，获取明细网格拥有的标题行对象的接口引用。
	//@别名 取标题行()
	/*virtual*/ class CIGRColumnTitle get_ColumnTitle(/*[out][retVal] class CIGRColumnTitle** pVal*/);
	//@备注 Columns，获取网格拥有的列集合对象的接口引用。
	//@别名 取列集合()
	/*virtual*/ class CIGRColumns get_Columns(/*[out][retVal] class CIGRColumns** pVal*/);
	//@备注 Groups，获取网格拥有的分组集合对象的接口引用。
	//@别名 取分组集合()
	/*virtual*/ class CIGRGroups get_Groups(/*[out][retVal] class CIGRGroups** pVal*/);
	//@备注 Recordset，获取网格拥有的记录集对象的接口引用。
	//@别名 取数据集()
	/*virtual*/ class CIGRRecordset get_Recordset(/*[out][retVal] class CIGRRecordset** pVal*/);
	//@备注 CrossTab，获取交叉表定义对象的接口引用。
	//@别名 取交叉表()
	/*virtual*/ class CIGRCrossTab get_CrossTab(/*[out][retVal] class CIGRCrossTab** pVal*/);
	/*virtual*/ class CIGRRecordset get_MasterRecordset(/*[out][retVal] class CIGRRecordset** pVal*/);
	//@备注 IsCrossTab，获取明细网格是否按交叉表方式去生成。
	//@别名 取交叉表方式()
	/*virtual*/ BOOL get_IsCrossTab(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_IsCrossTab(&_result); return (VARIANT_TRUE==_result); }
	//@备注 IsCrossTab，获取明细网格是否按交叉表方式去生成。
	//@参数 逻辑值 
	//@别名 置交叉表方式(逻辑值)
	/*virtual*/ HRESULT set_IsCrossTab(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_IsCrossTab(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_HasMasterRecordset(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_HasMasterRecordset(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_HasMasterRecordset(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_HasMasterRecordset(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ CXText get_RelationFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRDetailGrid*)m_ptr.p)->get_RelationFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_RelationFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_RelationFields((BSTR)pVal); return _result; }
	//@备注 Font，获取明细网格拥有的子对象的缺省字体对象的接口引用。
	//@别名 取字体()
	/*virtual*/ class CIGRFont get_Font(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 Border，绘制明细网格的边框定义对象。
	//@别名 取边框()
	/*virtual*/ class CIGRBorder get_Border(/*[out][retVal] class CIGRBorder** pVal*/);
	//@备注 ColLinePen，获取绘制明细网格列线的画笔。
	//@别名 取列线画笔()
	/*virtual*/ class CIGRPen get_ColLinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 RowLinePen，获取绘制明细网网格行线的画笔。
	//@别名 取行线画笔()
	/*virtual*/ class CIGRPen get_RowLinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 BackColor，指定明细网格的标题行、内容行、分组头与分组尾的默认背景色。
	// 此属性作为明细网格拥有的各种子对象的缺省背景色。
	//@别名 取背景色()
	/*virtual*/ OLE_COLOR get_BackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDetailGrid*)m_ptr.p)->get_BackColor(&_result); return _result; }
	//@备注 BackColor，指定明细网格的标题行、内容行、分组头与分组尾的默认背景色。
	// 此属性作为明细网格拥有的各种子对象的缺省背景色。
	//@参数 颜色值 
	//@别名 置背景色(颜色值)
	/*virtual*/ HRESULT set_BackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_BackColor(pVal); return _result; }
	//@备注 ShowColLine，指定是否显示网格列线。
	//@别名 取显示列线()
	/*virtual*/ BOOL get_ShowColLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_ShowColLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowColLine，指定是否显示网格列线。
	//@参数 逻辑值 
	//@别名 置显示列线(逻辑值)
	/*virtual*/ HRESULT set_ShowColLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_ShowColLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowRowLine，指定是否显示网格行线。
	//@别名 取显示行线()
	/*virtual*/ BOOL get_ShowRowLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_ShowRowLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowRowLine，指定是否显示网格行线。
	//@参数 逻辑值 
	//@别名 置显示行线(逻辑值)
	/*virtual*/ HRESULT set_ShowRowLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_ShowRowLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 NewPage，打印生成时，指定强制换新页的方式。
	//@别名 取换新页()
	/*virtual*/ GRNewPageStyle get_NewPage(/*[out][retVal] GRNewPageStyle* pVal*/){GRNewPageStyle _result; ((IGRDetailGrid*)m_ptr.p)->get_NewPage(&_result); return _result; }
	//@备注 NewPage，打印生成时，指定强制换新页的方式。 
	//@参数 换新页方式枚举值 
	//@别名 置换新页(换新页方式枚举值)
	/*virtual*/ HRESULT set_NewPage(/*[in]*/ GRNewPageStyle pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_NewPage(pVal); return _result; }
	//@备注 FixCols，查询显示时，指定锁定的列数，左边被锁定的列始终不进行水平滚动。
	// 指定固定列的个数，默认时0。当属性值大于0时，前 FixCols 个列不跟随水平滚动条的滚动而滚动，而是始终显示在明细网格的左端。
	// 注意：本属性只应用于查询显示器中。
	//@别名 取锁定列数()
	/*virtual*/ long get_FixCols(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDetailGrid*)m_ptr.p)->get_FixCols(&_result); return _result; }
	//@备注 FixCols，查询显示时，指定锁定的列数，左边被锁定的列始终不进行水平滚动。
	// 指定固定列的个数，默认时0。当属性值大于0时，前 FixCols 个列不跟随水平滚动条的滚动而滚动，而是始终显示在明细网格的左端。
	// 注意：本属性只应用于查询显示器中。
	//@参数 列数 当属性值大于0时，前 FixCols 个列不跟随水平滚动条的滚动而滚动，而是始终显示在明细网格的左端。
	//@别名 置锁定列数(列数)
	/*virtual*/ HRESULT set_FixCols(/*[in]*/ long pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_FixCols(pVal); return _result; }
	//@备注 CenterView，当明细网格的列总宽度小于显示区域宽度时，指定是否水平居中显示明细网格。
	// 当列的总宽度小于显示区域的宽度时，当本属性值为真时，在水平方向上将明细网格居中显示，反之则靠左边显示。
	// 此属性设置只对打印与打印预览有效。如果要设置报表表格在查询显示时是否居中显示，应该设置 IGRDisplayViewer.GridCenterView 属性。
	//@别名 取居中显示()
	/*virtual*/ BOOL get_CenterView(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_CenterView(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CenterView，当明细网格的列总宽度小于显示区域宽度时，指定是否水平居中显示明细网格。
	// 当列的总宽度小于显示区域的宽度时，当本属性值为真时，在水平方向上将明细网格居中显示，反之则靠左边显示。
	// 此属性设置只对打印与打印预览有效。如果要设置报表表格在查询显示时是否居中显示，应该设置 IGRDisplayViewer.GridCenterView 属性。
	//@参数 逻辑值 
	//@别名 置居中显示(逻辑值)
	/*virtual*/ HRESULT set_CenterView(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_CenterView(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GrowToBottom，指示是否将明细网格的下边框延伸到页的底部。
	//@别名 取伸展到页底()
	/*virtual*/ BOOL get_GrowToBottom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_GrowToBottom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GrowToBottom，指示是否将明细网格的下边框延伸到页的底部。
	//@参数 逻辑值 
	//@别名 置伸展到页底(逻辑值)
	/*virtual*/ HRESULT set_GrowToBottom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_GrowToBottom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BorderPrintType，指定明细网格的边框的打印类别。 
	//@别名 取边框打印类别()
	/*virtual*/ GRPrintType get_BorderPrintType(/*[out][retVal] GRPrintType* pVal*/){GRPrintType _result; ((IGRDetailGrid*)m_ptr.p)->get_BorderPrintType(&_result); return _result; }
	//@备注 BorderPrintType，指定明细网格的边框的打印类别。 
	//@参数 打印类别枚举值 
	//@别名 置边框打印类别(打印类别枚举值)
	/*virtual*/ HRESULT set_BorderPrintType(/*[in]*/ GRPrintType pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_BorderPrintType(pVal); return _result; }
	//@备注 GridLinePrintType，指定明细网格的行列线的打印输出方式。
	//@别名 取行列线打印类别()
	/*virtual*/ GRPrintType get_GridLinePrintType(/*[out][retVal] GRPrintType* pVal*/){GRPrintType _result; ((IGRDetailGrid*)m_ptr.p)->get_GridLinePrintType(&_result); return _result; }
	//@备注 GridLinePrintType，指定明细网格的行列线的打印输出方式。 
	//@参数 打印类别枚举值 
	//@别名 置行列线打印类别(打印类别枚举值)
	/*virtual*/ HRESULT set_GridLinePrintType(/*[in]*/ GRPrintType pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_GridLinePrintType(pVal); return _result; }
	//@备注 PageColumnDirection，在输出多栏报表时，数据行生成到输出位置的方向。
	//@别名 取页栏方向()
	/*virtual*/ GRPageColumnDirection get_PageColumnDirection(/*[out][retVal] GRPageColumnDirection* pVal*/){GRPageColumnDirection _result; ((IGRDetailGrid*)m_ptr.p)->get_PageColumnDirection(&_result); return _result; }
	//@备注 PageColumnDirection，在输出多栏报表时，数据行生成到输出位置的方向。
	//@参数 页栏输出方向枚举值 
	//@别名 置页栏方向(页栏输出方向枚举值)
	/*virtual*/ HRESULT set_PageColumnDirection(/*[in]*/ GRPageColumnDirection pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PageColumnDirection(pVal); return _result; }
	//@备注 PageColumnCount，在水平方向上均分打印输出区域的个数，也就是报表栏数。
	//@返回 值范围：1-50，默认值1
	//@别名 取页栏数()
	/*virtual*/ long get_PageColumnCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PageColumnCount(&_result); return _result; }
	//@备注 PageColumnCount，在水平方向上均分打印输出区域的个数，也就是报表栏数。
	//@参数 页栏数 值范围：1-50，默认值1
	//@别名 置页栏数(页栏数)
	/*virtual*/ HRESULT set_PageColumnCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PageColumnCount(pVal); return _result; }
	//@备注 PageColumnSpacing，指定多栏报表的栏间距，以报表的计量单位表示。
	//@别名 取页栏间隙()
	/*virtual*/ double get_PageColumnSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PageColumnSpacing(&_result); return _result; }
	//@备注 PageColumnSpacing，指定多栏报表的栏间距，以报表的计量单位表示。
	//@参数 小数值 
	//@别名 置页栏间隙(小数值)
	/*virtual*/ HRESULT set_PageColumnSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PageColumnSpacing(pVal); return _result; }
	//@备注 PageColumnGroupNA，指示多栏报表的分组头与分组尾是否禁止分栏。
	// 当本属性为“真”时，如果报表定义了分组，且报表为多栏报表时，则所有的分组头与分组尾将不进行分栏，而是整行显示。
	//@别名 取分组禁止分栏()
	/*virtual*/ BOOL get_PageColumnGroupNA(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PageColumnGroupNA(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PageColumnGroupNA，指示多栏报表的分组头与分组尾是否禁止分栏。
	// 当本属性为“真”时，如果报表定义了分组，且报表为多栏报表时，则所有的分组头与分组尾将不进行分栏，而是整行显示。
	//@参数 逻辑值 
	//@别名 置分组禁止分栏(逻辑值)
	/*virtual*/ HRESULT set_PageColumnGroupNA(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PageColumnGroupNA(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintAdaptMethod，打印输出时，根据输出页面的情况，指定列的输出策略。
	//@别名 取打印策略()
	/*virtual*/ GRColumnPrintAdaptMethod get_PrintAdaptMethod(/*[out][retVal] GRColumnPrintAdaptMethod* pVal*/){GRColumnPrintAdaptMethod _result; ((IGRDetailGrid*)m_ptr.p)->get_PrintAdaptMethod(&_result); return _result; }
	//@备注 PrintAdaptMethod，打印输出时，根据输出页面的情况，指定列的输出策略。
	//@参数 打印策略枚举值 
	//@别名 置打印策略(打印策略枚举值)
	/*virtual*/ HRESULT set_PrintAdaptMethod(/*[in]*/ GRColumnPrintAdaptMethod pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PrintAdaptMethod(pVal); return _result; }
	//@备注 PrintAdaptRepeat，当打印策略为‘横向分页...’或‘横向分页并重复固定列...’时，报表头与报表尾是否在新页中再次输出。
	//@别名 取重复打印()
	/*virtual*/ BOOL get_PrintAdaptRepeat(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PrintAdaptRepeat(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAdaptRepeat，当打印策略为‘横向分页...’或‘横向分页并重复固定列...’时，报表头与报表尾是否在新页中再次输出。
	//@参数 逻辑值 
	//@别名 置重复打印(逻辑值)
	/*virtual*/ HRESULT set_PrintAdaptRepeat(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PrintAdaptRepeat(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintAdaptFitText，指定是否在打印输出时自动调整列的宽度，以便列中的显示文字都能完整的显示出来。
	//@别名 取打印列宽适应内容()
	/*virtual*/ BOOL get_PrintAdaptFitText(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PrintAdaptFitText(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAdaptFitText，指定是否在打印输出时自动调整列的宽度，以便列中的显示文字都能完整的显示出来。
	//@参数 逻辑值 
	//@别名 置打印列宽适应内容(逻辑值)
	/*virtual*/ HRESULT set_PrintAdaptFitText(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PrintAdaptFitText(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintAdaptRFCStep，当横向分页打印时，锁定列重复打印的间隔页数。
	// 即横向分页几次重复输出一次明细网格的锁定列。
	//@别名 取打印锁定列重复间隔()
	/*virtual*/ long get_PrintAdaptRFCStep(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PrintAdaptRFCStep(&_result); return _result; }
	//@备注 PrintAdaptRFCStep，当横向分页打印时，锁定列重复打印的间隔页数。
	// 即横向分页几次重复输出一次明细网格的锁定列。
	//@参数 整数值 
	//@别名 置打印锁定列重复间隔(整数值)
	/*virtual*/ HRESULT set_PrintAdaptRFCStep(/*[in]*/ long pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PrintAdaptRFCStep(pVal); return _result; }
	//@备注 PrintAdaptTryToOnePage，报表横向分页输出时，尽量将横向产生的页面组合在一页中。
	// 当明细数据不多时，将数据显示在一页中。
	//@别名 取横向分页一页显示()
	/*virtual*/ BOOL get_PrintAdaptTryToOnePage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_PrintAdaptTryToOnePage(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAdaptTryToOnePage，报表横向分页输出时，尽量将横向产生的页面组合在一页中。
	// 当明细数据不多时，将数据显示在一页中。
	//@参数 逻辑值 
	//@别名 置横向分页一页显示(逻辑值)
	/*virtual*/ HRESULT set_PrintAdaptTryToOnePage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_PrintAdaptTryToOnePage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankRow，打印输出时，是否在页的剩余区域补充显示空白内容行的标志。
	//@别名 取追加空白行()
	/*virtual*/ BOOL get_AppendBlankRow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_AppendBlankRow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AppendBlankRow，打印输出时，是否在页的剩余区域补充显示空白内容行的标志。
	//@参数 逻辑值 
	//@别名 置追加空白行(逻辑值)
	/*virtual*/ HRESULT set_AppendBlankRow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_AppendBlankRow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankRowAtLast，打印输出时如果追加空白行,是否在分组尾之后输出空白行。
	//@别名 取追加空白行在后()
	/*virtual*/ BOOL get_AppendBlankRowAtLast(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_AppendBlankRowAtLast(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AppendBlankRowAtLast，打印输出时如果追加空白行,是否在分组尾之后输出空白行。
	//@参数 逻辑值 
	//@别名 置追加空白行在后(逻辑值)
	/*virtual*/ HRESULT set_AppendBlankRowAtLast(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_AppendBlankRowAtLast(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankCol，打印输出时，是否补充空白列把纸张右边的空白填满。
	//@别名 取追加空白列()
	/*virtual*/ BOOL get_AppendBlankCol(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDetailGrid*)m_ptr.p)->get_AppendBlankCol(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AppendBlankCol，打印输出时，是否补充空白列把纸张右边的空白填满。
	//@参数 逻辑值 
	//@别名 置追加空白列(逻辑值)
	/*virtual*/ HRESULT set_AppendBlankCol(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_AppendBlankCol(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankColWidth，当补充空白列打印时，指定空白列的宽度，为0则与最后列同宽。
	//@别名 取追加空白列宽度()
	/*virtual*/ double get_AppendBlankColWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDetailGrid*)m_ptr.p)->get_AppendBlankColWidth(&_result); return _result; }
	//@备注 AppendBlankColWidth，当补充空白列打印时，指定空白列的宽度，为0则与最后列同宽。
	//@参数 小数值 
	//@别名 置追加空白列宽度(小数值)
	/*virtual*/ HRESULT set_AppendBlankColWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_AppendBlankColWidth(pVal); return _result; }
	//@备注 AddColumn，增加一个新列。
	//@参数 名称 列的名称标识。
	//@参数 标题文本 列的标题文本。
	//@参数 关联字段 列关联的字段名称。
	//@参数 列宽度 列的宽度。
	//@别名 增加列(名称,标题文本,关联字段,列宽度)
	/*virtual*/ class CIGRColumn AddColumn(/*[in]*/ const wchar_t* Name, /*, [in]*/ const wchar_t* Title, /*, */ const wchar_t* DataField, /*, [in]*/ double Width/*, [out][retVal] class CIGRColumn** ppColumn*/);
	//@备注 ClearColumns，删除所有的列。
	//@别名 清空列()
	/*virtual*/ HRESULT ClearColumns(){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->raw_ClearColumns(); return _result; }
	//@备注 FindGroupTitleCell，根据名称找到组标题格对象的接口引用。
	// 如果存在与输入名称参数匹配的组标题格对象，则返回组标题格对象的接口引用，否则返回NULL。
	// 例如使用此方法取得组标题格的接口引用，然后向其中添加包含的列。
	//@参数 标题格名称 指定要查找组标题格的名称。 
	//@返回 名称匹配的组标题格对象的接口引用
	//@别名 查找组标题格(标题格名称)
	/*virtual*/ class CIGRColumnTitleCell FindGroupTitleCell(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRColumnTitleCell** ppTitle*/);
	//@备注 AddGroupTitle，增加一个新组标题格。
	//@参数 名称 指定新增组标题格的名称。
	//@参数 标题文本 指定新增组标题格的显示文本。
	//@别名 增加组标题格(名称,标题文本)
	/*virtual*/ class CIGRColumnTitleCell AddGroupTitle(/*[in]*/ const wchar_t* Name, /*, [in]*/ const wchar_t* Title/*, [out][retVal] class CIGRColumnTitleCell** ppTitle*/);
	//@备注 ClearGroupTitles，删除全部组标题格。
	//@别名 清空组标题格()
	/*virtual*/ HRESULT ClearGroupTitles(){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->raw_ClearGroupTitles(); return _result; }
	//@备注 ColumnMoveToEnd，将列的显示顺序移动到最后。
	//@参数 列序号 列序号，从1开始。
	//@别名 按序号移动列到最后(列序号)
	/*virtual*/ HRESULT ColumnMoveToEnd(/*[in]*/ VARIANT ColumnIndex){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->raw_ColumnMoveToEnd(ColumnIndex); return _result; }
	//@备注 ColumnMoveTo，移动指定列到新的显示位置。
	//@参数 要移动列的名称 指定要移动列的名称。
	//@参数 指定新位置所在组标题格名称 指定新位置所在的组标题格名称，如果不是多层表头或不在上层表头之下，参数应为空串。
	//@参数 指定新的显示顺序号 指定新的显示顺序号，顺序号从0开始
	//@别名 移动列至新位置(要移动列的名称,指定新位置所在组标题格名称,指定新的显示顺序号)
	/*virtual*/ HRESULT ColumnMoveTo(/*[in]*/ const wchar_t* ColumnName, /*, [in]*/ const wchar_t* NewGroupTitleCellName, /*, [in]*/ long NewShowOrderNo){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->raw_ColumnMoveTo((BSTR)ColumnName, (BSTR)NewGroupTitleCellName, NewShowOrderNo); return _result; }
	//@备注 StartNewGroup，在报表生成时，开始生成一个新的分组项。只能在报表生成时的 ProcessRecord 事件中调用本方法，目的是为了生成自定义的分组。
	//@参数 分组序号 指定分组对象顺序号，序号从1开始。
	//@别名 按序号开始新分组(分组序号)
	/*virtual*/ HRESULT StartNewGroup(/*[in]*/ VARIANT GroupIndex){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->raw_StartNewGroup(GroupIndex); return _result; }
	//@备注 ColumnByShowOrder，根据列的显示顺序号获取对应列，序号从0开始。
	//@参数 序号 列显示顺序号，从0开始。
	//@别名 按序号获取列(序号)
	/*virtual*/ class CIGRColumn ColumnByShowOrder(/*[in]*/ long OrderNo/*, [out][retVal] class CIGRColumn** ppColumn*/);
	/*virtual*/ GRBorderStyles get_BorderStyles(/*[out][retVal] GRBorderStyles* pVal*/){GRBorderStyles _result; ((IGRDetailGrid*)m_ptr.p)->get_BorderStyles(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderStyles(/*[in]*/ GRBorderStyles pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_BorderStyles(pVal); return _result; }
	/*virtual*/ double get_BorderWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDetailGrid*)m_ptr.p)->get_BorderWidth(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_BorderWidth(pVal); return _result; }
	/*virtual*/ OLE_COLOR get_BorderColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDetailGrid*)m_ptr.p)->get_BorderColor(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_BorderColor(pVal); return _result; }
	/*virtual*/ OLE_COLOR get_ColLineColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDetailGrid*)m_ptr.p)->get_ColLineColor(&_result); return _result; }
	/*virtual*/ HRESULT set_ColLineColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_ColLineColor(pVal); return _result; }
	/*virtual*/ double get_ColLineWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDetailGrid*)m_ptr.p)->get_ColLineWidth(&_result); return _result; }
	/*virtual*/ HRESULT set_ColLineWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_ColLineWidth(pVal); return _result; }
	/*virtual*/ OLE_COLOR get_RowLineColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDetailGrid*)m_ptr.p)->get_RowLineColor(&_result); return _result; }
	/*virtual*/ HRESULT set_RowLineColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_RowLineColor(pVal); return _result; }
	/*virtual*/ double get_RowLineWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDetailGrid*)m_ptr.p)->get_RowLineWidth(&_result); return _result; }
	/*virtual*/ HRESULT set_RowLineWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_RowLineWidth(pVal); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@别名 取锁定()
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRDetailGrid*)m_ptr.p)->get_Lock(&_result); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@参数 锁定类别枚举 
	//@别名 置锁定(锁定类别枚举)
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRDetailGrid*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Section，基类，报表各节的基接口，表示各种报表节相同的属性与方法。包括：页眉、页脚、报表节(报表头与报表尾)、列节(标题行与内容行)、分组节(分组头与分组尾)。
// Grid++Report 的显示由各种类型的节组成，每个节中包含一组部件框或单元格，部件框在生成时根据内容输出显示。
// Grid++Report 的报表节可以分成两大类：一是报表主对象直接拥有的报表节，包括报表头、报表尾、页眉、页脚；二是属于明细网格的报表节，包括标题行、内容行、分组头、分组尾。
//@别名 节
class CIGRSection : public CIGRObject
{
public:
	CIGRSection(){};
	CIGRSection(IGRSection* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRSection* GetPtr(){ return ((IGRSection*)m_ptr.p); }
	//@备注 SectionType，指示报表节的具体类型：1、页眉； 2、报表头； 3、报表尾； 4、页脚； 5、标题行； 6、内容行； 7、分组头； 8、分组尾
	//@别名 取类型()
	/*virtual*/ GRSectionType get_SectionType(/*[out][retVal] GRSectionType* pVal*/){GRSectionType _result; ((IGRSection*)m_ptr.p)->get_SectionType(&_result); return _result; }
	//@备注 Parent，父对象的IUnknown接口引用。
	//@别名 取父对象()
	/*virtual*/ IUnknownPtr get_Parent(/*[out][retVal] IUnknown** pVal*/){IUnknownPtr _result; ((IGRSection*)m_ptr.p)->get_Parent(&_result); return _result; }
	//@备注 Font，报表节的缺省字体。
	//@别名 取字体()
	/*virtual*/ class CIGRFont get_Font(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 Controls，获取拥有的部件框集合对象的接口引用。
	//@别名 取部件框集合()
	/*virtual*/ class CIGRControls get_Controls(/*[out][retVal] class CIGRControls** pVal*/);
	//@备注 Name，报表节的名称标识，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@返回 子类中页眉、页脚、列节(标题行与内容行)、分组节(分组头与分组尾)不继承本属性。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSection*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，报表节的名称标识，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@参数 名称 
	//@返回 子类中页眉、页脚、列节(标题行与内容行)、分组节(分组头与分组尾)不继承本属性。
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 Height，报表节的高度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 以报表使用的计量单位表示的节的高度值，如果高度值为零，则本节再生成时将被忽略掉。
	//@别名 取高度()
	/*virtual*/ double get_Height(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSection*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 Height，报表节的高度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 以报表使用的计量单位表示的节的高度值，如果高度值为零，则本节再生成时将被忽略掉。
	//@参数 高度值 
	//@别名 置高度(高度值)
	/*virtual*/ HRESULT set_Height(/*[in]*/ double pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_Height(pVal); return _result; }
	//@备注 CanGrow，指示节高度在运行时是否可以伸展的标志。报表运行时，如果本属性为真且节拥有可伸展的部件框，节的高度伸展幅度为所有拥有部件框的伸展高度之和。
	//@别名 取可伸展()
	/*virtual*/ BOOL get_CanGrow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSection*)m_ptr.p)->get_CanGrow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanGrow，指示节高度在运行时是否可以伸展的标志。报表运行时，如果本属性为真且节拥有可伸展的部件框，节的高度伸展幅度为所有拥有部件框的伸展高度之和。
	//@参数 逻辑值 
	//@别名 置可伸展(逻辑值)
	/*virtual*/ HRESULT set_CanGrow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_CanGrow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CanShrink，指示节高度在运行时是否可以收缩的标志。报表运行时，如果本属性为真且节拥有可收缩的部件框，节的高度收缩幅度为所有拥有部件框的收缩高度之和。
	//@别名 取可收缩()
	/*virtual*/ BOOL get_CanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSection*)m_ptr.p)->get_CanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanShrink，指示节高度在运行时是否可以收缩的标志。报表运行时，如果本属性为真且节拥有可收缩的部件框，节的高度收缩幅度为所有拥有部件框的收缩高度之和。
	//@参数 逻辑值 
	//@别名 置可收缩(逻辑值)
	/*virtual*/ HRESULT set_CanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_CanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BackColor，报表节的背景填充色。
	//@别名 取背景色()
	/*virtual*/ OLE_COLOR get_BackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRSection*)m_ptr.p)->get_BackColor(&_result); return _result; }
	//@备注 BackColor，报表节的背景填充色。
	//@参数 颜色值 
	//@别名 置背景色(颜色值)
	/*virtual*/ HRESULT set_BackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_BackColor(pVal); return _result; }
	//@备注 Visible，是否显示报表节的标志，当此属性为假时，报表节在输出时将被忽略掉。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSection*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，是否显示报表节的标志，当此属性为假时，报表节在输出时将被忽略掉。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 KeepTogether，是否保持本节输出显示在同一页标志。
	//@别名 取保持同页()
	/*virtual*/ BOOL get_KeepTogether(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSection*)m_ptr.p)->get_KeepTogether(&_result); return (VARIANT_TRUE==_result); }
	//@备注 KeepTogether，是否保持本节输出显示在同一页标志。
	//@参数 逻辑值 
	//@别名 置保持同页(逻辑值)
	/*virtual*/ HRESULT set_KeepTogether(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_KeepTogether(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BookmarkText，指定节的书签文本，文本中可以包含多种数据域。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 本属性的行为与综合文本框的“Text(文本)”属性是类似的。
	//@别名 取书签文本()
	/*virtual*/ CXText get_BookmarkText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSection*)m_ptr.p)->get_BookmarkText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 BookmarkText，指定节的书签文本，文本中可以包含多种数据域。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 本属性的行为与综合文本框的“Text(文本)”属性是类似的。
	//@参数 文本 表达式文本
	//@别名 置书签文本(文本)
	/*virtual*/ HRESULT set_BookmarkText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_BookmarkText((BSTR)pVal); return _result; }
	//@备注 FormatScript，表示报表 SectionFormat 事件对应的脚本语言代码。
	// 在此脚本中可以改变节的 Visible 属性从而控制节的显示与隐藏，达到根据条件显示报表节。
	// 可以在此脚本中改变部件框的 Visible 属性从而控制部件框的显示与隐藏，达到根据条件显示部件框。
	// 可以在此脚本中改节与部件框的外观属性从而改变数据显式，让数据根据不同的条件显示出不同的样式。
	//@别名 取格式化脚本()
	/*virtual*/ CXText get_FormatScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSection*)m_ptr.p)->get_FormatScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 FormatScript，表示报表 SectionFormat 事件对应的脚本语言代码。
	// 在此脚本中可以改变节的 Visible 属性从而控制节的显示与隐藏，达到根据条件显示报表节。
	// 可以在此脚本中改变部件框的 Visible 属性从而控制部件框的显示与隐藏，达到根据条件显示部件框。
	// 可以在此脚本中改节与部件框的外观属性从而改变数据显式，让数据根据不同的条件显示出不同的样式。
	//@参数 脚本文本 
	//@别名 置格式化脚本(脚本文本)
	/*virtual*/ HRESULT set_FormatScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSection*)m_ptr.p)->put_FormatScript((BSTR)pVal); return _result; }
	/*virtual*/ HRESULT _HasSectionFormatScript(){ HRESULT _result = ((IGRSection*)m_ptr.p)->raw__HasSectionFormatScript(); return _result; }

};
//@备注 ColumnSection，基类，明细网格的标题行与内容行的基接口。表示标题行与内容行的共同属性与方法。
//@别名 列节
class CIGRColumnSection : public CIGRSection
{
public:
	CIGRColumnSection(){};
	CIGRColumnSection(IGRColumnSection* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnSection* GetPtr(){ return ((IGRColumnSection*)m_ptr.p); }
	//@备注 DetailGrid，获取拥有本节的明细网格的接口引用。
	//@别名 取明细网格()
	/*virtual*/ class CIGRDetailGrid get_DetailGrid(/*[out][retVal] class CIGRDetailGrid** pVal*/);
	//@备注 Cursor，指定在查询显示报表时，在本内容行上显示的鼠标光标。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@别名 取光标()
	/*virtual*/ GRDisplayCursor get_Cursor(/*[out][retVal] GRDisplayCursor* pVal*/){GRDisplayCursor _result; ((IGRColumnSection*)m_ptr.p)->get_Cursor(&_result); return _result; }
	//@备注 Cursor，指定在查询显示报表时，在本内容行上显示的鼠标光标。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@参数 光标类型枚举值 
	//@别名 置光标(光标类型枚举值)
	/*virtual*/ HRESULT set_Cursor(/*[in]*/ GRDisplayCursor pVal){ HRESULT _result = ((IGRColumnSection*)m_ptr.p)->put_Cursor(pVal); return _result; }
	//@备注 SetCellsBackColor，改变节中全部格的背景色。
	//@参数 背景色 指定新的背景颜色 
	//@别名 设置全部格背景色(背景色)
	/*virtual*/ HRESULT SetCellsBackColor(/*[in]*/ OLE_COLOR BackColor){ HRESULT _result = ((IGRColumnSection*)m_ptr.p)->raw_SetCellsBackColor(BackColor); return _result; }
	//@备注 SetCellsForeColor，改变节中全部格的前景色。
	//@参数 前景色 指定新的文字颜色。
	//@别名 设置全部格前景色(前景色)
	/*virtual*/ HRESULT SetCellsForeColor(/*[in]*/ OLE_COLOR ForeColor){ HRESULT _result = ((IGRColumnSection*)m_ptr.p)->raw_SetCellsForeColor(ForeColor); return _result; }
	/*virtual*/ HRESULT LoadCursorFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRColumnSection*)m_ptr.p)->raw_LoadCursorFile((BSTR)PathFile); return _result; }

};
//@备注 ColumnContent，明细网格拥有的内容行的接口，在输出时，每条明细记录将根据内容行定义输出一次。
// 内容行显示在明细网格标题之后，按照明细网格的记录的顺序每个记录生成一次内容行，如果定义有分组，在每个分组开始与结束时，要插入分组头与分组尾。
// 内容行拥有所有内容格，内容行显示区域被一个个内容格所划分。
//@别名 内容行
class CIGRColumnContent : public CIGRColumnSection
{
public:
	CIGRColumnContent(){};
	CIGRColumnContent(IGRColumnContent* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnContent* GetPtr(){ return ((IGRColumnContent*)m_ptr.p); }
	//@备注 ContentCells，获取拥有的内容格集合对象的接口引用。
	//@别名 取内容格集合()
	/*virtual*/ class CIGRColumnContentCells get_ContentCells(/*[out][retVal] class CIGRColumnContentCells** pVal*/);
	//@备注 AlternatingBackColor，指定间隔输出内容行的交替背景色。
	// 如果本属性值与背景色(BackColor)属性值不相同，输出时用背景色与交替背景色轮流作为内容行的背景色，此时各个内容格本身的背景色将被忽略掉。
	//@别名 取交替背景色()
	/*virtual*/ OLE_COLOR get_AlternatingBackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRColumnContent*)m_ptr.p)->get_AlternatingBackColor(&_result); return _result; }
	//@备注 AlternatingBackColor，指定间隔输出内容行的交替背景色。
	// 如果本属性值与背景色(BackColor)属性值不相同，输出时用背景色与交替背景色轮流作为内容行的背景色，此时各个内容格本身的背景色将被忽略掉。
	//@参数 整数值 
	//@别名 置交替背景色(整数值)
	/*virtual*/ HRESULT set_AlternatingBackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_AlternatingBackColor(pVal); return _result; }
	//@备注 RowsPerPage，打印生成时，指定在一页中显示的行数。
	// 指定打印生成时一页中显示的内容行个数。当本属性等于 0 时，按照内容行的设计高度输出显示内容行，每页中显示内容行的个数为页中可以容纳行的个数。
	// 当本属性大于 0 时，每页中显示的内容行个数为 RowsPerPage。默认为 0。
	//@别名 取每页行数()
	/*virtual*/ long get_RowsPerPage(/*[out][retVal] long* pVal*/){long _result=0; ((IGRColumnContent*)m_ptr.p)->get_RowsPerPage(&_result); return _result; }
	//@备注 RowsPerPage，打印生成时，指定在一页中显示的行数。
	// 指定打印生成时一页中显示的内容行个数。当本属性等于 0 时，按照内容行的设计高度输出显示内容行，每页中显示内容行的个数为页中可以容纳行的个数。
	// 当本属性大于 0 时，每页中显示的内容行个数为 RowsPerPage。默认为 0。
	//@参数 整数值 
	//@别名 置每页行数(整数值)
	/*virtual*/ HRESULT set_RowsPerPage(/*[in]*/ long pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_RowsPerPage(pVal); return _result; }
	//@备注 RowsIncludeGroup，在计算每页行数时，是否将分组头与分组尾也计算在内。
	//@别名 取每页行数包含分组()
	/*virtual*/ BOOL get_RowsIncludeGroup(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnContent*)m_ptr.p)->get_RowsIncludeGroup(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RowsIncludeGroup，在计算每页行数时，是否将分组头与分组尾也计算在内。
	//@参数 逻辑值 
	//@别名 置每页行数包含分组(逻辑值)
	/*virtual*/ HRESULT set_RowsIncludeGroup(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_RowsIncludeGroup(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AdjustRowHeight，指定在每页输出固定行数时，是否自动调整行的高度。
	// 本属性只有当‘每页行数(RowsPerPage)’属性的值大于 0 时才有效。
	// 如果本属性为真，在生成打印页面时，自动调整每行的高度，使页面的输出区域刚好被行充满。反之则按设计的高度输出。
	//@别名 取调整行高()
	/*virtual*/ BOOL get_AdjustRowHeight(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnContent*)m_ptr.p)->get_AdjustRowHeight(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AdjustRowHeight，指定在每页输出固定行数时，是否自动调整行的高度。
	// 本属性只有当‘每页行数(RowsPerPage)’属性的值大于 0 时才有效。
	// 如果本属性为真，在生成打印页面时，自动调整每行的高度，使页面的输出区域刚好被行充满。反之则按设计的高度输出。
	//@参数 逻辑值 
	//@别名 置调整行高(逻辑值)
	/*virtual*/ HRESULT set_AdjustRowHeight(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_AdjustRowHeight(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GrowToNextRow，指定当列中的文字内容不能完全显示出来时，是否在下一行中继续显示。
	//@别名 取伸展到下行()
	/*virtual*/ BOOL get_GrowToNextRow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnContent*)m_ptr.p)->get_GrowToNextRow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GrowToNextRow，指定当列中的文字内容不能完全显示出来时，是否在下一行中继续显示。
	//@参数 逻辑值 
	//@别名 置伸展到下行(逻辑值)
	/*virtual*/ HRESULT set_GrowToNextRow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_GrowToNextRow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRColumnContent*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRColumnContent*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Font，表示报表对象显示文字所使用字体的对象。
// 表示报表对象显示文字所使用字体的对象。字体对象提供属性用来获取与设置字体定义，需要显示文本或需要为子对象提供缺省字体的报表对象拥有字体对象。
// 当报表对象不使用其缺省字体时，它的字体对象拥有一个OLE字体对象，其字体定义由OLE字体对象表示，可以通过 OleFont 属性取得OLE字体对象的接口引用。
// 当报表对象使用缺省字体时，其字体对象不拥有一个OLE字体对象，其字体定义来自其上级对象的字体定义，OleFont 属性为NULL。
// 报表开发者可以在 SectionFormat 事件响应函数中改变触发事件报表节本身或其拥有的单元格或部件框的字体定义，从而改变对应文本的显示。
// 通过设定字体对象的属性来改变字体定义，如果将 OleFont 属性设为NULL，将导致使用缺省字体。
// Grid++Report中拥有字体对象的报表对象有：
//   (1).报表主对象IGridppReport)。其字体对象定义整个报表的缺省字体。OleFont 属性永远不为NULL。
//   (3).明细网格(IGRDetailGrid),其字体对象定义其拥有的字节（标题行、内容行、分组头、分组尾）的缺省字体。其缺省字体来自报表主对象。
//   (2).报表节(IGRSection)。其字体对象定义其拥有全部部件框或单元格的缺省字体。如果报表节的类型为页眉、页脚、报表头、报表尾，其缺省字体来自报表主对象。
//       如果报表节的类型为标题行、内容行、分组头、分组尾，其缺省字体来自明细网格。
//   (4).单元格(IGRColumnCell)。如果为非自由格，其字体对象定义单元格文本的显示字体；如果为非自由格，其字体对象定义单元格拥有全部部件框的缺省字体。标题格的缺省字体来自标题行，内容格的缺省字体来自内容行。
//   (5).部件框(IGRControl)。其字体对象定义部件框文本的显示字体。其缺省字体来自父容器。
//@别名 报表字体
class CIGRFont : public CXComObj /*IDispatch*/
{
public:
	CIGRFont(){};
	CIGRFont(IGRFont* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFont* GetPtr(){ return ((IGRFont*)m_ptr.p); }
	//@备注 OleFont，IFont，如果报表对象使用缺省字体，此属性为NULL，反之此属性为一个有效的OLE字体对象的接口引用
	//@别名 取OLE字体()
	/*virtual*/ IFontPtr get_OleFont(/*[out][retVal] IFont** pVal*/){IFont* _result; ((IGRFont*)m_ptr.p)->get_OleFont(&_result); return _result; }
	//@备注 OleFont，IFont，如果报表对象使用缺省字体，此属性为NULL，反之此属性为一个有效的OLE字体对象的接口引用
	//@参数 字体对象 
	//@别名 置OLE字体(字体对象)
	/*virtual*/ HRESULT set_OleFont(/*[in]*/ IFont* pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_OleFont(pVal); return _result; }
	//@备注 UsingOleFont，(IFont)
	// 当报表对象使用自己定义的字体时，此属性的值等于 OleFont 属性的值。
	// 当报表对象使用缺省字体时，此属性的值来自上级对象(或上上级)的 UsingOleFont 属性。
	// 注意：如果使用本属性取得的OLE字体对象的接口引用进行改变字体的操作，有可能改变的是上级报表对象，或上级报表对象的上级报表对象的字体定义。
	//@别名 取引用OLE字体()
	/*virtual*/ IFontPtr get_UsingOleFont(/*[out][retVal] IFont** pVal*/){IFont* _result; ((IGRFont*)m_ptr.p)->get_UsingOleFont(&_result); return _result; }
	//@备注 Name，此字体对象的字体名称。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFont*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，此字体对象的字体名称。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 Point，指示此字体对象的字体大小尺寸，一般此值等同字体在字体对话框中显示的大小值。
	//@别名 取字号()
	/*virtual*/ double get_Point(/*[out][retVal] double* pVal*/){double _result=0; ((IGRFont*)m_ptr.p)->get_Point(&_result); return _result; }
	//@备注 Point，指示此字体对象的字体大小尺寸，一般此值等同字体在字体对话框中显示的大小值。
	//@参数 字号值 可以是小数值
	//@别名 置字号(字号值)
	/*virtual*/ HRESULT set_Point(/*[in]*/ double pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Point(pVal); return _result; }
	//@备注 Charset，该值指定此字体对象使用的 GDI 字符集。
	//@别名 取字符集()
	/*virtual*/ long get_Charset(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFont*)m_ptr.p)->get_Charset(&_result); return _result; }
	//@备注 Charset，该值指定此字体对象使用的 GDI 字符集。
	//@参数 粗细度值 
	//@别名 置字符集(粗细度值)
	/*virtual*/ HRESULT set_Charset(/*[in]*/ long pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Charset(pVal); return _result; }
	//@备注 Weight，该值用数字指示此字体对象的字体粗细，比 Bold 属性更具灵活性。
	//@别名 取粗细度()
	/*virtual*/ long get_Weight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFont*)m_ptr.p)->get_Weight(&_result); return _result; }
	//@备注 Weight，该值用数字指示此字体对象的字体粗细，比 Bold 属性更具灵活性。
	//@参数 粗细度值 550个是常规与粗体的临界值：由粗到细的字符。400等同于normal，而700等同于bold；如果权重低于550(FW_NORMAL 400和FW_BOLD 700的平均值)，则Bold属性也初始化为false。如果权重大于550，则Bold属性设置为true。
	// 可用值   值的说明
	// normal  缺省值。字体正常显示。
	// bold    粗体
	// bolder  比粗体更加粗
	// lighter 比正常字体淡
	// 100 至少和200一样淡
	// 200 至少和100一样粗，至少和300一样淡
	// 300 至少和200一样粗，至少和400一样淡
	// 400 字体正常显示，相当于normal。
	// 500 至少和400一样粗，至少和600一样淡
	// 600 至少和500一样粗，至少和700一样淡
	// 700 粗体，相当于bold。
	// 800 至少和700一样粗，至少和800一样淡
	// 900 至少和800一样粗
	//@别名 置粗细度(粗细度值)
	/*virtual*/ HRESULT set_Weight(/*[in]*/ long pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Weight(pVal); return _result; }
	//@备注 Bold，该值指示此字体对象是否为粗体。
	//@别名 取粗体()
	/*virtual*/ BOOL get_Bold(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFont*)m_ptr.p)->get_Bold(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Bold，该值指示此字体对象是否为粗体。
	//@参数 逻辑值 
	//@别名 置粗体(逻辑值)
	/*virtual*/ HRESULT set_Bold(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Bold(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Italic，指示此字体对象是否为斜体。
	//@别名 取斜体()
	/*virtual*/ BOOL get_Italic(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFont*)m_ptr.p)->get_Italic(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Italic，指示此字体对象是否为斜体。
	//@参数 逻辑值 
	//@别名 置斜体(逻辑值)
	/*virtual*/ HRESULT set_Italic(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Italic(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Underline，该值指示此字体对象是否有下划线。
	//@别名 取下划线()
	/*virtual*/ BOOL get_Underline(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFont*)m_ptr.p)->get_Underline(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Underline，该值指示此字体对象是否有下划线。
	//@参数 逻辑值 
	//@别名 置下划线(逻辑值)
	/*virtual*/ HRESULT set_Underline(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Underline(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Strikethrough，该值指示此字体对象是否指定通过该字体的横线。
	//@别名 取删除线()
	/*virtual*/ BOOL get_Strikethrough(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFont*)m_ptr.p)->get_Strikethrough(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Strikethrough，该值指示此字体对象是否指定通过该字体的横线。
	//@参数 逻辑值 
	//@别名 置删除线(逻辑值)
	/*virtual*/ HRESULT set_Strikethrough(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFont*)m_ptr.p)->put_Strikethrough(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Clone，根据本队象复制产生一个新的报表字体对象。
	//@别名 克隆()
	/*virtual*/ class CIGRFont Clone(/*[out][retVal] class CIGRFont** pVal*/);

};
//@备注 Controls，集合对象，部件框容器中的所有部件框的集合对象。
//@别名 部件框集合
class CIGRControls : public CXComObj /*IDispatch*/
{
public:
	CIGRControls(){};
	CIGRControls(IGRControls* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRControls* GetPtr(){ return ((IGRControls*)m_ptr.p); }
	/*virtual*/ class CIGRControl get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRControl** ppdoc*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRControls*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有部件框的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRControls*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，根据部件框的类型参数增加一个部件框并返回新增部件框的接口引用。
	//@参数 部件框类型枚举值 指定新增部件框的类型。
	//@返回 新增部件框对象的接口引用。
	//@别名 增加(部件框类型枚举值)
	/*virtual*/ class CIGRControl Add(/*[in]*/ GRControlType ControlType/*, [out][retVal] class CIGRControl** ppControl*/);
	//@备注 Remove，根据部件框的顺序号将部件框移除，在输入参数种指定要移除部件框的顺序号或名称。
	//@参数 序号 指定部件框的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRControls*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部部件框。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRControls*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据部件框的名称取得其顺序号，如果不存在与名称匹配的部件框，则返回-1。
	// 部件框的名称不区分字母的大小写。
	//@参数 名称 指定部件框的名称
	//@返回 如果有匹配的部件框，返回其顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRControls*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的部件框对象，序号从1开始。
	//@参数 序号 指定部件框对象在集合中的序号，从1开始。
	//@返回 获取到的部件框对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRControl ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRControl** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数部件框的顺序。
	//@参数 序号 指定部件框的序号，序号从1开始。
	//@参数 新顺序号 部件框在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRControls*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 Control，基类，各种部件框的基接口，定义各种类型的部件框所具有的共同属性与方法。
// 部件框是对报表中最基本可显示单元的统称，部件框在其父容器中占据一个矩形区域，部件框的内容输出在此矩形区域中。
// 部件框包括背景填充方式与背景色、边框输出模式、以及具体类型的部件框的输出前景色。
// 
// 部件框几种布局方式之间的关系：
// 按照优先级从高到底的顺序排列：对齐列-〉停靠-〉锚定-〉居中。
// 就是说在几种布局方式之间如果存在逻辑条件冲突时，优先按照高级别的布局方式调整部件框的大小与位置。
// 例如，将部件框的停靠方式设定为停靠左边缘（grdsLeft），而居中方式为水平居中（grcsHorizontal），则部件框将采用停靠左边缘的停靠方式，而忽略水平居中的居中方式。
//@别名 部件框
class CIGRControl : public CIGRObject
{
public:
	CIGRControl(){};
	CIGRControl(IGRControl* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRControl* GetPtr(){ return ((IGRControl*)m_ptr.p); }
	//@备注 ControlType，获取本部件框的具体类型。
	// 1、静态文字框； 2、图形框； 3、系统变量框； 4、字段框； 5、统计框； 6、RTF文字框； 7、图像框； 8、综合文字框； 9、子报表框； 10、线段框； 11、图表框； 12、条码框； 13、自由表格框
	//@别名 取部件框类型()
	/*virtual*/ GRControlType get_ControlType(/*[out][retVal] GRControlType* pVal*/){GRControlType _result; ((IGRControl*)m_ptr.p)->get_ControlType(&_result); return _result; }
	//@备注 Font，输出文字时使用的字体。1.当本属性值为空时，代表本部件使用父容器的字体。将本属性设置为NULL，使其使用缺省字体。
	//@别名 取字体()
	/*virtual*/ class CIGRFont get_Font(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 Parent，父容器对象的 IUnknown 接口引用。
	//@别名 取父对象()
	/*virtual*/ IUnknownPtr get_Parent(/*[out][retVal] IUnknown** pVal*/){IUnknownPtr _result; ((IGRControl*)m_ptr.p)->get_Parent(&_result); return _result; }
	//@备注 Name，部件框的名称，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRControl*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，部件框的名称，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 BackColor，部件框的背景色。如果 BackStyle 属性为 grbsTranparent 时，部件框生成时不填充背景，本属性此时被忽略掉。
	//@别名 取背景色()
	/*virtual*/ OLE_COLOR get_BackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRControl*)m_ptr.p)->get_BackColor(&_result); return _result; }
	//@备注 BackColor，部件框的背景色。如果 BackStyle 属性为 grbsTranparent 时，部件框生成时不填充背景，本属性此时被忽略掉。
	//@参数 颜色值 
	//@别名 置背景色(颜色值)
	/*virtual*/ HRESULT set_BackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_BackColor(pVal); return _result; }
	//@备注 BackStyle，部件框显示时背景的填充方式。
	//@别名 取背景模式()
	/*virtual*/ GRBackStyle get_BackStyle(/*[out][retVal] GRBackStyle* pVal*/){GRBackStyle _result; ((IGRControl*)m_ptr.p)->get_BackStyle(&_result); return _result; }
	//@备注 BackStyle，部件框显示时背景的填充方式。
	//@参数 背景模式枚举值 
	//@别名 置背景模式(背景模式枚举值)
	/*virtual*/ HRESULT set_BackStyle(/*[in]*/ GRBackStyle pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_BackStyle(pVal); return _result; }
	//@备注 ForeColor，部件框输出内容的前景色，一般表示输出文字的显示颜色。
	//@别名 取前景色()
	/*virtual*/ OLE_COLOR get_ForeColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRControl*)m_ptr.p)->get_ForeColor(&_result); return _result; }
	//@备注 ForeColor，部件框输出内容的前景色，一般表示输出文字的显示颜色。
	//@参数 颜色值 
	//@别名 置前景色(颜色值)
	/*virtual*/ HRESULT set_ForeColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_ForeColor(pVal); return _result; }
	//@备注 Border，部件框的边框定义对象。
	//@别名 取边框()
	/*virtual*/ class CIGRBorder get_Border(/*[out][retVal] class CIGRBorder** pVal*/);
	//@备注 Left，部件框的左端显示位置，以报表使用的计量单位表示的左端显示位置值，相对于父容器。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@别名 取左()
	/*virtual*/ double get_Left(/*[out][retVal] double* pVal*/){double _result=0; ((IGRControl*)m_ptr.p)->get_Left(&_result); return _result; }
	//@备注 Left，部件框的左端显示位置，以报表使用的计量单位表示的左端显示位置值，相对于父容器。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 左距值 
	//@别名 置左(左距值)
	/*virtual*/ HRESULT set_Left(/*[in]*/ double pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Left(pVal); return _result; }
	//@备注 Top，部件框的顶端显示位置，以报表使用的计量单位表示的顶端显示位置值，相对于父容器。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@别名 取上()
	/*virtual*/ double get_Top(/*[out][retVal] double* pVal*/){double _result=0; ((IGRControl*)m_ptr.p)->get_Top(&_result); return _result; }
	//@备注 Top，部件框的顶端显示位置，以报表使用的计量单位表示的顶端显示位置值，相对于父容器。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 上距值 
	//@别名 置上(上距值)
	/*virtual*/ HRESULT set_Top(/*[in]*/ double pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Top(pVal); return _result; }
	//@备注 Width，部件框的显示宽度，以报表使用的计量单位表示的显示宽度值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@别名 取宽度()
	/*virtual*/ double get_Width(/*[out][retVal] double* pVal*/){double _result=0; ((IGRControl*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Width，部件框的显示宽度，以报表使用的计量单位表示的显示宽度值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 宽度值 
	//@别名 置宽度(宽度值)
	/*virtual*/ HRESULT set_Width(/*[in]*/ double pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Width(pVal); return _result; }
	//@备注 Height，部件框的显示高度，以报表使用的计量单位表示的显示高度值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@别名 取高度()
	/*virtual*/ double get_Height(/*[out][retVal] double* pVal*/){double _result=0; ((IGRControl*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 Height，部件框的显示高度，以报表使用的计量单位表示的显示高度值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 高度值 
	//@别名 置高度(高度值)
	/*virtual*/ HRESULT set_Height(/*[in]*/ double pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Height(pVal); return _result; }
	//@备注 PaddingLeft，指定部件框输出内容的左边距，以屏幕像素为单位。
	//@别名 取左边距()
	/*virtual*/ long get_PaddingLeft(/*[out][retVal] long* pVal*/){long _result=0; ((IGRControl*)m_ptr.p)->get_PaddingLeft(&_result); return _result; }
	//@备注 PaddingLeft，指定部件框输出内容的左边距，以屏幕像素为单位。
	//@参数 像素值 
	//@别名 置左边距(像素值)
	/*virtual*/ HRESULT set_PaddingLeft(/*[in]*/ long pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_PaddingLeft(pVal); return _result; }
	//@备注 PaddingRight，指定部件框输出内容的右边距，以屏幕像素为单位。
	//@别名 取右边距()
	/*virtual*/ long get_PaddingRight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRControl*)m_ptr.p)->get_PaddingRight(&_result); return _result; }
	//@备注 PaddingRight，指定部件框输出内容的右边距，以屏幕像素为单位。
	//@参数 像素值 
	//@别名 置右边距(像素值)
	/*virtual*/ HRESULT set_PaddingRight(/*[in]*/ long pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_PaddingRight(pVal); return _result; }
	//@备注 PaddingTop，指定部件框输出内容的上边距，以屏幕像素为单位。
	//@别名 取上边距()
	/*virtual*/ long get_PaddingTop(/*[out][retVal] long* pVal*/){long _result=0; ((IGRControl*)m_ptr.p)->get_PaddingTop(&_result); return _result; }
	//@备注 PaddingTop，指定部件框输出内容的上边距，以屏幕像素为单位。
	//@参数 像素值 
	//@别名 置上边距(像素值)
	/*virtual*/ HRESULT set_PaddingTop(/*[in]*/ long pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_PaddingTop(pVal); return _result; }
	//@备注 PaddingBottom，指定部件框输出内容的下边距，以屏幕像素为单位。
	//@别名 取下边距()
	/*virtual*/ long get_PaddingBottom(/*[out][retVal] long* pVal*/){long _result=0; ((IGRControl*)m_ptr.p)->get_PaddingBottom(&_result); return _result; }
	//@备注 PaddingBottom，指定部件框输出内容的下边距，以屏幕像素为单位。
	//@参数 像素值 
	//@别名 置下边距(像素值)
	/*virtual*/ HRESULT set_PaddingBottom(/*[in]*/ long pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_PaddingBottom(pVal); return _result; }
	//@备注 Anchor，指定部件框的哪些边缘锚定到其容器边缘。
	// 通过部件框的 Anchor 属性指定部件框的锚定方式(GRAnchorStyles)，Anchor 的值按位组合。默认值是 grasTop 和 grasLeft。
	// 一个部件框可以锚定到其父容器的一个或多个边缘。将部件框锚定到其父容器，可确保当调整父容器的大小时锚定的边缘与父容器的边缘的相对位置保持不变。
	// 例如一个部件框的 Anchor 属性值设置为 grasTop 和 grasBottom，当父容器的高度增加时，部件框的高度也同时伸展，以保持到父容器的上边缘和下边缘的距离不变。
	// 本属性值是 GRAnchorStyles 值的按位组合。默认值是 grasTop 和 grasLeft：1、左边； 2、上边； 4、右边； 8、下边
	//@返回 锚定方式枚举  组合值：15 = 1+2+4+8 = 锚定方式枚举.左边 + 锚定方式枚举.上边 + 锚定方式枚举.右边 + 锚定方式枚举下边
	//@别名 取锚定()
	/*virtual*/ GRAnchorStyles get_Anchor(/*[out][retVal] GRAnchorStyles* pVal*/){GRAnchorStyles _result; ((IGRControl*)m_ptr.p)->get_Anchor(&_result); return _result; }
	//@备注 Anchor，指定部件框的哪些边缘锚定到其容器边缘。
	// 通过部件框的 Anchor 属性指定部件框的锚定方式(GRAnchorStyles)，Anchor 的值按位组合。默认值是 grasTop 和 grasLeft。
	// 一个部件框可以锚定到其父容器的一个或多个边缘。将部件框锚定到其父容器，可确保当调整父容器的大小时锚定的边缘与父容器的边缘的相对位置保持不变。
	// 例如一个部件框的 Anchor 属性值设置为 grasTop 和 grasBottom，当父容器的高度增加时，部件框的高度也同时伸展，以保持到父容器的上边缘和下边缘的距离不变。
	// 本属性值是 GRAnchorStyles 值的按位组合。默认值是 grasTop 和 grasLeft：1、左边； 2、上边； 4、右边； 8、下边
	//@参数 锚定方式枚举 组合值：15 = 1+2+4+8 = 锚定方式枚举.左边 + 锚定方式枚举.上边 + 锚定方式枚举.右边 + 锚定方式枚举下边
	//@别名 置锚定(锚定方式枚举)
	/*virtual*/ HRESULT set_Anchor(/*[in]*/ GRAnchorStyles pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Anchor(pVal); return _result; }
	//@备注 Dock，指定部件框停靠到父容器的哪一个边缘。
	// 指定部件框停靠到父容器的哪一个边缘或者可以停靠到所有边缘并充满父容器。通过部件框的 Dock 属性指定部件框的停靠方式（GRDockStyle）。
	// 默认值是不停靠到任何边缘（grdsNone）。部件框自动调整大小以使停靠边缘完全充满，部件框依照 Z 顺序停靠。
	// 例如，如果将该属性设置为 grdsLeft，部件框的左边缘将停靠到其父容器的左边缘，同时部件框的高度也变为父容器左边缘的高度。
	//@返回 0、无； 1、左边； 2、上边； 3、右边； 4、下边； 5、充满
	//@别名 取停靠方式()
	/*virtual*/ GRDockStyle get_Dock(/*[out][retVal] GRDockStyle* pVal*/){GRDockStyle _result; ((IGRControl*)m_ptr.p)->get_Dock(&_result); return _result; }
	//@备注 Dock，指定部件框停靠到父容器的哪一个边缘。
	// 指定部件框停靠到父容器的哪一个边缘或者可以停靠到所有边缘并充满父容器。通过部件框的 Dock 属性指定部件框的停靠方式（GRDockStyle）。
	// 默认值是不停靠到任何边缘（grdsNone）。部件框自动调整大小以使停靠边缘完全充满，部件框依照 Z 顺序停靠。
	// 例如，如果将该属性设置为 grdsLeft，部件框的左边缘将停靠到其父容器的左边缘，同时部件框的高度也变为父容器左边缘的高度。
	//@参数 停靠方式枚举值 0、无； 1、左边； 2、上边； 3、右边； 4、下边； 5、充满
	//@别名 置停靠方式(停靠方式枚举值)
	/*virtual*/ HRESULT set_Dock(/*[in]*/ GRDockStyle pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Dock(pVal); return _result; }
	//@备注 Center，指定水平与垂直方向的居中对齐方式。
	// 指定部件框在容器中水平与垂直方向上的居中对齐方式。
	// 指定部件框在水平与垂直方向上居中位于父容器的方式。通过部件框的 Center 属性指定部件框的居中方式(GRCenterStyle)。
	// 默认值是在两个方向都不居中(grcsNone)。如果在某个方向上居中，当父容器的大小发生改变时，部件框自动调整位置使自己一直居于父容器的中间。
	// 例如，如果将该属性设置为 grcsHorizontal，部件框始终在水平方向上居于父容器的正中间。
	//@返回 0、无； 1、水平； 2、垂直； 3、水平垂直
	//@别名 取居中方式()
	/*virtual*/ GRCenterStyle get_Center(/*[out][retVal] GRCenterStyle* pVal*/){GRCenterStyle _result; ((IGRControl*)m_ptr.p)->get_Center(&_result); return _result; }
	//@备注 Center，指定水平与垂直方向的居中对齐方式。
	// 指定部件框在容器中水平与垂直方向上的居中对齐方式。
	// 指定部件框在水平与垂直方向上居中位于父容器的方式。通过部件框的 Center 属性指定部件框的居中方式(GRCenterStyle)。
	// 默认值是在两个方向都不居中(grcsNone)。如果在某个方向上居中，当父容器的大小发生改变时，部件框自动调整位置使自己一直居于父容器的中间。
	// 例如，如果将该属性设置为 grcsHorizontal，部件框始终在水平方向上居于父容器的正中间。
	//@参数 居中方式枚举值 0、无； 1、水平； 2、垂直； 3、水平垂直
	//@别名 置居中方式(居中方式枚举值)
	/*virtual*/ HRESULT set_Center(/*[in]*/ GRCenterStyle pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Center(pVal); return _result; }
	//@备注 AlignColumn，部件框水平位置对齐到明细网格列的名称，如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// 指定部件框左端与右端位置与某一个或两个指定列的对齐方式。
	// 通过部件框的 AlignColumn,AlignColumnEx 与 AlignColumnSide 几个属性指定部件框对齐列的行为,AlignColumn 与 AlignColumnEx 指定对齐到那一个列或那两个列,AlignColumnSide 指定对齐到列的左端、右端或左右两端(GRAlignColumnStyle)。
	// 如果指定对齐到列,则部件框的左右端位置与宽度会随列的变化而变化,并始终保证对齐端的位置与列的对应端的位置保持一样,当对齐到列的左右两端时,部件框的宽度与列的宽度始终保持一样。
	// 如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// 说明：AlignColumn 和 AlignColumnEx
	// AlignColumnEx 与 AlignColumn 可以指定到不同的列，这样部件框就可以跨列对齐到不同的列。
	// 如果 AlignColumnEx 与 AlignColumn 只设定了其中之一的，则部件框只对齐到一个列。如果两者都没有设定，则部件框不会对齐到任何列。
	// AlignColumnEx 与 AlignColumn 可以指定对齐到明细网格的左端或右端，其分别对应的属性值为“(GridLeft)”与“(GridRight)”，大小写不能错。
	// 代码类似如下：
	// Control.AlignColumn = \"(GridLeft)\";
	// Control.AlignColumnEx = \"(GridRight)\";
	//@别名 取对齐列()
	/*virtual*/ CXText get_AlignColumn(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRControl*)m_ptr.p)->get_AlignColumn(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 AlignColumn，部件框水平位置对齐到明细网格列的名称，如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// 指定部件框左端与右端位置与某一个或两个指定列的对齐方式。
	// 通过部件框的 AlignColumn,AlignColumnEx 与 AlignColumnSide 几个属性指定部件框对齐列的行为,AlignColumn 与 AlignColumnEx 指定对齐到那一个列或那两个列,AlignColumnSide 指定对齐到列的左端、右端或左右两端(GRAlignColumnStyle)。
	// 如果指定对齐到列,则部件框的左右端位置与宽度会随列的变化而变化,并始终保证对齐端的位置与列的对应端的位置保持一样,当对齐到列的左右两端时,部件框的宽度与列的宽度始终保持一样。
	// 如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// 说明：AlignColumn 和 AlignColumnEx
	// AlignColumnEx 与 AlignColumn 可以指定到不同的列，这样部件框就可以跨列对齐到不同的列。
	// 如果 AlignColumnEx 与 AlignColumn 只设定了其中之一的，则部件框只对齐到一个列。如果两者都没有设定，则部件框不会对齐到任何列。
	// AlignColumnEx 与 AlignColumn 可以指定对齐到明细网格的左端或右端，其分别对应的属性值为“(GridLeft)”与“(GridRight)”，大小写不能错。
	// 代码类似如下：
	// Control.AlignColumn = \"(GridLeft)\";
	// Control.AlignColumnEx = \"(GridRight)\";
	//@参数 列名称 也可以：对齐列枚举.表格左端 = \"(GridLeft)\" 或 对齐列枚举.表格右端 = \"(GridRight)\"
	//@别名 置对齐列(列名称)
	/*virtual*/ HRESULT set_AlignColumn(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_AlignColumn((BSTR)pVal); return _result; }
	//@备注 AlignColumnEx，指定部件框水平位置对齐到明细网格另一个列的名称。
	// AlignColumn 和 AlignColumnEx
	// 如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// AlignColumnEx 与 AlignColumn 可以指定到不同的列，这样部件框就可以跨列对齐到不同的列。
	// 如果 AlignColumnEx 与 AlignColumn 只设定了其中之一的，则部件框只对齐到一个列。如果两者都没有设定，则部件框不会对齐到任何列。
	// AlignColumnEx 与 AlignColumn 可以指定对齐到明细网格的左端或右端，其分别对应的属性值为“(GridLeft)”与“(GridRight)”，大小写不能错。
	// 代码类似如下：
	// Control.AlignColumn = \"(GridLeft)\";
	// Control.AlignColumnEx = \"(GridRight)\";
	//@别名 取对齐列扩展()
	/*virtual*/ CXText get_AlignColumnEx(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRControl*)m_ptr.p)->get_AlignColumnEx(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 AlignColumnEx，指定部件框水平位置对齐到明细网格另一个列的名称。
	// AlignColumn 和 AlignColumnEx
	// 如果本属性值不为空时，配合 AlignColumnSide 属性一起指定部件框与列的对齐方式，部件框的水平位置将跟随列位置的改变而改变。
	// AlignColumnEx 与 AlignColumn 可以指定到不同的列，这样部件框就可以跨列对齐到不同的列。
	// 如果 AlignColumnEx 与 AlignColumn 只设定了其中之一的，则部件框只对齐到一个列。如果两者都没有设定，则部件框不会对齐到任何列。
	// AlignColumnEx 与 AlignColumn 可以指定对齐到明细网格的左端或右端，其分别对应的属性值为“(GridLeft)”与“(GridRight)”，大小写不能错。
	// 代码类似如下：
	// Control.AlignColumn = \"(GridLeft)\";
	// Control.AlignColumnEx = \"(GridRight)\";
	//@参数 列名称 也可以：对齐列枚举.表格左端 = \"(GridLeft)\" 或 对齐列枚举.表格右端 = \"(GridRight)\"
	//@别名 置对齐列扩展(列名称)
	/*virtual*/ HRESULT set_AlignColumnEx(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_AlignColumnEx((BSTR)pVal); return _result; }
	//@备注 AlignColumnSide，部件框对齐到明细网格列的方式，注意：只有当部件框在分组头与分组尾中时才能使用本属性。
	// 注意：由 AlignColumn 或 AlignColumnEx 决定对齐对象。1、左对齐； 2、右对齐； 3、两端对齐
	//@别名 取对齐列方式()
	/*virtual*/ GRAlignColumnStyle get_AlignColumnSide(/*[out][retVal] GRAlignColumnStyle* pVal*/){GRAlignColumnStyle _result; ((IGRControl*)m_ptr.p)->get_AlignColumnSide(&_result); return _result; }
	//@备注 AlignColumnSide，部件框对齐到明细网格列的方式，注意：只有当部件框在分组头与分组尾中时才能使用本属性。
	// 注意：由 AlignColumn 或 AlignColumnEx 决定对齐对象。1、左对齐； 2、右对齐； 3、两端对齐
	//@参数 对齐列方式枚举值 
	//@别名 置对齐列方式(对齐列方式枚举值)
	/*virtual*/ HRESULT set_AlignColumnSide(/*[in]*/ GRAlignColumnStyle pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_AlignColumnSide(pVal); return _result; }
	//@备注 Locked，在设计器中设计报表时，是否锁定部件框的大小与位置。仅对报表在设计器中设计时有效。
	// 当本属性为是时，不能通过鼠标拖放操作改变部件框的大小与位置。
	//@别名 取位置锁定()
	/*virtual*/ BOOL get_Locked(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRControl*)m_ptr.p)->get_Locked(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Locked，在设计器中设计报表时，是否锁定部件框的大小与位置。仅对报表在设计器中设计时有效。
	// 当本属性为是时，不能通过鼠标拖放操作改变部件框的大小与位置。
	//@参数 逻辑值 
	//@别名 置位置锁定(逻辑值)
	/*virtual*/ HRESULT set_Locked(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Locked(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShiftMode，指定部件框在其上层部件框发生高度自动伸展时，其垂直位置进行平移的方式。
	//@别名 取伸展位移()
	/*virtual*/ GRShiftMode get_ShiftMode(/*[out][retVal] GRShiftMode* pVal*/){GRShiftMode _result; ((IGRControl*)m_ptr.p)->get_ShiftMode(&_result); return _result; }
	//@备注 ShiftMode，指定部件框在其上层部件框发生高度自动伸展时，其垂直位置进行平移的方式。
	//@参数 伸展位移枚举值 
	//@别名 置伸展位移(伸展位移枚举值)
	/*virtual*/ HRESULT set_ShiftMode(/*[in]*/ GRShiftMode pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_ShiftMode(pVal); return _result; }
	//@备注 PrintType，部件框的打印输出方式：1、表单； 2、内容
	//@别名 取打印类别()
	/*virtual*/ GRPrintType get_PrintType(/*[out][retVal] GRPrintType* pVal*/){GRPrintType _result; ((IGRControl*)m_ptr.p)->get_PrintType(&_result); return _result; }
	//@备注 PrintType，部件框的打印输出方式：1、表单； 2、内容
	//@参数 打印类别枚举值 
	//@别名 置打印类别(打印类别枚举值)
	/*virtual*/ HRESULT set_PrintType(/*[in]*/ GRPrintType pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_PrintType(pVal); return _result; }
	//@备注 Visible，是否显示部件框的标志，当此属性为假时，部件框在输出时将被忽略掉。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRControl*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，是否显示部件框的标志，当此属性为假时，部件框在输出时将被忽略掉。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Cursor，指定在查询显示报表时，当鼠标光标位于该部件框上时要显示的鼠标光标类型。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@别名 取光标()
	/*virtual*/ GRDisplayCursor get_Cursor(/*[out][retVal] GRDisplayCursor* pVal*/){GRDisplayCursor _result; ((IGRControl*)m_ptr.p)->get_Cursor(&_result); return _result; }
	//@备注 Cursor，指定在查询显示报表时，当鼠标光标位于该部件框上时要显示的鼠标光标类型。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@参数 光标类型枚举值 
	//@别名 置光标(光标类型枚举值)
	/*virtual*/ HRESULT set_Cursor(/*[in]*/ GRDisplayCursor pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_Cursor(pVal); return _result; }
	//@备注 CustomDraw，指定部件框是否为自绘部件框。
	// 指定部件框是否为自绘部件框，自绘部件框不会自动输出显示内容，而是会触发 ControlCustomDraw 报表事件；
	// 如本部件框果存在自绘脚本(CustomDrawScript)，则会执行该脚本。由报表开发者在事件中或事件脚本中实现部件框显示输出。
	//@别名 取自定义绘制()
	/*virtual*/ BOOL get_CustomDraw(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRControl*)m_ptr.p)->get_CustomDraw(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CustomDraw，指定部件框是否为自绘部件框。
	// 指定部件框是否为自绘部件框，自绘部件框不会自动输出显示内容，而是会触发 ControlCustomDraw 报表事件；
	// 如本部件框果存在自绘脚本(CustomDrawScript)，则会执行该脚本。由报表开发者在事件中或事件脚本中实现部件框显示输出。
	//@参数 逻辑值 
	//@别名 置自定义绘制(逻辑值)
	/*virtual*/ HRESULT set_CustomDraw(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_CustomDraw(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ CXText get_HyperlinkText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRControl*)m_ptr.p)->get_HyperlinkText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_HyperlinkText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_HyperlinkText((BSTR)pVal); return _result; }
	//@备注 CustomDrawScript，指定部件框的自绘脚本代码，只有当部件框为自绘部件框时，此属性定义的脚本代码才会执行到。
	//@别名 取自定义绘制脚本()
	/*virtual*/ CXText get_CustomDrawScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRControl*)m_ptr.p)->get_CustomDrawScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 CustomDrawScript，指定部件框的自绘脚本代码，只有当部件框为自绘部件框时，此属性定义的脚本代码才会执行到。
	//@参数 脚本文本 
	//@别名 置自定义绘制脚本(脚本文本)
	/*virtual*/ HRESULT set_CustomDrawScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_CustomDrawScript((BSTR)pVal); return _result; }
	//@备注 AsTextBox，转换本部件框为文字框基类的接口引用。
	// 只有当本部件框确实是文字基类框(TextBox)派生类的对象时，才能成功读取本属性值。文字基类派生的类包括：静态文本框、综合文本框、字段框、统计框、系统变量框。
	//@别名 取为文字框()
	/*virtual*/ class CIGRTextBox get_AsTextBox(/*[out][retVal] class CIGRTextBox** pVal*/);
	//@备注 AsChart，只有当本部件框确实是图表(Chart)时，才能成功读取本属性值。
	//@别名 取为图表框()
	/*virtual*/ class CIGRChart get_AsChart(/*[out][retVal] class CIGRChart** pVal*/);
	//@备注 AsStaticBox，将本部件框转换为静态框的接口引用。只有当本部件框确实是静态框(StaticBox)时，才能成功读取本属性值。
	//@别名 取为静态文字框()
	/*virtual*/ class CIGRStaticBox get_AsStaticBox(/*[out][retVal] class CIGRStaticBox** pVal*/);
	//@备注 AsShapeBox，将本部件框转换为图形框的接口引用。只有当本部件框确实是图形框(ShapeBox)时，才能成功读取本属性值。
	//@别名 取为图形框()
	/*virtual*/ class CIGRShapeBox get_AsShapeBox(/*[out][retVal] class CIGRShapeBox** pVal*/);
	//@备注 AsSystemVarBox，将本部件框转换为系统变量框的接口引用。只有当本部件框确实是系统变量框(SystemVarBox)时，才能成功读取本属性值。
	//@别名 取为系统变量框()
	/*virtual*/ class CIGRSystemVarBox get_AsSystemVarBox(/*[out][retVal] class CIGRSystemVarBox** pVal*/);
	//@备注 AsFieldBox，将本部件框转换为字段框的接口引用。只有当本部件框确实是字段框(FieldBox)时，才能成功读取本属性值。
	// 
	//@别名 取为字段框()
	/*virtual*/ class CIGRFieldBox get_AsFieldBox(/*[out][retVal] class CIGRFieldBox** pVal*/);
	//@备注 AsSummaryBox，将本部件框转换为统计框的接口引用。只有当本部件框确实是统计框(SummaryBox)时，才能成功读取本属性值。
	//@别名 取为统计框()
	/*virtual*/ class CIGRSummaryBox get_AsSummaryBox(/*[out][retVal] class CIGRSummaryBox** pVal*/);
	//@备注 AsPictureBox，将本部件框转换为图像框的接口引用。只有当本部件框确实是图像框(PictureBox)时，才能成功读取本属性值。
	//@别名 取为图像框()
	/*virtual*/ class CIGRPictureBox get_AsPictureBox(/*[out][retVal] class CIGRPictureBox** pVal*/);
	//@备注 AsRichTextBox，将本部件框转换为RTF文本框的接口引用。只有当本部件框确实是RTF文本框(RichTextBox)时，才能成功读取本属性值。
	//@别名 取为RTF文字框()
	/*virtual*/ class CIGRRichTextBox get_AsRichTextBox(/*[out][retVal] class CIGRRichTextBox** pVal*/);
	//@备注 AsMemoBox，转换本部件框为综合文本框的接口引用。只有当本部件框确实是综合文本框(MemoBox)时，才能成功读取本属性值。
	//@别名 取为综合文字框()
	/*virtual*/ class CIGRMemoBox get_AsMemoBox(/*[out][retVal] class CIGRMemoBox** pVal*/);
	//@备注 AsSubReport，转换本部件框为子报表的接口引用。只有当本部件框确实是子报表(MemoBox)时，才能成功读取本属性值。
	//@别名 取为子报表框()
	/*virtual*/ class CIGRSubReport get_AsSubReport(/*[out][retVal] class CIGRSubReport** pVal*/);
	//@备注 AsLine，将本部件框转换为线段的接口引用。只有当本部件框确实是线段(Line)时，才能成功读取本属性值。
	//@别名 取为线段框()
	/*virtual*/ class CIGRLine get_AsLine(/*[out][retVal] class CIGRLine** pVal*/);
	//@备注 AsBarcode，将本部件框转换为条码框的接口引用。只有当本部件框确实是条码框(Barcode)时，才能成功读取本属性值。
	//@别名 取为条码框()
	/*virtual*/ class CIGRBarcode get_AsBarcode(/*[out][retVal] class CIGRBarcode** pVal*/);
	//@备注 AsFreeGrid，将本部件框转换为自由表格的接口引用。只有当本部件框确实是自由表格(FreeGrid)时，才能成功读取本属性值。
	//@别名 取为自由表格()
	/*virtual*/ class CIGRFreeGrid get_AsFreeGrid(/*[out][retVal] class CIGRFreeGrid** pVal*/);
	//@备注 SetBounds，设置部件框在其父容器中的边界位置。
	//@参数 左 左端位置
	//@参数 上 上端位置 
	//@参数 右 右端位置 
	//@参数 下 下端位置 
	//@别名 设置边界(左,上,右,下)
	/*virtual*/ HRESULT SetBounds(/*[in]*/ double Left, /*, [in]*/ double Top, /*, [in]*/ double Right, /*, [in]*/ double Bottom){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw_SetBounds(Left, Top, Right, Bottom); return _result; }
	//@备注 BringToFront，将部件框带到 Z 顺序的前面。此部件框将在同一容器中的其它部件框之后输出显示，如果前面输出的部件框与其在位置上有重叠，则此部件框将覆盖前面输出的部件框。
	//@别名 显示到前端()
	/*virtual*/ HRESULT BringToFront(){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw_BringToFront(); return _result; }
	//@备注 SendToBack，将部件框发送到 Z 顺序的后面。此部件框将在同一容器中的其它部件框之前输出显示，如果后输出的部件框与其在位置上有重叠，则后输出的部件框将覆盖此部件框。
	//@别名 显示到后端()
	/*virtual*/ HRESULT SendToBack(){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw_SendToBack(); return _result; }
	//@备注 LoadCursorFile，载入外部鼠标指针文件。
	//@参数 文件名 全路径文件名称。
	//@别名 载入鼠标指针(文件名)
	/*virtual*/ HRESULT LoadCursorFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw_LoadCursorFile((BSTR)PathFile); return _result; }
	//@备注 DrawDefault，按部件框本身行为输出显示内容，此方法只能在报表的 ControlCustomDraw 事件或部件框本身的自绘脚本(CustomDrawScript)中调用。
	// 例如：首先调用本方法输出部件框固有的显示内容，然后再输出一些额外的自定义内容。
	//@别名 默认绘制()
	/*virtual*/ HRESULT DrawDefault(){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw_DrawDefault(); return _result; }
	/*virtual*/ OLE_COLOR get__RealViewBackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRControl*)m_ptr.p)->get__RealViewBackColor(&_result); return _result; }
	/*virtual*/ OLE_HANDLE get__CursorHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRControl*)m_ptr.p)->get__CursorHandle(&_result); return _result; }
	/*virtual*/ OLE_HANDLE get__ControlHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRControl*)m_ptr.p)->get__ControlHandle(&_result); return _result; }
	/*virtual*/ HRESULT _HasCustomDrawScript(){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw__HasCustomDrawScript(); return _result; }
	/*virtual*/ HRESULT _Draw(/*[in]*/ OLE_HANDLE pDrawDevice, /*, [in]*/ OLE_HANDLE pDrawRect){ HRESULT _result = ((IGRControl*)m_ptr.p)->raw__Draw(pDrawDevice, pDrawRect); return _result; }
	/*virtual*/ double get_BorderWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRControl*)m_ptr.p)->get_BorderWidth(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_BorderWidth(pVal); return _result; }
	/*virtual*/ OLE_COLOR get_BorderColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRControl*)m_ptr.p)->get_BorderColor(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_BorderColor(pVal); return _result; }
	/*virtual*/ GRBorderStyles get_BorderStyles(/*[out][retVal] GRBorderStyles* pVal*/){GRBorderStyles _result; ((IGRControl*)m_ptr.p)->get_BorderStyles(&_result); return _result; }
	/*virtual*/ HRESULT set_BorderStyles(/*[in]*/ GRBorderStyles pVal){ HRESULT _result = ((IGRControl*)m_ptr.p)->put_BorderStyles(pVal); return _result; }

};
//@备注 Border，基础对象，所有报表对象的边框。
//@别名 边框
class CIGRBorder : public CXComObj /*IDispatch*/
{
public:
	CIGRBorder(){};
	CIGRBorder(IGRBorder* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRBorder* GetPtr(){ return ((IGRBorder*)m_ptr.p); }
	//@备注 Pen，绘制边框的画笔。
	//@别名 取画笔()
	/*virtual*/ class CIGRPen get_Pen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 Styles，边框线的显示方式。
	//@返回 枚举值：1、画左； 2、画上； 4、画右； 8、画下
	// 组合值：15 = 1+2+4+8 = 边框模式枚举.画左 + 边框模式枚举.画上 + 边框模式枚举.画右 + 边框模式枚举.画下
	//@别名 取边框模式()
	/*virtual*/ GRBorderStyles get_Styles(/*[out][retVal] GRBorderStyles* pVal*/){GRBorderStyles _result; ((IGRBorder*)m_ptr.p)->get_Styles(&_result); return _result; }
	//@备注 Styles，边框线的显示方式。 
	// 枚举值：1、画左； 2、画上； 4、画右； 8、画下
	//@参数 边框模式枚举值 组合值：15 = 1+2+4+8 = 边框模式枚举.画左 + 边框模式枚举.画上 + 边框模式枚举.画右 + 边框模式枚举.画下
	//@别名 置边框模式(边框模式枚举值)
	/*virtual*/ HRESULT set_Styles(/*[in]*/ GRBorderStyles pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_Styles(pVal); return _result; }
	//@备注 InnerIndent，内层边框缩进量，以屏幕像素为单位。
	//@返回 默认值2
	//@别名 取内层缩进()
	/*virtual*/ long get_InnerIndent(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBorder*)m_ptr.p)->get_InnerIndent(&_result); return _result; }
	//@备注 InnerIndent，内层边框缩进量，以屏幕像素为单位。
	//@参数 像素值 默认值2
	//@别名 置内层缩进(像素值)
	/*virtual*/ HRESULT set_InnerIndent(/*[in]*/ long pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_InnerIndent(pVal); return _result; }
	//@备注 InnerPen，绘制内层边框的画笔。
	//@别名 取内框画笔()
	/*virtual*/ class CIGRPen get_InnerPen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 InnerStyles，内层边框线的显示方式。
	//@别名 取内框模式()
	/*virtual*/ GRBorderStyles get_InnerStyles(/*[out][retVal] GRBorderStyles* pVal*/){GRBorderStyles _result; ((IGRBorder*)m_ptr.p)->get_InnerStyles(&_result); return _result; }
	//@备注 InnerStyles，内层边框线的显示方式。
	//@参数 边框样式枚举值 
	//@别名 置内框模式(边框样式枚举值)
	/*virtual*/ HRESULT set_InnerStyles(/*[in]*/ GRBorderStyles pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_InnerStyles(pVal); return _result; }
	//@备注 Shadow，是否显示阴影。
	//@别名 取显示阴影()
	/*virtual*/ BOOL get_Shadow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRBorder*)m_ptr.p)->get_Shadow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Shadow，是否显示阴影。
	//@参数 逻辑值 
	//@别名 置显示阴影(逻辑值)
	/*virtual*/ HRESULT set_Shadow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_Shadow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShadowWidth，阴影的宽度，以屏幕像素为单位。
	//@返回 默认值4
	//@别名 取阴影宽度()
	/*virtual*/ long get_ShadowWidth(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBorder*)m_ptr.p)->get_ShadowWidth(&_result); return _result; }
	//@备注 ShadowWidth，阴影的宽度，以屏幕像素为单位
	//@参数 像素值 默认值4
	//@别名 置阴影宽度(像素值)
	/*virtual*/ HRESULT set_ShadowWidth(/*[in]*/ long pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_ShadowWidth(pVal); return _result; }
	//@备注 ShadowColor，阴影的颜色。
	//@别名 取阴影颜色()
	/*virtual*/ OLE_COLOR get_ShadowColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRBorder*)m_ptr.p)->get_ShadowColor(&_result); return _result; }
	//@备注 ShadowColor，阴影的颜色。
	//@参数 颜色值 
	//@别名 置阴影颜色(颜色值)
	/*virtual*/ HRESULT set_ShadowColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRBorder*)m_ptr.p)->put_ShadowColor(pVal); return _result; }

};
//@备注 Pen，基础对象，表示报表中绘制线条或边框的画笔对象。
//@别名 画笔
class CIGRPen : public CXComObj /*IDispatch*/
{
public:
	CIGRPen(){};
	CIGRPen(IGRPen* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPen* GetPtr(){ return ((IGRPen*)m_ptr.p); }
	//@备注 Style，指定绘制的线条样式。
	//@别名 取类型()
	/*virtual*/ GRPenStyle get_Style(/*[out][retVal] GRPenStyle* pVal*/){GRPenStyle _result; ((IGRPen*)m_ptr.p)->get_Style(&_result); return _result; }
	//@备注 Style，指定绘制的线条样式。
	//@参数 画线笔类型枚举值 
	//@别名 置类型(画线笔类型枚举值)
	/*virtual*/ HRESULT set_Style(/*[in]*/ GRPenStyle pVal){ HRESULT _result = ((IGRPen*)m_ptr.p)->put_Style(pVal); return _result; }
	//@备注 Width，指定绘制线条的宽度。
	//@返回 帮助里以屏幕像素点为单位，实际上可以是小数。
	//@别名 取宽度()
	/*virtual*/ double get_Width(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPen*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Width，指定绘制线条的宽度。
	//@参数 宽度值 帮助里以屏幕像素点为单位，实际上可以是小数。
	//@别名 置宽度(宽度值)
	/*virtual*/ HRESULT set_Width(/*[in]*/ double pVal){ HRESULT _result = ((IGRPen*)m_ptr.p)->put_Width(pVal); return _result; }
	//@备注 Color，指定绘制线条的眼色。
	//@别名 取颜色()
	/*virtual*/ OLE_COLOR get_Color(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRPen*)m_ptr.p)->get_Color(&_result); return _result; }
	//@备注 Color，指定绘制线条的眼色。
	//@参数 颜色值 
	//@别名 置颜色(颜色值)
	/*virtual*/ HRESULT set_Color(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRPen*)m_ptr.p)->put_Color(pVal); return _result; }

};
//@备注 TextBox，基类，各种文字部件框的基接口，表示各种文字部件框的相同属性与方法。
// 各种显示文本的部件框的统称，包括：静态框、字段框、统计框、系统变量框、综合文字框。
//@别名 文字框
class CIGRTextBox : public CIGRControl
{
public:
	CIGRTextBox(){};
	CIGRTextBox(IGRTextBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRTextBox* GetPtr(){ return ((IGRTextBox*)m_ptr.p); }
	//@备注 TextFormat，输出文字的格式定义对象。
	//@别名 取文本格式()
	/*virtual*/ class CIGRTextFormat get_TextFormat(/*[out][retVal] class CIGRTextFormat** pVal*/);
	//@备注 CanGrow，指示部件框高度在运行时是否可以伸展的标志。
	// 如果本属性为真，报表运行时部件框的设计时高度不足以完整显示出拥有的文本，则部件框的高足自动伸展到刚好能完整显示出拥有的文本。
	// 如果文字要多行显示，应该将“文字自动绕行”属性设为“是”这样才会得到想要的伸展效果。
	//@别名 取可伸展()
	/*virtual*/ BOOL get_CanGrow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_CanGrow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanGrow，指示部件框高度在运行时是否可以伸展的标志。
	// 如果本属性为真，报表运行时部件框的设计时高度不足以完整显示出拥有的文本，则部件框的高足自动伸展到刚好能完整显示出拥有的文本。
	// 如果文字要多行显示，应该将“文字自动绕行”属性设为“是”这样才会得到想要的伸展效果。
	//@参数 逻辑值 
	//@别名 置可伸展(逻辑值)
	/*virtual*/ HRESULT set_CanGrow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_CanGrow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CanShrink，指示部件框高度在运行时是否可以收缩的标志。
	// 如果本属性为真，报表运行时部件框的设计时高度大于完整显示出拥有的文本所需要的高度，则部件框的高度自动收缩到刚好能完整显示出拥有的文本。
	//@别名 取可收缩()
	/*virtual*/ BOOL get_CanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_CanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanShrink，指示部件框高度在运行时是否可以收缩的标志。
	// 如果本属性为真，报表运行时部件框的设计时高度大于完整显示出拥有的文本所需要的高度，则部件框的高度自动收缩到刚好能完整显示出拥有的文本。
	//@参数 逻辑值 
	//@别名 置可收缩(逻辑值)
	/*virtual*/ HRESULT set_CanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_CanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShrinkFontToFit，在文字框的显示区域不能完整显示出文字内容时，指定是否自动缩小文字大小让文字完整显示出来。
	// 注意：
	// 1、缩小字体功能只有在打印与打印预览时才有效果，即查询显示时不支持字体缩小适应。
	// 2、当文字格式的支持HTML标签属性开启时，缩小字体功能不会生效。
	//@别名 取按需缩小字体()
	/*virtual*/ BOOL get_ShrinkFontToFit(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_ShrinkFontToFit(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShrinkFontToFit，在文字框的显示区域不能完整显示出文字内容时，指定是否自动缩小文字大小让文字完整显示出来。
	// 注意：
	// 1、缩小字体功能只有在打印与打印预览时才有效果，即查询显示时不支持字体缩小适应。
	// 2、当文字格式的支持HTML标签属性开启时，缩小字体功能不会生效。
	//@参数 逻辑值 
	//@别名 置按需缩小字体(逻辑值)
	/*virtual*/ HRESULT set_ShrinkFontToFit(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_ShrinkFontToFit(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_SpanToNewPage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_SpanToNewPage(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_SpanToNewPage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_SpanToNewPage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowMoneyLabel，指定是否在此文字框中显示金额标签。
	//@别名 取显示金额标签()
	/*virtual*/ BOOL get_ShowMoneyLabel(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_ShowMoneyLabel(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_ShowMoneyLabel(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_ShowMoneyLabel(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowMoneyLine，指定是否显示成金额线格式。
	//@别名 取显示金额线()
	/*virtual*/ BOOL get_ShowMoneyLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_ShowMoneyLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowMoneyLine，指定是否显示成金额线格式。
	//@参数 逻辑值 
	//@别名 置显示金额线(逻辑值)
	/*virtual*/ HRESULT set_ShowMoneyLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_ShowMoneyLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DisplayText，获取文字框部件框的输出显示文本。只有在运行时才能使用本属性。
	//@别名 取显示文字()
	/*virtual*/ CXText get_DisplayText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRTextBox*)m_ptr.p)->get_DisplayText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DisplayText，获取文字框部件框的输出显示文本。只有在运行时才能使用本属性。
	//@参数 显示文本 
	//@别名 置显示文字(显示文本)
	/*virtual*/ HRESULT set_DisplayText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_DisplayText((BSTR)pVal); return _result; }
	//@备注 GetDisplayTextScript，表示报表 TextBoxGetDisplayText 事件对应的脚本语言代码。
	// 在此脚本中改变文字部件框的显示文字，通过设置 DisplayText 属性的值实现改变文字部件框的显示文字。
	// 特别提示：在此脚本中，仅能设置 Sender 的 DisplayText 数据，对其它属性的设置可能是不起做用的，还有可能引发不可预料的异常。
	//@别名 取显示文字脚本()
	/*virtual*/ CXText get_GetDisplayTextScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRTextBox*)m_ptr.p)->get_GetDisplayTextScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetDisplayTextScript，表示报表 TextBoxGetDisplayText 事件对应的脚本语言代码。
	// 在此脚本中改变文字部件框的显示文字，通过设置 DisplayText 属性的值实现改变文字部件框的显示文字。
	// 特别提示：在此脚本中，仅能设置 Sender 的 DisplayText 数据，对其它属性的设置可能是不起做用的，还有可能引发不可预料的异常。
	// //按某个字段的值设置文字框的显示文字
	// var a = Report.FieldByName(\"Field1\").AsBoolean;
	// if (a) {
	//   Sender.DisplayText = \"条件成立的显示文字\";
	// }
	// else {
	//   Sender.DisplayText = \"其它的显示文字\";
	// }
	//@参数 脚本文本 
	//@别名 置显示文字脚本(脚本文本)
	/*virtual*/ HRESULT set_GetDisplayTextScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_GetDisplayTextScript((BSTR)pVal); return _result; }
	/*virtual*/ BOOL get_WordWrap(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_WordWrap(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_WordWrap(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_WordWrap(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_EndEllipsis(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextBox*)m_ptr.p)->get_EndEllipsis(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_EndEllipsis(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_EndEllipsis(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRTextAlign get_TextAlign(/*[out][retVal] GRTextAlign* pVal*/){GRTextAlign _result; ((IGRTextBox*)m_ptr.p)->get_TextAlign(&_result); return _result; }
	/*virtual*/ HRESULT set_TextAlign(/*[in]*/ GRTextAlign pVal){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->put_TextAlign(pVal); return _result; }
	/*virtual*/ CXText get__ExportXlsFormat(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRTextBox*)m_ptr.p)->get__ExportXlsFormat(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT _FetchExportData(/*[out]*/ double* pValue, /*, [out]*/ const wchar_t** pFormatText, /*, [out]*/ GRFieldType* pDataType){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->raw__FetchExportData(pValue, (BSTR*)pFormatText, pDataType); return _result; }
	/*virtual*/ HRESULT _HasGetDisplayTextScript(){ HRESULT _result = ((IGRTextBox*)m_ptr.p)->raw__HasGetDisplayTextScript(); return _result; }

};
//@备注 TextFormat，基础对象，在报表中显示文字时，表示文字格式信息的对象。
//@别名 文本格式
class CIGRTextFormat : public CXComObj /*IDispatch*/
{
public:
	CIGRTextFormat(){};
	CIGRTextFormat(IGRTextFormat* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRTextFormat* GetPtr(){ return ((IGRTextFormat*)m_ptr.p); }
	//@备注 WordWrap，是否自动换行显示文本。
	//@别名 取文字自动绕行()
	/*virtual*/ BOOL get_WordWrap(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextFormat*)m_ptr.p)->get_WordWrap(&_result); return (VARIANT_TRUE==_result); }
	//@备注 WordWrap，是否自动换行显示文本。
	//@参数 逻辑值 
	//@别名 置文字自动绕行(逻辑值)
	/*virtual*/ HRESULT set_WordWrap(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_WordWrap(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 EndEllipsis，是否用省略号(...)表示超出显示区域的文本。只有当文本不是多行显示时此属性才有意义。
	//@别名 取超长文字省略号()
	/*virtual*/ BOOL get_EndEllipsis(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextFormat*)m_ptr.p)->get_EndEllipsis(&_result); return (VARIANT_TRUE==_result); }
	//@备注 EndEllipsis，是否用省略号(...)表示超出显示区域的文本。只有当文本不是多行显示时此属性才有意义。
	//@参数 逻辑值 
	//@别名 置超长文字省略号(逻辑值)
	/*virtual*/ HRESULT set_EndEllipsis(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_EndEllipsis(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TextAlign，文字的输出对齐方式。
	// 
	//@别名 取文字对齐方式()
	/*virtual*/ GRTextAlign get_TextAlign(/*[out][retVal] GRTextAlign* pVal*/){GRTextAlign _result; ((IGRTextFormat*)m_ptr.p)->get_TextAlign(&_result); return _result; }
	//@备注 TextAlign，文字的输出对齐方式。 
	//@参数 文字对齐方式枚举值 
	//@别名 置文字对齐方式(文字对齐方式枚举值)
	/*virtual*/ HRESULT set_TextAlign(/*[in]*/ GRTextAlign pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_TextAlign(pVal); return _result; }
	//@备注 TextOrientation，文字的显示方向。
	//  
	//@别名 取文字方向()
	/*virtual*/ GRTextOrientation get_TextOrientation(/*[out][retVal] GRTextOrientation* pVal*/){GRTextOrientation _result; ((IGRTextFormat*)m_ptr.p)->get_TextOrientation(&_result); return _result; }
	//@备注 TextOrientation，文字的显示方向。
	//@参数 文字方向枚举值 
	//@别名 置文字方向(文字方向枚举值)
	/*virtual*/ HRESULT set_TextOrientation(/*[in]*/ GRTextOrientation pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_TextOrientation(pVal); return _result; }
	//@备注 TextAngle，文字的显示角度，以度为计量单位，逆时针方向为正。
	// 当文字角度大于0时，只有当文字方向为默认值时才会生效，此时文字只能单行显示，文字对齐方式设定也不起作用，否则将按特定的文字方向显示文字。
	//@别名 取文字角度()
	/*virtual*/ double get_TextAngle(/*[out][retVal] double* pVal*/){double _result=0; ((IGRTextFormat*)m_ptr.p)->get_TextAngle(&_result); return _result; }
	//@备注 TextAngle，文字的显示角度，以度为计量单位，逆时针方向为正。
	// 当文字角度大于0时，只有当文字方向为默认值时才会生效，此时文字只能单行显示，文字对齐方式设定也不起作用，否则将按特定的文字方向显示文字。
	//@参数 数值 
	//@别名 置文字角度(数值)
	/*virtual*/ HRESULT set_TextAngle(/*[in]*/ double pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_TextAngle(pVal); return _result; }
	//@备注 CharacterSpacing，输出文字的字间距，以屏幕像素点为计量单位。
	// 当文字按任意角度显示时，字间距与行间距设置不会起作用。 
	// 在显示长篇文字(文字内容超过一页，如合同与公文等)时，为了防止文字换页时出现从中间截断的情况，应该将“行间距”或“字间距”属性的值设为大于0，如“0.5”或“1.0”。
	//@别名 取字间距()
	/*virtual*/ double get_CharacterSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRTextFormat*)m_ptr.p)->get_CharacterSpacing(&_result); return _result; }
	//@备注 CharacterSpacing，输出文字的字间距，以屏幕像素点为计量单位。
	// 当文字按任意角度显示时，字间距与行间距设置不会起作用。 
	// 在显示长篇文字(文字内容超过一页，如合同与公文等)时，为了防止文字换页时出现从中间截断的情况，应该将“行间距”或“字间距”属性的值设为大于0，如“0.5”或“1.0”。
	//@参数 数值 
	//@别名 置字间距(数值)
	/*virtual*/ HRESULT set_CharacterSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_CharacterSpacing(pVal); return _result; }
	//@备注 LineSpacing，输出文字的行间距，以屏幕像素点为计量单。
	// 当文字按任意角度显示时，字间距与行间距设置不会起作用。 
	// 在显示长篇文字(文字内容超过一页，如合同与公文等)时，为了防止文字换页时出现从中间截断的情况，应该将“行间距”或“字间距”属性的值设为大于0，如“0.5”或“1.0”。
	//@别名 取行间距()
	/*virtual*/ double get_LineSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRTextFormat*)m_ptr.p)->get_LineSpacing(&_result); return _result; }
	//@备注 LineSpacing，输出文字的行间距，以屏幕像素点为计量单。
	// 当文字按任意角度显示时，字间距与行间距设置不会起作用。 
	// 在显示长篇文字(文字内容超过一页，如合同与公文等)时，为了防止文字换页时出现从中间截断的情况，应该将“行间距”或“字间距”属性的值设为大于0，如“0.5”或“1.0”。
	//@参数 数值 
	//@别名 置行间距(数值)
	/*virtual*/ HRESULT set_LineSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_LineSpacing(pVal); return _result; }
	//@备注 FontWidthRatio，文字显示的宽度比例。
	// 当此属性值为1时，文字按原始比例输出；当此属性值大于1时，文字按拉宽的样式输出；当此属性值小于1时，文字按收窄的样式输出。
	//@别名 取文字宽度比例()
	/*virtual*/ double get_FontWidthRatio(/*[out][retVal] double* pVal*/){double _result=0; ((IGRTextFormat*)m_ptr.p)->get_FontWidthRatio(&_result); return _result; }
	//@备注 FontWidthRatio，文字显示的宽度比例。
	// 当此属性值为1时，文字按原始比例输出；当此属性值大于1时，文字按拉宽的样式输出；当此属性值小于1时，文字按收窄的样式输出。
	//@参数 数值 
	//@别名 置文字宽度比例(数值)
	/*virtual*/ HRESULT set_FontWidthRatio(/*[in]*/ double pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_FontWidthRatio(pVal); return _result; }
	//@备注 FirstCharIndent，指定文字段落前第一个文字的缩进量，以屏幕像素为计量单位。
	//@别名 取首字缩进()
	/*virtual*/ long get_FirstCharIndent(/*[out][retVal] long* pVal*/){long _result=0; ((IGRTextFormat*)m_ptr.p)->get_FirstCharIndent(&_result); return _result; }
	//@备注 FirstCharIndent，指定文字段落前第一个文字的缩进量，以屏幕像素为计量单位。
	//@参数 数值 
	//@别名 置首字缩进(数值)
	/*virtual*/ HRESULT set_FirstCharIndent(/*[in]*/ long pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_FirstCharIndent(pVal); return _result; }
	//@备注 ParagraphSpacing，输出文字的段落之间的间距，以屏幕像素点为计量单位。
	//@别名 取段间距()
	/*virtual*/ double get_ParagraphSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRTextFormat*)m_ptr.p)->get_ParagraphSpacing(&_result); return _result; }
	//@备注 ParagraphSpacing，输出文字的段落之间的间距，以屏幕像素点为计量单位。
	//@参数 数值 
	//@别名 置段间距(数值)
	/*virtual*/ HRESULT set_ParagraphSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_ParagraphSpacing(pVal); return _result; }
	//@备注 HtmlTags，是否支持解析显示文字中的HTML标签。
	// 1、只支持部分HTML标签，支持的标签类型请参考帮助文档中“开发指南->...”的说明
	// 2、当本属性为是时，文字部件框的缩小字体功能不会生效。
	//@别名 取支持HTML标签()
	/*virtual*/ BOOL get_HtmlTags(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRTextFormat*)m_ptr.p)->get_HtmlTags(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HtmlTags，是否支持解析显示文字中的HTML标签。
	// 1、只支持部分HTML标签，支持的标签类型请参考帮助文档中“开发指南->...”的说明
	// 2、当本属性为是时，文字部件框的缩小字体功能不会生效。
	//@参数 逻辑值 
	//@别名 置支持HTML标签(逻辑值)
	/*virtual*/ HRESULT set_HtmlTags(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRTextFormat*)m_ptr.p)->put_HtmlTags(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Clone，根据本对象复制产生一个新的文字格式对象。
	//@别名 克隆()
	/*virtual*/ class CIGRTextFormat Clone(/*[out][retVal] class CIGRTextFormat** pVal*/);

};
//@备注 Chart，图表功能通过图表部件框来实现，用来显示各种类型的数据图表的部件框。
// 目前提供了柱图、饼图、折线图等多种图表类型，可以实现基本的图表功能。
// 图表数据既可以在报表设计时提供，也可以在报表运行时动态提供。
// 图表部件框可以插入到任何类型的报表节中，在内容行、分组头与分组尾节中，同一图表可以多次输出，并可以为每次输出提供不一样的数据。
// 图表在查询显示时，提供了交互事件，通过对交互事件的响应可以为图表提供穿透查询分析功能。
// 图表在查询显示时还可以指定图形与图例的显示区域特定鼠标光标。
//@别名 图表框
class CIGRChart : public CIGRControl
{
public:
	CIGRChart(){};
	CIGRChart(IGRChart* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRChart* GetPtr(){ return ((IGRChart*)m_ptr.p); }
	//@备注 Title，指定图表的标题显示文字。
	//@别名 取标题()
	/*virtual*/ CXText get_Title(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_Title(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Title，指定图表的标题显示文字。
	//@参数 标题文本 
	//@别名 置标题(标题文本)
	/*virtual*/ HRESULT set_Title(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_Title((BSTR)pVal); return _result; }
	//@备注 TitleFont，指定图表的标题文字的显示字体。
	//@别名 取标题字体()
	/*virtual*/ class CIGRFont get_TitleFont(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 ValueFont，指定图表的数据值文字的显示字体。
	//@别名 取数据值字体()
	/*virtual*/ class CIGRFont get_ValueFont(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 Chart3D，指定是否以三维图形方式显示，此属性仅对柱图与饼图有效。
	// 目前仅柱图与饼图支持三维图形显示。
	//@别名 取三维效果()
	/*virtual*/ BOOL get_Chart3D(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_Chart3D(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Chart3D，指定是否以三维图形方式显示，此属性仅对柱图与饼图有效。
	// 目前仅柱图与饼图支持三维图形显示。
	//@参数 逻辑值 
	//@别名 置三维效果(逻辑值)
	/*virtual*/ HRESULT set_Chart3D(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_Chart3D(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SingleSeriesColored，当只有一个序列时，是否用不同的颜色显示图形。
	// 此属性仅对柱图、连线图与曲线图有效。
	//@别名 取单序列多色显示()
	/*virtual*/ BOOL get_SingleSeriesColored(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_SingleSeriesColored(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SingleSeriesColored，当只有一个序列时，是否用不同的颜色显示图形。
	// 此属性仅对柱图、连线图与曲线图有效。
	//@参数 逻辑值 
	//@别名 置单序列多色显示(逻辑值)
	/*virtual*/ HRESULT set_SingleSeriesColored(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SingleSeriesColored(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 XAxis，图表X轴。
	//@别名 取X轴()
	/*virtual*/ class CIGRChartAxis get_XAxis(/*[out][retVal] class CIGRChartAxis** pVal*/);
	//@备注 YAxis，图表Y轴。
	//@别名 取Y轴()
	/*virtual*/ class CIGRChartAxis get_YAxis(/*[out][retVal] class CIGRChartAxis** pVal*/);
	//@备注 Y2Axis，图表Y2轴。
	//@别名 取Y2轴()
	/*virtual*/ class CIGRChartAxis get_Y2Axis(/*[out][retVal] class CIGRChartAxis** pVal*/);
	//@备注 Series，图表拥有的所有序列集合。
	//@别名 取序列集合()
	/*virtual*/ class CIGRChartSeriesCollection get_Series(/*[out][retVal] class CIGRChartSeriesCollection** pVal*/);
	//@备注 Recordset，图表拥有的记录集。
	//@别名 取数录集()
	/*virtual*/ class CIGRRecordset get_Recordset(/*[out][retVal] class CIGRRecordset** pVal*/);
	//@备注 SeriesField，产生序列标签文字的关联字段名称。
	//@别名 取序列字段()
	/*virtual*/ CXText get_SeriesField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_SeriesField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SeriesField，产生序列标签文字的关联字段名称。
	//@参数 文本 
	//@别名 置序列字段(文本)
	/*virtual*/ HRESULT set_SeriesField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SeriesField((BSTR)pVal); return _result; }
	//@备注 SeriesAuto，序列个数与标签文字是否根据数据自动产生。
	//@别名 取序列自动()
	/*virtual*/ BOOL get_SeriesAuto(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_SeriesAuto(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SeriesAuto，序列个数与标签文字是否根据数据自动产生。
	//@参数 逻辑值 
	//@别名 置序列自动(逻辑值)
	/*virtual*/ HRESULT set_SeriesAuto(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SeriesAuto(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GroupField，产生组簇标签文字的关联字段名称。
	//@别名 取组簇字段()
	/*virtual*/ CXText get_GroupField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_GroupField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GroupField，产生组簇标签文字的关联字段名称。
	//@参数 文本 
	//@别名 置组簇字段(文本)
	/*virtual*/ HRESULT set_GroupField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_GroupField((BSTR)pVal); return _result; }
	//@备注 GroupAuto，组簇个数与标签文字是否根据数据自动产生。
	//@别名 取组簇自动()
	/*virtual*/ BOOL get_GroupAuto(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_GroupAuto(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GroupAuto，组簇个数与标签文字是否根据数据自动产生。
	//@参数 逻辑值 
	//@别名 置组簇自动(逻辑值)
	/*virtual*/ HRESULT set_GroupAuto(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_GroupAuto(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LegendVisible，指定是否显示图例。
	//@别名 取图例可见性()
	/*virtual*/ BOOL get_LegendVisible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_LegendVisible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LegendVisible，指定是否显示图例。
	//@参数 逻辑值 
	//@别名 置图例可见性(逻辑值)
	/*virtual*/ HRESULT set_LegendVisible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendVisible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LegendValueVisible，指定是否在图例中显示数据值。
	// 只有当图表的组数与序列数之一为1且本属性值为真时，才会将数据值显示在图例中。
	//@别名 取图例中值可见性()
	/*virtual*/ BOOL get_LegendValueVisible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_LegendValueVisible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LegendValueVisible，指定是否在图例中显示数据值。
	// 只有当图表的组数与序列数之一为1且本属性值为真时，才会将数据值显示在图例中。
	//@参数 逻辑值 
	//@别名 置图例中值可见性(逻辑值)
	/*virtual*/ HRESULT set_LegendValueVisible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendValueVisible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LegendShowSum，指定是否在图例中显示合计数据
	//@别名 取图例合计显示()
	/*virtual*/ BOOL get_LegendShowSum(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_LegendShowSum(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LegendShowSum，指定是否在图例中显示合计数据
	//@参数 逻辑值 
	//@别名 置图例合计显示(逻辑值)
	/*virtual*/ HRESULT set_LegendShowSum(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendShowSum(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LegendAtBottom，指示图例是否显示在图表的底部区域。
	//@别名 取图例底部显示()
	/*virtual*/ BOOL get_LegendAtBottom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_LegendAtBottom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LegendAtBottom，指示图例是否显示在图表的底部区域。
	//@参数 逻辑值 
	//@别名 置图例底部显示(逻辑值)
	/*virtual*/ HRESULT set_LegendAtBottom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendAtBottom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LegendColumnCount，指定图例显示的栏数，如果为0，则由Grid++Report自动确定图例的显示栏数。
	// 此属性仅对图例不显示在底部有效。
	//@别名 取图例栏数()
	/*virtual*/ long get_LegendColumnCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_LegendColumnCount(&_result); return _result; }
	//@备注 LegendColumnCount，指定图例显示的栏数，如果为0，则由Grid++Report自动确定图例的显示栏数。
	// 此属性仅对图例不显示在底部有效。
	//@参数 整数值 
	//@别名 置图例栏数(整数值)
	/*virtual*/ HRESULT set_LegendColumnCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendColumnCount(pVal); return _result; }
	//@备注 LegendSumLabel，在图例显示合计值时，指定合计文字标签。
	//@别名 取图例合计标签()
	/*virtual*/ CXText get_LegendSumLabel(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_LegendSumLabel(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LegendSumLabel，在图例显示合计值时，指定合计文字标签。
	//@参数 标签文本 
	//@别名 置图例合计标签(标签文本)
	/*virtual*/ HRESULT set_LegendSumLabel(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendSumLabel((BSTR)pVal); return _result; }
	//@备注 GroupCount，图表的数据组数。
	//@返回 默认值5
	//@别名 取组簇个数()
	/*virtual*/ long get_GroupCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_GroupCount(&_result); return _result; }
	//@备注 GroupCount，图表的数据组数。
	//@参数 整数值 默认值5
	//@别名 置组簇个数(整数值)
	/*virtual*/ HRESULT set_GroupCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_GroupCount(pVal); return _result; }
	//@备注 SeriesCount，图表的数据序列数。
	//@返回 默认值1
	//@别名 取序列个数()
	/*virtual*/ long get_SeriesCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_SeriesCount(&_result); return _result; }
	//@备注 SeriesCount，图表的数据序列数。
	//@参数 整数值 默认值1
	//@别名 置序列个数(整数值)
	/*virtual*/ HRESULT set_SeriesCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SeriesCount(pVal); return _result; }
	/*virtual*/ GRDisplayCursor get_SeriesCursor(/*[out][retVal] GRDisplayCursor* pVal*/){GRDisplayCursor _result; ((IGRChart*)m_ptr.p)->get_SeriesCursor(&_result); return _result; }
	/*virtual*/ HRESULT set_SeriesCursor(/*[in]*/ GRDisplayCursor pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SeriesCursor(pVal); return _result; }
	//@备注 LegendCursor，指定在查询显示报表时，当鼠标光标位于图例项上时要显示的鼠标光标类型。
	//@别名 取图例光标()
	/*virtual*/ GRDisplayCursor get_LegendCursor(/*[out][retVal] GRDisplayCursor* pVal*/){GRDisplayCursor _result; ((IGRChart*)m_ptr.p)->get_LegendCursor(&_result); return _result; }
	//@备注 LegendCursor，指定在查询显示报表时，当鼠标光标位于图例项上时要显示的鼠标光标类型。
	//@参数 光标类型枚举值 
	//@别名 置图例光标(光标类型枚举值)
	/*virtual*/ HRESULT set_LegendCursor(/*[in]*/ GRDisplayCursor pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_LegendCursor(pVal); return _result; }
	//@备注 BarWidthPercent，指定柱图显示的总宽度占据整个宽度的百分比。此属性仅对柱图有效。
	//@返回 默认值70
	//@别名 取柱图宽度百分比()
	/*virtual*/ long get_BarWidthPercent(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_BarWidthPercent(&_result); return _result; }
	//@备注 BarWidthPercent，指定柱图显示的总宽度占据整个宽度的百分比。此属性仅对柱图有效。
	//@参数 百分比 默认值70
	//@别名 置柱图宽度百分比(百分比)
	/*virtual*/ HRESULT set_BarWidthPercent(/*[in]*/ long pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_BarWidthPercent(pVal); return _result; }
	//@备注 NegativeAsZero，指定柱状图中的负数值是否按0值显示对应图形。
	//@别名 取负数按0显示()
	/*virtual*/ BOOL get_NegativeAsZero(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->get_NegativeAsZero(&_result); return (VARIANT_TRUE==_result); }
	//@备注 NegativeAsZero，指定柱状图中的负数值是否按0值显示对应图形。
	//@参数 逻辑值 
	//@别名 置负数按0显示(逻辑值)
	/*virtual*/ HRESULT set_NegativeAsZero(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_NegativeAsZero(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BubbleScalePerCm，气泡图比例，指定一平方厘米表示的Z值大小。
	// 默认值为0，由Grid++Report自动确定气泡的大小比例。
	//@别名 取气泡图比例()
	/*virtual*/ double get_BubbleScalePerCm(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChart*)m_ptr.p)->get_BubbleScalePerCm(&_result); return _result; }
	//@备注 BubbleScalePerCm，气泡图比例，指定一平方厘米表示的Z值大小。
	// 默认值为0，由Grid++Report自动确定气泡的大小比例。
	//@参数 比例值 
	//@别名 置气泡图比例(比例值)
	/*virtual*/ HRESULT set_BubbleScalePerCm(/*[in]*/ double pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_BubbleScalePerCm(pVal); return _result; }
	/*virtual*/ CXText get_GroupLabel(/*[in]*/ long GroupIndex/*, [out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_GroupLabel(GroupIndex, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_GroupLabel(/*[in]*/ long GroupIndex, /*, [in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_GroupLabel(GroupIndex, (BSTR)pVal); return _result; }
	/*virtual*/ CXText get_SeriesLabel(/*[in]*/ long SeriesIndex/*, [out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->get_SeriesLabel(SeriesIndex, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_SeriesLabel(/*[in]*/ long SeriesIndex, /*, [in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_SeriesLabel(SeriesIndex, (BSTR)pVal); return _result; }
	/*virtual*/ double get_Value(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex/*, [out][retVal] double* pVal*/){double _result=0; ((IGRChart*)m_ptr.p)->get_Value(SeriesIndex, GroupIndex, &_result); return _result; }
	/*virtual*/ HRESULT set_Value(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex, /*, [in]*/ double pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_Value(SeriesIndex, GroupIndex, pVal); return _result; }
	/*virtual*/ long get_ValueCount(/*[in]*/ long SeriesIndex/*, [out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_ValueCount(SeriesIndex, &_result); return _result; }
	//@备注 FillColorCount，获取自定义图形填充颜色的个数。
	//@别名 取自定义填充颜色数()
	/*virtual*/ long get_FillColorCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChart*)m_ptr.p)->get_FillColorCount(&_result); return _result; }
	//@备注 FillColor，获取指定序号处的自定义图形填充颜色。
	// 属性采用整数下标序号，序号从 0 开始。
	// 脚本代码形如：
	// var x = Chart.FillColor(0);
	//@别名 取填充颜色()
	/*virtual*/ OLE_COLOR get_FillColor(/*[in]*/ long Index/*, [out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRChart*)m_ptr.p)->get_FillColor(Index, &_result); return _result; }
	//@备注 AddFillColor，增加一个自定义图形填充颜色。
	//@参数 颜色值 
	//@别名 增加自定义填充颜色(颜色值)
	/*virtual*/ HRESULT AddFillColor(/*[in]*/ OLE_COLOR FillColor){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_AddFillColor(FillColor); return _result; }
	//@备注 EmptyFillColors，清空全部自定义图形填充颜色。
	//@别名 清空自定义填充颜色()
	/*virtual*/ HRESULT EmptyFillColors(){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_EmptyFillColors(); return _result; }
	/*virtual*/ HRESULT PrepareSnapShot(){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_PrepareSnapShot(); return _result; }
	/*virtual*/ HRESULT SnapShot(){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_SnapShot(); return _result; }
	//@备注 LoadDataFromXML，从XML文本数据中获取图表数据。
	// 载入二维数组类型的图表数据，柱图、饼图、折线图、叠加柱状图与曲线图等需要这种类型的数据。
	//@参数 XML文本数据 指定要载入的XML数据包。 
	//@参数 第一列为序列标识 指定第一列是否为序列标识数据。 
	//@参数 自动获取序列标签 指定是否从数据中自动获取序列标签文字，只有当FirstSeries=true时才会自动获取序列标签文字。
	//@参数 自动获取组标签 指定是否从数据中自动获取组标签文字。
	//@返回 指定载入数据是否成功。
	//@别名 从XML载入数据(XML文本数据,第一列为序列标识,自动获取序列标签,自动获取组标签)
	/*virtual*/ BOOL LoadDataFromXML(/*[in]*/ const wchar_t* XML, /*, [in]*/ BOOL FirstSeries, /*, [in]*/ BOOL AutoSeries, /*, [in]*/ BOOL AutoGroup/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->raw_LoadDataFromXML((BSTR)XML, FirstSeries? VARIANT_TRUE : VARIANT_FALSE, AutoSeries? VARIANT_TRUE : VARIANT_FALSE, AutoGroup? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadXYDataFromXML，从XML文本数据中载入XY类型的图表数据
	// 载入坐标点(X,Y)类型的图表数据，散列点图、散列连线图、散列曲线图等需要这种类型的数据。
	//@参数 XML文本数据 指定要载入的XML数据包。 
	//@参数 自动获取序列标签 指定是否从数据中自动获取序列标签文字，只有当FirstSeries=true时才会自动获取序列标签文字。
	//@别名 从XML载入XY数据(XML文本数据,自动获取序列标签)
	/*virtual*/ BOOL LoadXYDataFromXML(/*[in]*/ const wchar_t* XML, /*, [in]*/ BOOL AutoSeries/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->raw_LoadXYDataFromXML((BSTR)XML, AutoSeries? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadXYZDataFromXML，从XML文本数据中载入XYZ类型的图表数据。
	// 载入三维类型的图表数据，气泡图需要这种类型的数据。
	//@参数 XML文本数据 指定要载入的XML数据包。 
	//@参数 自动获取序列标签 指定是否从数据中自动获取序列标签文字，只有当FirstSeries=true时才会自动获取序列标签文字。
	//@别名 从XML载入XYZ数据(XML文本数据,自动获取序列标签)
	/*virtual*/ BOOL LoadXYZDataFromXML(/*[in]*/ const wchar_t* XML, /*, [in]*/ BOOL AutoSeries/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRChart*)m_ptr.p)->raw_LoadXYZDataFromXML((BSTR)XML, AutoSeries? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 AddXYValue，在指定序列上增加坐标点值。
	// 在指定序列上增加坐标点值，散列点图、散列连线图、散列曲线图等。
	// 在用这个方法加入数据之前，一般需要调用 EmptyXYValue 方法清空已经存在的数据。
	// 如刷新生成报表时，上次生成加入的数据不会自动清理掉，如果不进行清理，再次加入的数据还是继续在原有数据的基础上继续增加，这样肯定不是我们期望的。
	//@参数 序列序号 指定序列，序号从 0 开始。 
	//@参数 X轴值 指定坐标X值。 
	//@参数 Y轴值 指定坐标Y值。
	//@别名 增加XY坐标值(序列序号,X轴值,Y轴值)
	/*virtual*/ HRESULT AddXYValue(/*[in]*/ long SeriesIndex, /*, [in]*/ double XVal, /*, [in]*/ double YVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_AddXYValue(SeriesIndex, XVal, YVal); return _result; }
	//@备注 AddXYZValue，在指定序列上增加坐标点值与Z值，XYZ类型的数据用于气泡图。
	// 在用这个方法加入数据之前，一般需要调用 EmptyXYValue 方法清空已经存在的数据。
	// 如刷新生成报表时，上次生成加入的数据不会自动清理掉，如果不进行清理，再次加入的数据还是继续在原有数据的基础上继续增加，这样肯定不是我们期望的。
	//@参数 序列序号 指定序列，序号从 0 开始。 
	//@参数 X轴值 指定坐标X值。 
	//@参数 Y轴值 指定坐标Y值。
	//@参数 Z轴值 指定坐标Z值。
	//@别名 增加XYZ坐标值(序列序号,X轴值,Y轴值,Z轴值)
	/*virtual*/ HRESULT AddXYZValue(/*[in]*/ long SeriesIndex, /*, [in]*/ double XVal, /*, [in]*/ double YVal, /*, [in]*/ double ZVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_AddXYZValue(SeriesIndex, XVal, YVal, ZVal); return _result; }
	//@备注 EmptyValues，清空全部值。
	// 此方法仅对 XY 或 XYZ 值类型图表有效。
	//@别名 清空全部值()
	/*virtual*/ HRESULT EmptyValues(){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_EmptyValues(); return _result; }
	//@备注 GetXYValue，获取指定坐标点的XY值
	//@参数 序列序号 指定序列，序号从 0 开始。 
	//@参数 索引 指定序列中的数据序号。 
	//@参数 X轴值 存储返回坐标点X值。 
	//@参数 Y轴值 存储返回坐标点Y值。
	//@别名 取XY坐标值(序列序号,索引,X轴值,Y轴值)
	/*virtual*/ HRESULT GetXYValue(/*[in]*/ long SeriesIndex, /*, [in]*/ long Index, /*, [out]*/ double* pXVal, /*, [out]*/ double* pYVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_GetXYValue(SeriesIndex, Index, pXVal, pYVal); return _result; }
	//@备注 GetXYZValue，获取指定序列指定序号的XYZ值
	//@参数 序列序号 指定序列，序号从 0 开始。 
	//@参数 索引 指定序列中的数据序号。 
	//@参数 X轴值 存储返回坐标点X值。 
	//@参数 Y轴值 存储返回坐标点Y值。
	//@参数 Z轴值 存储返回坐标点Z值。
	//@别名 取XYZ坐标值(序列序号,索引,X轴值,Y轴值,Z轴值)
	/*virtual*/ HRESULT GetXYZValue(/*[in]*/ long SeriesIndex, /*, [in]*/ long Index, /*, [out]*/ double* pXVal, /*, [out]*/ double* pYVal, /*, [out]*/ double* pZVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_GetXYZValue(SeriesIndex, Index, pXVal, pYVal, pZVal); return _result; }
	//@备注 GetValueText，获取指定序列和组簇的值文本。
	//@参数 序列序号 序号从 0 开始。
	//@参数 组簇序号 序号从 0 开始。
	//@别名 取值文本(序列序号,组簇序号)
	/*virtual*/ CXText GetValueText(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex/*, [out][retVal] const wchar_t** pValueText*/){ BSTR _result = 0; CXText _result_text; ((IGRChart*)m_ptr.p)->raw_GetValueText(SeriesIndex, GroupIndex, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SetValueText，设置指定序列和组簇的值文本。
	//@参数 序列序号 序号从 0 开始。
	//@参数 组簇序号 序号从 0 开始。
	//@参数 值文本 需要显示的文本。
	//@别名 置值文本(序列序号,组簇序号,值文本)
	/*virtual*/ HRESULT SetValueText(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex, /*, [in]*/ const wchar_t* ValueText){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_SetValueText(SeriesIndex, GroupIndex, (BSTR)ValueText); return _result; }
	/*virtual*/ HRESULT MapToRecordset(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_MapToRecordset(SeriesIndex, GroupIndex); return _result; }
	/*virtual*/ OLE_HANDLE get__SeriesCursorHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRChart*)m_ptr.p)->get__SeriesCursorHandle(&_result); return _result; }
	/*virtual*/ OLE_HANDLE get__LegendCursorHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRChart*)m_ptr.p)->get__LegendCursorHandle(&_result); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRChart*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->put_Lock(pVal); return _result; }
	//@备注 SetGroupLabel，方法，根据组簇序号设置某个组簇的标签文字。
	//@参数 组簇序号 组簇序号，从 0 开始。 
	//@参数 标签文本 要设置的标签文字。
	//@别名 设置组标签(组簇序号,标签文本)
	/*virtual*/ HRESULT SetGroupLabel(/*[in]*/ long GroupIndex, /*, [in]*/ const wchar_t* newVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_SetGroupLabel(GroupIndex, (BSTR)newVal); return _result; }
	//@备注 SetSeriesLabel，方法，根据序列序号设置某个序列的标签文字。
	//@参数 序列序号 序列序号，从 0 开始。
	//@参数 标签文本 要设置的标签文字。
	//@别名 设置序列标签(序列序号,标签文本)
	/*virtual*/ HRESULT SetSeriesLabel(/*[in]*/ long SeriesIndex, /*, [in]*/ const wchar_t* newVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_SetSeriesLabel(SeriesIndex, (BSTR)newVal); return _result; }
	//@备注 SetValue，方法，根据序列号与组簇号设定一个数据项的值。
	//@参数 序列序号 序列序号，从 0 开始。
	//@参数 组簇序号 组簇序号，从 0 开始。 
	//@参数 数据值 要设置的数字值。
	//@别名 设置值(序列序号,组簇序号,数据值)
	/*virtual*/ HRESULT SetValue(/*[in]*/ long SeriesIndex, /*, [in]*/ long GroupIndex, /*, [in]*/ double newVal){ HRESULT _result = ((IGRChart*)m_ptr.p)->raw_SetValue(SeriesIndex, GroupIndex, newVal); return _result; }

};
//@备注 ChartAxis，表示图表轴的接口。
//@别名 图表轴
class CIGRChartAxis : public CIGRObject
{
public:
	CIGRChartAxis(){};
	CIGRChartAxis(IGRChartAxis* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRChartAxis* GetPtr(){ return ((IGRChartAxis*)m_ptr.p); }
	//@备注 Label，坐标轴显示的标签文字。
	//@别名 取标签()
	/*virtual*/ CXText get_Label(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartAxis*)m_ptr.p)->get_Label(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Label，坐标轴显示的标签文字。
	//@参数 标签文本 
	//@别名 置标签(标签文本)
	/*virtual*/ HRESULT set_Label(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_Label((BSTR)pVal); return _result; }
	//@备注 Max，坐标轴表示的最大值。
	// 如果本属性值为0，将根据图表数据自动确定坐标轴的最大值。
	//@别名 取最大值()
	/*virtual*/ double get_Max(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChartAxis*)m_ptr.p)->get_Max(&_result); return _result; }
	//@备注 Max，坐标轴表示的最大值。
	// 如果本属性值为0，将根据图表数据自动确定坐标轴的最大值。
	//@参数 小数值 
	//@别名 置最大值(小数值)
	/*virtual*/ HRESULT set_Max(/*[in]*/ double pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_Max(pVal); return _result; }
	//@备注 Min，坐标轴表示的最小值。
	//@别名 取最小值()
	/*virtual*/ double get_Min(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChartAxis*)m_ptr.p)->get_Min(&_result); return _result; }
	//@备注 Min，坐标轴表示的最小值。
	//@参数 小数值 
	//@别名 置最小值(小数值)
	/*virtual*/ HRESULT set_Min(/*[in]*/ double pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_Min(pVal); return _result; }
	//@备注 Space，坐标轴的刻度步长。
	// 如果本属性值为0，将根据图表数据自动确定坐标轴的刻度步长值。
	//@别名 取刻度步长()
	/*virtual*/ double get_Space(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChartAxis*)m_ptr.p)->get_Space(&_result); return _result; }
	//@备注 Space，坐标轴的刻度步长。
	// 如果本属性值为0，将根据图表数据自动确定坐标轴的刻度步长值。
	//@参数 小数值 
	//@别名 置刻度步长(小数值)
	/*virtual*/ HRESULT set_Space(/*[in]*/ double pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_Space(pVal); return _result; }
	//@备注 TextAngle，坐标轴的刻度文字的显示角度，已度为单位，逆时针方向为正。
	//@别名 取文字角度()
	/*virtual*/ double get_TextAngle(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChartAxis*)m_ptr.p)->get_TextAngle(&_result); return _result; }
	//@备注 TextAngle，坐标轴的刻度文字的显示角度，已度为单位，逆时针方向为正。
	//@参数 角度值 
	//@别名 置文字角度(角度值)
	/*virtual*/ HRESULT set_TextAngle(/*[in]*/ double pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_TextAngle(pVal); return _result; }
	//@备注 TextVisible，指定坐标轴刻度文字是否显示。
	//@别名 取文字可见性()
	/*virtual*/ BOOL get_TextVisible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartAxis*)m_ptr.p)->get_TextVisible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 TextVisible，指定坐标轴刻度文字是否显示。
	//@参数 逻辑值 
	//@别名 置文字可见性(逻辑值)
	/*virtual*/ HRESULT set_TextVisible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_TextVisible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TextFormat，刻度值格式化串，根据其产生刻度的显示文字。
	//@别名 取刻度格式()
	/*virtual*/ CXText get_TextFormat(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartAxis*)m_ptr.p)->get_TextFormat(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TextFormat，刻度值格式化串，根据其产生刻度的显示文字。
	//@参数 格式文本 
	//@别名 置刻度格式(格式文本)
	/*virtual*/ HRESULT set_TextFormat(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_TextFormat((BSTR)pVal); return _result; }
	//@备注 LineVisible，指示坐标轴的轴线是否显示。
	//@别名 取轴线可见性()
	/*virtual*/ BOOL get_LineVisible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartAxis*)m_ptr.p)->get_LineVisible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LineVisible，指示坐标轴的轴线是否显示。
	//@参数 逻辑值 
	//@别名 置轴线可见性(逻辑值)
	/*virtual*/ HRESULT set_LineVisible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_LineVisible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CoordLineVisible，指定坐标轴的数据参考线是否可见。
	//@别名 取坐标线可见性()
	/*virtual*/ BOOL get_CoordLineVisible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartAxis*)m_ptr.p)->get_CoordLineVisible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CoordLineVisible，指定坐标轴的数据参考线是否可见。
	//@参数 逻辑值 
	//@别名 置坐标线可见性(逻辑值)
	/*virtual*/ HRESULT set_CoordLineVisible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_CoordLineVisible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LinePen，绘制坐标轴的轴线的画笔。
	//@别名 取轴线画笔()
	/*virtual*/ class CIGRPen get_LinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 CoordLinePen，绘制本坐标轴的刻度对应的坐标线画笔。
	//@别名 取坐标线画笔()
	/*virtual*/ class CIGRPen get_CoordLinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 MarginBeginWeight，坐标轴起始处留出的空白程度, 与一组(簇)数据所占宽度的百分比。
	// 如果本属性值为0，则最前面的图形紧贴坐标轴的起始位置输出。
	//@返回 默认值25，像素值。
	//@别名 取留起始空白程度()
	/*virtual*/ long get_MarginBeginWeight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChartAxis*)m_ptr.p)->get_MarginBeginWeight(&_result); return _result; }
	//@备注 MarginBeginWeight，坐标轴起始处留出的空白程度, 与一组(簇)数据所占宽度的百分比。
	// 如果本属性值为0，则最前面的图形紧贴坐标轴的起始位置输出。
	//@参数 参数值 默认值25，像素值。
	//@别名 置留起始空白程度(参数值)
	/*virtual*/ HRESULT set_MarginBeginWeight(/*[in]*/ long pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_MarginBeginWeight(pVal); return _result; }
	//@备注 MarginEndWeight，坐标轴终止处留出的空白程度, 与一组(簇)数据所占宽度的百分比。
	// 如果本属性值为0，则最后面的图形紧贴坐标轴的结束位置输出。
	//@返回 默认值25，像素值。
	//@别名 取留结束空白程度()
	/*virtual*/ long get_MarginEndWeight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChartAxis*)m_ptr.p)->get_MarginEndWeight(&_result); return _result; }
	//@备注 MarginEndWeight，坐标轴终止处留出的空白程度, 与一组(簇)数据所占宽度的百分比。
	// 如果本属性值为0，则最后面的图形紧贴坐标轴的结束位置输出。
	//@参数 整数值 默认值25，像素值。
	//@别名 置留结束空白程度(整数值)
	/*virtual*/ HRESULT set_MarginEndWeight(/*[in]*/ long pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_MarginEndWeight(pVal); return _result; }
	//@备注 ScaleCount，图表生成后，此坐标轴显示的刻度个数。
	//@别名 取刻度个数()
	/*virtual*/ long get_ScaleCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChartAxis*)m_ptr.p)->get_ScaleCount(&_result); return _result; }
	//@备注 AddCustomScale，为坐标轴增加一个自定义刻度，参数指定刻度值与显示文字。
	// Grid++Report会根据最大值、最小值与刻度步长自动产生坐标轴刻度，如果需要定义特殊的刻度，则可以应用此方法定义自定义刻度。本方法一次定义一个自定义刻度，通过多次调用把全部刻度定义出来。
	//@参数 刻度值 刻度数字值。
	//@参数 显示文字 刻度显示文字。
	//@别名 增加自定义刻度(刻度值,显示文字)
	/*virtual*/ HRESULT AddCustomScale(/*[in]*/ double ScaleVal, /*, [in]*/ const wchar_t* Text){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->raw_AddCustomScale(ScaleVal, (BSTR)Text); return _result; }
	//@备注 EmptyCustomScale，清除全部自定义刻度。
	// 全部自定义刻度被清除后，Grid++Report会根据最大值、最小值与刻度步长自动产生坐标轴刻度。
	//@别名 清除自定义刻度()
	/*virtual*/ HRESULT EmptyCustomScale(){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->raw_EmptyCustomScale(); return _result; }
	//@备注 GetScaleText，根据序号获得对应刻度的显示文字，序号从0开始。
	//@参数 刻度序号 刻度序号，序号从0开始。
	//@返回 刻度的显示文字。
	//@别名 取刻度文本(刻度序号)
	/*virtual*/ CXText GetScaleText(/*[in]*/ long Index/*, [out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartAxis*)m_ptr.p)->raw_GetScaleText(Index, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetScaleValue，根据序号获得对应刻度的数字值，序号从0开始。
	//@参数 刻度序号 刻度序号，序号从0开始。
	//@返回 刻度的数字值。
	//@别名 取刻度值(刻度序号)
	/*virtual*/ double GetScaleValue(/*[in]*/ long Index/*, [out][retVal] double* pVal*/){double _result=0; ((IGRChartAxis*)m_ptr.p)->raw_GetScaleValue(Index, &_result); return _result; }
	//@备注 AddCustomCoordLine，添加一条坐标轴基准线定义。
	//@参数 刻度值 基准线对应的坐标轴值。 
	//@参数 显示文字 基准线在坐标轴上的显示文字。 
	//@参数 线宽 基准线的宽度。 
	//@参数 线颜色 基准线的颜色。
	//@参数 画线笔样式枚举值 基准线的线条类型，画线笔样式枚举值：0、实线； 1、段线； 2、虚线； 3、点划线； 4、双点划线
	//@别名 增加自定义坐标线(刻度值,显示文字,线宽,线颜色,画线笔样式枚举值)
	/*virtual*/ HRESULT AddCustomCoordLine(/*[in]*/ double ScaleVal, /*, [in]*/ const wchar_t* Text, /*, [in]*/ double LineWidth, /*, [in]*/ OLE_COLOR LineColor, /*, [in]*/ GRPenStyle LineStyle){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->raw_AddCustomCoordLine(ScaleVal, (BSTR)Text, LineWidth, LineColor, LineStyle); return _result; }
	//@备注 EmptyCustomCoordLine，清空坐标轴的全部基准线定义。
	//@别名 清除自定义坐标线()
	/*virtual*/ HRESULT EmptyCustomCoordLine(){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->raw_EmptyCustomCoordLine(); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRChartAxis*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_Lock(pVal); return _result; }
	//@备注 DateTimeAxis，取本坐标轴的值是否为日期时间类型。
	//@别名 取日期时间轴()
	/*virtual*/ BOOL get_DateTimeAxis(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartAxis*)m_ptr.p)->get_DateTimeAxis(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DateTimeAxis，指定本坐标轴的值是否为日期时间类型。
	//@参数 逻辑值 
	//@别名 置日期时间轴(逻辑值)
	/*virtual*/ HRESULT set_DateTimeAxis(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_DateTimeAxis(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MaxAtScale，取轴的最大值是否必须在轴刻度上显示出来。
	//@别名 取最大值在刻度()
	/*virtual*/ BOOL get_MaxAtScale(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartAxis*)m_ptr.p)->get_MaxAtScale(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MaxAtScale，指定轴的最大值是否必须在轴刻度上显示出来。
	//@参数 逻辑值 
	//@别名 置最大值在刻度(逻辑值)
	/*virtual*/ HRESULT set_MaxAtScale(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartAxis*)m_ptr.p)->put_MaxAtScale(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 ChartSeriesCollection，集合对象，图表的所有序列的集合对象。
//@别名 图表序列集合
class CIGRChartSeriesCollection : public CXComObj /*IDispatch*/
{
public:
	CIGRChartSeriesCollection(){};
	CIGRChartSeriesCollection(IGRChartSeriesCollection* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRChartSeriesCollection* GetPtr(){ return ((IGRChartSeriesCollection*)m_ptr.p); }
	/*virtual*/ class CIGRChartSeries get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRChartSeries** ppChartSeries*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRChartSeriesCollection*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有序列的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRChartSeriesCollection*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个序列并返回新增序列的接口引用。
	//@返回 新增序列的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRChartSeries Add(/*[out][retVal] class CIGRChartSeries** ppChartSeries*/);
	//@备注 Remove，根据序列的顺序号将序列移除。
	//@参数 序号 指定序列的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRChartSeriesCollection*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部序列。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRChartSeriesCollection*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据序列的名称取得其顺序号，如果不存在与名称匹配的序列，则返回值为-1。
	// 序列的名称不区分字母的大小写。
	//@参数 名称 指定图表序列的名称。
	//@返回 如果存在名称匹配的序列，返回序列的顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRChartSeriesCollection*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的图表序列对象，序号从1开始。
	//@参数 序号 指定图表序列对象在集合中的序号，从1开始。
	//@返回 获取到的图表序列对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRChartSeries ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRChartSeries** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数图表序列的顺序。
	//@参数 序号 指定图表序列的序号，序号从1开始。
	//@参数 新顺序号 图表序列在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRChartSeriesCollection*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 ChartSeries，表示图表序列的接口。
//@别名 图表序列
class CIGRChartSeries : public CIGRObject
{
public:
	CIGRChartSeries(){};
	CIGRChartSeries(IGRChartSeries* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRChartSeries* GetPtr(){ return ((IGRChartSeries*)m_ptr.p); }
	//@备注 ChartType，指定本序列的图表类型。
	//@别名 取图表类型()
	/*virtual*/ GRChartType get_ChartType(/*[out][retVal] GRChartType* pVal*/){GRChartType _result; ((IGRChartSeries*)m_ptr.p)->get_ChartType(&_result); return _result; }
	//@备注 ChartType，指定本序列的图表类型。
	//@参数 图表类型枚举值 
	//@别名 置图表类型(图表类型枚举值)
	/*virtual*/ HRESULT set_ChartType(/*[in]*/ GRChartType pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_ChartType(pVal); return _result; }
	//@备注 ByY2Axis，指定本序列是否应用Y2坐标轴。
	// 如果整个图表是双轴图表，则必然会定义至少一个序列是应用Y2坐标轴。
	//@别名 取应用Y2座标轴()
	/*virtual*/ BOOL get_ByY2Axis(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_ByY2Axis(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ByY2Axis，指定本序列是否应用Y2坐标轴。
	// 如果整个图表是双轴图表，则必然会定义至少一个序列是应用Y2坐标轴。
	//@参数 逻辑值 
	//@别名 置应用Y2座标轴(逻辑值)
	/*virtual*/ HRESULT set_ByY2Axis(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_ByY2Axis(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SeriesName，如果未在数据中指定序列标签文字，此属性值将默认为标签文字。
	//@别名 取序列名称()
	/*virtual*/ CXText get_SeriesName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_SeriesName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SeriesName，如果未在数据中指定序列标签文字，此属性值将默认为标签文字。
	//@参数 名称 
	//@别名 置序列名称(名称)
	/*virtual*/ HRESULT set_SeriesName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_SeriesName((BSTR)pVal); return _result; }
	//@备注 XValueField，指定X值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义X值关联的字段名称。
	//@别名 取X值字段()
	/*virtual*/ CXText get_XValueField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_XValueField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 XValueField，指定X值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义X值关联的字段名称。
	//@参数 字段名称 
	//@别名 置X值字段(字段名称)
	/*virtual*/ HRESULT set_XValueField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_XValueField((BSTR)pVal); return _result; }
	//@备注 YValueField，指定Y值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义Y值关联的字段名称。
	//@别名 取Y值字段()
	/*virtual*/ CXText get_YValueField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_YValueField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 YValueField，指定Y值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义Y值关联的字段名称。
	//@参数 字段名称 
	//@别名 置Y值字段(字段名称)
	/*virtual*/ HRESULT set_YValueField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_YValueField((BSTR)pVal); return _result; }
	//@备注 ZValueField，指定Z值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义Z值关联的字段名称。
	//@别名 取Z值字段()
	/*virtual*/ CXText get_ZValueField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_ZValueField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ZValueField，指定Z值对应的字段名称。
	// 如果图标数据来自图表的记录集，则必须要定义Z值关联的字段名称。
	//@参数 字段名称 
	//@别名 置Z值字段(字段名称)
	/*virtual*/ HRESULT set_ZValueField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_ZValueField((BSTR)pVal); return _result; }
	//@备注 LabelText，标签显示文本，文本中可以插入动态数据域。
	// 标签文本类似综合文本框的“文本”属性定义，一般都需要在其中插入动态数据域，通常都需要插入图表变量。
	//@别名 取标签文本()
	/*virtual*/ CXText get_LabelText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_LabelText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LabelText，标签显示文本，文本中可以插入动态数据域。
	// 标签文本类似综合文本框的“文本”属性定义，一般都需要在其中插入动态数据域，通常都需要插入图表变量。
	//@参数 文本 表达式文本
	//@别名 置标签文本(文本)
	/*virtual*/ HRESULT set_LabelText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_LabelText((BSTR)pVal); return _result; }
	//@备注 LabelTextAngle，指定标签文字的显示角度，以度为单位。
	//@别名 取标签文本角度()
	/*virtual*/ double get_LabelTextAngle(/*[out][retVal] double* pVal*/){double _result=0; ((IGRChartSeries*)m_ptr.p)->get_LabelTextAngle(&_result); return _result; }
	//@备注 LabelTextAngle，指定标签文字的显示角度，以度为单位。
	//@参数 角度值 
	//@别名 置标签文本角度(角度值)
	/*virtual*/ HRESULT set_LabelTextAngle(/*[in]*/ double pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_LabelTextAngle(pVal); return _result; }
	//@备注 LabelAsGroup，指定是否按组簇显示标签文字。
	// 如果本属性值为是，则在一个组簇中，每个序列不各自产生标签文字，而是整个组簇产生一个共同的标签文字。
	//@别名 取按组显示标签()
	/*virtual*/ BOOL get_LabelAsGroup(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_LabelAsGroup(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LabelAsGroup，指定是否按组簇显示标签文字。
	// 如果本属性值为是，则在一个组簇中，每个序列不各自产生标签文字，而是整个组簇产生一个共同的标签文字。
	//@参数 逻辑值 
	//@别名 置按组显示标签(逻辑值)
	/*virtual*/ HRESULT set_LabelAsGroup(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_LabelAsGroup(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LabelInBar，指定标签文字是否显示在柱形中。
	// 此属性仅对各种柱状图有效。
	//@别名 取标签在柱形中()
	/*virtual*/ BOOL get_LabelInBar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_LabelInBar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LabelInBar，指定标签文字是否显示在柱形中。
	// 此属性仅对各种柱状图有效。
	//@参数 逻辑值 
	//@别名 置标签在柱形中(逻辑值)
	/*virtual*/ HRESULT set_LabelInBar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_LabelInBar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TooltipText，指定鼠标光标停留在数据项图形上时弹出显示的提示文字。
	// 此属性仅对报表在查询显示控件中展现时有效。
	//@别名 取提示文本()
	/*virtual*/ CXText get_TooltipText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_TooltipText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TooltipText，指定鼠标光标停留在数据项图形上时弹出显示的提示文字。
	// 此属性仅对报表在查询显示控件中展现时有效。
	//@参数 文本 
	//@别名 置提示文本(文本)
	/*virtual*/ HRESULT set_TooltipText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_TooltipText((BSTR)pVal); return _result; }
	//@备注 ValueFormat，产生数据项值的显示文字的格式化串。
	// 如果标签文本属性中未定义格式化串，则此属性会被用来格式化产生显示文字。图例中的数据值也用此属性格式化产生显示文字。
	//@别名 取数据格式()
	/*virtual*/ CXText get_ValueFormat(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRChartSeries*)m_ptr.p)->get_ValueFormat(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ValueFormat，产生数据项值的显示文字的格式化串。
	// 如果标签文本属性中未定义格式化串，则此属性会被用来格式化产生显示文字。图例中的数据值也用此属性格式化产生显示文字。
	//@参数 文本 
	//@别名 置数据格式(文本)
	/*virtual*/ HRESULT set_ValueFormat(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_ValueFormat((BSTR)pVal); return _result; }
	//@备注 BorderPen，指定绘制一个图形元素的边框画笔。
	// 如一个柱状图，在绘制一个柱形时，此属性指定了柱形外围的边框线。
	//@别名 取图形画笔()
	/*virtual*/ class CIGRPen get_BorderPen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 FillColor，指定本序列图形的填充颜色，如柱状图的柱形颜色。
	// 如果填充颜色自动属性值为是，则本属性定义不起作用。
	//@别名 取填充颜色()
	/*virtual*/ OLE_COLOR get_FillColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRChartSeries*)m_ptr.p)->get_FillColor(&_result); return _result; }
	//@备注 FillColor，指定本序列图形的填充颜色，如柱状图的柱形颜色。
	// 如果填充颜色自动属性值为是，则本属性定义不起作用。
	//@参数 整数值 
	//@别名 置填充颜色(整数值)
	/*virtual*/ HRESULT set_FillColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_FillColor(pVal); return _result; }
	//@备注 FillColorAuto，指定是否自动产生图形的填充颜色。
	// 如果本属性值为是，则填充颜色属性定义不起作用。
	//@别名 取填充颜色自动()
	/*virtual*/ BOOL get_FillColorAuto(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_FillColorAuto(&_result); return (VARIANT_TRUE==_result); }
	//@备注 FillColorAuto，指定是否自动产生图形的填充颜色。
	// 如果本属性值为是，则填充颜色属性定义不起作用。
	//@参数 逻辑值 
	//@别名 置填充颜色自动(逻辑值)
	/*virtual*/ HRESULT set_FillColorAuto(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_FillColorAuto(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MarkerStyle，数据项的标记图形类型。
	//@别名 取标记类型()
	/*virtual*/ GRPointMarkerStyle get_MarkerStyle(/*[out][retVal] GRPointMarkerStyle* pVal*/){GRPointMarkerStyle _result; ((IGRChartSeries*)m_ptr.p)->get_MarkerStyle(&_result); return _result; }
	//@备注 MarkerStyle，数据项的标记图形类型。
	//@参数 标记类型枚举值 
	//@别名 置标记类型(标记类型枚举值)
	/*virtual*/ HRESULT set_MarkerStyle(/*[in]*/ GRPointMarkerStyle pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_MarkerStyle(pVal); return _result; }
	//@备注 MarkerSize，数据项的标记图形的大小。
	//@返回 默认值8
	//@别名 取标记大小()
	/*virtual*/ long get_MarkerSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRChartSeries*)m_ptr.p)->get_MarkerSize(&_result); return _result; }
	//@备注 MarkerSize，数据项的标记图形的大小。
	//@参数 整数值 默认值8
	//@别名 置标记大小(整数值)
	/*virtual*/ HRESULT set_MarkerSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_MarkerSize(pVal); return _result; }
	//@备注 MarkerColor，数据项的标记图形颜色。
	//@别名 取标记颜色()
	/*virtual*/ OLE_COLOR get_MarkerColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRChartSeries*)m_ptr.p)->get_MarkerColor(&_result); return _result; }
	//@备注 MarkerColor，数据项的标记图形颜色。
	//@参数 整数值 
	//@别名 置标记颜色(整数值)
	/*virtual*/ HRESULT set_MarkerColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_MarkerColor(pVal); return _result; }
	//@备注 MarkerColorAuto，是否自动产生数据项的标记点颜色。
	// 如果本属性为是，则标记颜色属性定义无效。
	//@别名 取标记颜色自动()
	/*virtual*/ BOOL get_MarkerColorAuto(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_MarkerColorAuto(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MarkerColorAuto，是否自动产生数据项的标记点颜色。
	// 如果本属性为是，则标记颜色属性定义无效。
	//@参数 逻辑值 
	//@别名 置标记颜色自动(逻辑值)
	/*virtual*/ HRESULT set_MarkerColorAuto(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_MarkerColorAuto(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MarkerPen，绘制数据项的标记图形的画笔。
	//@别名 取标记画笔()
	/*virtual*/ class CIGRPen get_MarkerPen(/*[out][retVal] class CIGRPen** pVal*/);
	/*virtual*/ BOOL get_MarkerLegendShow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRChartSeries*)m_ptr.p)->get_MarkerLegendShow(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_MarkerLegendShow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_MarkerLegendShow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRChartSeries*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRChartSeries*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Recordset，表示明细网格的记录集。拥有一组字段，在报表运行时可以读取与添加记录数据。
// 存储与操作明细记录的对象，当添加明细网格之后，明细网格就自动拥有记录集对象。记录集由多个字段组成。
// 在运行时，提供给报表的明细记录数据被存储到此对象中。
// 报表开发者通过设置数据库连接串与查询SQL，报表在设计时与运行时根据此设置取得供明细记录数据。
// 如果没有设置数据库连接串与查询SQL或指定在运行时不根据数据库连接串与查询SQL设置取明细记录数据，则必须在 FetchRecord 事件中填充记录集数据。
//@别名 数据集
class CIGRRecordset : public CIGRObject
{
public:
	CIGRRecordset(){};
	CIGRRecordset(IGRRecordset* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRRecordset* GetPtr(){ return ((IGRRecordset*)m_ptr.p); }
	//@备注 Fields，拥有的字段集合对象的接口引用。
	//@别名 取字段集合()
	/*virtual*/ class CIGRFields get_Fields(/*[out][retVal] class CIGRFields** pVal*/);
	//@备注 RecordCount，指示记录集中的记录条数。
	//@别名 取记录数()
	/*virtual*/ long get_RecordCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRRecordset*)m_ptr.p)->get_RecordCount(&_result); return _result; }
	//@备注 RecordNo，指示当前记录的记录号，记录号从0开始。
	// 
	//@别名 取记录号()
	/*virtual*/ long get_RecordNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRRecordset*)m_ptr.p)->get_RecordNo(&_result); return _result; }
	//@备注 ConnectionString，与数据源连接的参数文字串。
	// 如果明细记录集的“数据库连接”属性不指定，明细记录集的查询SQL将自动应用报表主对象上的数据库连接设置。
	// 如果本报表是子报表，还将自动应用其父报表的数据库连接设置。
	//@别名 取连接串()
	/*virtual*/ CXText get_ConnectionString(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_ConnectionString(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ConnectionString，与数据源连接的参数文字串。
	// 如果明细记录集的“数据库连接”属性不指定，明细记录集的查询SQL将自动应用报表主对象上的数据库连接设置。
	// 如果本报表是子报表，还将自动应用其父报表的数据库连接设置。
	//@参数 连接串 
	//@别名 置连接串(连接串)
	/*virtual*/ HRESULT set_ConnectionString(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_ConnectionString((BSTR)pVal); return _result; }
	//@备注 QuerySQL，从数据源中取数的SQL语句。
	//@别名 取查询SQL()
	/*virtual*/ CXText get_QuerySQL(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_QuerySQL(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 QuerySQL，从数据源中取数的SQL语句。
	//@参数 查询SQL语句 
	//@别名 置查询SQL(查询SQL语句)
	/*virtual*/ HRESULT set_QuerySQL(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_QuerySQL((BSTR)pVal); return _result; }
	//@备注 SkipQuery，指示在生成报表时，是否忽略从数据源取数的属性设置。
	//@别名 取忽略数据查询()
	/*virtual*/ BOOL get_SkipQuery(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->get_SkipQuery(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SkipQuery，指示在生成报表时，是否忽略从数据源取数的属性设置。
	//@参数 逻辑值 
	//@别名 置忽略数据查询(逻辑值)
	/*virtual*/ HRESULT set_SkipQuery(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_SkipQuery(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 XmlTableName，指定本记录集对应的 XML 或 JSON 格式数据包中相对应的记录集的名称。
	// 通常情况下不需要设置此属性，只有当需要通过 XML 或 JSON 数据包加载数据，且数据包中包含有多个记录集，此时设置此属性才会生效。
	// Grid++Report 会自动匹配多记录集数据包中的各个记录集到报表中的对应对象中，通过设置此属性让本记录集与数据包中的记录集产生固定的关联，而不会采用自动匹配方式。
	//@别名 取Xml表名()
	/*virtual*/ CXText get_XmlTableName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_XmlTableName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 XmlTableName，指定本记录集对应的 XML 或 JSON 格式数据包中相对应的记录集的名称。
	// 通常情况下不需要设置此属性，只有当需要通过 XML 或 JSON 数据包加载数据，且数据包中包含有多个记录集，此时设置此属性才会生效。
	// Grid++Report 会自动匹配多记录集数据包中的各个记录集到报表中的对应对象中，通过设置此属性让本记录集与数据包中的记录集产生固定的关联，而不会采用自动匹配方式。
	//@参数 文本 
	//@别名 置Xml表名(文本)
	/*virtual*/ HRESULT set_XmlTableName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_XmlTableName((BSTR)pVal); return _result; }
	//@备注 SortFields，指定在报表生成时对记录进行排序的依据字段。
	// 如果设置了本属性，在记录集记录填充完成之后和对记录进行处理之前，报表引擎会根据排序字段对记录进行排序。
	// 如果要按多个字段进行排序，字段名称之间用‘;’隔开。也可以在字段后面加上激昂叙标志，指示对应字段按降序排序。
	// 例子1:按Fld1 与 Fld2 进行排序，两个字段都为升序
	// Fld1;Fld2
	// 例子2:按Fld1 与 Fld2 进行排序， Fld1为降序，Fld2为升序
	// Fld1 DESC;Fld2
	//@别名 取排序字段()
	/*virtual*/ CXText get_SortFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_SortFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SortFields，指定在报表生成时对记录进行排序的依据字段。
	// 如果设置了本属性，在记录集记录填充完成之后和对记录进行处理之前，报表引擎会根据排序字段对记录进行排序。
	// 如果要按多个字段进行排序，字段名称之间用‘;’隔开。也可以在字段后面加上激昂叙标志，指示对应字段按降序排序。
	// 例子1:按Fld1 与 Fld2 进行排序，两个字段都为升序
	// Fld1;Fld2
	// 例子2:按Fld1 与 Fld2 进行排序， Fld1为降序，Fld2为升序
	// Fld1 DESC;Fld2
	//@参数 字段名称 如果要按多个字段进行排序，字段名称之间用‘;’隔开。也可以在字段后面加上激昂叙标志，指示对应字段按降序排序。
	//@别名 置排序字段(字段名称)
	/*virtual*/ HRESULT set_SortFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_SortFields((BSTR)pVal); return _result; }
	//@备注 SortAsc，指定是否按升序排列记录。
	//@别名 取排序按升序()
	/*virtual*/ BOOL get_SortAsc(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->get_SortAsc(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SortAsc，指定是否按升序排列记录。
	//@参数 逻辑值 
	//@别名 置排序按升序(逻辑值)
	/*virtual*/ HRESULT set_SortAsc(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_SortAsc(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SortCaseSensitive，当排序字段为字符型时，指定排序比较是否为大小写字符敏感。
	//@别名 取排序大小写敏感()
	/*virtual*/ BOOL get_SortCaseSensitive(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->get_SortCaseSensitive(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SortCaseSensitive，当排序字段为字符型时，指定排序比较是否为大小写字符敏感。
	//@参数 逻辑值 
	//@别名 置排序大小写敏感(逻辑值)
	/*virtual*/ HRESULT set_SortCaseSensitive(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_SortCaseSensitive(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Editable，指定记录集在报表运行时是否为可编辑。
	//@别名 取可编辑()
	/*virtual*/ BOOL get_Editable(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->get_Editable(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Editable，指定记录集在报表运行时是否为可编辑。
	//@参数 逻辑值 
	//@别名 置可编辑(逻辑值)
	/*virtual*/ HRESULT set_Editable(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_Editable(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 FetchRecordScript，表示报表 FetchRecord 事件对应的脚本语言代码。
	//@别名 取记录脚本()
	/*virtual*/ CXText get_FetchRecordScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_FetchRecordScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 FetchRecordScript，表示报表 FetchRecord 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置取记录脚本(脚本文本)
	/*virtual*/ HRESULT set_FetchRecordScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_FetchRecordScript((BSTR)pVal); return _result; }
	//@备注 BeforePostRecordScript，表示报表 BeforePostRecord 事件对应的脚本语言代码。
	//@别名 取提交记录前脚本()
	/*virtual*/ CXText get_BeforePostRecordScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_BeforePostRecordScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 BeforePostRecordScript，表示报表 BeforePostRecord 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置提交记录前脚本(脚本文本)
	/*virtual*/ HRESULT set_BeforePostRecordScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_BeforePostRecordScript((BSTR)pVal); return _result; }
	//@备注 ProcessRecordScript，表示报表 ProcessRecord 事件对应的脚本语言代码。
	//@别名 取处理记录脚本()
	/*virtual*/ CXText get_ProcessRecordScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_ProcessRecordScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ProcessRecordScript，表示报表 ProcessRecord 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置处理记录脚本(脚本文本)
	/*virtual*/ HRESULT set_ProcessRecordScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_ProcessRecordScript((BSTR)pVal); return _result; }
	//@备注 PageProcessRecordScript，表示报表 PageProcessRecord 事件对应的脚本语言代码。
	//@别名 取页处理记录脚本()
	/*virtual*/ CXText get_PageProcessRecordScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->get_PageProcessRecordScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PageProcessRecordScript，表示报表 PageProcessRecord 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置页处理记录脚本(脚本文本)
	/*virtual*/ HRESULT set_PageProcessRecordScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_PageProcessRecordScript((BSTR)pVal); return _result; }
	//@备注 FieldByName，根据字段名称得到匹配字段对象的接口引用，如果找到名称匹配的字段，则返回该字段对象的接口引用，否则返回NULL。
	//@参数 字段名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按名称取字段(字段名称)
	/*virtual*/ class CIGRField FieldByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRField** ppField*/);
	//@备注 FieldByDBName，根据字段的数据源字段名称得到匹配字段对象的接口引用，如果找到匹配的字段，则返回该字段对象的接口引用，否则返回NULL。
	//@参数 字段名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按源名称取字段(字段名称)
	/*virtual*/ class CIGRField FieldByDBName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRField** ppField*/);
	//@备注 Append，添加一条形记录。
	// 在调用Append方法之后，然后向各个字段赋值，最后调用Post方法将新记录提交。
	// 新记录只有提交之后才会存储打记录集中。此方法只能在 FetchData 事件响应函数中使用。
	//@别名 追加()
	/*virtual*/ HRESULT Append(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Append(); return _result; }
	//@备注 Edit，使当前记录进入可编辑状态，从而可以改变字段的值。
	// 只有当报表处于运行时且记录集是可以编辑的，才能成功使当前记录进入可编辑状态。在记录进入可编辑状态之后，可以给各个字段赋值，最后调用 Post 方法将编辑后的记录保存到记录集中；也可以调用 Cancel
	//  方法取消编辑改变，将当前记录还原为原来的数据。
	// 注意：不能在记录编辑状态中改变不定长字符字段与二进制字段的值。
	//@别名 编辑()
	/*virtual*/ HRESULT Edit(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Edit(); return _result; }
	//@备注 Cancel，取消当前记录的可编辑状态，并还原记录的原来数据。
	//@别名 取消()
	/*virtual*/ HRESULT Cancel(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Cancel(); return _result; }
	//@备注 Post，提交新增记录。
	// 在调用Append方法之后，然后向各个字段赋值，最后调用Post方法将新记录提交。
	// 新记录只有提交之后才会存储打记录集中。此方法只能在 FetchData 事件响应函数中使用。
	//@别名 提交()
	/*virtual*/ HRESULT Post(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Post(); return _result; }
	//@备注 First，使第一条记录成为当前记录。
	//@别名 第一条()
	/*virtual*/ HRESULT First(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_First(); return _result; }
	//@备注 Next，使当前记录的下一条记录成为当前记录。
	// 如果当前记录已经是最后一条记录，调用Next方法将使记录集游标位于Eof(记录尾)。
	//@别名 下一条()
	/*virtual*/ HRESULT Next(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Next(); return _result; }
	//@备注 Prior，使当前记录的上一条记录成为当前记录。
	// 如果当前记录已经是第一条记录，调用Prior方法将使记录集游标位于Bof(记录头)。
	//@别名 上一条()
	/*virtual*/ HRESULT Prior(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Prior(); return _result; }
	//@备注 Last，使最后一条记录成为当前记录。
	//@别名 最后一条()
	/*virtual*/ HRESULT Last(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Last(); return _result; }
	//@备注 MoveBy，将游标向前或向后移动指定个数的记录。
	// 如果移动偏移量超出记录集的范围，将使记录集位置处于Bof或Eof的位置。
	//@参数 移动距离 当前记录移动偏移量，为正向前移动，为负向后移动
	//@别名 相对移动(移动距离)
	/*virtual*/ HRESULT MoveBy(/*[in]*/ int Delta){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_MoveBy(Delta); return _result; }
	//@备注 Bof，判断记录集的游标是否位于第一条记录之前。
	// 当游标位于第一条记录之前，各个字段的值为第一条记录的数据。当记录集中不存在记录时，Bof始终返回真。
	//@返回 bool 游标位于第一条记录之前，返回真，否则返回假。
	//@别名 记录头()
	/*virtual*/ BOOL Bof(/*[out][retVal] BOOL* IsBegin*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->raw_Bof(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Eof，判断记录集的游标是否位于最后一条记录之后。
	// 当游标位于最后一条记录之后，各个字段的值为最后一条记录的数据。当记录集中不存在记录时，Eof始终返回真。
	//@返回 bool 游标位于最后一条记录之后，返回真，否则返回假。
	//@别名 记录尾()
	/*virtual*/ BOOL Eof(/*[out][retVal] BOOL* IsEnd*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->raw_Eof(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MoveTo，将记录集的当前记录设为指定记录号的记录。
	// 记录好的编号从零开始，依次递增。
	//@参数 记录号 int RecordNo 指定移动到目标记录的记录号。
	//@别名 移动到(记录号)
	/*virtual*/ HRESULT MoveTo(/*[in]*/ long RecordNo){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_MoveTo(RecordNo); return _result; }
	//@备注 Empty，清空记录集中的全部记录。
	//@别名 清空()
	/*virtual*/ HRESULT Empty(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Empty(); return _result; }
	//@备注 AddField，增加一个字段。
	//@参数 字段名称 指定字段的名称标识。 
	//@参数 字段类型枚举值 指定字段的类型。1、字符； 2、整数； 3、浮点数； 4、货币； 5、逻辑； 6、日期时间； 7、二进制 
	//@返回 返回新增字段对象的接口引用
	//@别名 增加字段(字段名称,字段类型枚举值)
	/*virtual*/ class CIGRField AddField(/*[in]*/ const wchar_t* Name, /*, [in]*/ GRFieldType FieldType/*, [out][retVal] class CIGRField** ppField*/);
	//@备注 RemoveAllFields，删除所有的字段定义。
	//@别名 清空字段()
	/*virtual*/ HRESULT RemoveAllFields(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_RemoveAllFields(); return _result; }
	//@备注 Resort，对记录集中的记录进行重新排序。
	//@参数 排序字段 string Fields 指定排序字段，如果要按多个字段进行排序，字段名称之间用‘;’隔开。
	//@参数 是否升序排序 bool Ascending 指定是否按升序进行排序。 
	//@参数 是否大小写敏感 bool CaseSensitive 指定字符进行排序比较时是否大小写敏感。
	//@别名 重新排序(排序字段,是否升序排序,是否大小写敏感)
	/*virtual*/ BOOL Resort(/*[in]*/ const wchar_t* Fields, /*, [in]*/ BOOL Ascending, /*, [in]*/ BOOL CaseSensitive/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->raw_Resort((BSTR)Fields, Ascending? VARIANT_TRUE : VARIANT_FALSE, CaseSensitive? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveDataToXML，将记录集中的数据保存为XML文本。
	// XML数据格式如下：
	// <xml>
	// <row><CustomerID>HUNGC</CustomerID><CompanyName>五金机械</CompanyName><ContactName>苏先生</ContactName><City>大连</City><Phone>(053) 5556874</Phone></row>
	// <row><CustomerID>CENTC</CustomerID><CompanyName>三捷实业</CompanyName><ContactName>王先生</ContactName><City>大连</City><Phone>(061) 15553392</Phone></row>
	// <row><CustomerID>CACTU</CustomerID><CompanyName>威航货运有限公司</CompanyName><ContactName>刘先生</ContactName><City>大连</City><Phone>(061) 11355555</Phone></row>
	// <row><CustomerID>BLONP</CustomerID><CompanyName>国皓</CompanyName><ContactName>黄雅玲</ContactName><City>大连</City><Phone>(0671) 88601531</Phone></row>
	// </xml>
	//@返回 XML文本数据
	//@别名 保存数据到XML()
	/*virtual*/ CXText SaveDataToXML(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRecordset*)m_ptr.p)->raw_SaveDataToXML(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LoadData，从本地磁盘文件或网络URL处载入记录集数据，数据格式必须是满足格式要求的 XML 或 JSON 文本数据。
	// XML 与 JSON 文本数据的格式请参考：“报表插件(WEB报表)->报表数据”中的说明。
	//@参数 文件名 指定要载入数据的本地磁盘文件或网络URL。
	//@别名 从文件载入数据(文件名)
	/*virtual*/ BOOL LoadData(/*[in]*/ const wchar_t* File/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->raw_LoadData((BSTR)File, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadDataFromXML，从 XML 或 JSON 文本中载入记录集数据。
	// XML 与  JSON 文本数据的格式请参考：“报表插件(WEB报表)->报表数据”中的说明。
	//@参数 XML文本数据 XML文本形式的记录集数据。
	//@别名 从XML载入数据(XML文本数据)
	/*virtual*/ BOOL LoadDataFromXML(/*[in]*/ const wchar_t* XMLText/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRRecordset*)m_ptr.p)->raw_LoadDataFromXML((BSTR)XMLText, &_result); return (VARIANT_TRUE==_result); }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@别名 取锁定()
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRRecordset*)m_ptr.p)->get_Lock(&_result); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@参数 锁定类别枚举 
	//@别名 置锁定(锁定类别枚举)
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->put_Lock(pVal); return _result; }
	//@备注 Duplicate，复制当前正在添加的新记录。
	// 特别提示：此函数只能用在添加记录时触发的“提交记录前脚本(BeforePostRecord)”事件或对应的脚本代码(提交记录前脚本)中。
	// 此函数调用之后，可以重新设置各个字段的值，最后必须调用 Post 函数提交复制的记录。复制的记录在当前追加记录之前。此函数主要用于明细记录的重复打印。
	//   编程说明
	//   在记录集的“提交记录前脚本”属性上写如下脚本，实现复制 count 变量值指定的条路的记录，最后将获得 count+1 条相同的记录。
	//   var i = 0,
	//   count = 3;
	//   //在当前正在追加的记录前面复制 count 条相同的记录
	//   while (i++<count) {
	//   Sender.Duplicate();//复制记录(Duplicate)
	//   //... 这里可以对某些字段重新设置值
	//   Sender.Post(); //复制记录(Duplicate) 之后必须调用 提交(Post)
	//   }
	//@别名 复制记录()
	/*virtual*/ HRESULT Duplicate(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_Duplicate(); return _result; }
	//@备注 FilterByStep，根据间隔数抽样筛选明细记录数据。
	// 此方法一般在“开始处理脚本(ProcessBeginScript)”属性的报表脚本，或“IGridppReport.ProcessBegin 事件”的响应函数中调用。
	//@参数 间隔数 Step，抽样间隔数。
	//@参数 选中最后记录 AlwaysLast，指示最后一条记录是否总是被抽样选中。
	//@别名 筛选间隔(间隔数,选中最后记录)
	/*virtual*/ HRESULT FilterByStep(/*[in]*/ long Step, /*, [in]*/ BOOL AlwaysLast){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterByStep(Step, AlwaysLast? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 FilterByCount，按照均匀的间隔抽样筛选指定条数的明细记录数据。
	// 此方法一般在“开始处理脚本(ProcessBeginScript)”属性的报表脚本，或“IGridppReport.ProcessBegin 事件”的响应函数中调用。
	//@参数 最大计数 MaxCount，指定间隔抽样选择的记录数。
	//@别名 筛选记录数(最大计数)
	/*virtual*/ HRESULT FilterByCount(/*[in]*/ long MaxCount){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterByCount(MaxCount); return _result; }
	//@备注 FilterBegin，开始筛选明细记录，在筛选记录前必须调用本方法。
	// 筛选开始(FilterBegin)、筛选选中(FilterSelect) 与 筛选结束(FilterEnd) 必须在一起按顺序调用。
	// 筛选开始(FilterBegin) 与 筛选结束(FilterEnd) 在开始与结束时调用一次。
	// 筛选选中(FilterSelect) 通常会多次调用，在遍历记录的过程中，将满足条件的记录用 筛选选中(FilterSelect) 方法选中。
	// 这三个方法一般在“开始处理脚本(ProcessBeginScript)”属性的报表脚本，或“IGridppReport.ProcessBegin 事件”的响应函数中调用。
	//   编程说明
	//   //以下代码为“开始处理脚本(ProcessBeginScript)”属性的报表脚本：
	//   var rs = Report.DetailGrid.Recordset;
	//   rs.FilterBegin(); //开始筛选，必须调用
	//   rs.First();
	//   while(!rs.Eof()){
	//      //将符合条件的记录数据用FilterSelect筛选中
	//     if (Report.FieldByName(\"ID\").AsInteger % 50 == 0 || Report.FieldByName(\"ID\").AsInteger > 330){
	//       rs.FilterSelect();
	//      }
	//    rs.Next();
	//   }
	//   rs.FilterEnd(); //结束筛选，将筛选的记录应用上
	//@别名 筛选开始()
	/*virtual*/ HRESULT FilterBegin(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterBegin(); return _result; }
	//@备注 FilterEnd，结束抽样选择，将筛选的记录应用上，在筛选完成后必须调用本方法。
	// 筛选开始(FilterBegin)、筛选选中(FilterSelect) 与 筛选结束(FilterEnd) 必须在一起按顺序调用。
	// 筛选开始(FilterBegin) 与 筛选结束(FilterEnd) 在开始与结束时调用一次。
	// 筛选选中(FilterSelect) 通常会多次调用，在遍历记录的过程中，将满足条件的记录用 筛选选中(FilterSelect) 方法选中。
	//@别名 筛选结束()
	/*virtual*/ HRESULT FilterEnd(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterEnd(); return _result; }
	//@备注 FilterSelect，在筛选记录的过程中，将当前记录作为选中的数据。
	// 筛选开始(FilterBegin)、筛选选中(FilterSelect) 与 筛选结束(FilterEnd) 必须在一起按顺序调用。
	// 筛选开始(FilterBegin) 与 筛选结束(FilterEnd) 在开始与结束时调用一次。
	// 筛选选中(FilterSelect) 通常会多次调用，在遍历记录的过程中，将满足条件的记录用 筛选选中(FilterSelect) 方法选中。
	//@别名 筛选选中()
	/*virtual*/ HRESULT FilterSelect(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterSelect(); return _result; }
	//@备注 FilterReset，取消数据筛选，可访问记录数据将恢复为原始全部数据。
	//@别名 筛选取消()
	/*virtual*/ HRESULT FilterReset(){ HRESULT _result = ((IGRRecordset*)m_ptr.p)->raw_FilterReset(); return _result; }

};
//@备注 Fields，集合对象，记录集的所有字段的集合对象。
//@别名 字段集合
class CIGRFields : public CXComObj /*IDispatch*/
{
public:
	CIGRFields(){};
	CIGRFields(IGRFields* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFields* GetPtr(){ return ((IGRFields*)m_ptr.p); }
	/*virtual*/ class CIGRField get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRField** ppField*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRFields*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有字段的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRFields*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，根据字段类型参数增加一个字段并返回新增字段的接口引用。
	//@返回 新增字段的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRField Add(/*[out][retVal] class CIGRField** ppField*/);
	//@备注 Remove，根据字段的顺序号将字段移除，在输入参数种指定要移除字段的顺序号或名称。
	//@参数 序号 指定字段的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRFields*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部字段。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRFields*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据字段的名称取得其顺序号，如果不存在与名称匹配的字段，则返回-1。
	// 字段的名称不区分字母的大小写。
	//@参数 名称 指定字段的名称。
	//@返回 如果有匹配的字段，返回其顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRFields*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的字段对象，序号从1开始。
	//@参数 序号 指定字段对象在集合中的序号，从1开始。
	//@返回 获取到的字段对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRField ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRField** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数字段的顺序。
	//@参数 序号 指定字段的序号，序号从1开始。
	//@参数 新顺序号 字段在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRFields*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 Field，定义各种类型的数据字段的类。
// 定义记录的每个数据项，字段存储的数据类型由子段的类型确定。
// 在运行时，记录的读写就是通过各个字段值的读写实现。
// 在编辑记录时，不允许对不定长字符字段与二进制字段进行改变。
//@别名 字段
class CIGRField : public CIGRObject
{
public:
	CIGRField(){};
	CIGRField(IGRField* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRField* GetPtr(){ return ((IGRField*)m_ptr.p); }
	//@备注 Name，字段的名称，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，字段的名称，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 DBFieldName，指定字段对应的数据源字段名称。
	// 当以拉模式从数据源提取报表数据时，将按此属性值进行报表字段与数据源字段进行匹配。如果此属性没有定义，则默认与名称保持一致。
	//@别名 取数据源字段名()
	/*virtual*/ CXText get_DBFieldName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_DBFieldName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DBFieldName，指定字段对应的数据源字段名称。
	// 当以拉模式从数据源提取报表数据时，将按此属性值进行报表字段与数据源字段进行匹配。如果此属性没有定义，则默认与名称保持一致。
	//@参数 文本 
	//@别名 置数据源字段名(文本)
	/*virtual*/ HRESULT set_DBFieldName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_DBFieldName((BSTR)pVal); return _result; }
	//@备注 FieldType，获取字段的数据类型。
	//@返回 1、字符； 2、整数； 3、浮点数； 4、货币； 5、逻辑； 6、日期时间； 7、二进制
	//@别名 取类型()
	/*virtual*/ GRFieldType get_FieldType(/*[out][retVal] GRFieldType* pVal*/){GRFieldType _result; ((IGRField*)m_ptr.p)->get_FieldType(&_result); return _result; }
	//@备注 FieldType，设置字段的数据类型。
	//@参数 字段类型枚举值 1、字符； 2、整数； 3、浮点数； 4、货币； 5、逻辑； 6、日期时间； 7、二进制
	//@别名 置类型(字段类型枚举值)
	/*virtual*/ HRESULT set_FieldType(/*[in]*/ GRFieldType pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_FieldType(pVal); return _result; }
	//@备注 Length，获取字符类型字段的字符长度，为 0 表示不定长类型字符类型字段。
	// 不定长字符类型字段可以保存任意长度的字符数据，但在编辑记录时，不定长字符类型字段的值不允许改变。
	//@别名 取长度()
	/*virtual*/ long get_Length(/*[out][retVal] long* pVal*/){long _result=0; ((IGRField*)m_ptr.p)->get_Length(&_result); return _result; }
	//@备注 Length，设置字符类型字段的字符长度，为 0 表示不定长类型字符类型字段。
	// 不定长字符类型字段可以保存任意长度的字符数据，但在编辑记录时，不定长字符类型字段的值不允许改变。
	//@参数 整数值 
	//@别名 置长度(整数值)
	/*virtual*/ HRESULT set_Length(/*[in]*/ long pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_Length(pVal); return _result; }
	//@备注 RTrimBlankChars，指定是否自动截除字符型字段右边的空格字符。此属性仅对字符型字段有效。
	// 数据库中定长类型的字符字段会用空格补足字符位数，这样的文字在进行水平居中显示时就得不到想要的居中效果，如果将此属性置为真，就可以自动截除右边的空格文字，也就可以得到很好的居中效果。
	//@别名 取截除右端空格()
	/*virtual*/ BOOL get_RTrimBlankChars(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRField*)m_ptr.p)->get_RTrimBlankChars(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RTrimBlankChars，指定是否自动截除字符型字段右边的空格字符。此属性仅对字符型字段有效。
	// 数据库中定长类型的字符字段会用空格补足字符位数，这样的文字在进行水平居中显示时就得不到想要的居中效果，如果将此属性置为真，就可以自动截除右边的空格文字，也就可以得到很好的居中效果。
	//@参数 逻辑值 
	//@别名 置截除右端空格(逻辑值)
	/*virtual*/ HRESULT set_RTrimBlankChars(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_RTrimBlankChars(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Format，获取将字段值转换为显示文本时所应用的格式文字串。
	// 本属性只对布尔、整数、浮点数、货币及日期时间类型的字段有效。
	//@别名 取格式()
	/*virtual*/ CXText get_Format(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_Format(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Format，设置将字段值转换为显示文本时所应用的格式文字串。
	// 本属性只对布尔、整数、浮点数、货币及日期时间类型的字段有效。
	//@参数 格式文本 
	//@别名 置格式(格式文本)
	/*virtual*/ HRESULT set_Format(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_Format((BSTR)pVal); return _result; }
	//@备注 Value，获取字段在运行时的值。
	//@别名 取值()
	/*virtual*/ VARIANT get_Value(/*[out][retVal] VARIANT* pVal*/){VARIANT _result; VariantInit(&_result);((IGRField*)m_ptr.p)->get_Value(&_result); return _result; }
	//@备注 Value，设置字段在运行时的值。
	//@参数 变体数据 
	//@别名 置值(变体数据)
	/*virtual*/ HRESULT set_Value(/*[in]*/ VARIANT pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_Value(pVal); return _result; }
	//@备注 AsBoolean，获取字段的用布尔类型表示的逻辑值。
	//@别名 取逻辑值()
	/*virtual*/ BOOL get_AsBoolean(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRField*)m_ptr.p)->get_AsBoolean(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AsBoolean，设置字段的用布尔类型表示的逻辑值。
	//@参数 逻辑值 
	//@别名 置逻辑值(逻辑值)
	/*virtual*/ HRESULT set_AsBoolean(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsBoolean(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AsCurrency，获取字段的用货币类型表示的值。
	//@别名 取货币值()
	/*virtual*/ CURRENCY get_AsCurrency(/*[out][retVal] CURRENCY* pVal*/){CURRENCY _result; ((IGRField*)m_ptr.p)->get_AsCurrency(&_result); return _result; }
	//@备注 AsCurrency，设置字段的用货币类型表示的值。
	//@参数 小数值 
	//@别名 置货币值(小数值)
	/*virtual*/ HRESULT set_AsCurrency(/*[in]*/ CURRENCY pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsCurrency(pVal); return _result; }
	//@备注 AsDateTime，获取字段的用日期时间类型表示的值。
	//@别名 取日期时间值()
	/*virtual*/ DATE get_AsDateTime(/*[out][retVal] DATE* pVal*/){DATE _result=0; ((IGRField*)m_ptr.p)->get_AsDateTime(&_result); return _result; }
	//@备注 AsDateTime，设置字段的用日期时间类型表示的值。
	//@参数 小数值 
	//@别名 置日期时间值(小数值)
	/*virtual*/ HRESULT set_AsDateTime(/*[in]*/ DATE pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsDateTime(pVal); return _result; }
	//@备注 AsFloat，获取字段的用浮点数类型表示的值。
	//@别名 取浮点数值()
	/*virtual*/ double get_AsFloat(/*[out][retVal] double* pVal*/){double _result=0; ((IGRField*)m_ptr.p)->get_AsFloat(&_result); return _result; }
	//@备注 AsFloat，设置字段的用浮点数类型表示的值。
	//@参数 小数值 
	//@别名 置浮点数值(小数值)
	/*virtual*/ HRESULT set_AsFloat(/*[in]*/ double pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsFloat(pVal); return _result; }
	//@备注 AsInteger，获取字段的用整数类型表示的值。
	//@别名 取整数值()
	/*virtual*/ long get_AsInteger(/*[out][retVal] long* pVal*/){long _result=0; ((IGRField*)m_ptr.p)->get_AsInteger(&_result); return _result; }
	//@备注 AsInteger，设置字段的用整数类型表示的值。
	//@参数 整数值 
	//@别名 置整数值(整数值)
	/*virtual*/ HRESULT set_AsInteger(/*[in]*/ long pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsInteger(pVal); return _result; }
	//@备注 AsString，获取字段的用字符串类型表示的值。
	//@别名 取字符值()
	/*virtual*/ CXText get_AsString(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_AsString(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 AsString，设置字段的用字符串类型表示的值。
	//@参数 文本 
	//@别名 置字符值(文本)
	/*virtual*/ HRESULT set_AsString(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_AsString((BSTR)pVal); return _result; }
	//@备注 DisplayText，获取部件框的输出显示文本。只有在运行时才能使用本属性，当不能由Grid++Report根据字段的值自动产生显示文本时，在FieldGetDisplayText事件中为字段的DisplayText属性赋一个新的显示文本。
	//@别名 取显示文字()
	/*virtual*/ CXText get_DisplayText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_DisplayText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DisplayText，获取部件框的输出显示文本。只有在运行时才能使用本属性，当不能由Grid++Report根据字段的值自动产生显示文本时，在FieldGetDisplayText事件中为字段的DisplayText属性赋一个新的显示文本。
	//@参数 名称 
	//@别名 置显示文字(名称)
	/*virtual*/ HRESULT set_DisplayText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_DisplayText((BSTR)pVal); return _result; }
	//@备注 IsNull，获取字段值是否为空的标志。
	//@别名 取是否空值()
	/*virtual*/ BOOL get_IsNull(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRField*)m_ptr.p)->get_IsNull(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DataSize，获取存储二进制字段值的数据缓冲区的大小，以字节为计量单位。
	// 本属性只对二进制类型的字段有效，存储字段值的数据缓冲区的字节大小。用 DataBuffer 属性可以得到数据缓冲区的内存指针。
	//@别名 取数据尺寸()
	/*virtual*/ long get_DataSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRField*)m_ptr.p)->get_DataSize(&_result); return _result; }
	//@备注 DataBuffer，获取存储二进制字段值的数据缓冲区内存地址指针。
	// 本属性只对二进制类型的字段有效，存储字段值的数据缓冲区内存地址指针。用 DataSize 属性可以得到数据缓冲区的大小。
	//@别名 取数据缓冲区()
	/*virtual*/ LONG_PTR get_DataBuffer(/*[out][retVal] LONG_PTR* pVal*/){LONG_PTR _result; ((IGRField*)m_ptr.p)->get_DataBuffer(&_result); return _result; }
	//@备注 RunningDBField，获取在报表运行时与数据源字段进行匹配的字段名称。
	// 当定义了 DBFieldName 的属性值，这取得值为 DBFieldName 属性的值，否则为 Name 属性的值。
	//@别名 取运行时数据源字段名()
	/*virtual*/ CXText get_RunningDBField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_RunningDBField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetDisplayTextScript，表示报表 FieldGetDisplayText 事件对应的脚本语言代码。
	// 在此脚本中可以改写子段的显示文字，通过设置子段的 DisplayText 属性改变其显示文字。
	// 特别提示：在此脚本中，仅能设置 Sender 的 DisplayText 数据，对其它属性的设置可能是不起做用的，还有可能引发不可预料的异常。
	// 编程说明
	// //按条件设置字段的显示文字
	// var a = ...;
	// if (a == ...) 
	//   Sender.DisplayText = \"条件成立的显示文字\";
	// else
	//   Sender.DisplayText = \"其它的显示文字\";
	//@别名 取显示文字脚本()
	/*virtual*/ CXText get_GetDisplayTextScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRField*)m_ptr.p)->get_GetDisplayTextScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetDisplayTextScript，表示报表 FieldGetDisplayText 事件对应的脚本语言代码。
	// 在此脚本中可以改写子段的显示文字，通过设置子段的 DisplayText 属性改变其显示文字。
	// 特别提示：在此脚本中，仅能设置 Sender 的 DisplayText 数据，对其它属性的设置可能是不起做用的，还有可能引发不可预料的异常。
	// 编程说明
	// //按条件设置字段的显示文字
	// var a = ...;
	// if (a == ...) 
	//   Sender.DisplayText = \"条件成立的显示文字\";
	// else
	//   Sender.DisplayText = \"其它的显示文字\";
	//@参数 脚本文本 
	//@别名 置取显示文字脚本(脚本文本)
	/*virtual*/ HRESULT set_GetDisplayTextScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_GetDisplayTextScript((BSTR)pVal); return _result; }
	//@备注 Clear，将字段的值设为空。
	// 应只在报表主对象的 FetchRecord 与 BeforePostRecord 事件响应函数中调用此方法。
	//@别名 清空()
	/*virtual*/ HRESULT Clear(){ HRESULT _result = ((IGRField*)m_ptr.p)->raw_Clear(); return _result; }
	//@备注 LoadFromFile，运行时从文件中载入二进制字段的值。
	// 注意：本方法只对二进制类型的字段有效。
	//@参数 文件名 指定载入文件的完整路径名称。
	//@别名 从文件载入(文件名)
	/*virtual*/ HRESULT LoadFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRField*)m_ptr.p)->raw_LoadFromFile((BSTR)PathFile); return _result; }
	//@备注 LoadFromBinary，运行时从内二进制对象中载入二进制字段的值。
	// 注意：本方法只对二进制类型的字段有效。
	//@参数 二进制数据对象 二进制数据对象。
	//@别名 从二进制载入(二进制数据对象)
	/*virtual*/ HRESULT LoadFromBinary(/*[in]*/ class CIGRBinaryObject* pBinaryObject);
	//@备注 LoadFromMemory，运行时从内存数据缓冲区中载入二进制字段的值。
	// 注意：本方法只对二进制类型的字段有效。
	//@参数 数据指针 指定内存数据缓冲区的地址指针。
	//@参数 数据尺寸 指定内存数据缓冲区的字节大小。
	//@别名 从内存载入(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadFromMemory(/*[in]*/ unsigned char* pBuffer, /*, [in]*/ long ByteCount){ HRESULT _result = ((IGRField*)m_ptr.p)->raw_LoadFromMemory(pBuffer, ByteCount); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRField*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRField*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 BinaryObject，应用工具，二进制数据对象，负责实现二进制数据在报表中的相关应用。
//@别名 二进制数据
class CIGRBinaryObject : public CXComObj /*IDispatch*/
{
public:
	CIGRBinaryObject(){};
	CIGRBinaryObject(IGRBinaryObject* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRBinaryObject* GetPtr(){ return ((IGRBinaryObject*)m_ptr.p); }
	//@备注 DataSize，数据字节数。
	//@别名 取数据尺寸()
	/*virtual*/ long get_DataSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBinaryObject*)m_ptr.p)->get_DataSize(&_result); return _result; }
	//@备注 AsBase64Text，数据BASE64编码文字。
	//@别名 取BASE64编码文本()
	/*virtual*/ CXText get_AsBase64Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRBinaryObject*)m_ptr.p)->get_AsBase64Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LoadFromFile，从磁盘文件或网络URL中载入二进制数据。
	//@参数 文件名 磁盘文件路径与文件名，或网络URL。
	//@别名 从文件载入(文件名)
	/*virtual*/ BOOL LoadFromFile(/*[in]*/ const wchar_t* PathFile/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRBinaryObject*)m_ptr.p)->raw_LoadFromFile((BSTR)PathFile, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadFromField，从某个记录集字段中载入二进制数据。
	//@参数 字段类 对应的字段也应该是二进制类型的。
	//@别名 从字段载入(字段类)
	/*virtual*/ BOOL LoadFromField(/*[in]*/ class CIGRField* Field/*, [out][retVal] BOOL* pSucceeded*/);
	//@备注 LoadFromBase64Text，从BASE64编码的二进制文本中载入二进制数据。
	//@参数 BASE64编码文本数据 BASE64编码文本数据。
	//@别名 从BASE64编码载入(BASE64编码文本数据)
	/*virtual*/ BOOL LoadFromBase64Text(/*[in]*/ const wchar_t* Base64Text/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRBinaryObject*)m_ptr.p)->raw_LoadFromBase64Text((BSTR)Base64Text, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadFromVariant，从一个封装的二进制变量中载入数据。
	//@参数 变量 二进制变量。
	//@别名 从变量载入(变量)
	/*virtual*/ BOOL LoadFromVariant(/*[in]*/ VARIANT Buf/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRBinaryObject*)m_ptr.p)->raw_LoadFromVariant(Buf, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToFile，将二进制数据保存到磁盘文件或网络URL。
	//@参数 文件名 磁盘文件路径与文件名，或网络URL。
	//@别名 保存到文件(文件名)
	/*virtual*/ BOOL SaveToFile(/*[in]*/ const wchar_t* PathFile/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRBinaryObject*)m_ptr.p)->raw_SaveToFile((BSTR)PathFile, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToVariant，将二进制数据保存到一个封装的变量。
	//@别名 保存到变量()
	/*virtual*/ VARIANT SaveToVariant(/*[out][retVal] VARIANT* pBuf*/){VARIANT _result; VariantInit(&_result);((IGRBinaryObject*)m_ptr.p)->raw_SaveToVariant(&_result); return _result; }
	/*virtual*/ HRESULT LoadFromMemory(/*[in]*/ unsigned char* pData, /*, [in]*/ long ByteCount){ HRESULT _result = ((IGRBinaryObject*)m_ptr.p)->raw_LoadFromMemory(pData, ByteCount); return _result; }
	//@备注 DataBuf，获取数据存储块的内存指针。
	//@别名 取数据内存指针()
	/*virtual*/ OLE_HANDLE get_DataBuf(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRBinaryObject*)m_ptr.p)->get_DataBuf(&_result); return _result; }

};
//@备注 StaticBox，文字部件框。可以与参数对象关联，显示参数对象的值
// 用来显示静态文本的部件框，一般在设计时设定要显示的文本，在输出显示时根据输出格式信息将显示文本画出来。
// 静态框可以关联某个参数对象，在这种情况下，在输出显示时部件框的显示文本为参数对象的显示文本，当一个部件框在输出时要显示多次，而其关联的参数对象的值是变化的，则此静态框在不同位置输出时的显示文字是变化的。
//@别名 静态文字框
class CIGRStaticBox : public CIGRTextBox
{
public:
	CIGRStaticBox(){};
	CIGRStaticBox(IGRStaticBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRStaticBox* GetPtr(){ return ((IGRStaticBox*)m_ptr.p); }
	//@备注 Text，显示文本。当静态框关联参数时，此属性在显示时被忽略。
	//@别名 取文本()
	/*virtual*/ CXText get_Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRStaticBox*)m_ptr.p)->get_Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Text，显示文本。当静态框关联参数时，此属性在显示时被忽略。
	//@参数 文本 
	//@别名 置文本(文本)
	/*virtual*/ HRESULT set_Text(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRStaticBox*)m_ptr.p)->put_Text((BSTR)pVal); return _result; }
	//@备注 Parameter，指定关联参数对象的名称。
	//@别名 取参数()
	/*virtual*/ CXText get_Parameter(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRStaticBox*)m_ptr.p)->get_Parameter(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Parameter，指定关联参数对象的名称。
	//@参数 参数名称 
	//@别名 置参数(参数名称)
	/*virtual*/ HRESULT set_Parameter(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRStaticBox*)m_ptr.p)->put_Parameter((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRStaticBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRStaticBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ShapeBox，用来显示各种图形的部件框，在设计时设定某种图形类别，并设定该种图形的一些参数信息。
// 图形框一般用来对报表进行一些修饰。
//@别名 图形框
class CIGRShapeBox : public CIGRControl
{
public:
	CIGRShapeBox(){};
	CIGRShapeBox(IGRShapeBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRShapeBox* GetPtr(){ return ((IGRShapeBox*)m_ptr.p); }
	//@备注 ShapeType，指定图形的类型。
	//@别名 取图形类型()
	/*virtual*/ GRShapeType get_ShapeType(/*[out][retVal] GRShapeType* pVal*/){GRShapeType _result; ((IGRShapeBox*)m_ptr.p)->get_ShapeType(&_result); return _result; }
	//@备注 ShapeType，指定图形的类型。
	//@参数 图形类型枚举值 
	//@别名 置图形类型(图形类型枚举值)
	/*virtual*/ HRESULT set_ShapeType(/*[in]*/ GRShapeType pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_ShapeType(pVal); return _result; }
	//@备注 LinePen，指定绘制线段的画笔。
	//@别名 取线画笔()
	/*virtual*/ class CIGRPen get_LinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 FillColor，封闭图形对象的内部填充色。
	//@别名 取填充颜色()
	/*virtual*/ OLE_COLOR get_FillColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRShapeBox*)m_ptr.p)->get_FillColor(&_result); return _result; }
	//@备注 FillColor，封闭图形对象的内部填充色。
	//@参数 整数值 
	//@别名 置填充颜色(整数值)
	/*virtual*/ HRESULT set_FillColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_FillColor(pVal); return _result; }
	//@备注 FillStyle，封闭图形对象的内部填充方式。
	// 
	//@返回 1、填充； 2、透明
	//@别名 取填充方式()
	/*virtual*/ GRBackStyle get_FillStyle(/*[out][retVal] GRBackStyle* pVal*/){GRBackStyle _result; ((IGRShapeBox*)m_ptr.p)->get_FillStyle(&_result); return _result; }
	//@备注 FillStyle，封闭图形对象的内部填充方式。 
	//@参数 背景模式枚举值 1、填充； 2、透明
	//@别名 置填充方式(背景模式枚举值)
	/*virtual*/ HRESULT set_FillStyle(/*[in]*/ GRBackStyle pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_FillStyle(pVal); return _result; }
	/*virtual*/ GRLineType get_LineType(/*[out][retVal] GRLineType* pVal*/){GRLineType _result; ((IGRShapeBox*)m_ptr.p)->get_LineType(&_result); return _result; }
	/*virtual*/ HRESULT set_LineType(/*[in]*/ GRLineType pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_LineType(pVal); return _result; }
	//@备注 CornerDx，圆角矩形框的圆角椭圆宽度。
	//@返回 默认值4
	//@别名 取圆角椭圆宽度()
	/*virtual*/ long get_CornerDx(/*[out][retVal] long* pVal*/){long _result=0; ((IGRShapeBox*)m_ptr.p)->get_CornerDx(&_result); return _result; }
	//@备注 CornerDx，圆角矩形框的圆角椭圆宽度。
	//@参数 整数值 默认值4
	//@别名 置圆角椭圆宽度(整数值)
	/*virtual*/ HRESULT set_CornerDx(/*[in]*/ long pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_CornerDx(pVal); return _result; }
	//@备注 CornerDy，圆角矩形框的圆角椭圆高度。
	//@返回 默认值4
	//@别名 取圆角椭圆高度()
	/*virtual*/ long get_CornerDy(/*[out][retVal] long* pVal*/){long _result=0; ((IGRShapeBox*)m_ptr.p)->get_CornerDy(&_result); return _result; }
	//@备注 CornerDy，圆角矩形框的圆角椭圆高度。
	//@参数 整数值 默认值4
	//@别名 置圆角椭圆高度(整数值)
	/*virtual*/ HRESULT set_CornerDy(/*[in]*/ long pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_CornerDy(pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRShapeBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRShapeBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 SystemVarBox，用来显示系统变量值的部件框，在设计时设定某种系统变量，在系统变量框中可以定义值的输出格式。
//@别名 系统变量框
class CIGRSystemVarBox : public CIGRTextBox
{
public:
	CIGRSystemVarBox(){};
	CIGRSystemVarBox(IGRSystemVarBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRSystemVarBox* GetPtr(){ return ((IGRSystemVarBox*)m_ptr.p); }
	//@备注 SystemVar，指定应用的系统变量类型。
	//@别名 取系统变量()
	/*virtual*/ GRSystemVarType get_SystemVar(/*[out][retVal] GRSystemVarType* pVal*/){GRSystemVarType _result; ((IGRSystemVarBox*)m_ptr.p)->get_SystemVar(&_result); return _result; }
	//@备注 SystemVar，指定应用的系统变量类型。
	//@参数 系统变量枚举值 
	//@别名 置系统变量(系统变量枚举值)
	/*virtual*/ HRESULT set_SystemVar(/*[in]*/ GRSystemVarType pVal){ HRESULT _result = ((IGRSystemVarBox*)m_ptr.p)->put_SystemVar(pVal); return _result; }
	//@备注 GroupIndex，指定系统变量对应的分组，此属性只对分组相关系统变量有效。
	//@别名 取分组序号()
	/*virtual*/ long get_GroupIndex(/*[out][retVal] long* pVal*/){long _result=0; ((IGRSystemVarBox*)m_ptr.p)->get_GroupIndex(&_result); return _result; }
	/*virtual*/ HRESULT set_GroupIndex(/*[in]*/ long pVal){ HRESULT _result = ((IGRSystemVarBox*)m_ptr.p)->put_GroupIndex(pVal); return _result; }
	//@备注 Format，系统变量值生成显示文字所应用的格式串。
	//@别名 取格式()
	/*virtual*/ CXText get_Format(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSystemVarBox*)m_ptr.p)->get_Format(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Format，系统变量值生成显示文字所应用的格式串。
	//@参数 格式文本 
	//@别名 置格式(格式文本)
	/*virtual*/ HRESULT set_Format(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSystemVarBox*)m_ptr.p)->put_Format((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRSystemVarBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRSystemVarBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 FieldBox，表示字段部件框。关联一个记录集的字段，显示字段的值。
// 用来显示字段内容的部件框，在设计时关联一个字段对象，在输出显示时根据输出格式信息将字段对象在当前记录的显示文本画出来。
// 字段框一般使用在明细网格的自由内容格、分组头、分组尾中。
//@别名 字段框
class CIGRFieldBox : public CIGRTextBox
{
public:
	CIGRFieldBox(){};
	CIGRFieldBox(IGRFieldBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFieldBox* GetPtr(){ return ((IGRFieldBox*)m_ptr.p); }
	//@备注 DataField，获取关联字段对象的名称。
	//@别名 取数据字段()
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFieldBox*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataField，设置关联字段对象的名称。
	//@参数 字段名称 
	//@别名 置数据字段(字段名称)
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFieldBox*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRFieldBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRFieldBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 SummaryBox，用来显示统计数据的部件框，在设计时设定某种统计函数，除计数（Count）函数外，其余统计函数都需要关联一个字段对象。
// 用来显示统计数据的部件框，在设计时设定某种统计函数，除计数（Count）函数外，其余统计函数都需要关联一个字段对象。
// 在统计框中可以定义统计值的输出格式。
// 统计框一般使用在分组头、分组尾中。有时为了统计全部记录的统计数据，可以将部件框使用在报表尾，报表头中。
//@别名 统计框
class CIGRSummaryBox : public CIGRTextBox
{
public:
	CIGRSummaryBox(){};
	CIGRSummaryBox(IGRSummaryBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRSummaryBox* GetPtr(){ return ((IGRSummaryBox*)m_ptr.p); }
	//@备注 SummaryFun，指定应用的统计函数。
	//@别名 取统计函数()
	/*virtual*/ GRSummaryFun get_SummaryFun(/*[out][retVal] GRSummaryFun* pVal*/){GRSummaryFun _result; ((IGRSummaryBox*)m_ptr.p)->get_SummaryFun(&_result); return _result; }
	//@备注 SummaryFun，指定应用的统计函数。
	//@参数 统计函数枚举值 
	//@别名 置统计函数(统计函数枚举值)
	/*virtual*/ HRESULT set_SummaryFun(/*[in]*/ GRSummaryFun pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_SummaryFun(pVal); return _result; }
	//@备注 DataField，获取关联的数据字段对象名称。
	//@别名 取数据字段()
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSummaryBox*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataField，设置关联的数据字段对象名称。
	//@参数 字段名称 
	//@别名 置数据字段(字段名称)
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	//@备注 Format，获取统计值生成显示文字所应用的格式串。
	//@别名 取格式()
	/*virtual*/ CXText get_Format(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSummaryBox*)m_ptr.p)->get_Format(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Format，设置统计值生成显示文字所应用的格式串。
	//@参数 格式文本 
	//@别名 置格式(格式文本)
	/*virtual*/ HRESULT set_Format(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_Format((BSTR)pVal); return _result; }
	//@备注 Value，获取在报表生成过程中，获取或设置统计部件框的当前统计值。
	//@别名 取值()
	/*virtual*/ double get_Value(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSummaryBox*)m_ptr.p)->get_Value(&_result); return _result; }
	//@备注 Value，设置在报表生成过程中，获取或设置统计部件框的当前统计值。
	//@参数 变体数据 
	//@别名 置值(变体数据)
	/*virtual*/ HRESULT set_Value(/*[in]*/ double pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_Value(pVal); return _result; }
	//@备注 RankNo，指定取统计数据中的第几名数据。
	// 本属性仅用于 MinN 与 MaxN 这两个统计函数。
	//@别名 取第几名()
	/*virtual*/ long get_RankNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRSummaryBox*)m_ptr.p)->get_RankNo(&_result); return _result; }
	//@备注 RankNo，指定取统计数据中的第几名数据。
	// 本属性仅用于 MinN 与 MaxN 这两个统计函数。
	//@参数 整数值 
	//@别名 置第几名(整数值)
	/*virtual*/ HRESULT set_RankNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_RankNo(pVal); return _result; }
	//@备注 DisplayField，指定最值统计函数要显示的字段名称。
	// 此属性只对最值统计函数有效，指定对应最值要显示的字段。
	//@别名 取显示字段()
	/*virtual*/ CXText get_DisplayField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSummaryBox*)m_ptr.p)->get_DisplayField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DisplayField，指定最值统计函数要显示的字段名称。
	// 此属性只对最值统计函数有效，指定对应最值要显示的字段。
	//@参数 文本 
	//@别名 置显示字段(文本)
	/*virtual*/ HRESULT set_DisplayField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_DisplayField((BSTR)pVal); return _result; }
	/*virtual*/ CXText get_ConditionScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSummaryBox*)m_ptr.p)->get_ConditionScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_ConditionScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_ConditionScript((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRSummaryBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRSummaryBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 PictureBox，用来显示各种类型的图像数据的部件框。
// 用来显示各种类型的图像数据的部件框，图像数据可以直接保存在报表模板文件中，也可以在运行时从磁盘文件、WEB服务器上的图像URL、二进制字段和内存中载入。
// 图像框通过图像、数据字段、图像文件与图像序号等属性来关联图像数据，开发者应该选择其中之一方式。
//@别名 图像框
class CIGRPictureBox : public CIGRControl
{
public:
	CIGRPictureBox(){};
	CIGRPictureBox(IGRPictureBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPictureBox* GetPtr(){ return ((IGRPictureBox*)m_ptr.p); }
	//@备注 Alignment，指定图像在图像框中的显示对齐方式。
	//@别名 取显示方式()
	/*virtual*/ GRPictureAlignment get_Alignment(/*[out][retVal] GRPictureAlignment* pVal*/){GRPictureAlignment _result; ((IGRPictureBox*)m_ptr.p)->get_Alignment(&_result); return _result; }
	//@备注 Alignment，指定图像在图像框中的显示对齐方式。 
	//@参数 图像显示方式枚举值 
	//@别名 置显示方式(图像显示方式枚举值)
	/*virtual*/ HRESULT set_Alignment(/*[in]*/ GRPictureAlignment pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_Alignment(pVal); return _result; }
	//@备注 SizeMode，指定图像在图像框中显示时的伸缩方式。
	// 
	//@别名 取缩放方式()
	/*virtual*/ GRPictureSizeMode get_SizeMode(/*[out][retVal] GRPictureSizeMode* pVal*/){GRPictureSizeMode _result; ((IGRPictureBox*)m_ptr.p)->get_SizeMode(&_result); return _result; }
	//@备注 SizeMode，指定图像在图像框中显示时的伸缩方式。
	//@参数 图像缩放方式枚举值 
	//@别名 置缩放方式(图像缩放方式枚举值)
	/*virtual*/ HRESULT set_SizeMode(/*[in]*/ GRPictureSizeMode pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_SizeMode(pVal); return _result; }
	//@备注 DataField，获取关联字段对象的名称。
	// 如果字段值存储的是二进制数据，图像框将把字段值作为图像数据进行加载。
	// 如果字段值存储的是整数值，图像框将把字段值解析为图像序号，将从系统图像或图像集合中加载图像。
	// 如果字段值存储的是字符串，图像框将把字段值解析为图像文件名称，将从对应文件中加载图像，文件既可以是本地文件路径名，也可以是网络URL。
	//@别名 取数据字段()
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPictureBox*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataField，设置关联字段对象的名称。
	// 如果字段值存储的是二进制数据，图像框将把字段值作为图像数据进行加载。
	// 如果字段值存储的是整数值，图像框将把字段值解析为图像序号，将从系统图像或图像集合中加载图像。
	// 如果字段值存储的是字符串，图像框将把字段值解析为图像文件名称，将从对应文件中加载图像，文件既可以是本地文件路径名，也可以是网络URL。
	//@参数 字段名称 
	//@别名 置数据字段(字段名称)
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	//@备注 ImageIndex，指定图像框关联图像集合中某个图像的序号。
	// 图像的序号从1开始，0表示不关联。
	// Grid++Report在报表引擎中定义了一些系统内建图像，其图像序号通过枚举GRSystemImage的枚举项来指定，也可以通过设定本属性为某个枚举项的值来关联一个系统图像。
	//@别名 取图像序号()
	/*virtual*/ long get_ImageIndex(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPictureBox*)m_ptr.p)->get_ImageIndex(&_result); return _result; }
	//@备注 ImageIndex，指定图像框关联图像集合中某个图像的序号。
	// 图像的序号从1开始，0表示不关联。
	// Grid++Report在报表引擎中定义了一些系统内建图像，其图像序号通过枚举GRSystemImage的枚举项来指定，也可以通过设定本属性为某个枚举项的值来关联一个系统图像。
	//@参数 序号 图像的序号从1开始，0表示不关联。
	//@别名 置图像序号(序号)
	/*virtual*/ HRESULT set_ImageIndex(/*[in]*/ long pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_ImageIndex(pVal); return _result; }
	//@备注 ImageFile，指定图像框关联的图像路径文件名，既可以使本地文件名，也可以WEB服务器上的URL。
	//@别名 取图像文件()
	/*virtual*/ CXText get_ImageFile(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPictureBox*)m_ptr.p)->get_ImageFile(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ImageFile，指定图像框关联的图像路径文件名。
	//@参数 图像文件 既可以使本地文件名，也可以WEB服务器上的URL。
	//@别名 置图像文件(图像文件)
	/*virtual*/ HRESULT set_ImageFile(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_ImageFile((BSTR)pVal); return _result; }
	//@备注 TransparentMode，指定图像的透明显示方式。
	//@别名 取透明模式()
	/*virtual*/ GRPictureTransparentMode get_TransparentMode(/*[out][retVal] GRPictureTransparentMode* pVal*/){GRPictureTransparentMode _result; ((IGRPictureBox*)m_ptr.p)->get_TransparentMode(&_result); return _result; }
	//@备注 TransparentMode，指定图像的透明显示方式。
	//@参数 图像透明模式枚举值 
	//@别名 置透明模式(图像透明模式枚举值)
	/*virtual*/ HRESULT set_TransparentMode(/*[in]*/ GRPictureTransparentMode pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_TransparentMode(pVal); return _result; }
	//@备注 RotateMode，指定图像显示时的旋转模式。
	//@别名 取旋转模式()
	/*virtual*/ GRPictureRotateMode get_RotateMode(/*[out][retVal] GRPictureRotateMode* pVal*/){GRPictureRotateMode _result; ((IGRPictureBox*)m_ptr.p)->get_RotateMode(&_result); return _result; }
	//@备注 RotateMode，指定图像显示时的旋转模式。 
	//@参数 图像旋转模式枚举值 
	//@别名 置旋转模式(图像旋转模式枚举值)
	/*virtual*/ HRESULT set_RotateMode(/*[in]*/ GRPictureRotateMode pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_RotateMode(pVal); return _result; }
	//@备注 Picture，获取图像对象。
	// 
	//@别名 取图像()
	/*virtual*/ class CIGRPicture get_Picture(/*[out][retVal] class CIGRPicture** pVal*/);
	//@备注 Picture，设置图像对象。
	//@参数 报表图片对象 
	//@别名 置图像(报表图片对象)
	/*virtual*/ HRESULT set_Picture(/*[in]*/ class CIGRPicture* pVal);
	//@备注 LoadFromFile，运行时从磁盘文件或网络URL地址中载入图像文件。
	// 载入图像文件的时机:
	// 1. 如果图像框位于报表头、报表尾、页眉与页脚中，应在报表主对象的 Initialize 事件响应函数中执行载入文件。
	// 2. 如果图像框位于明细网格的内容格中，应在报表主对象的 ProcessRecord 事件响应函数中执行载入文件。
	// 3. 如果图像框位于明细网格的分组头或分组尾中，应在报表主对象的 GroupBegin 或 GroupEnd 事件响应函数中执行载入文件。
	//@参数 文件名 载入图像文件的路径与文件名，或URL。 
	//@别名 从文件载入(文件名)
	/*virtual*/ HRESULT LoadFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->raw_LoadFromFile((BSTR)PathFile); return _result; }
	//@备注 LoadFromBinary，从二进制对象中载入图像数据。
	//@参数 二进制数据对象 拥有图像数据的二进制对象。
	//@别名 从二进制载入(二进制数据对象)
	/*virtual*/ HRESULT LoadFromBinary(/*[in]*/ class CIGRBinaryObject* pBinaryObject);
	//@备注 LoadFromMemory，运行时从内存中载入图像数据。
	//@参数 数据指针 指定内存数据缓冲区的地址指针。
	//@参数 数据尺寸 指定内存数据缓冲区的字节大小。
	//@别名 从内存载入(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadFromMemory(/*[in]*/ unsigned char* pBuffer, /*, [in]*/ long BytesCount){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->raw_LoadFromMemory(pBuffer, BytesCount); return _result; }
	//@备注 LoadBmpPicture，从BMP格式图像对象中载入图像数据。
	// VC资源中的BMP图像应该调用本方法载入到报表中。
	//@参数 图片对象 图像对象。
	//@别名 从Bmp图片载入(图片对象)
	/*virtual*/ HRESULT LoadBmpPicture(/*[in]*/ IPicture* newVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->raw_LoadBmpPicture(newVal); return _result; }
	//@备注 AttachSystemImage，关联一个系统图像到本图像框,从而在本图像框中显示一个系统图像。
	//@参数 系统图像枚举值 
	//@别名 关联系统图像(系统图像枚举值)
	/*virtual*/ HRESULT AttachSystemImage(/*[in]*/ GRSystemImage SystemImage){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->raw_AttachSystemImage(SystemImage); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRPictureBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRPictureBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Picture，基础对象 全局使用对象(可多次创建变相清空内容值 或 创建多个对象)。
//@别名 报表图片
class CIGRPicture : public CXComObj /*IDispatch*/
{
public:
	CIGRPicture(){};
	CIGRPicture(IGRPicture* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPicture* GetPtr(){ return ((IGRPicture*)m_ptr.p); }
	//@备注 Type，获取当前加载的图像的类型。
	//@别名 取类型()
	/*virtual*/ GRPictureType get_Type(/*[out][retVal] GRPictureType* pVal*/){GRPictureType _result; ((IGRPicture*)m_ptr.p)->get_Type(&_result); return _result; }
	//@备注 Width，获取当前加载的图像的宽度像素值。
	//@别名 取宽度()
	/*virtual*/ long get_Width(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPicture*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Height，获取当前加载的图像的高度像素值。
	//@别名 取高度()
	/*virtual*/ long get_Height(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPicture*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 OlePicture，获取或设置图像对象关联的 OLE 图像对象。
	//@别名 取图片()
	/*virtual*/ IPicturePtr get_OlePicture(/*[out][retVal] IPicture** pVal*/){IPicture* _result; ((IGRPicture*)m_ptr.p)->get_OlePicture(&_result); return _result; }
	//@备注 OlePicture，获取或设置图像对象关联的 OLE 图像对象。
	//@参数 图片对象 
	//@别名 置图片(图片对象)
	/*virtual*/ HRESULT set_OlePicture(/*[in]*/ IPicture* pVal){ HRESULT _result = ((IGRPicture*)m_ptr.p)->put_OlePicture(pVal); return _result; }
	/*virtual*/ HRESULT Render(/*[in]*/ OLE_HANDLE hdc, /*, [in]*/ long Left, /*, [in]*/ long Top, /*, [in]*/ long Width, /*, [in]*/ long Height, /*, [in]*/ GRPictureAlignment PictureAlignment, /*, [in]*/ GRPictureSizeMode PictureSizeMode, /*, [in]*/ unsigned long BackColor, /*, [in]*/ BOOL FillBack, /*, [in]*/ GRPictureTransparentMode Transparent, /*, [in]*/ GRPictureRotateMode RotateMode){ HRESULT _result = ((IGRPicture*)m_ptr.p)->raw_Render(hdc, Left, Top, Width, Height, PictureAlignment, PictureSizeMode, BackColor, FillBack? VARIANT_TRUE : VARIANT_FALSE, Transparent, RotateMode); return _result; }
	//@备注 LoadFromFile，从指定磁盘本地文件或网络URL中载入图像数据。
	//@参数 文件名 图像文件路径名或图像数据URL。
	//@别名 从文件载入图片(文件名)
	/*virtual*/ BOOL LoadFromFile(/*[in]*/ const wchar_t* PathFile/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPicture*)m_ptr.p)->raw_LoadFromFile((BSTR)PathFile, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadFromBinary，从二进制数据对象中载入图像数据。
	//@参数 二进制数据对象 拥有图像数据的二进制对象。
	//@别名 从二进制载入图片(二进制数据对象)
	/*virtual*/ BOOL LoadFromBinary(/*[in]*/ class CIGRBinaryObject* pBinaryObject/*, [out][retVal] BOOL* pSucceeded*/);
	//@备注 SaveToFile，将图像数据保存到磁盘本地文件或发送到网络URL。
	//@参数 文件名 
	//@别名 保存到文件(文件名)
	/*virtual*/ BOOL SaveToFile(/*[in]*/ const wchar_t* PathFile/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPicture*)m_ptr.p)->raw_SaveToFile((BSTR)PathFile, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadFromMemory，从内存中载入图像数据。
	//@参数 数据指针 pBuffer，数据缓冲区内存地址。
	//@参数 数据尺寸 BytesCount，数据缓冲区的字节数。
	//@别名 从内存载入图片(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadFromMemory(/*[in]*/ unsigned char* pData, /*, [in]*/ long ByteCount){ HRESULT _result = ((IGRPicture*)m_ptr.p)->raw_LoadFromMemory(pData, ByteCount); return _result; }
	/*virtual*/ HRESULT _GetDataBuffer(/*[out]*/ OLE_HANDLE* ppData, /*, [out]*/ long* pBytesCount){ HRESULT _result = ((IGRPicture*)m_ptr.p)->raw__GetDataBuffer(ppData, pBytesCount); return _result; }
	/*virtual*/ BOOL LoadFromField(/*[in]*/ const wchar_t* DataField/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPicture*)m_ptr.p)->raw_LoadFromField((BSTR)DataField, &_result); return (VARIANT_TRUE==_result); }

};
//@备注 RichTextBox，表示RTF格式文本部件框。
// 用来定义RTF格式文本部件框，RTF格式文本数据可以直接保存在报表模板文件中，也可以在运行时从磁盘文件、二进制字段和内存中载入。
//@别名 RTF文字框
class CIGRRichTextBox : public CIGRControl
{
public:
	CIGRRichTextBox(){};
	CIGRRichTextBox(IGRRichTextBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRRichTextBox* GetPtr(){ return ((IGRRichTextBox*)m_ptr.p); }
	//@备注 CanGrow，指示部件框高度在运行时是否可以伸展标志。
	// 如果本属性为真，报表运行时部件框的设计时高度不足以完整显示出拥有的RTF文本，则部件框的高足自动伸展到刚好能完整显示出拥有的RTF文本。
	//@别名 取可伸展()
	/*virtual*/ BOOL get_CanGrow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRichTextBox*)m_ptr.p)->get_CanGrow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanGrow，指示部件框高度在运行时是否可以伸展标志。
	// 如果本属性为真，报表运行时部件框的设计时高度不足以完整显示出拥有的RTF文本，则部件框的高足自动伸展到刚好能完整显示出拥有的RTF文本。
	//@参数 逻辑值 
	//@别名 置可伸展(逻辑值)
	/*virtual*/ HRESULT set_CanGrow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->put_CanGrow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CanShrink，指示部件框的高度在运行时是否可以收缩标志。
	// 如果本属性为真，报表运行时部件框的设计时高度大于完整显示出拥有的RTF文本所需要的高度，则部件框的高度自动收缩到刚好能完整显示出拥有的RTF文本。
	//@别名 取可收缩()
	/*virtual*/ BOOL get_CanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRRichTextBox*)m_ptr.p)->get_CanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanShrink，指示部件框的高度在运行时是否可以收缩标志。
	// 如果本属性为真，报表运行时部件框的设计时高度大于完整显示出拥有的RTF文本所需要的高度，则部件框的高度自动收缩到刚好能完整显示出拥有的RTF文本。
	//@参数 逻辑值 
	//@别名 置可收缩(逻辑值)
	/*virtual*/ HRESULT set_CanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->put_CanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DataField，获取关联的数据字段对象名称。
	//@别名 取数据字段()
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRichTextBox*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataField，设置关联的数据字段对象名称。
	//@参数 字段名称 
	//@别名 置数据字段(字段名称)
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	//@备注 RTF，表示显示的RTF文本数据。
	//@返回 RTF文本数据
	//@别名 取RTF文本()
	/*virtual*/ CXText get_RTF(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRRichTextBox*)m_ptr.p)->get_RTF(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 RTF，表示显示的RTF文本数据。
	//@参数 RTF文本数据 
	//@别名 置RTF文本(RTF文本数据)
	/*virtual*/ HRESULT set_RTF(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->put_RTF((BSTR)pVal); return _result; }
	//@备注 LoadFromFile，运行时从磁盘文件中载入RTF格式文件。
	// 载入RTF文件的时机:
	// 1. 如果RTF文本框位于报表头、报表尾、页眉与页脚中，应在报表主对象的 Initialize 事件响应函数中执行载入文件。
	// 2. 如果RTF文本框位于明细网格的内容格中，应在报表主对象的 ProcessRecord 事件响应函数中执行载入文件。
	// 3. 如果RTF文本框位于明细网格的分组头或分组尾中，应在报表主对象的 GroupBegin 或 GroupEnd 事件响应函数中执行载入文件。
	//@参数 文件名 载入RTF文件的路径与文件名。
	//@别名 从文件载入(文件名)
	/*virtual*/ HRESULT LoadFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->raw_LoadFromFile((BSTR)PathFile); return _result; }
	//@备注 LoadFromMemory，运行时从内存中载入RTF格式文本数据。
	//@参数 数据指针 指定内存数据缓冲区的地址指针。
	//@参数 数据尺寸 指定内存数据缓冲区的字节大小。
	//@别名 从内存载入(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadFromMemory(/*[in]*/ unsigned char* pBuffer, /*, [in]*/ long BytesCount){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->raw_LoadFromMemory(pBuffer, BytesCount); return _result; }
	/*virtual*/ HRESULT _Prepare(){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->raw__Prepare(); return _result; }
	/*virtual*/ HRESULT _FetchExportText(/*[out]*/ const wchar_t** pExportText){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->raw__FetchExportText((BSTR*)pExportText); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRRichTextBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRRichTextBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 MemoBox，最常用的文字部件框。可以在文字中包含数据域，数据域在运行时被替换为对应的对象或函数的值。另域可以进行算术四则运算。
// 可以用来显示静态文本的部件框，一般在设计时设定要显示的文本，在输出显示时依原样输出。
// 除了显示静态框文字之外，MemoBox 更可以显示多种多样的同态内容，通过在文字中定义数据域，数据域在运行时被替换为对应的对象或函数的值。
// 综合文字框MemoBox 的数据域可以关联字段、参数、文字类型部件框、统计函数与系统变量。
// 多个值为数字类型的数据域可以进行数字四则运算。数据域可以设定其显示的格式化字符串，以便得到想要的显示文字。
// 综合文字框可以显示静态文本，关联动态数据域，动态数据域包括：字段、参数、文字部件框、统计函数与系统变量。
// 综合文字框可以定义四则运算表达式，在运行时表达式被替换为运算结果。
// 综合文字框是 Grid++Report 中最常用的部件框，它除了可以实现其它文字框的功能外，还可以组合静态文字与动态数据域，在运行时输出动态变化的文本，另外数据域还可以使用在四则运算表达式中，在运行时输出运算结果。
// 【数学四则运算表达式】
// 表达式由数据域、加减乘除运算符号与常数数字组合而成，组合关系必须符合数学四则运算规则。仅包含一个且只包含一个数据域的表达式在运行时不用进行数学运算，仅仅直接显示这个数据域的显示文字。
// 【各个数学函数简介】
//  round45(number,decemails)  //四舍五入,number:四舍五入的数值,decemails:保留小数位数
//  round465(number,decemails)  //四舍六入五成双,number:四舍六入五成双的数值,decemails:保留小数位数
//  abs(number)  //返回数字的绝对值
//  acos(number)  //参数范围：–1到1之间
//  asin(number)  //参数范围：–1到1之间
//  atan(number)  //返回数字的反正切值
//  atan2(number)  //返回由 X 轴到 (y,x) 点的角度（以弧度为单位）。
//  tan(number)  //返回数字的正切值
//  sin(number)  //返回数字的正弦值
//  cos(number)  //返回数的余弦值
//  exp(number)  //返回 e（自然对数的底）的幂 
//  log(number)  //返回数字的自然对数
//  ceil(number)  //向上取整
//  floor(number)  //向下取整
//  maxArray([number1[,number2[...[,numberN]]]])  //在一组数值中求最大值，参数为1..n个
//  minArray([number1[,number2[...[,numberN]]]])  //在一组数值中求最小值，参数为1..n个
//  pow(base,exponent)  //计算base的exponent次方
//  round(number)  //就近取整，四舍五入取整
//  sqrt(number)  //求平方根
//@别名 综合文字框
class CIGRMemoBox : public CIGRTextBox
{
public:
	CIGRMemoBox(){};
	CIGRMemoBox(IGRMemoBox* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRMemoBox* GetPtr(){ return ((IGRMemoBox*)m_ptr.p); }
	//@备注 Text，显示文本，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"{}\"括起来，则将用此名称显示对应参数的文字。
	// 【关于数据域的使用】
	// 1、拼接数据域显示文字
	// 当一个表达式只包含且只包含一个数据域时，此表达式在运行时将替换为此域的显示文字。如果要拼接多个数据域的显示文字，只需将各个数据域插入在不同的表达式中。
	// 如：[#Field1] [#StaticBox1]表示拼接Field1与StaticBox1 的显示文字。如：abc[#Field1] def[#StaticBox1]表示将Field1与StaticBox1 的显示文字插入到整个文本中的不同位置。
	// 2、关于引用数据域的说明
	// 在综合文字框中可以引用的数据域类型有字段、参数、文字部件框、统计函数与系统变量。如果数据域名称不满足“所有字符必须为英文字母、数字、汉字与连字符，且首字符不为数
	// 字。”的条件，则必须用中括号([])将数据域括起来。如果数据域名称中包含有中括号([])，数据域在运行有可能不能正确解析，此时应该调整对应数据域的名称。
	//@别名 取文本()
	/*virtual*/ CXText get_Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRMemoBox*)m_ptr.p)->get_Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Text，显示文本，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"{}\"括起来，则将用此名称显示对应参数的文字。
	// 【关于数据域的使用】
	// 1、拼接数据域显示文字
	// 当一个表达式只包含且只包含一个数据域时，此表达式在运行时将替换为此域的显示文字。如果要拼接多个数据域的显示文字，只需将各个数据域插入在不同的表达式中。
	// 如：[#Field1] [#StaticBox1]表示拼接Field1与StaticBox1 的显示文字。如：abc[#Field1] def[#StaticBox1]表示将Field1与StaticBox1 的显示文字插入到整个文本中的不同位置。
	// 2、关于引用数据域的说明
	// 在综合文字框中可以引用的数据域类型有字段、参数、文字部件框、统计函数与系统变量。如果数据域名称不满足“所有字符必须为英文字母、数字、汉字与连字符，且首字符不为数
	// 字。”的条件，则必须用中括号([])将数据域括起来。如果数据域名称中包含有中括号([])，数据域在运行有可能不能正确解析，此时应该调整对应数据域的名称。
	//@参数 文本 表达式文本
	//@别名 置文本(文本)
	/*virtual*/ HRESULT set_Text(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_Text((BSTR)pVal); return _result; }
	//@备注 FlowTo，指定超出本部件框区域的文字要跟随显示的综合文本框的名称。
	// 如果设定了本属性，当本综合文本框不能完整显示出内容文字时，没有显示的文字将显示到本属性指定的综合文本框中。
	//@返回 综合文本框名称。
	//@别名 取超出显示至()
	/*virtual*/ CXText get_FlowTo(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRMemoBox*)m_ptr.p)->get_FlowTo(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 FlowTo，指定超出本部件框区域的文字要跟随显示的综合文本框的名称。
	// 如果设定了本属性，当本综合文本框不能完整显示出内容文字时，没有显示的文字将显示到本属性指定的综合文本框中。
	//@参数 名称 指定的综合文本框名称。
	//@别名 置超出显示至(名称)
	/*virtual*/ HRESULT set_FlowTo(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_FlowTo((BSTR)pVal); return _result; }
	//@备注 AsFloat，在运行时获取表达式计算出来的数字值。
	// 只有当综合文本框的文本属性为纯表达式时，且只能在报表运行中才能获取本属性值。
	//@别名 取浮点数值()
	/*virtual*/ double get_AsFloat(/*[out][retVal] double* pVal*/){double _result=0; ((IGRMemoBox*)m_ptr.p)->get_AsFloat(&_result); return _result; }
	/*virtual*/ GRTextOrientation get_TextOrientation(/*[out][retVal] GRTextOrientation* pVal*/){GRTextOrientation _result; ((IGRMemoBox*)m_ptr.p)->get_TextOrientation(&_result); return _result; }
	/*virtual*/ HRESULT set_TextOrientation(/*[in]*/ GRTextOrientation pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_TextOrientation(pVal); return _result; }
	/*virtual*/ double get_TextAngle(/*[out][retVal] double* pVal*/){double _result=0; ((IGRMemoBox*)m_ptr.p)->get_TextAngle(&_result); return _result; }
	/*virtual*/ HRESULT set_TextAngle(/*[in]*/ double pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_TextAngle(pVal); return _result; }
	/*virtual*/ double get_CharacterSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRMemoBox*)m_ptr.p)->get_CharacterSpacing(&_result); return _result; }
	/*virtual*/ HRESULT set_CharacterSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_CharacterSpacing(pVal); return _result; }
	/*virtual*/ double get_LineSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGRMemoBox*)m_ptr.p)->get_LineSpacing(&_result); return _result; }
	/*virtual*/ HRESULT set_LineSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_LineSpacing(pVal); return _result; }
	/*virtual*/ BOOL get_HtmlTags(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRMemoBox*)m_ptr.p)->get_HtmlTags(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_HtmlTags(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_HtmlTags(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRMemoBox*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRMemoBox*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 SubReport，表示子报表部件框，通过关联另一个报表对象，在此报表中显示另外一个报表。
// 子报表受以下规则限制：1、子报表所在的节不允许重复打印；2、子报表本身的页眉与页脚在生成时被忽略掉。
// 子报表不能查询显示的说明：
// 包含有子报表的报表不适合用查询显示器控件(DisplayViewer)显示，如果明细网格中包含有子报表，这些子报表都不能在查询显示器控件中显示，所以含有子报表的报表直接用打印显示控件(PrintViewer)显示，即按打印预览方式显示。
// 如果实在需要查询显示方式显示这样的数据，建议不用子报表，而是用多个查询显示器控件分别显示数据的不同部分，每个明细表格对应一个查询显示器控件。
//@别名 子报表框
class CIGRSubReport : public CIGRControl
{
public:
	CIGRSubReport(){};
	CIGRSubReport(IGRSubReport* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRSubReport* GetPtr(){ return ((IGRSubReport*)m_ptr.p); }
	//@备注 Report，获取关联的报表对象的接口引用。
	//@别名 取关联报表()
	/*virtual*/ class CIGridppReport get_Report(/*[out][retVal] class CIGridppReport** pVal*/);
	//@备注 Report，设置关联的报表对象。
	//@参数 报表对象 
	//@别名 置关联报表(报表对象)
	/*virtual*/ HRESULT set_Report(/*[in]*/ class CIGridppReport* pVal);
	//@备注 CanGrow，指示子报表的高度在运行时是否可以伸展的标志。
	//@别名 取可伸展()
	/*virtual*/ BOOL get_CanGrow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_CanGrow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanGrow，指示子报表的高度在运行时是否可以伸展的标志。
	//@参数 逻辑值 
	//@别名 置可伸展(逻辑值)
	/*virtual*/ HRESULT set_CanGrow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_CanGrow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CanShrink，指示子报表的高度在运行时是否可以收缩的标志。
	//@别名 取可收缩()
	/*virtual*/ BOOL get_CanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_CanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanShrink，指示子报表的高度在运行时是否可以收缩的标志。
	//@参数 逻辑值 
	//@别名 置可收缩(逻辑值)
	/*virtual*/ HRESULT set_CanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_CanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_SpanToNewPage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_SpanToNewPage(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_SpanToNewPage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_SpanToNewPage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ParentPageSettings，指定子报表是否应用主表的页面设置参数。
	// 当此属性为FALSE，且子报表是独立产生的子报表时，子报表将应用其自身的页面设置参数。
	// 其它情况下子报表将应用主表的页面设置参数，自己的页面设置参数将不会被使用。页面设置参数包括纸张的类型、方向与页边距。
	// 当子报表是报表头或报表尾中的唯一部件框，且子报表的本属性值为“FALSE”，这样的子报表就是独立产生的子报表。
	//@别名 取主表页面设置()
	/*virtual*/ BOOL get_ParentPageSettings(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_ParentPageSettings(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ParentPageSettings，指定子报表是否应用主表的页面设置参数。
	// 当此属性为FALSE，且子报表是独立产生的子报表时，子报表将应用其自身的页面设置参数。
	// 其它情况下子报表将应用主表的页面设置参数，自己的页面设置参数将不会被使用。页面设置参数包括纸张的类型、方向与页边距。
	// 当子报表是报表头或报表尾中的唯一部件框，且子报表的本属性值为“FALSE”，这样的子报表就是独立产生的子报表。
	//@参数 逻辑值 
	//@别名 置主表页面设置(逻辑值)
	/*virtual*/ HRESULT set_ParentPageSettings(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_ParentPageSettings(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResetPageNumber，指定子报表产生时是否重新开始计数页号与页数。
	//@别名 取重置页号()
	/*virtual*/ BOOL get_ResetPageNumber(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_ResetPageNumber(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ResetPageNumber，指定子报表产生时是否重新开始计数页号与页数。
	//@参数 逻辑值 
	//@别名 置重置页号(逻辑值)
	/*virtual*/ HRESULT set_ResetPageNumber(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_ResetPageNumber(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ToNewExcelSheet，在报表导出Excel时，是否将此子报表导出到一个新的工作表。
	// 此属性仅当子报表为独立子报表时才有效，即子报表为报表头尾中的唯一部件框，且其“主表页面设置”属性为“否”。
	//@别名 取导出到新工作表()
	/*virtual*/ BOOL get_ToNewExcelSheet(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_ToNewExcelSheet(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ToNewExcelSheet，在报表导出Excel时，是否将此子报表导出到一个新的工作表。
	// 此属性仅当子报表为独立子报表时才有效，即子报表为报表头尾中的唯一部件框，且其“主表页面设置”属性为“否”。
	//@参数 逻辑值 
	//@别名 置导出到新工作表(逻辑值)
	/*virtual*/ HRESULT set_ToNewExcelSheet(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_ToNewExcelSheet(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 HideOnRecordsetEmpty，指示具有明细网格的子报表当其没有明细数据时是否隐藏整个子报表。
	//@别名 取无数据隐藏()
	/*virtual*/ BOOL get_HideOnRecordsetEmpty(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRSubReport*)m_ptr.p)->get_HideOnRecordsetEmpty(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HideOnRecordsetEmpty，指示具有明细网格的子报表当其没有明细数据时是否隐藏整个子报表。
	//@参数 逻辑值 
	//@别名 置无数据隐藏(逻辑值)
	/*virtual*/ HRESULT set_HideOnRecordsetEmpty(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_HideOnRecordsetEmpty(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 RelationFields，指定位于明细网格的子报表其筛选当前批次数据的关系字段。
	// 如果子报表定义在明细网格的内容行或分组节中，且希望报表数据一次性提供，则必须要建立主报表与子报表之间的主从关系，数据包中
	// 肯定包含有主报表的明细数据与子报表的明细数据。
	// 表中表的子报表在生成过程中会多次产生，每次产生都需要对应批次的数据，所以需要合理的筛选方法将一次性提供的数据分批筛选出来。
	// 设置子报表的“主从关系字段”属性即可建立子报表与主报表的主从关系，必须保证在子报表与主报表的明细记录集中都定义有子报表的
	// “主从关系字段”属性值对应的同名字段。报表在运行时，将根据主报表的主从关系字段的当前值去筛选子表明细记录的数据，只有与主
	// 报表的主从关系字段的当前值相等的数据才会作为子报表的当前数据来应用。
	// 更多详细说明请参考帮助文档中的“报表插件(WEB报表)->WEB报表数据->子报表 XML 数据”部分。
	//@别名 取主从关系字段()
	/*virtual*/ CXText get_RelationFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSubReport*)m_ptr.p)->get_RelationFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 RelationFields，指定位于明细网格的子报表其筛选当前批次数据的关系字段。
	// 如果子报表定义在明细网格的内容行或分组节中，且希望报表数据一次性提供，则必须要建立主报表与子报表之间的主从关系，数据包中
	// 肯定包含有主报表的明细数据与子报表的明细数据。
	// 表中表的子报表在生成过程中会多次产生，每次产生都需要对应批次的数据，所以需要合理的筛选方法将一次性提供的数据分批筛选出来。
	// 设置子报表的“主从关系字段”属性即可建立子报表与主报表的主从关系，必须保证在子报表与主报表的明细记录集中都定义有子报表的
	// “主从关系字段”属性值对应的同名字段。报表在运行时，将根据主报表的主从关系字段的当前值去筛选子表明细记录的数据，只有与主
	// 报表的主从关系字段的当前值相等的数据才会作为子报表的当前数据来应用。
	// 更多详细说明请参考帮助文档中的“报表插件(WEB报表)->WEB报表数据->子报表 XML 数据”部分。
	//@参数 关系字段名 
	//@别名 置主从关系字段(关系字段名)
	/*virtual*/ HRESULT set_RelationFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_RelationFields((BSTR)pVal); return _result; }
	//@备注 ReportFile，指定关联的报表模板文件名称。
	//@别名 取报表模板文件()
	/*virtual*/ CXText get_ReportFile(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSubReport*)m_ptr.p)->get_ReportFile(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ReportFile，指定关联的报表模板文件名称。
	//@参数 模板文件名称 
	//@别名 置报表模板文件(模板文件名称)
	/*virtual*/ HRESULT set_ReportFile(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_ReportFile((BSTR)pVal); return _result; }
	/*virtual*/ HRESULT _ResetSaveFlag(){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->raw__ResetSaveFlag(); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRSubReport*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRSubReport*)m_ptr.p)->put_Lock(pVal); return _result; }

};

//@分组{ 主对象

//@备注 Report，表示报表的主对象。
// 一个不可视的组件对象，定义报表的模板数据，在生成报表时存贮报表记录数据，对数据进行加工处理，生成打印页面，输出打印页面到打印机。
// 报表主对象是整个产品中最基础的构成部分，通过报表主对象可以访问报表中的各个子对象。
// 其他报表元素对象都是其子孙对象，对其它对象的访问与使用都是以此对象作为进入起点。
// 报表主对象Report是一个COM自动化（COM Automation）对象的接口定义，是Grid++Report组件对象模型的最外层对象。
// 报表主对象是所有其它报元素对象的直接或间接拥有者，直接拥有的报表元素对象有：明细网格，报表节集合、参数集合、打印机对象。
// 另也包括报表有关的公共信息，如设计行为属性、计量单位、整个报表的缺省字体等。
//@别名 报表
class CIGridppReport : public CIGRObject
{
public:
	CIGridppReport(){};
	CIGridppReport(IGridppReport* p){ m_ptr = p; }
	//@备注 创建报表实例()
	//@别名 创建()
	BOOL Create();
	//@别名 取COM对象指针()
	IGridppReport* GetPtr(){ return ((IGridppReport*)m_ptr.p); }

	//@别名 绑定事件()
	BOOL BindEvent(CIGridppReportEvents* pEvent);

	//@备注 Version，指示Grid++Report的当前运行版本。
	//@别名 取版本号()
	/*virtual*/ CXText get_Version(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_Version(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Language，Grid++根据Windows系统的区域设置自动选择界面语言，也可以用程序代码设置改变Grid++的界面显示语言。
	//@别名 取语言()
	/*virtual*/ long get_Language(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_Language(&_result); return _result; }
	//@备注 Language，Grid++根据Windows系统的区域设置自动选择界面语言，也可以用程序代码设置改变Grid++的界面显示语言。
	//@参数 语言类型枚举值 
	//@别名 置语言(语言类型枚举值)
	/*virtual*/ HRESULT set_Language(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Language(pVal); return _result; }
	//@备注 Font，获取报表的字体对象。
	//@别名 取字体()
	/*virtual*/ class CIGRFont get_Font(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 BackColor，报表主对象或子对象的缺省背景色。设置背景色后，新增的子对象将采用该背景色作为默认背景色。
	//@别名 取背景色()
	/*virtual*/ OLE_COLOR get_BackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGridppReport*)m_ptr.p)->get_BackColor(&_result); return _result; }
	//@备注 BackColor，报表主对象或子对象的缺省背景色。设置背景色后，新增的子对象将采用该背景色作为默认背景色。
	//@参数 颜色值 
	//@别名 置背景色(颜色值)
	/*virtual*/ HRESULT set_BackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_BackColor(pVal); return _result; }
	//@备注 DetailGrid，获取明细网格对象的接口引用。
	//@别名 取明细网格()
	/*virtual*/ class CIGRDetailGrid get_DetailGrid(/*[out][retVal] class CIGRDetailGrid** pVal*/);
	//@备注 PageHeader，获取报表的页眉。
	//@别名 取页眉()
	/*virtual*/ class CIGRPageHeader get_PageHeader(/*[out][retVal] class CIGRPageHeader** pVal*/);
	//@备注 PageFooter，获取报表的页脚。
	//@别名 取页脚()
	/*virtual*/ class CIGRPageFooter get_PageFooter(/*[out][retVal] class CIGRPageFooter** pVal*/);
	//@备注 Parameters，获取参数集合对象。
	//@别名 取参数集合()
	/*virtual*/ class CIGRParameters get_Parameters(/*[out][retVal] class CIGRParameters** pVal*/);
	//@备注 ReportHeaders，指定报表中的报表头集合。
	//@别名 取报表头集合()
	/*virtual*/ class CIGRReportHeaders get_ReportHeaders(/*[out][retVal] class CIGRReportHeaders** pVal*/);
	//@备注 ReportFooters，获取报表尾集合对象。
	//@别名 取报表尾集合()
	/*virtual*/ class CIGRReportFooters get_ReportFooters(/*[out][retVal] class CIGRReportFooters** pVal*/);
	//@备注 FloatControls，指定报表中的浮动部件框集合。
	//@别名 取浮动部件框集合()
	/*virtual*/ class CIGRControls get_FloatControls(/*[out][retVal] class CIGRControls** pVal*/);
	//@备注 ImageList，获取报表对象中图像集合对象的接口引用。
	//@别名 取图像集合()
	/*virtual*/ class CIGRImageList get_ImageList(/*[out][retVal] class CIGRImageList** pVal*/);
	//@备注 Printer，获取打印机对象的接口引用。
	//@别名 取打印机()
	/*virtual*/ class CIGRPrinter get_Printer(/*[out][retVal] class CIGRPrinter** pVal*/);
	//@备注 ParentReport，指定子报表对象的主报表引用。
	// 指定子报表对象的主报表引用，如果是非子报表对象，本属性值为空(NULL)。
	//@返回 返回父报表
	//@别名 取父报表()
	/*virtual*/ class CIGridppReport get_ParentReport(/*[out][retVal] class CIGridppReport** pVal*/);
	//@备注 FiringReport，获取正在触发报表事件的报表对象。此属性只能在报表事件响应函数中获取才能得到有效值，用于指定是哪个报表对象触发调用了本事件函数。
	// 此属性只能在报表事件响应函数中获取才能得到有效值，用于指定是哪个报表对象触发调用了本事件函数。
	// 当一个事件函数被多个报表对象关联时，获取本属性可以知道是哪个报表对象触发了当前事件。
	// 从任意一个报表对象获取本属性值都可以，在同一时刻，从不同报表对象获取的本属性值都是相同的。
	//@别名 取触发事件报表()
	/*virtual*/ class CIGridppReport get_FiringReport(/*[out][retVal] class CIGridppReport** pVal*/);
	//@备注 Graphics，获取自绘部件框的自绘对象。
	// 此属性仅在部件框自定义绘制时可用，即在部件框的自定义绘制事件与自定义绘制脚本上可用，在其它地方本对象不可用。
	//@别名 取绘图接口()
	/*virtual*/ class CIGRGraphics get_Graphics(/*[out][retVal] class CIGRGraphics** pVal*/);
	//@备注 Utility，获取报表辅助工具对象。
	//@别名 取功能函数()
	/*virtual*/ class CIGRUtility get_Utility(/*[out][retVal] class CIGRUtility** pVal*/);
	//@备注 PageDivideCount，打印输出时，纸张在垂直方向上的均分个数。
	//@别名 取页分割数()
	/*virtual*/ long get_PageDivideCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_PageDivideCount(&_result); return _result; }
	//@备注 PageDivideCount，打印输出时，纸张在垂直方向上的均分个数。
	//@参数 分割数量 
	//@别名 置页分割数(分割数量)
	/*virtual*/ HRESULT set_PageDivideCount(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PageDivideCount(pVal); return _result; }
	//@备注 PageDivideSpacing，打印输出时，纸张在垂直方向均分时的分隔间距。
	//@别名 取页分割间隙()
	/*virtual*/ double get_PageDivideSpacing(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_PageDivideSpacing(&_result); return _result; }
	//@备注 PageDivideSpacing，打印输出时，纸张在垂直方向均分时的分隔间距。
	//@参数 分割间隙 
	//@别名 置页分割间隙(分割间隙)
	/*virtual*/ HRESULT set_PageDivideSpacing(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PageDivideSpacing(pVal); return _result; }
	//@备注 PageDivideLine，打印输出时，是否显示纸张在垂直方向均分的分隔线。
	//@别名 取页分割线显示()
	/*virtual*/ BOOL get_PageDivideLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_PageDivideLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PageDivideLine，打印输出时，是否显示纸张在垂直方向均分的分隔线。
	//@参数 逻辑值 
	//@别名 置页分割线显示(逻辑值)
	/*virtual*/ HRESULT set_PageDivideLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PageDivideLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintAsDesignPaper，指定是否按设计时的页面设置生成打印页面。
	// 如果此属性为真，则打印页面按设计时的页面设置进行生成，反之则按系统中打印机的当前页面设置进行生成。
	//@别名 取按设计页面打印()
	/*virtual*/ BOOL get_PrintAsDesignPaper(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_PrintAsDesignPaper(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAsDesignPaper，指定是否按设计时的页面设置生成打印页面。
	// 如果此属性为真，则打印页面按设计时的页面设置进行生成，反之则按系统中打印机的当前页面设置进行生成。
	//@参数 逻辑值 
	//@别名 置按设计页面打印(逻辑值)
	/*virtual*/ HRESULT set_PrintAsDesignPaper(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PrintAsDesignPaper(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ContinuePrint，指定是否采用连续打印，即打即停的方式打印输出报表。
	//@别名 取即打即停()
	/*virtual*/ BOOL get_ContinuePrint(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_ContinuePrint(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ContinuePrint，指定是否采用连续打印，即打即停的方式打印输出报表。
	//@参数 逻辑值 
	//@别名 置即打即停(逻辑值)
	/*virtual*/ HRESULT set_ContinuePrint(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ContinuePrint(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MonoPrint，指定是否按黑白色打印输出。
	//@别名 取单色打印()
	/*virtual*/ BOOL get_MonoPrint(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_MonoPrint(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MonoPrint，指定是否按黑白色打印输出。
	//@参数 逻辑值 
	//@别名 置单色打印(逻辑值)
	/*virtual*/ HRESULT set_MonoPrint(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_MonoPrint(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MirrorMargins，当双面打印报表时，本属性为“是”，让左右页边距按镜像方式产生，这样方便报表的装订。
	//@别名 取镜像左右页边距()
	/*virtual*/ BOOL get_MirrorMargins(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_MirrorMargins(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MirrorMargins，当双面打印报表时，本属性为“是”，让左右页边距按镜像方式产生，这样方便报表的装订。
	//@参数 逻辑值 
	//@别名 置镜像左右页边距(逻辑值)
	/*virtual*/ HRESULT set_MirrorMargins(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_MirrorMargins(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BackImage，背景图仅在报表设计时使用，只有当报表进入页面视图中才会显示背景图。
	// 如果同时设定了 BackImage 与 BackImageFile 属性，此时只有 BackImage 属性指定的图像被显示。
	//@别名 取背景图像()
	/*virtual*/ class CIGRPicture get_BackImage(/*[out][retVal] class CIGRPicture** pVal*/);
	//@备注 BackImage，背景图仅在报表设计时使用，只有当报表进入页面视图中才会显示背景图。
	// 如果同时设定了 BackImage 与 BackImageFile 属性，此时只有 BackImage 属性指定的图像被显示。
	//@参数 报表图片对象 
	//@别名 置背景图像(报表图片对象)
	/*virtual*/ HRESULT set_BackImage(/*[in]*/ class CIGRPicture* pVal);
	//@备注 BackImageFile，背景图仅在报表设计时使用，只有当报表进入页面视图中才会显示背景图。
	// 如果同时设定了 BackImage 与 BackImageFile 属性，此时只有 BackImage 属性指定的图像被显示。
	//@返回 报表在设计器中进入页面视图时显示的背景图文件的路径与名称。
	//@别名 取背景图文件()
	/*virtual*/ CXText get_BackImageFile(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_BackImageFile(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 BackImageFile，背景图仅在报表设计时使用，只有当报表进入页面视图中才会显示背景图。
	// 如果同时设定了 BackImage 与 BackImageFile 属性，此时只有 BackImage 属性指定的图像被显示。
	//@参数 文件名 指定报表在设计器中进入页面视图时显示的背景图文件的路径与名称。
	//@别名 置背景图文件(文件名)
	/*virtual*/ HRESULT set_BackImageFile(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_BackImageFile((BSTR)pVal); return _result; }
	//@备注 BackImagePreview，指示在报表预览时，是否显示设计背景图。
	//@别名 取背景图预览()
	/*virtual*/ BOOL get_BackImagePreview(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_BackImagePreview(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BackImagePreview，指示在报表预览时，是否显示设计背景图。
	//@参数 逻辑值 
	//@别名 置背景图预览(逻辑值)
	/*virtual*/ HRESULT set_BackImagePreview(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_BackImagePreview(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BackImagePrint，指定在打印输出、导出PDF、导出图像时是否输出背景图。
	//@别名 取背景图打印()
	/*virtual*/ BOOL get_BackImagePrint(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_BackImagePrint(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BackImagePrint，指定在打印输出、导出PDF、导出图像时是否输出背景图。
	//@参数 逻辑值 
	//@别名 置背景图打印(逻辑值)
	/*virtual*/ HRESULT set_BackImagePrint(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_BackImagePrint(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Watermark，获取报表在生成打印页面时在每页中显示的水印背景图像。
	//@别名 取水印图像()
	/*virtual*/ class CIGRPicture get_Watermark(/*[out][retVal] class CIGRPicture** pVal*/);
	//@备注 Watermark，指定报表在生成打印页面时在每页中显示的水印背景图像。
	//@参数 报表图片对象 
	//@别名 置水印图像(报表图片对象)
	/*virtual*/ HRESULT set_Watermark(/*[in]*/ class CIGRPicture* pVal);
	//@备注 WatermarkAlignment，指定水印图在页面中显示时的位置对齐方式：1、左上角；2、右上角；3、居中；4、左下角；5、右下角
	//@别名 取水印图显示方式()
	/*virtual*/ GRPictureAlignment get_WatermarkAlignment(/*[out][retVal] GRPictureAlignment* pVal*/){GRPictureAlignment _result; ((IGridppReport*)m_ptr.p)->get_WatermarkAlignment(&_result); return _result; }
	//@备注 WatermarkAlignment，指定水印图在页面中显示时的位置对齐方式：1、左上角；2、右上角；3、居中；4、左下角；5、右下
	//@参数 图像显示方式枚举值 
	//@别名 置水印图显示方式(图像显示方式枚举值)
	/*virtual*/ HRESULT set_WatermarkAlignment(/*[in]*/ GRPictureAlignment pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_WatermarkAlignment(pVal); return _result; }
	//@备注 WatermarkSizeMode，指定水印图在页面中显示时使用的缩放方式：1、剪裁；2、伸缩铺满；3、伸缩；4、完整显示；5、平铺
	//@别名 取水印图缩放方式()
	/*virtual*/ GRPictureSizeMode get_WatermarkSizeMode(/*[out][retVal] GRPictureSizeMode* pVal*/){GRPictureSizeMode _result; ((IGridppReport*)m_ptr.p)->get_WatermarkSizeMode(&_result); return _result; }
	//@备注 WatermarkSizeMode，指定水印图在页面中显示时使用的缩放方式：1、剪裁；2、伸缩铺满；3、伸缩；4、完整显示；5、平铺
	//@参数 图像缩放方式枚举值 
	//@别名 置水印图缩放方式(图像缩放方式枚举值)
	/*virtual*/ HRESULT set_WatermarkSizeMode(/*[in]*/ GRPictureSizeMode pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_WatermarkSizeMode(pVal); return _result; }
	//@备注 ConnectionString，获取连接到数据源的连接串，如果报表主对象的“数据库连接”属性不指定，报表主对象的查询SQL将自动应用明细数据集上的数据库连接设置。
	//@别名 取参数化查询连接串()
	/*virtual*/ CXText get_ConnectionString(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ConnectionString(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ConnectionString，设置连接到数据源的连接串，如果报表主对象的“数据库连接”属性不指定，报表主对象的查询SQL将自动应用明细数据集上的数据库连接设置。
	//@参数 连接串文本 
	//@别名 置参数化查询连接串(连接串文本)
	/*virtual*/ HRESULT set_ConnectionString(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ConnectionString((BSTR)pVal); return _result; }
	//@备注 QuerySQL，从数据源中取数的SQL语句。
	// 报表参数查询SQL通常只返回一条记录，即使返回多条记录，Grid++Report也只应用第一条记录，将各个子段值自动传递给同名的参数与部件框。
	//@别名 取参数化查询SQL()
	/*virtual*/ CXText get_QuerySQL(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_QuerySQL(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 QuerySQL，从数据源中取数的SQL语句。
	// 报表参数查询SQL通常只返回一条记录，即使返回多条记录，Grid++Report也只应用第一条记录，将各个子段值自动传递给同名的参数与部件框。
	//@参数 查询SQL语句 
	//@别名 置参数化查询SQL(查询SQL语句)
	/*virtual*/ HRESULT set_QuerySQL(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_QuerySQL((BSTR)pVal); return _result; }
	//@备注 SkipQuery，指示在生成报表时，是否忽略从数据源取数的属性设置。
	//@别名 取忽略数据绑定()
	/*virtual*/ BOOL get_SkipQuery(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_SkipQuery(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SkipQuery，指示在生成报表时，是否忽略从数据源取数的属性设置。
	//@参数 逻辑值 
	//@别名 置忽略数据绑定(逻辑值)
	/*virtual*/ HRESULT set_SkipQuery(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_SkipQuery(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 XmlTableName，指定报表主对象对应的 XML 或 JSON 格式数据包中的数据集名称。
	// 通常情况下不需要设置此属性，只有当需要通过 XML 或 JSON 数据包加载数据，且数据包中包含有多个记录集，此时设置此属性才会生效。
	// Grid++Report 会自动匹配多记录集数据包中的各个记录集到报表中的对应对象中，通过设置此属性让报表参数或部件框与数据包中的记录集产生固定的关联，而不会采用自动匹配方式。
	//@别名 取Xml表名()
	/*virtual*/ CXText get_XmlTableName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_XmlTableName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 XmlTableName，指定报表主对象对应的 XML 或 JSON 格式数据包中的数据集名称。
	// 通常情况下不需要设置此属性，只有当需要通过 XML 或 JSON 数据包加载数据，且数据包中包含有多个记录集，此时设置此属性才会生效。
	// Grid++Report 会自动匹配多记录集数据包中的各个记录集到报表中的对应对象中，通过设置此属性让报表参数或部件框与数据包中的记录集产生固定的关联，而不会采用自动匹配方式。
	//@参数 Xml表名称 
	//@别名 置Xml表名(Xml表名称)
	/*virtual*/ HRESULT set_XmlTableName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_XmlTableName((BSTR)pVal); return _result; }
	/*virtual*/ GRStorageFormat get_StorageFormat(/*[out][retVal] GRStorageFormat* pVal*/){GRStorageFormat _result; ((IGridppReport*)m_ptr.p)->get_StorageFormat(&_result); return _result; }
	//@备注 StorageFormat，存储格式枚举值：1、文本；2、二进制；3、Base64编码；4、XML目前不支持。
	//@参数 存储格式枚举值 
	//@别名 置存储格式(存储格式枚举值)
	/*virtual*/ HRESULT set_StorageFormat(/*[in]*/ GRStorageFormat pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_StorageFormat(pVal); return _result; }
	//@备注 TextEncode，文本编码枚举值：1、Ansi码；2、UTF8码；3、Unicode码。
	//@别名 取文本编码()
	/*virtual*/ GRTextEncodeMode get_TextEncode(/*[out][retVal] GRTextEncodeMode* pVal*/){GRTextEncodeMode _result; ((IGridppReport*)m_ptr.p)->get_TextEncode(&_result); return _result; }
	//@备注 TextEncode，文本编码枚举值：1、Ansi码；2、UTF8码；3、Unicode码。
	//@参数 文本编码枚举值 
	//@别名 置文本编码(文本编码枚举值)
	/*virtual*/ HRESULT set_TextEncode(/*[in]*/ GRTextEncodeMode pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_TextEncode(pVal); return _result; }
	//@备注 Unit，报表单位枚举值：1、厘米；2、英寸
	//@别名 取单位()
	/*virtual*/ GRUnit get_Unit(/*[out][retVal] GRUnit* pVal*/){GRUnit _result; ((IGridppReport*)m_ptr.p)->get_Unit(&_result); return _result; }
	//@备注 Unit，报表单位枚举值：1、厘米；2、英寸
	//@参数 计量单位枚举值 
	//@别名 置单位(计量单位枚举值)
	/*virtual*/ HRESULT set_Unit(/*[in]*/ GRUnit pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Unit(pVal); return _result; }
	//@备注 ScriptType，获取在本报表中使用的脚本语言类型。
	//@别名 取脚本类型()
	/*virtual*/ GRScriptType get_ScriptType(/*[out][retVal] GRScriptType* pVal*/){GRScriptType _result; ((IGridppReport*)m_ptr.p)->get_ScriptType(&_result); return _result; }
	//@备注 ScriptType，指定在本报表中使用的脚本语言类型。
	//@参数 脚本语言枚举 
	//@别名 置脚本类型(脚本语言枚举)
	/*virtual*/ HRESULT set_ScriptType(/*[in]*/ GRScriptType pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ScriptType(pVal); return _result; }
	//@备注 CodePage，报表中的文字在Unicode与多字节字符集之间转换的内码表。
	// 本属性目前只用于QRCode二维码进行文字编码转换，如果二维码扫描识别乱码，应该考虑调整本属性。
	//@返回 默认65001
	//@别名 取内码表()
	/*virtual*/ long get_CodePage(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_CodePage(&_result); return _result; }
	//@备注 CodePage，报表中的文字在Unicode与多字节字符集之间转换的内码表。
	// 本属性目前只用于QRCode二维码进行文字编码转换，如果二维码扫描识别乱码，应该考虑调整本属性。
	//@参数 内码表枚举 默认65001
	//@别名 置内码表(内码表枚举)
	/*virtual*/ HRESULT set_CodePage(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_CodePage(pVal); return _result; }
	//@备注 AlignToGrid，当在设计器中设计报表模板时，是否将部件框的边框对齐到设计栅格点。
	//@别名 取对齐到栅格点()
	/*virtual*/ BOOL get_AlignToGrid(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_AlignToGrid(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AlignToGrid，当在设计器中设计报表模板时，是否将部件框的边框对齐到设计栅格点。
	//@参数 逻辑值 
	//@别名 置对齐到栅格点(逻辑值)
	/*virtual*/ HRESULT set_AlignToGrid(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_AlignToGrid(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowGrid，获取是否在设计器中显示设计栅格点的标志。
	//@别名 取显示栅格点()
	/*virtual*/ BOOL get_ShowGrid(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_ShowGrid(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowGrid，设置是否在设计器中显示设计栅格点的标志。
	//@参数 逻辑值 
	//@别名 置显示栅格点(逻辑值)
	/*virtual*/ HRESULT set_ShowGrid(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowGrid(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GridColsPerUnit，在设计器中，水平方向上每个计量单位显示的设计栅格点个数。
	//@返回 默认值5，有效值范围：1-50。
	//@别名 取每单位栅格点列数()
	/*virtual*/ long get_GridColsPerUnit(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_GridColsPerUnit(&_result); return _result; }
	//@备注 GridColsPerUnit，在设计器中，水平方向上每个计量单位显示的设计栅格点个数。
	//@参数 数量值 默认值5，有效值范围：1-50。
	//@别名 置每单位栅格点列数(数量值)
	/*virtual*/ HRESULT set_GridColsPerUnit(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_GridColsPerUnit(pVal); return _result; }
	//@备注 GridRowsPerUnit，在设计器中，垂直方向上每个计量单位显示的设计栅格点个数。
	//@返回 默认值5，有效值范围：1-50。
	//@别名 取每单位栅格点行数()
	/*virtual*/ long get_GridRowsPerUnit(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_GridRowsPerUnit(&_result); return _result; }
	//@备注 GridRowsPerUnit，在设计器中，垂直方向上每个计量单位显示的设计栅格点个数。
	//@参数 数量值 默认值5，有效值范围：1-50。
	//@返回 默认值5，有效值范围：1-50。
	//@别名 置每单位栅格点行数(数量值)
	/*virtual*/ HRESULT set_GridRowsPerUnit(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_GridRowsPerUnit(pVal); return _result; }
	//@备注 Title，报表文档的标题文字，当打印输出报表时，打印文档的标题是此属性的值。报表数据导出时，此属性将作为导出文件的默认文件名称。
	//@别名 取文档标题()
	/*virtual*/ CXText get_Title(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_Title(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Title，报表文档的标题文字，当打印输出报表时，打印文档的标题是此属性的值。报表数据导出时，此属性将作为导出文件的默认文件名称。
	//@参数 标题文本 
	//@别名 置文档标题(标题文本)
	/*virtual*/ HRESULT set_Title(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Title((BSTR)pVal); return _result; }
	//@备注 Author，指定报表的制作者，也可以记录其它信息，此属性设置不影响报表运行。
	//@别名 取作者()
	/*virtual*/ CXText get_Author(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_Author(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Author，指定报表的制作者，也可以记录其它信息，此属性设置不影响报表运行。
	//@参数 作者姓名 
	//@别名 置作者(作者姓名)
	/*virtual*/ HRESULT set_Author(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Author((BSTR)pVal); return _result; }
	//@备注 Description，指定报表的描述性文字，也可以记录其它信息，此属性设置不影响报表运行。
	//@别名 取简介()
	/*virtual*/ CXText get_Description(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_Description(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Description，指定报表的描述性文字，也可以记录其它信息，此属性设置不影响报表运行。
	//@参数 简介文本 
	//@别名 置简介(简介文本)
	/*virtual*/ HRESULT set_Description(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Description((BSTR)pVal); return _result; }
	//@备注 ShowMoneyDigit，获取在报表中显示金额线或金额位标签时显示的位数，位数不包括角与分位。
	//@返回 位数不包括角与分位。
	//@别名 取财务金额位数()
	/*virtual*/ long get_ShowMoneyDigit(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_ShowMoneyDigit(&_result); return _result; }
	//@备注 ShowMoneyDigit，获取在报表中显示金额线或金额位标签时显示的位数，位数不包括角与分位。
	//@参数 位数 位数不包括角与分位。
	//@别名 置财务金额位数(位数)
	/*virtual*/ HRESULT set_ShowMoneyDigit(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowMoneyDigit(pVal); return _result; }
	//@备注 ShowMoneyWidth，获取在报表中显示金额线或金额位标签时显示全部位的宽度，位数不包括角与分位。
	//@返回 以报表的计量单位表示属性值。当属性值为零时，报表在运行时将自动确定金额显示宽度。
	//@别名 取财务金额位总宽度()
	/*virtual*/ double get_ShowMoneyWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_ShowMoneyWidth(&_result); return _result; }
	//@备注 ShowMoneyWidth，获取在报表中显示金额线或金额位标签时显示全部位的宽度，位数不包括角与分位。
	//@参数 宽度值 以报表的计量单位表示属性值。当属性值为零时，报表在运行时将自动确定金额显示宽度。
	//@别名 置财务金额位总宽度(宽度值)
	/*virtual*/ HRESULT set_ShowMoneyWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowMoneyWidth(pVal); return _result; }
	//@备注 ShowMoneyLineColor，获取金额位分隔线的颜色。
	//@别名 取财务金额线颜色()
	/*virtual*/ OLE_COLOR get_ShowMoneyLineColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGridppReport*)m_ptr.p)->get_ShowMoneyLineColor(&_result); return _result; }
	//@备注 ShowMoneyLineColor，获取金额位分隔线的颜色。
	//@参数 颜色值 
	//@别名 置财务金额线颜色(颜色值)
	/*virtual*/ HRESULT set_ShowMoneyLineColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowMoneyLineColor(pVal); return _result; }
	//@备注 ShowMoneySepLineColor，获取元与角位之间的分隔线的颜色。
	//@别名 取财务金额分隔线颜色()
	/*virtual*/ OLE_COLOR get_ShowMoneySepLineColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGridppReport*)m_ptr.p)->get_ShowMoneySepLineColor(&_result); return _result; }
	//@备注 ShowMoneySepLineColor，获取元与角位之间的分隔线的颜色。
	//@参数 颜色值 
	//@别名 置财务金额分隔线颜色(颜色值)
	/*virtual*/ HRESULT set_ShowMoneySepLineColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowMoneySepLineColor(pVal); return _result; }
	//@备注 InitializeScript，可以在本脚本中修改定义报表模板、为报表参数赋值及其它任务等。
	//@别名 取初始化脚本()
	/*virtual*/ CXText get_InitializeScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_InitializeScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 InitializeScript，可以在本脚本中修改定义报表模板、为报表参数赋值及其它任务等。
	//@参数 脚本文本 
	//@别名 置初始化脚本(脚本文本)
	/*virtual*/ HRESULT set_InitializeScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_InitializeScript((BSTR)pVal); return _result; }
	//@备注 ProcessBeginScript，当报表准备对填入的数据进行分析处理之前触发本事件。
	//@别名 取开始处理记录脚本()
	/*virtual*/ CXText get_ProcessBeginScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ProcessBeginScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ProcessBeginScript，当报表准备对填入的数据进行分析处理之前触发本事件。
	//@参数 脚本文本 
	//@别名 置开始处理记录脚本(脚本文本)
	/*virtual*/ HRESULT set_ProcessBeginScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ProcessBeginScript((BSTR)pVal); return _result; }
	//@备注 ProcessEndScript，当报表对填入的数据进行分析处理完成之后触发本事件。
	//@别名 取结束处理记录脚本()
	/*virtual*/ CXText get_ProcessEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ProcessEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ProcessEndScript，当报表对填入的数据进行分析处理完成之后触发本事件。
	//@参数 脚本文本 
	//@别名 置结束处理记录脚本(脚本文本)
	/*virtual*/ HRESULT set_ProcessEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ProcessEndScript((BSTR)pVal); return _result; }
	//@备注 PageStartScript，表示报表 PageStart 事件对应的脚本语言代码。
	//@别名 取页开始脚本()
	/*virtual*/ CXText get_PageStartScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_PageStartScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PageStartScript，表示报表 PageStart 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置页开始脚本(脚本文本)
	/*virtual*/ HRESULT set_PageStartScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PageStartScript((BSTR)pVal); return _result; }
	//@备注 PageEndScript，表示报表 PageEnd 事件对应的脚本语言代码。
	//@别名 取页结束脚本()
	/*virtual*/ CXText get_PageEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_PageEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PageEndScript，表示报表 PageEnd 事件对应的脚本语言代码。
	//@参数 脚本文本 
	//@别名 置页结束脚本(脚本文本)
	/*virtual*/ HRESULT set_PageEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PageEndScript((BSTR)pVal); return _result; }
	//@备注 BeforeSortScript，当要对数据集中的记录进行重新排序之前触发本事件。
	//@别名 取排序前脚本()
	/*virtual*/ CXText get_BeforeSortScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_BeforeSortScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 BeforeSortScript，当要对数据集中的记录进行重新排序之前触发本事件。
	//@参数 脚本文本 
	//@别名 置排序前脚本(脚本文本)
	/*virtual*/ HRESULT set_BeforeSortScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_BeforeSortScript((BSTR)pVal); return _result; }
	//@备注 ExportBeginScript，表示报表 ExportBegin 事件对应的脚本代码。
	// 可以在本脚本中改写导出选项，改变报表的默认导出行为。本脚本对应的 Sender 对象为 IGRExportOption 接口引用，根据导出数据类型，可以把 Sender 对象转换为具体的导出类型对象，具体请参考 IGRExportOption 接口的编程参考帮助。
	//@别名 取导出前脚本()
	/*virtual*/ CXText get_ExportBeginScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ExportBeginScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ExportBeginScript，表示报表 ExportBegin 事件对应的脚本代码。
	// 可以在本脚本中改写导出选项，改变报表的默认导出行为。本脚本对应的 Sender 对象为 IGRExportOption 接口引用，根据导出数据类型，可以把 Sender 对象转换为具体的导出类型对象，具体请参考 IGRExportOption 接口的编程参考帮助。
	//@参数 脚本文本 
	//@别名 置导出前脚本(脚本文本)
	/*virtual*/ HRESULT set_ExportBeginScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ExportBeginScript((BSTR)pVal); return _result; }
	//@备注 ExportEndScript，表示报表 ExportEnd 事件对应的脚本代码。
	//@别名 取导出后脚本()
	/*virtual*/ CXText get_ExportEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ExportEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ExportEndScript，表示报表 ExportEnd 事件对应的脚本代码。
	//@参数 脚本文本 
	//@别名 置导出后脚本(脚本文本)
	/*virtual*/ HRESULT set_ExportEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ExportEndScript((BSTR)pVal); return _result; }
	//@备注 PrintBeginScript，表示报表 PrintBegin 事件对应的脚本代码。
	//@别名 取打印前脚本()
	/*virtual*/ CXText get_PrintBeginScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_PrintBeginScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PrintBeginScript，表示报表 PrintBegin 事件对应的脚本代码。
	//@参数 脚本文本 
	//@别名 置打印前脚本(脚本文本)
	/*virtual*/ HRESULT set_PrintBeginScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PrintBeginScript((BSTR)pVal); return _result; }
	//@备注 PrintEndScript，表示报表 PrintEnd 事件对应的脚本代码。
	//@别名 取打印后脚本()
	/*virtual*/ CXText get_PrintEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_PrintEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PrintEndScript，表示报表 PrintEnd 事件对应的脚本代码。
	//@参数 脚本文本 
	//@别名 置打印后脚本(脚本文本)
	/*virtual*/ HRESULT set_PrintEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PrintEndScript((BSTR)pVal); return _result; }
	//@备注 PrintPageScript，表示报表 PrintPage 事件对应的脚本代码。
	//@别名 取打印页脚本()
	/*virtual*/ CXText get_PrintPageScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_PrintPageScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PrintPageScript，表示报表 PrintPage 事件对应的脚本代码。
	//@参数 脚本文本 
	//@别名 置打印页脚本(脚本文本)
	/*virtual*/ HRESULT set_PrintPageScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_PrintPageScript((BSTR)pVal); return _result; }
	//@备注 ShowPreviewWndScript，表示报表 ShowPreviewWnd 事件对应的脚本代码。
	// 可以在本事件响应中通过 IGRPrintViewer 控件接口对默认预览窗口进行自定义。
	// 例子代码：
	// //去除Grid++的默认打印预览窗口的工具栏中的“邮件发送”按钮，
	// //即用 PrintPreview 与 PrintPreviewEx 方法调用出来的打印预览窗口
	// Sender.RemoveToolbarControl(6); //grtctMail 6 发送邮件按钮 
	// //从打印预览窗口执行执行打印时，不显示打印对话框
	// Sender.ShowPrintDlg = false;
	//@别名 取显示预览脚本()
	/*virtual*/ CXText get_ShowPreviewWndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_ShowPreviewWndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ShowPreviewWndScript，表示报表 ShowPreviewWnd 事件对应的脚本代码。
	// 可以在本事件响应中通过 IGRPrintViewer 控件接口对默认预览窗口进行自定义。
	// 例子代码：
	// //去除Grid++的默认打印预览窗口的工具栏中的“邮件发送”按钮，
	// //即用 PrintPreview 与 PrintPreviewEx 方法调用出来的打印预览窗口
	// Sender.RemoveToolbarControl(6); //grtctMail 6 发送邮件按钮 
	// //从打印预览窗口执行执行打印时，不显示打印对话框
	// Sender.ShowPrintDlg = false;
	//@参数 脚本文本 
	//@别名 置显示预览脚本(脚本文本)
	/*virtual*/ HRESULT set_ShowPreviewWndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowPreviewWndScript((BSTR)pVal); return _result; }
	//@备注 Running，处于运行状态中的报表不允许重新栽入或重新定义模板数据。
	//@别名 取运行中()
	/*virtual*/ BOOL get_Running(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_Running(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DisplayMode，指示报表的输出显示状态，报表显示模式枚举：1、查询显示；2、打印页面生成；3、空闲。
	// 在SectionFormat事件处理函数中，获取本属性的值以知道当前的显示输出过程，可以对查询显示器中报表的子画显示输出和打印页面生成显示输出采取不同的处理。
	//@返回 报表显示模式枚举：1、查询显示；2、预览显示；3、空闲。
	//@别名 取显示模式()
	/*virtual*/ GRReportDisplayMode get_DisplayMode(/*[out][retVal] GRReportDisplayMode* pVal*/){GRReportDisplayMode _result; ((IGridppReport*)m_ptr.p)->get_DisplayMode(&_result); return _result; }
	//@备注 FirstPass，指示报表是否在第一遍报表运行过程中，此属性必须用在于打印相关的报表事件中获取。
	// Grid++Report 在生成打印页面数据时，需要两次遍历处理报表数据，通过此属性可以侦测报表是处于第一遍生成过程中，还是处于第二遍生成过程中。
	//@别名 取是否首次生成()
	/*virtual*/ BOOL get_FirstPass(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_FirstPass(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PageBlankHeight，报表在生成打印页面数据的过程中，当前页面剩余的空白区域高度。必须在报表的 “GeneratePagesEnd 页面生成后脚本”属性上写报表脚本获取。
	// 此属性通常用来报表页面生成后获取最后一页剩余的空白纸张高度，记录下此属性值用于实现续打功能，具体请参考帮助中“开发指南->报表打印->续打(存折与病历打印)”的部分。
	// 此属性值用报表中的“计量单位”属性指定的计量单位。报表中的空白页的输出区域是指除掉页眉与页脚的中间区域，此属性值加上页脚的高度即为空白位置顶端距离页底的距离。
	// PageBlankHeight 属性值必须在报表的 “GeneratePagesEnd”事件响应函数中或报表主对象的“页面生成后脚本”属性上写报表脚本获取。其它地方读取本属性值将始终为0。
	//@别名 取页面空白高度()
	/*virtual*/ double get_PageBlankHeight(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_PageBlankHeight(&_result); return _result; }
	//@备注 HasFloatControl，指定报表中是否包含有浮动部件框。
	//@别名 取是否包含浮动节()
	/*virtual*/ BOOL get_HasFloatControl(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_HasFloatControl(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowProgressUI，指定报表在运行时是否显示进度指示。
	// 设置此属性值只能是在程序代码中，不能在报表模板中直接设置。
	//@别名 取显示进度界面()
	/*virtual*/ BOOL get_ShowProgressUI(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_ShowProgressUI(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowProgressUI，指定报表在运行时是否显示进度指示。
	// 设置此属性值只能是在程序代码中，不能在报表模板中直接设置。
	//@参数 逻辑值 
	//@别名 置显示进度界面(逻辑值)
	/*virtual*/ HRESULT set_ShowProgressUI(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ShowProgressUI(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_SummaryAccept(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_SummaryAccept(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_SummaryAccept(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_SummaryAccept(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ long get_MaxGenPages(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_MaxGenPages(&_result); return _result; }
	/*virtual*/ HRESULT set_MaxGenPages(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_MaxGenPages(pVal); return _result; }
	//@备注 IsBlank，指示报表模板是否为空白未定义状态。
	//@别名 取是否空载()
	/*virtual*/ BOOL get_IsBlank(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_IsBlank(&_result); return (VARIANT_TRUE==_result); }
	//@备注 LatestLoadedFile，仅运行时可用，本报表模板最近载入的路径文件。如果获取为空，则文件可能是动态生成的。
	//@返回 本报表模板最近载入的路径文件。
	//@别名 取最近加载的文件()
	/*virtual*/ CXText get_LatestLoadedFile(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_LatestLoadedFile(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LatestLoadedFile，仅运行时可用，本报表模板最近载入的路径文件。如果获取为空，则文件可能是动态生成的。
	//@参数 文件名 指定带路径的文件名。
	//@别名 置最近加载的文件(文件名)
	/*virtual*/ HRESULT set_LatestLoadedFile(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_LatestLoadedFile((BSTR)pVal); return _result; }
	/*virtual*/ HRESULT set_ErrorProcessed(/*[in]*/ BOOL _arg1){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_ErrorProcessed(_arg1? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DataLoaded，在报表运行过程中，指示报表数据是否已经载入。
	//@别名 取数据加载()
	/*virtual*/ BOOL get_DataLoaded(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->get_DataLoaded(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RunningDetailGrid，获取报表运行时展现出来的明细网格对象接口（特用于交叉表的明细网格），除了交叉表，其它类型的报表本属性与DetailGrid是一样的。
	//@别名 取运行时明细网格()
	/*virtual*/ class CIGRDetailGrid get_RunningDetailGrid(/*[out][retVal] class CIGRDetailGrid** pVal*/);
	//@备注 About，显示Grid++Report关于对话框。
	//@别名 关于()
	/*virtual*/ HRESULT About(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_About(); return _result; }
	//@备注 ControlByName，从报表主对象包括的所有部件框中根据部件框名称找到对应部件框对象的接口引用，如果找到名称匹配的部件框，则返回该部件框对象的接口引用，否则返回NULL。
	//@参数 名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按名称取部件框(名称)
	/*virtual*/ class CIGRControl ControlByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRControl** ppControl*/);
	//@备注 ColumnByName，根据名称找到对应列对象的接口引用，如果找到名称匹配的列，则返回该列对象的接口引用，否则返回NULL。
	//@参数 列名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按名称取列(列名称)
	/*virtual*/ class CIGRColumn ColumnByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRColumn** ppColumn*/);
	//@备注 FieldByName，根据字段名称得到匹配字段对象的接口引用，如果找到名称匹配的字段，则返回该字段对象的接口引用，否则返回NULL。
	//@参数 字段名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按名称取字段(字段名称)
	/*virtual*/ class CIGRField FieldByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRField** ppField*/);
	//@备注 FieldByDBName，根据字段的数据源字段名称得到匹配字段对象的接口引用，如果找到匹配的字段，则返回该字段对象的接口引用，否则返回NULL。
	//@参数 字段名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按源名称取字段(字段名称)
	/*virtual*/ class CIGRField FieldByDBName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRField** ppField*/);
	//@备注 ParameterByName，如果找到名称匹配的参数，则返回该参数对象的接口引用，否则返回NULL。
	//@参数 名称 注意：匹配名称时不区分字母的大小写。
	//@别名 按名称取参数(名称)
	/*virtual*/ class CIGRParameter ParameterByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] class CIGRParameter** ppParameter*/);
	//@备注 FindFirstControl，找出报表中的第一个部件框，如果报表中不存在部件框，则返回值为空值引用。
	//@别名 查找第一个部件框()
	/*virtual*/ class CIGRControl FindFirstControl(/*[out][retVal] class CIGRControl** ppControl*/);
	//@备注 FindNextControl，找出报表中的下一个部件框的引用，如果报表中不存在后续的部件框，则返回值为空值引用。在调用 FindNextControl 之前必须调用 FindFirstControl。 
	//@别名 查找下一个部件框()
	/*virtual*/ class CIGRControl FindNextControl(/*[out][retVal] class CIGRControl** ppControl*/);
	//@备注 PixelsToUnit，将屏幕像素值转换为报表当前使用的计量单位值。
	//@参数 像素值 指定要转换的屏幕像素值。
	//@别名 转换像素到单位(像素值)
	/*virtual*/ double PixelsToUnit(/*[in]*/ long Pixels/*, [out][retVal] double* pUnitValue*/){double _result=0; ((IGridppReport*)m_ptr.p)->raw_PixelsToUnit(Pixels, &_result); return _result; }
	//@备注 UnitToPixels，将报表当前使用的计量单位值转换为屏幕像素值。
	//@参数 计量单位 指定要转换的报表计量单位值。
	//@别名 转换单位到像素(计量单位)
	/*virtual*/ long UnitToPixels(/*[in]*/ double UnitValue/*, [out][retVal] long* pPixels*/){long _result=0; ((IGridppReport*)m_ptr.p)->raw_UnitToPixels(UnitValue, &_result); return _result; }
	//@备注 SystemVarValue，在报表运行时，取得本报表某个指定系统参数的当前值。如果是获取分组相关的系统变量，用本方法获取到的最外层第一个分组的相关值。
	//@参数 系统变量枚举值 系统变量枚举值：1、当期日期时间；2、页数；3、页号；4、记录号；8、行号；19、记录数；分组变量枚举值：20、分组序号；21、分组项数；22、分组项行号；23、分组项行数；24、分组项页号；25、分组项页数
	//@别名 获取系统变量值(系统变量枚举值)
	/*virtual*/ double SystemVarValue(/*[in]*/ GRSystemVarType SystemVar/*, [out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->raw_SystemVarValue(SystemVar, &_result); return _result; }
	/*virtual*/ double SystemVarValue2(/*[in]*/ GRSystemVarType SystemVar, /*, [in]*/ long GroupIndex/*, [out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->raw_SystemVarValue2(SystemVar, GroupIndex, &_result); return _result; }
	//@备注 AddParameter，增加一个参数定义。
	//@别名 增加参数()
	/*virtual*/ class CIGRParameter AddParameter(/*[in]*/ const wchar_t* Name, /*, [in]*/ GRParameterDataType DataType/*, [out][retVal] class CIGRParameter** ppParameter*/);
	//@备注 InsertDetailGrid，向报表主对象插入明细网格，使报表主对象具有明细网格。
	// 只有当报表主对象不存在明细网格对象时，才能成功插入明细网格，报表主对象只能拥有一个明细网格。此方法一般在以编程方式定义报表模板时使用。
	//@别名 插入明细网格()
	/*virtual*/ class CIGRDetailGrid InsertDetailGrid(/*[out][retVal] class CIGRDetailGrid** ppDetailGrid*/);
	//@备注 InsertPageHeader，增加页眉定义。
	// 增加页眉定义，使报表主对象具有一个页眉。如果报表主对象已经定义了页眉，此方法直接返回页眉的接口引用。
	//@别名 插入页眉()
	/*virtual*/ class CIGRPageHeader InsertPageHeader(/*[out][retVal] class CIGRPageHeader** ppPageHeader*/);
	//@备注 InsertPageFooter，增加页脚定义。
	// 增加页脚定义，使报表主对象具有一个页脚。如果报表主对象已经定义了页脚，此方法直接返回页脚的接口引用。
	//@别名 插入页脚()
	/*virtual*/ class CIGRPageFooter InsertPageFooter(/*[out][retVal] class CIGRPageFooter** ppPageFooter*/);
	//@备注 Clear，清除所有的报表模板定义数据，使报表主对象成为一张空白报表。如果要用完全编程的方式定义报表模板数据，在定义数据之前，有必要调用此方法将已存在的旧数据全部清除掉。
	//@别名 清空()
	/*virtual*/ HRESULT Clear(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_Clear(); return _result; }
	//@备注 DeleteDetailGrid，删除整个明细网格的定义，报表主对象将不具有明细网格。
	//@别名 删除明细网格()
	/*virtual*/ HRESULT DeleteDetailGrid(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_DeleteDetailGrid(); return _result; }
	//@备注 DeletePageHeader，删除页眉的定义，报表主对象将不具有页眉。
	//@别名 删除页眉()
	/*virtual*/ HRESULT DeletePageHeader(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_DeletePageHeader(); return _result; }
	//@备注 DeletePageFooter，删除页脚的定义，报表主对象将不具有页脚。
	//@别名 删除页脚()
	/*virtual*/ HRESULT DeletePageFooter(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_DeletePageFooter(); return _result; }
	//@备注 Print，调用此方法后，首先生成报表数据，过程中会触发一系列事件；然后生成打印页面数据，过程中也会触发一系列事件；最后将生成的打印数据送至打印机进行打印。
	//@参数 显示打印对话框 指示在打印前是否显示打印对话框。
	//@别名 打印(显示打印对话框)
	/*virtual*/ HRESULT Print(/*[in]*/ BOOL ShowPrintDialog){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_Print(ShowPrintDialog? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintEx，打印报表,按指定方式生成生成打印数据。
	//@参数 打印生成方式枚举值 1、表单；2、内容；3、全部；4、预览全部
	//@参数 显示打印对话框 指示在打印前是否显示打印对话框
	//@别名 打印扩展(打印生成方式枚举值,显示打印对话框)
	/*virtual*/ HRESULT PrintEx(/*[in]*/ GRPrintGenerateStyle GenerateStyle, /*, [in]*/ BOOL ShowPrintDialog){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_PrintEx(GenerateStyle, ShowPrintDialog? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintPreview，提供的缺省打印预览窗口中预览报表。
	//@参数 显示模式 参数值指定在进行预览窗口操作的同时是否允许同时对其他窗口进行操作。
	//@别名 打印预览(显示模式)
	/*virtual*/ HRESULT PrintPreview(/*[in]*/ BOOL ShowModal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_PrintPreview(ShowModal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintPreviewEx，提供的缺省打印预览窗口中预览报表，可以指定打印数据的生成方式。
	//@参数 打印生成方式枚举值 打印生成方式枚举：1、表单；2、内容；3、全部；4、预览全部
	//@参数 显示模式 参数值指定在进行预览窗口操作的同时是否允许同时对其他窗口进行操作。
	//@参数 最大化预览窗口 是否最大化打印预览窗口。
	//@别名 打印预览扩展(打印生成方式枚举值,显示模式,最大化预览窗口)
	/*virtual*/ HRESULT PrintPreviewEx(/*[in]*/ GRPrintGenerateStyle GenerateStyle, /*, [in]*/ BOOL ShowModal, /*, [in]*/ BOOL MaximizeWindow){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_PrintPreviewEx(GenerateStyle, ShowModal? VARIANT_TRUE : VARIANT_FALSE, MaximizeWindow? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BeginLoopPrint，三个方法“开始循环打印BeginLoopPrint,循环打印LoopPrint,结束循环打印EndLoopPrint”必须在一起调用，在要进行循环打印开始时调用BeginLoopPrint，在循环打印完成时调用EndLoopPrint，在中间根据需要多次调用LoopPrint。
	//@参数 打印生成方式枚举值 打印生成方式枚举：1、表单；2、内容；3、全部；4、预览全部
	//@参数 是否显示打印对话框 指示在打印前是否显示打印对话框。
	//@别名 开始循环打印(打印生成方式枚举值,是否显示打印对话框)
	/*virtual*/ BOOL BeginLoopPrint(/*[in]*/ GRPrintGenerateStyle GenerateStyle, /*, [in]*/ BOOL ShowPrintDialog/*, [out][retVal] BOOL* pSuccesss*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_BeginLoopPrint(GenerateStyle, ShowPrintDialog? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 EndLoopPrint，结束循环打印。
	//@别名 结束循环打印()
	/*virtual*/ HRESULT EndLoopPrint(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_EndLoopPrint(); return _result; }
	//@备注 LoopPrint，在循环打印过程中，执行一次打印生成过程。每调用一次 循环打印LoopPrint 方法，就会首先生成报表数据，然后生成打印页面数据，最后将打印页面数据送至打印机进行打印输出
	//@别名 循环打印()
	/*virtual*/ HRESULT LoopPrint(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_LoopPrint(); return _result; }
	//@备注 AbortPrint，中断打印任务的执行，此方法只能在 PrintBegin 与 PrintPage 事件中执行。
	//@别名 中断打印()
	/*virtual*/ HRESULT AbortPrint(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_AbortPrint(); return _result; }
	//@备注 ExportDirect，直接进行数据导出。
	//@参数 导出类型枚举值 1、导出XLS；2、导出TXT；3、导出HTM；4、导出RTF；5、导出PDF；6、导出CSV；7、导出IMG
	//@参数 文件名 指定导出的完整文件路径与文件名称。
	//@参数 显示导出设置对话框 指定是否在导出之前显示选项设置对话框。
	//@参数 打开文件 指示是否在导出数据之后用关联程序打开导出文件。
	//@别名 直接导出(导出类型枚举值,文件名,显示导出设置对话框,打开文件)
	/*virtual*/ BOOL ExportDirect(/*[in]*/ GRExportType ExportType, /*, [in]*/ const wchar_t* FileName, /*, [in]*/ BOOL ShowOptionDlg, /*, [in]*/ BOOL DoneOpen/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_ExportDirect(ExportType, (BSTR)FileName, ShowOptionDlg? VARIANT_TRUE : VARIANT_FALSE, DoneOpen? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 AbortExport，中断数据导出任务的执行，此方法只能在 ExportBegin 事件中执行，用于中止数据导出。
	//@别名 中断导出()
	/*virtual*/ HRESULT AbortExport(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_AbortExport(); return _result; }
	//@备注 GenerateDocumentFile，生成报表的 Grid++Report 文档文件到指定的文件。
	//@参数 文件名 保存数据的文件的路径与名称。
	//@别名 生成报表文档(文件名)
	/*virtual*/ HRESULT GenerateDocumentFile(/*[in]*/ const wchar_t* FileName){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_GenerateDocumentFile((BSTR)FileName); return _result; }
	//@备注 ForceNewPage，在报表生成过程中，结束当前页，开始一个新页面。在报表生成过程中，可以调用此方法强制进行分页。
	// 只能在PageProcessRecord 与 SectionFormat 事件中调用，在 SectionFormat 中调用时必须保证是在打印生成状态中。
	//@别名 强制换新页()
	/*virtual*/ HRESULT ForceNewPage(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_ForceNewPage(); return _result; }
	/*virtual*/ HRESULT Design(/*[in]*/ BOOL ShowModal, /*, [in]*/ BOOL MaximizeWindow){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_Design(ShowModal? VARIANT_TRUE : VARIANT_FALSE, MaximizeWindow? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 LoadFromFile，从报表模板文件中载入报表模板定义。
	//@参数 文件名 指定模板文件的完全路径名称。
	//@别名 从文件加载报表(文件名)
	/*virtual*/ BOOL LoadFromFile(/*[in]*/ const wchar_t* FileName/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadFromFile((BSTR)FileName, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToFile，将报表模板数据保存到文件中，以模板设置的存储格式保存模板数据。
	//@参数 文件名 指定模板文件的完全路径名称。
	//@别名 保存到文件(文件名)
	/*virtual*/ BOOL SaveToFile(/*[in]*/ const wchar_t* FileName/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_SaveToFile((BSTR)FileName, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL LoadFromURL(/*[in]*/ const wchar_t* URL/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadFromURL((BSTR)URL, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL SaveToURL(/*[in]*/ const wchar_t* URL/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_SaveToURL((BSTR)URL, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadFromStr，从字符文本串中载入报表模板数据。
	//@参数 数据文本串 指定报表模板数据文本。
	//@别名 从字符串加载报表(数据文本串)
	/*virtual*/ BOOL LoadFromStr(/*[in]*/ const wchar_t* data/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadFromStr((BSTR)data, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToStr，保存报表模板数据保存至字符串，以文本格式保存保存模板数据。
	//@别名 保存到字符串()
	/*virtual*/ CXText SaveToStr(/*[out][retVal] const wchar_t** pData*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->raw_SaveToStr(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LoadFromVariant，从一个包含报表模板数据的 Variant 变量中载入报表。
	//@参数 数据 数据包
	//@别名 从变量加载报表(数据)
	/*virtual*/ BOOL LoadFromVariant(/*[in]*/ VARIANT Buf/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadFromVariant(Buf, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToVariant，保存报表模板数据保存至内存缓冲区，以模板设置的存储格式保存模板数据。
	//@别名 保存到变量()
	/*virtual*/ VARIANT SaveToVariant(/*[out][retVal] VARIANT* pBuf*/){VARIANT _result; VariantInit(&_result);((IGridppReport*)m_ptr.p)->raw_SaveToVariant(&_result); return _result; }
	/*virtual*/ BOOL LoadDataFromURL(/*[in]*/ const wchar_t* URL/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadDataFromURL((BSTR)URL, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL LoadDataFromURLEx(/*[in]*/ const wchar_t* DataURL, /*, [in]*/ const wchar_t* DataParam/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadDataFromURLEx((BSTR)DataURL, (BSTR)DataParam, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadDataFromXML，从 XML 或 JSON 文字串中载入报表明细记录集数据，数据应符合约定的形式。
	// XML 与  JSON 文本数据的格式请参考：“报表插件(WEB报表)->报表数据”中的说明。
	// 不符合约定格式的数据可以抽取为一个数据项，然后用其它的函数加载到报表中。
	// 比如桌面程序可以采用推模式像报表提供数据，参考帮助“产品介绍->概念与原理->向报表提供数据：拉模式与推模式”中的说明，只要程序中能够访问到的数据都可以传递到报表中。
	//@参数 XML文本数据 XML文本形式的记录集数据。文本数据必须符合 Grid++Report 的约定格式要求。
	//@返回 指示载入是否成功。
	//@别名 从XML载入数据(XML文本数据)
	/*virtual*/ BOOL LoadDataFromXML(/*[in]*/ const wchar_t* XMLData/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadDataFromXML((BSTR)XMLData, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ CXText ExtractXMLFromURL(/*[in]*/ const wchar_t* URL/*, [out][retVal] const wchar_t** pXML*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->raw_ExtractXMLFromURL((BSTR)URL, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ CXText ExtractXMLFromURLEx(/*[in]*/ const wchar_t* DataURL, /*, [in][opt]*/ const wchar_t* DataParam/*, [out][retVal] const wchar_t** pXML*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->raw_ExtractXMLFromURLEx((BSTR)DataURL, (BSTR)DataParam, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 LoadBackImageFromFile，从指定的图像文件中载入报表设计页面背景图。
	//@参数 文件名 指定图像文件的路径与名称。
	//@别名 从文件加载背景图(文件名)
	/*virtual*/ HRESULT LoadBackImageFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_LoadBackImageFromFile((BSTR)PathFile); return _result; }
	//@备注 LoadWatermarkFromFile，从指定的图像文件中载入水印背景图。
	//@参数 文件名 指定图像文件的路径与名称。
	//@别名 从文件加载水印图(文件名)
	/*virtual*/ HRESULT LoadWatermarkFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_LoadWatermarkFromFile((BSTR)PathFile); return _result; }
	//@备注 PrepareLoadData，准备向报表中载入数据，调用此方法后，就可以向报表的记录集推送(加入)数据。
	// 当采用推模式提供报表数据时，通常是在报表主对象的 FetchRecord（请求记录数据）事件中填入记录集数据。
	// 如果要在此事件之外的地方填入记录集数据，在进行填入数据之前应该首先本方法。一般是在报表模板载入之后调用本方法。 
	// 注意：在子报表里用本方法加载明细数据时，导出到新Excel表时会丢失。
	//@别名 加载数据准备()
	/*virtual*/ HRESULT PrepareLoadData(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_PrepareLoadData(); return _result; }
	//@备注 CancelLoadData，取消向报表 加载数据PrepareLoadData 所进行的准备任务。
	//@别名 加载数据取消()
	/*virtual*/ HRESULT CancelLoadData(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_CancelLoadData(); return _result; }
	//@备注 LoadFromMemory，从内存中载入报表模板数据。
	//@参数 数据指针 pBuffer，数据缓冲区内存地址。
	//@参数 数据尺寸 BytesCount，数据缓冲区的字节数。
	//@别名 从内存加载报表(数据指针,数据尺寸)
	/*virtual*/ BOOL LoadFromMemory(/*[in]*/ unsigned char* pData, /*, [in]*/ long ByteCount/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_LoadFromMemory(pData, ByteCount, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SaveToMemory，保存报表模板数据保存至内存缓冲区，以模板设置的存储格式保存模板数据，返回保存报表模板数据是否成功。
	//@参数 数据指针 pBuffer，数据缓冲区内存地址。
	//@参数 数据尺寸 BytesCount，数据缓冲区的字节数。
	//@别名 保存到内存(数据指针,数据尺寸)
	/*virtual*/ BOOL SaveToMemory(/*[out]*/ OLE_HANDLE* ppData, /*, [out]*/ long* pBytesCount/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_SaveToMemory(ppData, pBytesCount, &_result); return (VARIANT_TRUE==_result); }
	//@备注 LoadBackImageFromMemory，从内存数据中载入报表设计页面背景图。
	//@参数 数据指针 pBuffer，数据缓冲区内存地址。
	//@参数 数据尺寸 BytesCount，数据缓冲区的字节数。
	//@别名 从内存加载背景图(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadBackImageFromMemory(/*[in]*/ unsigned char* pBuffer, /*, [in]*/ long BytesCount){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_LoadBackImageFromMemory(pBuffer, BytesCount); return _result; }
	//@备注 LoadWatermarkFromMemory，从内存数据中载入报表水印背景图。
	//@参数 数据指针 pBuffer，数据缓冲区内存地址。
	//@参数 数据尺寸 BytesCount，数据缓冲区的字节数。
	//@别名 从内存加载水印图(数据指针,数据尺寸)
	/*virtual*/ HRESULT LoadWatermarkFromMemory(/*[in]*/ unsigned char* pBuffer, /*, [in]*/ long BytesCount){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_LoadWatermarkFromMemory(pBuffer, BytesCount); return _result; }
	//@备注 Register，应当对注册码采取适当的加解密方式，避免注册码泄露。
	//@参数 注册码 12位发布码，可以使用自己的加解密算法对注册码进行加解密操作。
	//@别名 注册(注册码)
	/*virtual*/ BOOL Register(/*[in]*/ const wchar_t* SerialNo/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_Register((BSTR)SerialNo, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SharePrintSetupOptions，获取共享全局打印设置参数的选项组合值。
	// 用二进制Bit位表示相应的共享全局打印设置参数是否被当前报表使用。
	// 如果使用某个或某类全局打印设置参数，这对当前报表应用或设置打印设置参数都是对共享全局打印设置参数进行操作。
	// [PaperMargin|PaperKind|PaperOrientation|PaperSource|SelectedPrinter]=[纸张边距,纸张类型,纸张方向,纸张来源,打印机] 
	//@返回 组合值：1、纸张边距；2、纸张类型；4、纸张方向；8、纸张来源；16、选择打印机
	//@别名 取共享打印选项()
	/*virtual*/ long get_SharePrintSetupOptions(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_SharePrintSetupOptions(&_result); return _result; }
	//@备注 SharePrintSetupOptions，获取共享全局打印设置参数的选项组合值。
	// [PaperMargin|PaperKind|PaperOrientation|PaperSource|SelectedPrinter]=[纸张边距,纸张类型,纸张方向,纸张来源,打印机]
	// 组合值：1、纸张边距；2、纸张类型；4、纸张方向；8、纸张来源；16、选择打印机
	//@参数 选项值 组合值，用二进制Bit位表示相应的共享全局打印设置参数是否被当前报表使用。
	// 如果使用某个或某类全局打印设置参数，这对当前报表应用或设置打印设置参数都是对共享全局打印设置参数进行操作。
	//@别名 置共享打印选项(选项值)
	/*virtual*/ HRESULT set_SharePrintSetupOptions(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_SharePrintSetupOptions(pVal); return _result; }
	//@备注 SharePrintSetupObject，获取当前应用程序的共享全局打印设置对象的接口引用。
	// 通过此属性取得当前应用程序的共享全局打印设置对象的接口引用，从而可以对共享全局打印设置参数进行操作。
	//@别名 取共享打印设置()
	/*virtual*/ class CIGRSharePrintSetupObject get_SharePrintSetupObject(/*[out][retVal] class CIGRSharePrintSetupObject** pVal*/);
	/*virtual*/ HRESULT SharePrintSetupSetOptionEnabled(/*[in]*/ GRSharePrintSetupOption Option, /*, [in]*/ BOOL Enabled){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_SharePrintSetupSetOptionEnabled(Option, Enabled? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SharePrintSetupEnableAllOptions，指定应用全部的共享打印设置参数。
	//@别名 共享打印选项全部开启()
	/*virtual*/ HRESULT SharePrintSetupEnableAllOptions(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_SharePrintSetupEnableAllOptions(); return _result; }
	//@备注 SharePrintSetupDisableAllOptions，指定禁用全部的共享打印设置参数。
	//@别名 共享打印选项全部禁止()
	/*virtual*/ HRESULT SharePrintSetupDisableAllOptions(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_SharePrintSetupDisableAllOptions(); return _result; }
	//@备注 SharePrintSetupGetOptionEnabled，获取是否应用某个共享全局打印参数项的使能状态。
	// 1、页面边距；2、纸张类型；4、纸张方向；8、纸张来源；16、选择打印机
	//@参数 共享打印参数枚举值 
	//@别名 置共享打印参数值(共享打印参数枚举值)
	/*virtual*/ BOOL SharePrintSetupGetOptionEnabled(/*[in]*/ GRSharePrintSetupOption Option/*, [out][retVal] BOOL* pEnabled*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_SharePrintSetupGetOptionEnabled(Option, &_result); return (VARIANT_TRUE==_result); }
	//@备注 DesignLeftMargin，指定设计报表时所定义的页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计左边距()
	/*virtual*/ double get_DesignLeftMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignLeftMargin(&_result); return _result; }
	//@备注 DesignLeftMargin，指定设计报表时所定义的页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计左边距(小数值)
	/*virtual*/ HRESULT set_DesignLeftMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignLeftMargin(pVal); return _result; }
	//@备注 DesignRightMargin，指定设计报表时所定义的页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计右边距()
	/*virtual*/ double get_DesignRightMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignRightMargin(&_result); return _result; }
	//@备注 DesignRightMargin，指定设计报表时所定义的页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计右边距(小数值)
	/*virtual*/ HRESULT set_DesignRightMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignRightMargin(pVal); return _result; }
	//@备注 DesignTopMargin，指定设计报表时所定义的页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计上边距()
	/*virtual*/ double get_DesignTopMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignTopMargin(&_result); return _result; }
	//@备注 DesignTopMargin，指定设计报表时所定义的页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计上边距(小数值)
	/*virtual*/ HRESULT set_DesignTopMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignTopMargin(pVal); return _result; }
	//@备注 DesignBottomMargin，指定设计报表时所定义的页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计下边距()
	/*virtual*/ double get_DesignBottomMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignBottomMargin(&_result); return _result; }
	//@备注 DesignBottomMargin，指定设计报表时所定义的页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计下边距(小数值)
	/*virtual*/ HRESULT set_DesignBottomMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignBottomMargin(pVal); return _result; }
	//@备注 DesignPaperWidth，指定设计报表时所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计纸张宽度()
	/*virtual*/ double get_DesignPaperWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignPaperWidth(&_result); return _result; }
	//@备注 DesignPaperWidth，指定设计报表时所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计纸张宽度(小数值)
	/*virtual*/ HRESULT set_DesignPaperWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignPaperWidth(pVal); return _result; }
	//@备注 DesignPaperLength，指定设计报表时所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计纸张长度()
	/*virtual*/ double get_DesignPaperLength(/*[out][retVal] double* pVal*/){double _result=0; ((IGridppReport*)m_ptr.p)->get_DesignPaperLength(&_result); return _result; }
	//@备注 DesignPaperLength，指定设计报表时所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计纸张长度(小数值)
	/*virtual*/ HRESULT set_DesignPaperLength(/*[in]*/ double pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignPaperLength(pVal); return _result; }
	//@备注 DesignPaperOrientation，指定设计报表时所定义的纸张方向：0、默认；1、纵向；2、横向
	//@别名 取设计纸张方向()
	/*virtual*/ GRPaperOrientation get_DesignPaperOrientation(/*[out][retVal] GRPaperOrientation* pVal*/){GRPaperOrientation _result; ((IGridppReport*)m_ptr.p)->get_DesignPaperOrientation(&_result); return _result; }
	//@备注 DesignPaperOrientation，指定设计报表时所定义的纸张方向：0、默认；1、纵向；2、横向
	//@参数 纸张方向枚举值 0、默认；1、纵向；2、横向
	//@别名 置设计纸张方向(纸张方向枚举值)
	/*virtual*/ HRESULT set_DesignPaperOrientation(/*[in]*/ GRPaperOrientation pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignPaperOrientation(pVal); return _result; }
	//@备注 DesignPaperName，指定设计报表时所定义的纸张名称。
	//@别名 取设计纸张名称()
	/*virtual*/ CXText get_DesignPaperName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_DesignPaperName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DesignPaperName，指定设计报表时所定义的纸张名称。
	//@参数 纸张名称 
	//@别名 置设计纸张名称(纸张名称)
	/*virtual*/ HRESULT set_DesignPaperName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignPaperName((BSTR)pVal); return _result; }
	//@备注 DesignPaperSize，指定设计报表时所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@别名 取设计纸张规格()
	/*virtual*/ long get_DesignPaperSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_DesignPaperSize(&_result); return _result; }
	//@备注 DesignPaperSize，指定设计报表时所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@参数 标准纸张类型枚举值 
	//@别名 置设计纸张规格(标准纸张类型枚举值)
	/*virtual*/ HRESULT set_DesignPaperSize(/*[in]*/ long pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DesignPaperSize(pVal); return _result; }
	/*virtual*/ class CIGRReportHeader get_ReportHeader(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRReportHeader** pVal*/);
	/*virtual*/ class CIGRReportFooter get_ReportFooter(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRReportFooter** pVal*/);
	/*virtual*/ long get_ReportHeaderCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_ReportHeaderCount(&_result); return _result; }
	/*virtual*/ long get_ReportFooterCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGridppReport*)m_ptr.p)->get_ReportFooterCount(&_result); return _result; }
	//@备注 InsertReportHeader，增加报表头定义。
	// 增加报表头定义，使报表主对象增加一个报表头，此方法直接返回所增加的报表头接口引用。
	// 可以增加多个报表头，本版本也可以从报表头集合里增加报表头。
	//@别名 插入报表头()
	/*virtual*/ class CIGRReportHeader InsertReportHeader(/*[out][retVal] class CIGRReportHeader** ppReportHeader*/);
	//@备注 InsertReportFooter，增加报表尾定义。
	// 增加报表尾定义，使报表主对象增加一个报表尾，此方法直接返回所增加的报表尾接口引用。
	// 可以增加多个报表尾，本版本也可以从报表尾集合里增加报表尾。
	//@别名 插入报表尾()
	/*virtual*/ class CIGRReportFooter InsertReportFooter(/*[out][retVal] class CIGRReportFooter** ppReportFooter*/);
	//@备注 DeleteReportHeader，按名称删除一个报表头。
	//@参数 名称 报表头名称
	//@别名 按名称删除报表头(名称)
	/*virtual*/ HRESULT DeleteReportHeader(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_DeleteReportHeader(Index); return _result; }
	//@备注 DeleteReportFooter，按名称删除一个报表尾。
	//@参数 名称 报表尾名称
	//@别名 按名称删除报表尾(名称)
	/*virtual*/ HRESULT DeleteReportFooter(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_DeleteReportFooter(Index); return _result; }
	//@备注 Export，在调用Export方法之前一定要调用PrepareExport方法，在其后一定要调用UnprepareExport(完成导出)方法。
	//@参数 打开文件 指示是否在导出数据之后用关联程序打开导出文件。
	//@别名 导出(打开文件)
	/*virtual*/ BOOL Export(/*[in]*/ BOOL DoneOpen/*, [out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_Export(DoneOpen? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 PrepareExport，返回导出选项对象的接口，在调用Export(导出)方法之前一定要调用本方法，在其后一定要调用UnprepareExport(完成导出)方法。
	// 本方法返回的选项对象的接口引用可以用来设定选项值。
	//@参数 导出类型枚举值 
	//@别名 准备导出(导出类型枚举值)
	/*virtual*/ class CIGRExportOption PrepareExport(/*[in]*/ GRExportType ExportType/*, [out][retVal] class CIGRExportOption** pExportOption*/);
	//@备注 UnprepareExport，数据导出完成之后，进行一些内部释放任务。在调用Export(导出)方法之前一定要调用PrepareExport(准备导出)方法，在其后一定要调用UnprepareExport(完成导出)方法。
	//@别名 完成导出()
	/*virtual*/ HRESULT UnprepareExport(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_UnprepareExport(); return _result; }
	//@备注 PrepareRecordset，6.0之后此接口用PrepareLoadData(准备加载数据)替代。
	// 采用推模式提供报表数据时，通常是在报表主对象的 FetchRecord （请求记录数据）事件中填入记录集数据。
	// 如果要在此事件之外的地方填入记录集数据，在进行填入数据之前应该首先本方法。一般是在报表模板载入之后调用本方法。
	//  注意：在子报表里用本方法加载明细数据时，导出到新Excel表时会丢失。
	//@别名 添加记录准备()
	/*virtual*/ BOOL PrepareRecordset(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw_PrepareRecordset(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CancelRecordset，6.0之后此接口用CancelLoadData(取消载入数据)替代。取消向报表 添加记录 所进行的准备任务。
	//@别名 添加记录取消()
	/*virtual*/ HRESULT CancelRecordset(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw_CancelRecordset(); return _result; }
	/*virtual*/ OLE_HANDLE get__SystemImage(/*[in]*/ GRSystemImage SystemImage/*, [out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGridppReport*)m_ptr.p)->get__SystemImage(SystemImage, &_result); return _result; }
	/*virtual*/ OLE_HANDLE get__ResHinst(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGridppReport*)m_ptr.p)->get__ResHinst(&_result); return _result; }
	/*virtual*/ HRESULT _AttachDesigner(/*[in]*/ IDispatch* pDesigner){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__AttachDesigner(pDesigner); return _result; }
	/*virtual*/ HRESULT _ObjSaveBegin(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__ObjSaveBegin(); return _result; }
	/*virtual*/ HRESULT _ObjSaveEnd(/*[out]*/ OLE_HANDLE* ppData, /*, [out]*/ unsigned long* pBytesCount){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__ObjSaveEnd(ppData, pBytesCount); return _result; }
	/*virtual*/ HRESULT _ObjLoadBegin(/*[in]*/ unsigned char* pData, /*, [in]*/ unsigned long BytesCount){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__ObjLoadBegin(pData, BytesCount); return _result; }
	/*virtual*/ HRESULT _ObjLoadEnd(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__ObjLoadEnd(); return _result; }
	/*virtual*/ BOOL _ObjLoadEof(/*[out][retVal] BOOL* pEof*/){VARIANT_BOOL _result=0; ((IGridppReport*)m_ptr.p)->raw__ObjLoadEof(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ class CIGridppReport _CreateProxyReport(/*[out][retVal] class CIGridppReport** ppReport*/);
	/*virtual*/ HRESULT _DestroyProxyReport(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__DestroyProxyReport(); return _result; }
	/*virtual*/ HRESULT _RefreshPrinter(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__RefreshPrinter(); return _result; }
	/*virtual*/ HRESULT _PullData(){ HRESULT _result = ((IGridppReport*)m_ptr.p)->raw__PullData(); return _result; }
	/*virtual*/ OLE_HANDLE _GetMoneyLabelVarHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGridppReport*)m_ptr.p)->raw__GetMoneyLabelVarHandle(&_result); return _result; }
	//@备注 DocType，文档类型枚举值：1、对象格式；2、JSON格式
	//@别名 取文档类型()
	/*virtual*/ GRDocType get_DocType(/*[out][retVal] GRDocType* pVal*/){GRDocType _result; ((IGridppReport*)m_ptr.p)->get_DocType(&_result); return _result; }
	//@备注 DocType，文档类型枚举值：1、对象格式；2、JSON格式
	//@参数 文档类型枚举值 
	//@别名 置文档类型(文档类型枚举值)
	/*virtual*/ HRESULT set_DocType(/*[in]*/ GRDocType pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_DocType(pVal); return _result; }
	//@备注 PrintDocumentData，从二进制数据包中载入报表文档数据，然后将报表文档进行打印输出。
	//@参数 二进制对象 
	//@别名 打印文档数据(二进制对象)
	/*virtual*/ BOOL PrintDocumentData(/*[in]*/ class CIGRBinaryObject* pBinaryObject/*, [out][retVal] BOOL* pSucceeded*/);
	//@备注 GenerateDocumentData，产生报表文档数据包，返回存储报表文档数据的二进制数据对象。
	//@别名 生成文档数据()
	/*virtual*/ class CIGRBinaryObject GenerateDocumentData(/*[out][retVal] class CIGRBinaryObject** ppBinaryObject*/);
	//@备注 Lock，锁定类别枚举：0、不锁定；1、锁定继承；2、锁定对象；3、锁定数据；4、锁定数据行为；5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@别名 取锁定()
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGridppReport*)m_ptr.p)->get_Lock(&_result); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定；1、锁定继承；2、锁定对象；3、锁定数据；4、锁定数据行为；5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@参数 锁定类别枚举 
	//@别名 置锁定(锁定类别枚举)
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_Lock(pVal); return _result; }
	/*virtual*/ long WebRegisterStatus(/*[out][retVal] long* pResult*/){long _result=0; ((IGridppReport*)m_ptr.p)->raw_WebRegisterStatus(&_result); return _result; }
	//@备注 GlobalScript，获取报表脚本中的全局有效的变量与函数的脚本代码，全局脚本在报表开始运行时会首先被装载并执行，其中的变量与函数，可以在其它报表脚本代码中使用。
	// 说明：如果在多个报表脚本代码中要共享变量，就可以定义全局的变量。如果有相同的功能在多个脚本代码中用到，就可以定义一个全局函数。
	//@别名 取全局脚本()
	/*virtual*/ CXText get_GlobalScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_GlobalScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GlobalScript，获取报表脚本中的全局有效的变量与函数的脚本代码，全局脚本在报表开始运行时会首先被装载并执行，其中的变量与函数，可以在其它报表脚本代码中使用。
	// 说明：如果在多个报表脚本代码中要共享变量，就可以定义全局的变量。如果有相同的功能在多个脚本代码中用到，就可以定义一个全局函数。
	//@参数 脚本文本 
	//@别名 置全局脚本(脚本文本)
	/*virtual*/ HRESULT set_GlobalScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_GlobalScript((BSTR)pVal); return _result; }
	//@备注 GeneratePagesBeginScript，在产生报表页面数据之前会被执行的脚本代码。
	//@别名 取页面生成前脚本()
	/*virtual*/ CXText get_GeneratePagesBeginScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_GeneratePagesBeginScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GeneratePagesBeginScript，在产生报表页面数据之前会被执行的脚本代码。
	//@参数 脚本文本 
	//@别名 置页面生成前脚本(脚本文本)
	/*virtual*/ HRESULT set_GeneratePagesBeginScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_GeneratePagesBeginScript((BSTR)pVal); return _result; }
	//@备注 GeneratePagesEndScript，在产生报表页面数据之后会被执行的脚本代码。
	//@别名 取页面生成后脚本()
	/*virtual*/ CXText get_GeneratePagesEndScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGridppReport*)m_ptr.p)->get_GeneratePagesEndScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GeneratePagesEndScript，在产生报表页面数据之后会被执行的脚本代码。
	//@参数 脚本文本 
	//@别名 置页面生成后脚本(脚本文本)
	/*virtual*/ HRESULT set_GeneratePagesEndScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGridppReport*)m_ptr.p)->put_GeneratePagesEndScript((BSTR)pVal); return _result; }

};

//@分组}

//@备注 PageHeader，表示报表的页眉。页眉只在打印生成时显示，紧靠每页上边距的上面显示。
// 页眉在打印生成时，输出在每页的上边距之上；在屏幕查询显示时，页眉被忽略掉，即屏幕查询显示不使用页眉。
// 一个报表只能定义一个页眉。在页眉中一般定义页号，总页数，文档名称，打印时间及其它需要显示在输出纸张页眉区域的信息。
//@别名 页眉
class CIGRPageHeader : public CIGRSection
{
public:
	CIGRPageHeader(){};
	CIGRPageHeader(IGRPageHeader* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPageHeader* GetPtr(){ return ((IGRPageHeader*)m_ptr.p); }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRPageHeader*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRPageHeader*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 PageFooter，表示报表的页脚。页脚只在打印生成时显示，紧靠每页下边距的下面显示。
// 页脚在打印生成时，输出在每页的上边距之上；在屏幕查询显示时，页脚被忽略掉，即屏幕查询显示不使用页脚。一个报表只能定义一个页脚。
// 在页脚中一般定义页号，总页数，文档名称，打印时间及其它需要显示在输出纸张页脚区域的信息。
//@别名 页脚
class CIGRPageFooter : public CIGRSection
{
public:
	CIGRPageFooter(){};
	CIGRPageFooter(IGRPageFooter* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPageFooter* GetPtr(){ return ((IGRPageFooter*)m_ptr.p); }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRPageFooter*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRPageFooter*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Parameters，集合对象，报表主对象的所有参数的集合对象。
//@别名 参数集合
class CIGRParameters : public CXComObj /*IDispatch*/
{
public:
	CIGRParameters(){};
	CIGRParameters(IGRParameters* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRParameters* GetPtr(){ return ((IGRParameters*)m_ptr.p); }
	/*virtual*/ class CIGRParameter get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRParameter** ppParameter*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRParameters*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有参数的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRParameters*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个参数并返回新增参数的接口引用。
	//@返回 新增参数的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRParameter Add(/*[out][retVal] class CIGRParameter** ppParameter*/);
	//@备注 Remove，根据参数的顺序号将参数移除，在输入参数种指定要移除参数的顺序号或名称。
	//@参数 序号 指定参数的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRParameters*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部参数。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRParameters*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据参数的名称取得其顺序号，如果不存在与名称匹配的参数，则返回-1。
	// 参数的名称不区分字母的大小写。
	//@参数 名称 指定参数的名称。 
	//@返回 如果有匹配的参数，返回其顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRParameters*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，按序号获取对应的参数对象，序号从1开始。
	//@参数 序号 指定元素对象的序号，从1开始。
	//@返回 获取到的参数对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRParameter ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRParameter** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数对象的顺序。
	//@参数 序号 指定参数对象的序号，序号从1开始。
	//@参数 新顺序号 参数对象在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRParameters*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 Parameter，表示报表中的可变参数值。报表拥有一组参数，参数在报表运行时可以通过编程的方式改变其值。
// 报表开发者可以在报表生成过程中的事件中读取与设置参数的值，例如利用参数，我们可以进行自定义的数据统计计算。
// 报表参数用来在报表运行时存储生成过程中的数据，参数具有多种数据类型，参数可以被静态框与综合文本框关联，静态框与综合文本框输出参数值的显示文本，在综合文本框中参数还可以参与表达式的运算。
// ◆报表参数的几种典型用途
//   自定义复杂的统计计算，将统计运算结果存储在参数中，然后将参数关联到静态框，通过静态框将计算结果显示出来。例如通过对 GroupBegin，ProcessRecord，GroupEnd 事件的响应，对分组项数据进行自定义计算并将计算结果存储到参数对象，在分组头与分组尾中放置关联参数的静态框，将计算结果显示出来。 
//   当要通过循环打印的方式将主从表的数据打印出来，在每打印一条主表记录时，将主表的数据在 Initialize 事件处理函数中传递给参数，使各条主表的记录数据显示在每张报表中。 
//   为参数化查询SQL语句提供数据，在查询SQL语句中通过“:”后面跟参数名实现参数化查询SQL语句,报表在运行时, 查询SQL中的参数将被同名的参数对象的值所取代,从而实现报表数据的动态变化。一般在报表的 Initialize 事件中为参数对象赋值。 
// ◆为报表参数提供数据
//   在报表主对象上可以设置数据库连接串与查询SQL，通过此数据库连接串与查询SQL可以为参数自动获取数据。报表主对象上的数据库连接串与查询SQL通常只获取一条记录数据，Grid++Report也只会应用第一条记录数据，将查询SQL的字段值赋值到报表中同名的参数或部件框上。
//   根据报表主对象上的数据库连接串与查询SQL，可以自动创建对应的报表参数。
//   也可以用程序代码设置报表参数的值。
// ◆关于参数的数据类型说明：
//   字符：用于记录字符值，无长度限制。 
//   整数：用于记录整数值，根据格式串生成值的显示文字。 
//   浮点数：用于记录浮点数值，根据格式串生成值的显示文字。 
//   日期时间：用于记录日期时间值，根据格式串生成值的显示文字。 
//   布尔：用于真假值，根据真值显示文字与假值显示文字生成值的显示文字。
// ◆注意：因为没有二进制类型的参数，查询SQL中的二进制字段将不会产生对应的参数。在Grid++Report中，二进制数据通常都是作为图像框的图像数据，定义与二进制字段同名的图像框，在运行时，二进制字段的值将自动加载到同名图像框中。
//@别名 参数
class CIGRParameter : public CIGRObject
{
public:
	CIGRParameter(){};
	CIGRParameter(IGRParameter* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRParameter* GetPtr(){ return ((IGRParameter*)m_ptr.p); }
	//@备注 DataType，指示参数的数据类型。
	//@返回 1、字符串； 2、整数； 3、浮点数； 5、逻辑； 6、日期时间
	//@别名 取类型()
	/*virtual*/ GRParameterDataType get_DataType(/*[out][retVal] GRParameterDataType* pVal*/){GRParameterDataType _result; ((IGRParameter*)m_ptr.p)->get_DataType(&_result); return _result; }
	//@备注 DataType，指示参数的数据类型。
	//@参数 参数类型枚举值 1、字符串； 2、整数； 3、浮点数； 5、逻辑； 6、日期时间
	//@别名 置类型(参数类型枚举值)
	/*virtual*/ HRESULT set_DataType(/*[in]*/ GRParameterDataType pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_DataType(pVal); return _result; }
	//@备注 Name，参数的名称标识，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRParameter*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，参数的名称标识，采用26个英文字母(不区分大小写)和0-9这十个自然数,加上下划线\'_\'组成,共63个字符.不能出现其他字符。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 Value，获取参数的值。
	//@别名 取值()
	/*virtual*/ VARIANT get_Value(/*[out][retVal] VARIANT* pVal*/){VARIANT _result; VariantInit(&_result);((IGRParameter*)m_ptr.p)->get_Value(&_result); return _result; }
	//@备注 Value，设置参数的值。
	//@参数 变体数据 
	//@别名 置值(变体数据)
	/*virtual*/ HRESULT set_Value(/*[in]*/ VARIANT pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_Value(pVal); return _result; }
	//@备注 Format，获取将参数值转换为显示文本时所应用的格式文字串。
	// 本属只对性整数、浮点数、日期时间类型的参数生成输出显示文本的格式串。
	//@别名 取格式()
	/*virtual*/ CXText get_Format(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRParameter*)m_ptr.p)->get_Format(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Format，设置将参数值转换为显示文本时所应用的格式文字串。
	// 本属性只对整数、浮点数、日期时间类型的参数生成输出显示文本的格式串。
	//@参数 格式文本 
	//@别名 置格式(格式文本)
	/*virtual*/ HRESULT set_Format(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_Format((BSTR)pVal); return _result; }
	//@备注 AsInteger，获取参数整数值，只有当为整数类型参数时才能成功使用此属性。
	//@别名 取整数值()
	/*virtual*/ long get_AsInteger(/*[out][retVal] long* pVal*/){long _result=0; ((IGRParameter*)m_ptr.p)->get_AsInteger(&_result); return _result; }
	//@备注 AsInteger，设置参数整数值，只有当为整数类型参数时才能成功使用此属性。
	//@参数 整数值 
	//@别名 置整数值(整数值)
	/*virtual*/ HRESULT set_AsInteger(/*[in]*/ long pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_AsInteger(pVal); return _result; }
	//@备注 AsFloat，获取参数浮点数值，只有当为浮点数类型参数时才能成功使用此属性。
	//@别名 取浮点数值()
	/*virtual*/ double get_AsFloat(/*[out][retVal] double* pVal*/){double _result=0; ((IGRParameter*)m_ptr.p)->get_AsFloat(&_result); return _result; }
	//@备注 AsFloat，设置参数浮点数值，只有当为浮点数类型参数时才能成功使用此属性。
	//@参数 小数值 
	//@别名 置浮点数值(小数值)
	/*virtual*/ HRESULT set_AsFloat(/*[in]*/ double pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_AsFloat(pVal); return _result; }
	//@备注 AsString，获取参数文本值，只有当为文本类型参数时才能成功使用此属性。
	//@别名 取字符值()
	/*virtual*/ CXText get_AsString(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRParameter*)m_ptr.p)->get_AsString(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 AsString，设置参数文本值，只有当为文本类型参数时才能成功使用此属性。
	//@参数 文本 
	//@别名 置字符值(文本)
	/*virtual*/ HRESULT set_AsString(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_AsString((BSTR)pVal); return _result; }
	//@备注 AsBoolean，获取参数布尔值，只有当为布尔类型参数时才能成功使用此属性。
	//@别名 取逻辑值()
	/*virtual*/ BOOL get_AsBoolean(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRParameter*)m_ptr.p)->get_AsBoolean(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AsBoolean，设置参数布尔值，只有当为布尔类型参数时才能成功使用此属性。
	//@参数 逻辑值 
	//@别名 置逻辑值(逻辑值)
	/*virtual*/ HRESULT set_AsBoolean(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_AsBoolean(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AsDateTime，获取参数日期时间值，只有当为日期时间类型参数时才能成功使用此属性。
	//@别名 取日期时间值()
	/*virtual*/ DATE get_AsDateTime(/*[out][retVal] DATE* pVal*/){DATE _result=0; ((IGRParameter*)m_ptr.p)->get_AsDateTime(&_result); return _result; }
	//@备注 AsDateTime，设置参数日期时间值，只有当为日期时间类型参数时才能成功使用此属性。
	//@参数 小数值 
	//@别名 置日期时间值(小数值)
	/*virtual*/ HRESULT set_AsDateTime(/*[in]*/ DATE pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_AsDateTime(pVal); return _result; }
	//@备注 DisplayText，参数的输出显示文本。
	//@别名 取显示文字()
	/*virtual*/ CXText get_DisplayText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRParameter*)m_ptr.p)->get_DisplayText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 IsNull，获取参数的值是否为空标志。
	//@别名 取是否空值()
	/*virtual*/ BOOL get_IsNull(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRParameter*)m_ptr.p)->get_IsNull(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Clear，将参数的值清理掉，调用本方法后，参数状态为空。
	//@别名 清空()
	/*virtual*/ HRESULT Clear(){ HRESULT _result = ((IGRParameter*)m_ptr.p)->raw_Clear(); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRParameter*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRParameter*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ReportHeaders，集合对象，报表主对象的所有报表头的集合对象。
//@别名 报表头集合
class CIGRReportHeaders : public CXComObj /*IDispatch*/
{
public:
	CIGRReportHeaders(){};
	CIGRReportHeaders(IGRReportHeaders* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRReportHeaders* GetPtr(){ return ((IGRReportHeaders*)m_ptr.p); }
	/*virtual*/ class CIGRReportHeader get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRReportHeader** ppItem*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRReportHeaders*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有报表头的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRReportHeaders*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个报表头并返回新增报表头的接口引用。
	//@返回 新增报表头的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRReportHeader Add(/*[out][retVal] class CIGRReportHeader** ppItem*/);
	//@备注 Remove，根据报表头的顺序号将报表头移除。
	//@参数 序号 指定报表头的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRReportHeaders*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部报表头。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRReportHeaders*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据报表头的名称取得其顺序号，如果不存在与名称匹配的报表头，则返回值为-1。
	// 报表头的名称不区分字母的大小写。
	//@参数 名称 指定报表头的名称。
	//@返回 如果存在名称匹配的报表头，返回报表头的顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRReportHeaders*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的报表头对象，序号从1开始。
	//@参数 序号 指定报表头对象在集合中的序号，从1开始。
	//@返回 获取到的报表头对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRReportHeader ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRReportHeader** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数报表头的顺序。
	//@参数 序号 指定报表头的序号，序号从1开始。
	//@参数 新顺序号 报表头在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRReportHeaders*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 ReportSection，基类，报表头与报表尾的基接口。表示报表头与报表尾的共同属性与方法。
//@别名 报表节
class CIGRReportSection : public CIGRSection
{
public:
	CIGRReportSection(){};
	CIGRReportSection(IGRReportSection* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRReportSection* GetPtr(){ return ((IGRReportSection*)m_ptr.p); }
	//@备注 NewPage，指定新页的产生方式。
	//@别名 取换新页()
	/*virtual*/ GRNewPageStyle get_NewPage(/*[out][retVal] GRNewPageStyle* pVal*/){GRNewPageStyle _result; ((IGRReportSection*)m_ptr.p)->get_NewPage(&_result); return _result; }
	//@备注 NewPage，指定新页的产生方式。
	//@参数 换新页方式枚举值 
	//@别名 置换新页(换新页方式枚举值)
	/*virtual*/ HRESULT set_NewPage(/*[in]*/ GRNewPageStyle pVal){ HRESULT _result = ((IGRReportSection*)m_ptr.p)->put_NewPage(pVal); return _result; }
	//@备注 RepeatOnPage，打印输出时，是否在每页中重复显示的标志。
	//@别名 取每页重复打印()
	/*virtual*/ BOOL get_RepeatOnPage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRReportSection*)m_ptr.p)->get_RepeatOnPage(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RepeatOnPage，打印输出时，是否在每页中重复显示的标志。
	//@参数 逻辑值 
	//@别名 置每页重复打印(逻辑值)
	/*virtual*/ HRESULT set_RepeatOnPage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRReportSection*)m_ptr.p)->put_RepeatOnPage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CenterWithDetailGrid，指定本报表节是否跟随明细网格的居中显示而居中显示。
	//@别名 取跟随明细网格居中()
	/*virtual*/ BOOL get_CenterWithDetailGrid(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRReportSection*)m_ptr.p)->get_CenterWithDetailGrid(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CenterWithDetailGrid，指定本报表节是否跟随明细网格的居中显示而居中显示。
	//@参数 逻辑值 
	//@别名 置跟随明细网格居中(逻辑值)
	/*virtual*/ HRESULT set_CenterWithDetailGrid(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRReportSection*)m_ptr.p)->put_CenterWithDetailGrid(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 ReportHeader，报表头在打印生成时，如果不选择每页重复输出，则只在报表的开始生成时输出一次；在屏幕查询显示时，显示在明细网格之上。
// 一个报表可以定义多个报表头，在一般情况下我们只需定义一个报表头就可以了。
// 在报表头中一般定义报表的标题，报表标识信息，徽标图像及其它只需在报表开始时显示一次的信息。
//@别名 报表头
class CIGRReportHeader : public CIGRReportSection
{
public:
	CIGRReportHeader(){};
	CIGRReportHeader(IGRReportHeader* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRReportHeader* GetPtr(){ return ((IGRReportHeader*)m_ptr.p); }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRReportHeader*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRReportHeader*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ReportFooters，集合对象，报表主对象的所有报表尾的集合对象。
//@别名 报表尾集合
class CIGRReportFooters : public CXComObj /*IDispatch*/
{
public:
	CIGRReportFooters(){};
	CIGRReportFooters(IGRReportFooters* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRReportFooters* GetPtr(){ return ((IGRReportFooters*)m_ptr.p); }
	/*virtual*/ class CIGRReportFooter get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRReportFooter** ppItem*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRReportFooters*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有报表尾的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRReportFooters*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个报表尾并返回新增报表尾的接口引用。
	//@返回 新增报表尾的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRReportFooter Add(/*[out][retVal] class CIGRReportFooter** ppItem*/);
	//@备注 Remove，根据报表尾的顺序号将报表尾移除。
	//@参数 序号 指定报表尾的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRReportFooters*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部报表尾。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRReportFooters*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据报表尾的名称取得其顺序号，如果不存在与名称匹配的报表尾，则返回值为-1。
	// 报表尾的名称不区分字母的大小写。
	//@参数 名称 指定报表尾的名称。
	//@返回 如果存在名称匹配的报表尾，返回报表尾的顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRReportFooters*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的报表尾对象，序号从1开始。
	//@参数 序号 指定报表尾对象在集合中的序号，从1开始。
	//@返回 获取到的报表尾对象
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRReportFooter ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRReportFooter** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数报表尾的顺序。
	//@参数 序号 指定报表尾的序号，序号从1开始。 
	//@参数 新顺序号 报表尾在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRReportFooters*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 ReportFooter，表示报表的报表尾，报表尾一般显示在报表的最后面。
// 报表尾在打印生成时，如果不选择每页重复输出，则只在报表的最后输出一次；在屏幕查询显示时，显示在明细网格之下。
// 一个报表可以定义多个报表尾，在一般情况下我们只需定义一个报表尾就可以了。
// 在报表尾中一般定义报表的统计信息及其它只需在报表结束时显示一次的信息。
//@别名 报表尾
class CIGRReportFooter : public CIGRReportSection
{
public:
	CIGRReportFooter(){};
	CIGRReportFooter(IGRReportFooter* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRReportFooter* GetPtr(){ return ((IGRReportFooter*)m_ptr.p); }
	//@备注 PrintAtBottom，是否将本节输出在页面底部标志。
	//@别名 取打印在页底()
	/*virtual*/ BOOL get_PrintAtBottom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRReportFooter*)m_ptr.p)->get_PrintAtBottom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAtBottom，是否将本节输出在页面底部标志。
	//@参数 逻辑值 
	//@别名 置打印在页底(逻辑值)
	/*virtual*/ HRESULT set_PrintAtBottom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRReportFooter*)m_ptr.p)->put_PrintAtBottom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankRowExclude，是否将报表尾行从明细网格的空白行计数中排除。
	// 当明细网格设定追加空白行且指定了每页行数，本属性指定是否将本报表尾行作为本页中的一行对待。
	// 假设每页指定输出10行，数据行已输出6行，如果本属性为FALSE，则补充3行空白行，反之补充4行空白行。
	//@别名 取追加空白行排除()
	/*virtual*/ BOOL get_AppendBlankRowExclude(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRReportFooter*)m_ptr.p)->get_AppendBlankRowExclude(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AppendBlankRowExclude，是否将报表尾行从明细网格的空白行计数中排除。
	// 当明细网格设定追加空白行且指定了每页行数，本属性指定是否将本报表尾行作为本页中的一行对待。
	// 假设每页指定输出10行，数据行已输出6行，如果本属性为FALSE，则补充3行空白行，反之补充4行空白行。
	//@参数 逻辑值 
	//@别名 置追加空白行排除(逻辑值)
	/*virtual*/ HRESULT set_AppendBlankRowExclude(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRReportFooter*)m_ptr.p)->put_AppendBlankRowExclude(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRReportFooter*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRReportFooter*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ImageList，集合对象，管理在整个报表对象中共享使用的图像数据集合。
// 图像框通过指定引用的图像序号来显示某个共享的图像，图像序号从1开始。
//@别名 图像集合
class CIGRImageList : public CIGRObject
{
public:
	CIGRImageList(){};
	CIGRImageList(IGRImageList* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRImageList* GetPtr(){ return ((IGRImageList*)m_ptr.p); }
	/*virtual*/ class CIGRPicture get_Item(/*[in]*/ long Index/*, [out][retVal] class CIGRPicture** ppPicture*/);
	//@备注 Count，获取当前图像集合中图像个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRImageList*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，根据图像对象引用增加该图像到图像集合中。
	//@参数 报表图片对象 准备添加的图像对象引用。
	//@返回 指定新增图像的序号。
	//@别名 增加(报表图片对象)
	/*virtual*/ HRESULT Add(/*[in]*/ class CIGRPicture* pPicture);
	//@备注 AddFromFile，根据图像文件路径名将该图像添加到图像集合中。
	//@参数 文件名 图像文件路径名或图像数据URL。
	//@返回 指定新增图像的序号。
	//@别名 从文件增加图片(文件名)
	/*virtual*/ HRESULT AddFromFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRImageList*)m_ptr.p)->raw_AddFromFile((BSTR)PathFile); return _result; }
	//@备注 AddFromBinary，从二进制数据对象中载入图像到图像集合中。
	//@参数 二进制数据对象 拥有图像数据的二进制对象。
	//@返回 指定新增图像的序号。
	//@别名 从二进制增加图片(二进制数据对象)
	/*virtual*/ HRESULT AddFromBinary(/*[in]*/ class CIGRBinaryObject* pBinaryObject);
	//@备注 Remove，从图像集合中去除一个图像。
	//@参数 序号 图像序号，从1开始。
	//@别名 删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ long Index){ HRESULT _result = ((IGRImageList*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，将图像集合中的图像全部清除掉。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRImageList*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 AddFromMemory，将内存缓冲区中的图像添加到图像集合中。
	//@参数 数据指针 pBuffer，指定添加图像数据的内存地址。
	//@参数 数据尺寸 BytesCount，指定添加图像数据的字节数。
	//@返回 指定新增图像的序号。
	//@别名 从内存增加图片(数据指针,数据尺寸)
	/*virtual*/ HRESULT AddFromMemory(/*[in]*/ unsigned char* pData, /*, [in]*/ long ByteCount){ HRESULT _result = ((IGRImageList*)m_ptr.p)->raw_AddFromMemory(pData, ByteCount); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRImageList*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRImageList*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Printer，表示打印机与纸张。定义获取与设置打印机与纸张信息的属性与方法。
//@别名 报表打印机
class CIGRPrinter : public CXComObj /*IDispatch*/
{
public:
	CIGRPrinter(){};
	CIGRPrinter(IGRPrinter* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPrinter* GetPtr(){ return ((IGRPrinter*)m_ptr.p); }
	//@备注 PrintRangeType，指定打印输出选定的页范围。
	//@别名 取打印范围类型()
	/*virtual*/ GRPrintRangeType get_PrintRangeType(/*[out][retVal] GRPrintRangeType* pVal*/){GRPrintRangeType _result; ((IGRPrinter*)m_ptr.p)->get_PrintRangeType(&_result); return _result; }
	//@备注 PrintRangeType，指定打印输出选定的页范围。
	//@参数 打印页范围类型枚举值 
	//@别名 置打印范围类型(打印页范围类型枚举值)
	/*virtual*/ HRESULT set_PrintRangeType(/*[in]*/ GRPrintRangeType pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintRangeType(pVal); return _result; }
	//@备注 PrintPageType，指定从选定的页范围中输出的页类型。
	//@别名 取打印页类型()
	/*virtual*/ GRPrintPageType get_PrintPageType(/*[out][retVal] GRPrintPageType* pVal*/){GRPrintPageType _result; ((IGRPrinter*)m_ptr.p)->get_PrintPageType(&_result); return _result; }
	//@备注 PrintPageType，指定从选定的页范围中输出的页类型。 
	//@参数 打印页面类型枚举值 
	//@别名 置打印页类型(打印页面类型枚举值)
	/*virtual*/ HRESULT set_PrintPageType(/*[in]*/ GRPrintPageType pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintPageType(pVal); return _result; }
	//@备注 SelectionPrintPages，用文本指定的页范围，仅当PrintRangeType为grprtSelectionPages时才有效。
	//@返回 范围文本为单页页号文本，如1、3、8；或有效的页区间文本，如1-5、6-10。可以指定多个页或页区间，中间用AssII字符‘,’隔开。
	//@别名 取打印页范围()
	/*virtual*/ CXText get_SelectionPrintPages(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPrinter*)m_ptr.p)->get_SelectionPrintPages(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SelectionPrintPages，用文本指定的页范围，仅当PrintRangeType为grprtSelectionPages时才有效。
	//@参数 打印范围 范围文本为单页页号文本，如1、3、8；或有效的页区间文本，如1-5、6-10。可以指定多个页或页区间，中间用AssII字符‘,’隔开。
	//@别名 置打印页范围(打印范围)
	/*virtual*/ HRESULT set_SelectionPrintPages(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_SelectionPrintPages((BSTR)pVal); return _result; }
	//@备注 PageCount，指示当前打印文档的总页数。
	//@别名 取页数()
	/*virtual*/ long get_PageCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_PageCount(&_result); return _result; }
	//@备注 PageCount，指示当前打印文档的总页数。
	//@参数 整数值 
	//@别名 置页数(整数值)
	/*virtual*/ HRESULT set_PageCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PageCount(pVal); return _result; }
	//@备注 CurPageNo，获取或设置当前打印页号。
	//@别名 取当前页号()
	/*virtual*/ long get_CurPageNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_CurPageNo(&_result); return _result; }
	//@备注 CurPageNo，获取或设置当前打印页号。
	//@参数 整数值 
	//@别名 置当前页号(整数值)
	/*virtual*/ HRESULT set_CurPageNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_CurPageNo(pVal); return _result; }
	//@备注 Copies，获取或设置要打印的文档份数。
	// Report.Printer.Copies = n;
	// 如上代码可以设置多份打印，但测试时无效，是因为当前打印机不支持多份打印。
	// 通常Windows系统中的虚拟打印机（如生成 .PDF 与 .WPS 文档的打印机）都是不支持多份打印。改为用真实的打印机进行测试就会有效果。
	//@别名 取打印份数()
	/*virtual*/ long get_Copies(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_Copies(&_result); return _result; }
	//@备注 Copies，获取或设置要打印的文档份数。
	// Report.Printer.Copies = n;
	// 如上代码可以设置多份打印，但测试时无效，是因为当前打印机不支持多份打印。
	// 通常Windows系统中的虚拟打印机（如生成 .PDF 与 .WPS 文档的打印机）都是不支持多份打印。改为用真实的打印机进行测试就会有效果。
	//@参数 整数值 
	//@别名 置打印份数(整数值)
	/*virtual*/ HRESULT set_Copies(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_Copies(pVal); return _result; }
	//@备注 Collate，指示打印文档是否逐份打印。
	//@别名 取逐份打印()
	/*virtual*/ BOOL get_Collate(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_Collate(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Collate，指示打印文档是否逐份打印。
	//@参数 逻辑值 
	//@别名 置逐份打印(逻辑值)
	/*virtual*/ HRESULT set_Collate(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_Collate(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Duplex，指示报表打印输出应用的双面打印模式。
	//@返回 0、默认； 1、单面打印； 3、双面水平打印； 2、双面垂直打印
	//@别名 取双面打印()
	/*virtual*/ GRDuplexKind get_Duplex(/*[out][retVal] GRDuplexKind* pVal*/){GRDuplexKind _result; ((IGRPrinter*)m_ptr.p)->get_Duplex(&_result); return _result; }
	//@备注 Duplex，指示报表打印输出应用的双面打印模式。
	//@参数 双面打印方式枚举值 0、默认； 1、单面打印； 3、双面水平打印； 2、双面垂直打印
	//@别名 置双面打印(双面打印方式枚举值)
	/*virtual*/ HRESULT set_Duplex(/*[in]*/ GRDuplexKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_Duplex(pVal); return _result; }
	//@备注 LeftMargin，页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取左边距()
	/*virtual*/ double get_LeftMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_LeftMargin(&_result); return _result; }
	//@备注 LeftMargin，页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置左边距(小数值)
	/*virtual*/ HRESULT set_LeftMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_LeftMargin(pVal); return _result; }
	//@备注 RightMargin，页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取右边距()
	/*virtual*/ double get_RightMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_RightMargin(&_result); return _result; }
	//@备注 RightMargin，页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置右边距(小数值)
	/*virtual*/ HRESULT set_RightMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_RightMargin(pVal); return _result; }
	//@备注 TopMargin，页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取上边距()
	/*virtual*/ double get_TopMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_TopMargin(&_result); return _result; }
	//@备注 TopMargin，页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置上边距(小数值)
	/*virtual*/ HRESULT set_TopMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_TopMargin(pVal); return _result; }
	//@备注 BottomMargin，页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取下边距()
	/*virtual*/ double get_BottomMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_BottomMargin(&_result); return _result; }
	//@备注 BottomMargin，页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置下边距(小数值)
	/*virtual*/ HRESULT set_BottomMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_BottomMargin(pVal); return _result; }
	//@备注 PaperWidth，指定报表所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取纸张宽度()
	/*virtual*/ double get_PaperWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_PaperWidth(&_result); return _result; }
	//@备注 PaperWidth，指定报表所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置纸张宽度(小数值)
	/*virtual*/ HRESULT set_PaperWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperWidth(pVal); return _result; }
	//@备注 PaperLength，指定报表所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取页面长度()
	/*virtual*/ double get_PaperLength(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_PaperLength(&_result); return _result; }
	//@备注 PaperLength，指定报表所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置页面长度(小数值)
	/*virtual*/ HRESULT set_PaperLength(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperLength(pVal); return _result; }
	//@备注 PaperOrientation，指定报表所定义的纸张方向：0、默认； 1、纵向； 2、横向
	//@别名 取纸张方向()
	/*virtual*/ GRPaperOrientation get_PaperOrientation(/*[out][retVal] GRPaperOrientation* pVal*/){GRPaperOrientation _result; ((IGRPrinter*)m_ptr.p)->get_PaperOrientation(&_result); return _result; }
	//@备注 PaperOrientation，指定报表所定义的纸张方向：0、默认； 1、纵向； 2、横向
	//@参数 纸张方向枚举值 0、默认； 1、纵向； 2、横向
	//@别名 置纸张方向(纸张方向枚举值)
	/*virtual*/ HRESULT set_PaperOrientation(/*[in]*/ GRPaperOrientation pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperOrientation(pVal); return _result; }
	//@备注 PaperSize，指定报表所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@别名 取纸张规格()
	/*virtual*/ long get_PaperSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_PaperSize(&_result); return _result; }
	//@备注 PaperSize，指定报表所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@参数 标准纸张类型枚举值 
	//@别名 置纸张规格(标准纸张类型枚举值)
	/*virtual*/ HRESULT set_PaperSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperSize(pVal); return _result; }
	/*virtual*/ GRPaperKind get_PaperKind(/*[out][retVal] GRPaperKind* pVal*/){GRPaperKind _result; ((IGRPrinter*)m_ptr.p)->get_PaperKind(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperKind(/*[in]*/ GRPaperKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperKind(pVal); return _result; }
	//@备注 PaperName，指定报表所定义的纸张名称。
	//@别名 取纸张名称()
	/*virtual*/ CXText get_PaperName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPrinter*)m_ptr.p)->get_PaperName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PaperName，指定报表所定义的纸张名称。
	//@参数 纸张名称 
	//@别名 置纸张名称(纸张名称)
	/*virtual*/ HRESULT set_PaperName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperName((BSTR)pVal); return _result; }
	//@备注 PrinterName，指定默认打印机的名称。
	// 如果专门指定了此属性值，报表在运行时将把此打印机作为默认打印机。
	//@别名 取打印机名称()
	/*virtual*/ CXText get_PrinterName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPrinter*)m_ptr.p)->get_PrinterName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PrinterName，指定默认打印机的名称。
	// 如果专门指定了此属性值，报表在运行时将把此打印机作为默认打印机。
	//@参数 纸张名称 
	//@别名 置打印机名称(纸张名称)
	/*virtual*/ HRESULT set_PrinterName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrinterName((BSTR)pVal); return _result; }
	//@备注 PaperSource，指定打印机的纸张来源。
	// GRPaperSourceKind 枚举 中未能全部列出可能的纸张来源，根据枚举的字面描述，也许没法将其与纸盒对应起来。
	// 所以请参考帮助“开发指南->报表打印->打印参数设置”中的说明 获取正确的 PaperSource 属性值后再用于设置是正确的做法。
	// 对于强类型编译编程语言，枚举中不存在的属性值，可以用强制转换解决编译错误问题。 
	//@别名 取纸张来源()
	/*virtual*/ GRPaperSourceKind get_PaperSource(/*[out][retVal] GRPaperSourceKind* pVal*/){GRPaperSourceKind _result; ((IGRPrinter*)m_ptr.p)->get_PaperSource(&_result); return _result; }
	//@备注 PaperSource，指定打印机的纸张来源。
	// GRPaperSourceKind 枚举 中未能全部列出可能的纸张来源，根据枚举的字面描述，也许没法将其与纸盒对应起来。
	// 所以请参考帮助“开发指南->报表打印->打印参数设置”中的说明 获取正确的 PaperSource 属性值后再用于设置是正确的做法。
	// 对于强类型编译编程语言，枚举中不存在的属性值，可以用强制转换解决编译错误问题。  
	//@参数 纸张来源枚举值 
	//@别名 置纸张来源(纸张来源枚举值)
	/*virtual*/ HRESULT set_PaperSource(/*[in]*/ GRPaperSourceKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PaperSource(pVal); return _result; }
	//@备注 PrintOffsetX，指示报表的输出位置在水平方向上的偏移量，以报表的计量单位表示，向右为正，向左为负。
	//@别名 取打印水平偏移()
	/*virtual*/ double get_PrintOffsetX(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_PrintOffsetX(&_result); return _result; }
	//@备注 PrintOffsetX，指示报表的输出位置在水平方向上的偏移量，以报表的计量单位表示，向右为正，向左为负。
	//@参数 小数值 
	//@别名 置打印水平偏移(小数值)
	/*virtual*/ HRESULT set_PrintOffsetX(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintOffsetX(pVal); return _result; }
	//@备注 PrintOffsetY，指示报表的输出位置在垂直方向上的偏移量，以报表的计量单位表示，向下为正，向上为负。
	//@别名 取打印垂直偏移()
	/*virtual*/ double get_PrintOffsetY(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_PrintOffsetY(&_result); return _result; }
	//@备注 PrintOffsetY，指示报表的输出位置在垂直方向上的偏移量，以报表的计量单位表示，向下为正，向上为负。
	//@参数 小数值 
	//@别名 置打印垂直偏移(小数值)
	/*virtual*/ HRESULT set_PrintOffsetY(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintOffsetY(pVal); return _result; }
	//@备注 PrintOffsetSaveToLocal，指示是否将打印偏移量保存在客户端本地机器上。
	// 设置此属性为TRUE，此报表每次打印时，将把其设置的打印偏移量保存在本地电脑上，在以后再次打印此报表时，保存的打印偏移量将会自动应用上，这样就可以做到一次设置好的打印偏移量后续持续使用。
	// 不同电脑分别保存自己的打印偏移量，同一电脑中根据打印机名称为不同的打印机保存各自的打印偏移量，这样就实现了同一报表用不同的打印机打印时可以应用各自的打印偏移设置。
	// 打印偏移保存在本地电脑的功能对票据打印(套打)非常有用，开发者只要在设计时勾选开启此功能，不用编写任何代码。
	//@别名 取本地保存偏移设置()
	/*virtual*/ BOOL get_PrintOffsetSaveToLocal(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_PrintOffsetSaveToLocal(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintOffsetSaveToLocal，指示是否将打印偏移量保存在客户端本地机器上。
	// 设置此属性为TRUE，此报表每次打印时，将把其设置的打印偏移量保存在本地电脑上，在以后再次打印此报表时，保存的打印偏移量将会自动应用上，这样就可以做到一次设置好的打印偏移量后续持续使用。
	// 不同电脑分别保存自己的打印偏移量，同一电脑中根据打印机名称为不同的打印机保存各自的打印偏移量，这样就实现了同一报表用不同的打印机打印时可以应用各自的打印偏移设置。
	// 打印偏移保存在本地电脑的功能对票据打印(套打)非常有用，开发者只要在设计时勾选开启此功能，不用编写任何代码。
	//@参数 逻辑值 
	//@别名 置本地保存偏移设置(逻辑值)
	/*virtual*/ HRESULT set_PrintOffsetSaveToLocal(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintOffsetSaveToLocal(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SheetPages，指定在打印输出纸张上每页输出的页面版数
	// 通常在报表的 PrintBegin 事件中用代码设置与多版面打印相关的属性，下面代码就是用 JavaScript 响应 PrintBegin 事件的示例：
	//     Report.Printer.PrintRangeType = 3; //grprtSelectionPages 指定的页范围
	//     Report.Printer.SelectionPrintPages = \"1,8,2,4,3,6,4,5\"; //指定要打印的页，及输出顺序
	//     Report.Printer.SheetPages = 2;     //每页版面数为2
	//     Report.Printer.SheetPaperSize = 8; //指定版面的实际输出为A3纸张
	//@返回 1、每页排1版； 2、每页排2版； 4、每页排4版； 6、每页排6版； 8、每页排8版； 16、每页排16版
	//@别名 取每页版数()
	/*virtual*/ GRSheetPages get_SheetPages(/*[out][retVal] GRSheetPages* pVal*/){GRSheetPages _result; ((IGRPrinter*)m_ptr.p)->get_SheetPages(&_result); return _result; }
	//@备注 SheetPages，指定在打印输出纸张上每页输出的页面版数
	// 通常在报表的 PrintBegin 事件中用代码设置与多版面打印相关的属性，下面代码就是用 JavaScript 响应 PrintBegin 事件的示例：
	//     Report.Printer.PrintRangeType = 3; //grprtSelectionPages 指定的页范围
	//     Report.Printer.SelectionPrintPages = \"1,8,2,4,3,6,4,5\"; //指定要打印的页，及输出顺序
	//     Report.Printer.SheetPages = 2;     //每页版面数为2
	//     Report.Printer.SheetPaperSize = 8; //指定版面的实际输出为A3纸张
	//@参数 每页版数枚举值 1、每页排1版； 2、每页排2版； 4、每页排4版； 6、每页排6版； 8、每页排8版； 16、每页排16版
	//@别名 置每页版数(每页版数枚举值)
	/*virtual*/ HRESULT set_SheetPages(/*[in]*/ GRSheetPages pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_SheetPages(pVal); return _result; }
	//@备注 SheetPaperSize，指定实际输出纸张的类型，如果为0，则按报表生成的纸张类型进行打印，这种方式也是默认的方式。
	//@返回 标准纸张类型枚举，其中Custom为256，代表自定义纸张，但定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@别名 取按纸张规格缩放()
	/*virtual*/ long get_SheetPaperSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_SheetPaperSize(&_result); return _result; }
	//@备注 SheetPaperSize，指定实际输出纸张的类型，如果为0，则按报表生成的纸张类型进行打印，这种方式也是默认的方式。
	//@参数 纸张规格 标准纸张类型枚举，其中Custom为256，代表自定义纸张，但定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@别名 置按纸张规格缩放(纸张规格)
	/*virtual*/ HRESULT set_SheetPaperSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_SheetPaperSize(pVal); return _result; }
	//@备注 CanCollate，指示当前打印机是否支持逐份打印。
	//@别名 取支持逐份打印()
	/*virtual*/ BOOL get_CanCollate(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_CanCollate(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanDuplex，指示当前打印机是否支持双面打印。
	//@别名 取支持双面打印()
	/*virtual*/ BOOL get_CanDuplex(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_CanDuplex(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Online，指示当前打印机是否处于开机在线状态。
	//@别名 取联机状态()
	/*virtual*/ BOOL get_Online(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_Online(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SupportCustomPaper，指示当前打印机是否支持自定义纸张打印。
	//@别名 取支持自定义纸张()
	/*virtual*/ BOOL get_SupportCustomPaper(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->get_SupportCustomPaper(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DesignLeftMargin，指定设计报表时所定义的页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计左边距()
	/*virtual*/ double get_DesignLeftMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignLeftMargin(&_result); return _result; }
	//@备注 DesignLeftMargin，指定设计报表时所定义的页面的左边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计左边距(小数值)
	/*virtual*/ HRESULT set_DesignLeftMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignLeftMargin(pVal); return _result; }
	//@备注 DesignRightMargin，指定设计报表时所定义的页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计右边距()
	/*virtual*/ double get_DesignRightMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignRightMargin(&_result); return _result; }
	//@备注 DesignRightMargin，指定设计报表时所定义的页面的右边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计右边距(小数值)
	/*virtual*/ HRESULT set_DesignRightMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignRightMargin(pVal); return _result; }
	//@备注 DesignTopMargin，指定设计报表时所定义的页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计上边距()
	/*virtual*/ double get_DesignTopMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignTopMargin(&_result); return _result; }
	//@备注 DesignTopMargin，指定设计报表时所定义的页面的上边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计上边距(小数值)
	/*virtual*/ HRESULT set_DesignTopMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignTopMargin(pVal); return _result; }
	//@备注 DesignBottomMargin，指定设计报表时所定义的页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计下边距()
	/*virtual*/ double get_DesignBottomMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignBottomMargin(&_result); return _result; }
	//@备注 DesignBottomMargin，指定设计报表时所定义的页面的下边距。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计下边距(小数值)
	/*virtual*/ HRESULT set_DesignBottomMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignBottomMargin(pVal); return _result; }
	//@备注 DesignPaperWidth，指定设计报表时所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计纸张宽度()
	/*virtual*/ double get_DesignPaperWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignPaperWidth(&_result); return _result; }
	//@备注 DesignPaperWidth，指定设计报表时所定义的页面宽度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计纸张宽度(小数值)
	/*virtual*/ HRESULT set_DesignPaperWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperWidth(pVal); return _result; }
	//@备注 DesignPaperLength，指定设计报表时所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值2.5
	//@别名 取设计纸张长度()
	/*virtual*/ double get_DesignPaperLength(/*[out][retVal] double* pVal*/){double _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignPaperLength(&_result); return _result; }
	//@备注 DesignPaperLength，指定设计报表时所定义的页面长度，仅自定义纸张设置此属性有效。以报表使用的计量单位表示属性值。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值2.5
	//@别名 置设计纸张长度(小数值)
	/*virtual*/ HRESULT set_DesignPaperLength(/*[in]*/ double pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperLength(pVal); return _result; }
	//@备注 DesignPaperOrientation，指定设计报表时所定义的纸张方向：0、默认； 1、纵向； 2、横向
	//@别名 取设计纸张方向()
	/*virtual*/ GRPaperOrientation get_DesignPaperOrientation(/*[out][retVal] GRPaperOrientation* pVal*/){GRPaperOrientation _result; ((IGRPrinter*)m_ptr.p)->get_DesignPaperOrientation(&_result); return _result; }
	//@备注 DesignPaperOrientation，指定设计报表时所定义的纸张方向：0、默认； 1、纵向； 2、横向
	//@参数 纸张方向枚举值 0、默认； 1、纵向； 2、横向
	//@别名 置设计纸张方向(纸张方向枚举值)
	/*virtual*/ HRESULT set_DesignPaperOrientation(/*[in]*/ GRPaperOrientation pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperOrientation(pVal); return _result; }
	/*virtual*/ GRPaperSourceKind get_DesignPaperSource(/*[out][retVal] GRPaperSourceKind* pVal*/){GRPaperSourceKind _result; ((IGRPrinter*)m_ptr.p)->get_DesignPaperSource(&_result); return _result; }
	/*virtual*/ HRESULT set_DesignPaperSource(/*[in]*/ GRPaperSourceKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperSource(pVal); return _result; }
	/*virtual*/ GRCollateKind get_DesignPrintCollate(/*[out][retVal] GRCollateKind* pVal*/){GRCollateKind _result; ((IGRPrinter*)m_ptr.p)->get_DesignPrintCollate(&_result); return _result; }
	/*virtual*/ HRESULT set_DesignPrintCollate(/*[in]*/ GRCollateKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPrintCollate(pVal); return _result; }
	/*virtual*/ GRDuplexKind get_DesignPrintDuplex(/*[out][retVal] GRDuplexKind* pVal*/){GRDuplexKind _result; ((IGRPrinter*)m_ptr.p)->get_DesignPrintDuplex(&_result); return _result; }
	/*virtual*/ HRESULT set_DesignPrintDuplex(/*[in]*/ GRDuplexKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPrintDuplex(pVal); return _result; }
	//@备注 DesignPaperName，指定设计报表时所定义的纸张名称。
	//@别名 取设计纸张名称()
	/*virtual*/ CXText get_DesignPaperName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPrinter*)m_ptr.p)->get_DesignPaperName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DesignPaperName，指定设计报表时所定义的纸张名称。
	//@参数 纸张名称 
	//@别名 置设计纸张名称(纸张名称)
	/*virtual*/ HRESULT set_DesignPaperName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperName((BSTR)pVal); return _result; }
	//@备注 DesignPaperSize，指定设计报表时所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@别名 取设计纸张规格()
	/*virtual*/ long get_DesignPaperSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrinter*)m_ptr.p)->get_DesignPaperSize(&_result); return _result; }
	//@备注 DesignPaperSize，指定设计报表时所定义的纸张大小代号。
	// 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。其中256代表自定义纸张，当定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	//@参数 标准纸张类型枚举值 
	//@别名 置设计纸张规格(标准纸张类型枚举值)
	/*virtual*/ HRESULT set_DesignPaperSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperSize(pVal); return _result; }
	/*virtual*/ GRPaperKind get_DesignPaperKind(/*[out][retVal] GRPaperKind* pVal*/){GRPaperKind _result; ((IGRPrinter*)m_ptr.p)->get_DesignPaperKind(&_result); return _result; }
	/*virtual*/ HRESULT set_DesignPaperKind(/*[in]*/ GRPaperKind pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPaperKind(pVal); return _result; }
	//@备注 DesignPrinterName，在设计时指定默认打印机的名称。
	// 如果专门指定了此属性值，报表在运行时将把此打印机作为默认打印机。
	//@别名 取设计打印机名称()
	/*virtual*/ CXText get_DesignPrinterName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRPrinter*)m_ptr.p)->get_DesignPrinterName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DesignPrinterName，在设计时指定默认打印机的名称。
	// 如果专门指定了此属性值，报表在运行时将把此打印机作为默认打印机。
	//@参数 纸张名称 
	//@别名 置设计打印机名称(纸张名称)
	/*virtual*/ HRESULT set_DesignPrinterName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_DesignPrinterName((BSTR)pVal); return _result; }
	//@备注 PrintDialog，显示打印对话框。
	// 如果成功显示打印对会框，返回真，否则返回假。
	//@别名 打印机对话框()
	/*virtual*/ BOOL PrintDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->raw_PrintDialog(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrinterSetupDialog，显示打印机设置对话框。
	// 如果成功显示打印机对会框，返回真，否则返回假。
	//@别名 打印机设置对话框()
	/*virtual*/ BOOL PrinterSetupDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->raw_PrinterSetupDialog(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PageSetupDialog，显示页面设置对话框。
	// 如果成功显示页面设置对会框，返回真，否则返回假。
	//@别名 页面设置对话框()
	/*virtual*/ BOOL PageSetupDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRPrinter*)m_ptr.p)->raw_PageSetupDialog(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT _OpenPrinter(){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->raw__OpenPrinter(); return _result; }
	/*virtual*/ HRESULT _ClosePrinter(){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->raw__ClosePrinter(); return _result; }
	//@备注 PrintRotation，指定打印输出时旋转的角度。
	// 如果指定了旋转角度，报表在打印预览显示时还是按可阅读的正常方式显示，但打印输出时将按指定角度进行旋转后输出，旋转方向为顺时针。
	//@返回 本属性默认为不旋转。0：不旋转；1：旋转90度；2：旋转180度；3：旋转270度
	//@别名 取打印旋转()
	/*virtual*/ GRDrawRotation get_PrintRotation(/*[out][retVal] GRDrawRotation* pVal*/){GRDrawRotation _result; ((IGRPrinter*)m_ptr.p)->get_PrintRotation(&_result); return _result; }
	//@备注 PrintRotation，指定打印输出时旋转的角度。
	// 如果指定了旋转角度，报表在打印预览显示时还是按可阅读的正常方式显示，但打印输出时将按指定角度进行旋转后输出，旋转方向为顺时针。
	//@参数 打印旋转枚举值 0：不旋转；1：旋转90度；2：旋转180度；3：旋转270度
	//@别名 置打印旋转(打印旋转枚举值)
	/*virtual*/ HRESULT set_PrintRotation(/*[in]*/ GRDrawRotation pVal){ HRESULT _result = ((IGRPrinter*)m_ptr.p)->put_PrintRotation(pVal); return _result; }

};
//@备注 Graphics，应用工具，实现在部件框中自绘输出显示的功能接口，当部件框为自绘部件框时，调用本接口的方法在部件框中实现输出显示。
//@别名 绘图接口
class CIGRGraphics : public CXComObj /*IDispatch*/
{
public:
	CIGRGraphics(){};
	CIGRGraphics(IGRGraphics* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGraphics* GetPtr(){ return ((IGRGraphics*)m_ptr.p); }
	//@备注 MoveTo，设定画笔的起点位置。
	//@参数 左 指定位置X。
	//@参数 上 指定位置Y。
	//@别名 画笔起点(左,上)
	/*virtual*/ HRESULT MoveTo(/*[in]*/ double x, /*, [in]*/ double y){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_MoveTo(x, y); return _result; }
	//@备注 LineTo，从当前起点位置画直线到指定的位置。
	//@参数 左 指定位置X。
	//@参数 上 指定位置Y。 
	//@别名 画线到(左,上)
	/*virtual*/ HRESULT LineTo(/*[in]*/ double x, /*, [in]*/ double y){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_LineTo(x, y); return _result; }
	//@备注 FillRect，用指定的颜色填充矩形区域。
	//@参数 左 指定输出左上角的位置X。 
	//@参数 上 指定输出左上角的位置Y。 
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 高度 指定输出区域的高度。 
	//@参数 填充颜色值 指定填充颜色。
	//@别名 画填充矩形(左,上,宽度,高度,填充颜色值)
	/*virtual*/ HRESULT FillRect(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ OLE_COLOR FillColor){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_FillRect(x, y, Width, Height, FillColor); return _result; }
	//@备注 DrawPixel，在指定位置画出一个屏幕像素点。
	//@参数 x X位置。 
	//@参数 y Y位置。 
	//@参数 颜色值 颜色。 
	//@别名 绘制像素点(x,y,颜色值)
	/*virtual*/ HRESULT DrawPixel(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ OLE_COLOR Color){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_DrawPixel(x, y, Color); return _result; }
	//@备注 Rectangle，按照指定的矩形区域画出矩形。
	//@参数 左 指定矩形的左端位置。 
	//@参数 上 指定矩形的上端位置。 
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 高度 指定输出区域的高度。 
	//@参数 背景填充 指定是否进行背景填充。
	//@别名 画矩形(左,上,宽度,高度,背景填充)
	/*virtual*/ HRESULT Rectangle(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ BOOL ToFill){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_Rectangle(x, y, Width, Height, ToFill? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 RoundRect，在指定区域上绘出圆角矩形。
	//@参数 左 指定输出左上角的位置X。
	//@参数 上 指定输出左上角的位置Y。 
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 高度 指定输出区域的高度。 
	//@参数 椭圆宽度 圆角矩形框的圆角椭圆宽度，以屏幕像素为单位。 
	//@参数 椭圆高度 圆角矩形框的圆角椭圆高度，以屏幕像素为单位。 
	//@参数 背景填充 指定是否进行背景填充。 
	//@别名 画圆角矩形(左,上,宽度,高度,椭圆宽度,椭圆高度,背景填充)
	/*virtual*/ HRESULT RoundRect(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ long cornerx, /*, [in]*/ long cornery, /*, [in]*/ BOOL ToFill){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_RoundRect(x, y, Width, Height, cornerx, cornery, ToFill? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Ellipse，按照指定的矩形区域画出椭圆。
	//@参数 左 指定输出左上角的位置X。 
	//@参数 上 指定输出左上角的位置Y。
	//@参数 宽度 指定输出区域的宽度。
	//@参数 高度 指定输出区域的高度。 
	//@参数 背景填充 指定是否进行背景填充。
	//@别名 画椭圆(左,上,宽度,高度,背景填充)
	/*virtual*/ HRESULT Ellipse(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ BOOL ToFill){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_Ellipse(x, y, Width, Height, ToFill? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Pie，按照指定的园根据起止角度画出扇形。
	// 注意：开始角度小于(<)结束角度按逆时针方向绘制，反之按顺时针方向绘制。
	//@参数 x 指定圆心的位置X。 
	//@参数 y 指定圆心的位置Y。 
	//@参数 r 指定圆的半径。 
	//@参数 开始角度 指定开始角度，以度为单位。
	//@参数 结束角度 指定结束角度，以度为单位。
	//@参数 背景填充 指定是否进行背景填充。
	//@别名 画扇形(x,y,r,开始角度,结束角度,背景填充)
	/*virtual*/ HRESULT Pie(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double r, /*, [in]*/ double BeginAngleDegree, /*, [in]*/ double EndAngleDegree, /*, [in]*/ BOOL ToFill){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_Pie(x, y, r, BeginAngleDegree, EndAngleDegree, ToFill? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Arc，按照指定的圆根据起止角度画出弧线。
	// 注意：开始角度小于(<)结束角度按逆时针方向绘制，反之按顺时针方向绘制。
	//@参数 x 指定圆心的位置X。 
	//@参数 y 指定圆心的位置Y。 
	//@参数 r 指定圆的半径。 
	//@参数 开始角度 指定开始角度，以度为单位。 
	//@参数 结束角度 指定结束角度，以度为单位。 
	//@别名 画弧线(x,y,r,开始角度,结束角度)
	/*virtual*/ HRESULT Arc(/*[in]*/ double cx, /*, [in]*/ double cy, /*, [in]*/ double r, /*, [in]*/ double BeginAngleDegree, /*, [in]*/ double EndAngleDegree){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_Arc(cx, cy, r, BeginAngleDegree, EndAngleDegree); return _result; }
	//@备注 EllipseArc，在指定的矩形区域中根据起止角度画出椭圆弧线。
	// 注意：开始角度小于(<)结束角度按逆时针方向绘制，反之按顺时针方向绘制。
	//@参数 左 指定矩形的左端位置。 
	//@参数 上 指定矩形的上端位置。 
	//@参数 宽度 指定矩形的宽度。 
	//@参数 高度 指定矩形的高度。 
	//@参数 开始角度 指定开始角度，以度为单位。
	//@参数 结束角度 指定结束角度，以度为单位。 
	//@别名 画椭圆弧线(左,上,宽度,高度,开始角度,结束角度)
	/*virtual*/ HRESULT EllipseArc(/*[in]*/ double Left, /*, [in]*/ double Top, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ double BeginAngleDegree, /*, [in]*/ double EndAngleDegree){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_EllipseArc(Left, Top, Width, Height, BeginAngleDegree, EndAngleDegree); return _result; }
	//@备注 EllipsePie，在指定的矩形区域中根据起止角度画出椭圆扇形。
	// 注意：开始角度小于(<)结束角度按逆时针方向绘制，反之按顺时针方向绘制。
	//@参数 左 指定矩形的左端位置。 
	//@参数 上 指定矩形的上端位置。 
	//@参数 宽度 指定矩形的宽度。 
	//@参数 高度 指定矩形的高度。 
	//@参数 开始角度 指定开始角度，以度为单位。 
	//@参数 结束角度 指定结束角度，以度为单位。 
	//@参数 背景填充 指定是否进行背景填充。
	//@别名 画椭圆扇形(左,上,宽度,高度,开始角度,结束角度,背景填充)
	/*virtual*/ HRESULT EllipsePie(/*[in]*/ double Left, /*, [in]*/ double Top, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ double BeginAngleDegree, /*, [in]*/ double EndAngleDegree, /*, [in]*/ BOOL ToFill){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_EllipsePie(Left, Top, Width, Height, BeginAngleDegree, EndAngleDegree, ToFill? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DrawLabelText，在指定位置画出文字。
	//@参数 文本串 指定要输出的文字。 
	//@参数 左 输出区域的左端位置。
	//@参数 上 输出区域的上端位置。
	//@别名 绘制标签文本(文本串,左,上)
	/*virtual*/ HRESULT DrawLabelText(/*[in]*/ const wchar_t* String, /*, [in]*/ double x, /*, [in]*/ double y){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_DrawLabelText((BSTR)String, x, y); return _result; }
	//@备注 DrawRotateText，按输出角度在指定位置画出文字。
	//@参数 文本串 指定要输出的文字。 
	//@参数 左 输出区域的左端位置。 
	//@参数 上 输出区域的上端位置。
	//@参数 角度 指定文字的输出角度，以度为计量单位。
	//@别名 绘制旋转文本(文本串,左,上,角度)
	/*virtual*/ HRESULT DrawRotateText(/*[in]*/ const wchar_t* String, /*, [in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double RotateDegree){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_DrawRotateText((BSTR)String, x, y, RotateDegree); return _result; }
	//@备注 DrawText，在矩形区域内画出文字。
	//@参数 文本串 指定要输出的文字。 
	//@参数 左 输出区域的左端位置。  
	//@参数 上 输出区域的上端位置。 
	//@参数 宽度 指定输出区域的宽度。
	//@参数 高度 指定输出区域的高度。 
	//@参数 文字对齐方式枚举值 指定文字的对齐方式。 
	//@参数 逻辑值 指定文字是否自动绕行显示。
	//@别名 绘制文本(文本串,左,上,宽度,高度,文字对齐方式枚举值,逻辑值)
	/*virtual*/ HRESULT DrawText(/*[in]*/ const wchar_t* String, /*, [in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ GRTextAlign TextAlign, /*, [in]*/ BOOL WordWrap){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_DrawText((BSTR)String, x, y, Width, Height, TextAlign, WordWrap? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DrawFormatText，按指定文字格式在矩形区域内画出文字。
	//@参数 文本串 指定要输出的文字。 
	//@参数 左 输出区域的左端位置。  
	//@参数 上 输出区域的上端位置。
	//@参数 宽度 指定输出区域的宽度。
	//@参数 高度 指定输出区域的高度。
	//@参数 文本格式对象 指定文字格式。
	//@别名 绘制格式文本(文本串,左,上,宽度,高度,文本格式对象)
	/*virtual*/ HRESULT DrawFormatText(/*[in]*/ const wchar_t* String, /*, [in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ class CIGRTextFormat* TextFormat);
	//@备注 CalcLabelTextWidth，计算用当前字体完整输出指定文字需要的宽度。
	//@参数 文本串 进行计算的文字串。
	//@返回 返回指定文字的输出宽度。
	//@别名 计算标签文本宽度(文本串)
	/*virtual*/ double CalcLabelTextWidth(/*[in]*/ const wchar_t* String/*, [out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->raw_CalcLabelTextWidth((BSTR)String, &_result); return _result; }
	//@备注 CalcLabelTextHeight，计算用当前字体完整输出指定文字需要的高度。
	//@参数 文本串 进行计算的文字串。
	//@返回 返回指定文字的输出高度。
	//@别名 计算标签文本高度(文本串)
	/*virtual*/ double CalcLabelTextHeight(/*[in]*/ const wchar_t* String/*, [out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->raw_CalcLabelTextHeight((BSTR)String, &_result); return _result; }
	//@备注 CalcTextOutLen，计算出指定的文字在指定大小的区域中最多能完整输出多少个字符。
	//@参数 宽度 区域宽度。
	//@参数 高度 区域高度。
	//@参数 文本串 要输出的文字串 。
	//@参数 自动绕行 文字是否自动绕行输出。
	//@返回 返回能完整输出的字符个数。
	//@别名 计算文本输出个数(宽度,高度,文本串,自动绕行)
	/*virtual*/ long CalcTextOutLen(/*[in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ const wchar_t* Text, /*, [in]*/ BOOL WordWrap/*, [out][retVal] long* pTextLen*/){long _result=0; ((IGRGraphics*)m_ptr.p)->raw_CalcTextOutLen(Width, Height, (BSTR)Text, WordWrap? VARIANT_TRUE : VARIANT_FALSE, &_result); return _result; }
	//@备注 DrawPicture，绘制图片。
	//@参数 报表图片对象 要绘制的图像对象。
	//@参数 左 输出区域的左端位置。 
	//@参数 上 输出区域的上端位置。
	//@参数 宽度 输出区域的宽度。 
	//@参数 高度 输出区域的高度。 
	//@参数 图像显示方式枚举值 图片输出的位置对齐方式。
	//@参数 图像缩放方式枚举值 图片输出的大小缩放模式。 
	//@参数 图像透明模式枚举值 图片输出的透明处理模式。
	//@别名 绘制图片(报表图片对象,左,上,宽度,高度,图像显示方式枚举值,图像缩放方式枚举值,图像透明模式枚举值)
	/*virtual*/ HRESULT DrawPicture(/*[in]*/ class CIGRPicture* pPicture, /*, [in]*/ double Left, /*, [in]*/ double Top, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ GRPictureAlignment PictureAlignment, /*, [in]*/ GRPictureSizeMode PictureSizeMode, /*, [in]*/ GRPictureTransparentMode Transparent);
	//@备注 SelectFont，选择用来输出文字的字体对象。
	// SelectFont 与 RestoreFont 必须成对调用，在调用 SelectFont 方法后,在输出文字任务完成后,必须调用 RestoreFont 方法进行恢复操作。
	//@参数 字体对象 指定字体对象 
	//@别名 字体改变(字体对象)
	/*virtual*/ HRESULT SelectFont(/*[in]*/ class CIGRFont* pFont);
	//@备注 RestoreFont，恢复选择字体操作。
	// SelectFont 与 RestoreFont 必须成对调用，在调用 SelectFont 方法后,在输出文字任务完成后,必须调用 RestoreFont 方法进行恢复操作。
	//@别名 字体恢复()
	/*virtual*/ HRESULT RestoreFont(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_RestoreFont(); return _result; }
	//@备注 FontPointChangeTo，将当前的字体点数重新设置为指定值。
	// 将当前的字体点数重新设置为指定值，后面输出的文字将按新的字体大小输出。
	// 本方法必须与 FontPointRestore 方法成对调用，开始应用 FontPointChangeTo 
	// 方法设置字体大小，当应用字体大小设置输出任务完成后，必须调用 FontPointRestore 方法恢复字体设置
	//@参数 字号 要设置的字体点数，可以带小数位。 
	//@别名 字号改变(字号)
	/*virtual*/ HRESULT FontPointChangeTo(/*[in]*/ double Point){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_FontPointChangeTo(Point); return _result; }
	//@备注 FontPointRestore，恢复用 FontPointChangeTo 方法修改后的字体设置。
	// 本方法必须与 FontPointChangeTo 方法成对调用，开始应用 FontPointChangeTo 
	// 方法设置字体大小，当应用字体大小设置输出任务完成后，必须调用 FontPointRestore 方法恢复字体设置。
	//@别名 字号恢复()
	/*virtual*/ HRESULT FontPointRestore(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_FontPointRestore(); return _result; }
	//@备注 SelectTextColor，设置文字绘出颜色。
	// SelectTextColor 与 RestoreTextColor 必须成对调用，在调用 SelectTextColor 后并完成相关绘出任务，应该调用 RestoreTextColor 进行恢复操作。
	//@参数 颜色值 指定新的文字颜色。
	//@别名 文字色改变(颜色值)
	/*virtual*/ HRESULT SelectTextColor(/*[in]*/ OLE_COLOR TextColor){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_SelectTextColor(TextColor); return _result; }
	//@备注 RestoreTextColor，恢复文字颜色设置。
	// SelectTextColor 与 RestoreTextColor 必须成对调用，在调用 SelectTextColor 后并完成相关绘出任务，应该调用 RestoreTextColor 进行恢复操作。
	//@别名 文字色恢复()
	/*virtual*/ HRESULT RestoreTextColor(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_RestoreTextColor(); return _result; }
	//@备注 SelectPen，设置绘出画笔参数。
	// SelectPen 与 RestorePen 必须成对调用，在调用 SelectPen 后并完成相关绘出任务，应该调用 RestorePen 进行恢复操作。
	//@参数 宽度 指定画笔的宽度。 
	//@参数 颜色 指定画笔的颜色。
	//@参数 画线笔类型枚举 指定画笔的线型。 
	//@别名 画笔改变(宽度,颜色,画线笔类型枚举)
	/*virtual*/ HRESULT SelectPen(/*[in]*/ double PenWidth, /*, [in]*/ OLE_COLOR PenColor, /*, [in]*/ GRPenStyle PenStyle){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_SelectPen(PenWidth, PenColor, PenStyle); return _result; }
	//@备注 RestorePen，恢复画笔设置。
	// SelectPen 与 RestorePen 必须成对调用，在调用 SelectPen 后并完成相关绘出任务，应该调用 RestorePen 进行恢复操作。
	//@别名 画笔恢复()
	/*virtual*/ HRESULT RestorePen(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_RestorePen(); return _result; }
	//@备注 SelectFillColor，设置填充背景色。
	// SelectFillColor 与 RestoreFillColor 必须成对调用，在调用 SelectFillColor 后并完成相关绘出任务，应该调用 RestoreFillColor 进行恢复操作。
	//@参数 颜色值 指定新的填充色 
	//@别名 填充背景色改变(颜色值)
	/*virtual*/ HRESULT SelectFillColor(/*[in]*/ OLE_COLOR BrushColor){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_SelectFillColor(BrushColor); return _result; }
	//@备注 RestoreFillColor，恢复填充背景色设置。
	// SelectFillColor 与 RestoreFillColor 必须成对调用，在调用 SelectFillColor 后并完成相关绘出任务，应该调用 RestoreFillColor 进行恢复操作。
	//@别名 填充背景色恢复()
	/*virtual*/ HRESULT RestoreFillColor(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_RestoreFillColor(); return _result; }
	//@备注 PushClipRect，设置绘出剪裁区域。
	// 剪裁区域PushClipRect 与 剪裁恢复PopClipRect 必须成对调用，在调用 剪裁区域PushClipRect 后并完成相关绘出任务，应该调用 剪裁恢复PopClipRect 进行恢复操作。
	//@参数 左 指定区域左上角的位置X。
	//@参数 上 指定区域左上角的位置Y。 
	//@参数 宽度 指定区域的宽度。 
	//@参数 高度 指定区域的高度。
	//@别名 剪裁矩形(左,上,宽度,高度)
	/*virtual*/ HRESULT PushClipRect(/*[in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_PushClipRect(x, y, Width, Height); return _result; }
	//@备注 PopClipRect，恢复绘出剪裁区域。
	// 剪裁区域PushClipRect 与 剪裁恢复PopClipRect 必须成对调用，在调用 剪裁区域PushClipRect 后并完成相关绘出任务，应该调用 剪裁恢复PopClipRect 进行恢复操作。
	//@别名 剪裁恢复()
	/*virtual*/ HRESULT PopClipRect(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_PopClipRect(); return _result; }
	//@备注 Left，获取绘制输出的左端位置，此属性值始终为0，由 ByUnit 属性指定属性值采用的计量单位。
	//@别名 取左()
	/*virtual*/ double get_Left(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_Left(&_result); return _result; }
	//@备注 Top，获取绘制输出的上端位置，此属性值始终为0，由 ByUnit 属性指定属性值采用的计量单位。
	//@别名 取上()
	/*virtual*/ double get_Top(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_Top(&_result); return _result; }
	//@备注 Width，获取输出区域的高度，由 ByUnit 属性指定属性值采用的计量单位。
	//@别名 取宽度()
	/*virtual*/ double get_Width(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Height，获取输出区域的宽度，由 ByUnit 属性指定属性值采用的计量单位。
	//@别名 取高度()
	/*virtual*/ double get_Height(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 ByUnit，指定在绘制过程中与位置与大小相关的参数值采用哪种类型计量单位。
	// 如果本属性值为true，则采用报表的当前计量单位，通常为厘米或英寸，由报表主对象的“计量单位”属性指定；反之采用屏幕像素点为计量单位。
	//@返回 默认值false
	//@别名 取依据报表计量单位()
	/*virtual*/ BOOL get_ByUnit(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGraphics*)m_ptr.p)->get_ByUnit(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ByUnit，指定在绘制过程中与位置与大小相关的参数值采用哪种类型计量单位。
	// 如果本属性值为true，则采用报表的当前计量单位，通常为厘米或英寸，由报表主对象的“计量单位”属性指定；反之采用屏幕像素点为计量单位。
	//@参数 逻辑值 默认值false
	//@别名 置依据报表计量单位(逻辑值)
	/*virtual*/ HRESULT set_ByUnit(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->put_ByUnit(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CCPInnerX，获取绘制巴塞尔曲线的内侧控制点的 X 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取内侧控制点X()
	/*virtual*/ double get_CCPInnerX(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_CCPInnerX(&_result); return _result; }
	//@备注 CCPInnerY，获取绘制巴塞尔曲线的内侧控制点的 Y 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取内侧控制点Y()
	/*virtual*/ double get_CCPInnerY(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_CCPInnerY(&_result); return _result; }
	//@备注 CCPOuterX，获取绘制巴塞尔曲线的外侧控制点的 X 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取外侧控制点X()
	/*virtual*/ double get_CCPOuterX(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_CCPOuterX(&_result); return _result; }
	//@备注 CCPOuterY，获取绘制巴塞尔曲线的外侧控制点的 Y 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取外侧控制点Y()
	/*virtual*/ double get_CCPOuterY(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_CCPOuterY(&_result); return _result; }
	//@备注 CurveTo，从当前点开始用当前画笔绘制巴塞尔曲线。
	// 从当前位置开始，根据内侧控制点、外侧控制点及终点绘制巴塞尔曲线。曲线经过当前位置点与终点。
	//@参数 内侧点X 内侧控制点的 X 位置。 
	//@参数 内侧点Y 内侧控制点的 Y 位置。
	//@参数 外侧点X 外侧控制点的 X 位置。 
	//@参数 外侧点Y 外侧控制点的 Y 位置。 
	//@参数 曲线终点X 曲线终点的 X 位置。 
	//@参数 曲线终点Y 曲线终点的 Y 位置。 
	//@别名 绘制巴塞尔曲线(内侧点X,内侧点Y,外侧点X,外侧点Y,曲线终点X,曲线终点Y)
	/*virtual*/ HRESULT CurveTo(/*[in]*/ double xInnerControl, /*, [in]*/ double yInnerControl, /*, [in]*/ double xOuterControl, /*, [in]*/ double yOuterControl, /*, [in]*/ double xEnd, /*, [in]*/ double yEnd){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_CurveTo(xInnerControl, yInnerControl, xOuterControl, yOuterControl, xEnd, yEnd); return _result; }
	//@备注 CalcCurveControlPoints，计算出绘制巴塞尔曲线的控制点位置。
	// 根据前点、中间点与后点这三点计算出绘制巴塞尔曲线的控制点位置，得到的控制点是两个，是相对于中间点的内侧控制点与外侧控制点。本函数不会直接返回这两个控制点的数据，而是在执行本函数后通过 CCPInnerX、CCPInnerY、CCPOuterX 与 CCPOuterY 这四个属性获取控制点的位置值。
	//@参数 前点X 前点的 X 位置。
	//@参数 前点Y 前点的 Y 位置。 
	//@参数 中间点X 中间点的 X 位置。 
	//@参数 中间点Y 中间点的 Y 位置。 
	//@参数 后点X 后点的 X 位置。 
	//@参数 后点Y 后点的 Y 位置。 
	//@别名 取巴塞尔曲线控制点(前点X,前点Y,中间点X,中间点Y,后点X,后点Y)
	/*virtual*/ HRESULT CalcCurveControlPoints(/*[in]*/ double xFirst, /*, [in]*/ double yFirst, /*, [in]*/ double xMiddle, /*, [in]*/ double yMiddle, /*, [in]*/ double xAfter, /*, [in]*/ double yAfter){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_CalcCurveControlPoints(xFirst, yFirst, xMiddle, yMiddle, xAfter, yAfter); return _result; }
	//@备注 DrawPointMarker，在指定的位置绘制一个数据点图标。
	// 用当前画笔，填充色在指定位置绘制一个指定类型的图标。图标类型与图表中的数据点图标是一致的。
	//@参数 标记类型枚举值 指定图标的类型。 
	//@参数 中心点x 图标中心点的 X 位置。
	//@参数 中心点y 图标中心点的 Y 位置。 
	//@参数 尺寸 图标正方形区域的边长。
	//@别名 绘制标记点(标记类型枚举值,中心点x,中心点y,尺寸)
	/*virtual*/ HRESULT DrawPointMarker(/*[in]*/ GRPointMarkerStyle MarkerStyle, /*, [in]*/ double cx, /*, [in]*/ double cy, /*, [in]*/ double size){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_DrawPointMarker(MarkerStyle, cx, cy, size); return _result; }
	//@备注 DrawFormatTextShrinkToFit，按指定文字格式在矩形区域内画出文字，如有需要，缩小文字将全部文字都完整显示出来。
	//@参数 文本串 指定要输出的文字。 
	//@参数 左 指定输出左上角的位置X。 
	//@参数 上 指定输出左上角的位置Y。 
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 高度 指定输出区域的高度。 
	//@参数 文本格式对象 指定文字格式。
	//@别名 绘制格式文本缩小适应(文本串,左,上,宽度,高度,文本格式对象)
	/*virtual*/ HRESULT DrawFormatTextShrinkToFit(/*[in]*/ const wchar_t* String, /*, [in]*/ double x, /*, [in]*/ double y, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ class CIGRTextFormat* TextFormat);
	//@备注 CalcDrawFormatTextHeight，计算输出文字需要的高度。
	// 在指定的输出宽度下，将文字完整显示出来需要的高度。这里宽度与高度的计量单位由 ByUnit 属性值确定，默认以屏幕像素为计量单位。
	//@参数 文本串 指定要输出的文字。
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 文本格式对象 指定文字输出格式。 
	//@返回 返回完整输出文字需要的高度。
	//@别名 计算格式文本输出高度(文本串,宽度,文本格式对象)
	/*virtual*/ double CalcDrawFormatTextHeight(/*[in]*/ const wchar_t* String, /*, [in]*/ double Width, /*, [in]*/ class CIGRTextFormat* TextFormat/*, [out][retVal] double* pVal*/);
	//@备注 CalcDrawFormatTextWidth，计算出完整输出文字需要的宽度。
	// 将文字完整显示出来需要的宽度。这里宽度的计量单位由 ByUnit 属性值确定，默认以屏幕像素为计量单位。
	// 如果是多行文字，按每行文字分别计算需要的输出宽度，以其中的最大值为计算结果。
	//@参数 文本串 指定要输出的文字。 
	//@参数 文本格式对象 指定文字的输出格式。
	//@返回 返回完整输出文字需要的宽度。
	//@别名 计算格式文本输出宽度(文本串,文本格式对象)
	/*virtual*/ double CalcDrawFormatTextWidth(/*[in]*/ const wchar_t* String, /*, [in]*/ class CIGRTextFormat* TextFormat/*, [out][retVal] double* pVal*/);
	//@备注 CalcDrawFormatTextOutLen，在指定大小的区域中，可以输出的文字个数。
	// 在给定宽度与高度的区域中，求得传入的文字能输出多少个。如果能完整输出，则返回值与文字的长度一致。
	//@参数 文本串 指定要输出的文字。 
	//@参数 宽度 指定输出区域的宽度。 
	//@参数 高度 指定输出区域的高度。 
	//@参数 文本格式对象 指定文字的输出格式。 
	//@返回 返回可以输出的文字个数。
	//@别名 计算格式文本输出个数(文本串,宽度,高度,文本格式对象)
	/*virtual*/ long CalcDrawFormatTextOutLen(/*[in]*/ const wchar_t* Text, /*, [in]*/ double Width, /*, [in]*/ double Height, /*, [in]*/ class CIGRTextFormat* TextFormat/*, [out][retVal] long* pTextLen*/);
	//@备注 BeginPath，开始一个路径
	// 在本函数调用之后，必须调用 MoveTo、LineTo、CurveTo 等函数进行路径的定义，也可以调用 ClosePath 封闭一个路径，最后调用 FillPath、StrokePath 或 StrokeAndFillPath 函数进行路径绘制。
	//@别名 开始路径()
	/*virtual*/ HRESULT BeginPath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_BeginPath(); return _result; }
	//@备注 ClosePath，封闭一个路径，让当前路径点连直线到起点。
	//@别名 封闭路径()
	/*virtual*/ HRESULT ClosePath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_ClosePath(); return _result; }
	//@备注 EndPath，结束一个路径。
	//@别名 结束路径()
	/*virtual*/ HRESULT EndPath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_EndPath(); return _result; }
	//@备注 StrokePath，此函数必须在 BeginPath 函数之后调用，即前面必须已经定义了一个路径。
	//@别名 绘制路径()
	/*virtual*/ HRESULT StrokePath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_StrokePath(); return _result; }
	//@备注 FillPath，填充路径前必须保证当前路径是一个封闭路径。此函数必须在 BeginPath 函数之后调用，即前面必须已经定义了一个路径。
	//@别名 填充路径()
	/*virtual*/ HRESULT FillPath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_FillPath(); return _result; }
	//@备注 StrokeAndFillPath，绘制并填充路径，必须保证当前路径是一个封闭路径。此函数必须在 BeginPath 函数之后调用，即前面必须已经定义了一个路径。
	//@别名 绘制并填充路径()
	/*virtual*/ HRESULT StrokeAndFillPath(){ HRESULT _result = ((IGRGraphics*)m_ptr.p)->raw_StrokeAndFillPath(); return _result; }
	//@备注 LeftInPaper，获取当前自定义绘制部件框在页面中输出的左端位置。
	// 此属性值只有在生成报表页面时有效(即在报表查询显示时本属性值始终为0)，且只能在部件框的“自绘脚本”中，或报表的 ControlCustomDraw 事件响应函数中读取。
	// 如果部件框在整个报表中只会显示一次，将属性值记录到某个报表参数中，后面再通过读取报表参数的值来获取此属性的值。
	// 如果部件框在整个报表中会显示多次，应该在 ControlCustomDraw 事件响应函数中获取此属性值并分别记录下每次的获取值。
	// 此属性可用于对报表进行数字签章定位功能，通过获取一个自绘部件框的位置实现指定签章位置的要求。
	//@别名 取左端位置()
	/*virtual*/ double get_LeftInPaper(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_LeftInPaper(&_result); return _result; }
	//@备注 TopInPaper，获取当前自定义绘制部件框在页面中输出的上端位置。
	// 本属性进一步说明请参考 LeftInPaper 属性的详细说明。
	//@别名 取上端位置()
	/*virtual*/ double get_TopInPaper(/*[out][retVal] double* pVal*/){double _result=0; ((IGRGraphics*)m_ptr.p)->get_TopInPaper(&_result); return _result; }

};
//@备注 Utility，应用工具，报表辅助应用工具对象。
//@别名 功能函数
class CIGRUtility : public CXComObj /*IDispatch*/
{
public:
	CIGRUtility(){};
	CIGRUtility(IGRUtility* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRUtility* GetPtr(){ return ((IGRUtility*)m_ptr.p); }
	//@备注 CreatePicture，创建一个图像对象。
	//@返回 创建的图像对象。
	//@别名 创建图片()
	/*virtual*/ class CIGRPicture CreatePicture(/*[out][retVal] class CIGRPicture** pVal*/);
	//@备注 CreateRecordset，创建一个记录集对象。
	//@返回 创建的记录集对象。
	//@别名 创建数据集()
	/*virtual*/ class CIGRRecordset CreateRecordset(/*[out][retVal] class CIGRRecordset** pVal*/);
	//@备注 CreateTextFormat，创建一个文本格式对象。
	//@返回 创建的文本格式对象。
	//@别名 创建文本格式()
	/*virtual*/ class CIGRTextFormat CreateTextFormat(/*[out][retVal] class CIGRTextFormat** pVal*/);
	//@备注 CreateBinaryObject，创建一个二进制数据对象。
	//@返回 创建的二进制数据对象。
	//@别名 创建二进制数据()
	/*virtual*/ class CIGRBinaryObject CreateBinaryObject(/*[out][retVal] class CIGRBinaryObject** pVal*/);
	//@备注 CreateDateTime，创建一个日期时间对象。
	//@返回 创建的日期时间对象。
	//@别名 创建日期时间()
	/*virtual*/ class CIGRDateTime CreateDateTime(/*[out][retVal] class CIGRDateTime** pVal*/);
	//@备注 NumberFormat，按照格式化串产生一个数字值的显示文字。
	//@参数 数字值 进行转换的数字值。 
	//@参数 格式化串 
	//@返回 格式化产生的显示文字。
	//@别名 数值格式化(数字值,格式化串)
	/*virtual*/ CXText NumberFormat(/*[in]*/ double Value, /*, [in]*/ const wchar_t* Format/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_NumberFormat(Value, (BSTR)Format, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ CXText NumberFormatToEnglish(/*[in]*/ double Value, /*, [in]*/ long Decimals/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_NumberFormatToEnglish(Value, Decimals, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 NumberFormatToBigHZ，产生一个数字值的汉字大写显示文字。 
	//@参数 数字值 进行转换的数字值。 
	//@参数 小数位数 指定保留的小数位数。
	//@返回 格式化产生的显示文字。
	//@别名 数字格式化为汉字大写(数字值,小数位数)
	/*virtual*/ CXText NumberFormatToBigHZ(/*[in]*/ double Value, /*, [in]*/ long Decimals/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_NumberFormatToBigHZ(Value, Decimals, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 NumberFormatToBigHZAmount，产生一个数字值的汉字大写金额显示文字
	//@参数 数字值 进行转换的数字值。 
	//@返回 格式化产生的显示文字。
	//@别名 数字格式化为汉字大写金额(数字值)
	/*virtual*/ CXText NumberFormatToBigHZAmount(/*[in]*/ double Value/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_NumberFormatToBigHZAmount(Value, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 NumberRound45，获取一个数字值的四舍五入值。
	//@参数 数字值 进行转换的数字值。 
	//@参数 小数位数 指定保留的小数位数。
	//@返回 获取的四舍五入值。
	//@别名 数值四舍五入(数字值,小数位数)
	/*virtual*/ double NumberRound45(/*[in]*/ double Value, /*, [in]*/ long Decimals/*, [out][retVal] double* Result*/){double _result=0; ((IGRUtility*)m_ptr.p)->raw_NumberRound45(Value, Decimals, &_result); return _result; }
	//@备注 NumberRound465，获取一个数字值的四舍六入五成双值。
	// 四舍六入五成双的修约功能：这里“四”是指≤4 时舍去，\"六\"是指≥6时进上，\"五\"指的是根据5后面的数字来定，当5后有数时，舍5入1；当5后无有效数字时，需要分两种情况来讲：①5前为奇数，舍5入1；②5前为偶数，舍5不进。（0是偶数）
	//@参数 数字值 进行转换的数字值。 
	//@参数 小数位数 指定保留的小数位数。 
	//@返回 获取的四舍六入五成双值。
	//@别名 数值四舍六入五留双(数字值,小数位数)
	/*virtual*/ double NumberRound465(/*[in]*/ double Value, /*, [in]*/ long Decimals/*, [out][retVal] double* Result*/){double _result=0; ((IGRUtility*)m_ptr.p)->raw_NumberRound465(Value, Decimals, &_result); return _result; }
	/*virtual*/ CXText DateTimeFormat(/*[in]*/ DATE Date, /*, [in]*/ const wchar_t* Format/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_DateTimeFormat(Date, (BSTR)Format, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TooltipHoverTime，指定鼠标悬停出提示文字的时间长度，以1/1000秒为单位。
	// 当鼠标停留在相关数据区域时，指定停留多长时间后弹出显示相关提示文字。
	// 在 Grid++Report 中，如下情况下会出悬停提示文字，且其悬停时长受本属性控制：
	//   1、在报表查询显示时，当纯文字内容不能完整显示时。
	//   2、在报表查询显示时，图表序列设置了提示文字(TooltipText)属性，鼠标位于数据项的对应图形上时。
	//   3、设计报表时，当纯文字类型部件框的内容不能完整显示时。
	// 注意：设计报表时，属性窗口中的属性值不能完整显示时，也会出悬停出提示文字，但这里是马上弹出提示文字，不受本属性影响。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@返回 默认值500
	//@别名 取提示文本显示速度()
	/*virtual*/ long get_TooltipHoverTime(/*[out][retVal] long* pVal*/){long _result=0; ((IGRUtility*)m_ptr.p)->get_TooltipHoverTime(&_result); return _result; }
	//@备注 TooltipHoverTime，指定鼠标悬停出提示文字的时间长度，以1/1000秒为单位。
	// 当鼠标停留在相关数据区域时，指定停留多长时间后弹出显示相关提示文字。
	// 在 Grid++Report 中，如下情况下会出悬停提示文字，且其悬停时长受本属性控制：
	//   1、在报表查询显示时，当纯文字内容不能完整显示时。
	//   2、在报表查询显示时，图表序列设置了提示文字(TooltipText)属性，鼠标位于数据项的对应图形上时。
	//   3、设计报表时，当纯文字类型部件框的内容不能完整显示时。
	// 注意：设计报表时，属性窗口中的属性值不能完整显示时，也会出悬停出提示文字，但这里是马上弹出提示文字，不受本属性影响。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@参数 整数值 默认值500
	//@别名 置提示文本显示速度(整数值)
	/*virtual*/ HRESULT set_TooltipHoverTime(/*[in]*/ long pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_TooltipHoverTime(pVal); return _result; }
	/*virtual*/ HRESULT GetSkin(/*[out]*/ long* ColorRed, /*, [out]*/ long* ColorGreen, /*, [out]*/ long* ColorBlue, /*, [out]*/ long* Style){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_GetSkin(ColorRed, ColorGreen, ColorBlue, Style); return _result; }
	//@备注 SetSkin，设置控件界面背景色的三原色与背景模式。
	//@参数 红 设置背景色的三原色的红色值，0-255之间。 
	//@参数 绿 设置背景色的三原色的绿色值，0-255之间。 
	//@参数 蓝 设置背景色的三原色的蓝色值，0-255之间。 
	//@参数 风格类型 设置界面的风格类型，目前有效值为0或1。说明：Style参数仅可为 0 或 1，其中：0 表示按照同一色(Solid)方式填充背景；1 表示按照渐变色(Gradient)方式填充背景。
	//@别名 设置皮肤(红,绿,蓝,风格类型)
	/*virtual*/ HRESULT SetSkin(/*[in]*/ long ColorRed, /*, [in]*/ long ColorGreen, /*, [in]*/ long ColorBlue, /*, [in]*/ long Style){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_SetSkin(ColorRed, ColorGreen, ColorBlue, Style); return _result; }
	/*virtual*/ HRESULT SetHyperlinkClickedColor(/*[in]*/ long ColorRed, /*, [in]*/ long ColorGreen, /*, [in]*/ long ColorBlue){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_SetHyperlinkClickedColor(ColorRed, ColorGreen, ColorBlue); return _result; }
	/*virtual*/ HRESULT LoadDefaultPreviewWinIcon(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_LoadDefaultPreviewWinIcon((BSTR)PathFile); return _result; }
	//@备注 GZCompress，将数据按GZIP方式进行压缩。
	//@参数 数据Val 要进行压缩的数据包。
	//@返回 压缩得到的数据包。
	//@别名 GZ压缩(数据Val)
	/*virtual*/ VARIANT GZCompress(/*[in]*/ VARIANT Val/*, [out][retVal] VARIANT* Result*/){VARIANT _result; VariantInit(&_result);((IGRUtility*)m_ptr.p)->raw_GZCompress(Val, &_result); return _result; }
	//@备注 GZUncompress，将数据按GZIP方式进行解压缩。
	//@参数 数据Val 要进行解压缩的压缩数据包。
	//@返回 解压缩得到的数据包。
	//@别名 GZ解压缩(数据Val)
	/*virtual*/ VARIANT GZUncompress(/*[in]*/ VARIANT Val/*, [out][retVal] VARIANT* Result*/){VARIANT _result; VariantInit(&_result);((IGRUtility*)m_ptr.p)->raw_GZUncompress(Val, &_result); return _result; }
	/*virtual*/ HRESULT HTTPRequestSend(/*[in]*/ const wchar_t* URL, /*, [in]*/ VARIANT data){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_HTTPRequestSend((BSTR)URL, data); return _result; }
	//@备注 ShowFolderDialog，显示 Windows 系统的文件路径对话框。
	//@返回 选择的文件路径。
	//@别名 显示文件对话框()
	/*virtual*/ CXText ShowFolderDialog(/*[out][retVal] const wchar_t** FolderPath*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_ShowFolderDialog(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ShowOpenFileDialog，显示 Windows 系统的打开文件对话框。
	// 打开扩展名为\".grf\"的报表模板文件的代码如：
	// var PathFile = Report.Utility.ShowOpenFileDialog(\"锐浪报表模板文件\", \"grf\", \"\");
	//@参数 文件类型 FileType，文件类型名称。 
	//@参数 扩展名 ExtFile，文件扩展名、后缀。 
	//@参数 文件名称 DefaultFile，预设默认文件名称。 
	//@返回 选择的文件的全路径文件名。
	//@别名 显示打开文件对话框(文件类型,扩展名,文件名称)
	/*virtual*/ CXText ShowOpenFileDialog(/*[in]*/ const wchar_t* FileType, /*, [in]*/ const wchar_t* ExtFile, /*, [in]*/ const wchar_t* DefaultFile/*, [out][retVal] const wchar_t** PathFile*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_ShowOpenFileDialog((BSTR)FileType, (BSTR)ExtFile, (BSTR)DefaultFile, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ShowSaveFileDialog，显示 Windows 系统的保存文件对话框。
	//@参数 文件类型 FileType，文件类型名称。
	//@参数 扩展名 ExtFile，文件扩展名、后缀。
	//@参数 文件名称 DefaultFile，预设默认文件名称。
	//@返回 选择的文件的全路径文件名。
	//@别名 显示保存文件对话框(文件类型,扩展名,文件名称)
	/*virtual*/ CXText ShowSaveFileDialog(/*[in]*/ const wchar_t* FileType, /*, [in]*/ const wchar_t* ExtFile, /*, [in]*/ const wchar_t* DefaultFile/*, [out][retVal] const wchar_t** PathFile*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_ShowSaveFileDialog((BSTR)FileType, (BSTR)ExtFile, (BSTR)DefaultFile, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetPrinterCount，获取 Windows 系统中安装的打印机个数。
	//@返回 获取得的打印机个数。
	//@别名 取打印机数量()
	/*virtual*/ long GetPrinterCount(/*[out][retVal] long* Count*/){long _result=0; ((IGRUtility*)m_ptr.p)->raw_GetPrinterCount(&_result); return _result; }
	//@备注 GetPrinterName，根据序号得到对应打印机的名称，序号从1开始。
	// 一般在调用本方法前会调用 GetPrinterCount 方法，通过循环调用本方法可以将当前 Windows 系统中安装的打印机全部枚举出来。
	// 如下代码用 GetPrinterCount 方法获取当前电脑中安装的打印机个数，并用 GetPrinterName 方法获取各个打印的名称。
	// var PrinterCount = Report.Utility.GetPrinterCount(); 
	// var PtinterListNames = \"\";
	// for (i=1;i<=PrinterCount;++i)
	// {
	//     var PrinterName = Report.Utility.GetPrinterName(i); 
	//     PtinterListNames += PrinterName; 
	//     PtinterListNames += \"\\r\\n\"; 
	// }
	// alert(PtinterListNames);
	//@参数 序号 序号，从1开始。 
	//@返回 获得的打印机名称。
	//@别名 取打印机名称(序号)
	/*virtual*/ CXText GetPrinterName(/*[in]*/ long Index/*, [out][retVal] const wchar_t** PrinterName*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_GetPrinterName(Index, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 GetPrinterPaperCount，获取制定打印机支持的纸型个数。
	//@参数 打印机名称 打印机名称。
	//@返回 获取的纸型个数。
	//@别名 取打印机纸张数量(打印机名称)
	/*virtual*/ long GetPrinterPaperCount(/*[in]*/ const wchar_t* PrinterName/*, [out][retVal] long* Count*/){long _result=0; ((IGRUtility*)m_ptr.p)->raw_GetPrinterPaperCount((BSTR)PrinterName, &_result); return _result; }
	//@备注 GetPrinterPaperName，根据序号获得打印纸型的名称。
	// 在调用本方法前，必须调用 GetPrinterPaperCount 方法。
	// 通过循环调用本方法，可以将某个打印机支持的全部纸型枚举出来。
	// 如下代码用 GetPrinterPaperCount 方法获取指定打印机的可用的纸张个数，并用 GetPrinterPaperName 方法获取各个纸张的名称。
	// var PaperCount = Report.Utility.GetPrinterPaperCount(); 
	// var PaperListNames = \"\";
	// for (i=1;i<=PaperCount;++i)
	// {
	//     var PaperName = Report.Utility.GetPrinterPaperName(i); 
	//     PaperListNames += PaperName; 
	//     PaperListNames += \"\\r\\n\"; 
	// }
	// alert(PaperListNames);
	//@参数 纸型序号 纸型序号，从1开始。
	//@返回 打印纸型的名称
	//@别名 取打印机纸张名称(纸型序号)
	/*virtual*/ CXText GetPrinterPaperName(/*[in]*/ long Index/*, [out][retVal] const wchar_t** PaperName*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_GetPrinterPaperName(Index, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DisableDebug，禁止报表运行时的调试功能。
	// 执行本函数后，在报表查询与打印预览展现时不能通过“ctrl+shift 键同时按下”这样的方式保存报表模板与报表数据。
	// 另外一些报表运行出错的信息也将显示得更简洁一些，也不提示保存报表数据供锐浪参考分析。
	// 此设置是全局性的，只要设置一次，会影响到整个程序中的全部报表。
	// 示例代码：
	// Report.Utility.DisableDebug();
	//@别名 禁止调试()
	/*virtual*/ HRESULT DisableDebug(){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_DisableDebug(); return _result; }
	//@备注 SetMoneyLabelText，设置财务金额位的标签文字。
	// 参数中标签文字的最大长度为11个字符，多余数据将无效。在报表运行之前调用本方法，只用调用一次，这样的设置是全局影响的，即所有报表都将按新的设置显示金额位标签文字。
	// 在 Grid++Report 的默认设置中，财务金额位的标签文字为“分角元十百千万十百千亿”，开发者可以根据需要执行本方法对这些文字进行调整，最长用的新设置参数为“分角元拾佰仟万拾佰仟亿”。
	// 在报表运行之前调用本方法，只用调用一次，这样的设置是全局影响的，即所有报表都将按新的设置显示金额位标签文字。代码如下：
	// Report.Utility.SetMoneyLabelText(\"分角元拾佰仟万拾佰仟亿\");
	//@参数 标签文字 新的标签文字。
	//@别名 设置金额标签文字(标签文字)
	/*virtual*/ HRESULT SetMoneyLabelText(/*[in]*/ const wchar_t* MoneyLabelText){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_SetMoneyLabelText((BSTR)MoneyLabelText); return _result; }
	//@备注 TextWrapByWord，指定文字在绕行显示时是否按单词进行自动换行处理，即是否保持单词的完整性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 如果不希望多行显示的文字在显示时保持单词的完整性，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.TextWrapByWord = false;
	//@别名 取依据文本自动折行()
	/*virtual*/ BOOL get_TextWrapByWord(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRUtility*)m_ptr.p)->get_TextWrapByWord(&_result); return (VARIANT_TRUE==_result); }
	//@备注 TextWrapByWord，指定文字在绕行显示时是否按单词进行自动换行处理，即是否保持单词的完整性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 如果不希望多行显示的文字在显示时保持单词的完整性，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.TextWrapByWord = false;
	//@参数 逻辑值 
	//@别名 置依据文本自动折行(逻辑值)
	/*virtual*/ HRESULT set_TextWrapByWord(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_TextWrapByWord(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TextWrapToJustify，指定文字自动换行显示时是否自动拉伸文字间距进行两端分散对齐处理。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 如果不希望多行显示的文字是两端分散对齐的，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.TextWrapToJustify = false;
	//@别名 取文本折行两端分散对齐()
	/*virtual*/ BOOL get_TextWrapToJustify(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRUtility*)m_ptr.p)->get_TextWrapToJustify(&_result); return (VARIANT_TRUE==_result); }
	//@备注 TextWrapToJustify，指定文字自动换行显示时是否自动拉伸文字间距进行两端分散对齐处理。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 如果不希望多行显示的文字是两端分散对齐的，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.TextWrapToJustify = false;
	//@参数 逻辑值 
	//@别名 置文本折行两端分散对齐(逻辑值)
	/*virtual*/ HRESULT set_TextWrapToJustify(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_TextWrapToJustify(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TextLeftPunctuations，指定属于文字左侧标点符号的字符。
	// 文字如果属于左侧标点符号，则其不能显示在自动换行的行尾。
	// 不清楚需要设置那些字符，可以先将本属性值读取出来，然后去掉不需要的字符，补充增加的字符，然后设置本属性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@别名 取文本左边标点符号()
	/*virtual*/ CXText get_TextLeftPunctuations(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->get_TextLeftPunctuations(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TextLeftPunctuations，指定属于文字左侧标点符号的字符。
	// 文字如果属于左侧标点符号，则其不能显示在自动换行的行尾。
	// 不清楚需要设置那些字符，可以先将本属性值读取出来，然后去掉不需要的字符，补充增加的字符，然后设置本属性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@参数 文本 
	//@别名 置文本左边标点符号(文本)
	/*virtual*/ HRESULT set_TextLeftPunctuations(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_TextLeftPunctuations((BSTR)pVal); return _result; }
	//@备注 TextRightPunctuations，指定属于文字右侧标点符号的字符。
	// 文字如果属于右侧标点符号，则其不能显示在自动换行的行首。
	// 不清楚需要设置那些字符，可以先将本属性值读取出来，然后去掉不需要的字符，补充增加的字符，然后设置本属性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@别名 取文本右边标点符号()
	/*virtual*/ CXText get_TextRightPunctuations(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->get_TextRightPunctuations(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TextRightPunctuations，指定属于文字右侧标点符号的字符。
	// 文字如果属于右侧标点符号，则其不能显示在自动换行的行首。
	// 不清楚需要设置那些字符，可以先将本属性值读取出来，然后去掉不需要的字符，补充增加的字符，然后设置本属性。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	//@参数 文本 
	//@别名 置文本右边标点符号(文本)
	/*virtual*/ HRESULT set_TextRightPunctuations(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_TextRightPunctuations((BSTR)pVal); return _result; }
	//@备注 ColorFromRGB，根据三原色值生成一个颜色值。
	//@参数 红 颜色的红色因子，值范围0-255。 
	//@参数 绿 颜色的绿色因子，值范围0-255。
	//@参数 蓝 颜色的蓝色因子，值范围0-255。
	//@返回 返回值：生成的颜色值。
	//@别名 取RGB色值(红,绿,蓝)
	/*virtual*/ OLE_COLOR ColorFromRGB(/*[in]*/ long r, /*, [in]*/ long g, /*, [in]*/ long b/*, [out][retVal] OLE_COLOR* pColor*/){OLE_COLOR _result; ((IGRUtility*)m_ptr.p)->raw_ColorFromRGB(r, g, b, &_result); return _result; }
	/*virtual*/ CXText _GetResString(/*[in]*/ long ResID/*, [out][retVal] const wchar_t** String*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw__GetResString(ResID, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 ShrinkFontMinWidthRatio，指定报表在进行文字缩小字体适应处理时，允许压缩字体宽度的最小比例。
	// 有效值范围在0.5到1.0之间，如果将值设置为1.0，则进行文字缩小字体适应时，不进行字体宽度的压缩，字体宽度比例始终保持100%。
	// 本属性设置将影响到所有报表的运行，即所有报表的缩小字体适应处理将应用本属性。
	// 可以在报表主对象的“全局脚本”或“初始化脚本”属性中设置本属性值。
	//   Report.Utility.ShrinkFontMinWidthRatio = 1.0;//将值设置为1.0，禁止进行字体宽度压缩。
	//@返回 默认值0.5，有效值范围在0.5到1.0之间，如果将值设置为1.0，则进行文字缩小字体适应时，不进行字体宽度的压缩，字体宽度比例始终保持100%。
	//@别名 取字体最小缩放比()
	/*virtual*/ double get_ShrinkFontMinWidthRatio(/*[out][retVal] double* pVal*/){double _result=0; ((IGRUtility*)m_ptr.p)->get_ShrinkFontMinWidthRatio(&_result); return _result; }
	//@备注 ShrinkFontMinWidthRatio，指定报表在进行文字缩小字体适应处理时，允许压缩字体宽度的最小比例。
	// 有效值范围在0.5到1.0之间，如果将值设置为1.0，则进行文字缩小字体适应时，不进行字体宽度的压缩，字体宽度比例始终保持100%。
	// 本属性设置将影响到所有报表的运行，即所有报表的缩小字体适应处理将应用本属性。
	// 可以在报表主对象的“全局脚本”或“初始化脚本”属性中设置本属性值。
	//   Report.Utility.ShrinkFontMinWidthRatio = 1.0;//将值设置为1.0，禁止进行字体宽度压缩。
	//@参数 小数值 默认值0.5，有效值范围在0.5到1.0之间，如果将值设置为1.0，则进行文字缩小字体适应时，不进行字体宽度的压缩，字体宽度比例始终保持100%。
	//@别名 置字体最小缩放比(小数值)
	/*virtual*/ HRESULT set_ShrinkFontMinWidthRatio(/*[in]*/ double pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_ShrinkFontMinWidthRatio(pVal); return _result; }
	//@备注 DisableNormalMsg，指定报表在生成过程中是否禁止显示一般性提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableNormalMsg = true; //禁止显示一般性提示信息。
	//@别名 取禁止常规提示()
	/*virtual*/ BOOL get_DisableNormalMsg(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRUtility*)m_ptr.p)->get_DisableNormalMsg(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DisableNormalMsg，指定报表在生成过程中是否禁止显示一般性提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableNormalMsg = true; //禁止显示一般性提示信息。
	//@参数 逻辑值 
	//@别名 置禁止常规提示(逻辑值)
	/*virtual*/ HRESULT set_DisableNormalMsg(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_DisableNormalMsg(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DisableExceptionMsg，指定报表在生成过程中是否禁止显示异常提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableExceptionMsg = true; //禁止显示异常提示信息。
	//@别名 取禁止异常提示()
	/*virtual*/ BOOL get_DisableExceptionMsg(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRUtility*)m_ptr.p)->get_DisableExceptionMsg(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DisableExceptionMsg，指定报表在生成过程中是否禁止显示异常提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableExceptionMsg = true; //禁止显示异常提示信息。
	//@参数 逻辑值 
	//@别名 置禁止异常提示(逻辑值)
	/*virtual*/ HRESULT set_DisableExceptionMsg(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_DisableExceptionMsg(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 DisableHttpFailedMsg，指定报表在生成过程中是否禁止显示HTTP网络通讯失败提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableHttpFailedMsg = true; //禁止显示HTTP网络通讯失败提示信息。
	//@别名 取禁止提示HTTP通讯失败()
	/*virtual*/ BOOL get_DisableHttpFailedMsg(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRUtility*)m_ptr.p)->get_DisableHttpFailedMsg(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DisableHttpFailedMsg，指定报表在生成过程中是否禁止显示HTTP网络通讯失败提示信息。
	// 本属性设置是全局性的，将影响当前程序中所有报表的运行行为。
	// 报表打印预览显示器(PrintViewer)、报表查询显示器(DisplayViewer)与报表设计器(Designer)上的交互操作的相关提示信息不受此属性设置影响，即这些相关的提示信息也不能被禁止掉。
	// 编程说明
	// 如果不希望报表在运行过程中显示提示信息，可以在报表主对象的“初始化脚本”属性上写如下报表脚本：
	//   Report.Utility.DisableHttpFailedMsg = true; //禁止显示HTTP网络通讯失败提示信息。
	//@参数 逻辑值 
	//@别名 置禁止提示HTTP通讯失败(逻辑值)
	/*virtual*/ HRESULT set_DisableHttpFailedMsg(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRUtility*)m_ptr.p)->put_DisableHttpFailedMsg(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ HRESULT AppendResponseString(/*[in]*/ const wchar_t* Name, /*, [in]*/ const wchar_t* Value){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_AppendResponseString((BSTR)Name, (BSTR)Value); return _result; }
	/*virtual*/ HRESULT AppendResponseNumber(/*[in]*/ const wchar_t* Name, /*, [in]*/ double Value){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_AppendResponseNumber((BSTR)Name, Value); return _result; }
	/*virtual*/ HRESULT AppendResponseBoolean(/*[in]*/ const wchar_t* Name, /*, [in]*/ BOOL Value){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_AppendResponseBoolean((BSTR)Name, Value? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ CXText TransferResponse(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRUtility*)m_ptr.p)->raw_TransferResponse(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 FormatTextHeight，返回像素单位值。
	//@参数 文本串 
	//@参数 宽度 像素值
	//@参数 文本格式对象 
	//@参数 报表字体对象 若本参数为空，则以报表默认字体对象字号为基准进行计算。
	//@别名 取格式文本高度(文本串,宽度,文本格式对象,报表字体对象)
	/*virtual*/ long FormatTextHeight(/*[in]*/ const wchar_t* String, /*, [in]*/ long Width, /*, [in]*/ class CIGRTextFormat* TextFormat, /*, [in]*/ class CIGRFont* Font/*, [out][retVal] long* pVal*/);
	//@备注 FormatTextWidth，返回像素单位值。
	//@参数 文本串 
	//@参数 文本格式对象 
	//@参数 报表字体对象 若本参数为空，则以报表默认字体对象字号为基准进行计算。
	//@别名 取格式文本宽度(文本串,文本格式对象,报表字体对象)
	/*virtual*/ long FormatTextWidth(/*[in]*/ const wchar_t* String, /*, [in]*/ class CIGRTextFormat* TextFormat, /*, [in]*/ class CIGRFont* Font/*, [out][retVal] long* pVal*/);
	//@备注 FormatTextOutLen，在指定大小的区域中，可以输出的文字个数
	//@参数 文本串 
	//@参数 宽度 像素值
	//@参数 高度 像素值
	//@参数 文本格式对象 
	//@参数 报表字体对象 若本参数为空，则以报表默认字体对象字号为基准进行计算。
	//@别名 取格式文本输出个数(文本串,宽度,高度,文本格式对象,报表字体对象)
	/*virtual*/ long FormatTextOutLen(/*[in]*/ const wchar_t* Text, /*, [in]*/ long Width, /*, [in]*/ long Height, /*, [in]*/ class CIGRTextFormat* TextFormat, /*, [in]*/ class CIGRFont* Font/*, [out][retVal] long* pTextLen*/);
	//@备注 Alert，弹出一个消息对话框，将消息文字显示出来，主要用于报表脚本调试。
	// 如果是WEB报表服务器，消息文本将记录到日志文件中。
	//@参数 消息文本 显示的消息文本。
	//@别名 提示框(消息文本)
	/*virtual*/ HRESULT Alert(/*[in]*/ const wchar_t* Msg){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_Alert((BSTR)Msg); return _result; }
	//@备注 CalcCurveControlPoints，计算出绘制巴塞尔曲线的控制点位置。
	// 根据前点、中间点与后点这三点计算出绘制巴塞尔曲线的控制点位置，得到的控制点是两个，是相对于中间点的内侧控制点与外侧控制点。本函数不会直接返回这两个控制点的数据，而是在执行本函数后通过 CCPInnerX、CCPInnerY、CCPOuterX 与 CCPOuterY 这四个属性获取控制点的位置值。
	//@参数 前点X 前点的 X 位置。
	//@参数 前点Y 前点的 Y 位置。 
	//@参数 中间点X 中间点的 X 位置。 
	//@参数 中间点Y 中间点的 Y 位置。 
	//@参数 后点X 后点的 X 位置。 
	//@参数 后点Y 后点的 Y 位置。 
	//@别名 取巴塞尔曲线控制点(前点X,前点Y,中间点X,中间点Y,后点X,后点Y)
	/*virtual*/ HRESULT CalcCurveControlPoints(/*[in]*/ double xFirst, /*, [in]*/ double yFirst, /*, [in]*/ double xMiddle, /*, [in]*/ double yMiddle, /*, [in]*/ double xAfter, /*, [in]*/ double yAfter){ HRESULT _result = ((IGRUtility*)m_ptr.p)->raw_CalcCurveControlPoints(xFirst, yFirst, xMiddle, yMiddle, xAfter, yAfter); return _result; }
	//@备注 CCPInnerX，获取绘制巴塞尔曲线的内侧控制点的 X 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取内侧控制点X()
	/*virtual*/ double get_CCPInnerX(/*[out][retVal] double* pVal*/){double _result=0; ((IGRUtility*)m_ptr.p)->get_CCPInnerX(&_result); return _result; }
	//@备注 CCPInnerY，获取绘制巴塞尔曲线的内侧控制点的 Y 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取内侧控制点Y()
	/*virtual*/ double get_CCPInnerY(/*[out][retVal] double* pVal*/){double _result=0; ((IGRUtility*)m_ptr.p)->get_CCPInnerY(&_result); return _result; }
	//@备注 CCPOuterX，获取绘制巴塞尔曲线的外侧控制点的 X 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取外侧控制点X()
	/*virtual*/ double get_CCPOuterX(/*[out][retVal] double* pVal*/){double _result=0; ((IGRUtility*)m_ptr.p)->get_CCPOuterX(&_result); return _result; }
	//@备注 CCPOuterY，获取绘制巴塞尔曲线的外侧控制点的 Y 位置。
	// 在获取本属性值时，前面必须调用过 CalcCurveControlPoints 函数。
	//@别名 取外侧控制点Y()
	/*virtual*/ double get_CCPOuterY(/*[out][retVal] double* pVal*/){double _result=0; ((IGRUtility*)m_ptr.p)->get_CCPOuterY(&_result); return _result; }

};
//@备注 DateTime，应用工具，表示日期时间的对象。
//@别名 日期时间
class CIGRDateTime : public CXComObj /*IDispatch*/
{
public:
	CIGRDateTime(){};
	CIGRDateTime(IGRDateTime* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRDateTime* GetPtr(){ return ((IGRDateTime*)m_ptr.p); }
	//@备注 Year，获取年份整数值。
	//@别名 取年()
	/*virtual*/ long get_Year(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Year(&_result); return _result; }
	//@备注 Month，获取月份整数值。
	//@别名 取月()
	/*virtual*/ long get_Month(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Month(&_result); return _result; }
	//@备注 Day，获取月份中的日的整数值。
	//@别名 取日()
	/*virtual*/ long get_Day(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Day(&_result); return _result; }
	//@备注 Hour，获取小时的整数值。
	//@别名 取时()
	/*virtual*/ long get_Hour(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Hour(&_result); return _result; }
	//@备注 Minute，获取分钟的整数值。
	//@别名 取分()
	/*virtual*/ long get_Minute(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Minute(&_result); return _result; }
	//@备注 Second，获取秒的整数值。
	//@别名 取秒()
	/*virtual*/ long get_Second(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_Second(&_result); return _result; }
	//@备注 DayOfWeek，获取星期几的整数值。
	//@别名 取星期几()
	/*virtual*/ long get_DayOfWeek(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_DayOfWeek(&_result); return _result; }
	//@备注 DayOfYear，获取在年中的排序天数的整数值。
	//@别名 取第几天()
	/*virtual*/ long get_DayOfYear(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDateTime*)m_ptr.p)->get_DayOfYear(&_result); return _result; }
	//@备注 AsFloat，按小数值获取值。
	//@别名 取浮点数值()
	/*virtual*/ double get_AsFloat(/*[out][retVal] double* pVal*/){double _result=0; ((IGRDateTime*)m_ptr.p)->get_AsFloat(&_result); return _result; }
	//@备注 AsFloat，按小数值设置值。
	//@参数 小数值 
	//@别名 置浮点数值(小数值)
	/*virtual*/ HRESULT set_AsFloat(/*[in]*/ double pVal){ HRESULT _result = ((IGRDateTime*)m_ptr.p)->put_AsFloat(pVal); return _result; }
	//@备注 ValueFromDate，根据年月日产生日期时间值。
	//@参数 年 4位数值
	//@参数 月 1-2位数值，1-12
	//@参数 日 1-2位数值，1-31(28\\29\\30)
	//@别名 格式化日期(年,月,日)
	/*virtual*/ HRESULT ValueFromDate(/*[in]*/ long Year, /*, [in]*/ long Month, /*, [in]*/ long Day){ HRESULT _result = ((IGRDateTime*)m_ptr.p)->raw_ValueFromDate(Year, Month, Day); return _result; }
	//@备注 ValueFromDateTime，根据年月日时分秒产生日期时间值。
	//@参数 年 4位数值
	//@参数 月 1-2位数值，1-12
	//@参数 日 1-2位数值，1-31(28\\29\\30)
	//@参数 时 1-2位数值，0-23
	//@参数 分 1-2位数值，0-59
	//@参数 秒 1-2位数值，0-59
	//@别名 格式化时间(年,月,日,时,分,秒)
	/*virtual*/ HRESULT ValueFromDateTime(/*[in]*/ long Year, /*, [in]*/ long Month, /*, [in]*/ long Day, /*, [in]*/ long Hour, /*, [in]*/ long Minute, /*, [in]*/ long Second){ HRESULT _result = ((IGRDateTime*)m_ptr.p)->raw_ValueFromDateTime(Year, Month, Day, Hour, Minute, Second); return _result; }
	//@备注 Format，根据格式化串产生值的显示文字。
	//@参数 格式串 yyyy/MM/dd HH:mm:ss
	//@别名 格式化(格式串)
	/*virtual*/ CXText Format(/*[in]*/ const wchar_t* Format/*, [out][retVal] const wchar_t** Text*/){ BSTR _result = 0; CXText _result_text; ((IGRDateTime*)m_ptr.p)->raw_Format((BSTR)Format, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }

};
//@备注 Column，表示明细网格的列信息。明细网格拥有一组列，整个明细网格在垂直方向上按列切分。
// 每个列有显示宽度属性，每个列对应一个标题格，显示在标题行上，一个内容格，显示在内容行上。
// 一般情况下，如果一个字段的数据要显示出来，就需要定义一个对应的列。
// 列本身在输出时不能显示出来，而是通过标题格与内容格的显示来体现列的输出。
//@别名 列
class CIGRColumn : public CIGRObject
{
public:
	CIGRColumn(){};
	CIGRColumn(IGRColumn* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumn* GetPtr(){ return ((IGRColumn*)m_ptr.p); }
	//@备注 TitleCell，获取拥有的标题格对象的接口引用。
	//@别名 取标题格()
	/*virtual*/ class CIGRColumnTitleCell get_TitleCell(/*[out][retVal] class CIGRColumnTitleCell** pVal*/);
	//@备注 ContentCell，本列对应的内容格的接口引用。
	//@别名 取内容格()
	/*virtual*/ class CIGRColumnContentCell get_ContentCell(/*[out][retVal] class CIGRColumnContentCell** pVal*/);
	//@备注 Parent，获取父对象引用，拥有列的明细网格的接口引用。
	//@别名 取父对象()
	/*virtual*/ class CIGRDetailGrid get_Parent(/*[out][retVal] class CIGRDetailGrid** pVal*/);
	//@备注 Name，列的名称标识，必须保证每个列的名称唯一。
	// 列、对应标题格与对应内容格三者的名称始终保持一致，改变其中任一个的名称也会同时改变另外两者的名称。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRColumn*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，列的名称标识，必须保证每个列的名称唯一。
	// 列、对应标题格与对应内容格三者的名称始终保持一致，改变其中任一个的名称也会同时改变另外两者的名称。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRColumn*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	//@备注 Visible，指定列在输出时是否可见。
	// 如果Visible属性值为假，则本列在屏幕显示与打印生成时将被忽略掉。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumn*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，指定列在输出时是否可见。
	// 如果Visible属性值为假，则本列在屏幕显示与打印生成时将被忽略掉。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumn*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Width，列的显示宽度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 列的显示宽度，以报表使用的计量单位表示的输出宽度值。此属性代表列在设计时的宽度，当其输出时显示的宽度有可能与设计时的宽度不一致。
	// 例如，当明细网格的打印方法为列适应输出区域宽度，则列的宽度将按比例进行伸缩以刚好适应输出页面的输出区域宽度。
	//@别名 取宽度()
	/*virtual*/ double get_Width(/*[out][retVal] double* pVal*/){double _result=0; ((IGRColumn*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Width，列的显示宽度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 列的显示宽度，以报表使用的计量单位表示的输出宽度值。此属性代表列在设计时的宽度，当其输出时显示的宽度有可能与设计时的宽度不一致。
	// 例如，当明细网格的打印方法为列适应输出区域宽度，则列的宽度将按比例进行伸缩以刚好适应输出页面的输出区域宽度。
	//@参数 小数值 
	//@别名 置宽度(小数值)
	/*virtual*/ HRESULT set_Width(/*[in]*/ double pVal){ HRESULT _result = ((IGRColumn*)m_ptr.p)->put_Width(pVal); return _result; }
	//@备注 FixedWidth，在打印输出时，此列宽度是否始终按设计时宽度输出。
	//@别名 取宽度固定()
	/*virtual*/ BOOL get_FixedWidth(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumn*)m_ptr.p)->get_FixedWidth(&_result); return (VARIANT_TRUE==_result); }
	//@备注 FixedWidth，在打印输出时，此列宽度是否始终按设计时宽度输出。
	//@参数 逻辑值 
	//@别名 置宽度固定(逻辑值)
	/*virtual*/ HRESULT set_FixedWidth(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumn*)m_ptr.p)->put_FixedWidth(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@别名 取锁定()
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRColumn*)m_ptr.p)->get_Lock(&_result); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@参数 锁定类别枚举 
	//@别名 置锁定(锁定类别枚举)
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRColumn*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 CellBase，基类，报表中各种单元格接口的基接口，之前叫单元格基类，其实应该叫单元格，(单元格(列格)、标题格、内容格、自由表格子格)。
//@别名 单元格
class CIGRCellBase : public CIGRObject
{
public:
	CIGRCellBase(){};
	CIGRCellBase(IGRCellBase* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRCellBase* GetPtr(){ return ((IGRCellBase*)m_ptr.p); }
	//@备注 Border，绘制单元格的边框定义对象。
	//@别名 取边框()
	/*virtual*/ class CIGRBorder get_Border(/*[out][retVal] class CIGRBorder** pVal*/);
	//@备注 TextFormat，输出单元格文字的格式定义对象。
	//@别名 取文本格式()
	/*virtual*/ class CIGRTextFormat get_TextFormat(/*[out][retVal] class CIGRTextFormat** pVal*/);
	//@备注 Font，显示单元格文字的字体定义对象。如果单元格是非自由格，此属性表示输出显示文本使用的字体，如果单元格是自由格，此属性表示单元格拥有的部件框的缺省字体。
	//@别名 取字体()
	/*virtual*/ class CIGRFont get_Font(/*[out][retVal] class CIGRFont** pVal*/);
	//@备注 Controls，本单元格所拥有的部件框集合对象。如果格不是自由格时，因非自由格不是部件框容器，所以本属性值为NULL。
	//@别名 取部件框集合()
	/*virtual*/ class CIGRControls get_Controls(/*[out][retVal] class CIGRControls** pVal*/);
	//@备注 FreeCell，指定本单元格是否为自由格。
	// 当本属性为真时，单元格为自由格，单元格成为部件框容器，可以添加任意个数自由排列的部件框到单元格中；当本属性为假时，单元格不是部件框容器，不能向格中插入部件框，单元格本身可以显示输出文本。
	//@别名 取自由格()
	/*virtual*/ BOOL get_FreeCell(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_FreeCell(&_result); return (VARIANT_TRUE==_result); }
	//@备注 FreeCell，指定本单元格是否为自由格。
	// 当本属性为真时，单元格为自由格，单元格成为部件框容器，可以添加任意个数自由排列的部件框到单元格中；当本属性为假时，单元格不是部件框容器，不能向格中插入部件框，单元格本身可以显示输出文本。
	//@参数 逻辑值 
	//@别名 置自由格(逻辑值)
	/*virtual*/ HRESULT set_FreeCell(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_FreeCell(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BorderCustom，指示单元格的边框是否自身特别定义。
	// 如果本属性值为否，则此单元格的边框按照“边框”属性中的定义来进行绘制，反之单元格不进行单独的边框绘制，而是由父对象在其外围输出行线或列线。
	//@别名 取边框自定义()
	/*virtual*/ BOOL get_BorderCustom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_BorderCustom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BorderCustom，指示单元格的边框是否自身特别定义。
	// 如果本属性值为否，则此单元格的边框按照“边框”属性中的定义来进行绘制，反之单元格不进行单独的边框绘制，而是由父对象在其外围输出行线或列线。
	//@参数 逻辑值 
	//@别名 置边框自定义(逻辑值)
	/*virtual*/ HRESULT set_BorderCustom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_BorderCustom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BackColor，指定单元格的背景色。如果 BackStyle 属性为 grbsTranparent 时，单元格生成时不填充背景，本属性此时被忽略掉。
	//@别名 取背景色()
	/*virtual*/ OLE_COLOR get_BackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRCellBase*)m_ptr.p)->get_BackColor(&_result); return _result; }
	//@备注 BackColor，指定单元格的背景色。如果 BackStyle 属性为 grbsTranparent 时，单元格生成时不填充背景，本属性此时被忽略掉。
	//@参数 颜色值 
	//@别名 置背景色(颜色值)
	/*virtual*/ HRESULT set_BackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_BackColor(pVal); return _result; }
	//@备注 ForeColor，指定单元格的输出文本的文字颜色。注意：只有在单元格是非自由格时，才允许使用本属性。
	//@别名 取前景色()
	/*virtual*/ OLE_COLOR get_ForeColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRCellBase*)m_ptr.p)->get_ForeColor(&_result); return _result; }
	//@备注 ForeColor，指定单元格的输出文本的文字颜色。注意：只有在单元格是非自由格时，才允许使用本属性。
	//@参数 颜色值 
	//@别名 置前景色(颜色值)
	/*virtual*/ HRESULT set_ForeColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_ForeColor(pVal); return _result; }
	//@备注 CanGrow，指定单元格在运行时是否可以伸展高度。如果文字要多行显示，应该将“文字自动绕行”属性设为“是”这样才会得到想要的伸展效果。
	//@别名 取可伸展()
	/*virtual*/ BOOL get_CanGrow(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_CanGrow(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanGrow，指定单元格在运行时是否可以伸展高度。如果文字要多行显示，应该将“文字自动绕行”属性设为“是”这样才会得到想要的伸展效果。
	//@参数 逻辑值 
	//@别名 置可伸展(逻辑值)
	/*virtual*/ HRESULT set_CanGrow(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_CanGrow(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CanShrink，指定内容格在运行时是否可以收缩高度。
	//@别名 取可收缩()
	/*virtual*/ BOOL get_CanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_CanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CanShrink，指定内容格在运行时是否可以收缩高度。
	//@参数 逻辑值 
	//@别名 置可收缩(逻辑值)
	/*virtual*/ HRESULT set_CanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_CanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PrintType，指定单元格的打印生成类别：1、表单； 2、内容
	//@别名 取打印类别()
	/*virtual*/ GRPrintType get_PrintType(/*[out][retVal] GRPrintType* pVal*/){GRPrintType _result; ((IGRCellBase*)m_ptr.p)->get_PrintType(&_result); return _result; }
	//@备注 PrintType，指定单元格的打印生成类别：1、表单； 2、内容
	//@参数 打印类别枚举值 
	//@别名 置打印类别(打印类别枚举值)
	/*virtual*/ HRESULT set_PrintType(/*[in]*/ GRPrintType pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_PrintType(pVal); return _result; }
	//@备注 Cursor，指定在查询显示报表时，在此单元格上显示的鼠标光标。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@别名 取光标()
	/*virtual*/ GRDisplayCursor get_Cursor(/*[out][retVal] GRDisplayCursor* pVal*/){GRDisplayCursor _result; ((IGRCellBase*)m_ptr.p)->get_Cursor(&_result); return _result; }
	//@备注 Cursor，指定在查询显示报表时，在此单元格上显示的鼠标光标。
	// 0、默认光标； 1、箭头光标； 2、放大光标； 3、手指光标； 4、确定光标； 5、否定光标
	//@参数 光标类型枚举值 
	//@别名 置光标(光标类型枚举值)
	/*virtual*/ HRESULT set_Cursor(/*[in]*/ GRDisplayCursor pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_Cursor(pVal); return _result; }
	//@备注 ShrinkFontToFit，在单元格的显示区域不能完整显示出文字内容时，指定是否自动缩小文字大小让文字完整显示出来。
	// 在格为自由格时，此属性无效。 
	// 注意：缩小字体功能只有在打印与打印预览时才有效果，即查询显示时不支持字体缩小适应。
	//@别名 取按需缩小字体()
	/*virtual*/ BOOL get_ShrinkFontToFit(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_ShrinkFontToFit(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShrinkFontToFit，在单元格的显示区域不能完整显示出文字内容时，指定是否自动缩小文字大小让文字完整显示出来。
	// 在格为自由格时，此属性无效。 
	// 注意：缩小字体功能只有在打印与打印预览时才有效果，即查询显示时不支持字体缩小适应。
	//@参数 逻辑值 
	//@别名 置按需缩小字体(逻辑值)
	/*virtual*/ HRESULT set_ShrinkFontToFit(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_ShrinkFontToFit(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PaddingLeft，指定单元格输出文字的左边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@返回 默认值2
	//@别名 取左边距()
	/*virtual*/ long get_PaddingLeft(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCellBase*)m_ptr.p)->get_PaddingLeft(&_result); return _result; }
	//@备注 PaddingLeft，指定单元格输出文字的左边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@参数 像素值 默认值2
	//@别名 置左边距(像素值)
	/*virtual*/ HRESULT set_PaddingLeft(/*[in]*/ long pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_PaddingLeft(pVal); return _result; }
	//@备注 PaddingRight，指定单元格输出文字的右边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@返回 默认值1
	//@别名 取右边距()
	/*virtual*/ long get_PaddingRight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCellBase*)m_ptr.p)->get_PaddingRight(&_result); return _result; }
	//@备注 PaddingRight，指定单元格输出文字的右边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@参数 像素值 默认值1
	//@别名 置右边距(像素值)
	/*virtual*/ HRESULT set_PaddingRight(/*[in]*/ long pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_PaddingRight(pVal); return _result; }
	//@备注 PaddingTop，指定单元格输出文字的上边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@返回 默认值1
	//@别名 取上边距()
	/*virtual*/ long get_PaddingTop(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCellBase*)m_ptr.p)->get_PaddingTop(&_result); return _result; }
	//@备注 PaddingTop，指定单元格输出文字的上边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@参数 像素值 默认值1
	//@别名 置上边距(像素值)
	/*virtual*/ HRESULT set_PaddingTop(/*[in]*/ long pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_PaddingTop(pVal); return _result; }
	//@备注 PaddingBottom，指定单元格输出文字的下边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@返回 默认值1
	//@别名 取下边距()
	/*virtual*/ long get_PaddingBottom(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCellBase*)m_ptr.p)->get_PaddingBottom(&_result); return _result; }
	//@备注 PaddingBottom，指定单元格输出文字的下边距，以屏幕像素为单位。此属性仅在单元格为非自由格时才可用。
	//@参数 像素值 默认值1
	//@别名 置下边距(像素值)
	/*virtual*/ HRESULT set_PaddingBottom(/*[in]*/ long pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_PaddingBottom(pVal); return _result; }
	//@备注 ShowMoneyLabel，指定是否在此单元格中显示金额标签。注意：只有在格不是自由格时，才允许使用本属性。
	//@别名 取显示金额标签()
	/*virtual*/ BOOL get_ShowMoneyLabel(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_ShowMoneyLabel(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowMoneyLabel，指定是否在此单元格中显示金额标签。注意：只有在格不是自由格时，才允许使用本属性。
	//@参数 逻辑值 
	//@别名 置显示金额标签(逻辑值)
	/*virtual*/ HRESULT set_ShowMoneyLabel(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_ShowMoneyLabel(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowMoneyLine，指定是否在此单元格中将值显示成金额线格式。注意：只有在格不是自由格时，才允许使用本属性。
	//@别名 取显示金额线()
	/*virtual*/ BOOL get_ShowMoneyLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCellBase*)m_ptr.p)->get_ShowMoneyLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowMoneyLine，指定是否在此单元格中将值显示成金额线格式。注意：只有在格不是自由格时，才允许使用本属性。
	//@参数 逻辑值 
	//@别名 置显示金额线(逻辑值)
	/*virtual*/ HRESULT set_ShowMoneyLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_ShowMoneyLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ HRESULT LoadCursorFile(/*[in]*/ const wchar_t* PathFile){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->raw_LoadCursorFile((BSTR)PathFile); return _result; }
	/*virtual*/ OLE_HANDLE get__CursorHandle(/*[out][retVal] OLE_HANDLE* pVal*/){OLE_HANDLE _result; ((IGRCellBase*)m_ptr.p)->get__CursorHandle(&_result); return _result; }
	/*virtual*/ CXText get_GetDisplayTextScript(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCellBase*)m_ptr.p)->get_GetDisplayTextScript(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_GetDisplayTextScript(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCellBase*)m_ptr.p)->put_GetDisplayTextScript((BSTR)pVal); return _result; }

};
//@备注 ColumnCell，基类，明细网格中单元格接口的基接口（之前叫单元格，其实应该叫列格，包含：标题格、内容格）。
// 说明：明细网格的标题行与内容行的显示区域划分为一个个的单元格，单元格可以直接显示文字，也可以作为部件框容器使用，作为部件框容器的单元格称为自由格。
// 标题行中的单元格称为标题格，内容行中的单元格称为内容格。
//@别名 列格
class CIGRColumnCell : public CIGRCellBase
{
public:
	CIGRColumnCell(){};
	CIGRColumnCell(IGRColumnCell* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnCell* GetPtr(){ return ((IGRColumnCell*)m_ptr.p); }
	//@备注 Column，本单元格对应的列的接口引用。
	// 单元格按照列的宽度与顺序进行排列，一个列对应有一个标题格与一个内容格。
	// 如果是组标题格，因为组标题格不存在唯一对应的某个列，所以本属性值为NULL。
	//@别名 取列()
	/*virtual*/ class CIGRColumn get_Column(/*[out][retVal] class CIGRColumn** pVal*/);
	//@备注 Name，指定单元格的名称标识。
	// 注意：当为内容格或当为标题格而不是组标题格时，即格存在对应列，格的名称与列的名称保持一致。
	// 当改变格的名称也同时改变列的名称，反之改变列的名称也同时改变格的名称。
	//@别名 取名称()
	/*virtual*/ CXText get_Name(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRColumnCell*)m_ptr.p)->get_Name(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Name，指定单元格的名称标识。
	// 注意：当为内容格或当为标题格而不是组标题格时，即格存在对应列，格的名称与列的名称保持一致。
	// 当改变格的名称也同时改变列的名称，反之改变列的名称也同时改变格的名称。
	//@参数 名称 
	//@别名 置名称(名称)
	/*virtual*/ HRESULT set_Name(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRColumnCell*)m_ptr.p)->put_Name((BSTR)pVal); return _result; }
	/*virtual*/ BOOL get_WordWrap(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnCell*)m_ptr.p)->get_WordWrap(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_WordWrap(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnCell*)m_ptr.p)->put_WordWrap(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_EndEllipsis(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnCell*)m_ptr.p)->get_EndEllipsis(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_EndEllipsis(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnCell*)m_ptr.p)->put_EndEllipsis(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRTextAlign get_TextAlign(/*[out][retVal] GRTextAlign* pVal*/){GRTextAlign _result; ((IGRColumnCell*)m_ptr.p)->get_TextAlign(&_result); return _result; }
	/*virtual*/ HRESULT set_TextAlign(/*[in]*/ GRTextAlign pVal){ HRESULT _result = ((IGRColumnCell*)m_ptr.p)->put_TextAlign(pVal); return _result; }

};
//@备注 ColumnTitleCell，表示明细网格的标题行中的标题格，每个列对应一个标题格，一个拥有下级标题格的标题格称为组标题格，组标题格不与某个具体的列唯一对应。
// 每当增加一个明细网格的列之后，都会在标题行添加一个对应的显示单元格。一般在明细网格的标题格中定义列的标题文字。
// 当我们需要定义多层标题时，具有下级标题的标题也要在标题行添加一个对应的显示单元格，这两种类型的单元格称为标题格。
// 如果把标题格设为自由格，则标题格成为部件框容器，可以向标题格添加部件框。
//@别名 标题格
class CIGRColumnTitleCell : public CIGRColumnCell
{
public:
	CIGRColumnTitleCell(){};
	CIGRColumnTitleCell(IGRColumnTitleCell* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnTitleCell* GetPtr(){ return ((IGRColumnTitleCell*)m_ptr.p); }
	//@备注 Visible，指定是否显示本标题格。
	// 当标题格不是组标题格时，本属性与其对应的列的 Visible 属性保持一致。
	// 当标题格是组标题格时，当本属性为假时，本组标题格所包含的所有列在输出时都将被忽略掉，而不管所包含的列自身的 Visible 属性为何值。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnTitleCell*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，指定是否显示本标题格。
	// 当标题格不是组标题格时，本属性与其对应的列的 Visible 属性保持一致。
	// 当标题格是组标题格时，当本属性为假时，本组标题格所包含的所有列在输出时都将被忽略掉，而不管所包含的列自身的 Visible 属性为何值。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnTitleCell*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GroupTitle，指定本标题格是否为组标题格。
	// 组标题格不是由列自动创建，也不与一个列关联。
	// 组标题格包含数个下级标题格，从而使网格标题具有层次关系。
	//@返回 本属性为真，标题格称为组标题格。
	//@别名 取组标题格()
	/*virtual*/ BOOL get_GroupTitle(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnTitleCell*)m_ptr.p)->get_GroupTitle(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Text，指定标题格的显示文本。
	// 注意：本属性只能在标题格为非自由格时使用。
	//@别名 取文本()
	/*virtual*/ CXText get_Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRColumnTitleCell*)m_ptr.p)->get_Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Text，指定标题格的显示文本。
	// 注意：本属性只能在标题格为非自由格时使用。
	//@参数 文本 显示的文字
	//@别名 置文本(文本)
	/*virtual*/ HRESULT set_Text(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRColumnTitleCell*)m_ptr.p)->put_Text((BSTR)pVal); return _result; }
	//@备注 Height，指定组标题格的高度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 在定义多层表头时，使用本属性指定组标题格的高度，指定不同的属性值可以得到层高不等的多层表头表格。
	// 如果为默认值 0，则使用根据多层表头的层数求得的每层平均高度。
	// 本属性仅对组标题格有效。
	//@别名 取高度()
	/*virtual*/ double get_Height(/*[out][retVal] double* pVal*/){double _result=0; ((IGRColumnTitleCell*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 Height，指定组标题格的高度。以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	// 在定义多层表头时，使用本属性指定组标题格的高度，指定不同的属性值可以得到层高不等的多层表头表格。
	// 如果为默认值 0，则使用根据多层表头的层数求得的每层平均高度。
	// 本属性仅对组标题格有效。
	//@参数 高度值 
	//@别名 置高度(高度值)
	/*virtual*/ HRESULT set_Height(/*[in]*/ double pVal){ HRESULT _result = ((IGRColumnTitleCell*)m_ptr.p)->put_Height(pVal); return _result; }
	//@备注 Parent，获取拥有本标题格的标题行对象的接口引用。
	//@别名 取父对象()
	/*virtual*/ class CIGRColumnTitle get_Parent(/*[out][retVal] class CIGRColumnTitle** pVal*/);
	//@备注 SubTitles，获取本标题格拥有的直接下级标题格集合对象的接口引用。
	//@别名 取下级标题格集合()
	/*virtual*/ class CIGRColumnTitleCells get_SubTitles(/*[out][retVal] class CIGRColumnTitleCells** pVal*/);
	//@备注 SupCell，获取本标题格的上级组标题格。
	// 如果本标题格是组标题格下面的，本属性获得其上级组标题格的接口引用。否则本属性为空值。
	//@别名 取上级组标题格()
	/*virtual*/ class CIGRColumnTitleCell get_SupCell(/*[out][retVal] class CIGRColumnTitleCell** pVal*/);
	//@备注 EncloseColumn，将一个列对应的标题格包含到此组标题格中，新包含进来的列标题格在显示顺序上处于本组的最后。
	// 只有当标题格为组标题格时，才能调用本方法。
	//@参数 列序号 指定被包含列的顺序号，序号从1开始。
	//@别名 包含指定列号(列序号)
	/*virtual*/ HRESULT EncloseColumn(/*[in]*/ VARIANT ColumnIndex){ HRESULT _result = ((IGRColumnTitleCell*)m_ptr.p)->raw_EncloseColumn(ColumnIndex); return _result; }
	//@备注 AddSubGroupTitle，在此组标题格中增加一个下级组标题格。
	// 在一个组标题格中，如果还需要包括下级组标题格，则调用本方法进行定义。
	//@参数 名称 新增组标题格的名称标识。
	//@参数 标题 新增组标题格的显示文本。 
	//@返回 新增下级组标题格对象的接口引用。
	//@别名 增加下级组标题格(名称,标题)
	/*virtual*/ class CIGRColumnTitleCell AddSubGroupTitle(/*[in]*/ const wchar_t* Name, /*, [in]*/ const wchar_t* Title/*, [out][retVal] class CIGRColumnTitleCell** ppTitle*/);
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRColumnTitleCell*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRColumnTitleCell*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ColumnTitle，表示明细网格的标题行的接口。其拥有一组标题格，标题格在显示排列上具有层次关系，可以定义多层表头。
// 标题行一般显示在明细网格的最上端，通常只在明细网格开始时输出一次。标题行拥有所有标题格，标题行显示区域被一个个标题格所划分。
//@别名 标题行
class CIGRColumnTitle : public CIGRColumnSection
{
public:
	CIGRColumnTitle(){};
	CIGRColumnTitle(IGRColumnTitle* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnTitle* GetPtr(){ return ((IGRColumnTitle*)m_ptr.p); }
	//@备注 TitleCells，获取拥有的标题格集合对象的接口引用。
	//@别名 取标题格集合()
	/*virtual*/ class CIGRColumnTitleCells get_TitleCells(/*[out][retVal] class CIGRColumnTitleCells** pVal*/);
	//@备注 RepeatStyle，在打印生成时，指定明细网格标题的重复输出方式。
	// 一般标题行只在明细网格的开始位置输出显示一次，当指定重复方式之后，标题行就可以多次输出。
	//@别名 取重复打印方式()
	/*virtual*/ GRRepeatStyle get_RepeatStyle(/*[out][retVal] GRRepeatStyle* pVal*/){GRRepeatStyle _result; ((IGRColumnTitle*)m_ptr.p)->get_RepeatStyle(&_result); return _result; }
	//@备注 RepeatStyle，在打印生成时，指定明细网格标题的重复输出方式。
	// 一般标题行只在明细网格的开始位置输出显示一次，当指定重复方式之后，标题行就可以多次输出。
	//@参数 重复方式枚举值 
	//@别名 置重复打印方式(重复方式枚举值)
	/*virtual*/ HRESULT set_RepeatStyle(/*[in]*/ GRRepeatStyle pVal){ HRESULT _result = ((IGRColumnTitle*)m_ptr.p)->put_RepeatStyle(pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRColumnTitle*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRColumnTitle*)m_ptr.p)->put_Lock(pVal); return _result; }
	//@备注 BeforeHeaders，标题行在每页重复的分组头与页分组头之前显示。
	//@别名 取在页组头前显示()
	/*virtual*/ BOOL get_BeforeHeaders(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRColumnTitle*)m_ptr.p)->get_BeforeHeaders(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BeforeHeaders，标题行在每页重复的分组头与页分组头之前显示。
	//@参数 逻辑值 
	//@别名 置在页组头前显示(逻辑值)
	/*virtual*/ HRESULT set_BeforeHeaders(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRColumnTitle*)m_ptr.p)->put_BeforeHeaders(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 ColumnTitleCells，集合对象，标题行的拥有的标题格集合对象的接口。
// 与列对应的标题格伴随列的创建而创建，伴随列的移除而移除，但组标题格不存在唯一对应的列，其创建与移除独立于列。
// 所以在此集合对象中不提供增加与移除集合元素的通常方法，但提供AddGroup与RemoveGroup方法专门用来增加与移除组标题格。
//@别名 标题格集合
class CIGRColumnTitleCells : public CXComObj /*IDispatch*/
{
public:
	CIGRColumnTitleCells(){};
	CIGRColumnTitleCells(IGRColumnTitleCells* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnTitleCells* GetPtr(){ return ((IGRColumnTitleCells*)m_ptr.p); }
	//@备注 Count，指示拥有标题格的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRColumnTitleCells*)m_ptr.p)->get_Count(&_result); return _result; }
	/*virtual*/ class CIGRColumnTitleCell get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRColumnTitleCell** ppColumnTitleCell*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRColumnTitleCells*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 AddGroup，
	//@参数 名称 新增组标题格的名称。
	//@参数 标题 新增组标题格的显示文本。
	//@返回 新增组标题格的接口引用。
	//@别名 增加组标题格(名称,标题)
	/*virtual*/ class CIGRColumnTitleCell AddGroup(/*[in]*/ const wchar_t* Name, /*, [in]*/ const wchar_t* Title/*, [out][retVal] class CIGRColumnTitleCell** ppItem*/);
	//@备注 RemoveGroup，根据组标题格的顺序号移除一个组标题格。
	// 只有当指定序号的标题格存在，并且此标题格是组标题格时，才能成功移除标题格。
	//@参数 序号 指示准备移除的组标题格的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT RemoveGroup(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRColumnTitleCells*)m_ptr.p)->raw_RemoveGroup(Index); return _result; }
	//@备注 IndexByName，根据标题格的名称取得其顺序号，如果不存在与名称匹配的标题格，则返回-1。标题格的名称不区分字母大小写。
	//@参数 名称 指定查找标题格的名称。
	//@返回 如果有匹配的标题格，返回其顺序号，否则返回-1。
	// 
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRColumnTitleCells*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的标题格对象，序号从1开始。
	//@参数 序号 指定标题格对象在集合中的序号，从1开始。 
	//@返回 获取到的标题格对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRColumnTitleCell ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRColumnTitleCell** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数标题格的顺序。
	//@参数 序号 指定标题格的序号，序号从1开始。
	//@参数 新顺序号 标题格在集合中的新序号，从1开始。
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRColumnTitleCells*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 ColumnContentCell，表示明细网格的内容行中每个列对应的内容格，内容行拥有一组内容格。
// 每当增加一个明细网格的列之后，都会在内容行添加一个对应的显示单元格，此种显示单元格称为内容格。
// 一般每个内容格关联一个字段，用来显示字段的内容。
// 如果把内容格设为自由格，则内容格成为部件框容器，可以向内容格添加部件框。
//@别名 内容格
class CIGRColumnContentCell : public CIGRColumnCell
{
public:
	CIGRColumnContentCell(){};
	CIGRColumnContentCell(IGRColumnContentCell* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnContentCell* GetPtr(){ return ((IGRColumnContentCell*)m_ptr.p); }
	//@备注 Parent，获取拥有本内容格的内容行的接口引用。
	//@别名 取父对象()
	/*virtual*/ class CIGRColumnContent get_Parent(/*[out][retVal] class CIGRColumnContent** pVal*/);
	//@备注 DataField，指定本内容格关联的记录集字段的名称，在运行时将显示关联字段的显示文字。
	// 注意：本属性只能在内容格为非自由格时使用。
	//@别名 取数据字段()
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRColumnContentCell*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataField，指定本内容格关联的记录集字段的名称，在运行时将显示关联字段的显示文字。
	// 注意：本属性只能在内容格为非自由格时使用。
	//@参数 字段名称 
	//@别名 置数据字段(字段名称)
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRColumnContentCell*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRColumnContentCell*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRColumnContentCell*)m_ptr.p)->put_Lock(pVal); return _result; }

};
class CIGRSharePrintSetupObject : public CXComObj /*IDispatch*/
{
public:
	CIGRSharePrintSetupObject(){};
	CIGRSharePrintSetupObject(IGRSharePrintSetupObject* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRSharePrintSetupObject* GetPtr(){ return ((IGRSharePrintSetupObject*)m_ptr.p); }
	/*virtual*/ double get_LeftMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_LeftMargin(&_result); return _result; }
	/*virtual*/ HRESULT set_LeftMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_LeftMargin(pVal); return _result; }
	/*virtual*/ double get_RightMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_RightMargin(&_result); return _result; }
	/*virtual*/ HRESULT set_RightMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_RightMargin(pVal); return _result; }
	/*virtual*/ double get_TopMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_TopMargin(&_result); return _result; }
	/*virtual*/ HRESULT set_TopMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_TopMargin(pVal); return _result; }
	/*virtual*/ double get_BottomMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_BottomMargin(&_result); return _result; }
	/*virtual*/ HRESULT set_BottomMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_BottomMargin(pVal); return _result; }
	/*virtual*/ double get_PaperWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperWidth(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperWidth(pVal); return _result; }
	/*virtual*/ double get_PaperLength(/*[out][retVal] double* pVal*/){double _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperLength(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperLength(/*[in]*/ double pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperLength(pVal); return _result; }
	/*virtual*/ GRPaperOrientation get_PaperOrientation(/*[out][retVal] GRPaperOrientation* pVal*/){GRPaperOrientation _result; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperOrientation(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperOrientation(/*[in]*/ GRPaperOrientation pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperOrientation(pVal); return _result; }
	/*virtual*/ long get_PaperSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperSize(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperSize(pVal); return _result; }
	/*virtual*/ CXText get_PaperName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_PaperName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperName((BSTR)pVal); return _result; }
	/*virtual*/ CXText get_PrinterName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PrinterName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_PrinterName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PrinterName((BSTR)pVal); return _result; }
	/*virtual*/ GRPaperSourceKind get_PaperSource(/*[out][retVal] GRPaperSourceKind* pVal*/){GRPaperSourceKind _result; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperSource(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperSource(/*[in]*/ GRPaperSourceKind pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperSource(pVal); return _result; }
	/*virtual*/ GRUnit get_Unit(/*[out][retVal] GRUnit* pVal*/){GRUnit _result; ((IGRSharePrintSetupObject*)m_ptr.p)->get_Unit(&_result); return _result; }
	/*virtual*/ HRESULT set_Unit(/*[in]*/ GRUnit pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_Unit(pVal); return _result; }
	/*virtual*/ GRPaperKind get_PaperKind(/*[out][retVal] GRPaperKind* pVal*/){GRPaperKind _result; ((IGRSharePrintSetupObject*)m_ptr.p)->get_PaperKind(&_result); return _result; }
	/*virtual*/ HRESULT set_PaperKind(/*[in]*/ GRPaperKind pVal){ HRESULT _result = ((IGRSharePrintSetupObject*)m_ptr.p)->put_PaperKind(pVal); return _result; }
	/*virtual*/ BOOL PrintDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->raw_PrintDialog(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL PrinterSetupDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->raw_PrinterSetupDialog(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL PageSetupDialog(/*[out][retVal] BOOL* pSucceeded*/){VARIANT_BOOL _result=0; ((IGRSharePrintSetupObject*)m_ptr.p)->raw_PageSetupDialog(&_result); return (VARIANT_TRUE==_result); }

};
//@备注 ExportOption，数据导出选项的基类。
//@别名 导出选项
class CIGRExportOption : public CXComObj /*IDispatch*/
{
public:
	CIGRExportOption(){};
	CIGRExportOption(IGRExportOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRExportOption* GetPtr(){ return ((IGRExportOption*)m_ptr.p); }
	//@备注 FileName，获取导出文件的完整路径与文件名称。
	//@别名 取文件名()
	/*virtual*/ CXText get_FileName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRExportOption*)m_ptr.p)->get_FileName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 FileName，设置导出文件的完整路径与文件名称。
	//@参数 文件名 指定导出文件的完整路径与文件名称。
	//@别名 置文件名(文件名)
	/*virtual*/ HRESULT set_FileName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_FileName((BSTR)pVal); return _result; }
	//@备注 ExportType，获取本导出文件选项对象的具体类型。
	//@返回 1、导出XLS； 2、导出TXT； 3、导出HTM； 4、导出RTF； 5、导出PDF； 6、导出CSV； 7、导出IMG
	//@别名 取导出类型()
	/*virtual*/ GRExportType get_ExportType(/*[out][retVal] GRExportType* pVal*/){GRExportType _result; ((IGRExportOption*)m_ptr.p)->get_ExportType(&_result); return _result; }
	//@备注 MailExportFile，指定在导出之后是否启动邮件发送程序发送该导出文档。
	//@别名 取导出后发送邮件()
	/*virtual*/ BOOL get_MailExportFile(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRExportOption*)m_ptr.p)->get_MailExportFile(&_result); return (VARIANT_TRUE==_result); }
	//@备注 MailExportFile，指定在导出之后是否启动邮件发送程序发送该导出文档。
	//@参数 逻辑值 
	//@别名 置导出后发送邮件(逻辑值)
	/*virtual*/ HRESULT set_MailExportFile(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_MailExportFile(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 MailTo，指定邮件的收件人地址。
	//@别名 取邮件收件人()
	/*virtual*/ CXText get_MailTo(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRExportOption*)m_ptr.p)->get_MailTo(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 MailTo，指定邮件的收件人地址。
	//@参数 收件人 
	//@别名 置邮件收件人(收件人)
	/*virtual*/ HRESULT set_MailTo(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_MailTo((BSTR)pVal); return _result; }
	//@备注 MailSubject，指定邮件的标题。
	//@别名 取邮件主题()
	/*virtual*/ CXText get_MailSubject(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRExportOption*)m_ptr.p)->get_MailSubject(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 MailSubject，指定邮件的标题。
	//@参数 主题文本 
	//@别名 置邮件主题(主题文本)
	/*virtual*/ HRESULT set_MailSubject(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_MailSubject((BSTR)pVal); return _result; }
	//@备注 MailText，指定邮件的正文。
	//@别名 取邮件正文()
	/*virtual*/ CXText get_MailText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRExportOption*)m_ptr.p)->get_MailText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 MailText，指定邮件的正文。
	//@参数 正文文本 
	//@别名 置邮件正文(正文文本)
	/*virtual*/ HRESULT set_MailText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_MailText((BSTR)pVal); return _result; }
	//@备注 AbortShowOptionDlg，指定报表在导出之前是否显示导出选项设置对话框。
	//@别名 取显示导出设置对话框()
	/*virtual*/ BOOL get_AbortShowOptionDlg(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRExportOption*)m_ptr.p)->get_AbortShowOptionDlg(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AbortShowOptionDlg，指定报表在导出之前是否显示导出选项设置对话框。
	//@参数 逻辑值 
	//@别名 置显示导出设置对话框(逻辑值)
	/*virtual*/ HRESULT set_AbortShowOptionDlg(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_AbortShowOptionDlg(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AbortOpenFile，指定报表在导出为文档之后是否用关联程序打开该导出文档。
	//@别名 取导出后打开()
	/*virtual*/ BOOL get_AbortOpenFile(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRExportOption*)m_ptr.p)->get_AbortOpenFile(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AbortOpenFile，指定报表在导出为文档之后是否用关联程序打开该导出文档。
	//@参数 逻辑值 
	//@别名 置导出后打开(逻辑值)
	/*virtual*/ HRESULT set_AbortOpenFile(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->put_AbortOpenFile(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ class CIGRE2CellOption get_AsE2CellOption(/*[out][retVal] class CIGRE2CellOption** pVal*/);
	//@备注 AsE2XLSOption，获取将本对象转换为导出Excel文件选项对象的接口引用。
	// 将本对象转换为导出Excel文件选项对象，只有当本对象确实是一个导出Excel文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为XLS选项()
	/*virtual*/ class CIGRE2XLSOption get_AsE2XLSOption(/*[out][retVal] class CIGRE2XLSOption** pVal*/);
	//@备注 AsE2TXTOption，获取将本对象转换为导出文本文件选项对象的接口引用。
	// 将本对象转换为导出文本文件选项对象，只有当本对象确实是一个导出文本文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为TXT选项()
	/*virtual*/ class CIGRE2TXTOption get_AsE2TXTOption(/*[out][retVal] class CIGRE2TXTOption** pVal*/);
	//@备注 AsE2HTMOption，获取将本对象转换为导出Htm文件选项对象的接口引用。
	// 将本对象转换为导出Htm文件选项对象，只有当本对象确实是一个导出Htm文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为HTM选项()
	/*virtual*/ class CIGRE2HTMOption get_AsE2HTMOption(/*[out][retVal] class CIGRE2HTMOption** pVal*/);
	//@备注 AsE2RTFOption，获取将本对象转换为导出 RTF 文件选项对象的接口引用。
	// 将本对象转换为导出 RTF 文件选项对象，只有当本对象确实是一个导出 RTF 文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为RTF选项()
	/*virtual*/ class CIGRE2RTFOption get_AsE2RTFOption(/*[out][retVal] class CIGRE2RTFOption** pVal*/);
	//@备注 AsE2PDFOption，获取将本对象转换为导出PDF文件选项对象的接口引用。
	// 将本对象转换为导出PDF文件选项对象，只有当本对象确实是一个导出PDF文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为PDF选项()
	/*virtual*/ class CIGRE2PDFOption get_AsE2PDFOption(/*[out][retVal] class CIGRE2PDFOption** pVal*/);
	//@备注 AsE2CSVOption，获取将本对象转换为导出CSV文件选项对象的接口引用。
	// 将本对象转换为导出CSV文件选项对象，只有当本对象确实是一个导出CSV文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为CSV选项()
	/*virtual*/ class CIGRE2CSVOption get_AsE2CSVOption(/*[out][retVal] class CIGRE2CSVOption** pVal*/);
	//@备注 AsE2IMGOption，获取将本对象转换为导出图像文件选项对象的接口引用。
	// 将本对象转换为导出图像文件选项对象，只有当本对象确实是一个导出图像文件选项对象时,才能成功取得对象的接口引用。
	//@别名 取为IMG选项()
	/*virtual*/ class CIGRE2IMGOption get_AsE2IMGOption(/*[out][retVal] class CIGRE2IMGOption** pVal*/);
	//@备注 ShowOptionDlg，显示导出选项设置对话框，可以在打开的对话框中设定各个选项值。
	// 如果在关闭对话框时选择了确定按钮，返回真值，反之则返回假值。
	//@别名 显示选项对话框()
	/*virtual*/ BOOL ShowOptionDlg(/*[out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRExportOption*)m_ptr.p)->raw_ShowOptionDlg(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT _GetFileTextResID(/*[out]*/ unsigned long* pExtFileNameID, /*, [out]*/ unsigned long* pExtFileDescID){ HRESULT _result = ((IGRExportOption*)m_ptr.p)->raw__GetFileTextResID(pExtFileNameID, pExtFileDescID); return _result; }

};
//@备注 E2CellOption，基类，数据导出，导出格子类型数据XLS\\CSV\\HTM\\RTF\\TXT的导出选项基接口，PDF\\IMG除外。
//@别名 导出格基类
class CIGRE2CellOption : public CIGRExportOption
{
public:
	CIGRE2CellOption(){};
	CIGRE2CellOption(IGRE2CellOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2CellOption* GetPtr(){ return ((IGRE2CellOption*)m_ptr.p); }
	//@备注 ExportPageBreak，指定在导出数据时是否产生页之间的分隔。
	// Microsoft Office Excel 有 1026年手动水平分页符的工作表的限制。在 Excel 2007 中的手动分页符限制为 1023年。导出 Excel 时，如果分页符超过了1023个，将自动产生新的工作表继续进行导出
	//@别名 取输出页分隔行()
	/*virtual*/ BOOL get_ExportPageBreak(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_ExportPageBreak(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ExportPageBreak，指定在导出数据时是否产生页之间的分隔。
	// Microsoft Office Excel 有 1026年手动水平分页符的工作表的限制。在 Excel 2007 中的手动分页符限制为 1023年。导出 Excel 时，如果分页符超过了1023个，将自动产生新的工作表继续进行导出。
	//@参数 逻辑值 
	//@别名 置输出页分隔行(逻辑值)
	/*virtual*/ HRESULT set_ExportPageBreak(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_ExportPageBreak(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ExportPageHeaderFooter，指定是否导出页眉与页脚，只有在产生页间分隔时此属性才有效。
	//@别名 取输出页眉与页脚()
	/*virtual*/ BOOL get_ExportPageHeaderFooter(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_ExportPageHeaderFooter(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ExportPageHeaderFooter，指定是否导出页眉与页脚，只有在产生页间分隔时此属性才有效。
	//@参数 逻辑值 
	//@别名 置输出页眉与页脚(逻辑值)
	/*virtual*/ HRESULT set_ExportPageHeaderFooter(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_ExportPageHeaderFooter(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 OnlyExportDetailGrid，指定是否只导出明细网格中的数据。
	//@别名 取只输出明细网格()
	/*virtual*/ BOOL get_OnlyExportDetailGrid(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_OnlyExportDetailGrid(&_result); return (VARIANT_TRUE==_result); }
	//@备注 OnlyExportDetailGrid，指定是否只导出明细网格中的数据。
	//@参数 逻辑值 
	//@别名 置只输出明细网格(逻辑值)
	/*virtual*/ HRESULT set_OnlyExportDetailGrid(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_OnlyExportDetailGrid(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SupressEmptyLines，指定是否压缩空白行，即不产生空白行。
	//@别名 取压缩空白行()
	/*virtual*/ BOOL get_SupressEmptyLines(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_SupressEmptyLines(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SupressEmptyLines，指定是否压缩空白行，即不产生空白行。
	//@参数 逻辑值 
	//@别名 置压缩空白行(逻辑值)
	/*virtual*/ HRESULT set_SupressEmptyLines(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_SupressEmptyLines(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ColumnAsDetailGrid，指示导出文件的列是否与报表明细网格的列保持一致。
	// 当本属性为TRUE时，如导出的EXCEL，RTF等文件时会产生较少的列。
	//@别名 取列与明细网格保持一致()
	/*virtual*/ BOOL get_ColumnAsDetailGrid(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_ColumnAsDetailGrid(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ColumnAsDetailGrid，指示导出文件的列是否与报表明细网格的列保持一致。
	// 当本属性为TRUE时，如导出的EXCEL，RTF等文件时会产生较少的列。
	//@参数 逻辑值 
	//@别名 置列与明细网格保持一致(逻辑值)
	/*virtual*/ HRESULT set_ColumnAsDetailGrid(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_ColumnAsDetailGrid(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 OnlyExportPureText，是否只导出纯文本类型数据。
	//@别名 取只导出纯文本数据()
	/*virtual*/ BOOL get_OnlyExportPureText(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_OnlyExportPureText(&_result); return (VARIANT_TRUE==_result); }
	//@备注 OnlyExportPureText，是否只导出纯文本类型数据。
	//@参数 逻辑值 
	//@别名 置只导出纯文本数据(逻辑值)
	/*virtual*/ HRESULT set_OnlyExportPureText(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_OnlyExportPureText(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SameAsPrint，指定是否按打印输出方式产生导出数据。
	//@别名 取与打印页面保持一致()
	/*virtual*/ BOOL get_SameAsPrint(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2CellOption*)m_ptr.p)->get_SameAsPrint(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SameAsPrint，指定是否按打印输出方式产生导出数据。
	//@参数 逻辑值 
	//@别名 置与打印页面保持一致(逻辑值)
	/*virtual*/ HRESULT set_SameAsPrint(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2CellOption*)m_ptr.p)->put_SameAsPrint(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 E2XLSOption，数据导出，表示导出XLS格式文件的选项。
//@别名 导出XLS选项
class CIGRE2XLSOption : public CIGRE2CellOption
{
public:
	CIGRE2XLSOption(){};
	CIGRE2XLSOption(IGRE2XLSOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2XLSOption* GetPtr(){ return ((IGRE2XLSOption*)m_ptr.p); }
	//@备注 MinColumnWidth，指定导出产生的列的最小宽度，以字符为计量单位，用报表缺省字体的字符平均宽度进行转换。
	//@别名 取最小列宽()
	/*virtual*/ long get_MinColumnWidth(/*[out][retVal] long* pVal*/){long _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_MinColumnWidth(&_result); return _result; }
	//@备注 MinColumnWidth，指定导出产生的列的最小宽度，以字符为计量单位，用报表缺省字体的字符平均宽度进行转换。
	//@参数 小数值 
	//@别名 置最小列宽(小数值)
	/*virtual*/ HRESULT set_MinColumnWidth(/*[in]*/ long pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_MinColumnWidth(pVal); return _result; }
	//@备注 MinRowHeight，指定导出产生行的最小高度，以字符为计量单位，用报表缺省字体的字符平均宽度进行转换。
	//@别名 取最小行高()
	/*virtual*/ long get_MinRowHeight(/*[out][retVal] long* pVal*/){long _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_MinRowHeight(&_result); return _result; }
	//@备注 MinRowHeight，指定导出产生行的最小高度，以字符为计量单位，用报表缺省字体的字符平均宽度进行转换。
	//@参数 小数值 
	//@别名 置最小行高(小数值)
	/*virtual*/ HRESULT set_MinRowHeight(/*[in]*/ long pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_MinRowHeight(pVal); return _result; }
	//@备注 ExpandRowHeight，增大行高适应多行文字完整显示，指示是否加大EXCEL的行高以便多行文字数据可以在格中完整显示出来。
	// EXCEL中多行文字的行间距大于 Grid++Report 中文字的行间距，如果导出的EXCEL行高与报表保持一致，则多行文字在EXCEL中可能不能完整地显示出来。
	// 设置本选项值为真，可以保证多行文字在导出后也可以完整显示。
	//@别名 取增大行高适应()
	/*virtual*/ BOOL get_ExpandRowHeight(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_ExpandRowHeight(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ExpandRowHeight，增大行高适应多行文字完整显示，指示是否加大EXCEL的行高以便多行文字数据可以在格中完整显示出来。
	// EXCEL中多行文字的行间距大于 Grid++Report 中文字的行间距，如果导出的EXCEL行高与报表保持一致，则多行文字在EXCEL中可能不能完整地显示出来。
	// 设置本选项值为真，可以保证多行文字在导出后也可以完整显示。
	//@参数 逻辑值 
	//@别名 置增大行高适应(逻辑值)
	/*virtual*/ HRESULT set_ExpandRowHeight(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_ExpandRowHeight(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 NewSheetRows，指定导出多少行后在新工作表继续导出，默认为0，不导出到新工作
	//@别名 取换新数据表行数()
	/*virtual*/ long get_NewSheetRows(/*[out][retVal] long* pVal*/){long _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_NewSheetRows(&_result); return _result; }
	//@备注 NewSheetRows，指定导出多少行后在新工作表继续导出，默认为0，不导出到新工作
	//@参数 整数值 
	//@别名 置换新数据表行数(整数值)
	/*virtual*/ HRESULT set_NewSheetRows(/*[in]*/ long pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_NewSheetRows(pVal); return _result; }
	//@备注 ColumnTitleForbidRepeat，指定是否禁止明细网格的标题行重复输出。
	//@别名 取禁止标题行重复输出()
	/*virtual*/ BOOL get_ColumnTitleForbidRepeat(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_ColumnTitleForbidRepeat(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ColumnTitleForbidRepeat，指定是否禁止明细网格的标题行重复输出。
	//@参数 逻辑值 
	//@别名 置禁止标题行重复输出(逻辑值)
	/*virtual*/ HRESULT set_ColumnTitleForbidRepeat(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_ColumnTitleForbidRepeat(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PageLeftMargin，Excel页面设置的左边距，如果为0，由Grid++Report自动产生边距值。
	//@别名 取页面左边距()
	/*virtual*/ double get_PageLeftMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_PageLeftMargin(&_result); return _result; }
	//@备注 PageLeftMargin，Excel页面设置的左边距，如果为0，由Grid++Report自动产生边距值。
	//@参数 小数值 
	//@别名 置页面左边距(小数值)
	/*virtual*/ HRESULT set_PageLeftMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_PageLeftMargin(pVal); return _result; }
	//@备注 PageRightMargin，Excel页面设置的右边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的右边距设为0。
	//@别名 取页面右边距()
	/*virtual*/ double get_PageRightMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_PageRightMargin(&_result); return _result; }
	//@备注 PageRightMargin，Excel页面设置的右边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的右边距设为0。
	//@参数 小数值 
	//@别名 置页面右边距(小数值)
	/*virtual*/ HRESULT set_PageRightMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_PageRightMargin(pVal); return _result; }
	//@备注 PageTopMargin，Excel页面设置的上边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的上边距设为比报表中的小。
	//@别名 取页面上边距()
	/*virtual*/ double get_PageTopMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_PageTopMargin(&_result); return _result; }
	//@备注 PageTopMargin，Excel页面设置的上边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的上边距设为比报表中的小。
	//@参数 小数值 
	//@别名 置页面上边距(小数值)
	/*virtual*/ HRESULT set_PageTopMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_PageTopMargin(pVal); return _result; }
	//@备注 PageBottomMargin，Excel页面设置的下边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的下边距设为比报表中的小。
	//@别名 取页面下边距()
	/*virtual*/ double get_PageBottomMargin(/*[out][retVal] double* pVal*/){double _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_PageBottomMargin(&_result); return _result; }
	//@备注 PageBottomMargin，Excel页面设置的下边距，如果为0，由Grid++Report自动产生边距值。
	// 如果此属性值为0，为了保证报表中一页的内容能完整在Excel中也能一页显示出来，Grid++Report会把Excel页面的下边距设为比报表中的小。
	//@参数 小数值 
	//@别名 置页面下边距(小数值)
	/*virtual*/ HRESULT set_PageBottomMargin(/*[in]*/ double pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_PageBottomMargin(pVal); return _result; }
	//@备注 ToXlsxFormat，指示是否导出为新的 .xlsx 格式。
	//@别名 取导出xlsx格式()
	/*virtual*/ BOOL get_ToXlsxFormat(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2XLSOption*)m_ptr.p)->get_ToXlsxFormat(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ToXlsxFormat，指示是否导出为新的 .xlsx 格式。
	//@参数 逻辑值 
	//@别名 置导出xlsx格式(逻辑值)
	/*virtual*/ HRESULT set_ToXlsxFormat(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2XLSOption*)m_ptr.p)->put_ToXlsxFormat(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 E2TXTOption，数据导出,表示导出TXT格式文件的选项。
//@别名 导出TXT选项
class CIGRE2TXTOption : public CIGRE2CellOption
{
public:
	CIGRE2TXTOption(){};
	CIGRE2TXTOption(IGRE2TXTOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2TXTOption* GetPtr(){ return ((IGRE2TXTOption*)m_ptr.p); }
	//@备注 UsingTabChar，指定是否用tab符号进行对齐处理。
	// 一个tab符号相当于8个空格字符占据的位置，用tab符号进行对齐处理可以减少导出文件的大小。
	//@别名 取用Tab字符对齐()
	/*virtual*/ BOOL get_UsingTabChar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2TXTOption*)m_ptr.p)->get_UsingTabChar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 UsingTabChar，指定是否用tab符号进行对齐处理。
	// 一个tab符号相当于8个空格字符占据的位置，用tab符号进行对齐处理可以减少导出文件的大小。
	//@参数 逻辑值 
	//@别名 置用Tab字符对齐(逻辑值)
	/*virtual*/ HRESULT set_UsingTabChar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2TXTOption*)m_ptr.p)->put_UsingTabChar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TextEncode，指定文字的编码类型。
	//@别名 取文字编码()
	/*virtual*/ GRTextEncodeMode get_TextEncode(/*[out][retVal] GRTextEncodeMode* pVal*/){GRTextEncodeMode _result; ((IGRE2TXTOption*)m_ptr.p)->get_TextEncode(&_result); return _result; }
	//@备注 TextEncode，指定文字的编码类型。
	//@参数 文本编码枚举值 
	//@别名 置文字编码(文本编码枚举值)
	/*virtual*/ HRESULT set_TextEncode(/*[in]*/ GRTextEncodeMode pVal){ HRESULT _result = ((IGRE2TXTOption*)m_ptr.p)->put_TextEncode(pVal); return _result; }

};
//@备注 E2HTMOption，数据导出，表示导出HTM格式文件的选项。
//@别名 导出HTM选项
class CIGRE2HTMOption : public CIGRE2CellOption
{
public:
	CIGRE2HTMOption(){};
	CIGRE2HTMOption(IGRE2HTMOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2HTMOption* GetPtr(){ return ((IGRE2HTMOption*)m_ptr.p); }
	/*virtual*/ BOOL get_MultiPage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2HTMOption*)m_ptr.p)->get_MultiPage(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_MultiPage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2HTMOption*)m_ptr.p)->put_MultiPage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 PicturePath，指定导出的图片文件存储的子目录名称。
	//@别名 取图像路径()
	/*virtual*/ CXText get_PicturePath(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2HTMOption*)m_ptr.p)->get_PicturePath(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PicturePath，指定导出的图片文件存储的子目录名称。
	//@参数 路径 
	//@别名 置图像路径(路径)
	/*virtual*/ HRESULT set_PicturePath(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2HTMOption*)m_ptr.p)->put_PicturePath((BSTR)pVal); return _result; }
	/*virtual*/ BOOL get_ShowNavLink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2HTMOption*)m_ptr.p)->get_ShowNavLink(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_ShowNavLink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2HTMOption*)m_ptr.p)->put_ShowNavLink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ CXText get_Title(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2HTMOption*)m_ptr.p)->get_Title(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_Title(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2HTMOption*)m_ptr.p)->put_Title((BSTR)pVal); return _result; }

};
//@备注 E2RTFOption，数据导出，表示导出RTF格式文件的选项。
//@别名 导出RTF选项
class CIGRE2RTFOption : public CIGRE2CellOption
{
public:
	CIGRE2RTFOption(){};
	CIGRE2RTFOption(IGRE2RTFOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2RTFOption* GetPtr(){ return ((IGRE2RTFOption*)m_ptr.p); }
	//@备注 Author，指定导出的 RTF 文件的作者。
	//@别名 取作者()
	/*virtual*/ CXText get_Author(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2RTFOption*)m_ptr.p)->get_Author(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Author，指定导出的 RTF 文件的作者。
	//@参数 作者名 
	//@别名 置作者(作者名)
	/*virtual*/ HRESULT set_Author(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2RTFOption*)m_ptr.p)->put_Author((BSTR)pVal); return _result; }
	//@备注 Creator，指定导出的 RTF 文件的创建程序。
	//@别名 取创建程序()
	/*virtual*/ CXText get_Creator(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2RTFOption*)m_ptr.p)->get_Creator(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Creator，指定导出的 RTF 文件的创建程序。
	//@参数 文本 
	//@别名 置创建程序(文本)
	/*virtual*/ HRESULT set_Creator(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2RTFOption*)m_ptr.p)->put_Creator((BSTR)pVal); return _result; }

};
//@备注 E2PDFOption，数据导出，表示导出PDF格式文件的选项。
// PDF导出乱码原因与解决办法:
// 1、一般是因为报表中的“字体“属性中的“字符集”没有设为对应的语言；
// 2、报表主对象的字体属性中的“字符集”要设对，不应该是“西方”；
// 3、检查对应部件框或单元格的字体属性中的“字符集”要设对，不应该是“西方”；
// 4、如果是简体中文，字符集应该是GB2312，如果是繁体，字符集应该是CHINESE_BIG5；
// 5、尝试将PDF导出对话框的“ANSI文字编码”项不勾选，以新的方式进行PDF导出。
//@别名 导出PDF选项
class CIGRE2PDFOption : public CIGRExportOption
{
public:
	CIGRE2PDFOption(){};
	CIGRE2PDFOption(IGRE2PDFOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2PDFOption* GetPtr(){ return ((IGRE2PDFOption*)m_ptr.p); }
	//@备注 Author，指定 PDF 文件的作者(Author)属性。
	//@别名 取作者()
	/*virtual*/ CXText get_Author(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_Author(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Author，指定 PDF 文件的作者(Author)属性。
	//@参数 作者名 
	//@别名 置作者(作者名)
	/*virtual*/ HRESULT set_Author(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Author((BSTR)pVal); return _result; }
	//@备注 Creator，指定 PDF 文件的生成应用程序(Creator)属性。
	//@别名 取创建程序()
	/*virtual*/ CXText get_Creator(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_Creator(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Creator，指定 PDF 文件的生成应用程序(Creator)属性。
	//@参数 文本 
	//@别名 置创建程序(文本)
	/*virtual*/ HRESULT set_Creator(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Creator((BSTR)pVal); return _result; }
	//@备注 Subject，指定 PDF 文件的主题(Subject)属性。
	//@别名 取主题()
	/*virtual*/ CXText get_Subject(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_Subject(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Subject，指定 PDF 文件的主题(Subject)属性。
	//@参数 主题文本 
	//@别名 置主题(主题文本)
	/*virtual*/ HRESULT set_Subject(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Subject((BSTR)pVal); return _result; }
	//@备注 AnsiTextMode，指定是否将文本数据编码为ANSI字符方式。
	// 如果此属性为FALSE，则文本内容将编码为字体图形方式，这种方式能很好解决乱码问题，但可能存在Windows XP与Windows7下产生的PDF文件互不相认的问题。
	// PDF导出乱码原因与解决办法:
	// 1、一般是因为报表中的“字体“属性中的“字符集”没有设为对应的语言；
	// 2、报表主对象的字体属性中的“字符集”要设对，不应该是“西方”；
	// 3、检查对应部件框或单元格的字体属性中的“字符集”要设对，不应该是“西方”；
	// 4、如果是简体中文，字符集应该是GB2312，如果是繁体，字符集应该是CHINESE_BIG5；
	// 5、尝试将PDF导出对话框的“ANSI文字编码”项不勾选，以新的方式进行PDF导出。
	//@别名 取ANSI文字编码()
	/*virtual*/ BOOL get_AnsiTextMode(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2PDFOption*)m_ptr.p)->get_AnsiTextMode(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AnsiTextMode，指定是否将文本数据编码为ANSI字符方式。
	// 如果此属性为FALSE，则文本内容将编码为字体图形方式，这种方式能很好解决乱码问题，但可能存在Windows XP与Windows7下产生的PDF文件互不相认的问题。
	// PDF导出乱码原因与解决办法:
	// 1、一般是因为报表中的“字体“属性中的“字符集”没有设为对应的语言；
	// 2、报表主对象的字体属性中的“字符集”要设对，不应该是“西方”；
	// 3、检查对应部件框或单元格的字体属性中的“字符集”要设对，不应该是“西方”；
	// 4、如果是简体中文，字符集应该是GB2312，如果是繁体，字符集应该是CHINESE_BIG5；
	// 5、尝试将PDF导出对话框的“ANSI文字编码”项不勾选，以新的方式进行PDF导出。
	//@参数 逻辑值 
	//@别名 置ANSI文字编码(逻辑值)
	/*virtual*/ HRESULT set_AnsiTextMode(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_AnsiTextMode(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_AutoShrinkFont(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2PDFOption*)m_ptr.p)->get_AutoShrinkFont(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_AutoShrinkFont(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_AutoShrinkFont(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Compressed，指定是否对 PDF 页面数据进行压缩。
	// 压缩 PDF 页面数据可以产生更小的 PDF 文件，采用 zlib 压缩算法对数据进行压缩。
	// 如果不压缩页面数据，产生的 PDF 文件可以用文本方式打开，从而可以分析 PDF 文件的结构。
	//@别名 取压缩数据()
	/*virtual*/ BOOL get_Compressed(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2PDFOption*)m_ptr.p)->get_Compressed(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Compressed，指定是否对 PDF 页面数据进行压缩。
	// 压缩 PDF 页面数据可以产生更小的 PDF 文件，采用 zlib 压缩算法对数据进行压缩。
	// 如果不压缩页面数据，产生的 PDF 文件可以用文本方式打开，从而可以分析 PDF 文件的结构
	//@参数 逻辑值 
	//@别名 置压缩数据(逻辑值)
	/*virtual*/ HRESULT set_Compressed(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Compressed(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Producer，指定 PDF 文件的制作程序(Producer)属性。
	//@别名 取制作程序()
	/*virtual*/ CXText get_Producer(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_Producer(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Producer，指定 PDF 文件的制作程序(Producer)属性。
	//@参数 文本 
	//@别名 置制作程序(文本)
	/*virtual*/ HRESULT set_Producer(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Producer((BSTR)pVal); return _result; }
	//@备注 Keywords，指定 PDF 文件的关键字(Keywords)属性。
	//@别名 取关键字()
	/*virtual*/ CXText get_Keywords(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_Keywords(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Keywords，指定 PDF 文件的关键字(Keywords)属性。
	//@参数 文本 
	//@别名 置关键字(文本)
	/*virtual*/ HRESULT set_Keywords(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_Keywords((BSTR)pVal); return _result; }
	//@备注 OwnerPassword，指定 PDF 文件的拥有者密码。
	// 如果要设置文档的口令，OwnerPassword 是必须要设置的，而 UserPassword 不一定要设置。
	// OwnerPassword 与 UserPassword 必须不一样。只有设置了 UserPassword，在以阅读方式打开文档时才需要输入口令。
	//@别名 取拥有者密码()
	/*virtual*/ CXText get_OwnerPassword(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_OwnerPassword(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 OwnerPassword，指定 PDF 文件的拥有者密码。
	// 如果要设置文档的口令，OwnerPassword 是必须要设置的，而 UserPassword 不一定要设置。
	// OwnerPassword 与 UserPassword 必须不一样。只有设置了 UserPassword，在以阅读方式打开文档时才需要输入口令。
	//@参数 密码文本 
	//@别名 置拥有者密码(密码文本)
	/*virtual*/ HRESULT set_OwnerPassword(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_OwnerPassword((BSTR)pVal); return _result; }
	//@备注 UserPassword，指定 PDF 文件的用户密码。
	// 如果要设置文档的口令，OwnerPassword 是必须要设置的，而 UserPassword 不一定要设置。
	// OwnerPassword 与 UserPassword 必须不一样。只有设置了 UserPassword，在以阅读方式打开文档时才需要输入口令。
	//@别名 取用户密码()
	/*virtual*/ CXText get_UserPassword(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2PDFOption*)m_ptr.p)->get_UserPassword(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 UserPassword，指定 PDF 文件的用户密码。
	// 如果要设置文档的口令，OwnerPassword 是必须要设置的，而 UserPassword 不一定要设置。
	// OwnerPassword 与 UserPassword 必须不一样。只有设置了 UserPassword，在以阅读方式打开文档时才需要输入口令。
	//@参数 密码文本 
	//@别名 置用户密码(密码文本)
	/*virtual*/ HRESULT set_UserPassword(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_UserPassword((BSTR)pVal); return _result; }
	//@备注 GetDocPermission，获取文档某项安全性限制的是否允许的状态。
	//@参数 安全限制项 PDF安全限制项枚举：1、允许打印； 2、允许更改文档； 3、允许复制内容； 4、允许编辑
	//@别名 获取安全性限制状态(安全限制项)
	/*virtual*/ BOOL GetDocPermission(/*[in]*/ GRPDFDocPermission Permission/*, [out][retVal] BOOL* pEnabled*/){VARIANT_BOOL _result=0; ((IGRE2PDFOption*)m_ptr.p)->raw_GetDocPermission(Permission, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT SetDocPermission(/*[in]*/ GRPDFDocPermission Permission, /*, [in]*/ BOOL Enabled){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->raw_SetDocPermission(Permission, Enabled? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 FontEmbedding，指定是否将字体数据嵌入到生成的 PDF 文档中。
	//@别名 取嵌入字体数据()
	/*virtual*/ BOOL get_FontEmbedding(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2PDFOption*)m_ptr.p)->get_FontEmbedding(&_result); return (VARIANT_TRUE==_result); }
	//@备注 FontEmbedding，指定是否将字体数据嵌入到生成的 PDF 文档中。
	//@参数 逻辑值 
	//@别名 置嵌入字体数据(逻辑值)
	/*virtual*/ HRESULT set_FontEmbedding(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2PDFOption*)m_ptr.p)->put_FontEmbedding(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 E2CSVOption，数据导出，表示导出CSV格式文件的选项。
//@别名 导出CSV选项
class CIGRE2CSVOption : public CIGRE2CellOption
{
public:
	CIGRE2CSVOption(){};
	CIGRE2CSVOption(IGRE2CSVOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2CSVOption* GetPtr(){ return ((IGRE2CSVOption*)m_ptr.p); }
	//@备注 DelimiterChar，指定CSV分隔字符。
	//@别名 取CSV分隔字符()
	/*virtual*/ char get_DelimiterChar(/*[out][retVal] char* pVal*/){char _result=0; ((IGRE2CSVOption*)m_ptr.p)->get_DelimiterChar(&_result); return _result; }
	//@备注 DelimiterChar，指定CSV分隔字符。
	//@参数 文本 
	//@别名 置CSV分隔字符(文本)
	/*virtual*/ HRESULT set_DelimiterChar(/*[in]*/ char pVal){ HRESULT _result = ((IGRE2CSVOption*)m_ptr.p)->put_DelimiterChar(pVal); return _result; }
	//@备注 QuoteText，指定括定内容的符号文字，可以为空。
	//@别名 取引号分割字符()
	/*virtual*/ CXText get_QuoteText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRE2CSVOption*)m_ptr.p)->get_QuoteText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 QuoteText，指定括定内容的符号文字，可以为空。
	//@参数 文本 
	//@别名 置引号分割字符(文本)
	/*virtual*/ HRESULT set_QuoteText(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRE2CSVOption*)m_ptr.p)->put_QuoteText((BSTR)pVal); return _result; }
	//@备注 TextEncode，指定文字的编码类型。
	//@别名 取文字编码()
	/*virtual*/ GRTextEncodeMode get_TextEncode(/*[out][retVal] GRTextEncodeMode* pVal*/){GRTextEncodeMode _result; ((IGRE2CSVOption*)m_ptr.p)->get_TextEncode(&_result); return _result; }
	//@备注 TextEncode，指定文字的编码类型。
	//@参数 文本编码枚举值 
	//@别名 置文字编码(文本编码枚举值)
	/*virtual*/ HRESULT set_TextEncode(/*[in]*/ GRTextEncodeMode pVal){ HRESULT _result = ((IGRE2CSVOption*)m_ptr.p)->put_TextEncode(pVal); return _result; }

};
//@备注 E2IMGOption，数据导出，表示导出TMG格式文件的选项。
//@别名 导出IMG选项
class CIGRE2IMGOption : public CIGRExportOption
{
public:
	CIGRE2IMGOption(){};
	CIGRE2IMGOption(IGRE2IMGOption* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRE2IMGOption* GetPtr(){ return ((IGRE2IMGOption*)m_ptr.p); }
	//@备注 ImageType，指定导出的图像格式。
	//@别名 取图像类型()
	/*virtual*/ GRExportImageType get_ImageType(/*[out][retVal] GRExportImageType* pVal*/){GRExportImageType _result; ((IGRE2IMGOption*)m_ptr.p)->get_ImageType(&_result); return _result; }
	//@备注 ImageType，指定导出的图像格式。
	//@参数 图像类型枚举值 
	//@别名 置图像类型(图像类型枚举值)
	/*virtual*/ HRESULT set_ImageType(/*[in]*/ GRExportImageType pVal){ HRESULT _result = ((IGRE2IMGOption*)m_ptr.p)->put_ImageType(pVal); return _result; }
	//@备注 DPI，指定导出图像的分辨率DPI。
	// DPI越高，导出图像文件大小更大。
	//@别名 取分辨率()
	/*virtual*/ long get_DPI(/*[out][retVal] long* pVal*/){long _result=0; ((IGRE2IMGOption*)m_ptr.p)->get_DPI(&_result); return _result; }
	//@备注 DPI，指定导出图像的分辨率DPI。
	// DPI越高，导出图像文件大小更大。
	//@参数 整数值 
	//@别名 置分辨率(整数值)
	/*virtual*/ HRESULT set_DPI(/*[in]*/ long pVal){ HRESULT _result = ((IGRE2IMGOption*)m_ptr.p)->put_DPI(pVal); return _result; }
	//@备注 DrawPageBox，指定是否在导出的图像上绘制一个页边框。
	//@别名 取绘制页面框()
	/*virtual*/ BOOL get_DrawPageBox(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2IMGOption*)m_ptr.p)->get_DrawPageBox(&_result); return (VARIANT_TRUE==_result); }
	//@备注 DrawPageBox，指定是否在导出的图像上绘制一个页边框。
	//@参数 逻辑值 
	//@别名 置绘制页面框(逻辑值)
	/*virtual*/ HRESULT set_DrawPageBox(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2IMGOption*)m_ptr.p)->put_DrawPageBox(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AllInOne，指示是否将整个报表导出在一个图像文件中。
	//@别名 取全部在一页()
	/*virtual*/ BOOL get_AllInOne(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRE2IMGOption*)m_ptr.p)->get_AllInOne(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AllInOne，指示是否将整个报表导出在一个图像文件中。
	//@参数 逻辑值 
	//@别名 置全部在一页(逻辑值)
	/*virtual*/ HRESULT set_AllInOne(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRE2IMGOption*)m_ptr.p)->put_AllInOne(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 VertGap，当图像导出在一个图像中时，每页之间的垂直间距，以屏幕像素为单位。
	//@别名 取垂直间隙()
	/*virtual*/ long get_VertGap(/*[out][retVal] long* pVal*/){long _result=0; ((IGRE2IMGOption*)m_ptr.p)->get_VertGap(&_result); return _result; }
	//@备注 VertGap，当图像导出在一个图像中时，每页之间的垂直间距，以屏幕像素为单位。
	//@参数 间隙值 每页之间的垂直间距，以屏幕像素为单位。
	//@别名 置垂直间隙(间隙值)
	/*virtual*/ HRESULT set_VertGap(/*[in]*/ long pVal){ HRESULT _result = ((IGRE2IMGOption*)m_ptr.p)->put_VertGap(pVal); return _result; }

};
//@备注 Line，表示直线段，用来显示两点之间的直线段的部件框。
//@别名 线段框
class CIGRLine : public CIGRControl
{
public:
	CIGRLine(){};
	CIGRLine(IGRLine* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRLine* GetPtr(){ return ((IGRLine*)m_ptr.p); }
	//@备注 LinePen，绘制线段的画笔对象。
	//@别名 取画笔()
	/*virtual*/ class CIGRPen get_LinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 X1，线段的起点X坐标位置。
	// 以报表使用的计量单位表示的线段的起点X坐标位置，相对于父容器。
	//@别名 取X1()
	/*virtual*/ double get_X1(/*[out][retVal] double* pVal*/){double _result=0; ((IGRLine*)m_ptr.p)->get_X1(&_result); return _result; }
	//@备注 X1，线段的起点X坐标位置。
	// 以报表使用的计量单位表示的线段的起点X坐标位置，相对于父容器。
	//@参数 小数值 
	//@别名 置X1(小数值)
	/*virtual*/ HRESULT set_X1(/*[in]*/ double pVal){ HRESULT _result = ((IGRLine*)m_ptr.p)->put_X1(pVal); return _result; }
	//@备注 Y1，线段的起点Y坐标位置。
	// 以报表使用的计量单位表示的线段的起点Y坐标位置，相对于父容器。
	//@别名 取Y1()
	/*virtual*/ double get_Y1(/*[out][retVal] double* pVal*/){double _result=0; ((IGRLine*)m_ptr.p)->get_Y1(&_result); return _result; }
	//@备注 Y1，线段的起点Y坐标位置。
	// 以报表使用的计量单位表示的线段的起点Y坐标位置，相对于父容器。
	//@参数 小数值 
	//@别名 置Y1(小数值)
	/*virtual*/ HRESULT set_Y1(/*[in]*/ double pVal){ HRESULT _result = ((IGRLine*)m_ptr.p)->put_Y1(pVal); return _result; }
	//@备注 X2，线段的终点X坐标位置。
	// 以报表使用的计量单位表示的线段的终点X坐标位置，相对于父容器。
	//@别名 取X2()
	/*virtual*/ double get_X2(/*[out][retVal] double* pVal*/){double _result=0; ((IGRLine*)m_ptr.p)->get_X2(&_result); return _result; }
	//@备注 X2，线段的终点X坐标位置。
	// 以报表使用的计量单位表示的线段的终点X坐标位置，相对于父容器。
	//@参数 小数值 
	//@别名 置X2(小数值)
	/*virtual*/ HRESULT set_X2(/*[in]*/ double pVal){ HRESULT _result = ((IGRLine*)m_ptr.p)->put_X2(pVal); return _result; }
	//@备注 Y2，线段的终点Y坐标位置。
	// 以报表使用的计量单位表示的线段的终点Y坐标位置，相对于父容器。
	//@别名 取Y2()
	/*virtual*/ double get_Y2(/*[out][retVal] double* pVal*/){double _result=0; ((IGRLine*)m_ptr.p)->get_Y2(&_result); return _result; }
	//@备注 Y2，线段的终点Y坐标位置。
	// 以报表使用的计量单位表示的线段的终点Y坐标位置，相对于父容器。
	//@参数 小数值 
	//@别名 置Y2(小数值)
	/*virtual*/ HRESULT set_Y2(/*[in]*/ double pVal){ HRESULT _result = ((IGRLine*)m_ptr.p)->put_Y2(pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRLine*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRLine*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 Barcode 条形码&二维码。用来生成条形码的部件框，支持所有常用类型的条形码，打印输出的条形码精读高易读取。
//@别名 条码框
class CIGRBarcode : public CIGRControl
{
public:
	CIGRBarcode(){};
	CIGRBarcode(IGRBarcode* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRBarcode* GetPtr(){ return ((IGRBarcode*)m_ptr.p); }
	//@备注 BarcodeType，指定条形码的类型。
	//@别名 取条码类型()
	/*virtual*/ GRBarcodeType get_BarcodeType(/*[out][retVal] GRBarcodeType* pVal*/){GRBarcodeType _result; ((IGRBarcode*)m_ptr.p)->get_BarcodeType(&_result); return _result; }
	//@备注 BarcodeType，指定条形码的类型。
	//@参数 条码类型枚举值 
	//@别名 置条码类型(条码类型枚举值)
	/*virtual*/ HRESULT set_BarcodeType(/*[in]*/ GRBarcodeType pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_BarcodeType(pVal); return _result; }
	//@备注 Alignment，指定条形码文字输出时的对齐方式。
	//@别名 取对齐方式()
	/*virtual*/ GRStringAlignment get_Alignment(/*[out][retVal] GRStringAlignment* pVal*/){GRStringAlignment _result; ((IGRBarcode*)m_ptr.p)->get_Alignment(&_result); return _result; }
	//@备注 Alignment，指定条形码文字输出时的对齐方式。
	//@参数 文本对齐方式枚举值 
	//@别名 置对齐方式(文本对齐方式枚举值)
	/*virtual*/ HRESULT set_Alignment(/*[in]*/ GRStringAlignment pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_Alignment(pVal); return _result; }
	//@备注 BarRatio，指定宽条与窄条之间的宽度比例。
	//@别名 取宽窄条比例()
	/*virtual*/ double get_BarRatio(/*[out][retVal] double* pVal*/){double _result=0; ((IGRBarcode*)m_ptr.p)->get_BarRatio(&_result); return _result; }
	//@备注 BarRatio，指定宽条与窄条之间的宽度比例。
	//@参数 比例值 
	//@别名 置宽窄条比例(比例值)
	/*virtual*/ HRESULT set_BarRatio(/*[in]*/ double pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_BarRatio(pVal); return _result; }
	//@备注 BarWidth，指定一个窄条的宽度，以报表的计量单位表示。 
	// 如果本属性值为0，条的宽度根据整个条码显示矩形的宽度自动计算得来，让条码图形在整个显示区域中刚好完整显示出来。
	//@别名 取条宽度()
	/*virtual*/ double get_BarWidth(/*[out][retVal] double* pVal*/){double _result=0; ((IGRBarcode*)m_ptr.p)->get_BarWidth(&_result); return _result; }
	//@备注 BarWidth，指定一个窄条的宽度，以报表的计量单位表示。 
	// 如果本属性值为0，条的宽度根据整个条码显示矩形的宽度自动计算得来，让条码图形在整个显示区域中刚好完整显示出来。
	//@参数 宽度值 
	//@别名 置条宽度(宽度值)
	/*virtual*/ HRESULT set_BarWidth(/*[in]*/ double pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_BarWidth(pVal); return _result; }
	//@备注 CaptionPosition，指定条形码数据文字的输出位置，或不输出数据文字。
	//@别名 取文字位置()
	/*virtual*/ GRBarcodeCaptionPosition get_CaptionPosition(/*[out][retVal] GRBarcodeCaptionPosition* pVal*/){GRBarcodeCaptionPosition _result; ((IGRBarcode*)m_ptr.p)->get_CaptionPosition(&_result); return _result; }
	//@备注 CaptionPosition，指定条形码数据文字的输出位置，或不输出数据文字。
	//@参数 条码文字位置枚举值 
	//@别名 置文字位置(条码文字位置枚举值)
	/*virtual*/ HRESULT set_CaptionPosition(/*[in]*/ GRBarcodeCaptionPosition pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_CaptionPosition(pVal); return _result; }
	//@备注 CaptionAlignment，显示的文字对齐方式。
	//@别名 取文字对齐方式()
	/*virtual*/ GRStringAlignment get_CaptionAlignment(/*[out][retVal] GRStringAlignment* pVal*/){GRStringAlignment _result; ((IGRBarcode*)m_ptr.p)->get_CaptionAlignment(&_result); return _result; }
	//@备注 CaptionAlignment，显示的文字对齐方式。
	//@参数 文本对齐方式枚举值 
	//@别名 置文字对齐方式(文本对齐方式枚举值)
	/*virtual*/ HRESULT set_CaptionAlignment(/*[in]*/ GRStringAlignment pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_CaptionAlignment(pVal); return _result; }
	//@备注 CheckSum，指定条形码是否进行数据校验，进行数据校验会增加额外的校验数据位。
	// 当条码为 Code128C 时，如果本属性为真，且数据的位数为奇数个，则在数据的最前面自动补充一位0。
	//@别名 取数据校验()
	/*virtual*/ BOOL get_CheckSum(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRBarcode*)m_ptr.p)->get_CheckSum(&_result); return (VARIANT_TRUE==_result); }
	//@备注 CheckSum，指定条形码是否进行数据校验，进行数据校验会增加额外的校验数据位。
	// 当条码为 Code128C 时，如果本属性为真，且数据的位数为奇数个，则在数据的最前面自动补充一位0。
	//@参数 逻辑值 
	//@别名 置数据校验(逻辑值)
	/*virtual*/ HRESULT set_CheckSum(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_CheckSum(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Direction，指定条形码图形的输出方向。
	//@别名 取输出方向()
	/*virtual*/ GRBarcodeDirection get_Direction(/*[out][retVal] GRBarcodeDirection* pVal*/){GRBarcodeDirection _result; ((IGRBarcode*)m_ptr.p)->get_Direction(&_result); return _result; }
	//@备注 Direction，指定条形码图形的输出方向。
	//@参数 条形码方向枚举值 
	//@别名 置输出方向(条形码方向枚举值)
	/*virtual*/ HRESULT set_Direction(/*[in]*/ GRBarcodeDirection pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_Direction(pVal); return _result; }
	//@备注 Text，指定条形码的数据文字，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"{}\"括起来，则将用此名称显示对应参数的文字。
	//@别名 取文本()
	/*virtual*/ CXText get_Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRBarcode*)m_ptr.p)->get_Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Text，指定条形码的数据文字，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"{}\"括起来，则将用此名称显示对应参数的文字。
	//@参数 文本 表达式文本
	//@别名 置文本(文本)
	/*virtual*/ HRESULT set_Text(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_Text((BSTR)pVal); return _result; }
	//@备注 DisplayText，获取到条码的当前生成文字。
	//@别名 取显示文字()
	/*virtual*/ CXText get_DisplayText(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRBarcode*)m_ptr.p)->get_DisplayText(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PDF417Rows，专用于PDF417，指定条码的行数，值范围0-90，0为自动计算确定。
	//@别名 取PDF417行数()
	/*virtual*/ long get_PDF417Rows(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_PDF417Rows(&_result); return _result; }
	//@备注 PDF417Rows，专用于PDF417，指定条码的行数，值范围0-90，0为自动计算确定。
	//@参数 整数值 
	//@别名 置PDF417行数(整数值)
	/*virtual*/ HRESULT set_PDF417Rows(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_PDF417Rows(pVal); return _result; }
	//@备注 PDF417Columns，专用于PDF417，指定条码每行的编码字节个数，0为自动计算确定。
	//@别名 取PDF417列数()
	/*virtual*/ long get_PDF417Columns(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_PDF417Columns(&_result); return _result; }
	//@备注 PDF417Columns，专用于PDF417，指定条码每行的编码字节个数，0为自动计算确定。
	//@参数 整数值 
	//@别名 置PDF417列数(整数值)
	/*virtual*/ HRESULT set_PDF417Columns(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_PDF417Columns(pVal); return _result; }
	//@备注 PDF417ErrorLevel，专用于PDF417，指定条码的纠错等级，值范围0-8，0为自动计算确定。
	//@别名 取PDF417纠错等级()
	/*virtual*/ long get_PDF417ErrorLevel(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_PDF417ErrorLevel(&_result); return _result; }
	//@备注 PDF417ErrorLevel，专用于PDF417，指定条码的纠错等级，值范围0-8，0为自动计算确定。
	//@参数 整数值 
	//@别名 置PDF417纠错等级(整数值)
	/*virtual*/ HRESULT set_PDF417ErrorLevel(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_PDF417ErrorLevel(pVal); return _result; }
	//@备注 PDF417Simple，专用于PDF417，指定是否进行截短简化，简化的PDF417图形将省略右边的标识符并将终止符缩减为一个模块。
	//@别名 取PDF417截短()
	/*virtual*/ BOOL get_PDF417Simple(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRBarcode*)m_ptr.p)->get_PDF417Simple(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PDF417Simple，专用于PDF417，指定是否进行截短简化，简化的PDF417图形将省略右边的标识符并将终止符缩减为一个模块。
	//@参数 逻辑值 
	//@别名 置PDF417截短(逻辑值)
	/*virtual*/ HRESULT set_PDF417Simple(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_PDF417Simple(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 QRCodeErrorLevel，专用于QRCode条码，指定纠错等级，取值范围1-4，对应L,M,Q,H纠错等级。
	//@别名 取QRCode纠错等级()
	/*virtual*/ long get_QRCodeErrorLevel(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_QRCodeErrorLevel(&_result); return _result; }
	//@备注 QRCodeErrorLevel，专用于QRCode条码，指定纠错等级，取值范围1-4，对应L,M,Q,H纠错等级。
	//@参数 整数值 
	//@别名 置QRCode纠错等级(整数值)
	/*virtual*/ HRESULT set_QRCodeErrorLevel(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_QRCodeErrorLevel(pVal); return _result; }
	//@备注 QRCodeVersion，专用于QRCode条码，指定版本号，取值范围0-40，0为自动确定。
	//@别名 取QRCode版本()
	/*virtual*/ long get_QRCodeVersion(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_QRCodeVersion(&_result); return _result; }
	//@备注 QRCodeVersion，专用于QRCode条码，指定版本号，取值范围0-40，0为自动确定。
	//@参数 整数值 
	//@别名 置QRCode版本(整数值)
	/*virtual*/ HRESULT set_QRCodeVersion(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_QRCodeVersion(pVal); return _result; }
	//@备注 QRCodeMask，专用于QRCode条码，指定掩码模式，取值范围0-8，0为自动确定。
	//@别名 取QRCode掩模()
	/*virtual*/ long get_QRCodeMask(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_QRCodeMask(&_result); return _result; }
	//@备注 QRCodeMask，专用于QRCode条码，指定掩码模式，取值范围0-8，0为自动确定。
	//@参数 整数值 
	//@别名 置QRCode掩模(整数值)
	/*virtual*/ HRESULT set_QRCodeMask(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_QRCodeMask(pVal); return _result; }
	//@备注 DtmxEncoding，指定二维码DataMatrix的数据编码方式。
	// 
	//@别名 取DataMatrix编码()
	/*virtual*/ GRDtmxEncoding get_DtmxEncoding(/*[out][retVal] GRDtmxEncoding* pVal*/){GRDtmxEncoding _result; ((IGRBarcode*)m_ptr.p)->get_DtmxEncoding(&_result); return _result; }
	//@备注 DtmxEncoding，指定二维码DataMatrix的数据编码方式。
	//@参数 DataM编码枚举值 
	//@别名 置DataMatrix编码(DataM编码枚举值)
	/*virtual*/ HRESULT set_DtmxEncoding(/*[in]*/ GRDtmxEncoding pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_DtmxEncoding(pVal); return _result; }
	//@备注 DtmxMatrixSize，指定二维码DataMatrix的图形模块矩阵维度。
	//@别名 取DataMatrix矩阵维度()
	/*virtual*/ GRDtmxMatrixSize get_DtmxMatrixSize(/*[out][retVal] GRDtmxMatrixSize* pVal*/){GRDtmxMatrixSize _result; ((IGRBarcode*)m_ptr.p)->get_DtmxMatrixSize(&_result); return _result; }
	//@备注 DtmxMatrixSize，指定二维码DataMatrix的图形模块矩阵维度。
	//@参数 DataM矩阵维度枚举值 
	//@别名 置DataMatrix矩阵维度(DataM矩阵维度枚举值)
	/*virtual*/ HRESULT set_DtmxMatrixSize(/*[in]*/ GRDtmxMatrixSize pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_DtmxMatrixSize(pVal); return _result; }
	/*virtual*/ long get_DtmxModuleSize(/*[out][retVal] long* pVal*/){long _result=0; ((IGRBarcode*)m_ptr.p)->get_DtmxModuleSize(&_result); return _result; }
	/*virtual*/ HRESULT set_DtmxModuleSize(/*[in]*/ long pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_DtmxModuleSize(pVal); return _result; }
	/*virtual*/ CXText get_DataField(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRBarcode*)m_ptr.p)->get_DataField(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_DataField(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_DataField((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRBarcode*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRBarcode*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 FreeGrid，表示自由表格对象，自由表格可以方便创建各种形式自由的表格，可以如 Excel 那样进行单元格合并。
//@别名 自由表格
class CIGRFreeGrid : public CIGRControl
{
public:
	CIGRFreeGrid(){};
	CIGRFreeGrid(IGRFreeGrid* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFreeGrid* GetPtr(){ return ((IGRFreeGrid*)m_ptr.p); }
	//@备注 ColumnCount，指定表格的列数。
	//@返回 默认值5
	//@别名 取列数()
	/*virtual*/ long get_ColumnCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFreeGrid*)m_ptr.p)->get_ColumnCount(&_result); return _result; }
	//@备注 ColumnCount，指定表格的列数。
	//@参数 列数 默认值5
	//@别名 置列数(列数)
	/*virtual*/ HRESULT set_ColumnCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_ColumnCount(pVal); return _result; }
	//@备注 RowCount，指定表格的行数。
	//@返回 默认值5
	//@别名 取行数()
	/*virtual*/ long get_RowCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFreeGrid*)m_ptr.p)->get_RowCount(&_result); return _result; }
	//@备注 RowCount，指定表格的行数。
	//@参数 行数 默认值5
	//@别名 置行数(行数)
	/*virtual*/ HRESULT set_RowCount(/*[in]*/ long pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_RowCount(pVal); return _result; }
	//@备注 ColLinePen，绘制网格列线的画笔
	// 
	//@别名 取列线画笔()
	/*virtual*/ class CIGRPen get_ColLinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 RowLinePen，绘制明细网网格行线的画笔。
	//@别名 取行线画笔()
	/*virtual*/ class CIGRPen get_RowLinePen(/*[out][retVal] class CIGRPen** pVal*/);
	//@备注 ShowColLine，指定是否显示表格列线。
	//@别名 取显示列线()
	/*virtual*/ BOOL get_ShowColLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGrid*)m_ptr.p)->get_ShowColLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowColLine，指定是否显示表格列线。
	//@参数 逻辑值 
	//@别名 置显示列线(逻辑值)
	/*virtual*/ HRESULT set_ShowColLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_ShowColLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowRowLine，指定是否显示表格行线。
	//@别名 取显示行线()
	/*virtual*/ BOOL get_ShowRowLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGrid*)m_ptr.p)->get_ShowRowLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowRowLine，指定是否显示表格行线。
	//@参数 逻辑值 
	//@别名 置显示行线(逻辑值)
	/*virtual*/ HRESULT set_ShowRowLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_ShowRowLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GrowToBottom，指示是否将表格的下边框延伸到页的底部。
	//@别名 取伸展到页底()
	/*virtual*/ BOOL get_GrowToBottom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGrid*)m_ptr.p)->get_GrowToBottom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GrowToBottom，指示是否将表格的下边框延伸到页的底部。
	//@参数 逻辑值 
	//@别名 置伸展到页底(逻辑值)
	/*virtual*/ HRESULT set_GrowToBottom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_GrowToBottom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 TitleRows，指定表格的标题行数。
	// 此属性仅用于要进行每页重复打印表头时，通过此属性将表格前几行指定为标题行。
	//@返回 默认值1
	//@别名 取表头行数()
	/*virtual*/ long get_TitleRows(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFreeGrid*)m_ptr.p)->get_TitleRows(&_result); return _result; }
	//@备注 TitleRows，指定表格的标题行数。
	// 此属性仅用于要进行每页重复打印表头时，通过此属性将表格前几行指定为标题行。
	//@参数 表头行数 默认值1
	//@别名 置表头行数(表头行数)
	/*virtual*/ HRESULT set_TitleRows(/*[in]*/ long pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_TitleRows(pVal); return _result; }
	//@备注 TitleRepeat，指定是否在每页重复显示表格标题行。
	// 自由表格的标题行通过“表头行数”属性指定。
	//@别名 取表头每页重复()
	/*virtual*/ BOOL get_TitleRepeat(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGrid*)m_ptr.p)->get_TitleRepeat(&_result); return (VARIANT_TRUE==_result); }
	//@备注 TitleRepeat，指定是否在每页重复显示表格标题行。
	// 自由表格的标题行通过“表头行数”属性指定。
	//@参数 逻辑值 
	//@别名 置表头每页重复(逻辑值)
	/*virtual*/ HRESULT set_TitleRepeat(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_TitleRepeat(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ColumnAt，获取指定列对应的自由表格列对象。
	//@参数 列号 列号，从1开始。
	//@返回 获取到的自由表格列对象。
	//@别名 获取指定列(列号)
	/*virtual*/ class CIGRFreeGridColumn ColumnAt(/*[in]*/ long ColumnIndex/*, [out][retVal] class CIGRFreeGridColumn** ppItem*/);
	//@备注 RowAt，获取指定行对应的自由表格行对象。
	//@参数 行号 行号，从1开始。
	//@返回 获取到的自由表格行对象。
	//@别名 获取指定行(行号)
	/*virtual*/ class CIGRFreeGridRow RowAt(/*[in]*/ long RowIndex/*, [out][retVal] class CIGRFreeGridRow** ppItem*/);
	//@备注 CellAt，获取指定行列对应的自由表格单元格对象。
	//@参数 行号 行号，从1开始。
	//@参数 列号 列号，从1开始。
	//@返回 获取到的自由表格单元格对象。
	//@别名 获取指定单元格(行号,列号)
	/*virtual*/ class CIGRFreeGridCell CellAt(/*[in]*/ long RowIndex, /*, [in]*/ long ColumnIndex/*, [out][retVal] class CIGRFreeGridCell** ppItem*/);
	//@备注 CellByDataName，根据单元格的数据名称获取指定对应的自由表格单元格对象。
	//@参数 数据名称 单元格的数据名称。
	//@返回 获取到的自由表格单元格对象。
	//@别名 按数据名称获取单元格(数据名称)
	/*virtual*/ class CIGRFreeGridCell CellByDataName(/*[in]*/ const wchar_t* DataName/*, [out][retVal] class CIGRFreeGridCell** ppItem*/);
	/*virtual*/ class CIGRFreeGridCell _Cell(/*[in]*/ long RowIndex, /*, [in]*/ long ColumnIndex/*, [out][retVal] class CIGRFreeGridCell** ppItem*/);
	/*virtual*/ class CIGRFreeGridColumn _Column(/*[in]*/ long ColumnIndex/*, [out][retVal] class CIGRFreeGridColumn** ppItem*/);
	/*virtual*/ class CIGRFreeGridRow _Row(/*[in]*/ long RowIndex/*, [out][retVal] class CIGRFreeGridRow** ppItem*/);
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRFreeGrid*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRFreeGrid*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 FreeGridColumn，表示自由表格列对象。
//@别名 自由表格列
class CIGRFreeGridColumn : public CIGRObject
{
public:
	CIGRFreeGridColumn(){};
	CIGRFreeGridColumn(IGRFreeGridColumn* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFreeGridColumn* GetPtr(){ return ((IGRFreeGridColumn*)m_ptr.p); }
	//@备注 Width，指定本自由表格列的显示宽度。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值3
	//@别名 取宽度()
	/*virtual*/ double get_Width(/*[out][retVal] double* pVal*/){double _result=0; ((IGRFreeGridColumn*)m_ptr.p)->get_Width(&_result); return _result; }
	//@备注 Width，指定本自由表格列的显示宽度。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值3
	//@别名 置宽度(小数值)
	/*virtual*/ HRESULT set_Width(/*[in]*/ double pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_Width(pVal); return _result; }
	//@备注 Visible，指定本自由表格列在运行时是否显示。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridColumn*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，指定本自由表格列在运行时是否显示。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ CXText get_AlignColumn(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFreeGridColumn*)m_ptr.p)->get_AlignColumn(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_AlignColumn(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_AlignColumn((BSTR)pVal); return _result; }
	/*virtual*/ CXText get_AlignColumnEx(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFreeGridColumn*)m_ptr.p)->get_AlignColumnEx(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	/*virtual*/ HRESULT set_AlignColumnEx(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_AlignColumnEx((BSTR)pVal); return _result; }
	/*virtual*/ GRAlignColumnStyle get_AlignColumnSide(/*[out][retVal] GRAlignColumnStyle* pVal*/){GRAlignColumnStyle _result; ((IGRFreeGridColumn*)m_ptr.p)->get_AlignColumnSide(&_result); return _result; }
	/*virtual*/ HRESULT set_AlignColumnSide(/*[in]*/ GRAlignColumnStyle pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_AlignColumnSide(pVal); return _result; }
	//@备注 Locked，是否锁定当前自由表格列，被锁定的列不允许改变宽度与移动位置。
	//@别名 取锁定()
	/*virtual*/ BOOL get_Locked(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridColumn*)m_ptr.p)->get_Locked(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Locked，是否锁定当前自由表格列，被锁定的列不允许改变宽度与移动位置。
	//@参数 逻辑值 
	//@别名 置锁定(逻辑值)
	/*virtual*/ HRESULT set_Locked(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_Locked(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_FixedWidth(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridColumn*)m_ptr.p)->get_FixedWidth(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_FixedWidth(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_FixedWidth(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 FreeGrid，本自由表格行所在的自由表格对象。
	//@别名 取自由表格()
	/*virtual*/ class CIGRFreeGrid get_FreeGrid(/*[out][retVal] class CIGRFreeGrid** pVal*/);
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRFreeGridColumn*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRFreeGridColumn*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 FreeGridRow，表示自由表格行对象。
//@别名 自由表格行
class CIGRFreeGridRow : public CIGRObject
{
public:
	CIGRFreeGridRow(){};
	CIGRFreeGridRow(IGRFreeGridRow* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFreeGridRow* GetPtr(){ return ((IGRFreeGridRow*)m_ptr.p); }
	//@备注 Height，指定自由表格行的显示高度。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@返回 默认值3
	//@别名 取高度()
	/*virtual*/ double get_Height(/*[out][retVal] double* pVal*/){double _result=0; ((IGRFreeGridRow*)m_ptr.p)->get_Height(&_result); return _result; }
	//@备注 Height，指定自由表格行的显示高度。
	// 以报表主对象的“计量单位(Unit)”属性指定的值为计量单位，默认计量单位为厘米。
	//@参数 小数值 默认值3
	//@别名 置高度(小数值)
	/*virtual*/ HRESULT set_Height(/*[in]*/ double pVal){ HRESULT _result = ((IGRFreeGridRow*)m_ptr.p)->put_Height(pVal); return _result; }
	//@备注 Visible，指定本自由表格行在运行时是否显示。
	//@别名 取可见性()
	/*virtual*/ BOOL get_Visible(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridRow*)m_ptr.p)->get_Visible(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Visible，指定本自由表格行在运行时是否显示。
	//@参数 逻辑值 
	//@别名 置可见性(逻辑值)
	/*virtual*/ HRESULT set_Visible(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridRow*)m_ptr.p)->put_Visible(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 KeepTogether，是否保持本自由表格行在打印输出时在显示在同一页。
	//@别名 取保持同页()
	/*virtual*/ BOOL get_KeepTogether(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridRow*)m_ptr.p)->get_KeepTogether(&_result); return (VARIANT_TRUE==_result); }
	//@备注 KeepTogether，是否保持本自由表格行在打印输出时在显示在同一页。
	//@参数 逻辑值 
	//@别名 置保持同页(逻辑值)
	/*virtual*/ HRESULT set_KeepTogether(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridRow*)m_ptr.p)->put_KeepTogether(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Locked，是否锁定当前自由表格行，被锁定的行不允许改变高度与移动位置。
	//@别名 取锁定()
	/*virtual*/ BOOL get_Locked(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRFreeGridRow*)m_ptr.p)->get_Locked(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Locked，是否锁定当前自由表格行，被锁定的行不允许改变高度与移动位置。
	//@参数 逻辑值 
	//@别名 置锁定(逻辑值)
	/*virtual*/ HRESULT set_Locked(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRFreeGridRow*)m_ptr.p)->put_Locked(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 FreeGrid，本自由表格行所在的自由表格对象。
	//@别名 取自由表格()
	/*virtual*/ class CIGRFreeGrid get_FreeGrid(/*[out][retVal] class CIGRFreeGrid** pVal*/);
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRFreeGridRow*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRFreeGridRow*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 FreeGridCell，表示自由表格单元格对象。
//@别名 自由表格子格
class CIGRFreeGridCell : public CIGRCellBase
{
public:
	CIGRFreeGridCell(){};
	CIGRFreeGridCell(IGRFreeGridCell* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRFreeGridCell* GetPtr(){ return ((IGRFreeGridCell*)m_ptr.p); }
	//@备注 ColSpan，指定单元格要合并其右边单元格的个数。
	//@返回 默认值为1，表示不合并右边的单元格。
	//@别名 取合并列数()
	/*virtual*/ long get_ColSpan(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFreeGridCell*)m_ptr.p)->get_ColSpan(&_result); return _result; }
	//@备注 ColSpan，指定单元格要合并其右边单元格的个数
	//@参数 个数值 默认值为1
	//@别名 置合并列数(个数值)
	/*virtual*/ HRESULT set_ColSpan(/*[in]*/ long pVal){ HRESULT _result = ((IGRFreeGridCell*)m_ptr.p)->put_ColSpan(pVal); return _result; }
	//@备注 RowSpan，指定单元格要合并其下边单元格的个数。
	//@返回 默认值为1，表示不合并下边的单元格。
	//@别名 取合并行数()
	/*virtual*/ long get_RowSpan(/*[out][retVal] long* pVal*/){long _result=0; ((IGRFreeGridCell*)m_ptr.p)->get_RowSpan(&_result); return _result; }
	//@备注 RowSpan，指定单元格要合并其下边单元格的个数。
	//@参数 个数值 默认值为1
	//@别名 置合并行数(个数值)
	/*virtual*/ HRESULT set_RowSpan(/*[in]*/ long pVal){ HRESULT _result = ((IGRFreeGridCell*)m_ptr.p)->put_RowSpan(pVal); return _result; }
	//@备注 Text，单元格的显示文本，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 与综合文字框的Text(文本)属性定义是类同的。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的
	// 定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。
	// 如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"\"{}\"\"括起来，则将用此名称显示对应参数的文字。
	//@别名 取文本()
	/*virtual*/ CXText get_Text(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFreeGridCell*)m_ptr.p)->get_Text(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Text，单元格的显示文本，文本中可以包含多种数据域，如字段、参数、统计函数、系统变量与表达式等。
	// 与综合文字框的Text(文本)属性定义是类同的。
	// 数据域定义在文本中，数据域通过“[#”与“#]”扩起来，中间包含的文字可以成功解析为数据域或表达式，数据域的
	// 定义文本在运行时将被数据域的值替换，反之文字将以原样输出。
	// 数据域可以是字段、参数、文字部件框、系统变量与统计函数等。
	// 如果存在同名的字段与参数，则只显示字段的文字，将名称用大括号\"\"{}\"\"括起来，则将用此名称显示对应参数的文字。
	//@参数 文本 表达式文本
	//@别名 置文本(文本)
	/*virtual*/ HRESULT set_Text(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFreeGridCell*)m_ptr.p)->put_Text((BSTR)pVal); return _result; }
	//@备注 DataName，指定单元格的数据名称，用于与报表的 XML 或 JSON 数据包中的数据项进行匹配。
	//@别名 取数据名称()
	/*virtual*/ CXText get_DataName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRFreeGridCell*)m_ptr.p)->get_DataName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DataName，指定单元格的数据名称，用于与报表的 XML 或 JSON 数据包中的数据项进行匹配。
	//@参数 数据名称 
	//@别名 置数据名称(数据名称)
	/*virtual*/ HRESULT set_DataName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRFreeGridCell*)m_ptr.p)->put_DataName((BSTR)pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRFreeGridCell*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRFreeGridCell*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 ColumnContentCells，集合对象，内容行的所有内容格的集合对象。
// 在内容行(IGRColumnContent)对象中指定拥有的内容格，内容格伴随列的新增而新增，伴随列的删除而删除。
//@别名 内容格集合
class CIGRColumnContentCells : public CXComObj /*IDispatch*/
{
public:
	CIGRColumnContentCells(){};
	CIGRColumnContentCells(IGRColumnContentCells* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumnContentCells* GetPtr(){ return ((IGRColumnContentCells*)m_ptr.p); }
	/*virtual*/ class CIGRColumnContentCell get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRColumnContentCell** ppColumnContentCell*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRColumnContentCells*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有内容格的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRColumnContentCells*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 IndexByName，根据内容格的名称取得其顺序号，如果不存在与名称匹配的内容格，则返回值为-1。
	// 内容格的名称不区分字母的大小写。
	//@参数 名称 指定查找内容格的名称。
	//@返回 如果存在名称匹配的内容格，返回内容格的顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRColumnContentCells*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的内容格对象，序号从1开始。
	//@参数 序号 指定内容格对象在集合中的序号，从1开始。
	//@返回 获取到的内容格对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRColumnContentCell ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRColumnContentCell** ppItem*/);

};
//@备注 Columns，集合对象，明细网格的所有列的集合对象。指定明细网格(IGRDetailGrid)拥有的列。
// 关于获取列的显示顺序：
// 应该从IGRColumnTitle.TitleCells属性中获取列的显示顺序，即IGRColumnTitle.TitleCells的各个集合对象的顺序与列的显示顺序保持一致，如果是多层表头，这里就有树形关系，需要根据IGRColumnTitleCell.SubTitles 属性进一步获取下一级的各个标题格。
// IGRDetailGrid.Columns中的集合对象的顺序与列的显示顺序不一定保持一致。
//@别名 列集合
class CIGRColumns : public CXComObj /*IDispatch*/
{
public:
	CIGRColumns(){};
	CIGRColumns(IGRColumns* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRColumns* GetPtr(){ return ((IGRColumns*)m_ptr.p); }
	/*virtual*/ class CIGRColumn get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRColumn** ppColumn*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRColumns*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有列的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRColumns*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个列并返回新增列的接口引用。
	//@返回 新增列的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRColumn Add(/*[out][retVal] class CIGRColumn** ppColumn*/);
	//@备注 Remove，根据列的顺序号将列移除。
	//@参数 序号 指定列的顺序号，序号从1开始。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRColumns*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部列。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRColumns*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据列的名称取得其顺序号，如果不存在与名称匹配的列，则返回值为-1。
	// 列的名称不区分字母的大小写。
	//@参数 名称 指定列的名称。
	//@返回 如果存在名称匹配的列，返回列的顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRColumns*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的明细列对象，序号从1开始。
	//@参数 序号 指定明细列对象在集合中的序号，从1开始。
	//@返回 获取到的明细列对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRColumn ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRColumn** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数明细列的顺序。
	//@参数 序号 指定明细列的序号，序号从1开始。。
	//@参数 新顺序号 明细列在集合中的新序号，从1开始。 
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRColumns*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 Groups，集合对象，明细网格的所有分组的集合对象。
//@别名 分组集合
class CIGRGroups : public CXComObj /*IDispatch*/
{
public:
	CIGRGroups(){};
	CIGRGroups(IGRGroups* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGroups* GetPtr(){ return ((IGRGroups*)m_ptr.p); }
	/*virtual*/ class CIGRGroup get_Item(/*[in]*/ VARIANT Index/*, [out][retVal] class CIGRGroup** ppObject*/);
	/*virtual*/ IUnknownPtr get__NewEnum(/*[out][retVal] IUnknown** ppEnum*/){IUnknownPtr _result; ((IGRGroups*)m_ptr.p)->get__NewEnum(&_result); return _result; }
	//@备注 Count，指示拥有分组的个数。
	//@别名 取数目()
	/*virtual*/ long get_Count(/*[out][retVal] long* pnCount*/){long _result=0; ((IGRGroups*)m_ptr.p)->get_Count(&_result); return _result; }
	//@备注 Add，增加一个分组并返回新增分组的接口引用。
	//@返回 新增分组的接口引用。
	//@别名 增加()
	/*virtual*/ class CIGRGroup Add(/*[out][retVal] class CIGRGroup** ppObject*/);
	//@备注 Remove，根据分组的顺序号将分组移除，在输入参数种指定要移除分组的顺序号或名称。
	//@参数 序号 指定分组的顺序号。
	//@别名 按序号删除项目(序号)
	/*virtual*/ HRESULT Remove(/*[in]*/ VARIANT Index){ HRESULT _result = ((IGRGroups*)m_ptr.p)->raw_Remove(Index); return _result; }
	//@备注 RemoveAll，清除全部分组。
	//@别名 全部删除()
	/*virtual*/ HRESULT RemoveAll(){ HRESULT _result = ((IGRGroups*)m_ptr.p)->raw_RemoveAll(); return _result; }
	//@备注 IndexByName，根据分组的名称取得其顺序号，如果不存在与名称匹配的分组，则返回-1。
	// 分组的名称不区分字母的大小写。
	//@参数 名称 指定分组的名称。 
	//@返回 如果有匹配的分组，返回其顺序号，否则返回-1。
	//@别名 按名称取序号(名称)
	/*virtual*/ long IndexByName(/*[in]*/ const wchar_t* Name/*, [out][retVal] long* Index*/){long _result=0; ((IGRGroups*)m_ptr.p)->raw_IndexByName((BSTR)Name, &_result); return _result; }
	//@备注 ItemAt，从集合中按序号获取对应的分组对象，序号从1开始。
	//@参数 序号 指定分组对象在集合中的序号，从1开始。
	//@返回 获取到的分组对象。
	//@别名 获取指定项目(序号)
	/*virtual*/ class CIGRGroup ItemAt(/*[in]*/ long Index/*, [out][retVal] class CIGRGroup** ppItem*/);
	//@备注 ChangeItemOrder，在集合中改变指定参数分组的顺序。
	//@参数 序号 指定分组的序号，序号从1开始。
	//@参数 新顺序号 分组在集合中的新序号，从1开始。 
	//@别名 按序号改变项目顺序(序号,新顺序号)
	/*virtual*/ HRESULT ChangeItemOrder(/*[in]*/ VARIANT Index, /*, [in]*/ long NewOrder){ HRESULT _result = ((IGRGroups*)m_ptr.p)->raw_ChangeItemOrder(Index, NewOrder); return _result; }

};
//@备注 CrossTab，表示交叉表的定义接口。
//@别名 交叉表
class CIGRCrossTab : public CIGRObject
{
public:
	CIGRCrossTab(){};
	CIGRCrossTab(IGRCrossTab* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRCrossTab* GetPtr(){ return ((IGRCrossTab*)m_ptr.p); }
	//@备注 HCrossFields，指定横向交叉的数据字段名称，多个字段之间用\';\'号隔开。
	// 该属性对交叉表定义是必须的，只有定义了该属性交叉表才能成功生成。
	//@别名 取横向交叉字段()
	/*virtual*/ CXText get_HCrossFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_HCrossFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 HCrossFields，指定横向交叉的数据字段名称，多个字段之间用\';\'号隔开。
	// 该属性对交叉表定义是必须的，只有定义了该属性交叉表才能成功生成。
	//@参数 字段名称 字段名称，多个字段之间用\';\'号隔开。
	//@别名 置横向交叉字段(字段名称)
	/*virtual*/ HRESULT set_HCrossFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HCrossFields((BSTR)pVal); return _result; }
	//@备注 VCrossFields，指定纵向交叉的数据字段名称，多个字段之间用\';\'号隔开。
	// 如果本属性未定义，交叉表纵向只会产生一项，通常该属性都要定义。
	//@别名 取纵向交叉字段()
	/*virtual*/ CXText get_VCrossFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_VCrossFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 VCrossFields，指定纵向交叉的数据字段名称，多个字段之间用\';\'号隔开。
	// 如果本属性未定义，交叉表纵向只会产生一项，通常该属性都要定义。
	//@参数 字段名称 字段名称，多个字段之间用\';\'号隔开。
	//@别名 置纵向交叉字段(字段名称)
	/*virtual*/ HRESULT set_VCrossFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_VCrossFields((BSTR)pVal); return _result; }
	//@备注 ListCols，指定明细网格中显示纵向交叉数据位于前面的列数。
	//@别名 取项目列数()
	/*virtual*/ long get_ListCols(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCrossTab*)m_ptr.p)->get_ListCols(&_result); return _result; }
	//@备注 ListCols，指定明细网格中显示纵向交叉数据位于前面的列数。
	//@参数 列数 
	//@别名 置项目列数(列数)
	/*virtual*/ HRESULT set_ListCols(/*[in]*/ long pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_ListCols(pVal); return _result; }
	//@备注 TotalCols，指定明细网格中定义横向合计的列数，明细网格最后几列属于横向合计列。
	// 注意：横向求和关联的字段必须为数字类型的字段，不然就不会求出横向合计数。
	//@别名 取合计列数()
	/*virtual*/ long get_TotalCols(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCrossTab*)m_ptr.p)->get_TotalCols(&_result); return _result; }
	//@备注 TotalCols，指定明细网格中定义横向合计的列数，明细网格最后几列属于横向合计列。
	// 注意：横向求和关联的字段必须为数字类型的字段，不然就不会求出横向合计数。
	//@参数 整数值 
	//@别名 置合计列数(整数值)
	/*virtual*/ HRESULT set_TotalCols(/*[in]*/ long pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_TotalCols(pVal); return _result; }
	//@备注 SubtotalCols，指定明细网格中定义横向小计的列数，明细网格的横向合计列之前是小计列。
	//@别名 取小计列数()
	/*virtual*/ long get_SubtotalCols(/*[out][retVal] long* pVal*/){long _result=0; ((IGRCrossTab*)m_ptr.p)->get_SubtotalCols(&_result); return _result; }
	//@备注 SubtotalCols，指定明细网格中定义横向小计的列数，明细网格的横向合计列之前是小计列。
	//@参数 整数值 
	//@别名 置小计列数(整数值)
	/*virtual*/ HRESULT set_SubtotalCols(/*[in]*/ long pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_SubtotalCols(pVal); return _result; }
	//@备注 HResort，指示横向交叉数据是否按横向交叉字段重新排序
	// 特别提示：如果将此属性设置为“否(false)”，则交叉报表的原始记录数据顺序必须按横向交叉字段的值归类在一起，
	// 即同一横向交叉项的记录数据连片在一起，通常如按横向交叉字段在查询SQL中进行排序就能满足这样的要求。
	//@别名 取横向重排序()
	/*virtual*/ BOOL get_HResort(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_HResort(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HResort，指示横向交叉数据是否按横向交叉字段重新排序
	// 特别提示：如果将此属性设置为“否(false)”，则交叉报表的原始记录数据顺序必须按横向交叉字段的值归类在一起，
	// 即同一横向交叉项的记录数据连片在一起，通常如按横向交叉字段在查询SQL中进行排序就能满足这样的要求。
	//@参数 逻辑值 
	//@别名 置横向重排序(逻辑值)
	/*virtual*/ HRESULT set_HResort(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HResort(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 HSortAsc，指示横向交叉字段是否按升序排列。
	//@别名 取横向排序升序()
	/*virtual*/ BOOL get_HSortAsc(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_HSortAsc(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HSortAsc，指示横向交叉字段是否按升序排列。
	//@参数 逻辑值 
	//@别名 置横向排序升序(逻辑值)
	/*virtual*/ HRESULT set_HSortAsc(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HSortAsc(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 VResort，指示纵向交叉数据是否按纵向交叉字段重新排序。
	// 特别提示：如果将此属性设置为“否(false)”，交叉表在生成时将不会根据纵向交叉字段对数据重新进行排序，
	// 则交叉报表的原始记录数据顺序必须按纵向交叉字段的值聚集在一起，即同一纵向交叉项的记录数据连片在一起，
	// 通常如按纵向交叉字段在查询SQL中进行排序就能满足这样的要求。
	//@别名 取纵向重排序()
	/*virtual*/ BOOL get_VResort(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_VResort(&_result); return (VARIANT_TRUE==_result); }
	//@备注 VResort，指示纵向交叉数据是否按纵向交叉字段重新排序。
	// 特别提示：如果将此属性设置为“否(false)”，交叉表在生成时将不会根据纵向交叉字段对数据重新进行排序，
	// 则交叉报表的原始记录数据顺序必须按纵向交叉字段的值聚集在一起，即同一纵向交叉项的记录数据连片在一起，
	// 通常如按纵向交叉字段在查询SQL中进行排序就能满足这样的要求。
	//@参数 逻辑值 
	//@别名 置纵向重排序(逻辑值)
	/*virtual*/ HRESULT set_VResort(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_VResort(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 VSortAsc，指示纵向交叉字段是否按升序排列。
	//@别名 取纵向排序升序()
	/*virtual*/ BOOL get_VSortAsc(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_VSortAsc(&_result); return (VARIANT_TRUE==_result); }
	//@备注 VSortAsc，指示纵向交叉字段是否按升序排列。
	//@参数 逻辑值 
	//@别名 置纵向排序升序(逻辑值)
	/*virtual*/ HRESULT set_VSortAsc(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_VSortAsc(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 HTotalAtFirst，指定是否将横向合计栏显示在前面。
	//@别名 取横向合计在前()
	/*virtual*/ BOOL get_HTotalAtFirst(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_HTotalAtFirst(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HTotalAtFirst，指定是否将横向合计栏显示在前面。
	//@参数 逻辑值 
	//@别名 置横向合计在前(逻辑值)
	/*virtual*/ HRESULT set_HTotalAtFirst(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HTotalAtFirst(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 HPercentColumns，指定按横向计算比重百分比的列名称，多个列名称以‘;’隔开。
	//@别名 取横向求比率列()
	/*virtual*/ CXText get_HPercentColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_HPercentColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 HPercentColumns，指定按横向计算比重百分比的列名称，多个列名称以‘;’隔开。
	//@参数 字段名称 字段名称，多个字段之间用\';\'号隔开。
	//@别名 置横向求比率列(字段名称)
	/*virtual*/ HRESULT set_HPercentColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HPercentColumns((BSTR)pVal); return _result; }
	//@备注 VPercentColumns，指定按纵向计算比重百分比的列名称，多个列名称以‘;’隔开。
	//@别名 取纵向求比率列()
	/*virtual*/ CXText get_VPercentColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_VPercentColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 VPercentColumns，指定按纵向计算比重百分比的列名称，多个列名称以‘;’隔开。
	//@参数 字段名称 字段名称，多个字段之间用\';\'号隔开。
	//@别名 置纵向求比率列(字段名称)
	/*virtual*/ HRESULT set_VPercentColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_VPercentColumns((BSTR)pVal); return _result; }
	//@备注 TotalExcludeColumns，在合计列中，指定不进行合计的列的名称。
	// 此属性指定的列其关联数据将不会求和，而是按原始数据显示。
	//@别名 取横向合计排除列()
	/*virtual*/ CXText get_TotalExcludeColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_TotalExcludeColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TotalExcludeColumns，在合计列中，指定不进行合计的列的名称。
	// 此属性指定的列其关联数据将不会求和，而是按原始数据显示。
	//@参数 列名称 
	//@别名 置横向合计排除列(列名称)
	/*virtual*/ HRESULT set_TotalExcludeColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_TotalExcludeColumns((BSTR)pVal); return _result; }
	//@备注 TotalHPercentColumns，指定横向合计比重百分比的列名称，多个列名称以‘;’隔开。
	//@别名 取横向合计求比率列()
	/*virtual*/ CXText get_TotalHPercentColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_TotalHPercentColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TotalHPercentColumns，指定横向合计比重百分比的列名称，多个列名称以‘;’隔开。
	//@参数 列名称 列名称，多个列名称以‘;’隔开。
	//@别名 置横向合计求比率列(列名称)
	/*virtual*/ HRESULT set_TotalHPercentColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_TotalHPercentColumns((BSTR)pVal); return _result; }
	//@备注 TotalVPercentColumns，指定纵向合计比重百分比的列名称，多个列名称以‘;’隔开。
	//@别名 取纵向合计求比率列()
	/*virtual*/ CXText get_TotalVPercentColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_TotalVPercentColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 TotalVPercentColumns，指定纵向合计比重百分比的列名称，多个列名称以‘;’隔开。
	//@参数 列名称 列名称，多个列名称以‘;’隔开。
	//@别名 置纵向合计求比率列(列名称)
	/*virtual*/ HRESULT set_TotalVPercentColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_TotalVPercentColumns((BSTR)pVal); return _result; }
	//@备注 PercentFormat，指定比重百分比数据的格式化文字。
	//@别名 取百分比格式()
	/*virtual*/ CXText get_PercentFormat(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_PercentFormat(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 PercentFormat，指定比重百分比数据的格式化文字。
	//@参数 百分比格式文本 
	//@别名 置百分比格式(百分比格式文本)
	/*virtual*/ HRESULT set_PercentFormat(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_PercentFormat((BSTR)pVal); return _result; }
	//@备注 HCrossPeriodType，横向交叉的按期间交叉的期间类型。
	// 本属性的默认值为 grptNone，表示交叉表不是按日期期间交叉的。
	// 如果本属性设定了非 grptNone 值，则 HCrossFields 必须是一个日期类型字段的名称。
	//@别名 取横向交叉期间类型()
	/*virtual*/ GRPeriodType get_HCrossPeriodType(/*[out][retVal] GRPeriodType* pVal*/){GRPeriodType _result; ((IGRCrossTab*)m_ptr.p)->get_HCrossPeriodType(&_result); return _result; }
	//@备注 HCrossPeriodType，横向交叉的按期间交叉的期间类型。
	// 本属性的默认值为 grptNone，表示交叉表不是按日期期间交叉的。
	// 如果本属性设定了非 grptNone 值，则 HCrossFields 必须是一个日期类型字段的名称。
	//@参数 周期类型枚举值 
	//@别名 置横向交叉期间类型(周期类型枚举值)
	/*virtual*/ HRESULT set_HCrossPeriodType(/*[in]*/ GRPeriodType pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_HCrossPeriodType(pVal); return _result; }
	//@备注 BeginDateParameter，指定交叉期间的开始日期对应的参数对象名称。
	// 本属性仅对按期间交叉的报表有效。
	//@别名 取开始日期参数()
	/*virtual*/ CXText get_BeginDateParameter(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_BeginDateParameter(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 BeginDateParameter，指定交叉期间的开始日期对应的参数对象名称。
	// 本属性仅对按期间交叉的报表有效。
	//@参数 参数名称 
	//@别名 置开始日期参数(参数名称)
	/*virtual*/ HRESULT set_BeginDateParameter(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_BeginDateParameter((BSTR)pVal); return _result; }
	//@备注 EndDateParameter，指定交叉期间的结束日期对应的参数对象名称。
	// 本属性仅对按期间交叉的报表有效。
	//@别名 取结束日期参数()
	/*virtual*/ CXText get_EndDateParameter(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_EndDateParameter(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 EndDateParameter，指定交叉期间的结束日期对应的参数对象名称。
	// 本属性仅对按期间交叉的报表有效。
	//@参数 参数名称 
	//@别名 置结束日期参数(参数名称)
	/*virtual*/ HRESULT set_EndDateParameter(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_EndDateParameter((BSTR)pVal); return _result; }
	//@备注 GroupAutoSum，指定是否进行分组求和统计。
	// 交叉表中的分组头尾中，如果某列存在对齐的部件框，则此列不会自动产生求和统计框。
	// 如果希望某列不求和，或按非求和的方式进行统计，就可以加入与此列对齐的相应部件框。
	// 如果不合计其中一列，可以分组尾放置一个与此列对齐的静态框，其“文本”属性为空白。
	//@别名 取分组自动求和()
	/*virtual*/ BOOL get_GroupAutoSum(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRCrossTab*)m_ptr.p)->get_GroupAutoSum(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GroupAutoSum，指定是否进行分组求和统计。
	// 交叉表中的分组头尾中，如果某列存在对齐的部件框，则此列不会自动产生求和统计框。
	// 如果希望某列不求和，或按非求和的方式进行统计，就可以加入与此列对齐的相应部件框。
	// 如果不合计其中一列，可以分组尾放置一个与此列对齐的静态框，其“文本”属性为空白。
	//@参数 逻辑值 
	//@别名 置分组自动求和(逻辑值)
	/*virtual*/ HRESULT set_GroupAutoSum(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_GroupAutoSum(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Recordset，获取用于存储交叉表运行结果的记录集对象引用，此记录集不同于明细网格的记录集。
	//@别名 取数据集()
	/*virtual*/ class CIGRRecordset get_Recordset(/*[out][retVal] class CIGRRecordset** pVal*/);
	//@备注 HBeginAddItem，准备提供横向交叉项目数据。
	// 首先调用“开始横向交叉数据”(HBeginAddItem)开始添加横向交叉项目数据；
	// 然后向明细网格的记录集添加记录数据，只用向横向交叉字段提供数据；
	// 最后调用“完成横向交叉数据”(HEndAddItem)方法结束添加横向交叉项目数据。
	// 通过以上任务可以将不存在于数据中的横向交叉项目添加进来。
	// 以上任务必须在报表的“开始处理记录”(ProcessBegin)事件中执行。
	//@别名 开始横向交叉数据()
	/*virtual*/ HRESULT HBeginAddItem(){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->raw_HBeginAddItem(); return _result; }
	//@备注 HEndAddItem，完成提供横向交叉项目数据。 
	// 首先调用“准备横向交叉数据”(HBeginAddItem)开始添加横向交叉项目数据；
	// 然后向明细网格的记录集添加记录数据，只用向横向交叉字段提供数据；
	// 最后调用“结束横向交叉数据”(HEndAddItem)方法结束添加横向交叉项目数据。
	// 通过以上任务可以将不存在于数据中的横向交叉项目添加进来。
	// 以上任务必须在报表的“开始处理记录”(ProcessBegin)事件中执行。
	//@别名 结束横向交叉数据()
	/*virtual*/ HRESULT HEndAddItem(){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->raw_HEndAddItem(); return _result; }
	//@备注 VBeginAddItem，准备提供纵向交叉项目数据。
	// 首先调用“开始纵向交叉数据”(VBeginAddItem)开始添加纵向交叉项目数据；
	// 然后向明细网格的记录集添加记录数据，只用向纵向交叉字段提供数据；
	// 最后调用“完成纵向交叉数据”(VEndAddItem)方法结束添加纵向交叉项目数据。
	// 通过以上任务可以将不存在于数据中的纵向交叉项目添加进来。
	// 以上任务必须在报表的“开始处理记录”(ProcessBegin)事件中执行。
	//@别名 开始纵向交叉数据()
	/*virtual*/ HRESULT VBeginAddItem(){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->raw_VBeginAddItem(); return _result; }
	//@备注 VEndAddItem，完成提供纵向交叉项目数据。
	// 首先调用“开始纵向交叉数据”(VBeginAddItem)开始添加纵向交叉项目数据；
	// 然后向明细网格的记录集添加记录数据，只用向纵向交叉字段提供数据；
	// 最后调用“结束纵向交叉数据”(VEndAddItem)方法结束添加纵向交叉项目数据。
	// 通过以上任务可以将不存在于数据中的纵向交叉项目添加进来。
	// 以上任务必须在报表的“开始处理记录”(ProcessBegin)事件中执行。
	//@别名 结束纵向交叉数据()
	/*virtual*/ HRESULT VEndAddItem(){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->raw_VEndAddItem(); return _result; }
	//@备注 GetCurPeriodBeginDate，当交叉表为按期间交叉时，在报表生成过程中获取当前期间的开始日期。
	//@别名 获取交叉周期开始日期()
	/*virtual*/ DATE GetCurPeriodBeginDate(/*[out][retVal] DATE* pVal*/){DATE _result=0; ((IGRCrossTab*)m_ptr.p)->raw_GetCurPeriodBeginDate(&_result); return _result; }
	//@备注 GetCurPeriodEndDate，当交叉表为按期间交叉时，在报表生成过程中获取当前期间的结束日期。
	//@别名 获取交叉周期结束日期()
	/*virtual*/ DATE GetCurPeriodEndDate(/*[out][retVal] DATE* pVal*/){DATE _result=0; ((IGRCrossTab*)m_ptr.p)->raw_GetCurPeriodEndDate(&_result); return _result; }
	//@备注 DisabledSumFields，不参与交叉统计的字段，即使该字段使用在交叉统计列中。
	//@别名 取禁止统计字段()
	/*virtual*/ CXText get_DisabledSumFields(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRCrossTab*)m_ptr.p)->get_DisabledSumFields(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 DisabledSumFields，不参与交叉统计的字段，即使该字段使用在交叉统计列中。
	//@参数 字段名称 如果需要禁止多个字段，字段名称之间用‘;’隔开。
	//@别名 置禁止统计字段(字段名称)
	/*virtual*/ HRESULT set_DisabledSumFields(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_DisabledSumFields((BSTR)pVal); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@别名 取锁定()
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRCrossTab*)m_ptr.p)->get_Lock(&_result); return _result; }
	//@备注 Lock，锁定类别枚举：0、不锁定； 1、锁定继承； 2、锁定对象； 3、锁定数据； 4、锁定数据行为； 5、完全锁定
	// 说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
	//@参数 锁定类别枚举 
	//@别名 置锁定(锁定类别枚举)
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRCrossTab*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 GroupSection，基类，分组头与分组尾的基接口，表示分组头与分组尾相同的属性与方法。
//@别名 分组节
class CIGRGroupSection : public CIGRSection
{
public:
	CIGRGroupSection(){};
	CIGRGroupSection(IGRGroupSection* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGroupSection* GetPtr(){ return ((IGRGroupSection*)m_ptr.p); }
	//@备注 Group，获取拥有本分组节的分组对象的接口引用。
	//@别名 取分组()
	/*virtual*/ class CIGRGroup get_Group(/*[out][retVal] class CIGRGroup** pVal*/);
	//@备注 NewPage，获取换新页的产生方式。
	//@别名 取换新页()
	/*virtual*/ GRNewPageStyle get_NewPage(/*[out][retVal] GRNewPageStyle* pVal*/){GRNewPageStyle _result; ((IGRGroupSection*)m_ptr.p)->get_NewPage(&_result); return _result; }
	//@备注 NewPage，设置换新页的产生方式。
	//@参数 换新页方式枚举值 
	//@别名 置换新页(换新页方式枚举值)
	/*virtual*/ HRESULT set_NewPage(/*[in]*/ GRNewPageStyle pVal){ HRESULT _result = ((IGRGroupSection*)m_ptr.p)->put_NewPage(pVal); return _result; }
	//@备注 PrintGridBorder，获取是否打印本分组节对应位置的明细网格边框。
	// 当本属性值为是时，且明细网格的边框不具有内层并没有阴影，则此分组头或分组尾的左右两边不输出表格的边框线。即有内层边框或有阴影时，此属性设置无效。
	//@别名 取打印输出边框()
	/*virtual*/ BOOL get_PrintGridBorder(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupSection*)m_ptr.p)->get_PrintGridBorder(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintGridBorder，设置是否打印本分组节对应位置的明细网格边框。
	// 当本属性值为是时，且明细网格的边框不具有内层并没有阴影，则此分组头或分组尾的左右两边不输出表格的边框线。即有内层边框或有阴影时，此属性设置无效。
	//@参数 逻辑值 
	//@别名 置打印输出边框(逻辑值)
	/*virtual*/ HRESULT set_PrintGridBorder(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupSection*)m_ptr.p)->put_PrintGridBorder(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 HNewPageFixed，指定在横向分页打印时，分组头尾是否锁定始终打印页面左边的内容。
	// 在横向分页生成报表页面时，如果希望分组头或分组页始终显示输出左边的内容，应该设置本属性为“是”。否则分组头或分组页根据横向分页的偏移显示对应位置处的内容。
	//@别名 取横向分页锁定()
	/*virtual*/ BOOL get_HNewPageFixed(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupSection*)m_ptr.p)->get_HNewPageFixed(&_result); return (VARIANT_TRUE==_result); }
	//@备注 HNewPageFixed，指定在横向分页打印时，分组头尾是否锁定始终打印页面左边的内容。
	// 在横向分页生成报表页面时，如果希望分组头或分组页始终显示输出左边的内容，应该设置本属性为“是”。否则分组头或分组页根据横向分页的偏移显示对应位置处的内容。
	//@参数 逻辑值 
	//@别名 置横向分页锁定(逻辑值)
	/*virtual*/ HRESULT set_HNewPageFixed(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupSection*)m_ptr.p)->put_HNewPageFixed(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 NewPageColumn，指定强制换新页栏的方式。
	// 指定分组头尾在输出前与输出后产生新页栏的方式，此属性常用于多栏报表在分组开始或结束时产生新页栏。
	//@别名 取换新页栏()
	/*virtual*/ GRNewPageColumnStyle get_NewPageColumn(/*[out][retVal] GRNewPageColumnStyle* pVal*/){GRNewPageColumnStyle _result; ((IGRGroupSection*)m_ptr.p)->get_NewPageColumn(&_result); return _result; }
	//@备注 NewPageColumn，指定强制换新页栏的方式。
	// 指定分组头尾在输出前与输出后产生新页栏的方式，此属性常用于多栏报表在分组开始或结束时产生新页栏。
	//@参数 换新页栏方式枚举值 
	//@别名 置换新页栏(换新页栏方式枚举值)
	/*virtual*/ HRESULT set_NewPageColumn(/*[in]*/ GRNewPageColumnStyle pVal){ HRESULT _result = ((IGRGroupSection*)m_ptr.p)->put_NewPageColumn(pVal); return _result; }
	//@备注 RepeatOnPage，指定是否在新页中重复显示当前分组项的分组头。
	// 当本属性值为真时，如果一个分组项的所有行需要在多页显示，则在每页都显示分组头或分组尾。
	//@别名 取每页重复打印()
	/*virtual*/ BOOL get_RepeatOnPage(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupSection*)m_ptr.p)->get_RepeatOnPage(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RepeatOnPage，指定是否在新页中重复显示当前分组项的分组头。
	// 当本属性值为真时，如果一个分组项的所有行需要在多页显示，则在每页都显示分组头或分组尾。
	//@参数 逻辑值 
	//@别名 置每页重复打印(逻辑值)
	/*virtual*/ HRESULT set_RepeatOnPage(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupSection*)m_ptr.p)->put_RepeatOnPage(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }

};
//@备注 GroupHeader，表示明细网格分组的分组头。分组头显示在每个分组的第一行。
// 一个报表可以定义一个或多个嵌套分组，每个分组对应一个分组头与一个分组尾。分组头显示在每个分组开始位置，一般在分组头上定义分组的标识信息，分组初始值及其它只需在分组开始时显示一次的信息
//  关于分组页号与页数的更进一步说明：
// 1、为了产生分组页号与页数信息，必须设置对应分组头与分组尾的“可见性”属性为“是”，且其“高度”属性值大于0。
// 2、如果实际不需要显示分组头与分组尾，可以在其“格式化脚本”上写脚本代码“Sender.Visible = false;”，这样可以在运行时将分组头与分组尾隐藏不显示。
// 3、分组页号页数在查询显示报表时不会得到正确的值，所以不应在查询显示报表时显示分组页号页数。
//@别名 分组头
class CIGRGroupHeader : public CIGRGroupSection
{
public:
	CIGRGroupHeader(){};
	CIGRGroupHeader(IGRGroupHeader* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGroupHeader* GetPtr(){ return ((IGRGroupHeader*)m_ptr.p); }
	//@备注 OccupyColumn，获取或设置是否为占列式分组头的标志。
	// 当 OccupyColumn 属性为真时，在输出显示时，分组头不是独立占据一个水平带状区域，而是在 OccupiedColumns 属性指定列的显示区域中与内容行一起显示。
	// OccupiedColumns 属性指定的列本身的输出显示被忽略掉。
	//@别名 取占列式()
	/*virtual*/ BOOL get_OccupyColumn(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupHeader*)m_ptr.p)->get_OccupyColumn(&_result); return (VARIANT_TRUE==_result); }
	//@备注 OccupyColumn，获取或设置是否为占列式分组头的标志。
	// 当 OccupyColumn 属性为真时，在输出显示时，分组头不是独立占据一个水平带状区域，而是在 OccupiedColumns 属性指定列的显示区域中与内容行一起显示。
	// OccupiedColumns 属性指定的列本身的输出显示被忽略掉。
	//@参数 逻辑值 
	//@别名 置占列式(逻辑值)
	/*virtual*/ HRESULT set_OccupyColumn(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_OccupyColumn(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 OccupiedColumns，为占列式分组头时，指定占据列的名称。
	//@返回 如果要占据多个列，列名称之间用分号（;）隔开。
	//@别名 取占据列()
	/*virtual*/ CXText get_OccupiedColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRGroupHeader*)m_ptr.p)->get_OccupiedColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 OccupiedColumns，为占列式分组头时，指定占据列的名称。
	//@参数 列名称 如果要占据多个列，列名称之间用分号（;）隔开。
	//@别名 置占据列(列名称)
	/*virtual*/ HRESULT set_OccupiedColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_OccupiedColumns((BSTR)pVal); return _result; }
	//@备注 VAlign，为占列式分组头时，获取或设置显示位置在垂直方向上的对齐方式。
	//@别名 取垂直对齐方式()
	/*virtual*/ GROCGroupHeaderVAlign get_VAlign(/*[out][retVal] GROCGroupHeaderVAlign* pVal*/){GROCGroupHeaderVAlign _result; ((IGRGroupHeader*)m_ptr.p)->get_VAlign(&_result); return _result; }
	//@备注 VAlign，为占列式分组头时，获取或设置显示位置在垂直方向上的对齐方式。
	//@参数 分组头对齐方式枚举值 
	//@别名 置垂直对齐方式(分组头对齐方式枚举值)
	/*virtual*/ HRESULT set_VAlign(/*[in]*/ GROCGroupHeaderVAlign pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_VAlign(pVal); return _result; }
	//@备注 SameAsColumn，为占列式分组头时，获取或设置是否采用占据列的内容格定义进行显示的标志。
	// 为占列式分组头时，输出定义采用列内容格的定义。当此属性为真时，分组头中不用定义任何显示部件框，此时在报表设计器中禁止向此分组头插入部件框。
	//@别名 取显示同列()
	/*virtual*/ BOOL get_SameAsColumn(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupHeader*)m_ptr.p)->get_SameAsColumn(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SameAsColumn，为占列式分组头时，获取或设置是否采用占据列的内容格定义进行显示的标志。
	// 为占列式分组头时，输出定义采用列内容格的定义。当此属性为真时，分组头中不用定义任何显示部件框，此时在报表设计器中禁止向此分组头插入部件框。
	//@参数 逻辑值 
	//@别名 置显示同列(逻辑值)
	/*virtual*/ HRESULT set_SameAsColumn(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_SameAsColumn(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 IncludeFooter，为占列式分组头时，获取或设置分组尾是否被包含在占列分组中的标志。
	//@别名 取包括分组尾()
	/*virtual*/ BOOL get_IncludeFooter(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupHeader*)m_ptr.p)->get_IncludeFooter(&_result); return (VARIANT_TRUE==_result); }
	//@备注 IncludeFooter，为占列式分组头时，获取或设置分组尾是否被包含在占列分组中的标志。
	//@参数 逻辑值 
	//@别名 置包括分组尾(逻辑值)
	/*virtual*/ HRESULT set_IncludeFooter(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_IncludeFooter(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GroupKeepTogether，打印输出时，指定本分组项的分组头与其它行保持同页的方式。
	//@别名 取保持分组同页()
	/*virtual*/ GRGrpKpTogetherStyle get_GroupKeepTogether(/*[out][retVal] GRGrpKpTogetherStyle* pVal*/){GRGrpKpTogetherStyle _result; ((IGRGroupHeader*)m_ptr.p)->get_GroupKeepTogether(&_result); return _result; }
	//@备注 GroupKeepTogether，打印输出时，指定本分组项的分组头与其它行保持同页的方式。
	//@参数 分组保持同页方式枚举值 
	//@别名 置保持分组同页(分组保持同页方式枚举值)
	/*virtual*/ HRESULT set_GroupKeepTogether(/*[in]*/ GRGrpKpTogetherStyle pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_GroupKeepTogether(pVal); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRGroupHeader*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRGroupHeader*)m_ptr.p)->put_Lock(pVal); return _result; }

};
//@备注 GroupFooter，表示明细网格分组的分组尾。分组尾显示在每个分组的最后一行。
// 一个报表可以定义一个或多个嵌套分组，每个分组对应一个分组头与一个分组尾。
// 分组尾显示在每个分组结束位置，一般在分组尾上定义定义分组的统计信息及其它只需在分组开始时显示一次的信息。
//@别名 分组尾
class CIGRGroupFooter : public CIGRGroupSection
{
public:
	CIGRGroupFooter(){};
	CIGRGroupFooter(IGRGroupFooter* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRGroupFooter* GetPtr(){ return ((IGRGroupFooter*)m_ptr.p); }
	//@备注 PrintAtBottom，打印输出时，指定是否将本节显示在页面底部。
	//@别名 取打印在页底()
	/*virtual*/ BOOL get_PrintAtBottom(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupFooter*)m_ptr.p)->get_PrintAtBottom(&_result); return (VARIANT_TRUE==_result); }
	//@备注 PrintAtBottom，打印输出时，指定是否将本节显示在页面底部。
	//@参数 逻辑值 
	//@别名 置打印在页底(逻辑值)
	/*virtual*/ HRESULT set_PrintAtBottom(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupFooter*)m_ptr.p)->put_PrintAtBottom(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AppendBlankRowExclude，是否将分组尾行从空白行的计数中排除。
	// 当明细网格设定追加空白行且指定了每页行数，本属性指定是否将本行作为本页中的一行对待。
	// 假设每页指定输出10行，数据行已输出6行，如果本属性为FALSE，则补充3行空白行，反之补充4行空白行。
	//@别名 取追加空白行排除()
	/*virtual*/ BOOL get_AppendBlankRowExclude(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRGroupFooter*)m_ptr.p)->get_AppendBlankRowExclude(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AppendBlankRowExclude，是否将分组尾行从空白行的计数中排除。
	// 当明细网格设定追加空白行且指定了每页行数，本属性指定是否将本行作为本页中的一行对待。
	// 假设每页指定输出10行，数据行已输出6行，如果本属性为FALSE，则补充3行空白行，反之补充4行空白行
	//@参数 逻辑值 
	//@别名 置追加空白行排除(逻辑值)
	/*virtual*/ HRESULT set_AppendBlankRowExclude(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRGroupFooter*)m_ptr.p)->put_AppendBlankRowExclude(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ GRLockType get_Lock(/*[out][retVal] GRLockType* pVal*/){GRLockType _result; ((IGRGroupFooter*)m_ptr.p)->get_Lock(&_result); return _result; }
	/*virtual*/ HRESULT set_Lock(/*[in]*/ GRLockType pVal){ HRESULT _result = ((IGRGroupFooter*)m_ptr.p)->put_Lock(pVal); return _result; }

};

//@分组{ 主对象

//@备注 PrintViewer，报表打印显示器的ActiveX Control对象的接口，表示报表打印预览查看器。
// 一个 ActiveX Control。在使用时关联一个报表主对象。
// 开始运行时向报表主对象发出生成数据请求，并生成打印页面数据，然后本构件显示生成的打印页面，并且提供其它相应的页面操作与打印操作。
// 报表开发人员可以通过提供外部操作界面来执行构件接口的方法与属性，为最终用户提供报表打印预览界面。
// 虽然 Grid++Report 在内部提供了报表打印预览窗口，但使用本控件开发者可以实现自己个性化的打印预览窗口。
//@别名 打印显示器
class CIGRPrintViewer : public CXComObj /*IDispatch*/
{
public:
	CIGRPrintViewer(){};
	CIGRPrintViewer(IGRPrintViewer* p){ m_ptr = p; }
	//@别名 取COM对象指针()
	IGRPrintViewer* GetPtr(){ return ((IGRPrintViewer*)m_ptr.p); }
	
	//@别名 绑定事件()
	BOOL BindEvent(class CIGRPrintViewerEvents* pEvent);

	//@备注 Report，获取关联报表主对象的接口引用。
	//@别名 取关联报表()
	/*virtual*/ class CIGridppReport get_Report(/*[out][retVal] class CIGridppReport** pVal*/);
	//@备注 Report，设置关联报表主对象的接口引用。
	//@参数 报表对象 
	//@别名 置关联报表(报表对象)
	/*virtual*/ HRESULT set_Report(/*[in]*/ class CIGridppReport* pVal);
	//@备注 CurPageNo，当前显示页的页号，页号从1开始计数。
	//@别名 取当前页号()
	/*virtual*/ long get_CurPageNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrintViewer*)m_ptr.p)->get_CurPageNo(&_result); return _result; }
	//@备注 CurPageNo，当前显示页的页号，页号从1开始计数。
	//@参数 页号 
	//@别名 置当前页号(页号)
	/*virtual*/ HRESULT set_CurPageNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_CurPageNo(pVal); return _result; }
	//@备注 报表的总页数。
	//@别名 取页数()
	/*virtual*/ long get_PageCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrintViewer*)m_ptr.p)->get_PageCount(&_result); return _result; }
	//@备注 Running，获取本控件是否在运行状态中，指示打印显示器是否正在运行显示报表中。
	//@别名 取运行中()
	/*virtual*/ BOOL get_Running(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_Running(&_result); return (VARIANT_TRUE==_result); }
	//@备注 在响应工具栏命令事件时，指定是否再继续执行任务对应的内部行为。
	// 此属性只能在 ToolbarCommandClick 事件响应函数中使用，默认是 true，即在事件响应后再执行命令对应的任务，如打印命令在事件后继续执行弹出打印对话框，然后再进行打印的任务。如果在事件响应函数中将此属性设置为 false，则命令对应的任务在事件后就不会执行。
	//@别名  执行默认工具栏任务(逻辑值)
	/*virtual*/ HRESULT set_DefaultToolbarCommand(/*[in]*/ BOOL _arg1){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_DefaultToolbarCommand(_arg1? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BorderStyle，指定打印显示器的边框样式。
	//@参数 显示器边框样式枚举值 
	//@别名 置边框样式(显示器边框样式枚举值)
	/*virtual*/ HRESULT set_BorderStyle(/*[in]*/ GRViewerBorderStyle pstyle){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_BorderStyle(pstyle); return _result; }
	//@备注 BorderStyle，指定打印显示器的边框样式。
	//@别名 取边框样式()
	/*virtual*/ GRViewerBorderStyle get_BorderStyle(/*[out][retVal] GRViewerBorderStyle* pstyle*/){GRViewerBorderStyle _result; ((IGRPrintViewer*)m_ptr.p)->get_BorderStyle(&_result); return _result; }
	//@备注 EditMode，指定报表文字在预览时的即时编辑模式，默认为不可编辑。
	//@返回 1、禁用；2、单击编辑；3、双击编辑
	//@别名 取编辑模式()
	/*virtual*/ GRPreviewEditMode get_EditMode(/*[out][retVal] GRPreviewEditMode* pVal*/){GRPreviewEditMode _result; ((IGRPrintViewer*)m_ptr.p)->get_EditMode(&_result); return _result; }
	//@备注 EditMode，指定报表文字在预览时的即时编辑模式，默认为不可编辑。 
	//@参数 预览编辑模式枚举值 1、禁用；2、单击编辑；3、双击编辑
	//@别名 置编辑模式(预览编辑模式枚举值)
	/*virtual*/ HRESULT set_EditMode(/*[in]*/ GRPreviewEditMode pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_EditMode(pVal); return _result; }
	//@备注 RowPages，多页查看模式下，每列显示的页数，默认值为2。
	//@返回 值范围为1到16
	//@别名 取每列页数()
	/*virtual*/ long get_RowPages(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrintViewer*)m_ptr.p)->get_RowPages(&_result); return _result; }
	//@备注 RowPages，多页查看模式下，每列显示的页数，默认值为2。
	//@参数 页面数 值范围为1到16
	//@别名 置每列页数(页面数)
	/*virtual*/ HRESULT set_RowPages(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_RowPages(pVal); return _result; }
	//@备注 ColPages，多页查看模式下，每行显示的页数，默认值为3。
	//@返回 值范围为1到20
	//@别名 取每行页数()
	/*virtual*/ long get_ColPages(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ColPages(&_result); return _result; }
	//@备注 ColPages，多页查看模式下，每行显示的页数，默认值为3。
	//@参数 页面数 值范围为1到20
	//@别名 置每行页数(页面数)
	/*virtual*/ HRESULT set_ColPages(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ColPages(pVal); return _result; }
	//@备注 ZoomPercent，打印页面的查看显示百分比例。
	//@返回 默认值100
	//@别名 取显示百分比()
	/*virtual*/ long get_ZoomPercent(/*[out][retVal] long* pVal*/){long _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ZoomPercent(&_result); return _result; }
	//@备注 ZoomPercent，打印页面的查看显示百分比例。
	//@参数 百分比值 默认值100
	//@别名 置显示百分比(百分比值)
	/*virtual*/ HRESULT set_ZoomPercent(/*[in]*/ long pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ZoomPercent(pVal); return _result; }
	//@备注 ViewMode，打印页面的查看模式。
	//@返回 1、连续；2、单页；3、多页
	//@别名 取查看模式()
	/*virtual*/ GRPrintViewMode get_ViewMode(/*[out][retVal] GRPrintViewMode* pVal*/){GRPrintViewMode _result; ((IGRPrintViewer*)m_ptr.p)->get_ViewMode(&_result); return _result; }
	//@备注 ViewMode，打印页面的查看模式。
	//@参数 查看模式枚举值 
	//@别名 置查看模式(查看模式枚举值)
	/*virtual*/ HRESULT set_ViewMode(/*[in]*/ GRPrintViewMode pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ViewMode(pVal); return _result; }
	//@备注 ShowRuler，是否显示标尺标志。
	//@别名 取显示标尺()
	/*virtual*/ BOOL get_ShowRuler(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ShowRuler(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowRuler，是否显示标尺标志。
	//@参数 逻辑值 
	//@别名 置显示标尺(逻辑值)
	/*virtual*/ HRESULT set_ShowRuler(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ShowRuler(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowToolbar，是否显示工具栏标志。
	//@别名 取显示工具栏()
	/*virtual*/ BOOL get_ShowToolbar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ShowToolbar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowToolbar，是否显示工具栏标志。
	//@参数 逻辑值 
	//@返回 1、连续；2、单页；3、多页
	//@别名 置显示工具栏(逻辑值)
	/*virtual*/ HRESULT set_ShowToolbar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ShowToolbar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GenerateStyle，指定打印数据的生成方式。
	//@别名 取生成方式()
	/*virtual*/ GRPrintGenerateStyle get_GenerateStyle(/*[out][retVal] GRPrintGenerateStyle* pVal*/){GRPrintGenerateStyle _result; ((IGRPrintViewer*)m_ptr.p)->get_GenerateStyle(&_result); return _result; }
	//@备注 GenerateStyle，指定打印数据的生成方式。
	//@参数 打印生成方式枚举值 
	//@别名 置生成方式(打印生成方式枚举值)
	/*virtual*/ HRESULT set_GenerateStyle(/*[in]*/ GRPrintGenerateStyle pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_GenerateStyle(pVal); return _result; }
	//@备注 ShowMarginCorner，指示是否显示页边距的拐角指示线。
	//@别名 取显示边距角线()
	/*virtual*/ BOOL get_ShowMarginCorner(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ShowMarginCorner(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowMarginCorner，指示是否显示页边距的拐角指示线。
	//@参数 逻辑值 
	//@别名 置显示边距角线(逻辑值)
	/*virtual*/ HRESULT set_ShowMarginCorner(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ShowMarginCorner(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	/*virtual*/ BOOL get_Searchable(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_Searchable(&_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT set_Searchable(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_Searchable(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowBookmark，指定是否显示书签导航窗口。
	//@别名 取显示书签()
	/*virtual*/ BOOL get_ShowBookmark(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ShowBookmark(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowBookmark，指定是否显示书签导航窗口。
	//@参数 逻辑值 
	//@别名 置显示书签(逻辑值)
	/*virtual*/ HRESULT set_ShowBookmark(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ShowBookmark(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowPrintDlg，指定在执行打印任务时是否显示打印对话框。
	// 如果希望在点击工具栏的打印按钮时不显示打印对话框，可以将此属性设置为 false 即可达到目的。
	//@别名 取显示打印对话框()
	/*virtual*/ BOOL get_ShowPrintDlg(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->get_ShowPrintDlg(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowPrintDlg，指定在执行打印任务时是否显示打印对话框。
	// 如果希望在点击工具栏的打印按钮时不显示打印对话框，可以将此属性设置为 false 即可达到目的。
	//@参数 逻辑值 
	//@别名 置显示打印对话框(逻辑值)
	/*virtual*/ HRESULT set_ShowPrintDlg(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->put_ShowPrintDlg(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 NextPage，显示下一页。
	//@别名 下一页()
	/*virtual*/ HRESULT NextPage(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_NextPage(); return _result; }
	//@备注 PriorPage，显示上一页。
	//@别名 上一页()
	/*virtual*/ HRESULT PriorPage(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_PriorPage(); return _result; }
	//@备注 FirstPage，移动至首页。
	//@别名 首页()
	/*virtual*/ HRESULT FirstPage(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_FirstPage(); return _result; }
	//@备注 LastPage，移动至最后一页。
	//@别名 尾页()
	/*virtual*/ HRESULT LastPage(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_LastPage(); return _result; }
	//@备注 Print，打印出打印查看器生成的打印数据。
	//@参数 显示打印对话框 指示是否显示打印对话框。
	//@别名 打印(显示打印对话框)
	/*virtual*/ HRESULT Print(/*[in]*/ BOOL ShowPrintDialog){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_Print(ShowPrintDialog? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Refresh，调用此方法后，报表将重新生成数据展示，报表生成过程中触发的事件将再次触发（拉模式下）。
	// 提示：从XML加载的报表数据，刷新后将不显示（即：推模式下应重新推入数据）。
	//@别名 刷新()
	/*virtual*/ HRESULT Refresh(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_Refresh(); return _result; }
	//@备注 Start，开始报表生成并按查询显示的方式展现出来，执行此方法后，报表生成过程中的相关事件将被触发。
	//@别名 启动()
	/*virtual*/ HRESULT Start(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_Start(); return _result; }
	//@备注 Stop，停止报表的查询显示，并停止报表的运行，执行本方法后，查询显示输出所占用的资源将被释放掉。
	//@别名 停止()
	/*virtual*/ HRESULT Stop(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_Stop(); return _result; }
	//@备注 ZoomToHeight，缩放页面显示比例到刚好使其高度在查看区域中完整显示出来。注意：此方法只在单页查看模式与连续查看模式下有效。
	//@别名 缩放到适应高度()
	/*virtual*/ HRESULT ZoomToHeight(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ZoomToHeight(); return _result; }
	//@备注 ZoomIn，增大显示比例。注意：此方法只在单页查看模式与连续查看模式下有效。
	//@别名 放大()
	/*virtual*/ HRESULT ZoomIn(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ZoomIn(); return _result; }
	//@备注 ZoomOut，缩小显示比例。注意：此方法只在单页查看模式与连续查看模式下有效。
	//@别名 缩小()
	/*virtual*/ HRESULT ZoomOut(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ZoomOut(); return _result; }
	//@备注 ZoomToFit，缩放页面显示比例到刚好在查看区域中完整显示出来。注意：此方法只在单页查看模式与连续查看模式下有效。
	//@别名 缩放到完整显示()
	/*virtual*/ HRESULT ZoomToFit(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ZoomToFit(); return _result; }
	//@备注 ZoomToWidth，缩放页面显示比例到刚好使其宽度在查看区域中完整显示出来。注意：此方法只在单页查看模式与连续查看模式下有效。
	//@别名 缩放到适应宽度()
	/*virtual*/ HRESULT ZoomToWidth(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ZoomToWidth(); return _result; }
	//@备注 AddToolbarControl，功能：增加工具栏某个默认按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 按钮枚举值 按钮类型枚举： 
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；5、导出；6、邮件；7、保存报表文档；8、连续；9、单页；10、多页；
	// 11、放大；12、缩小；13、缩放百分比；14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；19、关闭；20、剪切；21、刷新；
	// 22、书签；30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；
	// 65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；72、邮件发送报表文档
	//@别名 增加工具栏按钮(按钮枚举值)
	/*virtual*/ HRESULT AddToolbarControl(/*[in]*/ GRToolControlType ControlType){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_AddToolbarControl(ControlType); return _result; }
	//@备注 AddToolbarCustomButton，功能：增加自定义按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 按钮ID BtnID，指定按钮的标识值，有效值从100到200。(取值范围必须在 0 至 1000 之间。)
	//@参数 图标文件 BtnFileName，指定按钮的图像文件名，或网络URL。(自定义按钮图像要求为16*16，256色的 bmp 图。)
	//@参数 气泡提示文本 TooltipText，指定按钮的提示文字。
	//@别名 增加工具栏自定义按钮(按钮ID,图标文件,气泡提示文本)
	/*virtual*/ HRESULT AddToolbarCustomButton(/*[in]*/ long BtnID, /*, [in]*/ const wchar_t* BtnFileName, /*, [in]*/ const wchar_t* TooltipText){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_AddToolbarCustomButton(BtnID, (BSTR)BtnFileName, (BSTR)TooltipText); return _result; }
	//@备注 RemoveToolbarControl，功能：从工具栏中删除显示指定的按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 按钮枚举值 按钮类型枚举：
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；5、导出；6、邮件；7、保存报表文档；8、连续；9、单页；10、多页；
	// 11、放大；12、缩小；13、缩放百分比；14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；19、关闭；20、剪切；21、刷新；
	// 22、书签；30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；
	// 65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；72、邮件发送报表文档
	//@别名 删除工具栏按钮(按钮枚举值)
	/*virtual*/ HRESULT RemoveToolbarControl(/*[in]*/ GRToolControlType ControlType){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_RemoveToolbarControl(ControlType); return _result; }
	//@备注 ResetToolbarContent，功能：清除工具栏中所有显示的按钮，以便重新进行加入定义。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@别名 清空工具栏按钮()
	/*virtual*/ HRESULT ResetToolbarContent(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ResetToolbarContent(); return _result; }
	//@备注 UpdateToolbar，功能：在所有改变按钮定义(增加、删除、重设、恢复等)之后，调用本方法重新显示工具栏，以便新定义生效。
	//@别名 更新工具栏()
	/*virtual*/ HRESULT UpdateToolbar(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_UpdateToolbar(); return _result; }
	//@备注 LoadFromDocumentFile，载入指定的 Grid++Report 文档文件并在打印查看器中显示。
	//@参数 路径文件名 指定文件的路径与名称。
	//@别名 加载报表文档(路径文件名)
	/*virtual*/ BOOL LoadFromDocumentFile(/*[in]*/ const wchar_t* FileName/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->raw_LoadFromDocumentFile((BSTR)FileName, &_result); return (VARIANT_TRUE==_result); }
	//@备注 QuickRefresh，重新生成报表展示而不重新获取报表记录数据。
	//@别名 快速刷新()
	/*virtual*/ HRESULT QuickRefresh(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_QuickRefresh(); return _result; }
	/*virtual*/ BOOL Search(/*[in]*/ const wchar_t* Text, /*, [in]*/ BOOL CaseSensitive, /*, [in]*/ BOOL WholeWord, /*, [in]*/ BOOL ToUp, /*, [in]*/ BOOL FromSelection, /*, [in]*/ BOOL ShowDlg, /*, [in]*/ BOOL ShowMsg/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->raw_Search((BSTR)Text, CaseSensitive? VARIANT_TRUE : VARIANT_FALSE, WholeWord? VARIANT_TRUE : VARIANT_FALSE, ToUp? VARIANT_TRUE : VARIANT_FALSE, FromSelection? VARIANT_TRUE : VARIANT_FALSE, ShowDlg? VARIANT_TRUE : VARIANT_FALSE, ShowMsg? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ BOOL SearchAgain(/*[in]*/ BOOL ShowMsg/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->raw_SearchAgain(ShowMsg? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 DoToolbarCommand，执行工具栏命令对应的任务。
	// 调用此方法不会触发工具栏命令被执行事件，即 ToolbarCommandClick 事件。如果没有显示控件本身的工具栏，而是在控件外围添加操作界面，可以调用此方法完成对应的任务。
	// 也可以在 ToolbarCommandClick 事件响应函数中调用本方法，在调用的前后可以执行一些自定义的任务，从而实现对相应工具栏按钮行为的自定义。
	//@参数 枚举值 对应的工具栏按钮或菜单项。
	//@别名 执行工具栏任务(枚举值)
	/*virtual*/ HRESULT DoToolbarCommand(/*[in]*/ GRToolControlType ControlType){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_DoToolbarCommand(ControlType); return _result; }
	//@备注 UpdateLanguage，在重新设置报表界面语言后，调用本方法更新控件界面显示。
	//@别名 更新语言()
	/*virtual*/ HRESULT UpdateLanguage(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_UpdateLanguage(); return _result; }
	//@备注 在改变界面皮肤或界面语言等设置后，调用本函数进行界面更新显示。
	//@别名 更新UI显示()
	/*virtual*/ HRESULT UpdateUI(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_UpdateUI(); return _result; }
	/*virtual*/ BOOL GetOptionValue(/*[in]*/ GRPrintViewerOption Option/*, [out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRPrintViewer*)m_ptr.p)->raw_GetOptionValue(Option, &_result); return (VARIANT_TRUE==_result); }
	/*virtual*/ HRESULT SetOptionValue(/*[in]*/ GRPrintViewerOption Option, /*, [in]*/ BOOL newVal){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_SetOptionValue(Option, newVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResetToolbar，恢复工具栏按钮默认布局显示，调用本方法后还须调用“更新工具栏(UpdateToolbar)”实时显示更新。
	//@别名 复位工具栏按钮()
	/*virtual*/ HRESULT ResetToolbar(){ HRESULT _result = ((IGRPrintViewer*)m_ptr.p)->raw_ResetToolbar(); return _result; }

};

//@分组}


//@分组{ 事件

//@备注 报表查询显示器事件类
//@别名 查询事件
class CIGRDisplayViewerEvents
{
public:
	//@备注 Click 编号：-600 当鼠标在查询显示器上进行了点击时触发。
	//@别名 被单击事件()
	/*dispatch*/ virtual void Click(){  }
	//@备注 DblClick 编号：-601 当鼠标在查询显示器上进行了双击时触发。
	//@别名 被双击事件()
	/*dispatch*/ virtual void DblClick(){  }
	//@备注 KeyDown 编号：-602 当查询显示器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 按下某键事件(功能键状态,键值)
	/*dispatch*/ virtual void KeyDown(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long Key){  }
	//@备注 KeyPress 编号：-603 当查询显示器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 字符输入事件(键值)
	/*dispatch*/ virtual void KeyPress(/*[in]*/ char Key){  }
	//@备注 KeyUp 编号：-604 当查询显示器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 放开某键事件(功能键状态,键值)
	/*dispatch*/ virtual void KeyUp(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long Key){  }
	//@备注 MouseDown 编号：-605 在查询显示器上鼠标按钮按下时触发。
	//@参数 鼠标按钮 Button，指示操作的鼠标按钮：1、左；2、右；3、中
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的横向位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的纵向位置，相对于显示器的客户区。
	//@别名 鼠标键按下(鼠标按钮,功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseDown(/*[in]*/ GRMouseButton Button, /*, [in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 MouseUp 编号：-607 在查询显示器上鼠标按钮按下再释放时触发。
	//@参数 鼠标按钮 Button，指示操作的鼠标按钮：1、左；2、右；3、中
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的X位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的Y位置，相对于显示器的客户区。
	//@别名 鼠标键放开(鼠标按钮,功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseUp(/*[in]*/ GRMouseButton Button, /*, [in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 MouseMove 编号：-606 在查询显示器上鼠标光标移动时触发。
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的X位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的Y位置，相对于显示器的客户区。
	//@别名 鼠标位置移动(功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseMove(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 ControlClick 编号：1 当鼠标点击在某个部件框上时触发。
	//@参数 部件框对象 
	//@别名 部件框被单击(部件框对象)
	/*dispatch*/ virtual void ControlClick(/*[in]*/ class CIGRControl* pSender){  }
	//@备注 ControlDblClick 编号：2 当鼠标双击在某个部件框上时触发。
	//@参数 部件框对象 事件参数 pSender，部件框。
	//@别名 部件框被双击(部件框对象)
	/*dispatch*/ virtual void ControlDblClick(/*[in]*/ class CIGRControl* pSender){  }
	//@备注 SectionClick 编号：3 当鼠标点击在某个节上时触发。
	//@参数 节对象 事件参数 pSender，节（IGRSection），包括：页眉、页脚、报表节ReportSection(报表头与报表尾)、列节ColumnSection(标题行与内容行)、分组节GroupSection(分组头与分组尾)。
	//@别名 报表节被单击(节对象)
	/*dispatch*/ virtual void SectionClick(/*[in]*/ class CIGRSection* pSender){  }
	//@备注 SectionDblClick 编号：4 当鼠标双击在某个节上时触发。
	//@参数 节对象 事件参数 pSender，节（IGRSection），包括：页眉、页脚、报表节ReportSection(报表头与报表尾)、列节ColumnSection(标题行与内容行)、分组节GroupSection(分组头与分组尾)。
	//@别名 报表节被双击(节对象)
	/*dispatch*/ virtual void SectionDblClick(/*[in]*/ class CIGRSection* pSender){  }
	//@备注 ContentCellClick 编号：5 当鼠标点击在某个内容格上时触发。
	//@参数 内容格对象 事件参数 pSender，内容格。
	//@别名 内容格被单击(内容格对象)
	/*dispatch*/ virtual void ContentCellClick(/*[in]*/ class CIGRColumnContentCell* pSender){  }
	//@备注 ContentCellDblClick 编号：6 当鼠标双击在某个内容格上时触发。
	//@参数 内容格对象 事件参数 pSender，内容格。
	//@别名 内容格被双击(内容格对象)
	/*dispatch*/ virtual void ContentCellDblClick(/*[in]*/ class CIGRColumnContentCell* pSender){  }
	//@备注 TitleCellClick 编号：7 当鼠标点击在某个标题格上时触发。
	//@参数 标题格对象 事件参数 pSender，标题格。
	//@别名 标题格被单击(标题格对象)
	/*dispatch*/ virtual void TitleCellClick(/*[in]*/ class CIGRColumnTitleCell* pSender){  }
	//@备注 TitleCellDblClick 编号：8 当鼠标双击在某个标题格上时触发。
	//@参数 标题格对象 事件参数 pSender，标题格。
	//@别名 标题格被双击(标题格对象)
	/*dispatch*/ virtual void TitleCellDblClick(/*[in]*/ class CIGRColumnTitleCell* pSender){  }
	//@备注 ChartClickSeries 编号：11 当点击图表的图形时触发本事件。
	//@参数 图表框对象 事件参数 pSender，图表框。
	//@参数 序列顺序号 事件参数 SeriesIndex，图标序列顺序号，指定点击位置的对应序列号。
	//@参数 组序号 事件参数 GroupIndex，组序号，指定点击位置的对应组号，如果是XY或XYZ类型图表，表示数据序号。
	//@别名 图表图形被单击(图表框对象,序列顺序号,组序号)
	/*dispatch*/ virtual void ChartClickSeries(/*[in]*/ class CIGRChart* pSender, /*, */ long SeriesIndex, /*, */ long GroupIndex){  }
	//@备注 ChartDblClickSeries 编号：12 当双击图表的图形时触发本事件。
	//@参数 图表框对象 事件参数 pSender，图表框。
	//@参数 序列顺序号 事件参数 SeriesIndex，图标序列顺序号，指定点击位置的对应序列号。
	//@参数 组序号 事件参数 GroupIndex，组序号，指定点击位置的对应组号，如果是XY或XYZ类型图表，表示数据序号。
	//@别名 图表图形被双击(图表框对象,序列顺序号,组序号)
	/*dispatch*/ virtual void ChartDblClickSeries(/*[in]*/ class CIGRChart* pSender, /*, */ long SeriesIndex, /*, */ long GroupIndex){  }
	//@备注 ChartClickLegend 编号：13 当单击图表的图例时触发本事件。
	//@参数 图表框对象 事件参数 pSender，图表框。
	//@参数 序列顺序号 事件参数 SeriesIndex，图标序列顺序号，指定点击位置的对应序列号。
	//@参数 组序号 事件参数 GroupIndex，组序号，指定点击位置的对应组号。
	//@别名 图表图例被单击(图表框对象,序列顺序号,组序号)
	/*dispatch*/ virtual void ChartClickLegend(/*[in]*/ class CIGRChart* pSender, /*, */ long SeriesIndex, /*, */ long GroupIndex){  }
	//@备注 ChartDblClickLegend 编号：14 当双击图表的图例时触发本事件。
	//@参数 图表框对象 事件参数 pSender，图表框。
	//@参数 序列顺序号 事件参数 SeriesIndex，图标序列顺序号，指定点击位置的对应序列号。
	//@参数 组序号 事件参数 GroupIndex，组序号，指定点击位置的对应组号。
	//@别名 图表图例被双击(图表框对象,序列顺序号,组序号)
	/*dispatch*/ virtual void ChartDblClickLegend(/*[in]*/ class CIGRChart* pSender, /*, */ long SeriesIndex, /*, */ long GroupIndex){  }
	//@备注 ColumnLayoutChange 编号：9 当列的显示宽度或顺序发生改变时触发。拖动改变列序时：只是改变了标题格的顺序，列序和字段序并没有改变。
	//@别名 列布局发生改变()
	/*dispatch*/ virtual void ColumnLayoutChange(){  }
	//@备注 SelectionCellChange 编号：10 当前显示的单元格发生改变时触发。
	//@参数 旧行号 OldRow，指示原来选中行的序号。
	//@参数 旧列号 OldCol，指示原来选中列的序号。
	//@别名 选中格改变(旧行号,旧列号)
	/*dispatch*/ virtual void SelectionCellChange(/*[in]*/ long OldRow, /*, [in]*/ long OldCol){  }
	//@备注 StatusChange 编号：22 当控件的查看状态发生改变时触发本事件。当改变分页查看方式，以及改变当前浏览页时都会触发本事件。
	//@别名 状态被改变()
	/*dispatch*/ virtual HRESULT StatusChange(){  }
	//@备注 CloseButtonClick 编号：29 当工具栏上的关闭按钮被点击时触发本事件。
	//@别名 关闭按钮被点击()
	/*dispatch*/ virtual void CloseButtonClick(){  }
	//@备注 CustomButtonClick 编号：30 当点击工具栏上的自定义按钮时触发本事件。
	//@参数 按钮ID 指定自定义按钮的标识号。
	//@别名 自定义按钮被点击(按钮ID)
	/*dispatch*/ virtual void CustomButtonClick(/*[in]*/ long BtnID){  }
	//@备注 ToolbarCommandClick 编号：31 当点击工具栏上的按钮时触发本事件。“5：导出”和“6：邮件”不会产生反馈事件，这两个按钮是导出数据和发送邮件下拉菜单的主按钮，因此不会响应事件。
	// 
	//@参数 查询显示器按钮枚举 按钮类型枚举：
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；5、导出；6、邮件；7、保存报表文档；14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；19、关闭；20、剪切；21、刷新；25、分页方式；
	// 30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；40、打印预览；41、打印应用布局；42、显示页面分隔线；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；80、列显示功能
	//@别名 工具栏按钮被点击(查询显示器按钮枚举)
	/*dispatch*/ virtual void ToolbarCommandClick(/*[in]*/ GRToolControlType2 ControlType){  }
	//@备注 BatchFetchRecord 编号：15  当分批次请求报表明细数据时触发本事件。
	// 当本控件的 BatchGetRecord 属性为 TRUE 时，在显示报表的过程中将触发本事件，当不端向后浏览报表数据时，本事件将不断被触发，直至全部数据被取完。
	// 分批次获取报表数据适合于大数据量报表，避免报表在打开之初产生并传输大量数据，改善整个报表的运行性能。
	// 报表开发者在本事件中根据数据批次信息载入对应批次的明细记录数据。此事件目前仅提供给WEB报表插件，C/S报表组件分批次请求数据还是触发报表引擎对象的 FetchRecord 事件。
	// 分批获取报表数据必须采用推模式给报表提供数据，每当报表请求下一批次数据时，都会触发调用本事件函数，如果在事件中没有追加新的明细记录数据给报表，表示数据已经全部取完。
	//@别名 分批次填充数据()
	/*dispatch*/ virtual void BatchFetchRecord(){  }

};
//@备注 报表打印显示器事件类
//@别名 打印事件
class CIGRPrintViewerEvents
{
public:
	//@备注 Click 编号：-600 当鼠标在打印查看器上点击时触发。
	//@别名 被单击事件()
	/*dispatch*/ virtual void Click(){  }
	//@备注 DblClick 编号：-601 当鼠标在打印查看器上双击时触发。
	//@别名 被双击事件()
	/*dispatch*/ virtual void DblClick(){  }
	//@备注 KeyDown 编号：-602 当打印查看器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 按下某键事件(功能键状态,键值)
	/*dispatch*/ virtual void KeyDown(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long Key){  }
	//@备注 KeyPress 编号：-603 当打印查看器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 字符输入事件(键值)
	/*dispatch*/ virtual void KeyPress(/*[in]*/ char Key){  }
	//@备注 KeyUp 编号：-604 当打印查看器拥有输入焦点时，某个键盘健按下时触发。键事件按下列顺序发生： KeyDown、KeyPress、KeyUp
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 键值 Key，指示按下键的虚键值。
	//@别名 放开某键事件(功能键状态,键值)
	/*dispatch*/ virtual void KeyUp(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long Key){  }
	//@备注 MouseDown 编号：-605 在打印查看器上鼠标按钮按下时触发。
	//@参数 鼠标键 Button，指示操作的鼠标按钮：1、左；2、右；3、中
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的横向位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的纵向位置，相对于显示器的客户区。
	//@别名 鼠标键按下(鼠标键,功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseDown(/*[in]*/ GRMouseButton Button, /*, [in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 MouseUp 编号：-607 在打印查看器上鼠标按钮按下之后再释放时触发。
	//@参数 鼠标键 Button，指示操作的鼠标按钮：1、左；2、右；3、中
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的横向位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的纵向位置，相对于显示器的客户区。
	//@别名 鼠标键放开(鼠标键,功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseUp(/*[in]*/ GRMouseButton Button, /*, [in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 MouseMove 编号：-606
	//@参数 功能键状态 Shift，指示切换键的状态：1、切换键Shift；2、切换键Alt；4、切换键Ctrl；8、鼠标左按钮；16、鼠标右按钮；32、鼠标中按钮；64、鼠标双击
	//@参数 横向位置 xPos，鼠标光标的横向位置，相对于显示器的客户区。
	//@参数 纵向位置 yPos，鼠标光标的纵向位置，相对于显示器的客户区。
	//@别名 鼠标位置移动(功能键状态,横向位置,纵向位置)
	/*dispatch*/ virtual void MouseMove(/*[in]*/ GRShiftStates Shift, /*, [in]*/ long xPos, /*, [in]*/ long yPos){  }
	//@备注 CurPageChange 编号：21
	//@参数 新当前页号 
	//@别名 当前页被改变(新当前页号)
	/*dispatch*/ virtual void CurPageChange(/*[in]*/ long NewCurPageNo){  }
	//@备注 StatusChange 编号：22 当打印查看器的状态信息改变时触发。
	// 这里所指状态信息包括：1、当前显示页的页号；2、页面查看模式；3、多也查看模式下，行列显示页数；4、显示比例；5、标尺是否显示标志；6、工具栏是否显示标志。
	//@别名 状态被改变()
	/*dispatch*/ virtual HRESULT StatusChange(){  }
	//@备注 RulerClick 编号：23
	//@参数 是否横向标尺 IsHorzRuler，指示当前点击的是否横向标尺。
	//@别名 标尺被单击(是否横向标尺)
	/*dispatch*/ virtual void RulerClick(/*[in]*/ BOOL IsHorzRuler){  }
	//@备注 RulerDblClick 编号：24
	//@参数 是否横向标尺 IsHorzRuler，指示当前点击的是否横向标尺。
	//@别名 标尺被双击(是否横向标尺)
	/*dispatch*/ virtual void RulerDblClick(/*[in]*/ BOOL IsHorzRuler){  }
	//@备注 PageClick 编号：27
	//@别名 页被单击()
	/*dispatch*/ virtual void PageClick(){  }
	//@备注 PageDblClick 编号：28
	//@别名 页被双击()
	/*dispatch*/ virtual void PageDblClick(){  }
	//@备注 CloseButtonClick 编号：29 当工具栏上的关闭按钮被点击时触发本事件。通过响应本事件，执行关闭预览窗口的动作。
	//@别名 关闭按钮被点击()
	/*dispatch*/ virtual void CloseButtonClick(){  }
	//@备注 CustomButtonClick 编号：30 当点击工具栏上的自定义按钮时触发本事件。
	//@参数 按钮ID 自定义增加的工具栏按钮ID号。
	//@别名 自定义按钮被点击(按钮ID)
	/*dispatch*/ virtual void CustomButtonClick(/*[in]*/ long BtnID){  }
	//@备注 ToolbarCommandClick 编号：31 当点击工具栏上的按钮时触发本事件。
	// “5：导出”和“6：邮件”不会产生反馈事件，这两个按钮是导出数据和发送邮件下拉菜单的主按钮，因此不会响应事件
	//@参数 打印显示器按钮枚举 按钮类型枚举：
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；5、导出；6、邮件；7、保存报表文档；8、连续；9、单页；10、多页；11、放大；12、缩小；13、缩放百分比；
	// 14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；19、关闭；20、剪切；21、刷新；22、书签；
	// 30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；72、邮件发送报表文档
	//@别名 工具栏按钮被点击(打印显示器按钮枚举)
	/*dispatch*/ virtual void ToolbarCommandClick(/*[in]*/ GRToolControlType ControlType){  }

};
//@分组}

//@分组{ 主对象

//@备注 DisplayViewer，报表查询显示器的ActiveX Control对象的接口。
// 一个 ActiveX Control。是报表查询显示器的ActiveX Control对象的接口定义，在使用时关联一个报表主对象。
// 开始运行时向报表主对象发出生成数据请求，然后本构件显示报表主对象生成的数据，本对象为最终用户提供了完善的查看数据的操作。
// 报表开发者通过对本对象交互事件的响应，可以为报表最终用户提供可交互的报表查询功能。
// 例如通过对汇总报表的明细网格内容格的双击事件的响应，打开对应的明细报表，达到从汇总报表向明细报表的穿透查询。
// 通过该控件实现报表查询显示功能也是 Grid++Report 独有与独创的。
//@别名 查询显示器
class CIGRDisplayViewer : public CXComObj /*IDispatch*/
{
public:
	CIGRDisplayViewer(){};
	CIGRDisplayViewer(IGRDisplayViewer* p){ m_ptr = p; }
	//@备注 创建报表显示器实例()
	//@别名 创建()
	BOOL Create(int x, int y, int cx, int cy, HWINDOW hWindow);
	//@别名 取COM对象指针()
	IGRDisplayViewer* GetPtr(){ return ((IGRDisplayViewer*)m_ptr.p); }

	//@别名 绑定事件()
	BOOL BindEvent(CIGRDisplayViewerEvents* pEvent);

	//@备注 BorderStyle，指定查询显示器的边框样式。
	//@参数 显示器边框样式枚举值 
	//@别名 置边框样式(显示器边框样式枚举值)
	/*virtual*/ HRESULT set_BorderStyle(/*[in]*/ GRViewerBorderStyle pstyle){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BorderStyle(pstyle); return _result; }
	//@备注 BorderStyle，指定查询显示器的边框样式。
	//@别名 取边框样式()
	/*virtual*/ GRViewerBorderStyle get_BorderStyle(/*[out][retVal] GRViewerBorderStyle* pstyle*/){GRViewerBorderStyle _result; ((IGRDisplayViewer*)m_ptr.p)->get_BorderStyle(&_result); return _result; }
	//@备注 LeftGap，左边留出的空白间距，以像素为单位。
	//@返回 默认值0
	//@别名 取左边距()
	/*virtual*/ long get_LeftGap(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_LeftGap(&_result); return _result; }
	//@备注 LeftGap，左边留出的空白间距，以像素为单位。
	//@参数 边距值 默认值0
	//@别名 置左边距(边距值)
	/*virtual*/ HRESULT set_LeftGap(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_LeftGap(pVal); return _result; }
	//@备注 RightGap，右边留出的空白间距，以像素为单位。
	//@返回 默认值0
	//@别名 取右边距()
	/*virtual*/ long get_RightGap(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_RightGap(&_result); return _result; }
	//@备注 RightGap，右边留出的空白间距，以像素为单位。
	//@参数 边距值 默认值0
	//@别名 置右边距(边距值)
	/*virtual*/ HRESULT set_RightGap(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_RightGap(pVal); return _result; }
	//@备注 TopGap，上边留出的空白间距，以像素为单位。
	//@返回 默认值0
	//@别名 取上边距()
	/*virtual*/ long get_TopGap(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_TopGap(&_result); return _result; }
	//@备注 TopGap，上边留出的空白间距，以像素为单位。
	//@参数 边距值 默认值0
	//@别名 置上边距(边距值)
	/*virtual*/ HRESULT set_TopGap(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_TopGap(pVal); return _result; }
	//@备注 BottomGap，下边留出的空白间距，以像素为单位。
	//@返回 默认值0
	//@别名 取下边距()
	/*virtual*/ long get_BottomGap(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BottomGap(&_result); return _result; }
	//@备注 BottomGap，下边留出的空白间距，以像素为单位。
	//@参数 边距值 默认值0
	//@别名 置下边距(边距值)
	/*virtual*/ HRESULT set_BottomGap(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BottomGap(pVal); return _result; }
	//@备注 RowsPerPage，指定浏览数据时的分页方式。
	// 当本属性为以下几种情况时，查询显示器以不同的方式对数据进行分页处理：
	// =0：不进行分页，所有数据以不间断的表格显示。
	// <0：按控件的大小自动进行分页。
	// >0：由本属性指定每页数据的行数。
	//@别名 取分页方式()
	/*virtual*/ long get_RowsPerPage(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_RowsPerPage(&_result); return _result; }
	//@备注 RowsPerPage，指定浏览数据时的分页方式。
	// 当本属性为以下几种情况时，查询显示器以不同的方式对数据进行分页处理：
	// =0：不进行分页，所有数据以不间断的表格显示。
	// <0：按控件的大小自动进行分页。
	// >0：由本属性指定每页数据的行数。
	//@参数 整数值 
	//@别名 置分页方式(整数值)
	/*virtual*/ HRESULT set_RowsPerPage(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_RowsPerPage(pVal); return _result; }
	//@备注 ShowHeader，是否显示报表头的标志。
	//@别名 取显示报表头()
	/*virtual*/ BOOL get_ShowHeader(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ShowHeader(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowHeader，是否显示报表头的标志。
	//@参数 逻辑值 
	//@别名 置显示报表头(逻辑值)
	/*virtual*/ HRESULT set_ShowHeader(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ShowHeader(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowFooter，是否显示报表尾的标志。
	//@别名 取显示报表尾()
	/*virtual*/ BOOL get_ShowFooter(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ShowFooter(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowFooter，是否显示报表尾的标志。
	//@参数 逻辑值 
	//@别名 置显示报表尾(逻辑值)
	/*virtual*/ HRESULT set_ShowFooter(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ShowFooter(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ShowToolbar，指定是否显示本控件的工具栏。
	//@别名 取显示工具栏()
	/*virtual*/ BOOL get_ShowToolbar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ShowToolbar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowToolbar，指定是否显示本控件的工具栏。
	//@参数 逻辑值 
	//@别名 置显示工具栏(逻辑值)
	/*virtual*/ HRESULT set_ShowToolbar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ShowToolbar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Resortable，指定是否可以通过点击明细网格的列标题对明细记录进行重新排序。
	//@别名 取点击列可重排序()
	/*virtual*/ BOOL get_Resortable(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_Resortable(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Resortable，指定是否可以通过点击明细网格的列标题对明细记录进行重新排序。
	//@参数 是否重新排序 
	//@别名 置点击列可重排序(是否重新排序)
	/*virtual*/ HRESULT set_Resortable(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_Resortable(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResortCaseSensitive，指定点击列标题进行排序时，对字符进行排序比较是否大小写敏感。
	//@别名 取重排序区分大小写()
	/*virtual*/ BOOL get_ResortCaseSensitive(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ResortCaseSensitive(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ResortCaseSensitive，指定点击列标题进行排序时，对字符进行排序比较是否大小写敏感。
	//@参数 逻辑值 
	//@别名 置重排序区分大小写(逻辑值)
	/*virtual*/ HRESULT set_ResortCaseSensitive(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ResortCaseSensitive(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResortDefaultAsc，当点击列标题进行排序时，首先是否按升序进行排序。
	//@别名 取重排序按升序()
	/*virtual*/ BOOL get_ResortDefaultAsc(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ResortDefaultAsc(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ResortDefaultAsc，当点击列标题进行排序时，首先是否按升序进行排序。
	//@参数 逻辑值 
	//@别名 置重排序按升序(逻辑值)
	/*virtual*/ HRESULT set_ResortDefaultAsc(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ResortDefaultAsc(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GridTitle3D，指定是否将明细网格的列标题显示为3D形状。
	//@别名 取网格标题3D()
	/*virtual*/ BOOL get_GridTitle3D(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_GridTitle3D(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GridTitle3D，指定是否将明细网格的列标题显示为3D形状。
	//@参数 逻辑值 
	//@别名 置网格标题3D(逻辑值)
	/*virtual*/ HRESULT set_GridTitle3D(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_GridTitle3D(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Searchable，指示是否提供默认的文字查找功能。
	// 如果本属性置为真，当查询显示器控件获得键盘输入焦点时，按下 Ctrl+F 键会弹出文字查找对话框，按下  F3 键会进行继续查找。
	//@别名 取可查找()
	/*virtual*/ BOOL get_Searchable(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_Searchable(&_result); return (VARIANT_TRUE==_result); }
	//@备注 Searchable，指示是否提供默认的文字查找功能。
	// 如果本属性置为真，当查询显示器控件获得键盘输入焦点时，按下 Ctrl+F 键会弹出文字查找对话框，按下  F3 键会进行继续查找。
	//@参数 逻辑值 
	//@别名 置可查找(逻辑值)
	/*virtual*/ HRESULT set_Searchable(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_Searchable(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GridCenterView，当报表明细网格所有列的总宽度小于本控件的宽度时，指定明细网格是否水平居中显示在本控件中。
	// 当报表明细网格所有列的总宽度小于本控件的宽度时，指定明细网格是否水平居中显示在本控件中。如果明细网格居中显示，报表头与报表尾也会跟随居中显示。
	// 如果报表不具备明细网格，此属性为真将指定报表头与报表尾在控件窗口中水平居中显示。
	//@别名 取报表居中显示()
	/*virtual*/ BOOL get_GridCenterView(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_GridCenterView(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GridCenterView，当报表明细网格所有列的总宽度小于本控件的宽度时，指定明细网格是否水平居中显示在本控件中。
	// 当报表明细网格所有列的总宽度小于本控件的宽度时，指定明细网格是否水平居中显示在本控件中。如果明细网格居中显示，报表头与报表尾也会跟随居中显示。
	// 如果报表不具备明细网格，此属性为真将指定报表头与报表尾在控件窗口中水平居中显示。
	//@参数 逻辑值 
	//@别名 置报表居中显示(逻辑值)
	/*virtual*/ HRESULT set_GridCenterView(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_GridCenterView(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 GridCanShrink，当明细网格数据较少时，是否缩小明细网格显示高度以适应数据，默认值为真。
	//@返回 注：为真时，报表尾会紧跟在明细网格下显示，不会固定在查询显示器底部。
	//@别名 取网格可收缩适应()
	/*virtual*/ BOOL get_GridCanShrink(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_GridCanShrink(&_result); return (VARIANT_TRUE==_result); }
	//@备注 GridCanShrink，当明细网格数据较少时，是否缩小明细网格显示高度以适应数据，默认值为真。
	//@参数 逻辑值 注：为真时，报表尾会紧跟在明细网格下显示，不会固定在查询显示器底部。
	//@别名 置网格可收缩适应(逻辑值)
	/*virtual*/ HRESULT set_GridCanShrink(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_GridCanShrink(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResizeToFit，指定是否对报表节的大小进行缩放，以适应本控件窗口的大小，以便所有报表节都完整显示出来。此属性仅当控件中显示的报表没有明细网格时有效。
	// 如果本属性值为真，报表中的所有报表头尾节的高度将按加权比例进行伸缩，高度之和与本控件的高度保持一样，所有报表头尾节的宽度也将伸缩与本控件的宽度一样。
	// 如果本属性值为假，则所有报表头尾节的大小保持不变，如果超出范围，本控件将自动产生滚动条，通过滚动可以完整查看整个报表的内容。
	//@别名 取节缩放适应()
	/*virtual*/ BOOL get_ResizeToFit(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ResizeToFit(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ResizeToFit，指定是否对报表节的大小进行缩放，以适应本控件窗口的大小，以便所有报表节都完整显示出来。此属性仅当控件中显示的报表没有明细网格时有效。
	// 如果本属性值为真，报表中的所有报表头尾节的高度将按加权比例进行伸缩，高度之和与本控件的高度保持一样，所有报表头尾节的宽度也将伸缩与本控件的宽度一样。
	// 如果本属性值为假，则所有报表头尾节的大小保持不变，如果超出范围，本控件将自动产生滚动条，通过滚动可以完整查看整个报表的内容。
	//@参数 逻辑值 
	//@别名 置节缩放适应(逻辑值)
	/*virtual*/ HRESULT set_ResizeToFit(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ResizeToFit(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SelectionBackColor，查询显示时，选中格或行的背景填充色。
	//@别名 取选中背景色()
	/*virtual*/ OLE_COLOR get_SelectionBackColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDisplayViewer*)m_ptr.p)->get_SelectionBackColor(&_result); return _result; }
	//@备注 SelectionBackColor，查询显示时，选中格或行的背景填充色。
	//@参数 背景色 
	//@别名 置选中背景色(背景色)
	/*virtual*/ HRESULT set_SelectionBackColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelectionBackColor(pVal); return _result; }
	//@备注 SelectionForeColor，查询显示时，选中格或行的前景色。
	//@别名 取选中前景色()
	/*virtual*/ OLE_COLOR get_SelectionForeColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDisplayViewer*)m_ptr.p)->get_SelectionForeColor(&_result); return _result; }
	//@备注 SelectionForeColor，查询显示时，选中格或行的前景色。
	//@参数 整数值 
	//@别名 置选中前景色(整数值)
	/*virtual*/ HRESULT set_SelectionForeColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelectionForeColor(pVal); return _result; }
	//@备注 SelectionFollowScroll，指示选中格或行是否跟随表格的垂直滚动而滚动。
	//@别名 取选中行跟随滚动()
	/*virtual*/ BOOL get_SelectionFollowScroll(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_SelectionFollowScroll(&_result); return (VARIANT_TRUE==_result); }
	//@备注 SelectionFollowScroll，指示选中格或行是否跟随表格的垂直滚动而滚动。
	//@参数 逻辑值 
	//@别名 置选中行跟随滚动(逻辑值)
	/*virtual*/ HRESULT set_SelectionFollowScroll(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelectionFollowScroll(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AlwaysShowHScrollBar，在所有列宽未占满查询显示器宽度时，是否始终显示明细表格的水平滚动条的标志。
	//@别名 取始终显示水平滚动条()
	/*virtual*/ BOOL get_AlwaysShowHScrollBar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_AlwaysShowHScrollBar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AlwaysShowHScrollBar，在所有列宽未占满查询显示器宽度时，是否始终显示明细表格的水平滚动条的标志。
	//@参数 逻辑值 
	//@别名 置始终显示水平滚动条(逻辑值)
	/*virtual*/ HRESULT set_AlwaysShowHScrollBar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_AlwaysShowHScrollBar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 AlwaysShowVScrollBar，在数据量少未占满查询显示器垂直显示空间的情况下，是否始终显示明细网格的垂直滚动条的标志。
	//@别名 取始终显示垂直滚动条()
	/*virtual*/ BOOL get_AlwaysShowVScrollBar(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_AlwaysShowVScrollBar(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AlwaysShowVScrollBar，在数据量少未占满查询显示器垂直显示空间的情况下，是否始终显示明细网格的垂直滚动条的标志。
	//@参数 逻辑值 
	//@别名 置始终显示垂直滚动条(逻辑值)
	/*virtual*/ HRESULT set_AlwaysShowVScrollBar(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_AlwaysShowVScrollBar(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BackgroundColor，当明细网格不能完整充满查询显示器的显示区域时，指定明细网格外围的空白区域的背景填充色。
	//@别名 取空白区背景色()
	/*virtual*/ OLE_COLOR get_BackgroundColor(/*[out][retVal] OLE_COLOR* pVal*/){OLE_COLOR _result; ((IGRDisplayViewer*)m_ptr.p)->get_BackgroundColor(&_result); return _result; }
	//@备注 BackgroundColor，当明细网格不能完整充满查询显示器的显示区域时，指定明细网格外围的空白区域的背景填充色。
	//@参数 整数值 
	//@别名 置空白区背景色(整数值)
	/*virtual*/ HRESULT set_BackgroundColor(/*[in]*/ OLE_COLOR pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BackgroundColor(pVal); return _result; }
	//@备注 ColumnMove，指定是否可以用鼠标拖放改变明细网格列的显示顺序。
	//@别名 取列顺序可移动()
	/*virtual*/ BOOL get_ColumnMove(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ColumnMove(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ColumnMove，指定是否可以用鼠标拖放改变明细网格列的显示顺序。
	//@参数 逻辑值 
	//@别名 置列顺序可移动(逻辑值)
	/*virtual*/ HRESULT set_ColumnMove(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ColumnMove(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ColumnResize，指定是否可以通过鼠标拖放改变明细网格列的显示宽度。
	//@别名 取列宽可调整()
	/*virtual*/ BOOL get_ColumnResize(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ColumnResize(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ColumnResize，指定是否可以通过鼠标拖放改变明细网格列的显示宽度。
	//@参数 逻辑值 
	//@别名 置列宽可调整(逻辑值)
	/*virtual*/ HRESULT set_ColumnResize(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ColumnResize(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 RowSelection，指定在查询显示报表时是否整行选中内容行。如果不是，选中仅为一个格。
	//@别名 取整行选中()
	/*virtual*/ BOOL get_RowSelection(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_RowSelection(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RowSelection，指定在查询显示报表时是否整行选中内容行。如果不是，选中仅为一个格。
	//@参数 逻辑值 
	//@别名 置整行选中(逻辑值)
	/*virtual*/ HRESULT set_RowSelection(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_RowSelection(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BatchGetRecord，指定是否为分批获取报表明细记录数据。
	// 当报表的明细数据量比较大时，可以将此属性设置为TRUE，指示报表的明细数据将分批获取。
	// 分批获取报表数据时，WEB报表插件在请求数据时将触发本控件的 BatchFetchRecord 事件，C/S报表组件在请求数据时将触发报表主对象的 FetchRecord 事件，在事件中将一个批次的数据填入到报表中。
	//@别名 取分批获取记录()
	/*virtual*/ BOOL get_BatchGetRecord(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BatchGetRecord(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BatchGetRecord，指定是否为分批获取报表明细记录数据。
	// 当报表的明细数据量比较大时，可以将此属性设置为TRUE，指示报表的明细数据将分批获取。
	// 分批获取报表数据时，WEB报表插件在请求数据时将触发本控件的 BatchFetchRecord 事件，C/S报表组件在请求数据时将触发报表主对象的 FetchRecord 事件，在事件中将一个批次的数据填入到报表中。
	//@参数 逻辑值 本属性为真时会触发“查询显示器_分批次填充数据”事件
	//@别名 置分批获取记录(逻辑值)
	/*virtual*/ HRESULT set_BatchGetRecord(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BatchGetRecord(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BatchWantRecords，指定一个批次希望获取的记录数量，如果为0，将由数据提供者自己确定一个批次获取的记录数量。
	// 如果本属性值大于0，当某批次取得的记录数小于本属性值，报表将认为数据已经全部取完。反之只有当某批次取得的记录数为0，报表认为数据已经全部取完。
	//@别名 取分批显示记录数()
	/*virtual*/ long get_BatchWantRecords(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BatchWantRecords(&_result); return _result; }
	//@备注 BatchWantRecords，指定一个批次希望获取的记录数量，如果为0，将由数据提供者自己确定一个批次获取的记录数量。
	// 如果本属性值大于0，当某批次取得的记录数小于本属性值，报表将认为数据已经全部取完。反之只有当某批次取得的记录数为0，报表认为数据已经全部取完。
	//@参数 整数值 
	//@别名 置分批显示记录数(整数值)
	/*virtual*/ HRESULT set_BatchWantRecords(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BatchWantRecords(pVal); return _result; }
	//@备注 TotalRecord，在分批次获取报表明细数据，且当获取第一批次的数据时，指定全部记录总数。
	// 此属性只能在 BatchFetchRecord 事件上设置，本属性值自动设置为-1，表示记录总数是未知的。
	// 在分批次获取报表明细数据时，指定本属性的值并不是必须的。如果能在取第一批次的数据时指定全部记录总数，有助于报表查询显示器产生更准确的分页信息或滚动条信息，如果报表没有分组，将能产生精确无误的分页信息或滚动条信息。
	//@别名 取总记录数()
	/*virtual*/ long get_TotalRecord(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_TotalRecord(&_result); return _result; }
	//@备注 TotalRecord，在分批次获取报表明细数据，且当获取第一批次的数据时，指定全部记录总数。
	// 此属性只能在 BatchFetchRecord 事件上设置，本属性值自动设置为-1，表示记录总数是未知的。
	// 在分批次获取报表明细数据时，指定本属性的值并不是必须的。如果能在取第一批次的数据时指定全部记录总数，有助于报表查询显示器产生更准确的分页信息或滚动条信息，如果报表没有分组，将能产生精确无误的分页信息或滚动条信息。
	//@参数 整数值 
	//@别名 置总记录数(整数值)
	/*virtual*/ HRESULT set_TotalRecord(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_TotalRecord(pVal); return _result; }
	//@备注 BatchFinished，指示在分批次获取报表明细记录时，所有数据已经全部获取完备。
	// 此属性只能在 BatchFetchRecord 事件上设置。
	// Grid++Report 会根据返回的记录数自动确定数据是否全部取完。
	// 报表开发者也可以在在 BatchFetchRecord 事件上设置 BatchFinished 属性值为 TRUE 指示数据已经取完，这样报表将不会再请求批次数据，BatchFetchRecord 事件也不会再被触发。
	//@别名 取分批完成()
	/*virtual*/ BOOL get_BatchFinished(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BatchFinished(&_result); return (VARIANT_TRUE==_result); }
	//@备注 BatchFinished，指示在分批次获取报表明细记录时，所有数据已经全部获取完备。
	// 此属性只能在 BatchFetchRecord 事件上设置。
	// Grid++Report 会根据返回的记录数自动确定数据是否全部取完。
	// 报表开发者也可以在在 BatchFetchRecord 事件上设置 BatchFinished 属性值为 TRUE 指示数据已经取完，这样报表将不会再请求批次数据，BatchFetchRecord 事件也不会再被触发。
	//@参数 逻辑值 
	//@别名 置分批完成(逻辑值)
	/*virtual*/ HRESULT set_BatchFinished(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_BatchFinished(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 BatchNo，指示在分批次获取报表明细记录时，指示当前请求数据的批次序号，序号从1开始。
	//@别名 取分批序号()
	/*virtual*/ long get_BatchNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BatchNo(&_result); return _result; }
	//@备注 BatchStartRecNo，指示在分批次获取报表明细记录时，指示当前请求数据的开始记录序号，记录序号从0开始。
	// 此属性只有在 BatchFetchRecord 事件上读取才有意义，报表开发者根据其值获取对应批次的数据。
	//@别名 取分批开始记录号()
	/*virtual*/ long get_BatchStartRecNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_BatchStartRecNo(&_result); return _result; }
	//@备注 Running，获取本控件是否在运行状态中，指示查询显示器是否正在运行显示报表中。
	//@别名 取运行中()
	/*virtual*/ BOOL get_Running(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_Running(&_result); return (VARIANT_TRUE==_result); }
	//@备注 RowCount，运行时，当前查看报表的总行数。仅运行时可用：每个记录对应的显示行为一行，每个显示的分组头算一行，每个显示的分组尾算一行，总行数为以上三种数据的合计。
	//@别名 取行数()
	/*virtual*/ long get_RowCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_RowCount(&_result); return _result; }
	//@备注 PageCount，获取当前数据的页数。
	//@别名 取页数()
	/*virtual*/ long get_PageCount(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_PageCount(&_result); return _result; }
	//@备注 在响应工具栏命令事件时，指定是否再继续执行任务对应的内部行为。
	// 此属性只能在 ToolbarCommandClick 事件响应函数中使用，默认是 true，即在事件响应后再执行命令对应的任务，如打印命令在事件后继续执行弹出打印对话框，然后再进行打印的任务。如果在事件响应函数中将此属性设置为 false，则命令对应的任务在事件后就不会执行。
	//@别名  执行默认工具栏任务(逻辑值)
	/*virtual*/ HRESULT set_DefaultToolbarCommand(/*[in]*/ BOOL _arg1){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_DefaultToolbarCommand(_arg1? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 Report，获取关联报表主对象的接口引用。
	//@别名 取关联报表()
	/*virtual*/ class CIGridppReport get_Report(/*[out][retVal] class CIGridppReport** pVal*/);
	//@备注 Report，设置关联报表主对象。
	//@参数 报表对象 
	//@别名 置关联报表(报表对象)
	/*virtual*/ HRESULT set_Report(/*[in]*/ class CIGridppReport* pVal);
	//@备注 ShowPreviewLine，指示是否显示报表打印页面的垂直区域分隔线。
	// 在报表查询显示中显示出页面分隔线，这样可以进行明确的列宽调整，以便得到适合的打印输出。
	//@别名 取显示页面分隔线()
	/*virtual*/ BOOL get_ShowPreviewLine(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ShowPreviewLine(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowPreviewLine，指示是否显示报表打印页面的垂直区域分隔线。
	// 在报表查询显示中显示出页面分隔线，这样可以进行明确的列宽调整，以便得到适合的打印输出。
	//@参数 逻辑值 
	//@别名 置显示页面分隔线(逻辑值)
	/*virtual*/ HRESULT set_ShowPreviewLine(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ShowPreviewLine(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 SelRowNo，选中单元格的行序号。行序号从0开始计数；如果存在分组，每个显示的分组头或分组尾各算一行。
	//@别名 取选中行号()
	/*virtual*/ long get_SelRowNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_SelRowNo(&_result); return _result; }
	//@备注 SelRowNo，选中单元格的行序号。行序号从0开始计数；如果存在分组，每个显示的分组头或分组尾各算一行。
	//@参数 行序号 行序号从0开始计数。
	//@别名 置选中行号(行序号)
	/*virtual*/ HRESULT set_SelRowNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelRowNo(pVal); return _result; }
	//@备注 SelColumnNo，选中单元格的列序号，列序号从0开始计数。
	//@别名 取选中列号()
	/*virtual*/ long get_SelColumnNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_SelColumnNo(&_result); return _result; }
	//@备注 SelColumnNo，选中单元格的列序号，列序号从0开始计数。
	//@参数 列号 从0开始计数。
	//@别名 置选中列号(列号)
	/*virtual*/ HRESULT set_SelColumnNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelColumnNo(pVal); return _result; }
	//@备注 SelColumnName，获取明细网格中当前选中列的名称。
	//@别名 取选中列名称()
	/*virtual*/ CXText get_SelColumnName(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRDisplayViewer*)m_ptr.p)->get_SelColumnName(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SelColumnName，设置明细网格中当前选中列的名称。
	//@参数 列名称 
	//@别名 置选中列名称(列名称)
	/*virtual*/ HRESULT set_SelColumnName(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SelColumnName((BSTR)pVal); return _result; }
	//@备注 VScrollPos，在运行时，获取与设置垂直滚动条的位置。
	//@别名 取垂直滚动条位置()
	/*virtual*/ long get_VScrollPos(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_VScrollPos(&_result); return _result; }
	//@备注 VScrollPos，在运行时，获取与设置垂直滚动条的位置。
	//@参数 整数值 
	//@别名 置垂直滚动条位置(整数值)
	/*virtual*/ HRESULT set_VScrollPos(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_VScrollPos(pVal); return _result; }
	//@备注 HScrollPos，在运行时，获取与设置水平滚动条的位置。
	//@别名 取水平滚动条位置()
	/*virtual*/ long get_HScrollPos(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_HScrollPos(&_result); return _result; }
	//@备注 HScrollPos，在运行时，获取与设置水平滚动条的位置。
	//@参数 整数值 
	//@别名 置水平滚动条位置(整数值)
	/*virtual*/ HRESULT set_HScrollPos(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_HScrollPos(pVal); return _result; }
	//@备注 SortColumns，指定当前进行排序的列名称，如果有多个列，中间用“;”隔开。
	// 本属性值也会包含排序顺序，如果某列是按降序排列，则会加上“DESC”标志。
	// 如本属性值为“Column1 DESC;Column2”，指定按Column1与Column2进行排序，其中Column1按降序排列，Column2按升序排列。
	//@别名 取排序列()
	/*virtual*/ CXText get_SortColumns(/*[out][retVal] const wchar_t** pVal*/){ BSTR _result = 0; CXText _result_text; ((IGRDisplayViewer*)m_ptr.p)->get_SortColumns(&_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 SortColumns，指定当前进行排序的列名称，如果有多个列，中间用“;”隔开。
	// 本属性值也会包含排序顺序，如果某列是按降序排列，则会加上“DESC”标志。
	// 如本属性值为“Column1 DESC;Column2”，指定按Column1与Column2进行排序，其中Column1按降序排列，Column2按升序排列。
	//@参数 列名称 可以指定多列名称并分别排序，比如：“Column1 DESC;Column2”，指定按Column1与Column2进行排序，其中Column1按降序排列，Column2按升序排列。
	//@别名 置排序列(列名称)
	/*virtual*/ HRESULT set_SortColumns(/*[in]*/ const wchar_t* pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_SortColumns((BSTR)pVal); return _result; }
	//@备注 AlwaysShowSelection，指定是否始终显示选中的内容格或内容行。
	// 当本属性值为真时，即使控件没有键盘输入焦点，选中的内容还是以选中色突出显示。
	//@别名 取始终显示选中行()
	/*virtual*/ BOOL get_AlwaysShowSelection(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_AlwaysShowSelection(&_result); return (VARIANT_TRUE==_result); }
	//@备注 AlwaysShowSelection，指定是否始终显示选中的内容格或内容行。
	// 当本属性值为真时，即使控件没有键盘输入焦点，选中的内容还是以选中色突出显示。
	//@参数 逻辑值 
	//@别名 置始终显示选中行(逻辑值)
	/*virtual*/ HRESULT set_AlwaysShowSelection(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_AlwaysShowSelection(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ToPostColumnLayout，指定是否将本控件上的列布局状态应用到打印输出上。
	// 当从本控件的工具栏执行打印任务时，且本属性为真，在本查询显示控件上所进行的列布局调整将引用到应用到打印上。
	// 列布局调整自改变列的顺序，调整列的宽度。
	//@别名 取应用当前列布局()
	/*virtual*/ BOOL get_ToPostColumnLayout(/*[out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_ToPostColumnLayout(&_result); return (VARIANT_TRUE==_result); }
	//@备注 ToPostColumnLayout，指定是否将本控件上的列布局状态应用到打印输出上。
	// 当从本控件的工具栏执行打印任务时，且本属性为真，在本查询显示控件上所进行的列布局调整将引用到应用到打印上。
	// 列布局调整自改变列的顺序，调整列的宽度。
	//@参数 逻辑值 
	//@别名 置应用当前列布局(逻辑值)
	/*virtual*/ HRESULT set_ToPostColumnLayout(/*[in]*/ BOOL pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_ToPostColumnLayout(pVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 CurPageNo，当分页显示报表时，指定对当前页号。
	//@别名 取当前页号()
	/*virtual*/ long get_CurPageNo(/*[out][retVal] long* pVal*/){long _result=0; ((IGRDisplayViewer*)m_ptr.p)->get_CurPageNo(&_result); return _result; }
	//@备注 CurPageNo，当分页显示报表时，指定对当前页号。
	//@参数 整数值 
	//@别名 置当前页号(整数值)
	/*virtual*/ HRESULT set_CurPageNo(/*[in]*/ long pVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->put_CurPageNo(pVal); return _result; }
	//@备注 QuickRefresh，重新生成报表展示而不重新获取报表记录数据。
	//@别名 快速刷新()
	/*virtual*/ HRESULT QuickRefresh(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_QuickRefresh(); return _result; }
	//@备注 Refresh，调用此方法后，报表将重新生成数据展示，报表生成过程中触发的事件将再次触发（拉模式下）。提示：从XML加载的报表数据，刷新后将不显示（即：推模式下应重新推入数据）。
	//@别名 刷新()
	/*virtual*/ HRESULT Refresh(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_Refresh(); return _result; }
	//@备注 Start，开始报表生成并按查询显示的方式展现出来，执行此方法后，报表生成过程中的相关事件将被触发。
	//@别名 启动()
	/*virtual*/ HRESULT Start(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_Start(); return _result; }
	//@备注 Stop，停止报表的查询显示，并停止报表的运行，执行本方法后，查询显示输出所占用的资源将被释放掉。
	//@别名 停止()
	/*virtual*/ HRESULT Stop(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_Stop(); return _result; }
	//@备注 GetControlFromPos，取得指定位置处的部件框对象的接口引用，传入位置参数是指查询显示器的客户区位置。
	//@参数 横向位置 xPos，水平方向的坐标位置。
	//@参数 纵向位置 yPos，垂直方向的坐标位置。
	//@别名 按位置获取部件框(横向位置,纵向位置)
	/*virtual*/ class CIGRControl GetControlFromPos(/*[in]*/ long xPos, /*, [in]*/ long yPos/*, [out][retVal] class CIGRControl** ppControl*/);
	//@备注 GetSectionFromPos，取得指定位置处的报表节对象的接口引用，传入位置参数是指查询显示器的客户区位置。
	//@参数 横向位置 xPos，水平方向的坐标位置。
	//@参数 纵向位置 yPos，垂直方向的坐标位置。
	//@别名 按位置获取报表节(横向位置,纵向位置)
	/*virtual*/ class CIGRSection GetSectionFromPos(/*[in]*/ long xPos, /*, [in]*/ long yPos/*, [out][retVal] class CIGRSection** ppSection*/);
	//@备注 GetContentCellFromPos，取得指定位置处的内容格对象的接口引用，传入位置参数是指查询显示器的客户区位置。
	//@参数 横向位置 xPos，水平方向的坐标位置。
	//@参数 纵向位置 yPos，垂直方向的坐标位置。
	//@别名 按位置获取内容格(横向位置,纵向位置)
	/*virtual*/ class CIGRColumnContentCell GetContentCellFromPos(/*[in]*/ long xPos, /*, [in]*/ long yPos/*, [out][retVal] class CIGRColumnContentCell** ppContentCell*/);
	//@备注 GetTitleCellFromPos，取得指定位置处的标题格对象的接口引用，传入位置参数是指查询显示器的客户区位置。
	//@参数 横向位置 xPos，水平方向的坐标位置。
	//@参数 纵向位置 yPos，垂直方向的坐标位置。
	//@别名 按位置获取标题格(横向位置,纵向位置)
	/*virtual*/ class CIGRColumnTitleCell GetTitleCellFromPos(/*[in]*/ long xPos, /*, [in]*/ long yPos/*, [out][retVal] class CIGRColumnTitleCell** ppTitleCell*/);
	//@备注 PostColumnLayout，在报表查询显示时，通过鼠标拖放可以改变列的显示顺序与宽度，将报表列的当前显示顺序与宽度信息提交到关联报表主对象中去。
	// 例如：如果在查询显示之后进行打印，列在查询显示器已经改变顺序与宽度，要求打印要反映列显示的状态，调用此方法就可以达到此目的。
	//@别名 保存当前列布局()
	/*virtual*/ HRESULT PostColumnLayout(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_PostColumnLayout(); return _result; }
	//@备注 ResizeColumnToFitPage，自动调整所有列的宽度，让整个网格可以在当前页面设置纸张中完整输出。
	// 此方法必须在报表已经在查询显示器中显示后调用，即必须在 Start 与 Refresh 方法之后调用。
	//@别名 自动调整列宽适应页面()
	/*virtual*/ HRESULT ResizeColumnToFitPage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ResizeColumnToFitPage(); return _result; }
	//@备注 ResizeColumnToFit，自动调整所有列的宽度，让所有列可以在网格的显示区域完整的显示出来并刚好完整显示。
	// 此方法必须在报表已经在查询显示器中显示后调用，即必须在 Start 与 Refresh 方法之后调用。
	//@别名 自动调整列宽适应()
	/*virtual*/ HRESULT ResizeColumnToFit(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ResizeColumnToFit(); return _result; }
	//@备注 ResizeColumnToFitText，按内容格中文字内容多少伸展列的显示宽度，以便文字完整显示出来，文字少不缩小。
	// 此方法必须在报表已经在查询显示器中显示后调用，即必须在 Start 与 Refresh 方法之后调用。
	//@别名 自动调整列宽适应文本()
	/*virtual*/ HRESULT ResizeColumnToFitText(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ResizeColumnToFitText(); return _result; }
	//@备注 NextPage，显示下一页。
	//@别名 下一页()
	/*virtual*/ HRESULT NextPage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_NextPage(); return _result; }
	//@备注 PriorPage，显示上一页。
	//@别名 上一页()
	/*virtual*/ HRESULT PriorPage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_PriorPage(); return _result; }
	//@备注 FirstPage，移动至首页。
	//@别名 首页()
	/*virtual*/ HRESULT FirstPage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_FirstPage(); return _result; }
	//@备注 LastPage，移动至最后一页。
	//@别名 尾页()
	/*virtual*/ HRESULT LastPage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_LastPage(); return _result; }
	//@备注 GetColumnVisible，取得指定列在查询显示器中的显示或隐藏状态，返回真假：表示列是否显示，为真表示列在查询显示器中显示。
	//@参数 列名称 指定操作列的名称。
	//@别名 获取列可见性(列名称)
	/*virtual*/ BOOL GetColumnVisible(/*[in]*/ const wchar_t* ColumnName/*, [out][retVal] BOOL* pVisible*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->raw_GetColumnVisible((BSTR)ColumnName, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SetColumnVisible，设置指定列在查询显示器中的显示或隐藏状态。在改变列的显示状态全部完成之后，应调用 “更新列视图(UpdateColumnView)” 方法更新显示。
	//@参数 列名称 指定操作列的名称。
	//@参数 可见性 指定是否显示列。
	//@别名 设置列可见性(列名称,可见性)
	/*virtual*/ HRESULT SetColumnVisible(/*[in]*/ const wchar_t* ColumnName, /*, [in]*/ BOOL Visible){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_SetColumnVisible((BSTR)ColumnName, Visible? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 UpdateColumnView，当改变列的显示状态之后，调用本方法更新列的显示。本方法不会使报表重新生成，只是根据列的显示状态更新明细网格的显示。
	// 在调用 SetColumnVisible(设置列可见性) 方法之后应调用本方法更新显示。
	//@别名 更新列视图()
	/*virtual*/ HRESULT UpdateColumnView(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateColumnView(); return _result; }
	//@备注 UpdateSelCell，更新显示当前选中内容格。
	// 在查询显示报表时，如果改变了当前选中内容格的数据，调用本方法反映最新的数据的显示。
	//@别名 更新选中格()
	/*virtual*/ HRESULT UpdateSelCell(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateSelCell(); return _result; }
	//@备注 UpdateSelRow，更新显示当前选中内容行。在查询显示报表时，如果改变了当前选中内容行的数据，调用本方法反映最新的数据的显示。
	//@别名 更新选中行()
	/*virtual*/ HRESULT UpdateSelRow(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateSelRow(); return _result; }
	//@备注 UpdateControl，更新显示指定的部件框。只有当部件框在报表头与报表尾中时，才能调用本方法进行显示更新。
	// 在查询显示报表时，如果改变了部件框的数据，调用本方法反映最新的数据的显示。
	//@参数 部件框对象 指定要更新显示的部件框对象的接口引用。
	//@别名 更新部件框(部件框对象)
	/*virtual*/ HRESULT UpdateControl(/*[in]*/ class CIGRControl* pControl);
	//@备注 UpdateViewer，更新显示整个查询显示器。
	//@别名 更新显示()
	/*virtual*/ HRESULT UpdateViewer(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateViewer(); return _result; }
	//@备注 LockUpdate，锁定控件的显示更新。
	//@别名 更新锁定()
	/*virtual*/ HRESULT LockUpdate(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_LockUpdate(); return _result; }
	//@备注 解锁控件的显示更新。
	//@别名 解锁更新()
	/*virtual*/ HRESULT UnlockUpdate(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UnlockUpdate(); return _result; }
	//@备注 GetSelRowCellText，获取当前选中行的指定单元格的显示文字。使用本方法可以获取当前行的显示文字，以便进行报表穿透处理。
	// 获取当前选中行的指定单元格的显示文字，列序号参数按列的显示顺序指定，第一个显示列的序号为0。
	//@参数 列索引 获取当前选中行的指定单元格的显示文字，列序号参数按列的显示顺序指定，第一个显示列的序号为 0。
	//@返回 单元格的显示文字
	//@别名 取选中行单元格文本(列索引)
	/*virtual*/ CXText GetSelRowCellText(/*[in]*/ long ColumnIndex/*, [out][retVal] const wchar_t** pText*/){ BSTR _result = 0; CXText _result_text; ((IGRDisplayViewer*)m_ptr.p)->raw_GetSelRowCellText(ColumnIndex, &_result); _result_text = _result; ::SysFreeString(_result); return _result_text; }
	//@备注 Search，执行查找报表文字任务，被匹配的文字将被高亮显示。
	//@参数 文本 指定要查找的文字。
	//@参数 匹配大小写 指定文字匹配时是否区分大小写。
	//@参数 完全匹配 指定是否要求全字匹配。
	//@参数 向上查找 指定是否按向上的方向进行查找。
	//@参数 从当前光标开始 指定是否从当前选中位置进行查找，如果不是：向下查找从首行开始，向上查找从最后一行开始。
	//@参数 显示对话框 指定在执行查找任务之前，是否显示查找对话框。
	//@参数 显示信息框 指定在执行查找任务时，是否弹出搜索完成消息。
	//@别名 查找文字(文本,匹配大小写,完全匹配,向上查找,从当前光标开始,显示对话框,显示信息框)
	/*virtual*/ BOOL Search(/*[in]*/ const wchar_t* Text, /*, [in]*/ BOOL CaseSensitive, /*, [in]*/ BOOL WholeWord, /*, [in]*/ BOOL ToUp, /*, [in]*/ BOOL FromSelection, /*, [in]*/ BOOL ShowDlg, /*, [in]*/ BOOL ShowMsg/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->raw_Search((BSTR)Text, CaseSensitive? VARIANT_TRUE : VARIANT_FALSE, WholeWord? VARIANT_TRUE : VARIANT_FALSE, ToUp? VARIANT_TRUE : VARIANT_FALSE, FromSelection? VARIANT_TRUE : VARIANT_FALSE, ShowDlg? VARIANT_TRUE : VARIANT_FALSE, ShowMsg? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SearchAgain，指示查找是否成功匹配。根据前面的查找条件进行继续查找，被匹配的文字将被高亮显示。
	//@参数 显示信息框 指示是否显示提示消息框。
	//@别名 继续查找(显示信息框)
	/*virtual*/ BOOL SearchAgain(/*[in]*/ BOOL ShowMsg/*, [out][retVal] BOOL* pSuccess*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->raw_SearchAgain(ShowMsg? VARIANT_TRUE : VARIANT_FALSE, &_result); return (VARIANT_TRUE==_result); }
	//@备注 ShowColumnVisibleDlg，打开报表列可见性设置对话框，在此对话框中可以设置列是否显示。
	// 报表中的锁定列不允许设置可见性，必须一直显示。设置时，必须保持至少有一个列是可见的。
	//@别名 显示列可视对话框()
	/*virtual*/ HRESULT ShowColumnVisibleDlg(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ShowColumnVisibleDlg(); return _result; }
	//@备注 UpdateLanguage，在重新设置报表界面语言后，调用本方法更新控件界面显示。
	//@别名 更新语言()
	/*virtual*/ HRESULT UpdateLanguage(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateLanguage(); return _result; }
	//@备注 UpdateUI，更新界面显示，在执行显示器显示相关的设置后，必须调用本方法才能让界面显示生效。
	//@别名 更新UI显示()
	/*virtual*/ HRESULT UpdateUI(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateUI(); return _result; }
	//@备注 AddToolbarControl，功能：增加工具栏某个默认按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 按钮枚举值 按钮类型枚举：
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；40、打印预览；41、打印应用布局；42、显示页面分隔线；
	// 30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；
	// 14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；25、分页方式；20、剪切；
	// 5、导出；6、邮件；7、保存报表文档；19、关闭；21、刷新；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；80、列显示功能
	//@别名 增加工具栏按钮(按钮枚举值)
	/*virtual*/ HRESULT AddToolbarControl(/*[in]*/ GRToolControlType2 ControlType){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_AddToolbarControl(ControlType); return _result; }
	//@备注 AddToolbarCustomButton，功能：增加自定义按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 按钮ID 指定按钮的标识值，有效值从100到200。(取值范围必须在 0 至 1000 之间。)
	//@参数 图标文件 指定按钮的图像文件名，或网络URL。(自定义按钮图像要求为16*16，256色的 bmp 图。)
	//@参数 气泡提示文本 指定按钮的提示文字。
	//@别名 增加工具栏自定义按钮(按钮ID,图标文件,气泡提示文本)
	/*virtual*/ HRESULT AddToolbarCustomButton(/*[in]*/ long BtnID, /*, [in]*/ const wchar_t* BtnFileName, /*, [in]*/ const wchar_t* TooltipText){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_AddToolbarCustomButton(BtnID, (BSTR)BtnFileName, (BSTR)TooltipText); return _result; }
	//@备注 RemoveToolbarControl，功能：从工具栏中删除显示指定的按钮。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@参数 枚举值 按钮类型枚举：
	// 1、分隔；2、打印；3、页面设置；4、打印机设置；40、打印预览；41、打印应用布局；42、显示页面分隔线；
	// 30、查找文本框；31、查找按钮；32、继续查找按钮；33、显示查找对话框钮；
	// 14、上一页；15、下一页；16、首页；17、尾页；18、当前页号；25、分页方式；20、剪切；
	// 5、导出；6、邮件；7、保存报表文档；19、关闭；21、刷新；
	// 50、导出XLS文件；51、导出TXT文件；52、导出HTM文件；53、导出RTF文件；54、导出PDF文件；55、导出CSV文件；56、导出IMG文件；
	// 60、导出XLS文件按钮；61、导出PDF文件按钮；65、邮件发送XLS文件；66、邮件发送TXT文件；67、邮件发送HTM文件；68、邮件发送RTF文件；69、邮件发送PDF文件；70、邮件发送CSV文件；71、邮件发送IMG文件；80、列显示功能
	//@别名 删除工具栏按钮(枚举值)
	/*virtual*/ HRESULT RemoveToolbarControl(/*[in]*/ GRToolControlType2 ControlType){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_RemoveToolbarControl(ControlType); return _result; }
	//@备注 ResetToolbarContent，功能：清除工具栏中所有显示的按钮，以便重新进行加入定义。在对工具栏中的操作界面元素调整完之后，应调用 更新工具栏（UpdateToolbar） 方法更新界面显示。
	//@别名 清空工具栏按钮()
	/*virtual*/ HRESULT ResetToolbarContent(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ResetToolbarContent(); return _result; }
	//@备注 UpdateToolbar，功能：在所有改变按钮定义(增加、删除、重设、恢复等)之后，调用本方法重新显示工具栏，以便新定义生效。
	//@别名 更新工具栏()
	/*virtual*/ HRESULT UpdateToolbar(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_UpdateToolbar(); return _result; }
	//@备注 DoToolbarCommand，执行工具栏命令对应的任务。
	// 调用此方法不会触发工具栏命令被执行事件，即 ToolbarCommandClick 事件。如果没有显示控件本身的工具栏，而是在控件外围添加操作界面，可以调用此方法完成对应的任务。
	// 也可以在 ToolbarCommandClick 事件响应函数中调用本方法，在调用的前后可以执行一些自定义的任务，从而实现对相应工具栏按钮行为的自定义。
	//@参数 枚举值 对应的工具栏按钮或菜单项。
	//@别名 执行工具栏任务(枚举值)
	/*virtual*/ HRESULT DoToolbarCommand(/*[in]*/ GRToolControlType2 ControlType){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_DoToolbarCommand(ControlType); return _result; }
	//@备注 GetOptionValue，获取指定的控制选项是否开启。
	//@参数 选项 查询显示器选项枚举 目前只有：1、显示控制菜单
	//@返回 TRUE(真) 表示获控制选项是开启的，FALSE(假) 表示获控制选项是关闭的。
	//@别名 获取选项值(选项)
	/*virtual*/ BOOL GetOptionValue(/*[in]*/ GRDisplayViewerOption Option/*, [out][retVal] BOOL* pVal*/){VARIANT_BOOL _result=0; ((IGRDisplayViewer*)m_ptr.p)->raw_GetOptionValue(Option, &_result); return (VARIANT_TRUE==_result); }
	//@备注 SetOptionValue，设置开启或关闭指定的控制选项。TRUE(真) 表示获控制选项是开启的，FALSE(假) 表示获控制选项是关闭的。
	//@参数 选项 查询显示器选项枚举 目前只有：1、显示控制菜单
	//@参数 新值 TRUE(真) 表示获控制选项是开启的，FALSE(假) 表示获控制选项是关闭的。
	//@别名 设置选项值(选项,新值)
	/*virtual*/ HRESULT SetOptionValue(/*[in]*/ GRDisplayViewerOption Option, /*, [in]*/ BOOL newVal){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_SetOptionValue(Option, newVal? VARIANT_TRUE : VARIANT_FALSE); return _result; }
	//@备注 ResetToolbar，恢复工具栏按钮默认布局显示，调用本方法后还须调用“更新工具栏(UpdateToolbar)”实时显示更新。
	//@别名 复位工具栏按钮()
	/*virtual*/ HRESULT ResetToolbar(){ HRESULT _result = ((IGRDisplayViewer*)m_ptr.p)->raw_ResetToolbar(); return _result; }

};
//@分组}


/*@声明
//@备注 GRSectionType 指定报表节的具体类型
//@别名 报表节类型枚举
enum GRSectionType{
	//@备注 1 grstPageHeader
	//@别名 页眉
	grstPageHeader = 1,
	//@备注 2 grstReportHeader
	//@别名 报表头
	grstReportHeader = 2,
	//@备注 3 grstReportFooter
	//@别名 报表尾
	grstReportFooter = 3,
	//@备注 4 grstPageFooter
	//@别名 页脚
	grstPageFooter = 4,
	//@备注 5 grstColumnTitle
	//@别名 标题行
	grstColumnTitle = 5,
	//@备注 6 grstColumnContent
	//@别名 内容行
	grstColumnContent = 6,
	//@备注 7 grstGroupHeader
	//@别名 分组头
	grstGroupHeader = 7,
	//@备注 8 grstGroupFooter
	//@别名 分组尾
	grstGroupFooter = 8,
};
//@备注 GRControlType 指定部件框的具体类型
//@别名 部件框类型枚举
enum GRControlType{
	//@备注 1 grctStaticBox
	//@别名 静态文字框
	grctStaticBox = 1,
	//@备注 2 grctShapeBox
	//@别名 图形框
	grctShapeBox = 2,
	//@备注 3 grctSystemVarBox
	//@别名 系统变量框
	grctSystemVarBox = 3,
	//@备注 4 grctFieldBox
	//@别名 字段框
	grctFieldBox = 4,
	//@备注 5 grctSummaryBox
	//@别名 统计框
	grctSummaryBox = 5,
	//@备注 6 grctRichTextBox
	//@别名 RTF文字框
	grctRichTextBox = 6,
	//@别名 图像框
	grctPictureBox = 7,
	//@备注 8 grctMemoBox
	//@别名 综合文字框
	grctMemoBox = 8,
	//@备注 9 grctSubReport
	//@别名 子报表框
	grctSubReport = 9,
	//@备注 10 grctLine
	//@别名 线段框
	grctLine = 10,
	//@备注 11 grctChart
	//@别名 图表框
	grctChart = 11,
	//@备注 12 grctBarcode
	//@别名 条码框
	grctBarcode = 12,
	//@备注 13 grctFreeGrid
	//@别名 自由表格
	grctFreeGrid = 13,
};
//@备注 GRBackStyle 指定部件再显示时用来填充其所占区域背景的方式。
//@别名 背景模式枚举
enum GRBackStyle{
	//@备注 1 grbkNormal 部件框使用背景色填充他占据的矩形区域。
	//@别名 填充
	grbkNormal = 1,
	//@备注 2 grbkTransparent 部件框背景透明,允许任何背景图像或其他部件框透过自身显示。
	//@别名 透明
	grbkTransparent = 2,
};
//@备注 GRPenStyle 画线条时,指定画线笔的类型。
//@别名 画线笔类型枚举
enum GRPenStyle{
	//@备注 0 grpsSolid
	//@别名 实线
	grpsSolid = 0,
	//@备注 1 grpsDash
	//@别名 段虚线
	grpsDash = 1,
	//@备注 2 grpsDot
	//@别名 点虚线
	grpsDot = 2,
	//@备注 3 grpsDashDot
	//@别名 点段虚线
	grpsDashDot = 3,
	//@备注 4 grpsDashDotDot
	//@别名 双点段虚线
	grpsDashDotDot = 4,
};
//@备注 GRBorderStyles (组合值)，指定是否画部件框的上下左右边框线的组合方式。
//@别名 边框模式枚举
enum GRBorderStyles{
	//@备注 1 grbsDrawLeft 部件框或明细网格显示左边边框线。
	//@别名 画左
	grbsDrawLeft = 1,
	//@备注 2 grbsDrawTop 部件框或明细网格显示上边边框线。
	//@别名 画上
	grbsDrawTop = 2,
	//@备注 4 grbsDrawRight 部件框或明细网格显示右边边框线。
	//@别名 画右
	grbsDrawRight = 4,
	//@备注 8 grbsDrawBottom 部件框或明细网格显示下边边框线。
	//@别名 画下
	grbsDrawBottom = 8,
};
//@备注 GRAnchorStyles (组合值)，指定部件框如何锚定到其容器的边缘。
// 如果将部件框锚定到其容器的边缘，当调整该容器的大小时，该部件框与指定边缘间的距离保持不变。
// 例如，如果将控件锚定到其容器的右边缘，则当调整该容器的大小时，该控件的右边缘与容器的右边缘之间的距离保持不变。
// 可以将控件锚定到任何控件边缘的组合上。如果将控件锚定到其容器的相对边缘上（例如，锚定到顶部和底部），当调整容器的大小时，控件大小就会随之改变。
//@别名 锚定方式枚举
enum GRAnchorStyles{
	//@备注 1 grasLeft 该部件框锚定到其容器的左边缘。
	//@别名 左边
	grasLeft = 1,
	//@备注 2 grasTop 该部件框锚定到其容器的上边缘。
	//@别名 上边
	grasTop = 2,
	//@备注 4 grasRight 该部件框锚定到其容器的右边缘。
	//@别名 右边
	grasRight = 4,
	//@备注 8 grasBottom 该部件框锚定到其容器的下边缘。
	//@别名 下边
	grasBottom = 8,
};
//@备注 GRDockStyle 指定部件框停靠的位置和方式。
// 当部件框停靠到其容器的一条边缘时，调整容器的大小时，始终使部件框与那条边缘对齐。
// 如果多个部件框停靠到一条边缘，那么这些部件框将按照它们的 Z 顺序并排出现，部件框在 Z 顺序中的位置越高，距离容器边缘就越远。
// 如果选择了 Left、Right、Top 或 Bottom，则调整部件框的指定边缘和相对边缘的尺寸至包含部件框的相应边缘的尺寸。
// 如果选择了 Fill，则调整部件框的所有四条边以匹配包含部件框的边缘。
//@别名 停靠方式枚举
enum GRDockStyle{
	//@备注 0 grdsNone 该部件框未停靠
	//@别名 无
	grdsNone = 0,
	//@备注 1 grdsLeft 该部件框的左边缘停靠在父容器的左边缘。
	//@别名 左边
	grdsLeft = 1,
	//@备注 2 grdsTop 该部件框的上边缘停靠在父容器的顶端。
	//@别名 上边
	grdsTop = 2,
	//@备注 3 grdsRight 该部件框的右边缘停靠在父容器的右边缘。
	//@别名 右边
	grdsRight = 3,
	//@备注 4 grdsBottom 该部件框的下边缘停靠在父容器的底部。
	//@别名 下边
	grdsBottom = 4,
	//@备注 5 grdsFill 部件框的各个边缘分别停靠在父容器的各个边缘,并且适当调整大小。
	//@别名 充满
	grdsFill = 5,
};
//@备注 GRCenterStyle 指定用来在容器中居中对齐部件框的方式。
//@别名 居中方式枚举
enum GRCenterStyle{
	//@备注 0 grcsNone 部件框在父容器中不居中对齐。
	//@别名 不应用
	grcsNone = 0,
	//@备注 1 grcsHorizontal 部件框始终位于父容器水平方向的正中间。
	//@别名 水平
	grcsHorizontal = 1,
	//@备注 2 grcsVertical 部件框始终位于父容器垂直方向的正中间。
	//@别名 垂直
	grcsVertical = 2,
	//@备注 3 grcsBoth 部件框始终位于父容器水平与垂直方向的正中间。
	//@别名 水平垂直
	grcsBoth = 3,
};
//@备注 GRAlignColumnStyle 指定用来对齐部件框到明细网格列方式。
//@别名 对齐列方式枚举
enum GRAlignColumnStyle{
	//@备注 1 gracsLeft 对齐到列的左端。
	//@别名 左端
	gracsLeft = 1,
	//@备注 2 gracsRight 对齐到列的右端。
	//@别名 右端
	gracsRight = 2,
	//@备注 3 gracsBoth 对齐到列的左右两端,部件框宽度与列保持一致。
	//@别名 左右两端
	gracsBoth = 3,
};
//@备注 GRShiftMode 指定部件框在其上部的部件框自动伸展高度时在垂直方向进行平移的方式。
//@别名 伸展位移枚举
enum GRShiftMode{
	//@备注 1 grsmNever 不进行位移。
	//@别名 不进行位移
	grsmNever = 0,
	//@备注 2 grsmAlways 总是进行位移。
	//@别名 总是进行位移
	grsmAlways = 1,
	//@备注 3 grsmWhenOverLapped 只有与上部部件框在垂直方向有重叠时才进行位移。
	//@别名 重叠时位移
	grsmWhenOverLapped = 2,
};
//@备注 GRPrintType
// 包括两种打印类别：报表表单数据（Form），报表内容数据（Content）。
// 打印生成时，如果指定打印生成方式（PrintGenerateStyle）为只输出报表内容数据（OnlyContent）,则只输出打印类别为报表内容数据的报表元素，其它打印类别为报表表单数据的报表元素将不会输出。
// 在只输出报表内容数据时，报表节的背景色不会填充，明细网格的边框线与行列线也不会输出。在只输出报表内容数据的打印生成方式特别适用于进行票据套打与现存格式报表的套打。
// 打印生成时，如果指定印生成方式（PrintGenerateStyle）为输出报表表单数据（OnlyForm）,生成方式与只输出报表内容数据（OnlyContent）反之对应。在此种方式下，明细网格的记录数据不会应用到，明细行的生成与明细记录不对应，不填充明细记录页可以输出报表表单数据。
// 报表表单数据一般只生成一页，用来制作票据与固定格式报表的印刷模版。
// 打印生成时，如果指定印生成方式（PrintGenerateStyle）为输出全部数据（All）,则所有数据都会输出，这也是我们平时最多用到的方式。
// 可以指定打印类别的报表元素包括部件框，明细网格标题格，明细网格内容格。
//@别名 打印类别枚举
enum GRPrintType{
	//@备注 1 grptForm 表单固定数据,在套打输出内容时不输出。
	//@别名 表单
	grptForm = 1,
	//@备注 2 grptContent 表单内容数据,在套打输出内容时输出。
	//@别名 内容
	grptContent = 2,
};
//@备注 GRDisplayCursor 指定查询显示报表时,可供使用的鼠标光标类型。
//@别名 光标类型枚举
enum GRDisplayCursor{
	//@备注 0 grdcDefault
	//@别名 默认光标
	grdcDefault = 0,
	//@备注 1 grdcArrow
	//@别名 普通箭头光标
	grdcArrow = 1,
	//@备注 2 grdcMagnify
	//@别名 放大镜光标
	grdcMagnify = 2,
	//@备注 3 grdcFinger
	//@别名 手指光标
	grdcFinger = 3,
	//@备注 4 grdcAffirm
	//@别名 肯定光标
	grdcAffirm = 4,
	//@备注 5 grdcNegative
	//@别名 否定光标
	grdcNegative = 5,
};
//@备注 GRTextAlign 指定文字在显示区域的输出对齐方式。
// 使用文字对齐的报表元素包括:各种文字显示部件,非自由格的明细网格标题格与内容格。
//@别名 文字对齐方式枚举
enum GRTextAlign{
	//@备注 17 grtaTopLeft 内容在垂直方向上顶部对齐,在水平方向上左边对齐。
	//@别名 左上
	grtaTopLeft = 17,
	//@备注 18 grtaTopCenter 内容在垂直方向上顶部对齐,在水平方向上居中对齐。
	//@别名 中上
	grtaTopCenter = 18,
	//@备注 20 grtaTopRight 内容在垂直方向上顶部对齐,在水平方向上右边对齐。
	//@别名 右上
	grtaTopRight = 20,
	//@备注 144 grtaTopJustiy 内容在垂直方向上顶部对齐,在水平方向上两端分散对齐。
	//@别名 靠上端两端分散对齐
	grtaTopJustiy = 144,
	//@备注 65 grtaBottomLeft 内容在垂直方向上底边对齐,在水平方向上左边对齐。
	//@别名 左下
	grtaBottomLeft = 65,
	//@备注 66 grtaBottomCenter 内容在垂直方向上底边对齐,在水平方向上居中对齐。
	//@别名 中下
	grtaBottomCenter = 66,
	//@备注 68 grtaBottomRight 内容在垂直方向上底边对齐,在水平方向上右边对齐。
	//@别名 右下
	grtaBottomRight = 68,
	//@备注 192 grtaBottomJustiy 内容在垂直方向上底边对齐,在水平方向上两端分散对齐。
	//@别名 靠下端两端分散对齐
	grtaBottomJustiy = 192,
	//@备注 33 grtaMiddleLeft 内容在垂直方向上中间对齐,在水平方向上左边对齐。
	//@别名 左中
	grtaMiddleLeft = 33,
	//@备注 34 grtaMiddleCenter 内容在垂直方向上中间对齐,在水平方向上居中对齐。
	//@别名 中中
	grtaMiddleCenter = 34,
	//@备注 36 grtaMiddleRight 内容在垂直方向上中间对齐,在水平方向上右边对齐。
	//@别名 右中
	grtaMiddleRight = 36,
	//@备注 160 grtaMiddleJustiy 内容在垂直方向上中间对齐,在水平方向上两端分散对齐。
	//@别名 垂直居中两端分散对齐
	grtaMiddleJustiy = 160,
};
//@备注 GRTextOrientation 指定综合文字框的各种文字行向。
//@别名 文字方向枚举
enum GRTextOrientation{
	//@备注 0 grtoDefault 默认方式,按从左到右,从上到下方式显示文字。
	//@别名 默认
	grtoDefault = 0,
	//@备注 5 grtoU2DL2R0 按从上到下,从左到右方式显示文字,文字不旋转。
	//@别名 从上至下从左至右0
	grtoU2DL2R0 = 5,
	//@备注 22 grtoD2UL2R1 按从下到上,从左到右方式显示文字,文字旋转。
	//@别名 从下至上从左至右1
	grtoD2UL2R1 = 22,
	//@备注 9 grtoU2DR2L0 按从上到下,从右到左方式显示文字,文字不旋转。
	//@别名 从上至下从右至左0
	grtoU2DR2L0 = 9,
	//@备注 25 grtoU2DR2L1 按从上到下,从右到左方式显示文字,文字旋转。
	//@别名 从上至下从右至左1
	grtoU2DR2L1 = 25,
	//@备注 58 grtoInvert倒影方式。
	//@别名 镜像翻转
	grtoInvert = 58,
	//@备注 38 grtoL2RD2U0 按从左到右,从下到上方式显示文字,适合用来进行脊背打印,字体应该选择旋转的,即字体名称前带\'@\'符号。
	//@别名 从左到右从下到上脊背模式
	grtoL2RD2U0 = 38,
	//@备注 54 grtoL2RD2U1 按从左到右,从下到上方式显示文字,文字旋转,适合用来进行脊背打印。
	//@别名 从左到右从下到上且旋转
	grtoL2RD2U1 = 54,
};
//@备注 GRFieldType 指定字段对象的具体类型。
//@别名 字段类型枚举
enum GRFieldType{
	//@备注 1 grftString
	//@别名 字符型
	grftString = 1,
	//@备注 2 grftInteger
	//@别名 整数型
	grftInteger = 2,
	//@备注 3 grftFloat
	//@别名 浮点数
	grftFloat = 3,
	//@备注 4 grftCurrency
	//@别名 货币型
	grftCurrency = 4,
	//@备注 5 grftBoolean
	//@别名 布尔型
	grftBoolean = 5,
	//@备注 6 grftDateTime
	//@别名 日期时间
	grftDateTime = 6,
	//@备注 7 grftBinary
	//@别名 二进制
	grftBinary = 7,
};
//@备注 Lock，说明：除1，2两项外，其它项按从弱到强的顺序锁定控制对象，后一项包括前一项的锁定权限。报表主对象设置为“锁定继承”等同于“不锁定”。
//@别名 锁定类别枚举
enum GRLockType{
	//@备注 0 grltNone，指定对象没有锁定，可以全部权限进行设计。
	//@别名 不锁定
	grltNone = 0,
	//@备注 1 grltInherited，指定对象的锁定控制来自父级对象，与父级对象保持一样的锁定控制。
	//@别名 锁定继承
	grltInherited = 1,
	//@备注 2 grltObject，指定对象自身不能删除，其子对象不能删除与增加。如记录集锁定对象后，现有的字段不能删除，也不能增加新的字段。
	//@别名 锁定对象
	grltObject = 2,
	//@备注 3 grltData，在锁定对象的基础上，再增加对象的数据相关的属性锁定控制，如明细网格不能改变数据连接串与查询SQL，字段框不能修改关联的“数据字段”。
	//@别名 锁定数据
	grltData = 3,
	//@备注 4 grltDataAction，在锁定数据的基础上，再增加对报表生成行为相关的锁定控制，主要体现为不能编辑“行为”与“脚本”类别的属性设置。
	//@别名 锁定数据行为
	grltDataAction = 4,
	//@备注 5 grltAll，对象完全不能编辑修改。
	//@别名 完全锁定
	grltAll = 5,
};
//@备注 GRChartType 表示图表的类型。
//@别名 图表类型枚举
enum GRChartType{
	//@备注 1 grctBarChart 柱图。
	//@别名 柱图
	grctBarChart = 1,
	//@备注 2 grctPieChart 饼图。
	//@别名 饼图
	grctPieChart = 2,
	//@备注 3 grctLineChart 折线图。
	//@别名 折线图
	grctLineChart = 3,
	//@备注 4 grctStackedBarChart 叠加柱图
	//@别名 叠加柱图
	grctStackedBarChart = 4,
	//@备注 5 grctXYScatterChart 散列点图
	//@别名 散列点图
	grctXYScatterChart = 5,
	//@备注 6 grctXYLineChart 散列点连线图
	//@别名 散列点连线图
	grctXYLineChart = 6,
	//@备注 7 grctCurveLineChart 连曲线图
	//@别名 连曲线图
	grctCurveLineChart = 7,
	//@备注 8 grctXYCurveLineChart 散列点连曲线图
	//@别名 散列点连曲线图
	grctXYCurveLineChart = 8,
	//@备注 9 grctBubble 气泡图
	//@别名 气泡图
	grctBubble = 9,
	//@备注 10 grctStackedBar100Chart 百分比柱状图
	//@别名 百分比柱状图
	grctStackedBar100Chart = 10,
	//@备注 11 grctColumnChart 横向柱状图
	//@别名 横向柱状图
	grctColumnChart = 11,
	//@备注 12 grctStackedColumnChart 横向叠加柱状图
	//@别名 横向叠加柱状图
	grctStackedColumnChart = 12,
	//@备注 13 grctStackedColumn100Chart 横向百分比柱状图
	//@别名 横向百分比柱状图
	grctStackedColumn100Chart = 13,
	grctStepBarChart = 4,
};
//@备注 GRPointMarkerStyle 指定数据项显示图案。
//@别名 标记类型枚举
enum GRPointMarkerStyle{
	//@备注 -1 grpmsNone
	//@别名 无图案
	grpmsNone = -1,
	//@备注 0 grpmsSquare
	//@别名 方框
	grpmsSquare = 0,
	//@备注 1 grpmsSquareCheck
	//@别名 框内勾
	grpmsSquareCheck = 1,
	//@备注 2 grpmsSquareCross
	//@别名 框内叉
	grpmsSquareCross = 2,
	//@备注 3 grpmsCircle
	//@别名 圆形
	grpmsCircle = 3,
	//@备注 4 grpmsCirclePoint
	//@别名 圆内点
	grpmsCirclePoint = 4,
	//@备注 5 grpmsCircleCross
	//@别名 圆内叉
	grpmsCircleCross = 5,
	//@备注 6 grpmsDimond
	//@别名 钻石形
	grpmsDimond = 6,
	//@备注 7 grpmsTriangle
	//@别名 三角形
	grpmsTriangle = 7,
	//@备注 8 grpmsCross
	//@别名 交叉
	grpmsCross = 8,
	//@备注 9 grpmsCross4
	//@别名 米字叉
	grpmsCross4 = 9,
	//@备注 10 grpmsStar4
	//@别名 四角星
	grpmsStar4 = 10,
	//@备注 11 grpmsStar5
	//@别名 五角星
	grpmsStar5 = 11,
	//@备注 12 grpmsStar6
	//@别名 六角星
	grpmsStar6 = 12,
	//@备注 13 grpmsStar10
	//@别名 十角星
	grpmsStar10 = 13,
};
//@备注 GRShapeType 指定图形部件框的具体类型。
//@别名 图形类型枚举
enum GRShapeType{
	//@备注 1 grsbtCircle
	//@别名 圆
	grsbtCircle = 1,
	//@备注 2 grsbtEllipse
	//@别名 椭圆
	grsbtEllipse = 2,
	//@备注 3 grsbtRectangle
	//@别名 矩形
	grsbtRectangle = 3,
	//@备注 4 grsbtRoundRect
	//@别名 圆角矩形
	grsbtRoundRect = 4,
	//@备注 5 grsbtRoundSquare
	//@别名 圆角正方形
	grsbtRoundSquare = 5,
	//@备注 6 grsbtSquare
	//@别名 正方形
	grsbtSquare = 6,
	//@备注 7 grsbtLine
	//@别名 直线
	grsbtLine = 7,
};
//@备注 虽隐藏，仍可用
//@别名 线条类型枚举
enum GRLineType{                                              
	//@备注  图形框_类型枚举_线_斜线\\
	grltTopLeftToBottomRight = 0,      //@别名 左上至右下       
	//@备注  图形框_类型枚举_线_斜线/"
	grltBottomLeftToTopRight = 1,      //@别名 左下至右上       
	//@备注  图形框_类型枚举_线_上横线
	grltTopLeftToTopRight = 2,         //@别名 左上至右上       
	//@备注  图形框_类型枚举_线_中横线
	grltMiddleLeftToMiddleRight = 3,   //@别名 左中至右中       
	//@备注  图形框_类型枚举_线_下横线
	grltBottomLeftToBottomRight = 4,   //@别名 左下至右下      
	//@备注  图形框_类型枚举_线_左竖线
	grltTopLeftToBottomLeft = 5,       //@别名 左上至左下       
	//@备注  图形框_类型枚举_线_中竖线
	grltTopCenterToBottomCenter = 6,   //@别名 上中至下中       
	//@备注  图形框_类型枚举_线_右竖线
	grltTopRightToBottomRight = 7,     //@别名 右上至右下
};
//@备注 GRSystemVarType 指定系统变量部件框应用的系统变量类型。
// grsvPageCount(页数)，grsvPageNumber(页号)，grsvGroupPageCount(分组页数)，grsvGroupPageNo(分组页号)等打印页面相关的系统变量只在产生打印页面数据时有效，在查询显示报表时，应避免对这些系统变量的使用。
// 关于分组相关的系统变量必须通过序号指定对应的分组。
// 如果是在表达式的系统变量函数中，或接口调用 SystemVarValue2 方法中，通过参数提供分组序号。如果是系统变量框，通过“分组序号”属性指定分组。
// 分组相关的系统变量如下：
// grsvGroupNo(分组序号)
// grsvGroupCount(分组数)
// grsvGroupRowNo(分组项行号)
// grsvGroupRowCount(分组项行数)
// grsvGroupPageNo(分组项页号)
// grsvGroupPageCount(分组项页数)
// 关于分组页号与页数的更进一步说明：
// 1、为了产生分组页号与页数信息，必须设置对应分组头与分组尾的“可见性”属性为“是”，且其“高度”属性值大于0。
// 2、如果实际不需要显示分组头与分组尾，可以在其“格式化脚本”上写脚本代码“Sender.Visible = false;”，这样可以在运行时将分组头与分组尾隐藏不显示。
// 3、分组页号页数在查询显示报表时不会得到正确的值，所以不应在查询显示报表时显示分组页号页数。
//@别名 系统变量枚举
enum GRSystemVarType{
	//@备注 1 grsvCurrentDateTime 计算机的当前日期时间。
	//@别名 当前日期时间
	grsvCurrentDateTime = 1,
	//@备注 2 grsvPageCount 总页数。
	//@别名 总页数
	grsvPageCount = 2,
	//@备注 3 grsvPageNumber 当前页号。
	//@别名 当前页号
	grsvPageNumber = 3,
	//@备注 4 grsvRecordNo 明细记录的当前记录号,从1开始计数。
	//@别名 记录号
	grsvRecordNo = 4,
	//@备注 8 grsvRowNo 明细网格的当前行号,从1开始计数。
	//@别名 行号
	grsvRowNo = 8,
	//@备注 19 grsvRecordCount 明细记录的记录数。
	//@别名 记录数
	grsvRecordCount = 19,
	
	grsvGroupNo = 20, //@别名 分组序号
	grsvGroupCount = 21, //@别名  分组数
	grsvGroupRowNo = 22, //@别名  分组项行号
	grsvGroupRowCount = 23, //@别名  分组项行数
	grsvGroupPageNo = 24, //@别名   分组项页号  
	grsvGroupPageCount = 25, //@别名  分组项页数
	grsvGroupOrderNo = 9,
	grsvGroup1RowNo = 5,
	grsvGroup2RowNo = 6,
	grsvGroup3RowNo = 7,
	grsvGroup1PageNumber = 10,
	grsvGroup2PageNumber = 11,
	grsvGroup3PageNumber = 12,
	grsvGroup1PageCount = 13,
	grsvGroup2PageCount = 14,
	grsvGroup3PageCount = 15,
	grsvGroup1OrderNo = 16,
	grsvGroup2OrderNo = 17,
	grsvGroup3OrderNo = 18,
};
//@备注 GRSummaryFun 指定统计部件框应用的统计函数。
//@别名 统计函数枚举
enum GRSummaryFun{
	//@备注 1 grsfSum 统计某个字段的合计值。
	//@别名 合计
	grsfSum = 1,
	//@备注 2 grsfAvg 统计某个字段的平均值。
	//@别名 平均
	grsfAvg = 2,
	//@备注 3 grsfCount 统计明细记录的个数。
	//@别名 数目
	grsfCount = 3,
	//@备注 4 grsfMin 找出某个字段的最小值。
	//@别名 最小值
	grsfMin = 4,
	//@备注 5 grsfMax 找出某个字段的最大值。
	//@别名 最大值
	grsfMax = 5,
	//@备注 6 grsfVar
	//@别名 方差
	grsfVar = 6,
	//@备注 7 grsfVarP
	//@别名 总体方差
	grsfVarP = 7,
	//@备注 8 grsfStdDev
	//@别名 标准偏差
	grsfStdDev = 8,
	//@备注 9 grsfStdDevP
	//@别名 总体标准偏差
	grsfStdDevP = 9,
	//@备注 10 grsfAveDev
	//@别名 平均偏差
	grsfAveDev = 10,
	//@备注 11 grsfDevSq
	//@别名 偏差平方和
	grsfDevSq = 11,
	//@备注 12 grsfCountBlank
	//@别名 空值个数
	grsfCountBlank = 12,
	//@备注 13 grsfCountA
	//@别名 非空值个数
	grsfCountA = 13,
	//@备注 14 grsfDistinct
	//@别名 非重复值个数
	grsfDistinct = 14,
	//@备注 15 grsfAvgA
	//@别名 非空值平均
	grsfAvgA = 15,
	//@备注 16 grsfMinN
	//@别名 第N个最小值
	grsfMinN = 16,
	//@备注 17 grsfMaxN
	//@别名 第N个最大值
	grsfMaxN = 17,
	//@备注 18 grsfStrMin
	//@别名 字符最小值
	grsfStrMin = 18,
	//@备注 19 grsfStrMax
	//@别名 字符最大值
	grsfStrMax = 19,
	//@备注 20 grsfVarA
	//@别名 非空方差
	grsfVarA = 20,
	//@备注 21 grsfVarPA
	//@别名 非空总体方差
	grsfVarPA = 21,
	//@备注 22 grsfStdDevA
	//@别名 非空标准偏差
	grsfStdDevA = 22,
	//@备注 23 grsfStdDevPA
	//@别名 非空总体标准偏差
	grsfStdDevPA = 23,
	//@备注 24 grsfAveDevA
	//@别名 非空平均偏差
	grsfAveDevA = 24,
	//@备注 25 grsfDevSqA
	//@别名 非空偏差平方和
	grsfDevSqA = 25,
	//@备注 26 grsfSumAbs
	//@别名 绝对值合计
	grsfSumAbs = 26,
	//@备注 27 grsfSumAcc 全程累计，从开始到当前行的合计。
	//@别名 累计
	grsfSumAcc = 27,
	//@备注 28 grsfGroupSumAcc 组累计，在上级组内累计，开始一个新分组，重新累计。
	//@别名 组累计
	grsfGroupSumAcc = 28,
	//@备注 29 grsfJoin，拼接，将数据显示文字拼接在一起。如果是统计框，字段之间的分隔符号由“格式”属性值确定，如果要换行，加入\"\\n\"字符。20210315-6.810版本增加
	//@别名 串接
	grsfJoin = 29,
	//@备注 30 grsfJoinUnique，非重复拼接，重复项只拼接一次。20210315-6.810版本增加
	//@别名 非重复串接
	grsfJoinUnique = 30,
};
//@备注 GRPictureAlignment 指定图像框中图像显示的对齐方式。
//@别名 图像显示方式枚举
enum GRPictureAlignment{
	//@备注 1 grpaTopLeft 图像的左上角紧靠图像框的左上角显示。
	//@别名 左上
	grpaTopLeft = 1,
	//@备注 2 grpaTopRight 图像的右上角紧靠图像框的右上角显示。
	//@别名 右上
	grpaTopRight = 2,
	//@备注 3 grpaCenter 图像居中显示在图像框中。
	//@别名 居中
	grpaCenter = 3,
	//@备注 4 grpaBottomLeft 图像的左下角紧靠图像框的左下角显示。
	//@别名 左下
	grpaBottomLeft = 4,
	//@备注 5 grpaBottomRight 图像的右下角紧靠图像框的右下角显示。
	//@别名 右下
	grpaBottomRight = 5,
};
//@备注 GRPictureSizeMode 指定图像框中图像的显示缩放方式。
//@别名 图像缩放方式枚举
enum GRPictureSizeMode{
	//@备注 1 grpsmClip 图像不进行缩放,按原始尺寸显示。
	//@别名 修剪
	grpsmClip = 1,
	//@备注 2 grpsmStretch 图像伸缩到完全显示到图像框中。
	//@别名 铺满
	grpsmStretch = 2,
	//@备注 3 grpsmZoom 根据图像框的大小图像保持宽高比例伸缩至某一方向完全铺满。
	//@别名 缩放
	grpsmZoom = 3,
	//@备注 4 grpsmEnsureFullView 如果图像不能在图像框中完全显示,根据图像框的大小图像保持宽高比例伸缩至某一方向完全铺满。反之图像保持原始尺寸显示。
	//@别名 完整显示
	grpsmEnsureFullView = 4,
	//@备注 5 grpsmTile 平铺多次显示图像,铺满整个显示区域。
	//@别名 平铺
	grpsmTile = 5,
};
//@备注 GRPictureTransparentMode 指定图像透明显示的方式
//@别名 图像透明模式枚举
enum GRPictureTransparentMode{
	//@备注 0 grptmNone
	//@别名 不透明
	grptmNone = 0,
	//@备注 1 grptmOverlying
	//@别名 叠加透明
	grptmOverlying = 1,
	//@备注 2 grptmBackground
	//@别名 背景透明
	grptmBackground = 2,
};
//@备注 GRPictureRotateMode 指定图像显示时的旋转方式。
//@别名 图像旋转模式枚举
enum GRPictureRotateMode{
	//@备注 0 grprmNone
	//@别名 不旋转
	grprmNone = 0,
	//@备注 1 grprmLeft
	//@别名 左旋
	grprmLeft = 1,
	//@备注 2 grprmRight
	//@别名 右旋
	grprmRight = 2,
	//@备注 3 grprmFlip
	//@别名 颠倒
	grprmFlip = 3,
	//@备注 4 grprmMirror
	//@别名 镜像
	grprmMirror = 4,
};
//@备注 GRPictureType 指定图像类型。
//@别名 图像类型枚举
enum GRPictureType{
	//@备注 0 grptUnknown
	//@别名 未知类型
	grptUnknown = 0,
	//@备注 1 grptBMP
	//@别名 BMP格式
	grptBMP = 1,
	//@备注 2 grptGIF
	//@别名 GIF格式
	grptGIF = 2,
	//@备注 3 grptJPEG
	//@别名 JPEG格式
	grptJPEG = 3,
	//@备注 4 grptPNG
	//@别名 PNG格式
	grptPNG = 4,
	//@备注 5 grptICON
	//@别名 ICON格式
	grptICON = 5,
	//@备注 6 grptTIFF
	//@别名 TIFF格式
	grptTIFF = 6,
	//@备注 7 grptWMF
	//@别名 WMF格式
	grptWMF = 10,
	grptEMF = -1,
};
//@备注 GRSystemImage 指定报表引擎中的系统内建图像。
// Grid++Report 在报表引擎中定义了一些系统内建图像。图片框可以将其图像序号指定为某个枚举项的值来关联某个系统图像,从而在图像框中显示系统图像。
// 另也可以调用 IGRPictureBox 接口的 AttachSystemImage 方法来关联系统图像。
//@别名 系统图像枚举
enum GRSystemImage{
	//@备注 -1 grsiChecked 值为-1,选中标志。
	//@别名 选中
	grsiChecked = -1,
	//@备注 -2 grsiUnchecked 值为-2,非选中标志。
	//@别名 未选中
	grsiUnchecked = -2,
	//@备注 -3 grsi3DChecked 值为-3,3D形式的选中标志。
	//@别名 选中3D
	grsi3DChecked = -3,
	//@备注 -4 grsi3DUnchecked 值为-4,3D形式的非选中标志。
	//@别名 未选中3D
	grsi3DUnchecked = -4,
	//@备注 -5 grsiAffirm 值为-5,肯定标志。
	//@别名 肯定标志
	grsiAffirm = -5,
	//@备注 -6 grsiNegative 值为-6,否定标志。
	//@别名 否定标志
	grsiNegative = -6,
	//@备注 -7 grsiArrowDown 值为-7,朝下箭头标志。
	//@别名 向下箭头
	grsiArrowDown = -7,
	//@备注 -8 grsiArrowUp 值为-8,朝上箭头标志。
	//@别名 向上箭头
	grsiArrowUp = -8,
	//@备注 -9 grsiRadio3DChecked 值为-9,3D形式的无线按钮(Radio)选中标志。
	//@别名 选中3D单选框
	grsiRadio3DChecked = -9,
	//@备注 -10 grsiRadio3DUnchecked 值为-10,3D形式的无线按钮(Radio)非选中标志。
	//@别名 未选中3D单选框
	grsiRadio3DUnchecked = -10,
};
//@备注 GRParameterDataType  指示参数对象值的具体数据类型。
//@别名 参数类型枚举
enum GRParameterDataType{
	//@备注 1 grptString 字符串类型,可以为任意长度。
	//@别名 字符型
	grptString = 1,
	//@备注 2 grptInteger 整数类型,可以设定格式化串。
	//@别名 整数型
	grptInteger = 2,
	//@备注 3 grptFloat 浮点数类型,可以设定格式化串。
	//@别名 浮点数
	grptFloat = 3,
	//@备注 5 grptBoolean 逻辑型或布尔类型,可以真值与假值的显示文字。
	//@别名 布尔型
	grptBoolean = 5,
	//@备注 6 grptDateTime 日期时间类型,可以设定格式化串。
	//@别名 日期时间
	grptDateTime = 6,
};
//@备注 GRNewPageStyle 在打印生成报表节时,指定是否强制产生新页的方式。
//@别名 换新页方式枚举
enum GRNewPageStyle{
	//@备注 1 grnpsNone 报表节不强制产生新页。
	//@别名 不应用
	grnpsNone = 1,
	//@备注 2 grnpsBefore 报表节在打印输出之前要求产生新页,保证本节在新页中输出。
	//@别名 节前
	grnpsBefore = 2,
	//@备注 3 grnpsAfter 报表节在打印输出之后要求产生新页,保证本节之后的后续节在新页中输出。
	//@别名 节后
	grnpsAfter = 3,
	//@备注 4 grnpsBeforeAfter 报表节在打印输出之前与之后要求产生新页。
	//@别名 节前与节后
	grnpsBeforeAfter = 4,
};
//@备注 GRPrintRangeType 指定打印时选定页范围的类型。
//@别名 打印页范围类型枚举
enum GRPrintRangeType{
	//@备注 1 grprtAllPages 选定全部页。
	//@别名 全部页
	grprtAllPages = 1,
	//@备注 2 grprtCurrentPage 定当前页,只有在从打印御览状态中执行打印任务时才有效。
	//@别名 当前页
	grprtCurrentPage = 2,
	//@备注 3 grprtSelectionPages 指定的页范围。
	//@别名 选定页
	grprtSelectionPages = 3,
};
//@备注 GRPrintPageType 指定打印时输出页的类型。
//@别名 打印页面类型枚举
enum GRPrintPageType{
	//@备注 1 grpptAllSelectionPages 输出选定页范围内的所有页。
	//@别名 全部选择页
	grpptAllSelectionPages = 1,
	//@备注 2 grpptOddSelectionPages 输出选定页范围内的奇数页。
	//@别名 奇数选择页
	grpptOddSelectionPages = 2,
	//@备注 3 grpptEvenSelectionPages 输出选定页范围内的偶数页。
	//@别名 偶数选择页
	grpptEvenSelectionPages = 3,
};
//@备注 GRDuplexKind 表示报表对双面打印的应用方式。
//@别名 双面打印方式枚举
enum GRDuplexKind{
	//@备注 0 grdkDefault 打印机默认的双面打印设置。
	//@别名 默认
	grdkDefault = 0,
	//@备注 1 grdkSimplex 单面打印。
	//@别名 单面打印
	grdkSimplex = 1,
	//@备注 3 grdkHorizontal 双面水平打印。
	//@别名 双面水平打印
	grdkHorizontal = 3,
	//@备注 2 grdkVertical 双面垂直打印。
	//@别名 双面垂直打印
	grdkVertical = 2,
};
//@备注 GRPaperOrientation 指定生成打印页面时在纸张中的输出方向。
//@别名 纸张方向枚举
enum GRPaperOrientation{
	//@备注 0 grpoDefault 应用打印机当前设置的纸张输出方向
	//@别名 默认
	grpoDefault = 0,
	//@备注 1 grpoPortrait 纸张输出方向为纵向。
	//@别名 纵向
	grpoPortrait = 1,
	//@备注 2 grpoLandscape 纸张输出方向为横向。
	//@别名 横向
	grpoLandscape = 2,
};
//@备注 参考Windows SDK中DEVMODE的成员dmPaperSize的说明。
//@别名 标准纸张类型枚举
enum GRPaperKind{                                         
	//@备注 默认纸张设置
	grpkDefault = 255,       //@别名 Default
	//@备注 其中256代表自定义纸张，但定义为自定义纸张时，可以设置纸张宽度与长度属性指定打印纸张的大小。
	grpkCustom = 256,        //@别名 Custom
	//@备注 Letter 1
	grpkLetter = 1,          //@别名 Letter
	//@备注 LetterSmall 2
	grpkLegal = 5,           //@别名 Legal
	//@备注 Tabloid 3
	grpk10X14 = 16,          //@别名 size10X14
	//@备注 Ledger 4
	grpk11X17 = 17,          //@别名 size11X17
	//@备注 Legal 5
	grpk12X11 = 90,          //@别名 size12X11
	//@备注 Statement 6
	grpkA3 = 8,              //@别名 A3
	//@备注 Executive 7
	grpkA4 = 9,              //@别名 A4
	//@备注 A3 8
	grpkA4Small = 10,        //@别名 A4Small
	//@备注 A4 9
	grpkA5 = 11,             //@别名 A5
	//@备注 A4Small 10
	grpkA6 = 70,             //@别名 A6
	//@备注 A5 11
	grpkB4 = 12,             //@别名 B4
	//@备注 A6 70
	grpkB5 = 13,             //@别名 B5
	//@备注 B4 12
	grpkB6 = 88,             //@别名 B6
	//@备注 B5 13
	grpkCSheet = 24,         //@别名 CSheet
	//@备注 B6 88
	grpkDSheet = 25,         //@别名 DSheet
	//@备注 Folio 14
	grpkEnvelope9 = 19,      //@别名 Envelope9
	//@备注 Quarto 15
	grpkEnvelope10 = 20,     //@别名 Envelope10
	//@备注 10X14 16
	grpkEnvelope11 = 21,     //@别名 Envelope11
	//@备注 11X17 17
	grpkEnvelope12 = 22,     //@别名 Envelope12
	//@备注 12X11 90
	grpkEnvelope14 = 23,     //@别名 Envelope14
	//@备注 Note 18
	grpkEnvelopeC5 = 28,     //@别名 EnvelopeC5
	//@备注 CSheet 24
	grpkEnvelopeC3 = 29,     //@别名 EnvelopeC3
	//@备注 DSheet 25
	grpkEnvelopeC4 = 30,     //@别名 EnvelopeC4
	//@备注 ESheet 26
	grpkEnvelopeC6 = 31,     //@别名 EnvelopeC6
	//@备注 Envelope9 19
	grpkEnvelopeC65 = 32,    //@别名 EnvelopeC65
	//@备注 Envelope10 20
	grpkEnvelopeB4 = 33,     //@别名 EnvelopeB4
	//@备注 Envelope11 21
	grpkEnvelopeB5 = 34,     //@别名 EnvelopeB5
	//@备注 Envelope12 22
	grpkEnvelopeB6 = 35,     //@别名 EnvelopeB6
	//@备注 Envelope14 23
	grpkEnvelopeDL = 27,     //@别名 EnvelopeDL
	//@备注 EnvelopeC5 28
	grpkEnvelopeItaly = 36,  //@别名 EnvelopeItaly
	//@备注 EnvelopeC3 29
	grpkEnvelopeMonarch = 37,//@别名 EnvelopeMonarch
	//@备注 EnvelopeC4 30
	grpkEnvelopePersonal = 38//@别名 EnvelopePersonal
	//@备注 EnvelopeC6 31
	grpkESheet = 26,         //@别名 ESheet
	//@备注 EnvelopeC65 32
	grpkExecutive = 7,       //@别名 Executive
	//@备注 EnvelopeB4 33
	grpkFanfold = 39,        //@别名 Fanfold
	//@备注 EnvelopeB5 34
	grpkFolio = 14,          //@别名 Folio
	//@备注 EnvelopeB6 35
	grpkLedger = 4,          //@别名 Ledger
	//@备注 EnvelopeDL 27
	grpkLetterSmall = 2,     //@别名 LetterSmall
	//@备注 EnvelopeItaly 36
	grpkNote = 18,           //@别名 Note
	//@备注 EnvelopeMonarch 37
	grpkP16K = 93,           //@别名 P16K
	//@备注 EnvelopePersonal 38
	grpkP32K = 94,           //@别名 P32K
	//@备注 Fanfold 39
	grpkQuarto = 15,         //@别名 Quarto
	//@备注 P16K 93
	grpkStatement = 6,       //@别名 Statement
	//@备注 P32K 94
	grpkTabloid = 3,         //@别名 Tabloid
};

//@备注 GRPaperSourceKind 指定打印机的各种纸张来源方式。
//@别名 纸张来源枚举
enum GRPaperSourceKind{
	//@备注 grpskDefault 打印机默认。
	//@别名 默认
	grpskDefault = 0,
	//@备注 grpskAutomaticFeed 自动送入的纸张。
	//@别名 自动选择
	grpskAutomaticFeed = 7,
	//@备注 grpskCassette 卡式纸盒。
	//@别名 磁带纸盒
	grpskCassette = 14,
	//@备注 grpskCustom 打印机特定的纸张来源。
	//@别名 自定义纸盒
	grpskCustom = 256,
	//@备注 grpskEnvelope 信封。
	//@别名 信封纸盒
	grpskEnvelope = 5,
	//@备注 grpskFormSource 打印机的默认送纸盒。
	//@别名 格式源纸盒
	grpskFormSource = 15,
	//@备注 grpskLargeCapacity 打印机的大容量纸盒。
	//@别名 大容量纸盒
	grpskLargeCapacity = 11,
	//@备注 grpskLargeFormat 大纸。
	//@别名 大号纸盒
	grpskLargeFormat = 10,
	//@备注 grpskLower 打印机的下层纸盒。
	//@别名 下部纸盒
	grpskLower = 2,
	//@备注 grpskManual 以手动方式送入的纸张。
	//@别名 手动送纸器
	grpskManual = 4,
	//@备注 grpskManualFeed 以手动方式送入的信封。
	//@别名 手动信封送纸器
	grpskManualFeed = 6,
	//@备注 grpskMiddle 打印机的中层纸盒。
	//@别名 中部纸盒
	grpskMiddle = 3,
	//@备注 grpskSmallFormat 小纸。
	//@别名 小号纸盒
	grpskSmallFormat = 9,
	//@备注 grpskTractorFeed 牵引器送纸。
	//@别名 跟踪送纸器
	grpskTractorFeed = 8,
	//@备注 grpskUpper 打印机的上层纸盒(如果打印机只有一个纸盒,那么这个纸盒就是上层纸盒)。
	//@别名 上部纸盒
	grpskUpper = 1,
};
//@备注 GRSheetPages 指定打印输出时每页输出版数
//@别名 每页版数枚举
enum GRSheetPages{
	//@备注 1 grsp1Pages 指定版面数为1,也就是最常规的单版面输出方式
	//@别名 每页排1版
	grsp1Pages = 1,
	//@备注 2 grsp2Pages 指定版面数为2
	//@别名 每页排2版
	grsp2Pages = 2,
	//@备注 3 grsp4Pages 指定版面数为4
	//@别名 每页排4版
	grsp4Pages = 4,
	//@备注 4 grsp6Pages 指定版面数为6
	//@别名 每页排6版
	grsp6Pages = 6,
	//@备注 5 grsp8Pages 指定版面数为8
	//@别名 每页排8版
	grsp8Pages = 8,
	//@备注 6 grsp16Pages 指定版面数为16
	//@别名 每页排16版
	grsp16Pages = 16,
};
//@备注 GRCollateKind 逐份打印类型
//@别名 逐份打印方式枚举
enum GRCollateKind{
	//@备注 0 Default 由打印机确定是否逐份打印
	//@别名 默认
	grckDefault = 0,
	//@备注 1 Collate
	//@别名 逐份
	grckCollate = 1,
	//@备注 2 NotCollate
	//@别名 不逐份
	grckNotCollate = 2,
};
//@备注 GRDrawRotation 目前仅用于打印输出时指定旋转角度。
//@别名 打印旋转枚举
enum GRDrawRotation{
	//@备注 0 grprRotate0
	//@别名 不旋转
	grprRotate0 = 0,
	//@备注 1 grprRotate90
	//@别名 旋转90度
	grprRotate90 = 1,
	//@备注 2 grprRotate180
	//@别名 旋转180度
	grprRotate180 = 2,
	//@备注 3 grprRotate270
	//@别名 旋转270度
	grprRotate270 = 3,
};
//@备注 GRStorageFormat 表示报表模板数据的存储格式。
//@别名 存储格式枚举
enum GRStorageFormat{
	//@备注 1 grsfText 文本格式。
	//@别名 文本
	grsfText = 1,
	//@备注 2 grsfBinary 二进制格式。
	//@别名 二进制
	grsfBinary = 2,
	//@备注 3 grsfBinBase64 Base64编码格式,Base64编码是用可见的ASCII字符表示二进制数据。
	//@别名 Base64编码
	grsfBinBase64 = 3,
};
//@备注 GRTextEncodeMode 指定文字的编码类型
//@别名 文本编码枚举
enum GRTextEncodeMode{
	//@备注 1 grtemAnsi ANSI编码
	//@别名 Ansi码
	grtemAnsi = 1,
	//@备注 2 grtemUTF8 UTF-8编码,数据最前面有2个字节的标识数据。
	//@别名 UTF8码
	grtemUTF8 = 2,
	//@备注 3 grtemUnicode Unicode编码
	//@别名 Unicode码
	grtemUnicode = 3,
	//@备注 4 grtemUTF8Pure UTF-8编码,数据最前面没有标识
	//@别名 UTF8Pure码
	grtemUTF8Pure = 4,
	//@备注 5 grtemUTF8WithHead 此项同grtemUTF8,特别注意:枚举值也应为 2
	//@别名 UTF8WithHead码
	grtemUTF8WithHead = 2,
};
//@备注 GRUnit 指定表示报表元素大小与位置的计量单位。
//@别名 计量单位枚举
enum GRUnit{
	//@备注 1 grmuCm 以厘米为单位表示报表部件的尺寸与位置。
	//@别名 厘米
	grmuCm = 1,
	//@备注 2 grmuInch 以英寸为单位表示报表部件的尺寸与位置。
	//@别名 英寸
	grmuInch = 2,
};
//@备注 GRScriptType 表示在报表中内置的脚本语言类型。
//@别名 脚本语言枚举
enum GRScriptType{
	//@备注 1 grstJScript JScript 脚本语言。
	//@别名 JScript格式
	grstJScript = 1,
	//@备注 2 grstVBScript VBScript 脚本语言。
	//@别名 VBScript格式
	grstVBScript = 2,
};
//@备注 GRReportDisplayMode 指定报表的输出显示模式。
//@别名 报表显示模式枚举
enum GRReportDisplayMode{
	//@备注 1 grrdmScreenView，正在查询显示器中报表处于自画过程中。
	//@别名 查询显示
	grrdmScreenView = 1,
	//@备注 2 grrdmPrintGenerate，报表处于打印显示器页面生成过程中。
	//@别名 预览显示
	grrdmPrintGenerate = 2,
	//@备注 3 grrdmIdle，报表不处于任何生成显示过程中。
	//@别名 空闲
	grrdmIdle = 3,
};
//@备注 GRRepeatStyle 指定明细网格标题的重复输出方式。
// 如果为不重复输出方式（None），则只在明细网格打印生成的开始时输出一次标题。如果为每页重复方式（OnPage)或每页列重复方式（OnPageColumn）,则在明细网格打印生成的开始时与产生新页或新页列时输出标题。
// 如果为在分组头上重复方式（OnGroupHeader），则在明细网格打印生成的开始时不输出报表头，而是在每个分组头输出后输出标题。
//@别名 重复方式枚举
enum GRRepeatStyle{
	//@备注 1 grrsNone 明细网格标题不重复输出。
	//@别名 不应用
	grrsNone = 1,
	//@备注 2 grrsOnPage 明细网格标题在每页重复输出。
	//@别名 新页
	grrsOnPage = 2,
	//@备注 4 grrsOnPageColumn 明细网格标题在每个页栏重复输出。
	//@别名 新页栏
	grrsOnPageColumn = 4,
	//@备注 8 grrsOnGroupHeader 明细网格标题在最内层的分组头之后重复输出。
	//@别名 新分组头
	grrsOnGroupHeader = 8,
	//@备注 10 grrsOnGroupHeaderPage 明细网格标题在每页与最内层的分组头之后重复输出。
	//@别名 新分组头新页
	grrsOnGroupHeaderPage = 10,
};
//@备注 GRPrintGenerateStyle 指示打印页面的生成方式。
// 打印生成时，如果指定打印生成方式为只输出报表内容数据（OnlyContent）,则只输出打印类别为报表内容数据的报表元素，其它打印类别为报表表单数据的报表元素将不会输出。
// 在只输出报表内容数据时，报表节的背景色不会填充，明细网格的边框线与行列线也不会输出。在只输出报表内容数据的打印生成方式特别适用于进行票据套打与现存格式报表的套打。
// 打印生成时，如果指定印生成方式为输出报表表单数据（OnlyForm）,生成方式与只输出报表内容数据（OnlyContent）反之对应。
// 在此种方式下，明细网格的记录数据不会被应用，明细行的生成与明细记录不对应，不填充明细记录页也可以输出报表表单数据。报表表单数据一般只生成一页。此种模式一般用来制作票据与固定格式报表的印刷模版。
// 打印生成时，如果指定印生成方式（PrintGenerateStyle）为输出全部数据（All）,则所有数据都会输出，这也是我们平时最多用到的方式。
// 使用打印页面的生成方式的地方有： 在IGridppReport接口中执行PrintEx与PrintViewEx方法中可以指定打印页面的生成方式，另可以设定打印预览查看器的打印页面的生成方式（GenerateStyle）属性。
//@别名 打印生成方式枚举
enum GRPrintGenerateStyle{
	//@备注 1 grpgsOnlyForm 只生成报表表单数据。
	//@别名 仅表单
	grpgsOnlyForm = 1,
	//@备注 2 grpgsOnlyContent 只生成报表内容数据。
	//@别名 仅内容
	grpgsOnlyContent = 2,
	//@备注 3 grpgsAll 生成报表所有数据。
	//@别名 全部
	grpgsAll = 3,
	//@备注 4 grpgsPreviewAll 预览报表全部内容,但只打印出内容数据。
	//@别名 预览全部
	grpgsPreviewAll = 4,
};
//@备注 GRExportType 指定数据导出的类型。
//@别名 导出类型枚举
enum GRExportType{
	//@备注 1 gretXLS 导出Excel文件。
	//@别名 导出XLS
	gretXLS = 1,
	//@备注 2 gretTXT 导出文本文件。
	//@别名 导出TXT
	gretTXT = 2,
	//@备注 3 gretHTM 导出Html超文本文件。
	//@别名 导出HTM
	gretHTM = 3,
	//@备注 4 gretRTF 导出RTF文件。
	//@别名 导出RTF
	gretRTF = 4,
	//@备注 5 gretPDF 导出PDF格式文件。
	//@别名 导出PDF
	gretPDF = 5,
	//@备注 6 gretCSV 导出CSV格式文件。
	//@别名 导出CSV
	gretCSV = 6,
	//@备注 7 gretIMG 导出图像文件，支持多种图像格式。
	//@别名 导出IMG
	gretIMG = 7,
};
//@备注 GRSharePrintSetupOption (组合值) 指定各个共享全局打印参数的项目。
//@别名 共享打印参数枚举
enum GRSharePrintSetupOption{
	//@备注 1 grspsoPaperMargin 页边距项目,对应上、下、左,右页边距属性。
	//@别名 页面边距
	grspsoPaperMargin = 1,
	//@备注 2 grspsoPaperKind 纸张类型项目,对应纸张类型与大小属性。
	//@别名 纸张类型
	grspsoPaperKind = 2,
	//@备注 3 grspsoPaperOrientation 纸张的打印方向项目。
	//@别名 纸张打印方向
	grspsoPaperOrientation = 4,
	//@备注 4 grspsoPaperSource 纸张的进纸来源项目。
	//@别名 纸张进纸来源
	grspsoPaperSource = 8,
	//@备注 5 grspsoSelectedPrinter 当前选定的打印机项目,对应打印机名称属性。
	//@别名 当前选定打印机
	grspsoSelectedPrinter = 16,
};
//@备注 GRPDFDocPermission 指定PDF文档的安全性限制类型。
//@别名 PDF安全限制项枚举
enum GRPDFDocPermission{
	//@备注 1 grpdpPrint 是否允许打印。
	//@别名 允许打印
	grpdpPrint = 1,
	//@备注 2 grpdpEditAll 是否允许完整修改文档。
	//@别名 允许更改文档
	grpdpEditAll = 2,
	//@备注 3 grpdpCopy 是否允许复制文档内容。
	//@别名 允许复制内容
	grpdpCopy = 3,
	//@备注 4 grpdpEdit 是否允许修改文档。
	//@别名 允许编辑
	grpdpEdit = 4,
};
//@备注 GRExportImageType 指定在导出图像文件时可用的各种图像格式。
//@别名 导出图像类型枚举
enum GRExportImageType{
	//@备注 greitBMP Bitmap 位图图像格式。
	//@别名 BMP图
	greitBMP = 1,
	//@备注 greitPNG PNG 图像格式。
	//@别名 PNG图
	greitPNG = 2,
	//@备注 greitJPEG JPEG 图像格式。
	//@别名 JPEG图
	greitJPEG = 3,
	greitGIF = 4,
	//@备注 greitTIFF TIFF 图像格式。
	//@别名 TIFF图
	greitTIFF = 5,
};
//@备注 GRDocType 指定报表模板的文档类型。以文本格式打开报表模板文件,可以看到不同文档类型保存的报表模板数据的差异。
//@别名 文档类型枚举
enum GRDocType{
	//@备注 1 grdtObject 按对象方式保存模板数据,此种格式为 Grid++Report 自有格式,内容非常直观易理解。
	//@别名 对象格式
	grdtObject = 1,
	//@备注 2 grdtJSON 按 JSON 格式保存报表模板数据,完全符合 JSON 规范要求。
	//@别名 JSON格式
	grdtJSON = 2,
	//@备注 3 grdtRegister 6.6.5.0 改变报表模板存储方式,让WEB无限分发版的各种注册方式共享相同的报表模板
	//@别名 注册格式
	grdtRegister = 3,
};
//@备注 GRBarcodeType 指定条形码的各种类型。
//@别名 条码类型枚举
enum GRBarcodeType{
	grbtCode25Intlv = 1,
	grbtCode25Ind = 2,
	grbtCode25Matrix = 3,
	//@备注 Code39
	//@别名 Code39
	grbtCode39 = 4,
	//@备注 Code39X
	//@别名 Code39X
	grbtCode39X = 5,
	//@备注 Code128A
	//@别名 Code128A
	grbtCode128A = 6,
	//@备注 Code128B
	//@别名 Code128B
	grbtCode128B = 7,
	//@备注 Code128C
	//@别名 Code128C
	grbtCode128C = 8,
	//@备注 Code93 Extended
	//@别名 Code93X
	grbtCode93 = 9,
	grbtCode93X = 10,
	//@备注 CodeMSI
	//@别名 CodeMSI
	grbtCodeMSI = 11,
	//@备注 CodePostNet
	//@别名 CodePostNet
	grbtCodePostNet = 12,
	//@备注 CodeCodabar
	//@别名 CodeCodabar
	grbtCodeCodabar = 13,
	//@备注 CodeEAN8,商品码,数据只能为数字
	//@别名 CodeEAN8
	grbtCodeEAN8 = 14,
	//@备注 CodeEAN13,,商品码,数据只能为数字。如果进行数据校验,提供12位数字数据,否则13位数字数据
	//@别名 CodeEAN13
	grbtCodeEAN13 = 15,
	//@备注 CodeUPC_A,商品码,数据只能为数字
	//@别名 CodeUPC_A
	grbtCodeUPC_A = 16,
	//@备注 CodeUPC_E0,商品码,数据只能为数字
	//@别名 CodeUPC_E0
	grbtCodeUPC_E0 = 17,
	//@备注 CodeUPC_E1,商品码,数据只能为数字
	//@别名 CodeUPC_E1
	grbtCodeUPC_E1 = 18,
	//@备注 CodeUPC_Supp2
	//@别名 CodeUPC_Supp2
	grbtCodeUPC_Supp2 = 19,
	//@备注 CodeUPC_Supp5
	//@别名 CodeUPC_Supp5
	grbtCodeUPC_Supp5 = 20,
	//@备注 CodeEAN128A
	//@别名 CodeEAN128A
	grbtCodeEAN128A = 21,
	//@备注 CodeEAN128B
	//@别名 CodeEAN128B
	grbtCodeEAN128B = 22,
	//@备注 CodeEAN128C
	//@别名 CodeEAN128C
	grbtCodeEAN128C = 23,
	//@备注 Code128Auto Code128自动编码
	//@别名 Code128Auto
	grbtCode128Auto = 24,
	grbtPDF417 = 50,
	grbtQRCode = 51,
	grbtDataMatrix = 52,
	grbtGS1DataMatrix = 53,
	grbtGS1QRCode = 54,
	grbtCodeEAN128Auto = 25,
	grbtITF_14 = 26,
};
//@备注 GRStringAlignment 指定文本字符串相对于其布局矩形的对齐方式。
//@别名 文本对齐方式枚举
enum GRStringAlignment{
	//@备注 1 grsaNear 定文本靠近布局对齐。在左到右布局中,近端位置是左。在右到左布局中,近端位置是右。
	//@别名 近端
	grsaNear = 1,
	//@备注 2 grsaCenter 指定文本在布局矩形中居中对齐。
	//@别名 居中
	grsaCenter = 2,
	//@备注 3 grsaFar 指定文本远离布局矩形的原点位置对齐。在左到右布局中,远端位置是右。在右到左布局中,远端位置是左。
	//@别名 远端
	grsaFar = 3,
};
//@备注 GRBarcodeCaptionPosition 表示条形码文字的输出位置。
//@别名 条码文字位置枚举
enum GRBarcodeCaptionPosition{
	//@备注 1 grbcpNone 条形码的文字不显示。
	//@别名 无
	grbcpNone = 1,
	//@备注 2 grbcpAbove 条形码的文字显示在上端。
	//@别名 上端
	grbcpAbove = 2,
	//@备注 3 grbcpBelow 条形码的文字显示在下端。
	//@别名 下端
	grbcpBelow = 3,
};
//@备注 GRBarcodeDirection 表示条形码图形的输出方向。
//@别名 条形码方向枚举
enum GRBarcodeDirection{
	//@备注 1 LeftToRight 从左到右。
	//@别名 从左到右
	grbdLeftToRight = 1,
	//@备注 2 RightToLeft 从右到左。
	//@别名 从右到左
	grbdRightToLeft = 2,
	//@备注 3 TopToBottom 从上到下。
	//@别名 从上到下
	grbdTopToBottom = 3,
	//@备注 4 BottomToTop 从下到上。
	//@别名 从下到上
	grbdBottomToTop = 4,
};
//@备注 GRDtmxEncoding 指定二维码DataMatrix的数据编码方式。
//@别名 DataM编码枚举
enum GRDtmxEncoding{
	//@备注 2 grdtmxeAuto 由程序根据数据自动选择编码方式
	//@别名 自动选择
	grdtmxeAuto = 2,
	//@备注 3 grdtmxeAscii Ascii编码方式
	//@别名 Ascii码
	grdtmxeAscii = 3,
	//@备注 4 grdtmxeC40 C40编码方式
	//@别名 C40码
	grdtmxeC40 = 4,
	//@备注 5 grdtmxeText Text编码方式
	//@别名 Text码
	grdtmxeText = 5,
	//@备注 6 grdtmxeX12 X12编码方式
	//@别名 X12码
	grdtmxeX12 = 6,
	//@备注 7 grdtmxeEdifact Edifact编码方式
	//@别名 Edifact码
	grdtmxeEdifact = 7,
	//@备注 8 grdtmxeBase256 Base256编码方式
	//@别名 Base256码
	grdtmxeBase256 = 8,
};
//@备注 GRDtmxMatrixSize 指定二维码DataMatrix的图形模块矩阵维数
//@别名 DataM矩阵维度枚举
enum GRDtmxMatrixSize{
	//@备注 grdtmxmsAuto
	//@别名 自动选择
	grdtmxmsAuto = 2,
	//@备注 grdtmxms10x10
	//@别名 维度10x10
	grdtmxms10x10 = 4,
	//@备注 grdtmxms12x12
	//@别名 维度12x12
	grdtmxms12x12 = 5,
	//@备注 grdtmxms14x14
	//@别名 维度14x14
	grdtmxms14x14 = 6,
	//@备注 grdtmxms16x16
	//@别名 维度16x16
	grdtmxms16x16 = 7,
	//@备注 grdtmxms18x18
	//@别名 维度18x18
	grdtmxms18x18 = 8,
	//@备注 grdtmxms20x20
	//@别名 维度20x20
	grdtmxms20x20 = 9,
	//@备注 grdtmxms22x22
	//@别名 维度22x22
	grdtmxms22x22 = 10,
	//@备注 grdtmxms24x24
	//@别名 维度24x24
	grdtmxms24x24 = 11,
	//@备注 grdtmxms26x26
	//@别名 维度26x26
	grdtmxms26x26 = 12,
	//@备注 grdtmxms32x32
	//@别名 维度32x32
	grdtmxms32x32 = 13,
	//@备注 grdtmxms36x36
	//@别名 维度36x36
	grdtmxms36x36 = 14,
	//@备注 grdtmxms40x40
	//@别名 维度40x40
	grdtmxms40x40 = 15,
	//@备注 grdtmxms44x44
	//@别名 维度44x44
	grdtmxms44x44 = 16,
	//@备注 grdtmxms48x48
	//@别名 维度48x48
	grdtmxms48x48 = 17,
	//@备注 grdtmxms52x52
	//@别名 维度52x52
	grdtmxms52x52 = 18,
	//@备注 grdtmxms64x64
	//@别名 维度64x64
	grdtmxms64x64 = 19,
	//@备注 grdtmxms72x72
	//@别名 维度72x72
	grdtmxms72x72 = 20,
	//@备注 grdtmxms80x80
	//@别名 维度80x80
	grdtmxms80x80 = 21,
	//@备注 grdtmxms88x88
	//@别名 维度88x88
	grdtmxms88x88 = 22,
	//@备注 grdtmxms96x96
	//@别名 维度96x96
	grdtmxms96x96 = 23,
	//@备注 grdtmxms104x104
	//@别名 维度104x104
	grdtmxms104x104 = 24,
	//@备注 grdtmxms120x120
	//@别名 维度120x120
	grdtmxms120x120 = 25,
	//@备注 grdtmxms132x132
	//@别名 维度132x132
	grdtmxms132x132 = 26,
	//@备注 grdtmxms144x144
	//@别名 维度144x144
	grdtmxms144x144 = 27,
	//@备注 grdtmxms8x18
	//@别名 维度8x18
	grdtmxms8x18 = 28,
	//@备注 grdtmxms8x32
	//@别名 维度8x32
	grdtmxms8x32 = 29,
	//@备注 grdtmxms12x26
	//@别名 维度12x26
	grdtmxms12x26 = 30,
	//@备注 grdtmxms12x36
	//@别名 维度12x36
	grdtmxms12x36 = 31,
	//@备注 grdtmxms16x36
	//@别名 维度16x36
	grdtmxms16x36 = 32,
	//@备注 grdtmxms16x48
	//@别名 维度16x48
	grdtmxms16x48 = 33,
};
//@备注 GRPeriodType 表示按日期期间交叉的交叉表日期期间的类型。
//@别名 周期类型枚举
enum GRPeriodType{
	//@备注 0 grptNone
	//@别名 无
	grptNone = 0,
	//@备注 1 grptDay
	//@别名 天
	grptDay = 1,
	//@备注 2 grptWeek
	//@别名 周
	grptWeek = 2,
	//@备注 3 grptThirdMonth
	//@别名 三个月
	grptThirdMonth = 3,
	//@备注 4 grptHalfMonth
	//@别名 半月
	grptHalfMonth = 4,
	//@备注 5 grptMonth
	//@别名 月
	grptMonth = 5,
	//@备注 6 grptQuarter
	//@别名 季度
	grptQuarter = 6,
	//@备注 7 grptHalfYear
	//@别名 半年
	grptHalfYear = 7,
	//@备注 8 grptYear
	//@别名 年
	grptYear = 8,
	//@备注 9 grptCalendar
	//@别名 日历表
	grptCalendar = 9,
};
//@备注 GRPageColumnDirection 在明细网格打印生成时,如果生成多栏报表,指定明细网格的各种行的在各页栏中的输出次序。
//@别名 页栏输出方向枚举
enum GRPageColumnDirection{
	//@备注 1 grpcdDownAcross 按从上到下,再从左到右的顺序在页栏中打印输出。
	//@别名 先从上到下再左到右
	grpcdDownAcross = 1,
	//@备注 2 grpcdAcrossDown 按从左到右,再从上到下的顺序在页栏中打印输出。
	//@别名 先从左到右再上到下
	grpcdAcrossDown = 2,
	//@备注 3 grpcdDownAcrossEqual 按从上到下,再从左到右的顺序在页栏中打印输出,保持每栏输出基本一样多的数据。
	//@别名 先从上到下且等分
	grpcdDownAcrossEqual = 3,
};
//@备注 GRColumnPrintAdaptMethod 打印生成时，明细网格列对输出页面的适应方法。
// 在打印输出到纸张页面中，输出列的总宽度与页面的输出宽度（除掉左右页边距的宽度）很可能不一样，系统可以采用几种方法来处理列的输出。
// 如采用调整列的宽度以适应输出区域的宽度，则系统根据每个列的设计宽度按比列调整其打印输出宽度，使所有打印输出列的打印输出总宽度与打印输出区域宽度保持一样；
// 如果列的设计总宽度小于输出区域宽度，所有列的打印宽度将放大，反之则缩小。
//@别名 打印策略枚举
enum GRColumnPrintAdaptMethod{
	//@备注 1 grcpamDiscard 在打印输出时,超出页面输出范围的列内容将被忽略掉,即不输出显示。
	//@别名 丢弃
	grcpamDiscard = 1,
	//@备注 2 grcpamWrap 在打印输出时,超出页面输出范围的列内容将另起新行输出显示。
	//@别名 绕行
	grcpamWrap = 2,
	//@备注 3 grcpamResizeToFit 在打印输出时,根据列的宽度按比列将所有要输出的列的总宽度调整到页面输出区域的宽度。
	//@别名 缩放适应
	grcpamResizeToFit = 3,
	//@备注 4 grcpamShrinkToFit 在打印输出时,如果列的总宽度超出页面输出范围,与grcpamResizeToFit相同,反之按设计时宽度输出。
	//@别名 按需缩小适应
	grcpamShrinkToFit = 4,
	//@备注 5 grcpamToNewPage 在打印输出时,超出页面输出范围的列内容将另起新页输出显示,按先从上到下的顺序输出。
	//@别名 横向分页先纵向
	grcpamToNewPage = 5,
	//@备注 6 grcpamToNewPageEx 在打印输出时,超出页面输出范围的列内容将另起新页输出显示,按先从左到右的顺序输出。
	//@别名 横向分页先横向
	grcpamToNewPageEx = 6,
	//@备注 7 grcpamToNewPageRFC 在打印输出时,超出页面输出范围的列内容将另起新页输出显示,且左边的固定列在每页中重复输出,按先从上到下的顺序输出。
	//@别名 横向分页并重复锁定列先纵向
	grcpamToNewPageRFC = 7,
	//@备注 8 grcpamToNewPageRFCEx 在打印输出时,超出页面输出范围的列内容将另起新页输出显示,且左边的固定列在每页中重复输出,按先从左到右的顺序输出。
	//@别名 横向分页并重复锁定列先横向
	grcpamToNewPageRFCEx = 8,
	//@备注 9 grcpamWrapExcludeGroup 类同 grcpamWrap,但分组头尾不另起新行。
	//@别名 排除分组绕行
	grcpamWrapExcludeGroup = 9,
};
//@备注 GRNewPageColumnStyle 在打印生成明细网格的分组头时,指定是否强制产生新页列的方式。
//@别名 换新页栏方式枚举
enum GRNewPageColumnStyle{
	//@备注 1 grncsNone 分组头在任何时候都不另起新页栏。
	//@别名 不应用
	grncsNone = 1,
	//@备注 2 grncsBefore 分组头在打印输出之前另起新页栏进行输出。
	//@别名 页栏前
	grncsBefore = 2,
	//@备注 3 grncsAfter 分组头在打印输出之后另起新页栏。后续内容输出在新页栏中。
	//@别名 页栏后
	grncsAfter = 3,
	//@备注 4 grncsBeforeAfter 分组头在打印输出之前与之后都另起新页栏。
	//@别名 页栏前与页栏后
	grncsBeforeAfter = 4,
};
//@备注 GROCGroupHeaderVAlign 指定占列式分组头在整个分组列区域的垂直方向上对齐位置。
//@别名 分组头对齐方式枚举
enum GROCGroupHeaderVAlign{
	//@备注 1 grbaTop 占列式分组头显示在整个分组列区域的顶部。
	//@别名 上端
	grbaTop = 1,
	//@备注 2 grbaBottom 占列式分组头显示在整个分组列区域的底部。
	//@别名 下端
	grbaBottom = 2,
	//@备注 3 grbaMiddle 占列式分组头显示在整个分组列区域的中部(垂直方向)。
	//@别名 居中
	grbaMiddle = 3,
};
//@备注 GRGrpKpTogetherStyle 指定分组头行与本分组项其他行在打印输出时聚集在相同页的方式。
//@别名 分组保持同页方式枚举
enum GRGrpKpTogetherStyle{
	//@备注 1 grgktsNone 不要求分组头行与本分组项其他行打印输出聚集在相同页。
	//@别名 不应用
	grgktsNone = 1,
	//@备注 2 grgktsFirstDetail 要求分组头行与本分组项的第一个明细记录行打印输出在相同页。
	//@别名 第一个记录行
	grgktsFirstDetail = 2,
	//@备注 3 grgktsAll 要求分组头行与本分组项的其他所有行尽量打印输出在相同页。
	//@别名 整个
	grgktsAll = 3,
};
//@备注 查询显示器和打印显示器公用
//@别名 显示器边框样式枚举
enum GRViewerBorderStyle{
	
	grvbsFixed3D = 1,     //@别名 固定3D
	grvbsFixedSingle = 2, //@别名 固定单边
	grvbsNone = 3,        //@别名 无
};
//@备注 GRPreviewEditMode 指定报表预览时文字的即时编辑模式。
//@别名 预览编辑模式枚举
enum GRPreviewEditMode{
	//@备注 grpemDisable 不开启文字编辑功能。 
	//@别名 禁用
	grpemDisable = 1,
	//@备注 grpemClickToEdit 单击文字进行即时编辑。 
	//@别名 单击编辑
	grpemClickToEdit = 2,
	//@备注 grpemDblClickToEdit 双击文字进行即时编辑。 
	//@别名 双击编辑
	grpemDblClickToEdit = 3,
};
//@备注 GRPrintViewMode 在打印预览查看器中，指定查看模式。
//@别名 查看模式枚举
enum GRPrintViewMode{
	grpvmContinuousPage = 1,  //@别名  连续
	grpvmSinglePage = 2,  //@别名  单页
	grpvmMultiPage = 3,  //@别名  多页
};
//@备注 GRToolControlType 指定打印显示器控件中工具栏上的按钮、编辑框与组合框的类型。
//@别名 打印显示器按钮枚举
enum GRToolControlType{
	//@备注 1 grtctSep 指定分隔空隙 
	//@别名 分隔
	grtctSep = 1,
	//@备注 2 grtctPrint 指定打印按钮 
	//@别名 打印
	grtctPrint = 2,
	//@备注 3 grtctPageSetup 指定页面设置按钮 
	//@别名 页面设置
	grtctPageSetup = 3,
	//@备注 4 grtctPrinterSetup 指定打印机设置按钮
	//@别名 打印机设置
	grtctPrinterSetup = 4,
	//@备注 5 grtctExport 指定数据导出按钮（数据导出多种格式文件功能的下拉菜单项主按钮，本身不会产生事件）
	//@别名 导出
	grtctExport = 5,
	//@备注 6 grtctMail 指定发送邮件按钮（导出多种格式文件并发送邮件功能的下拉菜单项主按钮，本身不会产生事件）
	//@别名 邮件
	grtctMail = 6,
	//@备注 7 grtctSaveDocument 指定保存为 Grid++Report 文档文件按钮
	//@别名 保存报表文档
	grtctSaveDocument = 7,
	//@备注 8 grtctContinuousPage 指定连续页查看模式按钮
	//@别名 连续
	grtctContinuousPage = 8,
	//@备注 9 grtctSinglePage 指定单页查看模式按钮 
	//@别名 单页
	grtctSinglePage = 9,
	//@备注 10 grtctMultiPage 指定多页查看模式按钮
	//@别名 多页
	grtctMultiPage = 10,
	//@备注 11 grtctZoomIn 指定放大显示比例按钮 
	//@别名 放大
	grtctZoomIn = 11,
	//@备注 12 grtctZoomOut 指定缩小显示比例按钮 
	//@别名 缩小
	grtctZoomOut = 12,
	//@备注 13 grtctZoomPercent 指定显示百分比下拉列表组合框 
	//@别名 缩放百分比
	grtctZoomPercent = 13,
	//@备注 14 grtctPriorPage 指定前一页按钮 
	//@别名 上一页
	grtctPriorPage = 14,
	//@备注 15 grtctNextPage 指定后一页按钮 
	//@别名 下一页
	grtctNextPage = 15,
	//@备注 16 grtctFirstPage 指定首页按钮 
	//@别名 首页
	grtctFirstPage = 16,
	//@备注 17 grtctLastPage 指定尾页按钮 
	//@别名 尾页
	grtctLastPage = 17,
	//@备注 18 grtctCurPageNo 指定当前显示页编辑框 
	//@别名 当前页号
	grtctCurPageNo = 18,
	//@备注 19 grtctClose 指定关闭按钮 
	//@别名 关闭
	grtctClose = 19,
	//@备注 20 grtctClip 指定内容复制粘贴按钮，包含3个按钮：鼠标拖动、鼠标选定、复制到剪贴板
	//@别名 剪切
	grtctClip = 20,
	//@备注 21 grtctRefresh 指定刷新按钮 
	//@别名 刷新
	grtctRefresh = 21,
	//@备注 22 grtctBookmark 指定书签按钮 
	//@别名 书签
	grtctBookmark = 22,
	//@备注 指定查找文字筐，尚未实现，预留
	//@别名 查找文本框
	grtctFindTextBox = 30,
	//@备注 指定查找按钮，尚未实现，预留
	//@别名 查找按钮
	grtctFind = 31,
	//@备注 指定继续查找按钮，尚未实现，预留
	//@别名 继续查找按钮
	grtctFindAgain = 32,
	//@备注 指定查找对话框按钮，尚未实现，预留
	//@别名 显示查找对话框钮
	grtctFindDlg = 33,
	//@备注 50 grtctExportXLS 指定导出 Excel 菜单项 
	//@别名 导出XLS文件
	grtctExportXLS = 50,
	//@备注 51 grtctExportTXT 指定导出 Text 菜单项 
	//@别名 导出TXT文件
	grtctExportTXT = 51,
	//@备注 52 grtctExportHTM 指定导出 html 菜单项 
	//@别名 导出HTM文件
	grtctExportHTM = 52,
	//@备注 53 grtctExportRTF 指定导出 RTF 菜单项 
	//@别名 导出RTF文件
	grtctExportRTF = 53,
	//@备注 54 grtctExportPDF 指定导出 PDF 菜单项 
	//@别名 导出PDF文件
	grtctExportPDF = 54,
	//@备注 55 grtctExportCSV 指定导出 CSV 菜单项 
	//@别名 导出CSV文件
	grtctExportCSV = 55,
	//@备注 56 grtctExportIMG 指定导出图像菜单项 
	//@别名 导出IMG文件
	grtctExportIMG = 56,
	//@备注 60 grtctExportXLSBtn 指定导出 Excel 按钮 
	//@别名 导出XLS文件按钮
	grtctExportXLSBtn = 60,
	//@备注 61 grtctExportPDFBtn 指定导出 PDF 按钮
	//@别名 导出PDF文件按钮
	grtctExportPDFBtn = 61,
	//@备注 65 grtctMailXLS 指定导出 Excel 并发送Email菜单项 
	//@别名 邮件发送XLS文件
	grtctMailXLS = 65,
	//@备注 66 grtctMailTXT 指定导出 Text 并发送Email菜单项 
	//@别名 邮件发送TXT文件
	grtctMailTXT = 66,
	//@备注 67 grtctMailHTM 指定导出 html 并发送Email菜单项 
	//@别名 邮件发送HTM文件
	grtctMailHTM = 67,
	//@备注 68 grtctMailRTF 指定导出 RTF 并发送Email菜单项
	//@别名 邮件发送RTF文件
	grtctMailRTF = 68,
	//@备注 69 grtctMailPDF 指定导出 PDF 并发送Email菜单项 
	//@别名 邮件发送PDF文件
	grtctMailPDF = 69,
	//@备注 70 grtctMailCSV 指定导出 CSV 并发送Email菜单项 
	//@别名 邮件发送CSV文件
	grtctMailCSV = 70,
	//@备注 71 grtctMailIMG 指定导出图像并发送Email菜单项 
	//@别名 邮件发送IMG文件
	grtctMailIMG = 71,
	//@备注 72 grtctMailSaveDocument 指定保存为 Grid++Report 文档并发送Email菜单项
	//@别名 邮件发送报表文档
	grtctMailSaveDocument = 72,
};
//@备注 GRPrintViewerOption  指定打印显示器某个选项参数
//@别名 打印显示器选项枚举
enum GRPrintViewerOption{
	//@备注 grpvoShowContentMenu 显示弹出式关联菜单。 
	//@别名 显示控制菜单
	grpvoShowContentMenu = 1,
	//@备注 grpvoDblClickSwitchViewMode 鼠标双击切换查看方式。 
	//@别名 双击切换视图模式
	grpvoDblClickSwitchViewMode = 2,
};
//@备注 GRShiftStates 在鼠标与键盘事件中，指定事件触发时鼠标与键盘的状态。
//@别名 切换状态枚举
enum GRShiftStates{
	//@备注 grssShift 指示键盘‘Shift’键按下标志。
	//@别名 功能键Shift
	grssShift = 1,
	//@备注 grssAlt 指示键盘‘Alt’键按下标志。
	//@别名 功能键Alt
	grssAlt = 2,
	//@备注 grssCtrl 指示键盘‘Ctrl’键按下标志。
	//@别名 功能键Ctrl
	grssCtrl = 4,
	//@备注 grssLeft 指示鼠标左按钮按下标志。
	//@别名 鼠标左键
	grssLeft = 8,
	//@备注 grssRight 指示鼠标右按钮按下标志。
	//@别名 鼠标右键
	grssRight = 16,
	//@备注 grssMiddle 指示鼠标中按钮按下标志。
	//@别名 鼠标中键
	grssMiddle = 32,
	//@备注 grssDouble 指示鼠标双击标志。
	//@别名 鼠标双击
	grssDouble = 64,
};
//@备注 GRMouseButton 指定鼠标按钮
//@别名 鼠标按钮枚举
enum GRMouseButton{
	//@备注 grmbLeft
	//@别名 左
	grmbLeft = 1,
	//@备注 grmbRight
	//@别名 右
	grmbRight = 2,
	//@备注 grmbMiddle
	//@别名 中
	grmbMiddle = 3,
};
//@备注 GRToolControlType2 指定报表查询显示器控件的工具栏中的各个按钮。
//@别名 查询显示器按钮枚举
enum GRToolControlType2{
	//@备注 1 grdtctSep 指定分隔按钮
	//@别名 分隔
	grdtctSep = 1,
	//@备注 2 grdtctPrint 指定打印按钮
	//@别名 打印
	grdtctPrint = 2,
	//@备注 3 grdtctPageSetup 指定打印页面设置按钮
	//@别名 页面设置
	grdtctPageSetup = 3,
	//@备注 4 grdtctPrinterSetup 指定打印机设置按钮
	//@别名 打印机设置
	grdtctPrinterSetup = 4,
	//@备注 40 grdtctPrintPreview 指定打印预览按钮
	//@别名 打印预览
	grdtctPrintPreview = 40,
	//@备注 41 grdtctPostLayout 指定打印提交布局选取框
	//@别名 打印应用布局
	grdtctPostLayout = 41,
	grdtctShowPreviewLine = 42,
	//@备注 30 grdtctFindTextBox 指定查找编辑框
	//@别名 查找文本框
	grdtctFindTextBox = 30,
	//@备注 31 grdtctFind 指定查找按钮
	//@别名 查找按钮
	grdtctFind = 31,
	//@备注 32 grdtctFindAgain 指定继续查找按钮
	//@别名 继续查找按钮
	grdtctFindAgain = 32,
	//@备注 33 grdtctFindDlg 指定查找对话框按钮
	//@别名 显示查找对话框钮
	grdtctFindDlg = 33,
	//@备注 14 grdtctPriorPage 指定上一页按钮
	//@别名 上一页
	grdtctPriorPage = 14,
	//@备注 15 grdtctNextPage 指定下一页按钮
	//@别名 下一页
	grdtctNextPage = 15,
	//@备注 16 grdtctFirstPage 指定首页按钮
	//@别名 首页
	grdtctFirstPage = 16,
	//@备注 17 grdtctLastPage 指定最后页按钮
	//@别名 尾页
	grdtctLastPage = 17,
	//@备注 18 grdtctCurPageNo 指定页号编辑框
	//@别名 当前页号
	grdtctCurPageNo = 18,
	//@备注 25 grdtctDividePage 指定明细网格数据分页方式组合框与每页行数编辑框
	//@别名 分页方式
	grdtctDividePage = 25,
	//@备 指定按钮，尚未实现，预留
	//@别名 剪切
	grdtctClip = 20,
	//@备注 5 grdtctExport 指定数据导出按钮（数据导出多种格式文件功能的下拉菜单项主按钮，本身不会产生事件）
	//@别名 导出
	grdtctExport = 5,
	//@备注 6 grdtctMail 指定邮件发送按钮（导出多种格式文件并发送邮件功能的下拉菜单项主按钮，本身不会产生事件）
	//@别名 邮件
	grdtctMail = 6,
	//@备注 7 grdtctSaveDocument 指定保存打印文档按钮 
	//@别名 保存报表文档
	grdtctSaveDocument = 7,
	//@备注 19 grdtctClose 指定关闭按钮
	//@别名 关闭
	grdtctClose = 19,
	//@备注 21 grdtctRefresh 指定刷新按钮
	//@别名 刷新
	grdtctRefresh = 21,
	//@备注 50 grdtctExportXLS 指定导出 Excel 菜单项
	//@别名 导出XLS文件
	grdtctExportXLS = 50,
	//@备注 51 grdtctExportTXT 指定导出文本菜单项
	//@别名 导出TXT文件
	grdtctExportTXT = 51,
	//@备注 52 grdtctExportHTM 指定导出 HTML 菜单项
	//@别名 导出HTM文件
	grdtctExportHTM = 52,
	//@备注 53 grdtctExportRTF 指定导出 RTF 菜单项
	//@别名 导出RTF文件
	grdtctExportRTF = 53,
	//@备注 54 grdtctExportPDF 指定导出 PDF 菜单项
	//@别名 导出PDF文件
	grdtctExportPDF = 54,
	//@备注 55 grdtctExportCSV 指定导出 CSV 菜单项
	//@别名 导出CSV文件
	grdtctExportCSV = 55,
	//@备注 56 grdtctExportIMG 指定导出图像菜单项
	//@别名 导出IMG文件
	grdtctExportIMG = 56,
	//@备注 60 grdtctExportXLSBtn 指定导出 Excel 按钮
	//@别名 导出XLS文件按钮
	grdtctExportXLSBtn = 60,
	//@备注 61 grdtctExportPDFBtn 指定导出 PDF 按钮
	//@别名 导出PDF文件按钮
	grdtctExportPDFBtn = 61,
	//@备注 65 grdtctMailXLS 指定导出 Excel 并发送Email菜单项
	//@别名 邮件发送XLS文件
	grdtctMailXLS = 65,
	//@备注 66 grdtctMailTXT 指定导出文本并发送Email菜单项
	//@别名 邮件发送TXT文件
	grdtctMailTXT = 66,
	//@备注 67 grdtctMailHTM 指定导出 HTML 并发送Email菜单项
	//@别名 邮件发送HTM文件
	grdtctMailHTM = 67,
	//@备注 68 grdtctMailRTF 指定导出 RTF 并发送Email菜单项
	//@别名 邮件发送RTF文件
	grdtctMailRTF = 68,
	//@备注 69 grdtctMailPDF 指定导出 PDF 并发送Email菜单项
	//@别名 邮件发送PDF文件
	grdtctMailPDF = 69,
	//@备注 70 grdtctMailCSV 指定导出 CSV 并发送Email菜单项
	//@别名 邮件发送CSV文件
	grdtctMailCSV = 70,
	//@备注 71 grdtctMailIMG 指定导出图像并发送Email菜单项
	//@别名 邮件发送IMG文件
	grdtctMailIMG = 71,
	//@备注 80 grdtctColumnVisible 指定打开列可见性设置对话框按钮
	//@别名 列显示功能
	grdtctColumnVisible = 80,
};
//@备注 GRDisplayViewerOption  指定查询显示器某个选项参数
//@别名 查询显示器选项枚举
enum GRDisplayViewerOption{
	//@备注  查询显示器右键菜单
	grdvoShowContentMenu = 1, //@别名  显示控制菜单
};
*/
