// dear imgui, v1.75 WIP
// (demo code)

// Message to the person tempted to delete this file when integrating Dear ImGui into their code base:
// Do NOT remove this file from your project! Think again! It is the most useful reference code that you and other coders
// will want to refer to and call. Have the ImGui::ShowDemoWindow() function wired in an always-available debug menu of
// your game/app! Removing this file from your project is hindering access to documentation for everyone in your team,
// likely leading you to poorer usage of the library.
// Everything in this file will be stripped out by the linker if you don't call ImGui::ShowDemoWindow().
// If you want to link core Dear ImGui in your shipped builds but want an easy guarantee that the demo will not be linked,
// you can setup your imconfig.h with #define IMGUI_DISABLE_DEMO_WINDOWS and those functions will be empty.
// In other situation, whenever you have Dear ImGui available you probably want this to be available for reference.
// Thank you,
// -Your beloved friend, imgui_demo.cpp (that you won't delete)

// Message to beginner C/C++ programmers about the meaning of the 'static' keyword:
// In this demo code, we frequently we use 'static' variables inside functions. A static variable persist across calls, so it is
// essentially like a global variable but declared inside the scope of the function. We do this as a way to gather code and data
// in the same place, to make the demo source code faster to read, faster to write, and smaller in size.
// It also happens to be a convenient way of storing simple UI related information as long as your function doesn't need to be
// reentrant or used in multiple threads. This might be a pattern you will want to use in your code, but most of the real data
// you would be editing is likely going to be stored outside your functions.

// The Demo code is this file is designed to be easy to copy-and-paste in into your application!
// Because of this:
// - We never omit the ImGui:: namespace when calling functions, even though most of our code is already in the same namespace.
// - We try to declare static variables in the local scope, as close as possible to the code using them.
// - We never use any of the helpers/facilities used internally by dear imgui, unless it has been exposed in the public API (imgui.h).
// - We never use maths operators on ImVec2/ImVec4. For other imgui sources files, they are provided by imgui_internal.h w/ IMGUI_DEFINE_MATH_OPERATORS,
//   for your own sources file they are optional and require you either enable those, either provide your own via IM_VEC2_CLASS_EXTRA in imconfig.h.
//   Because we don't want to assume anything about your support of maths operators, we don't use them in imgui_demo.cpp.

