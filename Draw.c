#include "Superlib.h"

void DrawSetup(gpointer data){
  mainwidget *a = (mainwidget *)data;
  
  a->CairoBasic = gtk_drawing_area_new();
  gtk_widget_set_size_request (a->CairoBasic, 639, 639);
  gtk_box_pack_start (GTK_BOX (a->playbox), a->CairoBasic, TRUE, TRUE, 0);
  
  
  GtkAllocation allocation;
  static cairo_surface_t *surface = NULL;

  gtk_widget_get_allocation (GTK_WIDGET(a->CairoBasic), &allocation);
  write(STDOUT_FILENO, "r u workin?\n", sizeof("r u workin?\n"));
  surface = gdk_window_create_similar_surface (gtk_widget_get_window (GTK_WIDGET(a->CairoBasic)),
       CAIRO_CONTENT_COLOR,
       639,
       639);
  write(STDOUT_FILENO, "r u workin?\n", sizeof("r u workin?\n"));
  a->cr = cairo_create (surface);
  write(STDOUT_FILENO, "r u workin?\n", sizeof("r u workin?\n"));
  cairo_destroy (a->cr);
}
