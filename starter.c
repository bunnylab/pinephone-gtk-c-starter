
#include <gtk/gtk.h>
#include <stdio.h>

struct widget_refs
{
    GtkEntry *a;  // textbox
    GtkEntry *b;  // blank
    GtkEntry *c;  // blank
};

// have to add g_module_export to our signal handlers otherwise they
// don't get put into our symbol table for gtk signals
// also need -rdynamic in make to export symbols so our function is visible
G_MODULE_EXPORT
void button1_handler(GtkButton *button, struct widget_refs *widgets)
{
    const char* msg = "this is a hardcoded message, all hail char consts";
    gtk_entry_set_text( widgets->a, msg);
}

G_MODULE_EXPORT
void button2_handler(GtkButton *button, struct widget_refs *widgets)
{
    gtk_entry_set_text( widgets->a, "");
}

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

    // Create a builder object that will load the file.
    GtkBuilder* builder = gtk_builder_new();
    // Widget refs structure to pass with our signals
    struct widget_refs widgets;

    // Load the XML from a file.
    gtk_builder_add_from_file(builder, "/usr/local/share/gtkstarter/starter.glade", NULL);

    // try loading style from css file
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider,
        "/usr/local/share/gtkstarter/starter.css", NULL);
    // have to add style context to the screen otherwise 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                          GTK_STYLE_PROVIDER(provider),
                                          GTK_STYLE_PROVIDER_PRIORITY_USER);

    // connect struct members to named gtkWidgets
    widgets.a = GTK_ENTRY( gtk_builder_get_object(builder, "entrybox"));
    
    // connect the signal handlers defined in the glade file.
    gtk_builder_connect_signals(builder, &widgets);

    // get the main-window object from glade file and show
    GObject* window = gtk_builder_get_object(builder, "main-window");
    gtk_widget_show(GTK_WIDGET(window));

    // quit when the main window is closed.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // main loop.
    gtk_main();

    return 0;
}