# ---------- Build Stage ----------
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-system-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the whole project (including the submodule)
COPY . .

# Ensure submodules exist (harmless if already present)
RUN git submodule update --init --recursive

# Configure and build
RUN cmake -S bot -B build
RUN cmake --build build --config Release -j$(nproc)


# ---------- Runtime Stage ----------
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    libboost-system1.83.0 \
    libssl3 \
    libcurl4 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /app/build/bot .

CMD ["./bot"]
