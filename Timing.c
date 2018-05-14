#include "Superlib.h"


static void
handler(int sig, siginfo_t *si, void *uc)
{
    /* since signals are system wide, check if this signal has beenSTDOUT_FILENO
       sent from MY timer */
    if (si->si_value.sival_ptr == &TimerID)
    {
        /* do NOT call printf() and friends here, since they are not
           signal safe! for a list of asynchronous signal safe
           functions see man 7 signal section "Async-signal-safe
           functions", however, if you NEED to call a async signal
           unsafe function you may do so by setting a flag variable
           which is examined outside your signal handler
        */
        write (STDOUT_FILENO, "Timeout happened", sizeof("Timeout happened"));
    }
}


//runs until speed parameter is not overwritten(refreshes the screen every n-times)
void Speedopt(gpointer data)
{
    mainwidget *a = (mainwidget *)data;

    int temp_speed = 0;
    a->t->Endflag = 0;
    float refreshrate;

    temp_speed = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed));
    refreshrate = 60 / temp_speed;


    struct sigevent sev;
//    struct itimerspec its;
    struct sigaction sa;

    printf("Establishing handler for signal %d\n", SIG);
    /* use a signal handler prototype containing three arguments
       instead of one */
    sa.sa_flags = SA_SIGINFO;
    /* pointer to signal handler */
    sa.sa_sigaction = handler;
    /* initializes the signal set given to empty, with all signals
       excluded from the set */
    (void) sigemptyset(&sa.sa_mask);
    /* defines the action to be taken upon this specific signal
       arrives. third argument can bes used to store the old
       behaviour */
    (void) sigaction(SIG, &sa, NULL);
    /* notify the process */
    sev.sigev_notify = SIGEV_SIGNAL;
    /* use this signal number*/
    sev.sigev_signo = SIG;
    /* data sent to the signal handler */
    sev.sigev_value.sival_ptr = &(TimerID);
    /* create, but stop the timer with the given signal
       configuration */
    timer_create(CLOCK_REALTIME, &sev, &(TimerID));

    its.it_value.tv_sec = (int) (refreshrate-fmod(refreshrate, 1));
    its.it_value.tv_nsec = (long int)(fmod(refreshrate, 1) * 10000000000);
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    timer_settime(TimerID, 0, &its, NULL);
//    while(1) {
//        if (a->t->Endflag == 1) {
//            a->t->Endflag = 0;
//            break;
//        }
//    }
    /*  while (1)*/
    /*  {*/
    /*    //printf("%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed)));*/
    /*    if (gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed)) != temp_speed)*/
    /*    {*/
    /*      temp_speed = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a->s->S_Speed));*/
    /*      refreshrate = 60 / temp_speed;*/
    /*    }*/
    /*    sleep(refreshrate);*/
    /*    //printf("ref: %f \n speed: %d \n", refreshrate , temp_speed);*/
    /*    if (a->t->Endflag == 1)*/
    /*      break;*/
    /*    //g_timeout_add would be to easy, lets implement it on system with timer_create*/
    /*  }*/
    return;
}