/*

Index of this file:

// [SECTION] Forward Declarations, Helpers
// [SECTION] Demo Window / ShowDemoWindow()
// [SECTION] About Window / ShowAboutWindow()
// [SECTION] Style Editor / ShowStyleEditor()
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
// [SECTION] Example App: Auto Resize / ShowExampleAppAutoResize()
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
// [SECTION] Example App: Simple Overlay / ShowExampleAppSimpleOverlay()
// [SECTION] Example App: Manipulating Window Titles / ShowExampleAppWindowTitles()
// [SECTION] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()

*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#endif
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wold-style-cast"             // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"    // warning : 'xx' is deprecated: The POSIX name for this item.. // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"   // warning : cast to 'void *' from smaller integer type 'int'
#pragma clang diagnostic ignored "-Wformat-security"            // warning : warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"      // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wunused-macros"              // warning : warning: macro is not used                         // we define snprintf/vsnprintf on Windows so they are available, but not always used.
#if __has_warning("-Wzero-as-null-pointer-constant")
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning : zero as null pointer constant                  // some standard header variations use #define NULL 0
#endif
#if __has_warning("-Wdouble-promotion")
#pragma clang diagnostic ignored "-Wdouble-promotion"           // warning: implicit conversion from 'float' to 'double' when passing argument to function  // using printf() is a misery with this as C++ va_arg ellipsis changes float to double.
#endif
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"          // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"                      // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"          // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"              // warning : format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"             // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"                   // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wmisleading-indentation"       // [__GNUC__ >= 6] warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#endif

// Play it nice with Windows users. Notepad in 2017 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif

//-----------------------------------------------------------------------------
// [SECTION] Forward Declarations, Helpers
//-----------------------------------------------------------------------------

#if !defined(IMGUI_DISABLE_DEMO_WINDOWS)

// Forward Declarations
static void ShowExampleAppDocuments(bool* p_open);
static void ShowExampleAppMainMenuBar();
static void ShowExampleAppConsole(bool* p_open);
static void ShowExampleAppLog(bool* p_open);
static void ShowExampleAppLayout(bool* p_open);
static void ShowExampleAppPropertyEditor(bool* p_open);
static void ShowExampleAppLongText(bool* p_open);
static void ShowExampleAppAutoResize(bool* p_open);
static void ShowExampleAppConstrainedResize(bool* p_open);
static void ShowExampleAppSimpleOverlay(bool* p_open);
static void ShowExampleAppWindowTitles(bool* p_open);
static void ShowExampleAppCustomRendering(bool* p_open);
static void ShowExampleMenuFile();

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.txt)
static void HelpMarker(const char* desc)
{
    im::TextDisabled("(?)");
    if (im::IsItemHovered())
    {
        im::BeginTooltip();
        im::PushTextWrapPos(im::GetFontSize() * 35.0f);
        im::TextUnformatted(desc);
        im::PopTextWrapPos();
        im::EndTooltip();
    }
}

// Helper to display basic user controls.
void im::ShowUserGuide()
{
    ImGuiIO& io = im::GetIO();
    im::BulletText("Double-click on title bar to collapse window.");
    im::BulletText("Click and drag on lower corner to resize window\n(double-click to auto fit window to its contents).");
    im::BulletText("CTRL+Click on a slider or drag box to input value as text.");
    im::BulletText("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
    if (io.FontAllowUserScaling)
        im::BulletText("CTRL+Mouse Wheel to zoom window contents.");
    im::BulletText("While inputing text:\n");
    im::Indent();
    im::BulletText("CTRL+Left/Right to word jump.");
    im::BulletText("CTRL+A or double-click to select all.");
    im::BulletText("CTRL+X/C/V to use clipboard cut/copy/paste.");
    im::BulletText("CTRL+Z,CTRL+Y to undo/redo.");
    im::BulletText("ESCAPE to revert.");
    im::BulletText("You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
    im::Unindent();
    im::BulletText("With keyboard navigation enabled:");
    im::Indent();
    im::BulletText("Arrow keys to navigate.");
    im::BulletText("Space to activate a widget.");
    im::BulletText("Return to input text into a widget.");
    im::BulletText("Escape to deactivate a widget, close popup, exit child window.");
    im::BulletText("Alt to jump to the menu layer of a window.");
    im::BulletText("CTRL+Tab to select a window.");
    im::Unindent();
}

//-----------------------------------------------------------------------------
// [SECTION] Demo Window / ShowDemoWindow()
//-----------------------------------------------------------------------------
// - ShowDemoWindowWidgets()
// - ShowDemoWindowLayout()
// - ShowDemoWindowPopups()
// - ShowDemoWindowColumns()
// - ShowDemoWindowMisc()
//-----------------------------------------------------------------------------

// We split the contents of the big ShowDemoWindow() function into smaller functions (because the link time of very large functions grow non-linearly)
static void ShowDemoWindowWidgets();
static void ShowDemoWindowLayout();
static void ShowDemoWindowPopups();
static void ShowDemoWindowColumns();
static void ShowDemoWindowMisc();

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does. You may then search for keywords in the code when you are interested by a specific feature.
void im::ShowDemoWindow(bool* p_open)
{
    IM_ASSERT(im::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup

    // Examples Apps (accessible from the "Examples" menu)
    static bool show_app_documents = false;
    static bool show_app_main_menu_bar = false;
    static bool show_app_console = false;
    static bool show_app_log = false;
    static bool show_app_layout = false;
    static bool show_app_property_editor = false;
    static bool show_app_long_text = false;
    static bool show_app_auto_resize = false;
    static bool show_app_constrained_resize = false;
    static bool show_app_simple_overlay = false;
    static bool show_app_window_titles = false;
    static bool show_app_custom_rendering = false;

    if (show_app_documents)           ShowExampleAppDocuments(&show_app_documents);
    if (show_app_main_menu_bar)       ShowExampleAppMainMenuBar();
    if (show_app_console)             ShowExampleAppConsole(&show_app_console);
    if (show_app_log)                 ShowExampleAppLog(&show_app_log);
    if (show_app_layout)              ShowExampleAppLayout(&show_app_layout);
    if (show_app_property_editor)     ShowExampleAppPropertyEditor(&show_app_property_editor);
    if (show_app_long_text)           ShowExampleAppLongText(&show_app_long_text);
    if (show_app_auto_resize)         ShowExampleAppAutoResize(&show_app_auto_resize);
    if (show_app_constrained_resize)  ShowExampleAppConstrainedResize(&show_app_constrained_resize);
    if (show_app_simple_overlay)      ShowExampleAppSimpleOverlay(&show_app_simple_overlay);
    if (show_app_window_titles)       ShowExampleAppWindowTitles(&show_app_window_titles);
    if (show_app_custom_rendering)    ShowExampleAppCustomRendering(&show_app_custom_rendering);

    // Dear ImGui Apps (accessible from the "Tools" menu)
    static bool show_app_metrics = false;
    static bool show_app_style_editor = false;
    static bool show_app_about = false;

    if (show_app_metrics)             { im::ShowMetricsWindow(&show_app_metrics); }
    if (show_app_style_editor)        { im::Begin("Style Editor", &show_app_style_editor); im::ShowStyleEditor(); im::End(); }
    if (show_app_about)               { im::ShowAboutWindow(&show_app_about); }

    // Demonstrate the various window flags. Typically you would just use the default!
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    // We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
    im::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
    im::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    // Main body of the Demo window starts here.
    if (!im::Begin("Dear ImGui Demo", p_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        im::End();
        return;
    }

    // Most "big" widgets share a common width settings by default.
    //ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // Use 2/3 of the space for widgets and 1/3 for labels (default)
    im::PushItemWidth(im::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

    // Menu Bar
    if (im::BeginMenuBar())
    {
        if (im::BeginMenu("Menu"))
        {
            ShowExampleMenuFile();
            im::EndMenu();
        }
        if (im::BeginMenu("Examples"))
        {
            im::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
            im::MenuItem("Console", NULL, &show_app_console);
            im::MenuItem("Log", NULL, &show_app_log);
            im::MenuItem("Simple layout", NULL, &show_app_layout);
            im::MenuItem("Property editor", NULL, &show_app_property_editor);
            im::MenuItem("Long text display", NULL, &show_app_long_text);
            im::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
            im::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
            im::MenuItem("Simple overlay", NULL, &show_app_simple_overlay);
            im::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
            im::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
            im::MenuItem("Documents", NULL, &show_app_documents);
            im::EndMenu();
        }
        if (im::BeginMenu("Tools"))
        {
            im::MenuItem("Metrics", NULL, &show_app_metrics);
            im::MenuItem("Style Editor", NULL, &show_app_style_editor);
            im::MenuItem("About Dear ImGui", NULL, &show_app_about);
            im::EndMenu();
        }
        im::EndMenuBar();
    }

    im::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
    im::Spacing();

    if (im::CollapsingHeader("Help"))
    {
        im::Text("ABOUT THIS DEMO:");
        im::BulletText("Sections below are demonstrating many aspects of the library.");
        im::BulletText("The \"Examples\" menu above leads to more demo contents.");
        im::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                          "and Metrics (general purpose Dear ImGui debugging tool).");
        im::Separator();

        im::Text("PROGRAMMER GUIDE:");
        im::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        im::BulletText("See comments in imgui.cpp.");
        im::BulletText("See example applications in the examples/ folder.");
        im::BulletText("Read the FAQ at http://www.dearimgui.org/faq/");
        im::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
        im::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
        im::Separator();

        im::Text("USER GUIDE:");
        im::ShowUserGuide();
    }

    if (im::CollapsingHeader("Configuration"))
    {
        ImGuiIO& io = im::GetIO();

        if (im::TreeNode("Configuration##2"))
        {
            im::CheckboxFlags("io.ConfigFlags: NavEnableKeyboard", (unsigned int *)&io.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard);
            im::CheckboxFlags("io.ConfigFlags: NavEnableGamepad", (unsigned int *)&io.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
            im::SameLine(); HelpMarker("Required back-end to feed in gamepad inputs in io.NavInputs[] and set io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details.");
            im::CheckboxFlags("io.ConfigFlags: NavEnableSetMousePos", (unsigned int *)&io.ConfigFlags, ImGuiConfigFlags_NavEnableSetMousePos);
            im::SameLine(); HelpMarker("Instruct navigation to move the mouse cursor. See comment for ImGuiConfigFlags_NavEnableSetMousePos.");
            im::CheckboxFlags("io.ConfigFlags: NoMouse", (unsigned int *)&io.ConfigFlags, ImGuiConfigFlags_NoMouse);
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse) // Create a way to restore this flag otherwise we could be stuck completely!
            {
                if (fmodf((float)im::GetTime(), 0.40f) < 0.20f)
                {
                    im::SameLine();
                    im::Text("<<PRESS SPACE TO DISABLE>>");
                }
                if (im::IsKeyPressed(im::GetKeyIndex(ImGuiKey_Space)))
                    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }
            im::CheckboxFlags("io.ConfigFlags: NoMouseCursorChange", (unsigned int *)&io.ConfigFlags, ImGuiConfigFlags_NoMouseCursorChange);
            im::SameLine(); HelpMarker("Instruct back-end to not alter mouse cursor shape and visibility.");
            im::Checkbox("io.ConfigInputTextCursorBlink", &io.ConfigInputTextCursorBlink);
            im::SameLine(); HelpMarker("Set to false to disable blinking cursor, for users who consider it distracting");
            im::Checkbox("io.ConfigWindowsResizeFromEdges", &io.ConfigWindowsResizeFromEdges);
            im::SameLine(); HelpMarker("Enable resizing of windows from their edges and from the lower-left corner.\nThis requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback.");
            im::Checkbox("io.ConfigWindowsMoveFromTitleBarOnly", &io.ConfigWindowsMoveFromTitleBarOnly);
            im::Checkbox("io.MouseDrawCursor", &io.MouseDrawCursor);
            im::SameLine(); HelpMarker("Instruct Dear ImGui to render a mouse cursor for you. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");
            im::TreePop();
            im::Separator();
        }

        if (im::TreeNode("Backend Flags"))
        {
            HelpMarker("Those flags are set by the back-ends (imgui_impl_xxx files) to specify their capabilities.\nHere we expose then as read-only fields to avoid breaking interactions with your back-end.");
            ImGuiBackendFlags backend_flags = io.BackendFlags; // Make a local copy to avoid modifying actual back-end flags.
            im::CheckboxFlags("io.BackendFlags: HasGamepad", (unsigned int *)&backend_flags, ImGuiBackendFlags_HasGamepad);
            im::CheckboxFlags("io.BackendFlags: HasMouseCursors", (unsigned int *)&backend_flags, ImGuiBackendFlags_HasMouseCursors);
            im::CheckboxFlags("io.BackendFlags: HasSetMousePos", (unsigned int *)&backend_flags, ImGuiBackendFlags_HasSetMousePos);
            im::CheckboxFlags("io.BackendFlags: RendererHasVtxOffset", (unsigned int *)&backend_flags, ImGuiBackendFlags_RendererHasVtxOffset);
            im::TreePop();
            im::Separator();
        }

        if (im::TreeNode("Style"))
        {
            HelpMarker("The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
            im::ShowStyleEditor();
            im::TreePop();
            im::Separator();
        }

        if (im::TreeNode("Capture/Logging"))
        {
            im::TextWrapped("The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded.");
            HelpMarker("Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
            im::LogButtons();
            im::TextWrapped("You can also call ImGui::LogText() to output directly to the log without a visual output.");
            if (im::Button("Copy \"Hello, world!\" to clipboard"))
            {
                im::LogToClipboard();
                im::LogText("Hello, world!");
                im::LogFinish();
            }
            im::TreePop();
        }
    }

    if (im::CollapsingHeader("Window options"))
    {
        im::Checkbox("No titlebar", &no_titlebar); im::SameLine(150);
        im::Checkbox("No scrollbar", &no_scrollbar); im::SameLine(300);
        im::Checkbox("No menu", &no_menu);
        im::Checkbox("No move", &no_move); im::SameLine(150);
        im::Checkbox("No resize", &no_resize); im::SameLine(300);
        im::Checkbox("No collapse", &no_collapse);
        im::Checkbox("No close", &no_close); im::SameLine(150);
        im::Checkbox("No nav", &no_nav); im::SameLine(300);
        im::Checkbox("No background", &no_background);
        im::Checkbox("No bring to front", &no_bring_to_front);
    }

    // All demo contents
    ShowDemoWindowWidgets();
    ShowDemoWindowLayout();
    ShowDemoWindowPopups();
    ShowDemoWindowColumns();
    ShowDemoWindowMisc();

    // End of ShowDemoWindow()
    im::End();
}

static void ShowDemoWindowWidgets()
{
    if (!im::CollapsingHeader("Widgets"))
        return;

    if (im::TreeNode("Basic"))
    {
        static int clicked = 0;
        if (im::Button("Button"))
            clicked++;
        if (clicked & 1)
        {
            im::SameLine();
            im::Text("Thanks for clicking me!");
        }

        static bool check = true;
        im::Checkbox("checkbox", &check);

        static int e = 0;
        im::RadioButton("radio a", &e, 0); im::SameLine();
        im::RadioButton("radio b", &e, 1); im::SameLine();
        im::RadioButton("radio c", &e, 2);

        // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
        for (int i = 0; i < 7; i++)
        {
            if (i > 0)
                im::SameLine();
            im::PushID(i);
            im::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i/7.0f, 0.6f, 0.6f));
            im::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i/7.0f, 0.7f, 0.7f));
            im::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i/7.0f, 0.8f, 0.8f));
            im::Button("Click");
            im::PopStyleColor(3);
            im::PopID();
        }

        // Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
        im::AlignTextToFramePadding();
        im::Text("Hold to repeat:");
        im::SameLine();

        // Arrow buttons with Repeater
        static int counter = 0;
        float spacing = im::GetStyle().ItemInnerSpacing.x;
        im::PushButtonRepeat(true);
        if (im::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
        im::SameLine(0.0f, spacing);
        if (im::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
        im::PopButtonRepeat();
        im::SameLine();
        im::Text("%d", counter);

        im::Text("Hover over me");
        if (im::IsItemHovered())
            im::SetTooltip("I am a tooltip");

        im::SameLine();
        im::Text("- or me");
        if (im::IsItemHovered())
        {
            im::BeginTooltip();
            im::Text("I am a fancy tooltip");
            static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
            im::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
            im::EndTooltip();
        }

        im::Separator();

        im::LabelText("label", "Value");

        {
            // Using the _simplified_ one-liner Combo() api here
            // See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
            static int item_current = 0;
            im::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));
            im::SameLine(); HelpMarker("Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, and demonstration of various flags.\n");
        }

        {
            static char str0[128] = "Hello, world!";
            im::InputText("input text", str0, IM_ARRAYSIZE(str0));
            im::SameLine(); HelpMarker("USER:\nHold SHIFT or use mouse to select text.\n" "CTRL+Left/Right to word jump.\n" "CTRL+A or double-click to select all.\n" "CTRL+X,CTRL+C,CTRL+V clipboard.\n" "CTRL+Z,CTRL+Y undo/redo.\n" "ESCAPE to revert.\n\nPROGRAMMER:\nYou can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated in imgui_demo.cpp).");

            static char str1[128] = "";
            im::InputTextWithHint("input text (w/ hint)", "enter text here", str1, IM_ARRAYSIZE(str1));

            static int i0 = 123;
            im::InputInt("input int", &i0);
            im::SameLine(); HelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n");

            static float f0 = 0.001f;
            im::InputFloat("input float", &f0, 0.01f, 1.0f, "%.3f");

            static double d0 = 999999.00000001;
            im::InputDouble("input double", &d0, 0.01f, 1.0f, "%.8f");

            static float f1 = 1.e10f;
            im::InputFloat("input scientific", &f1, 0.0f, 0.0f, "%e");
            im::SameLine(); HelpMarker("You can input value using the scientific notation,\n  e.g. \"1e+8\" becomes \"100000000\".\n");

            static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            im::InputFloat3("input float3", vec4a);
        }

        {
            static int i1 = 50, i2 = 42;
            im::DragInt("drag int", &i1, 1);
            im::SameLine(); HelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");

            im::DragInt("drag int 0..100", &i2, 1, 0, 100, "%d%%");

            static float f1=1.00f, f2=0.0067f;
            im::DragFloat("drag float", &f1, 0.005f);
            im::DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
        }

        {
            static int i1=0;
            im::SliderInt("slider int", &i1, -1, 3);
            im::SameLine(); HelpMarker("CTRL+click to input value.");

            static float f1=0.123f, f2=0.0f;
            im::SliderFloat("slider float", &f1, 0.0f, 1.0f, "ratio = %.3f");
            im::SliderFloat("slider float (curve)", &f2, -10.0f, 10.0f, "%.4f", 2.0f);

            static float angle = 0.0f;
            im::SliderAngle("slider angle", &angle);

            // Using the format string to display a name instead of an integer.
            // Here we completely omit '%d' from the format string, so it'll only display a name.
            // This technique can also be used with DragInt().
            enum Element { Element_Fire, Element_Earth, Element_Air, Element_Water, Element_COUNT };
            const char* element_names[Element_COUNT] = { "Fire", "Earth", "Air", "Water" };
            static int current_element = Element_Fire;
            const char* current_element_name = (current_element >= 0 && current_element < Element_COUNT) ? element_names[current_element] : "Unknown";
            im::SliderInt("slider enum", &current_element, 0, Element_COUNT - 1, current_element_name);
            im::SameLine(); HelpMarker("Using the format string parameter to display a name instead of the underlying integer.");
        }

        {
            static float col1[3] = { 1.0f,0.0f,0.2f };
            static float col2[4] = { 0.4f,0.7f,0.0f,0.5f };
            im::ColorEdit3("color 1", col1);
            im::SameLine(); HelpMarker("Click on the colored square to open a color picker.\nClick and hold to use drag and drop.\nRight-click on the colored square to show options.\nCTRL+click on individual component to input value.\n");

            im::ColorEdit4("color 2", col2);
        }

        {
            // List box
            const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
            static int listbox_item_current = 1;
            im::ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

            //static int listbox_item_current2 = 2;
            //ImGui::SetNextItemWidth(-1);
            //ImGui::ListBox("##listbox2", &listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
        }

        im::TreePop();
    }

    // Testing ImGuiOnceUponAFrame helper.
    //static ImGuiOnceUponAFrame once;
    //for (int i = 0; i < 5; i++)
    //    if (once)
    //        ImGui::Text("This will be displayed only once.");

    if (im::TreeNode("Trees"))
    {
        if (im::TreeNode("Basic trees"))
        {
            for (int i = 0; i < 5; i++)
            {
                // Use SetNextItemOpen() so set the default state of a node to be open.
                // We could also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
                if (i == 0)
                    im::SetNextItemOpen(true, ImGuiCond_Once);

                if (im::TreeNode((void*)(intptr_t)i, "Child %d", i))
                {
                    im::Text("blah blah");
                    im::SameLine();
                    if (im::SmallButton("button")) {};
                    im::TreePop();
                }
            }
            im::TreePop();
        }

        if (im::TreeNode("Advanced, with Selectable nodes"))
        {
            HelpMarker("This is a more typical looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            static bool align_label_with_current_x_position = false;
            im::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnArrow", (unsigned int*)&base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
            im::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnDoubleClick", (unsigned int*)&base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
            im::CheckboxFlags("ImGuiTreeNodeFlags_SpanAvailWidth", (unsigned int*)&base_flags, ImGuiTreeNodeFlags_SpanAvailWidth);
            im::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth", (unsigned int*)&base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
            im::Checkbox("Align label with current X position)", &align_label_with_current_x_position);
            im::Text("Hello!");
            if (align_label_with_current_x_position)
                im::Unindent(im::GetTreeNodeToLabelSpacing());

            static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
            int node_clicked = -1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
            for (int i = 0; i < 6; i++)
            {
                // Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
                ImGuiTreeNodeFlags node_flags = base_flags;
                const bool is_selected = (selection_mask & (1 << i)) != 0;
                if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                if (i < 3)
                {
                    // Items 0..2 are Tree Node
                    bool node_open = im::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                    if (im::IsItemClicked())
                        node_clicked = i;
                    if (node_open)
                    {
                        im::BulletText("Blah blah\nBlah Blah");
                        im::TreePop();
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf.
                    // Otherwise we can use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    im::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                    if (im::IsItemClicked())
                        node_clicked = i;
                }
            }
            if (node_clicked != -1)
            {
                // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                if (im::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            if (align_label_with_current_x_position)
                im::Indent(im::GetTreeNodeToLabelSpacing());
            im::TreePop();
        }
        im::TreePop();
    }

    if (im::TreeNode("Collapsing Headers"))
    {
        static bool closable_group = true;
        im::Checkbox("Show 2nd header", &closable_group);
        if (im::CollapsingHeader("Header", ImGuiTreeNodeFlags_None))
        {
            im::Text("IsItemHovered: %d", im::IsItemHovered());
            for (int i = 0; i < 5; i++)
                im::Text("Some content %d", i);
        }
        if (im::CollapsingHeader("Header with a close button", &closable_group))
        {
            im::Text("IsItemHovered: %d", im::IsItemHovered());
            for (int i = 0; i < 5; i++)
                im::Text("More content %d", i);
        }
        /*
        if (ImGui::CollapsingHeader("Header with a bullet", ImGuiTreeNodeFlags_Bullet))
            ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
        */
        im::TreePop();
    }

    if (im::TreeNode("Bullets"))
    {
        im::BulletText("Bullet point 1");
        im::BulletText("Bullet point 2\nOn multiple lines");
        if (im::TreeNode("Tree node"))
        {
            im::BulletText("Another bullet point");
            im::TreePop();
        }
        im::Bullet(); im::Text("Bullet point 3 (two calls)");
        im::Bullet(); im::SmallButton("Button");
        im::TreePop();
    }

    if (im::TreeNode("Text"))
    {
        if (im::TreeNode("Colored Text"))
        {
            // Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
            im::TextColored(ImVec4(1.0f,0.0f,1.0f,1.0f), "Pink");
            im::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "Yellow");
            im::TextDisabled("Disabled");
            im::SameLine(); HelpMarker("The TextDisabled color is stored in ImGuiStyle.");
            im::TreePop();
        }

        if (im::TreeNode("Word Wrapping"))
        {
            // Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
            im::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
            im::Spacing();

            static float wrap_width = 200.0f;
            im::SliderFloat("Wrap width", &wrap_width, -20, 600, "%.0f");

            im::Text("Test paragraph 1:");
            ImVec2 pos = im::GetCursorScreenPos();
            im::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + im::GetTextLineHeight()), IM_COL32(255,0,255,255));
            im::PushTextWrapPos(im::GetCursorPos().x + wrap_width);
            im::Text("The lazy dog is a good dog. This paragraph is made to fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width);
            im::GetWindowDrawList()->AddRect(im::GetItemRectMin(), im::GetItemRectMax(), IM_COL32(255,255,0,255));
            im::PopTextWrapPos();

            im::Text("Test paragraph 2:");
            pos = im::GetCursorScreenPos();
            im::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + im::GetTextLineHeight()), IM_COL32(255,0,255,255));
            im::PushTextWrapPos(im::GetCursorPos().x + wrap_width);
            im::Text("aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");
            im::GetWindowDrawList()->AddRect(im::GetItemRectMin(), im::GetItemRectMax(), IM_COL32(255,255,0,255));
            im::PopTextWrapPos();

            im::TreePop();
        }

        if (im::TreeNode("UTF-8 Text"))
        {
            // UTF-8 test with Japanese characters
            // (Needs a suitable font, try Noto, or Arial Unicode, or M+ fonts. Read docs/FONTS.txt for details.)
            // - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
            // - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. Visual Studio save your file as 'UTF-8 without signature')
            // - FOR THIS DEMO FILE ONLY, BECAUSE WE WANT TO SUPPORT OLD COMPILERS, WE ARE *NOT* INCLUDING RAW UTF-8 CHARACTERS IN THIS SOURCE FILE.
            //   Instead we are encoding a few strings with hexadecimal constants. Don't do this in your application!
            //   Please use u8"text in any language" in your application!
            // Note that characters values are preserved even by InputText() if the font cannot be displayed, so you can safely copy & paste garbled characters into another application.
            im::TextWrapped("CJK text will only appears if the font was loaded with the appropriate CJK character ranges. Call io.Font->AddFontFromFileTTF() manually to load extra character ranges. Read docs/FONTS.txt for details.");
            im::Text("Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)"); // Normally we would use u8"blah blah" with the proper characters directly in the string.
            im::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
            static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
            //static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
            im::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
            im::TreePop();
        }
        im::TreePop();
    }

    if (im::TreeNode("Images"))
    {
        ImGuiIO& io = im::GetIO();
        im::TextWrapped("Below we are displaying the font texture (which is the only texture we have access to in this demo). Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. Hover the texture for a zoomed view!");

        // Here we are grabbing the font texture because that's the only one we have access to inside the demo code.
        // Remember that ImTextureID is just storage for whatever you want it to be, it is essentially a value that will be passed to the render function inside the ImDrawCmd structure.
        // If you use one of the default imgui_impl_XXXX.cpp renderer, they all have comments at the top of their file to specify what they expect to be stored in ImTextureID.
        // (for example, the imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer. The imgui_impl_opengl3.cpp renderer expect a GLuint OpenGL texture identifier etc.)
        // If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers to ImGui::Image(), and gather width/height through your own functions, etc.
        // Using ShowMetricsWindow() as a "debugger" to inspect the draw data that are being passed to your render will help you debug issues if you are confused about this.
        // Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
        ImTextureID my_tex_id = io.Fonts->TexID;
        float my_tex_w = (float)io.Fonts->TexWidth;
        float my_tex_h = (float)io.Fonts->TexHeight;

        im::Text("%.0fx%.0f", my_tex_w, my_tex_h);
        ImVec2 pos = im::GetCursorScreenPos();
        im::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0,0), ImVec2(1,1), ImVec4(1.0f,1.0f,1.0f,1.0f), ImVec4(1.0f,1.0f,1.0f,0.5f));
        if (im::IsItemHovered())
        {
            im::BeginTooltip();
            float region_sz = 32.0f;
            float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if (region_x < 0.0f) region_x = 0.0f; else if (region_x > my_tex_w - region_sz) region_x = my_tex_w - region_sz;
            float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if (region_y < 0.0f) region_y = 0.0f; else if (region_y > my_tex_h - region_sz) region_y = my_tex_h - region_sz;
            float zoom = 4.0f;
            im::Text("Min: (%.2f, %.2f)", region_x, region_y);
            im::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
            ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
            ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
            im::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
            im::EndTooltip();
        }
        im::TextWrapped("And now some textured buttons..");
        static int pressed_count = 0;
        for (int i = 0; i < 8; i++)
        {
            im::PushID(i);
            int frame_padding = -1 + i;     // -1 = uses default padding
            if (im::ImageButton(my_tex_id, ImVec2(32,32), ImVec2(0,0), ImVec2(32.0f/my_tex_w,32/my_tex_h), frame_padding, ImVec4(0.0f,0.0f,0.0f,1.0f)))
                pressed_count += 1;
            im::PopID();
            im::SameLine();
        }
        im::NewLine();
        im::Text("Pressed %d times.", pressed_count);
        im::TreePop();
    }

    if (im::TreeNode("Combo"))
    {
        // Expose flags as checkbox for the demo
        static ImGuiComboFlags flags = 0;
        im::CheckboxFlags("ImGuiComboFlags_PopupAlignLeft", (unsigned int*)&flags, ImGuiComboFlags_PopupAlignLeft);
        im::SameLine(); HelpMarker("Only makes a difference if the popup is larger than the combo");
        if (im::CheckboxFlags("ImGuiComboFlags_NoArrowButton", (unsigned int*)&flags, ImGuiComboFlags_NoArrowButton))
            flags &= ~ImGuiComboFlags_NoPreview;     // Clear the other flag, as we cannot combine both
        if (im::CheckboxFlags("ImGuiComboFlags_NoPreview", (unsigned int*)&flags, ImGuiComboFlags_NoPreview))
            flags &= ~ImGuiComboFlags_NoArrowButton; // Clear the other flag, as we cannot combine both

        // General BeginCombo() API, you have full control over your selection data and display type.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag stored in the object itself, etc.)
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
        if (im::BeginCombo("combo 1", item_current, flags)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (item_current == items[n]);
                if (im::Selectable(items[n], is_selected))
                    item_current = items[n];
                if (is_selected)
                    im::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
            }
            im::EndCombo();
        }

        // Simplified one-liner Combo() API, using values packed in a single constant string
        static int item_current_2 = 0;
        im::Combo("combo 2 (one-liner)", &item_current_2, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

        // Simplified one-liner Combo() using an array of const char*
        static int item_current_3 = -1; // If the selection isn't within 0..count, Combo won't display a preview
        im::Combo("combo 3 (array)", &item_current_3, items, IM_ARRAYSIZE(items));

        // Simplified one-liner Combo() using an accessor function
        struct FuncHolder { static bool ItemGetter(void* data, int idx, const char** out_str) { *out_str = ((const char**)data)[idx]; return true; } };
        static int item_current_4 = 0;
        im::Combo("combo 4 (function)", &item_current_4, &FuncHolder::ItemGetter, items, IM_ARRAYSIZE(items));

        im::TreePop();
    }

    if (im::TreeNode("Selectables"))
    {
        // Selectable() has 2 overloads:
        // - The one taking "bool selected" as a read-only selection information. When Selectable() has been clicked is returns true and you can alter selection state accordingly.
        // - The one taking "bool* p_selected" as a read-write selection information (convenient in some cases)
        // The earlier is more flexible, as in real application your selection may be stored in a different manner (in flags within objects, as an external list, etc).
        if (im::TreeNode("Basic"))
        {
            static bool selection[5] = { false, true, false, false, false };
            im::Selectable("1. I am selectable", &selection[0]);
            im::Selectable("2. I am selectable", &selection[1]);
            im::Text("3. I am not selectable");
            im::Selectable("4. I am selectable", &selection[3]);
            if (im::Selectable("5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
                if (im::IsMouseDoubleClicked(0))
                    selection[4] = !selection[4];
            im::TreePop();
        }
        if (im::TreeNode("Selection State: Single Selection"))
        {
            static int selected = -1;
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, "Object %d", n);
                if (im::Selectable(buf, selected == n))
                    selected = n;
            }
            im::TreePop();
        }
        if (im::TreeNode("Selection State: Multiple Selection"))
        {
            HelpMarker("Hold CTRL and click to select multiple items.");
            static bool selection[5] = { false, false, false, false, false };
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, "Object %d", n);
                if (im::Selectable(buf, selection[n]))
                {
                    if (!im::GetIO().KeyCtrl)    // Clear selection when CTRL is not held
                        memset(selection, 0, sizeof(selection));
                    selection[n] ^= 1;
                }
            }
            im::TreePop();
        }
        if (im::TreeNode("Rendering more text into the same line"))
        {
            // Using the Selectable() override that takes "bool* p_selected" parameter and toggle your booleans automatically.
            static bool selected[3] = { false, false, false };
            im::Selectable("main.c",    &selected[0]); im::SameLine(300); im::Text(" 2,345 bytes");
            im::Selectable("Hello.cpp", &selected[1]); im::SameLine(300); im::Text("12,345 bytes");
            im::Selectable("Hello.h",   &selected[2]); im::SameLine(300); im::Text(" 2,345 bytes");
            im::TreePop();
        }
        if (im::TreeNode("In columns"))
        {
            im::Columns(3, NULL, false);
            static bool selected[16] = {};
            for (int i = 0; i < 16; i++)
            {
                char label[32]; sprintf(label, "Item %d", i);
                if (im::Selectable(label, &selected[i])) {}
                im::NextColumn();
            }
            im::Columns(1);
            im::TreePop();
        }
        if (im::TreeNode("Grid"))
        {
            static bool selected[4*4] = { true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, true };
            for (int i = 0; i < 4*4; i++)
            {
                im::PushID(i);
                if (im::Selectable("Sailor", &selected[i], 0, ImVec2(50,50)))
                {
                    // Note: We _unnecessarily_ test for both x/y and i here only to silence some static analyzer. The second part of each test is unnecessary.
                    int x = i % 4;
                    int y = i / 4;
                    if (x > 0)           { selected[i - 1] ^= 1; }
                    if (x < 3 && i < 15) { selected[i + 1] ^= 1; }
                    if (y > 0 && i > 3)  { selected[i - 4] ^= 1; }
                    if (y < 3 && i < 12) { selected[i + 4] ^= 1; }
                }
                if ((i % 4) < 3) im::SameLine();
                im::PopID();
            }
            im::TreePop();
        }
        if (im::TreeNode("Alignment"))
        {
            HelpMarker("Alignment applies when a selectable is larger than its text content.\nBy default, Selectables uses style.SelectableTextAlign but it can be overriden on a per-item basis using PushStyleVar().");
            static bool selected[3*3] = { true, false, true, false, true, false, true, false, true };
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    ImVec2 alignment = ImVec2((float)x / 2.0f, (float)y / 2.0f);
                    char name[32];
                    sprintf(name, "(%.1f,%.1f)", alignment.x, alignment.y);
                    if (x > 0) im::SameLine();
                    im::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, alignment);
                    im::Selectable(name, &selected[3*y+x], ImGuiSelectableFlags_None, ImVec2(80,80));
                    im::PopStyleVar();
                }
            }
            im::TreePop();
        }
        im::TreePop();
    }

    if (im::TreeNode("Text Input"))
    {
        if (im::TreeNode("Multi-line Text Input"))
        {
            // Note: we are using a fixed-sized buffer for simplicity here. See ImGuiInputTextFlags_CallbackResize
            // and the code in misc/cpp/imgui_stdlib.h for how to setup InputText() for dynamically resizing strings.
            static char text[1024 * 16] =
                "/*\n"
                " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
                " the hexadecimal encoding of one offending instruction,\n"
                " more formally, the invalid operand with locked CMPXCHG8B\n"
                " instruction bug, is a design flaw in the majority of\n"
                " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
                " processors (all in the P5 microarchitecture).\n"
                "*/\n\n"
                "label:\n"
                "\tlock cmpxchg8b eax\n";

            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
            HelpMarker("You can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputTextMultiline() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example. (This is not demonstrated in imgui_demo.cpp)");
            im::CheckboxFlags("ImGuiInputTextFlags_ReadOnly", (unsigned int*)&flags, ImGuiInputTextFlags_ReadOnly);
            im::CheckboxFlags("ImGuiInputTextFlags_AllowTabInput", (unsigned int*)&flags, ImGuiInputTextFlags_AllowTabInput);
            im::CheckboxFlags("ImGuiInputTextFlags_CtrlEnterForNewLine", (unsigned int*)&flags, ImGuiInputTextFlags_CtrlEnterForNewLine);
            im::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, im::GetTextLineHeight() * 16), flags);
            im::TreePop();
        }

        if (im::TreeNode("Filtered Text Input"))
        {
            static char buf1[64] = ""; im::InputText("default", buf1, 64);
            static char buf2[64] = ""; im::InputText("decimal", buf2, 64, ImGuiInputTextFlags_CharsDecimal);
            static char buf3[64] = ""; im::InputText("hexadecimal", buf3, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            static char buf4[64] = ""; im::InputText("uppercase", buf4, 64, ImGuiInputTextFlags_CharsUppercase);
            static char buf5[64] = ""; im::InputText("no blank", buf5, 64, ImGuiInputTextFlags_CharsNoBlank);
            struct TextFilters { static int FilterImGuiLetters(ImGuiInputTextCallbackData* data) { if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar)) return 0; return 1; } };
            static char buf6[64] = ""; im::InputText("\"imgui\" letters", buf6, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);

            im::Text("Password input");
            static char bufpass[64] = "password123";
            im::InputText("password", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
            im::SameLine(); HelpMarker("Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n");
            im::InputTextWithHint("password (w/ hint)", "<password>", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
            im::InputText("password (clear)", bufpass, 64, ImGuiInputTextFlags_CharsNoBlank);
            im::TreePop();
        }

        if (im::TreeNode("Resize Callback"))
        {
            // If you have a custom string type you would typically create a ImGui::InputText() wrapper than takes your type as input.
            // See misc/cpp/imgui_stdlib.h and .cpp for an implementation of this using std::string.
            HelpMarker("Demonstrate using ImGuiInputTextFlags_CallbackResize to wire your resizable string type to InputText().\n\nSee misc/cpp/imgui_stdlib.h for an implementation of this for std::string.");
            struct Funcs
            {
                static int MyResizeCallback(ImGuiInputTextCallbackData* data)
                {
                    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
                    {
                        ImVector<char>* my_str = (ImVector<char>*)data->UserData;
                        IM_ASSERT(my_str->begin() == data->Buf);
                        my_str->resize(data->BufSize);  // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
                        data->Buf = my_str->begin();
                    }
                    return 0;
                }

                // Tip: Because ImGui:: is a namespace you would typicall add your own function into the namespace in your own source files.
                // For example, you may add a function called ImGui::InputText(const char* label, MyString* my_str).
                static bool MyInputTextMultiline(const char* label, ImVector<char>* my_str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0)
                {
                    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
                    return im::InputTextMultiline(label, my_str->begin(), (size_t)my_str->size(), size, flags | ImGuiInputTextFlags_CallbackResize, Funcs::MyResizeCallback, (void*)my_str);
                }
            };

            // For this demo we are using ImVector as a string container.
            // Note that because we need to store a terminating zero character, our size/capacity are 1 more than usually reported by a typical string class.
            static ImVector<char> my_str;
            if (my_str.empty())
                my_str.push_back(0);
            Funcs::MyInputTextMultiline("##MyStr", &my_str, ImVec2(-FLT_MIN, im::GetTextLineHeight() * 16));
            im::Text("Data: %p\nSize: %d\nCapacity: %d", (void*)my_str.begin(), my_str.size(), my_str.capacity());
            im::TreePop();
        }

        im::TreePop();
    }

    // Plot/Graph widgets are currently fairly limited.
    // Consider writing your own plotting widget, or using a third-party one (see "Wiki->Useful Widgets", or github.com/ocornut/imgui/issues/2747)
    if (im::TreeNode("Plots Widgets"))
    {
        static bool animate = true;
        im::Checkbox("Animate", &animate);

        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        im::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

        // Create a dummy array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float and the sizeof() of your structure in the Stride parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = im::GetTime();
        while (refresh_time < im::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset+1) % IM_ARRAYSIZE(values);
            phase += 0.10f*values_offset;
            refresh_time += 1.0f/60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            im::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0,80));
        }
        im::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0,80));

        // Use functions to generate output
        // FIXME: This is rather awkward because current plot API only pass in indices. We probably want an API passing floats and user provide sample rate/count.
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };
        static int func_type = 0, display_count = 70;
        im::Separator();
        im::SetNextItemWidth(100);
        im::Combo("func", &func_type, "Sin\0Saw\0");
        im::SameLine();
        im::SliderInt("Sample count", &display_count, 1, 400);
        float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
        im::PlotLines("Lines", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0,80));
        im::PlotHistogram("Histogram", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0,80));
        im::Separator();

        // Animate a simple progress bar
        static float progress = 0.0f, progress_dir = 1.0f;
        if (animate)
        {
            progress += progress_dir * 0.4f * im::GetIO().DeltaTime;
            if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
            if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
        }

        // Typically we would use ImVec2(-1.0f,0.0f) or ImVec2(-FLT_MIN,0.0f) to use all available width,
        // or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
        im::ProgressBar(progress, ImVec2(0.0f,0.0f));
        im::SameLine(0.0f, im::GetStyle().ItemInnerSpacing.x);
        im::Text("Progress Bar");

        float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
        char buf[32];
        sprintf(buf, "%d/%d", (int)(progress_saturated*1753), 1753);
        im::ProgressBar(progress, ImVec2(0.f,0.f), buf);
        im::TreePop();
    }

    if (im::TreeNode("Color/Picker Widgets"))
    {
        static ImVec4 color = ImVec4(114.0f/255.0f, 144.0f/255.0f, 154.0f/255.0f, 200.0f/255.0f);

        static bool alpha_preview = true;
        static bool alpha_half_preview = false;
        static bool drag_and_drop = true;
        static bool options_menu = true;
        static bool hdr = false;
        im::Checkbox("With Alpha Preview", &alpha_preview);
        im::Checkbox("With Half Alpha Preview", &alpha_half_preview);
        im::Checkbox("With Drag and Drop", &drag_and_drop);
        im::Checkbox("With Options Menu", &options_menu); im::SameLine(); HelpMarker("Right-click on the individual color widget to show options.");
        im::Checkbox("With HDR", &hdr); im::SameLine(); HelpMarker("Currently all this does is to lift the 0..1 limits on dragging widgets.");
        ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

        im::Text("Color widget:");
        im::SameLine(); HelpMarker("Click on the colored square to open a color picker.\nCTRL+click on individual component to input value.\n");
        im::ColorEdit3("MyColor##1", (float*)&color, misc_flags);

        im::Text("Color widget HSV with Alpha:");
        im::ColorEdit4("MyColor##2", (float*)&color, ImGuiColorEditFlags_DisplayHSV | misc_flags);

        im::Text("Color widget with Float Display:");
        im::ColorEdit4("MyColor##2f", (float*)&color, ImGuiColorEditFlags_Float | misc_flags);

        im::Text("Color button with Picker:");
        im::SameLine(); HelpMarker("With the ImGuiColorEditFlags_NoInputs flag you can hide all the slider/text inputs.\nWith the ImGuiColorEditFlags_NoLabel flag you can pass a non-empty label which will only be used for the tooltip and picker popup.");
        im::ColorEdit4("MyColor##3", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);

        im::Text("Color button with Custom Picker Popup:");

        // Generate a dummy default palette. The palette will persist and can be edited.
        static bool saved_palette_init = true;
        static ImVec4 saved_palette[32] = {};
        if (saved_palette_init)
        {
            for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
            {
                im::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f, saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                saved_palette[n].w = 1.0f; // Alpha
            }
            saved_palette_init = false;
        }

        static ImVec4 backup_color;
        bool open_popup = im::ColorButton("MyColor##3b", color, misc_flags);
        im::SameLine(0, im::GetStyle().ItemInnerSpacing.x);
        open_popup |= im::Button("Palette");
        if (open_popup)
        {
            im::OpenPopup("mypicker");
            backup_color = color;
        }
        if (im::BeginPopup("mypicker"))
        {
            im::Text("MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
            im::Separator();
            im::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            im::SameLine();

            im::BeginGroup(); // Lock X position
            im::Text("Current");
            im::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40));
            im::Text("Previous");
            if (im::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40)))
                color = backup_color;
            im::Separator();
            im::Text("Palette");
            for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
            {
                im::PushID(n);
                if ((n % 8) != 0)
                    im::SameLine(0.0f, im::GetStyle().ItemSpacing.y);
                if (im::ColorButton("##palette", saved_palette[n], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20,20)))
                    color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

                // Allow user to drop colors into each palette entry
                // (Note that ColorButton is already a drag source by default, unless using ImGuiColorEditFlags_NoDragDrop)
                if (im::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = im::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                    if (const ImGuiPayload* payload = im::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                    im::EndDragDropTarget();
                }

                im::PopID();
            }
            im::EndGroup();
            im::EndPopup();
        }

        im::Text("Color button only:");
        im::ColorButton("MyColor##3c", *(ImVec4*)&color, misc_flags, ImVec2(80,80));

        im::Text("Color picker:");
        static bool alpha = true;
        static bool alpha_bar = true;
        static bool side_preview = true;
        static bool ref_color = false;
        static ImVec4 ref_color_v(1.0f,0.0f,1.0f,0.5f);
        static int display_mode = 0;
        static int picker_mode = 0;
        im::Checkbox("With Alpha", &alpha);
        im::Checkbox("With Alpha Bar", &alpha_bar);
        im::Checkbox("With Side Preview", &side_preview);
        if (side_preview)
        {
            im::SameLine();
            im::Checkbox("With Ref Color", &ref_color);
            if (ref_color)
            {
                im::SameLine();
                im::ColorEdit4("##RefColor", &ref_color_v.x, ImGuiColorEditFlags_NoInputs | misc_flags);
            }
        }
        im::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
        im::SameLine(); HelpMarker("ColorEdit defaults to displaying RGB inputs if you don't specify a display mode, but the user can change it with a right-click.\n\nColorPicker defaults to displaying RGB+HSV+Hex if you don't specify a display mode.\n\nYou can change the defaults using SetColorEditOptions().");
        im::Combo("Picker Mode", &picker_mode, "Auto/Current\0Hue bar + SV rect\0Hue wheel + SV triangle\0");
        im::SameLine(); HelpMarker("User can right-click the picker to change mode.");
        ImGuiColorEditFlags flags = misc_flags;
        if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
        if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
        if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
        if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
        if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
        if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
        if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
        if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
        if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
        im::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

        im::Text("Programmatically set defaults:");
        im::SameLine(); HelpMarker("SetColorEditOptions() is designed to allow you to set boot-time default.\nWe don't have Push/Pop functions because you can force options on a per-widget basis if needed, and the user can change non-forced ones with the options menu.\nWe don't have a getter to avoid encouraging you to persistently save values that aren't forward-compatible.");
        if (im::Button("Default: Uint8 + HSV + Hue Bar"))
            im::SetColorEditOptions(ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_PickerHueBar);
        if (im::Button("Default: Float + HDR + Hue Wheel"))
            im::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

        // HSV encoded support (to avoid RGB<>HSV round trips and singularities when S==0 or V==0)
        static ImVec4 color_stored_as_hsv(0.23f, 1.0f, 1.0f, 1.0f);
        im::Spacing();
        im::Text("HSV encoded colors");
        im::SameLine(); HelpMarker("By default, colors are given to ColorEdit and ColorPicker in RGB, but ImGuiColorEditFlags_InputHSV allows you to store colors as HSV and pass them to ColorEdit and ColorPicker as HSV. This comes with the added benefit that you can manipulate hue values with the picker even when saturation or value are zero.");
        im::Text("Color widget with InputHSV:");
        im::ColorEdit4("HSV shown as RGB##1", (float*)&color_stored_as_hsv, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        im::ColorEdit4("HSV shown as HSV##1", (float*)&color_stored_as_hsv, ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        im::DragFloat4("Raw HSV values", (float*)&color_stored_as_hsv, 0.01f, 0.0f, 1.0f);

        im::TreePop();
    }

    if (im::TreeNode("Range Widgets"))
    {
        static float begin = 10, end = 90;
        static int begin_i = 100, end_i = 1000;
        im::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
        im::DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %d units", "Max: %d units");
        im::TreePop();
    }

    if (im::TreeNode("Data Types"))
    {
        // The DragScalar/InputScalar/SliderScalar functions allow various data types: signed/unsigned int/long long and float/double
        // To avoid polluting the public API with all possible combinations, we use the ImGuiDataType enum to pass the type,
        // and passing all arguments by address.
        // This is the reason the test code below creates local variables to hold "zero" "one" etc. for each types.
        // In practice, if you frequently use a given type that is not covered by the normal API entry points, you can wrap it
        // yourself inside a 1 line function which can take typed argument as value instead of void*, and then pass their address
        // to the generic function. For example:
        //   bool MySliderU64(const char *label, u64* value, u64 min = 0, u64 max = 0, const char* format = "%lld")
        //   {
        //      return SliderScalar(label, ImGuiDataType_U64, value, &min, &max, format);
        //   }

        // Limits (as helper variables that we can take the address of)
        // Note that the SliderScalar function has a maximum usable range of half the natural type maximum, hence the /2 below.
        #ifndef LLONG_MIN
        ImS64 LLONG_MIN = -9223372036854775807LL - 1;
        ImS64 LLONG_MAX = 9223372036854775807LL;
        ImU64 ULLONG_MAX = (2ULL * 9223372036854775807LL + 1);
        #endif
        const char    s8_zero  = 0,   s8_one  = 1,   s8_fifty  = 50, s8_min  = -128,        s8_max = 127;
        const ImU8    u8_zero  = 0,   u8_one  = 1,   u8_fifty  = 50, u8_min  = 0,           u8_max = 255;
        const short   s16_zero = 0,   s16_one = 1,   s16_fifty = 50, s16_min = -32768,      s16_max = 32767;
        const ImU16   u16_zero = 0,   u16_one = 1,   u16_fifty = 50, u16_min = 0,           u16_max = 65535;
        const ImS32   s32_zero = 0,   s32_one = 1,   s32_fifty = 50, s32_min = INT_MIN/2,   s32_max = INT_MAX/2,    s32_hi_a = INT_MAX/2 - 100,    s32_hi_b = INT_MAX/2;
        const ImU32   u32_zero = 0,   u32_one = 1,   u32_fifty = 50, u32_min = 0,           u32_max = UINT_MAX/2,   u32_hi_a = UINT_MAX/2 - 100,   u32_hi_b = UINT_MAX/2;
        const ImS64   s64_zero = 0,   s64_one = 1,   s64_fifty = 50, s64_min = LLONG_MIN/2, s64_max = LLONG_MAX/2,  s64_hi_a = LLONG_MAX/2 - 100,  s64_hi_b = LLONG_MAX/2;
        const ImU64   u64_zero = 0,   u64_one = 1,   u64_fifty = 50, u64_min = 0,           u64_max = ULLONG_MAX/2, u64_hi_a = ULLONG_MAX/2 - 100, u64_hi_b = ULLONG_MAX/2;
        const float   f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
        const double  f64_zero = 0.,  f64_one = 1.,  f64_lo_a = -1000000000000000.0, f64_hi_a = +1000000000000000.0;

        // State
        static char   s8_v  = 127;
        static ImU8   u8_v  = 255;
        static short  s16_v = 32767;
        static ImU16  u16_v = 65535;
        static ImS32  s32_v = -1;
        static ImU32  u32_v = (ImU32)-1;
        static ImS64  s64_v = -1;
        static ImU64  u64_v = (ImU64)-1;
        static float  f32_v = 0.123f;
        static double f64_v = 90000.01234567890123456789;

        const float drag_speed = 0.2f;
        static bool drag_clamp = false;
        im::Text("Drags:");
        im::Checkbox("Clamp integers to 0..50", &drag_clamp); im::SameLine(); HelpMarker("As with every widgets in dear imgui, we never modify values unless there is a user interaction.\nYou can override the clamping limits by using CTRL+Click to input a value.");
        im::DragScalar("drag s8",        ImGuiDataType_S8,     &s8_v,  drag_speed, drag_clamp ? &s8_zero  : NULL, drag_clamp ? &s8_fifty  : NULL);
        im::DragScalar("drag u8",        ImGuiDataType_U8,     &u8_v,  drag_speed, drag_clamp ? &u8_zero  : NULL, drag_clamp ? &u8_fifty  : NULL, "%u ms");
        im::DragScalar("drag s16",       ImGuiDataType_S16,    &s16_v, drag_speed, drag_clamp ? &s16_zero : NULL, drag_clamp ? &s16_fifty : NULL);
        im::DragScalar("drag u16",       ImGuiDataType_U16,    &u16_v, drag_speed, drag_clamp ? &u16_zero : NULL, drag_clamp ? &u16_fifty : NULL, "%u ms");
        im::DragScalar("drag s32",       ImGuiDataType_S32,    &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL);
        im::DragScalar("drag u32",       ImGuiDataType_U32,    &u32_v, drag_speed, drag_clamp ? &u32_zero : NULL, drag_clamp ? &u32_fifty : NULL, "%u ms");
        im::DragScalar("drag s64",       ImGuiDataType_S64,    &s64_v, drag_speed, drag_clamp ? &s64_zero : NULL, drag_clamp ? &s64_fifty : NULL);
        im::DragScalar("drag u64",       ImGuiDataType_U64,    &u64_v, drag_speed, drag_clamp ? &u64_zero : NULL, drag_clamp ? &u64_fifty : NULL);
        im::DragScalar("drag float",     ImGuiDataType_Float,  &f32_v, 0.005f,  &f32_zero, &f32_one, "%f", 1.0f);
        im::DragScalar("drag float ^2",  ImGuiDataType_Float,  &f32_v, 0.005f,  &f32_zero, &f32_one, "%f", 2.0f); im::SameLine(); HelpMarker("You can use the 'power' parameter to increase tweaking precision on one side of the range.");
        im::DragScalar("drag double",    ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, NULL,     "%.10f grams", 1.0f);
        im::DragScalar("drag double ^2", ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, &f64_one, "0 < %.10f < 1", 2.0f);

        im::Text("Sliders");
        im::SliderScalar("slider s8 full",     ImGuiDataType_S8,     &s8_v,  &s8_min,   &s8_max,   "%d");
        im::SliderScalar("slider u8 full",     ImGuiDataType_U8,     &u8_v,  &u8_min,   &u8_max,   "%u");
        im::SliderScalar("slider s16 full",    ImGuiDataType_S16,    &s16_v, &s16_min,  &s16_max,  "%d");
        im::SliderScalar("slider u16 full",    ImGuiDataType_U16,    &u16_v, &u16_min,  &u16_max,  "%u");
        im::SliderScalar("slider s32 low",     ImGuiDataType_S32,    &s32_v, &s32_zero, &s32_fifty,"%d");
        im::SliderScalar("slider s32 high",    ImGuiDataType_S32,    &s32_v, &s32_hi_a, &s32_hi_b, "%d");
        im::SliderScalar("slider s32 full",    ImGuiDataType_S32,    &s32_v, &s32_min,  &s32_max,  "%d");
        im::SliderScalar("slider u32 low",     ImGuiDataType_U32,    &u32_v, &u32_zero, &u32_fifty,"%u");
        im::SliderScalar("slider u32 high",    ImGuiDataType_U32,    &u32_v, &u32_hi_a, &u32_hi_b, "%u");
        im::SliderScalar("slider u32 full",    ImGuiDataType_U32,    &u32_v, &u32_min,  &u32_max,  "%u");
        im::SliderScalar("slider s64 low",     ImGuiDataType_S64,    &s64_v, &s64_zero, &s64_fifty,"%I64d");
        im::SliderScalar("slider s64 high",    ImGuiDataType_S64,    &s64_v, &s64_hi_a, &s64_hi_b, "%I64d");
        im::SliderScalar("slider s64 full",    ImGuiDataType_S64,    &s64_v, &s64_min,  &s64_max,  "%I64d");
        im::SliderScalar("slider u64 low",     ImGuiDataType_U64,    &u64_v, &u64_zero, &u64_fifty,"%I64u ms");
        im::SliderScalar("slider u64 high",    ImGuiDataType_U64,    &u64_v, &u64_hi_a, &u64_hi_b, "%I64u ms");
        im::SliderScalar("slider u64 full",    ImGuiDataType_U64,    &u64_v, &u64_min,  &u64_max,  "%I64u ms");
        im::SliderScalar("slider float low",   ImGuiDataType_Float,  &f32_v, &f32_zero, &f32_one);
        im::SliderScalar("slider float low^2", ImGuiDataType_Float,  &f32_v, &f32_zero, &f32_one,  "%.10f", 2.0f);
        im::SliderScalar("slider float high",  ImGuiDataType_Float,  &f32_v, &f32_lo_a, &f32_hi_a, "%e");
        im::SliderScalar("slider double low",  ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one,  "%.10f grams", 1.0f);
        im::SliderScalar("slider double low^2",ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one,  "%.10f", 2.0f);
        im::SliderScalar("slider double high", ImGuiDataType_Double, &f64_v, &f64_lo_a, &f64_hi_a, "%e grams", 1.0f);

        static bool inputs_step = true;
        im::Text("Inputs");
        im::Checkbox("Show step buttons", &inputs_step);
        im::InputScalar("input s8",      ImGuiDataType_S8,     &s8_v,  inputs_step ? &s8_one  : NULL, NULL, "%d");
        im::InputScalar("input u8",      ImGuiDataType_U8,     &u8_v,  inputs_step ? &u8_one  : NULL, NULL, "%u");
        im::InputScalar("input s16",     ImGuiDataType_S16,    &s16_v, inputs_step ? &s16_one : NULL, NULL, "%d");
        im::InputScalar("input u16",     ImGuiDataType_U16,    &u16_v, inputs_step ? &u16_one : NULL, NULL, "%u");
        im::InputScalar("input s32",     ImGuiDataType_S32,    &s32_v, inputs_step ? &s32_one : NULL, NULL, "%d");
        im::InputScalar("input s32 hex", ImGuiDataType_S32,    &s32_v, inputs_step ? &s32_one : NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
        im::InputScalar("input u32",     ImGuiDataType_U32,    &u32_v, inputs_step ? &u32_one : NULL, NULL, "%u");
        im::InputScalar("input u32 hex", ImGuiDataType_U32,    &u32_v, inputs_step ? &u32_one : NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal);
        im::InputScalar("input s64",     ImGuiDataType_S64,    &s64_v, inputs_step ? &s64_one : NULL);
        im::InputScalar("input u64",     ImGuiDataType_U64,    &u64_v, inputs_step ? &u64_one : NULL);
        im::InputScalar("input float",   ImGuiDataType_Float,  &f32_v, inputs_step ? &f32_one : NULL);
        im::InputScalar("input double",  ImGuiDataType_Double, &f64_v, inputs_step ? &f64_one : NULL);

        im::TreePop();
    }

    if (im::TreeNode("Multi-component Widgets"))
    {
        static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
        static int vec4i[4] = { 1, 5, 100, 255 };

        im::InputFloat2("input float2", vec4f);
        im::DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f);
        im::SliderFloat2("slider float2", vec4f, 0.0f, 1.0f);
        im::InputInt2("input int2", vec4i);
        im::DragInt2("drag int2", vec4i, 1, 0, 255);
        im::SliderInt2("slider int2", vec4i, 0, 255);
        im::Spacing();

        im::InputFloat3("input float3", vec4f);
        im::DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f);
        im::SliderFloat3("slider float3", vec4f, 0.0f, 1.0f);
        im::InputInt3("input int3", vec4i);
        im::DragInt3("drag int3", vec4i, 1, 0, 255);
        im::SliderInt3("slider int3", vec4i, 0, 255);
        im::Spacing();

        im::InputFloat4("input float4", vec4f);
        im::DragFloat4("drag float4", vec4f, 0.01f, 0.0f, 1.0f);
        im::SliderFloat4("slider float4", vec4f, 0.0f, 1.0f);
        im::InputInt4("input int4", vec4i);
        im::DragInt4("drag int4", vec4i, 1, 0, 255);
        im::SliderInt4("slider int4", vec4i, 0, 255);

        im::TreePop();
    }

    if (im::TreeNode("Vertical Sliders"))
    {
        const float spacing = 4;
        im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

        static int int_value = 0;
        im::VSliderInt("##int", ImVec2(18,160), &int_value, 0, 5);
        im::SameLine();

        static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
        im::PushID("set1");
        for (int i = 0; i < 7; i++)
        {
            if (i > 0) im::SameLine();
            im::PushID(i);
            im::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i/7.0f, 0.5f, 0.5f));
            im::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i/7.0f, 0.6f, 0.5f));
            im::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i/7.0f, 0.7f, 0.5f));
            im::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i/7.0f, 0.9f, 0.9f));
            im::VSliderFloat("##v", ImVec2(18,160), &values[i], 0.0f, 1.0f, "");
            if (im::IsItemActive() || im::IsItemHovered())
                im::SetTooltip("%.3f", values[i]);
            im::PopStyleColor(4);
            im::PopID();
        }
        im::PopID();

        im::SameLine();
        im::PushID("set2");
        static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
        const int rows = 3;
        const ImVec2 small_slider_size(18, (float)(int)((160.0f - (rows - 1) * spacing) / rows));
        for (int nx = 0; nx < 4; nx++)
        {
            if (nx > 0) im::SameLine();
            im::BeginGroup();
            for (int ny = 0; ny < rows; ny++)
            {
                im::PushID(nx*rows+ny);
                im::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
                if (im::IsItemActive() || im::IsItemHovered())
                    im::SetTooltip("%.3f", values2[nx]);
                im::PopID();
            }
            im::EndGroup();
        }
        im::PopID();

        im::SameLine();
        im::PushID("set3");
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) im::SameLine();
            im::PushID(i);
            im::PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
            im::VSliderFloat("##v", ImVec2(40,160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
            im::PopStyleVar();
            im::PopID();
        }
        im::PopID();
        im::PopStyleVar();
        im::TreePop();
    }

    if (im::TreeNode("Drag and Drop"))
    {
        if (im::TreeNode("Drag and drop in standard widgets"))
        {
            // ColorEdit widgets automatically act as drag source and drag target.
            // They are using standardized payload strings IMGUI_PAYLOAD_TYPE_COLOR_3F and IMGUI_PAYLOAD_TYPE_COLOR_4F to allow your own widgets
            // to use colors in their drag and drop interaction. Also see the demo in Color Picker -> Palette demo.
            HelpMarker("You can drag from the colored squares.");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            im::ColorEdit3("color 1", col1);
            im::ColorEdit4("color 2", col2);
            im::TreePop();
        }

        if (im::TreeNode("Drag and drop to copy/swap items"))
        {
            enum Mode
            {
                Mode_Copy,
                Mode_Move,
                Mode_Swap
            };
            static int mode = 0;
            if (im::RadioButton("Copy", mode == Mode_Copy)) { mode = Mode_Copy; } im::SameLine();
            if (im::RadioButton("Move", mode == Mode_Move)) { mode = Mode_Move; } im::SameLine();
            if (im::RadioButton("Swap", mode == Mode_Swap)) { mode = Mode_Swap; }
            static const char* names[9] = { "Bobby", "Beatrice", "Betty", "Brianna", "Barry", "Bernard", "Bibi", "Blaine", "Bryn" };
            for (int n = 0; n < IM_ARRAYSIZE(names); n++)
            {
                im::PushID(n);
                if ((n % 3) != 0)
                    im::SameLine();
                im::Button(names[n], ImVec2(60,60));

                // Our buttons are both drag sources and drag targets here!
                if (im::BeginDragDropSource(ImGuiDragDropFlags_None))
                {
                    im::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));    // Set payload to carry the index of our item (could be anything)
                    if (mode == Mode_Copy) { im::Text("Copy %s", names[n]); }    // Display preview (could be anything, e.g. when dragging an image we could decide to display the filename and a small preview of the image, etc.)
                    if (mode == Mode_Move) { im::Text("Move %s", names[n]); }
                    if (mode == Mode_Swap) { im::Text("Swap %s", names[n]); }
                    im::EndDragDropSource();
                }
                if (im::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = im::AcceptDragDropPayload("DND_DEMO_CELL"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(int));
                        int payload_n = *(const int*)payload->Data;
                        if (mode == Mode_Copy)
                        {
                            names[n] = names[payload_n];
                        }
                        if (mode == Mode_Move)
                        {
                            names[n] = names[payload_n];
                            names[payload_n] = "";
                        }
                        if (mode == Mode_Swap)
                        {
                            const char* tmp = names[n];
                            names[n] = names[payload_n];
                            names[payload_n] = tmp;
                        }
                    }
                    im::EndDragDropTarget();
                }
                im::PopID();
            }
            im::TreePop();
        }

        if (im::TreeNode("Drag to reorder items (simple)"))
        {
            // Simple reordering
            HelpMarker("We don't use the drag and drop api at all here! Instead we query when the item is held but not hovered, and order items accordingly.");
            static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
            {
                const char* item = item_names[n];
                im::Selectable(item);

                if (im::IsItemActive() && !im::IsItemHovered())
                {
                    int n_next = n + (im::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
                    {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        im::ResetMouseDragDelta();
                    }
                }
            }
            im::TreePop();
        }

        im::TreePop();
    }

    if (im::TreeNode("Querying Status (Active/Focused/Hovered etc.)"))
    {
        // Submit an item (various types available) so we can query their status in the following block.
        static int item_type = 1;
        im::Combo("Item Type", &item_type, "Text\0Button\0Button (w/ repeat)\0Checkbox\0SliderFloat\0InputText\0InputFloat\0InputFloat3\0ColorEdit4\0MenuItem\0TreeNode\0TreeNode (w/ double-click)\0ListBox\0", 20);
        im::SameLine();
        HelpMarker("Testing how various types of items are interacting with the IsItemXXX functions.");
        bool ret = false;
        static bool b = false;
        static float col4f[4] = { 1.0f, 0.5, 0.0f, 1.0f };
        static char str[16] = {};
        if (item_type == 0) { im::Text("ITEM: Text"); }                                              // Testing text items with no identifier/interaction
        if (item_type == 1) { ret = im::Button("ITEM: Button"); }                                    // Testing button
        if (item_type == 2) { im::PushButtonRepeat(true); ret = im::Button("ITEM: Button"); im::PopButtonRepeat(); } // Testing button (with repeater)
        if (item_type == 3) { ret = im::Checkbox("ITEM: Checkbox", &b); }                            // Testing checkbox
        if (item_type == 4) { ret = im::SliderFloat("ITEM: SliderFloat", &col4f[0], 0.0f, 1.0f); }   // Testing basic item
        if (item_type == 5) { ret = im::InputText("ITEM: InputText", &str[0], IM_ARRAYSIZE(str)); }  // Testing input text (which handles tabbing)
        if (item_type == 6) { ret = im::InputFloat("ITEM: InputFloat", col4f, 1.0f); }               // Testing +/- buttons on scalar input
        if (item_type == 7) { ret = im::InputFloat3("ITEM: InputFloat3", col4f); }                   // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 8) { ret = im::ColorEdit4("ITEM: ColorEdit4", col4f); }                     // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 9) { ret = im::MenuItem("ITEM: MenuItem"); }                                // Testing menu item (they use ImGuiButtonFlags_PressedOnRelease button policy)
        if (item_type == 10){ ret = im::TreeNode("ITEM: TreeNode"); if (ret) im::TreePop(); }     // Testing tree node
        if (item_type == 11){ ret = im::TreeNodeEx("ITEM: TreeNode w/ ImGuiTreeNodeFlags_OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen); } // Testing tree node with ImGuiButtonFlags_PressedOnDoubleClick button policy.
        if (item_type == 12){ const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = im::ListBox("ITEM: ListBox", &current, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items)); }

        // Display the value of IsItemHovered() and other common item state functions.
        // Note that the ImGuiHoveredFlags_XXX flags can be combined.
        // Because BulletText is an item itself and that would affect the output of IsItemXXX functions,
        // we query every state in a single call to avoid storing them and to simplify the code
        im::BulletText(
            "Return value = %d\n"
            "IsItemFocused() = %d\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlapped) = %d\n"
            "IsItemHovered(_RectOnly) = %d\n"
            "IsItemActive() = %d\n"
            "IsItemEdited() = %d\n"
            "IsItemActivated() = %d\n"
            "IsItemDeactivated() = %d\n"
            "IsItemDeactivatedAfterEdit() = %d\n"
            "IsItemVisible() = %d\n"
            "IsItemClicked() = %d\n"
            "IsItemToggledOpen() = %d\n"
            "GetItemRectMin() = (%.1f, %.1f)\n"
            "GetItemRectMax() = (%.1f, %.1f)\n"
            "GetItemRectSize() = (%.1f, %.1f)",
            ret,
            im::IsItemFocused(),
            im::IsItemHovered(),
            im::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            im::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            im::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped),
            im::IsItemHovered(ImGuiHoveredFlags_RectOnly),
            im::IsItemActive(),
            im::IsItemEdited(),
            im::IsItemActivated(),
            im::IsItemDeactivated(),
            im::IsItemDeactivatedAfterEdit(),
            im::IsItemVisible(),
            im::IsItemClicked(),
            im::IsItemToggledOpen(),
            im::GetItemRectMin().x, im::GetItemRectMin().y,
            im::GetItemRectMax().x, im::GetItemRectMax().y,
            im::GetItemRectSize().x, im::GetItemRectSize().y
        );

        static bool embed_all_inside_a_child_window = false;
        im::Checkbox("Embed everything inside a child window (for additional testing)", &embed_all_inside_a_child_window);
        if (embed_all_inside_a_child_window)
            im::BeginChild("outer_child", ImVec2(0, im::GetFontSize() * 20), true);

        // Testing IsWindowFocused() function with its various flags.
        // Note that the ImGuiFocusedFlags_XXX flags can be combined.
        im::BulletText(
            "IsWindowFocused() = %d\n"
            "IsWindowFocused(_ChildWindows) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowFocused(_RootWindow) = %d\n"
            "IsWindowFocused(_AnyWindow) = %d\n",
            im::IsWindowFocused(),
            im::IsWindowFocused(ImGuiFocusedFlags_ChildWindows),
            im::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow),
            im::IsWindowFocused(ImGuiFocusedFlags_RootWindow),
            im::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));

        // Testing IsWindowHovered() function with its various flags.
        // Note that the ImGuiHoveredFlags_XXX flags can be combined.
        im::BulletText(
            "IsWindowHovered() = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsWindowHovered(_ChildWindows) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowHovered(_ChildWindows|_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_RootWindow) = %d\n"
            "IsWindowHovered(_AnyWindow) = %d\n",
            im::IsWindowHovered(),
            im::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            im::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            im::IsWindowHovered(ImGuiHoveredFlags_ChildWindows),
            im::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
            im::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            im::IsWindowHovered(ImGuiHoveredFlags_RootWindow),
            im::IsWindowHovered(ImGuiHoveredFlags_AnyWindow));

        im::BeginChild("child", ImVec2(0, 50), true);
        im::Text("This is another child window for testing the _ChildWindows flag.");
        im::EndChild();
        if (embed_all_inside_a_child_window)
            im::EndChild();

        static char dummy_str[] = "This is a dummy field to be able to tab-out of the widgets above.";
        im::InputText("dummy", dummy_str, IM_ARRAYSIZE(dummy_str), ImGuiInputTextFlags_ReadOnly);

        // Calling IsItemHovered() after begin returns the hovered status of the title bar.
        // This is useful in particular if you want to create a context menu (with BeginPopupContextItem) associated to the title bar of a window.
        static bool test_window = false;
        im::Checkbox("Hovered/Active tests after Begin() for title bar testing", &test_window);
        if (test_window)
        {
            im::Begin("Title bar Hovered/Active tests", &test_window);
            if (im::BeginPopupContextItem()) // <-- This is using IsItemHovered()
            {
                if (im::MenuItem("Close")) { test_window = false; }
                im::EndPopup();
            }
            im::Text(
                "IsItemHovered() after begin = %d (== is title bar hovered)\n"
                "IsItemActive() after begin = %d (== is window being clicked/moved)\n",
                im::IsItemHovered(), im::IsItemActive());
            im::End();
        }

        im::TreePop();
    }
}

