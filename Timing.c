#include "Superlib.h"


//runs until speed parameter is not overwritten(refreshes the screen every n-times)
void Speedopt(gpointer data)
{
  mainwidget *a = (mainwidget *)data;
  
  int frk;
  frk = fork();
  //forked process start
  if (frk == 0)
  {
    a->t->Tpid = getpid();
    if ( a->t->Tpid == 0 || a->t->Tpid == 1)
      something_fails(a);
    printf("Pid: %d", a->t->Tpid);
    int temp_speed = 0;
    float refreshrate;
    while (1)
    {
      printf("%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed)));
      if (gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed)) != temp_speed)
      {
        temp_speed = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed));
        refreshrate = 60 / temp_speed;
      }
      sleep(refreshrate);
      printf("ref: %f \n speed: %d \n", refreshrate , temp_speed);
      //g_timeout_add would be to easy, lets implement it on system
      
    }
  }
  //forked process end
}
