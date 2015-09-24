#include "tserver.h"

int open_socket() {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1020);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int s;
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Something wrong with socket!\n");
        
    }
    if (bind(s, (struct sockaddr*) &saddr, (socklen_t) (sizeof (saddr))) < 0) {
        printf("Bind error!\n");
        
        return -1;
    }
    printf("Server Started and is Listening...\n");
    
    if (listen(s, 3) == -1) {
        printf("Listen failed\n");
        
    }
    return s;
}

void *pintame(pFigura* fig1) {
    char buf[1023];
    
    while ((fig1->x_init != fig1->x_final) || (fig1->y_init != fig1->y_final)) {

        
        printf("xinit %d\n", fig1->x_init);
        printf("yinit %d\n", fig1->y_init);
        printf("xfinal: %d\n", fig1->x_final);
        printf("yfinal: %d\n", fig1->y_final);
        
        serialize(fig1, buf);
        //VALIDAR EL CASO CUANDO LA LISTAS ESTAN VACIAS, DEBE YA TENER LOS DOS SOCKETS CREADOS
        //TENER CUIDADO CON QUE HAY QUE INICIALIZAR LAS LISTAS
        //OPERACIOS CON LAS LISTAS
        // HACER AGREGAR, ELIMINAR(CAMBIAR DE MONITOR O DESPUES DE ESTE WHILE) Y ACTUALIZAR(DESPUES DE CAMBIAR POSICION) SEGUN EL MONITOR QUE ESTE
        //FALTA LA LOGICA QUE DECIDE A QUE MONITOR VA A PINTARSE Y SI TIENE QUE
        //CAMBIAR DE MONITAR --> ELIMINARSE DE LA LISTA DE UN MONITOR Y ENTRAR 
        //EN OTRO.
        //VALIDAR LOS CHOQUES CON LAS LISTAS DE CADA MONITOR
        send(socket_monitor_1, buf, sizeof (buf), 0);
        fig1->x_init += (fig1->incre_x * fig1->dirx);
        fig1->y_init += (fig1->incre_y * fig1->diry);
        my_thread_wait(fig1->waitTime);
        buf[0] = '\0';




    }
    /*Condicion de pintar el ultimp*/
    printf("xinit %d\n", fig1->x_init);
    printf("yinit %d\n", fig1->y_init);
    printf("xfinal: %d\n", fig1->x_final);
    printf("yfinal: %d\n", fig1->y_final);
    
    serialize(fig1, buf);
    send(socket_monitor_1, buf, sizeof (buf), 0);
    my_thread_wait(fig1->waitTime);
    buf[0] = '\0';
    
    //La figura ya no debe aparecer mas y se
    fig1->enable = 0;
    serialize(fig1, buf);
    send(socket_monitor_1, buf, sizeof (buf), 0);
    
    
    //NO SE PINTA MAS
    
}

void serialize(pFigura*figura, char* buf) {



    //ID
    memcpy(buf, &figura->id, sizeof (int));

    //Position
    memcpy(buf + 1 * sizeof (int), &figura->x_init, sizeof (int));
    memcpy(buf + 2 * sizeof (int), &figura->y_init, sizeof (int));

    //Rotacion
    memcpy(buf + 3 * sizeof (int), &figura->rotation, sizeof (int));

    //Colores
    memcpy(buf + 4 * sizeof (int), &figura->colorIn, sizeof (int));
    memcpy(buf + 5 * sizeof (int), &figura->colorOut, sizeof (int));

    //Enable
    memcpy(buf + 6 * sizeof (int), &figura->enable, sizeof (int));
}

int listener(void*sock) {
    struct sockaddr_in client;
    int m_sock = *(int*) sock;
    int new_sock;
    int c = sizeof (struct sockaddr_in);

    while (new_sock = accept(m_sock, (struct sockaddr*) &client, (socklen_t*) & c)) {

        printf("Connection accepted.\n");
        
        break;
    }
    return new_sock;
}



