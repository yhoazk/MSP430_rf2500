## Podman image for msp-gcc
##   The purpose of this container is to mount the src code
##   as a volume and compile it, giving the elf as a result

From registry.fedoraproject.org/fedora:30

#RUN dnf update -y && \
RUN    mkdir -p /opt/msp_gcc /downloads
# mount the volume where the compiler is stored
VOLUME [ "/home/porko/Downloads:/downloads" ]
RUN cp /home/porko/Downloads/msp430-gcc-full-linux-x64-installer-6.1.1.0.run /opt/msp_gcc &&\
        chmod +x /opt/msp_gcc/msp430-gcc-full-linux-x64-installer-6.1.1.0.run &&\
        /opt/msp_gcc/msp430-gcc-full-linux-x64-installer-6.1.1.0.run


