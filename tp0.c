/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"



int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"
	log_info(logger,"soy un log\n");
	config = leer_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion


	conexion = crear_conexion(ip,puerto);


	//enviar mensaje

	enviar_mensaje("Prueba",conexion);

	//recibir mensaje

	char* string_recibido = malloc(7);
	strcpy(string_recibido,recibir_mensaje(conexion));
	printf("%s\n",string_recibido);
	//loguear mensaje recibido
	log_info(logger,string_recibido);

	terminar_programa(conexion, logger, config);
}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("tp0.log","Game-watch-client",true, LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config(void)
{
	t_config* config = config_create("/home/utnso/Game-watch-client");
	config_set_value(config,"IP","127.0.0.1");
	config_set_value(config,"PUERTO","4444");
	config_save_in_file(config,"/home/utnso/Game-watch-client/tp0.config");
	return config;

}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
