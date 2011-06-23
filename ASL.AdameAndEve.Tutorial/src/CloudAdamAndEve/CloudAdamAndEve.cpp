/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
/****************************************************************************************************/

#include "express_viewer.hpp"
#include "report_exception.hpp"
#include <adobe/future/widgets/headers/display.hpp>
#include <adobe/future/windows_cast.hpp>
#include <adobe/future/widgets/headers/widget_utils.hpp>

#include <adobe/xstring.hpp>

#include <boost/filesystem/convenience.hpp>

#include <adobe/future/behavior.hpp>

#define WIN32_LEAN_AND_MEAN

/*************************************************************************************************/
#if defined(BOOST_MSVC) && defined(BOOST_THREAD_USE_LIB)
namespace boost {
	void tss_cleanup_implemented()
{ }
}
#endif
/******************************************* namespace adobe ******************************************************/
namespace adobe {

void setup_main_window( application_t* app )
{
    adobe::get_main_display().set_root(::CreateWindowExW(NULL,
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL, NULL, NULL, NULL, NULL,
                                         NULL,
                                         NULL,
                                         NULL));
}

bool os_initialize( application_t* app )
{

    //
    // Now we need to get a directory from the command line name.
    //
    boost::filesystem::path directory( "/", boost::filesystem::native );

    //
    // Tell the application...
    //
    app->set_resource_directory( directory.branch_path() );

    setup_main_window( app );

    return true;
}

void os_mainloop(adobe::application_t& app)
{
    //
    // This is just the standard Win32 message pump.
    //
    MSG msg;

    while ( GetMessage( &msg, 0, 0, 0 ) )
    {
        try
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        catch ( ... )
        {
            adobe::report_exception();
        }

        adobe::general_deferred_proc_queue()();
    }
}

void os_end_mainloop()
{
    //
    // This is just the standard Win32 quit message.
    //
    ::PostQuitMessage(0);
}

}
/******************************************* namespace adobe ******************************************************/

int  main(  )
{
    try
    {
        adobe::application_t* theApp = adobe::application_t::getInstance();

        if( theApp ) theApp->run();
    }
    catch( ... )
    {
        adobe::report_exception();
    }

    return 0;
} 

