#include "Superlib.h"


/******************************************************************************************************/

/*                                            CALLBACKS                                               */

/******************************************************************************************************/


void Starter(GtkWidget *window, gpointer data)
{
  mainwidget *a = (mainwidget *)data;
#if DEBUG
  g_printf("%p\n", a);
  g_printf("%p\n", a->msg);
  g_printf("%p\n", a->s->StrtBtn);
#endif
  if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(a->s->StrtBtn)) ,"Pause") != 0)
  {
    gtk_button_set_label(GTK_BUTTON(a->s->StrtBtn), "Pause");
    a->t->Endflag = 0;
    Speedopt(a);
  }
  else
  {
    gtk_button_set_label(GTK_BUTTON(a->s->StrtBtn), "Start");
    a->t->Endflag = 1;
    timer_delete(TimerID);
  }
}

void Refresh_Adjust(GtkWidget *window, gpointer data)
{
  mainwidget *a = (mainwidget *)data;
  
  if (a->t->Endflag == 0){
    int temp_speed;
    float refreshrate;
    temp_speed = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed));
    refreshrate = 60.0 / temp_speed;
    its.it_value.tv_sec = (int) (refreshrate-fmod(refreshrate, 1));
    its.it_value.tv_nsec = (long int)(fmod(refreshrate, 1) * 1000000000);
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    // Set new timescale
    timer_settime(TimerID, 0, &its, NULL);
  }
  else
    return;
}

/******************************************************************************************************/

/*                                                GUI                                                 */

/******************************************************************************************************/


int side_menu_setup(gpointer data)
{
  mainwidget *a = (mainwidget *)data;
  
  a->t->Endflag = 1;
  
  //basic layout
  a->sidegrid = gtk_grid_new();
  gtk_box_pack_start(GTK_BOX(a->settingsbox), GTK_WIDGET(a->sidegrid),TRUE,TRUE,0);
  gtk_grid_set_column_homogeneous(GTK_GRID(a->sidegrid), TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(a->sidegrid), TRUE);
//  gtk_grid_set_row_spacing(GTK_GRID(a->sidegrid), 15);
  
  //Speed control handler
  a->s->S_Speed_L = gtk_label_new("Speed :");
  gtk_widget_set_hexpand(a->s->S_Speed_L, TRUE);
  a->s->S_Speed = gtk_spin_button_new_with_range(6,150,1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->s->S_Speed), 12);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->S_Speed_L),0,0,2,1);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->S_Speed),2,0,1,1);
  gtk_widget_set_name(GTK_WIDGET(a->s->S_Speed), "SETTINGSPIN");
  g_signal_connect(GTK_WIDGET(a->s->S_Speed), "value-changed", G_CALLBACK (Refresh_Adjust), (gpointer *)a);
  
  //gamefield size control
  a->s->G_FieldSize_L = gtk_label_new("Field Scale (Next Game Only)");
  a->s->G_A_FieldSize = gtk_adjustment_new(64,32,128,16,0,0);
  a->s->G_FieldSize = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL,a->s->G_A_FieldSize);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->G_FieldSize),0,1,3,1);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->G_FieldSize_L),0,2,3,1);
  gtk_grid_set_row_baseline_position(GTK_GRID(a->sidegrid),2, GTK_BASELINE_POSITION_TOP);
  
  //Game Controll Settings
  a->s->CtrlType_L = gtk_label_new("Manual   /   A*lgorithm   /   Ai");
  a->s->CtrlType[0] = gtk_radio_button_new (NULL);
  for(gint i= 1; i < 3; i++)
  {
    a->s->CtrlType[i] = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(a->s->CtrlType[0]));
  }
  for(gint i= 0; i < 3; i++ )
  {
    gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->CtrlType[i]), (i),3,1,1);
  }
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->CtrlType_L), 0,4,3,1);
  gtk_grid_set_row_baseline_position(GTK_GRID(a->sidegrid),4, GTK_BASELINE_POSITION_TOP);
  //
  //    DO NOT FORGET TO ADD SIGNAL HANDLER!!!
  //
  
  //Some Visual Separation
  a->s->SetSep1 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->SetSep1), 0,5,3,1);
  
  //Adding Score board:
  a->s->Score_L = gtk_label_new("Score:");
  a->s->ScoreWrite = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_size_request(GTK_WIDGET(a->s->ScoreWrite), 100, 70);
  a->s->ScoreWrite_L = gtk_label_new("001");
  gtk_grid_attach(GTK_GRID(a->sidegrid), GTK_WIDGET(a->s->Score_L), 0,6,3,1);
  gtk_grid_attach(GTK_GRID(a->sidegrid), GTK_WIDGET(a->s->ScoreWrite), 0,8,3,2);
  gtk_box_pack_start(GTK_BOX(a->s->ScoreWrite), GTK_WIDGET(a->s->ScoreWrite_L), TRUE,TRUE,0);
  gtk_widget_set_name(GTK_WIDGET(a->s->ScoreWrite), "SCOREBOX");
  
  //Some Visual Separation
  a->s->SetSep2 = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
  gtk_grid_attach(GTK_GRID(a->sidegrid),GTK_WIDGET(a->s->SetSep2), 0,10,3,1);
  
  //Big User Button
  a->s->StrtBtn = gtk_button_new_with_label("Start");
  gtk_grid_attach(GTK_GRID(a->sidegrid), GTK_WIDGET(a->s->StrtBtn), 2,11,1,1);
  g_signal_connect(GTK_BUTTON(a->s->StrtBtn), "clicked", G_CALLBACK (Starter), (gpointer *)a);
  
  #if DEBUG
  g_printf("%p\n", a);
    g_printf("%p\n", a->msg);
    g_printf("%p\n", a->s->StrtBtn);
#endif
  
  return 1;
}

void something_fails(gpointer data)
{
  mainwidget *a = (mainwidget *)data;
  
  #if DEBUG
  g_printf("%p\n", a);
    g_printf("%p\n", a->msg);
#endif

  a->msg->Wentwrongmsg = gtk_message_dialog_new(GTK_WINDOW(a->window), 
                                                GTK_DIALOG_MODAL, 
                                                GTK_MESSAGE_ERROR, 
                                                GTK_BUTTONS_NONE, 
                                                "An Error occured While setup\n The Program will terminate now");
  gtk_widget_show_all(a->msg->Wentwrongmsg);
//  gtk_window_set_destroy_with_parent(GTK_WINDOW(a->window), TRUE);
}
