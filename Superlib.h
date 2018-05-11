#ifndef SUPERLIB_H
#define SUPERLIB_H

#define DEBUG 1

#include <time.h>
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

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

//Timer
typedef struct
{
  pid_t Tpid;
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

#endif
