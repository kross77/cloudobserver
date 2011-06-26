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

#include <boost/filesystem/path.hpp>
#include <boost/array.hpp>


//using namespace adobe;

/****************************************************************************************************/

inline bool always_break(adobe::name_t, const adobe::any_regular_t&)
    { return true; }

/****************************************************************************************************/

void append_button_to_layout(std::stringstream& layout,
                             const char* name,
                             std::size_t index,
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
                                   std::size_t                    default_button_index,
                                   std::size_t                    cancel_button_index)
{
    if ((button_0_name || button_1_name || button_2_name) == false)
        return;// std::make_pair<const char*, bool>(0, false);

    std::stringstream       sheet;
    std::stringstream       layout;
    boost::filesystem::path icon_directory_path;

    // The sheet for the alert dialog
    sheet <<
        "sheet alert_sheet\n"
        "{\n"
        "interface:\n"
        "   checkbox_value: false;\n"
        "output:\n"
        "   result <== { checkbox_value: checkbox_value };\n"
        "}\n"
    ;

    // Start by filling out the header for the layout of the alert
    layout <<
        "layout alert_layout\n"
        "{\n"
        "   view dialog(name: '" << window_name << "', placement: place_row, spacing: 10)\n"
        "   {\n";

    if (icon_path != boost::filesystem::path())
    {
        icon_directory_path = icon_path.branch_path();

        layout <<
            "       label_t(image: '" << icon_path.leaf() << "')\n"
        ;
    }

    layout <<
        "       column()\n"
        "       {\n"
        "           static_text(name:'" << message_text << "', horizontal: align_fill, characters: 25);\n"
        ;

    // add the checkbox if we have a name for one
    if (checkbox_name)
    {
        layout <<
            "checkbox(name: '" << checkbox_name << "', bind: @checkbox_value);\n"
            ;
    }

    // add the button set
    layout <<
        "row(horizontal: align_right)\n"
        "{\n"
        ;

    // add the buttons in *reverse* order, so the first is rightmost
    append_button_to_layout(layout, button_2_name, 2, default_button_index == 2, cancel_button_index == 2);
    append_button_to_layout(layout, button_1_name, 1, default_button_index == 1, cancel_button_index == 1);
    append_button_to_layout(layout, button_0_name, 0, default_button_index == 0, cancel_button_index == 0);

    // close out the rest of the layout
    layout << 
        "           }\n" // row
        "       }\n"     // column
        "   }\n"         // dialog
        "}\n"            // layout
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

    bool is_checked(result.command_m[adobe::static_name_t("checkbox_value")].cast<bool>());
}

int  main(  )
{
	alert(  "There were no errors at all=) .","Alert","OK",0,0,0,boost::filesystem::path(),0,1);
	std::cin.get();
    return 0;
} 

