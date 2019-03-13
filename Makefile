

FRAMES_JPEG=$(wildcard frames/*.jpg)

#ORDERED_DITHER?=h4x4a
ORDERED_DITHER?=h6x6a
#ORDERED_DITHER?=c6x6w
#ORDERED_DITHER?=c6x6b
#ORDERED_DITHER?=c6x6w
#ORDERED_DITHER?=c7x7b
#ORDERED_DITHER?=c7x7w

# test mode: 6min w/ 1fps (360 frames)
DURATION?=00:06:00
FPS?=1

all: $(FRAMES_JPEG:%.jpg=%.gif)

%.gif: %.jpg
	convert $< -ordered-dither ${ORDERED_DITHER} -colors 2 -monochrome $@

frames:
	ffmpeg -i input.mp4 -t ${DURATION} -vf scale=-2:400,crop=640:384,fps=${FPS} frames/%03d.jpg

clean:
	rm -f $(FRAMES_JPEG) $(FRAMES_JPEG:%.jpg=%.gif)

.PHONY: frames