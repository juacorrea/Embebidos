#use GPS_Custom.lib
#use Utilities.lib



main()
{
	int gps_state;
	char gps_data[100];
	
	GPS_init();
	
	while(1)
	{
	gps_state = GPS_gets(gps_data);
	if (gps_state == -1)
		{
			printf("Puerto B usado\n");
		}
	else if (gps_state == -2)
		{
		printf("Inicio no encontrado ($)\n");
		}
	else if (gps_state == -3)
		{
		printf("Fin no encontrado (*)\n");
		}
	else if (gps_state == 1)
		{
		printf("Senal adquirida:\n");
		printf(gps_data);
		
		}
	else
		{
		printf("No info\n");
		}		
	UT_delay(500);
	}
	
}