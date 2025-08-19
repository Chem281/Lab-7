# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

RUN apt-get clean && \
    apt-get update && \
    apt-get install -y \
                       curl \
                       cmake \
                       vim \
                       g++ \
                       git \
                       openbabel \
                       python3 \
                       python3-pip \
                       python3-dev \
                       build-essential

RUN curl https://sh.rustup.rs -sSf | sh -s -- --default-toolchain nightly -y && \
    . "$HOME/.cargo/env" && \
    rustc --version && \
    cargo --version

# Add Cargo to PATH permanently
ENV PATH="/root/.cargo/bin:${PATH}"

# Install Python packages
RUN pip3 install --no-cache-dir pandas rdkit

# Copy the entrypoint file into the Docker image
COPY entrypoint.sh /entrypoint.sh

# Make the entrypoint script executable
RUN chmod +x /entrypoint.sh

# Define the entrypoint script that should be run
ENTRYPOINT ["/entrypoint.sh"]
