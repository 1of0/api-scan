FROM 1of0/llvm:3.8

ADD ./ /var/build/
WORKDIR /var/build
RUN /bin/bash /var/build/.docker-build.sh