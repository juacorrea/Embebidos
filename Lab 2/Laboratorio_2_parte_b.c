#use IO.LIB
#use BTN.LIB
#use LED.LIB
#use UTILITIES.LIB


#define PRENDER						1
#define APAGAR					  		0
#define CANTIDAD_EVENTOS			8
#define VACIO							-1
#define STDIO_ENABLE_LONG_STRINGS
enum Led_Numb
{
	LED_0,
	LED_1,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
};

struct Event
{
	int numero;
	char command;
	char param;
	char frec;
	unsigned long time;

} ;

cofunc unsigned long int RTC_Time(void);


/*
-"command" es la acción a realizar en ese evento (por ejempo: 1 si es prender, 0 si es
apagar, 0xFF si el evento no está configurado).
- "param" es la información asociada al comando (por ejemplo: el número de salida
(LED) que se debe prender o apagar).
- "time" es el momento en el que se tiene que disparar el evento
*/

main()
{
	struct tm tiempo_actual;
	int *vacio;
	unsigned long int time;
	char tarea;
	char tarea_s [1];
	int i;
	char frec;
	char x_s [1];
	char x;
	char w[15];
	char borrar [15];
	int evento_borrar;
	struct Event evento [CANTIDAD_EVENTOS];
	for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
	{
	 evento[i].numero = VACIO;
   }


	HW_init();

	while(1)
	{

	costate // Usuario
	{
		printf("\n Elija la tarea a realizar\n\t 1 = Fijar Hora del reloj\n\t 2 = Consultar Hora \n\t 3  = Agregar Evento al calendario \n\t 4 = Quitar Evento del calendario \n\t 5 = Consultar lista de eventos activos del calendario\n\t");
      waitfor ( getswf(tarea_s));
		tarea = atoi (tarea_s);
		switch (tarea)
		{
			case(1)://fijar hora
				wfd time = RTC_Time();
				write_rtc (time);
				printf("\n Guardado \n");
			break;

			case(2)://consultar hora
				time = read_rtc();
				mktm ( &tiempo_actual, time);
				printf ("\n Fecha:%d/%d/%d \n Hora %d:%d:%d \n" ,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year + 1900, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec);
			break;

			case (3)://agregar evento
				for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
					{

						//vacio = &evento[i].numero ; //vacio apunta a la direccion de evento.numero i
						if (evento[i].numero == VACIO) //Cuando el lugar esta libre anoto el evento
						{

							wfd evento[i].time = RTC_Time();
							evento[i].numero = i;
							evento[i].command = PRENDER;
							printf ("Elija un led para el evento\n");
							waitfor (getswf(x_s));
							x = atoi(x_s);

							if (x < 8)
							{
								evento[i].param = x;      // x es el led que desea prender.
							}
							else
							{
								evento[i].numero  = VACIO;
								printf("ERROR!! el evento no ha sido guardado \n");
								break;
							}

							printf ("Elija frecuencia para prender y apagar el led ms \n");
							waitfor (getswf (w));
							frec = atoi (w);
							evento[i].frec = frec;      // frecuencia con la que desea prender y apagar el led
                     printf("Evento %d guradado/t%d",evento[i].numero,i);
                     i = CANTIDAD_EVENTOS;


						}
					}
			break;

			case (4): // Borrar evento   ARREGLAR!!!!!!!!!
				printf("Elija el numero del evento a borrar \n");
				waitfor (getswf(borrar));
				evento_borrar = atoi(borrar);
				if (evento_borrar < CANTIDAD_EVENTOS)
				{
					if(evento[evento_borrar].numero != VACIO)
					{
						printf("Evento borrado\n");
						evento[evento_borrar].numero =  VACIO;

					}
					else
					{
						printf("No existe evento\n");
					}
				}
				else
				{
					printf("ERROR \n");
					break;
				}
			break;

			case(5)://Despelga los eventos en pantalla
				for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
					{
						if (evento[i].numero != VACIO) //Cuando el lugar esta libre anoto el evento
						{
							printf("\nEvento %d:\n\tFecha:%d/%d/%d \n\t Hora %d:%d:%d\n\tLed: %d\t Frec.:%d ms\n" ,i,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec,evento[i].param),evento[i].frec;
						}
					}
			break;


			default:
				printf("ERROR \n");
				break;
		}
	}

	costate //Led rojo -------------------------------funciona
	{
		waitfor(DelayMs(800L));	//Espero 800ms para prender el led rojo
		RED_LED_SET();			//Prendo led rojo
		waitfor(DelayMs(400L));	//Espero 400ms para apagar el led rojo
		RED_LED_RESET();		//Apago led rojo
	}

/*	------------------------------------------------------------Hacer------------------------------------------------------------------------------
	costate // hace saltar el evento
	{

	}
*/

	}
}

cofunc unsigned long int RTC_Time(void)
{
	struct tm tiempo;
	char segundos[15];
	char minutos[15];
	char hora[15];
	char dia[15];
	char mes[15];
	char ano[15];

	printf ("Ingrese Ano \n");
	waitfor (getswf(ano));
	printf ("Ingrese Mes \n");
	waitfor (getswf(mes));
	printf ("Ingrese Dia \n");
	waitfor (getswf(dia));
	printf ("Ingrese hora \n");
	waitfor (getswf(hora));
	printf ("Ingrese Minutos \n");
	waitfor (getswf(minutos));
	printf ("Ingrese segundos \n");
	waitfor (getswf(segundos));

	tiempo.tm_sec = atoi (segundos);
	tiempo.tm_min = atoi (minutos);
	tiempo.tm_hour = atoi (hora);
	tiempo.tm_mday = atoi (dia);
	tiempo.tm_mon = atoi (mes);
	tiempo.tm_year = atoi (ano) - 1900;

	return mktime(&tiempo);
}












