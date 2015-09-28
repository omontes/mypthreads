#include "tserver.h"

int open_socket() {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1021);
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

void serialize(pFigura*figura, char* buf, int monitor_num, int cantidad_columnas) {

    int x = figura->x_init - monitor_num*cantidad_columnas;
    //printf("x %d\n", x);

    //ID
    memcpy(buf, &figura->id, sizeof (int));

    //Position
    memcpy(buf + 1 * sizeof (int), &x, sizeof (int));
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




void *pintame(pFigura* fig) {
    if(fig->tiempoInicio != 0){
        my_thread_wait(fig->tiempoInicio);
    }

    while (1) {


        printf("xinit %d\n", fig->x_init);
        printf("yinit %d\n", fig->y_init);


         if(isDead(fig)==1){
            fig->enable = 0;
            eliminarFiguraLista(fig);
            elegirSocketEnviarPosicionFigura(fig);
            break;    
        }
        
        while(verificarExisteChoque(fig)==1) {
            if (isDead(fig) == 1) {
                fig->enable = 0;
                eliminarFiguraLista(fig);
                elegirSocketEnviarPosicionFigura(fig);
                return;
            }
            my_thread_yield();
        }
        
        //VALIDAR SI ESTA MUERTO Y LUEGO ELIMINAR DE LA LISTA Y LUEGO BREAK

       
        
        //verifica si la figura a pintar choca, en caso de hacerlo espera 
        elegirSocketEnviarPosicionFigura(fig);

        fig->x_init += (fig->incre_x * fig->dirx);
        fig->y_init += (fig->incre_y * fig->diry);
        if(fig->animacion != 0)
            fig->rotation = rotacionIncrementalFigura(fig->rotation);
        my_thread_wait(fig->waitTime);


        if ((fig->x_init == fig->x_final) && (fig->y_init == fig->y_final)) {
            /*Condicion de pintar el ultimp*/
            printf("xinit %d\n", fig->x_init);
            printf("yinit %d\n", fig->y_init);
            
            verificarExisteChoque(fig);
            elegirSocketEnviarPosicionFigura(fig);
            //usleep(fig->waitTime);

            printf("termino figura\n");

            //La figura ya no debe aparecer mas y se
            fig->enable = 0;
            eliminarFiguraLista(fig);
            elegirSocketEnviarPosicionFigura(fig);
            break;
        }




    }


    //NO SE PINTA MAS

}

int isDead(pFigura* figura){
    clock_t end;
    double total;
    end =clock();
    total = (end - figura->startTime) / (double) 1000;
    if(total>=figura->lifeTime){
        return 1;
    }
    return 0;
    
    
}
//Lista figuras

void initLista() {
    listaFiguras = list_create();
}

void agregarFiguraLista(pFigura* figura) {
    if (list_is_empty(listaFiguras)) {
        list_add(listaFiguras, figura);
    } else {
        pFigura* fig = list_get(listaFiguras, figura->id);
        if (fig == NULL) {
            list_add(listaFiguras, figura);

        }
    }
}

void actualizarFiguraLista(pFigura* figura) {
    pFigura* fig = list_get(listaFiguras, figura->id);
    if (fig != NULL) {
        fig->x_init = figura->x_init;
        fig->y_init = figura->y_init;
        fig->rotation = figura->rotation;
    }
}

void eliminarFiguraLista(pFigura* figura) {
    list_remove(listaFiguras, figura);
}

//comprueba choque componente x
int verificarChoqueX(int nueva_posicion_x,pFigura* figura){
    if(((figura->x_init <= nueva_posicion_x) && (nueva_posicion_x <= (figura->x_init+10))) || ((figura->x_init <= (nueva_posicion_x+10)) && ((nueva_posicion_x+10) <= (figura->x_init+10))))
    {
        printf("choque en x ************ \n");
        return 1;
    }
    else{
        return 0;
    }
}

//comprueba choque componente y
int verificarChoqueY(int nueva_posicion_y,pFigura* figura){
    if(((figura->y_init <= nueva_posicion_y) && (nueva_posicion_y <= (figura->y_init+4))) || ((figura->y_init <= (nueva_posicion_y+4)) && ((nueva_posicion_y+4) <= (figura->y_init+4))))
    {
        printf("choque en y ************ \n");
        return 1;
    }
    else{
        return 0;
    }
}

int verificarExisteChoque(pFigura* figura) {
    pNodo* pointer = listaFiguras->front;
    int nueva_posicion_x = figura->x_init;
    int nueva_posicion_y = figura->y_init;
    while (pointer != NULL) {
        pFigura* fig = pointer->data;
        //choque en x
        if(!equals(fig,figura)){
            if (verificarChoqueX(nueva_posicion_x, fig) == 1 && verificarChoqueY(nueva_posicion_y, fig) == 1) {
                printf("hubo un choque !!!!!!!!!!!!!!!!!\n");
                return 1;
            }
        }
        pointer = pointer->next;
    }
    return 0;

}



//animacion

int asignarMonitor(int xInit){
    int cantidad_columnas = 80;
    if (xInit <= cantidad_columnas) {
        return 1;
    }else if(xInit > cantidad_columnas) {
        return 2;
    }
}

int rotacionIncrementalFigura(int angulo) {
    int nuevo_angulo = 0;
    if (angulo == 270) {
        return nuevo_angulo;
    } else {
        nuevo_angulo = angulo + 90;
        return nuevo_angulo;
    }
}

void elegirSocketEnviarPosicionFigura(pFigura* figura) {
    char buf[1023];
    int cantidad_columnas = 80;
    if (figura->x_init < cantidad_columnas - 9) {
        if(figura->monitor == 2){
            figura->enable = 0;
            serialize(figura, buf, 1, cantidad_columnas);
            send(socket_monitor_2, buf, sizeof (buf), 0);
            buf[0] = '\0';  
            figura->monitor = 1;
            figura->enable = 1;
        }
            
        serialize(figura, buf, 0, cantidad_columnas);
        send(socket_monitor_1, buf, sizeof (buf), 0);
    } else if (figura->x_init >= cantidad_columnas - 9 && figura->x_init < cantidad_columnas) {


        serialize(figura, buf, 0, cantidad_columnas);
        send(socket_monitor_1, buf, sizeof (buf), 0);
        buf[0] = '\0';
        printf("esta haciendo lo suyo");
        serialize(figura, buf, 1, cantidad_columnas);
        send(socket_monitor_2, buf, sizeof (buf), 0);
    }
    else if (figura->x_init >= cantidad_columnas) {
        if(figura->monitor == 1){
            figura->enable = 0;
            serialize(figura, buf,0 , cantidad_columnas);
            send(socket_monitor_1, buf, sizeof (buf), 0);
            buf[0] = '\0';  
            figura->monitor = 2;
            figura->enable = 1;
        }
        serialize(figura, buf, 1, cantidad_columnas);
        send(socket_monitor_2, buf, sizeof (buf), 0);
    }
    buf[0] = '\0';
}

// leer archivo configuracion 
void crearFigurasCFG(void){
    
   
    
}
