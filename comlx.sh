#!/bin/bash

gcc src\*.c \
	-o ./bin/cube \
	-lglfw -ldl -lGL \
	-I ./include \
	-I ./include/myh