#define LED_ROJO_Y_BUZZ			3 						//primer y segundo bit de SALIDA en 1 (buzz y led rojo encendido)
#define CALDERA             	4 						//tercer bit de SALIDA en 1 (caldera encendida)
#define LED_VERDE       		8						//cuarto bit de SALIDA en 1 (luz verde encendido)
#define T_UMBRAL             	1 						//primer bit de ENTRADA en 1(temp por arriba umbral)
#define BOT_APRETADO         	2 						//segundo bit ENTRADA en 1(boton apretado)
#define T_OK					0						//Temperatura por debajo del umbral

enum ESTADO
{
	Ok,
	No_Ok,
	Enfriando,
};



main()
{
//ESTADO INICIAL
//---------------------------------------------------------------------------------
char  estado, entrada, salida, i;
estado = Ok;
salida = LED_VERDE;
entrada = T_OK;
i = 0;												//utilizada en estado Enfriando
//----------------------------------------------------------------------------------

 while (1)
	{
		switch (estado)
		{
			case (Ok):
				salida = LED_VERDE; 						// Led verde prendido y caldera apagada
				
				entrada = entrada & T_UMBRAL ;				//chequea si el primer bit fue seteado (temp por arriba del umbral), si es asi cambio de estado a No_Ok
				if (entrada == T_UMBRAL )    				
					{
						estado = No_Ok;
					}
			break;

			case (No_Ok):
				salida = LED_ROJO_Y_BUZZ;                	// Apago led verde, prendo rojo y buzzer
				
				entrada = entrada & BOT_APRETADO;			// Chequea si el segundo bit fue seteado (boton apretado), si es asi cambio de estado a Enfriando
				if (entrada == BOT_APRETADO)            		
					{
						estado = Enfriando;
					}
			break;

			case (Enfriando):
         	/*Utiliza variable iterativa(i) para permanecer en estaddo Enfriando exactamente un ciclo del programa.
            Si la variable esta en 0 prende la caldera y cambia la variable a 1, en el siguiente ciclo apaga la
            caldera y vuelve la variable a 0*/

	         if (i == 1)
	         {
	            i--;
	            estado = Ok;
	         }
	         else if ( i == 0)
	         {
	            i++;
	            salida = CALDERA; 								//Enciende la caldera
	         }
			break;
		}
	}

}