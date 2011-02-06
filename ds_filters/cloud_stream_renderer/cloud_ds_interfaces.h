#if 0
#ifndef _CLOUD_DS_INTERFACES_H_
#define _CLOUD_DS_INTERFACES_H_

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
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


#ifndef __ICloudInetControl_FWD_DEFINED__
#define __ICloudInetControl_FWD_DEFINED__
typedef interface ICloudInetControl ICloudInetControl;
#endif 	/* __ICoudInetControl_FWD_DEFINED__ */


#ifndef __ICloudInetControl_INTERFACE_DEFINED__
#define __ICloudInetControl_INTERFACE_DEFINED__



/* interface ICoudInetControl */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_ICloudInetControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    MIDL_INTERFACE("80AE3F22-17DE-4d6c-BC3E-F2A38AFC53CC")
    ICloudInetControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAddress( 
            /* [in] */ LPCOLESTR pszAddress,/*[in]*/ int port) = 0;
    };
    
#else 	/* C style interface */

    typedef struct ICloudInetControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICloudInetControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICloudInetControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICloudInetControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAddress )( 
            ICloudInetControl * This,
            /* [in] */ LPCOLESTR pszAddress,int port);
        
        END_INTERFACE
    } ICloudInetControlVtbl;

    interface ICloudInetControl
    {
        CONST_VTBL struct ICloudInetControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICloudInetControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICloudInetControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICloudInetControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICloudInetControl_SetAddress(This,pszFileName,pmt)	\
    ( (This)->lpVtbl -> SetAddress(This,pszFileName,pmt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */

#endif 	/* __ICloudInetControl_INTERFACE_DEFINED__ */


#endif /* _CLOUD_DS_INTERFACES_H_ */
#endif