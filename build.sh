#!/bin/bash

docker build -f Dockerfile.dev -t api-scan .
docker run -tiv /var/ccache:/var/ccache api-scan
docker commit $(docker ps -qln1) api-scan