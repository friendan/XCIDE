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

#ifndef CEF_INCLUDE_CEF_RESPONSE_H_
#define CEF_INCLUDE_CEF_RESPONSE_H_
#pragma once

#include <map>

#include "include/cef_base.h"

///
/// Class used to represent a web response. The methods of this class may be
/// called on any thread.
///
/*--cef(source=library,no_debugct_check)--*/
class CefResponse : public virtual CefBaseRefCounted {
 public:
  typedef std::multimap<CefString, CefString> HeaderMap;

  ///
  /// Create a new CefResponse object.
  ///
  /*--cef()--*/
  static CefRefPtr<CefResponse> Create();

  ///
  /// Returns true if this object is read-only.
  ///
  /*--cef()--*/
  virtual bool IsReadOnly() = 0;

  ///
  /// Get the response error code. Returns ERR_NONE if there was no error.
  ///
  /*--cef(default_retval=ERR_NONE)--*/
  virtual cef_errorcode_t GetError() = 0;

  ///
  /// Set the response error code. This can be used by custom scheme handlers
  /// to return errors during initial request processing.
  ///
  /*--cef()--*/
  virtual void SetError(cef_errorcode_t error) = 0;

  ///
  /// Get the response status code.
  ///
  /*--cef()--*/
  virtual int GetStatus() = 0;

  ///
  /// Set the response status code.
  ///
  /*--cef()--*/
  virtual void SetStatus(int status) = 0;

  ///
  /// Get the response status text.
  ///
  /*--cef()--*/
  virtual CefString GetStatusText() = 0;

  ///
  /// Set the response status text.
  ///
  /*--cef(optional_param=statusText)--*/
  virtual void SetStatusText(const CefString& statusText) = 0;

  ///
  /// Get the response mime type.
  ///
  /*--cef()--*/
  virtual CefString GetMimeType() = 0;

  ///
  /// Set the response mime type.
  ///
  /*--cef(optional_param=mimeType)--*/
  virtual void SetMimeType(const CefString& mimeType) = 0;

  ///
  /// Get the response charset.
  ///
  /*--cef()--*/
  virtual CefString GetCharset() = 0;

  ///
  /// Set the response charset.
  ///
  /*--cef(optional_param=charset)--*/
  virtual void SetCharset(const CefString& charset) = 0;

  ///
  /// Get the value for the specified response header field.
  ///
  /*--cef()--*/
  virtual CefString GetHeaderByName(const CefString& name) = 0;

  ///
  /// Set the header |name| to |value|. If |overwrite| is true any existing
  /// values will be replaced with the new value. If |overwrite| is false any
  /// existing values will not be overwritten.
  ///
  /*--cef(optional_param=value)--*/
  virtual void SetHeaderByName(const CefString& name,
                               const CefString& value,
                               bool overwrite) = 0;

  ///
  /// Get all response header fields.
  ///
  /*--cef()--*/
  virtual void GetHeaderMap(HeaderMap& headerMap) = 0;

  ///
  /// Set all response header fields.
  ///
  /*--cef()--*/
  virtual void SetHeaderMap(const HeaderMap& headerMap) = 0;

  ///
  /// Get the resolved URL after redirects or changed as a result of HSTS.
  ///
  /*--cef()--*/
  virtual CefString GetURL() = 0;

  ///
  /// Set the resolved URL after redirects or changed as a result of HSTS.
  ///
  /*--cef(optional_param=url)--*/
  virtual void SetURL(const CefString& url) = 0;
};

#endif  // CEF_INCLUDE_CEF_RESPONSE_H_
