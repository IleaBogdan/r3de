#!/bin/bash

gcc src/*.c \
	-o ./bin/cube \
	-lglfw -ldl -lGL -lm \
	-I ./include \
	-I ./include/myh
