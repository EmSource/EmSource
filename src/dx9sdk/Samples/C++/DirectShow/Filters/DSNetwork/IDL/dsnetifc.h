
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Oct 03 19:33:29 2002
 */
/* Compiler settings for d:\DX\multimedia\Directx\dxsdk\samples\cpp\DirectShow\Filters\DSNetwork\idl\dsnetifc.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __dsnetifc_h__
#define __dsnetifc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMulticastConfig_FWD_DEFINED__
#define __IMulticastConfig_FWD_DEFINED__
typedef interface IMulticastConfig IMulticastConfig;
#endif 	/* __IMulticastConfig_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_dsnetifc_0000 */
/* [local] */ 

// {CE3B76CB-9540-48fa-9974-69A625D478E3}
DEFINE_GUID(CLSID_DSNetSend,
0xce3b76cb, 0x9540, 0x48fa, 0x99, 0x74, 0x69, 0xa6, 0x25, 0xd4, 0x78, 0xe3);
// {319F0815-ACEF-45fe-B497-A2E5D90A69D7}
DEFINE_GUID(CLSID_DSNetReceive,
0x319f0815, 0xacef, 0x45fe, 0xb4, 0x97, 0xa2, 0xe5, 0xd9, 0xa, 0x69, 0xd7);
// {03EC9C19-13C4-43d7-B183-895CB89E761C}
DEFINE_GUID(CLSID_IPMulticastSendProppage,
0x3ec9c19, 0x13c4, 0x43d7, 0xb1, 0x83, 0x89, 0x5c, 0xb8, 0x9e, 0x76, 0x1c);
// {DC01D8AD-2BF8-4914-A15E-231A96C04B0A}
DEFINE_GUID(CLSID_IPMulticastRecvProppage,
0xdc01d8ad, 0x2bf8, 0x4914, 0xa1, 0x5e, 0x23, 0x1a, 0x96, 0xc0, 0x4b, 0xa);



extern RPC_IF_HANDLE __MIDL_itf_dsnetifc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dsnetifc_0000_v0_0_s_ifspec;

#ifndef __IMulticastConfig_INTERFACE_DEFINED__
#define __IMulticastConfig_INTERFACE_DEFINED__

/* interface IMulticastConfig */
/* [uuid][object] */ 


EXTERN_C const IID IID_IMulticastConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB42CC8-D32C-4f73-9267-C114DA470378")
    IMulticastConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetNetworkInterface( 
            /* [in] */ ULONG ulNIC) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNetworkInterface( 
            /* [out] */ ULONG *pNIC) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMulticastGroup( 
            /* [in] */ ULONG ulIP,
            /* [in] */ USHORT usPort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMulticastGroup( 
            /* [out] */ ULONG *pIP,
            /* [out] */ USHORT *pPort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMulticastConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMulticastConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMulticastConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMulticastConfig * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetNetworkInterface )( 
            IMulticastConfig * This,
            /* [in] */ ULONG ulNIC);
        
        HRESULT ( STDMETHODCALLTYPE *GetNetworkInterface )( 
            IMulticastConfig * This,
            /* [out] */ ULONG *pNIC);
        
        HRESULT ( STDMETHODCALLTYPE *SetMulticastGroup )( 
            IMulticastConfig * This,
            /* [in] */ ULONG ulIP,
            /* [in] */ USHORT usPort);
        
        HRESULT ( STDMETHODCALLTYPE *GetMulticastGroup )( 
            IMulticastConfig * This,
            /* [out] */ ULONG *pIP,
            /* [out] */ USHORT *pPort);
        
        END_INTERFACE
    } IMulticastConfigVtbl;

    interface IMulticastConfig
    {
        CONST_VTBL struct IMulticastConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMulticastConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMulticastConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMulticastConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMulticastConfig_SetNetworkInterface(This,ulNIC)	\
    (This)->lpVtbl -> SetNetworkInterface(This,ulNIC)

#define IMulticastConfig_GetNetworkInterface(This,pNIC)	\
    (This)->lpVtbl -> GetNetworkInterface(This,pNIC)

#define IMulticastConfig_SetMulticastGroup(This,ulIP,usPort)	\
    (This)->lpVtbl -> SetMulticastGroup(This,ulIP,usPort)

#define IMulticastConfig_GetMulticastGroup(This,pIP,pPort)	\
    (This)->lpVtbl -> GetMulticastGroup(This,pIP,pPort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMulticastConfig_SetNetworkInterface_Proxy( 
    IMulticastConfig * This,
    /* [in] */ ULONG ulNIC);


void __RPC_STUB IMulticastConfig_SetNetworkInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMulticastConfig_GetNetworkInterface_Proxy( 
    IMulticastConfig * This,
    /* [out] */ ULONG *pNIC);


void __RPC_STUB IMulticastConfig_GetNetworkInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMulticastConfig_SetMulticastGroup_Proxy( 
    IMulticastConfig * This,
    /* [in] */ ULONG ulIP,
    /* [in] */ USHORT usPort);


void __RPC_STUB IMulticastConfig_SetMulticastGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMulticastConfig_GetMulticastGroup_Proxy( 
    IMulticastConfig * This,
    /* [out] */ ULONG *pIP,
    /* [out] */ USHORT *pPort);


void __RPC_STUB IMulticastConfig_GetMulticastGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMulticastConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dsnetifc_0010 */
/* [local] */ 

#define DECLARE_IMULTICASTCONFIG();\
virtual STDMETHODIMP SetNetworkInterface (ULONG) ;\
virtual STDMETHODIMP GetNetworkInterface (ULONG *) ;\
virtual STDMETHODIMP SetMulticastGroup (ULONG, USHORT) ;\
virtual STDMETHODIMP GetMulticastGroup (ULONG *, USHORT*) ;


extern RPC_IF_HANDLE __MIDL_itf_dsnetifc_0010_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dsnetifc_0010_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


