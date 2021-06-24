#include "TM4C123.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/*
 *	MPU 6050 Register Descriptions
 *
 */


#define XG_OFFS_TC          0x00
#define YG_OFFS_TC          0x01
#define ZG_OFFS_TC          0x02
#define X_FINE_GAIN         0x03
#define Y_FINE_GAIN         0x04
#define Z_FINE_GAIN         0x05
#define XA_OFFS_H           0x06 
#define XA_OFFS_L_TC        0x07
#define YA_OFFS_H           0x08 
#define YA_OFFS_L_TC        0x09
#define ZA_OFFS_H           0x0A 
#define ZA_OFFS_L_TC        0x0B
#define XG_OFFS_USRH        0x13
#define XG_OFFS_USRL        0x14
#define YG_OFFS_USRH        0x15
#define YG_OFFS_USRL        0x16
#define ZG_OFFS_USRH        0x17
#define ZG_OFFS_USRL        0x18
#define SMPLRT_DIV          0x19
#define CONFIG              0x1A
#define GYRO_CONFIG         0x1B
#define ACCEL_CONFIG        0x1C
#define FF_THR              0x1D
#define FF_DUR              0x1E
#define MOT_THR             0x1F
#define MOT_DUR             0x20
#define ZRMOT_THR           0x21
#define ZRMOT_DUR           0x22
#define FIFO_EN             0x23
#define I2C_MST_CTRL        0x24
#define I2C_SLV0_ADDR       0x25
#define I2C_SLV0_REG        0x26
#define I2C_SLV0_CTRL       0x27
#define I2C_SLV1_ADDR       0x28
#define I2C_SLV1_REG        0x29
#define I2C_SLV1_CTRL       0x2A
#define I2C_SLV2_ADDR       0x2B
#define I2C_SLV2_REG        0x2C
#define I2C_SLV2_CTRL       0x2D
#define I2C_SLV3_ADDR       0x2E
#define I2C_SLV3_REG        0x2F
#define I2C_SLV3_CTRL       0x30
#define I2C_SLV4_ADDR       0x31
#define I2C_SLV4_REG        0x32
#define I2C_SLV4_DO         0x33
#define I2C_SLV4_CTRL       0x34
#define I2C_SLV4_DI         0x35
#define I2C_MST_STATUS      0x36
#define INT_PIN_CFG         0x37
#define INT_ENABLE          0x38
#define DMP_INT_STATUS      0x39
#define INT_STATUS          0x3A
#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x3C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40
#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42
#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48
#define EXT_SENS_DATA_00    0x49
#define EXT_SENS_DATA_01    0x4A
#define EXT_SENS_DATA_02    0x4B
#define EXT_SENS_DATA_03    0x4C
#define EXT_SENS_DATA_04    0x4D
#define EXT_SENS_DATA_05    0x4E
#define EXT_SENS_DATA_06    0x4F
#define EXT_SENS_DATA_07    0x50
#define EXT_SENS_DATA_08    0x51
#define EXT_SENS_DATA_09    0x52
#define EXT_SENS_DATA_10    0x53
#define EXT_SENS_DATA_11    0x54
#define EXT_SENS_DATA_12    0x55
#define EXT_SENS_DATA_13    0x56
#define EXT_SENS_DATA_14    0x57
#define EXT_SENS_DATA_15    0x58
#define EXT_SENS_DATA_16    0x59
#define EXT_SENS_DATA_17    0x5A
#define EXT_SENS_DATA_18    0x5B
#define EXT_SENS_DATA_19    0x5C
#define EXT_SENS_DATA_20    0x5D
#define EXT_SENS_DATA_21    0x5E
#define EXT_SENS_DATA_22    0x5F
#define EXT_SENS_DATA_23    0x60
#define MOT_DETECT_STATUS   0x61
#define I2C_SLV0_DO         0x63
#define I2C_SLV1_DO         0x64
#define I2C_SLV2_DO         0x65
#define I2C_SLV3_DO         0x66
#define I2C_MST_DELAY_CTRL  0x67
#define SIGNAL_PATH_RESET   0x68
#define MOT_DETECT_CTRL     0x69
#define USER_CTRL           0x6A
#define PWR_MGMT_1          0x6B
#define PWR_MGMT_2          0x6C
#define BANK_SEL            0x6D
#define MEM_START_ADDR      0x6E
#define MEM_R_W             0x6F
#define DMP_CFG_1           0x70
#define DMP_CFG_2           0x71
#define FIFO_COUNTH         0x72
#define FIFO_COUNTL         0x73
#define FIFO_R_W            0x74
#define WHO_AM_I            0x75

/*
 *	Enum for checking error flags
 * 
 */
typedef enum
{	
	No_Error = 0x0U,
	Error = !No_Error

}I2C_ErrorType_t;

