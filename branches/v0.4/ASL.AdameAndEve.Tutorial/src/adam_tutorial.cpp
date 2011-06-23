/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/
// OJ 2011
/*************************************************************************************************/
//#define NO_STDIO_REDIRECT
#define _SCL_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#define ADOBE_STD_SERIALIZATION

#include <adobe/config.hpp>

#include <iostream>
#include <map>

#include <boost/version.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
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
/****************************************************************************************************/

namespace bfs = boost::filesystem;

/****************************************************************************************************/

typedef map<adobe::name_t, adobe::any_regular_t> cell_set_t;

/****************************************************************************************************/

void simple_display(cell_set_t::value_type& cell_m, const adobe::any_regular_t& new_value)
{
    cell_m.second = new_value;

    cout << "U \'" << cell_m.first.c_str() << "\' ==> "
              << adobe::begin_asl_cel << cell_m.second << adobe::end_asl_cel
              << endl;
}
  

/****************************************************************************************************/

void stream_cell_state(const cell_set_t::value_type& cell)
{
    cout << "   '" << cell.first.c_str() << "': "
              << adobe::begin_asl_cel << cell.second << adobe::end_asl_cel
              << endl;
}

/****************************************************************************************************/

adobe::dictionary_t parse_input_dictionary(const bfs::path& input_path)
{
	string path_str = boost::lexical_cast<string>(input_path);
		
    ifstream            input_stream(path_str.c_str());
    adobe::array_t           token_stream;
    adobe::virtual_machine_t vm;

    if (!adobe::expression_parser(input_stream,
                                  adobe::line_position_t("input_dictionary")).is_expression(token_stream))
        return adobe::dictionary_t();

    vm.evaluate(token_stream);

    const adobe::dictionary_t result(vm.back().cast<adobe::dictionary_t>());

    vm.pop_back();

    cout << "--" << endl
              << "Initializing sheet with the following input dictionary: "
              << adobe::begin_asl_cel << result << adobe::end_asl_cel
              << endl
              << "--" << endl;

    return result;
}

/****************************************************************************************************/

struct sheet_tracker
{
    sheet_tracker(const bfs::path& sheet_path,
                  const bfs::path& input_path) :
        callbacks_m(adobe::bind_to_sheet(sheet_m))
    {
        //  attach the VM to the sheet.
        sheet_m.machine_m.set_variable_lookup(boost::bind(&adobe::sheet_t::get, &sheet_m, _1));
    
        string     sheet_path_str = boost::lexical_cast<string>(sheet_path);

		ifstream   sheet_stream(sheet_path_str.c_str());

        callbacks_m.add_cell_proc_m = 
            boost::bind(&sheet_tracker::add_cell_trap, boost::ref(*this), 
                        callbacks_m.add_cell_proc_m, _1, _2, _3, _4);
        callbacks_m.add_interface_proc_m =
            boost::bind(&sheet_tracker::add_interface_trap, boost::ref(*this), 
                        callbacks_m.add_interface_proc_m, _1, _2, _3, _4, _5, _6);

        if (!sheet_stream.is_open())
            cerr << "Could not open \"" << sheet_path_str << "\"!\n";

        // set up adam sheet
        adobe::parse(sheet_stream,
                     adobe::line_position_t("property model sheet"),
                     callbacks_m);

        sheet_m.set(parse_input_dictionary(input_path));

        sheet_m.update();
    }

    void loop();

private:
    sheet_tracker();                                    // unimplemented
    sheet_tracker(const sheet_tracker&);                // unimplemented
    sheet_tracker& operator = (const sheet_tracker&);   // unimplemented

    void add_cell_trap( adobe::adam_callback_suite_t::add_cell_proc_t   original,
                        adobe::adam_callback_suite_t::cell_type_t       type,
                        adobe::name_t                                   cell_name,
                        const adobe::line_position_t&                   position,
                        const adobe::array_t&                           expr_or_init);

    void add_interface_trap(adobe::adam_callback_suite_t::add_interface_proc_t  original,
                            adobe::name_t                                       cell_name,
                            bool                                                linked,
                            const adobe::line_position_t&                       position1,
                            const adobe::array_t&                               initializer,
                            const adobe::line_position_t&                       position2,
                            const adobe::array_t&                               expression);

    adobe::sheet_t                          sheet_m;
    adobe::adam_callback_suite_t            callbacks_m;
    map<adobe::name_t, adobe::any_regular_t> cell_set_m;
};

/****************************************************************************************************/

