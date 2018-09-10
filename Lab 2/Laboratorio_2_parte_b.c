#use IO.LIB
#use BTN.LIB
#use LED.LIB
#use UTILITIES.LIB

#define PRENDER						1
#define APAGAR						0
#define CANTIDAD_EVENTOS			8
#define VACIO						-1
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
	char numero;
	char command;
	char param;
	char frec;
	unsigned long time;

} ;

unsigned long int RTC_Time(void);


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
	char *vacio;
	unsigned long int time;
	char tarea;
	int i, frec;
	char x;
	char w[15];
	char borrar [15];
	int evento_borrar;
	struct Event evento [CANTIDAD_EVENTOS];
	for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
	{
		//evento[CANTIDAD_EVENTOS].numero  = VACIO;       //---------------------------------ERROR/WARNING---------------------------------------
      evento[i].numero  = VACIO;
   }


	HW_init();
	printf("Elija la tarea a realizar\n\t 1 = Fijar Hora del reloj\n\t 2 = Consultar Hora \n\t 3  = Agregar Evento al calendario \n\t 4 = Quitar Evento del calendario \n\t 5 = Consultar lista de eventos activos del calendario");
	tarea = getc ();                        //---------------------------------WARNING---------------------------------------

	costate // Usuario
	{
		switch (tarea)
		{
			case(1)://fijar hora
			time = RTC_Time();
			write_rtc (time);
			break;

			case(2)://consultar hora
			time = read_rtc();
			mktm ( tiempo_actual, time); //---------------------------------WARNING---------------------------------------
			printf ("dia %d ,mes %d, ano %d \n hora %d, minutos %d, segundos %d \n" ,tiempo_actual.tm_year, tiempo_actual.tm_mon, tiempo_actual.tm_mday, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec);
			break;

			case (3)://agregar evento
			for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
				{
					*vacio = &evento.numero [i]; //vacio apunta a la direccion de evento.numero i   ---------------------------------ERROR---------------------------------------
					if (vacio == VACIO) //Cuando el lugar esta libre anoto el evento
					{
						evento[i].time = RTC_Time();
						evento[i].numero [i] = i;        //---------------------------------ERROR---------------------------------------
						evento[i].command = PRENDER;
						printf ("Elija un led para el evento\n");
						x = getc ();
						if (x < 8)
						{
							evento[i].param = x;      // x es el led que desea prender.
						}
						else
						{
							evento[i].numero  = VACIO;        //---------------------------------WARNING---------------------------------------
							printf("ERROR!! el evento no ha sido guardado \n");
							break;
						}

						printf ("Elija frecuencia para prender y apagar el led ms \n");
						gets (w);
						frec = atoi (w);            //---------------------------------ERROR---------------------------------------
						evento[i].frec = frec;      // frecuencia con la que desea prender y apagar el led   ---------------------------------ERROR---------------------------------------
						i = CANTIDAD_EVENTOS;

					}
				}
			break;

			case (4): // Borrar evento
			printf("Elija el numero del evento a borrar \n");
			gets(borrar);
			evento_borrar = atoi(borrar);
			if (evento_borrar < CANTIDAD_EVENTOS)
			{
				if(evento[evento_borrar].numero =! VACIO)
				{
					printf("Evento borrado\n");
					evento[evento_borrar].numero = VACIO;   //---------------------------------WARNING---------------------------------------

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
/*---------------------------------------------------------------Hacer-----------------------------------------------------------------------------
			case(4)://Despelga los eventos en pantalla

			break;
*/

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

unsigned long int RTC_Time(void)
{
	struct tm tiempo;
	char segundos[15];
	char minutos[15];
	char hora[15];
	char dia[15];
	char mes[15];
	char ano[15];

	printf ("Ingrese Ano \n");
	gets(ano);
	printf ("Ingrese Mes \n");
	gets(mes);
	printf ("Ingrese Dia \n");
	gets(dia);
	printf ("Ingrese hora \n");
	gets(hora);
	printf ("Ingrese Minutos \n");
	gets(minutos);
	printf ("Ingrese segundos \n");
	gets(segundos);

	tiempo.tm_sec = atoi (segundos);
	tiempo.tm_min = atoi (minutos);
	tiempo.tm_hour = atoi (hora);
	tiempo.tm_mday = atoi (dia);
	tiempo.tm_mon = atoi (mes);
	tiempo.tm_year = atoi (ano);

	return mktime(tiempo);        //---------------------------------WARNING---------------------------------------
}












