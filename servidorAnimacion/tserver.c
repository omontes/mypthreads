#include "tserver.h"

int open_socket() {
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
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

void *accept_client(void* ns) {
    char buf[1023];
    int my_sock = *(int*) ns;
    int cont = 0;
    while (1) {

        if (cont == 20)
            cont = 0;
        pFigura* fig1 = figura_create(1, cont, 10, 0, 1,
                2, 1);
        cont++;

        printw("%d\n", cont);


        serialize(fig1, buf);
        send(my_sock, buf, sizeof (buf), 0);

        usleep(DELAY);
        refresh();
        buf[0] = '\0';




    }
    close(my_sock);
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
