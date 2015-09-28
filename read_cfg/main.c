#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

int main(int argc, char **argv)
{
    config_t cfg, *cf;
    const config_setting_t *figuras, *figura_actual;
    const char *base = NULL;
    int count, n, enabled;
    
    int xInit,yInit;
    

    cf = &cfg;
    config_init(cf);

    if (!config_read_file(cf, "Archivos de Configuracion/test.cfg")) {
        fprintf(stderr, "%s:%d - %s\n",
            config_error_file(cf),
            config_error_line(cf),
            config_error_text(cf));
        config_destroy(cf);
        return(EXIT_FAILURE);
    }

    figuras = config_lookup(cf, "Figuras");
    count = config_setting_length(figuras);
    
    for (n = 0; n < count; n++) {
        figura_actual = config_setting_get_elem(figuras,n);
         config_setting_lookup_int(figura_actual,"Xinit",&xInit);
         printf("x: %d \n",xInit);
        //printf("\t#%d. %d\n", n + 1,
         //   config_setting_get_int_elem(figuras, n));
    }
    
    
    
    config_destroy(cf);
    return 0;
}