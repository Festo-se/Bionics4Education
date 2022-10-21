# Introduction in how to use the Arduino portable version with the Bionic Flower

This document explains how to install a portable version of the Arduino Software (IDE). This portable version contains all the files and directories necessary to work with the Bionic Flower. Thus, it allows you to start right away with programming the Bionic Flower without any extra library downloads/installations or delays.
## Download 
Go to the [Bionics4Education](https://www.bionics4education.com/startseite/support) website and download the compressed (.zip) file.
<br>![Download in website](../img/SC_Download_B4E_WebSite_LVNZ.png)

## Unzip 
Once the download is completed, you will find the file in zip format in the download folder of your computer.
<br>![Download folder](../img/SC_Download_Folder_LVNZ.png)
<br>You need to unzip it to access the file, for that right click on the mouse on the computer and select "*Extract All...*".
<br><img src="../img/SC_Extrac_LVNZ.png" alt="Unzip" width="800"/> <br>
<br>Now a window opens, you can now select the location of the file in your documents and extract. 
<br>![Chosing folder](../img/SC_Docuements_LVNZ.png)

## Start with Arduino IDE 
Now that everything is installed, you need to run the Arduino software. Go to the previous folder and execute the arduino.exe file. 
<br>![Arduino execution ](../img/SC_Arduino_execution-LVNZ.png)
<br>A window opens, this is the user interface of the Arduino IDE. 
<br>![Arduino layout ](../img/Arduino_Layout.PNG)

## Setup the Arduino IDE environement for the Bionic Flower
<br>To access all the functionality of the Arduino portable version with your Bionic Flower, you need to setup your ESP32 board. For this go to *File*-> *Preferences*.
<br>![Preferences](../img/SC_Preferences_Menu_LVNZ.png)
<br>Once opened the preferences window you will check if the URL for the ESP32 board is here. If not, please add in the additional board manager URLs the following link :  https://dl.espressif.com/dl/package_esp32_index.json 
<br>![Preferences_windows](../img/SC_Preferences_Windows_LVNZ.png)
<br>Then, you need to add the library for the ESP32 board. Go to *Tools* -> *Board* -> *Board Manager*. 
<br>![Board_Manager](../img/Board_Manager.png)
<br>Write *esp32* on the top of the windows wich is opened and click on *Install*.  
<br>![Board_Manager](../img/SC_ESP32_installation_LVNZ.png)
<br>Wait somes minutes. The installation is done when the *Installed* indication is displayed.You can close the window. 
<br>![Board_Manager](../img/SC_esp32_installed_LVNZ.png)

## ESP32 module connection 
You have to connect the ESP32 module to your computer via a USB port. If your computer doesn't find the ESp32 module you have to install the driver manually. Therefore go to [SiliconLabs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers), navigate to *Downloads* and download *CP210x Universal Windows Driver*.
<br> First, select the right board, go to *Tools* -> *Board* -> *ESP32 Arduino* -> *ESP32 Dev Module*. 
<br>![ESP32](../img/SC_Select_Board-LVNZ.png)
<br> After that, you have to make sure that the right port is selected. For that select *Tools* -> *Port*.
<br>![Port](../img/Port.PNG)
<br>Now, you are ready to start your first code with the Bionic Flower ! 

## First test with the Bionic Flower
Some code have been created specifically for you to learn about the Bionic Flower. You can find them by selecting *File* -> *Sketchbook* -> *12.Bionic_Flower*.
<br>Let's start with the code to work with led LED : *color_sequence.ino*. 
<br>![Example LED](../img/color_sequence_exemple.PNG)
<br> A new window opens with the code for the LED. 
<br>![Example LED_code](../img/Color_sequence_code.PNG)
<br> After reading the code, you can implement the code, i.e. downloaded the code on the ESP32 module. For this you click on right arrow button. 
<br>![Upload button](../img/SC_Upload_Code-LVNZ.png)
<br>Make sure the download is finished with this message. 
<br>![Upload done](../img/upload_done.PNG)
<br> If everything went well the Bionic Flower changes color ! 
<br>
<br> You can use the same procedure to work with the other sample code of the Bionic Flower. 
* **LEDs**
    <br>-> *Color_sequence.ino* : This example teach you how to change the color of the LEDs and create a color sequence (red,blue,green).
 * **Motor**
    <br>-> *Motor_Open_Close.ino* : This example will teach you how to use the Bionic Flower motor. The motor allows to open and close the flower. 
 * **Touch sensor**
   <br> -> *Right_Left.ino* : This example will teach you how to use the touche sensor and display a message if a touch is detected.
   <br> -> *Open_close_flower.ino* : This example will teach you how to use the touch sensor to open or close the flower. For this you need to know how use the motor and the touch sensor. 
   <br> -> *Change_color.ino* : This example will teach you how to use the touch sennsor to change the color of the flower. For this you need to know how use the LEDs and the touch sensor.  
 * **Light sensor**
   <br> -> *Light_value.ino* : This example will teach you how to use the light sensor and display the luminosity value on the serial monitor.
   <br> -> *Day_Night_Color.ino* : This example will teach you how to use light sensor to change the flower's color. If it is the day, the flower lights yellow. If it is the night, the flower lights blue. 
 * **All components** 
 <br> -> *Light_Touch_LED_Motor.ino*: This example will teach you how to use 2 sensors with the I2C communication. If a right touch is detected the flower is opening. If a left touch is detected the flower is closing. In addition, if the luminosity is enough the flower is yellow, otherwise the flower is blue.





