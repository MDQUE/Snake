#include "Superlib.h"


static void
handler(int sig, siginfo_t *si, void *uc)
{
    if (si->si_value.sival_ptr == &TimerID)
    {
#if DEBUG
        write (STDOUT_FILENO, "Timeout happened", sizeof("Timeout happened"));
#endif
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
    refreshrate = 60.0 / temp_speed;


    struct sigevent sev;
//    struct itimerspec its;
    struct sigaction sa;

    printf("Establishing handler for signal %d\n", SIG);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    (void) sigemptyset(&sa.sa_mask);
    (void) sigaction(SIG, &sa, NULL);
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = &(TimerID);

    timer_create(CLOCK_REALTIME, &sev, &(TimerID));

    its.it_value.tv_sec = (int) (refreshrate-fmod(refreshrate, 1));
    its.it_value.tv_nsec = (long int)(fmod(refreshrate, 1) * 1000000000);
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;

    timer_settime(TimerID, 0, &its, NULL);

    return;
}
