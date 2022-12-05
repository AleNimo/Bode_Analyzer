/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341.h"
#include "AD9833.h"
#include "Touch.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

CRC_HandleTypeDef hcrc;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

//osThreadId defaultTaskHandle;
/* USER CODE BEGIN PV */
float freq[600];
/*float freq[600]={
		1,
		1.02329,
		1.04713,
		1.07152,
		1.09648,
		1.12202,
		1.14815,
		1.1749,
		1.20226,
		1.23027,
		1.25893,
		1.28825,
		1.31826,
		1.34896,
		1.38038,
		1.41254,
		1.44544,
		1.47911,
		1.51356,
		1.54882,
		1.58489,
		1.62181,
		1.65959,
		1.69824,
		1.7378,
		1.77828,
		1.8197,
		1.86209,
		1.90546,
		1.94984,
		1.99526,
		2.04174,
		2.0893,
		2.13796,
		2.18776,
		2.23872,
		2.29087,
		2.34423,
		2.39883,
		2.45471,
		2.51189,
		2.5704,
		2.63027,
		2.69153,
		2.75423,
		2.81838,
		2.88403,
		2.95121,
		3.01995,
		3.0903,
		3.16228,
		3.23594,
		3.31131,
		3.38844,
		3.46737,
		3.54813,
		3.63078,
		3.71535,
		3.80189,
		3.89045,
		3.98107,
		4.0738,
		4.16869,
		4.2658,
		4.36516,
		4.46684,
		4.57088,
		4.67735,
		4.7863,
		4.89779,
		5.01187,
		5.12861,
		5.24807,
		5.37032,
		5.49541,
		5.62341,
		5.7544,
		5.88844,
		6.0256,
		6.16595,
		6.30957,
		6.45654,
		6.60693,
		6.76083,
		6.91831,
		7.07946,
		7.24436,
		7.4131,
		7.58578,
		7.76247,
		7.94328,
		8.12831,
		8.31764,
		8.51138,
		8.70964,
		8.91251,
		9.12011,
		9.33254,
		9.54993,
		9.77237,
		10,
		10.2329,
		10.4713,
		10.7152,
		10.9648,
		11.2202,
		11.4815,
		11.749,
		12.0226,
		12.3027,
		12.5893,
		12.8825,
		13.1826,
		13.4896,
		13.8038,
		14.1254,
		14.4544,
		14.7911,
		15.1356,
		15.4882,
		15.8489,
		16.2181,
		16.5959,
		16.9824,
		17.378,
		17.7828,
		18.197,
		18.6209,
		19.0546,
		19.4984,
		19.9526,
		20.4174,
		20.893,
		21.3796,
		21.8776,
		22.3872,
		22.9087,
		23.4423,
		23.9883,
		24.5471,
		25.1189,
		25.704,
		26.3027,
		26.9153,
		27.5423,
		28.1838,
		28.8403,
		29.5121,
		30.1995,
		30.903,
		31.6228,
		32.3594,
		33.1131,
		33.8844,
		34.6737,
		35.4813,
		36.3078,
		37.1535,
		38.0189,
		38.9045,
		39.8107,
		40.738,
		41.6869,
		42.658,
		43.6516,
		44.6684,
		45.7088,
		46.7735,
		47.863,
		48.9779,
		50.1187,
		51.2861,
		52.4807,
		53.7032,
		54.9541,
		56.2341,
		57.544,
		58.8844,
		60.256,
		61.6595,
		63.0957,
		64.5654,
		66.0693,
		67.6083,
		69.1831,
		70.7946,
		72.4436,
		74.131,
		75.8578,
		77.6247,
		79.4328,
		81.2831,
		83.1764,
		85.1138,
		87.0964,
		89.1251,
		91.2011,
		93.3254,
		95.4993,
		97.7237,
		100,
		102.329,
		104.713,
		107.152,
		109.648,
		112.202,
		114.815,
		117.49,
		120.226,
		123.027,
		125.893,
		128.825,
		131.826,
		134.896,
		138.038,
		141.254,
		144.544,
		147.911,
		151.356,
		154.882,
		158.489,
		162.181,
		165.959,
		169.824,
		173.78,
		177.828,
		181.97,
		186.209,
		190.546,
		194.984,
		199.526,
		204.174,
		208.93,
		213.796,
		218.776,
		223.872,
		229.087,
		234.423,
		239.883,
		245.471,
		251.189,
		257.04,
		263.027,
		269.153,
		275.423,
		281.838,
		288.403,
		295.121,
		301.995,
		309.03,
		316.228,
		323.594,
		331.131,
		338.844,
		346.737,
		354.813,
		363.078,
		371.535,
		380.189,
		389.045,
		398.107,
		407.38,
		416.869,
		426.58,
		436.516,
		446.684,
		457.088,
		467.735,
		478.63,
		489.779,
		501.187,
		512.861,
		524.807,
		537.032,
		549.541,
		562.341,
		575.44,
		588.844,
		602.56,
		616.595,
		630.957,
		645.654,
		660.693,
		676.083,
		691.831,
		707.946,
		724.436,
		741.31,
		758.578,
		776.247,
		794.328,
		812.831,
		831.764,
		851.138,
		870.964,
		891.251,
		912.011,
		933.254,
		954.993,
		977.237,
		1000,
		1023.29,
		1047.13,
		1071.52,
		1096.48,
		1122.02,
		1148.15,
		1174.9,
		1202.26,
		1230.27,
		1258.93,
		1288.25,
		1318.26,
		1348.96,
		1380.38,
		1412.54,
		1445.44,
		1479.11,
		1513.56,
		1548.82,
		1584.89,
		1621.81,
		1659.59,
		1698.24,
		1737.8,
		1778.28,
		1819.7,
		1862.09,
		1905.46,
		1949.84,
		1995.26,
		2041.74,
		2089.3,
		2137.96,
		2187.76,
		2238.72,
		2290.87,
		2344.23,
		2398.83,
		2454.71,
		2511.89,
		2570.4,
		2630.27,
		2691.53,
		2754.23,
		2818.38,
		2884.03,
		2951.21,
		3019.95,
		3090.3,
		3162.28,
		3235.94,
		3311.31,
		3388.44,
		3467.37,
		3548.13,
		3630.78,
		3715.35,
		3801.89,
		3890.45,
		3981.07,
		4073.8,
		4168.69,
		4265.8,
		4365.16,
		4466.84,
		4570.88,
		4677.35,
		4786.3,
		4897.79,
		5011.87,
		5128.61,
		5248.07,
		5370.32,
		5495.41,
		5623.41,
		5754.4,
		5888.44,
		6025.6,
		6165.95,
		6309.57,
		6456.54,
		6606.93,
		6760.83,
		6918.31,
		7079.46,
		7244.36,
		7413.1,
		7585.78,
		7762.47,
		7943.28,
		8128.31,
		8317.64,
		8511.38,
		8709.64,
		8912.51,
		9120.11,
		9332.54,
		9549.93,
		9772.37,
		10000,
		10232.9,
		10471.3,
		10715.2,
		10964.8,
		11220.2,
		11481.5,
		11749,
		12022.6,
		12302.7,
		12589.3,
		12882.5,
		13182.6,
		13489.6,
		13803.8,
		14125.4,
		14454.4,
		14791.1,
		15135.6,
		15488.2,
		15848.9,
		16218.1,
		16595.9,
		16982.4,
		17378,
		17782.8,
		18197,
		18620.9,
		19054.6,
		19498.4,
		19952.6,
		20417.4,
		20893,
		21379.6,
		21877.6,
		22387.2,
		22908.7,
		23442.3,
		23988.3,
		24547.1,
		25118.9,
		25704,
		26302.7,
		26915.3,
		27542.3,
		28183.8,
		28840.3,
		29512.1,
		30199.5,
		30903,
		31622.8,
		32359.4,
		33113.1,
		33884.4,
		34673.7,
		35481.3,
		36307.8,
		37153.5,
		38018.9,
		38904.5,
		39810.7,
		40738,
		41686.9,
		42658,
		43651.6,
		44668.4,
		45708.8,
		46773.5,
		47863,
		48977.9,
		50118.7,
		51286.1,
		52480.7,
		53703.2,
		54954.1,
		56234.1,
		57544,
		58884.4,
		60256,
		61659.5,
		63095.7,
		64565.4,
		66069.3,
		67608.3,
		69183.1,
		70794.6,
		72443.6,
		74131,
		75857.8,
		77624.7,
		79432.8,
		81283.1,
		83176.4,
		85113.8,
		87096.4,
		89125.1,
		91201.1,
		93325.4,
		95499.3,
		97723.7,
		100000,
		102329,
		104713,
		107152,
		109648,
		112202,
		114815,
		117490,
		120226,
		123027,
		125893,
		128825,
		131826,
		134896,
		138038,
		141254,
		144544,
		147911,
		151356,
		154882,
		158489,
		162181,
		165959,
		169824,
		173780,
		177828,
		181970,
		186209,
		190546,
		194984,
		199526,
		204174,
		208930,
		213796,
		218776,
		223872,
		229087,
		234423,
		239883,
		245471,
		251189,
		257040,
		263027,
		269153,
		275423,
		281838,
		288403,
		295121,
		301995,
		309030,
		316228,
		323594,
		331131,
		338844,
		346737,
		354813,
		363078,
		371535,
		380189,
		389045,
		398107,
		407380,
		416869,
		426580,
		436516,
		446684,
		457088,
		467735,
		478630,
		489779,
		501187,
		512861,
		524807,
		537032,
		549541,
		562341,
		575440,
		588844,
		602560,
		616595,
		630957,
		645654,
		660693,
		676083,
		691831,
		707946,
		724436,
		741310,
		758578,
		776247,
		794328,
		812831,
		831764,
		851138,
		870964,
		891251,
		912011,
		933254,
		954993,
		977237,
		1000000};
*/
	float mag [600]=
	{
			-0.000394776,
			-0.000413381,
			-0.000432863,
			-0.000453263,
			-0.000474624,
			-0.000496991,
			-0.000520413,
			-0.000544939,
			-0.00057062,
			-0.000597512,
			-0.000625671,
			-0.000655157,
			-0.000686033,
			-0.000718363,
			-0.000752217,
			-0.000787667,
			-0.000824787,
			-0.000863656,
			-0.000904357,
			-0.000946976,
			-0.000991604,
			-0.00103833,
			-0.00108727,
			-0.00113851,
			-0.00119216,
			-0.00124834,
			-0.00130717,
			-0.00136877,
			-0.00143327,
			-0.00150081,
			-0.00157154,
			-0.0016456,
			-0.00172315,
			-0.00180435,
			-0.00188938,
			-0.00197841,
			-0.00207164,
			-0.00216927,
			-0.00227149,
			-0.00237853,
			-0.00249061,
			-0.00260797,
			-0.00273087,
			-0.00285955,
			-0.0029943,
			-0.00313539,
			-0.00328313,
			-0.00343784,
			-0.00359983,
			-0.00376945,
			-0.00394706,
			-0.00413304,
			-0.00432779,
			-0.0045317,
			-0.00474522,
			-0.0049688,
			-0.00520292,
			-0.00544805,
			-0.00570474,
			-0.00597352,
			-0.00625495,
			-0.00654964,
			-0.00685821,
			-0.00718131,
			-0.00751963,
			-0.00787388,
			-0.00824481,
			-0.00863321,
			-0.0090399,
			-0.00946573,
			-0.00991162,
			-0.0103785,
			-0.0108674,
			-0.0113792,
			-0.0119152,
			-0.0124764,
			-0.013064,
			-0.0136793,
			-0.0143235,
			-0.014998,
			-0.0157043,
			-0.0164438,
			-0.0172181,
			-0.0180289,
			-0.0188777,
			-0.0197665,
			-0.0206971,
			-0.0216715,
			-0.0226917,
			-0.0237599,
			-0.0248782,
			-0.0260492,
			-0.0272752,
			-0.0285588,
			-0.0299027,
			-0.0313098,
			-0.0327829,
			-0.0343253,
			-0.0359401,
			-0.0376307,
			-0.0394007,
			-0.0412538,
			-0.0431938,
			-0.0452249,
			-0.0473512,
			-0.0495773,
			-0.0519077,
			-0.0543474,
			-0.0569015,
			-0.0595752,
			-0.0623741,
			-0.0653042,
			-0.0683714,
			-0.0715821,
			-0.074943,
			-0.0784612,
			-0.0821438,
			-0.0859985,
			-0.0900333,
			-0.0942565,
			-0.0986768,
			-0.103303,
			-0.108146,
			-0.113214,
			-0.118518,
			-0.124069,
			-0.129878,
			-0.135958,
			-0.14232,
			-0.148978,
			-0.155944,
			-0.163234,
			-0.170862,
			-0.178842,
			-0.187193,
			-0.195929,
			-0.205069,
			-0.21463,
			-0.224633,
			-0.235096,
			-0.24604,
			-0.257488,
			-0.269461,
			-0.281983,
			-0.295078,
			-0.308772,
			-0.323091,
			-0.338063,
			-0.353717,
			-0.370083,
			-0.387191,
			-0.405074,
			-0.423765,
			-0.4433,
			-0.463715,
			-0.485048,
			-0.507337,
			-0.530623,
			-0.554949,
			-0.580359,
			-0.606896,
			-0.634609,
			-0.663546,
			-0.693758,
			-0.725295,
			-0.758213,
			-0.792566,
			-0.828413,
			-0.865811,
			-0.904823,
			-0.945511,
			-0.987939,
			-1.03218,
			-1.07829,
			-1.12635,
			-1.17642,
			-1.22859,
			-1.28293,
			-1.33952,
			-1.39843,
			-1.45974,
			-1.52355,
			-1.58993,
			-1.65897,
			-1.73075,
			-1.80537,
			-1.88292,
			-1.96348,
			-2.04714,
			-2.13401,
			-2.22417,
			-2.31771,
			-2.41474,
			-2.51533,
			-2.6196,
			-2.72762,
			-2.83951,
			-2.95533,
			-3.0752,
			-3.19919,
			-3.3274,
			-3.45991,
			-3.59681,
			-3.73818,
			-3.8841,
			-4.03466,
			-4.18991,
			-4.34994,
			-4.51481,
			-4.68459,
			-4.85933,
			-5.03909,
			-5.22392,
			-5.41387,
			-5.60898,
			-5.80929,
			-6.01482,
			-6.2256,
			-6.44166,
			-6.66301,
			-6.88965,
			-7.12159,
			-7.35884,
			-7.60137,
			-7.84919,
			-8.10226,
			-8.36058,
			-8.6241,
			-8.89279,
			-9.16662,
			-9.44553,
			-9.72949,
			-10.0184,
			-10.3123,
			-10.611,
			-10.9146,
			-11.2228,
			-11.5357,
			-11.8532,
			-12.1752,
			-12.5017,
			-12.8324,
			-13.1674,
			-13.5066,
			-13.8498,
			-14.197,
			-14.5481,
			-14.903,
			-15.2616,
			-15.6238,
			-15.9895,
			-16.3587,
			-16.7311,
			-17.1068,
			-17.4856,
			-17.8675,
			-18.2524,
			-18.6401,
			-19.0306,
			-19.4238,
			-19.8195,
			-20.2178,
			-20.6186,
			-21.0217,
			-21.427,
			-21.8346,
			-22.2443,
			-22.656,
			-23.0697,
			-23.4853,
			-23.9028,
			-24.322,
			-24.7429,
			-25.1654,
			-25.5895,
			-26.0152,
			-26.4422,
			-26.8707,
			-27.3006,
			-27.7317,
			-28.164,
			-28.5976,
			-29.0323,
			-29.4681,
			-29.905,
			-30.3428,
			-30.7817,
			-31.2214,
			-31.6621,
			-32.1036,
			-32.546,
			-32.9891,
			-33.433,
			-33.8776,
			-34.3229,
			-34.7689,
			-35.2155,
			-35.6627,
			-36.1105,
			-36.5588,
			-37.0077,
			-37.4571,
			-37.907,
			-38.3573,
			-38.8081,
			-39.2593,
			-39.711,
			-40.163,
			-40.6154,
			-41.0682,
			-41.5213,
			-41.9747,
			-42.4285,
			-42.8825,
			-43.3368,
			-43.7914,
			-44.2463,
			-44.7014,
			-45.1568,
			-45.6124,
			-46.0682,
			-46.5242,
			-46.9805,
			-47.4369,
			-47.8935,
			-48.3502,
			-48.8072,
			-49.2643,
			-49.7215,
			-50.1789,
			-50.6365,
			-51.0941,
			-51.5519,
			-52.0099,
			-52.4679,
			-52.9261,
			-53.3843,
			-53.8427,
			-54.3011,
			-54.7597,
			-55.2183,
			-55.677,
			-56.1358,
			-56.5947,
			-57.0536,
			-57.5126,
			-57.9717,
			-58.4309,
			-58.8901,
			-59.3494,
			-59.8087,
			-60.2681,
			-60.7275,
			-61.187,
			-61.6465,
			-62.1061,
			-62.5657,
			-63.0253,
			-63.485,
			-63.9448,
			-64.4045,
			-64.8643,
			-65.3242,
			-65.784,
			-66.2439,
			-66.7038,
			-67.1638,
			-67.6238,
			-68.0837,
			-68.5438,
			-69.0038,
			-69.4639,
			-69.924,
			-70.3841,
			-70.8442,
			-71.3043,
			-71.7645,
			-72.2247,
			-72.6848,
			-73.145,
			-73.6053,
			-74.0655,
			-74.5257,
			-74.986,
			-75.4463,
			-75.9065,
			-76.3668,
			-76.8271,
			-77.2874,
			-77.7478,
			-78.2081,
			-78.6684,
			-79.1288,
			-79.5891,
			-80.0495,
			-80.5098,
			-80.9702,
			-81.4306,
			-81.891,
			-82.3514,
			-82.8118,
			-83.2722,
			-83.7326,
			-84.193,
			-84.6534,
			-85.1138,
			-85.5743,
			-86.0347,
			-86.4951,
			-86.9556,
			-87.416,
			-87.8765,
			-88.3369,
			-88.7974,
			-89.2578,
			-89.7183,
			-90.1787,
			-90.6392,
			-91.0997,
			-91.5601,
			-92.0206,
			-92.4811,
			-92.9415,
			-93.402,
			-93.8625,
			-94.323,
			-94.7835,
			-95.2439,
			-95.7044,
			-96.1649,
			-96.6254,
			-97.0859,
			-97.5464,
			-98.0069,
			-98.4674,
			-98.9278,
			-99.3883,
			-99.8488,
			-100.309,
			-100.77,
			-101.23,
			-101.691,
			-102.151,
			-102.612,
			-103.072,
			-103.533,
			-103.993,
			-104.454,
			-104.914,
			-105.375,
			-105.835,
			-106.296,
			-106.756,
			-107.217,
			-107.677,
			-108.138,
			-108.598,
			-109.059,
			-109.519,
			-109.98,
			-110.44,
			-110.901,
			-111.361,
			-111.822,
			-112.282,
			-112.743,
			-113.203,
			-113.664,
			-114.125,
			-114.585,
			-115.046,
			-115.506,
			-115.967,
			-116.427,
			-116.888,
			-117.348,
			-117.809,
			-118.269,
			-118.73,
			-119.19,
			-119.651,
			-120.111,
			-120.572,
			-121.032,
			-121.493,
			-121.953,
			-122.414,
			-122.874,
			-123.335,
			-123.795,
			-124.256,
			-124.716,
			-125.177,
			-125.637,
			-126.098,
			-126.558,
			-127.019,
			-127.479,
			-127.94,
			-128.4,
			-128.861,
			-129.321,
			-129.782,
			-130.243,
			-130.703,
			-131.164,
			-131.624,
			-132.085,
			-132.545,
			-133.006,
			-133.466,
			-133.927,
			-134.387,
			-134.848,
			-135.308,
			-135.769,
			-136.229,
			-136.69,
			-137.15,
			-137.611,
			-138.071,
			-138.532,
			-138.992,
			-139.453,
			-139.913,
			-140.374,
			-140.834,
			-141.295,
			-141.755,
			-142.216,
			-142.676,
			-143.137,
			-143.597,
			-144.058,
			-144.519,
			-144.979,
			-145.44,
			-145.9,
			-146.361,
			-146.821,
			-147.282,
			-147.742,
			-148.203,
			-148.663,
			-149.124,
			-149.584,
			-150.045,
			-150.505,
			-150.966,
			-151.426,
			-151.887,
			-152.347,
			-152.808,
			-153.268,
			-153.729,
			-154.189,
			-154.65,
			-155.11,
			-155.571,
			-156.031,
			-156.492,
			-156.952,
			-157.413,
			-157.874,
			-158.334,
			-158.795,
			-159.255,
			-159.716,
			-160.176,
			-160.637,
			-161.097,
			-161.558,
			-162.018,
			-162.479,
			-162.939,
			-163.4,
			-163.86,
			-164.321,
			-164.781,
			-165.242,
			-165.702,
			-166.163,
			-166.623,
			-167.084,
			-167.544,
			-168.005,
			-168.465,
			-168.926,
			-169.386,
			-169.847,
			-170.307,
			-170.768,
			-171.229,
			-171.689,
			-172.15,
			-172.61,
			-173.071,
			-173.531,
			-173.992,
			-174.452
	};
	float phase[600]=
	{
			-0.0062831,
			-0.00642945,
			-0.00657921,
			-0.00673245,
			-0.00688927,
			-0.00704973,
			-0.00721394,
			-0.00738196,
			-0.00755391,
			-0.00772985,
			-0.0079099,
			-0.00809413,
			-0.00828266,
			-0.00847558,
			-0.00867299,
			-0.008875,
			-0.00908172,
			-0.00929324,
			-0.0095097,
			-0.00973119,
			-0.00995785,
			-0.0101898,
			-0.0104271,
			-0.01067,
			-0.0109185,
			-0.0111728,
			-0.011433,
			-0.0116993,
			-0.0119718,
			-0.0122506,
			-0.0125359,
			-0.0128279,
			-0.0131267,
			-0.0134324,
			-0.0137452,
			-0.0140654,
			-0.014393,
			-0.0147282,
			-0.0150712,
			-0.0154222,
			-0.0157813,
			-0.0161489,
			-0.016525,
			-0.0169098,
			-0.0173036,
			-0.0177066,
			-0.0181189,
			-0.0185409,
			-0.0189726,
			-0.0194145,
			-0.0198666,
			-0.0203292,
			-0.0208026,
			-0.021287,
			-0.0217827,
			-0.0222899,
			-0.0228089,
			-0.02334,
			-0.0238835,
			-0.0244396,
			-0.0250086,
			-0.0255909,
			-0.0261867,
			-0.0267964,
			-0.0274202,
			-0.0280586,
			-0.0287118,
			-0.0293802,
			-0.0300642,
			-0.030764,
			-0.0314801,
			-0.0322129,
			-0.0329627,
			-0.0337299,
			-0.034515,
			-0.0353183,
			-0.0361402,
			-0.0369813,
			-0.0378419,
			-0.0387224,
			-0.0396235,
			-0.0405454,
			-0.0414888,
			-0.042454,
			-0.0434417,
			-0.0444522,
			-0.0454863,
			-0.0465443,
			-0.0476268,
			-0.0487344,
			-0.0498677,
			-0.0510273,
			-0.0522138,
			-0.0534277,
			-0.0546697,
			-0.0559405,
			-0.0572407,
			-0.058571,
			-0.0599321,
			-0.0613246,
			-0.0627494,
			-0.064207,
			-0.0656983,
			-0.0672241,
			-0.0687851,
			-0.0703821,
			-0.0720159,
			-0.0736873,
			-0.0753973,
			-0.0771467,
			-0.0789363,
			-0.080767,
			-0.0826399,
			-0.0845557,
			-0.0865156,
			-0.0885204,
			-0.0905712,
			-0.0926689,
			-0.0948147,
			-0.0970096,
			-0.0992546,
			-0.101551,
			-0.103899,
			-0.106302,
			-0.108758,
			-0.111271,
			-0.113841,
			-0.116469,
			-0.119156,
			-0.121905,
			-0.124715,
			-0.127589,
			-0.130528,
			-0.133533,
			-0.136605,
			-0.139746,
			-0.142958,
			-0.146241,
			-0.149597,
			-0.153028,
			-0.156535,
			-0.16012,
			-0.163784,
			-0.167529,
			-0.171356,
			-0.175267,
			-0.179264,
			-0.183347,
			-0.18752,
			-0.191783,
			-0.196137,
			-0.200586,
			-0.205129,
			-0.20977,
			-0.214509,
			-0.219349,
			-0.22429,
			-0.229335,
			-0.234486,
			-0.239743,
			-0.245109,
			-0.250584,
			-0.256172,
			-0.261873,
			-0.267688,
			-0.27362,
			-0.27967,
			-0.285839,
			-0.292128,
			-0.29854,
			-0.305075,
			-0.311734,
			-0.318519,
			-0.32543,
			-0.33247,
			-0.339638,
			-0.346936,
			-0.354364,
			-0.361923,
			-0.369613,
			-0.377436,
			-0.38539,
			-0.393478,
			-0.401697,
			-0.41005,
			-0.418534,
			-0.42715,
			-0.435898,
			-0.444776,
			-0.453784,
			-0.46292,
			-0.472184,
			-0.481574,
			-0.491087,
			-0.500724,
			-0.51048,
			-0.520355,
			-0.530345,
			-0.540449,
			-0.550662,
			-0.560982,
			-0.571406,
			-0.58193,
			-0.59255,
			-0.603263,
			-0.614064,
			-0.624949,
			-0.635913,
			-0.646951,
			-0.65806,
			-0.669233,
			-0.680465,
			-0.691752,
			-0.703087,
			-0.714464,
			-0.725879,
			-0.737325,
			-0.748797,
			-0.760287,
			-0.771791,
			-0.783303,
			-0.794815,
			-0.806322,
			-0.817819,
			-0.829298,
			-0.840754,
			-0.852181,
			-0.863573,
			-0.874924,
			-0.886229,
			-0.897481,
			-0.908676,
			-0.919809,
			-0.930874,
			-0.941866,
			-0.95278,
			-0.963612,
			-0.974357,
			-0.985011,
			-0.995571,
			-1.00603,
			-1.01639,
			-1.02664,
			-1.03679,
			-1.04682,
			-1.05673,
			-1.06653,
			-1.07622,
			-1.08577,
			-1.09521,
			-1.10452,
			-1.1137,
			-1.12276,
			-1.13168,
			-1.14048,
			-1.14914,
			-1.15767,
			-1.16607,
			-1.17434,
			-1.18248,
			-1.19048,
			-1.19835,
			-1.20609,
			-1.2137,
			-1.22117,
			-1.22852,
			-1.23573,
			-1.24282,
			-1.24978,
			-1.25661,
			-1.26331,
			-1.26989,
			-1.27635,
			-1.28268,
			-1.28889,
			-1.29499,
			-1.30096,
			-1.30682,
			-1.31256,
			-1.31819,
			-1.32371,
			-1.32911,
			-1.33441,
			-1.3396,
			-1.34468,
			-1.34966,
			-1.35454,
			-1.35931,
			-1.36399,
			-1.36857,
			-1.37305,
			-1.37744,
			-1.38174,
			-1.38594,
			-1.39006,
			-1.39408,
			-1.39803,
			-1.40188,
			-1.40566,
			-1.40935,
			-1.41297,
			-1.4165,
			-1.41996,
			-1.42334,
			-1.42665,
			-1.42989,
			-1.43306,
			-1.43615,
			-1.43918,
			-1.44214,
			-1.44504,
			-1.44788,
			-1.45065,
			-1.45336,
			-1.45601,
			-1.4586,
			-1.46113,
			-1.46361,
			-1.46603,
			-1.4684,
			-1.47071,
			-1.47298,
			-1.47519,
			-1.47735,
			-1.47947,
			-1.48153,
			-1.48356,
			-1.48553,
			-1.48746,
			-1.48935,
			-1.4912,
			-1.493,
			-1.49477,
			-1.49649,
			-1.49818,
			-1.49982,
			-1.50143,
			-1.50301,
			-1.50455,
			-1.50605,
			-1.50752,
			-1.50896,
			-1.51036,
			-1.51173,
			-1.51307,
			-1.51439,
			-1.51567,
			-1.51692,
			-1.51814,
			-1.51934,
			-1.52051,
			-1.52165,
			-1.52277,
			-1.52386,
			-1.52493,
			-1.52597,
			-1.52699,
			-1.52799,
			-1.52896,
			-1.52991,
			-1.53084,
			-1.53175,
			-1.53264,
			-1.5335,
			-1.53435,
			-1.53518,
			-1.53599,
			-1.53678,
			-1.53756,
			-1.53831,
			-1.53905,
			-1.53977,
			-1.54048,
			-1.54117,
			-1.54184,
			-1.5425,
			-1.54315,
			-1.54377,
			-1.54439,
			-1.54499,
			-1.54558,
			-1.54615,
			-1.54671,
			-1.54726,
			-1.5478,
			-1.54832,
			-1.54883,
			-1.54933,
			-1.54982,
			-1.5503,
			-1.55076,
			-1.55122,
			-1.55166,
			-1.5521,
			-1.55252,
			-1.55294,
			-1.55335,
			-1.55374,
			-1.55413,
			-1.55451,
			-1.55488,
			-1.55524,
			-1.5556,
			-1.55594,
			-1.55628,
			-1.55661,
			-1.55694,
			-1.55725,
			-1.55756,
			-1.55786,
			-1.55815,
			-1.55844,
			-1.55872,
			-1.559,
			-1.55927,
			-1.55953,
			-1.55979,
			-1.56004,
			-1.56028,
			-1.56052,
			-1.56075,
			-1.56098,
			-1.56121,
			-1.56142,
			-1.56164,
			-1.56185,
			-1.56205,
			-1.56225,
			-1.56244,
			-1.56263,
			-1.56282,
			-1.563,
			-1.56318,
			-1.56335,
			-1.56352,
			-1.56369,
			-1.56385,
			-1.56401,
			-1.56416,
			-1.56431,
			-1.56446,
			-1.5646,
			-1.56475,
			-1.56488,
			-1.56502,
			-1.56515,
			-1.56528,
			-1.5654,
			-1.56553,
			-1.56565,
			-1.56576,
			-1.56588,
			-1.56599,
			-1.5661,
			-1.56621,
			-1.56631,
			-1.56641,
			-1.56651,
			-1.56661,
			-1.56671,
			-1.5668,
			-1.56689,
			-1.56698,
			-1.56707,
			-1.56715,
			-1.56723,
			-1.56731,
			-1.56739,
			-1.56747,
			-1.56755,
			-1.56762,
			-1.56769,
			-1.56776,
			-1.56783,
			-1.5679,
			-1.56797,
			-1.56803,
			-1.56809,
			-1.56816,
			-1.56822,
			-1.56827,
			-1.56833,
			-1.56839,
			-1.56844,
			-1.5685,
			-1.56855,
			-1.5686,
			-1.56865,
			-1.5687,
			-1.56875,
			-1.56879,
			-1.56884,
			-1.56888,
			-1.56893,
			-1.56897,
			-1.56901,
			-1.56905,
			-1.56909,
			-1.56913,
			-1.56917,
			-1.5692,
			-1.56924,
			-1.56928,
			-1.56931,
			-1.56934,
			-1.56938,
			-1.56941,
			-1.56944,
			-1.56947,
			-1.5695,
			-1.56953,
			-1.56956,
			-1.56959,
			-1.56962,
			-1.56964,
			-1.56967,
			-1.5697,
			-1.56972,
			-1.56974,
			-1.56977,
			-1.56979,
			-1.56981,
			-1.56984,
			-1.56986,
			-1.56988,
			-1.5699,
			-1.56992,
			-1.56994,
			-1.56996,
			-1.56998,
			-1.57,
			-1.57002,
			-1.57003,
			-1.57005,
			-1.57007,
			-1.57009,
			-1.5701,
			-1.57012,
			-1.57013,
			-1.57015,
			-1.57016,
			-1.57018,
			-1.57019,
			-1.57021,
			-1.57022,
			-1.57023,
			-1.57024,
			-1.57026,
			-1.57027,
			-1.57028,
			-1.57029,
			-1.5703,
			-1.57032,
			-1.57033,
			-1.57034,
			-1.57035,
			-1.57036,
			-1.57037,
			-1.57038,
			-1.57039,
			-1.5704,
			-1.57041,
			-1.57041,
			-1.57042,
			-1.57043,
			-1.57044,
			-1.57045,
			-1.57046,
			-1.57046,
			-1.57047,
			-1.57048,
			-1.57049,
			-1.57049,
			-1.5705,
			-1.57051,
			-1.57051,
			-1.57052,
			-1.57053,
			-1.57053,
			-1.57054,
			-1.57054,
			-1.57055,
			-1.57056,
			-1.57056,
			-1.57057,
			-1.57057,
			-1.57058,
			-1.57058,
			-1.57059,
			-1.57059,
			-1.5706,
			-1.5706,
			-1.5706,
			-1.57061,
			-1.57061,
			-1.57062,
			-1.57062,
			-1.57063,
			-1.57063,
			-1.57063
	};