static void ShowDemoWindowLayout()
{
    if (!im::CollapsingHeader("Layout"))
        return;

    if (im::TreeNode("Child windows"))
    {
        HelpMarker("Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window.");
        static bool disable_mouse_wheel = false;
        static bool disable_menu = false;
        im::Checkbox("Disable Mouse Wheel", &disable_mouse_wheel);
        im::Checkbox("Disable Menu", &disable_menu);

        static int line = 50;
        bool goto_line = im::Button("Goto");
        im::SameLine();
        im::SetNextItemWidth(100);
        goto_line |= im::InputInt("##Line", &line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);

        // Child 1: no border, enable horizontal scrollbar
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0);
            im::BeginChild("Child1", ImVec2(im::GetWindowContentRegionWidth() * 0.5f, 260), false, window_flags);
            for (int i = 0; i < 100; i++)
            {
                im::Text("%04d: scrollable region", i);
                if (goto_line && line == i)
                    im::SetScrollHereY();
            }
            if (goto_line && line >= 100)
                im::SetScrollHereY();
            im::EndChild();
        }

        im::SameLine();

        // Child 2: rounded border
        {
            ImGuiWindowFlags window_flags = (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0) | (disable_menu ? 0 : ImGuiWindowFlags_MenuBar);
            im::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            im::BeginChild("Child2", ImVec2(0, 260), true, window_flags);
            if (!disable_menu && im::BeginMenuBar())
            {
                if (im::BeginMenu("Menu"))
                {
                    ShowExampleMenuFile();
                    im::EndMenu();
                }
                im::EndMenuBar();
            }
            im::Columns(2);
            for (int i = 0; i < 100; i++)
            {
                char buf[32];
                sprintf(buf, "%03d", i);
                im::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                im::NextColumn();
            }
            im::EndChild();
            im::PopStyleVar();
        }

        im::Separator();

        // Demonstrate a few extra things
        // - Changing ImGuiCol_ChildBg (which is transparent black in default styles)
        // - Using SetCursorPos() to position the child window (because the child window is an item from the POV of the parent window)
        //   You can also call SetNextWindowPos() to position the child window. The parent window will effectively layout from this position.
        // - Using ImGui::GetItemRectMin/Max() to query the "item" state (because the child window is an item from the POV of the parent window)
        //   See "Widgets" -> "Querying Status (Active/Focused/Hovered etc.)" section for more details about this.
        {
            im::SetCursorPosX(im::GetCursorPosX() + 10);
            im::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 0, 0, 100));
            im::BeginChild("blah", ImVec2(200, 100), true, ImGuiWindowFlags_None);
            for (int n = 0; n < 50; n++)
                im::Text("Some test %d", n);
            im::EndChild();
            ImVec2 child_rect_min = im::GetItemRectMin();
            ImVec2 child_rect_max = im::GetItemRectMax();
            im::PopStyleColor();
            im::Text("Rect of child window is: (%.0f,%.0f) (%.0f,%.0f)", child_rect_min.x, child_rect_min.y, child_rect_max.x, child_rect_max.y);
        }

        im::TreePop();
    }

    if (im::TreeNode("Widgets Width"))
    {
        // Use SetNextItemWidth() to set the width of a single upcoming item.
        // Use PushItemWidth()/PopItemWidth() to set the width of a group of items.
        static float f = 0.0f;
        im::Text("SetNextItemWidth/PushItemWidth(100)");
        im::SameLine(); HelpMarker("Fixed width.");
        im::SetNextItemWidth(100);
        im::DragFloat("float##1", &f);

        im::Text("SetNextItemWidth/PushItemWidth(GetWindowWidth() * 0.5f)");
        im::SameLine(); HelpMarker("Half of window width.");
        im::SetNextItemWidth(im::GetWindowWidth() * 0.5f);
        im::DragFloat("float##2", &f);

        im::Text("SetNextItemWidth/PushItemWidth(GetContentRegionAvail().x * 0.5f)");
        im::SameLine(); HelpMarker("Half of available width.\n(~ right-cursor_pos)\n(works within a column set)");
        im::SetNextItemWidth(im::GetContentRegionAvail().x * 0.5f);
        im::DragFloat("float##3", &f);

        im::Text("SetNextItemWidth/PushItemWidth(-100)");
        im::SameLine(); HelpMarker("Align to right edge minus 100");
        im::SetNextItemWidth(-100);
        im::DragFloat("float##4", &f);

        // Demonstrate using PushItemWidth to surround three items. Calling SetNextItemWidth() before each of them would have the same effect.
        im::Text("SetNextItemWidth/PushItemWidth(-1)");
        im::SameLine(); HelpMarker("Align to right edge");
        im::PushItemWidth(-1);
        im::DragFloat("##float5a", &f);
        im::DragFloat("##float5b", &f);
        im::DragFloat("##float5c", &f);
        im::PopItemWidth();

        im::TreePop();
    }

    if (im::TreeNode("Basic Horizontal Layout"))
    {
        im::TextWrapped("(Use ImGui::SameLine() to keep adding items to the right of the preceding item)");

        // Text
        im::Text("Two items: Hello"); im::SameLine();
        im::TextColored(ImVec4(1,1,0,1), "Sailor");

        // Adjust spacing
        im::Text("More spacing: Hello"); im::SameLine(0, 20);
        im::TextColored(ImVec4(1,1,0,1), "Sailor");

        // Button
        im::AlignTextToFramePadding();
        im::Text("Normal buttons"); im::SameLine();
        im::Button("Banana"); im::SameLine();
        im::Button("Apple"); im::SameLine();
        im::Button("Corniflower");

        // Button
        im::Text("Small buttons"); im::SameLine();
        im::SmallButton("Like this one"); im::SameLine();
        im::Text("can fit within a text block.");

        // Aligned to arbitrary position. Easy/cheap column.
        im::Text("Aligned");
        im::SameLine(150); im::Text("x=150");
        im::SameLine(300); im::Text("x=300");
        im::Text("Aligned");
        im::SameLine(150); im::SmallButton("x=150");
        im::SameLine(300); im::SmallButton("x=300");

        // Checkbox
        static bool c1 = false, c2 = false, c3 = false, c4 = false;
        im::Checkbox("My", &c1); im::SameLine();
        im::Checkbox("Tailor", &c2); im::SameLine();
        im::Checkbox("Is", &c3); im::SameLine();
        im::Checkbox("Rich", &c4);

        // Various
        static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
        im::PushItemWidth(80);
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD" };
        static int item = -1;
        im::Combo("Combo", &item, items, IM_ARRAYSIZE(items)); im::SameLine();
        im::SliderFloat("X", &f0, 0.0f, 5.0f); im::SameLine();
        im::SliderFloat("Y", &f1, 0.0f, 5.0f); im::SameLine();
        im::SliderFloat("Z", &f2, 0.0f, 5.0f);
        im::PopItemWidth();

        im::PushItemWidth(80);
        im::Text("Lists:");
        static int selection[4] = { 0, 1, 2, 3 };
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) im::SameLine();
            im::PushID(i);
            im::ListBox("", &selection[i], items, IM_ARRAYSIZE(items));
            im::PopID();
            //if (ImGui::IsItemHovered()) ImGui::SetTooltip("ListBox %d hovered", i);
        }
        im::PopItemWidth();

        // Dummy
        ImVec2 button_sz(40, 40);
        im::Button("A", button_sz); im::SameLine();
        im::Dummy(button_sz); im::SameLine();
        im::Button("B", button_sz);

        // Manually wrapping (we should eventually provide this as an automatic layout feature, but for now you can do it manually)
        im::Text("Manually wrapping:");
        ImGuiStyle& style = im::GetStyle();
        int buttons_count = 20;
        float window_visible_x2 = im::GetWindowPos().x + im::GetWindowContentRegionMax().x;
        for (int n = 0; n < buttons_count; n++)
        {
            im::PushID(n);
            im::Button("Box", button_sz);
            float last_button_x2 = im::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
            if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
                im::SameLine();
            im::PopID();
        }

        im::TreePop();
    }

    if (im::TreeNode("Tabs"))
    {
        if (im::TreeNode("Basic"))
        {
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (im::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (im::BeginTabItem("Avocado"))
                {
                    im::Text("This is the Avocado tab!\nblah blah blah blah blah");
                    im::EndTabItem();
                }
                if (im::BeginTabItem("Broccoli"))
                {
                    im::Text("This is the Broccoli tab!\nblah blah blah blah blah");
                    im::EndTabItem();
                }
                if (im::BeginTabItem("Cucumber"))
                {
                    im::Text("This is the Cucumber tab!\nblah blah blah blah blah");
                    im::EndTabItem();
                }
                im::EndTabBar();
            }
            im::Separator();
            im::TreePop();
        }

        if (im::TreeNode("Advanced & Close Button"))
        {
            // Expose a couple of the available flags. In most cases you may just call BeginTabBar() with no flags (0).
            static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
            im::CheckboxFlags("ImGuiTabBarFlags_Reorderable", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_Reorderable);
            im::CheckboxFlags("ImGuiTabBarFlags_AutoSelectNewTabs", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_AutoSelectNewTabs);
            im::CheckboxFlags("ImGuiTabBarFlags_TabListPopupButton", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_TabListPopupButton);
            im::CheckboxFlags("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
            if ((tab_bar_flags & ImGuiTabBarFlags_FittingPolicyMask_) == 0)
                tab_bar_flags |= ImGuiTabBarFlags_FittingPolicyDefault_;
            if (im::CheckboxFlags("ImGuiTabBarFlags_FittingPolicyResizeDown", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_FittingPolicyResizeDown))
                tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyResizeDown);
            if (im::CheckboxFlags("ImGuiTabBarFlags_FittingPolicyScroll", (unsigned int*)&tab_bar_flags, ImGuiTabBarFlags_FittingPolicyScroll))
                tab_bar_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyScroll);

            // Tab Bar
            const char* names[4] = { "Artichoke", "Beetroot", "Celery", "Daikon" };
            static bool opened[4] = { true, true, true, true }; // Persistent user state
            for (int n = 0; n < IM_ARRAYSIZE(opened); n++)
            {
                if (n > 0) { im::SameLine(); }
                im::Checkbox(names[n], &opened[n]);
            }

            // Passing a bool* to BeginTabItem() is similar to passing one to Begin(): the underlying bool will be set to false when the tab is closed.
            if (im::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                for (int n = 0; n < IM_ARRAYSIZE(opened); n++)
                    if (opened[n] && im::BeginTabItem(names[n], &opened[n], ImGuiTabItemFlags_None))
                    {
                        im::Text("This is the %s tab!", names[n]);
                        if (n & 1)
                            im::Text("I am an odd tab.");
                        im::EndTabItem();
                    }
                im::EndTabBar();
            }
            im::Separator();
            im::TreePop();
        }
        im::TreePop();
    }

    if (im::TreeNode("Groups"))
    {
        HelpMarker("BeginGroup() basically locks the horizontal position for new line. EndGroup() bundles the whole group so that you can use \"item\" functions such as IsItemHovered()/IsItemActive() or SameLine() etc. on the whole group.");
        im::BeginGroup();
        {
            im::BeginGroup();
            im::Button("AAA");
            im::SameLine();
            im::Button("BBB");
            im::SameLine();
            im::BeginGroup();
            im::Button("CCC");
            im::Button("DDD");
            im::EndGroup();
            im::SameLine();
            im::Button("EEE");
            im::EndGroup();
            if (im::IsItemHovered())
                im::SetTooltip("First group hovered");
        }
        // Capture the group size and create widgets using the same size
        ImVec2 size = im::GetItemRectSize();
        const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
        im::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

        im::Button("ACTION", ImVec2((size.x - im::GetStyle().ItemSpacing.x)*0.5f, size.y));
        im::SameLine();
        im::Button("REACTION", ImVec2((size.x - im::GetStyle().ItemSpacing.x)*0.5f, size.y));
        im::EndGroup();
        im::SameLine();

        im::Button("LEVERAGE\nBUZZWORD", size);
        im::SameLine();

        if (im::ListBoxHeader("List", size))
        {
            im::Selectable("Selected", true);
            im::Selectable("Not Selected", false);
            im::ListBoxFooter();
        }

        im::TreePop();
    }

    if (im::TreeNode("Text Baseline Alignment"))
    {
        {
            im::BulletText("Text baseline:");
            im::SameLine();
            HelpMarker("This is testing the vertical alignment that gets applied on text to keep it aligned with widgets. Lines only composed of text or \"small\" widgets fit in less vertical spaces than lines with normal widgets.");
            im::Indent();

            im::Text("KO Blahblah"); im::SameLine();
            im::Button("Some framed item"); im::SameLine();
            HelpMarker("Baseline of button will look misaligned with text..");

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            // Because we don't know what's coming after the Text() statement, we need to move the text baseline down by FramePadding.y
            im::AlignTextToFramePadding();
            im::Text("OK Blahblah"); im::SameLine();
            im::Button("Some framed item"); im::SameLine();
            HelpMarker("We call AlignTextToFramePadding() to vertically align the text baseline by +FramePadding.y");

            // SmallButton() uses the same vertical padding as Text
            im::Button("TEST##1"); im::SameLine();
            im::Text("TEST"); im::SameLine();
            im::SmallButton("TEST##2");

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            im::AlignTextToFramePadding();
            im::Text("Text aligned to framed item"); im::SameLine();
            im::Button("Item##1"); im::SameLine();
            im::Text("Item"); im::SameLine();
            im::SmallButton("Item##2"); im::SameLine();
            im::Button("Item##3");

            im::Unindent();
        }

        im::Spacing();

        {
            im::BulletText("Multi-line text:");
            im::Indent();
            im::Text("One\nTwo\nThree"); im::SameLine();
            im::Text("Hello\nWorld"); im::SameLine();
            im::Text("Banana");

            im::Text("Banana"); im::SameLine();
            im::Text("Hello\nWorld"); im::SameLine();
            im::Text("One\nTwo\nThree");

            im::Button("HOP##1"); im::SameLine();
            im::Text("Banana"); im::SameLine();
            im::Text("Hello\nWorld"); im::SameLine();
            im::Text("Banana");

            im::Button("HOP##2"); im::SameLine();
            im::Text("Hello\nWorld"); im::SameLine();
            im::Text("Banana");
            im::Unindent();
        }

        im::Spacing();

        {
            im::BulletText("Misc items:");
            im::Indent();

            // SmallButton() sets FramePadding to zero. Text baseline is aligned to match baseline of previous Button
            im::Button("80x80", ImVec2(80, 80));
            im::SameLine();
            im::Button("50x50", ImVec2(50, 50));
            im::SameLine();
            im::Button("Button()");
            im::SameLine();
            im::SmallButton("SmallButton()");

            // Tree
            const float spacing = im::GetStyle().ItemInnerSpacing.x;
            im::Button("Button##1");
            im::SameLine(0.0f, spacing);
            if (im::TreeNode("Node##1")) { for (int i = 0; i < 6; i++) im::BulletText("Item %d..", i); im::TreePop(); }    // Dummy tree data

            im::AlignTextToFramePadding();           // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
            bool node_open = im::TreeNode("Node##2");// Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
            im::SameLine(0.0f, spacing); im::Button("Button##2");
            if (node_open) { for (int i = 0; i < 6; i++) im::BulletText("Item %d..", i); im::TreePop(); }   // Dummy tree data

            // Bullet
            im::Button("Button##3");
            im::SameLine(0.0f, spacing);
            im::BulletText("Bullet text");

            im::AlignTextToFramePadding();
            im::BulletText("Node");
            im::SameLine(0.0f, spacing); im::Button("Button##4");
            im::Unindent();
        }

        im::TreePop();
    }

    if (im::TreeNode("Scrolling"))
    {
        // Vertical scroll functions
        HelpMarker("Use SetScrollHereY() or SetScrollFromPosY() to scroll to a given vertical position.");

        static int track_item = 50;
        static bool enable_track = true;
        static bool enable_extra_decorations = false;
        static float scroll_to_off_px = 0.0f;
        static float scroll_to_pos_px = 200.0f;

        im::Checkbox("Decoration", &enable_extra_decorations);
        im::SameLine();
        HelpMarker("We expose this for testing because scrolling sometimes had issues with window decoration such as menu-bars.");

        im::Checkbox("Track", &enable_track);
        im::PushItemWidth(100);
        im::SameLine(140); enable_track |= im::DragInt("##item", &track_item, 0.25f, 0, 99, "Item = %d");

        bool scroll_to_off = im::Button("Scroll Offset");
        im::SameLine(140); scroll_to_off |= im::DragFloat("##off", &scroll_to_off_px, 1.00f, 0, FLT_MAX, "+%.0f px");

        bool scroll_to_pos = im::Button("Scroll To Pos");
        im::SameLine(140); scroll_to_pos |= im::DragFloat("##pos", &scroll_to_pos_px, 1.00f, -10, FLT_MAX, "X/Y = %.0f px");
        im::PopItemWidth();

        if (scroll_to_off || scroll_to_pos)
            enable_track = false;

        ImGuiStyle& style = im::GetStyle();
        float child_w = (im::GetContentRegionAvail().x - 4 * style.ItemSpacing.x) / 5;
        if (child_w < 1.0f)
            child_w = 1.0f;
        im::PushID("##VerticalScrolling");
        for (int i = 0; i < 5; i++)
        {
            if (i > 0) im::SameLine();
            im::BeginGroup();
            const char* names[] = { "Top", "25%", "Center", "75%", "Bottom" };
            im::TextUnformatted(names[i]);

            ImGuiWindowFlags child_flags = enable_extra_decorations ? ImGuiWindowFlags_MenuBar : 0;
            bool window_visible = im::BeginChild(im::GetID((void*)(intptr_t)i), ImVec2(child_w, 200.0f), true, child_flags);
            if (im::BeginMenuBar())
            {
                im::TextUnformatted("abc");
                im::EndMenuBar();
            }
            if (scroll_to_off)
                im::SetScrollY(scroll_to_off_px);
            if (scroll_to_pos)
                im::SetScrollFromPosY(im::GetCursorStartPos().y + scroll_to_pos_px, i * 0.25f);
            if (window_visible) // Avoid calling SetScrollHereY when running with culled items
            {
                for (int item = 0; item < 100; item++)
                {
                    if (enable_track && item == track_item)
                    {
                        im::TextColored(ImVec4(1, 1, 0, 1), "Item %d", item);
                        im::SetScrollHereY(i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
                    }
                    else
                    {
                        im::Text("Item %d", item);
                    }
                }
            }
            float scroll_y = im::GetScrollY();
            float scroll_max_y = im::GetScrollMaxY();
            im::EndChild();
            im::Text("%.0f/%.0f", scroll_y, scroll_max_y);
            im::EndGroup();
        }
        im::PopID();

        // Horizontal scroll functions
        im::Spacing();
        HelpMarker("Use SetScrollHereX() or SetScrollFromPosX() to scroll to a given horizontal position.\n\nUsing the \"Scroll To Pos\" button above will make the discontinuity at edges visible: scrolling to the top/bottom/left/right-most item will add an additional WindowPadding to reflect on reaching the edge of the list.\n\nBecause the clipping rectangle of most window hides half worth of WindowPadding on the left/right, using SetScrollFromPosX(+1) will usually result in clipped text whereas the equivalent SetScrollFromPosY(+1) wouldn't.");
        im::PushID("##HorizontalScrolling");
        for (int i = 0; i < 5; i++)
        {
            float child_height = im::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
            ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (enable_extra_decorations ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
            bool window_visible = im::BeginChild(im::GetID((void*)(intptr_t)i), ImVec2(-100, child_height), true, child_flags);
            if (scroll_to_off)
                im::SetScrollX(scroll_to_off_px);
            if (scroll_to_pos)
                im::SetScrollFromPosX(im::GetCursorStartPos().x + scroll_to_pos_px, i * 0.25f);
            if (window_visible) // Avoid calling SetScrollHereY when running with culled items
            {
                for (int item = 0; item < 100; item++)
                {
                    if (enable_track && item == track_item)
                    {
                        im::TextColored(ImVec4(1, 1, 0, 1), "Item %d", item);
                        im::SetScrollHereX(i * 0.25f); // 0.0f:left, 0.5f:center, 1.0f:right
                    }
                    else
                    {
                        im::Text("Item %d", item);
                    }
                    im::SameLine();
                }
            }
            float scroll_x = im::GetScrollX();
            float scroll_max_x = im::GetScrollMaxX();
            im::EndChild();
            im::SameLine();
            const char* names[] = { "Left", "25%", "Center", "75%", "Right" };
            im::Text("%s\n%.0f/%.0f", names[i], scroll_x, scroll_max_x);
            im::Spacing();
        }
        im::PopID();

        // Miscellaneous Horizontal Scrolling Demo
        HelpMarker("Horizontal scrolling for a window has to be enabled explicitly via the ImGuiWindowFlags_HorizontalScrollbar flag.\n\nYou may want to explicitly specify content width by calling SetNextWindowContentWidth() before Begin().");
        static int lines = 7;
        im::SliderInt("Lines", &lines, 1, 15);
        im::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
        im::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 1.0f));
        im::BeginChild("scrolling", ImVec2(0, im::GetFrameHeightWithSpacing() * 7 + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
        for (int line = 0; line < lines; line++)
        {
            // Display random stuff (for the sake of this trivial demo we are using basic Button+SameLine. If you want to create your own time line for a real application you may be better off
            // manipulating the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets yourself. You may also want to use the lower-level ImDrawList API)
            int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
            for (int n = 0; n < num_buttons; n++)
            {
                if (n > 0) im::SameLine();
                im::PushID(n + line * 1000);
                char num_buf[16];
                sprintf(num_buf, "%d", n);
                const char* label = (!(n%15)) ? "FizzBuzz" : (!(n%3)) ? "Fizz" : (!(n%5)) ? "Buzz" : num_buf;
                float hue = n*0.05f;
                im::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
                im::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
                im::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
                im::Button(label, ImVec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
                im::PopStyleColor(3);
                im::PopID();
            }
        }
        float scroll_x = im::GetScrollX();
        float scroll_max_x = im::GetScrollMaxX();
        im::EndChild();
        im::PopStyleVar(2);
        float scroll_x_delta = 0.0f;
        im::SmallButton("<<"); if (im::IsItemActive()) { scroll_x_delta = -im::GetIO().DeltaTime * 1000.0f; } im::SameLine();
        im::Text("Scroll from code"); im::SameLine();
        im::SmallButton(">>"); if (im::IsItemActive()) { scroll_x_delta = +im::GetIO().DeltaTime * 1000.0f; } im::SameLine();
        im::Text("%.0f/%.0f", scroll_x, scroll_max_x);
        if (scroll_x_delta != 0.0f)
        {
            im::BeginChild("scrolling"); // Demonstrate a trick: you can use Begin to set yourself in the context of another window (here we are already out of your child window)
            im::SetScrollX(im::GetScrollX() + scroll_x_delta);
            im::EndChild();
        }
        im::Spacing();

        static bool show_horizontal_contents_size_demo_window = false;
        im::Checkbox("Show Horizontal contents size demo window", &show_horizontal_contents_size_demo_window);

        if (show_horizontal_contents_size_demo_window)
        {
            static bool show_h_scrollbar = true;
            static bool show_button = true;
            static bool show_tree_nodes = true;
            static bool show_text_wrapped = false;
            static bool show_columns = true;
            static bool show_tab_bar = true;
            static bool show_child = false;
            static bool explicit_content_size = false;
            static float contents_size_x = 300.0f;
            if (explicit_content_size)
                im::SetNextWindowContentSize(ImVec2(contents_size_x, 0.0f));
            im::Begin("Horizontal contents size demo window", &show_horizontal_contents_size_demo_window, show_h_scrollbar ? ImGuiWindowFlags_HorizontalScrollbar : 0);
            im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 0));
            im::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 0));
            HelpMarker("Test of different widgets react and impact the work rectangle growing when horizontal scrolling is enabled.\n\nUse 'Metrics->Tools->Show windows rectangles' to visualize rectangles.");
            im::Checkbox("H-scrollbar", &show_h_scrollbar);
            im::Checkbox("Button", &show_button);            // Will grow contents size (unless explicitly overwritten)
            im::Checkbox("Tree nodes", &show_tree_nodes);    // Will grow contents size and display highlight over full width
            im::Checkbox("Text wrapped", &show_text_wrapped);// Will grow and use contents size
            im::Checkbox("Columns", &show_columns);          // Will use contents size
            im::Checkbox("Tab bar", &show_tab_bar);          // Will use contents size
            im::Checkbox("Child", &show_child);              // Will grow and use contents size
            im::Checkbox("Explicit content size", &explicit_content_size);
            im::Text("Scroll %.1f/%.1f %.1f/%.1f", im::GetScrollX(), im::GetScrollMaxX(), im::GetScrollY(), im::GetScrollMaxY());
            if (explicit_content_size)
            {
                im::SameLine();
                im::SetNextItemWidth(100);
                im::DragFloat("##csx", &contents_size_x);
                ImVec2 p = im::GetCursorScreenPos();
                im::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + 10, p.y + 10), IM_COL32_WHITE);
                im::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + contents_size_x - 10, p.y), ImVec2(p.x + contents_size_x, p.y + 10), IM_COL32_WHITE);
                im::Dummy(ImVec2(0, 10));
            }
            im::PopStyleVar(2);
            im::Separator();
            if (show_button)
            {
                im::Button("this is a 300-wide button", ImVec2(300, 0));
            }
            if (show_tree_nodes)
            {
                bool open = true;
                if (im::TreeNode("this is a tree node"))
                {
                    if (im::TreeNode("another one of those tree node..."))
                    {
                        im::Text("Some tree contents");
                        im::TreePop();
                    }
                    im::TreePop();
                }
                im::CollapsingHeader("CollapsingHeader", &open);
            }
            if (show_text_wrapped)
            {
                im::TextWrapped("This text should automatically wrap on the edge of the work rectangle.");
            }
            if (show_columns)
            {
                im::Columns(4);
                for (int n = 0; n < 4; n++)
                {
                    im::Text("Width %.2f", im::GetColumnWidth());
                    im::NextColumn();
                }
                im::Columns(1);
            }
            if (show_tab_bar && im::BeginTabBar("Hello"))
            {
                if (im::BeginTabItem("OneOneOne")) { im::EndTabItem(); }
                if (im::BeginTabItem("TwoTwoTwo")) { im::EndTabItem(); }
                if (im::BeginTabItem("ThreeThreeThree")) { im::EndTabItem(); }
                if (im::BeginTabItem("FourFourFour")) { im::EndTabItem(); }
                im::EndTabBar();
            }
            if (show_child)
            {
                im::BeginChild("child", ImVec2(0,0), true);
                im::EndChild();
            }
            im::End();
        }

        im::TreePop();
    }

    if (im::TreeNode("Clipping"))
    {
        static ImVec2 size(100, 100), offset(50, 20);
        im::TextWrapped("On a per-widget basis we are occasionally clipping text CPU-side if it won't fit in its frame. Otherwise we are doing coarser clipping + passing a scissor rectangle to the renderer. The system is designed to try minimizing both execution and CPU/GPU rendering cost.");
        im::DragFloat2("size", (float*)&size, 0.5f, 1.0f, 200.0f, "%.0f");
        im::TextWrapped("(Click and drag)");
        ImVec2 pos = im::GetCursorScreenPos();
        ImVec4 clip_rect(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
        im::InvisibleButton("##dummy", size);
        if (im::IsItemActive() && im::IsMouseDragging(0)) { offset.x += im::GetIO().MouseDelta.x; offset.y += im::GetIO().MouseDelta.y; }
        im::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(90, 90, 120, 255));
        im::GetWindowDrawList()->AddText(im::GetFont(), im::GetFontSize()*2.0f, ImVec2(pos.x + offset.x, pos.y + offset.y), IM_COL32(255, 255, 255, 255), "Line 1 hello\nLine 2 clip me!", NULL, 0.0f, &clip_rect);
        im::TreePop();
    }
}

