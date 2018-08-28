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
void Rd_Bot(int bot); //prende led correspondiente al boton apretado

#define PRENDER_LED(Led)  Wr_Port_Bit(PORT_A,Led,1)
#define APAGAR_LED(Led)  Wr_Port_Bit(PORT_A,Led,0)
#define LEER_BOTON(bot) ((bot<4) ? Rd_Port_Bit(PORT_B,bot+2) : Rd_Port_Bit(PORT_F,bot))

main()
{
	unsigned int i;
	//int p;
	//int bot_stat;
   //bot_stat=0;
	WrPortI (SPCR,&SPCRShadow,0x084); //Setea Puerto A como SALIDA
	WrPortI (PBDDR,&PBDDRShadow,0x000); //Setea Puerto B como ENTRADA

	//PRENDER_LED(0);
	//for(i=0; i<50000;i++);
	APAGAR_LED(0);
	APAGAR_LED(1);
	APAGAR_LED(2);
	APAGAR_LED(3);
	APAGAR_LED(4);
	APAGAR_LED(5);
	APAGAR_LED(6);
	APAGAR_LED(7);


	while (1)
   {
   for(i=0; i<8;i++)
		if (LEER_BOTON(i)==0)
			PRENDER_LED(i);
		else if (LEER_BOTON(i)!=0)
			APAGAR_LED(i);
     //	printf("B%d = %d\n",i,LEER_BOTON(i));
     //	for(i=0; i<50000;i++);
     // printf("\n");
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


