void OW_Init(Struct_Settings* System_settings)
{
	/*WIFI settings*/
	sprintf(System_settings->SSID,"%s","TakeOut");
	sprintf(System_settings->PASSWORD,"%s", "takeout0503");
	
	/*Forecast settings*/
	sprintf(System_settings->A_Station_NM,"%s","%EC%A2%85%EB%A1%9C%EA%B5%AC");
	sprintf(System_settings->nx, "%s", "63");
	sprintf(System_settings->ny, "%s", "124");
	
	/*G_Bus settings*/
	sprintf(System_settings->G_Station_ID, "%s", "206000157");
	sprintf(System_settings->G_Route_ID, "%s", "204000005");
		
	/*S_Station_Ord_getter*/
	sprintf(System_settings->S_arsId, "%s", "23285");
	sprintf(System_settings->rtNm, "%s", "3412");
	
	/*S_Bus settings*/
	sprintf(System_settings->S_Station_ID, "%s", "122000182");
	sprintf(System_settings->S_Route_ID, "%s", "100100224");

	/*S_Metro settings*/
	sprintf(System_settings->M_Station_NM, "%s", "%EA%B0%95%EB%82%A8");
	sprintf(System_settings->M_subwayId, "%s", "1002");
	sprintf(System_settings->M_updnLine, "%s", "1");
}
