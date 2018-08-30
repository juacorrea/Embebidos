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
#define STX 2
#define ETX 3
//unsigned char p_state;
void delay(long int delay);
//void  Wr_Port_Bit ( enum portName p_port, enum bitNumber p_pin, unsigned char p_state);
//char Rd_Port_Bit (enum portName p_port, enum bitNumber p_pin);
int getAnalogInput(unsigned char p_input);

main()
{
	unsigned int i;

	WrPortI (SCCR,&SCCRShadow,0x00); //Setea Puerto C como SERIAL
   serCopen(9600);

	while(1)
	{
   	getAnalogInput(0);
		delay(2000);
	}
}

int getAnalogInput(unsigned char p_input)
{
	char data[29];
	char inicio[5];
	inicio[0] = STX;
	inicio[1] = '0';
	inicio[2] = '1';
	inicio[3] = ETX;
	inicio[4] = STX+ETX+'0'+'1';

	serCwrite(inicio,5);
	delay(500);
	serCread(data,29,10);
	printf("%s",data);
	printf("\n");
	return 0;

}


/*
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
*/
void delay(long int delay)
{
	long int endtime;
	endtime = MS_TIMER +delay;
	while ((long)(MS_TIMER - endtime) <0);
}