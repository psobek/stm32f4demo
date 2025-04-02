/*
 * th06.c
 *
 *  Created on: 1 apr 2025
 *      Author: psobek
 */

#include "i2c.h"

uint8_t i2c_write_bytes(uint8_t i2c_address, uint8_t *buf, int buflen)
{
    uint32_t timeout;

    /*!< While the bus is busy */
    timeout = I2C_LONG_TIMEOUT;
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }

    /* Start the config sequence */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* Test on EV5 and clear it */
    timeout = I2C_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }

    /* Transmit the slave address and enable writing operation */
    I2C_Send7bitAddress(I2C1, i2c_address, I2C_Direction_Transmitter);

    /* Test on EV6 and clear it */
    timeout = I2C_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }

    /* Transmit the first byte */
    I2C_SendData(I2C1, buf[0]);

    /* Test on EV8 and clear it */
    timeout = I2C_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }
    for (int ndx = 1; ndx < buflen - 1; ndx++)
    {
        uint8_t value = buf[ndx];
        /* Prepare the register value to be sent */
        I2C_SendData(I2C1, value);

        /*!< Wait till all data have been physically transferred on the bus */
        timeout = I2C_LONG_TIMEOUT;
        while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF))
        {
            if ((timeout--) == 0)
            {
                return 1;
            }
        }
    }
    /* End the configuration sequence */
    I2C_GenerateSTOP(I2C1, ENABLE);

    /* Return the verifying value: 0 (Passed) or 1 (Failed) */
    return 0;
}

uint8_t i2c_read_bytes(uint8_t i2c_address, uint8_t *buf, int buflen)
{
    uint32_t timeout;

    /*!< While the bus is busy */
    timeout = I2C_LONG_TIMEOUT;
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }

    /* Start the config sequence */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* Test on EV5 and clear it */
    timeout = I2C_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((timeout--) == 0)
        {
            return 1;
        }
    }

    /* Transmit the slave address and enable read operation */
    I2C_Send7bitAddress(I2C1, i2c_address, I2C_Direction_Receiver);
    /* Wait on ADDR flag to be set (ADDR is still not cleared at this level */
    timeout = I2C_LONG_TIMEOUT;
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR) == RESET)
    {
        if ((timeout--) == 0)
            return 1;
    }

    /* Enable ACK */
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    /* Clear ADDR register by reading SR1 then SR2 register (SR1 has already been read) */
    (void)I2C1->SR2;
    while (buflen > 0)
    {
        if (buflen == 1)
        {
            /*!< Disable Acknowledgment */
            I2C_AcknowledgeConfig(I2C1, DISABLE);

            // /* Clear ADDR register by reading SR1 then SR2 register (SR1 has already been read) */
            // (void)I2C1->SR2;
            /*!< Send STOP Condition */
            I2C_GenerateSTOP(I2C1, ENABLE);

            /* Wait for the byte to be received */
            timeout = I2C_LONG_TIMEOUT;
            while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET)
            {
                if ((timeout--) == 0)
                    return 1;
            }

            /*!< Read the byte received from the Codec */
            *buf++ = I2C_ReceiveData(I2C1);
            buflen--;

            /* Wait to make sure that STOP flag has been cleared */
            timeout = I2C_LONG_TIMEOUT;
            while (I2C1->CR1 & I2C_CR1_STOP)
            {
                if ((timeout--) == 0)
                    return 1;
            }

            /*!< Re-Enable Acknowledgment to be ready for another reception */
            I2C_AcknowledgeConfig(I2C1, ENABLE);

            /* Clear AF flag for next communication */
            I2C_ClearFlag(I2C1, I2C_FLAG_AF);
        }
        else
        {
            timeout = I2C_LONG_TIMEOUT;
            while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET)
            {
                if ((timeout--) == 0)
                    return 1;
            }
            *buf++ = I2C_ReceiveData(I2C1);
            buflen--;
        }
    }
    return 0;
}