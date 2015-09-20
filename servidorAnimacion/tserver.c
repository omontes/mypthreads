#include "tserver.h"

int open_socket() {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1020);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int s;
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        printw("Something wrong with socket!\n");
        refresh();
    }
    if (bind(s, (struct sockaddr*) &saddr, (socklen_t) (sizeof (saddr))) < 0) {
        printw("Bind error!\n");
        refresh();
        return -1;
    }
    printw("Server Started and is Listening...\n");
    refresh();
    if (listen(s, 3) == -1) {
        printw("Listen failed\n");
        refresh();
    }
    return s;
}

void *pintame(pFigura* fig1) {
    char buf[1023];
    refresh();
    while ((fig1->x_init != fig1->x_final) || (fig1->y_init != fig1->y_final)) {

        printw("xinit %d\n", fig1->x_init);
        printw("yinit %d\n", fig1->y_init);
        printw("xfinal: %d\n", fig1->x_final);
        printw("yfinal: %d\n", fig1->y_final);
        refresh();
        serialize(fig1, buf);
        send(socket_monitor_1, buf, sizeof (buf), 0);
        fig1->x_init += (fig1->incre_x * fig1->dirx);
        fig1->y_init += (fig1->incre_y * fig1->diry);
        usleep(fig1->waitTime);
        buf[0] = '\0';




    }
    //falta condicion de pintar el ultimo
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

        printw("Connection accepted.\n");
        refresh();
        break;
    }
    return new_sock;
}




//Terminal

void show_ncurs() {
    int row, col;
    initscr();
    raw();
    keypad(stdscr, true);
    //noecho();

    getmaxyx(stdscr, row, col);

}
