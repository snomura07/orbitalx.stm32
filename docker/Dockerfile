FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    gcc-arm-none-eabi \
    gdb-multiarch \
    make \
    cmake \
    libstdc++-arm-none-eabi-newlib \
    && apt clean

# 作業ディレクトリを設定
WORKDIR /var/opt/project

# 必要な環境変数を設定
ENV PATH="/usr/bin:$PATH"

# デフォルトコマンド（コンテナ実行時に起動するシェル）
CMD ["bash"]
