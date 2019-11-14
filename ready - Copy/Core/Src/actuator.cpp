#include "actuator.h"
#include "main.h"
//#include "pid.h"
#define setpoint (34.0)

extern motor gMotors[4];
//static float velocity_robot[3]={0,0,0};
// float velocity = 10;
int32_t time = HAL_GetTick();

void play(void)
{
   //PID pid;
/*   char data;
   if(HAL_UART_Receive(&huart2,(uint8_t*)&data,1,10)==HAL_OK){
      printf("\n %c",data);
      switch(data)
      {
         case 'L':{
            velocity_robot[0]= 0;
            velocity_robot[1]= velocity;
            velocity_robot[2]= 0;
            // printf("\nforward");
          break;
         }
         case 'R':{
            velocity_robot[0]= 0;
            velocity_robot[1]= -velocity;
            velocity_robot[2]= 0;
            // printf("\back");
          break;
         }
         case 'F':{
            velocity_robot[0]= velocity;
            velocity_robot[1]= 0;
            velocity_robot[2]= 0;
            // printf("\nright");
          break;
         }
         case 'B':{
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
          case 'G':{
            velocity_robot[0]= 0;
            velocity_robot[1]= 0;
            velocity_robot[2]= -(velocity-11);
            // printf("\nstop");
          break;
         }
          case 'I':{
            velocity_robot[0]= 0;
            velocity_robot[1]= 0;
            velocity_robot[2]= (velocity-11);
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
//}

void calculate_wheel_velocity()
//{
   // printf("here\n");
   float velocity_motor[4] = {0,0,0,0};
	float coupling_matrix[4][3] = {{0.707,0.707,1},
                                 {0.707,-0.707,1},
                                 {-0.707,-0.707,1},
                                 {-0.707,0.707,1}};
    for(int i=0;i<4;i++)
    {
        velocity_motor[i] = 0;
        for(int j=0;j<3;j++)
        {
             velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
      printf("\t%d",(int)(velocity_motor[i]*100) );
*/      
       // motor[i].(velocity_motor[i]);
       //float iOmega=get_data(3);
      // gMotors[3].set_omega(Omega);
		if((HAL_GetTick() - time) >= SAMPLE_TIME){
         time = HAL_GetTick();
         // calculate_data(0);   //omega=0,-5.4976
         // calculate_data(1);   //omega=0,-5.4976
         // calculate_data(2);   //omega=0,-5.4976
         // calculate_data(3);   //omega=0,-5.4976
         // float iOmega=get_data(0);     // printf("\n%f",iOmega);
         //  float iOmega=get_data(1);     // printf("\n%f",iOmega);
         // float iOmega=get_data(2);     // printf("\n%f",iOmega);
         // float iOmega=get_data(3);     // printf("\n%f",iOmega);
         //printf("\n%f\t%f\t%f\t%f",get_data(0),get_data(1),get_data(2),get_data(3));
         printf("\n");
         gMotors[0].motor_input(setpoint,get_data(0));
         gMotors[1].motor_input(setpoint,get_data(1));
         gMotors[2].motor_input(setpoint,get_data(2));
         gMotors[3].motor_input(setpoint,get_data(3));
             

         //gMotors[3].set_omega(iOmega);
        // get_data(3);
         //printf("Omega=%f",get_data(3));
         //get_cnt(0);
      }
      //pid.setPID(2.0526,0.078101,0);
      //pid.setlimits(75,-75);
     // printf("Omega=%f",get_data(1));
     // pid.computePID(50,get_data(1));

      
    //}
	
   //  for(int i=0;i<4;i++)
   //  {
   //      //ocr_motor[i] = ((249.0*velocity_motor[i])/(MAX_RPM));//multiply by icr_top value
	// 	ocr_motor[i] = velocity_motor[i]*PPR/3000.0;
	// 	velocity_robot[i] = 0;
	// 	p[i].Set_SP(ocr_motor[i]);
   //  }
	  
}

	  
