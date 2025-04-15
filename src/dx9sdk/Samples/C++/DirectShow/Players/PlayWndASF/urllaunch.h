//------------------------------------------------------------------------------
// File: URLLaunch.h
//
// Desc: DirectShow sample code - helper code for launching URLs
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef URLLAUNCH_H
#define URLLAUNCH_H

HRESULT MakeEscapedURL( LPCWSTR pszInURL, LPWSTR *ppszOutURL );

HRESULT LaunchURL( LPCWSTR pszURL );

#endif  // URLLAUNCH_H
