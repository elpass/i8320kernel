cmd_drivers/media/video/built-in.o :=  arm-none-eabi-ld -EL    -r -o drivers/media/video/built-in.o drivers/media/video/videodev.o drivers/media/video/v4l2-int-device.o drivers/media/video/v4l2-common.o drivers/media/video/v4l1-compat.o drivers/media/video/isp/built-in.o drivers/media/video/omap34xxcam.o drivers/media/video/cam_pmic.o drivers/media/video/m4mo_platform.o drivers/media/video/m4mo.o drivers/media/video/s5ka3dfx_platform.o drivers/media/video/s5ka3dfx.o drivers/media/video/videobuf-core.o drivers/media/video/videobuf-dma-sg.o drivers/media/video/videobuf-dma-contig.o drivers/media/video/omap/built-in.o 