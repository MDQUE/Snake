#ifndef SUPERLIB_H
#define SUPERLIB_H

#define DEBUG 0
#define SIG SIGRTMIN+0

#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>


//Global Shit
timer_t TimerID;


//Sidebar
typedef struct
{
  GtkWidget *S_Speed;
  GtkWidget *S_Speed_L;
  gint *SnakeSpeed;
  GtkWidget *G_FieldSize;
  GtkWidget *G_FieldSize_L;
  GtkAdjustment *G_A_FieldSize;
  gint *GameFieldSize;
  GtkWidget *CtrlType[3];
  GtkWidget *CtrlType_L;
  gchar *ControlType[1];
  GtkWidget *SetSep1;
  GtkWidget *Score_L;
  GtkWidget *ScoreWrite;
  GtkWidget *ScoreWrite_L;
  gint *Score;
  gchar *ScoreS;
  GtkWidget *SetSep2;
  GtkWidget *StrtBtn;
} SideSettigs;

//Timer_refresh dependencies
struct itimerspec its;

//Timer
typedef struct
{
  pid_t Tpid;
  gint Endflag;
  gint Refresh_Signal;
} Speeder;


//Popup
typedef struct
{
  GtkWidget *Wentwrongmsg;
} Notifications;


//Main
typedef struct
{
  GtkApplication *App;
  GtkWidget *window;
  GtkWidget *basicgrid;
  GtkWidget *sidegrid;
  GtkWidget *playbox;
  GtkWidget *settingsbox;
  GtkStyleContext *context;
  GtkStyleProvider *provider;
  Notifications *msg;
  SideSettigs *s;
  Speeder *t;
} mainwidget;




// Function Prototypes
int side_menu_setup(gpointer data);
void something_fails(gpointer data);
void Starter(GtkWidget *window, gpointer data);
void Speedopt(gpointer data);
void Refresh_Adjust(GtkWidget *window, gpointer data);

#endif
