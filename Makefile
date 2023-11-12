

FRAMES_JPEG=$(wildcard frames/*.jpg)

ORDERED_DITHER?=h4x4a
#ORDERED_DITHER?=h6x6a
#ORDERED_DITHER?=c6x6w
#ORDERED_DITHER?=c6x6b
#ORDERED_DITHER?=c6x6w
#ORDERED_DITHER?=c7x7b
#ORDERED_DITHER?=c7x7w

# test mode: 120min w/ 1fps (7200 frames)
DURATION?=02:00:00
FPS?=1

all: $(FRAMES_JPEG:%.jpg=%.dat)

gif: $(FRAMES_JPEG:%.jpg=%.gif)

%.gif: %.jpg
	echo convert $< -colorspace gray -colors 2 $@
	convert $< -ordered-dither ${ORDERED_DITHER} -colors 2 -monochrome $@

%.dat: %.gif
	python convert.py $< $@

frames: input.mp4
	ffmpeg -i input.mp4 -t ${DURATION} -vf scale=-2:400,crop=640:384,fps=${FPS} frames/%06d.jpg

frames-with-subtitle:
	ffmpeg -i input.mp4 -t ${DURATION} -vf scale=-2:400,crop=640:384,subtitles=subtitle.srt,fps=${FPS} frames/%06d.jpg

clean:
	rm -f $(FRAMES_JPEG:%.jpg=%.gif)
	rm -f $(FRAMES_JPEG:%.jpg=%.dat)

.PHONY: frames