#include "common.hpp"
#include "id3dsurf.h"

class CDirect3DSurface9: public IDirect3DSurface9Clone
{
public:
	CDirect3DSurface9();
	~CDirect3DSurface9();
/*	ULONG AddRef();
	HRESULT QueryInterface(REFIID iid, void **ppvObject);
	ULONG Release();*/

	// IUnknown methods
	STDMETHOD(QueryInterface) (REFIID  riid, 
														 VOID  **ppvObj);
	STDMETHOD_(ULONG,AddRef) ();
	STDMETHOD_(ULONG,Release) ();

	// IBuffer methods
	STDMETHOD(SetPrivateData)(REFGUID riid, 
														CONST VOID   *pvData, 
														DWORD   cbData, 
														DWORD   dwFlags);

	STDMETHOD(GetPrivateData)(REFGUID riid, 
														VOID   *pvData, 
														DWORD  *pcbData);

	STDMETHOD(FreePrivateData)(REFGUID riid);

	STDMETHOD(GetContainer)(REFIID riid, 
													void **ppContainer);

	STDMETHOD(GetDevice)(IDirect3DDevice9 **ppDevice);

	// IDirect3DSurface9 methods
	STDMETHOD_(D3DSURFACE_DESC, GetDesc)();

	STDMETHOD(LockRect)(D3DLOCKED_RECT  *pLockedRectData, 
											CONST RECT      *pRect, 
											DWORD            dwFlags);

	STDMETHOD(UnlockRect)();

	BOOL Create(int iWidth, int iHeight);

/*	HRESULT GetDevice(IDirect3DDevice9** ppDevice);
	HRESULT SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
	HRESULT GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
	HRESULT FreePrivateData(REFGUID refguid);
	HRESULT GetContainer(REFIID riid, void** ppContainer);

	D3DSURFACE_DESC GetDesc();
	HRESULT LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
	HRESULT UnlockRect();*/

private:
	int m_iRefCount;
	BYTE *m_pData;
	D3DSURFACE_DESC m_Desc;
};

CDirect3DSurface9::CDirect3DSurface9() : m_pData(NULL), m_iRefCount(1)
{
}

CDirect3DSurface9::~CDirect3DSurface9()
{
	delete[] m_pData;
}

BOOL CDirect3DSurface9::Create(int iWidth, int iHeight)
{
	m_pData = new BYTE[iWidth * iHeight * 4];
	if (!m_pData) return FALSE;

	m_Desc.Format = D3DFMT_A8R8G8B8;
	m_Desc.Type = D3DRTYPE_SURFACE;
	m_Desc.Usage = 0;
	m_Desc.Pool = D3DPOOL_SYSTEMMEM;
	m_Desc.Width = iWidth;
	m_Desc.Height = iHeight;
	m_Desc.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_Desc.Width = iWidth;
	m_Desc.Height = iHeight;
	return TRUE;
}

STDMETHODIMP_(ULONG) CDirect3DSurface9::AddRef()
{
	return ++m_iRefCount;
}

STDMETHODIMP CDirect3DSurface9::QueryInterface(REFIID iid, void **ppvObject)
{
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CDirect3DSurface9::Release()
{
	if (!--m_iRefCount)
	{
		delete this;
		return 0;
	}
	return m_iRefCount;
}

/////////// Dummy implementations ///////////////

STDMETHODIMP CDirect3DSurface9::SetPrivateData(REFGUID riid, CONST VOID *pvData, DWORD cbData, DWORD dwFlags)
{
	return S_OK;
}

STDMETHODIMP CDirect3DSurface9::GetPrivateData(REFGUID riid, VOID *pvData, DWORD *pcbData)
{
	return S_OK;
}

STDMETHODIMP CDirect3DSurface9::FreePrivateData(REFGUID riid)
{
	return S_OK;
}

STDMETHODIMP CDirect3DSurface9::GetContainer(REFIID riid, void **ppContainer)
{
	return S_OK;
}

STDMETHODIMP CDirect3DSurface9::GetDevice(IDirect3DDevice9 **ppDevice)
{
	return S_OK;
}

// Required implementation

STDMETHODIMP_(D3DSURFACE_DESC) CDirect3DSurface9::GetDesc()
{
	return m_Desc;
}

// Assume the entire surface is being locked.
STDMETHODIMP CDirect3DSurface9::LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
	pLockedRect->Pitch = m_Desc.Width * 4;
	pLockedRect->pBits = m_pData;
	return S_OK;
}

STDMETHODIMP CDirect3DSurface9::UnlockRect()
{
	return S_OK;
}



IDirect3DSurface9 *GetCloneSurface(int iWidth, int iHeight)
{
	CDirect3DSurface9 *pSurf = new CDirect3DSurface9;

	if (!pSurf) return NULL;
	if (!pSurf->Create(iWidth, iHeight))
	{
		delete pSurf;
		return NULL;
	}

	return (IDirect3DSurface9*)pSurf;
}
