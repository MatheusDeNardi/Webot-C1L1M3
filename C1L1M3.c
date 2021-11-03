/*
 * File:          Controlador1.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <stdio.h>
#include <stdlib.h>

#include <webots/robot.h>

#include <webots/motor.h>
#include <webots/distance_sensor.h>

#include <webots/supervisor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 32
#define QtddSensorDist 8

static WbDeviceTag motorE, motorD;

static WbDeviceTag GroundE, GroundD;
static double GroundE_Valor, GroundD_Valor;


#define LEFT 0
#define RIGHT 1
#define MAX_SPEED 6.28


/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
 
 
 
 
 
 
 
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  float right_speed,left_speed;
  
  
  wb_robot_init();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  //MOTORES
  motorE = wb_robot_get_device("left wheel motor");
  motorD = wb_robot_get_device("right wheel motor");
  
  wb_motor_set_position(motorE, INFINITY);
  wb_motor_set_position(motorD, INFINITY);
  
  wb_motor_set_velocity(motorE, 0);
  wb_motor_set_velocity(motorD, 0);
  
  
  
  //sensor de solo
  GroundE = wb_robot_get_device("IR0");
  wb_distance_sensor_enable(GroundE, TIME_STEP);
  
  GroundD = wb_robot_get_device("IR1");
  wb_distance_sensor_enable(GroundD, TIME_STEP);

  
  
  
  
  
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

 
    left_speed = MAX_SPEED*0.40;
    right_speed = MAX_SPEED*0.40;
    
    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
    
    GroundE_Valor = wb_distance_sensor_get_value(GroundE);
    GroundD_Valor = wb_distance_sensor_get_value(GroundD);

    if (GroundE_Valor>GroundD_Valor && 6<GroundE_Valor && GroundE_Valor<15) left_speed = -MAX_SPEED*0.15;
    else if (GroundD_Valor>GroundE_Valor && 6<GroundD_Valor && GroundD_Valor<15) right_speed = -MAX_SPEED*0.15;
    
    wb_motor_set_velocity(motorE, left_speed);
    wb_motor_set_velocity(motorD, right_speed); 
    
    
 
    //posicao_Caixa1 = wb_supervisor_field_get_sf_vec3f(Caixa1_field);
    
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
