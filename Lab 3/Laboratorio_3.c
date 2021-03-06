#use IO.LIB //cantidad de veces esta aqui
#use EVENTO.LIB
#use "dcrtcp.lib"

#define ERROR_CONEXION					-1
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
/*La funcion get_ethernet devuelve uno cuando le llego el valor, cero cuando no,
menos uno cuando la conexion esta caida.
ya que esta funcion es siempre llamada por un wfd*/
int get_ethernet (char *p_string )
{
	if (tcp_tick(&echosock) != 0)
	{
		if (sock_bytesready(&echosock)>0)
		{
			if(sock_gets(&echosock,p_string,512))
			{
				sock_puts(&echosock,p_string);
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
	unsigned long int time_2;
	int i ;
    char led;
    int frecuencia;
	char buffer[512];
	char buffer_print[256];
	int chequeo;

//INICIALIZO LOS EVENTOS COMO VACIOS
	for ( i = 0 ; i<CANTIDAD_EVENTOS; i++)
	{
		evento[i].numero = VACIO;
    }

	HW_init();

	while(1)
	{
//------------------- MENU DE USUARIO ---------------------------------------
		costate
		{
			wfd chequeo = EVENTO_Menu_Usuario[0]( evento, getswf, print_consola,0 );
		}
//----------------------------------------------------------------------------
//----------------------------------LED ROJO----------------------------------
/*Prende el led rojo durante 400ms, y lo apaga durande 800ms*/
		costate
		{
			waitfor(DelayMs(800));	//Espero 800ms para prender el led rojo
			RED_LED_SET();			//Prendo led rojo
			waitfor(DelayMs(400));	//Espero 400ms para apagar el led rojo
			RED_LED_RESET();		//Apago led rojo
		}
//----------------------------------------------------------------------------


//--------------------------------------ALARMA--------------------------------
	costate
		{
			time_2 = read_rtc();

			for(i = 0; i<CANTIDAD_EVENTOS;i++)
			{

				if (evento[i].numero != VACIO)
				{
					if (evento[i].time == time_2)
					{
						sprintf(buffer_print,"\n Evento!! %d\n",evento[i].numero);
						print_consola(buffer_print);
						print_ethernet(buffer_print);						
						led = evento[i].param;
						frecuencia = evento[i].frec;
						wfd LED_Prender_Led_frec_cant_veces(led,  frecuencia);
						evento[i].numero = VACIO;
					}
				}
			}

		}
//----------------------------------------------------------------------------
//-------------INICIALIZO ETHERNET Y MENU USUARIO EN ETHERNET-----------------
	costate
		{
			tcp_listen(&echosock,PORT,0,0,NULL,0);
			while (!sock_established(&echosock))
				{
					tcp_tick(NULL);
					yield;
				}
			printf("Usuario Conectado\n");
			sock_mode(&echosock,TCP_MODE_ASCII);
			while(tcp_tick(&echosock))
				{
				wfd  chequeo = EVENTO_Menu_Usuario[1](evento, get_ethernet, print_ethernet,1 );
				}
			if (chequeo == ERROR)
				{
					printf("Conexion caida /n");
				}
		}
//----------------------------------------------------------------------------
//-------------------------CHEQUEO CONEXION Y REINICIO CONEXION---------------
	 costate 
		{
			while (tcp_tick(&echosock))
		{
			//tcp_tick(&echosock);
			yield;
		} 
		tcp_listen(&echosock,PORT,0,0,NULL,0);
		while (!sock_established(&echosock))
			{
				tcp_tick(NULL);
				yield;
			}
		printf("Usuario Conectado\n");

		}
//------------------------------------------------------------------------------
	}	
}



