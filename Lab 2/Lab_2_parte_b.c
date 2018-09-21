#use IO.LIB //cantidad de veces esta aqui
#use BTN.LIB
#use LED.LIB
#use RTC.LIB

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
	int frec;
	unsigned long time;

} ;
//void programo_rtc(void);
struct Event evento[CANTIDAD_EVENTOS+1];

main()
{	
	struct tm tiempo_actual;
	int *vacio;
	unsigned long int time;
	unsigned long int time_evento;
	unsigned long int time_2;
	char tarea;
	char tarea_s [1]; // los _s son para usar la funcion gtswf y luego pasarlos por medio de atoi a la variable sin _s
	int i, i_1;
	int frec;
	char x_s [4];
	char x;
	char w_s[4];
	char w;
	char borrar [15];
	int evento_borrar;
	char error;
	int hay_lugar;
    int t; //variable a utilzar para colocar deafult en frecuencia y led.
    char led;
    int frecuencia;

	error = 0;
	for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
	{
	 evento[i].numero = VACIO;
    }


	HW_init();
	//programo_rtc;

	while(1)
	{

		costate // Usuario
		{
//------------------- MENU DE USUARIO ---------------------------------------
			printf("\n Elija la tarea a realizar\n\t 1 = Fijar Hora del reloj\n\t 2 = Consultar Hora \n\t 3  = Agregar Evento al calendario \n\t 4 = Quitar Evento del calendario \n\t 5 = Consultar lista de eventos activos del calendario\n\t");
			time = read_rtc();
			waitfor ( getswf(tarea_s));
			tarea = atoi (tarea_s);
//----------------------------------------------------------------------------
			switch (tarea)
			{
//-------------------------FIJAR HORA ---------------------------------------
/*Espero a que el usuario ingrese los valores correctos para la hora (RTC_WRITE_TIME),
esto me devuelve un valor y ese valor se lo asigno al RTC.
*/
				case(1):
					wfd time = RTC_WRITE_Time();
					write_rtc (time);
					printf("\n Hora Configurada\n");
					time = read_rtc();
					mktm ( &tiempo_actual, time);
					printf ("\n Fecha:%d/%d/%d \n Hora %d:%d:%d \n" ,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year + 1900, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec);

				break;
//----------------------------------------------------------------------------
//------------------------LEER HORA--------------------------------------------
/*Lee la hora del RTC, luego transforma ese valor en un estructura tm, y luego imprime en pantalla*/
				case(2):
					time = read_rtc();
					mktm ( &tiempo_actual, time);
					printf ("\n Fecha:%d/%d/%d \n Hora %d:%d:%d \n" ,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year + 1900, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec);
				break;
//--------------------------------------------------------------------------------
//-------------------------AGREGAR EVENTO-----------------------------------------
/*Busca un lugar libre para agregar el evento, cuando lo encuentra, el asigna ese valor (i) a
evento.numero, le pide al usuario los datos de evento, que led prender y a que frecuencia,
el usuario puede elegir unicamente un led, de elegir lo contrario, se le pedira que asgine
nuevamente, se utiliza la varibale hay_lugar para determinar si se puede agregar el evento o no
(antes de pedirle al usuario que ingrese todos los datos*/
				case (3):
				hay_lugar = 0;
					for ( i = 0 ; i<(CANTIDAD_EVENTOS); i++)
						{

							if (evento[i].numero == VACIO) //Cuando el lugar esta libre anoto el evento
							{
								
								i_1 = i;
								wfd time = RTC_WRITE_Time();
								i = i_1;
								evento[i].time = time; 
								 
								if (time == 0)
								{
									printf ("\n Evento no configurado \n");
									evento[i].numero = VACIO;
									break;
								}    
								evento[i].numero = i;
								evento[i].command = PRENDER;  
								printf ("Elija un led para el evento\n");
								
								error = 0;								
								while (error < 1)
								{
									i_1 = i;
									waitfor (getswf(x_s));
									x = atoi(x_s);
									i = i_1;
									if (x<8 && x>=0)
										{
											evento[i].param = x;
											printf("\n\t Led OK\n");
											error = 1;
										}
									else
										{
											printf("\n\t El Led no es valido, ingrese un numero del 0 al 7 \n");
											error = 0;
										}
								}   
															
								printf ("\n Elija frecuencia para prender y apagar el led \n elegir entre (1-9)*0.1s\n");
								error = 0;
								while (error <1 )
								{
									i_1 = i;
									waitfor (getswf (w_s));
									frec = atoi (w_s);
									i = i_1;
									//t = 0;
									if (frec <10 && frec >=0)
								   {
										evento[i].numero  = i;
										evento[i].frec = frec;      // frecuencia con la que desea prender y apagar el led
										printf("\n\t Frecuencia OK\n");
										printf("\n Evento %d guradado \t%d\n",evento[i].numero,i);
										i = CANTIDAD_EVENTOS;
										hay_lugar = 1;
										error = 1;
								   }
								   else
								   {
									   printf("\n\t La frecuencia no es valida, elegir entre (1-9)*0.1s \n");
									   error = 0;
								   }								
								}
							}
						}

						if (hay_lugar == 0)
						{
							printf("\n No hay espacio de memoria suficiente  \t\n");
						}
				break;
//------------------------------------------------------------------------------------------------------------------
//-----------------------------	BORRAR EVENTO ---------------------------------------------------------------------
/*El usuario tiene que ingresar el numero del evento a borrar,
chequeo que exista un evento en ese lugar (evento.numero != VACIO),
si existe el evento, entonces a evento.numero le asigno el valor de VACIO,
si no existe puede ser porque no hay un evento configurado o porque
exede la cantidad de eventos maxima (CANTIDAD_EVENTOS).*/
				case (4):
					printf("Elija el numero del evento a borrar \n");
					error = 0;
					while (error <1 )
					{
						waitfor (getswf(borrar));
						evento_borrar = atoi(borrar);
						if (evento_borrar < CANTIDAD_EVENTOS && CANTIDAD_EVENTOS>= 0)
						{
							if(evento[evento_borrar].numero != VACIO)
							{
								printf("Evento borrado\n");
								evento[evento_borrar].numero =  VACIO;
								error = 1;

							}
							else
							{
								printf("No existe evento\n Lista de eventos:");
								for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
									{
										if (evento[i].numero != VACIO) 
										{								
											time_evento = evento[i].time;
											mktm ( &tiempo_actual, time_evento);
											printf("\nEvento %d:\n\tFecha:%d/%d/%d \n\t Hora %d:%d:%d\n\tLed: %d\t Frec.:%d ms\n" ,i,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year+1900, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec,evento[i].param),evento[i].frec;
										}
									
									}
								error = 0;
							}
						}
						else
						{
							printf("\n\t El numero de evento no es valido, ingrese uno del 0 al 7 \n");
							break;
						}
					}
				break;
//-------------------------------------------------------------------------------
//-------------------------- MOSTRAR EVENTOS-----------------------------------
/*Imprime en pantalla unicamente los eventos que tengan el valor de evento.numero != VACIO*/
				case(5):
					for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
						{
							if (evento[i].numero != VACIO) 
							{								
								time_evento = evento[i].time;
								mktm ( &tiempo_actual, time_evento);
								printf("\nEvento %d:\n\tFecha:%d/%d/%d \n\t Hora %d:%d:%d\n\tLed: %d\t Frec.:%d ms\n" ,i,tiempo_actual.tm_mday, tiempo_actual.tm_mon, tiempo_actual.tm_year+1900, tiempo_actual.tm_hour, tiempo_actual.tm_min, tiempo_actual.tm_sec,evento[i].param,evento[i].frec);
							}
						}
				break;
//------------------------------------------------------------------------------

				default:
					printf("ERROR numero equivocado\n");
					break;
			}
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
	}
}

//SE ME DESCONFIGURO EL RTC EN LA PLACA, LO CONFIGURO MANUALMENTE PARA INICIALIZARLO BIEN :)
void programo_rtc(void)
{
	struct tm tiempo;
	tiempo.tm_year = 0;
	tiempo.tm_min = 0;
	tiempo.tm_mon = 0;
	tiempo.tm_mday = 0;
	tiempo.tm_hour	= 0 ;
	tiempo.tm_sec  = 0;
	write_rtc (mktime(&tiempo));
}











