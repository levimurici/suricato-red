/**
 * Generated by Eclipse Mita 0.1.0.
 * @date 2021-09-13 13:23:50
 */


#include <BCDS_Basics.h>
#include <FreeRTOS.h>
#include <inttypes.h>
#include <BCDS_Retcode.h>
#include <stdio.h>
#include <BCDS_CmdProcessor.h>
#include <XdkSystemStartup.h>
#include <timers.h>
#include "application.h"
#include "SensorButton_one.h"
#include "SensorLight.h"
#include "SensorEnvironment.h"
#include "ConnectivityMQTTMessaging.h"
#include "ConnectivityWLANMyWifiResource.h"
#include "MitaTime.h"
#include "MitaEvents.h"
#include "MitaExceptions.h"

static Retcode_T Mita_initialize(void* userParameter1, uint32_t userParameter2);
static Retcode_T Mita_goLive(void* userParameter1, uint32_t userParameter2);

CmdProcessor_T Mita_EventQueue;

/**
 * The priority of the event loop task. The default of 1 is just above the idle task
 * priority. Note that the platform may use tasks of higher prio, but XDK LIVE programs
 * are solely executed in this event loop context.
 */
#define TASK_PRIO_EVENT_LOOP         (UINT32_C(1))

/**
 * The stack size of the event loop task in 32-bit words. If you don't know what this
 * means, be careful when you change this value. More information can be found here:
 * http://www.freertos.org/FAQMem.html#StackSize
 */
#define TASK_STACK_SIZE_EVENT_LOOP   (UINT16_C(2000))

/**
 * The maximum number of events the event queue can hold. The default value should
 * be sufficient in most cases. If you need to handle a lot of events and have some
 * long running computations, you might want to increase this number if you find
 * events are missed.
 */
#define TASK_Q_LEN_EVENT_LOOP        (UINT32_C(10))


int main(void)
{
	/* Mapping Default Error Handling function */
	Retcode_T returnValue = Retcode_initialize(DefaultErrorHandlingFunc);
	if (RETCODE_OK == returnValue)
	{
	    returnValue = systemStartup();
	}
	if (RETCODE_OK == returnValue)
	{
		returnValue = CmdProcessor_Initialize(&Mita_EventQueue, (char *) "EventQueue", TASK_PRIO_EVENT_LOOP, TASK_STACK_SIZE_EVENT_LOOP, TASK_Q_LEN_EVENT_LOOP);
	}
	if (RETCODE_OK == returnValue)
	{
		returnValue = CmdProcessor_Enqueue(&Mita_EventQueue, Mita_initialize, NULL, UINT32_C(0));
	}
	if (RETCODE_OK == returnValue)
	{
	    returnValue = CmdProcessor_Enqueue(&Mita_EventQueue, Mita_goLive, NULL, UINT32_C(0));
	}
	if (RETCODE_OK != returnValue)
	{
	    printf("System Startup failed");
	    assert(false);
	}
	/* start scheduler */
	vTaskStartScheduler();
}

Retcode_T Mita_initialize(void* userParameter1, uint32_t userParameter2)
{
	BCDS_UNUSED(userParameter1);
	BCDS_UNUSED(userParameter2);
	Retcode_T exception = NO_EXCEPTION;
	

	// setup resources
	exception = ConnectivityWLANMyWifiResource_Setup();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup ConnectivityWLANMyWifiResource succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup ConnectivityWLANMyWifiResource\n", __FILE__, __LINE__);
		return exception;
	}
	
	exception = ConnectivityMQTTMessaging_Setup();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup ConnectivityMQTTMessaging succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup ConnectivityMQTTMessaging\n", __FILE__, __LINE__);
		return exception;
	}
	
	exception = SensorEnvironment_Setup();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup SensorEnvironment succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup SensorEnvironment\n", __FILE__, __LINE__);
		return exception;
	}
	
	exception = SensorLight_Setup();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup SensorLight succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup SensorLight\n", __FILE__, __LINE__);
		return exception;
	}
	
	exception = SensorButton_one_Setup();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup SensorButton_one succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup SensorButton_one\n", __FILE__, __LINE__);
		return exception;
	}
	


	// setup time
	exception = SetupTime();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] setup Time succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to setup Time\n", __FILE__, __LINE__);
		return exception;
	}
	return exception;
}

Retcode_T Mita_goLive(void* userParameter1, uint32_t userParameter2)
{
	BCDS_UNUSED(userParameter1);
	BCDS_UNUSED(userParameter2);
	Retcode_T exception = NO_EXCEPTION;
	

	exception = EnableTime();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable Time succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable Time\n", __FILE__, __LINE__);
		return exception;
	}
	
	exception = ConnectivityWLANMyWifiResource_Enable();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable ConnectivityWLANMyWifiResource succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable ConnectivityWLANMyWifiResource\n", __FILE__, __LINE__);
		return exception;
	}
	exception = ConnectivityMQTTMessaging_Enable();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable ConnectivityMQTTMessaging succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable ConnectivityMQTTMessaging\n", __FILE__, __LINE__);
		return exception;
	}
	exception = SensorEnvironment_Enable();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable SensorEnvironment succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable SensorEnvironment\n", __FILE__, __LINE__);
		return exception;
	}
	exception = SensorLight_Enable();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable SensorLight succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable SensorLight\n", __FILE__, __LINE__);
		return exception;
	}
	exception = SensorButton_one_Enable();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] enable SensorButton_one succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to enable SensorButton_one\n", __FILE__, __LINE__);
		return exception;
	}
	exception = initGlobalVariables_application();
	if(exception == NO_EXCEPTION)
	{
		printf("[INFO, %s:%d] do initGlobalVariables_application succeeded\n", __FILE__, __LINE__);
	}
	else
	{
		printf("[ERROR, %s:%d] failed to do initGlobalVariables_application\n", __FILE__, __LINE__);
		return exception;
	}
	return NO_EXCEPTION;
}

