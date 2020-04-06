// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

//
// IMPORTANT: Please read and understand serializer limitations and alternatives as
//            described ../../readme.md before beginning to use the serializer.
//

#include <stdlib.h>

#include <stdio.h>
#include <stdint.h>
#include "models.h"

/*String containing Hostname, Device Id & Device Key in the format:             */
/*  "HostName=<host_name>;DeviceId=<device_id>;SharedAccessKey=<device_key>"    */
static const char* connectionString = "replace this";

static char propText[1024];

EXECUTE_COMMAND_RESULT Download(DeviceCommands* command, char* downloadLink)
{
    (void)printf("Download link received is %s\n", downloadLink);
    return EXECUTE_COMMAND_SUCCESS;
}

void simplesample_amqp_run(void)
{
    if (platform_init() != 0)
    {
        printf("Failed to initialize the platform.\r\n");
    }
    else
    {
        if (serializer_init(NULL) != SERIALIZER_OK)
        {
            (void)printf("Failed on serializer_init\r\n");
        }
        else
        {
            /* Setup IoTHub client configuration */
            IOTHUB_CLIENT_HANDLE iotHubClientHandle = IoTHubClient_CreateFromConnectionString(connectionString, AMQP_Protocol);
            srand((unsigned int)time(NULL));
            int avgWindSpeed = 10;
            float minTemperature = 20.0;
            float minHumidity = 60.0;

            // Turn on Log
            bool trace = true;
            (void)IoTHubClient_SetOption(iotHubClientHandle, "logtrace", &trace);

            if (iotHubClientHandle == NULL)
            {
                (void)printf("Failed on IoTHubClient_Create\r\n");
            }
            else
            {
#ifdef SET_TRUSTED_CERT_IN_SAMPLES
                // For mbed add the certificate information
                if (IoTHubClient_SetOption(iotHubClientHandle, "TrustedCerts", certificates) != IOTHUB_CLIENT_OK)
                {
                    (void)printf("failure to set option \"TrustedCerts\"\r\n");
                }
#endif // SET_TRUSTED_CERT_IN_SAMPLES
                Log* logStruct = CREATE_MODEL_INSTANCE(BINE, Log);
                DeviceCommands* downloadStruct = CREATE_MODEL_INSTANCE(BINE, DeviceCommands);
                if (logStruct == NULL)
                {
                    (void)printf("Failed on CREATE_MODEL_INSTANCE\r\n");
                }
                else
                {
                    unsigned char* destination;
                    size_t destinationSize;

                    if (IoTHubClient_SetMessageCallback(iotHubClientHandle, IoTHubMessage, downloadStruct) != IOTHUB_CLIENT_OK)
                    {
                        printf("unable to IoTHubClient_SetMessageCallback for download struct\r\n");
                    }
                    else
                    {
                        logStruct->time = 1586185047275;
                        logStruct->level = 4;
                        logStruct->message = "Hello, this is from hub x";

                        if (SERIALIZE(&destination, &destinationSize, logStruct->time, logStruct->level, logStruct->message) != CODEFIRST_OK)
                        {
                            (void)printf("Failed to serialize\r\n");
                        }
                        else
                        {
                            sendLogMessage(iotHubClientHandle, destination, destinationSize, logStruct);
                        }

                        /* wait for commands */
                        (void)getchar();
                    }
                    DESTROY_MODEL_INSTANCE(logStruct);
                    DESTROY_MODEL_INSTANCE(downloadStruct);
                }
                IoTHubClient_Destroy(iotHubClientHandle);
            }
            serializer_deinit();
        }
        platform_deinit();
    }
}

int main()
{
	simplesample_amqp_run();
	return 1;
}
