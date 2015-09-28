#include "tserver.h"
#include "MyPthread/MyPthread.h"
#include "MyPthread/MyMutex.h"
#include "MyPthread/TCB.h"


myMutex* mt;

void sig_int(int signo) {
    close(socket_monitor_1);
    close(socket_monitor_2);
    printf("Exit\n");
    exit(0);
}

int main(int argc, char*argv[]) {
    //variables
    const config_setting_t *figuras, *figura_actual;
    int count, n;
    int xInit, yInit, xIncremento, yIncremento, xDir, yDir, xFinal, yFinal, rotacion, animacion, colorIn, colorOut, tiempoInicio, tiempoIntervalo,tiempoVida, tipoScheduler, tiquetes;


    
    

    //init socket ***

    struct sigaction sa;
    sa.sa_handler = &sig_int;
    // Block every signal during the handler
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("Error: cannot handle SIGINT");
    }
    int sock = open_socket();
    if (sock == -1) {
        printf("error occured\n");
        return -1;
    }
    /*Inicializa los sockets de los monitores 1 y 2*/
    int contador_sockets;
    for (contador_sockets = 0; contador_sockets < 2; contador_sockets++) {
        if (contador_sockets == 0) {
            socket_monitor_1 = listener((void*) &sock);
            printf("creo monitor 1\n");
        } else {
            socket_monitor_2 = listener((void*) &sock);
            printf("creo monitor 2\n");
        }
    }
    printf("ya cree todos los sockets\n");

    my_thread_init();
    my_mutex_init();
    mt = my_mutex_create();
     
    //init lista
    initLista();


    //Lectura figuras
    config_t cfg, *cf;
    cf = &cfg;
    config_init(cf);

    if (!config_read_file(cf, "Archivos de Configuracion/test.cfg")) { //directorio archivo
        fprintf(stderr, "%s:%d - %s\n",
                config_error_file(cf),
                config_error_line(cf),
                config_error_text(cf));
        config_destroy(cf);
        return (EXIT_FAILURE);
    }

    figuras = config_lookup(cf, "Figuras");
    count = config_setting_length(figuras);

    for (n = 0; n < count; n++) {
        figura_actual = config_setting_get_elem(figuras, n);
        config_setting_lookup_int(figura_actual, "Xinit", &xInit);
        config_setting_lookup_int(figura_actual, "Yinit", &yInit);
        config_setting_lookup_int(figura_actual, "Xincremento", &xIncremento);
        config_setting_lookup_int(figura_actual, "Yincremento", &yIncremento);
        config_setting_lookup_int(figura_actual, "Ydir", &xDir);
        config_setting_lookup_int(figura_actual, "Ydir", &yDir);
        config_setting_lookup_int(figura_actual, "XFinal", &xFinal);
        config_setting_lookup_int(figura_actual, "YFinal", &yFinal);
        config_setting_lookup_int(figura_actual, "RotacionInit", &rotacion);
        config_setting_lookup_int(figura_actual, "Animacion", &animacion);
        config_setting_lookup_int(figura_actual, "ColorIn", &colorIn);
        config_setting_lookup_int(figura_actual, "ColorOut", &colorOut);
        config_setting_lookup_int(figura_actual, "TiempoInicio", &tiempoInicio);
        config_setting_lookup_int(figura_actual, "TiempoIntervalo", &tiempoIntervalo);
         config_setting_lookup_int(figura_actual, "TiempoVida", &tiempoVida);
        config_setting_lookup_int(figura_actual, "TipoScheduler", &tipoScheduler);
        config_setting_lookup_int(figura_actual, "Tiquetes", &tiquetes);
        
        pFigura* fig = figura_create(n,xInit,yInit,rotacion,colorIn,colorOut,1,tiempoIntervalo,xIncremento,yIncremento, xDir,yDir,xFinal,yFinal,tiempoVida,asignarMonitor(xInit),tiempoInicio,animacion);
        agregarFiguraLista(fig);
        my_thread_create(pintame, 1, (void*) fig, tipoScheduler, tiquetes);

    }
    config_destroy(cf);

    /*
    pFigura* fig1 = figura_create(1, 0, 0, 0, 1, 2, 1, 300, 1, 0, 1, 1, 40, 0, 25000, asignarMonitor(0), 0, 1);
    pFigura* fig2 = figura_create(2, 40, 0, 0, 5, 6, 1, 200, 1, 0, -1, 1, 0, 0, 45000, asignarMonitor(40), 0, 1);
    pFigura* fig3 = figura_create(3, 0, 8, 0, 3, 4, 1, 500, 1, 0, 1, 1, 80, 8, 40000, asignarMonitor(0), 5000, 1);
    pFigura* fig4 = figura_create(4, 120, 8, 0, 6, 7, 1, 700, 1, 0, -1, 1, 0, 8, 60000, asignarMonitor(120), 2000, 1);
    agregarFiguraLista(fig1);
    agregarFiguraLista(fig2);
    agregarFiguraLista(fig3);
    agregarFiguraLista(fig4);

    my_thread_create(pintame, 1, (void*) fig1, 1, 0);
    my_thread_create(pintame, 1, (void*) fig2, 1, 0);
    my_thread_create(pintame, 1, (void*) fig3, 1, 0);
    my_thread_create(pintame, 1, (void*) fig4, 1, 0);
     */

    while (1);
    //my_thread_join(t3);



    //close(socket_monitor_1);
    //close(socket_monitor_2);
    printf("Exit\n");
    exit(0);
}