void I2C_Init(void); // I2C1 Module Configuration
void MPU6050_Init(void); // Configures the MPU6050
void UART_Config(void); // Configures the UART Module
void UART5_Transmitter(unsigned char data); // UART Send API
void Delay(unsigned long counter); // Delay for sometime
void printstring(char *str); // Print Message over UART
I2C_ErrorType_t I2C3_ReceiveData(int slaveAddr, char memAddr, int byteCount, char* data); // Receive data from MPU
I2C_ErrorType_t I2C_transmitData(uint8_t slaveAddr, uint8_t regAdrr, uint8_t dataToSend); // Transmit 1 byte data
I2C_ErrorType_t I2C_waitBusy(void); // Wait for busy flag


static char msg[20];

int main(void)
{
	int  Accal_RawData_X, Accal_RawData_Y, Accal_RawData_Z, Gyro_RawData_X, Gyro_RawData_Y, Gyro_RawData_Z; // Stores RAW Data
	double Accel_X, Accel_Y, Accel_Z, Gyro_X, Gyro_Y, Gyro_Z; // After Conversion Data
	char sensordata[14]; // Data from MPU 
	
	I2C_Init();     // Start I2C
	Delay(1000);    // Wait 
	MPU6050_Init(); // Start MPU
	Delay(1000);    // Wait
  UART_Config();  // Start UART
	
	while(1)
	{	 
		 I2C3_ReceiveData(0x68,ACCEL_XOUT_H, 14, sensordata);
		
		 Accal_RawData_X = (int) ( (sensordata[0] << 8 ) | sensordata[1] );
		 Accal_RawData_Y = (int) ( (sensordata[2] << 8 ) | sensordata[3] );
		 Accal_RawData_Z = (int) ( (sensordata[4] << 8 ) | sensordata[5] );
		 Gyro_RawData_X = (int) ( (sensordata[8] << 8 )  | sensordata[9] );
		 Gyro_RawData_Y = (int) ( (sensordata[10] << 8 ) | sensordata[11] );
		 Gyro_RawData_Z = (int) ( (sensordata[12] << 8 ) | sensordata[13] );
 
		
   // Convert The Readings
		
		Accel_X = (double)Accal_RawData_X/(double)16384.0;  // MPU 6050 
		Accel_Y = (double)Accal_RawData_Y/(double)16384.0;
		Accel_Z = (double)Accal_RawData_Z/(double)16384.0;
		Gyro_X = (double)Gyro_RawData_X/(double)131.0;
		Gyro_Y = (double)Gyro_RawData_Y/(double)131.0;
		Gyro_Z = (double)Gyro_RawData_Z/(double)131.0;
		
     sprintf(msg,"Gx = %.2f \t", Gyro_X);
     printstring(msg);
		 sprintf(msg,"Gy = %.2f \t",Gyro_Y);
     printstring(msg);
		 sprintf(msg,"Gz  = %.2f \t",Gyro_Z);
     printstring(msg);
		 sprintf(msg,"Ax  = %.2f \t",Accel_X);
     printstring(msg);
		 sprintf(msg,"Ay  = %.2f \t",Accel_Y);
     printstring(msg);
		 sprintf(msg,"Az  = %.2f \r\n",Accel_Z);
     printstring(msg);
		
     Delay(1000);
		 
	}

}

void I2C_Init(void)
{
	/* Tiva C Reference Manual */
	
	SYSCTL->RCGCI2C  |= (0x1U << 1U); // I2C1 Clock Enable
	SYSCTL->RCGCGPIO |= (0x1U << 0U); // Port A Enable  for PA6 = SCL   PA7 = SDA
	
	GPIOA->AFSEL |= (0x3U << 6U); 	  // PA6 ve PA7 Alternate Function Mode Enable
	GPIOA->DEN   |= (0x3U << 6U); 		// PA6 ve PA7 Digital Enable
	GPIOA->ODR   |= (0x1U << 7U); 		// Enable the Open Drain PA7
	GPIOA->PCTL  |= (0x3U << 6U) | (0x3U << 7U); //  Alternate Function 3 Mode is Enable for PA6 and PA7
	
	I2C1->MCR  |= (0x1U << 4U);  		  // Master Mode Enable
	I2C1->MTPR = 0x7U;            	  // 100 KHz I2C Clock Active


}

/* Tiva C Reference Manual */

