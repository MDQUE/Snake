#include "Superlib.h"


//Building the basic layout
static void activate (GtkApplication *app, gpointer data, gpointer user_data)
{
  mainwidget *a = (mainwidget *)data;

  
  //settings
  a->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (a->App));
	gtk_window_set_title (GTK_WINDOW (a->window), "Snake Evo v1");
  gtk_window_set_default_size(GTK_WINDOW(a->window), 839, 639);
  gtk_window_set_resizable(GTK_WINDOW(a->window), FALSE);
  
  //populate the Window
  a->basicgrid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(a->window), a->basicgrid);
  a->playbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  a->settingsbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_name(a->playbox, "PLAYBOX");
  gtk_widget_set_name(a->settingsbox, "SETTINGSBOX");
  gtk_widget_set_size_request(a->playbox, 639,639);
  gtk_widget_set_size_request(a->settingsbox, 200,639);
  gtk_grid_attach(GTK_GRID(a->basicgrid), a->playbox, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(a->basicgrid), a->settingsbox,1,0,1,1);
  int check = side_menu_setup(a);
  
  //Some failing check code
  
/*  if (check == -1)*/
/*  {*/
/*    something_fails(a);*/
/*    sleep(3);*/
/*    gtk_window_set_destroy_with_parent(GTK_WINDOW(a->window), TRUE);*/
/*  }*/

  //format window output via CSS
  a->provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER (a->provider), "S_loox_res.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(a->provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  
	gtk_widget_show_all (GTK_WIDGET (a->window));
}


//Begginning & initializing
int main (int argc, char **argv)
{
	mainwidget *a = g_malloc(sizeof(mainwidget));
 
  a->msg = g_malloc(sizeof(Notifications));
#if DEBUG
  g_printf("%p\n", a);
    g_printf("%p\n", a->msg);
#endif
  a->s = g_malloc(sizeof(SideSettigs));
  a->t = g_malloc(sizeof(Speeder));
	int status;

	a->App = gtk_application_new ("org.gtk.minimal", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (a->App, "activate", G_CALLBACK (activate), (gpointer) a);
	status = g_application_run (G_APPLICATION (a->App), argc, argv);
  g_free (a->t);
  g_free (a->s);
  g_free (a->msg);
	g_free (a);
	return status;
}
