#ifndef MAX30100_H_
#define MAX30100_H_
#include "ONboard_IIC.h"
#include "intrins.h"


#define MAX30100_FIFO_DEPTH                     0x10

// FIFO control and data registers
#define MAX30100_REG_FIFO_WRITE_POINTER         0x02
#define MAX30100_REG_FIFO_OVERFLOW_COUNTER      0x03
#define MAX30100_REG_FIFO_READ_POINTER          0x04
#define MAX30100_REG_FIFO_DATA                  0x05  // Burst read does not autoincrement addr

#define ADDRESS_MAX30100_INTSTATUS 0x00
#define ADDRESS_MAX30100_INTEN 0x01
#define ADDRESS_MAX30100_FIFOWRPtr 0x02
#define ADDRESS_MAX30100_OFCounter 0x03
#define ADDRESS_MAX30100_FIFIOEDPtr 0x04
#define ADDRESS_MAX30100_FIFOData 0x05
#define ADDRESS_MAX30100_MODECFG 0x06
#define ADDRESS_MAX30100_SPO2CFG 0x07
#define ADDRESS_MAX30100_LEDCFG 0x09

#define ADDRESS_MAX30100 0xAE
#define ADDRESS_MAX30100_TEMP 0x16

#define ADDRESS_MAX30100_RevID 0xFE
#define ADDRESS_MAX30100_PartID 0xFF

#define MAX30100_REG_MODE_CONFIGURATION         0x06
#define MAX30100_MC_TEMP_EN                     (1 << 3)
#define MAX30100_MC_SHDN                        (1 << 7)


#define MAX30100_REG_SPO2_CONFIGURATION         0x07
#define MAX30100_SPC_SPO2_HI_RES_EN             (1 << 6)
#define MAX30100_REG_LED_CONFIGURATION          0x09

#define MAX30100_DEFAULT_MODE                MAX30100_MODE_HRONLY
#define MAX30100_DEFAULT_SAMPLING_RATE       MAX30100_SAMPRATE_100HZ
#define MAX30100_DEFAULT_PULSE_WIDTH         MAX30100_SPC_PW_1600US_16BITS
#define MAX30100_DEFAULT_RED_LED_CURRENT     MAX30100_LED_CURR_50MA
#define MAX30100_DEFAULT_IR_LED_CURRENT      MAX30100_LED_CURR_50MA
#define MAX30100_EXPECTED_PART_ID            0x11
#define MAX30100_RINGBUFFER_SIZE             16


typedef enum _LEDCurrent {
	MAX30100_LED_CURR_0MA      = 0x00,
	MAX30100_LED_CURR_4_4MA    = 0x01,
	MAX30100_LED_CURR_7_6MA    = 0x02,
	MAX30100_LED_CURR_11MA     = 0x03,
	MAX30100_LED_CURR_14_2MA   = 0x04,
	MAX30100_LED_CURR_17_4MA   = 0x05,
	MAX30100_LED_CURR_20_8MA   = 0x06,
	MAX30100_LED_CURR_24MA     = 0x07,
	MAX30100_LED_CURR_27_1MA   = 0x08,
	MAX30100_LED_CURR_30_6MA   = 0x09,
	MAX30100_LED_CURR_33_8MA   = 0x0a,
	MAX30100_LED_CURR_37MA     = 0x0b,
	MAX30100_LED_CURR_40_2MA   = 0x0c,
	MAX30100_LED_CURR_43_6MA   = 0x0d,
	MAX30100_LED_CURR_46_8MA   = 0x0e,
	MAX30100_LED_CURR_50MA     = 0x0f
} LEDCurrent;


typedef enum _SamplingRate {
  MAX30100_SAMPRATE_50HZ      = 0x00,
	MAX30100_SAMPRATE_100HZ     = 0x01,
	MAX30100_SAMPRATE_167HZ     = 0x02,
	MAX30100_SAMPRATE_200HZ     = 0x03,
	MAX30100_SAMPRATE_400HZ     = 0x04,
	MAX30100_SAMPRATE_600HZ     = 0x05,
	MAX30100_SAMPRATE_800HZ     = 0x06,
	MAX30100_SAMPRATE_1000HZ    = 0x07
} SamplingRate;


typedef enum LEDPulseWidth {
    MAX30100_SPC_PW_200US_13BITS    = 0x00,
    MAX30100_SPC_PW_400US_14BITS    = 0x01,
    MAX30100_SPC_PW_800US_15BITS    = 0x02,
    MAX30100_SPC_PW_1600US_16BITS   = 0x03
} LEDPulseWidth;

typedef enum Mode {
    MAX30100_MODE_HRONLY    = 0x02,
    MAX30100_MODE_SPO2_HR   = 0x03
} Mode;

typedef struct {
    unsigned short ir;
    unsigned short red;
} SensorReadout;

extern SensorReadout xdata readoutBuffer[16];
extern SensorReadout xdata *head;
extern SensorReadout xdata *tail;
extern unsigned short MAX30100_count;
extern char MAX30100_Init();		//1
extern unsigned char MAX30100_getPartID();	//2
extern char MAX30100_readRegister(unsigned char RAdd);	
extern void MAX30100_writeRegister(unsigned char RAdd,unsigned char Data);	
void MAX30100_setMode(Mode mode);
void MAX30100_setLedsPulseWidth(LEDPulseWidth ledPulseWidth);
void MAX30100_setSamplingRate(SamplingRate samplingRate);
void MAX30100_setLedsCurrent(LEDCurrent irLedCurrent, LEDCurrent redLedCurrent);
void MAX30100_setHighresModeEnabled(char enabled);
void MAX30100_update();
char MAX30100_getRawValues(unsigned short *ir, unsigned short *red);
extern float MAX30100_getTemperature(); //4
extern void MAX30100_startTemperatureSampling();	//3
extern float MAX30100_retrieveTemperature();	//5
extern char MAX30100_readRegister(unsigned char RAdd);
extern void MAX30100_restFifo();	//0
extern void MAX30100_readMultiByte(unsigned char address,unsigned char* MAX30100_buffer,unsigned char length);
extern char MAX30100_Buffer_Push(SensorReadout value);
void readFifoData();
SensorReadout MAX30100_Buffer_pop();
void shutdown();				//6
void resume();                   //7

#endif
