// Copyright (c) 2012 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// The contents of this file must follow a specific format in order to
// support the CEF translator tool. See the translator.README.txt file in the
// tools directory for more information.
//

#ifndef CEF_INCLUDE_CEF_RESOURCE_BUNDLE_HANDLER_H_
#define CEF_INCLUDE_CEF_RESOURCE_BUNDLE_HANDLER_H_
#pragma once

#include "include/cef_base.h"

///
/// Class used to implement a custom resource bundle interface. See CefSettings
/// for additional options related to resource bundle loading. The methods of
/// this class may be called on multiple threads.
///
/*--cef(source=client)--*/
class CefResourceBundleHandler : public virtual CefBaseRefCounted {
 public:
  typedef cef_scale_factor_t ScaleFactor;

  ///
  /// Called to retrieve a localized translation for the specified |string_id|.
  /// To provide the translation set |string| to the translation string and
  /// return true. To use the default translation return false. Use the
  /// cef_id_for_pack_string_name() function for version-safe mapping of string
  /// IDS names from cef_pack_strings.h to version-specific numerical
  /// |string_id| values.
  ///
  /*--cef()--*/
  virtual bool GetLocalizedString(int string_id, CefString& string) = 0;

  ///
  /// Called to retrieve data for the specified scale independent |resource_id|.
  /// To provide the resource data set |data| and |data_size| to the data
  /// pointer and size respectively and return true. To use the default resource
  /// data return false. The resource data will not be copied and must remain
  /// resident in memory. Use the cef_id_for_pack_resource_name() function for
  /// version-safe mapping of resource IDR names from cef_pack_resources.h to
  /// version-specific numerical |resource_id| values.
  ///
  /*--cef()--*/
  virtual bool GetDataResource(int resource_id,
                               void*& data,
                               size_t& data_size) = 0;

  ///
  /// Called to retrieve data for the specified |resource_id| nearest the scale
  /// factor |scale_factor|. To provide the resource data set |data| and
  /// |data_size| to the data pointer and size respectively and return true. To
  /// use the default resource data return false. The resource data will not be
  /// copied and must remain resident in memory. Use the
  /// cef_id_for_pack_resource_name() function for version-safe mapping of
  /// resource IDR names from cef_pack_resources.h to version-specific numerical
  /// |resource_id| values.
  ///
  /*--cef()--*/
  virtual bool GetDataResourceForScale(int resource_id,
                                       ScaleFactor scale_factor,
                                       void*& data,
                                       size_t& data_size) = 0;
};

#endif  // CEF_INCLUDE_CEF_RESOURCE_BUNDLE_HANDLER_H_