adobe::name_t cell_type_to_name(adobe::adam_callback_suite_t::cell_type_t type)
{
    switch (type)
    {
        case adobe::adam_callback_suite_t::input_k:     
            return adobe::static_name_t("input");       break;
        case adobe::adam_callback_suite_t::output_k:    
            return adobe::static_name_t("output");      break;
        case adobe::adam_callback_suite_t::constant_k:  
            return adobe::static_name_t("constant");    break;
        case adobe::adam_callback_suite_t::logic_k:     
            return adobe::static_name_t("logic");       break;
        case adobe::adam_callback_suite_t::invariant_k: 
            return adobe::static_name_t("invariant");   break;
        default: 
            return adobe::static_name_t("unknown"); break;
    }
}

/****************************************************************************************************/

void sheet_tracker::add_cell_trap(  adobe::adam_callback_suite_t::add_cell_proc_t   original,
                                    adobe::adam_callback_suite_t::cell_type_t       type,
                                    adobe::name_t                                   cell_name,
                                    const adobe::line_position_t&                   position,
                                    const adobe::array_t&                           expr_or_init)
{
    original(type, cell_name, position, expr_or_init, string(), string());

    cout << "A \'" << cell_name.c_str() << "\' (" << cell_type_to_name(type) << ")" << endl;

    if (cell_type_to_name(type) == adobe::static_name_t("output"))
        cell_set_m[cell_name] = adobe::any_regular_t();
}

/****************************************************************************************************/

void sheet_tracker::add_interface_trap( adobe::adam_callback_suite_t::add_interface_proc_t  original,
                                        adobe::name_t                                       cell_name,
                                        bool                                                linked,
                                        const adobe::line_position_t&                       position1,
                                        const adobe::array_t&                               initializer,
                                        const adobe::line_position_t&                       position2,
                                        const adobe::array_t&                               expression)
{
    original(cell_name, linked, position1, initializer, position2, expression,
             string(), string());

    cout << "A \'" << cell_name.c_str() << "\' (interface)" <<  endl;

    cell_set_m[cell_name] = adobe::any_regular_t();
}

/****************************************************************************************************/

void sheet_tracker::loop()
{
    string              cell_name_buffer;
    vector<char>        new_value_buffer;

    cell_name_buffer.reserve(1024);
    new_value_buffer.reserve(1024);
    new_value_buffer.resize(1); 

	sheet_m.update();
    for(cell_set_t::iterator iter=cell_set_m.begin(), end = cell_set_m.end(); iter!= end; ++iter)
    {
        sheet_m.monitor_value(iter->first, 	boost::bind(&simple_display, boost::ref(*iter), _1));
    }

    while (true)
    {
        cout << "--" << endl;

        sheet_m.update();

        cout << "sheet:" << endl;
        adobe::for_each(cell_set_m, stream_cell_state);
        cout << "Enter in the name of a cell for which you would like to change the value: ";
        cin.getline(&cell_name_buffer[0], 1024);

        if (cell_name_buffer[0] == 0)
            break;

        cout << "Enter in the new value for cell \'" << &cell_name_buffer[0] << "\': ";
        cin.getline(&new_value_buffer[0], 1024);

        if (new_value_buffer[0] == 0)
            break;

        adobe::any_regular_t new_value(sheet_m.inspect(adobe::parse_adam_expression(&new_value_buffer[0])));

        adobe::name_t cell(&cell_name_buffer[0]);

        cout << "Setting cell " << cell << " to " << adobe::begin_asl_cel << new_value << adobe::end_asl_cel << endl;

        sheet_m.set(cell, new_value);
    }
}

/****************************************************************************************************/

int main(int argc, char* argv[])
{
    try
    {
        cout << "Adobe Adam Tutorial" << endl;
        cout << "Compiler: " << BOOST_COMPILER << endl;
        cout << "     ASL: v" << ADOBE_VERSION_MAJOR << "." << ADOBE_VERSION_MINOR << "." 
                  << ADOBE_VERSION_SUBMINOR << endl;
        cout << "   Boost: v" << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000 
                  << "." << BOOST_VERSION % 100 << endl;
        cout << "--" << endl;

        string sheet_pathname(argc > 1 ? (argv[1]) : ("assets/adam_tutorial_default.adm"));
        bfs::path   sheet_filepath(sheet_pathname.c_str(), bfs::native);
        string input_pathname(argc > 2 ? (argv[2]) : ("assets/adam_tutorial_input.cel"));
        bfs::path   input_filepath(input_pathname.c_str(), bfs::native);

        sheet_tracker(sheet_filepath, input_filepath).loop();
    }
    catch (const exception& error)
    {
        cerr << "Exception: " << error.what() << "\n";
    }
    catch (...)
    {
        cerr << "Unknown Exception\n";
    }

    cout << "Bye!" << endl;
}
