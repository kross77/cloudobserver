/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
// OJ 2011
/****************************************************************************************************/
#include <boost/thread/tss.hpp>
#include <adobe/future/modal_dialog_interface.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;

inline bool always_break(adobe::name_t, const adobe::any_regular_t&)
    { return true; }

void dialog()
{
    stringstream       sheet;
    stringstream       layout;
    boost::filesystem::path icon_directory_path;

    // The sheet for the dialog
    sheet <<
			"sheet my_sheet\n"
			"{\n"
			"interface:\n"
			"   my_value: 42;\n"
			"output:\n"
			"   result <== { value: my_value };\n"
			"}\n"
    ;

    // the layout
    layout <<
				"layout my_dialog\n"
				"{\n"
				"    view dialog(name: 'My Dialog')\n"
				"    {\n"
				"        slider(bind: @my_value, format: {first: 0, last: 100});\n"
				"        edit_number(name: 'Value:', bind: @my_value, format: '#', alt: 'Alters the value of the slider');\n"
				"        button (items: [\n"
				"                           { name: 'OK', action: @ok, bind: @result, alt: 'Perform the command with the current settings' },\n"
				"                           { name: 'Reset', action: @reset, modifiers: @opt, alt: 'Reset the dialog settings' }\n"
				"                       ]);\n"
				"    }\n"
				"}\n"
        ;

    // finally set up the params for the modal dialog interface call
    adobe::dialog_result_t result(adobe::handle_dialog(adobe::dictionary_t(),
                                                       adobe::dictionary_t(),
                                                       adobe::dictionary_t(),
                                                       adobe::dialog_display_s,
                                                       layout,
                                                       sheet,
                                                       &always_break,
                                                       icon_directory_path));

    int is_checked(result.command_m[adobe::static_name_t("value")].cast<int>());
	cout << "return value: " << is_checked << endl;
}

int  main(  )
{
	dialog();
	cin.get();
    return 0;
} 
