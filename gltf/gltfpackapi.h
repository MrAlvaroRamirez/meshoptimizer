/**
 * gltfpack - version 0.13
 *
 * Copyright (C) 2016-2020, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
 * Report bugs and download new versions at https://github.com/zeux/meshoptimizer
 *
 * This application is distributed under the MIT License. See notice at the end of this file.
 */

#ifndef GLTFPACKAPI_H_INCLUDED__
#define GLTFPACKAPI_H_INCLUDED__

struct Settings
{
	int pos_bits;
	int tex_bits;
	int nrm_bits;
	int col_bits;

	int trn_bits;
	int rot_bits;
	int scl_bits;

	int anim_freq;
	bool anim_const;

	bool keep_nodes;
	bool keep_materials;
	bool keep_extras;

	bool mesh_merge;
	bool mesh_instancing;

	float simplify_threshold;
	bool simplify_aggressive;
	float simplify_debug;

	int meshlet_debug;

	bool texture_ktx2;
	bool texture_uastc;
	bool texture_embed;
	bool texture_toktx;

	int texture_quality;
	float texture_scale;
	bool texture_pow2;

	bool quantize;

	bool compress;
	bool compressmore;
	bool fallback;

	int verbose;

	bool use_uint8_joints;
};

int gltfpack(const char* input, const char* output, const char* report, Settings settings);

#endif // GLTFPACKAPI_H_INCLUDED__

/**
 * Copyright (c) 2016-2020 Arseny Kapoulkine
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
