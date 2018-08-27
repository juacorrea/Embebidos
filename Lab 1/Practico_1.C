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
void setOutput ( enum portName p_port, enum bitNumber p_pin, unsigned char p_state);
char getInput(enum portName p_port, enum bitNumber p_pin);

#define PRENDER_LED(Led) setOutput(PORT_A,Led,1)
#define APAGAR_LED(Led) setOutput(PORT_A,Led,0)
//#define LEER_BOTON(Bot) getInput(PORT_B,Bot)

main()
{
	unsigned int i;
	int p;
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
	

	while (1);
	{
		for(p=0; p<8;p++);
		{
			if(getInput(PORT_B,p) == 0)
			{
			PRENDER_LED(p);
			}
			else if(getInput(PORT_B,p) == 1)
			{
			APAGAR_LED(p);
			}
		}
	}

}

char getInput(enum portName p_port, enum bitNumber p_pin)
{
		int stat;
		switch (p_port)
	{
		case(PORT_A)://Lee en puerto A
		stat = BitRdPortI (PADR, p_pin);
		break;

		case(1)://Lee en puerto B
		stat = BitRdPortI (PBDR, p_pin);
		break;

		case(2)://Lee en puerto C
		stat = BitRdPortI (PCDR, p_pin);
		break;

		case(3)://Lee en puerto D
		stat = BitRdPortI (PDDR, p_pin);
		break;

		case(4)://Lee en puerto E
		stat = BitRdPortI (PEDR, p_pin);
		break;

		case(5)://Lee en puerto F
		stat = BitRdPortI (PFDR, p_pin);
		break;
		
		default:
		stat = -1;
		break;
		
		
	}
	return stat;
}


void setOutput ( enum portName p_port, enum bitNumber p_pin, unsigned char p_state)
{
		switch (p_port)
	{
		case(0)://Escribe en puerto A
		BitWrPortI (PADR, &PADRShadow, p_state, p_pin);
		break;

		case(1)://Escribe en puerto B
		BitWrPortI (PBDR, &PBDRShadow, p_state, p_pin);
		break;

		case(2)://Escribe en puerto C
		BitWrPortI (PCDR, &PCDRShadow, p_state, p_pin);
		break;

		case(3)://Escribe en puerto D
		BitWrPortI (PDDR, &PDDRShadow, p_state, p_pin);
		break;

		case(4)://Escribe en puerto E
		BitWrPortI (PEDR, &PEDRShadow, p_state, p_pin);
		break;

		case(5)://Escribe en puerto F
		BitWrPortI (PFDR, &PFDRShadow, p_state, p_pin);
		break;
	}
}