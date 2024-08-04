/*
 * SPDX-FileCopyrightText: 2016-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_simplefoc.h"
#include "HAL.h"

#define TAG "FOC_Example"
/*update motor parameters based on hardware design*/
BLDCDriver3PWM driver = BLDCDriver3PWM(PHASE_U_GPIO, PHASE_V_GPIO, PHASE_W_GPIO);
BLDCMotor motor = BLDCMotor(MOTOR_PP);
MT6701 mt6701 = MT6701(MT6701_SPI_HOST, (gpio_num_t)MT6701_SPI_SCLK_GPIO, (gpio_num_t)MT6701_SPI_MISO_GPIO, (gpio_num_t)MT6701_SPI_MOSI_GPIO, (gpio_num_t)MT6701_SPI_CS_GPIO);

float target_angle = 0;
// instantiate the commander
Commander command = Commander(Serial);
void onTarget(char* cmd){command.target(&motor, cmd);}
void doMotor(char *cmd) { command.motor(&motor, cmd); }

/*Motor initialization*/
void motor_init(void)
{
  SimpleFOCDebug::enable();
  Serial.begin(115200);
  mt6701.init();
  motor.linkSensor(&mt6701);

  driver.voltage_power_supply = 5;
  driver.voltage_limit = 4;
  motor.velocity_limit = 10000;

#if USING_MCPWM
  driver.init(0);
#else
  driver.init({LEDC_CHAN_0, LEDC_CHAN_1, LEDC_CHAN_2});
#endif

  motor.linkDriver(&driver);
  motor.torque_controller = TorqueControlType::voltage;
  motor.controller = MotionControlType::torque;
  motor.motion_downsample = 2.0;

  // velocity loop PID
  motor.PID_velocity.P = 3.2;
  motor.PID_velocity.I = 0.0;
  motor.PID_velocity.D = 0.045;
  motor.PID_velocity.output_ramp = 10000.0;
  motor.PID_velocity.limit = 2.0;
  // Low pass filtering time constant
  motor.LPF_velocity.Tf = 0.005;
  // angle loop PID
  motor.P_angle.P = 20.0;
  motor.P_angle.I = 0.0;
  motor.P_angle.D = 0.0;
  motor.P_angle.output_ramp = 0.0;
  motor.P_angle.limit = 10000.0;
  // Low pass filtering time constant
  motor.LPF_angle.Tf = 0.0;
  // current q loop PID
  motor.PID_current_q.P = 3.0;
  motor.PID_current_q.I = 300.0;
  motor.PID_current_q.D = 0.0;
  motor.PID_current_q.output_ramp = 0.0;
  motor.PID_current_q.limit = 12.0;
  // Low pass filtering time constant
  motor.LPF_current_q.Tf = 0.005;
  // current d loop PID
  motor.PID_current_d.P = 3.0;
  motor.PID_current_d.I = 300.0;
  motor.PID_current_d.D = 0.0;
  motor.PID_current_d.output_ramp = 0.0;
  motor.PID_current_d.limit = 12.0;
  // Low pass filtering time constant
  motor.LPF_current_d.Tf = 0.005;
  // Limits
  motor.velocity_limit = 10000.0;
  motor.voltage_limit = 4.0;
  motor.current_limit = 2.0;
  // sensor zero offset - home position
  motor.sensor_offset = 0.0;
  // general settings
  // motor phase resistance
  motor.phase_resistance = 0.58;
  // pwm modulation settings
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor.modulation_centered = 1.0;

  // 添加串口命令
  command.add('M', doMotor, "my motor"); // align sensor and start FOC
  motor.useMonitoring(Serial);
  motor.init(); // initialize motor
  motor.initFOC();
  command.add('T', onTarget, "target angle");

  ESP_LOGI(TAG, "Motor Initialize Successfully");
}

static void motor_task(void *arg)
{
  while (1)
  {
    motor.loopFOC();
    // function intended to be used with serial plotter to monitor motor variables
    // significantly slowing the execution down!!!!
    motor.monitor(); // 使用simpleFOC Studio上位机设置的时候，这句一定要打开。但是会影响程序执行速度
    motor.move();

    // user communication
    command.run();
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void foc1_init(void)
{

  motor_init();

  xTaskCreate(motor_task, "motor_task", 4096, NULL, 5, NULL);
}
