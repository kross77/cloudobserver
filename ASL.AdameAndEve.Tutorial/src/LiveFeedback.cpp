/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
// OJ 2011
/****************************************************************************************************/
#include <iostream>

#include <boost/thread/tss.hpp>
#include <adobe/future/modal_dialog_interface.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <adobe/adam_evaluate.hpp>
#include <adobe/adam_parser.hpp>
#include <adobe/adam.hpp>
#include <adobe/algorithm/for_each.hpp>
#include <adobe/any_regular.hpp>
#include <adobe/array.hpp>
#include <adobe/dictionary.hpp>
#include <adobe/implementation/expression_parser.hpp>
#include <adobe/iomanip_asl_cel.hpp>
#include <adobe/name.hpp>
#include <adobe/virtual_machine.hpp>

using namespace std;
adobe::dialog_result_t *result;
adobe::dictionary_t input;
adobe::dictionary_t record;
adobe::dictionary_t display_state;

inline bool always_break(adobe::name_t a, const adobe::any_regular_t& new_value)
    {    
		

    std::cout << "U \'" << a.c_str() << "\' ==> "
              << adobe::begin_asl_cel << new_value << adobe::end_asl_cel
              << std::endl;
		
		return false;
}
void simple_display(adobe::dictionary_t new_value)
{


    std::cout << "A \'" << "\' ==> "
              << adobe::begin_asl_cel << new_value << adobe::end_asl_cel
              << std::endl;
}

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
			"   distance    : 15;\n"
			"	rate        : 3;\n"
			"   time        : 5;\n"
			"logic:\n"
				"    relate {\n"
				"        rate <== my_value / 1;\n"
				"        time <== my_value / 3;\n"
				"        distance <== my_value * 3;\n"
				"    }\n"
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
				"        edit_number(name: 'Value:', bind: @my_value , format: '#', alt: 'Alters the value of the slider');\n"
				"        button (name: 'OK', action: @ok, bind: @result, alt: 'Perform the command with the current settings' );\n"
				"    }\n"
				"}\n"
        ;

    // finally set up the params for the modal dialog interface call
  result = new adobe::dialog_result_t(adobe::handle_dialog(input,
                                                       record,
                                                       display_state,
                                                       adobe::dialog_display_s,
                                                       layout,
                                                       sheet,
                                                       &always_break,
                                                       icon_directory_path));
  

}
void printOut()
{ 	
	while(1){
	boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	//result->
	//simple_display(display_state);
	//cout << "return value: " << input << record << display_state << endl;
	}
}

int  main(  )
{
	boost::thread uiThread(dialog);
	boost::thread actionThread(printOut);

	cin.get();
    return 0;
} 
