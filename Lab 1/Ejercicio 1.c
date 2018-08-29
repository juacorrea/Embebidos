//Parte A y B 
enum portName
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
};

enum bitNumber
{
	BIT_0,
	BIT_1,
	BIT_2,
	BIT_3,
	BIT_4,
	BIT_5,
	BIT_6,
	BIT_7,
};
unsigned char p_state;
void  Wr_Port_Bit ( enum portName p_port, enum bitNumber p_pin, unsigned char p_state);
char Rd_Port_Bit (enum portName p_port, enum bitNumber p_pin);

#define PRENDER_LED(Led)  Wr_Port_Bit(PORT_A,Led,1)
#define APAGAR_LED(Led)  Wr_Port_Bit(PORT_A,Led,0)
#define LEER_BOTON(bot) ((bot<4) ? Rd_Port_Bit(PORT_B,bot+2) : Rd_Port_Bit(PORT_F,bot)) //Lee y devuelve el valor del boton pasado como parametro
#define BOTON_APRETADO(bot) ((LEER_BOTON(bot)!=0)? 0 : 1 ) // Si el boton esta apretado es igual a 0, entonces devuelvo 1
main()
{
	unsigned int i;
//FALTA CONFIGURAR PUERTO F
	WrPortI (SPCR,&SPCRShadow,0x084); //Setea Puerto A como SALIDA
	WrPortI (PBDDR,&PBDDRShadow,0x000); //Setea Puerto B como ENTRADA

	for(i=0; i<8;i++)
	APAGAR_LED(i);

	while (1)
   {
   for(i=0; i<8;i++) // Si un boton esta apretado prende el led correspondiente y si no lo papaga
		if (BOTON_APRETADO(i)==1)
			PRENDER_LED(i);
		else if (BOTON_APRETADO(i)!=0)
			APAGAR_LED(i);
   }

}

char Rd_Port_Bit(enum portName p_port, enum bitNumber p_pin)
{
		int stat;
		switch (p_port)
	{
		case(PORT_A)://Lee en puerto A
		stat = BitRdPortI (PADR, p_pin);
		break;

		case(PORT_B)://Lee en puerto B
		stat = BitRdPortI (PBDR, p_pin);
		break;

		case(PORT_C)://Lee en puerto C
		stat = BitRdPortI (PCDR, p_pin);
		break;

		case(PORT_D)://Lee en puerto D
		stat = BitRdPortI (PDDR, p_pin);
		break;

		case(PORT_E)://Lee en puerto E
		stat = BitRdPortI (PEDR, p_pin);
		break;

		case(PORT_F)://Lee en puerto F
		stat = BitRdPortI (PFDR, p_pin);
		break;

		default:
		stat = -1;
		break;


	}
	return stat;
}


void Wr_Port_Bit ( enum portName p_port, enum bitNumber p_pin, unsigned char p_state)
{
		switch (p_port)
	{
		case(PORT_A)://Escribe en puerto A
		BitWrPortI (PADR, &PADRShadow, p_state, p_pin);
		break;

		case(PORT_B)://Escribe en puerto B
		BitWrPortI (PBDR, &PBDRShadow, p_state, p_pin);
		break;

		case(PORT_C)://Escribe en puerto C
		BitWrPortI (PCDR, &PCDRShadow, p_state, p_pin);
		break;

		case(PORT_D)://Escribe en puerto D
		BitWrPortI (PDDR, &PDDRShadow, p_state, p_pin);
		break;

		case(PORT_E)://Escribe en puerto E
		BitWrPortI (PEDR, &PEDRShadow, p_state, p_pin);
		break;

		case(PORT_F)://Escribe en puerto F
		BitWrPortI (PFDR, &PFDRShadow, p_state, p_pin);
		break;
	}
}


