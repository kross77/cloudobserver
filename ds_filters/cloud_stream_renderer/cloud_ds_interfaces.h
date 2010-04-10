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


#ifndef __ICoudInetControl_FWD_DEFINED__
#define __ICoudInetControl_FWD_DEFINED__
typedef interface ICoudInetControl ICoudInetControl;
#endif 	/* __ICoudInetControl_FWD_DEFINED__ */


#ifndef __ICoudInetControl_INTERFACE_DEFINED__
#define __ICoudInetControl_INTERFACE_DEFINED__



/* interface ICoudInetControl */
/* [unique][uuid][object][local] */ 


EXTERN_C const IID IID_ICoudInetControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    MIDL_INTERFACE("80AE3F22-17DE-4d6c-BC3E-F2A38AFC53CC")
    ICoudInetControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAddress( 
            /* [in] */ LPCOLESTR pszAddress) = 0;
    };
    
#else 	/* C style interface */

    typedef struct ICoudInetControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoudInetControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoudInetControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoudInetControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAddress )( 
            ICoudInetControl * This,
            /* [in] */ LPCOLESTR pszAddress);
        
        END_INTERFACE
    } ICoudInetControlVtbl;

    interface ICoudInetControl
    {
        CONST_VTBL struct ICoudInetControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoudInetControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICoudInetControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICoudInetControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICoudInetControl_SetAddress(This,pszFileName,pmt)	\
    ( (This)->lpVtbl -> SetAddress(This,pszFileName,pmt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */

#endif 	/* __ICoudInetControl_INTERFACE_DEFINED__ */


#endif /* _CLOUD_DS_INTERFACES_H_ */
