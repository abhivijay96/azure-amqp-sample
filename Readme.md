
## Setting up environment on Ubuntu 18.04 (arm64v8/ubuntu or x86)

##### Install cmake tools

    ```Shell
    apt-get install cmake build-essential
    ```

##### Add azure-iot-sdk-c-dev package to the machine
    
    ```Shell
    apt-get update
    apt-get install -y software-properties-common
    add-apt-repository ppa:aziotsdklinux/ppa-azureiot
    apt-get update
    apt-get install -y azure-iot-sdk-c-dev
    ```

## Setting up CMake directories
    
    ```Shell
    mkdir cmake
    cd cmake
    cmake ..
    ```

## Building the application

    ```Shell
    cd cmake
    make
    ```

## Running the application

    ```Shell
    cd cmake
    ./app
    ```

### Miscellaneous

#### IoT Hub Message format 

{"Name" : "TurnFanOn", "Parameters" : {}}

Where "Name" is one of the Actions specified in the serializer
https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-device-sdk-c-serializer#message-handling

#### Serialization documentation

https://github.com/Azure/azure-iot-sdk-c/blob/master/serializer/devdoc/serializer_apis.md