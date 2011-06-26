/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
/****************************************************************************************************/
#include <boost/thread/tss.hpp>
#include <adobe/future/modal_dialog_interface.hpp>

#include <adobe/any_regular.hpp>
#include <adobe/name.hpp>
#include <adobe/name.hpp>

#include <utility>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/array.hpp>


using namespace std;


inline bool always_break(adobe::name_t, const adobe::any_regular_t&)
    { return true; }

void append_button_to_layout(stringstream& layout,
                             const char* name,
                             size_t index,
                             bool is_default,
                             bool is_cancel)
{
    if (name == 0)
        return;

    // NOTE (fbrereto) : For the sake of indexing the name of the action must be "bN"

    layout <<
        "button(name: '" << name << "', action: @b" << static_cast<unsigned long>(index)
        ;

    // A button cannot be both the default and the cancel button
    if (is_default)
        layout << ", default: true";
    else if (is_cancel)
        layout << ", cancel: true";

    layout <<
        ");\n"
        ;
}

void alert(const char*                    message_text,
                                   const char*                    window_name,
                                   const char*                    button_0_name,
                                   const char*                    button_1_name,
                                   const char*                    button_2_name,
                                   const char*                    checkbox_name,
                                   const boost::filesystem::path& icon_path,
                                   size_t                    default_button_index,
                                   size_t                    cancel_button_index)
{
    if ((button_0_name || button_1_name || button_2_name) == false)
        return;// make_pair<const char*, bool>(0, false);

    stringstream       sheet;
    stringstream       layout;
    boost::filesystem::path icon_directory_path;

    // The sheet for the alert dialog
    sheet <<
			"sheet my_sheet\n"
			"{\n"
			"interface:\n"
			"   my_value: 42;\n"
			"output:\n"
			"   result <== { value: my_value };\n"
			"}\n"
    ;

    // Start by filling out the header for the layout of the alert
    layout <<
				"layout my_dialog\n"
				"{\n"
				"    view dialog(name: localize(\"<xstr id='my_dialog_name'>My Dialog</xstr>\"))\n"
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
	alert(  "There was an error.","Alert","OK",0,0,0,boost::filesystem::path(),0,1);
	cin.get();
    return 0;
} 

