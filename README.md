# <p align = "center"><code><strong>Heart-Unhurt Project</strong></code></p>

<p align = "center"><strong> ---------------------------------------------------------------------</strong></p>

<div align = "justify">This software has a patient mode and a meditation mode. The patient mode tracks the ECG(electrocardiogram) of the user, and displays the ECG graph. The meditation instructs a 4-7-8 breathing pattern through vibration for a selected duration, and also provides a QR code for meditation music.</div>

<t></t> 

**`Requirements:`**

<div align = "justify">A M5Stack Core 2 is required to run the program. For the patient mode, ECG electrodes are needed to measure the user’s ECG. The ECG data is then saved into a SD card, which is read by the M5Stack Core 2 to display the ECG graph. For the meditation mode, no additional hardware is required, but it is recommended to have a smartphone to play music through the QR code.</div>

<t></t> 

**`Installation:`**

For softwares, an Arduino IDE (C++) is needed to run the program. On the Arduino, the following libraries should be installed:
  - M5Core2.h
  - String.h
  - SPI.h
  - SD.h
Refer to the following to link for additional information regarding the installation of M5Stack Core 2:
https://docs.m5stack.com/en/core/core2

<t></t> 

**`Usage notes:`**
<div align = "justify">After collecting and downloading all the required hardwares and softwares, connect the M5Stack Core 2 to your device with USB and run the code on the Arduino IDE. When the code is finished uploading, use the buttons to select between the patient mode and load data from patient mode. If the patient mode is selected, connect the ECG electrodes to the user’s left arm, right arm, and chest. The data will be read into a SD card.</div>

<t></t> 

<div align = "justify">The user returns to the main menu screen by pressing the A button. The user then uses the buttons to navigate from the patient mode to the show existing data mode. There, a graph of the patient’s ECG will be displayed on the M5Stack. The green parts of the graph shows when the patient’s heart is normal, otherwise the graph will turn red.</div>

<t></t> 
<div align = "justify">If the meditation mode is selected, choose the desired duration and scan the QR code from the screen to play meditation music. After 15 seconds, the device starts vibrating to instruct a 4-7-8 breathing pattern, which involves inhaling for 4 seconds, holding the breath for 7 seconds, and exhaling for 8 seconds. The user can choose to repeat the meditation after the duration. The QR code for the music can be changed by putting a new link inside the function Meditator().</div>

<t></t> 
<div align = "justify">Aside from the patient and meditation mode, the user also has the option to adjust the brightness of the screen by selecting settings from the main menu.</div>

<t></t>    
**`Challenges we have encountered:`**
<div align = "justify">Our initial plan was to play the meditation music directly from the M5Stack Core 2 through an SD card. However, we could not play MP3 music through a SD card even after trying for a long time, so we decided to display a QR code instead. Moreover, we also had trouble with reading data from the ECG electrodes as the item we purchased was for single-use. Hence, the accuracy of data may have decreased over time.</div> 

<t></t>
<div align = "justify">Hence, if we were to do the project again, we would start researching about playing music earlier, as it is an important feature for the meditation mode. We would also purchase a pulse oximeter for M5Stack Core 2, as the device is more convenient and is not for single use.</div>










