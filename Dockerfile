FROM eu.gcr.io/list-limited/gcc

WORKDIR /app
COPY . /app

RUN mkdir build && cd build \
      && cmake ..\
      && make 

RUN chmod a+x /app/entrypoint.sh
