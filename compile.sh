#!/bin/bash
rm testBuild
g++ main.cpp -o testBuild -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
./testBuild
