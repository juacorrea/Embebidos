#use IO.LIB //cantidad de veces esta aqui
#use EVENTO.LIB
#use "dcrtcp.lib"


//void programo_rtc(void);



main()
{

	struct Event evento[CANTIDAD_EVENTOS+1];
	unsigned long int time;
	unsigned long int time_evento;
	unsigned long int time_2;
	char tarea;
	char tarea_s [1]; // los _s son para usar la funcion gtswf y luego pasarlos por medio de atoi a la variable sin _s
	int i ;
    char led;
    int frecuencia;
	char buffer[512];
	int status;
	char esperando;
	esperando = 1 ;

	for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
	{
		evento[i].numero = VACIO;
    }


	HW_init();

	while(1)
	{

		costate // Usuario
		{
//------------------- MENU DE USUARIO ---------------------------------------
			printf("\n Elija la tarea a realizar\n\t 1 = Fijar Hora del reloj\n\t 2 = Consultar Hora \n\t 3 = Agregar Evento al calendario \n\t 4 = Quitar Evento del calendario \n\t 5 = Consultar lista de eventos activos del calendario\n\t 6 = Consultar entradas analogicas\n\t");
			waitfor ( getswf(tarea_s));
			tarea = atoi (tarea_s);
			
			while (esperando)
				{
					yield;
				}
			wfd EVENTO_Menu_Usuario( evento, tarea);
		}

//----------------------------------LED ROJO---------------------------------------------
/*Prende el led rojo durante 400ms, y lo apaga durande 800ms*/
		costate
		{
			waitfor(DelayMs(800));	//Espero 800ms para prender el led rojo
			RED_LED_SET();			//Prendo led rojo
			waitfor(DelayMs(400));	//Espero 400ms para apagar el led rojo
			RED_LED_RESET();		//Apago led rojo
		}
//-----------------------------------------------------------------------------------------


//	--------------------------------------ALARMA--------------------------------------------------
	costate
		{
			time_2 = read_rtc();

			for(i = 0; i<CANTIDAD_EVENTOS;i++)
			{

				if (evento[i].numero != VACIO)
				{
					if (evento[i].time == time_2)
					{
						printf("\n Evento!! %d\n",evento[i].numero);
						led = evento[i].param;
						frecuencia = evento[i].frec;
						wfd LED_Prender_Led_frec_cant_veces(led,  frecuencia);
						evento[i].numero = VACIO;

					}
				}
			}

		}

//------------------------------------------------------------------------
	costate
		{
			tcp_listen(&echosock,PORT,0,0,NULL,0);
			//sock_wait_established(&echosock,sock_delay,NULL,&status)
			while (!sock_established(&echosock))
				{
					tcp_tick(NULL);
					yield;
				}
			printf("Usuario Conectado\n");
			sock_mode(&echosock,TCP_MODE_ASCII);
			while(tcp_tick(&echosock))
			{
				//sock_wait_input(&echosock,0,NULL,&status)
				if (sock_bytesready(&echosock)>0)
					{
						//printf("entre");
					if(sock_gets(&echosock,buffer,512))
						{
							sock_puts(&echosock,buffer);
							printf("%s",buffer);
						}
						//printf("if sock_bytsread");
					}
					yield;
					//printf("if
			}
			printf("fuera while");

			sock_err:
			switch(status)
			{
				case 1: /* foreign host closed */
					printf("User closed session\n");
					break;
				case -1: /* time-out */
					printf("Connection timed out\n");
					break;
			}


		}

	}
}
/*
FALTA:
ecchosocket un array de usuarios
funcion que imprima o lea del socket o desde el serial
*/


