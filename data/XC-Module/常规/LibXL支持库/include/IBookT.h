///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                    LibXL C++ headers version 4.0.3                        //
//                                                                           //
//                 Copyright (c) 2008 - 2022 XLware s.r.o.                   //
//                                                                           //
//   THIS FILE AND THE SOFTWARE CONTAINED HEREIN IS PROVIDED 'AS IS' AND     //
//                COMES WITH NO WARRANTIES OF ANY KIND.                      //
//                                                                           //
//          Please define LIBXL_STATIC variable for static linking.          //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifndef LIBXL_IBOOKT_H
#define LIBXL_IBOOKT_H

#include <stddef.h>
#include "setup.h"
#include "enum.h"

namespace libxl {

    template<class TCHAR> struct ISheetT;
    template<class TCHAR> struct IFormatT;
    template<class TCHAR> struct IFontT;
    template<class TCHAR> struct IRichStringT;
    template<class TCHAR> struct IConditionalFormatT;

    template<class TCHAR>
    struct IBookT
    {
        virtual             bool XLAPIENTRY load(const TCHAR* filename, const TCHAR* tempFile = 0) = 0;
        virtual             bool XLAPIENTRY loadSheet(const TCHAR* filename, int sheetIndex, const TCHAR* tempFile = 0) = 0;
        virtual             bool XLAPIENTRY loadPartially(const TCHAR* filename, int sheetIndex, int firstRow, int lastRow, const TCHAR* tempFile = 0) = 0;
        virtual             bool XLAPIENTRY loadWithoutEmptyCells(const TCHAR* filename) = 0;
        virtual             bool XLAPIENTRY loadInfo(const TCHAR* filename) = 0;

        virtual             bool XLAPIENTRY save(const TCHAR* filename, bool useTempFile = false) = 0;

        virtual             bool XLAPIENTRY loadRaw(const char* data, unsigned size, int sheetIndex = -1, int firstRow = -1, int lastRow = -1) = 0;
        virtual             bool XLAPIENTRY saveRaw(const char** data, unsigned* size) = 0;

        virtual  ISheetT<TCHAR>* XLAPIENTRY addSheet(const TCHAR* name, ISheetT<TCHAR>* initSheet = 0) = 0;
        virtual  ISheetT<TCHAR>* XLAPIENTRY insertSheet(int index, const TCHAR* name, ISheetT<TCHAR>* initSheet = 0) = 0;
        virtual  ISheetT<TCHAR>* XLAPIENTRY getSheet(int index) const = 0;
        virtual     const TCHAR* XLAPIENTRY getSheetName(int index) const = 0;
        virtual        SheetType XLAPIENTRY sheetType(int index) const = 0;
        virtual             bool XLAPIENTRY moveSheet(int srcIndex, int dstIndex) = 0;
        virtual             bool XLAPIENTRY delSheet(int index) = 0;
        virtual              int XLAPIENTRY sheetCount() const = 0;

        virtual IFormatT<TCHAR>* XLAPIENTRY addFormat(IFormatT<TCHAR>* initFormat = 0) = 0;
        virtual   IFontT<TCHAR>* XLAPIENTRY addFont(IFontT<TCHAR>* initFont = 0) = 0;
        virtual IRichStringT<TCHAR>* XLAPIENTRY addRichString() = 0;
        virtual              int XLAPIENTRY addCustomNumFormat(const TCHAR* customNumFormat) = 0;
        virtual     const TCHAR* XLAPIENTRY customNumFormat(int fmt) = 0;

        virtual IFormatT<TCHAR>* XLAPIENTRY format(int index) = 0;
        virtual              int XLAPIENTRY formatSize() = 0;

        virtual   IFontT<TCHAR>* XLAPIENTRY font(int index) = 0;
        virtual              int XLAPIENTRY fontSize() = 0;

        virtual IConditionalFormatT<TCHAR>* XLAPIENTRY addConditionalFormat() = 0;

        virtual           double XLAPIENTRY datePack(int year, int month, int day, int hour = 0, int min = 0, int sec = 0, int msec = 0) = 0;
        virtual             bool XLAPIENTRY dateUnpack(double value, int* year, int* month, int* day, int* hour = 0, int* min = 0, int* sec = 0, int* msec = 0) = 0;

        virtual            Color XLAPIENTRY colorPack(int red, int green, int blue) = 0;
        virtual             void XLAPIENTRY colorUnpack(Color color, int* red, int* green, int* blue) = 0;

        virtual              int XLAPIENTRY activeSheet() const = 0;
        virtual             void XLAPIENTRY setActiveSheet(int index) = 0;

        virtual              int XLAPIENTRY pictureSize() const = 0;
        virtual      PictureType XLAPIENTRY getPicture(int index, const char** data, unsigned* size) const = 0;

        virtual              int XLAPIENTRY addPicture(const TCHAR* filename) = 0;
        virtual              int XLAPIENTRY addPicture2(const char* data, unsigned size) = 0;
        virtual              int XLAPIENTRY addPictureAsLink(const TCHAR* filename, bool insert = false) = 0;

        virtual     const TCHAR* XLAPIENTRY defaultFont(int* fontSize) = 0;
        virtual             void XLAPIENTRY setDefaultFont(const TCHAR* fontName, int fontSize) = 0;

        virtual             bool XLAPIENTRY refR1C1() const = 0;
        virtual             void XLAPIENTRY setRefR1C1(bool refR1C1 = true) = 0;

        virtual             void XLAPIENTRY setKey(const TCHAR* name, const TCHAR* key) = 0;

        virtual             bool XLAPIENTRY rgbMode() = 0;
        virtual             void XLAPIENTRY setRgbMode(bool rgbMode = true) = 0;

        virtual     CalcModeType XLAPIENTRY calcMode() const = 0;
        virtual             void XLAPIENTRY setCalcMode(CalcModeType calcMode) = 0;

        virtual              int XLAPIENTRY version() const = 0;
        virtual              int XLAPIENTRY biffVersion() const = 0;

        virtual             bool XLAPIENTRY isDate1904() const = 0;
        virtual             void XLAPIENTRY setDate1904(bool date1904 = true) = 0;

        virtual             bool XLAPIENTRY isTemplate() const = 0;
        virtual             void XLAPIENTRY setTemplate(bool tmpl = true) = 0;

        virtual             bool XLAPIENTRY isWriteProtected() const = 0;

        virtual             bool XLAPIENTRY setLocale(const char* locale) = 0;
        virtual      const TCHAR* XLAPIENTRY errorMessage() const = 0;

        virtual             void XLAPIENTRY release() = 0;

        virtual                             ~IBookT() {}
    };

}

extern "C" XLAPI libxl::IBookT<char>* XLAPIENTRY xlCreateBookA();
extern "C" XLAPI libxl::IBookT<wchar_t>* XLAPIENTRY xlCreateBookW();

extern "C" XLAPI libxl::IBookT<char>* XLAPIENTRY xlCreateXMLBookA();
extern "C" XLAPI libxl::IBookT<wchar_t>* XLAPIENTRY xlCreateXMLBookW();

#endif
