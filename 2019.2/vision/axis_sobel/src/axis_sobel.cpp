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

#include "axis_sobel.h"

void sobel_accel(AXI_STREAM& input, AXI_STREAM& output_x, AXI_STREAM& output_y,
                unsigned short rows,
                unsigned short cols) {
    #pragma HLS INTERFACE axis port=input
    #pragma HLS INTERFACE axis port=output_x
    #pragma HLS INTERFACE axis port=output_y
    #pragma HLS INTERFACE s_axilite port=rows               bundle=control
    #pragma HLS INTERFACE s_axilite port=cols               bundle=control
    #pragma HLS INTERFACE s_axilite port=return             bundle=control

    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, NPC1> _src(rows, cols);
    xf::cv::Mat<OUT_TYPE, HEIGHT, WIDTH, NPC1> _dstgx(rows, cols);
    xf::cv::Mat<OUT_TYPE, HEIGHT, WIDTH, NPC1> _dstgy(rows, cols);

    #pragma HLS stream variable=_src.data dim=1 depth=2
    #pragma HLS stream variable=_dstgx.data dim=1 depth=2
    #pragma HLS stream variable=_dstgy.data dim=1 depth=2
	#pragma HLS dataflow
    xf::cv::AXIvideo2xfMat(input, _src);
 
    xf::cv::Sobel<XF_BORDER_CONSTANT, FILTER_WIDTH, IN_TYPE, OUT_TYPE, HEIGHT, WIDTH, NPC1, XF_USE_URAM>(_src, 
                                                                                                        _dstgx,
                                                                                                        _dstgy);

    xf::cv::xfMat2AXIvideo(_dstgx, output_x);
    xf::cv::xfMat2AXIvideo(_dstgy, output_y);
    return;
}
