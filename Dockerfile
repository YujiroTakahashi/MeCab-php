FROM ubuntu:22.04 AS main-image
ENV DEBIAN_FRONTEND=noninteractive \
    LANG=en_US.UTF-8 \
    TZ='Asia/Tokyo'
RUN set -xe \
    && apt update \
    && apt install -y --install-recommends \
        software-properties-common \
    && add-apt-repository -y ppa:ondrej/php \
    && apt update \
    && apt install -y --install-recommends \
        mecab-ipadic-utf8 \
        mecab-jumandic-utf8 \
        mecab-naist-jdic-eucjp \
        php8.3 \
        php8.3-cli \
        php8.3-common \
        sudo \
        unidic-mecab \
    && groupadd -g 1000 croco \
    && useradd -m -s /bin/bash -u 1000 -g 1000 croco \
    && echo "croco ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers

FROM main-image AS build-image
RUN set -xe \
    && apt update \
    && apt install -y --install-recommends \
        autoconf \
        automake \
        cmake \
        g++ \
        gcc \
        libmecab-dev \
        libtool \
        make \
        php8.3-dev 

FROM build-image AS mecab-image
COPY mecab /opt/croco/mecab
WORKDIR /opt/croco/mecab
RUN set -xe \
    && mkdir build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make -j \
    && make install

FROM main-image AS runtime-image
COPY --from=mecab-image /usr/lib/x86_64-linux-gnu/libmecab.so /usr/lib/x86_64-linux-gnu/libmecab.so
COPY --from=mecab-image /usr/lib/php/20230831/mecab.so /usr/lib/php/20230831/mecab.so
RUN set -xe \
    && echo "extension=mecab.so" > /etc/php/8.3/mods-available/mecab.ini \
    && cd /etc/php/8.3/cli/conf.d \
    && ln -s /etc/php/8.3/mods-available/mecab.ini ./30-mecab.ini

USER croco
CMD [ "bash" ]