#pragma once
#include "InputPin.h"
#include "cloud_ctrl_h.h"
#include "cloud_ds_interfaces.h"
//We must implement 2 functions CheckMediaType and DoRenderSample
class CFilter : public CBaseRenderer, ICloudInetControl
{
//	friend class CInputPin;

public:
	//Function create one more instance for this filter. Specified in Called by system
	static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

	//Each filter is COM oject and must implement IUnknown interface
	DECLARE_IUNKNOWN;

	//method is called when try to connect input pin and check supporting media type 
	//for it
	HRESULT CheckMediaType(const CMediaType *pmt);
	
	HRESULT DoRenderSample(IMediaSample *pMediaSample);

	// Filter Start/Stop control
	HRESULT OnStartStreaming();
	HRESULT OnStopStreaming();

	HRESULT STDMETHODCALLTYPE SetAddress(/* [in] */ OLECHAR* pszAddress,int port);

	int				m_portNumber;		// Server Connection Port
	OLECHAR*		m_serverAddr;		// Server Address
	int				m_socket;
	sockaddr_in     ConnectionInfo;

private:
	// Overriden to say what interfaces we support where
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

	//Privite constructor. All object must be created from CreateInstance function
	CFilter(TCHAR *tszName, LPUNKNOWN punk, HRESULT *phr);
	~CFilter();
	
	//Server connection functions 
	int		Connect (OLECHAR* hostAddress, int port);
	void	Disconnect();
	int		ErrorInfo();
	
	CInputPin       m_InputPin;			// IPin based interfaces		

	
};