I2C_ErrorType_t I2C_transmitData(uint8_t slaveAddr, uint8_t regAdrr, uint8_t dataToSend)
{
	I2C_ErrorType_t errorStatus = No_Error;
	
	I2C1->MSA |= ((uint32_t)slaveAddr << 1U); // Slave Addr To Talk and for writing Bit0 = 0 for Write
	I2C1->MDR = regAdrr;
	I2C1->MCS |= (0xBU << 0U); //  /* S-(saddr+w)-ACK-regAdrr-ACK */ /* I2C's hardware Job */
	
	errorStatus = I2C_waitBusy();
	
	if(errorStatus) return errorStatus;
	
	I2C1->MDR = dataToSend;
	I2C1->MCS |= (0x5U << 0U);  /* -data-ACK-P */
	
	errorStatus = I2C_waitBusy();  /* wait until write is complete */
	
	while(I2C1->MCS & 0x40U); /* wait until bus is not busy */
	
	if(errorStatus) return errorStatus;
	
	
	return errorStatus; /* no error */

}

I2C_ErrorType_t I2C_waitBusy(void)
{
	I2C_ErrorType_t errorStatus = No_Error;
	
	while(I2C1->MCS & 0x1U);  // Checks the busy flag
	
	if(I2C1->MCS & 0xEU)
	{
		errorStatus = Error; // Error control
		
	}
	
	return errorStatus;
}

void MPU6050_Init(void)
{
	/* MPU6050 DataSheet */
	
	I2C_transmitData(0x68, SMPLRT_DIV, 0x7); // Sample rate for 1kHz
	I2C_transmitData(0x68, PWR_MGMT_1, 0x1); // 8 Mhz Internal Clock is active
	I2C_transmitData(0x68, GYRO_CONFIG, 0x18); // Configure GYRO
	I2C_transmitData(0x68, ACCEL_CONFIG, 0x18); // Configure Accel
	I2C_transmitData(0x68, INT_ENABLE, 0x1); // Enable data ready interrupt to read data when it is ready
	
}
void UART_Config(void)
{ 
		/* Tiva C Reference Manual */
	  /* UART Config */
	
	  SYSCTL->RCGCUART |= 0x20;  /* enable clock to UART5 */
    SYSCTL->RCGCGPIO |= 0x10;  /* enable clock to PORTE for PE4/Rx and PE5/Tx */
    Delay(1);
    /* UART0 initialization */
    UART5->CTL = 0;         /* UART5 module disbable */
    UART5->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART5->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART5->CC = 0;          /*select system clock*/
    UART5->LCRH = 0x60;     /* data length 8-bit, not parity bit, no FIFO */
    UART5->CTL = 0x301;     /* Enable UART5 module, Rx and Tx */

		/* PINS */
    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIOE->DEN = 0x30;      /* set PE4 and PE5 as digital */
    GPIOE->AFSEL = 0x30;    /* Use PE4,PE5 alternate function */
    GPIOE->AMSEL = 0;    /* Turn off analg function*/
    GPIOE->PCTL = 0x00110000;     /* configure PE4 and PE5 for UART */
}

void UART5_Transmitter(unsigned char data)  
{
    while((UART5->FR & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5->DR = data;                  /* before giving it another byte */
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter*10000; i++);
}

void printstring(char *str)
{
  while(*str)
	{
		UART5_Transmitter(*(str++));
	}
}

I2C_ErrorType_t I2C3_ReceiveData(int slaveAddr, char memAddr, int byteCount, char* data)
{
     I2C_ErrorType_t error;
    
    if (byteCount <= 0)
        return 1;         /* no read was performed */

    /* send slave address and starting address */
    I2C3->MSA = (uint32_t)slaveAddr << 1;
    I2C3->MDR = memAddr;
    I2C3->MCS = 3;       /* S-(saddr+w)-ACK-maddr-ACK */
    error = I2C_waitBusy();
    if (error)
        return error;

    /* to change bus from write to read, send restart with slave addr */
    I2C3->MSA = ((uint32_t)slaveAddr << 1) + 1U;   /* restart: -R-(saddr+r)-ACK */

    if (byteCount == 1)             /* if last byte, don't ack */
        I2C3->MCS = 7;              /* -data-NACK-P */
    else                            /* else ack */
        I2C3->MCS = 0xB;            /* -data-ACK- */
    error = I2C_waitBusy();
    if (error) return error;

    *data++ = (char)I2C1->MDR;            /* store the data received */

    if (--byteCount == 0)           /* if single byte read, done */
    {
        while(I2C3->MCS & 0x40);    /* wait until bus is not busy */
        return 0;       /* no error */
    }
 
    /* read the rest of the bytes */
    while (byteCount > 1)
    {
        I2C3->MCS = 9;              /* -data-ACK- */
        error = I2C_waitBusy();
        if (error) return error;
        byteCount--;
        *data++ = (char)I2C1->MDR;        /* store data received */
    }

    I2C3->MCS = 5;                  /* -data-NACK-P */
    error = I2C_waitBusy();
    *data = (char)I2C1->MDR;              /* store data received */
    while(I2C3->MCS & 0x40);        /* wait until bus is not busy */
    
    return 0;       /* no error */
}

