#include <gtk/gtk.h>

GtkWidget* createConsoleBox()
{
    GtkWidget* textArea = gtk_text_view_new();
    GtkWidget* scrollbar= gtk_vscrollbar_new(gtk_text_view_get_vadjustment(GTK_TEXT_VIEW(textArea)));
    GtkWidget* textEntry = gtk_entry_new();

    GtkWidget* console = gtk_table_new(2, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(console), textArea, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(console), scrollbar, 1, 2, 0, 1);
    //gtk_table_attach_defaults(GTK_TABLE(console), textEntry, 0, 2, 1, 2);

    //This code sets the preferred size for the widget, so it does not ask for extra space
    gtk_widget_set_size_request(textArea, 320, 240);

    return console;
}

int main( int argc, char *argv[])
{
  GtkWidget *window;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Center");
  gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  gtk_container_add(GTK_CONTAINER(window), createConsoleBox());
  gtk_widget_show_all(window);
  //gtk_widget_show(window);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

  gtk_main();

  // Add text to textarea
  void gtk_text_insert(GtkText    *text,
                      GdkFont    *font,
                      GdkColor   *fore,
                      GdkColor   *back,
                      const char *chars,
                      gint        length );

  return 0;
}
