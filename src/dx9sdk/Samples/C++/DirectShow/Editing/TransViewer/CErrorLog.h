// ---------------------------------------------------------------------------
// File: CErrorLog.h
// 
// CErrorLog: Logs DES rendering errors that occur at run-time,
//            using the IAMErrorLog interface 
//      
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#ifndef _CERRORLOG_H
#define _CERRORLOG_H


// IAMErrorLogEx Interface

// Note: The IAMErrorLog interface does not define a way to enable/disable
// error logging. You can use IAMSetErrorLog::put_ErrorLog(0), but for
// convenience the CErrorLog object supports a custom interface, IAMErrorLogEx,
// with a single method, ::Enable(bool)


#ifdef __cplusplus
extern "C" {
#endif

//
// IAMErrorLogEx GUID
//
// {92406902-98A6-42dc-B850-88C13D5C84E7}
DEFINE_GUID(IID_IAMErrorLogEx, 
0x92406902, 0x98a6, 0x42dc, 0xb8, 0x50, 0x88, 0xc1, 0x3d, 0x5c, 0x84, 0xe7);


//
// IAMErrorLogEx
//
DECLARE_INTERFACE_(IAMErrorLogEx, IUnknown) {

    STDMETHOD(Enable)     (THIS_ bool fEnable) PURE;
};


#ifdef __cplusplus
}
#endif


extern HWND g_hwnd;  // Application window

// CErrorLog: Error logging class
//
// Notes:
// To create this object, use the static CreateErrorLog() method. It cannot 
// be created with CoCreateInstance; it does not have a CLSID.
//
// The IAMErrorLog::LogError method is called by the DES render engine (essentially
// a callback). To reduce latency (and chance of deadlock), the CErrorLog object 
// copies the error msg and posts it to the application's message loop. 

class CErrorLog : public IAMErrorLog, public IAMErrorLogEx
{
private:
    HWND     m_hwnd;          // where to send messages
    bool     m_fEnabled;      // Is logging enabled?

    // ctor is private - use CreateErrorLog() instead
    CErrorLog(HWND hwnd) { 
        m_lRef = 0; 
        m_hwnd = hwnd;
        m_fEnabled = true;
    }

protected:
    long    m_lRef; // Reference count.

public:

    ~CErrorLog() {
    }

    // Static method to create a new instance - ensures proper ref counting.
    static HRESULT CreateErrorLog(IAMErrorLog **ppErrLog)
    {
        CErrorLog *err = new CErrorLog(g_hwnd);

        if (err == 0) {
            return E_OUTOFMEMORY;
        }
        return err->QueryInterface(IID_IAMErrorLog, (void**)ppErrLog);
    }


    // IUnknown
    STDMETHOD(QueryInterface(REFIID, void**));
    STDMETHOD_(ULONG, AddRef());
    STDMETHOD_(ULONG, Release());

    // IAMErrorLog
    STDMETHOD(LogError(LONG, BSTR, LONG, HRESULT, VARIANT*));

    // IAMErrorLogEx
    STDMETHODIMP Enable(bool fEnable) { 
        m_fEnabled = fEnable; 
        return S_OK;
    }

};


#endif // _CERRORLOG_H