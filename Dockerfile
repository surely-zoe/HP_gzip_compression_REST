FROM ubuntu

WORKDIR /home

RUN apt-get update &&\
apt-get install -y libcpprest-dev

COPY server /home/server

RUN cd server &&\
make 

CMD server/fin
