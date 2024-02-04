FROM ubuntu:latest
USER root
RUN apt-get update ; apt-get install -y g++ libmysqlcppconn-dev mysql-server  build-essential cmake libasio-dev git
WORKDIR /app
ADD ./ /app
RUN mkdir modules && cd ./modules && git clone https://github.com/CrowCpp/Crow.git && cd ./Crow && mkdir build && cd ./build && cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && make install
ENTRYPOINT service mysql start \
; service mysql status ; sleep 3 \
; mysql -uroot -e "CREATE DATABASE chimie;" \
; mysql -uroot -e "CREATE USER 'test'@'localhost' IDENTIFIED BY 'test';" \
; mysql -uroot -e "GRANT ALL PRIVILEGES ON chimie.* TO 'test'@'localhost';" \
; echo -e "\n\n\n--------------\nSleeping for 10 seconds...\n--------------\n\n" \
; g++ main.cpp -o main -lmysqlcppconn\
; g++ reseter.cpp -o first -lmysqlcppconn\
;./first\
;./main

