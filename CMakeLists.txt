cmake_minimum_required(VERSION 2.8.11)

set (CMAKE_C_FLAGS "--std=c99 ${CMAKE_C_FLAGS}")

set(AZUREIOT_INC_FOLDER ".." "/usr/include/azureiot" "/usr/include/azureiot/inc")

include_directories(${AZUREIOT_INC_FOLDER})

set(sample_application_c_files
	./sample.c
	./main.c
)

set(sample_application_h_files
	 ./sample.h)
	    
add_executable(sample_app ${sample_application_c_files} ${sample_application_h_files})

target_link_libraries(sample_app
		    serializer
		    iothub_client
		    iothub_client_amqp_transport
		    iothub_client_amqp_ws_transport
		    uamqp
		    aziotsharedutil
		    pthread
		    curl
		    ssl
		    crypto
		    m
		    uuid
		    prov_auth_client
		    hsm_security_client
		    uhttp
		    parson
		    )