static void ShowDemoWindowPopups()
{
    if (!im::CollapsingHeader("Popups & Modal windows"))
        return;

    // The properties of popups windows are:
    // - They block normal mouse hovering detection outside them. (*)
    // - Unless modal, they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
    // - Their visibility state (~bool) is held internally by Dear ImGui instead of being held by the programmer as we are used to with regular Begin() calls.
    //   User can manipulate the visibility state by calling OpenPopup().
    // (*) One can use IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) to bypass it and detect hovering even when normally blocked by a popup.
    // Those three properties are connected. The library needs to hold their visibility state because it can close popups at any time.

    // Typical use for regular windows:
    //   bool my_tool_is_active = false; if (ImGui::Button("Open")) my_tool_is_active = true; [...] if (my_tool_is_active) Begin("My Tool", &my_tool_is_active) { [...] } End();
    // Typical use for popups:
    //   if (ImGui::Button("Open")) ImGui::OpenPopup("MyPopup"); if (ImGui::BeginPopup("MyPopup") { [...] EndPopup(); }

    // With popups we have to go through a library call (here OpenPopup) to manipulate the visibility state.
    // This may be a bit confusing at first but it should quickly make sense. Follow on the examples below.

    if (im::TreeNode("Popups"))
    {
        im::TextWrapped("When a popup is active, it inhibits interacting with windows that are behind the popup. Clicking outside the popup closes it.");

        static int selected_fish = -1;
        const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
        static bool toggles[] = { true, false, false, false, false };

        // Simple selection popup
        // (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        if (im::Button("Select.."))
            im::OpenPopup("my_select_popup");
        im::SameLine();
        im::TextUnformatted(selected_fish == -1 ? "<None>" : names[selected_fish]);
        if (im::BeginPopup("my_select_popup"))
        {
            im::Text("Aquarium");
            im::Separator();
            for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                if (im::Selectable(names[i]))
                    selected_fish = i;
            im::EndPopup();
        }

        // Showing a menu with toggles
        if (im::Button("Toggle.."))
            im::OpenPopup("my_toggle_popup");
        if (im::BeginPopup("my_toggle_popup"))
        {
            for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                im::MenuItem(names[i], "", &toggles[i]);
            if (im::BeginMenu("Sub-menu"))
            {
                im::MenuItem("Click me");
                im::EndMenu();
            }

            im::Separator();
            im::Text("Tooltip here");
            if (im::IsItemHovered())
                im::SetTooltip("I am a tooltip over a popup");

            if (im::Button("Stacked Popup"))
                im::OpenPopup("another popup");
            if (im::BeginPopup("another popup"))
            {
                for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                    im::MenuItem(names[i], "", &toggles[i]);
                if (im::BeginMenu("Sub-menu"))
                {
                    im::MenuItem("Click me");
                    if (im::Button("Stacked Popup"))
                        im::OpenPopup("another popup");
                    if (im::BeginPopup("another popup"))
                    {
                        im::Text("I am the last one here.");
                        im::EndPopup();
                    }
                    im::EndMenu();
                }
                im::EndPopup();
            }
            im::EndPopup();
        }

        // Call the more complete ShowExampleMenuFile which we use in various places of this demo
        if (im::Button("File Menu.."))
            im::OpenPopup("my_file_popup");
        if (im::BeginPopup("my_file_popup"))
        {
            ShowExampleMenuFile();
            im::EndPopup();
        }

        im::TreePop();
    }

    if (im::TreeNode("Context menus"))
    {
        // BeginPopupContextItem() is a helper to provide common/simple popup behavior of essentially doing:
        //    if (IsItemHovered() && IsMouseReleased(0))
        //       OpenPopup(id);
        //    return BeginPopup(id);
        // For more advanced uses you may want to replicate and cuztomize this code. This the comments inside BeginPopupContextItem() implementation.
        static float value = 0.5f;
        im::Text("Value = %.3f (<-- right-click here)", value);
        if (im::BeginPopupContextItem("item context menu"))
        {
            if (im::Selectable("Set to zero")) value = 0.0f;
            if (im::Selectable("Set to PI")) value = 3.1415f;
            im::SetNextItemWidth(-1);
            im::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
            im::EndPopup();
        }

        // We can also use OpenPopupOnItemClick() which is the same as BeginPopupContextItem() but without the Begin call.
        // So here we will make it that clicking on the text field with the right mouse button (1) will toggle the visibility of the popup above.
        im::Text("(You can also right-click me to open the same popup as above.)");
        im::OpenPopupOnItemClick("item context menu", 1);

        // When used after an item that has an ID (here the Button), we can skip providing an ID to BeginPopupContextItem().
        // BeginPopupContextItem() will use the last item ID as the popup ID.
        // In addition here, we want to include your editable label inside the button label. We use the ### operator to override the ID (read FAQ about ID for details)
        static char name[32] = "Label1";
        char buf[64]; sprintf(buf, "Button: %s###Button", name); // ### operator override ID ignoring the preceding label
        im::Button(buf);
        if (im::BeginPopupContextItem())
        {
            im::Text("Edit name:");
            im::InputText("##edit", name, IM_ARRAYSIZE(name));
            if (im::Button("Close"))
                im::CloseCurrentPopup();
            im::EndPopup();
        }
        im::SameLine(); im::Text("(<-- right-click here)");

        im::TreePop();
    }

    if (im::TreeNode("Modals"))
    {
        im::TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside the window.");

        if (im::Button("Delete.."))
            im::OpenPopup("Delete?");

        if (im::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            im::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
            im::Separator();

            //static int dummy_i = 0;
            //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

            static bool dont_ask_me_next_time = false;
            im::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            im::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
            im::PopStyleVar();

            if (im::Button("OK", ImVec2(120, 0))) { im::CloseCurrentPopup(); }
            im::SetItemDefaultFocus();
            im::SameLine();
            if (im::Button("Cancel", ImVec2(120, 0))) { im::CloseCurrentPopup(); }
            im::EndPopup();
        }

        if (im::Button("Stacked modals.."))
            im::OpenPopup("Stacked 1");
        if (im::BeginPopupModal("Stacked 1", NULL, ImGuiWindowFlags_MenuBar))
        {
            if (im::BeginMenuBar())
            {
                if (im::BeginMenu("File"))
                {
                    if (im::MenuItem("Dummy menu item")) {}
                    im::EndMenu();
                }
                im::EndMenuBar();
            }
            im::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

            // Testing behavior of widgets stacking their own regular popups over the modal.
            static int item = 1;
            static float color[4] = { 0.4f,0.7f,0.0f,0.5f };
            im::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
            im::ColorEdit4("color", color);

            if (im::Button("Add another modal.."))
                im::OpenPopup("Stacked 2");

            // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which will close the popup.
            // Note that the visibility state of popups is owned by imgui, so the input value of the bool actually doesn't matter here.
            bool dummy_open = true;
            if (im::BeginPopupModal("Stacked 2", &dummy_open))
            {
                im::Text("Hello from Stacked The Second!");
                if (im::Button("Close"))
                    im::CloseCurrentPopup();
                im::EndPopup();
            }

            if (im::Button("Close"))
                im::CloseCurrentPopup();
            im::EndPopup();
        }

        im::TreePop();
    }

    if (im::TreeNode("Menus inside a regular window"))
    {
        im::TextWrapped("Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
        im::Separator();
        // NB: As a quirk in this very specific example, we want to differentiate the parent of this menu from the parent of the various popup menus above.
        // To do so we are encloding the items in a PushID()/PopID() block to make them two different menusets. If we don't, opening any popup above and hovering our menu here
        // would open it. This is because once a menu is active, we allow to switch to a sibling menu by just hovering on it, which is the desired behavior for regular menus.
        im::PushID("foo");
        im::MenuItem("Menu item", "CTRL+M");
        if (im::BeginMenu("Menu inside a regular window"))
        {
            ShowExampleMenuFile();
            im::EndMenu();
        }
        im::PopID();
        im::Separator();
        im::TreePop();
    }
}

static void ShowDemoWindowColumns()
{
    if (!im::CollapsingHeader("Columns"))
        return;

    im::PushID("Columns");

    static bool disable_indent = false;
    im::Checkbox("Disable tree indentation", &disable_indent);
    im::SameLine();
    HelpMarker("Disable the indenting of tree nodes so demo columns can use the full window width.");
    if (disable_indent)
        im::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);

    // Basic columns
    if (im::TreeNode("Basic"))
    {
        im::Text("Without border:");
        im::Columns(3, "mycolumns3", false);  // 3-ways, no border
        im::Separator();
        for (int n = 0; n < 14; n++)
        {
            char label[32];
            sprintf(label, "Item %d", n);
            if (im::Selectable(label)) {}
            //if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
            im::NextColumn();
        }
        im::Columns(1);
        im::Separator();

        im::Text("With border:");
        im::Columns(4, "mycolumns"); // 4-ways, with border
        im::Separator();
        im::Text("ID"); im::NextColumn();
        im::Text("Name"); im::NextColumn();
        im::Text("Path"); im::NextColumn();
        im::Text("Hovered"); im::NextColumn();
        im::Separator();
        const char* names[3] = { "One", "Two", "Three" };
        const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
        static int selected = -1;
        for (int i = 0; i < 3; i++)
        {
            char label[32];
            sprintf(label, "%04d", i);
            if (im::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
                selected = i;
            bool hovered = im::IsItemHovered();
            im::NextColumn();
            im::Text(names[i]); im::NextColumn();
            im::Text(paths[i]); im::NextColumn();
            im::Text("%d", hovered); im::NextColumn();
        }
        im::Columns(1);
        im::Separator();
        im::TreePop();
    }

    if (im::TreeNode("Borders"))
    {
        // NB: Future columns API should allow automatic horizontal borders.
        static bool h_borders = true;
        static bool v_borders = true;
        static int columns_count = 4;
        const int lines_count = 3;
        im::SetNextItemWidth(im::GetFontSize() * 8);
        im::DragInt("##columns_count", &columns_count, 0.1f, 2, 10, "%d columns");
        if (columns_count < 2)
            columns_count = 2;
        im::SameLine();
        im::Checkbox("horizontal", &h_borders);
        im::SameLine();
        im::Checkbox("vertical", &v_borders);
        im::Columns(columns_count, NULL, v_borders);
        for (int i = 0; i < columns_count * lines_count; i++)
        {
            if (h_borders && im::GetColumnIndex() == 0)
                im::Separator();
            im::Text("%c%c%c", 'a' + i, 'a' + i, 'a' + i);
            im::Text("Width %.2f", im::GetColumnWidth());
            im::Text("Avail %.2f", im::GetContentRegionAvail().x);
            im::Text("Offset %.2f", im::GetColumnOffset());
            im::Text("Long text that is likely to clip");
            im::Button("Button", ImVec2(-FLT_MIN, 0.0f));
            im::NextColumn();
        }
        im::Columns(1);
        if (h_borders)
            im::Separator();
        im::TreePop();
    }

    // Create multiple items in a same cell before switching to next column
    if (im::TreeNode("Mixed items"))
    {
        im::Columns(3, "mixed");
        im::Separator();

        im::Text("Hello");
        im::Button("Banana");
        im::NextColumn();

        im::Text("ImGui");
        im::Button("Apple");
        static float foo = 1.0f;
        im::InputFloat("red", &foo, 0.05f, 0, "%.3f");
        im::Text("An extra line here.");
        im::NextColumn();

        im::Text("Sailor");
        im::Button("Corniflower");
        static float bar = 1.0f;
        im::InputFloat("blue", &bar, 0.05f, 0, "%.3f");
        im::NextColumn();

        if (im::CollapsingHeader("Category A")) { im::Text("Blah blah blah"); } im::NextColumn();
        if (im::CollapsingHeader("Category B")) { im::Text("Blah blah blah"); } im::NextColumn();
        if (im::CollapsingHeader("Category C")) { im::Text("Blah blah blah"); } im::NextColumn();
        im::Columns(1);
        im::Separator();
        im::TreePop();
    }

    // Word wrapping
    if (im::TreeNode("Word-wrapping"))
    {
        im::Columns(2, "word-wrapping");
        im::Separator();
        im::TextWrapped("The quick brown fox jumps over the lazy dog.");
        im::TextWrapped("Hello Left");
        im::NextColumn();
        im::TextWrapped("The quick brown fox jumps over the lazy dog.");
        im::TextWrapped("Hello Right");
        im::Columns(1);
        im::Separator();
        im::TreePop();
    }

    // Scrolling columns
    /*
    if (ImGui::TreeNode("Vertical Scrolling"))
    {
        ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing()+ImGui::GetStyle().ItemSpacing.y));
        ImGui::Columns(3);
        ImGui::Text("ID"); ImGui::NextColumn();
        ImGui::Text("Name"); ImGui::NextColumn();
        ImGui::Text("Path"); ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::BeginChild("##scrollingregion", ImVec2(0, 60));
        ImGui::Columns(3);
        for (int i = 0; i < 10; i++)
        {
            ImGui::Text("%04d", i); ImGui::NextColumn();
            ImGui::Text("Foobar"); ImGui::NextColumn();
            ImGui::Text("/path/foobar/%04d/", i); ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::EndChild();
        ImGui::TreePop();
    }
    */

    if (im::TreeNode("Horizontal Scrolling"))
    {
        im::SetNextWindowContentSize(ImVec2(1500.0f, 0.0f));
        im::BeginChild("##ScrollingRegion", ImVec2(0, im::GetFontSize() * 20), false, ImGuiWindowFlags_HorizontalScrollbar);
        im::Columns(10);
        int ITEMS_COUNT = 2000;
        ImGuiListClipper clipper(ITEMS_COUNT);  // Also demonstrate using the clipper for large list
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                for (int j = 0; j < 10; j++)
                {
                    im::Text("Line %d Column %d...", i, j);
                    im::NextColumn();
                }
        }
        im::Columns(1);
        im::EndChild();
        im::TreePop();
    }

    if (im::TreeNode("Tree"))
    {
        im::Columns(2, "tree", true);
        for (int x = 0; x < 3; x++)
        {
            bool open1 = im::TreeNode((void*)(intptr_t)x, "Node%d", x);
            im::NextColumn();
            im::Text("Node contents");
            im::NextColumn();
            if (open1)
            {
                for (int y = 0; y < 3; y++)
                {
                    bool open2 = im::TreeNode((void*)(intptr_t)y, "Node%d.%d", x, y);
                    im::NextColumn();
                    im::Text("Node contents");
                    if (open2)
                    {
                        im::Text("Even more contents");
                        if (im::TreeNode("Tree in column"))
                        {
                            im::Text("The quick brown fox jumps over the lazy dog");
                            im::TreePop();
                        }
                    }
                    im::NextColumn();
                    if (open2)
                        im::TreePop();
                }
                im::TreePop();
            }
        }
        im::Columns(1);
        im::TreePop();
    }

    if (disable_indent)
        im::PopStyleVar();
    im::PopID();
}

