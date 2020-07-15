EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A?
U 1 1 5F0AD319
P 4050 3700
F 0 "A?" H 4100 4581 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 4100 4490 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 4325 2950 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 4150 3400 50  0001 C CNN
	1    4050 3700
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-S2-WROVER-I U?
U 1 1 5F0B0308
P 2150 3600
F 0 "U?" H 2150 4981 50  0000 C CNN
F 1 "ESP32-S2-WROVER-I" H 2150 4890 50  0000 C CNN
F 2 "RF_Module:ESP32-S2-WROVER" H 2900 2450 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-s2-wroom_esp32-s2-wroom-i_datasheet_en.pdf" H 1850 2800 50  0001 C CNN
	1    2150 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F0B2C0D
P 3800 2450
F 0 "#PWR?" H 3800 2200 50  0001 C CNN
F 1 "GND" H 3805 2277 50  0000 C CNN
F 2 "" H 3800 2450 50  0001 C CNN
F 3 "" H 3800 2450 50  0001 C CNN
	1    3800 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5F0B42D1
P 3200 2600
F 0 "#PWR?" H 3200 2450 50  0001 C CNN
F 1 "+3V3" H 3215 2773 50  0000 C CNN
F 2 "" H 3200 2600 50  0001 C CNN
F 3 "" H 3200 2600 50  0001 C CNN
	1    3200 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F?
U 1 1 5F0B7621
P 850 1650
F 0 "F?" H 910 1696 50  0000 L CNN
F 1 "Fuse" H 910 1605 50  0000 L CNN
F 2 "" V 780 1650 50  0001 C CNN
F 3 "~" H 850 1650 50  0001 C CNN
	1    850  1650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
