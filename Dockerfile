FROM gcc:latest
WORKDIR /usr/src/myapp
COPY . .
RUN g++ -o sistema_bar src/main.cpp
CMD ["./sistema_bar"]