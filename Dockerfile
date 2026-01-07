FROM gcc:13

WORKDIR /app

COPY src/ src/

RUN g++ src/simulator.cpp -o simulator

CMD ["./simulator"]
