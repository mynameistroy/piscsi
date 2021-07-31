EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
L Memory_EEPROM:24LC256 U?
U 1 1 5FE1F118
P 4000 2600
AR Path="/5FE1F118" Ref="U?"  Part="1" 
AR Path="/5FE03785/5FE1F118" Ref="U1"  Part="1" 
F 0 "U1" H 3900 2900 50  0000 C CNN
F 1 "24LC256" H 4200 2850 50  0000 C CNN
F 2 "Package_SO:SOIC-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.3mm" H 4000 2600 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/21203m.pdf" H 4000 2600 50  0001 C CNN
F 4 "C6482" H 4000 2600 50  0001 C CNN "LCSC"
	1    4000 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE1F11E
P 4000 2900
AR Path="/5FE1F11E" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE1F11E" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 4000 2650 50  0001 C CNN
F 1 "GND" V 4000 2700 50  0000 C CNN
F 2 "" H 4000 2900 50  0001 C CNN
F 3 "" H 4000 2900 50  0001 C CNN
	1    4000 2900
	1    0    0    -1  
$EndComp
Text GLabel 4700 2500 2    50   BiDi ~ 0
PI_SDA
Text GLabel 4700 2600 2    50   BiDi ~ 0
PI_SCL
$Comp
L Device:R_Small R?
U 1 1 5FE1F127
P 2900 2400
AR Path="/5FE1F127" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FE1F127" Ref="R59"  Part="1" 
F 0 "R59" V 3000 2350 50  0000 L CNN
F 1 "10k" V 2950 2500 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 2900 2400 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 2900 2400 50  0001 C CNN
F 4 "C25744" H 2900 2400 50  0001 C CNN "LCSC"
	1    2900 2400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5FE1F12E
P 2900 3050
AR Path="/5FE1F12E" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FE1F12E" Ref="R60"  Part="1" 
F 0 "R60" V 2950 3000 50  0000 L CNN
F 1 "10k" V 2800 3000 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 2900 3050 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 2900 3050 50  0001 C CNN
F 4 "C25744" H 2900 3050 50  0001 C CNN "LCSC"
	1    2900 3050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5FE1F135
P 2900 3700
AR Path="/5FE1F135" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FE1F135" Ref="R61"  Part="1" 
F 0 "R61" V 2950 3650 50  0000 L CNN
F 1 "10k" V 2800 3650 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 2900 3700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 2900 3700 50  0001 C CNN
F 4 "C25744" H 2900 3700 50  0001 C CNN "LCSC"
	1    2900 3700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5FE1F13C
P 4600 3050
AR Path="/5FE1F13C" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FE1F13C" Ref="R62"  Part="1" 
F 0 "R62" V 4500 3000 50  0000 L CNN
F 1 "10k" V 4550 2850 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 4600 3050 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 4600 3050 50  0001 C CNN
F 4 "C25744" H 4600 3050 50  0001 C CNN "LCSC"
	1    4600 3050
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE1F148
P 5300 2800
AR Path="/5FE1F148" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE1F148" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 5300 2650 50  0001 C CNN
F 1 "+3V3" H 5150 2900 50  0000 C CNN
F 2 "" H 5300 2800 50  0001 C CNN
F 3 "" H 5300 2800 50  0001 C CNN
	1    5300 2800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE1F14E
P 2400 3950
AR Path="/5FE1F14E" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE1F14E" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 2400 3700 50  0001 C CNN
F 1 "GND" V 2400 3750 50  0000 C CNN
F 2 "" H 2400 3950 50  0001 C CNN
F 3 "" H 2400 3950 50  0001 C CNN
	1    2400 3950
	0    1    1    0   
$EndComp
$Comp
L Jumper:Jumper_3_Bridged12 JP?
U 1 1 5FE1F161
P 2400 2400
AR Path="/5FE1F161" Ref="JP?"  Part="1" 
AR Path="/5FE03785/5FE1F161" Ref="JP1"  Part="1" 
F 0 "JP1" V 2446 2467 50  0000 L CNN
F 1 "Jumper_3_Bridged12" V 2355 2467 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged2Bar12_Pad1.0x1.5mm" H 2400 2400 50  0001 C CNN
F 3 "~" H 2400 2400 50  0001 C CNN
	1    2400 2400
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:Jumper_3_Bridged12 JP?
U 1 1 5FE1F167
P 2400 3050
AR Path="/5FE1F167" Ref="JP?"  Part="1" 
AR Path="/5FE03785/5FE1F167" Ref="JP2"  Part="1" 
F 0 "JP2" V 2446 3117 50  0000 L CNN
F 1 "Jumper_3_Bridged12" V 2355 3117 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged2Bar12_Pad1.0x1.5mm" H 2400 3050 50  0001 C CNN
F 3 "~" H 2400 3050 50  0001 C CNN
	1    2400 3050
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:Jumper_3_Bridged12 JP?
U 1 1 5FE1F16D
P 2400 3700
AR Path="/5FE1F16D" Ref="JP?"  Part="1" 
AR Path="/5FE03785/5FE1F16D" Ref="JP3"  Part="1" 
F 0 "JP3" V 2446 3767 50  0000 L CNN
F 1 "Jumper_3_Bridged12" V 2355 3767 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged2Bar12_Pad1.0x1.5mm" H 2400 3700 50  0001 C CNN
F 3 "~" H 2400 3700 50  0001 C CNN
	1    2400 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE1F173
P 2400 3300
AR Path="/5FE1F173" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE1F173" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 2400 3050 50  0001 C CNN
F 1 "GND" V 2400 3100 50  0000 C CNN
F 2 "" H 2400 3300 50  0001 C CNN
F 3 "" H 2400 3300 50  0001 C CNN
	1    2400 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE1F179
