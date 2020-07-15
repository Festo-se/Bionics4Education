
# Installation Guide Bionic-Kit

In this guide we provide you with instruction on how to write and deploy code on the Bionics-Kit. We provide guides for Ubuntu Linux and Windows 10.

# Ubuntu

This guide is tested on Ubuntu 16.04. It should work with subsequent versions.

### Arduino IDE

To develop code for the Bionic-Kit the Arduino IDE is required.

1. The current version can be retrieved [here](https://www.arduino.cc/en/Main/Software).

2. Extract the archive to a location of your choice, for example in your /home folder.

3. Navigate to the extracted folder and grant the installer execution rights:

        sudo chmod +x install.sh

4. Now execute the installer using

        ./install.sh

To start the Arduino IDE run the binary inside the extracted Arduino folder using the terminal:

    ./arduino

In case you encounter an error, visit the [Arduino Troubleshooting Page](https://forum.arduino.cc/index.php#c2)

### Additional Packages

To compile the source code of the Bionic-Kit, additional libraries need to be installed.

#### Espressif ESP32

**The Bionic-Kit is based on the ESP32 SoC from Espressif. To use the ESP32 we first install the asccording Arduino Core module. Follow the instructions on the official Espressif Arduino Github Repository [here](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/debian_ubuntu.md).**

#### Asynchron web server for ESP32

1. For the purpose of displaying the control website of the Bionic-Kit a special web server for the ESP32 is needed. Therefore run:

        cd ~/Arduino/libraries

2. Then clone the repository of the web server to the present directory:

        git clone https://github.com/me-no-dev/ESPAsyncWebServer.git AsyncWebserver

3. The web server needs an additional package. Therefore stay in the libraries folder and clone the AsyncTCP repository as well:

        git clone https://github.com/me-no-dev/AsyncTCP.git AsyncTCP

4. A special branch of the AsyncTCP has to be used, because of the current development status of the AsyncWebServer. For this, enter the directory and checkout the idf-update branch with:

        cd AsyncTCP

        git checkout idf-update

This extra step is necessary for the Asyncwebserver Version dated 26.09.2018. In future releases this step might not be necessary.

#### ESP32 Servo Library

The last library which is needed to get the Bionic-Kit running is the ESP32Servo library.

1. For this go back to the libraries folder and clone the following repository:

        cd ~/Arduino/libraries

        git clone https://github.com/jkb-git/ESP32Servo.git ESP32Servo

#### 4. Sketch Data Upload Plugin

To load the website to the internal file system of the ESP32 Chip a special upload tool is needed.

1. For this purpose go to <https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/> and download the ZIP file of the sketch data upload plugin.
2. Then navigate to the Arduino folder and create a folder named "tools"  if it doesn't exist yet.

        cd ~/Arduino
    
        mkdir tools

3. Unpack the previous downloaded ZIP archive into tools directory (the path will look like `<home_dir>/Arduino/tools/ESP32FS/tool/esp32fs.jar`).
4. Then restart the Arduino IDE if its open.

# Windows 10

This installation guide is tested on Windows 10.

### Arduino IDE

For the usage of the Bionic-Kit the Arduino IDE is needed. Install it from the [Microsoft Store](https://www.microsoft.com/de-de/p/arduino-ide/9nblggh4rsd8?ocid=badge&rtc=1&activetab=pivot:overviewtab).
You can also download the latest version from [here](https://www.arduino.cc/en/Main/Software).

### Additional Packages

To compile the source code of the Bionic-Kit, additional libraries are needed.

* For the additional Packages next to the Esperessif ESP32 Package you can click on the github link, click on `Clone or download` and then on `Download ZIP`.  

* Then open the Project-Sketch (the `festo_bionic_kit` file) and inside the Ardunio IDE select `Sketch > Include Library > Add ZIP Library`.  

* In the open file dialog select downloaded .zip-file

#### Espressif ESP32

**The Bionic-Kit is based on the ESP32 SoC from Espressif, therefore the Arduino Core for the SoC is mandatory. To install all needed files follow the instructions on the official Espressif Arduino GIT [here](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/windows.md).**

Step-by-step:

1. Clone <https://github.com/espressif/arduino-esp32.git> to `[ARDUINO_SKETCHBOOK_DIR]/hardware/espressif/esp32`. Your `[ARDUINO_SKETCHBOOK_DIR]` is usually located at `C:/Users/[YOUR_USER_NAME]/Documents/Arduino`

2. Open a `Git Bash` session in `[ARDUINO_SKETCHBOOK_DIR]/hardware/espressif/esp32` and run

        git submodule update --init --recursive

3. Navigate to `[ARDUINO_SKETCHBOOK_DIR]/hardware/espressif/esp32/tools` and run the `get.exe`. This might take up to an hour. Make sure your PC doesn't go to standby or shuts down.

4. Open the Arduino IDE. Under `Tools > Board` you should see your ESP32 after connecting it.

#### Asynchron Web server for ESP32

For the purpose of displaying the control website of the Bionic-Kit a special web server for the ESP32 is needed.

Clone the following Libraries and add them to the Arduino IDE:

* <https://github.com/me-no-dev/ESPAsyncWebServer.git>
* <https://github.com/me-no-dev/ESPAsyncWebServer.git>
* <https://github.com/me-no-dev/AsyncTCP.git>

#### ESP32 Servo Library

The last library which is needed to get the Bionic-Kit running is the ESP32Servo library.

Clone the following Libraries and add them to the Arduino IDE:

* <https://github.com/jkb-git/ESP32Servo.git>

#### Sketch Data Upload Plugin

To load the website to the internal file system of the ESP32 Chip a special upload tool is needed.

1. Go to <https://github.com/me-no-dev/arduino-esp32fs-plugin/releases> and download the ZIP file of the sketch data upload plugin.
2. Navigate to the Arduino folder and create a folder named ```tools```  if it doesn't exist yet.
3. Unpack the previous downloaded ZIP archive into tools directory (the path will look like <home_dir>/Arduino/tools/ESP32FS/tool/esp32fs.jar).
4. Restart the Arduino IDE

If the `Tools -> ESP32 Sketch Data Upload` fails due to the following error `SPIFFS Error: esptool not found` please try the follwing:

* Locate the file `esptool.exe` at `[ARDUINO_SKETCHBOOK_DIR]\hardware\espressif\esp32\tools\esptool\esptool.exe`
* Copy it to the parent folder `[ARDUINO_SKETCHBOOK_DIR]\hardware\espressif\esp32\tools\`
* Restart the Arduino IDE

# Compiling the Source Code

1. Download or clone the Bionic-Kit source code
2. Save it to a location of your choice.
3. Open the *.ino file with the Arduino IDE
4. Connect the Bionic-Kit to the PC with an Micro-USB cable
5. In the Arduino IDE select ```Tools -> Board: -> ESP32 Dev Module```

    <img src="img/screenshot_arduino_board.png" alt="arduino port" width="900"/>

6. Make sure that the right port is selected. For this select ```Tools -> Port```. If you use Windows the Port is named ```COM X```, if you use Ubuntu your serial port is called ```/dev/ttyUSBX```

    <img src="img/screenshot_arduino_port.png" alt="arduino port" width="900"/>

7. Click on the ```upload``` button (Arrow) on the top left corner of the Arduino IDE to compile the code and upload it to the Bionic-Kit. This may take a while. 
8. The last step is to upload the files for the Bionic-Kit control website. For this click on ```Tools -> ESP32 Sketch Data Upload```
9. Now reset the ESP32 by pressing down the reset button on the PCB

# Connection test  

1. Connect the Bionic-Kit to the PC with a USB cable
2. Open the ```Serial Monitor``` of the Arduino IDE (magnifying glass symbol in the top right corner)
3. Now reset the ESP32 by pressing down the reset button. The console output will show:

    <img src="img/screenshot_serial_monitor.png" alt="website" width="900"/>

4. Open your wifi settings menu of your PC and search for the shown ```ẀifiSSID``` for example "b4e_84_0D_8E_35_5A_EC"

    <img src="img/screenshot_wifi_crop.png" alt="website" width="300"/>

5. Connect to b4e* wifi network with password ```education```
6. Once connected, open your web browser and open ```http://192.168.4.1```

    <img src="img/b4e.png" alt="website" width="1400"/>

7. If the batteries are attached on the Bionic-Kit and the switch is turned on, you should now be able to control the servos using the Bionics-Kit website.

8. Where to go from here

## Useful development tools

### EspExceptionDecoder

To decode the ESP32 stacktraces you can use the EspExceptionDecoder <https://github.com/me-no-dev/EspExceptionDecoder>.
For installation instructions follow the README in the repository.

### More on the ESP32 SoC

If you are interested in more details regarding the ESP32 for Arduino explore the [official GIT repository](https://github.com/espressif/arduino-esp32) .
