/*
 * drivers/media/video/isp/omap_resizer.h
 *
 * Include file for Resizer module in TI's OMAP3430 ISP
 *
 * Copyright (C) 2008 Texas Instruments, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef OMAP_RESIZER_H
#define OMAP_RESIZER_H

#include <linux/types.h>
#include <linux/videodev2.h>
#include <mach/isp_user.h>


#define RSZ_INTYPE_YCBCR422_16BIT	0
#define RSZ_INTYPE_PLANAR_8BIT		1
#define RSZ_PIX_FMT_UYVY		1	/* cb:y:cr:y */
#define RSZ_PIX_FMT_YUYV		0	/* y:cb:y:cr */

enum config_done {
	STATE_CONFIGURED_,			/* Resizer driver configured
						 * by application.
						 */
	STATE_NOT_CONFIGURED			/* Resizer driver not
						 * configured by application.
						 */
};

typedef void (*rsz_callback) (void *arg1);
/*
 * Contains the status of hardware and channel
 */
struct rsz_stat {
	__u32 ch_busy;		/* 1: channel is busy, 0: channel is ready */
	__u32 hw_busy;		/* 1: hardware is busy, 0: hardware is ready */
};

struct rsz_yenh {
	__s32 type;				/* represents luma enable or
						 * disable.
						 */
	__u8 gain;			/* represents gain. */
	__u8 slop;			/* represents slop. */
	__u8 core;			/* Represents core value. */
};

struct rsz_params {
	__s32 in_hsize;				/* input frame horizontal
						 * size.
						 */
	__s32 in_vsize;				/* input frame vertical size */
	__s32 in_pitch;				/* offset between two rows of
						 * input frame.
						 */
	__s32 inptyp;				/* for determining 16 bit or
						 * 8 bit data.
						 */
	__s32 vert_starting_pixel;		/* for specifying vertical
						 * starting pixel in input.
						 */
	__s32 horz_starting_pixel;		/* for specyfing horizontal
						 * starting pixel in input.
						 */
	__s32 cbilin;				/* # defined, filter with luma
						 * or bi-linear interpolation.
						 */
	__s32 pix_fmt;				/* # defined, UYVY or YUYV */
	__s32 out_hsize;			/* output frame horizontal
						 * size.
						 */
	__s32 out_vsize;				/* output frame vertical
						 * size.
						 */
	__s32 out_pitch;			/* offset between two rows of
						 * output frame.
						 */
	__s32 hstph;				/* for specifying horizontal
						 * starting phase.
						 */
	__s32 vstph;				/* for specifying vertical
						 * starting phase.
						 */
	__u16 tap4filt_coeffs[32];		/* horizontal filter
						 * coefficients.
						 */
	__u16 tap7filt_coeffs[32];		/* vertical filter
						 * coefficients.
						 */
	struct rsz_yenh yenh_params;
};

/*
 * IOCTLS definition
 */
#define RSZ_IOC_BASE	'R'

/*
 * Ioctl options which are to be passed while calling the ioctl
 */
#define RSZ_S_PARAM  _IOWR(RSZ_IOC_BASE, 1, struct isp_node)
#define RSZ_G_PARAM  _IOWR(RSZ_IOC_BASE, 2, struct isp_node)
#define RSZ_G_STATUS _IOWR(RSZ_IOC_BASE, 3, struct rsz_stat)
#define RSZ_REQBUF   _IOWR(RSZ_IOC_BASE, 4, struct v4l2_requestbuffers)
#define RSZ_QUERYBUF _IOWR(RSZ_IOC_BASE, 5, struct v4l2_buffer)
#define RSZ_QUEUEBUF _IOWR(RSZ_IOC_BASE, 6, struct v4l2_buffer)
#define RSZ_RESIZE   _IOWR(RSZ_IOC_BASE, 7, int)

#define RSZ_IOC_MAXNR	7

#endif

int rsz_get_resource(void);
void rsz_put_resource(void);
int rsz_configure(struct rsz_params *params, rsz_callback callback,
		  u32 num_video_buffers, void *arg1);
int rsz_begin(u32 input_buffer_index,
			int output_buffer_index, u32 out_off, u32 out_phy_add,
			u32 in_phy_add, u32 in_off);