static void ShowDemoWindowMisc()
{
    if (im::CollapsingHeader("Filtering"))
    {
        // Helper class to easy setup a text filter.
        // You may want to implement a more feature-full filtering scheme in your own application.
        static ImGuiTextFilter filter;
        im::Text("Filter usage:\n"
                    "  \"\"         display all lines\n"
                    "  \"xxx\"      display lines containing \"xxx\"\n"
                    "  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
                    "  \"-xxx\"     hide lines containing \"xxx\"");
        filter.Draw();
        const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
        for (int i = 0; i < IM_ARRAYSIZE(lines); i++)
            if (filter.PassFilter(lines[i]))
                im::BulletText("%s", lines[i]);
    }

    if (im::CollapsingHeader("Inputs, Navigation & Focus"))
    {
        ImGuiIO& io = im::GetIO();

        // Display ImGuiIO output flags
        im::Text("WantCaptureMouse: %d", io.WantCaptureMouse);
        im::Text("WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
        im::Text("WantTextInput: %d", io.WantTextInput);
        im::Text("WantSetMousePos: %d", io.WantSetMousePos);
        im::Text("NavActive: %d, NavVisible: %d", io.NavActive, io.NavVisible);

        // Display Keyboard/Mouse state
        if (im::TreeNode("Keyboard, Mouse & Navigation State"))
        {
            if (im::IsMousePosValid())
                im::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
            else
                im::Text("Mouse pos: <INVALID>");
            im::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
            im::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseDownDuration[i] >= 0.0f)   { im::SameLine(); im::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
            im::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (im::IsMouseClicked(i))          { im::SameLine(); im::Text("b%d", i); }
            im::Text("Mouse dbl-clicked:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (im::IsMouseDoubleClicked(i)) { im::SameLine(); im::Text("b%d", i); }
            im::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (im::IsMouseReleased(i))         { im::SameLine(); im::Text("b%d", i); }
            im::Text("Mouse wheel: %.1f", io.MouseWheel);

            im::Text("Keys down:");      for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (io.KeysDownDuration[i] >= 0.0f)     { im::SameLine(); im::Text("%d (0x%X) (%.02f secs)", i, i, io.KeysDownDuration[i]); }
            im::Text("Keys pressed:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (im::IsKeyPressed(i))             { im::SameLine(); im::Text("%d (0x%X)", i, i); }
            im::Text("Keys release:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (im::IsKeyReleased(i))            { im::SameLine(); im::Text("%d (0x%X)", i, i); }
            im::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
            im::Text("Chars queue:");    for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; im::SameLine();  im::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

            im::Text("NavInputs down:"); for (int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if (io.NavInputs[i] > 0.0f)                    { im::SameLine(); im::Text("[%d] %.2f", i, io.NavInputs[i]); }
            im::Text("NavInputs pressed:"); for (int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if (io.NavInputsDownDuration[i] == 0.0f)    { im::SameLine(); im::Text("[%d]", i); }
            im::Text("NavInputs duration:"); for (int i = 0; i < IM_ARRAYSIZE(io.NavInputs); i++) if (io.NavInputsDownDuration[i] >= 0.0f)   { im::SameLine(); im::Text("[%d] %.2f", i, io.NavInputsDownDuration[i]); }

            im::Button("Hovering me sets the\nkeyboard capture flag");
            if (im::IsItemHovered())
                im::CaptureKeyboardFromApp(true);
            im::SameLine();
            im::Button("Holding me clears the\nthe keyboard capture flag");
            if (im::IsItemActive())
                im::CaptureKeyboardFromApp(false);

            im::TreePop();
        }

        if (im::TreeNode("Tabbing"))
        {
            im::Text("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");
            static char buf[32] = "dummy";
            im::InputText("1", buf, IM_ARRAYSIZE(buf));
            im::InputText("2", buf, IM_ARRAYSIZE(buf));
            im::InputText("3", buf, IM_ARRAYSIZE(buf));
            im::PushAllowKeyboardFocus(false);
            im::InputText("4 (tab skip)", buf, IM_ARRAYSIZE(buf));
            //ImGui::SameLine(); HelpMarker("Use ImGui::PushAllowKeyboardFocus(bool)\nto disable tabbing through certain widgets.");
            im::PopAllowKeyboardFocus();
            im::InputText("5", buf, IM_ARRAYSIZE(buf));
            im::TreePop();
        }

        if (im::TreeNode("Focus from code"))
        {
            bool focus_1 = im::Button("Focus on 1"); im::SameLine();
            bool focus_2 = im::Button("Focus on 2"); im::SameLine();
            bool focus_3 = im::Button("Focus on 3");
            int has_focus = 0;
            static char buf[128] = "click on a button to set focus";

            if (focus_1) im::SetKeyboardFocusHere();
            im::InputText("1", buf, IM_ARRAYSIZE(buf));
            if (im::IsItemActive()) has_focus = 1;

            if (focus_2) im::SetKeyboardFocusHere();
            im::InputText("2", buf, IM_ARRAYSIZE(buf));
            if (im::IsItemActive()) has_focus = 2;

            im::PushAllowKeyboardFocus(false);
            if (focus_3) im::SetKeyboardFocusHere();
            im::InputText("3 (tab skip)", buf, IM_ARRAYSIZE(buf));
            if (im::IsItemActive()) has_focus = 3;
            im::PopAllowKeyboardFocus();

            if (has_focus)
                im::Text("Item with focus: %d", has_focus);
            else
                im::Text("Item with focus: <none>");

            // Use >= 0 parameter to SetKeyboardFocusHere() to focus an upcoming item
            static float f3[3] = { 0.0f, 0.0f, 0.0f };
            int focus_ahead = -1;
            if (im::Button("Focus on X")) { focus_ahead = 0; } im::SameLine();
            if (im::Button("Focus on Y")) { focus_ahead = 1; } im::SameLine();
            if (im::Button("Focus on Z")) { focus_ahead = 2; }
            if (focus_ahead != -1) im::SetKeyboardFocusHere(focus_ahead);
            im::SliderFloat3("Float3", &f3[0], 0.0f, 1.0f);

            im::TextWrapped("NB: Cursor & selection are preserved when refocusing last used item in code.");
            im::TreePop();
        }

        if (im::TreeNode("Dragging"))
        {
            im::TextWrapped("You can use ImGui::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
            for (int button = 0; button < 3; button++)
                im::Text("IsMouseDragging(%d):\n  w/ default threshold: %d,\n  w/ zero threshold: %d\n  w/ large threshold: %d",
                    button, im::IsMouseDragging(button), im::IsMouseDragging(button, 0.0f), im::IsMouseDragging(button, 20.0f));

            im::Button("Drag Me");
            if (im::IsItemActive())
                im::GetForegroundDrawList()->AddLine(io.MouseClickedPos[0], io.MousePos, im::GetColorU32(ImGuiCol_Button), 4.0f); // Draw a line between the button and the mouse cursor

            // Drag operations gets "unlocked" when the mouse has moved past a certain threshold (the default threshold is stored in io.MouseDragThreshold)
            // You can request a lower or higher threshold using the second parameter of IsMouseDragging() and GetMouseDragDelta()
            ImVec2 value_raw = im::GetMouseDragDelta(0, 0.0f);
            ImVec2 value_with_lock_threshold = im::GetMouseDragDelta(0);
            ImVec2 mouse_delta = io.MouseDelta;
            im::Text("GetMouseDragDelta(0):\n  w/ default threshold: (%.1f, %.1f),\n  w/ zero threshold: (%.1f, %.1f)\nMouseDelta: (%.1f, %.1f)", value_with_lock_threshold.x, value_with_lock_threshold.y, value_raw.x, value_raw.y, mouse_delta.x, mouse_delta.y);
            im::TreePop();
        }

        if (im::TreeNode("Mouse cursors"))
        {
            const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };
            IM_ASSERT(IM_ARRAYSIZE(mouse_cursors_names) == ImGuiMouseCursor_COUNT);

            im::Text("Current mouse cursor = %d: %s", im::GetMouseCursor(), mouse_cursors_names[im::GetMouseCursor()]);
            im::Text("Hover to see mouse cursors:");
            im::SameLine(); HelpMarker("Your application can render a different mouse cursor based on what ImGui::GetMouseCursor() returns. If software cursor rendering (io.MouseDrawCursor) is set ImGui will draw the right cursor for you, otherwise your backend needs to handle it.");
            for (int i = 0; i < ImGuiMouseCursor_COUNT; i++)
            {
                char label[32];
                sprintf(label, "Mouse cursor %d: %s", i, mouse_cursors_names[i]);
                im::Bullet(); im::Selectable(label, false);
                if (im::IsItemHovered() || im::IsItemFocused())
                    im::SetMouseCursor(i);
            }
            im::TreePop();
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] About Window / ShowAboutWindow()
// Access from Dear ImGui Demo -> Tools -> About
//-----------------------------------------------------------------------------

void im::ShowAboutWindow(bool* p_open)
{
    if (!im::Begin("About Dear ImGui", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        im::End();
        return;
    }
    im::Text("Dear ImGui %s", im::GetVersion());
    im::Separator();
    im::Text("By Omar Cornut and all Dear ImGui contributors.");
    im::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");

    static bool show_config_info = false;
    im::Checkbox("Config/Build Information", &show_config_info);
    if (show_config_info)
    {
        ImGuiIO& io = im::GetIO();
        ImGuiStyle& style = im::GetStyle();

        bool copy_to_clipboard = im::Button("Copy to clipboard");
        im::BeginChildFrame(im::GetID("cfginfos"), ImVec2(0, im::GetTextLineHeightWithSpacing() * 18), ImGuiWindowFlags_NoMove);
        if (copy_to_clipboard)
        {
            im::LogToClipboard();
            im::LogText("```\n"); // Back quotes will make the text appears without formatting when pasting to GitHub
        }

        im::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
        im::Separator();
        im::Text("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
        im::Text("define: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_WIN32_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_FILE_FUNCTIONS
        ImGui::Text("define: IMGUI_DISABLE_FILE_FUNCTIONS");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
        ImGui::Text("define: IMGUI_DISABLE_DEFAULT_ALLOCATORS");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
        ImGui::Text("define: IMGUI_USE_BGRA_PACKED_COLOR");
#endif
#ifdef _WIN32
        im::Text("define: _WIN32");
#endif
#ifdef _WIN64
        im::Text("define: _WIN64");
#endif
#ifdef __linux__
        ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
        ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
        im::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef __MINGW32__
        ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
        ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
        ImGui::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
        ImGui::Text("define: __clang_version__=%s", __clang_version__);
#endif
        im::Separator();
        im::Text("io.BackendPlatformName: %s", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
        im::Text("io.BackendRendererName: %s", io.BackendRendererName ? io.BackendRendererName : "NULL");
        im::Text("io.ConfigFlags: 0x%08X", io.ConfigFlags);
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        im::Text(" NavEnableKeyboard");
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         im::Text(" NavEnableGamepad");
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableSetMousePos)     im::Text(" NavEnableSetMousePos");
        if (io.ConfigFlags & ImGuiConfigFlags_NavNoCaptureKeyboard)     im::Text(" NavNoCaptureKeyboard");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  im::Text(" NoMouse");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      im::Text(" NoMouseCursorChange");
        if (io.MouseDrawCursor)                                         im::Text("io.MouseDrawCursor");
        if (io.ConfigMacOSXBehaviors)                                   im::Text("io.ConfigMacOSXBehaviors");
        if (io.ConfigInputTextCursorBlink)                              im::Text("io.ConfigInputTextCursorBlink");
        if (io.ConfigWindowsResizeFromEdges)                            im::Text("io.ConfigWindowsResizeFromEdges");
        if (io.ConfigWindowsMoveFromTitleBarOnly)                       im::Text("io.ConfigWindowsMoveFromTitleBarOnly");
        if (io.ConfigWindowsMemoryCompactTimer >= 0.0f)                 im::Text("io.ConfigWindowsMemoryCompactTimer = %.1ff", io.ConfigWindowsMemoryCompactTimer);
        im::Text("io.BackendFlags: 0x%08X", io.BackendFlags);
        if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             im::Text(" HasGamepad");
        if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        im::Text(" HasMouseCursors");
        if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         im::Text(" HasSetMousePos");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset)   im::Text(" RendererHasVtxOffset");
        im::Separator();
        im::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexWidth, io.Fonts->TexHeight);
        im::Text("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y);
        im::Text("io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        im::Separator();
        im::Text("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y);
        im::Text("style.WindowBorderSize: %.2f", style.WindowBorderSize);
        im::Text("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y);
        im::Text("style.FrameRounding: %.2f", style.FrameRounding);
        im::Text("style.FrameBorderSize: %.2f", style.FrameBorderSize);
        im::Text("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y);
        im::Text("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

        if (copy_to_clipboard)
        {
            im::LogText("\n```\n");
            im::LogFinish();
        }
        im::EndChildFrame();
    }
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Style Editor / ShowStyleEditor()
//-----------------------------------------------------------------------------
// - ShowStyleSelector()
// - ShowFontSelector()
// - ShowStyleEditor()
//-----------------------------------------------------------------------------

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
// Here we use the simplified Combo() api that packs items into a single literal string. Useful for quick combo boxes where the choices are known locally.
bool im::ShowStyleSelector(const char* label)
{
    static int style_idx = -1;
    if (im::Combo(label, &style_idx, "Classic\0Dark\0Light\0"))
    {
        switch (style_idx)
        {
        case 0: im::StyleColorsClassic(); break;
        case 1: im::StyleColorsDark(); break;
        case 2: im::StyleColorsLight(); break;
        }
        return true;
    }
    return false;
}

// Demo helper function to select among loaded fonts.
// Here we use the regular BeginCombo()/EndCombo() api which is more the more flexible one.
void im::ShowFontSelector(const char* label)
{
    ImGuiIO& io = im::GetIO();
    ImFont* font_current = im::GetFont();
    if (im::BeginCombo(label, font_current->GetDebugName()))
    {
        for (int n = 0; n < io.Fonts->Fonts.Size; n++)
        {
            ImFont* font = io.Fonts->Fonts[n];
            im::PushID((void*)font);
            if (im::Selectable(font->GetDebugName(), font == font_current))
                io.FontDefault = font;
            im::PopID();
        }
        im::EndCombo();
    }
    im::SameLine();
    HelpMarker(
        "- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
        "- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
        "- Read FAQ and docs/FONTS.txt for more details.\n"
        "- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

void im::ShowStyleEditor(ImGuiStyle* ref)
{
    // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
    ImGuiStyle& style = im::GetStyle();
    static ImGuiStyle ref_saved_style;

    // Default to using internal storage as reference
    static bool init = true;
    if (init && ref == NULL)
        ref_saved_style = style;
    init = false;
    if (ref == NULL)
        ref = &ref_saved_style;

    im::PushItemWidth(im::GetWindowWidth() * 0.50f);

    if (im::ShowStyleSelector("Colors##Selector"))
        ref_saved_style = style;
    im::ShowFontSelector("Fonts##Selector");

    // Simplified Settings
    if (im::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
        style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
    { bool window_border = (style.WindowBorderSize > 0.0f); if (im::Checkbox("WindowBorder", &window_border)) style.WindowBorderSize = window_border ? 1.0f : 0.0f; }
    im::SameLine();
    { bool frame_border = (style.FrameBorderSize > 0.0f); if (im::Checkbox("FrameBorder", &frame_border)) style.FrameBorderSize = frame_border ? 1.0f : 0.0f; }
    im::SameLine();
    { bool popup_border = (style.PopupBorderSize > 0.0f); if (im::Checkbox("PopupBorder", &popup_border)) style.PopupBorderSize = popup_border ? 1.0f : 0.0f; }

    // Save/Revert button
    if (im::Button("Save Ref"))
        *ref = ref_saved_style = style;
    im::SameLine();
    if (im::Button("Revert Ref"))
        style = *ref;
    im::SameLine();
    HelpMarker("Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export\" below to save them somewhere.");

    im::Separator();

    if (im::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        if (im::BeginTabItem("Sizes"))
        {
            im::Text("Main");
            im::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
            im::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
            im::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
            im::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
            im::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
            im::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
            im::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
            im::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
            im::Text("Borders");
            im::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
            im::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
            im::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
            im::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
            im::SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
            im::Text("Rounding");
            im::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
            im::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
            im::Text("Alignment");
            im::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
            int window_menu_button_position = style.WindowMenuButtonPosition + 1;
            if (im::Combo("WindowMenuButtonPosition", (int*)&window_menu_button_position, "None\0Left\0Right\0"))
                style.WindowMenuButtonPosition = window_menu_button_position - 1;
            im::Combo("ColorButtonPosition", (int*)&style.ColorButtonPosition, "Left\0Right\0");
            im::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); im::SameLine(); HelpMarker("Alignment applies when a button is larger than its text content.");
            im::SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f"); im::SameLine(); HelpMarker("Alignment applies when a selectable is larger than its text content.");
            im::Text("Safe Area Padding"); im::SameLine(); HelpMarker("Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).");
            im::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
            im::EndTabItem();
        }

        if (im::BeginTabItem("Colors"))
        {
            static int output_dest = 0;
            static bool output_only_modified = true;
            if (im::Button("Export"))
            {
                if (output_dest == 0)
                    im::LogToClipboard();
                else
                    im::LogToTTY();
                im::LogText("ImVec4* colors = ImGui::GetStyle().Colors;" IM_NEWLINE);
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const ImVec4& col = style.Colors[i];
                    const char* name = im::GetStyleColorName(i);
                    if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
                        im::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
                }
                im::LogFinish();
            }
            im::SameLine(); im::SetNextItemWidth(120); im::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0");
            im::SameLine(); im::Checkbox("Only Modified Colors", &output_only_modified);

            static ImGuiTextFilter filter;
            filter.Draw("Filter colors", im::GetFontSize() * 16);

            static ImGuiColorEditFlags alpha_flags = 0;
            im::RadioButton("Opaque", &alpha_flags, 0); im::SameLine();
            im::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); im::SameLine();
            im::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); im::SameLine();
            HelpMarker("In the color list:\nLeft-click on colored square to open color picker,\nRight-click to open edit options menu.");

            im::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
            im::PushItemWidth(-160);
            for (int i = 0; i < ImGuiCol_COUNT; i++)
            {
                const char* name = im::GetStyleColorName(i);
                if (!filter.PassFilter(name))
                    continue;
                im::PushID(i);
                im::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
                if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
                {
                    // Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
                    // Read the FAQ and docs/FONTS.txt about using icon fonts. It's really easy and super convenient!
                    im::SameLine(0.0f, style.ItemInnerSpacing.x); if (im::Button("Save")) ref->Colors[i] = style.Colors[i];
                    im::SameLine(0.0f, style.ItemInnerSpacing.x); if (im::Button("Revert")) style.Colors[i] = ref->Colors[i];
                }
                im::SameLine(0.0f, style.ItemInnerSpacing.x);
                im::TextUnformatted(name);
                im::PopID();
            }
            im::PopItemWidth();
            im::EndChild();

            im::EndTabItem();
        }

        if (im::BeginTabItem("Fonts"))
        {
            ImGuiIO& io = im::GetIO();
            ImFontAtlas* atlas = io.Fonts;
            HelpMarker("Read FAQ and docs/FONTS.txt for details on font loading.");
            im::PushItemWidth(120);
            for (int i = 0; i < atlas->Fonts.Size; i++)
            {
                ImFont* font = atlas->Fonts[i];
                im::PushID(font);
                bool font_details_opened = im::TreeNode(font, "Font %d: \"%s\"\n%.2f px, %d glyphs, %d file(s)", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
                im::SameLine(); if (im::SmallButton("Set as default")) { io.FontDefault = font; }
                if (font_details_opened)
                {
                    im::PushFont(font);
                    im::Text("The quick brown fox jumps over the lazy dog");
                    im::PopFont();
                    im::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
                    im::SameLine(); HelpMarker("Note than the default embedded font is NOT meant to be scaled.\n\nFont are currently rendered into bitmaps at a given size at the time of building the atlas. You may oversample them to get some flexibility with scaling. You can also render at multiple sizes and select which one to use at runtime.\n\n(Glimmer of hope: the atlas system should hopefully be rewritten in the future to make scaling more natural and automatic.)");
                    im::InputFloat("Font offset", &font->DisplayOffset.y, 1, 1, "%.0f");
                    im::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
                    im::Text("Fallback character: '%c' (U+%04X)", font->FallbackChar, font->FallbackChar);
                    im::Text("Ellipsis character: '%c' (U+%04X)", font->EllipsisChar, font->EllipsisChar);
                    const float surface_sqrt = sqrtf((float)font->MetricsTotalSurface);
                    im::Text("Texture Area: about %d px ~%dx%d px", font->MetricsTotalSurface, (int)surface_sqrt, (int)surface_sqrt);
                    for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
                        if (const ImFontConfig* cfg = &font->ConfigData[config_i])
                            im::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
                    if (im::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
                    {
                        // Display all glyphs of the fonts in separate pages of 256 characters
                        for (unsigned int base = 0; base <= IM_UNICODE_CODEPOINT_MAX; base += 256)
                        {
                            int count = 0;
                            for (unsigned int n = 0; n < 256; n++)
                                count += font->FindGlyphNoFallback((ImWchar)(base + n)) ? 1 : 0;
                            if (count > 0 && im::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
                            {
                                float cell_size = font->FontSize * 1;
                                float cell_spacing = style.ItemSpacing.y;
                                ImVec2 base_pos = im::GetCursorScreenPos();
                                ImDrawList* draw_list = im::GetWindowDrawList();
                                for (unsigned int n = 0; n < 256; n++)
                                {
                                    ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
                                    ImVec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
                                    const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
                                    draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
                                    if (glyph)
                                        font->RenderChar(draw_list, cell_size, cell_p1, im::GetColorU32(ImGuiCol_Text), (ImWchar)(base + n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
                                    if (glyph && im::IsMouseHoveringRect(cell_p1, cell_p2))
                                    {
                                        im::BeginTooltip();
                                        im::Text("Codepoint: U+%04X", base + n);
                                        im::Separator();
                                        im::Text("AdvanceX: %.1f", glyph->AdvanceX);
                                        im::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
                                        im::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
                                        im::EndTooltip();
                                    }
                                }
                                im::Dummy(ImVec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
                                im::TreePop();
                            }
                        }
                        im::TreePop();
                    }
                    im::TreePop();
                }
                im::PopID();
            }
            if (im::TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
            {
                ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
                im::Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0, 0), ImVec2(1, 1), tint_col, border_col);
                im::TreePop();
            }

            HelpMarker("Those are old settings provided for convenience.\nHowever, the _correct_ way of scaling your UI is currently to reload your font at the designed size, rebuild the font atlas, and call style.ScaleAllSizes() on a reference ImGuiStyle structure.");
            static float window_scale = 1.0f;
            if (im::DragFloat("window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.2f"))   // scale only this window
                im::SetWindowFontScale(window_scale);
            im::DragFloat("global scale", &io.FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.2f");      // scale everything
            im::PopItemWidth();

            im::EndTabItem();
        }

        if (im::BeginTabItem("Rendering"))
        {
            im::Checkbox("Anti-aliased lines", &style.AntiAliasedLines); im::SameLine(); HelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
            im::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
            im::PushItemWidth(100);
            im::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, "%.2f", 2.0f);
            if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;
            im::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
            im::PopItemWidth();

            im::EndTabItem();
        }

        im::EndTabBar();
    }

    im::PopItemWidth();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
//-----------------------------------------------------------------------------
// - ShowExampleAppMainMenuBar()
// - ShowExampleMenuFile()
//-----------------------------------------------------------------------------

// Demonstrate creating a "main" fullscreen menu bar and populating it.
// Note the difference between BeginMainMenuBar() and BeginMenuBar():
// - BeginMenuBar() = menu-bar inside current window we Begin()-ed into (the window needs the ImGuiWindowFlags_MenuBar flag)
// - BeginMainMenuBar() = helper to create menu-bar-sized window at the top of the main viewport + call BeginMenuBar() into it.
static void ShowExampleAppMainMenuBar()
{
    if (im::BeginMainMenuBar())
    {
        if (im::BeginMenu("File"))
        {
            ShowExampleMenuFile();
            im::EndMenu();
        }
        if (im::BeginMenu("Edit"))
        {
            if (im::MenuItem("Undo", "CTRL+Z")) {}
            if (im::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            im::Separator();
            if (im::MenuItem("Cut", "CTRL+X")) {}
            if (im::MenuItem("Copy", "CTRL+C")) {}
            if (im::MenuItem("Paste", "CTRL+V")) {}
            im::EndMenu();
        }
        im::EndMainMenuBar();
    }
}

// Note that shortcuts are currently provided for display only (future version will add flags to BeginMenu to process shortcuts)
static void ShowExampleMenuFile()
{
    im::MenuItem("(dummy menu)", NULL, false, false);
    if (im::MenuItem("New")) {}
    if (im::MenuItem("Open", "Ctrl+O")) {}
    if (im::BeginMenu("Open Recent"))
    {
        im::MenuItem("fish_hat.c");
        im::MenuItem("fish_hat.inl");
        im::MenuItem("fish_hat.h");
        if (im::BeginMenu("More.."))
        {
            im::MenuItem("Hello");
            im::MenuItem("Sailor");
            if (im::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                im::EndMenu();
            }
            im::EndMenu();
        }
        im::EndMenu();
    }
    if (im::MenuItem("Save", "Ctrl+S")) {}
    if (im::MenuItem("Save As..")) {}
    im::Separator();
    if (im::BeginMenu("Options"))
    {
        static bool enabled = true;
        im::MenuItem("Enabled", "", &enabled);
        im::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            im::Text("Scrolling Text %d", i);
        im::EndChild();
        static float f = 0.5f;
        static int n = 0;
        static bool b = true;
        im::SliderFloat("Value", &f, 0.0f, 1.0f);
        im::InputFloat("Input", &f, 0.1f);
        im::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        im::Checkbox("Check", &b);
        im::EndMenu();
    }
    if (im::BeginMenu("Colors"))
    {
        float sz = im::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = im::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = im::GetCursorScreenPos();
            im::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x+sz, p.y+sz), im::GetColorU32((ImGuiCol)i));
            im::Dummy(ImVec2(sz, sz));
            im::SameLine();
            im::MenuItem(name);
        }
        im::EndMenu();
    }
    if (im::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (im::MenuItem("Checked", NULL, true)) {}
    if (im::MenuItem("Quit", "Alt+F4")) {}
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;

    ExampleAppConsole()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");  // "classify" is only here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
        AutoScroll = true;
        ScrollToBottom = false;
        AddLog("Welcome to Dear ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            free(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* str1, const char* str2)         { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
    static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
    static char* Strdup(const char *str)                             { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
    static void  Strtrim(char* str)                                  { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            free(Items[i]);
        Items.clear();
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
    }

    void    Draw(const char* title, bool* p_open)
    {
        im::SetNextWindowSize(ImVec2(520,600), ImGuiCond_FirstUseEver);
        if (!im::Begin(title, p_open))
        {
            im::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar. So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (im::BeginPopupContextItem())
        {
            if (im::MenuItem("Close Console"))
                *p_open = false;
            im::EndPopup();
        }

        im::TextWrapped("This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
        im::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

        // TODO: display items starting from the bottom

        if (im::SmallButton("Add Dummy Text"))  { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); } im::SameLine();
        if (im::SmallButton("Add Dummy Error")) { AddLog("[error] something went wrong"); } im::SameLine();
        if (im::SmallButton("Clear")) { ClearLog(); } im::SameLine();
        bool copy_to_clipboard = im::SmallButton("Copy");
        //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

        im::Separator();

        // Options menu
        if (im::BeginPopup("Options"))
        {
            im::Checkbox("Auto-scroll", &AutoScroll);
            im::EndPopup();
        }

        // Options, Filter
        if (im::Button("Options"))
            im::OpenPopup("Options");
        im::SameLine();
        Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        im::Separator();

        const float footer_height_to_reserve = im::GetStyle().ItemSpacing.y + im::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
        im::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
        if (im::BeginPopupContextWindow())
        {
            if (im::Selectable("Clear")) ClearLog();
            im::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
        // You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
        // To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
        //     ImGuiListClipper clipper(Items.Size);
        //     while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // However, note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
        // If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
        im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
        if (copy_to_clipboard)
            im::LogToClipboard();
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!Filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
            bool pop_color = false;
            if (strstr(item, "[error]"))            { im::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
            else if (strncmp(item, "# ", 2) == 0)   { im::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
            im::TextUnformatted(item);
            if (pop_color)
                im::PopStyleColor();
        }
        if (copy_to_clipboard)
            im::LogFinish();

        if (ScrollToBottom || (AutoScroll && im::GetScrollY() >= im::GetScrollMaxY()))
            im::SetScrollHereY(1.0f);
        ScrollToBottom = false;

        im::PopStyleVar();
        im::EndChild();
        im::Separator();

        // Command-line
        bool reclaim_focus = false;
        if (im::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
        {
            char* s = InputBuf;
            Strtrim(s);
            if (s[0])
                ExecCommand(s);
            strcpy(s, "");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        im::SetItemDefaultFocus();
        if (reclaim_focus)
            im::SetKeyboardFocusHere(-1); // Auto focus previous widget

        im::End();
    }

    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size-1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0)
            {
                free(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }

        // On commad input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ImGuiInputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
            {
                // Example of TEXT COMPLETION

                // Locate beginning of current word
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    const char c = word_start[-1];
                    if (c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }

                // Build a list of candidates
                ImVector<const char*> candidates;
                for (int i = 0; i < Commands.Size; i++)
                    if (Strnicmp(Commands[i], word_start, (int)(word_end-word_start)) == 0)
                        candidates.push_back(Commands[i]);

                if (candidates.Size == 0)
                {
                    // No match
                    AddLog("No match for \"%.*s\"!\n", (int)(word_end-word_start), word_start);
                }
                else if (candidates.Size == 1)
                {
                    // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                    data->DeleteChars((int)(word_start-data->Buf), (int)(word_end-word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                    int match_len = (int)(word_end - word_start);
                    for (;;)
                    {
                        int c = 0;
                        bool all_candidates_matches = true;
                        for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c == 0 || c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }

                    if (match_len > 0)
                    {
                        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end-word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }

                    // List matches
                    AddLog("Possible matches:\n");
                    for (int i = 0; i < candidates.Size; i++)
                        AddLog("- %s\n", candidates[i]);
                }

                break;
            }
        case ImGuiInputTextFlags_CallbackHistory:
            {
                // Example of HISTORY
                const int prev_history_pos = HistoryPos;
                if (data->EventKey == ImGuiKey_UpArrow)
                {
                    if (HistoryPos == -1)
                        HistoryPos = History.Size - 1;
                    else if (HistoryPos > 0)
                        HistoryPos--;
                }
                else if (data->EventKey == ImGuiKey_DownArrow)
                {
                    if (HistoryPos != -1)
                        if (++HistoryPos >= History.Size)
                            HistoryPos = -1;
                }

                // A better implementation would preserve the data on the current input line along with cursor position.
                if (prev_history_pos != HistoryPos)
                {
                    const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                    data->DeleteChars(0, data->BufTextLen);
                    data->InsertChars(0, history_str);
                }
            }
        }
        return 0;
    }
};

static void ShowExampleAppConsole(bool* p_open)
{
    static ExampleAppConsole console;
    console.Draw("Example: Console", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
//-----------------------------------------------------------------------------

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
    bool                AutoScroll;     // Keep scrolling if already at the bottom

    ExampleAppLog()
    {
        AutoScroll = true;
        Clear();
    }

    void    Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!im::Begin(title, p_open))
        {
            im::End();
            return;
        }

        // Options menu
        if (im::BeginPopup("Options"))
        {
            im::Checkbox("Auto-scroll", &AutoScroll);
            im::EndPopup();
        }

        // Main window
        if (im::Button("Options"))
            im::OpenPopup("Options");
        im::SameLine();
        bool clear = im::Button("Clear");
        im::SameLine();
        bool copy = im::Button("Copy");
        im::SameLine();
        Filter.Draw("Filter", -100.0f);

        im::Separator();
        im::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            im::LogToClipboard();

        im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = Buf.begin();
        const char* buf_end = Buf.end();
        if (Filter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have a random access on the result on our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
            // especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                if (Filter.PassFilter(line_start, line_end))
                    im::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
            // Here we instead demonstrate using the clipper to only process lines that are within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
            // Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
            // both of which we can handle since we an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
            // Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    im::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        im::PopStyleVar();

        if (AutoScroll && im::GetScrollY() >= im::GetScrollMaxY())
            im::SetScrollHereY(1.0f);

        im::EndChild();
        im::End();
    }
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
    static ExampleAppLog log;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    im::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    im::Begin("Example: Log", p_open);
    if (im::SmallButton("[Debug] Add 5 entries"))
    {
        static int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            const char* categories[3] = { "info", "warn", "error" };
            const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
            log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                im::GetFrameCount(), categories[counter % IM_ARRAYSIZE(categories)], im::GetTime(), words[counter % IM_ARRAYSIZE(words)]);
            counter++;
        }
    }
    im::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    log.Draw("Example: Log", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
//-----------------------------------------------------------------------------

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(bool* p_open)
{
    im::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (im::Begin("Example: Simple layout", p_open, ImGuiWindowFlags_MenuBar))
    {
        if (im::BeginMenuBar())
        {
            if (im::BeginMenu("File"))
            {
                if (im::MenuItem("Close")) *p_open = false;
                im::EndMenu();
            }
            im::EndMenuBar();
        }

        // left
        static int selected = 0;
        im::BeginChild("left pane", ImVec2(150, 0), true);
        for (int i = 0; i < 100; i++)
        {
            char label[128];
            sprintf(label, "MyObject %d", i);
            if (im::Selectable(label, selected == i))
                selected = i;
        }
        im::EndChild();
        im::SameLine();

        // right
        im::BeginGroup();
            im::BeginChild("item view", ImVec2(0, -im::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                im::Text("MyObject: %d", selected);
                im::Separator();
                if (im::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
                {
                    if (im::BeginTabItem("Description"))
                    {
                        im::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                        im::EndTabItem();
                    }
                    if (im::BeginTabItem("Details"))
                    {
                        im::Text("ID: 0123456789");
                        im::EndTabItem();
                    }
                    im::EndTabBar();
                }
            im::EndChild();
            if (im::Button("Revert")) {}
            im::SameLine();
            if (im::Button("Save")) {}
        im::EndGroup();
    }
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
//-----------------------------------------------------------------------------

// Demonstrate create a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open)
{
    im::SetNextWindowSize(ImVec2(430,450), ImGuiCond_FirstUseEver);
    if (!im::Begin("Example: Property editor", p_open))
    {
        im::End();
        return;
    }

    HelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

    im::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
    im::Columns(2);
    im::Separator();

    struct funcs
    {
        static void ShowDummyObject(const char* prefix, int uid)
        {
            im::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
            im::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
            bool node_open = im::TreeNode("Object", "%s_%u", prefix, uid);
            im::NextColumn();
            im::AlignTextToFramePadding();
            im::Text("my sailor is rich");
            im::NextColumn();
            if (node_open)
            {
                static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
                for (int i = 0; i < 8; i++)
                {
                    im::PushID(i); // Use field index as identifier.
                    if (i < 2)
                    {
                        ShowDummyObject("Child", 424242);
                    }
                    else
                    {
                        // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                        im::AlignTextToFramePadding();
                        im::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet, "Field_%d", i);
                        im::NextColumn();
                        im::SetNextItemWidth(-1);
                        if (i >= 5)
                            im::InputFloat("##value", &dummy_members[i], 1.0f);
                        else
                            im::DragFloat("##value", &dummy_members[i], 0.01f);
                        im::NextColumn();
                    }
                    im::PopID();
                }
                im::TreePop();
            }
            im::PopID();
        }
    };

    // Iterate dummy objects with dummy members (all the same data)
    for (int obj_i = 0; obj_i < 3; obj_i++)
        funcs::ShowDummyObject("Object", obj_i);

    im::Columns(1);
    im::Separator();
    im::PopStyleVar();
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
//-----------------------------------------------------------------------------

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
static void ShowExampleAppLongText(bool* p_open)
{
    im::SetNextWindowSize(ImVec2(520,600), ImGuiCond_FirstUseEver);
    if (!im::Begin("Example: Long text display", p_open))
    {
        im::End();
        return;
    }

    static int test_type = 0;
    static ImGuiTextBuffer log;
    static int lines = 0;
    im::Text("Printing unusually long amount of text.");
    im::Combo("Test type", &test_type, "Single call to TextUnformatted()\0Multiple calls to Text(), clipped\0Multiple calls to Text(), not clipped (slow)\0");
    im::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
    if (im::Button("Clear")) { log.clear(); lines = 0; }
    im::SameLine();
    if (im::Button("Add 1000 lines"))
    {
        for (int i = 0; i < 1000; i++)
            log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines+i);
        lines += 1000;
    }
    im::BeginChild("Log");
    switch (test_type)
    {
    case 0:
        // Single call to TextUnformatted() with a big buffer
        im::TextUnformatted(log.begin(), log.end());
        break;
    case 1:
        {
            // Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
            im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
            ImGuiListClipper clipper(lines);
            while (clipper.Step())
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                    im::Text("%i The quick brown fox jumps over the lazy dog", i);
            im::PopStyleVar();
            break;
        }
    case 2:
        // Multiple calls to Text(), not clipped (slow)
        im::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
        for (int i = 0; i < lines; i++)
            im::Text("%i The quick brown fox jumps over the lazy dog", i);
        im::PopStyleVar();
        break;
    }
    im::EndChild();
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Auto Resize / ShowExampleAppAutoResize()
//-----------------------------------------------------------------------------

// Demonstrate creating a window which gets auto-resized according to its content.
static void ShowExampleAppAutoResize(bool* p_open)
{
    if (!im::Begin("Example: Auto-resizing window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        im::End();
        return;
    }

    static int lines = 10;
    im::Text("Window will resize every-frame to the size of its content.\nNote that you probably don't want to query the window size to\noutput your content because that would create a feedback loop.");
    im::SliderInt("Number of lines", &lines, 1, 20);
    for (int i = 0; i < lines; i++)
        im::Text("%*sThis is line %d", i * 4, "", i); // Pad with space to extend size horizontally
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
//-----------------------------------------------------------------------------

// Demonstrate creating a window with custom resize constraints.
static void ShowExampleAppConstrainedResize(bool* p_open)
{
    struct CustomConstraints // Helper functions to demonstrate programmatic constraints
    {
        static void Square(ImGuiSizeCallbackData* data) { data->DesiredSize.x = data->DesiredSize.y = (data->DesiredSize.x > data->DesiredSize.y ? data->DesiredSize.x : data->DesiredSize.y); }
        static void Step(ImGuiSizeCallbackData* data)   { float step = (float)(int)(intptr_t)data->UserData; data->DesiredSize = ImVec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step); }
    };

    static bool auto_resize = false;
    static int type = 0;
    static int display_lines = 10;
    if (type == 0) im::SetNextWindowSizeConstraints(ImVec2(-1, 0),    ImVec2(-1, FLT_MAX));      // Vertical only
    if (type == 1) im::SetNextWindowSizeConstraints(ImVec2(0, -1),    ImVec2(FLT_MAX, -1));      // Horizontal only
    if (type == 2) im::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
    if (type == 3) im::SetNextWindowSizeConstraints(ImVec2(400, -1),  ImVec2(500, -1));          // Width 400-500
    if (type == 4) im::SetNextWindowSizeConstraints(ImVec2(-1, 400),  ImVec2(-1, 500));          // Height 400-500
    if (type == 5) im::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);                     // Always Square
    if (type == 6) im::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)(intptr_t)100); // Fixed Step

    ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : 0;
    if (im::Begin("Example: Constrained Resize", p_open, flags))
    {
        const char* desc[] =
        {
            "Resize vertical only",
            "Resize horizontal only",
            "Width > 100, Height > 100",
            "Width 400-500",
            "Height 400-500",
            "Custom: Always Square",
            "Custom: Fixed Steps (100)",
        };
        if (im::Button("200x200")) { im::SetWindowSize(ImVec2(200, 200)); } im::SameLine();
        if (im::Button("500x500")) { im::SetWindowSize(ImVec2(500, 500)); } im::SameLine();
        if (im::Button("800x200")) { im::SetWindowSize(ImVec2(800, 200)); }
        im::SetNextItemWidth(200);
        im::Combo("Constraint", &type, desc, IM_ARRAYSIZE(desc));
        im::SetNextItemWidth(200);
        im::DragInt("Lines", &display_lines, 0.2f, 1, 100);
        im::Checkbox("Auto-resize", &auto_resize);
        for (int i = 0; i < display_lines; i++)
            im::Text("%*sHello, sailor! Making this line long enough for the example.", i * 4, "");
    }
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Overlay / ShowExampleAppSimpleOverlay()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple static window with no decoration + a context-menu to choose which corner of the screen to use.
static void ShowExampleAppSimpleOverlay(bool* p_open)
{
    const float DISTANCE = 10.0f;
    static int corner = 0;
    ImGuiIO& io = im::GetIO();
    if (corner != -1)
    {
        ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
        ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        im::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    }
    im::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (im::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
    {
        im::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
        im::Separator();
        if (im::IsMousePosValid())
            im::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            im::Text("Mouse Position: <invalid>");
        if (im::BeginPopupContextWindow())
        {
            if (im::MenuItem("Custom",       NULL, corner == -1)) corner = -1;
            if (im::MenuItem("Top-left",     NULL, corner == 0)) corner = 0;
            if (im::MenuItem("Top-right",    NULL, corner == 1)) corner = 1;
            if (im::MenuItem("Bottom-left",  NULL, corner == 2)) corner = 2;
            if (im::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            if (p_open && im::MenuItem("Close")) *p_open = false;
            im::EndPopup();
        }
    }
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Manipulating Window Titles / ShowExampleAppWindowTitles()
//-----------------------------------------------------------------------------

// Demonstrate using "##" and "###" in identifiers to manipulate ID generation.
// This apply to all regular items as well. Read FAQ section "How can I have multiple widgets with the same label? Can I have widget without a label? (Yes). A primer on the purpose of labels/IDs." for details.
static void ShowExampleAppWindowTitles(bool*)
{
    // By default, Windows are uniquely identified by their title.
    // You can use the "##" and "###" markers to manipulate the display/ID.

    // Using "##" to display same title but have unique identifier.
    im::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    im::Begin("Same title as another window##1");
    im::Text("This is window 1.\nMy title is the same as window 2, but my identifier is unique.");
    im::End();

    im::SetNextWindowPos(ImVec2(100, 200), ImGuiCond_FirstUseEver);
    im::Begin("Same title as another window##2");
    im::Text("This is window 2.\nMy title is the same as window 1, but my identifier is unique.");
    im::End();

    // Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
    char buf[128];
    sprintf(buf, "Animated title %c %d###AnimatedTitle", "|/-\\"[(int)(im::GetTime() / 0.25f) & 3], im::GetFrameCount());
    im::SetNextWindowPos(ImVec2(100, 300), ImGuiCond_FirstUseEver);
    im::Begin(buf);
    im::Text("This window has a changing title.");
    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()
//-----------------------------------------------------------------------------

// Demonstrate using the low-level ImDrawList to draw custom shapes.
static void ShowExampleAppCustomRendering(bool* p_open)
{
    if (!im::Begin("Example: Custom rendering", p_open))
    {
        im::End();
        return;
    }

    // Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of overloaded operators, etc.
    // Define IM_VEC2_CLASS_EXTRA in imconfig.h to create implicit conversions between your types and ImVec2/ImVec4.
    // ImGui defines overloaded operators but they are internal to imgui.cpp and not exposed outside (to avoid messing with your types)
    // In this example we are not using the maths operators!
    ImDrawList* draw_list = im::GetWindowDrawList();

    if (im::BeginTabBar("##TabBar"))
    {
        // Primitives
        if (im::BeginTabItem("Primitives"))
        {
            static float sz = 36.0f;
            static float thickness = 3.0f;
            static int ngon_sides = 6;
            static ImVec4 colf = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
            im::DragFloat("Size", &sz, 0.2f, 2.0f, 72.0f, "%.0f");
            im::DragFloat("Thickness", &thickness, 0.05f, 1.0f, 8.0f, "%.02f");
            im::SliderInt("n-gon sides", &ngon_sides, 3, 12);
            im::ColorEdit4("Color", &colf.x);
            const ImVec2 p = im::GetCursorScreenPos();
            const ImU32 col = ImColor(colf);
            float x = p.x + 4.0f, y = p.y + 4.0f;
            float spacing = 10.0f;
            ImDrawCornerFlags corners_none = 0;
            ImDrawCornerFlags corners_all = ImDrawCornerFlags_All;
            ImDrawCornerFlags corners_tl_br = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotRight;
            for (int n = 0; n < 2; n++)
            {
                // First line uses a thickness of 1.0f, second line uses the configurable thickness
                float th = (n == 0) ? 1.0f : thickness;
                draw_list->AddNgon(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, ngon_sides, th);         x += sz + spacing;  // n-gon
                draw_list->AddCircle(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, 20, th);               x += sz + spacing;  // Circle
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 0.0f,  corners_none, th);     x += sz + spacing;  // Square
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f, corners_all, th);      x += sz + spacing;  // Square with all rounded corners
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f, corners_tl_br, th);    x += sz + spacing;  // Square with two rounded corners
                draw_list->AddTriangle(ImVec2(x+sz*0.5f,y), ImVec2(x+sz, y+sz-0.5f), ImVec2(x, y+sz-0.5f), col, th);      x += sz + spacing;      // Triangle
                draw_list->AddTriangle(ImVec2(x+sz*0.2f,y), ImVec2(x, y+sz-0.5f), ImVec2(x+sz*0.4f, y+sz-0.5f), col, th); x += sz*0.4f + spacing; // Thin triangle
                draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y), col, th);                               x += sz + spacing;  // Horizontal line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLine(ImVec2(x, y), ImVec2(x, y + sz), col, th);                               x += spacing;       // Vertical line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y + sz), col, th);                          x += sz + spacing;  // Diagonal line
                draw_list->AddBezierCurve(ImVec2(x, y), ImVec2(x + sz*1.3f, y + sz*0.3f), ImVec2(x + sz - sz*1.3f, y + sz - sz*0.3f), ImVec2(x + sz, y + sz), col, th);
                x = p.x + 4;
                y += sz + spacing;
            }
            draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz*0.5f, col, ngon_sides);   x += sz + spacing;  // n-gon
            draw_list->AddCircleFilled(ImVec2(x + sz*0.5f, y + sz*0.5f), sz*0.5f, col, 32);             x += sz + spacing;  // Circle
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col);                        x += sz + spacing;  // Square
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f);                 x += sz + spacing;  // Square with all rounded corners
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f, corners_tl_br);  x += sz + spacing;  // Square with two rounded corners
            draw_list->AddTriangleFilled(ImVec2(x+sz*0.5f,y), ImVec2(x+sz, y+sz-0.5f), ImVec2(x, y+sz-0.5f), col);      x += sz + spacing;      // Triangle
            draw_list->AddTriangleFilled(ImVec2(x+sz*0.2f,y), ImVec2(x, y+sz-0.5f), ImVec2(x+sz*0.4f, y+sz-0.5f), col); x += sz*0.4f + spacing; // Thin triangle
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + thickness), col);                 x += sz + spacing;  // Horizontal line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + thickness, y + sz), col);                 x += spacing*2.0f;  // Vertical line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + 1, y + 1), col);                          x += sz;            // Pixel (faster than AddLine)
            draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + sz, y + sz), IM_COL32(0, 0, 0, 255), IM_COL32(255, 0, 0, 255), IM_COL32(255, 255, 0, 255), IM_COL32(0, 255, 0, 255));
            im::Dummy(ImVec2((sz + spacing) * 9.8f, (sz + spacing) * 3));
            im::EndTabItem();
        }

        if (im::BeginTabItem("Canvas"))
        {
            static ImVector<ImVec2> points;
            static bool adding_line = false;
            if (im::Button("Clear")) points.clear();
            if (points.Size >= 2) { im::SameLine(); if (im::Button("Undo")) { points.pop_back(); points.pop_back(); } }
            im::Text("Left-click and drag to add lines,\nRight-click to undo");

            // Here we are using InvisibleButton() as a convenience to 1) advance the cursor and 2) allows us to use IsItemHovered()
            // But you can also draw directly and poll mouse/keyboard by yourself. You can manipulate the cursor using GetCursorPos() and SetCursorPos().
            // If you only use the ImDrawList API, you can notify the owner window of its extends by using SetCursorPos(max).
            ImVec2 canvas_pos = im::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
            ImVec2 canvas_size = im::GetContentRegionAvail();        // Resize canvas to what's available
            if (canvas_size.x < 50.0f) canvas_size.x = 50.0f;
            if (canvas_size.y < 50.0f) canvas_size.y = 50.0f;
            draw_list->AddRectFilledMultiColor(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(50, 50, 50, 255), IM_COL32(50, 50, 60, 255), IM_COL32(60, 60, 70, 255), IM_COL32(50, 50, 60, 255));
            draw_list->AddRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(255, 255, 255, 255));

            bool adding_preview = false;
            im::InvisibleButton("canvas", canvas_size);
            ImVec2 mouse_pos_in_canvas = ImVec2(im::GetIO().MousePos.x - canvas_pos.x, im::GetIO().MousePos.y - canvas_pos.y);
            if (adding_line)
            {
                adding_preview = true;
                points.push_back(mouse_pos_in_canvas);
                if (!im::IsMouseDown(0))
                    adding_line = adding_preview = false;
            }
            if (im::IsItemHovered())
            {
                if (!adding_line && im::IsMouseClicked(0))
                {
                    points.push_back(mouse_pos_in_canvas);
                    adding_line = true;
                }
                if (im::IsMouseClicked(1) && !points.empty())
                {
                    adding_line = adding_preview = false;
                    points.pop_back();
                    points.pop_back();
                }
            }
            draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), true);      // clip lines within the canvas (if we resize it, etc.)
            for (int i = 0; i < points.Size - 1; i += 2)
                draw_list->AddLine(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y), ImVec2(canvas_pos.x + points[i + 1].x, canvas_pos.y + points[i + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
            draw_list->PopClipRect();
            if (adding_preview)
                points.pop_back();
            im::EndTabItem();
        }

        if (im::BeginTabItem("BG/FG draw lists"))
        {
            static bool draw_bg = true;
            static bool draw_fg = true;
            im::Checkbox("Draw in Background draw list", &draw_bg);
            im::SameLine(); HelpMarker("The Background draw list will be rendered below every Dear ImGui windows.");
            im::Checkbox("Draw in Foreground draw list", &draw_fg);
            im::SameLine(); HelpMarker("The Foreground draw list will be rendered over every Dear ImGui windows.");
            ImVec2 window_pos = im::GetWindowPos();
            ImVec2 window_size = im::GetWindowSize();
            ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
            if (draw_bg)
                im::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 48, 10+4);
            if (draw_fg)
                im::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 48, 10);
            im::EndTabItem();
        }

        im::EndTabBar();
    }

    im::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()
//-----------------------------------------------------------------------------

// Simplified structure to mimic a Document model
struct MyDocument
{
    const char* Name;           // Document title
    bool        Open;           // Set when the document is open (in this demo, we keep an array of all available documents to simplify the demo)
    bool        OpenPrev;       // Copy of Open from last update.
    bool        Dirty;          // Set when the document has been modified
    bool        WantClose;      // Set when the document
    ImVec4      Color;          // An arbitrary variable associated to the document

    MyDocument(const char* name, bool open = true, const ImVec4& color = ImVec4(1.0f,1.0f,1.0f,1.0f))
    {
        Name = name;
        Open = OpenPrev = open;
        Dirty = false;
        WantClose = false;
        Color = color;
    }
    void DoOpen()       { Open = true; }
    void DoQueueClose() { WantClose = true; }
    void DoForceClose() { Open = false; Dirty = false; }
    void DoSave()       { Dirty = false; }

    // Display dummy contents for the Document
    static void DisplayContents(MyDocument* doc)
    {
        im::PushID(doc);
        im::Text("Document \"%s\"", doc->Name);
        im::PushStyleColor(ImGuiCol_Text, doc->Color);
        im::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
        im::PopStyleColor();
        if (im::Button("Modify", ImVec2(100, 0)))
            doc->Dirty = true;
        im::SameLine();
        if (im::Button("Save", ImVec2(100, 0)))
            doc->DoSave();
        im::ColorEdit3("color", &doc->Color.x);  // Useful to test drag and drop and hold-dragged-to-open-tab behavior.
        im::PopID();
    }

    // Display context menu for the Document
    static void DisplayContextMenu(MyDocument* doc)
    {
        if (!im::BeginPopupContextItem())
            return;

        char buf[256];
        sprintf(buf, "Save %s", doc->Name);
        if (im::MenuItem(buf, "CTRL+S", false, doc->Open))
            doc->DoSave();
        if (im::MenuItem("Close", "CTRL+W", false, doc->Open))
            doc->DoQueueClose();
        im::EndPopup();
    }
};

struct ExampleAppDocuments
{
    ImVector<MyDocument> Documents;

    ExampleAppDocuments()
    {
        Documents.push_back(MyDocument("Lettuce",             true,  ImVec4(0.4f, 0.8f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument("Eggplant",            true,  ImVec4(0.8f, 0.5f, 1.0f, 1.0f)));
        Documents.push_back(MyDocument("Carrot",              true,  ImVec4(1.0f, 0.8f, 0.5f, 1.0f)));
        Documents.push_back(MyDocument("Tomato",              false, ImVec4(1.0f, 0.3f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument("A Rather Long Title", false));
        Documents.push_back(MyDocument("Some Document",       false));
    }
};

// [Optional] Notify the system of Tabs/Windows closure that happened outside the regular tab interface.
// If a tab has been closed programmatically (aka closed from another source such as the Checkbox() in the demo, as opposed
// to clicking on the regular tab closing button) and stops being submitted, it will take a frame for the tab bar to notice its absence.
// During this frame there will be a gap in the tab bar, and if the tab that has disappeared was the selected one, the tab bar
// will report no selected tab during the frame. This will effectively give the impression of a flicker for one frame.
// We call SetTabItemClosed() to manually notify the Tab Bar or Docking system of removed tabs to avoid this glitch.
// Note that this completely optional, and only affect tab bars with the ImGuiTabBarFlags_Reorderable flag.
static void NotifyOfDocumentsClosedElsewhere(ExampleAppDocuments& app)
{
    for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
    {
        MyDocument* doc = &app.Documents[doc_n];
        if (!doc->Open && doc->OpenPrev)
            im::SetTabItemClosed(doc->Name);
        doc->OpenPrev = doc->Open;
    }
}

void ShowExampleAppDocuments(bool* p_open)
{
    static ExampleAppDocuments app;

    // Options
    static bool opt_reorderable = true;
    static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

    if (!im::Begin("Example: Documents", p_open, ImGuiWindowFlags_MenuBar))
    {
        im::End();
        return;
    }

    // Menu
    if (im::BeginMenuBar())
    {
        if (im::BeginMenu("File"))
        {
            int open_count = 0;
            for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
                open_count += app.Documents[doc_n].Open ? 1 : 0;

            if (im::BeginMenu("Open", open_count < app.Documents.Size))
            {
                for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
                {
                    MyDocument* doc = &app.Documents[doc_n];
                    if (!doc->Open)
                        if (im::MenuItem(doc->Name))
                            doc->DoOpen();
                }
                im::EndMenu();
            }
            if (im::MenuItem("Close All Documents", NULL, false, open_count > 0))
                for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
                    app.Documents[doc_n].DoQueueClose();
            if (im::MenuItem("Exit", "Alt+F4")) {}
            im::EndMenu();
        }
        im::EndMenuBar();
    }

    // [Debug] List documents with one checkbox for each
    for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
    {
        MyDocument* doc = &app.Documents[doc_n];
        if (doc_n > 0)
            im::SameLine();
        im::PushID(doc);
        if (im::Checkbox(doc->Name, &doc->Open))
            if (!doc->Open)
                doc->DoForceClose();
        im::PopID();
    }

    im::Separator();

    // Submit Tab Bar and Tabs
    {
        ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
        if (im::BeginTabBar("##tabs", tab_bar_flags))
        {
            if (opt_reorderable)
                NotifyOfDocumentsClosedElsewhere(app);

            // [DEBUG] Stress tests
            //if ((ImGui::GetFrameCount() % 30) == 0) docs[1].Open ^= 1;            // [DEBUG] Automatically show/hide a tab. Test various interactions e.g. dragging with this on.
            //if (ImGui::GetIO().KeyCtrl) ImGui::SetTabItemSelected(docs[1].Name);  // [DEBUG] Test SetTabItemSelected(), probably not very useful as-is anyway..

            // Submit Tabs
            for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
            {
                MyDocument* doc = &app.Documents[doc_n];
                if (!doc->Open)
                    continue;

                ImGuiTabItemFlags tab_flags = (doc->Dirty ? ImGuiTabItemFlags_UnsavedDocument : 0);
                bool visible = im::BeginTabItem(doc->Name, &doc->Open, tab_flags);

                // Cancel attempt to close when unsaved add to save queue so we can display a popup.
                if (!doc->Open && doc->Dirty)
                {
                    doc->Open = true;
                    doc->DoQueueClose();
                }

                MyDocument::DisplayContextMenu(doc);
                if (visible)
                {
                    MyDocument::DisplayContents(doc);
                    im::EndTabItem();
                }
            }

            im::EndTabBar();
        }
    }

    // Update closing queue
    static ImVector<MyDocument*> close_queue;
    if (close_queue.empty())
    {
        // Close queue is locked once we started a popup
        for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
        {
            MyDocument* doc = &app.Documents[doc_n];
            if (doc->WantClose)
            {
                doc->WantClose = false;
                close_queue.push_back(doc);
            }
        }
    }

    // Display closing confirmation UI
    if (!close_queue.empty())
    {
        int close_queue_unsaved_documents = 0;
        for (int n = 0; n < close_queue.Size; n++)
            if (close_queue[n]->Dirty)
                close_queue_unsaved_documents++;

        if (close_queue_unsaved_documents == 0)
        {
            // Close documents when all are unsaved
            for (int n = 0; n < close_queue.Size; n++)
                close_queue[n]->DoForceClose();
            close_queue.clear();
        }
        else
        {
            if (!im::IsPopupOpen("Save?"))
                im::OpenPopup("Save?");
            if (im::BeginPopupModal("Save?"))
            {
                im::Text("Save change to the following items?");
                im::SetNextItemWidth(-1.0f);
                if (im::ListBoxHeader("##", close_queue_unsaved_documents, 6))
                {
                    for (int n = 0; n < close_queue.Size; n++)
                        if (close_queue[n]->Dirty)
                            im::Text("%s", close_queue[n]->Name);
                    im::ListBoxFooter();
                }

                if (im::Button("Yes", ImVec2(80, 0)))
                {
                    for (int n = 0; n < close_queue.Size; n++)
                    {
                        if (close_queue[n]->Dirty)
                            close_queue[n]->DoSave();
                        close_queue[n]->DoForceClose();
                    }
                    close_queue.clear();
                    im::CloseCurrentPopup();
                }
                im::SameLine();
                if (im::Button("No", ImVec2(80, 0)))
                {
                    for (int n = 0; n < close_queue.Size; n++)
                        close_queue[n]->DoForceClose();
                    close_queue.clear();
                    im::CloseCurrentPopup();
                }
                im::SameLine();
                if (im::Button("Cancel", ImVec2(80, 0)))
                {
                    close_queue.clear();
                    im::CloseCurrentPopup();
                }
                im::EndPopup();
            }
        }
    }

    im::End();
}

// End of Demo code
#else

void ImGui::ShowAboutWindow(bool*) {}
void ImGui::ShowDemoWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif
