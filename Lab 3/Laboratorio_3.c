#use IO.LIB //cantidad de veces esta aqui
#use EVENTO.LIB
#use "dcrtcp.lib"

#define ERROR_CONEXION			-1 


int status;

//void programo_rtc(void);
void print_consola( char *p_string );
void print_ethernet(  char *p_string );
cofunc int get_ethernet (char *p_string );
void print_consola( char *p_string )
{
	printf(p_string);
}

void print_ethernet( char *p_string )
{
	sock_puts (&echosock, p_string);
}
/*La funcion get_ethernet devuelve uno cuando le llego el valor, cero cuando no
ya que esta funcion es siempre llamada por un wfd*/
int get_ethernet (char *p_string )
{
		if (tcp_tick(&echosock) == 1)
		{
			//sock_wait_input(&echosock,0,NULL,&status)
			if (sock_bytesready(&echosock)>0)
			{
				if(sock_gets(&echosock,p_string,512))
				{
					sock_puts(&echosock,p_string);
					printf("%s",p_string);
					return 1;
				}
			}
			else
			{
				return 0;
			}
		}
		else 
		{
			
			return ERROR_CONEXION; // TIENE QUE VALER -1
			
		
		}
}






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
	char buffer_print[256];
	int chequeo;


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


			wfd chequeo = EVENTO_Menu_Usuario[0]( evento, getswf, print_consola );
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

			wfd  chequeo = EVENTO_Menu_Usuario[1](evento, get_ethernet, print_ethernet );
			if (chequeo == ERROR)
			{
				printf("Conexion caida /n");
			}
		





		}

	}
}
/*
FALTA:
ecchosocket un array de usuarios
funcion que imprima o lea del socket o desde el serial
*/