unsigned char data_ready = 0;
unsigned int total_points = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI2_Init(void);
static void MX_CRC_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
//void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
void StartHardwareTask(void *pvParameters);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_CRC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */

  LCD_Init();

/*
  for(int i = 50;i<250;i++)
  {
	  Draw_Pixel(i, 10, 0xFF00);
	  Draw_Pixel(i, 20, 0xFF00);
	  Draw_Pixel(i, 30, 0xFF00);
	  Draw_Pixel(i, 40, 0xFF00);
	  Draw_Pixel(i, 50, 0xFF00);
	  Draw_Pixel(i, 60, 0xF000);
	  Draw_Pixel(i, 70, 0xFF00);
	  Draw_Pixel(i, 80, 0xFF00);
	  Draw_Pixel(i, 90, 0xFF00);
	  Draw_Pixel(i, 100, 0xFF00);
	  HAL_Delay(10);


  }*/

/*
  uint16_t width = 320/2;
  uint16_t heigth = 240/2;

  uint16_t pixels[width*heigth];

  uint16_t color = 0x7E0;

  for(uint32_t j =0;j<width*heigth;j++)
  {
	  if(j==width*heigth/2)
		  color = 0x704;
	  pixels[j]=color;

  }

  Address_Set(0, width-1, 0, heigth-1);

  uint32_t i = 0;
  while(i<width*heigth)
  {
	  LCD_Data_Write(pixels[i]);
	  i++;
	  HAL_Delay(1);
  }
  */



  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2000);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate(StartHardwareTask, "HW_init", 2000, NULL, tskIDLE_PRIORITY+1, NULL);
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  //osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  vTaskStartScheduler();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  //XPT2046_TouchGetCoordinates(&x, &y);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8399;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 30;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DB0_Pin|DB1_Pin|DB2_Pin|DB3_Pin
                          |DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin
                          |DB8_Pin|DB9_Pin|DB10_Pin|DB11_Pin
                          |DB12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RESET_Pin|LCD_WR_Pin|LD2_Pin|LCD_RD_Pin
                          |LCD_RS_Pin|DDS_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB13_Pin|DB14_Pin|DB15_Pin|LCD_CS_Pin
                          |TOUCH_CS_Pin|RST_VIN_Pin|RST_VOUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DB0_Pin DB1_Pin DB2_Pin DB3_Pin
                           DB4_Pin DB5_Pin DB6_Pin DB7_Pin
                           DB8_Pin DB9_Pin DB10_Pin DB11_Pin
                           DB12_Pin */
  GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB3_Pin
                          |DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin
                          |DB8_Pin|DB9_Pin|DB10_Pin|DB11_Pin
                          |DB12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RESET_Pin LCD_WR_Pin LD2_Pin LCD_RD_Pin
                           LCD_RS_Pin DDS_CS_Pin */
  GPIO_InitStruct.Pin = LCD_RESET_Pin|LCD_WR_Pin|LD2_Pin|LCD_RD_Pin
                          |LCD_RS_Pin|DDS_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DB13_Pin DB14_Pin DB15_Pin LCD_CS_Pin
                           TOUCH_CS_Pin RST_VIN_Pin RST_VOUT_Pin */
  GPIO_InitStruct.Pin = DB13_Pin|DB14_Pin|DB15_Pin|LCD_CS_Pin
                          |TOUCH_CS_Pin|RST_VIN_Pin|RST_VOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_IRQ_Pin */
  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
extern void touchgfxSignalVSync(void);

void StartHardwareTask(void* pvParameters)
{
	/* init code for USB_DEVICE */
	MX_USB_DEVICE_Init();
	/* USER CODE BEGIN 5 */
	HAL_TIM_Base_Start_IT(&htim2);
	MX_TouchGFX_Process();
	while(1)
	{

	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
//void StartDefaultTask(void const * argument)
//{
//  /* init code for USB_DEVICE */
//  MX_USB_DEVICE_Init();
//  /* USER CODE BEGIN 5 */
//	HAL_TIM_Base_Start_IT(&htim2);
//	MX_TouchGFX_Process();
//	while(1)
//	{
//
//	}
//}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
//void StartDefaultTask(void const * argument)
//{
//  /* init code for USB_DEVICE */
//  MX_USB_DEVICE_Init();
//  /* USER CODE BEGIN 5 */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
  /* USER CODE END 5 */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim->Instance == TIM2)
	touchgfxSignalVSync();
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
