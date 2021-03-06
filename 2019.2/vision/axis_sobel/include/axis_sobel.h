/*
 * Copyright 2019 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _XF_SOBEL_CONFIG_H_
#define _XF_SOBEL_CONFIG_H_

#include "hls_stream.h"

#include "common/xf_common.hpp"
#include "common/xf_utility.hpp"
#include "imgproc/xf_sobel.hpp"
#include "common/xf_infra.hpp"

#include "axis_sobel_params.h"

typedef unsigned int uint32_t;

//////////////  To set the parameters in Top and Test bench //////////////////

/* Define the AXI Stream type */
const int PPC = 8;
const int PIXEL_WIDTH = 8 * PPC; /* 8 pixels per clock*/
// typedef ap_axis <PIXEL_WIDTH,1,1,1> AXI_T;
// hls::stream<ap_uint<128>
typedef hls::stream<xf::cv::ap_axiu<PIXEL_WIDTH, 1, 1, 1> > AXI_STREAM;
/// typedef ap_axiu<PIXEL_WIDTH, 1, 1, 1> package_t;
// typedef hls::stream<package_t> AXI_STREAM;

/* config width and height */
#define WIDTH 1920
#define HEIGHT 1080

//#define DDEPTH XF_8UC1

#if FILTER_SIZE_3
#define FILTER_WIDTH 3
#elif FILTER_SIZE_5
#define FILTER_WIDTH 5
#elif FILTER_SIZE_7
#define FILTER_WIDTH 7
#endif
#if GRAY
#if (FILTER_WIDTH == 3 | FILTER_WIDTH == 5)
#if RO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC8
#endif
#if NO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC1
#endif
#endif

#if (FILTER_WIDTH == 7)
#if NO
#define IN_TYPE XF_8UC1
#define OUT_TYPE XF_8UC1
#define NPC1 XF_NPPC1
#endif
#endif

#else

#if (FILTER_WIDTH == 3 | FILTER_WIDTH == 5)
#if RO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC8
#endif
#if NO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC1
#endif
#endif

#if (FILTER_WIDTH == 7)
#if NO
#define IN_TYPE XF_8UC3
#define OUT_TYPE XF_8UC3
#define NPC1 XF_NPPC1
#endif
#endif
#endif



void sobel_accel(AXI_STREAM& input, 
                AXI_STREAM& output_x, 
                AXI_STREAM& output_y,
                unsigned short rows,
                unsigned short cols); 

#endif //  _XF_SOBEL_CONFIG_H_
