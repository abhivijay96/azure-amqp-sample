cmake_minimum_required(VERSION 2.8.11)

set (CMAKE_C_FLAGS "--std=c99 ${CMAKE_C_FLAGS}")

set(AZUREIOT_INC_FOLDER ".." "/usr/include/azureiot" "/usr/include/azureiot/inc")

include_directories(${AZUREIOT_INC_FOLDER})

set(application_c_files
	./main.c
)

set(application_h_files
	 ./models.h)
	    
add_executable(app ${application_c_files} ${application_h_files})

target_link_libraries(app
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
