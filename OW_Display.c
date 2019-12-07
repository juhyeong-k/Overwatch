void shift1(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_0);
      GPIO_ResetBits(GPIOE, GPIO_Pin_0);
   }
   void latch1(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_1);
      GPIO_ResetBits(GPIOE, GPIO_Pin_1);
   }
   void shift2(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_2);
      GPIO_ResetBits(GPIOE, GPIO_Pin_2);
   }
   void latch2(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_3);
      GPIO_ResetBits(GPIOE, GPIO_Pin_3);
   }
   void shift3(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_4);
      GPIO_ResetBits(GPIOE, GPIO_Pin_4);
   }
   void latch3(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_5);
      GPIO_ResetBits(GPIOE, GPIO_Pin_5);
   }
   void shift4(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_6);
      GPIO_ResetBits(GPIOE, GPIO_Pin_6);
   }
   void latch4(void){
      GPIO_SetBits(GPIOE, GPIO_Pin_7);
      GPIO_ResetBits(GPIOE, GPIO_Pin_7);
   }
   void time_write1(uint8_t time_data){
   uint8_t check= 3;
      for(int i= 0; i< 8; i++){
         if(time_data& 128){
            GPIO_SetBits(GPIOE, GPIO_Pin_8);
         }
         else{
            GPIO_ResetBits(GPIOE, GPIO_Pin_8);
         }
         shift1();
         time_data= time_data<< 1;
      }
      latch1();
   }
   void time_write2(uint8_t time_data){
   uint8_t check= 3;
      for(int i= 0; i< 8; i++){
         if(time_data& 128){
            GPIO_SetBits(GPIOE, GPIO_Pin_9);
         }
         else{
            GPIO_ResetBits(GPIOE, GPIO_Pin_9);
         }
         shift2();
         time_data= time_data<< 1;
      }
      latch2();
   }
   void time_write3(uint8_t time_data){
   uint8_t check= 3;
      for(int i= 0; i< 8; i++){
         if(time_data& 128){
            GPIO_SetBits(GPIOE, GPIO_Pin_10);
         }
         else{
            GPIO_ResetBits(GPIOE, GPIO_Pin_10);
         }
         shift3();
         time_data= time_data<< 1;
      }
      latch3();
   }
   void time_write4(uint8_t time_data){
   uint8_t check= 3;
      for(int i= 0; i< 8; i++){
         if(time_data& 128){
            GPIO_SetBits(GPIOE, GPIO_Pin_11);
         }
         else{
            GPIO_ResetBits(GPIOE, GPIO_Pin_11);
         }
         shift4();
         time_data= time_data<< 1;
      }
      latch4();
   }
void Disp(int get_time)
{
		
      int t1, t2, t3, t4= 0;
      
      if(get_time > 999){
         t1= get_time%10;
         get_time= get_time/10;
         t2= get_time%10;
         get_time= get_time/10;
         t3= get_time%10;
         get_time= get_time/10;
         t4= get_time%10;
      }
			else{
				t1= get_time%10;
				get_time= get_time/10;
         t2= get_time%10;
         get_time= get_time/10;
         t3= get_time%10;
         get_time= get_time/10;
         t4= 0;
			}
      
      uint8_t num[11]= {192, 249, 164, 176, 153, 146, 130, 248, 128, 144, 0};
      uint8_t num_rev[11]= {192, 207, 164, 134, 139, 146, 144, 199, 128, 130,0};
			time_write1(num_rev[10]);
      time_write2(num_rev[10]);
      time_write3(num[10]);
      time_write4(num[10]);
      time_write1(num_rev[t1]);
      time_write2(num_rev[t2]);
      time_write3(num[t3]);
      time_write4(num[t4]);
   
}
void Display(Struct_Info* System_info, Struct_Time* System_time)
{
	osMutexAcquire(System_time_using,osWaitForever);
	int get_time = (atoi(System_time->Hours)*100) + atoi(System_time->Minutes);
	osMutexRelease(System_time_using);

	Disp(get_time);
}
