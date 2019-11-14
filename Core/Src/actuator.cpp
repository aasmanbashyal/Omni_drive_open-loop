#include "actuator.h"
#include "main.h"

extern motor motor[4];

static float velocity_robot[3]={0,0,0};
float velocity = 30;
int32_t time = HAL_GetTick();

void play(void)
{
    char data;
   if(HAL_UART_Receive(&huart2,(uint8_t*)&data,1,10)==HAL_OK){
      printf("\n %c",data);
      switch(data)
      {
         case 'F':{
            velocity_robot[0]= 0;
            velocity_robot[1]= velocity;
            velocity_robot[2]= 0;
            // printf("\nforward");
          break;
         }
         case 'B':{
            velocity_robot[0]= 0;
            velocity_robot[1]= -velocity;
            velocity_robot[2]= 0;
            // printf("\back");
          break;
         }
         case 'L':{
            velocity_robot[0]= velocity;
            velocity_robot[1]= 0;
            velocity_robot[2]= 0;
            // printf("\nright");
          break;
         }
         case 'R':{
            velocity_robot[0]= -velocity;
            velocity_robot[1]= 0;
            velocity_robot[2]= 0;
            // printf("\nleft");
          break;
         }
         case 'S':{
            velocity_robot[0]= 0;
            velocity_robot[1]= 0;
            velocity_robot[2]= 0;
            // printf("\nstop");
          break;
         }
          case 'I':{
            velocity_robot[0]= -(velocity/2);
            velocity_robot[1]= -(velocity/2);
            velocity_robot[2]= 0;
            // printf("\nstop");
          break;
         }
          case 'G':{
            velocity_robot[0]= (velocity/2);
            velocity_robot[1]= (velocity/2);
            velocity_robot[2]= 0;
            // printf("\nstop");
          break;
         }
         case 'H':{
            velocity_robot[0]= (velocity/2);
            velocity_robot[1]= -(velocity/2);
            velocity_robot[2]= 0;
            // printf("\nstop");
          break;
         }
         case 'J':{
            velocity_robot[0]= -(velocity/2);
            velocity_robot[1]= (velocity/2);
            velocity_robot[2]= 0;
            // printf("\nstop");
          break;
         }
         default:{
          velocity_robot[0]= 0;
            velocity_robot[1]= 0;
            velocity_robot[2]= 0;
            // printf("\ndefault");
          break;
         }
      }
      // printf("here too");
      printf("\n%d\t%d\t%d\t",(int)velocity_robot[0], (int)velocity_robot[1], (int)velocity_robot[2] );
   
      calculate_wheel_velocity();
   }
   else{
      // printf("\nnodata");
   }
}

void calculate_wheel_velocity()
{
   // printf("here\n");
   float velocity_motor[4] = {0,0,0,0};
	float coupling_matrix[4][3] = {{0.707,-0.707,1},
                                 {-0.707,-0.707,1},
                                 {-0.707,0.707,1},
                                 {0.707,0.707,1}};
    for(int i=0;i<4;i++)
    {
        velocity_motor[i] = 0;
        for(int j=0;j<3;j++)
        {
             velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
      printf("\t%d",(int)(velocity_motor[i]*100) );
      
       motor[i].set_omega(velocity_motor[i]);
      //  motor[1].set_omega(-30);
		// if((HAL_GetTick() - time) >= SAMPLE_TIME){
      //    time = HAL_GetTick();
      //    calculate_data(1);
      //    get_data(1);
         //get_cnt(0);
      }
    //}
	
}

	  