P 2400 2650
AR Path="/5FE1F179" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE1F179" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 2400 2400 50  0001 C CNN
F 1 "GND" V 2400 2450 50  0000 C CNN
F 2 "" H 2400 2650 50  0001 C CNN
F 3 "" H 2400 2650 50  0001 C CNN
	1    2400 2650
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE385DA
P 2400 3450
AR Path="/5FE385DA" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE385DA" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 2400 3300 50  0001 C CNN
F 1 "+3V3" V 2400 3650 50  0000 C CNN
F 2 "" H 2400 3450 50  0001 C CNN
F 3 "" H 2400 3450 50  0001 C CNN
	1    2400 3450
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE385E0
P 2400 2800
AR Path="/5FE385E0" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE385E0" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 2400 2650 50  0001 C CNN
F 1 "+3V3" V 2400 3000 50  0000 C CNN
F 2 "" H 2400 2800 50  0001 C CNN
F 3 "" H 2400 2800 50  0001 C CNN
	1    2400 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 2600 4650 2600
Wire Wire Line
	4400 2500 4500 2500
$Comp
L power:GND #PWR?
U 1 1 5FE7346C
P 5300 3300
AR Path="/5FE7346C" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE7346C" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 5300 3050 50  0001 C CNN
F 1 "GND" V 5300 3100 50  0000 C CNN
F 2 "" H 5300 3300 50  0001 C CNN
F 3 "" H 5300 3300 50  0001 C CNN
	1    5300 3300
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE73A17
P 4000 2300
AR Path="/5FE73A17" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE73A17" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 4000 2150 50  0001 C CNN
F 1 "+3V3" H 3850 2400 50  0000 C CNN
F 2 "" H 4000 2300 50  0001 C CNN
F 3 "" H 4000 2300 50  0001 C CNN
	1    4000 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE78C02
P 2400 2150
AR Path="/5FE78C02" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FE78C02" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 2400 2000 50  0001 C CNN
F 1 "+3V3" V 2400 2350 50  0000 C CNN
F 2 "" H 2400 2150 50  0001 C CNN
F 3 "" H 2400 2150 50  0001 C CNN
	1    2400 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2550 3700 2800 3700
Wire Wire Line
	3000 3700 3600 3700
Wire Wire Line
	3600 3700 3600 2700
Wire Wire Line
	2550 3050 2800 3050
Wire Wire Line
	3350 3050 3350 2600
Wire Wire Line
	3350 2600 3600 2600
Wire Wire Line
	3600 2500 3350 2500
Wire Wire Line
	3350 2500 3350 2400
Wire Wire Line
	3350 2400 3000 2400
Wire Wire Line
	2800 2400 2550 2400
Wire Wire Line
	3000 3050 3350 3050
Text Notes 4550 4000 2    50   ~ 0
HAT Serial EEPROM
Wire Notes Line
	6300 4150 1350 4150
Wire Notes Line
	1350 4150 1350 1900
Wire Notes Line
	1350 1900 6300 1900
Wire Notes Line
	6300 1900 6300 4150
$Comp
L Jumper:Jumper_3_Bridged12 JP?
U 1 1 5FE882AF
P 5300 3050
AR Path="/5FE882AF" Ref="JP?"  Part="1" 
AR Path="/5FE03785/5FE882AF" Ref="JP4"  Part="1" 
F 0 "JP4" V 5346 3117 50  0000 L CNN
F 1 "Jumper_3_Bridged12" V 5255 3117 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged2Bar12_Pad1.0x1.5mm" H 5300 3050 50  0001 C CNN
F 3 "~" H 5300 3050 50  0001 C CNN
	1    5300 3050
	0    1    -1   0   
$EndComp
Wire Wire Line
	4400 2700 4500 2700
Wire Wire Line
	4700 3050 5150 3050
Wire Wire Line
	4500 2700 4500 3050
$Comp
L power:+3V3 #PWR?
U 1 1 5FEEFA21
P 4650 2050
AR Path="/5FEEFA21" Ref="#PWR?"  Part="1" 
AR Path="/5FE03785/5FEEFA21" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 4650 1900 50  0001 C CNN
F 1 "+3V3" H 4500 2150 50  0000 C CNN
F 2 "" H 4650 2050 50  0001 C CNN
F 3 "" H 4650 2050 50  0001 C CNN
	1    4650 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5FEF0453
P 4500 2250
AR Path="/5FEF0453" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FEF0453" Ref="R63"  Part="1" 
F 0 "R63" V 4400 2200 50  0000 L CNN
F 1 "4.7k" V 4300 2200 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 4500 2250 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 4500 2250 50  0001 C CNN
F 4 "C25900" H 4500 2250 50  0001 C CNN "LCSC"
	1    4500 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5FEF0C20
P 4650 2250
AR Path="/5FEF0C20" Ref="R?"  Part="1" 
AR Path="/5FE03785/5FEF0C20" Ref="R64"  Part="1" 
F 0 "R64" V 4750 2200 50  0000 L CNN
F 1 "4.7k" V 4850 2200 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 4650 2250 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Uniroyal-Elec-0402WGF1002TCE_C25744.pdf" H 4650 2250 50  0001 C CNN
F 4 "C25900" H 4650 2250 50  0001 C CNN "LCSC"
	1    4650 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2050 4500 2050
Wire Wire Line
	4500 2050 4500 2150
Wire Wire Line
	4650 2050 4650 2150
Connection ~ 4650 2050
Wire Wire Line
	4650 2350 4650 2600
Connection ~ 4650 2600
Wire Wire Line
	4650 2600 4400 2600
Wire Wire Line
	4500 2350 4500 2500
Connection ~ 4500 2500
Wire Wire Line
	4500 2500 4700 2500
$EndSCHEMATC
